// license:BSD-3-Clause
// copyright-holders:eziochiu,Drunken Cat

#include "emu.h"
#include "ips.h"
#include "emuopts.h"
#include "hash.h"
#include "fileio.h"
#include "romload.h"
#include "path.h"

#include "corestr.h"

#include <vector>
#include <string>
#include <cstring>
#include <memory>

#include <map>
#include <algorithm>
#include <sstream>

namespace ips {

#define IPS_SIGNATURE	"PATCH"
#define IPS_TAG_EOF	"EOF"
#define INDEX_EXT	".dat"
#define IPS_EXT		".ips"
#define CRC_STAG	"CRC("
#define CRC_ETAG	")"

#define BYTE3_TO_UINT(bp) \
	(((bp[0] << 16) & 0x00ff0000) | \
	 ((bp[1] << 8)  & 0x0000ff00) | \
	 ((bp[2] << 0)  & 0x000000ff))

#define BYTE2_TO_UINT(bp) \
	(((bp[0] << 8) & 0xff00) | \
	 ((bp[1] << 0) & 0x00ff))

struct ips_chunk
{
    u32 offset;
    u32 size;
    std::vector<u8> data;
};

struct ips_entry
{
    std::string rom_name;
    std::string ips_name;
    std::vector<ips_chunk> chunks;
    std::vector<std::string> dependencies;
    std::vector<std::string> conflicts;

    size_t current_chunk_index;
    u32 current_offset_remain;
    u32 current_data_remain;
};

static std::vector<std::unique_ptr<ips_entry>> s_ips_list;
static std::string s_error_string;
static int s_warning_count = 0;

std::string &get_error_string()
{
    return s_error_string;
}

int get_warning_count()
{
    return s_warning_count;
}

static const romload::file *find_rom_file(const tiny_rom_entry *romp, const char *name)
{
	for (romload::region const &region : romload::regions(romp))
	{
		if (!region.is_romdata())
			continue;

		for (romload::file const &file : region.get_files())
		{
			if (core_stricmp(file.get_name(), name) == 0)
				return &file;
		}
	}

	return nullptr;
}

//缘来是你
//================================== IPS CRC =========================================>>>
static const romload::file *find_rom_file_by_crc(const tiny_rom_entry *romp, const char *crc_str)
{
	if (!crc_str) return nullptr;

	std::string crc_val(crc_str);
	size_t start_paren = crc_val.find('(');
	if (start_paren == std::string::npos) return nullptr;
	size_t end_paren = crc_val.find(')', start_paren);
	if (end_paren == std::string::npos) return nullptr;
	std::string target_crc = crc_val.substr(start_paren + 1, end_paren - start_paren - 1);
	if (target_crc.length() != 8) return nullptr;

	for (romload::region const &region : romload::regions(romp))
	{
		if (!region.is_romdata())
			continue;

		for (romload::file const &file : region.get_files())
		{
			util::hash_collection rom_hashes(file.get_hashdata());
			u32 crc_val;
			if (rom_hashes.crc(crc_val))
			{
				std::string rom_crc = string_format("%08X", crc_val);
				if (core_stricmp(rom_crc.c_str(), target_crc.c_str()) == 0)
					return &file;
			}
		}
	}
	return nullptr;
}

// IPS 读取子目录
static bool load_ips_file(running_machine &machine, std::vector<ips_chunk> &chunks, const std::vector<std::string> &paths)
{
    emu_file file(machine.options().value(OPTION_IPSPATH), OPEN_FLAG_READ);
    std::error_condition filerr;
    std::string opened_path;
    for (const auto &p : paths)
    {
        filerr = file.open(p.c_str());
        if (!filerr)
        {
            opened_path = p;
            break;
        }
    }

    if (filerr)
    {
        s_error_string += string_format("ERROR: %s: open fail\n", paths.front().c_str());
#if USE_WARNING
		osd_printf_warning("IPS: %s\n", s_error_string.c_str());
#endif
        s_warning_count++;
        return false;
    }

    osd_printf_verbose("IPS: loading ips \"%s\"\n", opened_path.c_str());
//====================================================================================================>>>

    u8 buffer[8];
    if (file.read(buffer, 5) != 5 || memcmp(buffer, IPS_SIGNATURE, 5) != 0)
    {
        s_error_string += string_format("ERROR: %s: incorrect IPS header\n", opened_path.c_str());
#if USE_WARNING
		osd_printf_warning("IPS: %s\n", s_error_string.c_str());
#endif
        file.close();
        s_warning_count++;
        return false;
    }
	
    bool error = false;
    bool eof_ok = false;

		while (true)
		{
			u8 offset_buf[3];
			if (file.read(offset_buf, 3) != 3)
			{
				error = true;
				break;
			}
		
			if (memcmp(offset_buf, IPS_TAG_EOF, 3) == 0)
			{
				eof_ok = true;
				break;
			}

        u32 offset = BYTE3_TO_UINT(offset_buf);

        u8 size_buf[2];
        if (file.read(size_buf, 2) != 2)
        {
            error = true;
            break;
        }

        u16 size = BYTE2_TO_UINT(size_buf);
        bool bRLE = false;
        u16 rle_size = 0;

        if (size == 0)
        {
            if (file.read(size_buf, 2) != 2)
            {
                error = true;
                break;
            }
             
            rle_size = BYTE2_TO_UINT(size_buf);
            bRLE = true;
            size = 1;
        }

        ips_chunk chunk;
        chunk.offset = offset;
        
        if (bRLE)
        {
            u8 fill_byte;
            if (file.read(&fill_byte, 1) != 1)
            {
                error = true;
                break;
            }
            
            chunk.size = rle_size;
            chunk.data.resize(rle_size);
            std::memset(chunk.data.data(), fill_byte, rle_size);
        }
        else
        {
            chunk.size = size;
            chunk.data.resize(size);
            if (file.read(chunk.data.data(), size) != size)
            {
                error = true;
                break;
            }
        }

        chunks.push_back(std::move(chunk));
    }

    file.close();

    if (error || !eof_ok)
    {
        chunks.clear();
        s_error_string += string_format("ERROR: %s: incomplete or malformed IPS file\n", opened_path.c_str());
#if USE_WARNING
        osd_printf_warning("IPS: %s\n", s_error_string.c_str());
#endif
        s_warning_count++;
        return false;
    }
 return true;
}

// ================醉猫(Drunken Cat)==== 依赖/冲突 ====================>>>
static void parse_patch_metadata(const char* line, ips_entry* entry)
{
    auto split_by_comma = [](const std::string& s, std::vector<std::string>& out) {
        size_t start = 0, end;
        while ((end = s.find(',', start)) != std::string::npos) {
            std::string token = s.substr(start, end - start);
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            if (!token.empty()) out.push_back(token);
            start = end + 1;
        }
        std::string last = s.substr(start);
        last.erase(0, last.find_first_not_of(" \t"));
        last.erase(last.find_last_not_of(" \t") + 1);
        if (!last.empty()) out.push_back(last);
    };

    const char* deps = strstr(line, "need=");
    if (deps) {
        const char* start = deps + 5;
        while (*start && isspace((u8)*start)) start++;
        const char* end = start;
        while (*end && !isspace((u8)*end)) end++;
        if (end > start) {
            std::string dep_str(start, end - start);
            split_by_comma(dep_str, entry->dependencies);
        }
    }

    const char* confs = strstr(line, "noconf=");
    if (confs) {
        const char* start = confs + 7;
        while (*start && isspace((u8)*start)) start++;
        const char* end = start;
        while (*end && !isspace((u8)*end)) end++;
        if (end > start) {
            std::string conf_str(start, end - start);
            split_by_comma(conf_str, entry->conflicts);
        }
    }
}
//===================================================================>>>

static bool parse_ips_patch(running_machine &machine, const char *patch_name, const tiny_rom_entry *romp)
{
    std::string fname_base = std::string(machine.system().name).append(PATH_SEPARATOR).append(patch_name);
    std::string fname = fname_base + INDEX_EXT;
    
    osd_printf_info("IPS: parse_ips_patch looking for dat file: '%s'\n", fname.c_str());
    osd_printf_info("IPS: ipspath = '%s'\n", machine.options().value(OPTION_IPSPATH));

    emu_file fpDat(machine.options().value(OPTION_IPSPATH), OPEN_FLAG_READ);
    std::error_condition open_err = fpDat.open(fname.c_str());
    if (open_err)
    {
        osd_printf_info("IPS: ERROR - failed to open dat file: '%s' (error: %s)\n", fname.c_str(), open_err.message().c_str());
        s_error_string += string_format("ERROR: %s: IPS file is not found\n", patch_name);
#if USE_WARNING
		osd_printf_warning("IPS: %s\n", s_error_string.c_str());
#endif		
        s_warning_count++;
        return false;
    }

    osd_printf_info("IPS: Successfully opened dat file: '%s'\n", fname.c_str());
    
    char buffer[1024];
    int line_count = 0;
    while (fpDat.gets(buffer, sizeof(buffer)))
    {
        line_count++;
        char *p = buffer;
        while (*p && isspace((u8)*p)) p++;
        
        if (*p == 0 || *p == '#' || *p == '[') continue;

        osd_printf_info("IPS: Parsing line %d: '%s'\n", line_count, p);
        
        char *line_start = p;
        std::vector<char> line_copy(line_start, line_start + strlen(line_start) + 1);
        char *copy_ptr = line_copy.data();
        
        while (*copy_ptr && isspace((u8)*copy_ptr)) copy_ptr++;
        if (!*copy_ptr) continue;
        char *rom_name = copy_ptr;
        while (*copy_ptr && !isspace((u8)*copy_ptr)) copy_ptr++;
        if (*copy_ptr) *copy_ptr++ = '\0';

        while (*copy_ptr && isspace((u8)*copy_ptr)) copy_ptr++;
        if (!*copy_ptr)
        {
            s_error_string += string_format("ERROR: IPS file is not defined for ROM entry \"%s\"\n", rom_name);
            continue;
        }
        char *ips_entry_name = copy_ptr;
        while (*copy_ptr && !isspace((u8)*copy_ptr)) copy_ptr++;
        if (*copy_ptr) *copy_ptr++ = '\0';
		
        while (*copy_ptr && isspace((u8)*copy_ptr)) copy_ptr++;
        char *crc = (*copy_ptr) ? copy_ptr : nullptr;
        
        if (crc)
        {
            char *crc_end = crc + strlen(crc) - 1;
            while (crc_end > crc && isspace((u8)*crc_end)) *crc_end-- = 0;
			
//缘来是你
//======================== 跳过空 CRC 空值 =================================>>>
            char *paren_start = strchr(crc, '(');
            char *paren_end = strchr(crc, ')');
            if (paren_start && paren_end && paren_end > paren_start)
            {
                size_t inner_len = paren_end - paren_start - 1;
                if (inner_len == 8)
                {
                    bool all_zero = true;
                    for (size_t i = 0; i < inner_len; i++)
                    {
                        if (paren_start[1 + i] != '0')
                        {
                            all_zero = false;
                            break;
                        }
                    }
                    if (all_zero)
                    {
                        osd_printf_info("IPS: CRC value is all zeros, ignoring CRC and falling back to filename match\n");
                        crc = nullptr;
                    }
                }
            }
		}

        const romload::file *rom_file = nullptr;

        if (crc)
            rom_file = find_rom_file_by_crc(romp, crc);

        if (!rom_file)
            rom_file = find_rom_file(romp, rom_name);

        if (!rom_file)
        {
            if (crc)
                s_error_string += string_format("ERROR: ROM with CRC %s not found for IPS file \"%s\"\n", crc, patch_name);
            else
                s_error_string += string_format("ERROR: ROM entry \"%s\" not found for IPS file \"%s\"\n", rom_name, patch_name);
#if USE_WARNING
				osd_printf_warning("IPS: %s\n", s_error_string.c_str());
#endif
            s_warning_count++;
            continue;
        }

        std::string ips_dir_str = util::path_concat(machine.system().name, patch_name);
        std::string ips_name_str = ips_entry_name;

        std::string sys = machine.system().name;
		if (ips_name_str.size() > sys.size() &&
            ips_name_str.compare(0, sys.size(), sys) == 0 &&
			ips_name_str[sys.size()] == '\\')
        {
            ips_name_str = ips_name_str.substr(sys.size() + 1);
        }

        auto entry = std::make_unique<ips_entry>();
        entry->rom_name = rom_file->get_name();
        entry->ips_name = ips_name_str;

        parse_patch_metadata(line_start, entry.get());

		//IPS 优先子目录模式        
        std::vector<std::string> candidate_paths;
        candidate_paths.push_back(util::path_concat(ips_dir_str, ips_name_str + IPS_EXT));
        candidate_paths.push_back(util::path_concat(machine.system().name, ips_name_str + IPS_EXT));
        
        if (!load_ips_file(machine, entry->chunks, candidate_paths))
//==================================================================================>>>
        {
            osd_printf_info("IPS: ERROR - load_ips_file FAILED for '%s'\n", entry->ips_name.c_str());
            s_error_string += string_format("ERROR: %s/%s: IPS data could not be loaded\n", ips_dir_str, entry->ips_name);
#if USE_WARNING
			osd_printf_warning("IPS: %s\n", s_error_string.c_str());
#endif
            continue;
        }
        
        if (entry->chunks.empty())
        {
            osd_printf_info("IPS: ERROR - IPS chunks empty for '%s'\n", entry->ips_name.c_str());
            s_error_string += string_format("ERROR: %s/%s: IPS data is empty\n", ips_dir_str, entry->ips_name);
            continue;
        }

        osd_printf_info("IPS: SUCCESS - Loaded %zu chunks for ROM '%s' from IPS '%s'\n", entry->chunks.size(), rom_name, entry->ips_name.c_str());
        s_ips_list.push_back(std::move(entry));
    }
    
    osd_printf_info("IPS: parse_ips_patch complete. Total entries in s_ips_list: %zu\n", s_ips_list.size());
    fpDat.close();
    return true;
}

// ========== 醉猫(Drunken Cat) ========== 冲突检测 ====================>>>
ConflictType check_chunk_conflict(const ips_chunk& a, const ips_chunk& b)
{
    u32 a_end = a.offset + a.size - 1;
    u32 b_end = b.offset + b.size - 1;
    
    if (a_end < b.offset || b_end < a.offset)
        return ConflictType::NONE;
    
    u32 overlap_start = std::max(a.offset, b.offset);
    u32 overlap_end = std::min(a_end, b_end);
    u32 overlap_size = overlap_end - overlap_start + 1;
    
    for (u32 i = 0; i < overlap_size; i++) {
        u8 a_byte = a.data[(overlap_start - a.offset) + i];
        u8 b_byte = b.data[(overlap_start - b.offset) + i];
        if (a_byte != b_byte)
            return ConflictType::DATA_CONFLICT;
    }
    return ConflictType::ADDRESS_ONLY;
}

static bool patches_conflict(const ips_entry* p1, const ips_entry* p2)
{
    if (p1->rom_name != p2->rom_name)
        return false;
    
    bool has_real_conflict = false;
    for (const auto& c1 : p1->chunks) {
        for (const auto& c2 : p2->chunks) {
            ConflictType result = check_chunk_conflict(c1, c2);
            if (result == ConflictType::DATA_CONFLICT) {
                s_error_string += string_format(
                    "  Conflict: %s(0x%X) vs %s(0x%X) modifying the same address but with different data\n",
                    p1->ips_name.c_str(), c1.offset,
                    p2->ips_name.c_str(), c2.offset);
                has_real_conflict = true;
            } else if (result == ConflictType::ADDRESS_ONLY) {
                osd_printf_verbose("IPS: %s and %s modify the same address but have the same data\n",
                    p1->ips_name.c_str(), p2->ips_name.c_str());
            }
        }
    }
    return has_real_conflict;
}

static void detect_all_conflicts()
{
    for (size_t i = 0; i < s_ips_list.size(); i++) {
        for (size_t j = i + 1; j < s_ips_list.size(); j++) {
            if (patches_conflict(s_ips_list[i].get(), s_ips_list[j].get())) {
                s_error_string += string_format(
                    "WARNING: IPS patch conflict: '%s' conflicts with '%s'\n",
                    s_ips_list[i]->ips_name.c_str(),
                    s_ips_list[j]->ips_name.c_str());
                s_warning_count++;
            }
        }
    }
}

// ================醉猫(Drunken Cat)===== 依赖关系 ====================>>>
static bool verify_patch_dependencies()
{
    bool all_valid = true;
    std::map<std::string, ips_entry*> patch_map;
    for (const auto& patch : s_ips_list)
        patch_map[patch->ips_name] = patch.get();
    
    for (const auto& patch : s_ips_list) {
        for (const auto& dep_name : patch->dependencies) {
            auto it = patch_map.find(dep_name);
            if (it == patch_map.end()) {
                s_error_string += string_format(
                    "ERROR: Patch '%s' depends on patch '%s' not found\n",
                    patch->ips_name.c_str(), dep_name.c_str());
                all_valid = false;
            }
        }
        for (const auto& conf_name : patch->conflicts) {
            auto it = patch_map.find(conf_name);
            if (it != patch_map.end()) {
                s_error_string += string_format(
                    "ERROR: Patches '%s' and Patches '%s' Conflict, cannot be used simultaneously\n",
                    patch->ips_name.c_str(), conf_name.c_str());
                all_valid = false;
            }
        }
    }
    return all_valid;
}
// ============================================================>>>
int open_entry(running_machine &machine, const char *patch_name, rom_load_manager *romload, const tiny_rom_entry *romp)
{
    osd_printf_info("IPS: open_entry called with patch_name='%s'\n", patch_name ? patch_name : "(null)");
    
    s_ips_list.clear();
    s_error_string.clear();
    s_warning_count = 0;

    if (!patch_name || !*patch_name)
        return 0;

    std::string patches(patch_name);
    std::string current;
    bool result = false;

    size_t start = 0, end = 0;
    while ((end = patches.find(',', start)) != std::string::npos) {
        current = patches.substr(start, end - start);
        if (parse_ips_patch(machine, current.c_str(), romp))
            result = true;
        start = end + 1;
    }
    current = patches.substr(start);
    if (parse_ips_patch(machine, current.c_str(), romp))
        result = true;

    if (!verify_patch_dependencies()) {
        s_warning_count++;
        result = false;
    }
    
    detect_all_conflicts();

    return result ? 1 : 0;
}

int close_entry(rom_load_manager *romload)
{
    s_ips_list.clear();
    return 1;
}

void *assign_patch(const char *rom_name)
{
    if (!rom_name) return nullptr;
    ips_entry *found_entry = nullptr;

    for (auto &entry : s_ips_list)
    {
        if (core_stricmp(entry->rom_name.c_str(), rom_name) == 0)
        {
            osd_printf_verbose("IPS: assign IPS file \"%s\" to ROM entry \"%s\"\n", entry->ips_name.c_str(), entry->rom_name.c_str());
            
            entry->current_chunk_index = 0;
            if (!entry->chunks.empty())
            {
                entry->current_offset_remain = entry->chunks[0].offset;
                entry->current_data_remain = entry->chunks[0].size;
            }
            found_entry = entry.get();
        }
    }

    return found_entry;
}
//缘来是你
//======================= IPS 复选 ======================>>>
void apply_all_patches(const char *rom_name, u8 *buffer, int length)
{
    if (!rom_name || !buffer || length <= 0) return;
    for (auto &entry : s_ips_list)
    {
        if (core_stricmp(entry->rom_name.c_str(), rom_name) == 0)
        {
            if (entry->chunks.empty())
            {
                osd_printf_verbose("IPS: Skip empty patch for ROM '%s'\n", rom_name);
                continue;
            }
            entry->current_chunk_index = 0;
            apply_patch(entry.get(), buffer, length);
        }
    }
}
//========================================================>>>

void apply_patch(void *patch, u8 *buffer, int length)
{
    if (!patch) return;

    ips_entry *p = (ips_entry *)patch;
    
    for (size_t i = 0; i < p->chunks.size(); i++)
    {
        ips_chunk &chunk = p->chunks[i];
        
        if (chunk.offset >= (u32)length)
        {
#if USE_WARNING
            osd_printf_warning("IPS: Patch '%s' offset 0x%X exceeds ROM size (%d) and has been skipped\n",
                               p->ips_name.c_str(), chunk.offset, length);
            s_warning_count++;
#endif
            continue;
        }
	  
        u32 available = length - chunk.offset;
#if USE_WARNING
        if (chunk.size > available)
        {
            osd_printf_warning("IPS: The patch '%s' requires writing 0x%X bytes at offset 0x%X, but since only 0x%X bytes remain, it will be truncated\n",
                               p->ips_name.c_str(), chunk.offset, chunk.size, available);
            s_warning_count++;
        }
#endif
        u32 copy_len = std::min(chunk.size, available);
        
        memcpy(buffer + chunk.offset, chunk.data.data(), copy_len);
    }
}

} // namespace ips