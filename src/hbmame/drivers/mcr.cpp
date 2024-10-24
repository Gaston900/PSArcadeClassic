// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/mcr.cpp"

 /****
 Tron
*******/

ROM_START( handiman ) // all roms from tron2 except gfx2
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "scpu-pga_lctn-c2_tron_jun_25.c2", 0x0000, 0x2000, CRC(5151770b) SHA1(26f4d830de7be228528e462dd628f439629a2641) )
	ROM_LOAD( "scpu-pgb_lctn-c3_tron_aug_9.c3", 0x2000, 0x2000, CRC(8ddf8717) SHA1(e0c294afa8ba0b0ba89e3e0fb3ff6d8fc4398e32) )
	ROM_LOAD( "scpu-pgc_lctn-c4_tron_aug_9.c4", 0x4000, 0x2000, CRC(4241e3a0) SHA1(24c1bd2f31e194542571c391c5dccf21354115c2) )
	ROM_LOAD( "scpu-pgd_lctn-c5_tron_aug_9.c5", 0x6000, 0x2000, CRC(035d2fe7) SHA1(1b827ca30a439d2f4cc94fcc0e90ee0cf87e018c) )
	ROM_LOAD( "scpu-pge_lctn-c6_tron_aug_9.c6", 0x8000, 0x2000, CRC(24c185d8) SHA1(45ac7c53f6f4eba5c7bf3fc6559cddd3821eddad) )
	ROM_LOAD( "scpu-pgf_lctn-c7_tron_aug_9.c7", 0xa000, 0x2000, CRC(38c4bbaf) SHA1(a7cd496ce75199b8279ea963520cf70d5f562bb2) )

	ROM_REGION( 0x10000, "ssio:cpu", 0 )
	ROM_LOAD( "ssi-0a_lctn-a7_tron.a7",   0x0000, 0x1000, CRC(765e6eba) SHA1(42efeefc8571dfc237c0be3368248f1e56add92e) )
	ROM_LOAD( "ssi-0b_lctn-a8_tron.a8",   0x1000, 0x1000, CRC(1b90ccdd) SHA1(0876e5eeaa63bb8cc97f3634a6ddd8a29a9b012f) )
	ROM_LOAD( "ssi-0c_lctn-a9_tron.a9",   0x2000, 0x1000, CRC(3a4bc629) SHA1(ce8452a99a313ae7429de471bbea39de08c9fd4b) )

	ROM_REGION( 0x04000, "gfx1", 0 )
	ROM_LOAD( "scpu-bgg_lctn-g3_tron.g3", 0x0000, 0x2000, CRC(1a9ed2f5) SHA1(b0d85b47873ac8ad475da18b9540d37232cb2b7c) )
	ROM_LOAD( "scpu-bgh_lctn-g4_tron.g4", 0x2000, 0x2000, CRC(3220f974) SHA1(a38ea5f1db27f05d9689db838ce7a8de98f34837) )

	ROM_REGION( 0x10000, "gfx2", 0 )
	ROM_LOAD( "handiman.e1",     0x00000, 0x2000, CRC(8fb79ed7) SHA1(70e5f2aecda3d055eaedf2039128e549a94bd2cd) )
	ROM_LOAD( "handiman.d1",     0x04000, 0x2000, CRC(c0b2b28e) SHA1(3d9d2c1b7a136f02e5c5595d52add03892cb0db1) )
	ROM_LOAD( "handiman.c1",     0x08000, 0x2000, CRC(ee776741) SHA1(02ea99dd02cd469d1425a958202efe28dc202291) )
	ROM_LOAD( "handiman.a1",     0x0c000, 0x2000, CRC(e17ec630) SHA1(7929bfeea0e5e47d412619f08ca09a31618b96da) )
ROM_END

 /***************
 Satan's Hollow
*******************/

ROM_START( shtron )
	ROM_REGION( 0x10000, "maincpu", 0 ) // same as shollow2 except for 2 cpu roms
	ROM_LOAD( "shtron.00",    0x0000, 0x2000, CRC(9AEC754C) SHA1(D17A221CEB8AF59D9087AE63A73026C0BD1D58CB) )
	ROM_LOAD( "sh-pro.01",    0x2000, 0x2000, CRC(b99f6ff8) SHA1(575cdba5bf9965c7765ce913a3376c7ba36b8291) )
	ROM_LOAD( "shtron.02",    0x4000, 0x2000, CRC(621AD715) SHA1(8CD34D33C86D10142E0503994A0666AC77C08D4B) )
	ROM_LOAD( "sh-pro.03",    0x6000, 0x2000, CRC(0a64afb9) SHA1(3ac6660d2b0166c58ec4fecfe37ce36e545064df) )
	ROM_LOAD( "sh-pro.04",    0x8000, 0x2000, CRC(22fa9175) SHA1(fd8ea76b3a7ffaf48fc11dd3b7c58e548e3e57c5) )
	ROM_LOAD( "sh-pro.05",    0xa000, 0x2000, CRC(1716e2bb) SHA1(771e4c20d63e4e1d99723e6355db67064a278ae5) )

	ROM_REGION( 0x10000, "ssio:cpu", 0 )
	ROM_LOAD( "snd-0.a7",     0x0000, 0x1000, CRC(9d815bb3) SHA1(51af797e08dbe3921e11ce70c3d0da50979336a4) )
	ROM_LOAD( "snd-1.a8",     0x1000, 0x1000, CRC(9f253412) SHA1(a526e864073a2f9e67e2cbe53ab17fe726336241) )
	ROM_LOAD( "snd-2.a9",     0x2000, 0x1000, CRC(7783d6c6) SHA1(1fb2117532e7da28afdb9837bcb6848165cf8173) )

	ROM_REGION( 0x04000, "gfx1", 0 )
	ROM_LOAD( "sh-bg.00",     0x0000, 0x2000, CRC(3e2b333c) SHA1(b4347d0b3d6149e94da4a38684c0fab931e76cc5) )
	ROM_LOAD( "sh-bg.01",     0x2000, 0x2000, CRC(d1d70cc4) SHA1(550e2e8c0bcbf7913b218fe48cd3324622c8d0f4) )

	ROM_REGION( 0x08000, "gfx2", 0 )
	ROM_LOAD( "sh-fg.00",     0x0000, 0x2000, CRC(33f4554e) SHA1(88dd803158d3c65429b79d2aaf8334130315aa93) )
	ROM_LOAD( "sh-fg.01",     0x2000, 0x2000, CRC(ba1a38b4) SHA1(cee5f0a66e40c779f1bfbb4bfafe5301385e7dae) )
	ROM_LOAD( "sh-fg.02",     0x4000, 0x2000, CRC(6b57f6da) SHA1(71165df59dd5ca037116dc0f46fd4f6aac6dbfd1) )
	ROM_LOAD( "sh-fg.03",     0x6000, 0x2000, CRC(37ea9d07) SHA1(82e006b01ee12390308be530d4b68fc2404b6b91) )
ROM_END

 /******
 Tapper
*********/

ROM_START( stapper ) // cpu roms from tapper
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "tappg0.bin",   0x00000, 0x4000, CRC(127171d1) SHA1(373e9a9d73b71e100c02862662d025f5ead2f94d) )
	ROM_LOAD( "tappg1.bin",   0x04000, 0x4000, CRC(9d6a47f7) SHA1(e493e46fc70a765e54bfdd7ba7ca570e6a5c79d6) )
	ROM_LOAD( "tappg2.bin",   0x08000, 0x4000, CRC(3a1f8778) SHA1(cb46a2248289ced7282b1463f433dcb970c42c1a) )
	ROM_LOAD( "tappg3.bin",   0x0c000, 0x2000, CRC(e8dcdaa4) SHA1(45bf1571a2418c7dc00ccc7061a3e04e65cb6bff) )

	ROM_REGION( 0x10000, "ssio:cpu", 0 )
	ROM_LOAD( "tapper_sound_snd_0_a7_12-7-83.a7", 0x0000, 0x1000, CRC(0e8bb9d5) SHA1(9e281c340b7702523c86d56317efad9e3688e585) )
	ROM_LOAD( "tapper_sound_snd_1_a8_12-7-83.a8", 0x1000, 0x1000, CRC(0cf0e29b) SHA1(14334b9d2bfece3fe5bda0cbd53158ead8d27e53) )
	ROM_LOAD( "tapper_sound_snd_2_a9_12-7-83.a9", 0x2000, 0x1000, CRC(31eb6dc6) SHA1(b38bba5f12516d899e023f99147868e3402fbd7b) )
	ROM_LOAD( "tapper_sound_snd_3_a10_12-7-83.a10", 0x3000, 0x1000, CRC(01a9be6a) SHA1(0011407c1e886071282808c0a561789b1245a789) )

	ROM_REGION( 0x08000, "gfx1", 0 )
	ROM_LOAD( "stapper.bg1",  0x00000, 0x4000, CRC(1326da21) SHA1(6886cbb83372ee4c53e19325a1552d312ce5de69) )
	ROM_LOAD( "stapper.bg0",  0x04000, 0x4000, CRC(539b93c3) SHA1(6196516940893fd72d0c0f18efa7584a2df44833) )

	ROM_REGION( 0x20000, "gfx2", 0 )
	ROM_LOAD( "stapper.fg1",  0x00000, 0x4000, CRC(29dd8e85) SHA1(f7f7e8a3aebf075fb9a2508ce438ed3bbfdcddba) )
	ROM_LOAD( "stapper.fg0",  0x04000, 0x4000, CRC(a8ba850f) SHA1(e143dab595e129936a4744266788542422e3c503) )
	ROM_LOAD( "stapper.fg3",  0x08000, 0x4000, CRC(3d9133e4) SHA1(3ca946aee704d59a150a9cd8ea02edf5204022e3) )
	ROM_LOAD( "stapper.fg2",  0x0c000, 0x4000, CRC(9254d87c) SHA1(084f71436c984cb0c42cd0d07ce47ab0959b64e1) )
	ROM_LOAD( "stapper.fg5",  0x10000, 0x4000, CRC(5ec2544f) SHA1(1a919b0a80417c0f0e22bac2ab6932411bd4ad55) )
	ROM_LOAD( "stapper.fg4",  0x14000, 0x4000, CRC(9b970c4b) SHA1(f690708107c4923db5ffe344015388199c7e879a) )
	ROM_LOAD( "stapper.fg7",  0x18000, 0x4000, CRC(a2ef5c06) SHA1(cce74ff117921eb0438524e7f598fd2117044b1c) )
	ROM_LOAD( "stapper.fg6",  0x1c000, 0x4000, CRC(1baca746) SHA1(3c7015e63ab1a3f98485415e212a4b80f648dcae) )
ROM_END

ROM_START( stapper1 )
	ROM_REGION( 0x10000, "maincpu", 0 ) // same as stapper except 2 of the cpu roms
	ROM_LOAD( "stapper1.pg0", 0x00000, 0x4000, CRC(c915f608) SHA1(aad2f1944334a7cdb0483613fdad40caab720259) )
	ROM_LOAD( "tappg1.bin",   0x04000, 0x4000, CRC(9d6a47f7) SHA1(e493e46fc70a765e54bfdd7ba7ca570e6a5c79d6) )
	ROM_LOAD( "tappg2.bin",   0x08000, 0x4000, CRC(3a1f8778) SHA1(cb46a2248289ced7282b1463f433dcb970c42c1a) )
	ROM_LOAD( "stapper1.pg3", 0x0c000, 0x2000, CRC(dd4c785f) SHA1(6e19e77a0af6073c3955c61cf741b13921ce6bf0) )

	ROM_REGION( 0x10000, "ssio:cpu", 0 )
	ROM_LOAD( "tapper_sound_snd_0_a7_12-7-83.a7", 0x0000, 0x1000, CRC(0e8bb9d5) SHA1(9e281c340b7702523c86d56317efad9e3688e585) )
	ROM_LOAD( "tapper_sound_snd_1_a8_12-7-83.a8", 0x1000, 0x1000, CRC(0cf0e29b) SHA1(14334b9d2bfece3fe5bda0cbd53158ead8d27e53) )
	ROM_LOAD( "tapper_sound_snd_2_a9_12-7-83.a9", 0x2000, 0x1000, CRC(31eb6dc6) SHA1(b38bba5f12516d899e023f99147868e3402fbd7b) )
	ROM_LOAD( "tapper_sound_snd_3_a10_12-7-83.a10", 0x3000, 0x1000, CRC(01a9be6a) SHA1(0011407c1e886071282808c0a561789b1245a789) )

	ROM_REGION( 0x08000, "gfx1", 0 )
	ROM_LOAD( "stapper.bg1",  0x00000, 0x4000, CRC(1326da21) SHA1(6886cbb83372ee4c53e19325a1552d312ce5de69) )
	ROM_LOAD( "stapper.bg0",  0x04000, 0x4000, CRC(539b93c3) SHA1(6196516940893fd72d0c0f18efa7584a2df44833) )

	ROM_REGION( 0x20000, "gfx2", 0 )
	ROM_LOAD( "stapper.fg1",  0x00000, 0x4000, CRC(29dd8e85) SHA1(f7f7e8a3aebf075fb9a2508ce438ed3bbfdcddba) )
	ROM_LOAD( "stapper.fg0",  0x04000, 0x4000, CRC(a8ba850f) SHA1(e143dab595e129936a4744266788542422e3c503) )
	ROM_LOAD( "stapper.fg3",  0x08000, 0x4000, CRC(3d9133e4) SHA1(3ca946aee704d59a150a9cd8ea02edf5204022e3) )
	ROM_LOAD( "stapper.fg2",  0x0c000, 0x4000, CRC(9254d87c) SHA1(084f71436c984cb0c42cd0d07ce47ab0959b64e1) )
	ROM_LOAD( "stapper.fg5",  0x10000, 0x4000, CRC(5ec2544f) SHA1(1a919b0a80417c0f0e22bac2ab6932411bd4ad55) )
	ROM_LOAD( "stapper.fg4",  0x14000, 0x4000, CRC(9b970c4b) SHA1(f690708107c4923db5ffe344015388199c7e879a) )
	ROM_LOAD( "stapper.fg7",  0x18000, 0x4000, CRC(a2ef5c06) SHA1(cce74ff117921eb0438524e7f598fd2117044b1c) )
	ROM_LOAD( "stapper.fg6",  0x1c000, 0x4000, CRC(1baca746) SHA1(3c7015e63ab1a3f98485415e212a4b80f648dcae) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Tron
GAME( 1998, handiman, tron,    mcr_90010, tron,   mcr_state, init_mcr_90010, ROT90, "hack",             "Handi-Man in Cyberworld", MACHINE_SUPPORTS_SAVE )
// Satan's Hollow
GAME( 2004, shtron,   shollow, mcr_90010, tron,   mcr_state, init_mcr_90010, ROT90, "hack",             "Satan's Hollow (Tron Hardware)", MACHINE_SUPPORTS_SAVE )
// Tapper
GAME( 2002, stapper,  tapper,  mcr_91490, tapper, mcr_state, init_mcr_91490, ROT0,  "hack",             "Tapper (Simpsons Hack)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, stapper1, tapper,  mcr_91490, tapper, mcr_state, init_mcr_91490, ROT0,  "hack",             "Tapper (Simpsons Hack ver.81)", MACHINE_SUPPORTS_SAVE )
