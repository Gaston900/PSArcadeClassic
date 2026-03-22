// NeoEX
// copyright-holders:Gaston90
#include "../mame/drivers/nemesis.cpp"

/******
  Hack
********/

ROM_START( salamandhc01 ) //spclone
	ROM_REGION( 0x80000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "587-d02_hc01.18b",  0x00000, 0x10000, CRC(14c19a46) SHA1(1a65a98c390693949247f4e568fe71cff82d59b4) )
	ROM_LOAD16_BYTE( "587-d05_hc01.18c",  0x00001, 0x10000, CRC(fdafc246) SHA1(1641411023f85afe82af749b15d067efc5859f4e) )
	ROM_LOAD16_BYTE( "587-c03.17b",  0x40000, 0x20000, CRC(e5caf6e6) SHA1(f5df4fbc43cfa6e2866558c99dd95ba8dc89dc7a) )
	ROM_LOAD16_BYTE( "587-c06.17c",  0x40001, 0x20000, CRC(c2f567ea) SHA1(0c38fea53f3d4a9ae0deada5669deca4be8c9fd3) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "587-d09_hc01.11j",   0x00000, 0x08000, CRC(bf83b182) SHA1(e702eddffea3bad8944bfab03d53c6e277bca866) )

	ROM_REGION( 0x04000, "vlm", 0 )
	ROM_LOAD( "587-d08.8g",    0x00000, 0x04000, CRC(f9ac6b82) SHA1(3370fc3a7f82e922e19d54afb3bca7b07fa4aa9a) )

	ROM_REGION( 0x20000, "k007232", 0 )
	ROM_LOAD( "587-c01.10a",   0x00000, 0x20000, CRC(09fe0632) SHA1(4c3b29c623d70bbe8a938a0beb4638912c46fb6a) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
/* Nemesis Hack */
GAME( 2007, salamandhc01,  salamand, salamand, lifefrcj, nemesis_state, empty_init, ROT0, "Konami", "Salamander (version YY 0.7.3) ", MACHINE_SUPPORTS_SAVE )
