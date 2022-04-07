// license:BSD-3-Clause
// copyright-holders:Gaston90
/***************************************************************************

    hbmame.c

    Specific (per target) constants

****************************************************************************/

#include "emu.h"

#define APPNAME             "PSARCADE CLASSIC+"
#define APPNAME_LOWER       "PSArcade Classic+"
#define CONFIGNAME          "PSArcade Classic+"
#define COPYRIGHT           "Copyright Gaston90\nand the MAME team\nhttp://mamedev.org"
#define COPYRIGHT_INFO      "\nMAME portions are copyright the MAME team.\n" \
                            "PSArcade Classic+ portions are copyright Gaston90."

const char * emulator_info::get_appname() { return APPNAME;}
const char * emulator_info::get_appname_lower() { return APPNAME_LOWER;}
const char * emulator_info::get_configname() { return CONFIGNAME;}
const char * emulator_info::get_copyright() { return COPYRIGHT;}
const char * emulator_info::get_copyright_info() { return COPYRIGHT_INFO;}
