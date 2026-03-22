// NeoEX
// copyright-holders:Gaston90
#include "../mame/drivers/pacland.cpp"

/******
  Hack
********/

ROM_START( paclandhc01 ) //mariopac
	ROM_REGION( 0x20000, "maincpu", 0 )
	ROM_LOAD( "pl5_01b.8b",     0x08000, 0x4000, CRC(b0ea7631) SHA1(424afa6f397310c7af39c9e8b580aa9ccd42c39c) )
	ROM_LOAD( "pl5_02.8d",      0x0C000, 0x4000, CRC(d903e84e) SHA1(25338726227bfbec65847879aac5228a6a307db4) )
	ROM_LOAD( "pl1_3.8e",       0x10000, 0x4000, CRC(aa9fa739) SHA1(7b1f7857eb5f68e166b1f8988c82051aaf05df48) )
	ROM_LOAD( "pl1_4.8f",       0x14000, 0x4000, CRC(2b895a90) SHA1(820f8873c6a5a736089406d0f03d491dfb82d00d) )
	ROM_LOAD( "pl1_5.8h",       0x18000, 0x4000, CRC(7af66200) SHA1(f44161ded1633e9801b7a9cd84d481e53823f5d9) )
	ROM_LOAD( "pl3_6.8j",       0x1c000, 0x4000, CRC(2ffe3319) SHA1(c2540321cd5a1fe29ecb077abdf8f997893192e9) )

	ROM_REGION( 0x10000, "mcu", 0 )
	ROM_LOAD( "pl1_7.3e",       0x8000, 0x2000, CRC(8c5becae) SHA1(14d67136395c4c64472980a69648ce2d479ae67f) )
	ROM_LOAD( "cus60-60a1_hc01.mcu", 0xf000, 0x1000, CRC(6ef08fb3) SHA1(4842590d60035a0059b0899eb2d5f58ae72c2529) )

	ROM_REGION( 0x02000, "fg_chars", 0 )
	ROM_LOAD( "pl2_12_hc01.6n", 0x00000, 0x2000, CRC(abba0923) SHA1(2286b0d162e5502160895940d0c9637abe5d6d2f) )

	ROM_REGION( 0x02000, "bg_chars", 0 )
	ROM_LOAD( "pl4_13.6t",      0x00000, 0x2000, CRC(3ae582fd) SHA1(696b2cfadb6b071de8e43d20cd65b37713ca3b30) )

	ROM_REGION( 0x10000, "sprites", 0 )
	ROM_LOAD( "pl1-9_hc01.6f",    0x00000, 0x4000, CRC(98439154) SHA1(7bad68705ae3d9fa6e03ad7dc9421cf6063e1669) )
	ROM_LOAD( "pl1-8_hc01.6e",    0x04000, 0x4000, CRC(d0c1f225) SHA1(bcaa68922e49b7257959471641d3c91e505a8d53) )
	ROM_LOAD( "pl1-10_hc01.7e",   0x08000, 0x4000, CRC(6005b277) SHA1(acacffe38edfc2d325dc286d182253ee5bb62489) )
	ROM_LOAD( "pl1-11_hc01.7f",   0x0c000, 0x4000, CRC(eeed9880) SHA1(e037dd299895db22a88c1d32dda157833b1e8a09) )

	ROM_REGION( 0x1400, "proms", 0 )
	ROM_LOAD( "pl1-2.1t",       0x0000, 0x0400, CRC(472885de) SHA1(8d552c90b8d5bc6ad6c60934c00f4303cd180ce7) )
	ROM_LOAD( "pl1-1.1r",       0x0400, 0x0400, CRC(a78ebdaf) SHA1(8ea215701eb5e1a2a329ef92c19fc69b18fc28c7) )
	ROM_LOAD( "pl1-5.5t",       0x0800, 0x0400, CRC(4b7ee712) SHA1(dd0ec4c632d8b160f7b54d8f18fcf4ef1508d832) )
	ROM_LOAD( "pl1-4.4n",       0x0c00, 0x0400, CRC(3a7be418) SHA1(475cdc68205e3acce83fe79b00b74c6a7e28dde4) )
	ROM_LOAD( "pl1-3.6l",       0x1000, 0x0400, CRC(80558da8) SHA1(7e1483467817295f36d1e2bdb32934c4f2617d52) )
ROM_END

/*    YEAR  NAME         PARENT    MACHINE  INPUT                      INIT   MONITOR   COMPANY      FULLNAME FLAGS */
/* Pacland Hack */
GAME( 2001, paclandhc01, pacland, pacland, pacland, pacland_state, empty_init, ROT0, "Marks Hacks", "Mario in Pac-Land", MACHINE_SUPPORTS_SAVE )

