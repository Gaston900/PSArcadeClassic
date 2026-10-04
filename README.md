# PSArcadeClassic+
What is PSARCADECLASSIC+?

It's called Project Shadow Arcade Classic+, it is a project that began in the middle of year 2016, currently a version 0.245 [HBMAME](https://hbmame.1emulation.com/) is being used as a base system.

This project is focused on merging two emulator systems [ARCADE64](https://arcade.mameworld.info/) + [HBMAME](https://hbmame.1emulation.com/), then has implemented the new hack roms (Which was not included in the [HBMAME](https://hbmame.1emulation.com/) version), has been done with a total cleaning of the roms/hack roms, eliminating thus hundreds of useless roms or . chd and unnecessary and thus be able to generate a collectible edition and in this way a single version will be published. In order to make the rom system much lighter for our hard drive.

I am only supporting the operating systems 64x bits, Windows 7, Windows 8, Windows 10 and Windows 11.

How to compile
--------------

In order to compile this version we will need the source code, for this we will place it in the folder docs/Source Code[HBMame]/hbmame-tag245.7z.001, once located we will begin to unzip the files it will take a few minutes, once unzipped we will have a folder with the name hbmame-tag245.7z, we will rename it to “src”. Now we will get the latest source code from this Github container once downloaded we will start to unzip and once finished unzipping we will select the files that we had left in the folder “3rdparty, scripts, src and makefile” we will copy them into the src folder, the system will ask us to replace it we will say yes.

And we will apply this command to start the compilation:
```
make PTR64=1 SUBTARGET=arcade OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```

The compilation [TOOL](https://github.com/mamedev/buildtools/releases) is suggested to be version 7.0 msys64 (Jan 11, 2022).

Open Source Software Projects
------------------------------
Although the source code is free to use, please note that the use of this code for any commercial exploitation or use of the project for fundraising purposes is prohibited.
