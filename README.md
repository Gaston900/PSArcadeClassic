# PSArcadeClassic+
What is PSARCADECLASSIC+?

It's called Project Shadow Arcade Classic+, it's a project that started at the beginning of this year 2022, a version 0.232 [ARCADE64] is being used as a base system, but it really started with a version 0.215 [The PSMame project was used as the base system Plus Metal Slug Forever Special Edition], but it was decided to abandon this version due to various situations that became more complicated as I progressed adding new games because I had to downgrade the modern codes and convert the codes to be compatible with the version 0.215, these codes are still preserved since many have been advanced and have been left in a 2.0 prototype state, it will be located in docs/Old Code Version/PSArcade Classic+ 2.0.7z.

This project is focused on merging the Arcade64 + HBMame system, a base system of a version 0.232 was used to update until version 0.243, it will be the only version that will be published, since it is a collectible edition.

The main thing of all has started a total cleaning in the roms sets eliminating hundreds of useless and unnecessary roms or .chd, so that we can leave roms sets much lighter for our hard drive.

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

Does not include fruit game sets.

Does not include slot games or gambling.

Does not include console games.

Does not include games that display a black screen.

It does not include games that are sound test or demo, controls, color palette.

It does not include games of does not work correctly .CHD.

What has been optimized in this version?
---------------------------------------

The command of all the game systems was optimized, now it is much more practical to be able to play, the command of the arrow keys "Up, Down, Left, Right" comes by default, this command is used to be able to move and to take actions For shooting or jumping and throwing grenades, the A, S, D key is used and the rest of the keys are used for certain kinds of games Z, X, C, Q, W, E.

Added custom buttons and auto fire

Removed warning screen.

Removed Startups, Loading, Decryption screen texts.

The Arcade64 “GUI” was modernized with new icons, a custom default configuration has been made.

It is already pre-configured, enforce aspect ratio is disabled, full screen mode and tricks are already enabled by default.

How to compile
--------------

To be able to compile this version we will need the source codes, for this we will place it in the folder docs/Old HBMAME Source Code/store1-tag232.7z.001, once located we will start to decompress the files it will take a few minutes, once decompressed we will have a folder with the name store1-tag232.7z, we will rename it to “src”, now we will paste the remains of the files that we have left “scripts, src and makefile” in the src folder, the system will ask to replace it we will say yes .

Now we will locate the folder where the compiler that we want to use is located, being msys64. Now we will paste the “src” folder.

And we will apply this command to start the compilation, this command is for Windows 64Bit system:

make PTR64=1 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
--------------------------------------------------------------

I recommend downloading the compilation tool, whether it is the version msys64-32 that is from the year 2019-03-25, since this version is much more comfortable to compile for this version.

The build tools will be located on the MAMEDEV github website:
https://github.com/mamedev/buildtools/releases
