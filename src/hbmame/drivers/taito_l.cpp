// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/taito_l.cpp"


ROM_START( sokoban )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "sokoban.ic10",      0x00000, 0x10000, CRC(5959ddb4) SHA1(73f206e19cdfd151426092aa3eea6f72093f360b) )

	ROM_REGION( 0x20000, "gfx1", 0 )
	ROM_LOAD16_BYTE( "sokoban.ic9", 0x00000, 0x10000, CRC(859e1ff4) SHA1(899b71bd0eb9923e88cf7142ed634b36b3e34c6c) )
	ROM_LOAD16_BYTE( "sokoban.ic8", 0x00001, 0x10000, CRC(439a6670) SHA1(79144e3ba5205f5356f28d3b23ef32d3d4fca51c) )

	// came with the zipfile but not used
	ROM_REGION( 0x0200, "plds", 0 )
	ROM_LOAD_OPTIONAL( "gal16v8-b86-04.bin", 0x0000, 0x0117, CRC(bf8c0ea0) SHA1(e0a00f1f6363fb79650202f90a56329990876d49) )
ROM_END

ROM_START( speccies )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "speccies.ic10",     0x00000, 0x55e9, CRC(29e126ac) SHA1(1e3e1379f964e0967d6ea5ef6a84741319b5108f) )

	// came with the zipfile but not used
	ROM_REGION( 0x0800, "mcu", 0 )
	ROM_LOAD_OPTIONAL( "mc68705p3.ic4", 0x0000, 0x0800, CRC(085f68b4) SHA1(2dbc7e2c015220dc59ee1f1208540744e5b9b7cc) )

	ROM_REGION( 0x20000, "gfx1", 0 )
	ROM_LOAD16_BYTE( "speccies.ic9", 0x00000, 0x10000, CRC(11ed1528) SHA1(55f0b63bcbbbe4ad4d1041dca980b55ccb7a7aea) )
	ROM_LOAD16_BYTE( "speccies.ic8", 0x00001, 0x10000, CRC(fcfeb89f) SHA1(fc0e811c72313b371d3a6530b27f9023ff201e31) )

	// came with the zipfile but not used
	ROM_REGION( 0x0200, "plds", 0 )
	ROM_LOAD_OPTIONAL( "gal16v8-b86-04.bin", 0x0000, 0x0117, CRC(bf8c0ea0) SHA1(e0a00f1f6363fb79650202f90a56329990876d49) )
ROM_END

ROM_START( sqij ) // this version works on real hardware
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "sqij.ic10",     0x00000, 0xf000, CRC(793c8b97) SHA1(66b1a6b6c9cd95f06ca5c23843bf61be0474b659) )

	ROM_REGION( 0x20000, "gfx1", 0 )
	ROM_LOAD16_BYTE( "sqij.ic9", 0x00000, 0x10000, CRC(c4de729b) SHA1(58e4c8d8af121dd25eba737cc1917841bc3ec6f5) )
	ROM_LOAD16_BYTE( "sqij.ic8", 0x00001, 0x10000, CRC(978df42d) SHA1(51d7310591c68ec12178b606f0779915f15de8a0) )

	// came with the zipfile but not used
	ROM_REGION( 0x0200, "plds", 0 )
	ROM_LOAD_OPTIONAL( "gal16v8-b86-04.bin", 0x0000, 0x0117, CRC(bf8c0ea0) SHA1(e0a00f1f6363fb79650202f90a56329990876d49) )
ROM_END

GAME( 2015, sokoban,     0,        plotting,  plotting, taitol_1cpu_state, empty_init, ROT0,   "cmonkey", "Sokoban LE", 0 )
GAME( 2015, speccies,    0,        plotting,  plotting, taitol_1cpu_state, empty_init, ROT0,   "Sokurah", "Speccies 2", 0 )
GAME( 2018, sqij,        0,        plotting,  plotting, taitol_1cpu_state, empty_init, ROT0,   "Sokurah", "SQIJ!", 0 )

 /***********
  Evil Stone
**************/

ROM_START( evilstonhack01 )
	ROM_REGION( 0x40000, "maincpu", 0 )
	ROM_LOAD( "c67-03_hack01.ic2", 0x00000, 0x20000, CRC(3fa7e884) SHA1(94716256c199b5f347bbe122d04adbab1a54b1ce) )
	ROM_LOAD( "c67-04_hack01.ic6", 0x20000, 0x20000, CRC(8c43dc76) SHA1(ee395d55ee8e66c86e12f604774799ca7cfe1858) )

	ROM_REGION( 0x80000, "audiocpu", 0 )
	ROM_LOAD( "c67-05.ic22",  0x00000, 0x20000, CRC(94d3a642) SHA1(af20aa5bb60a45c05eb1deba23ba30e6640ca235) )

	ROM_REGION( 0x100000, "gfx1", 0 )
	ROM_LOAD( "c67-01.ic1",  0x00000, 0x80000, CRC(2f351bf4) SHA1(0fb37abf3413cd11baece1c9bbca5a51b0f28938) )
	ROM_LOAD( "c67-02.ic5",  0x80000, 0x80000, CRC(eb4f895c) SHA1(2c902572fe5a5d4442e4dd29e8a85cb40c384140) )
ROM_END


 /***********
 Kuri Kinton
**************/

ROM_START( kurikinthack01 )
	ROM_REGION( 0x40000, "maincpu", 0 )
	ROM_LOAD( "b42-05_hack01.ic2",  0x00000, 0x20000, CRC(b0656c45) SHA1(777a9206ac8bc3a519000c35cbab58dafec461f5) )
	ROM_LOAD( "b42-06_hack01.ic6",  0x20000, 0x20000, CRC(677547d9) SHA1(56c2befe20182d5241580fae3787abf506df2b6f) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "b42-07.ic22", 0x00000, 0x10000, CRC(0f2719c0) SHA1(f870335a75f236f0059522f9a577dee7ca3acb2f) )

	ROM_REGION( 0x100000, "gfx1", 0 )
	ROM_LOAD( "b42-01_hack01.ic1",  0x00000, 0x80000, CRC(592c6d20) SHA1(4c5d58e23855a905064049a7758706778a81f129) )
	ROM_LOAD( "b42-02_hack01.ic5",  0x80000, 0x80000, CRC(cd5fc143) SHA1(5a5a6e674a47786ed9c843cefacf307429df9933) )
ROM_END

 /********
 Plotting
***********/

ROM_START( plottinghack01 )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "plot01_hack01.ic10", 0x00000, 0x10000, CRC(134e39a3) SHA1(c3ec3ed35b3fb39d780369a4c50beb6e4ccaaff2) )

	ROM_REGION( 0x20000, "gfx1", 0 )
	ROM_LOAD16_BYTE( "b96-02_hack01.ic9", 0x00000, 0x10000, CRC(78b05c85) SHA1(384626d0ef246702cdf6869bedee42fa18c2f438) )
	ROM_LOAD16_BYTE( "b96-03_hack01.ic8", 0x00001, 0x10000, CRC(ef56d689) SHA1(16391444b2e50accfd81e5bf35bf2b5f74e3d138) )

	ROM_REGION( 0x0200, "plds", 0 )
	ROM_LOAD( "gal16v8-b86-04.bin", 0x0000, 0x0117, CRC(bf8c0ea0) SHA1(e0a00f1f6363fb79650202f90a56329990876d49) ) 
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Evil Stone
GAME( 2007, evilstonhack01,  evilston, evilston,  evilston, taitol_2cpu_state, empty_init, ROT270, "Arkatrad", "Evil Stone (Translation French)", MACHINE_IMPERFECT_SOUND )
// Kuri Kinton
GAME( 1988, kurikinthack01,  kurikint, kurikint,  kurikintj, taitol_2cpu_state, empty_init, ROT0,   "hack", "Kuri Kinton (Translation Chinese)", 0 )
// Plotting
GAME( 1989, plottinghack01, plotting, plotting,  plotting,  taitol_1cpu_state, init_plottinga, ROT0,   "hack", "Plotting (Translation Chinese)", 0 )

