// license:GPL_2.0
// copyright-holders:Robbbert
#include "../mame/drivers/exedexes.cpp"

/******
  Hack
********/

ROM_START( exedexeshc01 )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "11m_ee04_hc01.bin", 0x0000, 0x4000, CRC(e1b7ee12) SHA1(d5a227aacac06e718e1995fc3747d4ee5228b88f) )
	ROM_LOAD( "10m_ee03_hc01.bin", 0x4000, 0x4000, CRC(ceef62f6) SHA1(4e1831348b30024a1dc74fbb146f76afe2da984b) )
	ROM_LOAD( "09m_ee02_hc01.bin", 0x8000, 0x4000, CRC(9a93c1c2) SHA1(761952cad602d4cb76c23911da4f863564b5add1) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "11e_ee01.bin", 0x0000, 0x4000, CRC(73cdf3b2) SHA1(c9f2c91011bdeecec8fa76a42d95f3a5ec77cec9) )

	ROM_REGION( 0x02000, "gfx1", 0 )
	ROM_LOAD( "05c_ee00.bin", 0x0000, 0x2000, CRC(cadb75bd) SHA1(2086be5e295e5d870bcb35f116cc925f811b7583) )

	ROM_REGION( 0x04000, "gfx2", 0 )
	ROM_LOAD( "h01_ee08.bin", 0x0000, 0x4000, CRC(96a65c1d) SHA1(3b49c64b32f01ec72cf2d943bfe3aa575d62a765) )

	ROM_REGION( 0x08000, "gfx3", 0 )
	ROM_LOAD( "a03_ee06.bin", 0x0000, 0x4000, CRC(6039bdd1) SHA1(01156e02ed59e6c1e55204729e515cd4419568fb) )
	ROM_LOAD( "a02_ee05.bin", 0x4000, 0x4000, CRC(b32d8252) SHA1(738225146ba38f2a9216fda278838e7ebb29a0bb) )

	ROM_REGION( 0x08000, "gfx4", 0 )
	ROM_LOAD( "j11_ee10.bin", 0x0000, 0x4000, CRC(bc83e265) SHA1(ac9b4cce9e539c560414abf2fc239910f2bfbb2d) )
	ROM_LOAD( "j12_ee11.bin", 0x4000, 0x4000, CRC(0e0f300d) SHA1(2f973748e459b16673115abf7de8615219e39fa4) )

	ROM_REGION( 0x6000, "tilerom", 0 )
	ROM_LOAD( "c01_ee07_hc01.bin", 0x0000, 0x4000, CRC(3b6f6490) SHA1(6aa41231f4912a368235d56befcc7b92b3979ae2) )
	ROM_LOAD( "h04_ee09.bin", 0x4000, 0x2000, CRC(6057c907) SHA1(886790641b84b8cd659d2eb5fd1adbabdd7dad3d) )

	ROM_REGION( 0x0b20, "proms", 0 )
	ROM_LOAD( "02d_e-02.bin", 0x0000, 0x0100, CRC(8d0d5935) SHA1(a0ab827ff3b641965ef851893c399e3988fde55e) )    /* red component */
	ROM_LOAD( "03d_e-03.bin", 0x0100, 0x0100, CRC(d3c17efc) SHA1(af88340287bd732c91bc5c75970f9de0431b4304) )    /* green component */
	ROM_LOAD( "04d_e-04.bin", 0x0200, 0x0100, CRC(58ba964c) SHA1(1f98f8e484a0462f1a9fadef9e57612a32652599) )    /* blue component */
	ROM_LOAD( "06f_e-05.bin", 0x0300, 0x0100, CRC(35a03579) SHA1(1f1b8c777622a1f5564409c5f3ce69cc68199dae) )    /* char lookup table */
	ROM_LOAD( "l04_e-10.bin", 0x0400, 0x0100, CRC(1dfad87a) SHA1(684844c24e630f46525df97ed67e2e63f7e66d0f) )    /* 32x32 tile lookup table */
	ROM_LOAD( "c04_e-07.bin", 0x0500, 0x0100, CRC(850064e0) SHA1(3884485e91bd82539d0d33f46b7abac60f4c3b1c) )    /* 16x16 tile lookup table */
	ROM_LOAD( "l09_e-11.bin", 0x0600, 0x0100, CRC(2bb68710) SHA1(cfb375316245cb8751e765f163e6acf071dda9ca) )    /* sprite lookup table */
	ROM_LOAD( "l10_e-12.bin", 0x0700, 0x0100, CRC(173184ef) SHA1(f91ecbdc67af1eed6757f660cac8a0e6866c1822) )    /* sprite palette bank */
	ROM_LOAD( "06l_e-06.bin", 0x0800, 0x0100, CRC(712ac508) SHA1(5349d722ab6733afdda65f6e0a98322f0d515e86) )    /* interrupt timing (not used) */
	ROM_LOAD( "k06_e-08.bin", 0x0900, 0x0100, CRC(0eaf5158) SHA1(bafd4108708f66cd7b280e47152b108f3e254fc9) )    /* video timing (not used) */
	ROM_LOAD( "l03_e-09.bin", 0x0a00, 0x0100, CRC(0d968558) SHA1(b376885ac8452b6cbf9ced81b1080bfd570d9b91) )    /* unknown (all 0) */
	ROM_LOAD( "03e_e-01.bin", 0x0b00, 0x0020, CRC(1acee376) SHA1(367094d924f8e0ec36d8310fada4d8143358f697) )    /* unknown (priority?) */
ROM_END

/*    YEAR    NAME       PARENT   MACHINE  INPUT                INIT      MONITOR   COMPANY       FULLNAME FLAGS */
/* Exedexes Hack */
GAME( 2026, exedexeshc01, exedexes, exedexes, exedexes, exedexes_state, empty_init, ROT270, "Zeroco", "Exed Exes (Recreation of loctest ver, 2026-09-21)", MACHINE_SUPPORTS_SAVE )

