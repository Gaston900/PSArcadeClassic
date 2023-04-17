// Proyecto Shadows Arcade Classic+
// copyright-holders:Gaston90
#include "../mame/drivers/cps3.cpp"

class cps3_hbmame : public cps3_state
{
public:
	using cps3_state::cps3_state;

	void init_jojon();
	void init_jojoban();
	void init_redeartno();
	void init_sfiiin();
	void init_sfiii2n();
	void init_sfiii3n();
	void redeartn(machine_config &config);

private:

	DECLARE_MACHINE_RESET(redeartn);
	TIMER_CALLBACK_MEMBER(fastboot_timer_callback);
	void hb_unscramble();
	emu_timer* m_fastboot_timer;
};

TIMER_CALLBACK_MEMBER(cps3_hbmame::fastboot_timer_callback)
{
	uint32_t *rom =  (uint32_t*)m_decrypted_gamerom;

	m_maincpu->set_state_int(SH4_PC, rom[0]);
	m_maincpu->set_state_int(SH4_R15, rom[1]);
	m_maincpu->set_state_int(SH4_VBR, 0x6000000);
}

void cps3_hbmame::hb_unscramble()
{
	uint8_t *rom = memregion("old4")->base();
	uint8_t *simm0 = memregion("simm1.0")->base();
	uint8_t *simm1 = memregion("simm1.1")->base();
	uint8_t *simm2 = memregion("simm1.2")->base();
	uint8_t *simm3 = memregion("simm1.3")->base();
	uint32_t i, j = 0;
	for (i = 0; i < 0x200000; i++)
	{
		simm3[i] = rom[j++];
		simm2[i] = rom[j++];
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}

	if (memregion("simm2.0"))
	{
		simm0 = memregion("simm2.0")->base();
		simm1 = memregion("simm2.1")->base();
		simm2 = memregion("simm2.2")->base();
		simm3 = memregion("simm2.3")->base();
		for (i = 0; i < 0x200000; i++)
		{
			simm3[i] = rom[j++];
			simm2[i] = rom[j++];
			simm1[i] = rom[j++];
			simm0[i] = rom[j++];
		}
	}

	j = 0;
	rom = memregion("old5")->base();
	simm0 = memregion("simm3.0")->base();
	simm1 = memregion("simm3.1")->base();
	for (i = 0; i < 0x200000; i++)
	{
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}
	simm0 = memregion("simm3.2")->base();
	simm1 = memregion("simm3.3")->base();
	for (i = 0; i < 0x200000; i++)
	{
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}
	simm0 = memregion("simm3.4")->base();
	simm1 = memregion("simm3.5")->base();
	for (i = 0; i < 0x200000; i++)
	{
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}
	simm0 = memregion("simm3.6")->base();
	simm1 = memregion("simm3.7")->base();
	for (i = 0; i < 0x200000; i++)
	{
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}
	simm0 = memregion("simm4.0")->base();
	simm1 = memregion("simm4.1")->base();
	for (i = 0; i < 0x200000; i++)
	{
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}
	simm0 = memregion("simm4.2")->base();
	simm1 = memregion("simm4.3")->base();
	for (i = 0; i < 0x200000; i++)
	{
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}
	simm0 = memregion("simm4.4")->base();
	simm1 = memregion("simm4.5")->base();
	for (i = 0; i < 0x200000; i++)
	{
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}
	simm0 = memregion("simm4.6")->base();
	simm1 = memregion("simm4.7")->base();
	for (i = 0; i < 0x200000; i++)
	{
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}
	simm0 = memregion("simm5.0")->base();
	simm1 = memregion("simm5.1")->base();
	for (i = 0; i < 0x200000; i++)
	{
		simm1[i] = rom[j++];
		simm0[i] = rom[j++];
	}

	if (memregion("simm5.2"))
	{
		simm0 = memregion("simm5.2")->base();
		simm1 = memregion("simm5.3")->base();
		for (i = 0; i < 0x200000; i++)
		{
			simm1[i] = rom[j++];
			simm0[i] = rom[j++];
		}
	}

	if (memregion("simm5.4"))
	{
		simm0 = memregion("simm5.4")->base();
		simm1 = memregion("simm5.5")->base();
		for (i = 0; i < 0x200000; i++)
		{
			simm1[i] = rom[j++];
			simm0[i] = rom[j++];
		}
		simm0 = memregion("simm5.6")->base();
		simm1 = memregion("simm5.7")->base();
		for (i = 0; i < 0x200000; i++)
		{
			simm1[i] = rom[j++];
			simm0[i] = rom[j++];
		}
	}

	if (memregion("simm6.0"))
	{
		simm0 = memregion("simm6.0")->base();
		simm1 = memregion("simm6.1")->base();
		for (i = 0; i < 0x200000; i++)
		{
			simm1[i] = rom[j++];
			simm0[i] = rom[j++];
		}
		simm0 = memregion("simm6.2")->base();
		simm1 = memregion("simm6.3")->base();
		for (i = 0; i < 0x200000; i++)
		{
			simm1[i] = rom[j++];
			simm0[i] = rom[j++];
		}
		simm0 = memregion("simm6.4")->base();
		simm1 = memregion("simm6.5")->base();
		for (i = 0; i < 0x200000; i++)
		{
			simm1[i] = rom[j++];
			simm0[i] = rom[j++];
		}
		simm0 = memregion("simm6.6")->base();
		simm1 = memregion("simm6.7")->base();
		for (i = 0; i < 0x200000; i++)
		{
			simm1[i] = rom[j++];
			simm0[i] = rom[j++];
		}
	}
}

void cps3_hbmame::init_jojon()
{
	hb_unscramble();
	init_jojo();
}

void cps3_hbmame::init_jojoban()
{
	hb_unscramble();
	init_jojoba();
}

void cps3_hbmame::init_redeartno()
{
	hb_unscramble();
	init_redearth();
}

void cps3_hbmame::init_sfiiin()
{
	hb_unscramble();
	init_sfiii();
}

void cps3_hbmame::init_sfiii2n()
{
	hb_unscramble();
	init_sfiii2();
}

void cps3_hbmame::init_sfiii3n()
{
	hb_unscramble();
	init_sfiii3();
}

MACHINE_RESET_MEMBER( cps3_hbmame, redeartn )
{
	m_current_table_address = -1;

	m_fastboot_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(cps3_hbmame::fastboot_timer_callback),this));
	m_fastboot_timer->adjust(attotime::zero);

	// copy data from flashroms back into user regions + decrypt into regions we execute/draw from.
	copy_from_nvram();
}

void cps3_hbmame::redeartn(machine_config &config)
{
	redearth(config);
	MCFG_MACHINE_RESET_OVERRIDE(cps3_hbmame, redeartn)
}

static INPUT_PORTS_START ( cps3_ren )
	PORT_INCLUDE ( cps3 )
	PORT_MODIFY("INPUTS")
	PORT_BIT( 0x10000000, IP_ACTIVE_LOW, IPT_START1 ) PORT_NAME("P1 Start / Change Orb")
	PORT_BIT( 0x20000000, IP_ACTIVE_LOW, IPT_START2 ) PORT_NAME("P2 Start / Change Orb")

	PORT_START("REG")
	PORT_DIPNAME( 0x0000000f, 0x00000000, DEF_STR( Region ) )
	PORT_DIPSETTING( 0x00000000, "Default" )
	// none of these do anything
	//PORT_DIPSETTING( 0x00000001, DEF_STR( Japan ) )
	//PORT_DIPSETTING( 0x00000002, DEF_STR( Asia ) )
	//PORT_DIPSETTING( 0x00000003, DEF_STR( Europe ) )
	//PORT_DIPSETTING( 0x00000004, DEF_STR( USA ) )
	//PORT_DIPSETTING( 0x00000005, "Hispanic" )
	//PORT_DIPSETTING( 0x00000006, "Brazil" )
	//PORT_DIPSETTING( 0x00000007, "Oceania" )
	//PORT_DIPSETTING( 0x00000008, "Asia NCD" )

	PORT_START("VER")
	PORT_DIPNAME( 0x000000f0, 0x00000060, DEF_STR( Version ) )
	PORT_DIPSETTING( 0x00000060, DEF_STR( Normal ) )
	// none of these do anything
	//PORT_DIPSETTING( 0x00000010, "Character Check" )
	//PORT_DIPSETTING( 0x00000020, "Publicity" )
	//PORT_DIPSETTING( 0x00000030, "Location Test" )
	//PORT_DIPSETTING( 0x00000040, "Show" )
	//PORT_DIPSETTING( 0x00000050, "???" )
INPUT_PORTS_END


ROM_START( redeartn )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "redearthn_asia_nocd.29f400.u2", 0x000000, 0x080000, CRC(db09f27c) SHA1(f2d299cda7cda175b4218526a15f12560654d97f) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "redeartn-simm1.0", 0x00000, 0x200000, CRC(cad468f8) SHA1(b3aa4f7d3fae84e8821417ccde9528d3eda2b7a6) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "redeartn-simm1.1", 0x00000, 0x200000, CRC(e9721d89) SHA1(5c63d10bdbce52d50b6dde14d4a0f1369383d656) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "redeartn-simm1.2", 0x00000, 0x200000, CRC(2889ec98) SHA1(a94310eb4777f908d87e9d90969db8504b4140ff) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "redeartn-simm1.3", 0x00000, 0x200000, CRC(5a6cd148) SHA1(d65c6e8378a91828474a16a3bbcd13c4b3b15f13) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "redeartn-simm3.0", 0x00000, 0x200000, CRC(83350cc5) SHA1(922b1abf80a4a89f35279b66311a7369d3965bd0) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "redeartn-simm3.1", 0x00000, 0x200000, CRC(56734de6) SHA1(75699fa6efe5bec335e4b02e15b3c45726b68fa8) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "redeartn-simm3.2", 0x00000, 0x200000, CRC(800ea0f1) SHA1(33871ab56dc1cd24441389d53e43fb8e43b149d9) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "redeartn-simm3.3", 0x00000, 0x200000, CRC(97e9146c) SHA1(ab7744709615081440bee72f4080d6fd5b938668) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "redeartn-simm3.4", 0x00000, 0x200000, CRC(0cb1d648) SHA1(7042a590c2b7ec55323062127e254da3cdc790a1) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "redeartn-simm3.5", 0x00000, 0x200000, CRC(7a1099f0) SHA1(c6a92ec86eb24485f1db530e0e78f647e8432231) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "redeartn-simm3.6", 0x00000, 0x200000, CRC(aeff8f54) SHA1(fd760e237c2e5fb2da45e32a1c12fd3defb4c3e4) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "redeartn-simm3.7", 0x00000, 0x200000, CRC(f770acd0) SHA1(4b3ccb6f91568f95f04ede6c574144918d131201) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "redeartn-simm4.0", 0x00000, 0x200000, CRC(301e56f2) SHA1(4847d971bff70a2aeed4599e1201c7ec9677da60) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "redeartn-simm4.1", 0x00000, 0x200000, CRC(2048e103) SHA1(b21f95b05cd99749bd3f25cc71b2671c2026847b) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "redeartn-simm4.2", 0x00000, 0x200000, CRC(c9433455) SHA1(63a269d76bac332c2e991d0f6a20c35e0e88680a) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "redeartn-simm4.3", 0x00000, 0x200000, CRC(c02171a8) SHA1(2e9228729b27a6113d9f2e42af310a834979f714) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "redeartn-simm4.4", 0x00000, 0x200000, CRC(2ddbf276) SHA1(b232baaa8edc8db18f8a3bdcc2d38fe984a94a34) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "redeartn-simm4.5", 0x00000, 0x200000, CRC(fea820a6) SHA1(55ee8ef95751f5a509fb126513e1b2a70a3414e5) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "redeartn-simm4.6", 0x00000, 0x200000, CRC(c7528df1) SHA1(aa312f80c2d7759d18d1aa8d416cf932b2850824) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "redeartn-simm4.7", 0x00000, 0x200000, CRC(2449cf3b) SHA1(c60d8042136d74e547f668ad787cae529c42eed9) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "redeartn-simm5.0", 0x00000, 0x200000, CRC(424451b9) SHA1(250fb92254c9e7ff5bc8dbeea5872f8a771dc9bd) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "redeartn-simm5.1", 0x00000, 0x200000, CRC(9b8cb56b) SHA1(2ff1081dc99bb7c2f1e036f4c112137c96b83d23) )
ROM_END

/*    YEAR  NAME       PARENT    MACHINE        INPUT       CLASS             INIT       MONITOR     COMPANY        FULLNAME FLAGS */
GAME( 1996, redeartn,  0,        redeartn,      cps3_ren,   cps3_hbmame, init_redearth,   ROT0,     "Capcom",       "Red Earth (Asia 961121, NO CD)", 0 )



/********************
  Hack And Homebrow
***********************/

ROM_START( jojobahc01 )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "jojoba_euro_nocd.29f400.u2", 0x000000, 0x080000, CRC(1ee2d679) SHA1(9e129b454a376606b3f7e8aec64de425cf9c635c) )

	ROM_REGION( 0x200000, "simm1.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.7", ROMREGION_ERASEFF )

	ROM_REGION32_BE( USER4REGION_LENGTH, "old4", ROMREGION_ERASEFF )
	ROM_LOAD( "10_hc01",  0x000000, 0x800000, CRC(45e18e22) SHA1(e49fe9659852346ad36907b7ddd30b26ae44f309) )
	ROM_LOAD( "20",  0x800000, 0x800000, CRC(1293892b) SHA1(b1beafac1a9c4b6d0640658af8a3eb359e76eb25) )
	ROM_REGION16_BE( USER5REGION_LENGTH, "old5", ROMREGION_ERASEFF )
	ROM_LOAD( "30",  0x0000000, 0x800000, CRC(d25c5005) SHA1(93a19a14783d604bb42feffbe23eb370d11281e8) )
	ROM_LOAD( "31",  0x0800000, 0x800000, CRC(51bb3dba) SHA1(39e95a05882909820b3efa6a3b457b8574012638) )
	ROM_LOAD( "40",  0x1000000, 0x800000, CRC(94dc26d4) SHA1(5ae2815142972f322886eea4885baf2b82563ab1) )
	ROM_LOAD( "41",  0x1800000, 0x800000, CRC(1c53ee62) SHA1(e096bf3cb6fbc3d45955787b8f3213abcd76d120) )
	ROM_LOAD( "50",  0x2000000, 0x800000, CRC(36e416ed) SHA1(58d0e95cc13f39bc171165468ce72f4f17b8d8d6) )
	ROM_LOAD( "51",  0x2800000, 0x800000, CRC(eedf19ca) SHA1(a7660bf9ff87911afb4f83b64456245059986830) )
ROM_END

ROM_START( jojobahc02 )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "jojoba_euro_nocd.29f400.u2", 0x000000, 0x080000, CRC(1ee2d679) SHA1(9e129b454a376606b3f7e8aec64de425cf9c635c) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "jojoba-simm1_hc02.0", 0x00000, 0x200000, CRC(0f37dfd5) SHA1(F4aff0d6c9a6c66e59b2a69c40d401999278bf8c) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "jojoba-simm1_hc02.1", 0x00000, 0x200000, CRC(Bada31bd) SHA1(86a9bf7dd64564c313b9744e8e57209e89ad04c7) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "jojoba-simm1_hc02.2", 0x00000, 0x200000, CRC(C9798137) SHA1(8d71c711479d6d2d1e23dd74ce00b0b529772040) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "jojoba-simm1_hc02.3", 0x00000, 0x200000, CRC(cc1e02e3) SHA1(c4f9f9d557738aa4b8ac3ad9fa90d163f8358c23) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "jojoba-simm2_hc02.0", 0x00000, 0x200000, CRC(305c4914) SHA1(c3a73ffe58f61ab8f1cd9e3f0891037638dc5a9b) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "jojoba-simm2_hc02.1", 0x00000, 0x200000, CRC(18af4f3b) SHA1(04b8fdf23a782b10c203b111cc634a6d3474044a) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "jojoba-simm2_hc02.2", 0x00000, 0x200000, CRC(397e5c9e) SHA1(021d86ee66bf951fb6a1dd90fb7007c6865cbb8b) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "jojoba-simm2_hc02.3", 0x00000, 0x200000, CRC(a9d0a7d7) SHA1(b2cfc0661f8903ddbeea8a604ee8b42097e10ab8) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "jojoba-simm3.0",  0x00000, 0x200000, CRC(4d16e111) SHA1(f198007375be65e89856d64ee2b3857a18b4eab8) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "jojoba-simm3.1",  0x00000, 0x200000, CRC(9b3406d3) SHA1(54e90cd334d13e2c74305c6b87ebce1365ef3d59) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "jojoba-simm3.2",  0x00000, 0x200000, CRC(f2414997) SHA1(fb89d5784250538ad17fd527267b513afb6eca20) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "jojoba-simm3.3",  0x00000, 0x200000, CRC(954b9c7d) SHA1(0d64d97167d4e669d7e4f3a388f9d5ec1e18ed42) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "jojoba-simm3.4",  0x00000, 0x200000, CRC(625adc1d) SHA1(533d62759ecece10c711d99bfca403e5cba279b5) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "jojoba-simm3.5",  0x00000, 0x200000, CRC(20a70bb4) SHA1(3bd8376304ffc974fb8031eac8bebff27969538c) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "jojoba-simm3.6",  0x00000, 0x200000, CRC(a10ec5af) SHA1(9b403260e8fbdacaa5369ab79fc05855cc6a6bdb) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "jojoba-simm3.7",  0x00000, 0x200000, CRC(0bd0de7a) SHA1(1debecda5f282f2a1dd17e887e522a4d00c5dc9d) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "jojoba-simm4.0",  0x00000, 0x200000, CRC(6ea14adc) SHA1(696b2ec66f3c197817a60f507a1b4c78db37f488) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "jojoba-simm4.1",  0x00000, 0x200000, CRC(8f4c42fb) SHA1(363d769b0b066ce139125426d2da6dfa15d1eb28) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "jojoba-simm4.2",  0x00000, 0x200000, CRC(ef0586d1) SHA1(8fcc350da20e3e59fa76fa14e10f2c47233ba9dc) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "jojoba-simm4.3",  0x00000, 0x200000, CRC(93ccc470) SHA1(5d267679e61c0fb592ad5f696d3c06ec1746d0b3) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "jojoba-simm4.4",  0x00000, 0x200000, CRC(3d9ec7d2) SHA1(665b867bab928be183c2006527e55f9b8ec4a271) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "jojoba-simm4.5",  0x00000, 0x200000, CRC(03e66850) SHA1(8478662dc9db20d9a186d315a883bd1cbb5e5000) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "jojoba-simm4.6",  0x00000, 0x200000, CRC(01606ac3) SHA1(ccc74edeca6abdd86fc1cf42ececa1ea393b3261) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "jojoba-simm4.7",  0x00000, 0x200000, CRC(36392b87) SHA1(e62080c8461775c1e180400dfb44414679fd0fc1) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "jojoba-simm5.0",  0x00000, 0x200000, CRC(2ef8c60c) SHA1(dea87a73a11b8edd27c3c9c5ab2af295cb5508f9) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "jojoba-simm5.1",  0x00000, 0x200000, CRC(cf7d7ca6) SHA1(b347707b1e5bc71d28b282273f893592e5f9e333) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "jojoba-simm5.2",  0x00000, 0x200000, CRC(b7815bfa) SHA1(0b5a3a2ffe1b3c0ca765dcedc297e78e5928302b) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "jojoba-simm5.3",  0x00000, 0x200000, CRC(9bfec049) SHA1(62cc9a1920047863205544b77344ee18f310f084) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "jojoba-simm5.4",  0x00000, 0x200000, CRC(d167536b) SHA1(e2637d3486f168ce44e0a00413d38960cb86db4c) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "jojoba-simm5.5",  0x00000, 0x200000, CRC(55e7a042) SHA1(c18bda61fa005d9174a27b7b7d324004262a4525) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "jojoba-simm5.6",  0x00000, 0x200000, CRC(4fb32906) SHA1(3a5965b3197517932c8aa4c07a6ea6a190a338d7) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "jojoba-simm5.7",  0x00000, 0x200000, CRC(8c8be520) SHA1(c461f3f76a83592b36b29afb316679a7c8972404) )
ROM_END

ROM_START( jojobahc03 ) //jojobanrb
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "jojoba_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(4dab19f5) SHA1(ba07190e7662937fc267f07285c51e99a45c061e) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "jojoba-simm1_hc03.0", 0x00000, 0x200000, CRC(3b75c72e) SHA1(30a1cb70dac1db81714dd75fbdbfb4327d953b44) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "jojoba-simm1_hc03.1", 0x00000, 0x200000, CRC(9f0d57f6) SHA1(227b3cbcfc47d56a655fa7a1b54ec03880f6ddc9) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "jojoba-simm1_hc03.2", 0x00000, 0x200000, CRC(480184c2) SHA1(92223a81c91811cc2a2858182f6e5de28f39083d) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "jojoba-simm1_hc03.3", 0x00000, 0x200000, CRC(2ddb747c) SHA1(0cc5ecb5f04637a298567f97c24969ef73f5c130) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "jojoba-simm2_hc03.0", 0x00000, 0x200000, CRC(7d618904) SHA1(80abecbc0c9aa130e0b7115faa1c7c686ef956b6) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "jojoba-simm2_hc03.1", 0x00000, 0x200000, CRC(882f76a0) SHA1(3a6c3fb09e843a1df1dcb1b70b192b957e7afccc) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "jojoba-simm2_hc03.2", 0x00000, 0x200000, CRC(58ed6139) SHA1(105e92d1c77a248476c96b073cceb684800844df) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "jojoba-simm2_hc03.3", 0x00000, 0x200000, CRC(64c19159) SHA1(66916fed0034a0f4151f5f58b920f74593d1a273) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "jojoba-simm3_hc03.0",  0x00000, 0x200000, CRC(c579314a) SHA1(4d7f913ad1bd17c90566c14afe227b552cd2a845) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "jojoba-simm3_hc03.1",  0x00000, 0x200000, CRC(2dc0682d) SHA1(fcd1c551596195f300dbb6e4871dec3fcf9a0f99) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "jojoba-simm3_hc03.2",  0x00000, 0x200000, CRC(eb3470ff) SHA1(329d00e4ab66dc9d2bd66c89068d7f113182c79a) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "jojoba-simm3_hc03.3",  0x00000, 0x200000, CRC(b9d1fb4f) SHA1(7045154809b065b8e8628ee71703fd826318d359) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "jojoba-simm3_hc03.4",  0x00000, 0x200000, CRC(bb8a7b4d) SHA1(a2bd7db4ca5d577a08f876245b2f3fd9fbe882a1) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "jojoba-simm3_hc03.5",  0x00000, 0x200000, CRC(b5e2a429) SHA1(c57d3b8285bc3797d2024df4a9c21826da469cbb) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "jojoba-simm3.6",  0x00000, 0x200000, CRC(a10ec5af) SHA1(9b403260e8fbdacaa5369ab79fc05855cc6a6bdb) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "jojoba-simm3.7",  0x00000, 0x200000, CRC(0bd0de7a) SHA1(1debecda5f282f2a1dd17e887e522a4d00c5dc9d) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "jojoba-simm4.0",  0x00000, 0x200000, CRC(6ea14adc) SHA1(696b2ec66f3c197817a60f507a1b4c78db37f488) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "jojoba-simm4.1",  0x00000, 0x200000, CRC(8f4c42fb) SHA1(363d769b0b066ce139125426d2da6dfa15d1eb28) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "jojoba-simm4.2",  0x00000, 0x200000, CRC(ef0586d1) SHA1(8fcc350da20e3e59fa76fa14e10f2c47233ba9dc) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "jojoba-simm4.3",  0x00000, 0x200000, CRC(93ccc470) SHA1(5d267679e61c0fb592ad5f696d3c06ec1746d0b3) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "jojoba-simm4.4",  0x00000, 0x200000, CRC(3d9ec7d2) SHA1(665b867bab928be183c2006527e55f9b8ec4a271) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "jojoba-simm4.5",  0x00000, 0x200000, CRC(03e66850) SHA1(8478662dc9db20d9a186d315a883bd1cbb5e5000) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "jojoba-simm4.6",  0x00000, 0x200000, CRC(01606ac3) SHA1(ccc74edeca6abdd86fc1cf42ececa1ea393b3261) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "jojoba-simm4.7",  0x00000, 0x200000, CRC(36392b87) SHA1(e62080c8461775c1e180400dfb44414679fd0fc1) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "jojoba-simm5.0",  0x00000, 0x200000, CRC(2ef8c60c) SHA1(dea87a73a11b8edd27c3c9c5ab2af295cb5508f9) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "jojoba-simm5.1",  0x00000, 0x200000, CRC(cf7d7ca6) SHA1(b347707b1e5bc71d28b282273f893592e5f9e333) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "jojoba-simm5.2",  0x00000, 0x200000, CRC(b7815bfa) SHA1(0b5a3a2ffe1b3c0ca765dcedc297e78e5928302b) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "jojoba-simm5.3",  0x00000, 0x200000, CRC(9bfec049) SHA1(62cc9a1920047863205544b77344ee18f310f084) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "jojoba-simm5_hc03.4",  0x00000, 0x200000, CRC(f475f126) SHA1(0beec12f9a75a1cfe5397ac00300f900e76c5c5d) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "jojoba-simm5_hc03.5",  0x00000, 0x200000, CRC(b028b441) SHA1(b7e11141a2a8dee75fe59e82ac3d381222659ddd) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "jojoba-simm5.6",  0x00000, 0x200000, CRC(4fb32906) SHA1(3a5965b3197517932c8aa4c07a6ea6a190a338d7) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "jojoba-simm5.7",  0x00000, 0x200000, CRC(8c8be520) SHA1(c461f3f76a83592b36b29afb316679a7c8972404) )
ROM_END

ROM_START( jojohc01 ) //jojonbss
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "jojo_asia_nocd.29f400.u2", 0x000000, 0x080000, CRC(05b4f953) SHA1(c746c7bb5359acc9adced817cb4870b1912eaefd) )

	ROM_REGION( 0x200000, "simm1.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.3", ROMREGION_ERASEFF )

	ROM_REGION32_BE( USER4REGION_LENGTH, "old4", ROMREGION_ERASEFF )
	ROM_LOAD( "10_hc01",  0x0000000, 0x800000, CRC(fccbce04) SHA1(cd4d429620afdd1924ceb33f1a435c9de91453c3) )
	ROM_LOAD( "20",  0x0800000, 0x800000, CRC(0e1daddf) SHA1(34bb4e0fb86258095a7b20f60174453195f3735a) )
	ROM_REGION16_BE( USER5REGION_LENGTH, "old5", ROMREGION_ERASEFF )
	ROM_LOAD( "30",  0x0000000, 0x800000, CRC(1d99181b) SHA1(25c216de16cefac2d5892039ad23d07848a457e6) )
	ROM_LOAD( "31",  0x0800000, 0x800000, CRC(6889fbda) SHA1(53a51b993d319d81a604cdf70b224955eacb617e) )
	ROM_LOAD( "40",  0x1000000, 0x800000, CRC(8069f9de) SHA1(7862ee104a2e9034910dd592687b40ebe75fa9ce) )
	ROM_LOAD( "41",  0x1800000, 0x800000, CRC(9c426823) SHA1(1839dccc7943a44063e8cb2376cd566b24e8b797) )
	ROM_LOAD( "50",  0x2000000, 0x400000, CRC(1c749cc7) SHA1(23df741360476d8035c68247e645278fbab53b59) )
ROM_END

ROM_START( redeartnhc01 ) //redearex
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "redearthn_asia_nocd.29f400.u2", 0x000000, 0x080000, CRC(db09f27c) SHA1(f2d299cda7cda175b4218526a15f12560654d97f) )

	ROM_REGION( 0x200000, "simm1.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.1", ROMREGION_ERASEFF )

	ROM_REGION32_BE( USER4REGION_LENGTH, "old4", 0 )
	ROM_LOAD( "10_hc01",  0x000000,  0x800000, CRC(e44131ad) SHA1(1b395edd8c0cb2705a1bdbb8df75e6d218d8e379) )
	ROM_REGION16_BE( USER5REGION_LENGTH, "old5", 0 )
	ROM_LOAD( "30",  0x0000000, 0x800000, CRC(074cab4d) SHA1(4cb6cc9cce3b1a932b07058a5d723b3effa23fcf) )
	ROM_LOAD( "31",  0x0800000, 0x800000, CRC(14e2cad4) SHA1(9958a4e315e4476e4791a6219b93495413c7b751) )
	ROM_LOAD( "40",  0x1000000, 0x800000, CRC(72d98890) SHA1(f40926c52cb7a71b0ef0027a0ea38bbc7e8b31b0) )
	ROM_LOAD( "41",  0x1800000, 0x800000, CRC(88ccb33c) SHA1(1e7af35d186d0b4e45b6c27458ddb9cfddd7c9bc) )
	ROM_LOAD( "50",  0x2000000, 0x400000, CRC(2f5b44bd) SHA1(7ffdbed5b6899b7e31414a0828e04543d07435e4) )
ROM_END

ROM_START( sfiiihc01 )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii_asia_nocd.29f400.u2", 0x000000, 0x080000, CRC(ca2b715f) SHA1(86319987f9af4afd272a2488e73de8382743cb37) ) // this is a different VERSION of the bios compared to all other sets, not just an alt region code

	ROM_REGION( 0x500000, "simm1.0", 0 )
	ROM_LOAD( "sfiii-simm1_hc01.0", 0x00000, 0x454F4D, CRC(2858434c) SHA1(528b9b3716a8384bca1206a6a3863dde5a4c06f4) )
	ROM_REGION( 0x500000, "simm1.1", 0 )
	ROM_LOAD( "sfiii-simm1_hc01.1", 0x00000, 0x454F47, CRC(75d3a584) SHA1(d2f9809d0614498bf6538b8c24eb172cd37906de) )
	ROM_REGION( 0x500000, "simm1.2", 0 )
	ROM_LOAD( "sfiii-simm1_hc01.2", 0x00000, 0x454F47, CRC(9a9c8312) SHA1(14d7ba6aa7186c2df1a403191d658c24bc0a5560) )
	ROM_REGION( 0x500000, "simm1.3", 0 )
	ROM_LOAD( "sfiii-simm1_hc01.3", 0x00000, 0x454F47, CRC(d338a53f) SHA1(4814c416b37914dbfb50fd008a1b8b21f7facf33) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii-simm3.0", 0x00000, 0x200000, CRC(080b3bd3) SHA1(f51bc5de95ab22b87ba09ea721285b308afd0bda) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii-simm3.1", 0x00000, 0x200000, CRC(5c356f2f) SHA1(e969ce388f6e565d9612e65b0895560c7bb472e6) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii-simm3.2", 0x00000, 0x200000, CRC(f9c97a45) SHA1(58a9691696c3f26a1150a451567c501f55cf1874) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii-simm3.3", 0x00000, 0x200000, CRC(09de3ead) SHA1(2f41d84a96cb5e0d169200a4e9358ad5f407a2b7) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii-simm3.4", 0x00000, 0x200000, CRC(7dd7e1f3) SHA1(bcf1023287457d97f09d9f6e9c93fdf24cc24a07) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii-simm3.5", 0x00000, 0x200000, CRC(47a03a3a) SHA1(2509e5737059251888e4e1efbcdfac86a89ff1a1) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii-simm3.6", 0x00000, 0x200000, CRC(e9eb7a26) SHA1(b8547edb7085e9149aa59d5226ad2d1976cab2bd) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii-simm3.7", 0x00000, 0x200000, CRC(7f44395c) SHA1(f4d2e283cb3a4aad4eae4e13963a74e20be7c181) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii-simm4.0", 0x00000, 0x200000, CRC(9ac080fc) SHA1(2e5024b35b147513ee42eda8748df9d669410377) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii-simm4.1", 0x00000, 0x200000, CRC(6e2c4c94) SHA1(5a185cb76b5999bd826bc9b5ea584a5c3498f69d) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii-simm4.2", 0x00000, 0x200000, CRC(8afc22d4) SHA1(04a419a3092c98fc4a7693e6acf30ae5a849e5c1) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii-simm4.3", 0x00000, 0x200000, CRC(9f3873b8) SHA1(33499d6f02bc84c80acb56be078aaed7f8d1300d) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii-simm4.4", 0x00000, 0x200000, CRC(166b3c97) SHA1(40e6e9d43cbbd8496b430931b8ab7db01dc1c6d5) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii-simm4.5", 0x00000, 0x200000, CRC(e5ea2547) SHA1(a823c689098f37a3054d728bddb0033a4b8396f1) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii-simm4.6", 0x00000, 0x200000, CRC(e85b9fdd) SHA1(264cb10fe9b3ede384c7db42bfc58ed5c21ea8f8) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii-simm4.7", 0x00000, 0x200000, CRC(362c01b7) SHA1(9c404312a6aabe8e91e68dde193e3972bc1636cd) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii-simm5.0", 0x00000, 0x200000, CRC(9bc108b2) SHA1(894dadab7957044bf877029c7f8e556d5d6e85d3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii-simm5.1", 0x00000, 0x200000, CRC(c6f1c066) SHA1(00de492dd1ef7aef05027a8c501c296b6602e917) )
ROM_END

ROM_START( sfiiihc02 ) //sfiiibhp
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii_asia_nocdo.29f400.u2", 0x000000, 0x080000, CRC(73e32463) SHA1(45d144e533e4b20cc5a744ca4f618e288430c601) )

	ROM_REGION( 0x200000, "simm1.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.1", ROMREGION_ERASEFF )

	ROM_REGION32_BE( USER4REGION_LENGTH, "old4", 0 )
	ROM_LOAD( "10_hc02",  0x0000000, 0x800000, CRC(cebd13a2) SHA1(18017d798448f6271f5c7b07325e0410b5d55f0d) )
	ROM_REGION16_BE( USER5REGION_LENGTH, "old5", 0 )
	ROM_LOAD( "30",  0x0000000, 0x800000, CRC(98c2d07c) SHA1(604ce4a16170847c10bc233a47a47a119ce170f7) )
	ROM_LOAD( "31",  0x0800000, 0x800000, CRC(7115a396) SHA1(b60a74259e3c223138e66e68a3f6457694a0c639) )
	ROM_LOAD( "40",  0x1000000, 0x800000, CRC(839f0972) SHA1(844e43fcc157b7c774044408bfe918c49e174cdb) )
	ROM_LOAD( "41",  0x1800000, 0x800000, CRC(8a8b252c) SHA1(9ead4028a212c689d7a25746fbd656dca6f938e8) )
	ROM_LOAD( "50",  0x2000000, 0x400000, CRC(58933dc2) SHA1(1f1723be676a817237e96b6e20263b935c59daae) )
ROM_END

ROM_START( sfiii2hc01 )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii2_asia_nocd.29f400.u2", 0x000000, 0x080000, CRC(fd297c0d) SHA1(4323deda2789f104b53f32a663196ec16de73215) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "sfiii2-simm1_hc01.0", 0x00000, 0x200000, CRC(6dbece23) SHA1(294cf2ebcca56258da039fa004d9c183ddf4edd8) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "sfiii2-simm1_hc01.1", 0x00000, 0x200000, CRC(6db2e601) SHA1(E8326eac4eecf33d6d7a4bf0878fc1135a255d1a) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "sfiii2-simm1_hc01.2", 0x00000, 0x200000, CRC(A9d988e8) SHA1(29c265b23fbd091276476f1f37a8fde359665f82) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "sfiii2-simm1_hc01.3", 0x00000, 0x200000, CRC(Cfa1f8a2) SHA1(6efa2e1252fb886cdea572ac86f34ee24b1b7ae5) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii2-simm2.0", 0x00000, 0x200000, CRC(94a4ce0f) SHA1(2c8e26a66d1dcd17c22c70baa2a3ff5a54511514) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii2-simm2.1", 0x00000, 0x200000, CRC(67585033) SHA1(24df9968a54c330fbe95f8e4dfe6e7dfd144ed0c) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii2-simm2.2", 0x00000, 0x200000, CRC(fabffcd5) SHA1(9399f64c42f63a64e44a21a2690e44779943a2b2) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii2-simm2.3", 0x00000, 0x200000, CRC(623c09ca) SHA1(dc9618a08bb7f44e569ac17605d268511155a14e) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii2-simm3.0", 0x00000, 0x200000, CRC(dab2d766) SHA1(d265cc8b1b497eb4bedd63b3f1de60eb1c1db0df) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii2-simm3.1", 0x00000, 0x200000, CRC(1f2aa34b) SHA1(38b224d34c4550f1f33c2c368e2a252d0d176cc0) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii2-simm3.2", 0x00000, 0x200000, CRC(6f1a04eb) SHA1(980ca929114075d1920e2da44f9a22087cc92e55) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii2-simm3.3", 0x00000, 0x200000, CRC(e05ef205) SHA1(e604e3832549740f953581fc91e850beda6a73c8) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii2-simm3.4", 0x00000, 0x200000, CRC(affb074f) SHA1(0e76973807039bc66fd0f3233401cea8d2c45f84) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii2-simm3.5", 0x00000, 0x200000, CRC(6962872e) SHA1(f16b2d0792697345145d0e9d950e912a2ffabe0d) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii2-simm3.6", 0x00000, 0x200000, CRC(6eed87de) SHA1(5d5067ad36234c5efd57a2baebeffa2f44f2caec) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii2-simm3.7", 0x00000, 0x200000, CRC(e18f479e) SHA1(cd4c1812ab422336bfa414e0b2098b472d2f9251) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii2-simm4.0", 0x00000, 0x200000, CRC(764c2503) SHA1(cad3f20ade2e1d3ac52f8c318443da20062ae943) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii2-simm4.1", 0x00000, 0x200000, CRC(3e16af6e) SHA1(afde2ed4bf3a3e95035fc02c572c5b83178a9467) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii2-simm4.2", 0x00000, 0x200000, CRC(215705e6) SHA1(42d3849f8a9242a89ba465dbc205f310186c67cd) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii2-simm4.3", 0x00000, 0x200000, CRC(e30cbd9c) SHA1(c205101ada86154921e09fed4f6908d15ec60761) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii2-simm4.4", 0x00000, 0x200000, CRC(4185ded9) SHA1(24bf9b5f25d7753f1feb09b82611f7482f30d304) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii2-simm4.5", 0x00000, 0x200000, CRC(4e8db013) SHA1(6816df2b6c60005fb375530ea93bb30a960c9b01) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii2-simm4.6", 0x00000, 0x200000, CRC(08df48ce) SHA1(e8a3b68ebeab193539446c3f6e0a19b37f1f3495) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii2-simm4.7", 0x00000, 0x200000, CRC(bb8f80a5) SHA1(35d9e86637d54405c97fdb7da9c42cc53907cae3) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii2-simm5.0", 0x00000, 0x200000, CRC(ebdc4787) SHA1(f86e8ebf4b2214be166dbe4ea921058a552364ea) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii2-simm5.1", 0x00000, 0x200000, CRC(6b7c550e) SHA1(77cdabccf3ecebf142ac86dffe6e24052941e3a1) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii2-simm5.2", 0x00000, 0x200000, CRC(56ff8c50) SHA1(16f7602a4549a5b724e3fcdb75b0f3c397077b81) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii2-simm5.3", 0x00000, 0x200000, CRC(3f2ac3e9) SHA1(a7b631f18ce572a42f46314f37a01d9840abc765) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii2-simm5.4", 0x00000, 0x200000, CRC(48cda50e) SHA1(35e9f27fb8b69e3b3a313ea33dc53b1102e5f66e) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii2-simm5.5", 0x00000, 0x200000, CRC(520c0af6) SHA1(7bed1b6707974eafbfb62ccb84a51df8a100e070) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "sfiii2-simm5.6", 0x00000, 0x200000, CRC(2edc5986) SHA1(761ab2c67d0d873ffd74158eb77f7722c076f3e3) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "sfiii2-simm5.7", 0x00000, 0x200000, CRC(93ffa199) SHA1(33ec2379f30c6fdf47ba72c1d0cad8bdd02f17df) )
ROM_END

ROM_START( sfiii2hc02 )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii2_asia_nocd.29f400.u2", 0x000000, 0x080000, CRC(fd297c0d) SHA1(4323deda2789f104b53f32a663196ec16de73215) )

	ROM_REGION( 0x500000, "simm1.0", 0 )
	ROM_LOAD( "sfiii2-simm_hc02.0", 0x00000, 0x454F4B, CRC(2d666f0b) SHA1(58e40d55054799f2bcfca72b601a9149ab600a70) )
	ROM_REGION( 0x500000, "simm1.1", 0 )
	ROM_LOAD( "sfiii2-simm_hc02.1", 0x00000, 0x454F4C, CRC(2a3a8ef6) SHA1(c3d058e4dfb141a0e63083aebaded501037dd544) )
	ROM_REGION( 0x500000, "simm1.2", 0 )
	ROM_LOAD( "sfiii2-simm_hc02.2", 0x00000, 0x454F4C, CRC(161d2206) SHA1(b57303a9b38010fdd2c4c05e08e06ae654b86341) )
	ROM_REGION( 0x500000, "simm1.3", 0 )
	ROM_LOAD( "sfiii2-simm_hc02.3", 0x00000, 0x454F4B, CRC(87ded8a3) SHA1(64be027af5507875bf2617393b6fa9c7cc305255) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii2-simm2.0", 0x00000, 0x200000, CRC(94a4ce0f) SHA1(2c8e26a66d1dcd17c22c70baa2a3ff5a54511514) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii2-simm2.1", 0x00000, 0x200000, CRC(67585033) SHA1(24df9968a54c330fbe95f8e4dfe6e7dfd144ed0c) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii2-simm2.2", 0x00000, 0x200000, CRC(fabffcd5) SHA1(9399f64c42f63a64e44a21a2690e44779943a2b2) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii2-simm2.3", 0x00000, 0x200000, CRC(623c09ca) SHA1(dc9618a08bb7f44e569ac17605d268511155a14e) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii2-simm3.0", 0x00000, 0x200000, CRC(dab2d766) SHA1(d265cc8b1b497eb4bedd63b3f1de60eb1c1db0df) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii2-simm3.1", 0x00000, 0x200000, CRC(1f2aa34b) SHA1(38b224d34c4550f1f33c2c368e2a252d0d176cc0) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii2-simm3.2", 0x00000, 0x200000, CRC(6f1a04eb) SHA1(980ca929114075d1920e2da44f9a22087cc92e55) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii2-simm3.3", 0x00000, 0x200000, CRC(e05ef205) SHA1(e604e3832549740f953581fc91e850beda6a73c8) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii2-simm3.4", 0x00000, 0x200000, CRC(affb074f) SHA1(0e76973807039bc66fd0f3233401cea8d2c45f84) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii2-simm3.5", 0x00000, 0x200000, CRC(6962872e) SHA1(f16b2d0792697345145d0e9d950e912a2ffabe0d) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii2-simm3.6", 0x00000, 0x200000, CRC(6eed87de) SHA1(5d5067ad36234c5efd57a2baebeffa2f44f2caec) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii2-simm3.7", 0x00000, 0x200000, CRC(e18f479e) SHA1(cd4c1812ab422336bfa414e0b2098b472d2f9251) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii2-simm4.0", 0x00000, 0x200000, CRC(764c2503) SHA1(cad3f20ade2e1d3ac52f8c318443da20062ae943) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii2-simm4.1", 0x00000, 0x200000, CRC(3e16af6e) SHA1(afde2ed4bf3a3e95035fc02c572c5b83178a9467) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii2-simm4.2", 0x00000, 0x200000, CRC(215705e6) SHA1(42d3849f8a9242a89ba465dbc205f310186c67cd) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii2-simm4.3", 0x00000, 0x200000, CRC(e30cbd9c) SHA1(c205101ada86154921e09fed4f6908d15ec60761) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii2-simm4.4", 0x00000, 0x200000, CRC(4185ded9) SHA1(24bf9b5f25d7753f1feb09b82611f7482f30d304) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii2-simm4.5", 0x00000, 0x200000, CRC(4e8db013) SHA1(6816df2b6c60005fb375530ea93bb30a960c9b01) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii2-simm4.6", 0x00000, 0x200000, CRC(08df48ce) SHA1(e8a3b68ebeab193539446c3f6e0a19b37f1f3495) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii2-simm4.7", 0x00000, 0x200000, CRC(bb8f80a5) SHA1(35d9e86637d54405c97fdb7da9c42cc53907cae3) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii2-simm5.0", 0x00000, 0x200000, CRC(ebdc4787) SHA1(f86e8ebf4b2214be166dbe4ea921058a552364ea) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii2-simm5.1", 0x00000, 0x200000, CRC(6b7c550e) SHA1(77cdabccf3ecebf142ac86dffe6e24052941e3a1) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii2-simm5.2", 0x00000, 0x200000, CRC(56ff8c50) SHA1(16f7602a4549a5b724e3fcdb75b0f3c397077b81) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii2-simm5.3", 0x00000, 0x200000, CRC(3f2ac3e9) SHA1(a7b631f18ce572a42f46314f37a01d9840abc765) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii2-simm5.4", 0x00000, 0x200000, CRC(48cda50e) SHA1(35e9f27fb8b69e3b3a313ea33dc53b1102e5f66e) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii2-simm5.5", 0x00000, 0x200000, CRC(520c0af6) SHA1(7bed1b6707974eafbfb62ccb84a51df8a100e070) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "sfiii2-simm5.6", 0x00000, 0x200000, CRC(2edc5986) SHA1(761ab2c67d0d873ffd74158eb77f7722c076f3e3) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "sfiii2-simm5.7", 0x00000, 0x200000, CRC(93ffa199) SHA1(33ec2379f30c6fdf47ba72c1d0cad8bdd02f17df) )
ROM_END

ROM_START( sfiii2hc03 )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii2_asia_nocd.29f400.u2", 0x000000, 0x080000, CRC(fd297c0d) SHA1(4323deda2789f104b53f32a663196ec16de73215) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "sfiii2-simm1_hc03.0", 0x00000, 0x200000, CRC(116116a4) SHA1(6050151bbd10162b40588a16778d68c9812c0632) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "sfiii2-simm1_hc03.1", 0x00000, 0x200000, CRC(a3d639cd) SHA1(249c958afcab3b22ca5666b151b2cc6eea74c127) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "sfiii2-simm1_hc03.2", 0x00000, 0x200000, CRC(a9d988e8) SHA1(29c265b23fbd091276476f1f37a8fde359665f82) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "sfiii2-simm1_hc03.3", 0x00000, 0x200000, CRC(1d1335d9) SHA1(b41d5439a0807b3eb27dffe1803ee8581661b30d) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii2-simm2.0", 0x00000, 0x200000, CRC(94a4ce0f) SHA1(2c8e26a66d1dcd17c22c70baa2a3ff5a54511514) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii2-simm2.1", 0x00000, 0x200000, CRC(67585033) SHA1(24df9968a54c330fbe95f8e4dfe6e7dfd144ed0c) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii2-simm2.2", 0x00000, 0x200000, CRC(fabffcd5) SHA1(9399f64c42f63a64e44a21a2690e44779943a2b2) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii2-simm2.3", 0x00000, 0x200000, CRC(623c09ca) SHA1(dc9618a08bb7f44e569ac17605d268511155a14e) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii2-simm3.0", 0x00000, 0x200000, CRC(dab2d766) SHA1(d265cc8b1b497eb4bedd63b3f1de60eb1c1db0df) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii2-simm3.1", 0x00000, 0x200000, CRC(1f2aa34b) SHA1(38b224d34c4550f1f33c2c368e2a252d0d176cc0) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii2-simm3.2", 0x00000, 0x200000, CRC(6f1a04eb) SHA1(980ca929114075d1920e2da44f9a22087cc92e55) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii2-simm3.3", 0x00000, 0x200000, CRC(e05ef205) SHA1(e604e3832549740f953581fc91e850beda6a73c8) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii2-simm3.4", 0x00000, 0x200000, CRC(affb074f) SHA1(0e76973807039bc66fd0f3233401cea8d2c45f84) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii2-simm3.5", 0x00000, 0x200000, CRC(6962872e) SHA1(f16b2d0792697345145d0e9d950e912a2ffabe0d) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii2-simm3.6", 0x00000, 0x200000, CRC(6eed87de) SHA1(5d5067ad36234c5efd57a2baebeffa2f44f2caec) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii2-simm3.7", 0x00000, 0x200000, CRC(e18f479e) SHA1(cd4c1812ab422336bfa414e0b2098b472d2f9251) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii2-simm4.0", 0x00000, 0x200000, CRC(764c2503) SHA1(cad3f20ade2e1d3ac52f8c318443da20062ae943) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii2-simm4.1", 0x00000, 0x200000, CRC(3e16af6e) SHA1(afde2ed4bf3a3e95035fc02c572c5b83178a9467) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii2-simm4.2", 0x00000, 0x200000, CRC(215705e6) SHA1(42d3849f8a9242a89ba465dbc205f310186c67cd) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii2-simm4.3", 0x00000, 0x200000, CRC(e30cbd9c) SHA1(c205101ada86154921e09fed4f6908d15ec60761) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii2-simm4.4", 0x00000, 0x200000, CRC(4185ded9) SHA1(24bf9b5f25d7753f1feb09b82611f7482f30d304) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii2-simm4.5", 0x00000, 0x200000, CRC(4e8db013) SHA1(6816df2b6c60005fb375530ea93bb30a960c9b01) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii2-simm4.6", 0x00000, 0x200000, CRC(08df48ce) SHA1(e8a3b68ebeab193539446c3f6e0a19b37f1f3495) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii2-simm4.7", 0x00000, 0x200000, CRC(bb8f80a5) SHA1(35d9e86637d54405c97fdb7da9c42cc53907cae3) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii2-simm5.0", 0x00000, 0x200000, CRC(ebdc4787) SHA1(f86e8ebf4b2214be166dbe4ea921058a552364ea) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii2-simm5.1", 0x00000, 0x200000, CRC(6b7c550e) SHA1(77cdabccf3ecebf142ac86dffe6e24052941e3a1) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii2-simm5.2", 0x00000, 0x200000, CRC(56ff8c50) SHA1(16f7602a4549a5b724e3fcdb75b0f3c397077b81) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii2-simm5.3", 0x00000, 0x200000, CRC(3f2ac3e9) SHA1(a7b631f18ce572a42f46314f37a01d9840abc765) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii2-simm5.4", 0x00000, 0x200000, CRC(48cda50e) SHA1(35e9f27fb8b69e3b3a313ea33dc53b1102e5f66e) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii2-simm5.5", 0x00000, 0x200000, CRC(520c0af6) SHA1(7bed1b6707974eafbfb62ccb84a51df8a100e070) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "sfiii2-simm5.6", 0x00000, 0x200000, CRC(2edc5986) SHA1(761ab2c67d0d873ffd74158eb77f7722c076f3e3) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "sfiii2-simm5.7", 0x00000, 0x200000, CRC(93ffa199) SHA1(33ec2379f30c6fdf47ba72c1d0cad8bdd02f17df) )
ROM_END

ROM_START( sfiii3hc01 ) //sfiii3ws
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "sfiii3-simm1_hc01.0", 0x00000, 0x200000, CRC(c1c25038) SHA1(898cf59d39fb304e8eb834ecdd62a1f9854fd8ff) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "sfiii3-simm1_hc01.1", 0x00000, 0x200000, CRC(284a0c1c) SHA1(e0a6dd54ca17ad2e7fb1293fabd65b27468929b0) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "sfiii3-simm1_hc01.2", 0x00000, 0x200000, CRC(3ab2c9c2) SHA1(30c556f4b9af982f33c24c8ccbaffbc837e39039) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "sfiii3-simm1_hc01.3", 0x00000, 0x200000, CRC(dffd42b2) SHA1(38f16df9f69f94cc58aa14fa1dab793d21520476) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii3-simm2.0", 0x00000, 0x200000, CRC(06eb969e) SHA1(d89f6a6585b76692d57d337f0f8186398fb056da) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii3-simm2.1", 0x00000, 0x200000, CRC(e7039f82) SHA1(8e81e66b5a4f45ae14b070a491bde47a6a74499f) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii3-simm2.2", 0x00000, 0x200000, CRC(645c96f7) SHA1(06d5a54874d4bf100b776131ec9060da209ad037) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii3-simm2.3", 0x00000, 0x200000, CRC(610efab1) SHA1(bbc21ed6ff6220ff6017a3f02ebd9a341fbc9040) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii3-simm3.0", 0x00000, 0x200000, CRC(7baa1f79) SHA1(3f409df28c24dd7221966b5340d59898ea756b6f) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii3-simm3.1", 0x00000, 0x200000, CRC(234bf8fe) SHA1(2191781ae4d726cab28de97f27efa4a13f3bdd69) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii3-simm3.2", 0x00000, 0x200000, CRC(d9ebc308) SHA1(af6a0dca77e5181c9f20533a06760a782c5fd51d) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii3-simm3.3", 0x00000, 0x200000, CRC(293cba77) SHA1(294604cacdc24261aec4d39e489de91c41fa1758) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii3-simm3.4", 0x00000, 0x200000, CRC(6055e747) SHA1(3813852c5a4a5355ef739ca8f0913bbd390b984b) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii3-simm3.5", 0x00000, 0x200000, CRC(499aa6fc) SHA1(5b9b6eab3e99ff3e1d7c1f50b9d8bc6a81f3f8a9) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii3-simm3.6", 0x00000, 0x200000, CRC(6c13879e) SHA1(de189b0b8f42bc7dd89983e62bc2ecb4237b3277) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii3-simm3.7", 0x00000, 0x200000, CRC(cf4f8ede) SHA1(e0fb68fcb0e445f824c62fa828d6e1dcd7e3683a) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii3-simm4.0", 0x00000, 0x200000, CRC(091fd5ba) SHA1(3327ad7c2623c119bf728af717ea2ce3b74673a9) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii3-simm4.1", 0x00000, 0x200000, CRC(0bca8917) SHA1(b7b284e2f16f46d46bcfaae779b232c5b980924f) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii3-simm4.2", 0x00000, 0x200000, CRC(a0fd578b) SHA1(100c9db9f00ecd88d518076f5a0822e6ac3695b3) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii3-simm4.3", 0x00000, 0x200000, CRC(4bf8c699) SHA1(2c0b4288b5ebc5e54d9e782dfc39eb8c78fd4c21) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii3-simm4.4", 0x00000, 0x200000, CRC(137b8785) SHA1(56a579520a8ce2abbf36be57777f024e80474eee) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii3-simm4.5", 0x00000, 0x200000, CRC(4fb70671) SHA1(9aba83c18cfc099a5ce18793119bff0c2b9c777f) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii3-simm4.6", 0x00000, 0x200000, CRC(832374a4) SHA1(c84629e32fbf47cb7b5b4ee7555bfc2ac9b3857f) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii3-simm4.7", 0x00000, 0x200000, CRC(1c88576d) SHA1(0f039944d0c2305999ed5dbd351c3eb87812dc3b) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii3-simm5.0", 0x00000, 0x200000, CRC(c67d9190) SHA1(d265475244099d0ec153059986f3445c7bd910a3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii3-simm5.1", 0x00000, 0x200000, CRC(6cb79868) SHA1(c94237f30e05bfcb2e23945530c812d9e4c73416) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii3-simm5.2", 0x00000, 0x200000, CRC(df69930e) SHA1(c76b7c559a1d5558138afbc796249efa2f49f6a8) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii3-simm5.3", 0x00000, 0x200000, CRC(333754e0) SHA1(4c18a569c26524a492ecd6f4c8b3c8e803a077d3) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii3-simm5.4", 0x00000, 0x200000, CRC(78f6d417) SHA1(a69577cc5399fcf0a24548661168f27f3e7e8e40) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii3-simm5.5", 0x00000, 0x200000, CRC(8ccad9b1) SHA1(f8bda399f87be2497b7ac39e9661f9863bf4f873) )
	ROM_REGION( 0x500000, "simm5.6", 0 )
	ROM_LOAD( "sfiii3-simm5_hc01.6", 0x00000, 0x454F4A, CRC(c59e5cc6) SHA1(6d3ca8a319e7f7debcd853d5862ffaa2f760ae5e) )
	ROM_REGION( 0x500000, "simm5.7", 0 )
	ROM_LOAD( "sfiii3-simm5_hc01.7", 0x00000, 0x454F4A, CRC(411d6285) SHA1(7cc58774db896801643d2d04e4c6dd956003e9f2) )

	ROM_REGION( 0x200000, "simm6.0", 0 )
	ROM_LOAD( "sfiii3-simm6.0", 0x00000, 0x200000, CRC(8da69042) SHA1(fd3d08295342635b2136e48d543c9350d287bb22) )
	ROM_REGION( 0x200000, "simm6.1", 0 )
	ROM_LOAD( "sfiii3-simm6.1", 0x00000, 0x200000, CRC(1c8c7ac4) SHA1(ac9f8353a4c356ef98aa7c226baba00b01f5a80f) )
	ROM_REGION( 0x200000, "simm6.2", 0 )
	ROM_LOAD( "sfiii3-simm6.2", 0x00000, 0x200000, CRC(a671341d) SHA1(636f4c04962bc1e1ddb29d2e01244b00389b234f) )
	ROM_REGION( 0x200000, "simm6.3", 0 )
	ROM_LOAD( "sfiii3-simm6.3", 0x00000, 0x200000, CRC(1a990249) SHA1(2acc639e2c0c53bf24096b8620eab090bc25d03b) )
	ROM_REGION( 0x200000, "simm6.4", 0 )
	ROM_LOAD( "sfiii3-simm6.4", 0x00000, 0x200000, CRC(20cb39ac) SHA1(7d13a0fea1ef719dd2ff77dfb547d53c6023cc9e) )
	ROM_REGION( 0x200000, "simm6.5", 0 )
	ROM_LOAD( "sfiii3-simm6.5", 0x00000, 0x200000, CRC(5f844b2f) SHA1(564e4934f89ed3b92a4c4874519f8f00f3b48696) )
	ROM_REGION( 0x200000, "simm6.6", 0 )
	ROM_LOAD( "sfiii3-simm6.6", 0x00000, 0x200000, CRC(450e8d28) SHA1(885db658132aa27926df617ec2d2a1f38abdbb60) )
	ROM_REGION( 0x200000, "simm6.7", 0 )
	ROM_LOAD( "sfiii3-simm6.7", 0x00000, 0x200000, CRC(cc5f4187) SHA1(248ddace21ed4736a56e92f77cc6ad219d7fef0b) )
ROM_END

ROM_START( sfiii3hc02 ) //sfiii3ws
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "sfiii3-simm1_hc02.0", 0x00000, 0x200000, CRC(16843828) SHA1(b2e3e47ecca1422cb7adc1a0aab9120fa44fbef0) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "sfiii3-simm1_hc02.1", 0x00000, 0x200000, CRC(0d084fbc) SHA1(750602b92ea3c994d81e91f09031081bc465a8a4) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "sfiii3-simm1_hc02.2", 0x00000, 0x200000, CRC(3f6d1f52) SHA1(c50a2f327adb38ece5a572ac453732de02559d70) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "sfiii3-simm1_hc02.3", 0x00000, 0x200000, CRC(3ff7516b) SHA1(2ff27926017f81a9330c16ed9d3559e71263b03d) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii3-simm2.0", 0x00000, 0x200000, CRC(06eb969e) SHA1(d89f6a6585b76692d57d337f0f8186398fb056da) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii3-simm2.1", 0x00000, 0x200000, CRC(e7039f82) SHA1(8e81e66b5a4f45ae14b070a491bde47a6a74499f) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii3-simm2.2", 0x00000, 0x200000, CRC(645c96f7) SHA1(06d5a54874d4bf100b776131ec9060da209ad037) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii3-simm2.3", 0x00000, 0x200000, CRC(610efab1) SHA1(bbc21ed6ff6220ff6017a3f02ebd9a341fbc9040) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii3-simm3.0", 0x00000, 0x200000, CRC(7baa1f79) SHA1(3f409df28c24dd7221966b5340d59898ea756b6f) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii3-simm3.1", 0x00000, 0x200000, CRC(234bf8fe) SHA1(2191781ae4d726cab28de97f27efa4a13f3bdd69) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii3-simm3.2", 0x00000, 0x200000, CRC(d9ebc308) SHA1(af6a0dca77e5181c9f20533a06760a782c5fd51d) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii3-simm3.3", 0x00000, 0x200000, CRC(293cba77) SHA1(294604cacdc24261aec4d39e489de91c41fa1758) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii3-simm3.4", 0x00000, 0x200000, CRC(6055e747) SHA1(3813852c5a4a5355ef739ca8f0913bbd390b984b) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii3-simm3.5", 0x00000, 0x200000, CRC(499aa6fc) SHA1(5b9b6eab3e99ff3e1d7c1f50b9d8bc6a81f3f8a9) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii3-simm3.6", 0x00000, 0x200000, CRC(6c13879e) SHA1(de189b0b8f42bc7dd89983e62bc2ecb4237b3277) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii3-simm3.7", 0x00000, 0x200000, CRC(cf4f8ede) SHA1(e0fb68fcb0e445f824c62fa828d6e1dcd7e3683a) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii3-simm4.0", 0x00000, 0x200000, CRC(091fd5ba) SHA1(3327ad7c2623c119bf728af717ea2ce3b74673a9) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii3-simm4.1", 0x00000, 0x200000, CRC(0bca8917) SHA1(b7b284e2f16f46d46bcfaae779b232c5b980924f) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii3-simm4.2", 0x00000, 0x200000, CRC(a0fd578b) SHA1(100c9db9f00ecd88d518076f5a0822e6ac3695b3) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii3-simm4.3", 0x00000, 0x200000, CRC(4bf8c699) SHA1(2c0b4288b5ebc5e54d9e782dfc39eb8c78fd4c21) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii3-simm4.4", 0x00000, 0x200000, CRC(137b8785) SHA1(56a579520a8ce2abbf36be57777f024e80474eee) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii3-simm4.5", 0x00000, 0x200000, CRC(4fb70671) SHA1(9aba83c18cfc099a5ce18793119bff0c2b9c777f) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii3-simm4.6", 0x00000, 0x200000, CRC(832374a4) SHA1(c84629e32fbf47cb7b5b4ee7555bfc2ac9b3857f) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii3-simm4.7", 0x00000, 0x200000, CRC(1c88576d) SHA1(0f039944d0c2305999ed5dbd351c3eb87812dc3b) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii3-simm5.0", 0x00000, 0x200000, CRC(c67d9190) SHA1(d265475244099d0ec153059986f3445c7bd910a3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii3-simm5.1", 0x00000, 0x200000, CRC(6cb79868) SHA1(c94237f30e05bfcb2e23945530c812d9e4c73416) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii3-simm5.2", 0x00000, 0x200000, CRC(df69930e) SHA1(c76b7c559a1d5558138afbc796249efa2f49f6a8) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii3-simm5.3", 0x00000, 0x200000, CRC(333754e0) SHA1(4c18a569c26524a492ecd6f4c8b3c8e803a077d3) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii3-simm5.4", 0x00000, 0x200000, CRC(78f6d417) SHA1(a69577cc5399fcf0a24548661168f27f3e7e8e40) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii3-simm5.5", 0x00000, 0x200000, CRC(8ccad9b1) SHA1(f8bda399f87be2497b7ac39e9661f9863bf4f873) )
	ROM_REGION( 0x500000, "simm5.6", 0 )
	ROM_LOAD( "sfiii3-simm5_hc01.6", 0x00000, 0x454F4A, CRC(c59e5cc6) SHA1(6d3ca8a319e7f7debcd853d5862ffaa2f760ae5e) )
	ROM_REGION( 0x500000, "simm5.7", 0 )
	ROM_LOAD( "sfiii3-simm5_hc01.7", 0x00000, 0x454F4A, CRC(411d6285) SHA1(7cc58774db896801643d2d04e4c6dd956003e9f2) )

	ROM_REGION( 0x200000, "simm6.0", 0 )
	ROM_LOAD( "sfiii3-simm6.0", 0x00000, 0x200000, CRC(8da69042) SHA1(fd3d08295342635b2136e48d543c9350d287bb22) )
	ROM_REGION( 0x200000, "simm6.1", 0 )
	ROM_LOAD( "sfiii3-simm6.1", 0x00000, 0x200000, CRC(1c8c7ac4) SHA1(ac9f8353a4c356ef98aa7c226baba00b01f5a80f) )
	ROM_REGION( 0x200000, "simm6.2", 0 )
	ROM_LOAD( "sfiii3-simm6.2", 0x00000, 0x200000, CRC(a671341d) SHA1(636f4c04962bc1e1ddb29d2e01244b00389b234f) )
	ROM_REGION( 0x200000, "simm6.3", 0 )
	ROM_LOAD( "sfiii3-simm6.3", 0x00000, 0x200000, CRC(1a990249) SHA1(2acc639e2c0c53bf24096b8620eab090bc25d03b) )
	ROM_REGION( 0x200000, "simm6.4", 0 )
	ROM_LOAD( "sfiii3-simm6.4", 0x00000, 0x200000, CRC(20cb39ac) SHA1(7d13a0fea1ef719dd2ff77dfb547d53c6023cc9e) )
	ROM_REGION( 0x200000, "simm6.5", 0 )
	ROM_LOAD( "sfiii3-simm6.5", 0x00000, 0x200000, CRC(5f844b2f) SHA1(564e4934f89ed3b92a4c4874519f8f00f3b48696) )
	ROM_REGION( 0x200000, "simm6.6", 0 )
	ROM_LOAD( "sfiii3-simm6.6", 0x00000, 0x200000, CRC(450e8d28) SHA1(885db658132aa27926df617ec2d2a1f38abdbb60) )
	ROM_REGION( 0x200000, "simm6.7", 0 )
	ROM_LOAD( "sfiii3-simm6.7", 0x00000, 0x200000, CRC(cc5f4187) SHA1(248ddace21ed4736a56e92f77cc6ad219d7fef0b) )
ROM_END

ROM_START( sfiii3hc03 )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "sfiii3-simm1_hc03.0", 0x00000, 0x200000, CRC(83e35a6c) SHA1(0598cb7203178f17a8994a9e24b80bdce29480f8) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "sfiii3-simm1_hc03.1", 0x00000, 0x200000, CRC(e83f927b) SHA1(551090cfce16f602929c0a76266120cd660c50e8) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "sfiii3-simm1_hc03.2", 0x00000, 0x200000, CRC(Cd6367b3) SHA1(C0cff444a79edec3044f8da05bc87981c8a00d00) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "sfiii3-simm1_hc03.3", 0x00000, 0x200000, CRC(E5c4245a) SHA1(9cba661d231aa9b5e37eea9b347b2e92eaa51dce) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii3-simm2.0", 0x00000, 0x200000, CRC(06eb969e) SHA1(d89f6a6585b76692d57d337f0f8186398fb056da) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii3-simm2.1", 0x00000, 0x200000, CRC(e7039f82) SHA1(8e81e66b5a4f45ae14b070a491bde47a6a74499f) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii3-simm2.2", 0x00000, 0x200000, CRC(645c96f7) SHA1(06d5a54874d4bf100b776131ec9060da209ad037) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii3-simm2.3", 0x00000, 0x200000, CRC(610efab1) SHA1(bbc21ed6ff6220ff6017a3f02ebd9a341fbc9040) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii3-simm3.0", 0x00000, 0x200000, CRC(7baa1f79) SHA1(3f409df28c24dd7221966b5340d59898ea756b6f) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii3-simm3.1", 0x00000, 0x200000, CRC(234bf8fe) SHA1(2191781ae4d726cab28de97f27efa4a13f3bdd69) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii3-simm3.2", 0x00000, 0x200000, CRC(d9ebc308) SHA1(af6a0dca77e5181c9f20533a06760a782c5fd51d) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii3-simm3.3", 0x00000, 0x200000, CRC(293cba77) SHA1(294604cacdc24261aec4d39e489de91c41fa1758) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii3-simm3.4", 0x00000, 0x200000, CRC(6055e747) SHA1(3813852c5a4a5355ef739ca8f0913bbd390b984b) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii3-simm3.5", 0x00000, 0x200000, CRC(499aa6fc) SHA1(5b9b6eab3e99ff3e1d7c1f50b9d8bc6a81f3f8a9) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii3-simm3.6", 0x00000, 0x200000, CRC(6c13879e) SHA1(de189b0b8f42bc7dd89983e62bc2ecb4237b3277) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii3-simm3.7", 0x00000, 0x200000, CRC(cf4f8ede) SHA1(e0fb68fcb0e445f824c62fa828d6e1dcd7e3683a) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii3-simm4.0", 0x00000, 0x200000, CRC(091fd5ba) SHA1(3327ad7c2623c119bf728af717ea2ce3b74673a9) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii3-simm4.1", 0x00000, 0x200000, CRC(0bca8917) SHA1(b7b284e2f16f46d46bcfaae779b232c5b980924f) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii3-simm4.2", 0x00000, 0x200000, CRC(a0fd578b) SHA1(100c9db9f00ecd88d518076f5a0822e6ac3695b3) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii3-simm4.3", 0x00000, 0x200000, CRC(4bf8c699) SHA1(2c0b4288b5ebc5e54d9e782dfc39eb8c78fd4c21) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii3-simm4.4", 0x00000, 0x200000, CRC(137b8785) SHA1(56a579520a8ce2abbf36be57777f024e80474eee) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii3-simm4.5", 0x00000, 0x200000, CRC(4fb70671) SHA1(9aba83c18cfc099a5ce18793119bff0c2b9c777f) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii3-simm4.6", 0x00000, 0x200000, CRC(832374a4) SHA1(c84629e32fbf47cb7b5b4ee7555bfc2ac9b3857f) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii3-simm4.7", 0x00000, 0x200000, CRC(1c88576d) SHA1(0f039944d0c2305999ed5dbd351c3eb87812dc3b) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii3-simm5.0", 0x00000, 0x200000, CRC(c67d9190) SHA1(d265475244099d0ec153059986f3445c7bd910a3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii3-simm5.1", 0x00000, 0x200000, CRC(6cb79868) SHA1(c94237f30e05bfcb2e23945530c812d9e4c73416) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii3-simm5.2", 0x00000, 0x200000, CRC(df69930e) SHA1(c76b7c559a1d5558138afbc796249efa2f49f6a8) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii3-simm5.3", 0x00000, 0x200000, CRC(333754e0) SHA1(4c18a569c26524a492ecd6f4c8b3c8e803a077d3) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii3-simm5.4", 0x00000, 0x200000, CRC(78f6d417) SHA1(a69577cc5399fcf0a24548661168f27f3e7e8e40) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii3-simm5.5", 0x00000, 0x200000, CRC(8ccad9b1) SHA1(f8bda399f87be2497b7ac39e9661f9863bf4f873) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "sfiii3-simm5.6", 0x00000, 0x200000, CRC(85de59e5) SHA1(748b5c91f15777b85d8c1d35b685cd90d3185ec6) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "sfiii3-simm5.7", 0x00000, 0x200000, CRC(ee7e29b3) SHA1(63dc30c6904ca2f58d229249bee5eef51fafa158) )

	ROM_REGION( 0x200000, "simm6.0", 0 )
	ROM_LOAD( "sfiii3-simm6.0", 0x00000, 0x200000, CRC(8da69042) SHA1(fd3d08295342635b2136e48d543c9350d287bb22) )
	ROM_REGION( 0x200000, "simm6.1", 0 )
	ROM_LOAD( "sfiii3-simm6.1", 0x00000, 0x200000, CRC(1c8c7ac4) SHA1(ac9f8353a4c356ef98aa7c226baba00b01f5a80f) )
	ROM_REGION( 0x200000, "simm6.2", 0 )
	ROM_LOAD( "sfiii3-simm6.2", 0x00000, 0x200000, CRC(a671341d) SHA1(636f4c04962bc1e1ddb29d2e01244b00389b234f) )
	ROM_REGION( 0x200000, "simm6.3", 0 )
	ROM_LOAD( "sfiii3-simm6.3", 0x00000, 0x200000, CRC(1a990249) SHA1(2acc639e2c0c53bf24096b8620eab090bc25d03b) )
	ROM_REGION( 0x200000, "simm6.4", 0 )
	ROM_LOAD( "sfiii3-simm6.4", 0x00000, 0x200000, CRC(20cb39ac) SHA1(7d13a0fea1ef719dd2ff77dfb547d53c6023cc9e) )
	ROM_REGION( 0x200000, "simm6.5", 0 )
	ROM_LOAD( "sfiii3-simm6.5", 0x00000, 0x200000, CRC(5f844b2f) SHA1(564e4934f89ed3b92a4c4874519f8f00f3b48696) )
	ROM_REGION( 0x200000, "simm6.6", 0 )
	ROM_LOAD( "sfiii3-simm6.6", 0x00000, 0x200000, CRC(450e8d28) SHA1(885db658132aa27926df617ec2d2a1f38abdbb60) )
	ROM_REGION( 0x200000, "simm6.7", 0 )
	ROM_LOAD( "sfiii3-simm6.7", 0x00000, 0x200000, CRC(cc5f4187) SHA1(248ddace21ed4736a56e92f77cc6ad219d7fef0b) )
ROM_END

ROM_START( sfiii3hc04 )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x500000, "simm1.0", 0 )
	ROM_LOAD( "sfiii3-simm1_hc04.0", 0x00000, 0x454F4B, CRC(11dfd3cd) SHA1(de7cea6021b0e92586531990c70f035d327f581e) )
	ROM_REGION( 0x500000, "simm1.1", 0 )
	ROM_LOAD( "sfiii3-simm1_hc04.1", 0x00000, 0x454F4C, CRC(c50585e6) SHA1(9486ae732e229f6bfa6bd4ebdc49802a3cfa5649) )
	ROM_REGION( 0x500000, "simm1.2", 0 )
	ROM_LOAD( "sfiii3-simm1_hc04.2", 0x00000, 0x454F4F, CRC(8e011d9b) SHA1(65ec49d694924f8283e53adc3877eab851dd49f0) )
	ROM_REGION( 0x500000, "simm1.3", 0 )
	ROM_LOAD( "sfiii3-simm1_hc04.3", 0x00000, 0x454F4B, CRC(dca8d92f) SHA1(bae290f473132df058248c7b012a5e602866a4a2) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii3-simm2.0",  0x00000, 0x200000, CRC(06eb969e) SHA1(d89f6a6585b76692d57d337f0f8186398fb056da) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii3-simm2.1",  0x00000, 0x200000, CRC(e7039f82) SHA1(8e81e66b5a4f45ae14b070a491bde47a6a74499f) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii3-simm2.2",  0x00000, 0x200000, CRC(645c96f7) SHA1(06d5a54874d4bf100b776131ec9060da209ad037) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii3-simm2.3",  0x00000, 0x200000, CRC(610efab1) SHA1(bbc21ed6ff6220ff6017a3f02ebd9a341fbc9040) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii3-simm3.0",  0x00000, 0x200000, CRC(7baa1f79) SHA1(3f409df28c24dd7221966b5340d59898ea756b6f) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii3-simm3.1",  0x00000, 0x200000, CRC(234bf8fe) SHA1(2191781ae4d726cab28de97f27efa4a13f3bdd69) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii3-simm3.2",  0x00000, 0x200000, CRC(d9ebc308) SHA1(af6a0dca77e5181c9f20533a06760a782c5fd51d) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii3-simm3.3",  0x00000, 0x200000, CRC(293cba77) SHA1(294604cacdc24261aec4d39e489de91c41fa1758) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii3-simm3.4",  0x00000, 0x200000, CRC(6055e747) SHA1(3813852c5a4a5355ef739ca8f0913bbd390b984b) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii3-simm3.5",  0x00000, 0x200000, CRC(499aa6fc) SHA1(5b9b6eab3e99ff3e1d7c1f50b9d8bc6a81f3f8a9) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii3-simm3.6",  0x00000, 0x200000, CRC(6c13879e) SHA1(de189b0b8f42bc7dd89983e62bc2ecb4237b3277) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii3-simm3.7",  0x00000, 0x200000, CRC(cf4f8ede) SHA1(e0fb68fcb0e445f824c62fa828d6e1dcd7e3683a) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii3-simm4.0",  0x00000, 0x200000, CRC(091fd5ba) SHA1(3327ad7c2623c119bf728af717ea2ce3b74673a9) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii3-simm4.1",  0x00000, 0x200000, CRC(0bca8917) SHA1(b7b284e2f16f46d46bcfaae779b232c5b980924f) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii3-simm4.2",  0x00000, 0x200000, CRC(a0fd578b) SHA1(100c9db9f00ecd88d518076f5a0822e6ac3695b3) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii3-simm4.3",  0x00000, 0x200000, CRC(4bf8c699) SHA1(2c0b4288b5ebc5e54d9e782dfc39eb8c78fd4c21) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii3-simm4.4",  0x00000, 0x200000, CRC(137b8785) SHA1(56a579520a8ce2abbf36be57777f024e80474eee) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii3-simm4.5",  0x00000, 0x200000, CRC(4fb70671) SHA1(9aba83c18cfc099a5ce18793119bff0c2b9c777f) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii3-simm4.6",  0x00000, 0x200000, CRC(832374a4) SHA1(c84629e32fbf47cb7b5b4ee7555bfc2ac9b3857f) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii3-simm4.7",  0x00000, 0x200000, CRC(1c88576d) SHA1(0f039944d0c2305999ed5dbd351c3eb87812dc3b) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii3-simm5.0",  0x00000, 0x200000, CRC(c67d9190) SHA1(d265475244099d0ec153059986f3445c7bd910a3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii3-simm5.1",  0x00000, 0x200000, CRC(6cb79868) SHA1(c94237f30e05bfcb2e23945530c812d9e4c73416) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii3-simm5.2",  0x00000, 0x200000, CRC(df69930e) SHA1(c76b7c559a1d5558138afbc796249efa2f49f6a8) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii3-simm5.3",  0x00000, 0x200000, CRC(333754e0) SHA1(4c18a569c26524a492ecd6f4c8b3c8e803a077d3) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii3-simm5.4",  0x00000, 0x200000, CRC(78f6d417) SHA1(a69577cc5399fcf0a24548661168f27f3e7e8e40) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii3-simm5.5",  0x00000, 0x200000, CRC(8ccad9b1) SHA1(f8bda399f87be2497b7ac39e9661f9863bf4f873) )
	ROM_REGION( 0x500000, "simm5.6", 0 )
	ROM_LOAD( "sfiii3-simm5_hc01.6", 0x00000, 0x454F4A, CRC(c59e5cc6) SHA1(6d3ca8a319e7f7debcd853d5862ffaa2f760ae5e) )
	ROM_REGION( 0x500000, "simm5.7", 0 )
	ROM_LOAD( "sfiii3-simm5_hc01.7", 0x00000, 0x454F4A, CRC(411d6285) SHA1(7cc58774db896801643d2d04e4c6dd956003e9f2) )

	ROM_REGION( 0x200000, "simm6.0", 0 )
	ROM_LOAD( "sfiii3-simm6.0",  0x00000, 0x200000, CRC(8da69042) SHA1(fd3d08295342635b2136e48d543c9350d287bb22) )
	ROM_REGION( 0x200000, "simm6.1", 0 )
	ROM_LOAD( "sfiii3-simm6.1",  0x00000, 0x200000, CRC(1c8c7ac4) SHA1(ac9f8353a4c356ef98aa7c226baba00b01f5a80f) )
	ROM_REGION( 0x200000, "simm6.2", 0 )
	ROM_LOAD( "sfiii3-simm6.2",  0x00000, 0x200000, CRC(a671341d) SHA1(636f4c04962bc1e1ddb29d2e01244b00389b234f) )
	ROM_REGION( 0x200000, "simm6.3", 0 )
	ROM_LOAD( "sfiii3-simm6.3",  0x00000, 0x200000, CRC(1a990249) SHA1(2acc639e2c0c53bf24096b8620eab090bc25d03b) )
	ROM_REGION( 0x200000, "simm6.4", 0 )
	ROM_LOAD( "sfiii3-simm6.4",  0x00000, 0x200000, CRC(20cb39ac) SHA1(7d13a0fea1ef719dd2ff77dfb547d53c6023cc9e) )
	ROM_REGION( 0x200000, "simm6.5", 0 )
	ROM_LOAD( "sfiii3-simm6.5",  0x00000, 0x200000, CRC(5f844b2f) SHA1(564e4934f89ed3b92a4c4874519f8f00f3b48696) )
	ROM_REGION( 0x200000, "simm6.6", 0 )
	ROM_LOAD( "sfiii3-simm6.6",  0x00000, 0x200000, CRC(450e8d28) SHA1(885db658132aa27926df617ec2d2a1f38abdbb60) )
	ROM_REGION( 0x200000, "simm6.7", 0 )
	ROM_LOAD( "sfiii3-simm6.7",  0x00000, 0x200000, CRC(cc5f4187) SHA1(248ddace21ed4736a56e92f77cc6ad219d7fef0b) )
ROM_END

ROM_START( sfiii3hc05 ) //sfiii4n
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x500000, "simm1.0", 0 )
	ROM_LOAD( "sfiii3-simm1_hc05.0", 0x00000, 0x454F4B, CRC(11dfd3cd) SHA1(29b259d595cce0051a903ea8b46f054c2a9fb8b2) )
	ROM_REGION( 0x500000, "simm1.1", 0 )
	ROM_LOAD( "sfiii3-simm1_hc05.1", 0x00000, 0x454F4C, CRC(c50585e6) SHA1(6a6fc852c5de629e28547223ec00405b2469bca1) )
	ROM_REGION( 0x500000, "simm1.2", 0 )
	ROM_LOAD( "sfiii3-simm1_hc05.2", 0x00000, 0x454F4B, CRC(8e011d9b) SHA1(6d41632c6b4295058fc2e923ef808b22170f29b5) )
	ROM_REGION( 0x500000, "simm1.3", 0 )
	ROM_LOAD( "sfiii3-simm1_hc05.3", 0x00000, 0x454F4B, CRC(dca8d92f) SHA1(7cd07ddc75f943f5e5c9dcc1bc4e33459e97fdf3) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii3-simm2.0", 0x00000, 0x200000, CRC(06eb969e) SHA1(d89f6a6585b76692d57d337f0f8186398fb056da) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii3-simm2.1", 0x00000, 0x200000, CRC(e7039f82) SHA1(8e81e66b5a4f45ae14b070a491bde47a6a74499f) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii3-simm2.2", 0x00000, 0x200000, CRC(645c96f7) SHA1(06d5a54874d4bf100b776131ec9060da209ad037) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii3-simm2.3", 0x00000, 0x200000, CRC(610efab1) SHA1(bbc21ed6ff6220ff6017a3f02ebd9a341fbc9040) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii3-simm3.0", 0x00000, 0x200000, CRC(7baa1f79) SHA1(3f409df28c24dd7221966b5340d59898ea756b6f) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii3-simm3.1", 0x00000, 0x200000, CRC(234bf8fe) SHA1(2191781ae4d726cab28de97f27efa4a13f3bdd69) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii3-simm3.2", 0x00000, 0x200000, CRC(d9ebc308) SHA1(af6a0dca77e5181c9f20533a06760a782c5fd51d) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii3-simm3.3", 0x00000, 0x200000, CRC(293cba77) SHA1(294604cacdc24261aec4d39e489de91c41fa1758) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii3-simm3.4", 0x00000, 0x200000, CRC(6055e747) SHA1(3813852c5a4a5355ef739ca8f0913bbd390b984b) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii3-simm3.5", 0x00000, 0x200000, CRC(499aa6fc) SHA1(5b9b6eab3e99ff3e1d7c1f50b9d8bc6a81f3f8a9) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii3-simm3.6", 0x00000, 0x200000, CRC(6c13879e) SHA1(de189b0b8f42bc7dd89983e62bc2ecb4237b3277) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii3-simm3.7", 0x00000, 0x200000, CRC(cf4f8ede) SHA1(e0fb68fcb0e445f824c62fa828d6e1dcd7e3683a) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii3-simm4.0", 0x00000, 0x200000, CRC(091fd5ba) SHA1(3327ad7c2623c119bf728af717ea2ce3b74673a9) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii3-simm4.1", 0x00000, 0x200000, CRC(0bca8917) SHA1(b7b284e2f16f46d46bcfaae779b232c5b980924f) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii3-simm4.2", 0x00000, 0x200000, CRC(a0fd578b) SHA1(100c9db9f00ecd88d518076f5a0822e6ac3695b3) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii3-simm4.3", 0x00000, 0x200000, CRC(4bf8c699) SHA1(2c0b4288b5ebc5e54d9e782dfc39eb8c78fd4c21) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii3-simm4.4", 0x00000, 0x200000, CRC(137b8785) SHA1(56a579520a8ce2abbf36be57777f024e80474eee) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii3-simm4.5", 0x00000, 0x200000, CRC(4fb70671) SHA1(9aba83c18cfc099a5ce18793119bff0c2b9c777f) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii3-simm4.6", 0x00000, 0x200000, CRC(832374a4) SHA1(c84629e32fbf47cb7b5b4ee7555bfc2ac9b3857f) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii3-simm4.7", 0x00000, 0x200000, CRC(1c88576d) SHA1(0f039944d0c2305999ed5dbd351c3eb87812dc3b) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii3-simm5.0", 0x00000, 0x200000, CRC(c67d9190) SHA1(d265475244099d0ec153059986f3445c7bd910a3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii3-simm5.1", 0x00000, 0x200000, CRC(6cb79868) SHA1(c94237f30e05bfcb2e23945530c812d9e4c73416) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii3-simm5.2", 0x00000, 0x200000, CRC(df69930e) SHA1(c76b7c559a1d5558138afbc796249efa2f49f6a8) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii3-simm5.3", 0x00000, 0x200000, CRC(333754e0) SHA1(4c18a569c26524a492ecd6f4c8b3c8e803a077d3) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii3-simm5_hc05.4", 0x00000, 0x200000, CRC(Ce54bff9) SHA1(0331a0de8ac42dd3df800eaf653922458e2ec8b1) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii3-simm5_hc05.5", 0x00000, 0x200000, CRC(15c325b2) SHA1(A35303784f8b8bdc6596ab11ca03d9a36fd70ea1) )
	ROM_REGION( 0x500000, "simm5.6", 0 )
	ROM_LOAD( "sfiii3-simm5_hc05.6", 0x00000, 0x454F4A, CRC(e6f6c399) SHA1(423fba19e2262081dde61e9e8e0beedb40f95d35) )
	ROM_REGION( 0x500000, "simm5.7", 0 )
	ROM_LOAD( "sfiii3-simm5_hc05.7", 0x00000, 0x454F4A, CRC(37ab0379) SHA1(eeb64c1374d8f2272ba32d4afa46ef191a82f7ce) )

	ROM_REGION( 0x200000, "simm6.0", 0 )
	ROM_LOAD( "sfiii3-simm6.0", 0x00000, 0x200000, CRC(8da69042) SHA1(fd3d08295342635b2136e48d543c9350d287bb22) )
	ROM_REGION( 0x200000, "simm6.1", 0 )
	ROM_LOAD( "sfiii3-simm6.1", 0x00000, 0x200000, CRC(1c8c7ac4) SHA1(ac9f8353a4c356ef98aa7c226baba00b01f5a80f) )
	ROM_REGION( 0x200000, "simm6.2", 0 )
	ROM_LOAD( "sfiii3-simm6.2", 0x00000, 0x200000, CRC(a671341d) SHA1(636f4c04962bc1e1ddb29d2e01244b00389b234f) )
	ROM_REGION( 0x200000, "simm6.3", 0 )
	ROM_LOAD( "sfiii3-simm6.3", 0x00000, 0x200000, CRC(1a990249) SHA1(2acc639e2c0c53bf24096b8620eab090bc25d03b) )
	ROM_REGION( 0x200000, "simm6.4", 0 )
	ROM_LOAD( "sfiii3-simm6.4", 0x00000, 0x200000, CRC(20cb39ac) SHA1(7d13a0fea1ef719dd2ff77dfb547d53c6023cc9e) )
	ROM_REGION( 0x200000, "simm6.5", 0 )
	ROM_LOAD( "sfiii3-simm6.5", 0x00000, 0x200000, CRC(5f844b2f) SHA1(564e4934f89ed3b92a4c4874519f8f00f3b48696) )
	ROM_REGION( 0x200000, "simm6.6", 0 )
	ROM_LOAD( "sfiii3-simm6.6", 0x00000, 0x200000, CRC(450e8d28) SHA1(885db658132aa27926df617ec2d2a1f38abdbb60) )
	ROM_REGION( 0x200000, "simm6.7", 0 )
	ROM_LOAD( "sfiii3-simm6.7", 0x00000, 0x200000, CRC(cc5f4187) SHA1(248ddace21ed4736a56e92f77cc6ad219d7fef0b) )
ROM_END

ROM_START( sfiii3hc06 ) //sfiii4n
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "sfiii3-simm1_hc06.0", 0x00000, 0x200000, CRC(ca97f95e) SHA1(624f1af8c3722c0554a65bfb4f0682ed66a70b55) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "sfiii3-simm1_hc06.1", 0x00000, 0x200000, CRC(5bc7faa6) SHA1(291b6102d8ad7478ea45e73d34ad8d65332beaf0) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "sfiii3-simm1_hc06.2", 0x00000, 0x200000, CRC(ec2eaa29) SHA1(981d452f15da43d4577339ab5799c7561f298d62) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "sfiii3-simm1_hc06.3", 0x00000, 0x200000, CRC(41c4ce7c) SHA1(273f21735200becb0da06ab3e40023918df2a062) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii3-simm2.0", 0x00000, 0x200000, CRC(06eb969e) SHA1(d89f6a6585b76692d57d337f0f8186398fb056da) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii3-simm2.1", 0x00000, 0x200000, CRC(e7039f82) SHA1(8e81e66b5a4f45ae14b070a491bde47a6a74499f) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii3-simm2.2", 0x00000, 0x200000, CRC(645c96f7) SHA1(06d5a54874d4bf100b776131ec9060da209ad037) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii3-simm2.3", 0x00000, 0x200000, CRC(610efab1) SHA1(bbc21ed6ff6220ff6017a3f02ebd9a341fbc9040) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii3-simm3.0", 0x00000, 0x200000, CRC(7baa1f79) SHA1(3f409df28c24dd7221966b5340d59898ea756b6f) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii3-simm3.1", 0x00000, 0x200000, CRC(234bf8fe) SHA1(2191781ae4d726cab28de97f27efa4a13f3bdd69) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii3-simm3.2", 0x00000, 0x200000, CRC(d9ebc308) SHA1(af6a0dca77e5181c9f20533a06760a782c5fd51d) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii3-simm3.3", 0x00000, 0x200000, CRC(293cba77) SHA1(294604cacdc24261aec4d39e489de91c41fa1758) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii3-simm3.4", 0x00000, 0x200000, CRC(6055e747) SHA1(3813852c5a4a5355ef739ca8f0913bbd390b984b) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii3-simm3.5", 0x00000, 0x200000, CRC(499aa6fc) SHA1(5b9b6eab3e99ff3e1d7c1f50b9d8bc6a81f3f8a9) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii3-simm3.6", 0x00000, 0x200000, CRC(6c13879e) SHA1(de189b0b8f42bc7dd89983e62bc2ecb4237b3277) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii3-simm3.7", 0x00000, 0x200000, CRC(cf4f8ede) SHA1(e0fb68fcb0e445f824c62fa828d6e1dcd7e3683a) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii3-simm4.0", 0x00000, 0x200000, CRC(091fd5ba) SHA1(3327ad7c2623c119bf728af717ea2ce3b74673a9) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii3-simm4.1", 0x00000, 0x200000, CRC(0bca8917) SHA1(b7b284e2f16f46d46bcfaae779b232c5b980924f) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii3-simm4.2", 0x00000, 0x200000, CRC(a0fd578b) SHA1(100c9db9f00ecd88d518076f5a0822e6ac3695b3) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii3-simm4.3", 0x00000, 0x200000, CRC(4bf8c699) SHA1(2c0b4288b5ebc5e54d9e782dfc39eb8c78fd4c21) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii3-simm4.4", 0x00000, 0x200000, CRC(137b8785) SHA1(56a579520a8ce2abbf36be57777f024e80474eee) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii3-simm4.5", 0x00000, 0x200000, CRC(4fb70671) SHA1(9aba83c18cfc099a5ce18793119bff0c2b9c777f) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii3-simm4.6", 0x00000, 0x200000, CRC(832374a4) SHA1(c84629e32fbf47cb7b5b4ee7555bfc2ac9b3857f) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii3-simm4.7", 0x00000, 0x200000, CRC(1c88576d) SHA1(0f039944d0c2305999ed5dbd351c3eb87812dc3b) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii3-simm5.0", 0x00000, 0x200000, CRC(c67d9190) SHA1(d265475244099d0ec153059986f3445c7bd910a3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii3-simm5.1", 0x00000, 0x200000, CRC(6cb79868) SHA1(c94237f30e05bfcb2e23945530c812d9e4c73416) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii3-simm5.2", 0x00000, 0x200000, CRC(df69930e) SHA1(c76b7c559a1d5558138afbc796249efa2f49f6a8) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii3-simm5.3", 0x00000, 0x200000, CRC(333754e0) SHA1(4c18a569c26524a492ecd6f4c8b3c8e803a077d3) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii3-simm5.4", 0x00000, 0x200000, CRC(78f6d417) SHA1(a69577cc5399fcf0a24548661168f27f3e7e8e40) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii3-simm5.5", 0x00000, 0x200000, CRC(8ccad9b1) SHA1(f8bda399f87be2497b7ac39e9661f9863bf4f873) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "sfiii3-simm5_hc06.6", 0x00000, 0x200000, CRC(e9b61a56) SHA1(9277ac5da4715aa5325ae9f8c055f1e826b4ce54) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "sfiii3-simm5_hc06.7", 0x00000, 0x200000, CRC(8db3a249) SHA1(db38963ce011535a95f11426c17fb3eeda300917) )

	ROM_REGION( 0x200000, "simm6.0", 0 )
	ROM_LOAD( "sfiii3-simm6.0", 0x00000, 0x200000, CRC(8da69042) SHA1(fd3d08295342635b2136e48d543c9350d287bb22) )
	ROM_REGION( 0x200000, "simm6.1", 0 )
	ROM_LOAD( "sfiii3-simm6.1", 0x00000, 0x200000, CRC(1c8c7ac4) SHA1(ac9f8353a4c356ef98aa7c226baba00b01f5a80f) )
	ROM_REGION( 0x200000, "simm6.2", 0 )
	ROM_LOAD( "sfiii3-simm6.2", 0x00000, 0x200000, CRC(a671341d) SHA1(636f4c04962bc1e1ddb29d2e01244b00389b234f) )
	ROM_REGION( 0x200000, "simm6.3", 0 )
	ROM_LOAD( "sfiii3-simm6.3", 0x00000, 0x200000, CRC(1a990249) SHA1(2acc639e2c0c53bf24096b8620eab090bc25d03b) )
	ROM_REGION( 0x200000, "simm6.4", 0 )
	ROM_LOAD( "sfiii3-simm6.4", 0x00000, 0x200000, CRC(20cb39ac) SHA1(7d13a0fea1ef719dd2ff77dfb547d53c6023cc9e) )
	ROM_REGION( 0x200000, "simm6.5", 0 )
	ROM_LOAD( "sfiii3-simm6.5", 0x00000, 0x200000, CRC(5f844b2f) SHA1(564e4934f89ed3b92a4c4874519f8f00f3b48696) )
	ROM_REGION( 0x200000, "simm6.6", 0 )
	ROM_LOAD( "sfiii3-simm6.6", 0x00000, 0x200000, CRC(450e8d28) SHA1(885db658132aa27926df617ec2d2a1f38abdbb60) )
	ROM_REGION( 0x200000, "simm6.7", 0 )
	ROM_LOAD( "sfiii3-simm6.7", 0x00000, 0x200000, CRC(cc5f4187) SHA1(248ddace21ed4736a56e92f77cc6ad219d7fef0b) )
ROM_END

ROM_START( sfiii3hc07 )
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x200000, "simm1.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm1.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm2.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm3.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm4.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm5.7", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm6.0", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm6.1", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm6.2", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm6.3", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm6.4", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm6.5", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm6.6", ROMREGION_ERASEFF )
	ROM_REGION( 0x200000, "simm6.7", ROMREGION_ERASEFF )

	ROM_REGION32_BE( USER4REGION_LENGTH, "old4", ROMREGION_ERASEFF )
	ROM_LOAD( "10_hc07",  0x0000000, 0x800000, CRC(b18be430) SHA1(0ede4ab7c950dc838e01b8df9b9ddd725ff640ee) )
	ROM_LOAD( "20",  0x0800000, 0x800000, CRC(5ca8faba) SHA1(71c12638ae7fa38b362d68c3ccb4bb3ccd67f0e9) )
	ROM_REGION16_BE( USER5REGION_LENGTH, "old5", ROMREGION_ERASEFF )
	ROM_LOAD( "30",  0x0000000, 0x800000, CRC(b37cf960) SHA1(60310f95e4ecedee85846c08ccba71e286cda73b) )
	ROM_LOAD( "31",  0x0800000, 0x800000, CRC(450ec982) SHA1(1cb3626b8479997c4f1b29c41c81cac038fac31b) )
	ROM_LOAD( "40",  0x1000000, 0x800000, CRC(632c965f) SHA1(9a46b759f5dee35411fd6446c2457c084a6dfcd8) )
	ROM_LOAD( "41",  0x1800000, 0x800000, CRC(7a4c5f33) SHA1(f33cdfe247c7caf9d3d394499712f72ca930705e) )
	ROM_LOAD( "50",  0x2000000, 0x800000, CRC(8562358e) SHA1(8ed78f6b106659a3e4d94f38f8a354efcbdf3aa7) )
	ROM_LOAD( "51",  0x2800000, 0x800000, CRC(7baf234b) SHA1(38feb45d6315d771de5f9ae965119cb25bae2a1e) )
	ROM_LOAD( "60",  0x3000000, 0x800000, CRC(bc9487b7) SHA1(bc2cd2d3551cc20aa231bba425ff721570735eba) )
	ROM_LOAD( "61",  0x3800000, 0x800000, CRC(b813a1b1) SHA1(16de0ee3dfd6bf33d07b0ff2e797ebe2cfe6589e) )
ROM_END

ROM_START( sfiii3hc08 ) //sfiii3th
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "sfiii3-simm1.0", 0x00000, 0x200000, CRC(11dfd3cd) SHA1(dba1f77c46e80317e3279298411154dfb6db2309) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "sfiii3-simm1.1", 0x00000, 0x200000, CRC(c50585e6) SHA1(a289237957ea1c7f58b1c65e24c54ceb34cb1712) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "sfiii3-simm1.2", 0x00000, 0x200000, CRC(8e011d9b) SHA1(e0861bcd3c4f865474d7ce47aa9eeec7b3d28da6) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "sfiii3-simm1.3", 0x00000, 0x200000, CRC(dca8d92f) SHA1(7cd241641c943df446e2c75b88b5cf2d2ebf7b2e) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii3-simm2.0", 0x00000, 0x200000, CRC(06eb969e) SHA1(d89f6a6585b76692d57d337f0f8186398fb056da) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii3-simm2.1", 0x00000, 0x200000, CRC(e7039f82) SHA1(8e81e66b5a4f45ae14b070a491bde47a6a74499f) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii3-simm2.2", 0x00000, 0x200000, CRC(645c96f7) SHA1(06d5a54874d4bf100b776131ec9060da209ad037) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii3-simm2.3", 0x00000, 0x200000, CRC(610efab1) SHA1(bbc21ed6ff6220ff6017a3f02ebd9a341fbc9040) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii3-simm3.0", 0x00000, 0x200000, CRC(7baa1f79) SHA1(3f409df28c24dd7221966b5340d59898ea756b6f) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii3-simm3.1", 0x00000, 0x200000, CRC(234bf8fe) SHA1(2191781ae4d726cab28de97f27efa4a13f3bdd69) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii3-simm3.2", 0x00000, 0x200000, CRC(d9ebc308) SHA1(af6a0dca77e5181c9f20533a06760a782c5fd51d) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii3-simm3.3", 0x00000, 0x200000, CRC(293cba77) SHA1(294604cacdc24261aec4d39e489de91c41fa1758) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii3-simm3.4", 0x00000, 0x200000, CRC(6055e747) SHA1(3813852c5a4a5355ef739ca8f0913bbd390b984b) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii3-simm3.5", 0x00000, 0x200000, CRC(499aa6fc) SHA1(5b9b6eab3e99ff3e1d7c1f50b9d8bc6a81f3f8a9) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii3-simm3.6", 0x00000, 0x200000, CRC(6c13879e) SHA1(de189b0b8f42bc7dd89983e62bc2ecb4237b3277) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii3-simm3.7", 0x00000, 0x200000, CRC(cf4f8ede) SHA1(e0fb68fcb0e445f824c62fa828d6e1dcd7e3683a) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii3-simm4.0", 0x00000, 0x200000, CRC(091fd5ba) SHA1(3327ad7c2623c119bf728af717ea2ce3b74673a9) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii3-simm4.1", 0x00000, 0x200000, CRC(0bca8917) SHA1(b7b284e2f16f46d46bcfaae779b232c5b980924f) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii3-simm4.2", 0x00000, 0x200000, CRC(a0fd578b) SHA1(100c9db9f00ecd88d518076f5a0822e6ac3695b3) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii3-simm4.3", 0x00000, 0x200000, CRC(4bf8c699) SHA1(2c0b4288b5ebc5e54d9e782dfc39eb8c78fd4c21) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii3-simm4.4", 0x00000, 0x200000, CRC(137b8785) SHA1(56a579520a8ce2abbf36be57777f024e80474eee) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii3-simm4.5", 0x00000, 0x200000, CRC(4fb70671) SHA1(9aba83c18cfc099a5ce18793119bff0c2b9c777f) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii3-simm4.6", 0x00000, 0x200000, CRC(832374a4) SHA1(c84629e32fbf47cb7b5b4ee7555bfc2ac9b3857f) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii3-simm4.7", 0x00000, 0x200000, CRC(1c88576d) SHA1(0f039944d0c2305999ed5dbd351c3eb87812dc3b) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii3-simm5.0", 0x00000, 0x200000, CRC(c67d9190) SHA1(d265475244099d0ec153059986f3445c7bd910a3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii3-simm5.1", 0x00000, 0x200000, CRC(6cb79868) SHA1(c94237f30e05bfcb2e23945530c812d9e4c73416) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii3-simm5.2", 0x00000, 0x200000, CRC(df69930e) SHA1(c76b7c559a1d5558138afbc796249efa2f49f6a8) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii3-simm5.3", 0x00000, 0x200000, CRC(333754e0) SHA1(4c18a569c26524a492ecd6f4c8b3c8e803a077d3) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii3-simm5.4", 0x00000, 0x200000, CRC(78f6d417) SHA1(a69577cc5399fcf0a24548661168f27f3e7e8e40) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii3-simm5.5", 0x00000, 0x200000, CRC(8ccad9b1) SHA1(f8bda399f87be2497b7ac39e9661f9863bf4f873) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "sfiii3-simm5_hc08.6", 0x00000, 0x200000, CRC(7fffb6d4) SHA1(5212d7d3e5228be8354bade969c5612d1c7a62cc) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "sfiii3-simm5_hc08.7", 0x00000, 0x200000, CRC(2dfcd4a6) SHA1(62a8bfc619ed6e1c4e50f7206188d7b5c54d763b) )

	ROM_REGION( 0x200000, "simm6.0", 0 )
	ROM_LOAD( "sfiii3-simm6.0", 0x00000, 0x200000, CRC(8da69042) SHA1(fd3d08295342635b2136e48d543c9350d287bb22) )
	ROM_REGION( 0x200000, "simm6.1", 0 )
	ROM_LOAD( "sfiii3-simm6.1", 0x00000, 0x200000, CRC(1c8c7ac4) SHA1(ac9f8353a4c356ef98aa7c226baba00b01f5a80f) )
	ROM_REGION( 0x200000, "simm6.2", 0 )
	ROM_LOAD( "sfiii3-simm6.2", 0x00000, 0x200000, CRC(a671341d) SHA1(636f4c04962bc1e1ddb29d2e01244b00389b234f) )
	ROM_REGION( 0x200000, "simm6.3", 0 )
	ROM_LOAD( "sfiii3-simm6.3", 0x00000, 0x200000, CRC(1a990249) SHA1(2acc639e2c0c53bf24096b8620eab090bc25d03b) )
	ROM_REGION( 0x200000, "simm6.4", 0 )
	ROM_LOAD( "sfiii3-simm6.4", 0x00000, 0x200000, CRC(20cb39ac) SHA1(7d13a0fea1ef719dd2ff77dfb547d53c6023cc9e) )
	ROM_REGION( 0x200000, "simm6.5", 0 )
	ROM_LOAD( "sfiii3-simm6.5", 0x00000, 0x200000, CRC(5f844b2f) SHA1(564e4934f89ed3b92a4c4874519f8f00f3b48696) )
	ROM_REGION( 0x200000, "simm6.6", 0 )
	ROM_LOAD( "sfiii3-simm6.6", 0x00000, 0x200000, CRC(450e8d28) SHA1(885db658132aa27926df617ec2d2a1f38abdbb60) )
	ROM_REGION( 0x200000, "simm6.7", 0 )
	ROM_LOAD( "sfiii3-simm6.7", 0x00000, 0x200000, CRC(cc5f4187) SHA1(248ddace21ed4736a56e92f77cc6ad219d7fef0b) )
ROM_END

ROM_START( sfiii3hc09 ) //sfiii4n
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "sfiii3-simm1_hc09.0", 0x00000, 0x200000, CRC(2963aa89) SHA1(e60ac38bf3894ba810c59882c2abd16800c967a2) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "sfiii3-simm1_hc09.1", 0x00000, 0x200000, CRC(3d4038e9) SHA1(9eec38f90ebe3924f09f18195c153cb77c65a131) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "sfiii3-simm1_hc09.2", 0x00000, 0x200000, CRC(d5a580ce) SHA1(7767d4cd14e92d736cff299a9e699b3e4feb4221) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "sfiii3-simm1_hc09.3", 0x00000, 0x200000, CRC(1686fa39) SHA1(546daf72fb1e0f0e2e1dc3e0a2044468197ae78f) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii3-simm2.0", 0x00000, 0x200000, CRC(06eb969e) SHA1(d89f6a6585b76692d57d337f0f8186398fb056da) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii3-simm2.1", 0x00000, 0x200000, CRC(e7039f82) SHA1(8e81e66b5a4f45ae14b070a491bde47a6a74499f) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii3-simm2.2", 0x00000, 0x200000, CRC(645c96f7) SHA1(06d5a54874d4bf100b776131ec9060da209ad037) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii3-simm2.3", 0x00000, 0x200000, CRC(610efab1) SHA1(bbc21ed6ff6220ff6017a3f02ebd9a341fbc9040) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii3-simm3.0", 0x00000, 0x200000, CRC(7baa1f79) SHA1(3f409df28c24dd7221966b5340d59898ea756b6f) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii3-simm3.1", 0x00000, 0x200000, CRC(234bf8fe) SHA1(2191781ae4d726cab28de97f27efa4a13f3bdd69) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii3-simm3.2", 0x00000, 0x200000, CRC(d9ebc308) SHA1(af6a0dca77e5181c9f20533a06760a782c5fd51d) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii3-simm3.3", 0x00000, 0x200000, CRC(293cba77) SHA1(294604cacdc24261aec4d39e489de91c41fa1758) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii3-simm3.4", 0x00000, 0x200000, CRC(6055e747) SHA1(3813852c5a4a5355ef739ca8f0913bbd390b984b) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii3-simm3.5", 0x00000, 0x200000, CRC(499aa6fc) SHA1(5b9b6eab3e99ff3e1d7c1f50b9d8bc6a81f3f8a9) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii3-simm3.6", 0x00000, 0x200000, CRC(6c13879e) SHA1(de189b0b8f42bc7dd89983e62bc2ecb4237b3277) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii3-simm3.7", 0x00000, 0x200000, CRC(cf4f8ede) SHA1(e0fb68fcb0e445f824c62fa828d6e1dcd7e3683a) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii3-simm4.0", 0x00000, 0x200000, CRC(091fd5ba) SHA1(3327ad7c2623c119bf728af717ea2ce3b74673a9) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii3-simm4.1", 0x00000, 0x200000, CRC(0bca8917) SHA1(b7b284e2f16f46d46bcfaae779b232c5b980924f) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii3-simm4.2", 0x00000, 0x200000, CRC(a0fd578b) SHA1(100c9db9f00ecd88d518076f5a0822e6ac3695b3) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii3-simm4.3", 0x00000, 0x200000, CRC(4bf8c699) SHA1(2c0b4288b5ebc5e54d9e782dfc39eb8c78fd4c21) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii3-simm4.4", 0x00000, 0x200000, CRC(137b8785) SHA1(56a579520a8ce2abbf36be57777f024e80474eee) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii3-simm4.5", 0x00000, 0x200000, CRC(4fb70671) SHA1(9aba83c18cfc099a5ce18793119bff0c2b9c777f) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii3-simm4.6", 0x00000, 0x200000, CRC(832374a4) SHA1(c84629e32fbf47cb7b5b4ee7555bfc2ac9b3857f) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii3-simm4.7", 0x00000, 0x200000, CRC(1c88576d) SHA1(0f039944d0c2305999ed5dbd351c3eb87812dc3b) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii3-simm5.0", 0x00000, 0x200000, CRC(c67d9190) SHA1(d265475244099d0ec153059986f3445c7bd910a3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii3-simm5.1", 0x00000, 0x200000, CRC(6cb79868) SHA1(c94237f30e05bfcb2e23945530c812d9e4c73416) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii3-simm5.2", 0x00000, 0x200000, CRC(df69930e) SHA1(c76b7c559a1d5558138afbc796249efa2f49f6a8) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii3-simm5.3", 0x00000, 0x200000, CRC(333754e0) SHA1(4c18a569c26524a492ecd6f4c8b3c8e803a077d3) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii3-simm5.4", 0x00000, 0x200000, CRC(78f6d417) SHA1(a69577cc5399fcf0a24548661168f27f3e7e8e40) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii3-simm5.5", 0x00000, 0x200000, CRC(8ccad9b1) SHA1(f8bda399f87be2497b7ac39e9661f9863bf4f873) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "sfiii3-simm5_hc09.6", 0x00000, 0x200000, CRC(85de59e5) SHA1(748b5c91f15777b85d8c1d35b685cd90d3185ec6) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "sfiii3-simm5_hc09.7", 0x00000, 0x200000, CRC(ee7e29b3) SHA1(63dc30c6904ca2f58d229249bee5eef51fafa158) )

	ROM_REGION( 0x200000, "simm6.0", 0 )
	ROM_LOAD( "sfiii3-simm6.0", 0x00000, 0x200000, CRC(8da69042) SHA1(fd3d08295342635b2136e48d543c9350d287bb22) )
	ROM_REGION( 0x200000, "simm6.1", 0 )
	ROM_LOAD( "sfiii3-simm6.1", 0x00000, 0x200000, CRC(1c8c7ac4) SHA1(ac9f8353a4c356ef98aa7c226baba00b01f5a80f) )
	ROM_REGION( 0x200000, "simm6.2", 0 )
	ROM_LOAD( "sfiii3-simm6.2", 0x00000, 0x200000, CRC(a671341d) SHA1(636f4c04962bc1e1ddb29d2e01244b00389b234f) )
	ROM_REGION( 0x200000, "simm6.3", 0 )
	ROM_LOAD( "sfiii3-simm6.3", 0x00000, 0x200000, CRC(1a990249) SHA1(2acc639e2c0c53bf24096b8620eab090bc25d03b) )
	ROM_REGION( 0x200000, "simm6.4", 0 )
	ROM_LOAD( "sfiii3-simm6.4", 0x00000, 0x200000, CRC(20cb39ac) SHA1(7d13a0fea1ef719dd2ff77dfb547d53c6023cc9e) )
	ROM_REGION( 0x200000, "simm6.5", 0 )
	ROM_LOAD( "sfiii3-simm6.5", 0x00000, 0x200000, CRC(5f844b2f) SHA1(564e4934f89ed3b92a4c4874519f8f00f3b48696) )
	ROM_REGION( 0x200000, "simm6.6", 0 )
	ROM_LOAD( "sfiii3-simm6.6", 0x00000, 0x200000, CRC(450e8d28) SHA1(885db658132aa27926df617ec2d2a1f38abdbb60) )
	ROM_REGION( 0x200000, "simm6.7", 0 )
	ROM_LOAD( "sfiii3-simm6.7", 0x00000, 0x200000, CRC(cc5f4187) SHA1(248ddace21ed4736a56e92f77cc6ad219d7fef0b) )
ROM_END

ROM_START( sfiii3hc10 ) //sfiii4n
	ROM_REGION32_BE( 0x080000, "bios", 0 )
	ROM_LOAD( "sfiii3_japan_nocd.29f400.u2", 0x000000, 0x080000, CRC(1edc6366) SHA1(60b4b9adeb030a33059d74fdf03873029e465b52) )

	ROM_REGION( 0x200000, "simm1.0", 0 )
	ROM_LOAD( "sfiii3-simm1_hc10.0", 0x00000, 0x200000, CRC(01bd1df9) SHA1(056a47a50778bb0798a357fd4a12948775a2b7c7) )
	ROM_REGION( 0x200000, "simm1.1", 0 )
	ROM_LOAD( "sfiii3-simm1_hc10.1", 0x00000, 0x200000, CRC(6c0e1f37) SHA1(a7c63429ad4c17d29c1f915af017a38900a32d1e) )
	ROM_REGION( 0x200000, "simm1.2", 0 )
	ROM_LOAD( "sfiii3-simm1_hc10.2", 0x00000, 0x200000, CRC(8f3f5a42) SHA1(ac21d4e1f38d7ac199d8146fec5e1565d27296a0) )
	ROM_REGION( 0x200000, "simm1.3", 0 )
	ROM_LOAD( "sfiii3-simm1_hc10.3", 0x00000, 0x200000, CRC(1d6ba352) SHA1(264ca4a507422ca51b803aca8aa09011e1704335) )

	ROM_REGION( 0x200000, "simm2.0", 0 )
	ROM_LOAD( "sfiii3-simm2.0", 0x00000, 0x200000, CRC(06eb969e) SHA1(d89f6a6585b76692d57d337f0f8186398fb056da) )
	ROM_REGION( 0x200000, "simm2.1", 0 )
	ROM_LOAD( "sfiii3-simm2.1", 0x00000, 0x200000, CRC(e7039f82) SHA1(8e81e66b5a4f45ae14b070a491bde47a6a74499f) )
	ROM_REGION( 0x200000, "simm2.2", 0 )
	ROM_LOAD( "sfiii3-simm2.2", 0x00000, 0x200000, CRC(645c96f7) SHA1(06d5a54874d4bf100b776131ec9060da209ad037) )
	ROM_REGION( 0x200000, "simm2.3", 0 )
	ROM_LOAD( "sfiii3-simm2.3", 0x00000, 0x200000, CRC(610efab1) SHA1(bbc21ed6ff6220ff6017a3f02ebd9a341fbc9040) )

	ROM_REGION( 0x200000, "simm3.0", 0 )
	ROM_LOAD( "sfiii3-simm3.0", 0x00000, 0x200000, CRC(7baa1f79) SHA1(3f409df28c24dd7221966b5340d59898ea756b6f) )
	ROM_REGION( 0x200000, "simm3.1", 0 )
	ROM_LOAD( "sfiii3-simm3.1", 0x00000, 0x200000, CRC(234bf8fe) SHA1(2191781ae4d726cab28de97f27efa4a13f3bdd69) )
	ROM_REGION( 0x200000, "simm3.2", 0 )
	ROM_LOAD( "sfiii3-simm3.2", 0x00000, 0x200000, CRC(d9ebc308) SHA1(af6a0dca77e5181c9f20533a06760a782c5fd51d) )
	ROM_REGION( 0x200000, "simm3.3", 0 )
	ROM_LOAD( "sfiii3-simm3.3", 0x00000, 0x200000, CRC(293cba77) SHA1(294604cacdc24261aec4d39e489de91c41fa1758) )
	ROM_REGION( 0x200000, "simm3.4", 0 )
	ROM_LOAD( "sfiii3-simm3.4", 0x00000, 0x200000, CRC(6055e747) SHA1(3813852c5a4a5355ef739ca8f0913bbd390b984b) )
	ROM_REGION( 0x200000, "simm3.5", 0 )
	ROM_LOAD( "sfiii3-simm3.5", 0x00000, 0x200000, CRC(499aa6fc) SHA1(5b9b6eab3e99ff3e1d7c1f50b9d8bc6a81f3f8a9) )
	ROM_REGION( 0x200000, "simm3.6", 0 )
	ROM_LOAD( "sfiii3-simm3.6", 0x00000, 0x200000, CRC(6c13879e) SHA1(de189b0b8f42bc7dd89983e62bc2ecb4237b3277) )
	ROM_REGION( 0x200000, "simm3.7", 0 )
	ROM_LOAD( "sfiii3-simm3.7", 0x00000, 0x200000, CRC(cf4f8ede) SHA1(e0fb68fcb0e445f824c62fa828d6e1dcd7e3683a) )

	ROM_REGION( 0x200000, "simm4.0", 0 )
	ROM_LOAD( "sfiii3-simm4.0", 0x00000, 0x200000, CRC(091fd5ba) SHA1(3327ad7c2623c119bf728af717ea2ce3b74673a9) )
	ROM_REGION( 0x200000, "simm4.1", 0 )
	ROM_LOAD( "sfiii3-simm4.1", 0x00000, 0x200000, CRC(0bca8917) SHA1(b7b284e2f16f46d46bcfaae779b232c5b980924f) )
	ROM_REGION( 0x200000, "simm4.2", 0 )
	ROM_LOAD( "sfiii3-simm4.2", 0x00000, 0x200000, CRC(a0fd578b) SHA1(100c9db9f00ecd88d518076f5a0822e6ac3695b3) )
	ROM_REGION( 0x200000, "simm4.3", 0 )
	ROM_LOAD( "sfiii3-simm4.3", 0x00000, 0x200000, CRC(4bf8c699) SHA1(2c0b4288b5ebc5e54d9e782dfc39eb8c78fd4c21) )
	ROM_REGION( 0x200000, "simm4.4", 0 )
	ROM_LOAD( "sfiii3-simm4.4", 0x00000, 0x200000, CRC(137b8785) SHA1(56a579520a8ce2abbf36be57777f024e80474eee) )
	ROM_REGION( 0x200000, "simm4.5", 0 )
	ROM_LOAD( "sfiii3-simm4.5", 0x00000, 0x200000, CRC(4fb70671) SHA1(9aba83c18cfc099a5ce18793119bff0c2b9c777f) )
	ROM_REGION( 0x200000, "simm4.6", 0 )
	ROM_LOAD( "sfiii3-simm4.6", 0x00000, 0x200000, CRC(832374a4) SHA1(c84629e32fbf47cb7b5b4ee7555bfc2ac9b3857f) )
	ROM_REGION( 0x200000, "simm4.7", 0 )
	ROM_LOAD( "sfiii3-simm4.7", 0x00000, 0x200000, CRC(1c88576d) SHA1(0f039944d0c2305999ed5dbd351c3eb87812dc3b) )

	ROM_REGION( 0x200000, "simm5.0", 0 )
	ROM_LOAD( "sfiii3-simm5.0", 0x00000, 0x200000, CRC(c67d9190) SHA1(d265475244099d0ec153059986f3445c7bd910a3) )
	ROM_REGION( 0x200000, "simm5.1", 0 )
	ROM_LOAD( "sfiii3-simm5.1", 0x00000, 0x200000, CRC(6cb79868) SHA1(c94237f30e05bfcb2e23945530c812d9e4c73416) )
	ROM_REGION( 0x200000, "simm5.2", 0 )
	ROM_LOAD( "sfiii3-simm5.2", 0x00000, 0x200000, CRC(df69930e) SHA1(c76b7c559a1d5558138afbc796249efa2f49f6a8) )
	ROM_REGION( 0x200000, "simm5.3", 0 )
	ROM_LOAD( "sfiii3-simm5.3", 0x00000, 0x200000, CRC(333754e0) SHA1(4c18a569c26524a492ecd6f4c8b3c8e803a077d3) )
	ROM_REGION( 0x200000, "simm5.4", 0 )
	ROM_LOAD( "sfiii3-simm5.4", 0x00000, 0x200000, CRC(78f6d417) SHA1(a69577cc5399fcf0a24548661168f27f3e7e8e40) )
	ROM_REGION( 0x200000, "simm5.5", 0 )
	ROM_LOAD( "sfiii3-simm5.5", 0x00000, 0x200000, CRC(8ccad9b1) SHA1(f8bda399f87be2497b7ac39e9661f9863bf4f873) )
	ROM_REGION( 0x200000, "simm5.6", 0 )
	ROM_LOAD( "sfiii3-simm5_hc09.6", 0x00000, 0x200000, CRC(85de59e5) SHA1(748b5c91f15777b85d8c1d35b685cd90d3185ec6) )
	ROM_REGION( 0x200000, "simm5.7", 0 )
	ROM_LOAD( "sfiii3-simm5_hc09.7", 0x00000, 0x200000, CRC(ee7e29b3) SHA1(63dc30c6904ca2f58d229249bee5eef51fafa158) )

	ROM_REGION( 0x200000, "simm6.0", 0 )
	ROM_LOAD( "sfiii3-simm6.0", 0x00000, 0x200000, CRC(8da69042) SHA1(fd3d08295342635b2136e48d543c9350d287bb22) )
	ROM_REGION( 0x200000, "simm6.1", 0 )
	ROM_LOAD( "sfiii3-simm6.1", 0x00000, 0x200000, CRC(1c8c7ac4) SHA1(ac9f8353a4c356ef98aa7c226baba00b01f5a80f) )
	ROM_REGION( 0x200000, "simm6.2", 0 )
	ROM_LOAD( "sfiii3-simm6.2", 0x00000, 0x200000, CRC(a671341d) SHA1(636f4c04962bc1e1ddb29d2e01244b00389b234f) )
	ROM_REGION( 0x200000, "simm6.3", 0 )
	ROM_LOAD( "sfiii3-simm6.3", 0x00000, 0x200000, CRC(1a990249) SHA1(2acc639e2c0c53bf24096b8620eab090bc25d03b) )
	ROM_REGION( 0x200000, "simm6.4", 0 )
	ROM_LOAD( "sfiii3-simm6.4", 0x00000, 0x200000, CRC(20cb39ac) SHA1(7d13a0fea1ef719dd2ff77dfb547d53c6023cc9e) )
	ROM_REGION( 0x200000, "simm6.5", 0 )
	ROM_LOAD( "sfiii3-simm6.5", 0x00000, 0x200000, CRC(5f844b2f) SHA1(564e4934f89ed3b92a4c4874519f8f00f3b48696) )
	ROM_REGION( 0x200000, "simm6.6", 0 )
	ROM_LOAD( "sfiii3-simm6.6", 0x00000, 0x200000, CRC(450e8d28) SHA1(885db658132aa27926df617ec2d2a1f38abdbb60) )
	ROM_REGION( 0x200000, "simm6.7", 0 )
	ROM_LOAD( "sfiii3-simm6.7", 0x00000, 0x200000, CRC(cc5f4187) SHA1(248ddace21ed4736a56e92f77cc6ad219d7fef0b) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       CLASS                INIT      MONITOR     COMPANY        FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2018, jojobahc01,     jojoba,   jojoba,        cps3_jojo,  cps3_hbmame,     init_jojoban,  ROT0,      "hack",        "JoJo's Bizarre Adventure (Enable Hidden Characters 2009-08-08)", 0 )
GAME( 2018, jojobahc02,     jojoba,   jojoba,        cps3_jojo,  cps3_state,      init_jojoba,   ROT0,      "hack",        "JoJo's Bizarre Adventure (Ex Super Version Edition)", 0 )
GAME( 2021, jojobahc03,     jojoba,   jojoba,        cps3_jojo,  cps3_state,      init_jojoba,   ROT0,      "hack",        "JoJo's Bizarre Adventure (Rainbow Edition v1.0.1 2021)", 0 )
GAME( 2009, jojohc01,       jojo,     jojo,          cps3_jojo,  cps3_hbmame,     init_jojon,    ROT0,      "hack",        "JoJo's Venture (Enable Hidden Characters 2009-07-09)", 0 )
GAME( 2009, redeartnhc01,   redeartn, redeartn,      cps3_ren,   cps3_hbmame,     init_redeartno,ROT0,      "hack",        "Red Earth (Ex Super Version 2009-09-08)", 0 )
GAME( 2016, sfiiihc01,      sfiii,    sfiii,         cps3,       cps3_state,      init_sfiii,    ROT0,      "hack",        "Street Fighter III: New Generation (Simple Attack 2016-01-21)", 0 )
GAME( 2009, sfiiihc02,      sfiii,    sfiii,         cps3,       cps3_hbmame,     init_sfiiin,   ROT0,      "hack",        "Street Fighter III: New Generation (Enable Hidden Characters 2009-08-08)", 0 )
GAMEL(1997, sfiii2hc01,     sfiii2,   sfiii2,        cps3,       cps3_state,      init_sfiii2,   ROT0,      "hack",        "Street Fighter III 2nd Impact: Giant Attack (Enable Hidden Characters)", 0, layout_sfiii2 )
GAMEL(2016, sfiii2hc02,     sfiii2,   sfiii2,        cps3,       cps3_state,      init_sfiii2,   ROT0,      "hack",        "Street Fighter III 2nd Impact: Giant Attack (Boss With Simple Attack Edition 2016-01-11)", 0, layout_sfiii2 )
GAMEL(2016, sfiii2hc03,     sfiii2,   sfiii2,        cps3,       cps3_state,      init_sfiii2,   ROT0,      "hack",        "Street Fighter III 2nd Impact: Giant Attack (Hits The Second Time 2014-11-19)", 0, layout_sfiii2 )
GAME( 2022, sfiii3hc01,     sfiii3,   sfiii3,        cps3,       cps3_state,      init_sfiii3,   ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (Widescreen Edition 2022-07-01)", 0 )
GAME( 2022, sfiii3hc02,     sfiii3,   sfiii3,        cps3,       cps3_state,      init_sfiii3,   ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (Widescreen Edition 2022-09-08)", 0 )
GAME( 2014, sfiii3hc03,     sfiii3,   sfiii3,        cps3,       cps3_state,      init_sfiii3,   ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (Hits The Third Time 2014-11-20)", 0 )
GAME( 2015, sfiii3hc04,     sfiii3,   sfiii3,        cps3,       cps3_state,      init_sfiii3,   ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (Boss With Simple Attack Edition 2015-12-16)", 0 )
GAME( 2014, sfiii3hc05,     sfiii3,   sfiii3,        cps3,       cps3_state,      init_sfiii3,   ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (4rd Arrange Edition 2013 Simplified 2014-11-16)", 0 )
GAME( 2013, sfiii3hc06,     sfiii3,   sfiii3,        cps3,       cps3_state,      init_sfiii3,   ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (4rd Arrange Edition 2013 Original 2013-07-16)", 0 )
GAME( 1999, sfiii3hc07,     sfiii3,   sfiii3,        cps3,       cps3_hbmame,     init_sfiii3n,  ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (Enable Hidden Characters)", 0 )
GAME( 2021, sfiii3hc08,     sfiii3,   sfiii3,        cps3,       cps3_state,      init_sfiii3,   ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (THIRD Update 2021)", 0 )
GAME( 2021, sfiii3hc09,     sfiii3,   sfiii3,        cps3,       cps3_state,      init_sfiii3,   ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (4rd Arrange Edition Original 2021-07-31)", 0 )
GAME( 2021, sfiii3hc10,     sfiii3,   sfiii3,        cps3,       cps3_state,      init_sfiii3,   ROT0,      "hack",        "Street Fighter III 3rd Strike: Fight for the Future (4rd Arrange Edition Simplified 2021-07-31)", 0 )
