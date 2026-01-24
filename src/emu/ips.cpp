// license:BSD-3-Clause
// copyright-holders:eziochiu

#include "emu.h"
#include "ips.h"
#include "emuopts.h"
#include "hash.h"
#include "fileio.h"
#include "romload.h"

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

static bool load_ips_file(running_machine &machine, std::vector<ips_chunk> &chunks, const char *ips_dir, const char *ips_name)
{
    std::string path;
    if (ips_dir && *ips_dir)
        path = std::string(ips_dir).append(PATH_SEPARATOR).append(ips_name).append(IPS_EXT);
    else
        path = std::string(ips_name).append(IPS_EXT);

    osd_printf_verbose("IPS: loading ips \"%s\"\n", path.c_str());

    emu_file file(machine.options().value(OPTION_IPSPATH), OPEN_FLAG_READ);
    std::error_condition filerr = file.open(path.c_str());
    
    if (filerr)
    {
    }

    if (filerr)
    {
        s_error_string += string_format("ERROR: %s: open fail\n", path);
        s_warning_count++;
        return false;
    }

    u8 buffer[8];
    if (file.read(buffer, 5) != 5 || memcmp(buffer, IPS_SIGNATURE, 5) != 0)
    {
        s_error_string += string_format("ERROR: %s: incorrect IPS header\n", path);
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

static bool check_crc(const char *crc_str, const char *rom_hash)
{
    if (!crc_str) return false;

    std::string crc_val(crc_str);
    if (crc_val.find(CRC_STAG) != 0) return false;
    
    size_t end_pos = crc_val.find(CRC_ETAG);
    if (end_pos == std::string::npos) return false;

    std::string actual_crc = crc_val.substr(strlen(CRC_STAG), end_pos - strlen(CRC_STAG));
    if (actual_crc.length() != 8) return false;

    util::hash_collection ips_hash;
    ips_hash.add_from_string(util::hash_collection::HASH_CRC, actual_crc.c_str());

    util::hash_collection rom_hashes(rom_hash);
    
    return ips_hash == rom_hashes;
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

        const romload::file *current = find_rom_file(romp, rom_name);
        if (!current)
        {
            osd_printf_info("IPS: ROM entry '%s' NOT FOUND in driver ROM list\n", rom_name);
            s_error_string += string_format("ERROR: ROM entry \"%s\" is not found for IPS file \"%s\"\n", rom_name, patch_name);
            continue;
        }
        
        osd_printf_info("IPS: ROM entry '%s' FOUND, proceeding...\n", rom_name);

        char *ips_entry_name = strtok(nullptr, " \t\r\n");
        if (!ips_entry_name)
        {
            s_error_string += string_format("ERROR: IPS file is not defined for ROM entry \"%s\"\n", rom_name);
            continue;
        }

        char *crc = strtok(nullptr, "\r\n");
        
        if (current && crc)
        {
            char *crc_end = crc + strlen(crc) - 1;
            while (crc_end > crc && isspace((u8)*crc_end)) *crc_end-- = 0;

            if (!check_crc(crc, current->get_hashdata()))
            {
                s_error_string += string_format("ERROR: wrong CRC for ROM entry \"%s\"\n", rom_name);
                continue; 
            }
        }

        std::string ips_dir_str = machine.system().name;
        std::string ips_name_str = ips_entry_name;
        
        if (ips_name_str.find('\\') != std::string::npos)
        {
        }

        auto entry = std::make_unique<ips_entry>();
        entry->rom_name = rom_name;
        entry->ips_name = ips_name_str;
        
        osd_printf_info("IPS: Loading IPS file for ROM '%s': dir='%s', name='%s'\n", rom_name, ips_dir_str.c_str(), entry->ips_name.c_str());
        
        if (!load_ips_file(machine, entry->chunks, ips_dir_str.c_str(), entry->ips_name.c_str()))
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
