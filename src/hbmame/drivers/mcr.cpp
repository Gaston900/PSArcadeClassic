// NeoEX
// copyright-holders:Gaston90
#include "../mame/drivers/mcr.cpp"

/******
  Hack
********/

ROM_START( tapperhc01 ) //stapper
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "tapper_c.p.u._pg_0_1c.1c",   0x00000, 0x4000, CRC(127171d1) SHA1(373e9a9d73b71e100c02862662d025f5ead2f94d) ) /* labeled TAPPER C.P.U. PRO 0 1C 1/12/84 */
	ROM_LOAD( "tapper_c.p.u._pg_1_2c.1c",   0x04000, 0x4000, CRC(9d6a47f7) SHA1(e493e46fc70a765e54bfdd7ba7ca570e6a5c79d6) ) /* labeled TAPPER C.P.U. PRO 1 2C 1/12/84 */
	ROM_LOAD( "tapper_c.p.u._pg_2_3c.3c",   0x08000, 0x4000, CRC(3a1f8778) SHA1(cb46a2248289ced7282b1463f433dcb970c42c1a) ) /* labeled TAPPER C.P.U. PRO 2 3C 1/12/84 */
	ROM_LOAD( "tapper_c.p.u._pg_3_4c.4c",   0x0c000, 0x2000, CRC(e8dcdaa4) SHA1(45bf1571a2418c7dc00ccc7061a3e04e65cb6bff) ) /* labeled TAPPER C.P.U. PRO 3 4C 1/12/84 */

	ROM_REGION( 0x10000, "ssio:cpu", 0 )
	ROM_LOAD( "tapper_sound_snd_0_a7_12-7-83.a7", 0x0000, 0x1000, CRC(0e8bb9d5) SHA1(9e281c340b7702523c86d56317efad9e3688e585) )
	ROM_LOAD( "tapper_sound_snd_1_a8_12-7-83.a8", 0x1000, 0x1000, CRC(0cf0e29b) SHA1(14334b9d2bfece3fe5bda0cbd53158ead8d27e53) )
	ROM_LOAD( "tapper_sound_snd_2_a9_12-7-83.a9", 0x2000, 0x1000, CRC(31eb6dc6) SHA1(b38bba5f12516d899e023f99147868e3402fbd7b) )
	ROM_LOAD( "tapper_sound_snd_3_a10_12-7-83.a10", 0x3000, 0x1000, CRC(01a9be6a) SHA1(0011407c1e886071282808c0a561789b1245a789) )

	ROM_REGION( 0x08000, "gfx1", 0 )
	ROM_LOAD( "tapper_c.p.u._bg_1_6f_12-7-83_hc01.6f",  0x00000, 0x4000, CRC(1326da21) SHA1(6886cbb83372ee4c53e19325a1552d312ce5de69) )
	ROM_LOAD( "tapper_c.p.u._bg_0_5f_12-7-83_hc01.5f",  0x04000, 0x4000, CRC(539b93c3) SHA1(6196516940893fd72d0c0f18efa7584a2df44833) )

	ROM_REGION( 0x20000, "gfx2", 0 )
	ROM_LOAD( "tapper_video_fg_1_a7_12-7-83_hc01.a7",  0x00000, 0x4000, CRC(29dd8e85) SHA1(f7f7e8a3aebf075fb9a2508ce438ed3bbfdcddba) )
	ROM_LOAD( "tapper_video_fg_0_a8_12-7-83_hc01.a8",  0x04000, 0x4000, CRC(a8ba850f) SHA1(e143dab595e129936a4744266788542422e3c503) )
	ROM_LOAD( "tapper_video_fg_3_a5_12-7-83_hc01.a5",  0x08000, 0x4000, CRC(3d9133e4) SHA1(3ca946aee704d59a150a9cd8ea02edf5204022e3) )
	ROM_LOAD( "tapper_video_fg_2_a6_12-7-83_hc01.a6",  0x0c000, 0x4000, CRC(9254d87c) SHA1(084f71436c984cb0c42cd0d07ce47ab0959b64e1) )
	ROM_LOAD( "tapper_video_fg_5_a3_12-7-83_hc01.a3",  0x10000, 0x4000, CRC(5ec2544f) SHA1(1a919b0a80417c0f0e22bac2ab6932411bd4ad55) )
	ROM_LOAD( "tapper_video_fg_4_a4_12-7-83_hc01.a4",  0x14000, 0x4000, CRC(9b970c4b) SHA1(f690708107c4923db5ffe344015388199c7e879a) )
	ROM_LOAD( "tapper_video_fg_7_a1_12-7-83_hc01.a1",  0x18000, 0x4000, CRC(a2ef5c06) SHA1(cce74ff117921eb0438524e7f598fd2117044b1c) )
	ROM_LOAD( "tapper_video_fg_6_a2_12-7-83_hc01.a2",  0x1c000, 0x4000, CRC(1baca746) SHA1(3c7015e63ab1a3f98485415e212a4b80f648dcae) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
/* Mcr Hack */
GAME( 2002, tapperhc01,     tapper,  mcr_91490, tapper, mcr_state, init_mcr_91490, ROT0,  "DC", "Tapper (Simpsons Hack)", MACHINE_SUPPORTS_SAVE )
