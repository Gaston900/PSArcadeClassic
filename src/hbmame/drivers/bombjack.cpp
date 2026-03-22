// NeoEX
// copyright-holders:Robbbert
#include "../mame/drivers/bombjack.cpp"

/******
  Hack
********/

ROM_START( bombjackhc01 )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "09_j01b.bin",  0x0000, 0x2000, CRC(c668dc30) SHA1(51dd6a2688b42e9f28f0882bd76f75be7ec3222a) )
	ROM_LOAD( "10_l01b.bin",  0x2000, 0x2000, CRC(52a1e5fb) SHA1(e1cdc4b4efbc6c7a1e4fa65019486617f2acba1b) )
	ROM_LOAD( "11_m01b.bin",  0x4000, 0x2000, CRC(b68a062a) SHA1(43bae56494ac0202aaa8f1ed5c1ed1bff775b2b8) )
	ROM_LOAD( "12_n01b_hc01.bin", 0x6000, 0x2000, CRC(b457909f) SHA1(807b30742a89a327721596c4f5d091912f0ab4ec) )
	ROM_LOAD( "13_hc01.1r",       0xc000, 0x2000, CRC(f8e14e2c) SHA1(a5dff87ad26eff6a07313594d9bce2ea568c8f26) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "01_h03t.bin",  0x0000, 0x2000, CRC(8407917d) SHA1(318face9f7a7ab6c7eeac773995040425e780aaf) )

	ROM_REGION( 0x3000, "chars", 0 )
	ROM_LOAD( "03_e08t_hc01.bin", 0x0000, 0x1000, CRC(df120e35) SHA1(b389320cd95fe3ac7bfb613098140d169c0485b1) )
	ROM_LOAD( "04_h08t_hc01.bin", 0x1000, 0x1000, CRC(2af09b2b) SHA1(4ce87353a941c6527c9426e578ed2a6c7286175e) )
	ROM_LOAD( "05_k08t_hc01.bin", 0x2000, 0x1000, CRC(4362417c) SHA1(680a5c06c938e7cca33880bc18a2b592a4204ec8) )

	ROM_REGION( 0x6000, "tiles", 0 )
	ROM_LOAD( "06_l08t.bin",  0x0000, 0x2000, CRC(51eebd89) SHA1(515128a3971fcb97b60c5b6bdd2b03026aec1921) )
	ROM_LOAD( "07_n08t.bin",  0x2000, 0x2000, CRC(9dd98e9d) SHA1(6db6006a6e20ff7c243d88293ca53681c4703ea5) )
	ROM_LOAD( "08_r08t.bin",  0x4000, 0x2000, CRC(3155ee7d) SHA1(e7897dca4c145f10b7d975b8ef0e4d8aa9354c25) )

	ROM_REGION( 0x6000, "sprites", 0 )
	ROM_LOAD( "16_m07b_hc01.bin", 0x0000, 0x2000, CRC(e33942bf) SHA1(a9fad16f9b83faf1c0948ad15186959ec17eb448) )
	ROM_LOAD( "15_l07b_hc01.bin", 0x2000, 0x2000, CRC(1bb8ec79) SHA1(14c8b6ee9f22491330bbf14356fa4ab3c62cb811) )
	ROM_LOAD( "14_j07b_hc01.bin", 0x4000, 0x2000, CRC(0a9b3106) SHA1(bfd1c430e3e96896ebf4db962f755353a9a57be8) )

	ROM_REGION( 0x1000, "gfx4", 0 )
	ROM_LOAD( "02_p04t.bin",  0x0000, 0x1000, CRC(398d4a02) SHA1(ac18a8219f99ba9178b96c9564de3978e39c59fd) )
ROM_END

ROM_START( bombjackhc02 )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "09_j01b_hc02.bin",  0x0000, 0x2000, CRC(fe674884) SHA1(e7ce4527dd0d84c6430c962648f82319a27c9e5b) )
	ROM_LOAD( "10_l01b.bin",  0x2000, 0x2000, CRC(52a1e5fb) SHA1(e1cdc4b4efbc6c7a1e4fa65019486617f2acba1b) )
	ROM_LOAD( "11_m01b.bin",  0x4000, 0x2000, CRC(b68a062a) SHA1(43bae56494ac0202aaa8f1ed5c1ed1bff775b2b8) )
	ROM_LOAD( "12_n01b_hc02.bin",  0x6000, 0x2000, CRC(ff6627cd) SHA1(918aa40ef0d9b01cd1714c751f69edf6cb0415de) )
	ROM_LOAD( "13.1r_hc02.bin",    0xc000, 0x2000, CRC(e8d84fa1) SHA1(c14e91c7e82fca2fb81d03d531f33a399dc34282) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "01_h03t.bin",  0x0000, 0x2000, CRC(8407917d) SHA1(318face9f7a7ab6c7eeac773995040425e780aaf) )

	ROM_REGION( 0x3000, "chars", 0 )
	ROM_LOAD( "03_e08t_hc02.bin",  0x0000, 0x1000, CRC(dd7e96eb) SHA1(31fde4df2733cc795f5fd64edd090f2f016ab6ac) )
	ROM_LOAD( "04_h08t_hc02.bin",  0x1000, 0x1000, CRC(7c06a2ac) SHA1(71f34dd84cff1b8de7cfe2796b5acad6b85c88b6) )
	ROM_LOAD( "05_k08t_hc02.bin",  0x2000, 0x1000, CRC(d4e5be07) SHA1(386edf85b110215c8bb2005006338bad1c799491) )

	ROM_REGION( 0x6000, "tiles", 0 )
	ROM_LOAD( "06_l08t.bin",  0x0000, 0x2000, CRC(51eebd89) SHA1(515128a3971fcb97b60c5b6bdd2b03026aec1921) )
	ROM_LOAD( "07_n08t.bin",  0x2000, 0x2000, CRC(9dd98e9d) SHA1(6db6006a6e20ff7c243d88293ca53681c4703ea5) )
	ROM_LOAD( "08_r08t.bin",  0x4000, 0x2000, CRC(3155ee7d) SHA1(e7897dca4c145f10b7d975b8ef0e4d8aa9354c25) )

	ROM_REGION( 0x6000, "sprites", 0 )
	ROM_LOAD( "16_m07b_hc02.bin",  0x0000, 0x2000, CRC(36317f2a) SHA1(bdeb62f50fc40562062df8d5571a39526609e8eb) )
	ROM_LOAD( "15_l07b_hc02.bin",  0x2000, 0x2000, CRC(e53e8335) SHA1(a61269d3a75afd38cfc8920a7a21dae0128e2ed8) )
	ROM_LOAD( "14_j07b_hc02.bin",  0x4000, 0x2000, CRC(21c7d648) SHA1(239663b31027d5a49edcafac92b3e8e175b2edf2) )

	ROM_REGION( 0x1000, "gfx4", 0 )
	ROM_LOAD( "02_p04t.bin",  0x0000, 0x1000, CRC(398d4a02) SHA1(ac18a8219f99ba9178b96c9564de3978e39c59fd) )
ROM_END

/*    YEAR  NAME           PARENT     MACHINE    INPUT                       INIT   MONITOR COMPANY     FULLNAME FLAGS */
/* Bombjack Hack */
GAME( 1984, bombjackhc01,   bombjack, bombjack, bombjack, bombjack_state, empty_init, ROT90, "hack",    "Bomb Jack (Greek Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 1984, bombjackhc02,   bombjack, bombjack, bombjack, bombjack_state, empty_init, ROT90, "hack",    "Bomb Jack (Chinese Translation)", MACHINE_SUPPORTS_SAVE )
