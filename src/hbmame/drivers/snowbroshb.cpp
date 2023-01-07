// Proyecto Shadows Arcade Classic+
// copyright-holders:Gaston90
#include "../mame/drivers/snowbros.cpp"
#include "../mame/video/kan_pand.cpp"
 
/********************
  Hack And Homebrow
***********************/

ROM_START( snowbroshc01 ) //snowbrosa
	ROM_REGION( 0x40000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sn6_hack01.bin",  0x00000, 0x20000, CRC(090800df) SHA1(02cdb6a07a9043ef26f4abb6769928be8324db85) )
	ROM_LOAD16_BYTE( "sn5_hack01.bin",  0x00001, 0x20000, CRC(b7ebd161) SHA1(66cb4baf3eb341dddb9381b6b4e1873f5678a916) )

	ROM_REGION( 0x10000, "soundcpu", 0 )
	ROM_LOAD( "sbros-4.29",   0x0000, 0x8000, CRC(e6eab4e4) SHA1(d08187d03b21192e188784cb840a37a7bdb5ad32) )

	ROM_REGION( 0x80000, "gfx1", 0 )
	ROM_LOAD( "sbros-1.41",   0x00000, 0x80000, CRC(16f06b3a) SHA1(c64d3b2d32f0f0fcf1d8c5f02f8589d59ddfd428) )
ROM_END

/*    YEAR    NAME          PARENT     MACHINE    INPUT                        INIT      MONITOR   COMPANY       FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2018, snowbroshc01,   snowbros,  snowbros,  snowbros, snowbros_state, empty_init,   ROT0,    "hack",       "Snow Bros (Cure Version 2.6B 2018-08-15)", MACHINE_SUPPORTS_SAVE )
