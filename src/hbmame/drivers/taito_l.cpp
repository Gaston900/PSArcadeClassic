// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/taito_l.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( evilstonhc01 )
	ROM_REGION( 0x40000, "maincpu", 0 )
	ROM_LOAD( "c67-03_hc01.ic2", 0x00000, 0x20000, CRC(3fa7e884) SHA1(94716256c199b5f347bbe122d04adbab1a54b1ce) )
	ROM_LOAD( "c67-04_hc01.ic6", 0x20000, 0x20000, CRC(8c43dc76) SHA1(ee395d55ee8e66c86e12f604774799ca7cfe1858) )

	ROM_REGION( 0x80000, "audiocpu", 0 )
	ROM_LOAD( "c67-05.ic22",  0x00000, 0x20000, CRC(94d3a642) SHA1(af20aa5bb60a45c05eb1deba23ba30e6640ca235) )

	ROM_REGION( 0x100000, "maincpu:gfx", 0 )
	ROM_LOAD( "c67-01.ic1",  0x00000, 0x80000, CRC(2f351bf4) SHA1(0fb37abf3413cd11baece1c9bbca5a51b0f28938) )
	ROM_LOAD( "c67-02.ic5",  0x80000, 0x80000, CRC(eb4f895c) SHA1(2c902572fe5a5d4442e4dd29e8a85cb40c384140) )
ROM_END

ROM_START( kurikinthc01 )
	ROM_REGION( 0x40000, "maincpu", 0 )
	ROM_LOAD( "b42-05_hc01.ic2",  0x00000, 0x20000, CRC(b0656c45) SHA1(777a9206ac8bc3a519000c35cbab58dafec461f5) )
	ROM_LOAD( "b42-06_hc01.ic6",  0x20000, 0x20000, CRC(677547d9) SHA1(56c2befe20182d5241580fae3787abf506df2b6f) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "b42-07.ic22", 0x00000, 0x10000, CRC(0f2719c0) SHA1(f870335a75f236f0059522f9a577dee7ca3acb2f) )

	ROM_REGION( 0x100000, "maincpu:gfx", 0 )
	ROM_LOAD( "b42-01_hc01.ic1",  0x00000, 0x80000, CRC(592c6d20) SHA1(4c5d58e23855a905064049a7758706778a81f129) )
	ROM_LOAD( "b42-02_hc01.ic5",  0x80000, 0x80000, CRC(cd5fc143) SHA1(5a5a6e674a47786ed9c843cefacf307429df9933) )

	ROM_REGION( 0x022e, "plds", 0 )
	ROM_LOAD( "gal16v8-b42-03.ic4.bin",  0x0000, 0x0117, CRC(f7150d37) SHA1(10f9190b89c802e0722fd6ba0f17ba97d463f434) )  /* derived, but verified, PAL16L8 Stamped B42-03 */
	ROM_LOAD( "gal16v8-b42-04.ic21.bin", 0x0117, 0x0117, CRC(b57b806c) SHA1(04cbb008256b7317ebf366327dfd38ead8eaf94e) )  /* derived, but verified, PAL16L8 Stamped B42-04 */
ROM_END

ROM_START( plottinghc01 )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "plot01_hc01.ic10", 0x00000, 0x10000, CRC(134e39a3) SHA1(c3ec3ed35b3fb39d780369a4c50beb6e4ccaaff2) )

	ROM_REGION( 0x20000, "maincpu:gfx", 0 )
	ROM_LOAD16_BYTE( "b96-02_hc01.ic9", 0x00000, 0x10000, CRC(78b05c85) SHA1(384626d0ef246702cdf6869bedee42fa18c2f438) )
	ROM_LOAD16_BYTE( "b96-03_hc01.ic8", 0x00001, 0x10000, CRC(ef56d689) SHA1(16391444b2e50accfd81e5bf35bf2b5f74e3d138) )

	ROM_REGION( 0x0200, "plds", 0 )
	ROM_LOAD( "gal16v8-b86-04.bin", 0x0000, 0x0117, CRC(bf8c0ea0) SHA1(e0a00f1f6363fb79650202f90a56329990876d49) ) 
ROM_END

/*    YEAR  NAME            PARENT    MACHINE      INPUT                        INIT          MONITOR  COMPANY     FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2007, evilstonhc01,  evilston, evilston,  evilston,  taitol_2cpu_state, empty_init,     ROT270, "Arkatrad", "Evil Stone (Translation French)", MACHINE_IMPERFECT_SOUND )
GAME( 1988, kurikinthc01,  kurikint, kurikint,  kurikintj, taitol_2cpu_state, empty_init,     ROT0,   "hack",     "Kuri Kinton (Translation Chinese)", 0 )
GAME( 1989, plottinghc01,  plotting, plotting,  plotting,  taitol_1cpu_state, init_plottinga, ROT0,   "hack",     "Plotting (Translation Chinese)", 0 )
