# PSArcadeClassic+
What is PSARCADECLASSIC+?

It's called Project Shadow Arcade Classic+, it is a project that began in the middle of year 2016, currently a version 0.245 [HBMAME](https://hbmame.1emulation.com/) is being used as a base system.

This project is focused on merging two emulator systems [ARCADE64](https://arcade.mameworld.info/) + [HBMAME](https://hbmame.1emulation.com/), then has implemented the new hack roms (Which was not included in the [HBMAME](https://hbmame.1emulation.com/) version), has been done with a total cleaning of the roms/hack roms, eliminating thus hundreds of useless roms or . chd and unnecessary and thus be able to generate a collectible edition and in this way a single version will be published. In order to make the rom system much lighter for our hard drive.

I am only supporting the operating systems 64x bits, Windows 7, Windows 8, Windows 10 and Windows 11.

All source code used to create the base system, extracted from the GitHub repository:

Robert [[HBMAME](https://github.com/Robbbert/hbmame)], Dirstac [[Arcade Extended](https://github.com/Dirstac/ArcadeUI-CHS)], Kaze [[EKMAME](https://github.com/WOOSEOK99/EKMAME)] and Chamcham [[MSLUG6](https://github.com/Zansword/MAME-0.243)]

How to compile
--------------

In order to compile this version we will need the source code, for this we will place it in the folder docs/Source Code[HBMame]/hbmame-tag245.7z.001, once located we will begin to unzip the files it will take a few minutes, once unzipped we will have a folder with the name hbmame-tag245.7z, we will rename it to “src”. Now we will get the latest source code from this Github container once downloaded we will start to unzip and once finished unzipping we will select the files that we had left in the folder “3rdparty, scripts, src and makefile” folders, then copy them into the "src" folder. When the system asks to confirm file replacement, accept the operation.

The version used is msys64 15.0.2; if you do not have it, you can find it in the folder “docs / Build Tools / msys64-15.0.2.7z.001”.

And we will apply this command to start the compilation:
```
make PTR64=1 SUBTARGET=arcade OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```

Open Source Software Projects
------------------------------
Although the source code is free to use, please note that the use of this code for any commercial exploitation or use of the project for fundraising purposes is prohibited.
