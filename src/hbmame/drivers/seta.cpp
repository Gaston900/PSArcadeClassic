// Proyecto Shadows Arcade Classic+
// copyright-holders:Gaston90
#include "../mame/drivers/seta.cpp"

 /*******************
 The FairyLand Story   
**********************/

ROM_START( blandiahack01 )
	ROM_REGION( 0x200000, "maincpu", 0 )  
	ROM_LOAD16_BYTE( "ux001001_hack01.u3", 0x000000, 0x040000, CRC(245d404d) SHA1(708dede3bb37e1a90fbd196cf7297f1c5c4fc518) )
	ROM_LOAD16_BYTE( "ux001002_hack01.u4", 0x000001, 0x040000, CRC(9aa9fb5c) SHA1(24ead69c38573ea2b0f1cc8de5c46adb712e5b3b) )
	ROM_LOAD16_WORD_SWAP( "ux001003.u202",    0x100000, 0x100000, CRC(98052c63) SHA1(b523596de29038b3ec9f1b6e1f7374a6a8709d42) )

	ROM_REGION( 0x400000, "gfx1", 0 )
	ROM_LOAD( "ux001005.u200", 0x300000, 0x100000, CRC(bea0c4a5) SHA1(a690c17fb7cbdab533c1dfad13abbad9359b9631) )
	ROM_LOAD( "ux001007.u201", 0x100000, 0x100000, CRC(4440fdd1) SHA1(7bfee90f81a2c867bd487abcf5905393ad400902) )
	ROM_LOAD( "ux001006.u63",  0x200000, 0x100000, CRC(abc01cf7) SHA1(c3f26e75eeb68073d2825be8df82cc6afcfbfb26) )
	ROM_LOAD( "ux001008.u64",  0x000000, 0x100000, CRC(413647b6) SHA1(594e010ca6f49ec82cc6d44fe23ac3427c4c3dbd) )

	ROM_REGION( 0x180000, "gfx2", 0 )
	ROM_LOAD24_BYTE     ( "ux001009.u65", 0x000000, 0x080000, CRC(bc6f6aea) SHA1(673efa0c70587b5650ccf0a3c4bc316f53d52ba6) )
	ROM_LOAD24_WORD_SWAP( "ux001010.u66", 0x000001, 0x080000, CRC(bd7f7614) SHA1(dc865ff0f327f460956915b2018aaac815e8fce5) )

	ROM_REGION( 0x180000, "gfx3", 0 )
	ROM_LOAD24_BYTE     ( "ux001011.u67",  0x000000, 0x080000, CRC(5efe0397) SHA1(a294a2dae9a10e93912543a8614a7f960a011f27) )
	ROM_LOAD24_WORD_SWAP( "ux001012.u068", 0x000001, 0x080000, CRC(f29959f6) SHA1(edccea3d0bf972a07edd6339e18792d089033bff) )

	ROM_REGION( 0x200000, "x1snd", 0 )
	ROM_LOAD( "ux001013.u69", 0x000000, 0x100000, CRC(5cd273cd) SHA1(602e1f10454e2b1c941f2e6983872bb9ca77a542) )
	ROM_LOAD( "ux001014.u70", 0x100000, 0x080000, CRC(86b49b4e) SHA1(045b352950d848907af4c22b817d154b2cfff382) )

	ROM_REGION( 0xc00, "plds", 0 )
	ROM_LOAD( "ux-015.u206", 0x000, 0x117, CRC(08cddbdd) SHA1(c7330b96375f96406c63abe5d17d02e84828d884) )
	ROM_LOAD( "ux-016.u116", 0x200, 0x117, CRC(9734f1af) SHA1(e7299892a26e9e8ee607ece93cefdee19a13ffae) )
	ROM_LOAD( "ux-017.u14",  0x400, 0x117, CRC(9e95d8d5) SHA1(f7e7250e9aa6fc1c14874230a5b0019704e54c4c) )
	ROM_LOAD( "ux-018.u35",  0x600, 0x117, CRC(c9579473) SHA1(ff65a5ed840b60bd8416ae7e11805635bfcec9ad) )
	ROM_LOAD( "ux-019.u36",  0x800, 0x117, CRC(d85c359d) SHA1(251c1fc833c1be6b15e70240cbb6c997443baea3) )
	ROM_LOAD( "ux-020.u76",  0xa00, 0x117, CRC(116278bf) SHA1(e34bceab30dce17c2a9cb0bf51a5eda0a89da08c) )
ROM_END

ROM_START( blandiahack02 )
	ROM_REGION( 0x200000, "maincpu", 0 )  
	ROM_LOAD16_BYTE( "ux001001_hack02.u3", 0x000000, 0x040000, CRC(370b5fef) SHA1(39b310e7c1f5e4b17d618b2ad583697cbbdc4936) )
	ROM_LOAD16_BYTE( "ux001002_hack02.u4", 0x000001, 0x040000, CRC(cdbf1488) SHA1(ed3c0ecf0d15ece35d54e8d6be64f6091328505e) )
	ROM_LOAD16_WORD_SWAP( "ux001003.u202",    0x100000, 0x100000, CRC(98052c63) SHA1(b523596de29038b3ec9f1b6e1f7374a6a8709d42) )

	ROM_REGION( 0x400000, "gfx1", 0 )
	ROM_LOAD( "ux001005.u200", 0x300000, 0x100000, CRC(bea0c4a5) SHA1(a690c17fb7cbdab533c1dfad13abbad9359b9631) )
	ROM_LOAD( "ux001007.u201", 0x100000, 0x100000, CRC(4440fdd1) SHA1(7bfee90f81a2c867bd487abcf5905393ad400902) )
	ROM_LOAD( "ux001006.u63",  0x200000, 0x100000, CRC(abc01cf7) SHA1(c3f26e75eeb68073d2825be8df82cc6afcfbfb26) )
	ROM_LOAD( "ux001008.u64",  0x000000, 0x100000, CRC(413647b6) SHA1(594e010ca6f49ec82cc6d44fe23ac3427c4c3dbd) )

	ROM_REGION( 0x180000, "gfx2", 0 )
	ROM_LOAD24_BYTE     ( "ux001009.u65", 0x000000, 0x080000, CRC(bc6f6aea) SHA1(673efa0c70587b5650ccf0a3c4bc316f53d52ba6) )
	ROM_LOAD24_WORD_SWAP( "ux001010.u66", 0x000001, 0x080000, CRC(bd7f7614) SHA1(dc865ff0f327f460956915b2018aaac815e8fce5) )

	ROM_REGION( 0x180000, "gfx3", 0 )
	ROM_LOAD24_BYTE     ( "ux001011.u67",  0x000000, 0x080000, CRC(5efe0397) SHA1(a294a2dae9a10e93912543a8614a7f960a011f27) )
	ROM_LOAD24_WORD_SWAP( "ux001012.u068", 0x000001, 0x080000, CRC(f29959f6) SHA1(edccea3d0bf972a07edd6339e18792d089033bff) )

	ROM_REGION( 0x200000, "x1snd", 0 )
	ROM_LOAD( "ux001013.u69", 0x000000, 0x100000, CRC(5cd273cd) SHA1(602e1f10454e2b1c941f2e6983872bb9ca77a542) )
	ROM_LOAD( "ux001014.u70", 0x100000, 0x080000, CRC(86b49b4e) SHA1(045b352950d848907af4c22b817d154b2cfff382) )

	ROM_REGION( 0xc00, "plds", 0 )
	ROM_LOAD( "ux-015.u206", 0x000, 0x117, CRC(08cddbdd) SHA1(c7330b96375f96406c63abe5d17d02e84828d884) )
	ROM_LOAD( "ux-016.u116", 0x200, 0x117, CRC(9734f1af) SHA1(e7299892a26e9e8ee607ece93cefdee19a13ffae) )
	ROM_LOAD( "ux-017.u14",  0x400, 0x117, CRC(9e95d8d5) SHA1(f7e7250e9aa6fc1c14874230a5b0019704e54c4c) )
	ROM_LOAD( "ux-018.u35",  0x600, 0x117, CRC(c9579473) SHA1(ff65a5ed840b60bd8416ae7e11805635bfcec9ad) )
	ROM_LOAD( "ux-019.u36",  0x800, 0x117, CRC(d85c359d) SHA1(251c1fc833c1be6b15e70240cbb6c997443baea3) )
	ROM_LOAD( "ux-020.u76",  0xa00, 0x117, CRC(116278bf) SHA1(e34bceab30dce17c2a9cb0bf51a5eda0a89da08c) )
ROM_END

ROM_START( blandiahack03 )
	ROM_REGION( 0x200000, "maincpu", 0 )  
	ROM_LOAD16_BYTE( "ux001001_hack03.u3", 0x000000, 0x040000, CRC(3020be51) SHA1(0e00fa720e23271cacb745830d41a0070476f935) )
	ROM_LOAD16_BYTE( "ux001002_hack03.u4", 0x000001, 0x040000, CRC(ee030ea6) SHA1(dd917cc5bee20368257331ede395e2774fe094ea) )
	ROM_LOAD16_WORD_SWAP( "ux001003.u202",    0x100000, 0x100000, CRC(98052c63) SHA1(b523596de29038b3ec9f1b6e1f7374a6a8709d42) )

	ROM_REGION( 0x400000, "gfx1", 0 )
	ROM_LOAD( "ux001005.u200", 0x300000, 0x100000, CRC(bea0c4a5) SHA1(a690c17fb7cbdab533c1dfad13abbad9359b9631) )
	ROM_LOAD( "ux001007.u201", 0x100000, 0x100000, CRC(4440fdd1) SHA1(7bfee90f81a2c867bd487abcf5905393ad400902) )
	ROM_LOAD( "ux001006.u63",  0x200000, 0x100000, CRC(abc01cf7) SHA1(c3f26e75eeb68073d2825be8df82cc6afcfbfb26) )
	ROM_LOAD( "ux001008.u64",  0x000000, 0x100000, CRC(413647b6) SHA1(594e010ca6f49ec82cc6d44fe23ac3427c4c3dbd) )

	ROM_REGION( 0x180000, "gfx2", 0 )
	ROM_LOAD24_BYTE     ( "ux001009.u65", 0x000000, 0x080000, CRC(bc6f6aea) SHA1(673efa0c70587b5650ccf0a3c4bc316f53d52ba6) )
	ROM_LOAD24_WORD_SWAP( "ux001010.u66", 0x000001, 0x080000, CRC(bd7f7614) SHA1(dc865ff0f327f460956915b2018aaac815e8fce5) )

	ROM_REGION( 0x180000, "gfx3", 0 )
	ROM_LOAD24_BYTE     ( "ux001011.u67",  0x000000, 0x080000, CRC(5efe0397) SHA1(a294a2dae9a10e93912543a8614a7f960a011f27) )
	ROM_LOAD24_WORD_SWAP( "ux001012.u068", 0x000001, 0x080000, CRC(f29959f6) SHA1(edccea3d0bf972a07edd6339e18792d089033bff) )

	ROM_REGION( 0x200000, "x1snd", 0 )
	ROM_LOAD( "ux001013.u69", 0x000000, 0x100000, CRC(5cd273cd) SHA1(602e1f10454e2b1c941f2e6983872bb9ca77a542) )
	ROM_LOAD( "ux001014.u70", 0x100000, 0x080000, CRC(86b49b4e) SHA1(045b352950d848907af4c22b817d154b2cfff382) )

	ROM_REGION( 0xc00, "plds", 0 )
	ROM_LOAD( "ux-015.u206", 0x000, 0x117, CRC(08cddbdd) SHA1(c7330b96375f96406c63abe5d17d02e84828d884) )
	ROM_LOAD( "ux-016.u116", 0x200, 0x117, CRC(9734f1af) SHA1(e7299892a26e9e8ee607ece93cefdee19a13ffae) )
	ROM_LOAD( "ux-017.u14",  0x400, 0x117, CRC(9e95d8d5) SHA1(f7e7250e9aa6fc1c14874230a5b0019704e54c4c) )
	ROM_LOAD( "ux-018.u35",  0x600, 0x117, CRC(c9579473) SHA1(ff65a5ed840b60bd8416ae7e11805635bfcec9ad) )
	ROM_LOAD( "ux-019.u36",  0x800, 0x117, CRC(d85c359d) SHA1(251c1fc833c1be6b15e70240cbb6c997443baea3) )
	ROM_LOAD( "ux-020.u76",  0xa00, 0x117, CRC(116278bf) SHA1(e34bceab30dce17c2a9cb0bf51a5eda0a89da08c) )
ROM_END

 /******************
 Mobile Suit Gundam  
*********************/

ROM_START( msgundamhack01 )
	ROM_REGION( 0x200000, "maincpu", 0 )  
	ROM_LOAD16_WORD_SWAP( "fa003002_hack01.u25",  0x000000, 0x080000, CRC(b06cc71a) SHA1(b5de10639458a569fe4789e3595fa4acd645dbf4) )
	ROM_LOAD16_WORD_SWAP( "fa001001.u20",  0x100000, 0x100000, CRC(fca139d0) SHA1(b56282c69f7ec64c697a48e42d59a2565401c032) )

	ROM_REGION( 0x400000, "gfx1", 0 )
	ROM_LOAD( "fa001008.u21",  0x000000, 0x200000, CRC(e7accf48) SHA1(dca9d53bc9cf0ecb661358d5a3f388c4ce9388e7) )
	ROM_LOAD( "fa001007.u22",  0x200000, 0x200000, CRC(793198a6) SHA1(45f53870e74b14126680d18dd58dbbe01a6ef509) )

	ROM_REGION( 0x100000, "gfx2", 0 )
	ROM_LOAD16_WORD_SWAP( "fa001006.u23",  0x000000, 0x100000, CRC(3b60365c) SHA1(bdf5a0b1b45eb75dbbb6725d1e5303716321aeb9) )

	ROM_REGION( 0x080000, "gfx3", 0 )  
	ROM_LOAD16_WORD_SWAP( "fa001005.u24",  0x000000, 0x080000, CRC(8cd7ff86) SHA1(ce7eb90776e21239f8f52e822c636143506c6f9b) )

	ROM_REGION( 0x100000, "x1snd", 0 )
	ROM_LOAD( "fa001004.u26",  0x000000, 0x100000, CRC(b965f07c) SHA1(ff7827cc80655465ffbb732d55ba81f21f51a5ca) )
	
	ROM_REGION( 0xa00, "plds", 0 )
	ROM_LOAD( "fa-011.u50", 0x000, 0x104, NO_DUMP )
	ROM_LOAD( "fa-012.u51", 0x200, 0x104, NO_DUMP )
	ROM_LOAD( "fa-013.u52", 0x400, 0x104, NO_DUMP )
	ROM_LOAD( "fa-014.u53", 0x600, 0x104, NO_DUMP )
	ROM_LOAD( "fa-015.u54", 0x800, 0x104, NO_DUMP )
ROM_END

/*    YEAR  NAME           PARENT    MACHINE     INPUT     INIT            MONITOR COMPANY         FULLNAME FLAGS */
// The FairyLand Story
GAME( 1992, blandiahack01,   blandia,   blandia,   blandia,   seta_state,     init_bankx1,    ROT0,   "DDJ",   "Blandia (Enable hidden characters)", MACHINE_IMPERFECT_GRAPHICS )
GAME( 1992, blandiahack02,   blandia,   blandia,   blandia,   seta_state,     init_bankx1,    ROT0,   "DDJ",   "Blandia (Easy Move)", MACHINE_IMPERFECT_GRAPHICS )
GAME( 2018, blandiahack03,   blandia,   blandia,   blandia,   seta_state,     init_bankx1,    ROT0,   "hack",  "Blandia (Boss With Simple Attack Edition  2018-07-28)", MACHINE_IMPERFECT_GRAPHICS )
// Mobile Suit Gundam
GAME( 1993, msgundamhack01,  msgundam,  msgundam,  msgundam,  seta_state,     empty_init,     ROT0,   "DDJ",   "Mobile Suit Gundam (Easy Move)", 0 )
