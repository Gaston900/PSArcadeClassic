// license:BSD-3-Clause
// copyright-holders:Based on the IPS code modification made by eziochiu
// The code that automatically matches IPS descriptions is provided by 醉猫(Drunken Cat)
#include "emu.h"
#include "menu_ips_patches.h"
#include "emuopts.h"
#include "fileio.h"
#include "path.h"
#include "corestr.h"
#include "osdepend.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <map>

namespace ui {

menu_ips_patches::menu_ips_patches(mame_ui_manager &mui, render_container &container)
    : menu(mui, container)
    , m_need_reset(false)
{
    set_process_flags(PROCESS_LR_REPEAT);
    scan_patches();
}

menu_ips_patches::~menu_ips_patches()
{
}

static std::string trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

static std::string to_lower(const std::string &s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

static void scan_directory(const std::string &dir_path, const std::string &relative_path,
                           std::vector<menu_ips_patches::patch_info> &patches,
                           const std::string &target_lang)
{
    file_enumerator fpath(dir_path.c_str());
    const osd::directory::entry *entry;
    while ((entry = fpath.next()) != nullptr)
    {
        std::string name(entry->name);
        if (entry->type == osd::directory::entry::entry_type::FILE)
        {
            if (name.size() > 4 && name.compare(name.size()-4, 4, ".dat") == 0)
            {
                std::string patch_name = name.substr(0, name.size()-4);
                std::string full_name = relative_path.empty()
                                        ? patch_name
                                        : util::path_concat(relative_path, patch_name);
                
                menu_ips_patches::patch_info info;
                info.name = full_name;
                info.display_name = patch_name;
                
                std::string fullpath = util::path_concat(dir_path, name);
                emu_file file(OPEN_FLAG_READ);
                if (!file.open(fullpath))
                {
                    std::map<std::string, std::string> sections;
                    std::string current_section;
                    bool in_section = false;
                    
//===========================  醉猫 === 兼容UTF-8编码 ===================>>> 
                    std::string file_content;
                    char ch;
                    while (file.read(&ch, 1) == 1)
                        file_content += ch;
                    
                    if (file_content.size() >= 3 &&
                        (uint8_t)file_content[0] == 0xEF &&
                        (uint8_t)file_content[1] == 0xBB &&
                        (uint8_t)file_content[2] == 0xBF)
                    {
                        file_content = file_content.substr(3);
                    }
                    
                    std::istringstream iss(file_content);
                    std::string line;
                    while (std::getline(iss, line))
                    {
                        if (!line.empty() && line.back() == '\r')
                            line.pop_back();
                        
                        std::string sline = trim(line);
//=====================================================================>>>
                        if (sline.empty()) continue;
                        
                        if (!in_section && sline.front() == '[' && sline.find(']') != std::string::npos)
                        {
                            size_t end = sline.find(']');
                            std::string section = sline.substr(1, end - 1);
                            section = trim(section);
                            current_section = to_lower(section);
                            in_section = true;
                            continue;
                        }
                        else if (in_section)
                        {
                            if (sections.find(current_section) == sections.end())
                            {
                                sections[current_section] = sline;
                            }
                            in_section = false; 
                        }
                    }
                    
                    std::string selected_name;
                    auto it = sections.find(target_lang);
                    if (it != sections.end())
                        selected_name = it->second;
                    else
                    {
                        std::string other_lang = (target_lang == "zh_cn") ? "zh_tw" : "zh_cn";
                        it = sections.find(other_lang);
                        if (it != sections.end())
                            selected_name = it->second;
                        else
                        {
                            it = sections.find("en_us");
                            if (it != sections.end())
                                selected_name = it->second;
                            else if (!sections.empty())
                            {
                                selected_name = sections.begin()->second;
                            }
                        }
                    }
                    
                    if (!selected_name.empty())
                        info.display_name = selected_name;
                    
                    file.close();
                }
                patches.push_back(std::move(info));
            }
        }
        else if (entry->type == osd::directory::entry::entry_type::DIR)
        {
            if (name == "." || name == "..")
                continue;
            std::string subdir = util::path_concat(dir_path, name);
            std::string new_relative = relative_path.empty() ? name : util::path_concat(relative_path, name);
            scan_directory(subdir, new_relative, patches, target_lang);
        }
    }
}

void menu_ips_patches::scan_patches()
{
    m_patches.clear();
    
    std::string lang = machine().options().language();
    std::string lang_lower = to_lower(lang);
    std::string target_lang;
    
    if (lang_lower.find("simplified") != std::string::npos || lang_lower == "zh_cn")
        target_lang = "zh_cn";
    else if (lang_lower.find("traditional") != std::string::npos || lang_lower == "zh_tw")
        target_lang = "zh_tw";
    else
        target_lang = "en_us"; 
    
    const char *ipspath = machine().options().value(OPTION_IPSPATH);
    std::string sysname = machine().system().name;
    
    std::string path_str(ipspath);
    size_t start = 0;
    while (start < path_str.size())
    {
        size_t end = path_str.find(';', start);
        std::string single_path = path_str.substr(start, end - start);
        if (!single_path.empty())
        {
            std::string search_dir = util::path_concat(single_path, sysname);
            std::vector<patch_info> found;
            scan_directory(search_dir, "", found, target_lang);
            for (auto &info : found)
            {
                if (std::find_if(m_patches.begin(), m_patches.end(),
                    [&](const patch_info &p) { return p.name == info.name; }) == m_patches.end())
                {
                    m_patches.push_back(info);
                }
            }
        }
        if (end == std::string::npos) break;
        start = end + 1;
    }
    
    std::sort(m_patches.begin(), m_patches.end(),
        [](const patch_info &a, const patch_info &b) { return a.display_name < b.display_name; });
    
    m_patch_enabled.assign(m_patches.size(), false);
    const char *current_ips = machine().options().value(OPTION_IPS);
    if (current_ips && *current_ips)
    {
        std::string ips_str(current_ips);
        size_t pos = 0;
        while (pos < ips_str.size())
        {
            size_t comma = ips_str.find(',', pos);
            std::string patch = ips_str.substr(pos, comma - pos);
            patch = trim(patch);
            if (!patch.empty())
            {
                auto it = std::find_if(m_patches.begin(), m_patches.end(),
                    [&](const patch_info &p) { return p.name == patch; });
                if (it != m_patches.end())
                    m_patch_enabled[it - m_patches.begin()] = true;
            }
            if (comma == std::string::npos) break;
            pos = comma + 1;
        }
    }
}

void menu_ips_patches::populate(float &customtop, float &custombottom)
{
    int enabled_count = std::count(m_patch_enabled.begin(), m_patch_enabled.end(), true);
    std::string header = string_format("IPS Manager (%d Enabled)", enabled_count);
    item_append(header, FLAG_DISABLE, nullptr);

	item_append(menu_item_type::SEPARATOR);

    for (size_t i = 0; i < m_patches.size(); i++)
    {
        item_append_on_off(m_patches[i].display_name, m_patch_enabled[i], FLAG_LEFT_ARROW | FLAG_RIGHT_ARROW, (void *)(uintptr_t)(i + 1));
    }

	    item_append(menu_item_type::SEPARATOR);

    if (m_need_reset)
        item_append("Modification requires reloading the game", FLAG_DISABLE, nullptr);
		item_append(menu_item_type::SEPARATOR);
}

void menu_ips_patches::update_ips_option()
{
    std::string new_ips;
    for (size_t i = 0; i < m_patches.size(); i++)
    {
        if (m_patch_enabled[i])
        {
            if (!new_ips.empty()) new_ips += ',';
            new_ips += m_patches[i].name; 
        }
    }
    machine().options().set_value(OPTION_IPS, new_ips.c_str(), OPTION_PRIORITY_CMDLINE);
}

void menu_ips_patches::handle(event const *ev)
{
    if (ev && ev->itemref != nullptr)
    {
        size_t index = (uintptr_t)ev->itemref - 1;
        if (index < m_patches.size())
        {
            if (ev->iptkey == IPT_UI_LEFT || ev->iptkey == IPT_UI_RIGHT)
            {
                bool new_state = (ev->iptkey == IPT_UI_RIGHT); 
                if (m_patch_enabled[index] != new_state)
                {
                    m_patch_enabled[index] = new_state;
                    m_need_reset = true;
                    update_ips_option();
                    reset(reset_options::REMEMBER_REF);
                }
            }
        }
    }
// Automatically restarts after changing settings
// I have tried both soft and hard restarts, but neither worked
// Leaving this code here in the hope that someone can fix it
    else if (ev && ev->iptkey == IPT_UI_CANCEL && m_need_reset)
    {
        machine().schedule_hard_reset();
    }
}

} // namespace ui