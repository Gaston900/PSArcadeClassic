// license:BSD-3-Clause
// copyright-holders:Vas Crabb, Gastón90
/***************************************************************************

    ui/quitmenu.cpp

    Menus involved in quitting MAME.

***************************************************************************/

#include "emu.h"
#include "quitmenu.h"
#include "emuopts.h"

#include "uiinput.h"
#include "ui/state.h"

#include "debugger.h"
#include "debug/debugcpu.h" 
#include <windows.h>


extern int g_InsertGlobalConfiguration;

namespace ui {

enum
{
	ITEM_INSERT_COIN = 0,
	ITEM_LOAD_STATE,
	ITEM_SAVE_STATE,
	ITEM_SAVE_SNAPSHOT,
	ITEM_RECORD_AVI,
	ITEM_SHOW_FPS,
	ITEM_TOGGLE_THROTTLE,
	ITEM_TOGGLE_DEBUG,
	ITEM_SERVICE_MODE,
	ITEM_RESET_SYSTEM,
	ITEM_QUIT_GAME,
	ITEM_RETURN_EMU
};

menu_confirm_quit::menu_confirm_quit(mame_ui_manager &mui, render_container &container)
	: autopause_menu<>(mui, container)
{
	set_one_shot(true);
	set_needs_prev_menu_item(false);
	set_heading(_("menu-quit", "Are you sure you want to quit?"));
}


menu_confirm_quit::~menu_confirm_quit()
{
}


void menu_confirm_quit::populate(float &customtop, float &custombottom)
{
	item_append(_("menu-quit", "Developer Tools"), FLAG_UI_HEADING | FLAG_DISABLE, nullptr);

	item_append(_("menu-quit", "Insert Coin"), 0, (void *)(uintptr_t)ITEM_INSERT_COIN);
	item_append(_("menu-quit", "Load State"), 0, (void *)(uintptr_t)ITEM_LOAD_STATE);
	item_append(_("menu-quit", "Save State"), 0, (void *)(uintptr_t)ITEM_SAVE_STATE);
	item_append(_("menu-quit", "Save Snapshot"), 0, (void *)(uintptr_t)ITEM_SAVE_SNAPSHOT);
	item_append(_("menu-quit", "Record AVI"), 0, (void *)(uintptr_t)ITEM_RECORD_AVI);
	item_append(_("menu-quit", "Show FPS"), 0, (void *)(uintptr_t)ITEM_SHOW_FPS);
	item_append(_("menu-quit", "Show Speed"), 0, (void *)(uintptr_t)ITEM_TOGGLE_THROTTLE);
	item_append(_("menu-quit", "Modo Debug"), 0, (void *)(uintptr_t)ITEM_TOGGLE_DEBUG);
	item_append(_("menu-quit", "Service Mode"), 0, (void *)(uintptr_t)ITEM_SERVICE_MODE);
	item_append(_("menu-quit", "Reset System"), 0, (void *)(uintptr_t)ITEM_RESET_SYSTEM);
	item_append(_("menu-quit", "Quit Game"), 0, (void *)(uintptr_t)ITEM_QUIT_GAME);
	item_append(menu_item_type::SEPARATOR);
    item_append(_("menu-quit", "       Return to emulation       "), 0, (void *)(uintptr_t)ITEM_RETURN_EMU);
}


void menu_confirm_quit::handle(event const *ev)
{
	if (ev && (IPT_UI_SELECT == ev->iptkey))
	{
		uintptr_t action = uintptr_t(ev->itemref);

		switch (action)
		{
			case ITEM_INSERT_COIN:
				machine().resume();
				g_InsertGlobalConfiguration = 1;
				stack_pop();
				break;

			case ITEM_LOAD_STATE:
				menu::stack_push<ui::menu_load_state>(ui(), container(), true);
				break;

			case ITEM_SAVE_STATE:
				menu::stack_push<ui::menu_save_state>(ui(), container(), true);
				break;

			case ITEM_SAVE_SNAPSHOT:
				machine().video().save_active_screen_snapshots();
				stack_pop();
				break;

			case ITEM_RECORD_AVI:
				machine().video().toggle_record_movie(movie_recording::format::AVI);
				stack_pop();
				break;

			case ITEM_SHOW_FPS:
				ui().set_show_fps(!ui().show_fps());
				stack_pop();
				break;

			case ITEM_TOGGLE_THROTTLE:
				{
					bool bNuevoEstadoThrottle = !machine().video().throttled();
					machine().video().set_throttled(bNuevoEstadoThrottle);

					if (!bNuevoEstadoThrottle)
					{
						ui().set_show_fps(true);
					}
					else
					{
						ui().set_show_fps(false);
					}
					stack_pop();
				}
				break;

			case ITEM_TOGGLE_DEBUG:
				if (machine().debug_flags & DEBUG_FLAG_ENABLED)
				{
					stack_pop();
					machine().debugger().cpu().set_execution_stopped();
				}
				else
				{
					DWORD current_pid = GetCurrentProcessId();
					
					std::string cmd_overclock = "start \"\" \".\\PSArcadeClassic+.exe\" " + std::string(machine().system().name) + " -debug && taskkill /f /pid " + std::to_string(current_pid);
					std::system(cmd_overclock.c_str());
					machine().schedule_exit();
				}
				break;

			case ITEM_SERVICE_MODE:
				machine().resume();
				g_InsertGlobalConfiguration = 99;
				stack_pop();
				break;

			case ITEM_RESET_SYSTEM:
				machine().schedule_hard_reset();
				stack_pop();
				break;

			case ITEM_QUIT_GAME:
				machine().schedule_exit();
				break;

			case ITEM_RETURN_EMU:
			default:
				stack_pop();
				break;
		}
	}
}

} // namespace ui
