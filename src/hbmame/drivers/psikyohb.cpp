// Proyecto Shadows Arcade Classic+
// copyright-holders:Gaston90
#include "../mame/drivers/psikyo.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( tengaihc01 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "5-u40_hc01.bin", 0x000000, 0x080000, CRC(aae15ef1) SHA1(e5d056eb0ef26a697544cbeacb5f993217fdbd0a) )
    ROM_LOAD32_WORD_SWAP( "4-u41_hc01.bin", 0x000002, 0x080000, CRC(e8863874) SHA1(f6ac25170516658c368fb86b2b653e3356b42f19) )

	ROM_REGION( 0x020000, "audiocpu", 0 )
	ROM_LOAD( "1-u63.bin", 0x00000, 0x20000, CRC(2025e387) SHA1(334b0eb3b416d46ccaadff3eee6f1abba63285fb) )

	ROM_REGION( 0x001000, "mcu", 0 )
	ROM_LOAD( "4-u59.bin", 0x00000, 0x01000, NO_DUMP )

	ROM_REGION( 0x600000, "gfx1", 0 )
	ROM_LOAD( "u20.bin",  0x000000, 0x200000, CRC(ed42ef73) SHA1(74693fcc83a2654ddb18fd513d528033863d6116) )
	ROM_LOAD( "u22.bin",  0x200000, 0x200000, CRC(8d21caee) SHA1(2a68af8b2be2158dcb152c434e91a75871478d41) )
	ROM_LOAD( "u21.bin",  0x400000, 0x200000, CRC(efe34eed) SHA1(7891495b443a5acc7b2f17fe694584f6cb0afacc) )

	ROM_REGION( 0x400000, "gfx2", 0 )
	ROM_LOAD( "u34.bin",  0x000000, 0x400000, CRC(2a2e2eeb) SHA1(f1d99353c0affc5c908985e6f2a5724e5223cccc) )

	ROM_REGION( 0x400000, "ymf", 0 )
	ROM_LOAD( "u61.bin",  0x000000, 0x200000, CRC(a63633c5) SHA1(89e75a40518926ebcc7d88dea86c01ba0bb496e5) )
	ROM_LOAD( "u62.bin",  0x200000, 0x200000, CRC(3ad0c357) SHA1(35f78cfa2eafa93ab96b24e336f569ee84af06b6) )

	ROM_REGION16_LE( 0x040000, "spritelut", 0 )
	ROM_LOAD( "u1.bin",  0x000000, 0x040000, CRC(681d7d55) SHA1(b0b28471440d747adbc4d22d1918f89f6ede1615) )
ROM_END

/********************
  Korean Translation
***********************/

ROM_START( gunbirdkp )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "4k.u46", 0x000000, 0x40000, CRC(8066b6f3) SHA1(6ea07cf1cb058da838524ae7f83f6ed24836848d) )
	ROM_LOAD32_WORD_SWAP( "5k.u39", 0x000002, 0x40000, CRC(0a425ce0) SHA1(9b8a5f825c45b8919e43b83cc47056925bed6499) )

	ROM_REGION( 0x020000, "audiocpu", 0 )
	ROM_LOAD( "3.u71",     0x00000, 0x20000, CRC(2168e4ba) SHA1(ca7ad6acb5f806ce2528e7b52c19e8cceecb8543) )

	ROM_REGION( 0x700000, "gfx1", 0 )
	ROM_LOAD16_WORD_SWAP( "u14k.u14",  0x000000, 0x200000, CRC(e143090a) SHA1(545ba6fdfd9b94efeb798b06ba07e8a5b27f8608) )
	ROM_LOAD16_WORD_SWAP( "u24.bin",   0x200000, 0x200000, CRC(5e3ffc9d) SHA1(c284eb9ef56c8e6261fe11f91a10c5c5a56c9803) )
	ROM_LOAD16_WORD_SWAP( "u15k.u15",  0x400000, 0x200000, CRC(e5f6bfb6) SHA1(87825cb74f139aa9a6affc4b236910968a410de7) )
	ROM_LOAD16_WORD_SWAP( "u25k.u25",  0x600000, 0x100000, CRC(cf571ff8) SHA1(0310bc422fde4ab7c4a760ed6dc0606f10ed009a) )

	ROM_REGION( 0x200000, "gfx2", 0 )
	ROM_LOAD16_WORD_SWAP( "u33.bin",  0x000000, 0x200000, CRC(54494e6b) SHA1(f5d090d2d34d908b56b53a246def194929eba990) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "u56.bin",  0x000000, 0x100000, CRC(9e07104d) SHA1(3bc54cb755bb3194197706965b532d62b48c4d12) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "u64.bin",  0x000000, 0x080000, CRC(e187ed4f) SHA1(05060723d89b1d05714447a14b5f5888ff3c2306) )

	ROM_REGION16_LE( 0x040000, "spritelut", 0 )
	ROM_LOAD( "u3.bin",  0x000000, 0x040000, CRC(0905aeb2) SHA1(8cca09f7dfe3f804e77515f7b1b1bdbeb7bb3d80) )
ROM_END

ROM_START( tengaik )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "5k.u40", 0x000000, 0x80000, CRC(279f7493) SHA1(bb39c50258fe30e4cc4b3da1f2acc05c362f8ddf) )
	ROM_LOAD32_WORD_SWAP( "4k.u41", 0x000002, 0x80000, CRC(59fe486e) SHA1(a6dfbe2e19926c9c1491a5aba480018732c57293) )

	ROM_REGION( 0x020000, "audiocpu", 0 )
	ROM_LOAD( "1-u63.bin", 0x00000, 0x20000, CRC(2025e387) SHA1(334b0eb3b416d46ccaadff3eee6f1abba63285fb) )

	ROM_REGION( 0x001000, "mcu", 0 )
	ROM_LOAD( "4-u59.bin", 0x00000, 0x01000, NO_DUMP )

	ROM_REGION( 0x600000, "gfx1", 0 )
	ROM_LOAD( "s03.u20",  0x000000, 0x200000, CRC(0bdc0c2d) SHA1(78f62237ef64c94e549fdf7f87f448a9cec02e67) )
	ROM_LOAD( "u22.bin",  0x200000, 0x200000, CRC(8d21caee) SHA1(2a68af8b2be2158dcb152c434e91a75871478d41) )
	ROM_LOAD( "s03.u21",  0x400000, 0x200000, CRC(435669ca) SHA1(4eaf8531e750d5d4bea6b3f4eaa39f7267fe7206) )

	ROM_REGION( 0x400000, "gfx2", 0 )
	ROM_LOAD( "s03.u34",  0x000000, 0x400000, CRC(801fc802) SHA1(023c2d6515a91188791d923046365d6453c62808) )

	ROM_REGION( 0x400000, "ymf", 0 )
	ROM_LOAD( "u61.bin",  0x000000, 0x200000, CRC(a63633c5) SHA1(89e75a40518926ebcc7d88dea86c01ba0bb496e5) )
	ROM_LOAD( "u62.bin",  0x200000, 0x200000, CRC(3ad0c357) SHA1(35f78cfa2eafa93ab96b24e336f569ee84af06b6) )

	ROM_REGION16_LE( 0x040000, "spritelut", 0 )
	ROM_LOAD( "u1.bin",  0x000000, 0x040000, CRC(681d7d55) SHA1(b0b28471440d747adbc4d22d1918f89f6ede1615) )
ROM_END

/*    YEAR    NAME         PARENT   MACHINE    INPUT                      INIT      MONITOR   COMPANY       FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2009, tengaihc01,    tengai,   s1945,    tengai,   psikyo_state, init_tengai,   ROT0,   "hack",       "Tengai (Ex Super Version 2009-10-31)", MACHINE_SUPPORTS_SAVE )

/* Korean Translation */
GAME( 1994, gunbirdkp,  gunbird,  gunbird,  gunbirdj, psikyo_state, init_gunbird,  ROT270, "hack",          "Gunbird (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, tengaik,    tengai,   s1945,    tengaij,  psikyo_state, init_tengai,   ROT0,   "hack",          "Tengai (Korean Translation)", MACHINE_SUPPORTS_SAVE )
