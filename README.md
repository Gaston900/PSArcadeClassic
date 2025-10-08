# PSArcadeClassic+
What is PSARCADECLASSIC+?

It's called Project Shadow Arcade Classic+, it's a project that started at the beginning of this year 2022, currently a version 0.245 [HBMAME](https://hbmame.1emulation.com/) is being used as a base system.

This project is focused on merging two emulator systems [ARCADE64](https://arcade.mameworld.info/) + [HBMAME](https://hbmame.1emulation.com/), has started updating the Roms from version 0.245 - 0.260, then has implemented the new hack roms (Which was not included in the [HBMAME](https://hbmame.1emulation.com/) version), has been done with a total cleaning of the roms/hack roms, eliminating thus hundreds of useless roms or . chd and unnecessary and thus be able to generate a collectible edition and in this way a single version will be published. In order to make the rom system much lighter for our hard drive.

Included with synchronization with the most current source of codes [PSMSLUGFOREVER](https://github.com/Gaston900/PSMSlugForever) 5.3 

I am only supporting the operating systems, Windows 7, Windows 8, Windows 10 and Windows 11.

So you can enjoy all the arcade systems in a single version, including all the hacks that currently exist.

Games that have not been included:
----------------------------------

Does not include mechanical games.

Does not include pinball games.

Does not include crane games.

Does not include trivia games.

Does not include bingo games.

Does not include mahjong games.

Does not include poker games.

Does not include skeleton drivers.

Does not include fruit games.

Does not include slot games or gambling.

Does not include console games.

Does not include games that display a black screen.

It does not include games that are sound test or demo, controls, color palette.

It does not include games of does not work correctly .CHD.

What has been optimized in this version?
---------------------------------------

Players 1 and 2 use this controller by default:

* To move, use the arrow keys "Up, Down, Left, Right."
* To perform actions, use the "A, S, D, Z, X, C, Q, W, E" keys.

The M68000 CPU core has been modified to be compatible with all current types of hack ROMs.

Support for extending adpcma files (NeoGeo) (By Robert)

The free mod is enabled on the NeoGeo system by pressing the Start button, you don't need to add credits every time you lose.

Added custom buttons and autofire.

Removed the black border on NeoGeo systems, now has full screen.

Removed warning screen, startups, Loading, Decryption screen texts.

Removed the following annoying messages: “WRONG LENGTH”, “NO_DUMP”, “WRONG CHECKSUMS”, “BAD_DUMP” And “THE PARENT FILE DOES NOT EXIST”.

Added movement optimization for all fighting games (By GSC2007).

Fix screen timings, remove non-existent sprite buffer ram [PGM].

The Arcade64 "GUI" EKMAME source code has been implemented (By KAZE).

The Arcade64 "GUI" some default settings have been implemented.

It is already pre-configured, enforce aspect ratio is disabled, full screen mode and tricks are already enabled by default.

The cheat reference function, if the cloned game does not have a cheat file, it will reference the cheat file of the main ROM.

Supports game list language files.

CPS 1, 2, NEOGEO, PGM, driver supports key combination settings.

Two new folder sections called “config” and “support” were added that independently group the configurations and extra content, so that everything is kept in order in a single folder.

In the Config folders it is incorporated by:

Bgfx, Cfg, Comments, Crosshair, Diff, Docs, Folders, Glsl, Gui, Hash, Hlsl, Ini, Inp, Language, Nvram, Plugins, Share, Sta.

In the support folders it is incorporated by:

Artpreview, Artwork, Bosses, Cabinets, Cheat, Cpanel, Ctrlr, Flyers, Gameover, Howto, Icons,
Logo, Manuals, Marquees, Pcb, Roms, Samples, Scores, Select, Snap, Titles, Versus, Video, Cheat.7z, Command.dat, Gameinit.dat, Hiscore.dat, History.dat, Mameinfo.dat, Story. dat and Sysinfo.dat

How to compile
--------------

In order to compile this version we will need the source code, for this we will place it in the folder docs/Source Code[HBMame]/hbmame-tag245.7z.001, once located we will begin to unzip the files it will take a few minutes, once unzipped we will have a folder with the name hbmame-tag245.7z, we will rename it to “src”. Now we will get the latest source code from this Github container once downloaded we will start to unzip and once finished unzipping we will select the files that we had left in the folder “3rdparty, scripts, src and makefile” we will copy them into the src folder, the system will ask us to replace it we will say yes.

And we will apply this command to start the compilation, this command is for Windows 64Bit system:
```
make PTR64=1 SUBTARGET=arcade OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```

The compilation [TOOL](https://github.com/mamedev/buildtools/releases) is suggested to be version msys64 2020-11-03.

Open Source Software Projects
------------------------------
Although the source code is free to use, please note that the use of this code for any commercial exploitation or use of the project for fundraising purposes is prohibited.
