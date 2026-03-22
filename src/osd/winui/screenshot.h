// license:BSD-3-Clause
// For licensing and usage information, read docs/release/winui_license.txt

#ifndef SCREENSHOT_H
#define SCREENSHOT_H

bool LoadScreenShot(int nGame, int nType);
HANDLE GetScreenShotHandle(void);
int GetScreenShotWidth(void);
int GetScreenShotHeight(void);
void FreeScreenShot(void);
bool ScreenShotLoaded(void);

#endif
