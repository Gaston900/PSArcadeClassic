// NeoEX
// copyright-holders:Gaston90
#include "../mame/drivers/snowbros.cpp"
#include "../mame/video/kan_pand.cpp"

/******
  Hack
********/

ROM_START( snowbroshc01 ) //snowbrosxnlx
	ROM_REGION( 0x40000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sn6_hc01.bin",  0x00000, 0x20000, CRC(f18de1bb) SHA1(4d189cf7be03ca9a8fa49b122bf7e08844657c84) )
	ROM_LOAD16_BYTE( "sn5_hc01.bin",  0x00001, 0x20000, CRC(6272cf27) SHA1(5cae082931bd14e4cb3c61f33141565e438062d4) )

	ROM_REGION( 0x10000, "soundcpu", 0 )
	ROM_LOAD( "sbros-4.29",   0x0000, 0x8000, CRC(e6eab4e4) SHA1(d08187d03b21192e188784cb840a37a7bdb5ad32) )

	ROM_REGION( 0x80000, "gfx1", 0 )
	ROM_LOAD( "sbros-1.41",   0x00000, 0x80000, CRC(16f06b3a) SHA1(c64d3b2d32f0f0fcf1d8c5f02f8589d59ddfd428) )
ROM_END

/*    YEAR  NAME            PARENT     MACHINE       INPUT                       INIT    MONITOR   COMPANY       FULLNAME FLAGS */
/* Snowbros Hack */
GAME( 2024, snowbroshc01,   snowbros,  snowbros,    snowbros, snowbros_state, empty_init, ROT0,    "GOTVG",      "Snow Bros (Infinite Power 2024-11-22)", MACHINE_SUPPORTS_SAVE )
