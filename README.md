# PSArcadeClassic+
What is PSARCADECLASSIC+?

It's called Project Shadow Arcade Classic+, it's a project that started at the beginning of this year 2022, a version 0.232 [ARCADE64] is being used as a base system, but in reality it started with a version 0.215 [The project was used as a base system PSMame Plus Metal Slug Forever Special Edition], but it was decided to drop this version due to several various problem situations that became more complicated as it progressed adding new roms to the system, because modern codes had to be downgraded and in order to be able to convert them so that were compatible with the version. 0.215, these source codes are still being preserved as a lot of progress has been made and will locate it in docs/Source Code [Version Old]/PSArcade Classic+ 2.0.7z, it can be compiled for the Windows XP operating system.
 
This project is focused on merging the Arcade64 + HBMame system, The main thing has started by updating the Roms Sets from version 0.232 - 0.245, then it continued with a total cleaning of the roms thus eliminating hundreds of useless roms or .chd and unnecessary and thus to be able to generate a collectible edition and in this way a single version will be published. So that we can leave the roms system much lighter for our hard drive.
 
I am only giving support for the Windows XP, Windows 7, Windows 8, Windows 10 and Windows 11 operating systems,
for the 86/64 bit cpu of the compatible microprocessors.

This way you will be able to enjoy all the arcade systems in a single version, including all the hacks that currently exist.

Games that have not been included:
----------------------------------

Does not include mechanical games.

Does not include pinball games.

Does not include crane games.

Does not include erotic games.

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

The command of all the game systems was optimized, now it is much more practical to be able to play, the command of the arrow keys "Up, Down, Left, Right" comes by default, this command is used to be able to move and to take actions For shooting or jumping and throwing grenades, the A, S, D key is used and the rest of the keys are used for certain kinds of games Z, X, C, Q, W, E.

Added custom buttons and auto fire

Removed the black border on NeoGeo systems, now has full screen.

Removed warning screen.

Removed Startups, Loading, Decryption screen texts.

Removed the following annoying messages: “WRONG LENGTH”, “NO_DUMP”, “WRONG CHECKSUMS”, “BAD_DUMP” And “THE PARENT FILE DOES NOT EXIST”.

Added movement optimization for all fighting games “GSC2007”.

The Arcade64 “GUI” was modernized with new icons, a custom default configuration has been made.

It is already pre-configured, enforce aspect ratio is disabled, full screen mode and tricks are already enabled by default.

Two new folder sections called “config” and “support” were added that independently group the configurations and extra content, so that everything is kept in order in a single folder.

In the Config folders it is incorporated by:

Audio, Bgfx, Cfg, Comments, Crosshair, Diff, Docs, Folders, Glsl, Gui, Hash, Hlsl, Ini, Inp, Language, Nvram, Plugins, Share, Sta and m1fx.exe

In the support folders it is incorporated by:

Artpreview, Artwork, Bosses, Cabinets, Cheat, Cpanel, Ctrlr, Flyers, Gameover, Howto, Icons,
Logo, Manuals, Marquees, Pcb, Roms, Samples, Scores, Select, Snap, Titles, Versus, Video, Cheat.7z, Command.dat, Gameinit.dat, Hiscore.dat, History.dat, Mameinfo.dat, Story. dat and Sysinfo.dat

How to compile
--------------

To be able to compile this version we will need the source codes, for this we will place it in the folder docs/Source Code [HBMame Old]/store1-tag232.7z.001, once located we will start to decompress the files it will take a few minutes, once decompressed we will have a folder with the name store1-tag232.7z, we will rename it to “src”, now we will paste the remains of the files that we have left “scripts, src and makefile” in the src folder, the system will ask to replace it we will say yes .

Now we will locate the folder where the compiler that we want to use is located, being msys64. Now we will paste the “src” folder.

And we will apply this command to start the compilation, this command is for Windows 64Bit system:
```
make PTR64=1 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```

I recommend downloading the compilation tool, whether it is the version msys64-32 that is from the year 2019-03-25, since this version is much more comfortable to compile for this version.

The build tools will be located on the MAMEDEV github website:
https://github.com/mamedev/buildtools/releases
