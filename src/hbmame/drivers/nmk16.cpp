// NeoEX
// Copyright-Holders:Gaston90
#include "../mame/drivers/nmk16.cpp"

/******
  Hack
********/

ROM_START( vandykehc01 ) //vandykeplus
	ROM_REGION( 0x40000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "vdk-1_hc01.16",  0x00000, 0x20000, CRC(4b193f69) SHA1(4b5dc228e1c529900e56be5aa19d4957be37b130) )
	ROM_LOAD16_BYTE( "vdk-2_hc01.15",  0x00001, 0x20000, CRC(8fef26f0) SHA1(665c384e5c79aeb16f7e234ad02584f8ea301a91) )

	ROM_REGION(0x10000, "audiocpu", 0 )
	ROM_LOAD( "vdk-4.127",    0x00000, 0x10000, CRC(eba544f0) SHA1(36f6d048d15a392542a9220a244d8a7049aaff8b) )

	ROM_REGION( 0x010000, "fgtile", 0 )
	ROM_LOAD( "vdk-3.222",      0x000000, 0x010000, CRC(5a547c1b) SHA1(2d61f51ce2f91ebf0053ce3a00911d1bcbaba816) )

	ROM_REGION( 0x080000, "bgtile", 0 )
	ROM_LOAD( "vdk-01.13",      0x000000, 0x080000, CRC(195a24be) SHA1(3a20dd746a87efc5c1fdc5025b709efeff82e05e) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "vdk-07.202",  0x000000, 0x080000, CRC(42d41f06) SHA1(69fd1d38187b8081f65acea2424bc1a0d455d90c) )
	ROM_LOAD16_BYTE( "vdk-06.203",  0x000001, 0x080000, CRC(d54722a8) SHA1(47f8e97b29ae0ff1a1d7d50734e4219a87a2ed57) )
	ROM_LOAD16_BYTE( "vdk-04.2-1",  0x100000, 0x080000, CRC(0a730547) SHA1(afac0549eb86d1fab5ca8ae2a0dad14144f55c02) )
	ROM_LOAD16_BYTE( "vdk-05.3-1",  0x100001, 0x080000, CRC(ba456d27) SHA1(5485a560ae2c2c8b6fdec314393c02a3de758ef3) )

	ROM_REGION( 0x080000, "oki1", 0 )
	ROM_LOAD( "vdk-02.126",     0x000000, 0x080000, CRC(b2103274) SHA1(6bbdc912393607cd5306be946327c5ea0178c7a6) )

	ROM_REGION( 0x080000, "oki2", 0 )
	ROM_LOAD( "vdk-03.165",     0x000000, 0x080000, CRC(631776d3) SHA1(ffd76e5b03130252c55eaa6ae7edfee5632dae73) )

	ROM_REGION( 0x0200, "proms", 0 )
	ROM_LOAD( "ic100.bpr", 0x0000, 0x0100, CRC(98ed1c97) SHA1(f125ad05c3cbd1b1ab356161f9b1d814781d4c3b) )
	ROM_LOAD( "ic101.bpr", 0x0100, 0x0100, CRC(cfdbb86c) SHA1(588822f6308a860937349c9106c2b4b1a75823ec) )
ROM_END

/*    YEAR  NAME            PARENT     MACHINE       INPUT                          INIT    MONITOR   COMPANY       FULLNAME FLAGS */
/* NMK16 Hack */
GAME( 2025, vandykehc01,    vandyke,   vandyke,      vandyke,      nmk16_state, empty_init, ROT270,  "GOTVG",       "Vandyke (Enhanced 2025-02-12)", 0 )

