// Proyecto Shadows Arcade Classic+
// copyright-holders:Gaston90
#include "../mame/drivers/twincobr.cpp"

 /***********
 Twin Twist
**************/

ROM_START( twincobrhack01 )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "b30_01.7j", 0x00000, 0x10000, CRC(07f64d13) SHA1(864ce0f9369c40c3ae792fc4ab2444a168214749) )
	ROM_LOAD16_BYTE( "b30_03.7h", 0x00001, 0x10000, CRC(41be6978) SHA1(4784804b738a332c7f24a43bcbb7a1e607365735) )
	ROM_LOAD16_BYTE( "b30_26_ii.8j", 0x20000, 0x08000, CRC(3a646618) SHA1(fc1ed8f3c491f5cf16a17e5ce08c5d8f3ce03683) )
	ROM_LOAD16_BYTE( "b30_27_ii.8h", 0x20001, 0x08000, CRC(d7d1e317) SHA1(57b8433b1677a390a7c7e00a1464bb8ed9cbfc73) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "b30_05_ii.4f", 0x00000, 0x08000, CRC(e37b3c44) SHA1(5fed10b29c14e27aee0cd92ecde5c5cb422273b1) )

	ROM_REGION( 0x2000, "dsp", 0 )
	ROM_LOAD16_BYTE( "dsp_22.bin", 0x0001, 0x0800, CRC(79389a71) SHA1(14ec4c1c9b06702319e89a7a250d0038393437f4) )
	ROM_LOAD16_BYTE( "dsp_21.bin", 0x0000, 0x0800, CRC(2d135376) SHA1(67a2cc774d272ee1cd6e6bc1c5fc33fc6968837e) )

	ROM_REGION( 0x0c000, "gfx1", 0 )
	ROM_LOAD( "b30_08.8c", 0x00000, 0x04000, CRC(0a254133) SHA1(17e9cc5e36fb4696012d0f9229fa172034cd843a) )
	ROM_LOAD( "b30_07.10b", 0x04000, 0x04000, CRC(e9e2d4b1) SHA1(e0a19dd46a9ba85d95bba7fbf81d8dc36dbfeabd) )
	ROM_LOAD( "b30_06.8b", 0x08000, 0x04000, CRC(a599d845) SHA1(732001f2d378d890f148e6b616c287d71fae832a) )

	ROM_REGION( 0x40000, "gfx2", 0 )
	ROM_LOAD( "b30_16.20b", 0x00000, 0x10000, CRC(15b3991d) SHA1(f5e7ed7a7721ed7e6dfd440634160390b7a294e4) )
	ROM_LOAD( "b30_15.18b", 0x10000, 0x10000, CRC(d9e2e55d) SHA1(0409e6df836d1d5198b64b21b42192631aa6d096) )
	ROM_LOAD( "b30_13.18c", 0x20000, 0x10000, CRC(13daeac8) SHA1(1cb103f434e2ecf193fa936ca7ea9194064c5b39) )
	ROM_LOAD( "b30_14.20c", 0x30000, 0x10000, CRC(8cc79357) SHA1(31064df2b796ca85ad3caccf626b684dff1104a1) )

	ROM_REGION( 0x20000, "gfx3", 0 )
	ROM_LOAD( "b30_12.16c", 0x00000, 0x08000, CRC(b5d48389) SHA1(a00c5b9c231d3d580fa20c7ad3f8b6fd990e6594) )
	ROM_LOAD( "b30_11.14c", 0x08000, 0x08000, CRC(97f20fdc) SHA1(7cb3cd0637b0db889a3d552fd7c1a916eee5ca27) )
	ROM_LOAD( "b30_10.12c", 0x10000, 0x08000, CRC(170c01db) SHA1(f4c5a1600f6cbb48abbace66c6f7514f79138e8b) )
	ROM_LOAD( "b30_09.10c", 0x18000, 0x08000, CRC(44f5accd) SHA1(2f9bdebe71c8be195332356df68992fd38d86994) )

	ROM_REGION( 0x40000, "scu", 0 )
	ROM_LOAD( "b30_20_hack01.12d", 0x00000, 0x10000, CRC(41c8f4ea) SHA1(9da6911b89b5cf49b64a8bcb12ab191cc98316f2) )
	ROM_LOAD( "b30_19_hack01.14d", 0x10000, 0x10000, CRC(8d5db99e) SHA1(33a1a51396fd289ee23ea1c645bc85bfed37848d) )
	ROM_LOAD( "b30_18_hack01.15d", 0x20000, 0x10000, CRC(eade1ca3) SHA1(af62d4b3a4072d6b0970a47ab6ef68987bac9c93) )
	ROM_LOAD( "b30_17_hack01.16d", 0x30000, 0x10000, CRC(6a559622) SHA1(8a07f792efea9d521a5fd0169a5d6c15fe615d5d) )

	ROM_REGION( 0x260, "proms", 0 )
	ROM_LOAD( "82s129.d3", 0x000, 0x100, CRC(24e7d62f) SHA1(1c06a1ef1b6a722794ca1d5ee2c476ecaa5178a3) )
	ROM_LOAD( "82s129.d4", 0x100, 0x100, CRC(a50cef09) SHA1(55cafb5b2551b80ae708e9b966cf37c70a16d310) )
	ROM_LOAD( "82s123.d2", 0x200, 0x020, CRC(f72482db) SHA1(b0cb911f9c81f6088a5aa8760916ddae1f8534d7) )
	ROM_LOAD( "82s123.e18", 0x220, 0x020, CRC(bc88cced) SHA1(5055362710c0f58823c05fb4c0e0eec638b91e3d) )
	ROM_LOAD( "82s123.b24", 0x240, 0x020, CRC(4fb5df2a) SHA1(506ef2c8e4cf45c256d6831a0a5760732f2de422) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Twin Twist
GAME( 2002, twincobrhack01, twincobr, twincobr, twincobr,  twincobr_state, init_twincobr, ROT270, "hack", "Twin Twist (Airplane sprite change)", MACHINE_SUPPORTS_SAVE )