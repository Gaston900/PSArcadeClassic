// license:GPL_2.0
// copyright-holders:Robbbert
#include "../mame/drivers/midyunit.cpp"

/******
  Hack
********/

ROM_START( y_test )
	ROM_REGION( 0x90000, "cvsd:cpu", 0 )    /* sound CPU */
	ROM_LOAD ( "sl2_smash_tv_sound_rom_u4.u4",   0x10000, 0x10000, CRC(29d3f6c8) SHA1(8a90cdff54f59ddb7dba521504d880515a59df08) )
	ROM_RELOAD(                                  0x20000, 0x10000 )
	ROM_LOAD ( "sl2_smash_tv_sound_rom_u19.u19", 0x30000, 0x10000, CRC(ac5a402a) SHA1(c476018062126dc3936caa2c328de490737165ec) )
	ROM_RELOAD(                                  0x40000, 0x10000 )
	ROM_LOAD ( "sl2_smash_tv_sound_rom_u20.u20", 0x50000, 0x10000, CRC(875c66d9) SHA1(51cdad62ec57e69bba6fcf14e59841ec628dec11) )
	ROM_RELOAD(                                  0x60000, 0x10000 )

	ROM_REGION16_LE( 0x100000, "user1", 0 ) /* 34010 code */
	ROM_LOAD16_BYTE( "y_test.u105", 0xc0000, 0x20000, CRC(bd29a7d1) SHA1(211905c16874a23840652555757b9d2f2712facb) )
	ROM_LOAD16_BYTE( "y_test.u89",   0xc0001, 0x20000, CRC(6db6e0cd) SHA1(3f4c7cd48d6606c03195ed9209f7cedbc9efd42d) )

	ROM_REGION( 0x800000, "gfx1", 0 )
	ROM_LOAD ( "la1_smash_tv_game_rom_u111.u111",  0x000000, 0x20000, CRC(72f0ba84) SHA1(2e925b3cdd3c8e14046b3948d82f0f3cde3c22c5) )
	ROM_LOAD ( "la1_smash_tv_game_rom_u112.u112",  0x020000, 0x20000, CRC(436f0283) SHA1(ec33a8942c0fc326db885e08dad9346ec5a63360) )
	ROM_LOAD ( "la1_smash_tv_game_rom_u113.u113",  0x040000, 0x20000, CRC(4a4b8110) SHA1(9f1881d1d2682764ab85aebd685d97eb8b4afe46) )

	ROM_LOAD ( "la1_smash_tv_game_rom_u95.u95",    0x200000, 0x20000, CRC(e864a44b) SHA1(40eb8e11a183f4f82dc8decb36aaeded9cd1bc26) )
	ROM_LOAD ( "la1_smash_tv_game_rom_u96.u96",    0x220000, 0x20000, CRC(15555ea7) SHA1(4fefc059736ca424dc05a08cb55b9acf9e31228b) )
	ROM_LOAD ( "la1_smash_tv_game_rom_u97.u97",    0x240000, 0x20000, CRC(ccac9d9e) SHA1(a43d70d1a0bbd377f0fc539c2e8b725f7079f463) )

	ROM_LOAD ( "la1_smash_tv_game_rom_u106.u106",  0x400000, 0x20000, CRC(5c718361) SHA1(6178b1d53411f24d5a5a01559727e300cd27d587) )
	ROM_LOAD ( "la1_smash_tv_game_rom_u107.u107",  0x420000, 0x20000, CRC(0fba1e36) SHA1(17038cf35a72678bba149a632f1ad1b80cc3a38c) )
	ROM_LOAD ( "la1_smash_tv_game_rom_u108.u108",  0x440000, 0x20000, CRC(cb0a092f) SHA1(33cbb87b4be1eadb1f3624ef5e218e65109fa3eb) )
ROM_END

/*    YEAR  NAME              PARENT            MACHINE            INPUT                              INIT           MONITOR COMPANY       FULLNAME FLAGS */
/* Midyunit Hack */
GAME( 1990, y_test,   smashtv,  yunit_cvsd_6bit_slow,    smashtv,  midyunit_state, init_smashtv,  ROT0, "Williams", "Midway Y-unit Test Rom v1.40 (HB)", MACHINE_SUPPORTS_SAVE )

