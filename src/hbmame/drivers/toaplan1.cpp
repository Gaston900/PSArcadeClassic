// license:BSD-3-Clause
// copyright-holders:Gaston90
#include "../mame/drivers/toaplan1.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( zerowinghc01 )
	ROM_REGION( 0x080000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "o15-11ii_hc01.bin",  0x000000, 0x08000, CRC(15093e1c) SHA1(ee67110e5170efa7df66ba47b1ba552377fa2cbb) )
	ROM_LOAD16_BYTE( "o15-12ii_hc01.bin",  0x000001, 0x08000, CRC(5ca8448a) SHA1(35d597e29185335ff28538b8cbdffcf0c61425ab) )
	ROM_LOAD16_BYTE( "o15-09.rom",    0x040000, 0x20000, CRC(13764e95) SHA1(61da49b73ba81edd951e96e9ce6673c1c3bd65f2) )
	ROM_LOAD16_BYTE( "o15-10.rom",    0x040001, 0x20000, CRC(351ba71a) SHA1(937331549140506711b08252497cc0f2efa58268) )

	ROM_REGION( 0x8000, "audiocpu", 0 )
	ROM_LOAD( "o15-13.rom",  0x0000, 0x8000, CRC(e7b72383) SHA1(ea1f6f33a86d14d58bd396fd46081462f00177d5) )

	ROM_REGION( 0x80000, "gfx1", 0 )
	ROM_LOAD16_BYTE( "o15-05.rom",  0x00000, 0x20000, CRC(4e5dd246) SHA1(5366b4a6f3c900a4f57a6583b7399163a06f42d7) )
	ROM_LOAD16_BYTE( "o15-06.rom",  0x00001, 0x20000, CRC(c8c6d428) SHA1(76ee5bcb8f10fe201fc5c32697beee3de9d8b751) )
	ROM_LOAD16_BYTE( "o15-07.rom",  0x40000, 0x20000, CRC(efc40e99) SHA1(a04fad4197a7fb4787cd9bebf43e1d9b02b2f61b) )
	ROM_LOAD16_BYTE( "o15-08.rom",  0x40001, 0x20000, CRC(1b019eab) SHA1(c9569ca85696825142acc5cde9ac829e82b1ca1b) )

	ROM_REGION( 0x80000, "gfx2", 0 )
	ROM_LOAD16_BYTE( "o15-03.rom",  0x00000, 0x20000, CRC(7f245fd3) SHA1(efbcb3663d4accc4f8128a8fee5475bc109bc17a) )
	ROM_LOAD16_BYTE( "o15-04.rom",  0x00001, 0x20000, CRC(0b1a1289) SHA1(ce6c06342392d11952873e3b1d6aea8dc02a551c) )
	ROM_LOAD16_BYTE( "o15-01.rom",  0x40000, 0x20000, CRC(70570e43) SHA1(acc9baec71b0930cb2f193677e0663efa5d5551d) )
	ROM_LOAD16_BYTE( "o15-02.rom",  0x40001, 0x20000, CRC(724b487f) SHA1(06af31520866eea69aebbd5d428f80e882289a15) )

	ROM_REGION( 0x40, "proms", 0 )
	ROM_LOAD( "tp015_14.bpr",  0x00, 0x20, CRC(bc88cced) SHA1(5055362710c0f58823c05fb4c0e0eec638b91e3d) )
	ROM_LOAD( "tp015_15.bpr",  0x20, 0x20, CRC(a1e17492) SHA1(9ddec4c97f2d541f69f3c32c47aaa21fd9699ae2) )
ROM_END

/*    YEAR  NAME              PARENT            MACHINE          INPUT                           INIT  MONITOR COMPANY        FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2022, zerowinghc01,     zerowing,         zerowing,      zerowing2,   toaplan1_state,  empty_init, ROT0, "hack",        "Zero Wing (Fighter Delta 2022-05-11)", 0 )
