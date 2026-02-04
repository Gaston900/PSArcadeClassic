// Proyecto Shadows Arcade Classic+
// copyright-holders:Gaston90

#include "sound/samples.h" //Zero800

//************** AUDIO SAMPLES ******************

// All samples code (c) Zero800, 2023
const char *const samples_id_l[] =
{
	"*sfz3mix_l",
	"empty", // 00
	"L01", // 01
	"L02", // 02
	"L03", // 03
	"L04", // 04
	"L05", // 05
	"L06", // 06
	"L07", // 07
	"L08", // 08
	"L09", // 09
	"L0A", // 10
	"L0B", // 11
	"L0C", // 12
	"L0D", // 13
	"L0E", // 14
	"L0F", // 15
	"L10", // 16
	"L11", // 17
	"L12", // 18
	"L13", // 19
	"L14", // 20
	"L15", // 21
	"L16", // 22
	"L17", // 23
	"L18", // 24
	"L19", // 25
	"L1A", // 26
	"L1B", // 27
	"L1C", // 28
	"L1D", // 29
	"L1E", // 30
	"L1F", // 31
	"L20", // 32
	"L21", // 33
	"L22", // 34
	"L23", // 35
	"L24", // 36
	"L25", // 37
	"L26", // 38
	"L27", // 39
	"L28", // 40
	"L29", // 41
	"L2A", // 42
	"L2B", // 43
	"L2C", // 44
	"L2D", // 45
	"L2E", // 46
	"L2F", // 47
	"L30", // 48
	"L31", // 49
	"L32", // 50
	"L33", // 51
	"L34", // 52
	"L35", // 53
	"L36", // 54
	"L37", // 55
	"L38", // 56
	"L39", // 57
	"L3A", // 58
	"L3B", // 59
	"L3C", // 60
	"L3D", // 61
	"L3E", // 62
	"L3F", // 63
	0
};


const char *const samples_id_r[] =
{
	"*sfz3mix_r",
	"empty", // 00
	"R01", // 01
	"R02", // 02
	"R03", // 03
	"R04", // 04
	"R05", // 05
	"R06", // 06
	"R07", // 07
	"R08", // 08
	"R09", // 09
	"R0A", // 10
	"R0B", // 11
	"R0C", // 12
	"R0D", // 13
	"R0E", // 14
	"R0F", // 15
	"R10", // 16
	"R11", // 17
	"R12", // 18
	"R13", // 19
	"R14", // 20
	"R15", // 21
	"R16", // 22
	"R17", // 23
	"R18", // 24
	"R19", // 25
	"R1A", // 26
	"R1B", // 27
	"R1C", // 28
	"R1D", // 29
	"R1E", // 30
	"R1F", // 31
	"R20", // 32
	"R21", // 33
	"R22", // 34
	"R23", // 35
	"R24", // 36
	"R25", // 37
	"R26", // 38
	"R27", // 39
	"R28", // 40
	"R29", // 41
	"R2A", // 42
	"R2B", // 43
	"R2C", // 44
	"R2D", // 45
	"R2E", // 46
	"R2F", // 47
	"R30", // 48
	"R31", // 49
	"R32", // 50
	"R33", // 51
	"R34", // 52
	"R35", // 53
	"R36", // 54
	"R37", // 55
	"R38", // 56
	"R39", // 57
	"R3A", // 58
	"R3B", // 59
	"R3C", // 60
	"R3D", // 61
	"R3E", // 62
	"R3F", // 63
	0
};

// This function (c) Zero800, tidied by Robbbert
void cps2_state::qsound_sharedram1_samples_w(offs_t offset, uint16_t data, uint16_t mem_mask) //allows you to write and signal when a new song is played
{
	if (ACCESSING_BITS_0_7)
	{
		if (offset == 0x0001 && (data & 0xff) == 0x00 && m_qsound_sharedram1[0x00] == 0xff) //stop samples sound
		{
			m_samples_l->start(0, 0, false);
			m_samples_r->start(0, 0, false);
			//printf("%s Stop: %02x to %x\n", machine().describe_context().c_str(), offset, offset);
		}

		if (offset == 0xffe)
		{
			if (m_qsound_sharedram1[0x80] == 0x77) //stop music condition in audiocpu = C080 (z80 hacked)
			{
				m_samples_l->start(0, 0, false); //init L samples
				m_samples_r->start(0, 0, false); //init R samples
				m_qsound_sharedram2[0x27] = 0xc9; //Enable Qsound Volume
				m_qsound_sharedram1[0x80] = 0xff; //Reset music id flag
				m_qsound_sharedram1[0x81] = 0xff; //Reset music id flag
				//printf("%s Clear: %02x to %x\n", machine().describe_context().c_str(), data, offset);
			}
			else
			if (m_qsound_sharedram1[0x81] > 0x00 && m_qsound_sharedram1[0x81] < 0x40) //play music condition in audiocpu = C081 (z80 hacked)
			{
				int data_byte = m_qsound_sharedram1[0x81];
				m_qsound_sharedram1[0x80] = 0xff; //Reset music id flag
				m_qsound_sharedram1[0x81] = 0xff; //Reset music id flag
				//printf("%s Music: %02x to %x\n", machine().describe_context().c_str(), data_byte, offset);
				m_samples_l->start(0, data_byte, true);
				if (m_samples_l->playing(0) == true)
					m_qsound_sharedram2[0x27] = 0x00; //Qsound music volume = 0
				else
					m_samples_l->start(0, 0, false); //init L samples

				m_samples_r->start(0, data_byte, true);
				if (m_samples_r->playing(0)  == true)
					m_qsound_sharedram2[0x27] = 0x00; //Qsound music volume = 0
				else
					m_samples_r->start(0, 0, false); //init R samples
			}
			else
			if (m_qsound_sharedram2[0x27] == 0x00 && m_samples_l->playing(0) != true) //if loadstate and qsound volume = 0 && samples stopped
			{
				m_samples_l->start(0, 0, false); //init L samples
				m_samples_r->start(0, 0, false); //init R samples
				m_qsound_sharedram2[0x27] = 0xc9; //Enable Qsound Volume
				m_qsound_sharedram1[0x80] = 0xff; //Reset music id flag
				m_qsound_sharedram1[0x81] = 0xff; //Reset music id flag
				//printf("%s Volume0: %02x to %x\n", machine().describe_context().c_str(), data, offset);
			}
			else
			if (m_qsound_sharedram2[0x27] != 0x00 && m_samples_l->playing(0) == true) //if loadstate and qsound volume != 0 && samples playing
			{
				m_samples_l->start(0, 0, false); //init L samples
				m_samples_r->start(0, 0, false); //init R samples
				m_qsound_sharedram2[0x27] = 0xc9; //Enable Qsound Volume
				m_qsound_sharedram1[0x80] = 0xff; //Reset music id flag
				m_qsound_sharedram1[0x81] = 0xff; //Reset music id flag
				//printf("%s Volume0: %02x to %x\n", machine().describe_context().c_str(), data, offset);
			}
			else 
			if ((data & 0xff) == 0x55) //init samples in rom start
			{
				m_samples_l->start(0, 0, false);
				m_samples_r->start(0, 0, false);
			}
		}

		m_qsound_sharedram1[offset] = data;	//Play data Qsound
	}
}

// (c) Zero800
void cps2_state::cps2turbo_map(address_map &map)
{
	map(0x000000, 0x3fffff).rom(); //+200000 extra                                                                                    // 68000 ROM
	map(0x618000, 0x619fff).rw(FUNC(cps2_state::qsound_sharedram1_r), FUNC(cps2_state::qsound_sharedram1_samples_w));                 // Q RAM + Play samples condition
	map(0x660000, 0x663fff).ram();                                                                                                    // When bit 14 of 0x804030 equals 0 this space is available. Many games store highscores and other info here if available.
	map(0x664000, 0x664001).ram();                                                                                                    // Unknown - Only used if 0x660000-0x663fff available (could be RAM enable?)
	map(0x665000, 0x66500b).ram().share("output"); //moved from 0x400000                                                              // CPS2 object output
	map(0x700000, 0x701fff).w(FUNC(cps2_state::cps2_objram1_w)).share("objram1");                                                     // Object RAM, no game seems to use it directly
	map(0x708000, 0x709fff).mirror(0x006000).rw(FUNC(cps2_state::cps2_objram2_r), FUNC(cps2_state::cps2_objram2_w)).share("objram2"); // Object RAM
	map(0x800100, 0x80013f).w(FUNC(cps2_state::cps1_cps_a_w)).share("cps_a_regs");                                                    // Mirror (sfa)
	map(0x800140, 0x80017f).rw(FUNC(cps2_state::cps1_cps_b_r), FUNC(cps2_state::cps1_cps_b_w)).share("cps_b_regs");                   // Mirror (sfa)
	map(0x804000, 0x804001).portr("IN0");                                                                                             // IN0
	map(0x804010, 0x804011).portr("IN1");                                                                                             // IN1
	map(0x804020, 0x804021).portr("IN2");                                                                                             // IN2 + EEPROM
	map(0x804030, 0x804031).r(FUNC(cps2_state::cps2_qsound_volume_r));                                                                // Master volume. Also when bit 14=0 addon memory is present, when bit 15=0 network adapter present.
	map(0x804040, 0x804041).w(FUNC(cps2_state::cps2_eeprom_port_w));                                                                  // EEPROM
	map(0x8040a0, 0x8040a1).nopw();                                                                                                   // Unknown (reset once on startup)
	map(0x8040b0, 0x8040b3).r(FUNC(cps2_state::kludge_r));                                                                            // Unknown (xmcotaj hangs if this is 0)
	map(0x8040e0, 0x8040e1).w(FUNC(cps2_state::cps2_objram_bank_w));                                                                  // bit 0 = Object ram bank swap
	map(0x804100, 0x80413f).w(FUNC(cps2_state::cps1_cps_a_w)).share("cps_a_regs");                                                    // CPS-A custom
	map(0x804140, 0x80417f).rw(FUNC(cps2_state::cps1_cps_b_r), FUNC(cps2_state::cps1_cps_b_w));                                       // CPS-B custom
	map(0x900000, 0x92ffff).ram().w(FUNC(cps2_state::cps1_gfxram_w)).share("gfxram");                                                 // Video RAM
	map(0xff0000, 0xffffef).ram();                                                                                                    // RAM
	map(0xfffff0, 0xfffffb).ram().share("output");                                                                                    // CPS2 output
	map(0xfffffc, 0xffffff).ram();
}

void cps2_state::init_sfz3mix()
{
	m_turbo = 1;
	init_cps2();
}

// Modified by Zero800
void cps2_state::cps2turbo(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, XTAL(32'000'000));
	m_maincpu->set_addrmap(AS_PROGRAM, &cps2_state::cps2turbo_map);
	m_maincpu->set_addrmap(AS_OPCODES, &cps2_state::decrypted_opcodes_map);
	//m_maincpu->disable_interrupt_mixer();
	TIMER(config, "scantimer").configure_scanline(FUNC(cps2_state::cps2_interrupt), "screen", 0, 1);

	Z80(config, m_audiocpu, XTAL(16'000'000));
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps2_state::qsound_sub_map);
	m_audiocpu->set_periodic_int(FUNC(cps2_state::irq0_line_hold), attotime::from_hz(250));

	MCFG_MACHINE_START_OVERRIDE(cps2_state, cps2)

	EEPROM_93C46_16BIT(config, "eeprom");

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_video_attributes(VIDEO_UPDATE_BEFORE_VBLANK);
	m_screen->set_raw(CPS_PIXEL_CLOCK, CPS_HTOTAL, 48, 464, CPS_VTOTAL, 12, 246);
	m_screen->set_screen_update(FUNC(cps2_state::screen_update_cps1));
	m_screen->screen_vblank().set(FUNC(cps2_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette, palette_device::BLACK).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps2_state, cps2)

	/* sound hardware */
	SPEAKER(config, "lspeaker").front_left();
	SPEAKER(config, "rspeaker").front_right();

	QSOUND(config, m_qsound);
	m_qsound->add_route(0, "lspeaker", 1.0);
	m_qsound->add_route(1, "rspeaker", 1.0);

	//Zero800
	SAMPLES(config, m_samples_l);
	m_samples_l->set_channels(1);
	m_samples_l->set_samples_names(samples_id_l);
	m_samples_l->add_route(0, "lspeaker", 0.1);

	SAMPLES(config, m_samples_r);
	m_samples_r->set_channels(1);
	m_samples_r->set_samples_names(samples_id_r);
	m_samples_r->add_route(0, "rspeaker", 0.1); 
}

/********************
 *  ROM definitions
 *********************/

ROM_START( sfz3mix ) // 0.31
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD( "sfz3mix.03", 0x000000, 0x400000, CRC(94c8f969) SHA1(25c14dae5958723481e03dbddb7617ec481a55d5) ) // 03
	ROM_IGNORE(0x200000)  // empty

	ROM_REGION( 0x4000000, "gfx", 0 )
	ROM_LOAD( "sfz3mix.13m", 0x0000000, 0x2000000, CRC(59025f91) SHA1(9e8ebbbf909f74cd857a0876fc42087a243d1b23) ) // 13m
	ROM_LOAD( "sfz3mix.21m", 0x2000000, 0x2000000, CRC(914c7031) SHA1(7b7ce04e563ef23f6f9454f268a968b9114ac729) ) // 21m

	ROM_REGION( 0x80000, "audiocpu", 0 )
	ROM_LOAD( "sfz3mix.01", 0x000000, 0x080000, CRC(52f98a5c) SHA1(5e1251b85d0bfb707b3e519aeb3a716893191a20) ) // 01

	ROM_REGION( 0x1000000, "qsound", 0 )
	ROM_LOAD( "sfz3mix.11m",   0x000000, 0x1000000, CRC(395edce2) SHA1(0f6a4be84ed1e1a13319a480b41c1f35b36f35fc) ) // 11m

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x00, 0x14, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

/*    YEAR  NAME          PARENT       MACHINE         INPUT                  INIT        MONITOR   COMPANY       FULLNAME FLAGS */
// CPS2 Hack
GAME( 2024, sfz3mix,    sfa3,         cps2turbo,    cps2_2p6b, cps2_state, init_sfz3mix,  ROT0,   "Zero800",     "Street Fighter Zero 3 (Turbo Mix 0.31)", MACHINE_SUPPORTS_SAVE )

/******
  Hack
********/

ROM_START( 19xxhc01 ) //19xxh
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "19xu_hc01.03", 0x000000, 0x80000, CRC(03a35085) SHA1(224fab94df8691a8e68a6ff30a57497350624bc0) )
	ROM_LOAD16_WORD_SWAP( "19xu.04", 0x080000, 0x80000, CRC(3111ab7f) SHA1(8bbce20ae7ba47949f4939b2f35014fb6decd283) )
	ROM_LOAD16_WORD_SWAP( "19xu.05", 0x100000, 0x80000, CRC(38df4a63) SHA1(1303f7ab6296f1454907a24d64878bdbd1ef88a7) )
	ROM_LOAD16_WORD_SWAP( "19xu.06", 0x180000, 0x80000, CRC(5c7e60d3) SHA1(26bf0936962051be871d7a7776cf78abfca5b5ee) )
	ROM_LOAD16_WORD_SWAP( "19x.07",  0x200000, 0x80000, CRC(61c0296c) SHA1(9e225beccffd14bb53a32f8c0f2aef7f331dae30) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "19x.13m",   0x0000000, 0x080000, CRC(427aeb18) SHA1(901029b5423e4bda85f592735036c06b7d426680) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19x.15m",   0x0000002, 0x080000, CRC(63bdbf54) SHA1(9beb64ef0a8c92490848599d5d979bf42532609d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19x.17m",   0x0000004, 0x080000, CRC(2dfe18b5) SHA1(8a44364d9af6b9e1664b44b9235dc172182c9eb8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19x.19m",   0x0000006, 0x080000, CRC(cbef9579) SHA1(172413f220b242411218c7865e04014ec6417537) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19x.14m",   0x0800000, 0x200000, CRC(e916967c) SHA1(3f937022166149a80585f91388de521055ca88ca) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19x.16m",   0x0800002, 0x200000, CRC(6e75f3db) SHA1(4e1c8466eaa612102d0807d2e8bf1004e97476ea) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19x.18m",   0x0800004, 0x200000, CRC(2213e798) SHA1(b1a9d5547f3f6c3ab59e8b761d224793c6ca33cb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19x.20m",   0x0800006, 0x200000, CRC(ab9d5b96) SHA1(52b755da401fde90c13181b02ab33e5e4b2aa1f7) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "19x.01",   0x00000, 0x08000, CRC(ef55195e) SHA1(813f465f2d392f6abeadbf661c54cf51171fa006) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "19x.11m",   0x000000, 0x200000, CRC(d38beef3) SHA1(134e961b926a97cca5e45d3558efb98f6f278e08) )
	ROM_LOAD16_WORD_SWAP( "19x.12m",   0x200000, 0x200000, CRC(d47c96e2) SHA1(3c1b5563f8e7ee1c450b3592fcb319e928caec3c) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "19xx.key",     0x00, 0x14, CRC(77e67ba1) SHA1(8c995bd00941ffe0145cb80e4f105ef8ef0a0001) )
ROM_END

ROM_START( 19xxhc02 ) //19xxjr1c
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "19xu_hc02.03", 0x000000, 0x80000, CRC(36aa1a2f) SHA1(8946961f5eeb19d7b75cd814fa6776703e0d5cc4) )
	ROM_LOAD16_WORD_SWAP( "19xu_hc02.04", 0x080000, 0x80000, CRC(936d2b48) SHA1(7620baea050122da16a5500b4a293efda55a4116) )
	ROM_LOAD16_WORD_SWAP( "19xu_hc02.05", 0x100000, 0x80000, CRC(e86c9a96) SHA1(a34b98d6dbfbb6fbd501720bb10003ce68920b7d) )
	ROM_LOAD16_WORD_SWAP( "19xu_hc02.06", 0x180000, 0x80000, CRC(67d76362) SHA1(12d78542a5fb09c5bf63196774a5437057197601) )
	ROM_LOAD16_WORD_SWAP( "19x.07",  0x200000, 0x80000, CRC(61c0296c) SHA1(9e225beccffd14bb53a32f8c0f2aef7f331dae30) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "19xj_hc02.13m",   0x0000000, 0x080000, CRC(33c7141a) SHA1(d7af081e001d2cf0fcc6a2f93d14108e4843f9ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19xj_hc02.15m",   0x0000002, 0x080000, CRC(c64488d9) SHA1(4da8a9be134665b3a81d78d21a0df8c187f300a8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19xj_hc02.17m",   0x0000004, 0x080000, CRC(1d676d81) SHA1(d415599a5d01d5eefbe5c7135f50f30c28403f8f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19xj_hc02.19m",   0x0000006, 0x080000, CRC(9555afde) SHA1(eba87eb5350b477127714752665c249d9d6e4e7e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19xj_hc02.14m",   0x0800000, 0x200000, CRC(0c887947) SHA1(3976aa6bb8e6708b07e98a1ac5ebdcdf4eddc1b9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19xj_hc02.16m",   0x0800002, 0x200000, CRC(3a7b431b) SHA1(ad0a6ad86de043202c8648b6df2702c4f006ca28) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19xj_hc02.18m",   0x0800004, 0x200000, CRC(9c785b4d) SHA1(095ba0f2369b425918a00a435125060fcb70141a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "19xj_hc02.20m",   0x0800006, 0x200000, CRC(280f29c8) SHA1(8af6f82fca322072e8077b06b23b7d852d1fc75b) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "19x.01",   0x00000, 0x08000, CRC(ef55195e) SHA1(813f465f2d392f6abeadbf661c54cf51171fa006) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "19x.11m",   0x000000, 0x200000, CRC(d38beef3) SHA1(134e961b926a97cca5e45d3558efb98f6f278e08) )
	ROM_LOAD16_WORD_SWAP( "19x.12m",   0x200000, 0x200000, CRC(d47c96e2) SHA1(3c1b5563f8e7ee1c450b3592fcb319e928caec3c) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "19xxj.key",    0x00, 0x14, CRC(9aafa71a) SHA1(82188cc69e59d5ce86d0e178cf6d9f8f04da0633) )
ROM_END

ROM_START( 1944hc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "nffu_hc01.03", 0x000000, 0x80000, CRC(3239f3a2) SHA1(22f6e5772c3f2f98db79c9ec6809cb0343b7c877) )
	ROM_LOAD16_WORD_SWAP( "nffu_hc01.04", 0x080000, 0x80000, CRC(91297ec9) SHA1(3ef111613e758540a3187d972018b100bcb1652a) )
	ROM_LOAD16_WORD_SWAP( "nffu.05", 0x100000, 0x80000, CRC(ea813eb7) SHA1(34e0175a5f22d08c3538369b4bfd077a7427a128) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "nff.13m",   0x0000000, 0x400000, CRC(c9fca741) SHA1(1781d4fc18b6d6f79b7b39d9bcace750fb61a5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "nff.15m",   0x0000002, 0x400000, CRC(f809d898) SHA1(a0b6af49e1780678d808c317b875161cedddb314) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "nff.17m",   0x0000004, 0x400000, CRC(15ba4507) SHA1(bed6a82bf1dc1aa501d4c2d098115a15e18d446a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "nff.19m",   0x0000006, 0x400000, CRC(3dd41b8c) SHA1(676078baad789e25f6e5a79de29672587be7ff00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "nff.14m",   0x1000000, 0x100000, CRC(3fe3a54b) SHA1(0a8e5cae141d24fd8b3cb11796c44728b0acd69e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "nff.16m",   0x1000002, 0x100000, CRC(565cd231) SHA1(0aecd433fb4ca2de1aca9fbb1e314fb1f6979321) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "nff.18m",   0x1000004, 0x100000, CRC(63ca5988) SHA1(30137fa77573c84bcc24570bccb7dba61ddb413c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "nff.20m",   0x1000006, 0x100000, CRC(21eb8f3b) SHA1(efa69f19a958047dd91a294c88857ed3133fcbef) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "nff.01",   0x00000, 0x08000, CRC(d2e44318) SHA1(33e45f6fe9fed098a4c072b8c39406aef1a949b2) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "nff.11m",   0x000000, 0x400000, CRC(243e4e05) SHA1(83281f7290ac105a3f9a7507cbc11317d45ba706) )
	ROM_LOAD16_WORD_SWAP( "nff.12m",   0x400000, 0x400000, CRC(4fcf1600) SHA1(36f18c5d92b79433bdf7088b29a244708929d48e) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "1944fp.key",   0x00, 0x14, CRC(81b5e47e) SHA1(3dde33f070508859b04c4e4a393ea9548c48287c) )
ROM_END

ROM_START( avsphc01 ) //avspu3p, avspp
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "avp_hc01.03d", 0x000000, 0x80000, CRC(2f3dfdd3) SHA1(730a6d70a6cb44a6c60f500d9312c1b8c31d0f4b) )
	ROM_LOAD16_WORD_SWAP( "avp_hc01.04d", 0x080000, 0x80000, CRC(04229fd7) SHA1(65a5719697c7c1cb46c330c69559666f2bf6e16f) )
	ROM_LOAD16_WORD_SWAP( "avp.05d",  0x100000, 0x80000, CRC(fbfb5d7a) SHA1(5549bc9d780753bc9c10fba82588e5c3d4a2acb2) )
	ROM_LOAD16_WORD_SWAP( "avp.06",   0x180000, 0x80000, CRC(190b817f) SHA1(9bcfc0a015ffba9cdac25b6270939a9690de5da7) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "avp.13m",   0x0000000, 0x200000, CRC(8f8b5ae4) SHA1(457ce959aa5db3a003de7dda2b3799b2f1ae279b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.15m",   0x0000002, 0x200000, CRC(b00280df) SHA1(bc1291a4a222d410bc99b6f1ed392067d9c3999e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.17m",   0x0000004, 0x200000, CRC(94403195) SHA1(efaad001527a5eba8f626aea9037ac6ef9a2c295) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.19m",   0x0000006, 0x200000, CRC(e1981245) SHA1(809ccb7f10262e227d5e9d9f710e06f0e751f550) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.14m",   0x0800000, 0x200000, CRC(ebba093e) SHA1(77aaf4197d1dae3321cf9c6d2b7967ee54cf3f30) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.16m",   0x0800002, 0x200000, CRC(fb228297) SHA1(ebd02a4ba085dc70c0603662e14d61625fa04648) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.18m",   0x0800004, 0x200000, CRC(34fb7232) SHA1(8b1f15bfa758a61e6ad519af24ca774edc70d194) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.20m",   0x0800006, 0x200000, CRC(f90baa21) SHA1(20a900819a9d321316e3dfd241210725d7191ecf) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "avp.01",   0x00000, 0x08000, CRC(2d3b4220) SHA1(2b2d04d4282550fa9f6e1ad8528f20d1f2ac02eb) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "avp.11m",   0x000000, 0x200000, CRC(83499817) SHA1(e65b0ebd61ddc748842a9d4d92404b5305307623) )
	ROM_LOAD16_WORD_SWAP( "avp.12m",   0x200000, 0x200000, CRC(f4110d49) SHA1(f27538776cc1ba8213f19f98728ed8c02508d3ac) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "avspu.key",    0x000000, 0x000014, CRC(4e68e346) SHA1(60d5a12c77d07efc01f48968f4a12c59bf6b629e) )
ROM_END

ROM_START( avsphc02 ) //avsph
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "avp_hc02.03d", 0x000000, 0x80000, CRC(5bf9a02d) SHA1(9fd0d2260cd3d7e7ac0d363f8a2cac376742c6fd) )
	ROM_LOAD16_WORD_SWAP( "avp_hc02.04d", 0x080000, 0x80000, CRC(7eb392f7) SHA1(fbe0e40b060a5b64b4ee529f25d2c01c4dace5e0) )
	ROM_LOAD16_WORD_SWAP( "avp.05d",  0x100000, 0x80000, CRC(fbfb5d7a) SHA1(5549bc9d780753bc9c10fba82588e5c3d4a2acb2) )
	ROM_LOAD16_WORD_SWAP( "avp.06",   0x180000, 0x80000, CRC(190b817f) SHA1(9bcfc0a015ffba9cdac25b6270939a9690de5da7) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "avp.13m",   0x0000000, 0x200000, CRC(8f8b5ae4) SHA1(457ce959aa5db3a003de7dda2b3799b2f1ae279b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.15m",   0x0000002, 0x200000, CRC(b00280df) SHA1(bc1291a4a222d410bc99b6f1ed392067d9c3999e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.17m",   0x0000004, 0x200000, CRC(94403195) SHA1(efaad001527a5eba8f626aea9037ac6ef9a2c295) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.19m",   0x0000006, 0x200000, CRC(e1981245) SHA1(809ccb7f10262e227d5e9d9f710e06f0e751f550) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.14m",   0x0800000, 0x200000, CRC(ebba093e) SHA1(77aaf4197d1dae3321cf9c6d2b7967ee54cf3f30) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.16m",   0x0800002, 0x200000, CRC(fb228297) SHA1(ebd02a4ba085dc70c0603662e14d61625fa04648) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.18m",   0x0800004, 0x200000, CRC(34fb7232) SHA1(8b1f15bfa758a61e6ad519af24ca774edc70d194) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "avp.20m",   0x0800006, 0x200000, CRC(f90baa21) SHA1(20a900819a9d321316e3dfd241210725d7191ecf) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "avp.01",   0x00000, 0x08000, CRC(2d3b4220) SHA1(2b2d04d4282550fa9f6e1ad8528f20d1f2ac02eb) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "avp.11m",   0x000000, 0x200000, CRC(83499817) SHA1(e65b0ebd61ddc748842a9d4d92404b5305307623) )
	ROM_LOAD16_WORD_SWAP( "avp.12m",   0x200000, 0x200000, CRC(f4110d49) SHA1(f27538776cc1ba8213f19f98728ed8c02508d3ac) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "avsph.key",    0x000000, 0x000014, CRC(cae7b680) SHA1(b5f7c90c6c258ee9d0943028298bc8a0fcba63fb) )
ROM_END

ROM_START( avsphc03 ) //avspek
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "avp_hc03.03d", 0x000000, 0x80000, CRC(2d12ee9a) SHA1(7cfee45a8336db8a9df5c55c6b7e7db747f111f8) )
	ROM_LOAD16_WORD_SWAP( "avp_hc03.04d", 0x080000, 0x80000, CRC(48d480b8) SHA1(83ec28ef01d585dbe93c56554646cfe7b7af6456) )
	ROM_LOAD16_WORD_SWAP( "avpk.05d",  0x100000, 0x80000, CRC(a8dfff2e) SHA1(f3db74147ac9bf1e161d962f74508755668fbb55) )
	ROM_LOAD16_WORD_SWAP( "avp.06",   0x180000, 0x80000, CRC(190b817f) SHA1(9bcfc0a015ffba9cdac25b6270939a9690de5da7) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROM_LOAD64_WORD( "avp.13m",   0x0000000, 0x200000, CRC(8f8b5ae4) SHA1(457ce959aa5db3a003de7dda2b3799b2f1ae279b) ) // LH53706A
	ROM_LOAD64_WORD( "avp.15m",   0x0000002, 0x200000, CRC(b00280df) SHA1(bc1291a4a222d410bc99b6f1ed392067d9c3999e) ) // LH53706B
	ROM_LOAD64_WORD( "avp.17m",   0x0000004, 0x200000, CRC(94403195) SHA1(efaad001527a5eba8f626aea9037ac6ef9a2c295) ) // LH53706C
	ROM_LOAD64_WORD( "avp.19m",   0x0000006, 0x200000, CRC(e1981245) SHA1(809ccb7f10262e227d5e9d9f710e06f0e751f550) ) // LH53706D
	ROM_LOAD64_WORD( "avp_hc03.14m",  0x0800000, 0x100000, CRC(893a2d85) SHA1(08b5b56680687960eb7597710b3c65ced2416428) ) // LH53855G
	ROM_LOAD64_WORD( "avp_hc03.16m",  0x0800002, 0x100000, CRC(89d1a27b) SHA1(f908def0b5380fb11f678ec8d33c531b303b8048) ) // LH53855H
	ROM_LOAD64_WORD( "avp_hc03.18m",  0x0800004, 0x100000, CRC(9e82fd9d) SHA1(76a8f69ace9410850475d3cb26d995ebd065dbda) ) // LH53855J
	ROM_LOAD64_WORD( "avp_hc03.20m",  0x0800006, 0x100000, CRC(e8e90701) SHA1(4d545203aad0da720b57be9446d9ea4c606a0bc7) ) // LH53855K

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "avp.01",   0x00000, 0x08000, CRC(2d3b4220) SHA1(2b2d04d4282550fa9f6e1ad8528f20d1f2ac02eb) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "avp.11m",   0x000000, 0x200000, CRC(83499817) SHA1(e65b0ebd61ddc748842a9d4d92404b5305307623) )
	ROM_LOAD16_WORD_SWAP( "avp.12m",   0x200000, 0x200000, CRC(f4110d49) SHA1(f27538776cc1ba8213f19f98728ed8c02508d3ac) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "avspj.key",    0x000000, 0x000014, CRC(3d5ccc08) SHA1(85b30ccde86e2e1f50e662598dc81d47219519a1) )
ROM_END

ROM_START( batcirhc01 ) //batcird
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "btced_hc01.03", 0x000000, 0x80000, CRC(03bd6707) SHA1(62eda0d68b9940f5d07a529d05e8c90fe6a8ad02) )
	ROM_LOAD16_WORD_SWAP( "btced_hc01.04", 0x080000, 0x80000, CRC(c3ff82b6) SHA1(3b23b13e0588479a598dd43093a42cd0c9db1484) )
	ROM_LOAD16_WORD_SWAP( "btced.05", 0x100000, 0x80000, CRC(20bdbb14) SHA1(fe3a202741ca657b2b67e89050788b67d709a36d) )
	ROM_LOAD16_WORD_SWAP( "btced.06", 0x180000, 0x80000, CRC(b4d8f5bc) SHA1(dc5ca580ecfb051ded551663ea4e9f161f820f81) )
	ROM_LOAD16_WORD_SWAP( "btce_hc01.07",   0x200000, 0x80000, CRC(b194270f) SHA1(e152d48760c92b84c748014ef68050f138f75cf5) )
	ROM_LOAD16_WORD_SWAP( "btc.08",   0x280000, 0x80000, CRC(6aac85ab) SHA1(ad02d4185c2b3664fb96350d8ad317d3939a7554) )
	ROM_LOAD16_WORD_SWAP( "btc_hc01.09",   0x300000, 0x80000, CRC(31865161) SHA1(2217a4b8ca1ed3fe52e9b9d4ead85ce7df3a6bf9) )

	ROM_REGION16_BE( CODE_SIZE, "user1", 0 )
	ROM_FILL( 0x000000, 0x100000, 0x00 )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "btc.13m",   0x000000, 0x400000, CRC(dc705bad) SHA1(96e37147674bf9cd21c770897da59daac25d921a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "btc.15m",   0x000002, 0x400000, CRC(e5779a3c) SHA1(bbd7fbe061e751388d2f02434144daf9b1e36640) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "btc.17m",   0x000004, 0x400000, CRC(b33f4112) SHA1(e501fd921c8bcede69946b029e05d422714c1040) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "btc.19m",   0x000006, 0x400000, CRC(a6fcdb7e) SHA1(7a28d5d7aa036d23d97fad17d0cdb8210dc8153a) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "btc.01",   0x00000, 0x08000, CRC(1e194310) SHA1(3b29de0aca9dbca59d6b50fb2509e2a913c6b0af) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "btc.02",   0x28000, 0x20000, CRC(01aeb8e6) SHA1(50a5d1cce0caf7c5143d4904431e8f41e2a57464) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "btc.11m",   0x000000, 0x200000, CRC(c27f2229) SHA1(df2459493af40937b6656a16fad43ff51bed2204) )
	ROM_LOAD16_WORD_SWAP( "btc.12m",   0x200000, 0x200000, CRC(418a2e33) SHA1(0642ddff2ab9255f154419da24ba644ed63f34ab) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x000000, 0x000014, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( csclubhc01 ) //csclubek
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "csc_hc01.03", 0x000000, 0x80000, CRC(bd9fdb94) SHA1(f4f5c70fa8c905959482ef565cd455326e811f5b) )
	ROM_LOAD16_WORD_SWAP( "cscj.04",  0x080000, 0x80000, CRC(60c632bb) SHA1(0d42c33aa476d2cc4efcdad78667353b88225966) )
	ROM_LOAD16_WORD_SWAP( "cscj.05",  0x100000, 0x80000, CRC(ad042003) SHA1(1e167c88f3b0617c38c9f43bdc816045ac0296e0) )
	ROM_LOAD16_WORD_SWAP( "cscj.06",  0x180000, 0x80000, CRC(169e4d40) SHA1(6540d89df5e76189d32b696be7626087fe26e33b) )
	ROM_LOAD16_WORD_SWAP( "csc.07",   0x200000, 0x80000, CRC(01b05caa) SHA1(5b84487da68e6b6f2889c76bf9e070e25941988c) )

	ROM_REGION( 0x1000000, "gfx", ROMREGION_ERASE00 )
	ROM_FILL(              0x000000, 0x800000, 0x00 )
	ROM_LOAD64_WORD( "csc_hc01.14m",  0x800000, 0x200000, CRC(af69c781) SHA1(d265d1de2dc15cc4450150e8fa1eae4d18578001) )
	ROM_LOAD64_WORD( "csc_hc01.16m",  0x800002, 0x200000, CRC(60fd4794) SHA1(bbb06181742a3ae6e508247fa3626552b1845ca4) )
	ROM_LOAD64_WORD( "csc_hc01.18m",  0x800004, 0x200000, CRC(9e8a3643) SHA1(1d513b528bca67cea4e1708bf760b97c4a948743) )
	ROM_LOAD64_WORD( "csc_hc01.20m",  0x800006, 0x200000, CRC(eefb5de5) SHA1(bb70dc487995f34fd65c71d564983737debaedea) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "csc.01",   0x00000, 0x08000, CRC(ee162111) SHA1(ce8d4bd32bb10ee8b0274ba6fcef05a583b39d48) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "csc.11m",   0x000000, 0x200000, CRC(a027b827) SHA1(6d58a63efc7bd5d07353d9b55826c01a3c416c33) )
	ROM_LOAD16_WORD_SWAP( "csc.12m",   0x200000, 0x200000, CRC(cb7f6e55) SHA1(b64e6b663fd09e887d2dc0f4b545e88688c0af55) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "csclubj.key",  0x00, 0x14, CRC(519a04db) SHA1(8f792831dc7e07fb621806c4e320a047f801e9b8) )
ROM_END

ROM_START( cybotshc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cyb_hc01.03", 0x000000, 0x80000, CRC(52e1a8a4) SHA1(859137e41f60f9ca79bdace395847a93d335562b) )
	ROM_LOAD16_WORD_SWAP( "cyb_hc01.04", 0x080000, 0x80000, CRC(627be72a) SHA1(43d16f8bcbbdfd02535eaf6dadb2e30b2df33ed8) )
	ROM_LOAD16_WORD_SWAP( "cyb.05",  0x100000, 0x80000, CRC(ec40408e) SHA1(dd611c1708e7ef86e4f7cac4b7b0dff7baaee5ed) )
	ROM_LOAD16_WORD_SWAP( "cyb.06",  0x180000, 0x80000, CRC(1ad0bed2) SHA1(2ea005f3e73b05f8f0ec006cd9e95f7731a73897) )
	ROM_LOAD16_WORD_SWAP( "cyb.07",  0x200000, 0x80000, CRC(6245a39a) SHA1(4f607e733e2dea80211497522be6d0f09571928d) )
	ROM_LOAD16_WORD_SWAP( "cyb.08",  0x280000, 0x80000, CRC(4b48e223) SHA1(9714579a7a78b9716e44bca6c18bf1a93aa4e482) )
	ROM_LOAD16_WORD_SWAP( "cyb.09",  0x300000, 0x80000, CRC(e15238f6) SHA1(16abd92ebed921a6a7e8eac4b098dc61f7e5485c) )
	ROM_LOAD16_WORD_SWAP( "cyb_hc01.10",  0x380000, 0x80000, CRC(bbfd041e) SHA1(240f6705ecc93c6df5cfe380a060a088ad5861f3) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "cyb.13m",   0x0000000, 0x400000, CRC(f0dce192) SHA1(b743938dc8e772dc3f63ed88a4a54c34fffdba21) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.15m",   0x0000002, 0x400000, CRC(187aa39c) SHA1(80e3cf5c69f13343de667e1476bb716d45d3ff63) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.17m",   0x0000004, 0x400000, CRC(8a0e4b12) SHA1(40132f3cc79b0a74460ebd4e0d4ddbe240efc06f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.19m",   0x0000006, 0x400000, CRC(34b62612) SHA1(154bbceb7d303a208abb1b2f3d507d5afacc71ed) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.14m",   0x1000000, 0x400000, CRC(c1537957) SHA1(bfb1cc6786277b94ce28bfd464e2bbb6f6d3486e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.16m",   0x1000002, 0x400000, CRC(15349e86) SHA1(b0cde577d29a9f4e718b673c8645529ef0ababc9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.18m",   0x1000004, 0x400000, CRC(d83e977d) SHA1(e03f4a120c95a2f476ffc8492bca85e0c5cea068) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.20m",   0x1000006, 0x400000, CRC(77cdad5c) SHA1(94d0cc5f05de4bc2d43977d91f887005dc10310c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "cyb.01",   0x00000, 0x08000, CRC(9c0fb079) SHA1(06d260875a76da08d56ea2b2ae277e8c2dbae6e3) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "cyb.02",   0x28000, 0x20000, CRC(51cb0c4e) SHA1(c322957558d8d3e9dad090aebbe485978cbce8f5) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "cyb.11m",   0x000000, 0x200000, CRC(362ccab2) SHA1(28e537067d4846f22657ee37166d18b8f05f4da1) )
	ROM_LOAD16_WORD_SWAP( "cyb.12m",   0x200000, 0x200000, CRC(7066e9cc) SHA1(eb6a9d4998b3311344d73bae88d661d81609c492) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "cybots.key",   0x000000, 0x000014, CRC(9bbcbef3) SHA1(ec7a322c8dceb16c98f7c2837679e91b738fdd0a) )
ROM_END

ROM_START( cybotshc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cybj_hc02.03", 0x000000, 0x80000, CRC(a4fa00db) SHA1(fec6a17933fede227c3ac06b327837c6d5009070) )
	ROM_LOAD16_WORD_SWAP( "cybj.04", 0x080000, 0x80000, CRC(7b0ffaa9) SHA1(595c3e679ea02282bf8a5aa6c7c09e5c30e839c7) )
	ROM_LOAD16_WORD_SWAP( "cyb.05",  0x100000, 0x80000, CRC(ec40408e) SHA1(dd611c1708e7ef86e4f7cac4b7b0dff7baaee5ed) )
	ROM_LOAD16_WORD_SWAP( "cyb.06",  0x180000, 0x80000, CRC(1ad0bed2) SHA1(2ea005f3e73b05f8f0ec006cd9e95f7731a73897) )
	ROM_LOAD16_WORD_SWAP( "cyb.07",  0x200000, 0x80000, CRC(6245a39a) SHA1(4f607e733e2dea80211497522be6d0f09571928d) )
	ROM_LOAD16_WORD_SWAP( "cyb.08",  0x280000, 0x80000, CRC(4b48e223) SHA1(9714579a7a78b9716e44bca6c18bf1a93aa4e482) )
	ROM_LOAD16_WORD_SWAP( "cyb.09",  0x300000, 0x80000, CRC(e15238f6) SHA1(16abd92ebed921a6a7e8eac4b098dc61f7e5485c) )
	ROM_LOAD16_WORD_SWAP( "cyb.10",  0x380000, 0x80000, CRC(75f4003b) SHA1(8a65026ae35247cda016ce85a34034c62b3aa1a6) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "cyb.13m",   0x0000000, 0x400000, CRC(f0dce192) SHA1(b743938dc8e772dc3f63ed88a4a54c34fffdba21) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.15m",   0x0000002, 0x400000, CRC(187aa39c) SHA1(80e3cf5c69f13343de667e1476bb716d45d3ff63) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.17m",   0x0000004, 0x400000, CRC(8a0e4b12) SHA1(40132f3cc79b0a74460ebd4e0d4ddbe240efc06f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.19m",   0x0000006, 0x400000, CRC(34b62612) SHA1(154bbceb7d303a208abb1b2f3d507d5afacc71ed) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.14m",   0x1000000, 0x400000, CRC(c1537957) SHA1(bfb1cc6786277b94ce28bfd464e2bbb6f6d3486e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.16m",   0x1000002, 0x400000, CRC(15349e86) SHA1(b0cde577d29a9f4e718b673c8645529ef0ababc9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.18m",   0x1000004, 0x400000, CRC(d83e977d) SHA1(e03f4a120c95a2f476ffc8492bca85e0c5cea068) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cyb.20m",   0x1000006, 0x400000, CRC(77cdad5c) SHA1(94d0cc5f05de4bc2d43977d91f887005dc10310c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "cyb.01",   0x00000, 0x08000, CRC(9c0fb079) SHA1(06d260875a76da08d56ea2b2ae277e8c2dbae6e3) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "cyb.02",   0x28000, 0x20000, CRC(51cb0c4e) SHA1(c322957558d8d3e9dad090aebbe485978cbce8f5) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "cyb.11m",   0x000000, 0x200000, CRC(362ccab2) SHA1(28e537067d4846f22657ee37166d18b8f05f4da1) )
	ROM_LOAD16_WORD_SWAP( "cyb.12m",   0x200000, 0x200000, CRC(7066e9cc) SHA1(eb6a9d4998b3311344d73bae88d661d81609c492) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "cybotsj.key",  0x00, 0x14, CRC(d4d560b7) SHA1(66f2d85a25140ab9071a0e192ee40e750381bffc) )
ROM_END

ROM_START( ddsomhc01 ) //ddsomjc
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2_hc01.03g", 0x000000, 0x80000, CRC(ed73e646) SHA1(d438e440f8de98cf3bc4d4c47fc8eb9202b0e995) )
	ROM_LOAD16_WORD_SWAP( "dd2_hc01.04g", 0x080000, 0x80000, CRC(c5a6e4b5) SHA1(8f1f285fd73bcce22a1dfdff24dcd8680f791fdc) )
	ROM_LOAD16_WORD_SWAP( "dd2.05g",  0x100000, 0x80000, CRC(5eb1991c) SHA1(429a60b5396ff4192904867fbe0524268f0edbcb) )
	ROM_LOAD16_WORD_SWAP( "dd2_hc01.06",  0x180000, 0x80000, CRC(05c5fd8e) SHA1(21b7c8da9a671c98bdcdb5e65334396b57cc3914) )
	ROM_LOAD16_WORD_SWAP( "dd2.07",   0x200000, 0x80000, CRC(909a0b8b) SHA1(58bda17c36063a79df8b5031755c7909a9bda221) )
	ROM_LOAD16_WORD_SWAP( "dd2.08",   0x280000, 0x80000, CRC(e53c4d01) SHA1(bad872e4e793a39f68bc0e580772e982714b5876) )
	ROM_LOAD16_WORD_SWAP( "dd2_hc01.09",   0x300000, 0x80000, CRC(1547eab4) SHA1(8bc05a1ab05f66e1413cf5fbcee47decbc0c12c5) )
	ROM_LOAD16_WORD_SWAP( "dd2.10",   0x380000, 0x80000, CRC(ad954c26) SHA1(468c01735dbdb1114b37060546a660678290a97f) )

	ROM_REGION( 0x1800000, "gfx", 0 )
	ROMX_LOAD( "dd2.13ms01",   0x0000000, 0x400000, CRC(cf628d3e) SHA1(88a2c87fe14fd67d0b2122324779695329f97963) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.15ms01",   0x0000002, 0x400000, CRC(b7a16e7b) SHA1(1168627ea6544750439887f92722d1d888a10bad) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.17ms01",   0x0000004, 0x400000, CRC(abfc24b4) SHA1(97706ffc1d0dc1d15ba76f3205706e190404cdec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.19ms01",   0x0000006, 0x400000, CRC(2b6b77bf) SHA1(ca9b329012ad4caa539d35942be178f4cb5f92f3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.14ms01",   0x1000000, 0x200000, CRC(358674f5) SHA1(e1326e30377507d61ea315f590da578f17c88b4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.16ms01",   0x1000002, 0x200000, CRC(005cd6e0) SHA1(f4f565149171ac348cd6148002042da078e6e54b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.18ms01",   0x1000004, 0x200000, CRC(01895a06) SHA1(2eaaf9d1005bef712d76e97f37eaba1cda873a5b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.20ms01",   0x1000006, 0x200000, CRC(623c5e89) SHA1(a5a04e9fab7f10d342635a25bfc9d7596350f44e) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "dd2.01",   0x00000, 0x08000, CRC(99d657e5) SHA1(1528dd6b07a0e79951a35c0457c8a9c9770e9c78) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "dd2.02",   0x28000, 0x20000, CRC(117a3824) SHA1(14f3a12170b601c5466c93af9d2f24e0b386b4e4) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2.11m",   0x000000, 0x200000, CRC(98d0c325) SHA1(7406e8d943d77c468eb418c4113261f4ab973bbf) )
	ROM_LOAD16_WORD_SWAP( "dd2.12m",   0x200000, 0x200000, CRC(5ea2e7fa) SHA1(0e6a9fd007f637adcb2226c902394f07de45e803) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ddsomj.key",   0x00, 0x14, CRC(d8dadb22) SHA1(e07b50ae464c35439333dd983e2acac48a1ce529) )
ROM_END

ROM_START( ddsomhc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2j_hc02.03g", 0x000000, 0x80000, CRC(cc650f5b) SHA1(b39dd217b8a4cf82f994e1657909ff001fc4721b) )
	ROM_LOAD16_WORD_SWAP( "dd2j.04g",  0x080000, 0x80000, CRC(8386c0bd) SHA1(59bfc71914ec2bb7d1b9f327b25d2399181d4bb2) )
	ROM_LOAD16_WORD_SWAP( "dd2.05g",   0x100000, 0x80000, CRC(5eb1991c) SHA1(429a60b5396ff4192904867fbe0524268f0edbcb) )
	ROM_LOAD16_WORD_SWAP( "dd2.06g",   0x180000, 0x80000, CRC(c26b5e55) SHA1(9590206f30459941880ff4b56c7f276cc78e3a22) )
	ROM_LOAD16_WORD_SWAP( "dd2_hc02.07", 0x200000, 0x80000, CRC(9c520a00) SHA1(7f801f86ebc725bbbeae9eb832b843b282428ec1) )
	ROM_LOAD16_WORD_SWAP( "dd2.08",   0x280000, 0x80000, CRC(e53c4d01) SHA1(bad872e4e793a39f68bc0e580772e982714b5876) )
	ROM_LOAD16_WORD_SWAP( "dd2.09",   0x300000, 0x80000, CRC(5f86279f) SHA1(c2a454e5f821b1cdd49f2cf0602e9bfb7ba63340) )
	ROM_LOAD16_WORD_SWAP( "dd2.10",   0x380000, 0x80000, CRC(ad954c26) SHA1(468c01735dbdb1114b37060546a660678290a97f) )

	ROM_REGION( 0x1800000, "gfx", 0 )
	ROMX_LOAD( "dd2.13m",   0x0000000, 0x400000, CRC(a46b4e6e) SHA1(fb90f42868c581c481b4ceff9f692753fb186b30) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.15m",   0x0000002, 0x400000, CRC(d5fc50fc) SHA1(bc692f17b18bb47a724cd5152377cd5ccd6e184a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.17m",   0x0000004, 0x400000, CRC(837c0867) SHA1(3d6db290a8f76299a23543f0ccf6a7905e1088ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.19m",   0x0000006, 0x400000, CRC(bb0ec21c) SHA1(e43ccc1cf63ccd2b504cc9fd701af849a7321914) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.14m",   0x1000000, 0x200000, CRC(6d824ce2) SHA1(0ccfe6c8a944937718e28a1a373b5822c7b7001b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.16m",   0x1000002, 0x200000, CRC(79682ae5) SHA1(ee84f4791c29ce9e2bae06ba3ec47ff4d2cd7054) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.18m",   0x1000004, 0x200000, CRC(acddd149) SHA1(7f50de9b2d1cc733594c642be1804190519caffa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.20m",   0x1000006, 0x200000, CRC(117fb0c0) SHA1(15c01fa1a71b6469b0e1bde0ce5835c5ff9d938c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "dd2.01",   0x00000, 0x08000, CRC(99d657e5) SHA1(1528dd6b07a0e79951a35c0457c8a9c9770e9c78) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "dd2.02",   0x28000, 0x20000, CRC(117a3824) SHA1(14f3a12170b601c5466c93af9d2f24e0b386b4e4) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2.11m",   0x000000, 0x200000, CRC(98d0c325) SHA1(7406e8d943d77c468eb418c4113261f4ab973bbf) )
	ROM_LOAD16_WORD_SWAP( "dd2.12m",   0x200000, 0x200000, CRC(5ea2e7fa) SHA1(0e6a9fd007f637adcb2226c902394f07de45e803) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ddsomj.key",   0x00, 0x14, CRC(d8dadb22) SHA1(e07b50ae464c35439333dd983e2acac48a1ce529) )
ROM_END

ROM_START( ddsomhc03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2_hc03.03g", 0x000000, 0x80000, CRC(41429cbc) SHA1(dfd6011a52c8a8c5b42c85ee3c886cd3db8964b9) )
	ROM_LOAD16_WORD_SWAP( "dd2_hc03.04g", 0x080000, 0x80000, CRC(11f7496d) SHA1(b0f64487f8b9e410195ae6810a30b58874c2497c) )
	ROM_LOAD16_WORD_SWAP( "dd2_hc03.05g", 0x100000, 0x80000, CRC(c00d5fb6) SHA1(35b7011905f5f9d12a17171609e71c53b1e1ecb5) )
	ROM_LOAD16_WORD_SWAP( "dd2_hc03.06g", 0x180000, 0x80000, CRC(5eaf9618) SHA1(e9381a81d2bd971666656835991109867341a9a5) )
	ROM_LOAD16_WORD_SWAP( "dd2.07",   0x200000, 0x80000, CRC(909a0b8b) SHA1(58bda17c36063a79df8b5031755c7909a9bda221) )
	ROM_LOAD16_WORD_SWAP( "dd2.08",   0x280000, 0x80000, CRC(e53c4d01) SHA1(bad872e4e793a39f68bc0e580772e982714b5876) )
	ROM_LOAD16_WORD_SWAP( "dd2.09",   0x300000, 0x80000, CRC(5f86279f) SHA1(c2a454e5f821b1cdd49f2cf0602e9bfb7ba63340) )
	ROM_LOAD16_WORD_SWAP( "dd2_hc03.10", 0x380000, 0x80000, CRC(33d55230) SHA1(245b3a99a29c0f11bae4409c1c51f02e102b0fc2) )

	ROM_REGION( 0x1800000, "gfx", 0 )
	ROMX_LOAD( "dd2.13m", 0x0000000, 0x400000, CRC(a46b4e6e) SHA1(fb90f42868c581c481b4ceff9f692753fb186b30) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.15m", 0x0000002, 0x400000, CRC(d5fc50fc) SHA1(bc692f17b18bb47a724cd5152377cd5ccd6e184a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.17m", 0x0000004, 0x400000, CRC(837c0867) SHA1(3d6db290a8f76299a23543f0ccf6a7905e1088ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.19m", 0x0000006, 0x400000, CRC(bb0ec21c) SHA1(e43ccc1cf63ccd2b504cc9fd701af849a7321914) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.14m", 0x1000000, 0x200000, CRC(6d824ce2) SHA1(0ccfe6c8a944937718e28a1a373b5822c7b7001b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.16m", 0x1000002, 0x200000, CRC(79682ae5) SHA1(ee84f4791c29ce9e2bae06ba3ec47ff4d2cd7054) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.18m", 0x1000004, 0x200000, CRC(acddd149) SHA1(7f50de9b2d1cc733594c642be1804190519caffa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.20m", 0x1000006, 0x200000, CRC(117fb0c0) SHA1(15c01fa1a71b6469b0e1bde0ce5835c5ff9d938c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "dd2.01", 0x00000, 0x08000, CRC(99d657e5) SHA1(1528dd6b07a0e79951a35c0457c8a9c9770e9c78) )
	ROM_CONTINUE( 0x10000, 0x18000 )
	ROM_LOAD( "dd2.02", 0x28000, 0x20000, CRC(117a3824) SHA1(14f3a12170b601c5466c93af9d2f24e0b386b4e4) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2.11m", 0x000000, 0x200000, CRC(98d0c325) SHA1(7406e8d943d77c468eb418c4113261f4ab973bbf) )
	ROM_LOAD16_WORD_SWAP( "dd2.12m", 0x200000, 0x200000, CRC(5ea2e7fa) SHA1(0e6a9fd007f637adcb2226c902394f07de45e803) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x000000, 0x000014, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( ddsomhc04 ) //ddsoma4p
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2_hc04.03g", 0x000000, 0x80000, CRC(e28c61f2) SHA1(a15ba7e4d1c6e2e2c047e12edefc6b1564464496) )
	ROM_LOAD16_WORD_SWAP( "dd2_hc04.04g", 0x080000, 0x80000, CRC(145efa6f) SHA1(2da422bf43c4b4abd20ddcf7b0dd4a37f23d756a) )
	ROM_LOAD16_WORD_SWAP( "dd2.05g",  0x100000, 0x80000, CRC(5eb1991c) SHA1(429a60b5396ff4192904867fbe0524268f0edbcb) )
	ROM_LOAD16_WORD_SWAP( "dd2.06g",  0x180000, 0x80000, CRC(c26b5e55) SHA1(9590206f30459941880ff4b56c7f276cc78e3a22) )
	ROM_LOAD16_WORD_SWAP( "dd2.07",   0x200000, 0x80000, CRC(909a0b8b) SHA1(58bda17c36063a79df8b5031755c7909a9bda221) )
	ROM_LOAD16_WORD_SWAP( "dd2.08",   0x280000, 0x80000, CRC(e53c4d01) SHA1(bad872e4e793a39f68bc0e580772e982714b5876) )
	ROM_LOAD16_WORD_SWAP( "dd2.09",   0x300000, 0x80000, CRC(5f86279f) SHA1(c2a454e5f821b1cdd49f2cf0602e9bfb7ba63340) )
	ROM_LOAD16_WORD_SWAP( "dd2.10",   0x380000, 0x80000, CRC(ad954c26) SHA1(468c01735dbdb1114b37060546a660678290a97f) )

	ROM_REGION( 0x1800000, "gfx", 0 )
	ROMX_LOAD( "dd2.13m",   0x0000000, 0x400000, CRC(a46b4e6e) SHA1(fb90f42868c581c481b4ceff9f692753fb186b30) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.15m",   0x0000002, 0x400000, CRC(d5fc50fc) SHA1(bc692f17b18bb47a724cd5152377cd5ccd6e184a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.17m",   0x0000004, 0x400000, CRC(837c0867) SHA1(3d6db290a8f76299a23543f0ccf6a7905e1088ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.19m",   0x0000006, 0x400000, CRC(bb0ec21c) SHA1(e43ccc1cf63ccd2b504cc9fd701af849a7321914) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.14m",   0x1000000, 0x200000, CRC(6d824ce2) SHA1(0ccfe6c8a944937718e28a1a373b5822c7b7001b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.16m",   0x1000002, 0x200000, CRC(79682ae5) SHA1(ee84f4791c29ce9e2bae06ba3ec47ff4d2cd7054) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.18m",   0x1000004, 0x200000, CRC(acddd149) SHA1(7f50de9b2d1cc733594c642be1804190519caffa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dd2.20m",   0x1000006, 0x200000, CRC(117fb0c0) SHA1(15c01fa1a71b6469b0e1bde0ce5835c5ff9d938c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "dd2.01",   0x00000, 0x08000, CRC(99d657e5) SHA1(1528dd6b07a0e79951a35c0457c8a9c9770e9c78) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "dd2.02",   0x28000, 0x20000, CRC(117a3824) SHA1(14f3a12170b601c5466c93af9d2f24e0b386b4e4) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2.11m",   0x000000, 0x200000, CRC(98d0c325) SHA1(7406e8d943d77c468eb418c4113261f4ab973bbf) )
	ROM_LOAD16_WORD_SWAP( "dd2.12m",   0x200000, 0x200000, CRC(5ea2e7fa) SHA1(0e6a9fd007f637adcb2226c902394f07de45e803) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ddsoma.key",   0x00, 0x14, CRC(8c3cc560) SHA1(ad19e78b938a67c9f5ed0dcd5c68b383e6ce0575) )
ROM_END

ROM_START( ddsomhc05 ) //ddsomek
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2k.03g",  0x000000, 0x80000, CRC(e89d22e3) SHA1(d20bcc55ed92dc391ec25504956aa8a0895f0a24) )
	ROM_LOAD16_WORD_SWAP( "dd2k.04g",  0x080000, 0x80000, CRC(9a44d69c) SHA1(1bc2907058581fa39ddbbea5184cef9eac8a81c8) )
	ROM_LOAD16_WORD_SWAP( "dd2.05g",   0x100000, 0x80000, CRC(5eb1991c) SHA1(429a60b5396ff4192904867fbe0524268f0edbcb) )
	ROM_LOAD16_WORD_SWAP( "dd2k.06g",  0x180000, 0x80000, CRC(7f7ded68) SHA1(2a4784cf8156e5874f7b28d1995ba387d2530c67) )
	ROM_LOAD16_WORD_SWAP( "dd2.07",    0x200000, 0x80000, CRC(909a0b8b) SHA1(58bda17c36063a79df8b5031755c7909a9bda221) )
	ROM_LOAD16_WORD_SWAP( "dd2.08",    0x280000, 0x80000, CRC(e53c4d01) SHA1(bad872e4e793a39f68bc0e580772e982714b5876) )
	ROM_LOAD16_WORD_SWAP( "dd2k.09",   0x300000, 0x80000, CRC(62f76683) SHA1(3ba1620c096e38b2ba108d69441f83aa4d5cc741) )
	ROM_LOAD16_WORD_SWAP( "dd2k.10",   0x380000, 0x80000, CRC(df5efd28) SHA1(fc5079c4e2b316b9787e79391e80e59cad099a68) )

	ROM_REGION( 0x1800000, "gfx", 0 )
	ROM_LOAD64_WORD( "dd2k.13m", 0x0000000, 0x400000, CRC(9da53675) SHA1(39a2b51ea8da7fe271a86c8ac1f98bdb637f06ac) )
	ROM_LOAD64_WORD( "dd2k.15m", 0x0000002, 0x400000, CRC(78a5c30f) SHA1(254b551dad21fa6ea965d3c7f1cc7d3600a7cc89) )
	ROM_LOAD64_WORD( "dd2k.17m", 0x0000004, 0x400000, CRC(7289bac1) SHA1(117e693ecea88d8249a6440d2fb3113428aaaaa3) )
	ROM_LOAD64_WORD( "dd2k.19m", 0x0000006, 0x400000, CRC(e23746e8) SHA1(7ec101f0bb001ec88a77b88999f21d6b3746165b) )
	ROM_LOAD64_WORD( "dd2k.14m", 0x1000000, 0x200000, CRC(75b8fd5d) SHA1(3cd27336027d9aabcaef4a57f7155df3221ab209) )
	ROM_LOAD64_WORD( "dd2k.16m", 0x1000002, 0x200000, CRC(9187a205) SHA1(c5caa3ef637fe88c98d16860c2fb4d95e44e7a7a) )
	ROM_LOAD64_WORD( "dd2k.18m", 0x1000004, 0x200000, CRC(7e4fad8a) SHA1(fbc4f90722018efa5ffa2882cdcca5098666a864) )
	ROM_LOAD64_WORD( "dd2k.20m", 0x1000006, 0x200000, CRC(2d5bb55c) SHA1(faf8c1f59c8f19dc9f7d1a23a8fc15ef4ed995cd) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "dd2.01",   0x00000, 0x08000, CRC(99d657e5) SHA1(1528dd6b07a0e79951a35c0457c8a9c9770e9c78) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "dd2.02",   0x28000, 0x20000, CRC(117a3824) SHA1(14f3a12170b601c5466c93af9d2f24e0b386b4e4) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "dd2.11m",   0x000000, 0x200000, CRC(98d0c325) SHA1(7406e8d943d77c468eb418c4113261f4ab973bbf) )
	ROM_LOAD16_WORD_SWAP( "dd2.12m",   0x200000, 0x200000, CRC(5ea2e7fa) SHA1(0e6a9fd007f637adcb2226c902394f07de45e803) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ddsoma.key",   0x00, 0x14, CRC(8c3cc560) SHA1(ad19e78b938a67c9f5ed0dcd5c68b383e6ce0575) )
ROM_END

ROM_START( ddtodhc01 ) //ddtodd
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "daded_hc01.03c", 0x000000, 0x80000, CRC(748d17d3) SHA1(43c1fc9352dbf4e62b78e9eb7003480eb915cd82) )
	ROM_LOAD16_WORD_SWAP( "daded.04c", 0x080000, 0x80000, CRC(306f14fc) SHA1(b684ee72acc3087ada20b2d13202366c3cff1014) )
	ROM_LOAD16_WORD_SWAP( "daded.05c", 0x100000, 0x80000, CRC(8c6b8328) SHA1(ab5d2c608bd3cdb298a9743d819616bf2df02ddd) )
	ROM_LOAD16_WORD_SWAP( "dad_hc01.06a",   0x180000, 0x80000, CRC(1005b2d7) SHA1(00c3d60f1582b9143ff2dcb385c886809a4b14a3) )
	ROM_LOAD16_WORD_SWAP( "dadd.07a",  0x200000, 0x80000, CRC(0f0df6cc) SHA1(5da5f989ed71faf5e2950fdf9650d94918616ae4) )

	ROM_REGION16_BE( CODE_SIZE, "user1", 0 )
	ROM_FILL( 0x000000, 0x100000, 0x00 )

	ROM_REGION( 0xc00000, "gfx", 0 )
	ROMX_LOAD( "dad.13m",   0x000000, 0x200000, CRC(da3cb7d6) SHA1(d59bb53d5f32889eb6eb7f8b1c8781948c97283d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dad.15m",   0x000002, 0x200000, CRC(92b63172) SHA1(9bed7dbbb17729f2ad3d318396f5335c0bd39937) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dad.17m",   0x000004, 0x200000, CRC(b98757f5) SHA1(3eead22e097906bf0e1e151cd0a9c75abc5a32d4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dad.19m",   0x000006, 0x200000, CRC(8121ce46) SHA1(40c4dc969318d38f0c6d5401c9c64371f51aa12c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dad.14m",   0x800000, 0x100000, CRC(837e6f3f) SHA1(c060183474fba0e82d765b9f282b84838550dff6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dad.16m",   0x800002, 0x100000, CRC(f0916bdb) SHA1(9354d258dd26cbbf12c78ecfc277c357cbdb360e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dad.18m",   0x800004, 0x100000, CRC(cef393ef) SHA1(830b33c86cc24776d17ad65fa89a3b16c40446a1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "dad.20m",   0x800006, 0x100000, CRC(8953fe9e) SHA1(f4795beb006335d13e3934aa9760e775eb0bb950) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "dad.01",   0x00000, 0x08000, CRC(3f5e2424) SHA1(4aa744576bc6752c43a90a27a816ebd90076b248) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "dad.11m",   0x000000, 0x200000, CRC(0c499b67) SHA1(a8ebd8a1cd6dece8344b7cb0439d85843fb97616) )
	ROM_LOAD16_WORD_SWAP( "dad.12m",   0x200000, 0x200000, CRC(2f0b5a4e) SHA1(8d1ebbb811aa469b0f0d29d719d2b9af28fb63a2) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x000000, 0x000014, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( ddtodhc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "dada_hc02.03c", 0x000000, 0x80000, CRC(fc8b949f) SHA1(b0442bf6036dcab41738612aa54849d717467d39) )
	ROM_LOAD16_WORD_SWAP( "dada_hc02.04c", 0x080000, 0x80000, CRC(f931f325) SHA1(f0bdd649b302007f452a633bb9ac1788aa0cee1f) )
	ROM_LOAD16_WORD_SWAP( "dada_hc02.05c", 0x100000, 0x80000, CRC(3fc42c7e) SHA1(b14c0be83cfdb7803ea023886ccdee20147a817f) )
	ROM_LOAD16_WORD_SWAP( "dadk.06a",  0x180000, 0x80000, CRC(e9fc6884) SHA1(fdd436925a471e665ffeace676be4106568c6dd4) )
	ROM_LOAD16_WORD_SWAP( "dad.07a",  0x200000, 0x80000, CRC(b3480ec3) SHA1(a66f8dba67101fd71c2af4f3c3d71e55778a9f2c) )

	ROM_REGION( 0xc00000, "gfx", 0 )
	ROM_LOAD64_WORD( "dad_hc02.13m",   0x000000, 0x200000, CRC(d89b6f34) SHA1(ba5a83ef7db0f675ec6b981efbbda423e969c682) )
	ROM_LOAD64_WORD( "dad_hc02.15m",   0x000002, 0x200000, CRC(09939159) SHA1(b90e9fd102d2d8e85148c7d7f4a040540729691a) )
	ROM_LOAD64_WORD( "dad_hc02.17m",   0x000004, 0x200000, CRC(f1678c95) SHA1(eeb7a0796e10f4ee27b6e66e40360f6d837686ac) )
	ROM_LOAD64_WORD( "dad_hc02.19m",   0x000006, 0x200000, CRC(62bbaec0) SHA1(34a2450348ef016f11fa86178bb74b0771f03eb4) )
	ROM_LOAD64_WORD( "dad_hc02.14m",   0x800000, 0x100000, CRC(d36dfb89) SHA1(59b135654e339e6c96b213311c5478843af0c46c) )
	ROM_LOAD64_WORD( "dad_hc02.16m",   0x800002, 0x100000, CRC(d3c7bde7) SHA1(4c58fabbb034f2de944c727f66a37ded01bbcbb4) )
	ROM_LOAD64_WORD( "dad_hc02.18m",   0x800004, 0x100000, CRC(9ee00759) SHA1(e2eeedd8a5d918432095db8d7c6bd479af7308e0) )
	ROM_LOAD64_WORD( "dad_hc02.20m",   0x800006, 0x100000, CRC(aa0528a2) SHA1(2ed1a14a48caaad11ca7724ceae2ed5af7c4fbb8) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "dad.01",   0x00000, 0x08000, CRC(3f5e2424) SHA1(4aa744576bc6752c43a90a27a816ebd90076b248) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "dad.11m",   0x000000, 0x200000, CRC(0c499b67) SHA1(a8ebd8a1cd6dece8344b7cb0439d85843fb97616) )
	ROM_LOAD16_WORD_SWAP( "dad.12m",   0x200000, 0x200000, CRC(2f0b5a4e) SHA1(8d1ebbb811aa469b0f0d29d719d2b9af28fb63a2) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ddtoda.key",   0x000000, 0x000014, CRC(e5e8d1b8) SHA1(04667003776e2dbd207933b5c707bed635871cac) )
ROM_END

ROM_START( dstlkhc01 ) //dstlkl
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "vame_hc01.03a", 0x000000, 0x80000, CRC(062da6f1) SHA1(6f470b5a68d70f066fbb29e88d819496de611713) )
	ROM_LOAD16_WORD_SWAP( "vame.04a", 0x080000, 0x80000, CRC(ae413ff2) SHA1(e9b85ac04d6d1a57368c70aa24e3ab8a8d67409f) )
	ROM_LOAD16_WORD_SWAP( "vame.05a", 0x100000, 0x80000, CRC(60678756) SHA1(5d10829ad7522b5de3b318dd8cbf1b506ba4c2d4) )
	ROM_LOAD16_WORD_SWAP( "vame.06a", 0x180000, 0x80000, CRC(912870b3) SHA1(9c7620c7e25d236050411ba94fbc5b3b501970a3) )
	ROM_LOAD16_WORD_SWAP( "vame.07a", 0x200000, 0x80000, CRC(dabae3e8) SHA1(126f8433491db36649f5e1908bbe45eb123048e4) )
	ROM_LOAD16_WORD_SWAP( "vame.08a", 0x280000, 0x80000, CRC(2c6e3077) SHA1(d8042312ec546e3e807e3ef0a14af9b4f716e415) )
	ROM_LOAD16_WORD_SWAP( "vame.09a", 0x300000, 0x80000, CRC(f16db74b) SHA1(7b7e31916a61e7fb35ec20849c6d22d74e169ec0) )
	ROM_LOAD16_WORD_SWAP( "vame.10a", 0x380000, 0x80000, CRC(701e2147) SHA1(c0a0603e01fbed67a600b83902091c1073e2ed27) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "vam.13m",   0x0000000, 0x400000, CRC(c51baf99) SHA1(2fb6642908e542e404391eb17392f8270e87bf48) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.15m",   0x0000002, 0x400000, CRC(3ce83c77) SHA1(93369b23c6d7d834297434691bb047ee3dd9539c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.17m",   0x0000004, 0x400000, CRC(4f2408e0) SHA1(cd49c6b3c7e6470c6058f98ccc5210b052bb13e2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.19m",   0x0000006, 0x400000, CRC(9ff60250) SHA1(d69ba4dc6bd37d003245f0cf3211d6e2623005b8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.14m",   0x1000000, 0x100000, CRC(bd87243c) SHA1(87b33aeb72514e1228ffc27ec6dd534f14882760) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.16m",   0x1000002, 0x100000, CRC(afec855f) SHA1(cd117833b8d475489b90ff44b57e2c5cb1af3af5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.18m",   0x1000004, 0x100000, CRC(3a033625) SHA1(294238f30cba5cf4f8f1de951d54c2077bd95de9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.20m",   0x1000006, 0x100000, CRC(2bff6a89) SHA1(8f4e131e5ce0af48fb89f98026d9f0356c7c301f) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "vam.01",   0x00000, 0x08000, CRC(64b685d5) SHA1(6c180e7420db754eca5cad17a40f5a64f5c3bd15) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "vam.02",   0x28000, 0x20000, CRC(cf7c97c7) SHA1(109a4b56ecd59be9c3f5869de99d40619bdaef21) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "vam.11m",   0x000000, 0x200000, CRC(4a39deb2) SHA1(7e63e615869958db66a4e52a0272afee5a10e446) )
	ROM_LOAD16_WORD_SWAP( "vam.12m",   0x200000, 0x200000, CRC(1a3e5c03) SHA1(c5a556e125d6c3d68da745b4d56cd7a851f2a23d) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "dstlk.key",    0x000000, 0x000014, CRC(cfa46dec) SHA1(ce57b3d53557f04ac53dac97d67374c288d85866) )
ROM_END

ROM_START( dstlkhc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "vamj_hc02.03a", 0x000000, 0x80000, CRC(55c1be82) SHA1(948e1e322945adc775da8b22165697b5c7999b1b) )
	ROM_LOAD16_WORD_SWAP( "vamj_hc02.04b", 0x080000, 0x80000, CRC(9c12017e) SHA1(0800802748ce61b01a18c06b61fcb8fd7bb34f62) )
	ROM_LOAD16_WORD_SWAP( "vamj.05a", 0x100000, 0x80000, CRC(6c497e92) SHA1(7c1ccdfd77fb50afe024c8402376daaeab641a24) )
	ROM_LOAD16_WORD_SWAP( "vamj.06a", 0x180000, 0x80000, CRC(f1bbecb6) SHA1(6adba89393e05f16f70b57085cabd6b4c20f53e8) )
	ROM_LOAD16_WORD_SWAP( "vamj.07a", 0x200000, 0x80000, CRC(1067ad84) SHA1(5e4cc75cfdfd512b6230c656e7304262b5143aee) )
	ROM_LOAD16_WORD_SWAP( "vamj.08a", 0x280000, 0x80000, CRC(4b89f41f) SHA1(bd78f33a6d448655eecf7448921d282b302fa4cb) )
	ROM_LOAD16_WORD_SWAP( "vamj.09a", 0x300000, 0x80000, CRC(fc0a4aac) SHA1(a2c79eb4dc838c238e182a4da3567ac8db3488d8) )
	ROM_LOAD16_WORD_SWAP( "vamj.10a", 0x380000, 0x80000, CRC(9270c26b) SHA1(c2a7e199a74c9f27704cf935483ebddc6da256a1) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "vam.13m",   0x0000000, 0x400000, CRC(c51baf99) SHA1(2fb6642908e542e404391eb17392f8270e87bf48) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.15m",   0x0000002, 0x400000, CRC(3ce83c77) SHA1(93369b23c6d7d834297434691bb047ee3dd9539c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.17m",   0x0000004, 0x400000, CRC(4f2408e0) SHA1(cd49c6b3c7e6470c6058f98ccc5210b052bb13e2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.19m",   0x0000006, 0x400000, CRC(9ff60250) SHA1(d69ba4dc6bd37d003245f0cf3211d6e2623005b8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.14m",   0x1000000, 0x100000, CRC(bd87243c) SHA1(87b33aeb72514e1228ffc27ec6dd534f14882760) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.16m",   0x1000002, 0x100000, CRC(afec855f) SHA1(cd117833b8d475489b90ff44b57e2c5cb1af3af5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.18m",   0x1000004, 0x100000, CRC(3a033625) SHA1(294238f30cba5cf4f8f1de951d54c2077bd95de9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "vam.20m",   0x1000006, 0x100000, CRC(2bff6a89) SHA1(8f4e131e5ce0af48fb89f98026d9f0356c7c301f) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "vam.01",   0x00000, 0x08000, CRC(64b685d5) SHA1(6c180e7420db754eca5cad17a40f5a64f5c3bd15) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "vam.02",   0x28000, 0x20000, CRC(cf7c97c7) SHA1(109a4b56ecd59be9c3f5869de99d40619bdaef21) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "vam.11m",   0x000000, 0x200000, CRC(4a39deb2) SHA1(7e63e615869958db66a4e52a0272afee5a10e446) )
	ROM_LOAD16_WORD_SWAP( "vam.12m",   0x200000, 0x200000, CRC(1a3e5c03) SHA1(c5a556e125d6c3d68da745b4d56cd7a851f2a23d) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "vampj.key",    0x00, 0x14, CRC(8418cc6f) SHA1(e7128ac94fc7c37a64e4640db08f1769215769e5) )
ROM_END

ROM_START( ffightaec2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ff-23m.8h", 0x000000, 0x80000, CRC(b598d599) SHA1(f4e5ebc3c1900fbfb004f8e6532ffb8593622fe5) )
	ROM_LOAD16_WORD_SWAP( "ff-22m.7h", 0x080000, 0x80000, CRC(3615cfb9) SHA1(f83ebdb084505b3c35513f40666ad828846339d2) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "ff-5m.7a", 0x000000, 0x400000, CRC(3f4028c5) SHA1(4a4cf19422f4f0fc66ce18ea082320c5adb59750) )
	ROM_LOAD64_WORD( "ff-7m.9a", 0x000002, 0x400000, CRC(be3858b0) SHA1(ec9e1be10bba4c3b8bf35fca821cd7f4025dfb4a) )
	ROM_LOAD64_WORD( "ff-1m.3a", 0x000004, 0x400000, CRC(ed622314) SHA1(f7155a41d4fdbcdd4e626b86de18c391125298e3) )
	ROM_LOAD64_WORD( "ff-3m.5a", 0x000006, 0x400000, CRC(d65b53e9) SHA1(6df4aa177a38407814a35a3560da4e9c301b3fa0) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz3.01",   0x00000, 0x08000, CRC(7ee68d38) SHA1(d533226911c23be34aa9df7d7ee37a0b2cf407ab) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz3.02",   0x28000, 0x20000, CRC(72445dc4) SHA1(14fca7596ac45ba655016eef5b6120f9f9671c23) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3.11m",   0x000000, 0x400000, CRC(71af8d5a) SHA1(8e9dfcd1d44f792cff4b13f8b8f73aa8f9b0a2ec) )
	ROM_LOAD16_WORD_SWAP( "sz3.12m",   0x400000, 0x400000, CRC(f392b13a) SHA1(fa04ce0370144a49bd1d5acd873eef87b0dc9d15) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x00, 0x14, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( ffightaec2ds )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ffaeds-23m.8h", 0x000000, 0x80000, CRC(b598d599) SHA1(f4e5ebc3c1900fbfb004f8e6532ffb8593622fe5) )
	ROM_LOAD16_WORD_SWAP( "ffaeds-22m.7h", 0x080000, 0x80000, CRC(3615cfb9) SHA1(f83ebdb084505b3c35513f40666ad828846339d2) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "ff-5m.7a", 0x000000, 0x400000, CRC(3f4028c5) SHA1(4a4cf19422f4f0fc66ce18ea082320c5adb59750) )
	ROM_LOAD64_WORD( "ff-7m.9a", 0x000002, 0x400000, CRC(be3858b0) SHA1(ec9e1be10bba4c3b8bf35fca821cd7f4025dfb4a) )
	ROM_LOAD64_WORD( "ff-1m.3a", 0x000004, 0x400000, CRC(ed622314) SHA1(f7155a41d4fdbcdd4e626b86de18c391125298e3) )
	ROM_LOAD64_WORD( "ff-3m.5a", 0x000006, 0x400000, CRC(d65b53e9) SHA1(6df4aa177a38407814a35a3560da4e9c301b3fa0) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz3.01",   0x00000, 0x08000, CRC(7ee68d38) SHA1(d533226911c23be34aa9df7d7ee37a0b2cf407ab) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz3.02",   0x28000, 0x20000, CRC(72445dc4) SHA1(14fca7596ac45ba655016eef5b6120f9f9671c23) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3.11m",   0x000000, 0x400000, CRC(71af8d5a) SHA1(8e9dfcd1d44f792cff4b13f8b8f73aa8f9b0a2ec) )
	ROM_LOAD16_WORD_SWAP( "sz3.12m",   0x400000, 0x400000, CRC(f392b13a) SHA1(fa04ce0370144a49bd1d5acd873eef87b0dc9d15) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x00, 0x14, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( gigawinghc01 ) //gigawingh
	ROM_REGION(CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ggwu_hc01.03", 0x000000, 0x80000, CRC(c85a97ba) SHA1(ac0a0677bc82507cc742f49a76b2e84a3e5729e1) )
	ROM_LOAD16_WORD_SWAP( "ggwu.04", 0x080000, 0x80000, CRC(392f4118) SHA1(3bb0bd9503ef60892d5abd8640af524cf71da848) )
	ROM_LOAD16_WORD_SWAP( "ggw.05",  0x100000, 0x80000, CRC(3239d642) SHA1(2fe3984c46a72aedb30a28e3db5af2612bdf0045) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "ggw.13m",   0x000000, 0x400000, CRC(105530a4) SHA1(3be06c032985ea6bd3805d73a407bf748385087b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ggw.15m",   0x000002, 0x400000, CRC(9e774ab9) SHA1(adea1e844f3d9ccd5ad116ff8277f16a96e68d76) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ggw.17m",   0x000004, 0x400000, CRC(466e0ba4) SHA1(9563455b95d36fafe508290659088b153539cfdf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ggw.19m",   0x000006, 0x400000, CRC(840c8dea) SHA1(ea04afce17f00b45d3d2cd5140d0dd7ab4bccc00) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION(QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "ggw.01",   0x00000, 0x08000, CRC(4c6351d5) SHA1(cef81fb7c4b8cb2ef1f8f3c27982aefbcbe38160) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "ggw.11m",   0x000000, 0x400000, CRC(e172acf5) SHA1(d7b0963d66165f3607d887741c5e7ab952bcf2ff) )
	ROM_LOAD16_WORD_SWAP( "ggw.12m",   0x400000, 0x400000, CRC(4bee4e8f) SHA1(c440b5a38359ec3b8002f39690b79bf78703f5d0) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "gigawing.key", 0x000000, 0x000014, CRC(5076c26b) SHA1(81a0aa6768a1e94aed25503ad8b3814bb23c41b5) )
ROM_END

ROM_START( hsf2hc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2_hc01.03",  0x000000, 0x80000, CRC(bf63d85b) SHA1(6ce1e31b85c9086e04de614b0c4a5280dfc2d46a) )
	ROM_LOAD16_WORD_SWAP( "hs2_hc01.04",  0x080000, 0x80000, CRC(c1c0c809) SHA1(ba26bbc4c6ff17bfcc87618d720a2bcba202e4ab) )
	ROM_LOAD16_WORD_SWAP( "hs2.05",   0x100000, 0x80000, CRC(dde34a35) SHA1(f5be2d2916db6e86e0886d61d55bddf138273ebc) )
	ROM_LOAD16_WORD_SWAP( "hs2.06",   0x180000, 0x80000, CRC(f4e56dda) SHA1(c6490707c2a416ab88612c2d73abbe5853d8cb92) )
	ROM_LOAD16_WORD_SWAP( "hs2.07",   0x200000, 0x80000, CRC(ee4420fc) SHA1(06cf76660b0c794d2460c52d9fe8334fff51e9de) )
	ROM_LOAD16_WORD_SWAP( "hs2.08",   0x280000, 0x80000, CRC(c9441533) SHA1(bf178fac1f060fcce3ff9118333c8517dadc9429) )
	ROM_LOAD16_WORD_SWAP( "hs2.09",   0x300000, 0x80000, CRC(3fc638a8) SHA1(2a42877b26c8abc437da46225701f0bba6e40058) )
	ROM_LOAD16_WORD_SWAP( "hs2.10",   0x380000, 0x80000, CRC(20d0f9e4) SHA1(80a5eeef9472e327b0d4ee26434bad109a9434ea) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "hs2.13m",   0x0000000, 0x800000, CRC(a6ecab17) SHA1(6749a4c8dc81f4b10f910c31c82cf6674e2a44eb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.15m",   0x0000002, 0x800000, CRC(10a0ae4d) SHA1(701b4900fbc8bef20efa1a706891c8df4bf14641) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.17m",   0x0000004, 0x800000, CRC(adfa7726) SHA1(8d36ec125a8c91abfe5213893d794f8bc11c8acd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.19m",   0x0000006, 0x800000, CRC(bb3ae322) SHA1(ecd289d7a0fe365fdd7c5527cb17796002beb553) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "hs2.01",   0x00000, 0x08000, CRC(c1a13786) SHA1(c7392c7efb15ea4042e75bd9007e974293d8935d) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "hs2.02",   0x28000, 0x20000, CRC(2d8794aa) SHA1(c634affdc2568020cce6af97b4fa79925d9943f3) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2.11m",   0x000000, 0x800000, CRC(0e15c359) SHA1(176108b0d76d821a849324680aba0cd04b5016c1) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "hsf2j.key",    0x00, 0x14, CRC(19455a93) SHA1(925cee29b37cb7a4048383ac715ad96f83280d37) )
ROM_END

ROM_START( hsf2hc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2_hc02.03", 0x000000, 0x80000, CRC(d6fbe270) SHA1(ea7cc743127521404635aa608a1a23c62d251f4f) )
	ROM_LOAD16_WORD_SWAP( "hs2_hc02.04", 0x080000, 0x80000, CRC(50b4b202) SHA1(866b0a69ba188d6faed8ea2a821a02bc6ffc1f53) )
	ROM_LOAD16_WORD_SWAP( "hs2.05",   0x100000, 0x80000, CRC(dde34a35) SHA1(f5be2d2916db6e86e0886d61d55bddf138273ebc) )
	ROM_LOAD16_WORD_SWAP( "hs2.06",   0x180000, 0x80000, CRC(f4e56dda) SHA1(c6490707c2a416ab88612c2d73abbe5853d8cb92) )
	ROM_LOAD16_WORD_SWAP( "hs2.07",   0x200000, 0x80000, CRC(ee4420fc) SHA1(06cf76660b0c794d2460c52d9fe8334fff51e9de) )
	ROM_LOAD16_WORD_SWAP( "hs2.08",   0x280000, 0x80000, CRC(c9441533) SHA1(bf178fac1f060fcce3ff9118333c8517dadc9429) )
	ROM_LOAD16_WORD_SWAP( "hs2.09",   0x300000, 0x80000, CRC(3fc638a8) SHA1(2a42877b26c8abc437da46225701f0bba6e40058) )
	ROM_LOAD16_WORD_SWAP( "hs2.10",   0x380000, 0x80000, CRC(20d0f9e4) SHA1(80a5eeef9472e327b0d4ee26434bad109a9434ea) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "hs2.13m",   0x0000000, 0x800000, CRC(a6ecab17) SHA1(6749a4c8dc81f4b10f910c31c82cf6674e2a44eb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.15m",   0x0000002, 0x800000, CRC(10a0ae4d) SHA1(701b4900fbc8bef20efa1a706891c8df4bf14641) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.17m",   0x0000004, 0x800000, CRC(adfa7726) SHA1(8d36ec125a8c91abfe5213893d794f8bc11c8acd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.19m",   0x0000006, 0x800000, CRC(bb3ae322) SHA1(ecd289d7a0fe365fdd7c5527cb17796002beb553) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "hs2.01",   0x00000, 0x08000, CRC(c1a13786) SHA1(c7392c7efb15ea4042e75bd9007e974293d8935d) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "hs2.02",   0x28000, 0x20000, CRC(2d8794aa) SHA1(c634affdc2568020cce6af97b4fa79925d9943f3) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2.11m",   0x000000, 0x800000, CRC(0e15c359) SHA1(176108b0d76d821a849324680aba0cd04b5016c1) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "hsf2j.key",    0x00, 0x14, CRC(19455a93) SHA1(925cee29b37cb7a4048383ac715ad96f83280d37) )
ROM_END

ROM_START( hsf2hc03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2j_hc03.03",  0x000000, 0x80000, CRC(252b335d) SHA1(68a710cbac6377cf3276289c3ee641be968ba15b) )
	ROM_LOAD16_WORD_SWAP( "hs2j.04",  0x080000, 0x80000, CRC(40072c4a) SHA1(85b95bd3c907b4276a31777e092b8c40d3763257) )
	ROM_LOAD16_WORD_SWAP( "hs2.05",   0x100000, 0x80000, CRC(dde34a35) SHA1(f5be2d2916db6e86e0886d61d55bddf138273ebc) )
	ROM_LOAD16_WORD_SWAP( "hs2.06",   0x180000, 0x80000, CRC(f4e56dda) SHA1(c6490707c2a416ab88612c2d73abbe5853d8cb92) )
	ROM_LOAD16_WORD_SWAP( "hs2.07",   0x200000, 0x80000, CRC(ee4420fc) SHA1(06cf76660b0c794d2460c52d9fe8334fff51e9de) )
	ROM_LOAD16_WORD_SWAP( "hs2.08",   0x280000, 0x80000, CRC(c9441533) SHA1(bf178fac1f060fcce3ff9118333c8517dadc9429) )
	ROM_LOAD16_WORD_SWAP( "hs2.09",   0x300000, 0x80000, CRC(3fc638a8) SHA1(2a42877b26c8abc437da46225701f0bba6e40058) )
	ROM_LOAD16_WORD_SWAP( "hs2.10",   0x380000, 0x80000, CRC(20d0f9e4) SHA1(80a5eeef9472e327b0d4ee26434bad109a9434ea) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "hs2.13m",   0x0000000, 0x800000, CRC(a6ecab17) SHA1(6749a4c8dc81f4b10f910c31c82cf6674e2a44eb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.15m",   0x0000002, 0x800000, CRC(10a0ae4d) SHA1(701b4900fbc8bef20efa1a706891c8df4bf14641) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.17m",   0x0000004, 0x800000, CRC(adfa7726) SHA1(8d36ec125a8c91abfe5213893d794f8bc11c8acd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.19m",   0x0000006, 0x800000, CRC(bb3ae322) SHA1(ecd289d7a0fe365fdd7c5527cb17796002beb553) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "hs2.01",   0x00000, 0x08000, CRC(c1a13786) SHA1(c7392c7efb15ea4042e75bd9007e974293d8935d) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "hs2.02",   0x28000, 0x20000, CRC(2d8794aa) SHA1(c634affdc2568020cce6af97b4fa79925d9943f3) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2.11m",   0x000000, 0x800000, CRC(0e15c359) SHA1(176108b0d76d821a849324680aba0cd04b5016c1) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "hsf2j.key",    0x00, 0x14, CRC(19455a93) SHA1(925cee29b37cb7a4048383ac715ad96f83280d37) )
ROM_END

ROM_START( hsf2hc04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2_hc04.03c", 0x000000, 0x80000, CRC(b5952336) SHA1(e5396781d525343b285613255bbafa77aa53ed31) )
	ROM_LOAD16_WORD_SWAP( "hs2_hc04.04b", 0x080000, 0x80000, CRC(7a02d7b6) SHA1(00c69673cadb86efaa8c96c778d3b4a9f61bd1e4) )
	ROM_LOAD16_WORD_SWAP( "hs2.05",  0x100000, 0x80000, CRC(dde34a35) SHA1(f5be2d2916db6e86e0886d61d55bddf138273ebc) )
	ROM_LOAD16_WORD_SWAP( "hs2.06",  0x180000, 0x80000, CRC(f4e56dda) SHA1(c6490707c2a416ab88612c2d73abbe5853d8cb92) )
	ROM_LOAD16_WORD_SWAP( "hs2.07",  0x200000, 0x80000, CRC(ee4420fc) SHA1(06cf76660b0c794d2460c52d9fe8334fff51e9de) )
	ROM_LOAD16_WORD_SWAP( "hs2.08",  0x280000, 0x80000, CRC(c9441533) SHA1(bf178fac1f060fcce3ff9118333c8517dadc9429) )
	ROM_LOAD16_WORD_SWAP( "hs2.09",  0x300000, 0x80000, CRC(3fc638a8) SHA1(2a42877b26c8abc437da46225701f0bba6e40058) )
	ROM_LOAD16_WORD_SWAP( "hs2.10",  0x380000, 0x80000, CRC(20d0f9e4) SHA1(80a5eeef9472e327b0d4ee26434bad109a9434ea) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "hs2.13m",   0x0000000, 0x800000, CRC(a6ecab17) SHA1(6749a4c8dc81f4b10f910c31c82cf6674e2a44eb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.15m",   0x0000002, 0x800000, CRC(10a0ae4d) SHA1(701b4900fbc8bef20efa1a706891c8df4bf14641) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.17m",   0x0000004, 0x800000, CRC(adfa7726) SHA1(8d36ec125a8c91abfe5213893d794f8bc11c8acd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.19m",   0x0000006, 0x800000, CRC(bb3ae322) SHA1(ecd289d7a0fe365fdd7c5527cb17796002beb553) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "hs2.01",   0x00000, 0x08000, CRC(c1a13786) SHA1(c7392c7efb15ea4042e75bd9007e974293d8935d) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "hs2.02",   0x28000, 0x20000, CRC(2d8794aa) SHA1(c634affdc2568020cce6af97b4fa79925d9943f3) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2.11m",   0x000000, 0x800000, CRC(0e15c359) SHA1(176108b0d76d821a849324680aba0cd04b5016c1) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x00, 0x14, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( hsf2hc05 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2_hc05.03",  0x000000, 0x80000, CRC(2ef3f7db) SHA1(062eb0f2a38c23557cc0723e74ea458f7c3d6f61) )
	ROM_LOAD16_WORD_SWAP( "hs2u.04",  0x080000, 0x80000, CRC(327aa49c) SHA1(6719cd6ecc2a4487fdbf5cbcd47e35fc43000607) )
	ROM_LOAD16_WORD_SWAP( "hs2.05",   0x100000, 0x80000, CRC(dde34a35) SHA1(f5be2d2916db6e86e0886d61d55bddf138273ebc) )
	ROM_LOAD16_WORD_SWAP( "hs2.06",   0x180000, 0x80000, CRC(f4e56dda) SHA1(c6490707c2a416ab88612c2d73abbe5853d8cb92) )
	ROM_LOAD16_WORD_SWAP( "hs2.07",   0x200000, 0x80000, CRC(ee4420fc) SHA1(06cf76660b0c794d2460c52d9fe8334fff51e9de) )
	ROM_LOAD16_WORD_SWAP( "hs2.08",   0x280000, 0x80000, CRC(c9441533) SHA1(bf178fac1f060fcce3ff9118333c8517dadc9429) )
	ROM_LOAD16_WORD_SWAP( "hs2.09",   0x300000, 0x80000, CRC(3fc638a8) SHA1(2a42877b26c8abc437da46225701f0bba6e40058) )
	ROM_LOAD16_WORD_SWAP( "hs2.10",   0x380000, 0x80000, CRC(20d0f9e4) SHA1(80a5eeef9472e327b0d4ee26434bad109a9434ea) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "hs2.13m",   0x0000000, 0x800000, CRC(a6ecab17) SHA1(6749a4c8dc81f4b10f910c31c82cf6674e2a44eb) )
	ROM_LOAD64_WORD( "hs2.15m",   0x0000002, 0x800000, CRC(10a0ae4d) SHA1(701b4900fbc8bef20efa1a706891c8df4bf14641) )
	ROM_LOAD64_WORD( "hs2.17m",   0x0000004, 0x800000, CRC(adfa7726) SHA1(8d36ec125a8c91abfe5213893d794f8bc11c8acd) )
	ROM_LOAD64_WORD( "hs2.19m",   0x0000006, 0x800000, CRC(bb3ae322) SHA1(ecd289d7a0fe365fdd7c5527cb17796002beb553) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 ) // 64k for the audio CPU (+banks)
	ROM_LOAD( "hs2.01",   0x00000, 0x08000, CRC(c1a13786) SHA1(c7392c7efb15ea4042e75bd9007e974293d8935d) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "hs2.02",   0x28000, 0x20000, CRC(2d8794aa) SHA1(c634affdc2568020cce6af97b4fa79925d9943f3) )

	ROM_REGION( 0x800000, "qsound", 0 ) // QSound samples
	ROM_LOAD16_WORD_SWAP( "hs2.11m",   0x000000, 0x800000, CRC(0e15c359) SHA1(176108b0d76d821a849324680aba0cd04b5016c1) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "hsf2.key",     0x000000, 0x000014, CRC(fc9b18c9) SHA1(457b6ba05458f1be9ebb8aa9cbab0a8808cb6857) )
ROM_END

ROM_START( hsf2hc06 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2u.03",  0x000000, 0x80000, CRC(b308151e) SHA1(afdfd3b049c6435e2291bc35d8c26ff5bff223d8) )
	ROM_LOAD16_WORD_SWAP( "hs2u.04",  0x080000, 0x80000, CRC(327aa49c) SHA1(6719cd6ecc2a4487fdbf5cbcd47e35fc43000607) )
	ROM_LOAD16_WORD_SWAP( "hs2.05",   0x100000, 0x80000, CRC(dde34a35) SHA1(f5be2d2916db6e86e0886d61d55bddf138273ebc) )
	ROM_LOAD16_WORD_SWAP( "hs2.06",   0x180000, 0x80000, CRC(f4e56dda) SHA1(c6490707c2a416ab88612c2d73abbe5853d8cb92) )
	ROM_LOAD16_WORD_SWAP( "hs2.07",   0x200000, 0x80000, CRC(ee4420fc) SHA1(06cf76660b0c794d2460c52d9fe8334fff51e9de) )
	ROM_LOAD16_WORD_SWAP( "hs2.08",   0x280000, 0x80000, CRC(c9441533) SHA1(bf178fac1f060fcce3ff9118333c8517dadc9429) )
	ROM_LOAD16_WORD_SWAP( "hs2_hc06.09",   0x300000, 0x80000, CRC(ed1c9127) SHA1(4e4da9fccbd62323dfdfff27a67db865fce54b70) )
	ROM_LOAD16_WORD_SWAP( "hs2.10",   0x380000, 0x80000, CRC(20d0f9e4) SHA1(80a5eeef9472e327b0d4ee26434bad109a9434ea) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "hs2.13m",   0x0000000, 0x800000, CRC(a6ecab17) SHA1(6749a4c8dc81f4b10f910c31c82cf6674e2a44eb) )
	ROM_LOAD64_WORD( "hs2.15m",   0x0000002, 0x800000, CRC(10a0ae4d) SHA1(701b4900fbc8bef20efa1a706891c8df4bf14641) )
	ROM_LOAD64_WORD( "hs2.17m",   0x0000004, 0x800000, CRC(adfa7726) SHA1(8d36ec125a8c91abfe5213893d794f8bc11c8acd) )
	ROM_LOAD64_WORD( "hs2.19m",   0x0000006, 0x800000, CRC(bb3ae322) SHA1(ecd289d7a0fe365fdd7c5527cb17796002beb553) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "hs2.01",   0x00000, 0x08000, CRC(c1a13786) SHA1(c7392c7efb15ea4042e75bd9007e974293d8935d) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "hs2.02",   0x28000, 0x20000, CRC(2d8794aa) SHA1(c634affdc2568020cce6af97b4fa79925d9943f3) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2.11m",   0x000000, 0x800000, CRC(0e15c359) SHA1(176108b0d76d821a849324680aba0cd04b5016c1) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "hsf2.key",     0x000000, 0x000014, CRC(fc9b18c9) SHA1(457b6ba05458f1be9ebb8aa9cbab0a8808cb6857) )
ROM_END

ROM_START( hsf2hc07 ) //hsf2pp
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2_hc09.03", 0x000000, 0x80000, CRC(652728a6) SHA1(ca1a8b0402f87ac16ab947dc6fe0c5bc2d1b83bb) )
	ROM_LOAD16_WORD_SWAP( "hs2_hc04.04b", 0x080000, 0x80000, CRC(7a02d7b6) SHA1(00c69673cadb86efaa8c96c778d3b4a9f61bd1e4) )
	ROM_LOAD16_WORD_SWAP( "hs2.05",   0x100000, 0x80000, CRC(dde34a35) SHA1(f5be2d2916db6e86e0886d61d55bddf138273ebc) )
	ROM_LOAD16_WORD_SWAP( "hs2.06",   0x180000, 0x80000, CRC(f4e56dda) SHA1(c6490707c2a416ab88612c2d73abbe5853d8cb92) )
	ROM_LOAD16_WORD_SWAP( "hs2.07",   0x200000, 0x80000, CRC(ee4420fc) SHA1(06cf76660b0c794d2460c52d9fe8334fff51e9de) )
	ROM_LOAD16_WORD_SWAP( "hs2.08",   0x280000, 0x80000, CRC(c9441533) SHA1(bf178fac1f060fcce3ff9118333c8517dadc9429) )
	ROM_LOAD16_WORD_SWAP( "hs2.09",   0x300000, 0x80000, CRC(3fc638a8) SHA1(2a42877b26c8abc437da46225701f0bba6e40058) )
	ROM_LOAD16_WORD_SWAP( "hs2.10",   0x380000, 0x80000, CRC(20d0f9e4) SHA1(80a5eeef9472e327b0d4ee26434bad109a9434ea) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "hs2.13m",   0x0000000, 0x800000, CRC(a6ecab17) SHA1(6749a4c8dc81f4b10f910c31c82cf6674e2a44eb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.15m",   0x0000002, 0x800000, CRC(10a0ae4d) SHA1(701b4900fbc8bef20efa1a706891c8df4bf14641) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.17m",   0x0000004, 0x800000, CRC(adfa7726) SHA1(8d36ec125a8c91abfe5213893d794f8bc11c8acd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "hs2.19m",   0x0000006, 0x800000, CRC(bb3ae322) SHA1(ecd289d7a0fe365fdd7c5527cb17796002beb553) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "hs2.01",   0x00000, 0x08000, CRC(c1a13786) SHA1(c7392c7efb15ea4042e75bd9007e974293d8935d) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "hs2.02",   0x28000, 0x20000, CRC(2d8794aa) SHA1(c634affdc2568020cce6af97b4fa79925d9943f3) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2.11m",   0x000000, 0x800000, CRC(0e15c359) SHA1(176108b0d76d821a849324680aba0cd04b5016c1) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",    0x00, 0x14, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( hsf2hc08 ) // v0.66 - press 9 to insert coin
	ROM_REGION( CODE_SIZE, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "hs2_hc08.03", 0x000000, 0x80000, CRC(27b6ac88) SHA1(becdc139f0af175fbbc91c230753d095253d0acc) )
	ROM_LOAD16_WORD_SWAP( "hs2_hc08.04", 0x080000, 0x80000, CRC(8d9baac1) SHA1(3b302e2483f72a8a0f7327089de0c86620890ee3) )
	ROM_LOAD16_WORD_SWAP( "hs2_hc08.05", 0x100000, 0x80000, CRC(15f6c1b9) SHA1(66c8ae49a05ce50dd606867ff7ab5d08a02f1314) )
	ROM_LOAD16_WORD_SWAP( "hs2_hc08.06", 0x180000, 0x80000, CRC(095ee372) SHA1(644e756e2a1280c573b348632a8d3b77994b15dc) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "hs2_hc08.13m",   0x0000000, 0x800000, CRC(51b072ab) SHA1(5bc384ea17aa2826904aa2f7b4be2f0905cc6383) )
	ROM_LOAD64_WORD( "hs2_hc08.15m",   0x0000002, 0x800000, CRC(f236c5da) SHA1(4d30ff915447a4933f19f375be9116d34f80ef17) )
	ROM_LOAD64_WORD( "hs2_hc08.17m",   0x0000004, 0x800000, CRC(ea223314) SHA1(0d49439eb0103b38e7c283b6c43fb77e39337dbf) )
	ROM_LOAD64_WORD( "hs2_hc08.19m",   0x0000006, 0x800000, CRC(623b6cb3) SHA1(1427bcb56b62df3870e627b9f245b5864a8d26be) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "hs2.01",        0x00000, 0x08000, CRC(6ce233a7) SHA1(5ff00de2fa8f31e66c9518049828d532554cb316) )
	ROM_CONTINUE(              0x10000, 0x18000 )
	ROM_LOAD( "hs2_hc08.02",   0x28000, 0x20000, CRC(2d8794aa) SHA1(c634affdc2568020cce6af97b4fa79925d9943f3) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "hs2_hc08.11m",   0x000000, 0x800000, CRC(cd8b2d9f) SHA1(bc4965b1cb6c211cdcf29ab5988702abd82effbc) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",    0x00, 0x14, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END


ROM_START( mvschc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mvcj_hc01.03a", 0x000000, 0x80000, CRC(8a50f418) SHA1(17db6f6afbe7866a4803bf2a20fb9b01b2b80250) )
	ROM_LOAD16_WORD_SWAP( "mvcj.04a", 0x080000, 0x80000, CRC(07d212e8) SHA1(c5420e9bd580910c1f1d0264240aeef20aac30a7) )
	ROM_LOAD16_WORD_SWAP( "mvc.05a",  0x100000, 0x80000, CRC(2d8c8e86) SHA1(b07d640a734c5d336054ed05195786224c9a6cd4) )
	ROM_LOAD16_WORD_SWAP( "mvc.06a",  0x180000, 0x80000, CRC(8528e1f5) SHA1(cd065c05268ab581b05676da544baf6af642acac) )
	ROM_LOAD16_WORD_SWAP( "mvc.07",   0x200000, 0x80000, CRC(c3baa32b) SHA1(d35589847e0753e869ffcd7c3abed925bfdb0fa2) )
	ROM_LOAD16_WORD_SWAP( "mvc.08",   0x280000, 0x80000, CRC(bc002fcd) SHA1(0b6735a071a9274f7ab25c743271fc30411fe819) )
	ROM_LOAD16_WORD_SWAP( "mvc.09",   0x300000, 0x80000, CRC(c67b26df) SHA1(6e9969246c57269d7ba0992a5cc319c8910bf8a9) )
	ROM_LOAD16_WORD_SWAP( "mvc.10",   0x380000, 0x80000, CRC(0fdd1e26) SHA1(5fa684d823b4f4eec61ed9e9b8938af5272ae1ed) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "mvc.13m",   0x0000000, 0x400000, CRC(fa5f74bc) SHA1(79a619248938a85ce4f7794a704647b9cf564fbc) )
	ROM_LOAD64_WORD( "mvc.15m",   0x0000002, 0x400000, CRC(71938a8f) SHA1(6982f7203458c1c46a1c1c13c0d0f2a5e109d271) )
	ROM_LOAD64_WORD( "mvc.17m",   0x0000004, 0x400000, CRC(92741d07) SHA1(ddfd70eab7c983ab452194b1860059f8ad694459) )
	ROM_LOAD64_WORD( "mvc.19m",   0x0000006, 0x400000, CRC(bcb72fc6) SHA1(46ab98dcdf6f5d611646a22a7355939ef5b2bbe5) )
	ROM_LOAD64_WORD( "mvc.14m",   0x1000000, 0x400000, CRC(7f1df4e4) SHA1(ede92b31c1fe87f91b4fe74ac211f2fb5f863bc2) )
	ROM_LOAD64_WORD( "mvc.16m",   0x1000002, 0x400000, CRC(90bd3203) SHA1(ed83208c486ea0f407b7e5d16a8cf242a6f73774) )
	ROM_LOAD64_WORD( "mvc.18m",   0x1000004, 0x400000, CRC(67aaf727) SHA1(e0e69104e31d2c41e18c0d24e9ab962406a7ca9a) )
	ROM_LOAD64_WORD( "mvc.20m",   0x1000006, 0x400000, CRC(8b0bade8) SHA1(c5732361bb4bf284c4d12a82ac2c5750b1f9d441) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "mvc.01",   0x00000, 0x08000, CRC(41629e95) SHA1(36925c05b5fdcbe43283a882d021e5360c947061) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "mvc.02",   0x28000, 0x20000, CRC(963abf6b) SHA1(6b784870e338701cefabbbe4669984b5c4e8a9a5) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "mvc.11m",   0x000000, 0x400000, CRC(850fe663) SHA1(81e519d05a08855f242ea2e17ee0859b449db895) )
	ROM_LOAD16_WORD_SWAP( "mvc.12m",   0x400000, 0x400000, CRC(7ccb1896) SHA1(74caadf3282fcc6acffb1bbe3734106f81124121) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "mvscj.key",    0x000000, 0x000014, CRC(9dedbcaf) SHA1(6468dd20ba89e4f6dc03340d218694690151ebe0) )
ROM_END

ROM_START( mvschc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mvce_hc02.03a", 0x000000, 0x80000, CRC(e557a885) SHA1(b7bf4e814660e7aaf1a8135ec70a43a6a6edb6bc) )
	ROM_LOAD16_WORD_SWAP( "mvce_hc02.04a", 0x080000, 0x80000, CRC(05e4ba51) SHA1(21e7107d53c2416b215c9ff442a85e98489ac8ba) )
	ROM_LOAD16_WORD_SWAP( "mvc.05a",  0x100000, 0x80000, CRC(2d8c8e86) SHA1(b07d640a734c5d336054ed05195786224c9a6cd4) )
	ROM_LOAD16_WORD_SWAP( "mvc.06a",  0x180000, 0x80000, CRC(8528e1f5) SHA1(cd065c05268ab581b05676da544baf6af642acac) )
	ROM_LOAD16_WORD_SWAP( "mvc.07",   0x200000, 0x80000, CRC(c3baa32b) SHA1(d35589847e0753e869ffcd7c3abed925bfdb0fa2) )
	ROM_LOAD16_WORD_SWAP( "mvc.08",   0x280000, 0x80000, CRC(bc002fcd) SHA1(0b6735a071a9274f7ab25c743271fc30411fe819) )
	ROM_LOAD16_WORD_SWAP( "mvc.09",   0x300000, 0x80000, CRC(c67b26df) SHA1(6e9969246c57269d7ba0992a5cc319c8910bf8a9) )
	ROM_LOAD16_WORD_SWAP( "mvc.10",   0x380000, 0x80000, CRC(0fdd1e26) SHA1(5fa684d823b4f4eec61ed9e9b8938af5272ae1ed) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "mvc.13m",   0x0000000, 0x400000, CRC(fa5f74bc) SHA1(79a619248938a85ce4f7794a704647b9cf564fbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvc.15m",   0x0000002, 0x400000, CRC(71938a8f) SHA1(6982f7203458c1c46a1c1c13c0d0f2a5e109d271) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvc.17m",   0x0000004, 0x400000, CRC(92741d07) SHA1(ddfd70eab7c983ab452194b1860059f8ad694459) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvc.19m",   0x0000006, 0x400000, CRC(bcb72fc6) SHA1(46ab98dcdf6f5d611646a22a7355939ef5b2bbe5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvc.14m",   0x1000000, 0x400000, CRC(7f1df4e4) SHA1(ede92b31c1fe87f91b4fe74ac211f2fb5f863bc2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvc.16m",   0x1000002, 0x400000, CRC(90bd3203) SHA1(ed83208c486ea0f407b7e5d16a8cf242a6f73774) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvc.18m",   0x1000004, 0x400000, CRC(67aaf727) SHA1(e0e69104e31d2c41e18c0d24e9ab962406a7ca9a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvc.20m",   0x1000006, 0x400000, CRC(8b0bade8) SHA1(c5732361bb4bf284c4d12a82ac2c5750b1f9d441) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "mvc.01",   0x00000, 0x08000, CRC(41629e95) SHA1(36925c05b5fdcbe43283a882d021e5360c947061) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "mvc.02",   0x28000, 0x20000, CRC(963abf6b) SHA1(6b784870e338701cefabbbe4669984b5c4e8a9a5) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "mvc.11m",   0x000000, 0x400000, CRC(850fe663) SHA1(81e519d05a08855f242ea2e17ee0859b449db895) )
	ROM_LOAD16_WORD_SWAP( "mvc.12m",   0x400000, 0x400000, CRC(7ccb1896) SHA1(74caadf3282fcc6acffb1bbe3734106f81124121) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "mvscu.key",    0x00, 0x14, CRC(a83db333) SHA1(7f7288ceadf233d913728f7c4a8841adcb5994e8) )
ROM_END

ROM_START( mshhc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mshj_hc01.03", 0x000000, 0x80000, CRC(31ae1efc) SHA1(02d3447edceb07ae4e40b068d8a5637547cbc17e) )
	ROM_LOAD16_WORD_SWAP( "mshj_hc02.04g", 0x080000, 0x80000, CRC(d66257ab) SHA1(5d7c4fab12c2e66c0f20f8cd728fdf37120c233b) )
	ROM_LOAD16_WORD_SWAP( "msh.05a",  0x100000, 0x80000, CRC(f37539e6) SHA1(770febc25ca5615b6c2023727edab3c68b15b2c4) )
	ROM_LOAD16_WORD_SWAP( "msh.06b",  0x180000, 0x80000, CRC(803e3fa4) SHA1(0acdeda65002521bf24130cbf06f9faa1dcef9e5) )
	ROM_LOAD16_WORD_SWAP( "msh.07a",  0x200000, 0x80000, CRC(c45f8e27) SHA1(4d28e0782c31ce56e728ac6ef5edd10437f00637) )
	ROM_LOAD16_WORD_SWAP( "msh.08a",  0x280000, 0x80000, CRC(9ca6f12c) SHA1(26ad682667b983b805e1f577426e5fca8ee3c82b) )
	ROM_LOAD16_WORD_SWAP( "msh.09a",  0x300000, 0x80000, CRC(82ec27af) SHA1(caf76268063ba91d28e8af684d60c2d71f29b9b9) )
	ROM_LOAD16_WORD_SWAP( "msh.10b",  0x380000, 0x80000, CRC(8d931196) SHA1(983e62efcdb4c8db6bce6acf4f86acb9447b565d) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "msh.13m",   0x0000000, 0x400000, CRC(09d14566) SHA1(c96463654043f22da5e844c6da17aa9273dc3439) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.15m",   0x0000002, 0x400000, CRC(ee962057) SHA1(24e359accb5f71a5863d7bad4088719fa547f88c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.17m",   0x0000004, 0x400000, CRC(604ece14) SHA1(880fb62b33ba4cceb38635e4ec056fac11a3c70f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.19m",   0x0000006, 0x400000, CRC(94a731e8) SHA1(1e784a3412e7361e3001494e1daf840ef8c20449) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.14m",   0x1000000, 0x400000, CRC(4197973e) SHA1(93aeea1a480b5f452c8a40ae3fff956796b859fa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.16m",   0x1000002, 0x400000, CRC(438da4a0) SHA1(ca93b14c3a570f9dd582efbb3f0536a92e535042) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.18m",   0x1000004, 0x400000, CRC(4db92d94) SHA1(f1b25ccc0627139ad5b287a8f2ab3b4a2fb8b8e4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.20m",   0x1000006, 0x400000, CRC(a2b0c6c0) SHA1(71016c01c1a706b73cf5b9ac7e384a030c6cf08d) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "msh.01",   0x00000, 0x08000, CRC(c976e6f9) SHA1(281025e5aaf97c0aeddc8bd0f737d092daadad9e) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "msh.02",   0x28000, 0x20000, CRC(ce67d0d9) SHA1(324226597cc5a11603f04085fef7715a314ecc05) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "msh.11m",   0x000000, 0x200000, CRC(37ac6d30) SHA1(ec67421fbf4a08a686e76792cb35e9cbf04d022d) )
	ROM_LOAD16_WORD_SWAP( "msh.12m",   0x200000, 0x200000, CRC(de092570) SHA1(a03d0df901f6ea79685eaed67db65bee14ec29c6) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "mshj.key",     0x00, 0x14, CRC(888761ac) SHA1(a1c72deedab2bafe5d594bba905a6274575b6e56) )
ROM_END

ROM_START( mshhc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mshe_hc02.03e", 0x000000, 0x80000, CRC(ce707863) SHA1(5e60c0ffdd93d2cad0c29b2d45c36c4e22d73899) )
	ROM_LOAD16_WORD_SWAP( "mshe_hc02.04",  0x080000, 0x80000, CRC(073dcbe9) SHA1(c216d75f980623075c9cb354b6b83243bd4fcbb4) )
	ROM_IGNORE( 0x3D4F47 )
	ROM_LOAD16_WORD_SWAP( "msh.05",   0x100000, 0x80000, CRC(6a091b9e) SHA1(7fa54e69e1a1ca348cb08d892d55023e9a3ff4cb) )
	ROM_LOAD16_WORD_SWAP( "msh.06b",  0x180000, 0x80000, CRC(803e3fa4) SHA1(0acdeda65002521bf24130cbf06f9faa1dcef9e5) )
	ROM_LOAD16_WORD_SWAP( "msh.07a",  0x200000, 0x80000, CRC(c45f8e27) SHA1(4d28e0782c31ce56e728ac6ef5edd10437f00637) )
	ROM_LOAD16_WORD_SWAP( "msh.08a",  0x280000, 0x80000, CRC(9ca6f12c) SHA1(26ad682667b983b805e1f577426e5fca8ee3c82b) )
	ROM_LOAD16_WORD_SWAP( "msh.09a",  0x300000, 0x80000, CRC(82ec27af) SHA1(caf76268063ba91d28e8af684d60c2d71f29b9b9) )
	ROM_LOAD16_WORD_SWAP( "msh.10b",  0x380000, 0x80000, CRC(8d931196) SHA1(983e62efcdb4c8db6bce6acf4f86acb9447b565d) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "msh.13m",   0x0000000, 0x400000, CRC(09d14566) SHA1(c96463654043f22da5e844c6da17aa9273dc3439) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.15m",   0x0000002, 0x400000, CRC(ee962057) SHA1(24e359accb5f71a5863d7bad4088719fa547f88c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.17m",   0x0000004, 0x400000, CRC(604ece14) SHA1(880fb62b33ba4cceb38635e4ec056fac11a3c70f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.19m",   0x0000006, 0x400000, CRC(94a731e8) SHA1(1e784a3412e7361e3001494e1daf840ef8c20449) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.14m",   0x1000000, 0x400000, CRC(4197973e) SHA1(93aeea1a480b5f452c8a40ae3fff956796b859fa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.16m",   0x1000002, 0x400000, CRC(438da4a0) SHA1(ca93b14c3a570f9dd582efbb3f0536a92e535042) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.18m",   0x1000004, 0x400000, CRC(4db92d94) SHA1(f1b25ccc0627139ad5b287a8f2ab3b4a2fb8b8e4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.20m",   0x1000006, 0x400000, CRC(a2b0c6c0) SHA1(71016c01c1a706b73cf5b9ac7e384a030c6cf08d) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "msh.01",   0x00000, 0x08000, CRC(c976e6f9) SHA1(281025e5aaf97c0aeddc8bd0f737d092daadad9e) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "msh.02",   0x28000, 0x20000, CRC(ce67d0d9) SHA1(324226597cc5a11603f04085fef7715a314ecc05) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "msh.11m",   0x000000, 0x200000, CRC(37ac6d30) SHA1(ec67421fbf4a08a686e76792cb35e9cbf04d022d) )
	ROM_LOAD16_WORD_SWAP( "msh.12m",   0x200000, 0x200000, CRC(de092570) SHA1(a03d0df901f6ea79685eaed67db65bee14ec29c6) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "msh.key",      0x00, 0x14, CRC(b494368e) SHA1(8efc561cec2bcc17902d27ed4e27b7d2b9eccdbc) )
ROM_END

ROM_START( mshhc03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mshe_hc03.03e", 0x000000, 0x80000, CRC(bd951414) SHA1(5585bdd1484dc18c7630d689f60d91c068aafc97) )
	ROM_LOAD16_WORD_SWAP( "mshe_hc03.04", 0x080000, 0x80000, CRC(adbd5707) SHA1(79d56d5a28328ababec10e080e46d1bfa6d8cab7) )
	ROM_LOAD16_WORD_SWAP( "msh.05",   0x100000, 0x80000, CRC(6a091b9e) SHA1(7fa54e69e1a1ca348cb08d892d55023e9a3ff4cb) )
	ROM_LOAD16_WORD_SWAP( "msh.06b",  0x180000, 0x80000, CRC(803e3fa4) SHA1(0acdeda65002521bf24130cbf06f9faa1dcef9e5) )
	ROM_LOAD16_WORD_SWAP( "msh.07a",  0x200000, 0x80000, CRC(c45f8e27) SHA1(4d28e0782c31ce56e728ac6ef5edd10437f00637) )
	ROM_LOAD16_WORD_SWAP( "msh.08a",  0x280000, 0x80000, CRC(9ca6f12c) SHA1(26ad682667b983b805e1f577426e5fca8ee3c82b) )
	ROM_LOAD16_WORD_SWAP( "msh.09a",  0x300000, 0x80000, CRC(82ec27af) SHA1(caf76268063ba91d28e8af684d60c2d71f29b9b9) )
	ROM_LOAD16_WORD_SWAP( "msh.10b",  0x380000, 0x80000, CRC(8d931196) SHA1(983e62efcdb4c8db6bce6acf4f86acb9447b565d) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "msh.13m",   0x0000000, 0x400000, CRC(09d14566) SHA1(c96463654043f22da5e844c6da17aa9273dc3439) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.15m",   0x0000002, 0x400000, CRC(ee962057) SHA1(24e359accb5f71a5863d7bad4088719fa547f88c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.17m",   0x0000004, 0x400000, CRC(604ece14) SHA1(880fb62b33ba4cceb38635e4ec056fac11a3c70f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.19m",   0x0000006, 0x400000, CRC(94a731e8) SHA1(1e784a3412e7361e3001494e1daf840ef8c20449) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.14m",   0x1000000, 0x400000, CRC(4197973e) SHA1(93aeea1a480b5f452c8a40ae3fff956796b859fa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.16m",   0x1000002, 0x400000, CRC(438da4a0) SHA1(ca93b14c3a570f9dd582efbb3f0536a92e535042) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.18m",   0x1000004, 0x400000, CRC(4db92d94) SHA1(f1b25ccc0627139ad5b287a8f2ab3b4a2fb8b8e4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "msh.20m",   0x1000006, 0x400000, CRC(a2b0c6c0) SHA1(71016c01c1a706b73cf5b9ac7e384a030c6cf08d) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "msh.01",   0x00000, 0x08000, CRC(c976e6f9) SHA1(281025e5aaf97c0aeddc8bd0f737d092daadad9e) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "msh.02",   0x28000, 0x20000, CRC(ce67d0d9) SHA1(324226597cc5a11603f04085fef7715a314ecc05) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "msh.11m",   0x000000, 0x200000, CRC(37ac6d30) SHA1(ec67421fbf4a08a686e76792cb35e9cbf04d022d) )
	ROM_LOAD16_WORD_SWAP( "msh.12m",   0x200000, 0x200000, CRC(de092570) SHA1(a03d0df901f6ea79685eaed67db65bee14ec29c6) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "msh.key",      0x00, 0x14, CRC(b494368e) SHA1(8efc561cec2bcc17902d27ed4e27b7d2b9eccdbc) )
ROM_END

ROM_START( mshvsfhc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mvse_hc01.3f", 0x000000, 0x80000, CRC(c077afa4) SHA1(97b234825f47e3c1bc66ddd343b4b68c7ff45d15) )
	ROM_LOAD16_WORD_SWAP( "mvse_hc01.4f", 0x080000, 0x80000, CRC(6031012f) SHA1(8905d52110f5c9da35ce4ec497c48ec73eb35e13) )
	ROM_LOAD16_WORD_SWAP( "mvs.05h",  0x100000, 0x80000, CRC(77870dc3) SHA1(924a7c82456bb44d7b0be65af11dbe1a2420a3f0) )
	ROM_LOAD16_WORD_SWAP( "mvs.06a",  0x180000, 0x80000, CRC(959f3030) SHA1(fbbaa915324815246738f3426232e623f039ce26) )
	ROM_LOAD16_WORD_SWAP( "mvs.07b",  0x200000, 0x80000, CRC(7f915bdb) SHA1(683da09c5ba55e31b59aa95a8e13c45dc574ab3c) )
	ROM_LOAD16_WORD_SWAP( "mvs.08a",  0x280000, 0x80000, CRC(c2813884) SHA1(49e5d4bc48f90c8146cb6aafb9240aff0119f1a7) )
	ROM_LOAD16_WORD_SWAP( "mvs.09b",  0x300000, 0x80000, CRC(3ba08818) SHA1(9ab132a3cac55fcccebe6c99b6fb0ba1305f8f6e) )
	ROM_LOAD16_WORD_SWAP( "mvs.10b",  0x380000, 0x80000, CRC(cf0dba98) SHA1(f4c1f8a6e7a79ecc6241d5268b3039f8a09ea516) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "mvs.13m",   0x0000000, 0x400000, CRC(29b05fd9) SHA1(e8fdb1ee5515a560eb4256ae4fd99bb1192e1a87) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.15m",   0x0000002, 0x400000, CRC(faddccf1) SHA1(4ed03ea91883a0413325f57edcc1614120b5922c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.17m",   0x0000004, 0x400000, CRC(97aaf4c7) SHA1(6a054921cc14fe080cb3f62c391f8ae3cc7e8ba9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.19m",   0x0000006, 0x400000, CRC(cb70e915) SHA1(da4d2480d348ac6dfd01256a88f4f3db8357ae46) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.14m",   0x1000000, 0x400000, CRC(b3b1972d) SHA1(0f2c3fb7de014181ee481ec35d0578b2c116c2dc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.16m",   0x1000002, 0x400000, CRC(08aadb5d) SHA1(3a2c222eca3e7df80ce69951b3db6442312751a4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.18m",   0x1000004, 0x400000, CRC(c1228b35) SHA1(7afdfb552888c79d0fbb30242b3d917b87fad57a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.20m",   0x1000006, 0x400000, CRC(366cc6c2) SHA1(6f2a789087c8e404c5227b927fa8328c03593243) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "mvs.01",   0x00000, 0x08000, CRC(68252324) SHA1(138ef320ef27956b2ab5591d49a1315b7b0a194c) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "mvs.02",   0x28000, 0x20000, CRC(b34e773d) SHA1(3bcf44bf06c35814cff29d244142db7abe05bd39) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "mvs.11m",   0x000000, 0x400000, CRC(86219770) SHA1(4e5b68d382a5aa37f8b0b6434c53a2b95f5f9a4d) )
	ROM_LOAD16_WORD_SWAP( "mvs.12m",   0x400000, 0x400000, CRC(f2fd7f68) SHA1(28a30d55d3eaf963006c7cbe7c288099cd3ba536) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "mshvsfj.key",  0x00, 0x14, CRC(565eeebb) SHA1(762844b59b2fcf529a26ad3dde8282415db926b3) )
ROM_END

ROM_START( mshvsfhc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mvse_hc02.3f", 0x000000, 0x80000, CRC(86672cbb) SHA1(7dc683ed8cf5bc205851375deab0438a1105d581) )
	ROM_LOAD16_WORD_SWAP( "mvsj.04i", 0x080000, 0x80000, CRC(32741ace) SHA1(36db3a3aeaf29369977593c051bf5665cffefb2d) )
	ROM_LOAD16_WORD_SWAP( "mvs.05h",  0x100000, 0x80000, CRC(77870dc3) SHA1(924a7c82456bb44d7b0be65af11dbe1a2420a3f0) )
	ROM_LOAD16_WORD_SWAP( "mvs.06a",  0x180000, 0x80000, CRC(959f3030) SHA1(fbbaa915324815246738f3426232e623f039ce26) )
	ROM_LOAD16_WORD_SWAP( "mvs.07b",  0x200000, 0x80000, CRC(7f915bdb) SHA1(683da09c5ba55e31b59aa95a8e13c45dc574ab3c) )
	ROM_LOAD16_WORD_SWAP( "mvs.08a",  0x280000, 0x80000, CRC(c2813884) SHA1(49e5d4bc48f90c8146cb6aafb9240aff0119f1a7) )
	ROM_LOAD16_WORD_SWAP( "mvs.09b",  0x300000, 0x80000, CRC(3ba08818) SHA1(9ab132a3cac55fcccebe6c99b6fb0ba1305f8f6e) )
	ROM_LOAD16_WORD_SWAP( "mvs.10b",  0x380000, 0x80000, CRC(cf0dba98) SHA1(f4c1f8a6e7a79ecc6241d5268b3039f8a09ea516) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "mvs.13m",   0x0000000, 0x400000, CRC(29b05fd9) SHA1(e8fdb1ee5515a560eb4256ae4fd99bb1192e1a87) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.15m",   0x0000002, 0x400000, CRC(faddccf1) SHA1(4ed03ea91883a0413325f57edcc1614120b5922c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.17m",   0x0000004, 0x400000, CRC(97aaf4c7) SHA1(6a054921cc14fe080cb3f62c391f8ae3cc7e8ba9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.19m",   0x0000006, 0x400000, CRC(cb70e915) SHA1(da4d2480d348ac6dfd01256a88f4f3db8357ae46) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.14m",   0x1000000, 0x400000, CRC(b3b1972d) SHA1(0f2c3fb7de014181ee481ec35d0578b2c116c2dc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.16m",   0x1000002, 0x400000, CRC(08aadb5d) SHA1(3a2c222eca3e7df80ce69951b3db6442312751a4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.18m",   0x1000004, 0x400000, CRC(c1228b35) SHA1(7afdfb552888c79d0fbb30242b3d917b87fad57a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.20m",   0x1000006, 0x400000, CRC(366cc6c2) SHA1(6f2a789087c8e404c5227b927fa8328c03593243) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "mvs.01",   0x00000, 0x08000, CRC(68252324) SHA1(138ef320ef27956b2ab5591d49a1315b7b0a194c) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "mvs.02",   0x28000, 0x20000, CRC(b34e773d) SHA1(3bcf44bf06c35814cff29d244142db7abe05bd39) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "mvs.11m",   0x000000, 0x400000, CRC(86219770) SHA1(4e5b68d382a5aa37f8b0b6434c53a2b95f5f9a4d) )
	ROM_LOAD16_WORD_SWAP( "mvs.12m",   0x400000, 0x400000, CRC(f2fd7f68) SHA1(28a30d55d3eaf963006c7cbe7c288099cd3ba536) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "mshvsfj.key",  0x00, 0x14, CRC(565eeebb) SHA1(762844b59b2fcf529a26ad3dde8282415db926b3) )
ROM_END

ROM_START( mshvsfhc03 ) //mshvsfbh
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mvse_hc03.3f", 0x000000, 0x80000, CRC(54ecd389) SHA1(be6d34587de852d93d575f7d1e5001e43f4be9e9) )
	ROM_LOAD16_WORD_SWAP( "mvse_hc03.4f", 0x080000, 0x80000, CRC(6031012f) SHA1(8905d52110f5c9da35ce4ec497c48ec73eb35e13) )
	ROM_LOAD16_WORD_SWAP( "mvs.05h",  0x100000, 0x80000, CRC(77870dc3) SHA1(924a7c82456bb44d7b0be65af11dbe1a2420a3f0) )
	ROM_LOAD16_WORD_SWAP( "mvs.06a",  0x180000, 0x80000, CRC(959f3030) SHA1(fbbaa915324815246738f3426232e623f039ce26) )
	ROM_LOAD16_WORD_SWAP( "mvs.07b",  0x200000, 0x80000, CRC(7f915bdb) SHA1(683da09c5ba55e31b59aa95a8e13c45dc574ab3c) )
	ROM_LOAD16_WORD_SWAP( "mvs.08a",  0x280000, 0x80000, CRC(c2813884) SHA1(49e5d4bc48f90c8146cb6aafb9240aff0119f1a7) )
	ROM_LOAD16_WORD_SWAP( "mvs.09b",  0x300000, 0x80000, CRC(3ba08818) SHA1(9ab132a3cac55fcccebe6c99b6fb0ba1305f8f6e) )
	ROM_LOAD16_WORD_SWAP( "mvs.10b",  0x380000, 0x80000, CRC(cf0dba98) SHA1(f4c1f8a6e7a79ecc6241d5268b3039f8a09ea516) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "mvs.13m",   0x0000000, 0x400000, CRC(29b05fd9) SHA1(e8fdb1ee5515a560eb4256ae4fd99bb1192e1a87) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.15m",   0x0000002, 0x400000, CRC(faddccf1) SHA1(4ed03ea91883a0413325f57edcc1614120b5922c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.17m",   0x0000004, 0x400000, CRC(97aaf4c7) SHA1(6a054921cc14fe080cb3f62c391f8ae3cc7e8ba9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.19m",   0x0000006, 0x400000, CRC(cb70e915) SHA1(da4d2480d348ac6dfd01256a88f4f3db8357ae46) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.14m",   0x1000000, 0x400000, CRC(b3b1972d) SHA1(0f2c3fb7de014181ee481ec35d0578b2c116c2dc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.16m",   0x1000002, 0x400000, CRC(08aadb5d) SHA1(3a2c222eca3e7df80ce69951b3db6442312751a4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.18m",   0x1000004, 0x400000, CRC(c1228b35) SHA1(7afdfb552888c79d0fbb30242b3d917b87fad57a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mvs.20m",   0x1000006, 0x400000, CRC(366cc6c2) SHA1(6f2a789087c8e404c5227b927fa8328c03593243) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "mvs.01",   0x00000, 0x08000, CRC(68252324) SHA1(138ef320ef27956b2ab5591d49a1315b7b0a194c) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "mvs.02",   0x28000, 0x20000, CRC(b34e773d) SHA1(3bcf44bf06c35814cff29d244142db7abe05bd39) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "mvs.11m",   0x000000, 0x400000, CRC(86219770) SHA1(4e5b68d382a5aa37f8b0b6434c53a2b95f5f9a4d) )
	ROM_LOAD16_WORD_SWAP( "mvs.12m",   0x400000, 0x400000, CRC(f2fd7f68) SHA1(28a30d55d3eaf963006c7cbe7c288099cd3ba536) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "mshvsfj.key",  0x00, 0x14, CRC(565eeebb) SHA1(762844b59b2fcf529a26ad3dde8282415db926b3) )
ROM_END

ROM_START( mshvsfhc04 ) //mshvsfcph
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mvse_hc04.03f", 0x000000, 0x80000, CRC(086f345a) SHA1(6c13774ef6d9e295ef8fc38b51220143e29b6373) )
	ROM_LOAD16_WORD_SWAP( "mvse.04f", 0x080000, 0x80000, CRC(6ef799f9) SHA1(2d45dbf7bc277b84c6bcd9615ab3b80c42af7781) )
	ROM_LOAD16_WORD_SWAP( "mvs.05a",  0x100000, 0x80000, CRC(1a5de0cb) SHA1(738a27f83704c208d36d73bf766d861ef2d51a89) )
	ROM_LOAD16_WORD_SWAP( "mvs.06a",  0x180000, 0x80000, CRC(959f3030) SHA1(fbbaa915324815246738f3426232e623f039ce26) )
	ROM_LOAD16_WORD_SWAP( "mvs.07b",  0x200000, 0x80000, CRC(7f915bdb) SHA1(683da09c5ba55e31b59aa95a8e13c45dc574ab3c) )
	ROM_LOAD16_WORD_SWAP( "mvs.08a",  0x280000, 0x80000, CRC(c2813884) SHA1(49e5d4bc48f90c8146cb6aafb9240aff0119f1a7) )
	ROM_LOAD16_WORD_SWAP( "mvs.09b",  0x300000, 0x80000, CRC(3ba08818) SHA1(9ab132a3cac55fcccebe6c99b6fb0ba1305f8f6e) )
	ROM_LOAD16_WORD_SWAP( "mvs.10b",  0x380000, 0x80000, CRC(cf0dba98) SHA1(f4c1f8a6e7a79ecc6241d5268b3039f8a09ea516) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "mvs.13m",   0x0000000, 0x400000, CRC(29b05fd9) SHA1(e8fdb1ee5515a560eb4256ae4fd99bb1192e1a87) )
	ROM_LOAD64_WORD( "mvs.15m",   0x0000002, 0x400000, CRC(faddccf1) SHA1(4ed03ea91883a0413325f57edcc1614120b5922c) )
	ROM_LOAD64_WORD( "mvs.17m",   0x0000004, 0x400000, CRC(97aaf4c7) SHA1(6a054921cc14fe080cb3f62c391f8ae3cc7e8ba9) )
	ROM_LOAD64_WORD( "mvs.19m",   0x0000006, 0x400000, CRC(cb70e915) SHA1(da4d2480d348ac6dfd01256a88f4f3db8357ae46) )
	ROM_LOAD64_WORD( "mvs.14m",   0x1000000, 0x400000, CRC(b3b1972d) SHA1(0f2c3fb7de014181ee481ec35d0578b2c116c2dc) )
	ROM_LOAD64_WORD( "mvs.16m",   0x1000002, 0x400000, CRC(08aadb5d) SHA1(3a2c222eca3e7df80ce69951b3db6442312751a4) )
	ROM_LOAD64_WORD( "mvs.18m",   0x1000004, 0x400000, CRC(c1228b35) SHA1(7afdfb552888c79d0fbb30242b3d917b87fad57a) )
	ROM_LOAD64_WORD( "mvs.20m",   0x1000006, 0x400000, CRC(366cc6c2) SHA1(6f2a789087c8e404c5227b927fa8328c03593243) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "mvs.01",   0x00000, 0x08000, CRC(68252324) SHA1(138ef320ef27956b2ab5591d49a1315b7b0a194c) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "mvs.02",   0x28000, 0x20000, CRC(b34e773d) SHA1(3bcf44bf06c35814cff29d244142db7abe05bd39) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "mvs.11m",   0x000000, 0x400000, CRC(86219770) SHA1(4e5b68d382a5aa37f8b0b6434c53a2b95f5f9a4d) )
	ROM_LOAD16_WORD_SWAP( "mvs.12m",   0x400000, 0x400000, CRC(f2fd7f68) SHA1(28a30d55d3eaf963006c7cbe7c288099cd3ba536) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "mshvsf.key",   0x000000, 0x000014, CRC(64660867) SHA1(448eb440494c971800370f103b4d1f21a7266c6c) )
ROM_END

ROM_START( pfghthc01 ) //pfghtsc
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pcfj.03", 0x000000, 0x80000, CRC(681da43e) SHA1(1bd4b6b395ac7208c0208b254455276719e98c4b) )
	ROM_LOAD16_WORD_SWAP( "pcf_hc01.04",  0x080000, 0x80000, CRC(53462930) SHA1(1337a7636de76c50849b4abc7a7b29677f086e9a) )
	ROM_LOAD16_WORD_SWAP( "pcf.05",  0x100000, 0x80000, CRC(215655f6) SHA1(242c0f4401520f2a3b0deafc3a807b18b987e496) )
	ROM_LOAD16_WORD_SWAP( "pcf.06",  0x180000, 0x80000, CRC(ea6f13ea) SHA1(1bc924a8a9da1d2ad7667685cdb92fe317a39aba) )
	ROM_LOAD16_WORD_SWAP( "pcf.07",  0x200000, 0x80000, CRC(5ac6d5ea) SHA1(9ce8e4668b565658597a868830545fb75a5eeaa6) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROM_LOAD64_WORD( "pcf_hc01.13m",   0x0000000, 0x400000, CRC(f516d278) SHA1(ef1ebc8290daa75094f12ee9bb704369547bf73b) )
	ROM_LOAD64_WORD( "pcf_hc01.15m",   0x0000002, 0x400000, CRC(7d9de75b) SHA1(a55f27ff051fa63f86aafc6b61c50817c613d574) )
	ROM_LOAD64_WORD( "pcf_hc01.17m",   0x0000004, 0x400000, CRC(7343967c) SHA1(c86dd5413863f2a60474a2de393d390a9f19ddc7) )
	ROM_LOAD64_WORD( "pcf_hc01.19m",   0x0000006, 0x400000, CRC(9368a861) SHA1(a2f90ddd160dd4713ad1f6aec938350364aa65d0) )
	ROM_LOAD64_WORD( "pcf.14m",   0x1000000, 0x100000, CRC(0383897c) SHA1(aba14afa1d0c971afcee4317f480e88117d77b5e) )
	ROM_LOAD64_WORD( "pcf.16m",   0x1000002, 0x100000, CRC(76f91084) SHA1(3d1e32467f2aa5dd6fb96bd5c866ecc9691660fc) )
	ROM_LOAD64_WORD( "pcf.18m",   0x1000004, 0x100000, CRC(756c3754) SHA1(be2f709b90222a567f198f851cf07ffb0ad433d7) )
	ROM_LOAD64_WORD( "pcf.20m",   0x1000006, 0x100000, CRC(9ec9277d) SHA1(b7ceeaca30dfcdf498b61a6961f0aa1a068b8ec4) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pcf.01",   0x00000, 0x08000, CRC(254e5f33) SHA1(c413ec0630b9bdd15e64f42893eba8958a09b573) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "pcf.02",   0x28000, 0x20000, CRC(6902f4f9) SHA1(9bfe4ddade3c666076d26a2b545120f6d059fd7c) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pcf.11m",   0x000000, 0x400000, CRC(a5dea005) SHA1(3ae79baf6ff5bd527f82b26f164c7e3c65423ae2) )
	ROM_LOAD16_WORD_SWAP( "pcf.12m",   0x400000, 0x400000, CRC(4ce235fe) SHA1(795b94557e954cc0e45fd3778b609064d57a34a2) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "pfghtj.key",   0x000000, 0x000014, CRC(62297638) SHA1(efe090ffa8992823cfd787ade736df5487d69ca7) )
ROM_END

ROM_START( pfghthc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pcf_hc02.03", 0x000000, 0x80000, CRC(64a6e6ef) SHA1(0a3a5a66e7b23cafed2cbb0b26b004d8483a26e6) )
	ROM_LOAD16_WORD_SWAP( "pcf_hc02.04",  0x080000, 0x80000, CRC(6c882837) SHA1(0fc4f96a1a5e50ae72a1d3913f8691a2582009a6) )
	ROM_LOAD16_WORD_SWAP( "pcf.05",  0x100000, 0x80000, CRC(215655f6) SHA1(242c0f4401520f2a3b0deafc3a807b18b987e496) )
	ROM_LOAD16_WORD_SWAP( "pcf.06",  0x180000, 0x80000, CRC(ea6f13ea) SHA1(1bc924a8a9da1d2ad7667685cdb92fe317a39aba) )
	ROM_LOAD16_WORD_SWAP( "pcf.07",  0x200000, 0x80000, CRC(5ac6d5ea) SHA1(9ce8e4668b565658597a868830545fb75a5eeaa6) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROM_LOAD64_WORD( "pcf_hc02.13m",   0x0000000, 0x400000, CRC(068c3659) SHA1(2877100c92297694f8bd1c8572ca9dd0f1849e7c) )
	ROM_LOAD64_WORD( "pcf_hc02.15m",   0x0000002, 0x400000, CRC(0d93bbdd) SHA1(470ab3a4b93b31f2ba8da4875a273a05a05c8067) )
	ROM_LOAD64_WORD( "pcf_hc02.17m",   0x0000004, 0x400000, CRC(946ad5cb) SHA1(63a8903ccba285092b3c8f32442cc7fcf98d9d62) )
	ROM_LOAD64_WORD( "pcf_hc02.19m",   0x0000006, 0x400000, CRC(8945c67f) SHA1(ee757f5f2622e0f7a66399aa218f1eaad9abe027) )
	ROM_LOAD64_WORD( "pcf.14m",   0x1000000, 0x100000, CRC(0383897c) SHA1(aba14afa1d0c971afcee4317f480e88117d77b5e) )
	ROM_LOAD64_WORD( "pcf.16m",   0x1000002, 0x100000, CRC(76f91084) SHA1(3d1e32467f2aa5dd6fb96bd5c866ecc9691660fc) )
	ROM_LOAD64_WORD( "pcf.18m",   0x1000004, 0x100000, CRC(756c3754) SHA1(be2f709b90222a567f198f851cf07ffb0ad433d7) )
	ROM_LOAD64_WORD( "pcf.20m",   0x1000006, 0x100000, CRC(9ec9277d) SHA1(b7ceeaca30dfcdf498b61a6961f0aa1a068b8ec4) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pcf.01",   0x00000, 0x08000, CRC(254e5f33) SHA1(c413ec0630b9bdd15e64f42893eba8958a09b573) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "pcf.02",   0x28000, 0x20000, CRC(6902f4f9) SHA1(9bfe4ddade3c666076d26a2b545120f6d059fd7c) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pcf.11m",   0x000000, 0x400000, CRC(a5dea005) SHA1(3ae79baf6ff5bd527f82b26f164c7e3c65423ae2) )
	ROM_LOAD16_WORD_SWAP( "pcf.12m",   0x400000, 0x400000, CRC(4ce235fe) SHA1(795b94557e954cc0e45fd3778b609064d57a34a2) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "pfghtj.key",   0x000000, 0x000014, CRC(62297638) SHA1(efe090ffa8992823cfd787ade736df5487d69ca7) )
ROM_END

ROM_START( pfghthc03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pcf_hc03.03", 0x000000, 0x80000, CRC(5b91a900) SHA1(503fc8b5e687c11bfa5a3b55a7df8b22b8a02103) )
	ROM_LOAD16_WORD_SWAP( "pcf.04",  0x080000, 0x80000, CRC(f4314c96) SHA1(c40ed74039bf0096eb3648b7243a8e697638e0a6) )
	ROM_LOAD16_WORD_SWAP( "pcf.05",  0x100000, 0x80000, CRC(215655f6) SHA1(242c0f4401520f2a3b0deafc3a807b18b987e496) )
	ROM_LOAD16_WORD_SWAP( "pcf.06",  0x180000, 0x80000, CRC(ea6f13ea) SHA1(1bc924a8a9da1d2ad7667685cdb92fe317a39aba) )
	ROM_LOAD16_WORD_SWAP( "pcf.07",  0x200000, 0x80000, CRC(5ac6d5ea) SHA1(9ce8e4668b565658597a868830545fb75a5eeaa6) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "pcf.13m",   0x0000000, 0x400000, CRC(22d72ab9) SHA1(653efd95c34b4b9d2ab0d219f41a99ca84e12214) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pcf.15m",   0x0000002, 0x400000, CRC(16a4813c) SHA1(bf5fce6008214f353414d1b64bea4ed0c7673670) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pcf.17m",   0x0000004, 0x400000, CRC(1097e035) SHA1(4bd51e4e9447af27d2cac1f6d2201e37c949912b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pcf.19m",   0x0000006, 0x400000, CRC(d362d874) SHA1(30c42af18440496cc05e4418e4efa41172ae4ced) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pcf.14m",   0x1000000, 0x100000, CRC(0383897c) SHA1(aba14afa1d0c971afcee4317f480e88117d77b5e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pcf.16m",   0x1000002, 0x100000, CRC(76f91084) SHA1(3d1e32467f2aa5dd6fb96bd5c866ecc9691660fc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pcf.18m",   0x1000004, 0x100000, CRC(756c3754) SHA1(be2f709b90222a567f198f851cf07ffb0ad433d7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pcf.20m",   0x1000006, 0x100000, CRC(9ec9277d) SHA1(b7ceeaca30dfcdf498b61a6961f0aa1a068b8ec4) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pcf.01",   0x00000, 0x08000, CRC(254e5f33) SHA1(c413ec0630b9bdd15e64f42893eba8958a09b573) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "pcf.02",   0x28000, 0x20000, CRC(6902f4f9) SHA1(9bfe4ddade3c666076d26a2b545120f6d059fd7c) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pcf.11m",   0x000000, 0x400000, CRC(a5dea005) SHA1(3ae79baf6ff5bd527f82b26f164c7e3c65423ae2) )
	ROM_LOAD16_WORD_SWAP( "pcf.12m",   0x400000, 0x400000, CRC(4ce235fe) SHA1(795b94557e954cc0e45fd3778b609064d57a34a2) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "pfghtj.key",   0x00, 0x14, CRC(62297638) SHA1(efe090ffa8992823cfd787ade736df5487d69ca7) )
ROM_END

ROM_START( progearhc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pgaj_hc01.03", 0x000000, 0x80000, CRC(d65d47f9) SHA1(d1c45f3e191730b7757f7925de8dca969900ded2) )
	ROM_LOAD16_WORD_SWAP( "pgaj_d.04", 0x080000, 0x80000, CRC(be4b7799) SHA1(0414922296079ca9380a41bf3c628ce67acec06d) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "pga-simm.01c",   0x0000000, 0x200000,  CRC(452f98b0) SHA1(a10e615c32098f6d25becd466da8faa967523a7b) , ROM_GROUPBYTE | ROM_SKIP(7) )
	ROMX_LOAD( "pga-simm.01d",   0x0000001, 0x200000,  CRC(9e672092) SHA1(fce0b8b43a1c069262f4e3e81c1a04621e232c88) , ROM_GROUPBYTE | ROM_SKIP(7) )
	ROMX_LOAD( "pga-simm.01a",   0x0000002, 0x200000,  CRC(ae9ddafe) SHA1(afbb26fed6cd0cb5c0099a10d35aeb453318c14d) , ROM_GROUPBYTE | ROM_SKIP(7) )
	ROMX_LOAD( "pga-simm.01b",   0x0000003, 0x200000,  CRC(94d72d94) SHA1(df6a3fe49c008f73b160eb6f2a44dc371ff73cba) , ROM_GROUPBYTE | ROM_SKIP(7) )
	ROMX_LOAD( "pga-simm.03c",   0x0000004, 0x200000,  CRC(48a1886d) SHA1(ebf44b42d784924e08a832a7e5f66a887bab244b) , ROM_GROUPBYTE | ROM_SKIP(7) )
	ROMX_LOAD( "pga-simm.03d",   0x0000005, 0x200000,  CRC(172d7e37) SHA1(0eaedd24cd3fa87b6f35fbd63078d40c493c92d0) , ROM_GROUPBYTE | ROM_SKIP(7) )
	ROMX_LOAD( "pga-simm.03a",   0x0000006, 0x200000,  CRC(9ee33d98) SHA1(85d1bd31940e35ac8c732165020881a2d65cd6b1) , ROM_GROUPBYTE | ROM_SKIP(7) )
	ROMX_LOAD( "pga-simm.03b",   0x0000007, 0x200000,  CRC(848dee32) SHA1(c591288e86ad1624d0fe66563808af9fac786e64) , ROM_GROUPBYTE | ROM_SKIP(7) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pga.01",   0x00000, 0x08000, CRC(bdbfa992) SHA1(7c5496c1daaea6a7ab95c0b25625d325ec3427cc) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pga-simm.05a",   0x000000, 0x200000, CRC(c0aac80c) SHA1(91784d35d4f7e113529bb5be6081b67094b150ea) )
	ROM_LOAD16_WORD_SWAP( "pga-simm.05b",   0x200000, 0x200000, CRC(37a65d86) SHA1(374d562a4648734f82aa2ddb6d258e870896dd45) )
	ROM_LOAD16_WORD_SWAP( "pga-simm.06a",   0x400000, 0x200000, CRC(d3f1e934) SHA1(5dcea28c873d0d472f5b94e07d97cd77ace2b252) )
	ROM_LOAD16_WORD_SWAP( "pga-simm.06b",   0x600000, 0x200000, CRC(8b39489a) SHA1(fd790efaf37dc2c4c16f657941044e3e2d3c2711) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x00, 0x14, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( progearhc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pgaj_hc03.03",   0x000000, 0x080000, CRC(55ce8d4a) SHA1(3b7342afbfa1244cb5cbf5be7391d3e1f8231822) )
	ROM_LOAD16_WORD_SWAP( "pgaj_hc03.04",   0x080000, 0x080000, CRC(71060b9e) SHA1(007a174ceca6ae080f19f088bf0fc6cd0fe2510c) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "pga.13m",   0x0000000, 0x400000, CRC(5194c198) SHA1(f9ae16cad8b30547b8dd3a1ea1d6e845d76ccefe) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pga.15m",   0x0000002, 0x400000, CRC(b794e83f) SHA1(0332fa798b2955464ab336929866c9185bd4b520) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pga.17m",   0x0000004, 0x400000, CRC(87f22918) SHA1(7f048d66593f385526bd2c669cf6b8ad58d12bbf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pga.19m",   0x0000006, 0x400000, CRC(65ffb45b) SHA1(9c21187519c1ec95c5a960b2c815ee41ace4fa7e) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pga.01",   0x00000, 0x08000, CRC(bdbfa992) SHA1(7c5496c1daaea6a7ab95c0b25625d325ec3427cc) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pga_hc03.11m", 0x000000, 0x400000, CRC(33ebf625) SHA1(39e5f9afd37a258005b0143fa38b9c53b63f700d) )
	ROM_LOAD16_WORD_SWAP( "pga_hc03.12m", 0x000000, 0x400000, CRC(47f25cf4) SHA1(714b5baf146d720cc86f77aeee5b1160f553d958) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x00, 0x14, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( rmancp2hc01 ) //rmancp2jk
	ROM_REGION(CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "rcm_hc01.03a", 0x000000, 0x80000, CRC(09512f87) SHA1(8cbf2e64115dbaa0f7332d17b7e53d698ec74140) )
	ROM_LOAD16_WORD_SWAP( "rcm_hc01.04a", 0x080000, 0x80000, CRC(09c95de1) SHA1(6273f5d4c6412255878e9b7270dbafece2619215) )
	ROM_LOAD16_WORD_SWAP( "rcm.05a", 0x100000, 0x80000, CRC(517ccde2) SHA1(492256c192f0c4814efa1ee1dd390453dd2e5865) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROM_FILL(              0x000000, 0x800000, 0x00 )
	ROM_LOAD64_WORD( "rcm_hc01.73",  0x800000, 0x080000, CRC(11542f04) SHA1(35d4fd9bdb075b968b60c067a896870d07146be7) )
	ROM_LOAD64_WORD( "rcm_hc01.63",  0x800002, 0x080000, CRC(922ece19) SHA1(99729f1f429e4726d8ab21da8b647669d0bd3d7a) )
	ROM_LOAD64_WORD( "rcm_hc01.83",  0x800004, 0x080000, CRC(0ceb4599) SHA1(383aa72a5e246f21bb37c4ba77022b32b0b3ff01) )
	ROM_LOAD64_WORD( "rcm_hc01.93",  0x800006, 0x080000, CRC(44d9e31d) SHA1(c4ff9dae0eec4f43ff0af3b3c1d8b0511ff0619a) )
	ROM_LOAD64_WORD( "rcm.74",   0xa00000, 0x080000, CRC(004ec725) SHA1(b1d3bcf920b0a1d0f4b59c77f5962e8162bbef65) )
	ROM_LOAD64_WORD( "rcm.64",   0xa00002, 0x080000, CRC(65c0464e) SHA1(4a035f4d28fc8aa72bfe0a06392b93b0abfba458) )
	ROM_LOAD64_WORD( "rcm.84",   0xa00004, 0x080000, CRC(fb3097cc) SHA1(7bff2372809cdfa4dcd8537a448b177c0e86a94e) )
	ROM_LOAD64_WORD( "rcm.94",   0xa00006, 0x080000, CRC(2e16557a) SHA1(f4a916c1524a8de23fc6afabc8c724a89530c631) )
	ROM_LOAD64_WORD( "rcm_hc01.75",  0xc00000, 0x080000, CRC(0be9a313) SHA1(2d5de4ff2bd84da6f67e23235d59709e53b8d4c9) )
	ROM_LOAD64_WORD( "rcm_hc01.65",  0xc00002, 0x080000, CRC(cc022b9a) SHA1(ad529367efca8ddecf6bc6e598373ac50abd33bc) )
	ROM_LOAD64_WORD( "rcm_hc01.85",  0xc00004, 0x080000, CRC(53a5e239) SHA1(397c8dec7d57b2d7eeb66ba7940fa52c520ec9ef) )
	ROM_LOAD64_WORD( "rcm_hc01.95",  0xc00006, 0x080000, CRC(a256c1d0) SHA1(8655c7020d2e9ee5d042eb3d593efb255b0ba5f4) )
	ROM_LOAD64_WORD( "rcm.76",   0xe00000, 0x080000, CRC(89a889ad) SHA1(1ffe112051a3afc94df1326f17ef58dc2fc531aa) )
	ROM_LOAD64_WORD( "rcm.66",   0xe00002, 0x080000, CRC(1300eb7b) SHA1(db4f53b1cf521df99d073dcf0bfafe7b113e95d5) )
	ROM_LOAD64_WORD( "rcm.86",   0xe00004, 0x080000, CRC(6d974ebd) SHA1(41de66481a64fa8a6471c512fc5dcaf96d95ee69) )
	ROM_LOAD64_WORD( "rcm.96",   0xe00006, 0x080000, CRC(7da4cd24) SHA1(dd44377ff9f83f15cac032c4e7ef2071adcfa196) )

	ROM_REGION(QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "rcm.01",   0x00000, 0x08000, CRC(d60cf8a3) SHA1(dccd84b93e62489c703011422d0fe84444c7f7db) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "rcm.51",   0x000000, 0x80000, CRC(b6d07080) SHA1(b8f07553c01b1f67b0696110cd4e35e4cf4fa158) )
	ROM_LOAD16_WORD_SWAP( "rcm.52",   0x080000, 0x80000, CRC(dfddc493) SHA1(56b5129f24d05d2c85a767b0a632bf260f5425b2) )
	ROM_LOAD16_WORD_SWAP( "rcm.53",   0x100000, 0x80000, CRC(6062ae3a) SHA1(28a4d59bce0c341c240ee8cc92f85850ea8ffb10) )
	ROM_LOAD16_WORD_SWAP( "rcm.54",   0x180000, 0x80000, CRC(08c6f3bf) SHA1(6b8175748ff25b90572f914e4565935e27aa09a5) )
	ROM_LOAD16_WORD_SWAP( "rcm.55",   0x200000, 0x80000, CRC(f97dfccc) SHA1(752a3855d78e55dc31291e14d0223104691784f4) )
	ROM_LOAD16_WORD_SWAP( "rcm.56",   0x280000, 0x80000, CRC(ade475bc) SHA1(02ae6bc21d5e41e05595845f264c9ad040d70b37) )
	ROM_LOAD16_WORD_SWAP( "rcm.57",   0x300000, 0x80000, CRC(075effb3) SHA1(4be02d966d933c0d92908c5e05842c6b33c9703b) )
	ROM_LOAD16_WORD_SWAP( "rcm.58",   0x380000, 0x80000, CRC(f6c1f87b) SHA1(d6cd8d2bac96404b6983d738093b7177d478f12e) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "rmancp2j.key", 0x000000, 0x000014, CRC(17309a70) SHA1(7d72a07bd556874a4b9b5cf3727d3c547051bb7a) )
ROM_END

ROM_START( rockman2hc01 ) //rockman2k
	ROM_REGION(CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "rm2_hc01.03", 0x000000, 0x80000, CRC(6ba5e8d2) SHA1(73d925dee1fc3f910b13525703784a19045dd42a) )
	ROM_LOAD16_WORD_SWAP( "rm2_hc01.04", 0x080000, 0x80000, CRC(211105c9) SHA1(72f83c58a2729e7a6d1a469c6bbc8236d722181a) )
	ROM_LOAD16_WORD_SWAP( "rm2.05",   0x100000, 0x80000, CRC(02ee9efc) SHA1(1b80c40389b51a03b930051f232630616c12e6c5) )

	ROM_REGION( 0x1000000, "gfx", ROMREGION_ERASE00 )
	ROM_FILL(              0x000000, 0x800000, 0x00 )
	ROM_LOAD64_WORD( "rm2_hc01.14m",  0x800000, 0x200000, CRC(712ccd27) SHA1(45fa1380fb9f11624369b3d478713e8319f32322) )
	ROM_LOAD64_WORD( "rm2_hc01.16m",  0x800002, 0x200000, CRC(ba4cc30b) SHA1(75b2697de7891c66c64285cb12e1b28af5aec668) )
	ROM_LOAD64_WORD( "rm2_hc01.18m",  0x800004, 0x200000, CRC(53cb1a05) SHA1(91a34006d63c5d8c28ea1df15470abab45c69834) )
	ROM_LOAD64_WORD( "rm2_hc01.20m",  0x800006, 0x200000, CRC(7b019f2c) SHA1(cfbb1dbbca954a9d33d5b53e406c24316018b2be) )

	ROM_REGION(QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "rm2.01a",  0x00000, 0x08000, CRC(d18e7859) SHA1(0939fac70042d0b4db5c2fdcef1f79b95febd45e) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "rm2.02",   0x28000, 0x20000, CRC(c463ece0) SHA1(5c3e41eb61610b3f8c431206f6672907e3a0bdb0) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "rm2.11m",   0x000000, 0x200000, CRC(2106174d) SHA1(0a35d9ca8ebcad74904b20648d5320f839d6377e) )
	ROM_LOAD16_WORD_SWAP( "rm2.12m",   0x200000, 0x200000, CRC(546c1636) SHA1(f96b172ab899f2c6ee17a5dd1fb61af9432e3cd2) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "rockman2j.key", 0x00, 0x14, CRC(c590187a) SHA1(f9140da0849711938c4d8a98fb38bc1504582a43) )
ROM_END

ROM_START( sfahc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sfz_hc01.03d", 0x000000, 0x80000, CRC(b67268ef) SHA1(b53802a3ba3ee6c14c01ab54c518dad84148708c) )
	ROM_LOAD16_WORD_SWAP( "sfz.04b",  0x080000, 0x80000, CRC(8b73b0e5) SHA1(5318761f615c21395366b5333e75eaaa73ef2073) )
	ROM_LOAD16_WORD_SWAP( "sfz.05a",  0x100000, 0x80000, CRC(0810544d) SHA1(5f39bda3e7b16508eb58e5a2e0cc58c09cf428ce) )
	ROM_LOAD16_WORD_SWAP( "sfz.06",   0x180000, 0x80000, CRC(806e8f38) SHA1(b6d6912aa8f2f590335d7ff9a8214648e7131ebb) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROM_FILL(              0x000000, 0x800000, 0x00 )
	ROMX_LOAD( "sfz.14m",  0x800000, 0x200000, CRC(90fefdb3) SHA1(5eb28c8de57acfeaefebdd01509c7d9ba5244705) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfz.16m",  0x800002, 0x200000, CRC(5354c948) SHA1(07588f1ba6addc04fef3274c971174aaf3e632ab) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfz.18m",  0x800004, 0x200000, CRC(41a1e790) SHA1(ce25dad542308691dbe9606b26279bbd59ea4b81) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfz.20m",  0x800006, 0x200000, CRC(a549df98) SHA1(f054e95df650a891ef56da8bfb31cb2c945a9aed) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sfz.01",   0x00000, 0x08000, CRC(ffffec7d) SHA1(75b4aef001b72a0f571b51b2b97803facc1832dd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sfz.02",   0x28000, 0x20000, CRC(45f46a08) SHA1(e32dbd27b52ab708278045b5a829376e55a4ca81) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sfz.11m",   0x000000, 0x200000, CRC(c4b093cd) SHA1(256526bb693a0b72443f047e060304c9b739acd1) )
	ROM_LOAD16_WORD_SWAP( "sfz.12m",   0x200000, 0x200000, CRC(8bdbc4b4) SHA1(0e21c9a75a17a7e7dfd8bb51098c2b9dc4c933ec) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa.key",      0x000000, 0x000014, CRC(7c095631) SHA1(aa54369b385435991ae884801228427a0d07cfc7) )
ROM_END

ROM_START( sfahc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sfz_hc02.03d", 0x000000, 0x80000, CRC(2ebec801) SHA1(5070d307a3ee66d9dfcf754677c086358a87c8c4) )
	ROM_LOAD16_WORD_SWAP( "sfz.04b",  0x080000, 0x80000, CRC(8b73b0e5) SHA1(5318761f615c21395366b5333e75eaaa73ef2073) )
	ROM_LOAD16_WORD_SWAP( "sfz.05a",  0x100000, 0x80000, CRC(0810544d) SHA1(5f39bda3e7b16508eb58e5a2e0cc58c09cf428ce) )
	ROM_LOAD16_WORD_SWAP( "sfz.06",   0x180000, 0x80000, CRC(806e8f38) SHA1(b6d6912aa8f2f590335d7ff9a8214648e7131ebb) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROM_FILL(              0x000000, 0x800000, 0x00 )
	ROMX_LOAD( "sfz.14m",  0x800000, 0x200000, CRC(90fefdb3) SHA1(5eb28c8de57acfeaefebdd01509c7d9ba5244705) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfz.16m",  0x800002, 0x200000, CRC(5354c948) SHA1(07588f1ba6addc04fef3274c971174aaf3e632ab) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfz.18m",  0x800004, 0x200000, CRC(41a1e790) SHA1(ce25dad542308691dbe9606b26279bbd59ea4b81) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfz.20m",  0x800006, 0x200000, CRC(a549df98) SHA1(f054e95df650a891ef56da8bfb31cb2c945a9aed) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sfz.01",   0x00000, 0x08000, CRC(ffffec7d) SHA1(75b4aef001b72a0f571b51b2b97803facc1832dd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sfz.02",   0x28000, 0x20000, CRC(45f46a08) SHA1(e32dbd27b52ab708278045b5a829376e55a4ca81) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sfz.11m",   0x000000, 0x200000, CRC(c4b093cd) SHA1(256526bb693a0b72443f047e060304c9b739acd1) )
	ROM_LOAD16_WORD_SWAP( "sfz.12m",   0x200000, 0x200000, CRC(8bdbc4b4) SHA1(0e21c9a75a17a7e7dfd8bb51098c2b9dc4c933ec) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa.key",      0x000000, 0x000014, CRC(7c095631) SHA1(aa54369b385435991ae884801228427a0d07cfc7) )
ROM_END

ROM_START( sfahc03 ) //sfah
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sfz_hc03.03d", 0x000000, 0x80000, CRC(ef6eee82) SHA1(71a6deaa17c66befe30cb6d158ab4a93a8db1c44) )
	ROM_LOAD16_WORD_SWAP( "sfz.04b",  0x080000, 0x80000, CRC(8b73b0e5) SHA1(5318761f615c21395366b5333e75eaaa73ef2073) )
	ROM_LOAD16_WORD_SWAP( "sfz.05a",  0x100000, 0x80000, CRC(0810544d) SHA1(5f39bda3e7b16508eb58e5a2e0cc58c09cf428ce) )
	ROM_LOAD16_WORD_SWAP( "sfz_hc03.06", 0x180000, 0x80000, CRC(b6c4fec7) SHA1(602c9acb8034219334df05ff4d5dc67514823182) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROM_FILL(              0x000000, 0x800000, 0x00 )
	ROMX_LOAD( "sfz.14m",  0x800000, 0x200000, CRC(90fefdb3) SHA1(5eb28c8de57acfeaefebdd01509c7d9ba5244705) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfz.16m",  0x800002, 0x200000, CRC(5354c948) SHA1(07588f1ba6addc04fef3274c971174aaf3e632ab) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfz.18m",  0x800004, 0x200000, CRC(41a1e790) SHA1(ce25dad542308691dbe9606b26279bbd59ea4b81) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfz.20m",  0x800006, 0x200000, CRC(a549df98) SHA1(f054e95df650a891ef56da8bfb31cb2c945a9aed) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sfz.01",   0x00000, 0x08000, CRC(ffffec7d) SHA1(75b4aef001b72a0f571b51b2b97803facc1832dd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sfz.02",   0x28000, 0x20000, CRC(45f46a08) SHA1(e32dbd27b52ab708278045b5a829376e55a4ca81) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sfz.11m",   0x000000, 0x200000, CRC(c4b093cd) SHA1(256526bb693a0b72443f047e060304c9b739acd1) )
	ROM_LOAD16_WORD_SWAP( "sfz.12m",   0x200000, 0x200000, CRC(8bdbc4b4) SHA1(0e21c9a75a17a7e7dfd8bb51098c2b9dc4c933ec) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa.key",      0x00, 0x14, CRC(7c095631) SHA1(aa54369b385435991ae884801228427a0d07cfc7) )
ROM_END

ROM_START( sfahc04 ) //sfaek
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sfz_hc04.03d", 0x000000, 0x80000, CRC(ff9f72cc) SHA1(2b79b5833bb9c6396398a336d6e9385fb6af57c4) )
	ROM_LOAD16_WORD_SWAP( "sfz.04b",  0x080000, 0x80000, CRC(8b73b0e5) SHA1(5318761f615c21395366b5333e75eaaa73ef2073) )
	ROM_LOAD16_WORD_SWAP( "sfz.05a",  0x100000, 0x80000, CRC(0810544d) SHA1(5f39bda3e7b16508eb58e5a2e0cc58c09cf428ce) )
	ROM_LOAD16_WORD_SWAP( "sfz.06",  0x180000, 0x80000, CRC(806e8f38) SHA1(b6d6912aa8f2f590335d7ff9a8214648e7131ebb) )

	ROM_REGION( 0x1000000, "gfx", ROMREGION_ERASE00 )
	ROM_LOAD64_WORD( "sfz_hc04.14m",  0x800000, 0x200000, CRC(2abed9af) SHA1(0996e70f3f6b4aac894aa0ef5a637b06ce6571bf) )
	ROM_LOAD64_WORD( "sfz_hc04.16m",  0x800002, 0x200000, CRC(e30c4e37) SHA1(e999e7ac3b85a3cff2332f24faba748683962e7d) )
	ROM_LOAD64_WORD( "sfz_hc04.18m",  0x800004, 0x200000, CRC(a5a760b9) SHA1(60940a5057ce3afd2135b08643049532b92fca45) )
	ROM_LOAD64_WORD( "sfz_hc04.20m",  0x800006, 0x200000, CRC(c72b7c2d) SHA1(7342fea8e32b39d262f2f4b81f2ba54c1de1ada1) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sfz.01",   0x00000, 0x08000, CRC(ffffec7d) SHA1(75b4aef001b72a0f571b51b2b97803facc1832dd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sfz.02",   0x28000, 0x20000, CRC(45f46a08) SHA1(e32dbd27b52ab708278045b5a829376e55a4ca81) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sfz.11m",   0x000000, 0x200000, CRC(c4b093cd) SHA1(256526bb693a0b72443f047e060304c9b739acd1) )
	ROM_LOAD16_WORD_SWAP( "sfz.12m",   0x200000, 0x200000, CRC(8bdbc4b4) SHA1(0e21c9a75a17a7e7dfd8bb51098c2b9dc4c933ec) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfzj.key",     0x00, 0x14, CRC(355d85b8) SHA1(5da2c407852ce7b28153f3f94de8328802ff2f2d) )
ROM_END

ROM_START( sfa2hc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz2e_hc02.03", 0x000000, 0x80000, CRC(6cbeb97d) SHA1(054cf7a0bbcb84bcd77ff2c5a084754f2c7694aa) )
	ROM_LOAD16_WORD_SWAP( "sz2e.04", 0x080000, 0x80000, CRC(22d17b26) SHA1(2d7a9cedae1bb2b7cfb80d2bfcf24cb7738df0bf) )
	ROM_LOAD16_WORD_SWAP( "sz2.05",  0x100000, 0x80000, CRC(4b442a7c) SHA1(a0d7d229cff8efb2a253ff06270258b0b4d2761e) )
	ROM_LOAD16_WORD_SWAP( "sz2.06",  0x180000, 0x80000, CRC(5b1d49c0) SHA1(f0a0c894c9cbe2b18e7f59058665949ee0025732) )
	ROM_LOAD16_WORD_SWAP( "sz2.07",  0x200000, 0x80000, CRC(8e184246) SHA1(c51f6480cfa1dcec6c4713fd38c7a27338c3fa65) )
	ROM_LOAD16_WORD_SWAP( "sz2.08",  0x280000, 0x80000, CRC(0fe8585d) SHA1(0cd5369a5aa90c98d8dc1ff3342cd4d990631cff) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "sz2.13m",   0x0000000, 0x400000, CRC(4d1f1f22) SHA1(659fb4305bcf0cbbbbec97ede6e68a8323b13308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.15m",   0x0000002, 0x400000, CRC(19cea680) SHA1(4cb88963a0fbcef191c8419b6379387c01b4c81e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.17m",   0x0000004, 0x400000, CRC(e01b4588) SHA1(c2936608fd75ff6cd5fa94c6d6d6f0c77c44a450) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.19m",   0x0000006, 0x400000, CRC(0feeda64) SHA1(f5b350601437bd94b70d97feb23d791df19da6b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz2.01a",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz2.02a",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz2.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sz2.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa2.key",     0x000000, 0x000014, CRC(1578dcb0) SHA1(a8bc83b341f9ea2bcc18861419bd574d159c6fcc) )
ROM_END

ROM_START( sfa2hc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz2_hc04.03", 0x000000, 0x80000, CRC(f24e7b3a) SHA1(0cf5169fcf46dcea5a100bf75a5dcd791c51b671) )
	ROM_LOAD16_WORD_SWAP( "sz2e.04", 0x080000, 0x80000, CRC(22d17b26) SHA1(2d7a9cedae1bb2b7cfb80d2bfcf24cb7738df0bf) )
	ROM_LOAD16_WORD_SWAP( "sz2.05",  0x100000, 0x80000, CRC(4b442a7c) SHA1(a0d7d229cff8efb2a253ff06270258b0b4d2761e) )
	ROM_LOAD16_WORD_SWAP( "sz2.06",  0x180000, 0x80000, CRC(5b1d49c0) SHA1(f0a0c894c9cbe2b18e7f59058665949ee0025732) )
	ROM_LOAD16_WORD_SWAP( "sz2.07",  0x200000, 0x80000, CRC(8e184246) SHA1(c51f6480cfa1dcec6c4713fd38c7a27338c3fa65) )
	ROM_LOAD16_WORD_SWAP( "sz2.08",  0x280000, 0x80000, CRC(0fe8585d) SHA1(0cd5369a5aa90c98d8dc1ff3342cd4d990631cff) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "sz2.13m",   0x0000000, 0x400000, CRC(4d1f1f22) SHA1(659fb4305bcf0cbbbbec97ede6e68a8323b13308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.15m",   0x0000002, 0x400000, CRC(19cea680) SHA1(4cb88963a0fbcef191c8419b6379387c01b4c81e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.17m",   0x0000004, 0x400000, CRC(e01b4588) SHA1(c2936608fd75ff6cd5fa94c6d6d6f0c77c44a450) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.19m",   0x0000006, 0x400000, CRC(0feeda64) SHA1(f5b350601437bd94b70d97feb23d791df19da6b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz2.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz2.01a",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz2.02a",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz2.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sz2.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa2.key",     0x00, 0x14, CRC(1578dcb0) SHA1(a8bc83b341f9ea2bcc18861419bd574d159c6fcc) )
ROM_END

ROM_START( sfa2hc03 ) //sfa2ultra
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz2_hc07.03a", 0x000000, 0x80000, CRC(1c7fcea1) SHA1(b2ff37bcc4cc7b03af85efebb534941ccd4836e5) )
	ROM_LOAD16_WORD_SWAP( "sz2u.04a", 0x080000, 0x80000, CRC(fae0e9c3) SHA1(d84cfbf16079f9987df683911b83896b80b52b1a) )
	ROM_LOAD16_WORD_SWAP( "sz2u.05a", 0x100000, 0x80000, CRC(d02dd758) SHA1(581bcd451b1d081b9b73d4a1b485da9f29756613) )
	ROM_LOAD16_WORD_SWAP( "sz2u.06",  0x180000, 0x80000, CRC(c5c8eb63) SHA1(4ea033834c7b260877335296f88c0db484dea289) )
	ROM_LOAD16_WORD_SWAP( "sz2u.07",  0x200000, 0x80000, CRC(5de01cc5) SHA1(b19bfe970b217c96e782860fc3ae3fcb976ed30d) )
	ROM_LOAD16_WORD_SWAP( "sz2u.08",  0x280000, 0x80000, CRC(bea11d56) SHA1(a1d475066d36de7cc5d931671ccdcd89737bc7ee) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROM_LOAD64_WORD( "sz2.13m",   0x0000000, 0x400000, CRC(4d1f1f22) SHA1(659fb4305bcf0cbbbbec97ede6e68a8323b13308) )
	ROM_LOAD64_WORD( "sz2.15m",   0x0000002, 0x400000, CRC(19cea680) SHA1(4cb88963a0fbcef191c8419b6379387c01b4c81e) )
	ROM_LOAD64_WORD( "sz2.17m",   0x0000004, 0x400000, CRC(e01b4588) SHA1(c2936608fd75ff6cd5fa94c6d6d6f0c77c44a450) )
	ROM_LOAD64_WORD( "sz2.19m",   0x0000006, 0x400000, CRC(0feeda64) SHA1(f5b350601437bd94b70d97feb23d791df19da6b3) )
	ROM_LOAD64_WORD( "sz2.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) )
	ROM_LOAD64_WORD( "sz2.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) )
	ROM_LOAD64_WORD( "sz2.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) )
	ROM_LOAD64_WORD( "sz2.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz2.01a",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz2.02a",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz2.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sz2.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa2u.key",    0x000000, 0x000014, CRC(4a8d91ef) SHA1(e22567ab83b35c39c6545742bc85ca98ae97f288) )
ROM_END

ROM_START( sfa2hc04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz2j_hc04.03b", 0x000000, 0x80000, CRC(e46526a9) SHA1(07f2a35fb24d0dcfc48fdc0d5328d4c710a6cea7) )
	ROM_LOAD16_WORD_SWAP( "sz2j_hc04.04b", 0x080000, 0x80000, CRC(5f8f5bc3) SHA1(a46e357e81003c74f7bed8b661c73eb4eb647936) )
	ROM_LOAD16_WORD_SWAP( "sz2j.05b",  0x100000, 0x80000, CRC(dd224156) SHA1(85d29f2a288430d51c53b88130f255131e5dc601) )
	ROM_LOAD16_WORD_SWAP( "sz2j.06b",  0x180000, 0x80000, CRC(a45a75a6) SHA1(e9cd4ad08ac0d058e9e1660acb07eb350a141fd6) )
	ROM_LOAD16_WORD_SWAP( "sz2j_hc04.07b", 0x200000, 0x80000, CRC(515ceb77) SHA1(25269af66e480484d432fa12076ffe26ab958e37) )
	ROM_LOAD16_WORD_SWAP( "sz2j.08b",  0x280000, 0x80000, CRC(92b66e01) SHA1(f09cb38aa49b22a9c98219fb2ad8a66b11fa5872) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROM_LOAD64_WORD( "sz2j_hc04.13m",   0x0000000, 0x400000, CRC(10ef2d2b) SHA1(e2bac04e12763fea420ea544eef7b15f2b908b2a) )
	ROM_LOAD64_WORD( "sz2j_hc04.15m",   0x0000002, 0x400000, CRC(fcc1f004) SHA1(3480c1665f78fb3f7b0467e7dedf8b170e8a4b96) )
	ROM_LOAD64_WORD( "sz2j_hc04.17m",   0x0000004, 0x400000, CRC(e364b775) SHA1(f15218c33292049aa7fbc3e4a8de735473a5b9e3) )
	ROM_LOAD64_WORD( "sz2j_hc04.19m",   0x0000006, 0x400000, CRC(ea68b6a9) SHA1(d116adc03593e2809e32c3de55c5cf70bebf308e) )
	ROM_LOAD64_WORD( "sz2.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) )
	ROM_LOAD64_WORD( "sz2.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) )
	ROM_LOAD64_WORD( "sz2.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) )
	ROM_LOAD64_WORD( "sz2.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz2.01a",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz2.02a",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz2.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sz2.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfz2j.key",    0x00, 0x14, CRC(455bd098) SHA1(6a928a2d44f416ccdb0c09a8dd7466ac12f38110) )
ROM_END

ROM_START( sfa3hc01 ) //sfa3ce
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3e_hc01.03c", 0x000000, 0x80000, CRC(e6a3c330) SHA1(39c5c9219e9c974b861c1bc083e142b2db811d25) )
	ROM_LOAD16_WORD_SWAP( "sz3e_hc01.04c", 0x080000, 0x80000, CRC(78650280) SHA1(d9c2a4a8f4dc076d5a8b6db612270e6d30618f6f) )
	ROM_LOAD16_WORD_SWAP( "sz3.05c",  0x100000, 0x80000, CRC(57fd0a40) SHA1(bc2d5f4d57117bbf58b1adb088e00424ef489e92) )
	ROM_LOAD16_WORD_SWAP( "sz3.06c",  0x180000, 0x80000, CRC(f6305f8b) SHA1(3fd1ebdbad96103aca604e950b488e52460a71ec) )
	ROM_LOAD16_WORD_SWAP( "sz3.07c",  0x200000, 0x80000, CRC(6eab0f6f) SHA1(f8d093dda65cf4e8a3000dc1b96355bb03dcb495) )
	ROM_LOAD16_WORD_SWAP( "sz3.08c",  0x280000, 0x80000, CRC(910c4a3b) SHA1(dbd41280f9b16ad6a5b8f12092549970349395f1) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc01.09c",  0x300000, 0x80000, CRC(8353dae0) SHA1(b6fd70d95ed5180e4fa953b30f3668b64a24343a) )
	ROM_LOAD16_WORD_SWAP( "sz3.10b",  0x380000, 0x80000, CRC(deb2ff52) SHA1(0aa4722aad68a04164946c78bf05752f947b4322) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "sz3_hc01.13m",   0x0000000, 0x400000, CRC(d941f463) SHA1(fae09d5d29ef3d9650440e589ac574c98f20b899) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc01.15m",   0x0000002, 0x400000, CRC(d25f4fbf) SHA1(dee478f694c11f2ab17821f471ed2ed270d5d113) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc01.17m",   0x0000004, 0x400000, CRC(5c210d31) SHA1(27e6f75640f1a8b06e23b820fdfcb22728d517cc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc01.19m",   0x0000006, 0x400000, CRC(a0b6f359) SHA1(4e053f29fda3211d7356d3af8005ad195b199c2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.14m",   0x1000000, 0x400000, CRC(5ff98297) SHA1(9e0ce43380b776c7a03872bafd4856f6fa60bda7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.16m",   0x1000002, 0x400000, CRC(52b5bdee) SHA1(7918204dc457f7a146d8fb8cf7242dfed3109fd8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.18m",   0x1000004, 0x400000, CRC(40631ed5) SHA1(c18c56822b90a71ca5fbdf3440eb2671011f3d8f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.20m",   0x1000006, 0x400000, CRC(763409b4) SHA1(af60a5116c1ca9050366a35ea29128921867f3cc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz3.01",   0x00000, 0x08000, CRC(de810084) SHA1(fd0b969b732921ed8b40c16fbfa30ee09c7a7cbd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz3.02",   0x28000, 0x20000, CRC(72445dc4) SHA1(14fca7596ac45ba655016eef5b6120f9f9671c23) )

	ROM_REGION( 0x800000, "qsound", 0 ) /* QSound samples */
	ROM_LOAD16_WORD_SWAP( "sz3.11m",   0x000000, 0x400000, CRC(1c89eed1) SHA1(649a0b0a3eb72e2e69e9fb1ac51a58b70daa39f3) )
	ROM_LOAD16_WORD_SWAP( "sz3.12m",   0x400000, 0x400000, CRC(f392b13a) SHA1(fa04ce0370144a49bd1d5acd873eef87b0dc9d15) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa3u.key",    0x000000, 0x000014, CRC(4a8f98c1) SHA1(11953de12ed8fbb6f60ad03b1ba5e22a429b7cfa) )
ROM_END

ROM_START( sfa3hc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3_hc09.03c", 0x000000, 0x80000, CRC(c04b48df) SHA1(e66d3fd367c0409757ad113e227c8b0c7368c21a) )
	ROM_LOAD16_WORD_SWAP( "sz3e.04c", 0x080000, 0x80000, CRC(5ad3f721) SHA1(fec11cc5f63593f0181eb28ae85ad916686793eb) )
	ROM_LOAD16_WORD_SWAP( "sz3.05c",  0x100000, 0x80000, CRC(57fd0a40) SHA1(bc2d5f4d57117bbf58b1adb088e00424ef489e92) )
	ROM_LOAD16_WORD_SWAP( "sz3.06c",  0x180000, 0x80000, CRC(f6305f8b) SHA1(3fd1ebdbad96103aca604e950b488e52460a71ec) )
	ROM_LOAD16_WORD_SWAP( "sz3.07c",  0x200000, 0x80000, CRC(6eab0f6f) SHA1(f8d093dda65cf4e8a3000dc1b96355bb03dcb495) )
	ROM_LOAD16_WORD_SWAP( "sz3.08c",  0x280000, 0x80000, CRC(910c4a3b) SHA1(dbd41280f9b16ad6a5b8f12092549970349395f1) )
	ROM_LOAD16_WORD_SWAP( "sz3.09c",  0x300000, 0x80000, CRC(b29e5199) SHA1(c6c215eb5aa37f678a9cafcbd8620969fb5ca12f) )
	ROM_LOAD16_WORD_SWAP( "sz3.10b",  0x380000, 0x80000, CRC(deb2ff52) SHA1(0aa4722aad68a04164946c78bf05752f947b4322) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "sz3.13m",   0x0000000, 0x400000, CRC(0f7a60d9) SHA1(c69e0ee22537312909dacc86d2e4be319d54e426) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.15m",   0x0000002, 0x400000, CRC(8e933741) SHA1(f4ac4bfe830dc7df9fe4f680e4e0c053e7cbd8fe) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.17m",   0x0000004, 0x400000, CRC(d6e98147) SHA1(37f331fbb1284db446faecade6f484f58c0e1b2a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.19m",   0x0000006, 0x400000, CRC(f31a728a) SHA1(f14136564648f006c1b74afda78349f260524b5f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.14m",   0x1000000, 0x400000, CRC(5ff98297) SHA1(9e0ce43380b776c7a03872bafd4856f6fa60bda7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.16m",   0x1000002, 0x400000, CRC(52b5bdee) SHA1(7918204dc457f7a146d8fb8cf7242dfed3109fd8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.18m",   0x1000004, 0x400000, CRC(40631ed5) SHA1(c18c56822b90a71ca5fbdf3440eb2671011f3d8f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.20m",   0x1000006, 0x400000, CRC(763409b4) SHA1(af60a5116c1ca9050366a35ea29128921867f3cc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz3.01",   0x00000, 0x08000, CRC(de810084) SHA1(fd0b969b732921ed8b40c16fbfa30ee09c7a7cbd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz3.02",   0x28000, 0x20000, CRC(72445dc4) SHA1(14fca7596ac45ba655016eef5b6120f9f9671c23) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3.11m",   0x000000, 0x400000, CRC(1c89eed1) SHA1(649a0b0a3eb72e2e69e9fb1ac51a58b70daa39f3) )
	ROM_LOAD16_WORD_SWAP( "sz3.12m",   0x400000, 0x400000, CRC(f392b13a) SHA1(fa04ce0370144a49bd1d5acd873eef87b0dc9d15) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa3.key",     0x000000, 0x000014, CRC(54fa39c6) SHA1(a0d2f8e697a7a4201762cb02842581840b2a7f78) )
ROM_END

ROM_START( sfa3hc03 ) //sfa3xl
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3_hc10.03", 0x000000, 0x80000, CRC(9411ced4) SHA1(45c963125242eb78992d7d13c3f773f00115ba97) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc10.04", 0x080000, 0x80000, CRC(01a7b266) SHA1(32bec1fa10641c6c155e71827aaa9853e946f8c6) )
	ROM_LOAD16_WORD_SWAP( "sz3.05c",  0x100000, 0x80000, CRC(57fd0a40) SHA1(bc2d5f4d57117bbf58b1adb088e00424ef489e92) )
	ROM_LOAD16_WORD_SWAP( "sz3.06c",  0x180000, 0x80000, CRC(f6305f8b) SHA1(3fd1ebdbad96103aca604e950b488e52460a71ec) )
	ROM_LOAD16_WORD_SWAP( "sz3.07c",  0x200000, 0x80000, CRC(6eab0f6f) SHA1(f8d093dda65cf4e8a3000dc1b96355bb03dcb495) )
	ROM_LOAD16_WORD_SWAP( "sz3.08c",  0x280000, 0x80000, CRC(910c4a3b) SHA1(dbd41280f9b16ad6a5b8f12092549970349395f1) )
	ROM_LOAD16_WORD_SWAP( "sz3.09c",  0x300000, 0x80000, CRC(b29e5199) SHA1(c6c215eb5aa37f678a9cafcbd8620969fb5ca12f) )
	ROM_LOAD16_WORD_SWAP( "sz3.10b",  0x380000, 0x80000, CRC(deb2ff52) SHA1(0aa4722aad68a04164946c78bf05752f947b4322) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "sz3.13m",   0x0000000, 0x400000, CRC(0f7a60d9) SHA1(c69e0ee22537312909dacc86d2e4be319d54e426) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.15m",   0x0000002, 0x400000, CRC(8e933741) SHA1(f4ac4bfe830dc7df9fe4f680e4e0c053e7cbd8fe) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.17m",   0x0000004, 0x400000, CRC(d6e98147) SHA1(37f331fbb1284db446faecade6f484f58c0e1b2a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.19m",   0x0000006, 0x400000, CRC(f31a728a) SHA1(f14136564648f006c1b74afda78349f260524b5f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.14m",   0x1000000, 0x400000, CRC(5ff98297) SHA1(9e0ce43380b776c7a03872bafd4856f6fa60bda7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.16m",   0x1000002, 0x400000, CRC(52b5bdee) SHA1(7918204dc457f7a146d8fb8cf7242dfed3109fd8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.18m",   0x1000004, 0x400000, CRC(40631ed5) SHA1(c18c56822b90a71ca5fbdf3440eb2671011f3d8f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.20m",   0x1000006, 0x400000, CRC(763409b4) SHA1(af60a5116c1ca9050366a35ea29128921867f3cc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz3.01",   0x00000, 0x08000, CRC(de810084) SHA1(fd0b969b732921ed8b40c16fbfa30ee09c7a7cbd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz3.02",   0x28000, 0x20000, CRC(72445dc4) SHA1(14fca7596ac45ba655016eef5b6120f9f9671c23) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3.11m",   0x000000, 0x400000, CRC(1c89eed1) SHA1(649a0b0a3eb72e2e69e9fb1ac51a58b70daa39f3) )
	ROM_LOAD16_WORD_SWAP( "sz3.12m",   0x400000, 0x400000, CRC(f392b13a) SHA1(fa04ce0370144a49bd1d5acd873eef87b0dc9d15) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa3.key",     0x00, 0x14, CRC(54fa39c6) SHA1(a0d2f8e697a7a4201762cb02842581840b2a7f78) )
ROM_END

ROM_START( sfa3hc04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3_hc11.03", 0x000000, 0x80000, CRC(41b961b4) SHA1(e2865fa71b647b4a8a86cc260b13d6f9616859fa) )
	ROM_LOAD16_WORD_SWAP( "sz3e.04c", 0x080000, 0x80000, CRC(5ad3f721) SHA1(fec11cc5f63593f0181eb28ae85ad916686793eb) )
	ROM_LOAD16_WORD_SWAP( "sz3.05c",  0x100000, 0x80000, CRC(57fd0a40) SHA1(bc2d5f4d57117bbf58b1adb088e00424ef489e92) )
	ROM_LOAD16_WORD_SWAP( "sz3.06c",  0x180000, 0x80000, CRC(f6305f8b) SHA1(3fd1ebdbad96103aca604e950b488e52460a71ec) )
	ROM_LOAD16_WORD_SWAP( "sz3.07c",  0x200000, 0x80000, CRC(6eab0f6f) SHA1(f8d093dda65cf4e8a3000dc1b96355bb03dcb495) )
	ROM_LOAD16_WORD_SWAP( "sz3.08c",  0x280000, 0x80000, CRC(910c4a3b) SHA1(dbd41280f9b16ad6a5b8f12092549970349395f1) )
	ROM_LOAD16_WORD_SWAP( "sz3.09c",  0x300000, 0x80000, CRC(b29e5199) SHA1(c6c215eb5aa37f678a9cafcbd8620969fb5ca12f) )
	ROM_LOAD16_WORD_SWAP( "sz3.10b",  0x380000, 0x80000, CRC(deb2ff52) SHA1(0aa4722aad68a04164946c78bf05752f947b4322) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "sz3.13m",   0x0000000, 0x400000, CRC(0f7a60d9) SHA1(c69e0ee22537312909dacc86d2e4be319d54e426) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.15m",   0x0000002, 0x400000, CRC(8e933741) SHA1(f4ac4bfe830dc7df9fe4f680e4e0c053e7cbd8fe) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.17m",   0x0000004, 0x400000, CRC(d6e98147) SHA1(37f331fbb1284db446faecade6f484f58c0e1b2a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.19m",   0x0000006, 0x400000, CRC(f31a728a) SHA1(f14136564648f006c1b74afda78349f260524b5f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.14m",   0x1000000, 0x400000, CRC(5ff98297) SHA1(9e0ce43380b776c7a03872bafd4856f6fa60bda7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.16m",   0x1000002, 0x400000, CRC(52b5bdee) SHA1(7918204dc457f7a146d8fb8cf7242dfed3109fd8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.18m",   0x1000004, 0x400000, CRC(40631ed5) SHA1(c18c56822b90a71ca5fbdf3440eb2671011f3d8f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.20m",   0x1000006, 0x400000, CRC(763409b4) SHA1(af60a5116c1ca9050366a35ea29128921867f3cc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz3.01",   0x00000, 0x08000, CRC(de810084) SHA1(fd0b969b732921ed8b40c16fbfa30ee09c7a7cbd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz3.02",   0x28000, 0x20000, CRC(72445dc4) SHA1(14fca7596ac45ba655016eef5b6120f9f9671c23) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3.11m",   0x000000, 0x400000, CRC(1c89eed1) SHA1(649a0b0a3eb72e2e69e9fb1ac51a58b70daa39f3) )
	ROM_LOAD16_WORD_SWAP( "sz3.12m",   0x400000, 0x400000, CRC(f392b13a) SHA1(fa04ce0370144a49bd1d5acd873eef87b0dc9d15) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa3.key",     0x00, 0x14, CRC(54fa39c6) SHA1(a0d2f8e697a7a4201762cb02842581840b2a7f78) )
ROM_END

ROM_START( sfa3hc05 ) //sfz3te
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3_hc13.03", 0x000000, 0x80000, CRC(2fb19531) SHA1(27c9badb2be5b231a240929a8a9d5e75677478b7) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc13.04", 0x080000, 0x80000, CRC(01e60fc4) SHA1(f51b0a10183f310f195c24c5b68f480974404d08) )
	ROM_LOAD16_WORD_SWAP( "sz3.05",  0x100000, 0x80000, CRC(9b21518a) SHA1(5a928307cb90a98a62e7598cb101fb66d62b85f9) )
	ROM_LOAD16_WORD_SWAP( "sz3.06",  0x180000, 0x80000, CRC(e7a6c3a7) SHA1(63441eb19efcbf9149f4b723d3e9191fa972de2a) )
	ROM_LOAD16_WORD_SWAP( "sz3.07",  0x200000, 0x80000, CRC(ec4c0cfd) SHA1(1a5148e77bf633c728a8179dacb59c776f981bc4) )
	ROM_LOAD16_WORD_SWAP( "sz3.08",  0x280000, 0x80000, CRC(5c7e7240) SHA1(33bdcdd1889f8fa77916373ed33b0854410d0263) )
	ROM_LOAD16_WORD_SWAP( "sz3.09",  0x300000, 0x80000, CRC(c5589553) SHA1(cda1fdc2ab2f390a2358defd9923a2796093926d) )
	ROM_LOAD16_WORD_SWAP( "sz3.10",  0x380000, 0x80000, CRC(a9717252) SHA1(7ee94ace2a49e4e5d30474e49c0da04a488010fe) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "sz3.13m",   0x0000000, 0x400000, CRC(0f7a60d9) SHA1(c69e0ee22537312909dacc86d2e4be319d54e426) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.15m",   0x0000002, 0x400000, CRC(8e933741) SHA1(f4ac4bfe830dc7df9fe4f680e4e0c053e7cbd8fe) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.17m",   0x0000004, 0x400000, CRC(d6e98147) SHA1(37f331fbb1284db446faecade6f484f58c0e1b2a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.19m",   0x0000006, 0x400000, CRC(f31a728a) SHA1(f14136564648f006c1b74afda78349f260524b5f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.14m",   0x1000000, 0x400000, CRC(5ff98297) SHA1(9e0ce43380b776c7a03872bafd4856f6fa60bda7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.16m",   0x1000002, 0x400000, CRC(52b5bdee) SHA1(7918204dc457f7a146d8fb8cf7242dfed3109fd8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.18m",   0x1000004, 0x400000, CRC(40631ed5) SHA1(c18c56822b90a71ca5fbdf3440eb2671011f3d8f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3.20m",   0x1000006, 0x400000, CRC(763409b4) SHA1(af60a5116c1ca9050366a35ea29128921867f3cc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz3.01",   0x00000, 0x08000, CRC(de810084) SHA1(fd0b969b732921ed8b40c16fbfa30ee09c7a7cbd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz3.02",   0x28000, 0x20000, CRC(72445dc4) SHA1(14fca7596ac45ba655016eef5b6120f9f9671c23) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3.11m",   0x000000, 0x400000, CRC(1c89eed1) SHA1(649a0b0a3eb72e2e69e9fb1ac51a58b70daa39f3) )
	ROM_LOAD16_WORD_SWAP( "sz3.12m",   0x400000, 0x400000, CRC(f392b13a) SHA1(fa04ce0370144a49bd1d5acd873eef87b0dc9d15) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfz3j.key",    0x00, 0x14, CRC(d30cca8d) SHA1(b05869902d4d5968d5f79ed6165eb4b78e1ddcdd) )
ROM_END

ROM_START( sfa3hc06 ) //sfa3br
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3_hc06.03c", 0x000000, 0x80000, CRC(b2a99137) SHA1(cba8777cd241e270c19fe375489efc421cc01549) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc06.04c", 0x080000, 0x80000, CRC(3e5cefe6) SHA1(f889bc9f7212e27d5df50ebda909b60e85dbfe29) )
	ROM_LOAD16_WORD_SWAP( "sz3.05c",  0x100000, 0x80000, CRC(57fd0a40) SHA1(bc2d5f4d57117bbf58b1adb088e00424ef489e92) )
	ROM_LOAD16_WORD_SWAP( "sz3.06c",  0x180000, 0x80000, CRC(f6305f8b) SHA1(3fd1ebdbad96103aca604e950b488e52460a71ec) )
	ROM_LOAD16_WORD_SWAP( "sz3.07c",  0x200000, 0x80000, CRC(6eab0f6f) SHA1(f8d093dda65cf4e8a3000dc1b96355bb03dcb495) )
	ROM_LOAD16_WORD_SWAP( "sz3.08c",  0x280000, 0x80000, CRC(910c4a3b) SHA1(dbd41280f9b16ad6a5b8f12092549970349395f1) )
	ROM_LOAD16_WORD_SWAP( "sz3.09c",  0x300000, 0x80000, CRC(b29e5199) SHA1(c6c215eb5aa37f678a9cafcbd8620969fb5ca12f) )
	ROM_LOAD16_WORD_SWAP( "sz3.10b",  0x380000, 0x80000, CRC(deb2ff52) SHA1(0aa4722aad68a04164946c78bf05752f947b4322) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "sz3_hc06.13m",   0x0000000, 0x400000, CRC(f18ffe2d) SHA1(3b7251f3027461a847749c8238ff9b0a9ab1c405) )
	ROM_LOAD64_WORD( "sz3_hc06.15m",   0x0000002, 0x400000, CRC(3283878c) SHA1(e879ad81be09f73949c188e45506f63a114999c9) )
	ROM_LOAD64_WORD( "sz3_hc06.17m",   0x0000004, 0x400000, CRC(869e0ae2) SHA1(30e018f3b38dbdac6cd1d228865627811886624f) )
	ROM_LOAD64_WORD( "sz3_hc06.19m",   0x0000006, 0x400000, CRC(81e0ebfa) SHA1(449b7afc0c88edbab51b27abef4be5ff3698470c) )
	ROM_LOAD64_WORD( "sz3.14m",   0x1000000, 0x400000, CRC(5ff98297) SHA1(9e0ce43380b776c7a03872bafd4856f6fa60bda7) )
	ROM_LOAD64_WORD( "sz3.16m",   0x1000002, 0x400000, CRC(52b5bdee) SHA1(7918204dc457f7a146d8fb8cf7242dfed3109fd8) )
	ROM_LOAD64_WORD( "sz3.18m",   0x1000004, 0x400000, CRC(40631ed5) SHA1(c18c56822b90a71ca5fbdf3440eb2671011f3d8f) )
	ROM_LOAD64_WORD( "sz3.20m",   0x1000006, 0x400000, CRC(763409b4) SHA1(af60a5116c1ca9050366a35ea29128921867f3cc) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz3.01",   0x00000, 0x08000, CRC(de810084) SHA1(fd0b969b732921ed8b40c16fbfa30ee09c7a7cbd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz3.02",   0x28000, 0x20000, CRC(72445dc4) SHA1(14fca7596ac45ba655016eef5b6120f9f9671c23) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3.11m",   0x000000, 0x400000, CRC(1c89eed1) SHA1(649a0b0a3eb72e2e69e9fb1ac51a58b70daa39f3) )
	ROM_LOAD16_WORD_SWAP( "sz3.12m",   0x400000, 0x400000, CRC(f392b13a) SHA1(fa04ce0370144a49bd1d5acd873eef87b0dc9d15) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfa3u.key",    0x00, 0x14, CRC(4a8f98c1) SHA1(11953de12ed8fbb6f60ad03b1ba5e22a429b7cfa) )
ROM_END

ROM_START( sfa3hc07 ) //sfz3mix
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3e_hc07.03c", 0x000000, 0x80000, CRC(39b106fe) SHA1(71a653d69889e24ef08f16ed19510b5beb4e6c88) )
	ROM_LOAD16_WORD_SWAP( "sz3e_hc07.04c", 0x080000, 0x80000, CRC(0cde4b42) SHA1(a87c5b0fd07881b6ea316a3dc8e8a0d4212b8ff3) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc07.05c",  0x100000, 0x80000, CRC(b8b19c1f) SHA1(72a38eb482b20e2e6c95dbadd0ef9108bbda2868) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc07.06c",  0x180000, 0x80000, CRC(35639da3) SHA1(7ad71481f38846e9c80556b241fcfacec638c66a) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc07.07c",  0x200000, 0x80000, CRC(a9d9f83e) SHA1(a4728207aefed7a97fafab291a427278ef77044e) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc07.08c",  0x280000, 0x80000, CRC(a85e33a5) SHA1(f6ce81bfa91008e60090df7cf8a9c73d4d8dee78) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc07.09c",  0x300000, 0x80000, CRC(7a5a0d3c) SHA1(4c9eb75c4b555a37e39d67c1318f4735bf7702f7) )
	ROM_LOAD16_WORD_SWAP( "sz3_hc07.10b",  0x380000, 0x80000, CRC(3fa5f874) SHA1(46a39c1cc6010a0c500b4b79b8709a93a7995e3d) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "sz3_hc07.13m",   0x0000000, 0x400000, CRC(93183516) SHA1(a4435cf5d384294dc5f85325b8f47f166020fe7b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc07.15m",   0x0000002, 0x400000, CRC(b06f14ce) SHA1(f653f8c10157102426430670f557d8fc2e0c70ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc07.17m",   0x0000004, 0x400000, CRC(661c1355) SHA1(4d53b8bbc466d947320c8c12bdff72b01493c20b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc07.19m",   0x0000006, 0x400000, CRC(7227f353) SHA1(343534f1679858fae27970a859d54c6e46d16748) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc07.14m",   0x1000000, 0x400000, CRC(62496779) SHA1(8534226cc1074097fce296ec1ab6e453f9a2b69d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc07.16m",   0x1000002, 0x400000, CRC(1e7aa3cb) SHA1(66bfe1d7897f9dfd02db0523e8296aa50f4cf8c5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc07.18m",   0x1000004, 0x400000, CRC(95e161ce) SHA1(ef863b415fe4f07f5acf1e5082378c7603d8e58c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sz3_hc07.20m",   0x1000006, 0x400000, CRC(a6afdc2d) SHA1(6bfd7261246f19cc12364fe02ba090d456a482ce) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sz3_hc07.01",   0x00000, 0x08000, CRC(5ac9bfe5) SHA1(85fa8599de7b035ceb8ee6ffb88c93f94572a0cd) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sz3_hc07.02",   0x28000, 0x20000, CRC(68a17d87) SHA1(f6ebdabdeb1d94a3293cbe55de31c10900f45375) )

	ROM_REGION( 0x800000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sz3_hc07.11m",   0x000000, 0x400000, CRC(ab9415fb) SHA1(8de2f4576aafe631f762d3a5aeb720642b98d2e8) )
	ROM_LOAD16_WORD_SWAP( "sz3.12m",   0x400000, 0x400000, CRC(f392b13a) SHA1(fa04ce0370144a49bd1d5acd873eef87b0dc9d15) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "phoenix.key",  0x000000, 0x000014, CRC(2cf772b0) SHA1(eff33c65a4f3862c231f9e4d6fefa7b34398dbf2) )
ROM_END

ROM_START( sfz2alhc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "szaj_hc01.03a", 0x000000, 0x80000, CRC(A4ad2f9e) SHA1(67b0dd178c797811ba9fe312a8a1b3e3b730d2a1) )
	ROM_LOAD16_WORD_SWAP( "szaj.04a", 0x080000, 0x80000, CRC(e7ca87c7) SHA1(e44c930b27431dd2b983d93471a440d292e7a8bb) )
	ROM_LOAD16_WORD_SWAP( "szaj.05a", 0x100000, 0x80000, CRC(c88ebf88) SHA1(e37cf232fc70b9a3254dea99754e288232f04e25) )
	ROM_LOAD16_WORD_SWAP( "szaj.06a", 0x180000, 0x80000, CRC(35ed5b7a) SHA1(b03cb92f594eb35fa374445f74930e9040a2baff) )
	ROM_LOAD16_WORD_SWAP( "szaj.07a", 0x200000, 0x80000, CRC(975dcb3e) SHA1(a2ca8e5a768e49cce9e2137ec0dcba9337ed2ad5) )
	ROM_LOAD16_WORD_SWAP( "szaj.08a", 0x280000, 0x80000, CRC(dc73f2d7) SHA1(09fa10e7d1ff5f0dac87a6cf3d66730e3ab9ad25) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "sza.13m",   0x0000000, 0x400000, CRC(4d1f1f22) SHA1(659fb4305bcf0cbbbbec97ede6e68a8323b13308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.15m",   0x0000002, 0x400000, CRC(19cea680) SHA1(4cb88963a0fbcef191c8419b6379387c01b4c81e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.17m",   0x0000004, 0x400000, CRC(e01b4588) SHA1(c2936608fd75ff6cd5fa94c6d6d6f0c77c44a450) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.19m",   0x0000006, 0x400000, CRC(0feeda64) SHA1(f5b350601437bd94b70d97feb23d791df19da6b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sza.01",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sza.02",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sza.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sza.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfz2alj.key",  0x00, 0x14, CRC(4c42320f) SHA1(0fabdab677416c5a8060526d997e6f80b26f9bb3) )
ROM_END

ROM_START( sfz2alhc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "szaj_hc02.03", 0x000000, 0x80000, CRC(fdb28eb2) SHA1(262b3e4b6c0fac9a7350dd241c776869a135a10d) )
	ROM_LOAD16_WORD_SWAP( "szaj_hc05.04", 0x080000, 0x80000, CRC(b124800a) SHA1(560e708e1296ac3e7e6b74bee99a152a0d1f6894) )
	ROM_LOAD16_WORD_SWAP( "szaj.05a", 0x100000, 0x80000, CRC(c88ebf88) SHA1(e37cf232fc70b9a3254dea99754e288232f04e25) )
	ROM_LOAD16_WORD_SWAP( "szaj.06a", 0x180000, 0x80000, CRC(35ed5b7a) SHA1(b03cb92f594eb35fa374445f74930e9040a2baff) )
	ROM_LOAD16_WORD_SWAP( "szaj.07a", 0x200000, 0x80000, CRC(975dcb3e) SHA1(a2ca8e5a768e49cce9e2137ec0dcba9337ed2ad5) )
	ROM_LOAD16_WORD_SWAP( "szaj.08a", 0x280000, 0x80000, CRC(dc73f2d7) SHA1(09fa10e7d1ff5f0dac87a6cf3d66730e3ab9ad25) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "sza.13m",   0x0000000, 0x400000, CRC(4d1f1f22) SHA1(659fb4305bcf0cbbbbec97ede6e68a8323b13308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.15m",   0x0000002, 0x400000, CRC(19cea680) SHA1(4cb88963a0fbcef191c8419b6379387c01b4c81e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.17m",   0x0000004, 0x400000, CRC(e01b4588) SHA1(c2936608fd75ff6cd5fa94c6d6d6f0c77c44a450) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.19m",   0x0000006, 0x400000, CRC(0feeda64) SHA1(f5b350601437bd94b70d97feb23d791df19da6b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sza.01",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sza.02",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sza.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sza.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfz2alj.key",  0x00, 0x14, CRC(4c42320f) SHA1(0fabdab677416c5a8060526d997e6f80b26f9bb3) )
ROM_END

ROM_START( sfz2alhc03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "szaa_hc03.03", 0x000000, 0x80000, CRC(c6919918) SHA1(d599bce464b8be26ce11bf6264bdd1528a83b7d3) )
	ROM_LOAD16_WORD_SWAP( "szaa.04", 0x080000, 0x80000, CRC(ae8ec36e) SHA1(b2f3de9e33169f6266aaabd5eae6c057ea10dcab) )
	ROM_LOAD16_WORD_SWAP( "szaa.05", 0x100000, 0x80000, CRC(f053a55e) SHA1(f98a8af5cd33a543a5596d59381f9adafed38854) )
	ROM_LOAD16_WORD_SWAP( "szaa.06", 0x180000, 0x80000, CRC(cfc0e7a8) SHA1(31ed58451c7a6ac88a8fccab369167694698f044) )
	ROM_LOAD16_WORD_SWAP( "szaa.07", 0x200000, 0x80000, CRC(5feb8b20) SHA1(13c79c9b72c3abf0a0b75d507d91ece71e460c06) )
	ROM_LOAD16_WORD_SWAP( "szaa.08", 0x280000, 0x80000, CRC(6eb6d412) SHA1(c858fec9c1dfea70dfcca629c1c24306f8ae6d81) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "sza.13m",   0x0000000, 0x400000, CRC(4d1f1f22) SHA1(659fb4305bcf0cbbbbec97ede6e68a8323b13308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.15m",   0x0000002, 0x400000, CRC(19cea680) SHA1(4cb88963a0fbcef191c8419b6379387c01b4c81e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.17m",   0x0000004, 0x400000, CRC(e01b4588) SHA1(c2936608fd75ff6cd5fa94c6d6d6f0c77c44a450) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.19m",   0x0000006, 0x400000, CRC(0feeda64) SHA1(f5b350601437bd94b70d97feb23d791df19da6b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sza.01",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sza.02",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sza.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sza.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfz2al.key",   0x000000, 0x000014, CRC(2904963e) SHA1(f4fa44646746ab4c6f2e76eaba57a7aee32e2933) )
ROM_END

ROM_START( sfz2alhc04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "szaj_hc04.03", 0x000000, 0x80000, CRC(67bc6f45) SHA1(d810865d890fc7830078e5dc13002f4447a0b3ea) )
	ROM_LOAD16_WORD_SWAP( "szaj_hc04.04", 0x080000, 0x80000, CRC(b124800a) SHA1(560e708e1296ac3e7e6b74bee99a152a0d1f6894) )
	ROM_LOAD16_WORD_SWAP( "szaj.05a", 0x100000, 0x80000, CRC(c88ebf88) SHA1(e37cf232fc70b9a3254dea99754e288232f04e25) )
	ROM_LOAD16_WORD_SWAP( "szaj.06a", 0x180000, 0x80000, CRC(35ed5b7a) SHA1(b03cb92f594eb35fa374445f74930e9040a2baff) )
	ROM_LOAD16_WORD_SWAP( "szaj.07a", 0x200000, 0x80000, CRC(975dcb3e) SHA1(a2ca8e5a768e49cce9e2137ec0dcba9337ed2ad5) )
	ROM_LOAD16_WORD_SWAP( "szaj.08a", 0x280000, 0x80000, CRC(dc73f2d7) SHA1(09fa10e7d1ff5f0dac87a6cf3d66730e3ab9ad25) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROMX_LOAD( "sza.13m",   0x0000000, 0x400000, CRC(4d1f1f22) SHA1(659fb4305bcf0cbbbbec97ede6e68a8323b13308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.15m",   0x0000002, 0x400000, CRC(19cea680) SHA1(4cb88963a0fbcef191c8419b6379387c01b4c81e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.17m",   0x0000004, 0x400000, CRC(e01b4588) SHA1(c2936608fd75ff6cd5fa94c6d6d6f0c77c44a450) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.19m",   0x0000006, 0x400000, CRC(0feeda64) SHA1(f5b350601437bd94b70d97feb23d791df19da6b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sza.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sza.01",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sza.02",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sza.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sza.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfz2alj.key",  0x00, 0x14, CRC(4c42320f) SHA1(0fabdab677416c5a8060526d997e6f80b26f9bb3) )
ROM_END

ROM_START( sfz2alhc05 ) //sfz2alek
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "szaj_hc05.03a", 0x000000, 0x80000, CRC(3b795a57) SHA1(ce003f59f6b2f122c690596ac99ba467766f6a30) )
	ROM_LOAD16_WORD_SWAP( "szaj_hc05.04a", 0x080000, 0x80000, CRC(9559af19) SHA1(f15ba3404f6e35e082b082b2560ecbfdd1a49e59) )
	ROM_LOAD16_WORD_SWAP( "szaj_hc05.05a", 0x100000, 0x80000, CRC(d2cb29fa) SHA1(eb7271409ec30692a5b81b4a8e163902b249f4f1) )
	ROM_LOAD16_WORD_SWAP( "szaj.06a", 0x180000, 0x80000, CRC(35ed5b7a) SHA1(b03cb92f594eb35fa374445f74930e9040a2baff) )
	ROM_LOAD16_WORD_SWAP( "szaj.07a", 0x200000, 0x80000, CRC(975dcb3e) SHA1(a2ca8e5a768e49cce9e2137ec0dcba9337ed2ad5) )
	ROM_LOAD16_WORD_SWAP( "szaj.08a", 0x280000, 0x80000, CRC(dc73f2d7) SHA1(09fa10e7d1ff5f0dac87a6cf3d66730e3ab9ad25) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROM_LOAD64_WORD( "sza.13m",   0x0000000, 0x400000, CRC(4d1f1f22) SHA1(659fb4305bcf0cbbbbec97ede6e68a8323b13308) )
	ROM_LOAD64_WORD( "sza.15m",   0x0000002, 0x400000, CRC(19cea680) SHA1(4cb88963a0fbcef191c8419b6379387c01b4c81e) )
	ROM_LOAD64_WORD( "sza.17m",   0x0000004, 0x400000, CRC(e01b4588) SHA1(c2936608fd75ff6cd5fa94c6d6d6f0c77c44a450) )
	ROM_LOAD64_WORD( "sza.19m",   0x0000006, 0x400000, CRC(0feeda64) SHA1(f5b350601437bd94b70d97feb23d791df19da6b3) )
	ROM_LOAD64_WORD( "sza.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) )
	ROM_LOAD64_WORD( "sza.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) )
	ROM_LOAD64_WORD( "sza.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) )
	ROM_LOAD64_WORD( "sza.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sza.01",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sza.02",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sza.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sza.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfz2alj.key",  0x00, 0x14, CRC(4c42320f) SHA1(0fabdab677416c5a8060526d997e6f80b26f9bb3) )
ROM_END

ROM_START( sfz2alhc06 ) //sfz2albr
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sza_hc06.03a", 0x000000, 0x80000, CRC(0e8e719b) SHA1(ef013adf386925c68f3d38159adfe447c8f259de) )
	ROM_LOAD16_WORD_SWAP( "sza_hc06.04a", 0x080000, 0x80000, CRC(bc7271a0) SHA1(601a0e21926a1d9aebebf41e6dc08523b6773338) )
	ROM_LOAD16_WORD_SWAP( "sza_hc06.05a", 0x100000, 0x80000, CRC(e19eee58) SHA1(f0a2f8606136450c375d9b43f182e4cee2ec1208) )
	ROM_LOAD16_WORD_SWAP( "szaa.06", 0x180000, 0x80000, CRC(cfc0e7a8) SHA1(31ed58451c7a6ac88a8fccab369167694698f044) )
	ROM_LOAD16_WORD_SWAP( "szaa.07", 0x200000, 0x80000, CRC(5feb8b20) SHA1(13c79c9b72c3abf0a0b75d507d91ece71e460c06) )
	ROM_LOAD16_WORD_SWAP( "szaa.08", 0x280000, 0x80000, CRC(6eb6d412) SHA1(c858fec9c1dfea70dfcca629c1c24306f8ae6d81) )

	ROM_REGION( 0x1400000, "gfx", 0 )
	ROM_LOAD64_WORD( "sza_hc06.13m",   0x0000000, 0x400000, CRC(a3b979fe) SHA1(236378162562aea3e522a182bbf395b020452893) )
	ROM_LOAD64_WORD( "sza_hc06.15m",   0x0000002, 0x400000, CRC(ab0e6693) SHA1(6f00bdf5064fb1cb2e152c2731d26a11cd8bf376) )
	ROM_LOAD64_WORD( "sza_hc06.17m",   0x0000004, 0x400000, CRC(ce0913ba) SHA1(684c402c7ca1e50018ef439331b5bd002f573db8) )
	ROM_LOAD64_WORD( "sza_hc06.19m",   0x0000006, 0x400000, CRC(3c8cffe6) SHA1(26d4ed4a20a4e84b8c87c7120b181371e428ad58) )
	ROM_LOAD64_WORD( "sza.14m",   0x1000000, 0x100000, CRC(0560c6aa) SHA1(f2bed3a8efef18052b51a7f0f6a888a18db813a1) )
	ROM_LOAD64_WORD( "sza.16m",   0x1000002, 0x100000, CRC(ae940f87) SHA1(39ee26333abbe302ba76dced0196a2e6b3b1d02a) )
	ROM_LOAD64_WORD( "sza.18m",   0x1000004, 0x100000, CRC(4bc3c8bc) SHA1(6256963c515bf56f39b6e559afefd653ead56c54) )
	ROM_LOAD64_WORD( "sza.20m",   0x1000006, 0x100000, CRC(39e674c0) SHA1(8e771a2d8c2accad0463bccd21d7b23af0c895a1) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sza.01",   0x00000, 0x08000, CRC(1bc323cf) SHA1(83fbd6e9b327700dc9f1c59700b7385bc3705749) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sza.02",   0x28000, 0x20000, CRC(ba6a5013) SHA1(7814f3e56b69529b9860dd61c3b1e8d700244b03) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sza.11m",   0x000000, 0x200000, CRC(aa47a601) SHA1(a4d1ee89c84a3b9db06469bb66e85293b5aa9ac9) )
	ROM_LOAD16_WORD_SWAP( "sza.12m",   0x200000, 0x200000, CRC(2237bc53) SHA1(96d5693047e4cf1ed10a8ee1905cea267a278e92) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "sfz2al.key",   0x00, 0x14, CRC(2904963e) SHA1(f4fa44646746ab4c6f2e76eaba57a7aee32e2933) )
ROM_END

ROM_START( ssf2thc01 )  // ssf2tnl 0.9
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sfxh_hc01.03c",  0x000000, 0x80000, CRC(4beda7d5) SHA1(2045e322043387a05fb1773d45bcc2c1215a9a98) )
	ROM_LOAD16_WORD_SWAP( "sfxh_hc01.04a",  0x080000, 0x80000, CRC(d00594d8) SHA1(2ee61a9ecbeab64d2b03e38b1e753c4d800b62b1) )
	ROM_LOAD16_WORD_SWAP( "sfxh_hc01.05",   0x100000, 0x80000, CRC(c7e8ded4) SHA1(3fd9b943e7fc61925910e53eded1ac3e8083845e) )
	ROM_LOAD16_WORD_SWAP( "sfxh_hc01.06a",  0x180000, 0x80000, CRC(16b305b7) SHA1(af0a85295ecefc7d8a4c612b8f0e0c8c3ed5748d) )
	ROM_LOAD16_WORD_SWAP( "sfxh_hc01.07",   0x200000, 0x80000, CRC(43ad0333) SHA1(5ae4b127a9dd3f4c7c9396fb7f2398d6dc820524) )
	ROM_LOAD16_WORD_SWAP( "sfxh_hc01.08",   0x280000, 0x80000, CRC(1c1696e4) SHA1(a3baf599b2e8a9cb124e1f80a819688626047ed5) )
	ROM_LOAD16_WORD_SWAP( "sfxh_hc01.09",   0x300000, 0x80000, CRC(6b2068bc) SHA1(db5e69a0748df373a0ecff39cd1ac2c426f0e6d5) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROM_LOAD64_WORD( "sfxh_hc01.13m",     0x000000, 0x200000, CRC(c1df58ed) SHA1(b24d6033aefc8dee1b946bb82c5496725716c8cd) )
	ROM_LOAD64_WORD( "sfxh_hc01.15m",     0x000002, 0x200000, CRC(0f1bdf35) SHA1(f2c037e52fc704f4237bf8df3bf427b534851195) )
	ROM_LOAD64_WORD( "sfxh_hc01.17m",     0x000004, 0x200000, CRC(13acf82f) SHA1(a8bcc134644f355232493896af9c0b8287984f3c) )
	ROM_LOAD64_WORD( "sfxh_hc01.19m",     0x000006, 0x200000, CRC(7a7e1bba) SHA1(f62de983c5bd7c9ccb3367dd8e2171f7f0c87e61) )
	ROM_LOAD64_WORD( "sfxh_hc01.14m",     0x800000, 0x100000, CRC(d24d002b) SHA1(ef63edabca6cdaf53b526349e9100ae1792f32e7) )
	ROM_LOAD64_WORD( "sfxh_hc01.16m",     0x800002, 0x100000, CRC(8e81e9c4) SHA1(5f77a3d30230481f62573cb7f92dd263a866cae2) )
	ROM_LOAD64_WORD( "sfxh_hc01.18m",     0x800004, 0x100000, CRC(261285bc) SHA1(d01cac512858500a1d52575844c0a280eafe1965) )
	ROM_LOAD64_WORD( "sfxh_hc01.20m",     0x800006, 0x100000, CRC(ffa37375) SHA1(3589e3f1048d55cd8f8a9986b487bcc5d096d6d8) )
	ROM_LOAD64_WORD( "sfxh_hc01.21m",     0xc00000, 0x100000, CRC(648519f7) SHA1(5810d710dcbbd1b34168a0390176bfa170f49fcf) )
	ROM_LOAD64_WORD( "sfxh_hc01.23m",     0xc00002, 0x100000, CRC(efd2eb24) SHA1(500311f92817520983bb7f6957cdc5eb9bc3135a) )
	ROM_LOAD64_WORD( "sfxh_hc01.25m",     0xc00004, 0x100000, CRC(3294c78b) SHA1(8166a2c0434c301f7ef5eec5362f41ce0382a8c1) )
	ROM_LOAD64_WORD( "sfxh_hc01.27m",     0xc00006, 0x100000, CRC(fc283290) SHA1(ee35fb03fd1e3ca238d9155d3bc8491d38173826) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sfx.01",   0x00000, 0x08000, CRC(b47b8835) SHA1(c8b2d50fe3a329bd0592ea160d505155d873dab1) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sfx.02",   0x28000, 0x20000, CRC(0022633f) SHA1(cab3afc79da53e3887eb1ccd1f4d19790728e6cd) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sfx.11m",   0x000000, 0x200000, CRC(9bdbd476) SHA1(a8520f77f30b97aae36408e0c4ca1ebbde1808a5) )
	ROM_LOAD16_WORD_SWAP( "sfx.12m",   0x200000, 0x200000, CRC(a05e3aab) SHA1(d4eb9cae66c74e956569fea8b815156fbd420f83) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ssf2t.key",    0x00, 0x14, CRC(524d608e) SHA1(fcd2b9a1a640a0dee4a674dc9cfb3975466f7757) )
ROM_END

ROM_START( ssf2thc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sfxe_hc02.03c", 0x000000, 0x80000, CRC(2b8989d5) SHA1(9db44d3dd92ffd1586c340242eabffcabd8a10ce) )
	ROM_LOAD16_WORD_SWAP( "sfxe.04a", 0x080000, 0x80000, CRC(d0bc29c6) SHA1(d9f89bcd79cba26db2100a00dd7bd8ee6ecb75f3) )
	ROM_LOAD16_WORD_SWAP( "sfxe.05",  0x100000, 0x80000, CRC(65222964) SHA1(025bb708dc5b6365cc7fe60fc3f242511ad8f384) )
	ROM_LOAD16_WORD_SWAP( "sfxe.06a", 0x180000, 0x80000, CRC(8fe9f531) SHA1(b5d9ed498f730fdb968992bdec33605db1a007f4) )
	ROM_LOAD16_WORD_SWAP( "sfxe.07",  0x200000, 0x80000, CRC(8a7d0cb6) SHA1(27ea0cea73a93c27257bf2a170d1deaf938cc311) )
	ROM_LOAD16_WORD_SWAP( "sfxe.08",  0x280000, 0x80000, CRC(74c24062) SHA1(f3eca09e0544c6aa46b0c4bead2246ab1e9a97d9) )
	ROM_LOAD16_WORD_SWAP( "sfx.09",   0x300000, 0x80000, CRC(642fae3f) SHA1(746df99b826b9837bba267104132161153c1daff) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROM_LOAD64_WORD( "sfx.13m",   0x000000, 0x200000, CRC(cf94d275) SHA1(bf2a6d98a656d1cb5734da7836686242d3211137) )
	ROM_LOAD64_WORD( "sfx.15m",   0x000002, 0x200000, CRC(5eb703af) SHA1(4b302dbb66e8a5c2ad92798699391e981bada427) )
	ROM_LOAD64_WORD( "sfx.17m",   0x000004, 0x200000, CRC(ffa60e0f) SHA1(b21b1c749a8241440879bf8e7cb33968ccef97e5) )
	ROM_LOAD64_WORD( "sfx.19m",   0x000006, 0x200000, CRC(34e825c5) SHA1(4d320fc96d1ef0b9928a8ce801734245a4c097a5) )
	ROM_LOAD64_WORD( "sfx.14m",   0x800000, 0x100000, CRC(b7cc32e7) SHA1(0f4d26af338dab5dce5b7b34d32ad0c573434ace) )
	ROM_LOAD64_WORD( "sfx.16m",   0x800002, 0x100000, CRC(8376ad18) SHA1(f4456833fb396e6501f4174c0fe5fd63ea40a188) )
	ROM_LOAD64_WORD( "sfx.18m",   0x800004, 0x100000, CRC(f5b1b336) SHA1(4b060501e56b9d61294748da5387cdae5280ec4d) )
	ROM_LOAD64_WORD( "sfx.20m",   0x800006, 0x100000, CRC(459d5c6b) SHA1(32b11ba7a12004aff810d719bff7508204c7b7c0) )
	ROM_LOAD64_WORD( "sfx.21m",   0xc00000, 0x100000, CRC(e32854af) SHA1(1a5e11e9caa2b96108d89ae660ef1f6bcb469a74) )
	ROM_LOAD64_WORD( "sfx.23m",   0xc00002, 0x100000, CRC(760f2927) SHA1(491e28e14ee06821fc9e709efa7b91313bc0c2db) )
	ROM_LOAD64_WORD( "sfx.25m",   0xc00004, 0x100000, CRC(1ee90208) SHA1(83df1d9953560edddc2951ea426d29fb014e6a8a) )
	ROM_LOAD64_WORD( "sfx.27m",   0xc00006, 0x100000, CRC(f814400f) SHA1(ad6921af36d0bd5dfb89b1fb53c3ca3fd92d7204) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 ) // 64k for the audio CPU (+banks)
	ROM_LOAD( "sfx.01",   0x00000, 0x08000, CRC(b47b8835) SHA1(c8b2d50fe3a329bd0592ea160d505155d873dab1) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sfx.02",   0x28000, 0x20000, CRC(0022633f) SHA1(cab3afc79da53e3887eb1ccd1f4d19790728e6cd) )

	ROM_REGION( 0x400000, "qsound", 0 ) // QSound samples
	ROM_LOAD16_WORD_SWAP( "sfx.11m",   0x000000, 0x200000, CRC(9bdbd476) SHA1(a8520f77f30b97aae36408e0c4ca1ebbde1808a5) )
	ROM_LOAD16_WORD_SWAP( "sfx.12m",   0x200000, 0x200000, CRC(a05e3aab) SHA1(d4eb9cae66c74e956569fea8b815156fbd420f83) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ssf2t.key",    0x000000, 0x000014, CRC(524d608e) SHA1(fcd2b9a1a640a0dee4a674dc9cfb3975466f7757) )
ROM_END

ROM_START( ssf2thc03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sfxe_hc03.03c", 0x000000, 0x80000, CRC(c8c491d1) SHA1(5e12ccd36c8cd086d3d628e7f121aefcbc17340e) )
	ROM_LOAD16_WORD_SWAP( "sfxe_hc03.04a", 0x080000, 0x80000, CRC(b018ceea) SHA1(75fa14f93c82ade94713556cffcfd17dfcef3e35) )
	ROM_LOAD16_WORD_SWAP( "sfxe.05",  0x100000, 0x80000, CRC(65222964) SHA1(025bb708dc5b6365cc7fe60fc3f242511ad8f384) )
	ROM_LOAD16_WORD_SWAP( "sfxe.06a", 0x180000, 0x80000, CRC(8fe9f531) SHA1(b5d9ed498f730fdb968992bdec33605db1a007f4) )
	ROM_LOAD16_WORD_SWAP( "sfxe.07",  0x200000, 0x80000, CRC(8a7d0cb6) SHA1(27ea0cea73a93c27257bf2a170d1deaf938cc311) )
	ROM_LOAD16_WORD_SWAP( "sfxe.08",  0x280000, 0x80000, CRC(74c24062) SHA1(f3eca09e0544c6aa46b0c4bead2246ab1e9a97d9) )
	ROM_LOAD16_WORD_SWAP( "sfx.09",   0x300000, 0x80000, CRC(642fae3f) SHA1(746df99b826b9837bba267104132161153c1daff) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROM_LOAD64_WORD( "sfx.13m",   0x000000, 0x200000, CRC(cf94d275) SHA1(bf2a6d98a656d1cb5734da7836686242d3211137) )
	ROM_LOAD64_WORD( "sfx.15m",   0x000002, 0x200000, CRC(5eb703af) SHA1(4b302dbb66e8a5c2ad92798699391e981bada427) )
	ROM_LOAD64_WORD( "sfx.17m",   0x000004, 0x200000, CRC(ffa60e0f) SHA1(b21b1c749a8241440879bf8e7cb33968ccef97e5) )
	ROM_LOAD64_WORD( "sfx.19m",   0x000006, 0x200000, CRC(34e825c5) SHA1(4d320fc96d1ef0b9928a8ce801734245a4c097a5) )
	ROM_LOAD64_WORD( "sfx.14m",   0x800000, 0x100000, CRC(b7cc32e7) SHA1(0f4d26af338dab5dce5b7b34d32ad0c573434ace) )
	ROM_LOAD64_WORD( "sfx.16m",   0x800002, 0x100000, CRC(8376ad18) SHA1(f4456833fb396e6501f4174c0fe5fd63ea40a188) )
	ROM_LOAD64_WORD( "sfx.18m",   0x800004, 0x100000, CRC(f5b1b336) SHA1(4b060501e56b9d61294748da5387cdae5280ec4d) )
	ROM_LOAD64_WORD( "sfx.20m",   0x800006, 0x100000, CRC(459d5c6b) SHA1(32b11ba7a12004aff810d719bff7508204c7b7c0) )
	ROM_LOAD64_WORD( "sfx.21m",   0xc00000, 0x100000, CRC(e32854af) SHA1(1a5e11e9caa2b96108d89ae660ef1f6bcb469a74) )
	ROM_LOAD64_WORD( "sfx.23m",   0xc00002, 0x100000, CRC(760f2927) SHA1(491e28e14ee06821fc9e709efa7b91313bc0c2db) )
	ROM_LOAD64_WORD( "sfx.25m",   0xc00004, 0x100000, CRC(1ee90208) SHA1(83df1d9953560edddc2951ea426d29fb014e6a8a) )
	ROM_LOAD64_WORD( "sfx.27m",   0xc00006, 0x100000, CRC(f814400f) SHA1(ad6921af36d0bd5dfb89b1fb53c3ca3fd92d7204) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 ) // 64k for the audio CPU (+banks)
	ROM_LOAD( "sfx.01",   0x00000, 0x08000, CRC(b47b8835) SHA1(c8b2d50fe3a329bd0592ea160d505155d873dab1) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sfx.02",   0x28000, 0x20000, CRC(0022633f) SHA1(cab3afc79da53e3887eb1ccd1f4d19790728e6cd) )

	ROM_REGION( 0x400000, "qsound", 0 ) // QSound samples
	ROM_LOAD16_WORD_SWAP( "sfx.11m",   0x000000, 0x200000, CRC(9bdbd476) SHA1(a8520f77f30b97aae36408e0c4ca1ebbde1808a5) )
	ROM_LOAD16_WORD_SWAP( "sfx.12m",   0x200000, 0x200000, CRC(a05e3aab) SHA1(d4eb9cae66c74e956569fea8b815156fbd420f83) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ssf2t.key",    0x000000, 0x000014, CRC(524d608e) SHA1(fcd2b9a1a640a0dee4a674dc9cfb3975466f7757) )
ROM_END

ROM_START( ssf2xhc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sfxj_hc01.03", 0x000000, 0x80000, CRC(62b59bf0) SHA1(b8ef9a39dd594f243dab3b440c871730356403c8) )
	ROM_LOAD16_WORD_SWAP( "sfxj.04a", 0x080000, 0x80000, CRC(af7767b4) SHA1(61e7364408bf07c01634913c112b6245acce48ab) )
	ROM_LOAD16_WORD_SWAP( "sfxj.05",  0x100000, 0x80000, CRC(f4ff18f5) SHA1(aa713c9e1a2eba35bf1c9b40bb262ff7e46b9ce4) )
	ROM_LOAD16_WORD_SWAP( "sfxj.06a", 0x180000, 0x80000, CRC(260d0370) SHA1(5339cf87000caef74d491815391be59cfd701c8b) )
	ROM_LOAD16_WORD_SWAP( "sfxj.07",  0x200000, 0x80000, CRC(1324d02a) SHA1(c23a6ea09819bd33b6e2f58aa28c317ce53a46a0) )
	ROM_LOAD16_WORD_SWAP( "sfxj.08",  0x280000, 0x80000, CRC(2de76f10) SHA1(8cbe96dfeaa41306caa2819b82272ce3b0b9f926) )
	ROM_LOAD16_WORD_SWAP( "sfx.09",   0x300000, 0x80000, CRC(642fae3f) SHA1(746df99b826b9837bba267104132161153c1daff) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "sfx.13m",   0x000000, 0x200000, CRC(cf94d275) SHA1(bf2a6d98a656d1cb5734da7836686242d3211137) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.15m",   0x000002, 0x200000, CRC(5eb703af) SHA1(4b302dbb66e8a5c2ad92798699391e981bada427) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.17m",   0x000004, 0x200000, CRC(ffa60e0f) SHA1(b21b1c749a8241440879bf8e7cb33968ccef97e5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.19m",   0x000006, 0x200000, CRC(34e825c5) SHA1(4d320fc96d1ef0b9928a8ce801734245a4c097a5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.14m",   0x800000, 0x100000, CRC(b7cc32e7) SHA1(0f4d26af338dab5dce5b7b34d32ad0c573434ace) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.16m",   0x800002, 0x100000, CRC(8376ad18) SHA1(f4456833fb396e6501f4174c0fe5fd63ea40a188) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.18m",   0x800004, 0x100000, CRC(f5b1b336) SHA1(4b060501e56b9d61294748da5387cdae5280ec4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.20m",   0x800006, 0x100000, CRC(459d5c6b) SHA1(32b11ba7a12004aff810d719bff7508204c7b7c0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.21m",   0xc00000, 0x100000, CRC(e32854af) SHA1(1a5e11e9caa2b96108d89ae660ef1f6bcb469a74) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.23m",   0xc00002, 0x100000, CRC(760f2927) SHA1(491e28e14ee06821fc9e709efa7b91313bc0c2db) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.25m",   0xc00004, 0x100000, CRC(1ee90208) SHA1(83df1d9953560edddc2951ea426d29fb014e6a8a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.27m",   0xc00006, 0x100000, CRC(f814400f) SHA1(ad6921af36d0bd5dfb89b1fb53c3ca3fd92d7204) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sfx.01",   0x00000, 0x08000, CRC(b47b8835) SHA1(c8b2d50fe3a329bd0592ea160d505155d873dab1) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sfx.02",   0x28000, 0x20000, CRC(0022633f) SHA1(cab3afc79da53e3887eb1ccd1f4d19790728e6cd) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sfx.11m",   0x000000, 0x200000, CRC(9bdbd476) SHA1(a8520f77f30b97aae36408e0c4ca1ebbde1808a5) )
	ROM_LOAD16_WORD_SWAP( "sfx.12m",   0x200000, 0x200000, CRC(a05e3aab) SHA1(d4eb9cae66c74e956569fea8b815156fbd420f83) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ssf2xj.key",   0x00, 0x14, CRC(160d1424) SHA1(187baff83b54acfdcedd9b9222a4cc768040c622) )
ROM_END

ROM_START( ssf2xhc02 ) //ssf2xjr1trn
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sfxj_hc02.03",  0x000000, 0x80000, CRC(37b25225) SHA1(5f89c69ea6073a5414abe4b849e356c45e1145d1) )
	ROM_LOAD16_WORD_SWAP( "sfxj_hc02.04a", 0x080000, 0x80000, CRC(bf2ae059) SHA1(eb3f2ac5133194edb247dac2249852fdbc0e4d12) )
	ROM_LOAD16_WORD_SWAP( "sfxj.05",  0x100000, 0x80000, CRC(f4ff18f5) SHA1(aa713c9e1a2eba35bf1c9b40bb262ff7e46b9ce4) )
	ROM_LOAD16_WORD_SWAP( "sfxj.06a", 0x180000, 0x80000, CRC(260d0370) SHA1(5339cf87000caef74d491815391be59cfd701c8b) )
	ROM_LOAD16_WORD_SWAP( "sfxj.07",  0x200000, 0x80000, CRC(1324d02a) SHA1(c23a6ea09819bd33b6e2f58aa28c317ce53a46a0) )
	ROM_LOAD16_WORD_SWAP( "sfxj.08",  0x280000, 0x80000, CRC(2de76f10) SHA1(8cbe96dfeaa41306caa2819b82272ce3b0b9f926) )
	ROM_LOAD16_WORD_SWAP( "sfx.09",   0x300000, 0x80000, CRC(642fae3f) SHA1(746df99b826b9837bba267104132161153c1daff) )

	ROM_REGION( 0x1000000, "gfx", 0 )
	ROMX_LOAD( "sfx.13m",   0x000000, 0x200000, CRC(cf94d275) SHA1(bf2a6d98a656d1cb5734da7836686242d3211137) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.15m",   0x000002, 0x200000, CRC(5eb703af) SHA1(4b302dbb66e8a5c2ad92798699391e981bada427) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.17m",   0x000004, 0x200000, CRC(ffa60e0f) SHA1(b21b1c749a8241440879bf8e7cb33968ccef97e5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.19m",   0x000006, 0x200000, CRC(34e825c5) SHA1(4d320fc96d1ef0b9928a8ce801734245a4c097a5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.14m",   0x800000, 0x100000, CRC(b7cc32e7) SHA1(0f4d26af338dab5dce5b7b34d32ad0c573434ace) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.16m",   0x800002, 0x100000, CRC(8376ad18) SHA1(f4456833fb396e6501f4174c0fe5fd63ea40a188) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.18m",   0x800004, 0x100000, CRC(f5b1b336) SHA1(4b060501e56b9d61294748da5387cdae5280ec4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.20m",   0x800006, 0x100000, CRC(459d5c6b) SHA1(32b11ba7a12004aff810d719bff7508204c7b7c0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.21m",   0xc00000, 0x100000, CRC(e32854af) SHA1(1a5e11e9caa2b96108d89ae660ef1f6bcb469a74) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.23m",   0xc00002, 0x100000, CRC(760f2927) SHA1(491e28e14ee06821fc9e709efa7b91313bc0c2db) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.25m",   0xc00004, 0x100000, CRC(1ee90208) SHA1(83df1d9953560edddc2951ea426d29fb014e6a8a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sfx.27m",   0xc00006, 0x100000, CRC(f814400f) SHA1(ad6921af36d0bd5dfb89b1fb53c3ca3fd92d7204) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "sfx.01",   0x00000, 0x08000, CRC(b47b8835) SHA1(c8b2d50fe3a329bd0592ea160d505155d873dab1) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "sfx.02",   0x28000, 0x20000, CRC(0022633f) SHA1(cab3afc79da53e3887eb1ccd1f4d19790728e6cd) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "sfx.11m",   0x000000, 0x200000, CRC(9bdbd476) SHA1(a8520f77f30b97aae36408e0c4ca1ebbde1808a5) )
	ROM_LOAD16_WORD_SWAP( "sfx.12m",   0x200000, 0x200000, CRC(a05e3aab) SHA1(d4eb9cae66c74e956569fea8b815156fbd420f83) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ssf2xj.key",   0x00, 0x14, CRC(160d1424) SHA1(187baff83b54acfdcedd9b9222a4cc768040c622) )
ROM_END

ROM_START( ssf2hc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ssfj_hc01.03b", 0x000000, 0x80000, CRC(ea1d3237) SHA1(f7a8dded94299b34657d066a89f55bfd91c7070c) )
	ROM_LOAD16_WORD_SWAP( "ssfj_hc01.04a", 0x080000, 0x80000, CRC(07a12776) SHA1(db22da16b038767a31a7dc7c04fd3071ae228fd3) )
	ROM_LOAD16_WORD_SWAP( "ssfj.05",  0x100000, 0x80000, CRC(0918d19a) SHA1(c23be61dd193058eb1391d39fbc22fbcf0640ee0) )
	ROM_LOAD16_WORD_SWAP( "ssfj.06b", 0x180000, 0x80000, CRC(014e0c6d) SHA1(4a5689a05900564c2544c95741cd450ce55da0a7) )
	ROM_LOAD16_WORD_SWAP( "ssfj.07",  0x200000, 0x80000, CRC(eb6a9b1b) SHA1(daedb669b0025f6efb0f3302a40d88dcde2fc76f) )

	ROM_REGION( 0xc00000, "gfx", 0 )
	ROMX_LOAD( "ssf.13m",   0x000000, 0x200000, CRC(cf94d275) SHA1(bf2a6d98a656d1cb5734da7836686242d3211137) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ssf.15m",   0x000002, 0x200000, CRC(5eb703af) SHA1(4b302dbb66e8a5c2ad92798699391e981bada427) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ssf.17m",   0x000004, 0x200000, CRC(ffa60e0f) SHA1(b21b1c749a8241440879bf8e7cb33968ccef97e5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ssf.19m",   0x000006, 0x200000, CRC(34e825c5) SHA1(4d320fc96d1ef0b9928a8ce801734245a4c097a5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ssf.14m",   0x800000, 0x100000, CRC(b7cc32e7) SHA1(0f4d26af338dab5dce5b7b34d32ad0c573434ace) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ssf.16m",   0x800002, 0x100000, CRC(8376ad18) SHA1(f4456833fb396e6501f4174c0fe5fd63ea40a188) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ssf.18m",   0x800004, 0x100000, CRC(f5b1b336) SHA1(4b060501e56b9d61294748da5387cdae5280ec4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ssf.20m",   0x800006, 0x100000, CRC(459d5c6b) SHA1(32b11ba7a12004aff810d719bff7508204c7b7c0) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "ssf.01",   0x00000, 0x08000, CRC(eb247e8c) SHA1(24296c18d9b1136d69712bf1c9d9d15463041e83) )
	ROM_CONTINUE(         0x10000, 0x18000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD( "ssf.q01",  0x000000, 0x080000, CRC(a6f9da5c) SHA1(6d19f83a01bd25b838d5c2871f7964529d926c98) )
	ROM_LOAD( "ssf.q02",  0x080000, 0x080000, CRC(8c66ae26) SHA1(32a82aee6ed4480e5a990f9af161734c7c0a1403) )
	ROM_LOAD( "ssf.q03",  0x100000, 0x080000, CRC(695cc2ca) SHA1(c2675f0233608b76de528d2a6ef19846d1348060) )
	ROM_LOAD( "ssf.q04",  0x180000, 0x080000, CRC(9d9ebe32) SHA1(9b26329370041374f1a90b479a172d2bc2801c4d) )
	ROM_LOAD( "ssf.q05",  0x200000, 0x080000, CRC(4770e7b7) SHA1(0e764f0befb9227b0b36508d8ca8ec9be31bcb05) )
	ROM_LOAD( "ssf.q06",  0x280000, 0x080000, CRC(4e79c951) SHA1(1144781d7dc57ef8a6458d982f5c91548ff59e27) )
	ROM_LOAD( "ssf.q07",  0x300000, 0x080000, CRC(cdd14313) SHA1(ebe767a9d4b51dba4282fa0a36a546a88620dd59) )
	ROM_LOAD( "ssf.q08",  0x380000, 0x080000, CRC(6f5a088c) SHA1(6c0b4690479647a99d76335f174be8455b4ff118) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "ssf2j.key",    0x000000, 0x000014, CRC(bca45cc2) SHA1(5e9ccfde4b476efdce4e4fcbaf8facefe41a4c89) )
ROM_END

ROM_START( spf2thc01 )
	ROM_REGION(CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pzf_hc01.03a", 0x000000, 0x80000, CRC(ca1f3e42) SHA1(784214517f3ac3f5f727a18f50992d4fa3417726) )
	ROM_LOAD16_WORD_SWAP( "pzf.04",    0x080000, 0x80000, CRC(b80649e2) SHA1(5bfccd656aea7ff82e9a20bb5856f4ab99b5a007) )

	ROM_REGION( 0xC00000, "gfx", 0 )
	ROM_FILL(              0x000000, 0x800000, 0 )
	ROMX_LOAD( "pzf.14m",  0x800000, 0x100000, CRC(2d4881cb) SHA1(fd3baa183c25bed153b19c251980e2fb761600e2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pzf.16m",  0x800002, 0x100000, CRC(4b0fd1be) SHA1(377aafdcdb7a866b1c8487670e3598d8197976e4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pzf.18m",  0x800004, 0x100000, CRC(e43aac33) SHA1(d041e0688c3807d3363861a7f216de43b34d846c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pzf.20m",  0x800006, 0x100000, CRC(7f536ff1) SHA1(905b9d62ef7bef47297c7f4a4dd697aed6df38a5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION(QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pzf.01",   0x00000, 0x08000, CRC(600fb2a3) SHA1(1fab1c2a23bf6ad8309d29ddbbc29435a8aeea13) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "pzf.02",   0x28000, 0x20000, CRC(496076e0) SHA1(1ee4e135140afd0e8e03231e570cd77d140f6367) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pzf.11m",   0x000000, 0x200000, CRC(78442743) SHA1(b61190bb586871de6d54af580e3e1d9cc0de0acb) )
	ROM_LOAD16_WORD_SWAP( "pzf.12m",   0x200000, 0x200000, CRC(399d2c7b) SHA1(e849dea97b8d16540415c0d9bbc4f9f4eb755ec4) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "spf2tb.key",    0x00, 0x14, CRC(5d7b15e8) SHA1(c14c6b148761856bf83b31b52df83be461ac8d62) )
ROM_END

ROM_START( spf2thc02 ) //spf2xpri
	ROM_REGION(CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pzf_hc02.03a", 0x000000, 0x80000, CRC(f205a7da) SHA1(3fa4b7ecc54d239061148781ecdc469f975122af) )
	ROM_LOAD16_WORD_SWAP( "pzf_hc02.04",  0x080000, 0x80000, CRC(4177aadd) SHA1(c218d2446f3fc348a952a8b7a75dace864fed0f9) )

	ROM_REGION( 0xC00000, "gfx", 0 )
	ROM_FILL(              0x000000, 0x800000, 0 )
	ROMX_LOAD( "pzf_hc02.14m",  0x800000, 0x100000, CRC(930b0ec7) SHA1(60b786dca5a943010b0273a5f6d084453a3bd121) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pzf_hc02.16m",  0x800002, 0x100000, CRC(769377ad) SHA1(eb86026999ab01e74a975d03305d637899615bf4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pzf_hc02.18m",  0x800004, 0x100000, CRC(5a79233f) SHA1(31ca4744be2d7860351dc56fbb3e03e0ddf35b09) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pzf_hc02.20m",  0x800006, 0x100000, CRC(42cfc9e2) SHA1(04cadb017163732f5ba022733d0cb442ce3cada3) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION(QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pzf.01",   0x00000, 0x08000, CRC(600fb2a3) SHA1(1fab1c2a23bf6ad8309d29ddbbc29435a8aeea13) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "pzf.02",   0x28000, 0x20000, CRC(496076e0) SHA1(1ee4e135140afd0e8e03231e570cd77d140f6367) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pzf.11m",   0x000000, 0x200000, CRC(78442743) SHA1(b61190bb586871de6d54af580e3e1d9cc0de0acb) )
	ROM_LOAD16_WORD_SWAP( "pzf.12m",   0x200000, 0x200000, CRC(399d2c7b) SHA1(e849dea97b8d16540415c0d9bbc4f9f4eb755ec4) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "spf2t.key",    0x000000, 0x000014, CRC(4c4dc7e3) SHA1(db4f257f6006b2f3cfa7cc70917228d639324513) )
ROM_END

ROM_START( spf2thc03 ) //Spf2tcb
	ROM_REGION(CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pzfe.03", 0x000000, 0x80000, CRC(2af51954) SHA1(51f8797918391e772cf3cc27074ed6ca419806bd) )
	ROM_LOAD16_WORD_SWAP( "pzf_hc03.04",  0x080000, 0x80000, CRC(14f163a7) SHA1(cff5c58c38f7e70e64cb98e345d44618d93b2bae) )

	ROM_REGION( 0xC00000, "gfx", 0 )
	ROM_FILL(              0x000000, 0x800000, 0 )
	ROMX_LOAD( "pzf.14m",  0x800000, 0x100000, CRC(2d4881cb) SHA1(fd3baa183c25bed153b19c251980e2fb761600e2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pzf.16m",  0x800002, 0x100000, CRC(4b0fd1be) SHA1(377aafdcdb7a866b1c8487670e3598d8197976e4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pzf.18m",  0x800004, 0x100000, CRC(e43aac33) SHA1(d041e0688c3807d3363861a7f216de43b34d846c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "pzf.20m",  0x800006, 0x100000, CRC(7f536ff1) SHA1(905b9d62ef7bef47297c7f4a4dd697aed6df38a5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION(QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pzf.01",   0x00000, 0x08000, CRC(600fb2a3) SHA1(1fab1c2a23bf6ad8309d29ddbbc29435a8aeea13) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "pzf.02",   0x28000, 0x20000, CRC(496076e0) SHA1(1ee4e135140afd0e8e03231e570cd77d140f6367) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pzf.11m",   0x000000, 0x200000, CRC(78442743) SHA1(b61190bb586871de6d54af580e3e1d9cc0de0acb) )
	ROM_LOAD16_WORD_SWAP( "pzf.12m",   0x200000, 0x200000, CRC(399d2c7b) SHA1(e849dea97b8d16540415c0d9bbc4f9f4eb755ec4) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "spf2t.key",    0x000000, 0x000014, CRC(4c4dc7e3) SHA1(db4f257f6006b2f3cfa7cc70917228d639324513) )
ROM_END

ROM_START( spf2xhc01 )
	ROM_REGION(CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pzfj_hc01.03a", 0x000000, 0x80000, CRC(f205a7da) SHA1(3fa4b7ecc54d239061148781ecdc469f975122af) )
	ROM_LOAD16_WORD_SWAP( "pzfj_hc01.04",  0x080000, 0x80000, CRC(4177aadd) SHA1(c218d2446f3fc348a952a8b7a75dace864fed0f9) )

	ROM_REGION( 0xC00000, "gfx", 0 )
	ROM_FILL(             0x000000, 0x800000, 0x00 )
	ROM_LOAD64_WORD( "pzf_hc01.14m", 0x800000, 0x100000, CRC(930b0ec7) SHA1(60b786dca5a943010b0273a5f6d084453a3bd121) )
	ROM_LOAD64_WORD( "pzf_hc01.16m", 0x800002, 0x100000, CRC(769377ad) SHA1(eb86026999ab01e74a975d03305d637899615bf4) )
	ROM_LOAD64_WORD( "pzf_hc01.18m", 0x800004, 0x100000, CRC(5a79233f) SHA1(31ca4744be2d7860351dc56fbb3e03e0ddf35b09) )
	ROM_LOAD64_WORD( "pzf_hc01.20m", 0x800006, 0x100000, CRC(42cfc9e2) SHA1(04cadb017163732f5ba022733d0cb442ce3cada3) )

	ROM_REGION(QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pzf.01",   0x00000, 0x08000, CRC(600fb2a3) SHA1(1fab1c2a23bf6ad8309d29ddbbc29435a8aeea13) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "pzf.02",   0x28000, 0x20000, CRC(496076e0) SHA1(1ee4e135140afd0e8e03231e570cd77d140f6367) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pzf.11m",   0x000000, 0x200000, CRC(78442743) SHA1(b61190bb586871de6d54af580e3e1d9cc0de0acb) )
	ROM_LOAD16_WORD_SWAP( "pzf.12m",   0x200000, 0x200000, CRC(399d2c7b) SHA1(e849dea97b8d16540415c0d9bbc4f9f4eb755ec4) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "spf2t.key",    0x000000, 0x000014, CRC(4c4dc7e3) SHA1(db4f257f6006b2f3cfa7cc70917228d639324513) )
ROM_END

ROM_START( spf2xhc02 )
	ROM_REGION(CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pzf_hc02.03a", 0x000000, 0x80000, CRC(4c29e2a6) SHA1(a5cd108fd01eb9e9f63e170a088c7235acfcf0da) )
	ROM_LOAD16_WORD_SWAP( "pzf_hc02.04",   0x080000, 0x80000, CRC(faf9c818) SHA1(d2bc8d30d3a16eb30620f2c5835fa840f72af744) )

	ROM_REGION( 0xC00000, "gfx", 0 )
	ROM_FILL(             0x000000, 0x800000, 0x00 )
	ROM_LOAD64_WORD( "pzf_hc02.14m", 0x800000, 0x100000, CRC(bb5da961) SHA1(b9dbc81504ae187d3be9520b81355abc35697b24) )
	ROM_LOAD64_WORD( "pzf_hc02.16m", 0x800002, 0x100000, CRC(2eee8408) SHA1(16f9fa8db183b381969901cba91e3121479519de) )
	ROM_LOAD64_WORD( "pzf_hc02.18m", 0x800004, 0x100000, CRC(9e792b30) SHA1(433ded7ff199a44514866db6d4087bd2ed3192a8) )
	ROM_LOAD64_WORD( "pzf_hc02.20m", 0x800006, 0x100000, CRC(26605f63) SHA1(e1a0cf979485ce6f5b78b5f6d7bd32bbae5f9f39) )

	ROM_REGION(QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "pzf.01",   0x00000, 0x08000, CRC(600fb2a3) SHA1(1fab1c2a23bf6ad8309d29ddbbc29435a8aeea13) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "pzf.02",   0x28000, 0x20000, CRC(496076e0) SHA1(1ee4e135140afd0e8e03231e570cd77d140f6367) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "pzf.11m",   0x000000, 0x200000, CRC(78442743) SHA1(b61190bb586871de6d54af580e3e1d9cc0de0acb) )
	ROM_LOAD16_WORD_SWAP( "pzf.12m",   0x200000, 0x200000, CRC(399d2c7b) SHA1(e849dea97b8d16540415c0d9bbc4f9f4eb755ec4) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "spf2xj.key",   0x000000, 0x000014, CRC(dc39fd34) SHA1(d18f015070d08e772677ef79b542f12664cfba53) )
ROM_END

ROM_START( xmcotahc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "xmnj_hc01.03",  0x000000, 0x80000, CRC(bd2f0b84) SHA1(2b5c6deb2bb7e10a142a490781231d2ccfceee1c) )
	ROM_LOAD16_WORD_SWAP( "xmnj_hc01.04b", 0x080000, 0x80000, CRC(5de40342) SHA1(c5ba56560155197232869f4f8dbfbfde46daf081) )
	ROM_LOAD16_WORD_SWAP( "xmn.05",   0x100000, 0x80000, CRC(c3ed62a2) SHA1(4e3317d7ca981e33318822103a16e59f4ce20deb) )
	ROM_LOAD16_WORD_SWAP( "xmn.06",   0x180000, 0x80000, CRC(f03c52e1) SHA1(904b2312ee594f5ece0484cad0eed25cc758185e) )
	ROM_LOAD16_WORD_SWAP( "xmn.07",   0x200000, 0x80000, CRC(325626b1) SHA1(3f3a0aabbe5ffad8136ac91e0de785103b16059b) )
	ROM_LOAD16_WORD_SWAP( "xmn.08",   0x280000, 0x80000, CRC(7194ea10) SHA1(40a5892d816f24cbfd4c310792eeabf689c6fa7e) )
	ROM_LOAD16_WORD_SWAP( "xmn.09",   0x300000, 0x80000, CRC(ae946df3) SHA1(733671f76d766bda7110df9d338791cc5202b050) )
	ROM_LOAD16_WORD_SWAP( "xmn.10",   0x380000, 0x80000, CRC(32a6be1d) SHA1(8f5fcb33b528abed670b4fc3fa62431a6e033c56) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "xmn.13m",   0x0000000, 0x400000, CRC(bf4df073) SHA1(4d2740c3a827f0ec2cf75ad99c65e393c6a11c23) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.15m",   0x0000002, 0x400000, CRC(4d7e4cef) SHA1(50b8797b8099a8d76ad063ba1201a13dbb88ae3a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.17m",   0x0000004, 0x400000, CRC(513eea17) SHA1(a497477ad9ac13180911d8745ef6ee1955c0b877) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.19m",   0x0000006, 0x400000, CRC(d23897fc) SHA1(1e31627999736652252164d32662779a1ac6ca29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.14m",   0x1000000, 0x400000, CRC(778237b7) SHA1(89a759ec383518ec52f5059d10ec342f2247aa20) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.16m",   0x1000002, 0x400000, CRC(67b36948) SHA1(692fb6e4096b880aa22996d554b160f664bbd907) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.18m",   0x1000004, 0x400000, CRC(015a7c4c) SHA1(cccc95dafd076a1a9fa004710006149c42d058ba) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.20m",   0x1000006, 0x400000, CRC(9dde2758) SHA1(17ba259cad03c7b5d56c0a5eda9ab53521665729) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "xmn.01a",  0x00000, 0x08000, CRC(40f479ea) SHA1(f29e15f537675305264ae2138a0a537fb9e2008b) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "xmn.02a",  0x28000, 0x20000, CRC(39d9b5ad) SHA1(af502debfd36100d4fc971ed25fdf9d7121d6f18) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "xmn.11m",   0x000000, 0x200000, CRC(c848a6bc) SHA1(ac8ac564d3c43225822f8bc330eba9f35b24b0a4) )
	ROM_LOAD16_WORD_SWAP( "xmn.12m",   0x200000, 0x200000, CRC(729c188f) SHA1(3279774ad8aebbcf0fc779cdfcbe21044dd192ad) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "xmcotaj.key",  0x00, 0x14, CRC(d278b4ac) SHA1(06d94e8a203172792f405c73f9cbb37f4738429f) )
ROM_END

ROM_START( xmcotahc02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "xmnj_hc02.03", 0x000000, 0x80000, CRC(e52f9f70) SHA1(a0e33506e5b95f8a4b37d6be2d4d47a0ef8c5206) )
	ROM_LOAD16_WORD_SWAP( "xmnj_hc01.04b", 0x080000, 0x80000, CRC(5de40342) SHA1(c5ba56560155197232869f4f8dbfbfde46daf081) )
	ROM_LOAD16_WORD_SWAP( "xmn.05",   0x100000, 0x80000, CRC(c3ed62a2) SHA1(4e3317d7ca981e33318822103a16e59f4ce20deb) )
	ROM_LOAD16_WORD_SWAP( "xmn.06",   0x180000, 0x80000, CRC(f03c52e1) SHA1(904b2312ee594f5ece0484cad0eed25cc758185e) )
	ROM_LOAD16_WORD_SWAP( "xmn.07",   0x200000, 0x80000, CRC(325626b1) SHA1(3f3a0aabbe5ffad8136ac91e0de785103b16059b) )
	ROM_LOAD16_WORD_SWAP( "xmn.08",   0x280000, 0x80000, CRC(7194ea10) SHA1(40a5892d816f24cbfd4c310792eeabf689c6fa7e) )
	ROM_LOAD16_WORD_SWAP( "xmn.09",   0x300000, 0x80000, CRC(ae946df3) SHA1(733671f76d766bda7110df9d338791cc5202b050) )
	ROM_LOAD16_WORD_SWAP( "xmn.10",   0x380000, 0x80000, CRC(32a6be1d) SHA1(8f5fcb33b528abed670b4fc3fa62431a6e033c56) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "xmn.13m",   0x0000000, 0x400000, CRC(bf4df073) SHA1(4d2740c3a827f0ec2cf75ad99c65e393c6a11c23) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.15m",   0x0000002, 0x400000, CRC(4d7e4cef) SHA1(50b8797b8099a8d76ad063ba1201a13dbb88ae3a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.17m",   0x0000004, 0x400000, CRC(513eea17) SHA1(a497477ad9ac13180911d8745ef6ee1955c0b877) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.19m",   0x0000006, 0x400000, CRC(d23897fc) SHA1(1e31627999736652252164d32662779a1ac6ca29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.14m",   0x1000000, 0x400000, CRC(778237b7) SHA1(89a759ec383518ec52f5059d10ec342f2247aa20) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.16m",   0x1000002, 0x400000, CRC(67b36948) SHA1(692fb6e4096b880aa22996d554b160f664bbd907) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.18m",   0x1000004, 0x400000, CRC(015a7c4c) SHA1(cccc95dafd076a1a9fa004710006149c42d058ba) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xmn.20m",   0x1000006, 0x400000, CRC(9dde2758) SHA1(17ba259cad03c7b5d56c0a5eda9ab53521665729) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "xmn.01a",  0x00000, 0x08000, CRC(40f479ea) SHA1(f29e15f537675305264ae2138a0a537fb9e2008b) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "xmn.02a",  0x28000, 0x20000, CRC(39d9b5ad) SHA1(af502debfd36100d4fc971ed25fdf9d7121d6f18) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "xmn.11m",   0x000000, 0x200000, CRC(c848a6bc) SHA1(ac8ac564d3c43225822f8bc330eba9f35b24b0a4) )
	ROM_LOAD16_WORD_SWAP( "xmn.12m",   0x200000, 0x200000, CRC(729c188f) SHA1(3279774ad8aebbcf0fc779cdfcbe21044dd192ad) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "xmcotaj.key",  0x00, 0x14, CRC(d278b4ac) SHA1(06d94e8a203172792f405c73f9cbb37f4738429f) )
ROM_END

ROM_START( xmvsfhc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "xvse_hc01.03f", 0x000000, 0x80000, CRC(55eadea0) SHA1(4ebceb04ccd0bb7ccd99d4f8ff0e88a661425944) )
	ROM_LOAD16_WORD_SWAP( "xvse.04d", 0x080000, 0x80000, CRC(5eb9c02e) SHA1(25a392913213b98ce1bbd463bf5e5e10729bde0c) )
	ROM_LOAD16_WORD_SWAP( "xvse_hc01.05a",  0x100000, 0x80000, CRC(6b12c0d9) SHA1(0b7bb7fd0d9b080aef675463de1065efcb4a3309) )
	ROM_IGNORE( 0x3D4F52 )
	ROM_LOAD16_WORD_SWAP( "xvs.06a",  0x180000, 0x80000, CRC(e8e2c75c) SHA1(929408cb5d98e95cec75ea58e4701b0cbdbcd016) )
	ROM_LOAD16_WORD_SWAP( "xvs.07",   0x200000, 0x80000, CRC(08f0abed) SHA1(ef16c376232dba63b0b9bc3aa0640f9001ccb68a) )
	ROM_LOAD16_WORD_SWAP( "xvs.08",   0x280000, 0x80000, CRC(81929675) SHA1(19cf7afbc1daaefec40195e40ba74970f3906a1c) )
	ROM_LOAD16_WORD_SWAP( "xvs.09",   0x300000, 0x80000, CRC(9641f36b) SHA1(dcba3482d1ba37ccfb30d402793ee063c6621aed) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROMX_LOAD( "xvs.13m",   0x0000000, 0x400000, CRC(f6684efd) SHA1(c0a2f3a9e82ab8b084a500aec71ac633e947328c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xvs.15m",   0x0000002, 0x400000, CRC(29109221) SHA1(898b8f678fd03c462ce0d8eb7fb3441ef601085b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xvs.17m",   0x0000004, 0x400000, CRC(92db3474) SHA1(7b6f4c8ebfdac167b25f35029068b6253c141fe6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xvs.19m",   0x0000006, 0x400000, CRC(3733473c) SHA1(6579da7145c95b3ad00844a5fc8c2e22c23365e2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xvs.14m",   0x1000000, 0x400000, CRC(bcac2e41) SHA1(838ff24f7e8543a787a55a5d592c9517ce3b8b93) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xvs.16m",   0x1000002, 0x400000, CRC(ea04a272) SHA1(cd7c79037b5b4a39bef5156433e984dc4dc2c081) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xvs.18m",   0x1000004, 0x400000, CRC(b0def86a) SHA1(da3a6705ea7050fc5c2c10d33400ed67be9f455d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "xvs.20m",   0x1000006, 0x400000, CRC(4b40ff9f) SHA1(9a981d442132efff09a27408d74646ba357c7357) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 )
	ROM_LOAD( "xvs.01",   0x00000, 0x08000, CRC(3999e93a) SHA1(fefcff8a9a5c83df7655a16187cf9ba3e7efbb25) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "xvs.02",   0x28000, 0x20000, CRC(101bdee9) SHA1(75920e88bf46fcd33a7957777a1d799818ffb0d6) )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD16_WORD_SWAP( "xvs.11m",   0x000000, 0x200000, CRC(9cadcdbc) SHA1(64d3bd53b04daec84c9af4aa3ff010867b3d306d) )
	ROM_LOAD16_WORD_SWAP( "xvs.12m",   0x200000, 0x200000, CRC(7b11e460) SHA1(a581c84acaaf0ce056841c15a6f36889e88be68d) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "xmvsf.key",    0x00, 0x14, CRC(d5c07311) SHA1(1b401ffc241436c4869486c174774b67e3bf3df8) )
ROM_END

ROM_START( xmvsfhc02 ) //xmvsfcph
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "xvse_hc02.03d", 0x000000, 0x80000, CRC(d0d03ddf) SHA1(f3f96bb865f109005b1c772aa09a83c81e216d04) )
	ROM_LOAD16_WORD_SWAP( "xvse.04f", 0x080000, 0x80000, CRC(ef015aef) SHA1(d3504cb8c38f720b1f4528157266db60c8c6c075) )
	ROM_LOAD16_WORD_SWAP( "xvs.05a",  0x100000, 0x80000, CRC(7db6025d) SHA1(2d74f48f83f45359bfaca28ab686625766af12ee) )
	ROM_LOAD16_WORD_SWAP( "xvs.06a",  0x180000, 0x80000, CRC(e8e2c75c) SHA1(929408cb5d98e95cec75ea58e4701b0cbdbcd016) )
	ROM_LOAD16_WORD_SWAP( "xvs.07",   0x200000, 0x80000, CRC(08f0abed) SHA1(ef16c376232dba63b0b9bc3aa0640f9001ccb68a) )
	ROM_LOAD16_WORD_SWAP( "xvs.08",   0x280000, 0x80000, CRC(81929675) SHA1(19cf7afbc1daaefec40195e40ba74970f3906a1c) )
	ROM_LOAD16_WORD_SWAP( "xvs.09",   0x300000, 0x80000, CRC(9641f36b) SHA1(dcba3482d1ba37ccfb30d402793ee063c6621aed) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "xvs.13m",   0x0000000, 0x400000, CRC(f6684efd) SHA1(c0a2f3a9e82ab8b084a500aec71ac633e947328c) )
	ROM_LOAD64_WORD( "xvs.15m",   0x0000002, 0x400000, CRC(29109221) SHA1(898b8f678fd03c462ce0d8eb7fb3441ef601085b) )
	ROM_LOAD64_WORD( "xvs.17m",   0x0000004, 0x400000, CRC(92db3474) SHA1(7b6f4c8ebfdac167b25f35029068b6253c141fe6) )
	ROM_LOAD64_WORD( "xvs.19m",   0x0000006, 0x400000, CRC(3733473c) SHA1(6579da7145c95b3ad00844a5fc8c2e22c23365e2) )
	ROM_LOAD64_WORD( "xvs.14m",   0x1000000, 0x400000, CRC(bcac2e41) SHA1(838ff24f7e8543a787a55a5d592c9517ce3b8b93) )
	ROM_LOAD64_WORD( "xvs.16m",   0x1000002, 0x400000, CRC(ea04a272) SHA1(cd7c79037b5b4a39bef5156433e984dc4dc2c081) )
	ROM_LOAD64_WORD( "xvs.18m",   0x1000004, 0x400000, CRC(b0def86a) SHA1(da3a6705ea7050fc5c2c10d33400ed67be9f455d) )
	ROM_LOAD64_WORD( "xvs.20m",   0x1000006, 0x400000, CRC(4b40ff9f) SHA1(9a981d442132efff09a27408d74646ba357c7357) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 ) // 64k for the audio CPU (+banks)
	ROM_LOAD( "xvs.01",   0x00000, 0x08000, CRC(3999e93a) SHA1(fefcff8a9a5c83df7655a16187cf9ba3e7efbb25) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "xvs.02",   0x28000, 0x20000, CRC(101bdee9) SHA1(75920e88bf46fcd33a7957777a1d799818ffb0d6) )

	ROM_REGION( 0x400000, "qsound", 0 ) // QSound samples
	ROM_LOAD16_WORD_SWAP( "xvs.11m",   0x000000, 0x200000, CRC(9cadcdbc) SHA1(64d3bd53b04daec84c9af4aa3ff010867b3d306d) )
	ROM_LOAD16_WORD_SWAP( "xvs.12m",   0x200000, 0x200000, CRC(7b11e460) SHA1(a581c84acaaf0ce056841c15a6f36889e88be68d) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "xmvsf.key",    0x000000, 0x000014, CRC(d5c07311) SHA1(1b401ffc241436c4869486c174774b67e3bf3df8) )
ROM_END

ROM_START( xmvsfhc03 ) //xmvsfcph
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "xvse_hc03.03d", 0x000000, 0x80000, CRC(ed7c235a) SHA1(c49bfeef0351165ee30c8433feb026acebd7a36a) )
	ROM_LOAD16_WORD_SWAP( "xvse_hc03.04f", 0x080000, 0x80000, CRC(3a527f69) SHA1(72312d4aeaac07c4b4f91a0301948faf2f17d74d) )
	ROM_LOAD16_WORD_SWAP( "xvs.05a",  0x100000, 0x80000, CRC(7db6025d) SHA1(2d74f48f83f45359bfaca28ab686625766af12ee) )
	ROM_LOAD16_WORD_SWAP( "xvs.06a",  0x180000, 0x80000, CRC(e8e2c75c) SHA1(929408cb5d98e95cec75ea58e4701b0cbdbcd016) )
	ROM_LOAD16_WORD_SWAP( "xvs.07",   0x200000, 0x80000, CRC(08f0abed) SHA1(ef16c376232dba63b0b9bc3aa0640f9001ccb68a) )
	ROM_LOAD16_WORD_SWAP( "xvs.08",   0x280000, 0x80000, CRC(81929675) SHA1(19cf7afbc1daaefec40195e40ba74970f3906a1c) )
	ROM_LOAD16_WORD_SWAP( "xvs.09",   0x300000, 0x80000, CRC(9641f36b) SHA1(dcba3482d1ba37ccfb30d402793ee063c6621aed) )

	ROM_REGION( 0x2000000, "gfx", 0 )
	ROM_LOAD64_WORD( "xvs.13m",   0x0000000, 0x400000, CRC(f6684efd) SHA1(c0a2f3a9e82ab8b084a500aec71ac633e947328c) )
	ROM_LOAD64_WORD( "xvs.15m",   0x0000002, 0x400000, CRC(29109221) SHA1(898b8f678fd03c462ce0d8eb7fb3441ef601085b) )
	ROM_LOAD64_WORD( "xvs.17m",   0x0000004, 0x400000, CRC(92db3474) SHA1(7b6f4c8ebfdac167b25f35029068b6253c141fe6) )
	ROM_LOAD64_WORD( "xvs.19m",   0x0000006, 0x400000, CRC(3733473c) SHA1(6579da7145c95b3ad00844a5fc8c2e22c23365e2) )
	ROM_LOAD64_WORD( "xvs.14m",   0x1000000, 0x400000, CRC(bcac2e41) SHA1(838ff24f7e8543a787a55a5d592c9517ce3b8b93) )
	ROM_LOAD64_WORD( "xvs.16m",   0x1000002, 0x400000, CRC(ea04a272) SHA1(cd7c79037b5b4a39bef5156433e984dc4dc2c081) )
	ROM_LOAD64_WORD( "xvs.18m",   0x1000004, 0x400000, CRC(b0def86a) SHA1(da3a6705ea7050fc5c2c10d33400ed67be9f455d) )
	ROM_LOAD64_WORD( "xvs.20m",   0x1000006, 0x400000, CRC(4b40ff9f) SHA1(9a981d442132efff09a27408d74646ba357c7357) )

	ROM_REGION( QSOUND_SIZE, "audiocpu", 0 ) // 64k for the audio CPU (+banks)
	ROM_LOAD( "xvs.01",   0x00000, 0x08000, CRC(3999e93a) SHA1(fefcff8a9a5c83df7655a16187cf9ba3e7efbb25) )
	ROM_CONTINUE(         0x10000, 0x18000 )
	ROM_LOAD( "xvs.02",   0x28000, 0x20000, CRC(101bdee9) SHA1(75920e88bf46fcd33a7957777a1d799818ffb0d6) )

	ROM_REGION( 0x400000, "qsound", 0 ) // QSound samples
	ROM_LOAD16_WORD_SWAP( "xvs.11m",   0x000000, 0x200000, CRC(9cadcdbc) SHA1(64d3bd53b04daec84c9af4aa3ff010867b3d306d) )
	ROM_LOAD16_WORD_SWAP( "xvs.12m",   0x200000, 0x200000, CRC(7b11e460) SHA1(a581c84acaaf0ce056841c15a6f36889e88be68d) )

	ROM_REGION( 0x20, "key", 0 )
	ROM_LOAD( "xmvsf.key",    0x000000, 0x000014, CRC(d5c07311) SHA1(1b401ffc241436c4869486c174774b67e3bf3df8) )
ROM_END

/*    YEAR  NAME          PARENT       MACHINE         INPUT                  INIT        MONITOR   COMPANY       FULLNAME FLAGS */
// CPS2 Hack
GAME( 2022, 19xxhc01,    19xx,         cps2,         cps2_2p2b, cps2_state, init_cps2,     ROT270, "DDJ",         "19XX: The War Against Destiny (The Strongest Firepower 2022-03-31)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, 19xxhc02,    19xx,         cps2,         cps2_2p2b, cps2_state, init_cps2,     ROT270, "hack",        "19XX: The War Against Destiny (Chinese Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2014, 1944hc01,    1944,         cps2,         cps2_2p2b, cps2_state, init_cps2,     ROT0,   "DDJ",         "1944: The Loop Master (The Strongest Firepower 2014-11-04)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, avsphc01,    avsp,         cps2,         cps2_3p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Alien vs. Predator (1V3 2017-12-30)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, avsphc02,    avsp,         cps2,         cps2_3p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Alien vs. Predator (Ex Super Version 2020-08-30)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, avsphc03,    avsp,         cps2,         cps2_3p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Alien vs. Predator (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, batcirhc01,  batcir,       dead_cps2,    cps2_4p2b, cps2_state, init_cps2,     ROT0,   "hack",        "Battle Circuit (Evolution 2019-10-21)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, csclubhc01,  csclub,       cps2,         cps2_2p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Capcom Sports Club (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, cybotshc01,  cybots,       cps2,         cybots,    cps2_state, init_cps2,     ROT0,   "hack",        "Cyberbots: Fullmetal Madness (Panic AM Modified Version 2022-01-23)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, cybotshc02,  cybots,       cps2,         cybots,    cps2_state, init_cps2,     ROT0,   "hack",        "Cyberbots: Fullmetal Madness (Ex Super Version)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ddsomhc01,   ddsom,        cps2,         cps2_4p4b, cps2_state, init_cps2,     ROT0,   "hack",        "Dungeons & Dragons: Shadow over Mystara (Chinese Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2009, ddsomhc02,   ddsom,        cps2,         cps2_4p4b, cps2_state, init_cps2,     ROT0,   "hack",        "Dungeons & Dragons: Shadow over Mystara (Change the Final Strike condition 2009-07-17)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, ddsomhc03,   ddsom,        dead_cps2,    cps2_4p4b, cps2_state, init_cps2,     ROT0,   "GOTVG",       "Dungeons & Dragons: Shadow over Mystara (Plus 2016-08-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2009, ddsomhc04,   ddsom,        cps2,         cps2_4p4b, cps2_state, init_cps2,     ROT0,   "hack",        "Dungeons & Dragons: Shadow over Mystara (1v4 2009-06-29)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ddsomhc05,   ddsom,        cps2,         cps2_4p4b, cps2_state, init_cps2,     ROT0,   "hack",        "Dungeons & Dragons: Shadow over Mystara (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, ddtodhc01,   ddtod,        dead_cps2,    cps2_4p4b, cps2_state, init_cps2,     ROT0,   "GOTVG",       "Dungeons & Dragons: Tower of Doom (Plus 2016-08-25)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, ddtodhc02,   ddtod,        cps2,         cps2_4p4b, cps2_state, init_cps2,     ROT0,   "hack",        "Dungeons & Dragons: Tower of Doom (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, dstlkhc01,   dstlk,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Darkstalkers: The Night Warriors (Easy Moves)", MACHINE_SUPPORTS_SAVE )
GAME( 2006, dstlkhc02,   dstlk,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Darkstalkers: The Night Warriors (Enable hidden characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, ffightaec2,  0,            dead_cps2,    cps2_3p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Fight Fight Anniversary Edition (CPS2 hardware)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, ffightaec2ds,ffightaec2,   dead_cps2,    cps2_3p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Fight Fight Anniversary Edition (Deadly Streets)", MACHINE_SUPPORTS_SAVE )
GAME( 2014, gigawinghc01,gigawing,     cps2,         cps2_2p2b, cps2_state, init_cps2,     ROT0,   "hack",        "Giga Wing (The Strongest Firepower 2014-11-04)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, hsf2hc01,    hsf2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Hyper Street Fighter II: The Anniversary Edition (Gouki Edition 2018-07-29)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, hsf2hc02,    hsf2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "DDJ",         "Hyper Street Fighter II: The Anniversary Edition (Easy Move)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, hsf2hc03,    hsf2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "DDJ",         "Hyper Street Fighter II: The Anniversary Edition (Always Have Super Move)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, hsf2hc04,    hsf2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Hyper Street Fighter II: The Anniversary Edition (Enabled Hidden Characters In Normal Mode)", MACHINE_SUPPORTS_SAVE )
GAME( 2024, hsf2hc05,    hsf2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Hyper Street Fighter II: The Anniversary Edition (Difficulty Fix)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, hsf2hc06,    hsf2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Hyper Street Fighter II: The Anniversary Edition (30% Blood)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, hsf2hc07,    hsf2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Hyper Street Fighter II: The Anniversary Edition (Plus Plus 2017-06-25)", MACHINE_SUPPORTS_SAVE )
GAME( 2025, hsf2hc08,    hsf2,         dead_cps2,    cps2_2p6b, cps2_state, init_cps2,     ROT0,   "Zero800",     "Street Fighter II': Prime (v0.66)", MACHINE_SUPPORTS_SAVE )
GAME( 2009, mvschc01,    mvsc,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Marvel Vs. Capcom: Clash of Super Heroes (Easy Moves)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, mvschc02,    mvsc,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Marvel Vs. Capcom: Clash of Super Heroes (Enable Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2014, mshhc01,     msh,          cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Marvel Super Heroes (Rise Again 2014-12-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, mshhc02,     msh,          cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Marvel Super Heroes (Boss With Simple Attack Edition 2015-12-04)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, mshhc03,     msh,          cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Marvel Super Heroes (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2014, mshvsfhc01,  mshvsf,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Marvel Super Heroes Vs. Street Fighter (Rise Again 2014-12-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2009, mshvsfhc02,  mshvsf,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Marvel Super Heroes Vs. Street Fighter (Easy Moves)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, mshvsfhc03,  mshvsf,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Marvel Super Heroes Vs. Street Fighter (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, mshvsfhc04,  mshvsf,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Marvel Super Heroes Vs. Street Fighter (Coop 2024-06-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2025, pfghthc01,   sgemf,        cps2,         cps2_2p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Pocket Fighter (Chinese translation)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, pfghthc02,   sgemf,        cps2,         cps2_2p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Pocket Fighter (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2014, pfghthc03,   sgemf,        cps2,         cps2_2p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Pocket Fighter (Resurgence Lite 2014-12-17)", MACHINE_SUPPORTS_SAVE )
GAME( 2001, progearhc01, progear,      dead_cps2,    cps2_2p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Progear no Arashi (Crazy Fire)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, progearhc02, progear,      dead_cps2,    cps2_2p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Progear no Arashi (Halfway to Hell - Progear Red Label 2016-01-17)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, rmancp2hc01, megaman,      cps2,         cps2_2p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Rockman: The Power Battle (Korean Translation / CPS2)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, rockman2hc01,megaman2,     cps2,         cps2_2p3b, cps2_state, init_cps2,     ROT0,   "hack",        "Rockman 2: The Power Fighters (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, sfahc01,     sfa,          cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "DDJ",         "Street Fighter Alpha: Warriors' Dreams (Easy Move)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, sfahc02,     sfa,          cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "DDJ",         "Street Fighter Alpha: Warriors' Dreams (Enable Hidden Character)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, sfahc03,     sfa,          cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Zero (Subduing the Dragon 2016-11-02)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, sfahc04,     sfa,          cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Zero (Korean Translation / CPS2)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, sfa2hc01,    sfa2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "DDJ",         "Street Fighter Alpha 2 (Easy Move)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, sfa2hc02,    sfa2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Alpha 2 (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, sfa2hc03,    sfa2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Alpha 2 (Ultra Beta 2023-07-08)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, sfa2hc04,    sfa2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Zero 2 (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, sfa3hc01,    sfa3,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Alpha 3 (Challenger 2022-07-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, sfa3hc02,    sfa3,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "DDJ",         "Street Fighter Alpha 3 (Easy Move)", MACHINE_SUPPORTS_SAVE )
GAME( 2009, sfa3hc03,    sfa3,         cps2,         cps2_2p6bt,cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Alpha 3 (Xiang Long 2009-05-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2009, sfa3hc04,    sfa3,         cps2,         cps2_2p6bt,cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Alpha 3 (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, sfa3hc05,    sfa3,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Zero 3 (Training Edition v1.2)", MACHINE_SUPPORTS_SAVE )
GAME( 2005, sfa3hc06,    sfa3,         cps2,         cps2_2p6bt,cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Alpha 3 (Brazil Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, sfa3hc07,    sfa3,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "Zero800",     "Street Fighter Zero 3 (Mix 0.13)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, sfz2alhc01,  sfz2al,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Zero 2 Alpha (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2014, sfz2alhc02,  sfz2al,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Zero 2 Alpha (Dragon Fighter 2014-11-19)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, sfz2alhc03,  sfz2al,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "DDJ",         "Street Fighter Zero 2 Alpha (Easy Move 2016-11-18)", MACHINE_SUPPORTS_SAVE )
GAME( 2009, sfz2alhc04,  sfz2al,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Zero 2 Alpha (Dragon Level 2009-04-24)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, sfz2alhc05,  sfz2al,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Zero 2 Alpha (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, sfz2alhc06,  sfz2al,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Street Fighter Zero 2 Alpha (Brazil Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 2024, ssf2thc01,   ssf2t,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Street Fighter II Turbo (New Legacy v0.9 beta, 2024-04-02)", MACHINE_SUPPORTS_SAVE )
GAME( 2024, ssf2thc02,   ssf2t,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Street Fighter II Turbo (Difficulty Fix)", MACHINE_SUPPORTS_SAVE )
GAME( 2005, ssf2thc03,   ssf2t,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Street Fighter II Turbo (French Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, ssf2xhc01,   ssf2t,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Street Fighter II X: Grand Master Challenge (Enable hidden characters)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, ssf2xhc02,   ssf2t,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Street Fighter II X: Grand Master Challenge (Trainer)", MACHINE_SUPPORTS_SAVE )
GAME( 2012, ssf2hc01,    ssf2,         cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "DDJ",         "Super Street Fighter II X: The New Challengers (Easy Move)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, spf2thc01,   spf2t,        cps2,         cps2_2p2b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Puzzle Fighter II Turbo (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, spf2thc02,   spf2t,        cps2,         cps2_2p2b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Puzzle Fighter II Turbo (Patch Modified Version 2022-01-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, spf2thc03,   spf2t,        cps2,         cps2_2p2b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Puzzle Fighter II Turbo (Color Blind v1.1)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, spf2xhc01,   spf2t,        cps2,         cps2_2p2b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Puzzle Fighter II X (Balance Patch)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, spf2xhc02,   spf2t,        cps2,         cps2_2p2b, cps2_state, init_cps2,     ROT0,   "hack",        "Super Puzzle Fighter II X (Korean Translation)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, xmcotahc01,  xmcota,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "X-Men: Children of the Atom (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, xmcotahc02,  xmcota,       cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "X-Men: Children of the Atom (Boss With Simple Attack 2013-01-09)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, xmvsfhc01,   xmvsf,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "X-Men Vs. Street Fighter (Easy Move)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, xmvsfhc02,   xmvsf,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "X-Men Vs. Street Fighter (Coop 2022-05-20)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, xmvsfhc03,   xmvsf,        cps2,         cps2_2p6b, cps2_state, init_cps2,     ROT0,   "hack",        "X-Men Vs. Street Fighter (Change Character In Battle)", MACHINE_SUPPORTS_SAVE )
