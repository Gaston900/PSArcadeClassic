// license:BSD-3-Clause
// copyright-holders:eziochiu

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
        s_warning_count++;
        return false;
    }

    osd_printf_verbose("IPS: loading ips \"%s\"\n", opened_path.c_str());
//====================================================================================================>>>

    u8 buffer[8];
    if (file.read(buffer, 5) != 5 || memcmp(buffer, IPS_SIGNATURE, 5) != 0)
    {
        s_error_string += string_format("ERROR: %s: incorrect IPS header\n", opened_path.c_str());	//缘来是你
        file.close();
        s_warning_count++;
        return false;
    }

    while (true)
    {
        u8 offset_buf[3];
        if (file.read(offset_buf, 3) != 3)
            break;

        if (memcmp(offset_buf, IPS_TAG_EOF, 3) == 0)
            break;

        u32 offset = BYTE3_TO_UINT(offset_buf);

        u8 size_buf[2];
        if (file.read(size_buf, 2) != 2)
            break;

        u16 size = BYTE2_TO_UINT(size_buf);
        bool bRLE = false;
        u16 rle_size = 0;

        if (size == 0)
        {
            if (file.read(size_buf, 2) != 2)
                break;
             
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
                break;
            
            chunk.size = rle_size;
            chunk.data.resize(rle_size);
            std::memset(chunk.data.data(), fill_byte, rle_size);
        }
        else
        {
            chunk.size = size;
            chunk.data.resize(size);
            if (file.read(chunk.data.data(), size) != size)
                break;
        }

        chunks.push_back(std::move(chunk));
    }

    file.close();
    return true;
}

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
        // Trim leading whitespace
        while (*p && isspace((u8)*p)) p++;
        
        if (*p == 0 || *p == '#' || *p == '[') continue;

        osd_printf_info("IPS: Parsing line %d: '%s'\n", line_count, p);
        
        char *rom_name = strtok(p, " \t\r\n");
        if (!rom_name) continue;
      
        char *ips_entry_name = strtok(nullptr, " \t\r\n");
        if (!ips_entry_name)
        {
            s_error_string += string_format("ERROR: IPS file is not defined for ROM entry \"%s\"\n", rom_name);
            continue;
        }

        char *crc = strtok(nullptr, "\r\n");
        
        if (crc)
        {
            char *crc_end = crc + strlen(crc) - 1;
            while (crc_end > crc && isspace((u8)*crc_end)) *crc_end-- = 0;
			
//缘来是你
//======================== IPS CRC =================================>>>
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
            s_warning_count++;
            continue;
        }

        std::string ips_dir_str = util::path_concat(machine.system().name, patch_name);	//缘来是你
        std::string ips_name_str = ips_entry_name;
//======================================================================>>>

        auto entry = std::make_unique<ips_entry>();
        entry->rom_name = rom_file->get_name();  //IPS CRC 
        entry->ips_name = ips_name_str;
        
//缘来是你
//======================== IPS 子目录 ============================>>>
        std::vector<std::string> candidate_paths;
        candidate_paths.push_back(util::path_concat(ips_dir_str, ips_name_str + IPS_EXT));
        candidate_paths.push_back(util::path_concat(machine.system().name, ips_name_str + IPS_EXT));
        
        if (!load_ips_file(machine, entry->chunks, candidate_paths))
//================================================================>>>
        {
            osd_printf_info("IPS: ERROR - load_ips_file FAILED for '%s'\n", entry->ips_name.c_str());
            s_error_string += string_format("ERROR: %s/%s: IPS data could not be loaded\n", ips_dir_str, entry->ips_name);
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
            continue;
        
        u32 available = length - chunk.offset;
        u32 copy_len = std::min(chunk.size, available);
        
        memcpy(buffer + chunk.offset, chunk.data.data(), copy_len);
    }
}

}
