// Proyecto Shadows Arcade Classic+
// copyright-holders:Gaston90
#include "../mame/drivers/vamphalf.cpp"
 
 /*************
 Age Of Heroes 
****************/

ROM_START( aohhack01 )
	ROM_REGION32_BE( 0x400000, "maincpu", ROMREGION_ERASE00 )
	ROM_LOAD16_WORD_SWAP( "rom1", 0x000000, 0x200000, CRC(2e55ff55) SHA1(b2b7605b87ee609dfbc7c21dfae0ef8d847019f0) )
	ROM_LOAD16_WORD_SWAP( "rom2_hack01", 0x200000, 0x200000, CRC(68da971c) SHA1(670e3478d009d74772a4ec62e84e9eb8c87ff279) )

	ROM_REGION( 0x4000000, "gfx", 0 )
	ROM_LOAD32_WORD( "g05", 0x0000002, 0x800000, CRC(64c8f493) SHA1(d487a74c813abbd0a612f8346eed8a7c3ff3e84e) )
	ROM_LOAD32_WORD( "g09", 0x0000000, 0x800000, CRC(c359febb) SHA1(7955385748e24dd076bc4f954b193a53c0a729c5) )
	ROM_LOAD32_WORD( "g06", 0x1000002, 0x800000, CRC(ffbc9fe5) SHA1(5e0e5cfdf6af23db0733c9fedee9c5f9ccde1109) )
	ROM_LOAD32_WORD( "g10", 0x1000000, 0x800000, CRC(08217573) SHA1(10cecdfc3a1ef835a62325b023d3bca8d0aea67d) )
	ROM_LOAD32_WORD( "g07", 0x2000002, 0x800000, CRC(5cb3c86a) SHA1(2e89f467c1a220f2510977677215e040295c3dd0) )
	ROM_LOAD32_WORD( "g11", 0x2000000, 0x800000, CRC(5f0461b8) SHA1(a0ac37d9a357e69367b8fee68bc358bfea5ecca0) )
	ROM_LOAD32_WORD( "g08", 0x3000002, 0x800000, CRC(1fd08aa0) SHA1(376a91220cd6e63418b04d590b232bb1079a40c7) )
	ROM_LOAD32_WORD( "g12", 0x3000000, 0x800000, CRC(e437b35f) SHA1(411d2926d619fba057476864f0e580f608830522) )

	ROM_REGION( 0x40000, "oki_1", 0 )
	ROM_LOAD( "rom3", 0x00000, 0x40000, CRC(db8cb455) SHA1(6723b4018208d554bd1bf1e0640b72d2f4f47302) )

	ROM_REGION( 0x80000, "oki2", 0 )
	ROM_LOAD( "rom4", 0x00000, 0x80000, CRC(bba47755) SHA1(e6eeb5f64eaa88a74536119b731a76921e79f8ff) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Age Of Heroes
GAME( 2001, aohhack01,   aoh,    aoh,   aoh,      vamphalf_state,      init_aoh,    ROT0,   "DDJ",    "Age Of Heroes - Silkroad 2 (Easy Move)", MACHINE_SUPPORTS_SAVE )
