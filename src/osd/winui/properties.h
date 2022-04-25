// license:BSD-3-Clause
// copyright-holders:Chris Kirmse, Mike Haaland, René Single, Mamesick

#ifndef PROPERTIES_H
#define PROPERTIES_H

#define MAX_SCREENS				4
#define SHEET_TREE_WIDTH 		180
#define NUMPAGES 				std::size(g_PropSheets)
#define NUMVIDEO 				std::size(g_ComboBoxVideo)
#define NUMSOUND 				std::size(g_ComboBoxSound)
#define NUMSAMPLERATE 			std::size(g_ComboBoxSampleRate)
#define NUMSELECTSCREEN 		std::size(g_ComboBoxSelectScreen)
#define NUMVIEW 				std::size(g_ComboBoxView)
#define NUMFRAMESKIP 			std::size(g_ComboBoxFrameSkip)
#define NUMDEVICES 				std::size(g_ComboBoxDevice)
#define NUMSNAPNAME 			std::size(g_ComboBoxSnapName)
#define NUMSNAPVIEW 			std::size(g_ComboBoxSnapView)
#define NUMGLSLFILTER 			std::size(g_ComboBoxGLSLFilter)
#define NUMBGFXBACKEND			std::size(g_ComboBoxBGFXBackend)

/* Called in winui.c to create the property page */
void InitPropertyPage(HINSTANCE hInst, HWND hWnd, OPTIONS_TYPE opt_type, int folder_id, int game_num);
intptr_t CALLBACK GamePropertiesDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif
