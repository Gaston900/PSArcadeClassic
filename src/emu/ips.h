// license:BSD-3-Clause
// copyright-holders:eziochiu

#ifndef MAME_EMU_IPS_H
#define MAME_EMU_IPS_H

#pragma once

#include <string>

class running_machine;
class rom_load_manager;
struct tiny_rom_entry;

namespace ips {

int open_entry(running_machine &machine, const char *patch_name, rom_load_manager *romload, const tiny_rom_entry *romp);
int close_entry(rom_load_manager *romload);
void *assign_patch(const char *rom_name);
void apply_patch(void *patch, u8 *buffer, int length);
std::string &get_error_string();
int get_warning_count();

}

#endif // MAME_EMU_IPS_H
