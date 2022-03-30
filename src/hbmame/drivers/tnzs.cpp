// Proyecto Shadows Arcade Classic+
// copyright-holders:Gaston90
#include "../mame/drivers/tnzs.cpp"

 /**********
 Insector X
************/

ROM_START( insectxhack01 )
	ROM_REGION( 0x20000, "maincpu", 0 )
	ROM_LOAD( "b97__03_hack01.u32", 0x00000, 0x20000, CRC(2f478739) SHA1(b073170bbf14a974d7ab28d8c078c4e8823f259f) )

	ROM_REGION( 0x10000, "sub", 0 )
	ROM_LOAD( "b97__07.u38", 0x00000, 0x10000, CRC(324b28c9) SHA1(db77a4ac60196d0f0f35dbc5c951ec29d6392463) )

	ROM_REGION( 0x100000, "gfx1", 0 )
	ROM_LOAD( "b97__01_hack01.u1", 0x00000, 0x80000, CRC(4b6ec740) SHA1(f6065bdc73e9997e24e19a664eb161cad6948c95) )
	ROM_LOAD( "b97__02_hack01.u2", 0x80000, 0x80000, CRC(78e9ecc4) SHA1(a6921d434d0c3dc6ac6ee4aad7ac8b1d901d0daf) )
ROM_END

/*    YEAR  NAME          PARENT           MACHINE   INPUT     INIT                 MONITOR COMPANY       FULLNAME FLAGS */
// Insector X
GAME( 1989, insectxhack01,   insectx,    insectx,  insectx,  insectx_state,  empty_init, ROT0,   "hack", "Insector X (Translation Chinese)", MACHINE_SUPPORTS_SAVE )
