// NeoEX
// copyright-holders:Gaston90
#include "../mame/drivers/gottlieb.cpp"

/******
  Hack
********/

ROM_START( qberthc01 ) //pbert
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "qb-rom2.bin",  0xa000, 0x2000, CRC(fe434526) SHA1(4cfc5d52dd6c82163e035af82d6112c0c93a3797) )
	ROM_LOAD( "qb-rom1.bin",  0xc000, 0x2000, CRC(55635447) SHA1(ca6acdef1c9e06b33efe1f0a2df2dfb03723cfbe) )
	ROM_LOAD( "qb-rom0.bin",  0xe000, 0x2000, CRC(8e318641) SHA1(7f8f66d1e6a7905e93cce07fc92e8801370b7194) )

	ROM_REGION( 0x10000, "r1sound:audiocpu", 0 )
	ROM_LOAD( "qb-snd1.bin",  0x7000, 0x0800, CRC(15787c07) SHA1(8b7d03fbf2ebaa71b3a7e2f636a0d1bb9b796e43) )
	ROM_LOAD( "qb-snd2.bin",  0x7800, 0x0800, CRC(58437508) SHA1(09d8053e7e99679b602dcda230d64db7fe6cb7f5) )

	ROM_REGION( 0x2000, "bgtiles", 0 )
	ROM_LOAD( "qb-bg0_hc01.bin",   0x0000, 0x1000, CRC(14e193e9) SHA1(5d67b3da848d4a90a4f9bf7f6145ce1aa33188f7) )
	ROM_LOAD( "qb-bg1_hc01.bin",   0x1000, 0x1000, CRC(a91180f9) SHA1(c8a3ceae19afe9a0ad1e05bed99585e6bacbc09b) )

	ROM_REGION( 0x8000, "sprites", 0 )
	ROM_LOAD( "qb-fg3_hc01.bin",   0x0000, 0x2000, CRC(26def34c) SHA1(b36dd87e4c36d201aaec0c283e5f3d1ad4056d5d) )
	ROM_LOAD( "qb-fg2_hc01.bin",   0x2000, 0x2000, CRC(cf3309ca) SHA1(5be9a28b3681990729f0582f9d2c3dd0314bdd15) )
	ROM_LOAD( "qb-fg1_hc01.bin",   0x4000, 0x2000, CRC(a5f3a203) SHA1(4d7d45e5ba87acd8c44421f2c7fb2129a1866f03) )
	ROM_LOAD( "qb-fg0_hc01.bin",   0x6000, 0x2000, CRC(495d90e9) SHA1(d4d28c30901eb09da8933c03b2178152f0fc7b84) )
ROM_END

ROM_START( qberthc02 ) //vbert
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "qb-rom2.bin",  0xa000, 0x2000, CRC(fe434526) SHA1(4cfc5d52dd6c82163e035af82d6112c0c93a3797) )
	ROM_LOAD( "qb-rom1.bin",  0xc000, 0x2000, CRC(55635447) SHA1(ca6acdef1c9e06b33efe1f0a2df2dfb03723cfbe) )
	ROM_LOAD( "qb-rom0.bin",  0xe000, 0x2000, CRC(8e318641) SHA1(7f8f66d1e6a7905e93cce07fc92e8801370b7194) )

	ROM_REGION( 0x10000, "r1sound:audiocpu", 0 )
	ROM_LOAD( "qb-snd1.bin",  0x7000, 0x0800, CRC(15787c07) SHA1(8b7d03fbf2ebaa71b3a7e2f636a0d1bb9b796e43) )
	ROM_LOAD( "qb-snd2.bin",  0x7800, 0x0800, CRC(58437508) SHA1(09d8053e7e99679b602dcda230d64db7fe6cb7f5) )

	ROM_REGION( 0x2000, "bgtiles", 0 )
	ROM_LOAD( "qb-bg0_hc02.bin",   0x0000, 0x1000, CRC(8963b939) SHA1(1416f56938163b4cdc212758eb2c3f6b773c7e32) )
	ROM_LOAD( "qb-bg1_hc02.bin",   0x1000, 0x1000, CRC(96033c96) SHA1(0a5780377bfd3baeeb2d899aa230e503539f7c92) )

	ROM_REGION( 0x8000, "sprites", 0 )
	ROM_LOAD( "qb-fg3_hc02.bin",   0x0000, 0x2000, CRC(8cb4bdb4) SHA1(7b9b626b93daa4d2639a1e87ace61b1d254af96c) )
	ROM_LOAD( "qb-fg2_hc02.bin",   0x2000, 0x2000, CRC(79883cc3) SHA1(01cfca389021747e2d750fc8bb251abb2d5fe7a8) )
	ROM_LOAD( "qb-fg1_hc02.bin",   0x4000, 0x2000, CRC(b0fe9bd5) SHA1(be2990904efff19adbe18eb674727214ffae9ad3) )
	ROM_LOAD( "qb-fg0_hc02.bin",   0x6000, 0x2000, CRC(4c3db270) SHA1(212f1c353511fb4166a7ad0135dd295a2a16af8d) )
ROM_END

/*    YEAR  NAME          PARENT    MACHINE   INPUT                     INIT     MONITOR     COMPANY    FULLNAME FLAGS */
/* Gottlieb Hack */
GAME( 2003, qberthc01,    qbert,   qbert,    qbert, gottlieb_state, init_qbert, ROT270,      "hack",    "P*bert", MACHINE_SUPPORTS_SAVE )
GAME( 2003, qberthc02,    qbert,   qbert,    qbert, gottlieb_state, init_qbert, ROT270,      "hack",    "V*bert", MACHINE_SUPPORTS_SAVE )
