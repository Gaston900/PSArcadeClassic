#ifndef MAME_FRONTEND_UI_MENU_IPS_PATCHES_H
#define MAME_FRONTEND_UI_MENU_IPS_PATCHES_H

#pragma once

#include "ui/menu.h"
#include <vector>
#include <string>

namespace ui {

class menu_ips_patches : public menu
{
public:
    menu_ips_patches(mame_ui_manager &mui, render_container &container);
    virtual ~menu_ips_patches() override;

private:
    struct patch_info
    {
        std::string name; 
        std::string display_name; 
    };

    virtual void populate(float &customtop, float &custombottom) override;
    virtual void handle(event const *ev) override;

    void scan_patches();
    void update_ips_option();

    std::vector<patch_info> m_patches;
    std::vector<bool> m_patch_enabled;
    bool m_need_reset;
};

} // namespace ui

#endif // MAME_FRONTEND_UI_MENU_IPS_PATCHES_H