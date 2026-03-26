// 基于 eziochiu 制作的 IPS 代码修改

#include "emu.h"
#include "menu_ips_patches.h"

#include "emuopts.h"
#include "fileio.h"
#include "path.h"
#include "corestr.h"

#include <algorithm>
#include <cctype>

namespace ui {

static std::string trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

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

void menu_ips_patches::scan_patches()
{
    m_patches.clear();

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
            file_enumerator fpath(search_dir.c_str());
            const osd::directory::entry *entry;
            while ((entry = fpath.next()) != nullptr)
            {
                if (entry->type == osd::directory::entry::entry_type::FILE)
                {
                    std::string name(entry->name);
                    if (name.size() > 4 && name.compare(name.size()-4, 4, ".dat") == 0)
                    {
                        std::string patch_name = name.substr(0, name.size()-4);
                        if (std::find_if(m_patches.begin(), m_patches.end(),
                            [&](const patch_info &p) { return p.name == patch_name; }) != m_patches.end())
                            continue;

                        patch_info info;
                        info.name = patch_name;
                        info.display_name = patch_name;

                        std::string fullpath = util::path_concat(search_dir, name);
emu_file file(OPEN_FLAG_READ); 
if (!file.open(fullpath))
{
    bool in_section = false;
    char line[1024];
    while (file.gets(line, sizeof(line)))
    {
        std::string raw_line(line);
        if (raw_line.size() >= 3 &&
            (uint8_t)raw_line[0] == 0xEF &&
            (uint8_t)raw_line[1] == 0xBB &&
            (uint8_t)raw_line[2] == 0xBF)
        {
            raw_line = raw_line.substr(3);
        }
        std::string sline = trim(raw_line);
        if (sline.empty()) continue;

        if (!in_section && sline.front() == '[' && sline.find(']') != std::string::npos)
        {
            in_section = true;
            continue;
        }
        else if (in_section)
        {
            info.display_name = sline;
            break;
        }
    }
    file.close();
}
                        m_patches.push_back(std::move(info));
                    }
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

    for (size_t i = 0; i < m_patches.size(); i++)
    {
	    item_append(menu_item_type::SEPARATOR);
        item_append_on_off(m_patches[i].display_name, m_patch_enabled[i], FLAG_LEFT_ARROW | FLAG_RIGHT_ARROW, (void *)(uintptr_t)(i + 1));
    }
	    item_append(menu_item_type::SEPARATOR);
		
//    if (m_need_reset)

        item_append("Modification requires reloading the game.", FLAG_DISABLE, nullptr);
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

    else if (ev && ev->iptkey == IPT_UI_CANCEL && m_need_reset)
    {
        machine().schedule_hard_reset();
    }

}

} // namespace ui