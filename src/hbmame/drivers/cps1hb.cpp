// license:BSD-3-Clause
// copyright-holders:Robbbert
/*******************************************************************************************************************

        CPS-1 driver for hacks and bootlegs

Issues:

- knightsh
	the title screen is garbage.

- kodh
	title, problem with placement of the letters.

- sk2h1, sk2h2, sk2h3, sk2h22, sk2h31, sk2h32, sk2h33, sk2h34
	setup screen is blank.
	map doesn't show first time around prior to demo 1, and never before demo 3.

- sk2h22, sk2h31, sk2h32, sk2h33, sk2h34, sk2h35
	coin 3, start 3, 3rd player not working.

- wofjcn
	chinese language rom isn't working. Whatever is tried breaks stuff.


*******************************************************************************************************************/

WRITE16_MEMBER( cps_state::dinoh_sound_command_w )
{
	/* Pass the Sound Code to the Q-Sound Shared Ram */
	m_qsound_sharedram1[1] = data;
}

WRITE16_MEMBER( cps_state::daimakb_palctrl_w )
{
	m_cps_b_regs[0x30 / 2] = data;
}

WRITE16_MEMBER(cps_state::daimakb_layer_w)
{
	if (offset == 0x00)
		m_cps_a_regs[0x0e / 2] = data; /* scroll 1y */
	else
	if (offset == 0x01)
		m_cps_a_regs[0x0c / 2] = data - 0x40; /* scroll 1x */
	else
	if (offset == 0x02)
	{
		m_cps_a_regs[0x12 / 2] = data; /* scroll 2y */
		m_cps_a_regs[0x20 / 2] = data; /* row scroll start */
	}
	else
	if (offset == 0x03)
		m_cps_a_regs[0x10 / 2] = data - 0x40; /* scroll 2x */
	else
	if (offset == 0x04)
		m_cps_a_regs[0x16 / 2] = data; /* scroll 3y */
	else
	if (offset == 0x05)
		m_cps_a_regs[0x14 / 2] = data - 0x40; /* scroll 3x */
	else
	if (offset == 0x06)
	{
		switch (data)
		{
		case 0x0000:
			data = (1 << 12) | (2 << 8) | (3 << 6);
			break;
		case 0x0001:
			data = (1 << 12) | (3 << 6);
			break;
		case 0x0002:
			data = (3 << 12) | (1 << 6);
			break;
		case 0x0006:
			data = 0;
			break;
		default:
			data = 0;
			printf ("Unknown control word = %X\n",data);
		}
		m_cps_b_regs[0x26 / 2] = data;
	}
}



/**************************************************************************

	Address Maps

***************************************************************************/

void cps_state::daimakb_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800001).portr("IN1");  /* Player input ports */
	map(0x800006,0x800007).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_hack_dsw_r));  /* System input ports / Dip Switches */
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800166,0x800171).nopw();  // not used
	map(0xe00000,0xe0003f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");  // dummy region
	map(0x880000,0x880001).w(FUNC(cps_state::daimakb_palctrl_w));
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0x980000,0x98000d).w(FUNC(cps_state::daimakb_layer_w));
	map(0x990000,0x993fff).nopw();  // bootleg sprites, not needed
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::sk2h35_map(address_map &map) {
/* unknown addresses (all write): 930008-930807. No 3rd player controls. NVRAM doesn't work */
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800001).portr("IN1");  /* Player input ports */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x80001c,0x80001d).portr("EEPROMIN").portw("EEPROMOUT");
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");  /* CPS-B custom */
	map(0x800180,0x800187).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x800188,0x80018f).w(FUNC(cps_state::cps1_soundlatch2_w));  /* Sound timer fade */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0x930008,0x930807).nopw();
	map(0xf18000,0xf19fff).rw(FUNC(cps_state::qsound_sharedram1_r),FUNC(cps_state::qsound_sharedram1_w));  /* Q RAM */
	map(0xf1ce74,0xf1ce75).nopw();
	map(0xf1e000,0xf1ffff).rw(FUNC(cps_state::qsound_sharedram2_r),FUNC(cps_state::qsound_sharedram2_w));  /* Q RAM */
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::cps1frog_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800001).portr("IN1");  /* Player input ports */
	map(0x800030,0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* Output ports */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x800180,0x800187).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x800188,0x80018f).w(FUNC(cps_state::cps1_soundlatch2_w));  /* Sound timer fade */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::sk2h1q_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800030,0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).ram().share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x880000,0x880001).portr("IN1");  /* Player input ports */
	map(0x880006,0x88000d).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x88000e,0x88000f).nopw();
	map(0x880e78,0x880e79).r(FUNC(cps_state::cps1_in2_r));  /* Player 3 controls (later games) */
	map(0x890000,0x890001).nopw();
	map(0x8bfff6,0x8bfff9).nopr();  /* unknown */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf18000,0xf19fff).rw(FUNC(cps_state::qsound_sharedram1_r),FUNC(cps_state::qsound_sharedram1_w));  /* Q RAM */
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xf1e000,0xf1ffff).rw(FUNC(cps_state::qsound_sharedram2_r),FUNC(cps_state::qsound_sharedram2_w));  /* Q RAM */
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::sk2h3_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800030,0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).ram().share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x880000,0x880001).portr("IN1");  /* Player input ports */
	map(0x880006,0x88000d).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x88000e,0x88000f).w(FUNC(cps_state::cps1_soundlatch_w));
	map(0x880e78,0x880e79).r(FUNC(cps_state::cps1_in2_r));  /* Player 3 controls (later games) */
	map(0x890000,0x890001).nopw();
	map(0x8bfff6,0x8bfff9).nopr();  /* unknown */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::sk2h31q_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800030,0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* Output ports */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x880000,0x880001).portr("IN1");  /* Player input ports */
	map(0x880006,0x880007).nopw();  // soundlatch on non-qsound hw
	map(0x880008,0x88000f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x880e7e,0x880e7f).r(FUNC(cps_state::cps1_in2_r));  /* Player 3 controls (later games) */
	map(0x890000,0x890001).nopw();
	map(0x8bfff6,0x8bfff9).nopr();  /* unknown */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf18000,0xf19fff).rw(FUNC(cps_state::qsound_sharedram1_r),FUNC(cps_state::qsound_sharedram1_w));  /* Q RAM */
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xf1e000,0xf1ffff).rw(FUNC(cps_state::qsound_sharedram2_r),FUNC(cps_state::qsound_sharedram2_w));  /* Q RAM */
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::sk2h31_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800030,0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* Output ports */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x880000,0x880001).portr("IN1");  /* Player input ports */
	map(0x880006,0x880007).w(FUNC(cps_state::cps1_soundlatch_w));
	map(0x880008,0x88000f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x880e7e,0x880e7f).r(FUNC(cps_state::cps1_in2_r));  /* Player 3 controls (later games) */
	map(0x890000,0x890001).nopw();
	map(0x8bfff6,0x8bfff9).nopr();  /* unknown */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::wofsf2_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800007).portr("IN1");
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_hack_dsw_r));
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x800180,0x800187).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf18000,0xf19fff).ram();
	map(0xf1c000,0xf1c001).r(FUNC(cps_state::cps1_in2_r));  /* Player 3 controls */
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000,0xffffff).ram().share("mainram");
}

/********************************************************************

	Inputs and dips

*********************************************************************/

static INPUT_PORTS_START( dinohz )
	PORT_INCLUDE( dino )

	PORT_MODIFY("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT  ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN  ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP    ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT  ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN  ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP    ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_MODIFY("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
//	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )
INPUT_PORTS_END

static INPUT_PORTS_START( knightsh )
	PORT_INCLUDE( knights )

	PORT_MODIFY("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_MODIFY("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
//	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )
INPUT_PORTS_END

static INPUT_PORTS_START( kodh )
	PORT_INCLUDE( kod )

	PORT_MODIFY("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )
INPUT_PORTS_END

static INPUT_PORTS_START( pnicku )
	PORT_INCLUDE( pnickj )
	PORT_MODIFY("DSWA")
	PORT_DIPNAME( 0x07, 0x07, DEF_STR( Coinage ) )  PORT_DIPLOCATION("SW(A):1,2,3")
	PORT_DIPSETTING(    0x00, DEF_STR( 5C_1C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 4C_1C ) )
	PORT_DIPSETTING(    0x02, DEF_STR( 3C_1C ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0x07, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x06, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0x05, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0x04, DEF_STR( 1C_4C ) )

	PORT_DIPNAME( 0x10, 0x10, "Chuters" )           PORT_DIPLOCATION("SW(A):5")
	PORT_DIPSETTING(    0x00, "2" )
	PORT_DIPSETTING(    0x10, "1" )

	PORT_MODIFY("DSWC")
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Free_Play ) ) PORT_DIPLOCATION("SW(C):3")
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
INPUT_PORTS_END

static INPUT_PORTS_START( sk2h3 )
	PORT_START ("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWA")
	PORT_DIPNAME( 0x03, 0x00, "Play Mode" )
	PORT_DIPSETTING(    0x00, DEF_STR( Normal ) )
	PORT_DIPSETTING(    0x03, "Tournament" )
	PORT_BIT( 0xfc, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWB")
	PORT_DIPNAME( 0x03, 0x03, DEF_STR( Coinage ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x02, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_4C ) )
	PORT_BIT( 0xfc, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWC")
	PORT_BIT( 0xff, IP_ACTIVE_HIGH, IPT_UNKNOWN )

	PORT_START ("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )

	PORT_START( "EEPROMIN" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_READ_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, do_read)

	PORT_START( "EEPROMOUT" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, di_write)
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, clk_write)
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, cs_write)
INPUT_PORTS_END

static INPUT_PORTS_START( sk2h21 )
	PORT_INCLUDE( wof )

	PORT_MODIFY("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_MODIFY("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
//	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )
INPUT_PORTS_END


/***********************************************************
             INPUT PORTS, DIPs
***********************************************************/

static INPUT_PORTS_START( cps1frog )
	PORT_START ("IN0")
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWA")
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWB")
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWC")
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )
INPUT_PORTS_END

static INPUT_PORTS_START( sk2h1 )
	PORT_START ("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWA")
	PORT_DIPNAME( 0x03, 0x00, "Play Mode" )
	PORT_DIPSETTING(    0x00, DEF_STR( Normal ) )
	PORT_DIPSETTING(    0x03, "Tournament" )
	PORT_BIT( 0xfc, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWB")
	PORT_DIPNAME( 0x03, 0x03, DEF_STR( Coinage ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x02, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_4C ) )
	PORT_BIT( 0xfc, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWC")
	PORT_BIT( 0xff, IP_ACTIVE_HIGH, IPT_UNKNOWN )

	PORT_START ("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )

	PORT_START( "EEPROMIN" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_READ_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, do_read)

	PORT_START( "EEPROMOUT" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, di_write)
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, clk_write)
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, cs_write)
INPUT_PORTS_END

static INPUT_PORTS_START( sk2h31 )
	PORT_START ("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWA")	/* there are lots of other combinations, but this covers the useful ones */
	PORT_DIPNAME( 0xff, 0xff, DEF_STR( Coinage ) )
	PORT_DIPSETTING(    0xde, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0xff, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0xfe, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0xfd, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0xfc, DEF_STR( 1C_4C ) )
	PORT_DIPSETTING(    0x7f, DEF_STR( 1C_7C ) )
	PORT_DIPSETTING(    0xdf, DEF_STR( 1C_8C ) )

	PORT_START ("DSWB")      /* (not used, EEPROM) */
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWC")      /* (not used, EEPROM) */
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )

	PORT_START( "EEPROMIN" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_READ_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, do_read)

	PORT_START( "EEPROMOUT" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, di_write)
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, clk_write)
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, cs_write)
INPUT_PORTS_END

INPUT_PORTS_START( sf2mix )
	PORT_INCLUDE( sf2 )
	PORT_MODIFY("DSWA")
	PORT_DIPNAME( 0x80, 0x80, "Win Quotes" )   PORT_DIPLOCATION("SW(A):8")
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_MODIFY("DSWB")
	PORT_DIPNAME( 0x08, 0x08, "False 3D, Car in India, Random Bonus Stages" )   PORT_DIPLOCATION("SW(B):4")
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
INPUT_PORTS_END
/********************************************************************
*
*  Machine Driver macro
*  ====================
*
*
********************************************************************/


void cps_state::wofsf2(machine_config &config)
{
	wofhfh(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::wofsf2_map);
}

void cps_state::daimakb(machine_config &config)
{
	cps1_10MHz(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::daimakb_map);
}

void cps_state::sk2h3(machine_config &config)
{
	wofhfh(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sk2h3_map);
}

void cps_state::sk2h31(machine_config &config)
{
	wofhfh(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sk2h31_map);
}

void cps_state::sk2h35(machine_config &config)
{
	qsound(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sk2h35_map);
}

void cps_state::cps1frog(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, XTAL(10'000'000));    /* verified on pcb */
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::cps1frog_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, XTAL(3'579'545));  /* verified on pcb */
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::sub_map);

	MCFG_MACHINE_START_OVERRIDE(cps_state, cps1)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_raw(8'000'000, 518, 64, 448, 259, 16, 240);
	m_screen->set_screen_update(FUNC(cps_state::screen_update_cps1));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state, cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	GENERIC_LATCH_8(config, m_soundlatch);
	GENERIC_LATCH_8(config, m_soundlatch2);
	ym2151_device &ym2151(YM2151(config, "2151", XTAL(3'579'545)));  /* verified on pcb */
	ym2151.irq_handler().set_inputline(m_audiocpu, 0);
	ym2151.add_route(0, "mono", 0.35);
	ym2151.add_route(1, "mono", 0.35);
	OKIM6295(config, m_oki, XTAL(16'000'000)/4/4, okim6295_device::PIN7_HIGH).add_route(ALL_OUTPUTS, "mono", 0.30);
}

void cps_state::sk2h1q(machine_config &config)
{
	cps1frog(config);

	/* basic machine hardware */
	m_maincpu->set_clock(XTAL(12'000'000));    /* verified on pcb */
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sk2h1q_map);

	Z80(config.replace(), m_audiocpu, XTAL(8'000'000));  /* verified on pcb */
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::qsound_sub_map);
	m_audiocpu->set_addrmap(AS_OPCODES, &cps_state::qsound_decrypted_opcodes_map);
	m_audiocpu->set_periodic_int(FUNC(cps_state::irq0_line_hold), attotime::from_hz(250)); // measured (cps2.cpp)

	MCFG_MACHINE_START_OVERRIDE(cps_state, qsound)

	EEPROM_93C46_16BIT(config, "eeprom");

	/* sound hardware */
	config.device_remove("mono");
	SPEAKER(config, "lspeaker").front_left();
	SPEAKER(config, "rspeaker").front_right();

	config.device_remove("2151");
	config.device_remove("oki");

	qsound_device &qsound(QSOUND(config, "qsound"));
	qsound.add_route(0, "lspeaker", 1.0);
	qsound.add_route(1, "rspeaker", 1.0);
}

void cps_state::sk2h31q(machine_config &config)
{
	sk2h1q(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sk2h31q_map);
}

void cps_state::init_dinoeh()
{
	m_maincpu->space(AS_PROGRAM).install_write_handler(0x800180, 0x800181, write16_delegate(FUNC(cps_state::dinoh_sound_command_w),this));
	kabuki_setup(dino_decode);
	init_cps1();
}

void cps_state::init_dinoh()
{
	/* Patch out Q-Sound test */
	uint16_t *rom = (uint16_t *)memregion("maincpu")->base();
	rom[0xaacf4/2] = 0x4e71;
	init_dinoeh();
}

void cps_state::init_dinoz()
{
	uint16_t *rom = (uint16_t *)memregion("maincpu")->base();
	rom[0xaaa82/2] = 0x4e71; // Patch out Q-Sound test
	rom[0x1cfb4/2] = 0x4e71; // patch out invalid instruction
	init_dinoeh();
}

void cps_state::init_dinohb()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Fix draw scroll
//	mem8[0x006c2] = 0xC0;
//	mem8[0x006c3] = 0xFF;
	// Fix gfx
	mem8[0x472] = 0xFC;
	mem8[0x473] = 0x33;
	mem8[0x474] = 0x0;
	mem8[0x475] = 0x90;
	mem8[0x476] = 0x80;
	mem8[0x478] = 0x0;
	mem8[0x479] = 0x1;
	mem8[0x47A] = 0xFC;
	mem8[0x47B] = 0x33;
	mem8[0x47C] = 0x80;
	mem8[0x47D] = 0x90;
	mem8[0x47E] = 0x80;
	mem8[0x480] = 0x2;
	mem8[0x481] = 0x1;
	mem8[0x482] = 0xFC;
	mem8[0x483] = 0x33;
	mem8[0x484] = 0xC0;
	mem8[0x485] = 0x90;
	mem8[0x486] = 0x80;
	mem8[0x487] = 0x0;
	mem8[0x488] = 0x4;
	mem8[0x489] = 0x1;
	mem8[0x48A] = 0xFC;
	mem8[0x48B] = 0x33;
	mem8[0x48C] = 0x0;
	mem8[0x48D] = 0x91;
	mem8[0x48E] = 0x80;
	mem8[0x48F] = 0x0;
	mem8[0x490] = 0x6;
	mem8[0x491] = 0x1;
	mem8[0x006cc] = 0x80;
	mem8[0x006cd] = 0x00;
	mem8[0x006ce] = 0x0C;
	mem8[0x006cf] = 0x01;
	mem8[0x006de] = 0x80;
	mem8[0x006df] = 0x00;
	mem8[0x006e0] = 0x10;
	mem8[0x006e1] = 0x01;
	mem8[0x006f0] = 0x80;
	mem8[0x006f1] = 0x00;
	mem8[0x006f2] = 0x14;
	mem8[0x006f3] = 0x01;
	mem8[0x00704] = 0x80;
	mem8[0x00705] = 0x00;
	mem8[0x00706] = 0x0E;
	mem8[0x00707] = 0x01;
	mem8[0x00718] = 0x80;
	mem8[0x00719] = 0x00;
	mem8[0x0071a] = 0x12;
	mem8[0x0071b] = 0x01;
	mem8[0x0072c] = 0x80;
	mem8[0x0072d] = 0x00;
	mem8[0x0072e] = 0x16;
	mem8[0x0072f] = 0x01;
	// Fix screen transitions
	mem8[0x00b28] = 0x00;
	mem8[0x00b29] = 0x70;
	mem8[0x00b2a] = 0x00;
	mem8[0x00b2b] = 0x72;
	mem8[0x00b2c] = 0x3C;
	mem8[0x00b2d] = 0x34;
	mem8[0x00b32] = 0xC1;
	mem8[0x00b33] = 0x20;
	// Fix sound
	mem8[0x00666] = 0xF1;
	mem8[0x00667] = 0x00;
	mem8[0x00668] = 0x02;
	mem8[0x00669] = 0x80;
	mem8[0xaaa6c] = 0xD8;
	mem8[0xaaa6d] = 0x00;

	kabuki_setup(dino_decode);
	init_cps1();
}

void cps_state::init_punisherb()
{
	// note: bytes are swapped around compared to rom_fill.
	uint8_t *mem8 = memregion("maincpu")->base();
	// Use standard ports
	mem8[0xAB3] = 0x33;
	mem8[0xAB4] = 0x30;
	mem8[0xAB6] = 0x80;
	mem8[0xAB7] = 0x0;
	mem8[0xAB8] = 0x56;
	mem8[0xAB9] = 0x1;
	mem8[0xABA] = 0xED;
	mem8[0xABB] = 0x33;
	mem8[0xABC] = 0x32;
	mem8[0xABD] = 0xDB;
	mem8[0xABE] = 0x80;
	mem8[0xABF] = 0x0;
	mem8[0xAC0] = 0x48;
	mem8[0xAC1] = 0x1;
	mem8[0xAC2] = 0xED;
	mem8[0xAC3] = 0x33;
	mem8[0xAC4] = 0x34;
	mem8[0xAC5] = 0xDB;
	mem8[0xAC6] = 0x80;
	mem8[0xAC7] = 0x0;
	mem8[0xAC8] = 0x4A;
	mem8[0xAC9] = 0x1;
	mem8[0xACA] = 0xED;
	mem8[0xACB] = 0x33;
	mem8[0xACC] = 0x2E;
	mem8[0xACD] = 0xDB;
	mem8[0xACE] = 0x80;
	mem8[0xAD0] = 0x52;
	mem8[0xAD1] = 0x1;
	mem8[0xAD2] = 0xED;
	mem8[0xAD3] = 0x33;
	mem8[0xAD4] = 0x88;
	mem8[0xAD5] = 0xDB;
	mem8[0xAD6] = 0x80;
	mem8[0xAD7] = 0x0;
	mem8[0xAD8] = 0x0;
	mem8[0xAD9] = 0x1;
	mem8[0xADA] = 0xED;
	mem8[0xADB] = 0x33;
	mem8[0xADC] = 0x8A;
	mem8[0xADD] = 0xDB;
	mem8[0xADE] = 0x80;
	mem8[0xADF] = 0x0;
	mem8[0xAE0] = 0x2;
	mem8[0xAE1] = 0x1;
	mem8[0xAE2] = 0xED;
	mem8[0xAE3] = 0x33;
	mem8[0xAE4] = 0x8C;
	mem8[0xAE5] = 0xDB;
	mem8[0xAE6] = 0x80;
	mem8[0xAE7] = 0x0;
	mem8[0xAE8] = 0x4;
	mem8[0xAE9] = 0x1;
	mem8[0xAEA] = 0xED;
	mem8[0xAEB] = 0x33;
	mem8[0xAEC] = 0x8E;
	mem8[0xAED] = 0xDB;
	mem8[0xAEE] = 0x80;
	mem8[0xAEF] = 0x0;
	mem8[0xAF0] = 0x6;
	mem8[0xAF1] = 0x1;
	mem8[0xAF2] = 0xED;
	mem8[0xAF3] = 0x33;
	mem8[0xAF4] = 0x90;
	mem8[0xAF5] = 0xDB;
	mem8[0xAF6] = 0x80;
	mem8[0xAF7] = 0x0;
	mem8[0xAF8] = 0x8;
	mem8[0xAF9] = 0x1;
	mem8[0xAFA] = 0xED;
	mem8[0xAFB] = 0x50;
	mem8[0xAFC] = 0x49;
	mem8[0xAFD] = 0xDB;
	mem8[0xAFE] = 0xFC;
	mem8[0xAFF] = 0x33;
	mem8[0xB00] = 0x3F;
	mem8[0xB02] = 0x80;
	mem8[0xB03] = 0x0;
	mem8[0xB04] = 0x4C;
	mem8[0xB05] = 0x1;
	mem8[0xB06] = 0xFC;
	mem8[0xB07] = 0x33;
	mem8[0xB08] = 0x40;
	mem8[0xB09] = 0x91;
	mem8[0xB0A] = 0x80;
	mem8[0xB0C] = 0xA;
	mem8[0xB0D] = 0x1;
	mem8[0xBA8] = 0x80;
	mem8[0xBAA] = 0xC;
	mem8[0xBAB] = 0x1;
	mem8[0xBBA] = 0x80;
	mem8[0xBBC] = 0x10;
	mem8[0xBBD] = 0x1;
	mem8[0xBCC] = 0x80;
	mem8[0xBCE] = 0x14;
	mem8[0xBCF] = 0x1;
	mem8[0xBDA] = 0x80;
	mem8[0xBDC] = 0xE;
	mem8[0xBDD] = 0x1;
	mem8[0xBEE] = 0x80;
	mem8[0xBF0] = 0x12;
	mem8[0xBF1] = 0x1;
	mem8[0xC02] = 0x80;
	mem8[0xC04] = 0x16;
	mem8[0xC05] = 0x1;
	// Transitions
	mem8[0x42b5] = 0;
	// Q sound
	mem8[0x4DBC] = 0x0;
	mem8[0x4DBE] = 0x58;
	mem8[0x4DBF] = 0x0;
	mem8[0x4DC0] = 0xF9;
	mem8[0x4DC1] = 0x41;
	mem8[0x4DC2] = 0xF1;
	mem8[0x4DC3] = 0x0;
	mem8[0x4DC4] = 0x0;
	mem8[0x4DC5] = 0x80;
	mem8[0x4DC6] = 0x28;
	mem8[0x4DC7] = 0x4A;
	mem8[0x4DC8] = 0x1F;
	mem8[0x4DC9] = 0x0;
	mem8[0x4DCA] = 0x0;
	mem8[0x4DCB] = 0x6A;
	mem8[0x4DCC] = 0x4A;
	mem8[0x4DCD] = 0x0;
	mem8[0x4DCE] = 0xED;
	mem8[0x4DCF] = 0x49;
	mem8[0x4DD0] = 0x96;
	mem8[0x4DD1] = 0xE2;
	mem8[0x4DD2] = 0xF4;
	mem8[0x4DD3] = 0x49;
	mem8[0x4DD4] = 0x0;
	mem8[0x4DD5] = 0x0;
	mem8[0x4DD6] = 0x40;
	mem8[0x4DD7] = 0x6;
	mem8[0x4DD8] = 0x10;
	mem8[0x4DDA] = 0x40;
	mem8[0x4DDB] = 0x2;
	mem8[0x4DDC] = 0xFF;
	mem8[0x4DDD] = 0xF;
	mem8[0x4DDE] = 0x40;
	mem8[0x4DDF] = 0x3B;
	mem8[0x4DE0] = 0xE8;
	mem8[0x4DE1] = 0xDA;
	mem8[0x4DE2] = 0x5C;
	mem8[0x4DE3] = 0x11;
	mem8[0x4DE4] = 0x1;
	mem8[0x4DE6] = 0x5C;
	mem8[0x4DE7] = 0x11;
	mem8[0x4DE8] = 0x3;
	mem8[0x4DE9] = 0x0;
	mem8[0x4DEA] = 0x5C;
	mem8[0x4DEB] = 0x11;
	mem8[0x4DEC] = 0x7;
	mem8[0x4DED] = 0x0;
	mem8[0x4DEE] = 0x5C;
	mem8[0x4DEF] = 0x11;
	mem8[0x4DF0] = 0x9;
	mem8[0x4DF1] = 0x0;
	mem8[0x4DF2] = 0x1C;
	mem8[0x4DF3] = 0x30;
	mem8[0x4DF4] = 0x40;
	mem8[0x4DF5] = 0x11;
	mem8[0x4DF6] = 0xD;
	mem8[0x4DF7] = 0x0;
	mem8[0x4DF8] = 0x5C;
	mem8[0x4DF9] = 0x11;
	mem8[0x4DFA] = 0xF;
	mem8[0x4DFB] = 0x0;
	mem8[0x4DFC] = 0x5C;
	mem8[0x4DFD] = 0x11;
	mem8[0x4DFE] = 0x11;
	mem8[0x4E00] = 0x5C;
	mem8[0x4E01] = 0x11;
	mem8[0x4E02] = 0x17;
	mem8[0x4E04] = 0x5C;
	mem8[0x4E05] = 0x11;
	mem8[0x4E06] = 0x19;
	mem8[0x4E07] = 0x0;
	mem8[0x4E08] = 0x5C;
	mem8[0x4E09] = 0x11;
	mem8[0x4E0A] = 0x13;
	mem8[0x4E0B] = 0x0;
	mem8[0x4E0C] = 0x5C;
	mem8[0x4E0D] = 0x11;
	mem8[0x4E0E] = 0x15;
	mem8[0x4E0F] = 0x0;
	mem8[0x4E10] = 0x7C;
	mem8[0x4E11] = 0x11;
	mem8[0x4E12] = 0x0;
	mem8[0x4E14] = 0x1F;
	mem8[0x4E16] = 0x75;
	mem8[0x4E17] = 0x4E;
	// Sprites
	mem8[0x14CA0] = 0x90;
	mem8[0x14CA3] = 0x0;
	mem8[0x14CB0] = 0x90;
	mem8[0x14CB3] = 0x40;
	mem8[0x14F68] = 0xFC;
	mem8[0x14F69] = 0x28;
	mem8[0x14F6A] = 0x0;
	mem8[0x14F6D] = 0x1;

	kabuki_setup(punisher_decode);
	init_cps1();
}

void cps_state::init_sf2h9()
{
	/* Patch out protection check */
	uint16_t *rom = (uint16_t *)memregion("maincpu")->base();
	rom[0xc0670/2] = 0x4e71;
	init_cps1();
}

void cps_state::init_sf2h13()
{
	uint16_t *rom = (uint16_t *)memregion("maincpu")->base();

	// Fix scroll
	rom[0x1d22a/2] = 0x0120;
	// Fix bg layer
	rom[0x1d270/2] = 0x0166;
	// Fix gfx
	rom[0x1d470/2] = 0x0170;

	// Fix title gfx
	rom[0x21bec/2] = 0x0083;
	rom[0x21cf8/2] = 0x828e;
	rom[0x21cfa/2] = 0x829e;
	rom[0x21cfc/2] = 0x82ae;
	rom[0x21d06/2] = 0x827f;
	rom[0x21d08/2] = 0x828f;
	rom[0x21d0a/2] = 0x829f;
	rom[0x21d0c/2] = 0x82af;
	rom[0x21d16/2] = 0x827e;
	rom[0x21d18/2] = 0x82a0;
	rom[0x21d1a/2] = 0x822c;
	rom[0x21d1c/2] = 0x823c;
	rom[0x21d2a/2] = 0x822d;

	init_cps1();
}

void cps_state::init_wofb()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Fix gfx
	mem8[0x506] = 0xE7;
	mem8[0x507] = 0x48;
	mem8[0x508] = 0xFE;
	mem8[0x509] = 0xFF;
	mem8[0x50A] = 0xF8;
	mem8[0x50B] = 0x4B;
	mem8[0x6ABC] = 0x6;
	mem8[0x6ABD] = 0x1;
	// Fix sound
	mem8[0x764E] = 0x71;
	mem8[0x7650] = 0x71;
	mem8[0x7651] = 0x4E;
	// Fix screen transitions
	mem8[0x5D236] = 0xFC;
	mem8[0x5D237] = 0x28;
	mem8[0x5D238] = 0x0;
	mem8[0x5D23B] = 0x1;

	kabuki_setup(wof_decode);
	init_cps1();
}

void cps_state::init_sk2h35()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Patch Q sound protection? check
	mem8[0x5A1A] = 0x00;
	mem8[0x5A1B] = 0x67;
	mem8[0x5A1C] = 0x56;
	mem8[0x5A1D] = 0x00;
	mem8[0x5A1E] = 0x7C;
	mem8[0x5A1F] = 0x20;
	mem8[0x5A20] = 0xF1;
	mem8[0x5A21] = 0x00;
	mem8[0x5A22] = 0x00;
	mem8[0x5A23] = 0x80;
	mem8[0x5A24] = 0x28;
	mem8[0x5A25] = 0x4A;
	mem8[0x5A26] = 0x1F;
	mem8[0x5A27] = 0x00;
	mem8[0x5A28] = 0x00;
	mem8[0x5A29] = 0x6A;
	mem8[0x5A40] = 0x5C;
	mem8[0x5A41] = 0x11;
	mem8[0x5A42] = 0x01;
	mem8[0x5A43] = 0x00;
	mem8[0x5A44] = 0x5C;
	mem8[0x5A45] = 0x11;
	mem8[0x5A46] = 0x03;
	mem8[0x5A47] = 0x00;
	mem8[0x5A4A] = 0x07;
	mem8[0x5A4B] = 0x00;
	mem8[0x5A4C] = 0x5C;
	mem8[0x5A4D] = 0x11;
	mem8[0x5A4E] = 0x09;
	mem8[0x5A4F] = 0x00;
	mem8[0x5A50] = 0x5C;
	mem8[0x5A51] = 0x31;
	mem8[0x5A52] = 0x0C;
	mem8[0x5A53] = 0x00;
	mem8[0x5A54] = 0x5C;
	mem8[0x5A55] = 0x11;
	mem8[0x5A56] = 0x0F;
	mem8[0x5A57] = 0x00;
	mem8[0x5A58] = 0x5C;
	mem8[0x5A59] = 0x11;
	mem8[0x72A6] = 0x71;
	mem8[0x72A7] = 0x4E;
	mem8[0x72A8] = 0x71;
	mem8[0x72A9] = 0x4E;
	mem8[0x72AA] = 0x71;
	mem8[0x72AB] = 0x4E;
	mem8[0x72AC] = 0x71;
	mem8[0x72AD] = 0x4E;
	mem8[0x72AE] = 0x71;
	mem8[0x72AF] = 0x4E;
	mem8[0x72B0] = 0x71;
	mem8[0x72B1] = 0x4E;
	mem8[0x72B2] = 0x39;
	mem8[0x72B3] = 0x30;
	mem8[0x72B4] = 0xF1;
	mem8[0x72B5] = 0x00;
	mem8[0x72B6] = 0xFE;
	mem8[0x72B7] = 0x9F;
	mem8[0x72B8] = 0x00;
	mem8[0x72B9] = 0x0C;
	/* enable coin slots 1 and 2 */
	mem8[0x71bc] = 0x0c;
	kabuki_setup(wof_decode);
	init_cps1();
}

void cps_state::init_sk2h1q()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Stage Order
	mem8[0x72a6] = 0x00;
	// Disable Sprite Recoding
	mem8[0x5d858] = 0x00;
	mem8[0x5d859] = 0x61;
	mem8[0x5d85a] = 0xe6;
	mem8[0x5d85b] = 0x01;
	mem8[0x5d890] = 0x6d;
	mem8[0x5d891] = 0x0c;
	mem8[0x5d892] = 0x00;
	mem8[0x5d893] = 0x90;
	mem8[0x5d894] = 0xd2;
	mem8[0x5d895] = 0xe3;
	mem8[0x5d8e8] = 0x90;
	mem8[0x5d8e9] = 0x00;
	mem8[0x5d8ea] = 0x00;
	mem8[0x5d8eb] = 0x00;
	mem8[0x5d8f8] = 0x90;
	mem8[0x5d8f9] = 0x00;
	mem8[0x5d8fa] = 0x00;
	mem8[0x5d8fb] = 0x40;
	// Patch protection? check
	mem8[0xf11ec] = 0x71;
	mem8[0xf11ed] = 0x4e;
	mem8[0xf11ee] = 0x71;
	mem8[0xf11ef] = 0x4e;
	// Patch Q sound protection? check
	mem8[0x5A0E] = 0x39;
	mem8[0x5A0F] = 0x30;
	mem8[0x5A10] = 0xF1;
	mem8[0x5A12] = 0xFE;
	mem8[0x5A13] = 0x9F;
	mem8[0x5A14] = 0x00;
	mem8[0x5A15] = 0x0C;
	mem8[0x5A16] = 0x77;
	mem8[0x5A17] = 0x00;
	mem8[0x5A18] = 0xF4;
	mem8[0x5A19] = 0x66;
	mem8[0x5A1A] = 0xF9;
	mem8[0x5A1B] = 0x4E;
	mem8[0x5A1C] = 0x00;
	mem8[0x5A1E] = 0xB2;
	mem8[0x5A1F] = 0x72;
	mem8[0x5A20] = 0x7C;
	mem8[0x5A21] = 0x20;
	mem8[0x5A22] = 0xF1;
	mem8[0x5A23] = 0x00;
	mem8[0x5A24] = 0x00;
	mem8[0x5A25] = 0x80;
	mem8[0x5A26] = 0x7C;
	mem8[0x5A27] = 0x11;
	mem8[0x5A29] = 0x00;
	mem8[0x5A2A] = 0x01;
	mem8[0x5A2C] = 0x7C;
	mem8[0x5A2D] = 0x11;
	mem8[0x5A2E] = 0x10;
	mem8[0x5A2F] = 0x00;
	mem8[0x5A30] = 0x0F;
	mem8[0x5A31] = 0x00;
	mem8[0x5A32] = 0x7C;
	mem8[0x5A33] = 0x11;
	mem8[0x5A34] = 0x00;
	mem8[0x5A35] = 0x00;
	mem8[0x5A36] = 0x07;
	mem8[0x5A38] = 0x7C;
	mem8[0x5A39] = 0x11;
	mem8[0x5A3A] = 0x00;
	mem8[0x5A3B] = 0x00;
	mem8[0x5A3C] = 0x09;
	mem8[0x5A3D] = 0x00;
	mem8[0x5A3E] = 0x7C;
	mem8[0x5A3F] = 0x11;
	mem8[0x5A40] = 0x00;
	mem8[0x5A41] = 0x00;
	mem8[0x5A42] = 0x0C;
	mem8[0x5A44] = 0x41;
	mem8[0x5A48] = 0x7C;
	mem8[0x5A4A] = 0x00;
	mem8[0x5A4C] = 0x11;
	mem8[0x5A4D] = 0x00;
	mem8[0x5A4E] = 0x7C;
	mem8[0x5A4F] = 0x11;
	mem8[0x5A50] = 0x00;
	mem8[0x5A51] = 0x00;
	mem8[0x5A52] = 0x17;
	mem8[0x5A54] = 0x7C;
	mem8[0x5A56] = 0x00;
	mem8[0x5A58] = 0x19;
	mem8[0x5A59] = 0x00;
	mem8[0x5A5A] = 0x7C;
	mem8[0x5A5B] = 0x11;
	mem8[0x5A5C] = 0x00;
	mem8[0x5A5D] = 0x00;
	mem8[0x5A5E] = 0x13;
	mem8[0x5A60] = 0x7C;
	mem8[0x5A62] = 0x00;
	mem8[0x5A64] = 0x15;
	mem8[0x5A65] = 0x00;
	mem8[0x5A66] = 0x7C;
	mem8[0x5A67] = 0x11;
	mem8[0x5A68] = 0x00;
	mem8[0x5A69] = 0x00;
	mem8[0x5A6A] = 0x1F;
	mem8[0x5A6C] = 0xF9;
	mem8[0x5A6D] = 0x4E;
	mem8[0x5A6E] = 0x05;
	mem8[0x5A70] = 0x2C;
	mem8[0x5A71] = 0xE8;
	mem8[0x729A] = 0xF9;
	mem8[0x729C] = 0x00;
	mem8[0x729D] = 0x00;
	mem8[0x729E] = 0x0E;
	mem8[0x729F] = 0x5A;
	mem8[0x5E826] = 0xF9;
	mem8[0x5E827] = 0x4E;
	mem8[0x5E828] = 0x00;
	mem8[0x5E82A] = 0x20;
	mem8[0x5E82B] = 0x5A;
	kabuki_setup(wof_decode);
	init_cps1();
}

void cps_state::init_sk2h1()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Stage Order
	mem8[0x72a6] = 0x00;
	// Disable Sprite Recoding
	mem8[0x5d858] = 0x00;
	mem8[0x5d859] = 0x61;
	mem8[0x5d85a] = 0xe6;
	mem8[0x5d85b] = 0x01;
	mem8[0x5d890] = 0x6d;
	mem8[0x5d891] = 0x0c;
	mem8[0x5d892] = 0x00;
	mem8[0x5d893] = 0x90;
	mem8[0x5d894] = 0xd2;
	mem8[0x5d895] = 0xe3;
	mem8[0x5d8e8] = 0x90;
	mem8[0x5d8e9] = 0x00;
	mem8[0x5d8ea] = 0x00;
	mem8[0x5d8eb] = 0x00;
	mem8[0x5d8f8] = 0x90;
	mem8[0x5d8f9] = 0x00;
	mem8[0x5d8fa] = 0x00;
	mem8[0x5d8fb] = 0x40;
	// Patch protection? check
	mem8[0xf11ec] = 0x71;
	mem8[0xf11ed] = 0x4e;
	mem8[0xf11ee] = 0x71;
	mem8[0xf11ef] = 0x4e;
	init_cps1();
}

void cps_state::init_sk2h3()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Disable Sprite Recoding
	mem8[0x5d858] = 0x00;
	mem8[0x5d859] = 0x61;
	mem8[0x5d85a] = 0xe6;
	mem8[0x5d85b] = 0x01;
	mem8[0x5d890] = 0x6d;
	mem8[0x5d891] = 0x0c;
	mem8[0x5d892] = 0x00;
	mem8[0x5d893] = 0x90;
	mem8[0x5d894] = 0xd2;
	mem8[0x5d895] = 0xe3;
	mem8[0x5d8e8] = 0x90;
	mem8[0x5d8eb] = 0x00;
	mem8[0x5d8f8] = 0x90;

	//Transitions
	//mem8[0x02449] = 0x07; // fixed by above code

	//Protections
	mem8[0x708da] = 0xff;
	mem8[0x708db] = 0xff;
	mem8[0x708dc] = 0xff;
	mem8[0x708dd] = 0xff;
	mem8[0xf11eb] = 0x60;

	//Start at stage 1
	mem8[0x072a6] = 0x00;

	init_cps1();
}

void cps_state::init_sk2h21()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Patch Q sound protection? check
	mem8[0x0554] = 0xb4;
	mem8[0x0555] = 0x54;
	mem8[0x5A50] = 0x5c;
	mem8[0x5A51] = 0x31;
	mem8[0x5A52] = 0x0c;
	mem8[0x5A53] = 0x00;
	mem8[0x5A54] = 0x5c;
	mem8[0x5A55] = 0x11;
	mem8[0x5A56] = 0x0f;
	mem8[0x5A58] = 0x5c;
	mem8[0x5A59] = 0x11;
	mem8[0x5A5A] = 0x11;
	mem8[0x5A5B] = 0x00;
	kabuki_setup(wof_decode);
	init_cps1();
}

void cps_state::init_sk2h22()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Protection
	mem8[0xE7AD0] = 0x71;
	mem8[0xE7AD1] = 0x4E;

	// Disable Sprite Recoding
	mem8[0x5de96] = 0x00;
	mem8[0x5de97] = 0x61;
	mem8[0x5de98] = 0xe6;
	mem8[0x5de99] = 0x01;
	mem8[0x5dece] = 0x6d;
	mem8[0x5decf] = 0x0c;
	mem8[0x5ded0] = 0x00;
	mem8[0x5ded1] = 0x90;
	mem8[0x5ded2] = 0xd2;
	mem8[0x5ded3] = 0xe3;
	mem8[0x5df26] = 0x90;
	mem8[0x5df29] = 0x00;
	mem8[0x5df36] = 0x90;

	init_cps1();
}

void cps_state::init_sk2h31()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Disable Sprite Recoding
	mem8[0x5de96] = 0x00;
	mem8[0x5de97] = 0x61;
	mem8[0x5de98] = 0xe6;
	mem8[0x5de99] = 0x01;
	mem8[0x5dece] = 0x6d;
	mem8[0x5decf] = 0x0c;
	mem8[0x5ded0] = 0x00;
	mem8[0x5ded1] = 0x90;
	mem8[0x5ded2] = 0xd2;
	mem8[0x5ded3] = 0xe3;
	mem8[0x5df26] = 0x90;
	mem8[0x5df29] = 0x00;
	mem8[0x5df36] = 0x90;

	// Patch Q sound protection? check
	mem8[0x5A0E] = 0x39;
	mem8[0x5A0F] = 0x30;
	mem8[0x5A10] = 0xF1;
	mem8[0x5A12] = 0xFE;
	mem8[0x5A13] = 0x9F;
	mem8[0x5A14] = 0x00;
	mem8[0x5A15] = 0x0C;
	mem8[0x5A16] = 0x77;
	mem8[0x5A17] = 0x00;
	mem8[0x5A18] = 0xF4;
	mem8[0x5A19] = 0x66;
	mem8[0x5A1A] = 0xF9;
	mem8[0x5A1B] = 0x4E;
	mem8[0x5A1C] = 0x00;
	mem8[0x5A1E] = 0xBE;
	mem8[0x5A1F] = 0x72;
	mem8[0x5A20] = 0x7C;
	mem8[0x5A21] = 0x20;
	mem8[0x5A22] = 0xF1;
	mem8[0x5A23] = 0x00;
	mem8[0x5A24] = 0x00;
	mem8[0x5A25] = 0x80;
	mem8[0x5A26] = 0x7C;
	mem8[0x5A27] = 0x11;
	mem8[0x5A29] = 0x00;
	mem8[0x5A2A] = 0x01;
	mem8[0x5A2C] = 0x7C;
	mem8[0x5A2D] = 0x11;
	mem8[0x5A2E] = 0x10;
	mem8[0x5A2F] = 0x00;
	mem8[0x5A30] = 0x0F;
	mem8[0x5A31] = 0x00;
	mem8[0x5A32] = 0x7C;
	mem8[0x5A33] = 0x11;
	mem8[0x5A34] = 0x00;
	mem8[0x5A35] = 0x00;
	mem8[0x5A36] = 0x07;
	mem8[0x5A38] = 0x7C;
	mem8[0x5A39] = 0x11;
	mem8[0x5A3A] = 0x00;
	mem8[0x5A3B] = 0x00;
	mem8[0x5A3C] = 0x09;
	mem8[0x5A3D] = 0x00;
	mem8[0x5A3E] = 0x7C;
	mem8[0x5A3F] = 0x11;
	mem8[0x5A40] = 0x00;
	mem8[0x5A41] = 0x00;
	mem8[0x5A42] = 0x0C;
	mem8[0x5A44] = 0x41;
	mem8[0x5A48] = 0x7C;
	mem8[0x5A4A] = 0x00;
	mem8[0x5A4C] = 0x11;
	mem8[0x5A4D] = 0x00;
	mem8[0x5A4E] = 0x7C;
	mem8[0x5A4F] = 0x11;
	mem8[0x5A50] = 0x00;
	mem8[0x5A51] = 0x00;
	mem8[0x5A52] = 0x17;
	mem8[0x5A54] = 0x7C;
	mem8[0x5A56] = 0x00;
	mem8[0x5A58] = 0x19;
	mem8[0x5A59] = 0x00;
	mem8[0x5A5A] = 0x7C;
	mem8[0x5A5B] = 0x11;
	mem8[0x5A5C] = 0x00;
	mem8[0x5A5D] = 0x00;
	mem8[0x5A5E] = 0x13;
	mem8[0x5A60] = 0x7C;
	mem8[0x5A62] = 0x00;
	mem8[0x5A64] = 0x15;
	mem8[0x5A65] = 0x00;
	mem8[0x5A66] = 0x7C;
	mem8[0x5A67] = 0x11;
	mem8[0x5A68] = 0x00;
	mem8[0x5A69] = 0x00;
	mem8[0x5A6A] = 0x1F;
	mem8[0x5A6C] = 0xF9;
	mem8[0x5A6D] = 0x4E;
	mem8[0x5A6E] = 0x05;
	mem8[0x5A70] = 0x6A;
	mem8[0x5A71] = 0xEE;
	mem8[0x72A6] = 0xF9;
	mem8[0x72A8] = 0x00;
	mem8[0x72A9] = 0x00;
	mem8[0x72AA] = 0x0E;
	mem8[0x72AB] = 0x5A;
	mem8[0x5EE64] = 0xF9;
	mem8[0x5EE65] = 0x4E;
	mem8[0x5EE66] = 0x00;
	mem8[0x5EE68] = 0x20;
	mem8[0x5EE69] = 0x5A;
	kabuki_setup(wof_decode);
	init_cps1();
}

static INPUT_PORTS_START( ffightae )
	PORT_INCLUDE( cps1_3players )

	PORT_START("DSWA")
	CPS1_COINAGE_1( "SW(A)" )
	PORT_DIPNAME( 0x40, 0x40, "2 Coins to Start, 1 to Continue" )   PORT_DIPLOCATION("SW(A):7")
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(A):8" )

	PORT_START("DSWB")
	PORT_DIPNAME( 0x07, 0x04, "Difficulty Level 1" )                PORT_DIPLOCATION("SW(B):1,2,3")
	PORT_DIPSETTING(    0x07, DEF_STR( Easiest ) )      // "01"
	PORT_DIPSETTING(    0x06, DEF_STR( Easier ) )       // "02"
	PORT_DIPSETTING(    0x05, DEF_STR( Easy ) )         // "03"
	PORT_DIPSETTING(    0x04, DEF_STR( Normal ) )       // "04"
	PORT_DIPSETTING(    0x03, DEF_STR( Medium ) )       // "05"
	PORT_DIPSETTING(    0x02, DEF_STR( Hard ) )         // "06"
	PORT_DIPSETTING(    0x01, DEF_STR( Harder ) )       // "07"
	PORT_DIPSETTING(    0x00, DEF_STR( Hardest ) )      // "08"
	PORT_DIPNAME( 0x18, 0x10, "Difficulty Level 2" )                PORT_DIPLOCATION("SW(B):4,5")
	PORT_DIPSETTING(    0x18, DEF_STR( Easy ) )         // "01"
	PORT_DIPSETTING(    0x10, DEF_STR( Normal ) )       // "02"
	PORT_DIPSETTING(    0x08, DEF_STR( Hard ) )         // "03"
	PORT_DIPSETTING(    0x00, DEF_STR( Hardest ) )      // "04"
	PORT_DIPNAME( 0x60, 0x60, DEF_STR( Bonus_Life ) )               PORT_DIPLOCATION("SW(B):6,7")
	PORT_DIPSETTING(    0x60, "100k" )
	PORT_DIPSETTING(    0x40, "200k" )
	PORT_DIPSETTING(    0x20, "100k and every 200k" )
	PORT_DIPSETTING(    0x00, DEF_STR( None ) )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(B):8" )

	PORT_START("DSWC")
	PORT_DIPNAME( 0x03, 0x03, DEF_STR( Lives ) )                    PORT_DIPLOCATION("SW(C):1,2")
	PORT_DIPSETTING(    0x00, "1" )
	PORT_DIPSETTING(    0x03, "2" )
	PORT_DIPSETTING(    0x02, "3" )
	PORT_DIPSETTING(    0x01, "4" )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Free_Play ) )                PORT_DIPLOCATION("SW(C):3")
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, "Freeze" )                            PORT_DIPLOCATION("SW(C):4")
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Flip_Screen ) )              PORT_DIPLOCATION("SW(C):5")
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x00, DEF_STR( Demo_Sounds ) )              PORT_DIPLOCATION("SW(C):6")
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Allow_Continue ) )           PORT_DIPLOCATION("SW(C):7")
	PORT_DIPSETTING(    0x40, DEF_STR( No ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Yes ) )
	PORT_DIPNAME( 0x80, 0x80, "Game Mode")                          PORT_DIPLOCATION("SW(C):8")
	PORT_DIPSETTING(    0x80, "Game" )
	PORT_DIPSETTING(    0x00, DEF_STR( Test ) )
INPUT_PORTS_END



ROM_START( cps1frog )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "frog30-36.bin",  0x00000, 0x20000, CRC(8eb8ddbe) SHA1(298c72b3eb6f2721f204cf80ec4a7c52dc8b23fd) )
	ROM_LOAD16_BYTE( "frog35-42.bin",  0x00001, 0x20000, CRC(acb5a988) SHA1(7264bb94f7bacef9bf03713d0a6d32e81ca1f8e2) )
	ROM_LOAD16_WORD_SWAP( "frog32-32m.bin", 0x80000, 0x80000, CRC(75660aac) SHA1(6a521e1d2a632c26e53b83d2cc4b0edecfc1e68c) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "frog05-05m.bin", 0x000000, 0x80000, CRC(7bbc4b54) SHA1(5a40bd85ce71dc733071732a8306d648b3e6dd39) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "frog07-07m.bin", 0x000002, 0x80000, CRC(0beadd80) SHA1(f43d6ad936b8ffa242c17d8da26bf2e2a12d85a8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "frog01-01m.bin", 0x000004, 0x80000, CRC(f84d02bb) SHA1(b89322ab65a3b3e8202c27af62de2b182a4ed2e9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "frog03-03m.bin", 0x000006, 0x80000, CRC(d784a5b0) SHA1(8891bb8fc39f51db200c51e2a65961c351d655c2) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "frog09-09.bin",   0x00000, 0x08000, CRC(3ac7fb5c) SHA1(01057078b67dc82d80403533a3dca3deb95f166c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "frog18-18.bin",  0x00000, 0x20000, CRC(65d1ef07) SHA1(0bc2dbf5053430f659d64d1b287799bb5cc4db65) )
	ROM_LOAD( "frog19-19.bin",  0x20000, 0x20000, CRC(7ee8cdcd) SHA1(67dfd19f3eb3649d6f3f6631e44d0bd36b8d8d19) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "cps1frog.key", 0x00, 0x80, CRC(3adeff30) SHA1(5d242a4e5edcf47905fb50d767d41c2977bfd78b) )
ROM_END

ROM_START( pnicku )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pnij_36.12f",  0x00000, 0x20000, CRC(2d4ffb2b) SHA1(6e49cf89a36834fd1de8b4b860fe66f3d7d67a84) )
	ROM_LOAD16_BYTE( "pnicku.42",    0x00001, 0x20000, CRC(22d20227) SHA1(a103c9b1f6134c529405bd258da9f601c1459c47) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "pnij_09.4b",  0x000000, 0x20000, CRC(48177b0a) SHA1(eba5de6cd9bb0c4ad76a13bddc9cdeb2e4380122) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_01.4a",  0x000001, 0x20000, CRC(01a0f311) SHA1(9bcd8716f90ccd410543ffcdc5c2916077b8d4c3) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_13.9b",  0x000002, 0x20000, CRC(406451b0) SHA1(5a7a7fecba7de8b8cf4a284b2ae7adae901623f6) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_05.9a",  0x000003, 0x20000, CRC(8c515dc0) SHA1(aa1e13cf9e7cf0458bb5c4332b1ea73034f9a874) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_26.5e",  0x000004, 0x20000, CRC(e2af981e) SHA1(3c2b28b4a4d457aa94a760dfca0181a9f050c319) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_18.5c",  0x000005, 0x20000, CRC(f17a0e56) SHA1(7c89aca230f176e12f995892f9d1bce22c57fbdf) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_38.8h",  0x000006, 0x20000, CRC(eb75bd8c) SHA1(2129460e06eb64019fc5f7eab6334ff43229b995) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_32.8f",  0x000007, 0x20000, CRC(84560bef) SHA1(9e94ae434b50ecf82781080e11d0c4741e992d0d) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_10.5b",  0x100000, 0x20000, CRC(c2acc171) SHA1(7c86db3f2acca1252d403c5f12c871d0357fa109) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_02.5a",  0x100001, 0x20000, CRC(0e21fc33) SHA1(c4a29d45c4257c8871038d3c9b13140e874db0c1) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_14.10b", 0x100002, 0x20000, CRC(7fe59b19) SHA1(a273b8b8fbfd5d31d25479a9ede09ce35e1cc873) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_06.10a", 0x100003, 0x20000, CRC(79f4bfe3) SHA1(bc17cc1c8535e3d202588893713926b6c06f92fd) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_27.7e",  0x100004, 0x20000, CRC(83d5cb0e) SHA1(44c93fa5eedcafc8dc6d88ee827c6cadc9c671f0) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_19.7c",  0x100005, 0x20000, CRC(af08b230) SHA1(a3b5b3013012efa1860699648518f8d8031c5f30) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_39.9h",  0x100006, 0x20000, CRC(70fbe579) SHA1(b5b7ed5588ecd884b20dd50bfc5385a9af03c5d8) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_33.9f",  0x100007, 0x20000, CRC(3ed2c680) SHA1(0afe84d8d89f8d45afc79f6172337e622e29a8a2) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "pnij_17.13b",  0x00000, 0x08000, CRC(e86f787a) SHA1(de04cbe89c655faf04afe169bfd9913049ccc4a8) )
	ROM_CONTINUE(             0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "pnij_24.12c",  0x00000, 0x20000, CRC(5092257d) SHA1(95dc9d10940653b2fb37baf5c1ed27145b02104e) )
	ROM_LOAD( "pnij_25.13c",  0x20000, 0x20000, CRC(22109aaa) SHA1(cf21e75674d81b2daae2083d02f9f4b6e52722c6) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "pnickj.key", 0x00, 0x80, CRC(38afadc4) SHA1(05b49635f99e7cb97a99b9666239d68154cb3641) )
ROM_END

ROM_START( sk2h103 ) // same as MAME sgyxz - here until it gets fixed
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sgyxz_prg2.bin", 0x000000, 0x20000, CRC(95429c83) SHA1(e981624d018132e5625a66113b6ac4fc44e55cf7) )
	ROM_CONTINUE( 0x80000, 0x20000 )
	ROM_CONTINUE( 0x40000, 0x20000 )
	ROM_CONTINUE( 0xc0000, 0x20000 )
	ROM_LOAD16_BYTE( "sgyxz_prg1.bin", 0x000001, 0x20000, CRC(d8511929) SHA1(4de9263778f327693f4d1e21b48e43806f673487) )
	ROM_CONTINUE( 0x80001, 0x20000 )
	ROM_CONTINUE( 0x40001, 0x20000 )
	ROM_CONTINUE( 0xc0001, 0x20000 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD("sgyx-1.160",    0x000000, 0x80000, CRC(a60be9f6) SHA1(2298a4b6a2c83b76dc106a1efa19606b298d378a), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD("sgyx-2.160",    0x000002, 0x80000, CRC(6ad9d048) SHA1(d47212d28d0a1ce349e4c59e5d0d99c541b3458e), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x20000, "audiocpu", 0 )
	ROM_LOAD( "sgyxz_snd2.bin", 0x00000, 0x10000,  CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) )
	ROM_RELOAD(           0x8000, 0x10000 )

	ROM_REGION( 0x040000, "oki", 0 )
	ROM_LOAD( "sgyxz_snd1.bin", 0x00000, 0x40000,  CRC(c15ac0f2) SHA1(8d9e5519d9820e4ac4f70555088c80e64d052c9d) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sk2h101.key",     0x00, 0x80, CRC(679300a3) SHA1(f3e8197955f6b2b54493a449386b804b0d5e15ed) ) // OK
ROM_END

HACK( 2006, cps1frog,    0,        cps1frog,   cps1frog, cps_state, cps1,     ROT0,   "Rastersoft", "Frog Feast (CPS1)", MACHINE_SUPPORTS_SAVE )
HACK( 1994, pnicku,      pnickj,   cps1_10MHz, pnicku,   cps_state, cps1,     ROT0,   "Creamymami[EGCG]", "Pnickies (This Edition Is Just A Regional USA Version)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sk2h103,     wof,      sk2h3,      sk2h3,    cps_state, sk2h3,    ROT0,   "All-In Co Ltd", "Sangokushi II (set H3)", MACHINE_SUPPORTS_SAVE )

/**************
 Three Wonders
***************/

ROM_START( 3wondershack01 ) //3wondersu
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "rte_hack01.11f", 0x00000, 0x20000, CRC(772b1217) SHA1(813d64fd85a9ed0aa52a184ce6ee381c681b7d27) )
	ROM_LOAD16_BYTE( "rte_hack01.11h", 0x00001, 0x20000, CRC(Cac5db10) SHA1(30f3eab4449e352aa98480d1526ba89efade2ff7) )
	ROM_LOAD16_BYTE( "rte_31a.12f", 0x40000, 0x20000, CRC(32835e5e) SHA1(9ec530561030a75a1283ff2aacc21e55613b682b) )
	ROM_LOAD16_BYTE( "rte_hack01.12h", 0x40001, 0x20000, CRC(A0c32403) SHA1(8cd43f894ae7a01b78ec94b9b1dfd4dc10b43c3c) )
	ROM_LOAD16_BYTE( "rt_28a.9f",   0x80000, 0x20000, CRC(054137c8) SHA1(e4c406e0a32198323a5931093fbaa6836510b8ad) )
	ROM_LOAD16_BYTE( "rt_33a.9h",   0x80001, 0x20000, CRC(7264cb1b) SHA1(b367acb9f6579569321ecaa98a14e29dd775b9db) )
	ROM_LOAD16_BYTE( "rte_29a.10f", 0xc0000, 0x20000, CRC(cddaa919) SHA1(0c98e95ad5033d2c5ade7651243e7ccdb4e35463) )
	ROM_LOAD16_BYTE( "rte_34a.10h", 0xc0001, 0x20000, CRC(ed52e7e5) SHA1(352433ae484967d26376141e3a8a0f968b98fde6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "rt-5m.7a",  0x000000, 0x80000, CRC(86aef804) SHA1(723927ef3bf992d12395c52db051ece7bf57d5e5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-7m.9a",  0x000002, 0x80000, CRC(4f057110) SHA1(b7d35c883a74cf4bfb242d9f15a0e40ed1ec111f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-1m.3a",  0x000004, 0x80000, CRC(902489d0) SHA1(748ba416a8b9343059a3e7d8b93f02162feb1d0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-3m.5a",  0x000006, 0x80000, CRC(e35ce720) SHA1(6c1a87a1f819bdc20408b5a7823cf35a79d34110) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-6m.8a",  0x200000, 0x80000, CRC(13cb0e7c) SHA1(e429d594d9a7ff4cc6306e2796a9d6ad0fa25569) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-8m.10a", 0x200002, 0x80000, CRC(1f055014) SHA1(d64f5be9bb2ef761ca9b2e797dbc3554cf996a79) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-2m.4a",  0x200004, 0x80000, CRC(e9a034f4) SHA1(deb4cb5886705380b57d4fe9b9bf3c032e1d6227) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-4m.6a",  0x200006, 0x80000, CRC(df0eea8b) SHA1(5afa05654cccb0504bd44569d42fd68f08fd172f) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "rt_9.12b",   0x00000, 0x08000, CRC(abfca165) SHA1(428069d3bdc45775854cd0e8abe447f134fe5492) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "rt_18.11c",  0x00000, 0x20000, CRC(26b211ab) SHA1(0ea03fdd9edff41eacfc52aa9e0421c10968356b) )
	ROM_LOAD( "rt_19.12c",  0x20000, 0x20000, CRC(dbe64ad0) SHA1(09f2ad522fe75d7bcca094b8c6696c3733b539d5) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "3wonders.key", 0x00, 0x80, CRC(4ff53ff9) SHA1(95e1d3a9e69c6f11a11b3eebeccd4ce2d237e350) )
ROM_END

/********
 bootleg
**********/

ROM_START( 3wondrud )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "3wondrud.30", 0x00000, 0x20000, CRC(b0953ff4) SHA1(79d0b68948a9b5be8eacd33810ddcf4fa08dbe71) )
	ROM_LOAD16_BYTE( "3wondrud.35", 0x00001, 0x20000, CRC(7695e8c6) SHA1(f78e7cb1098d77ce84d58a0d4509a77f5c483a77) )
	ROM_LOAD16_BYTE( "3wondrud.31", 0x40000, 0x20000, CRC(8cf00a3c) SHA1(dceb5bccf7c96802e7c228ea52f82fbb49388e0d) )
	ROM_LOAD16_BYTE( "3wondrud.36", 0x40001, 0x20000, CRC(b649ad19) SHA1(f91dad60a583a46f80e71bb23bfd051b3ed3fbe5) )
	ROM_LOAD16_BYTE( "rt_28a.9f",   0x80000, 0x20000, CRC(054137c8) SHA1(e4c406e0a32198323a5931093fbaa6836510b8ad) )
	ROM_LOAD16_BYTE( "rt_33a.9h",   0x80001, 0x20000, CRC(7264cb1b) SHA1(b367acb9f6579569321ecaa98a14e29dd775b9db) )
	ROM_LOAD16_BYTE( "rtu_29a.10f", 0xc0000, 0x20000, CRC(37ba3e20) SHA1(a128b1a17639b06a4fd8acffe0357f1dbd1d4fe9) )
	ROM_LOAD16_BYTE( "rtu_34a.10h", 0xc0001, 0x20000, CRC(f99f46c0) SHA1(cda24a6baa3f861e7078fb2fa91328cc1cddc866) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "rt-5m.7a",  0x000000, 0x80000, CRC(86aef804) SHA1(723927ef3bf992d12395c52db051ece7bf57d5e5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-7m.9a",  0x000002, 0x80000, CRC(4f057110) SHA1(b7d35c883a74cf4bfb242d9f15a0e40ed1ec111f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-1m.3a",  0x000004, 0x80000, CRC(902489d0) SHA1(748ba416a8b9343059a3e7d8b93f02162feb1d0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-3m.5a",  0x000006, 0x80000, CRC(e35ce720) SHA1(6c1a87a1f819bdc20408b5a7823cf35a79d34110) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-6m.8a",  0x200000, 0x80000, CRC(13cb0e7c) SHA1(e429d594d9a7ff4cc6306e2796a9d6ad0fa25569) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-8m.10a", 0x200002, 0x80000, CRC(1f055014) SHA1(d64f5be9bb2ef761ca9b2e797dbc3554cf996a79) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-2m.4a",  0x200004, 0x80000, CRC(e9a034f4) SHA1(deb4cb5886705380b57d4fe9b9bf3c032e1d6227) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-4m.6a",  0x200006, 0x80000, CRC(df0eea8b) SHA1(5afa05654cccb0504bd44569d42fd68f08fd172f) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "rt_9.12b",   0x00000, 0x08000, CRC(abfca165) SHA1(428069d3bdc45775854cd0e8abe447f134fe5492) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "rt_18.11c",  0x00000, 0x20000, CRC(26b211ab) SHA1(0ea03fdd9edff41eacfc52aa9e0421c10968356b) )
	ROM_LOAD( "rt_19.12c",  0x20000, 0x20000, CRC(dbe64ad0) SHA1(09f2ad522fe75d7bcca094b8c6696c3733b539d5) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "3wondrud.key", 0x00, 0x80, CRC(5066be6f) SHA1(a514ffb7561b1d563382c4c69e24c81574902081) )
ROM_END

ROM_START( 3wondersha ) // same as 3wondersh except for program roms
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "b01.22",      0x00000, 0x40000, CRC(8eb6b675) SHA1(835a777af57579e80d0800b5e86bed01ee5168a3) )
	ROM_LOAD16_BYTE( "b01.26",      0x00001, 0x40000, CRC(ab2d0699) SHA1(f2d7bb4b94fba398d3d896683264fc6828d1de5c) )
	ROM_LOAD16_BYTE( "b01.23",      0x80000, 0x40000, CRC(74db820f) SHA1(5980998ad3d25e417bb74020a1867207aaa6a0b1) )
	ROM_LOAD16_BYTE( "b01.27",      0x80001, 0x40000, CRC(c75e807b) SHA1(9baacd6183e66c4c655c9e32d1858898434f2b87) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "16.bin",    0x000000, 0x40000, CRC(c997bca2) SHA1(6b6cd9c2fc56690c42a3368cd5e6c98d6bff5b5b) , ROM_SKIP(7) )
	ROMX_LOAD( "6.bin",     0x000001, 0x40000, CRC(3eea321a) SHA1(4368aaf8a532c29f4b950adb2daedd3069d84cf1) , ROM_SKIP(7) )
	ROMX_LOAD( "18.bin",    0x000002, 0x40000, CRC(98acdfd4) SHA1(910dfd6742e166530388c700c0797e692e501f97) , ROM_SKIP(7) )
	ROMX_LOAD( "8.bin",     0x000003, 0x40000, CRC(dc9ca6f9) SHA1(77549e9a128d1b7ca0c4547cdc56f43450d426e0) , ROM_SKIP(7) )
	ROMX_LOAD( "12.bin",    0x000004, 0x40000, CRC(0d8a6007) SHA1(48d61cbd91df01ba4b2f0e80e60375a50ddb065e) , ROM_SKIP(7) )
	ROMX_LOAD( "2.bin",     0x000005, 0x40000, CRC(d75563b9) SHA1(7b7b105b84dc5d7b17838961fdd8be5bac90cbc6) , ROM_SKIP(7) )
	ROMX_LOAD( "14.bin",    0x000006, 0x40000, CRC(84369a28) SHA1(3877186371fe289522133fd99be034b141a974ca) , ROM_SKIP(7) )
	ROMX_LOAD( "4.bin",     0x000007, 0x40000, CRC(d4831578) SHA1(9ff5860f22976e9e4c023946f35e24fde84fe8ea) , ROM_SKIP(7) )
	ROMX_LOAD( "17.bin",    0x200000, 0x40000, CRC(040edff5) SHA1(9747d67b980cc357c6fa732300a84ae55150bc51) , ROM_SKIP(7) )
	ROMX_LOAD( "7.bin",     0x200001, 0x40000, CRC(c7c0468c) SHA1(e7a14cf579b023e8954b7e06aa2337db4f53bedc) , ROM_SKIP(7) )
	ROMX_LOAD( "19.bin",    0x200002, 0x40000, CRC(9fef114f) SHA1(394afb083ce7c46d9a39097d0040f9e18aaab508) , ROM_SKIP(7) )
	ROMX_LOAD( "9.bin",     0x200003, 0x40000, CRC(48cbfba5) SHA1(74047433e50795e29d8299526ae2c424610f0a5e) , ROM_SKIP(7) )
	ROMX_LOAD( "13.bin",    0x200004, 0x40000, CRC(8fc3d7d1) SHA1(e2784e0fccfe062ea8dc440e4a884fc665f4a846) , ROM_SKIP(7) )
	ROMX_LOAD( "3.bin",     0x200005, 0x40000, CRC(c65e9a86) SHA1(359ab1e2dd0fcf38ed9815a6a50294cbeca8223c) , ROM_SKIP(7) )
	ROMX_LOAD( "15.bin",    0x200006, 0x40000, CRC(f239341a) SHA1(b1858f5f7a5d210c5327b84a797ed7e898250596) , ROM_SKIP(7) )
	ROMX_LOAD( "5.bin",     0x200007, 0x40000, CRC(947ac944) SHA1(d962f49ba532fc60209bb3957ff8a456855ef67f) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "rt_9.12b",   0x00000, 0x08000, CRC(abfca165) SHA1(428069d3bdc45775854cd0e8abe447f134fe5492) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "rt_18.11c",  0x00000, 0x20000, CRC(26b211ab) SHA1(0ea03fdd9edff41eacfc52aa9e0421c10968356b) )
	ROM_LOAD( "rt_19.12c",  0x20000, 0x20000, CRC(dbe64ad0) SHA1(09f2ad522fe75d7bcca094b8c6696c3733b539d5) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "3wonders.key", 0x00, 0x80, CRC(4ff53ff9) SHA1(95e1d3a9e69c6f11a11b3eebeccd4ce2d237e350) )
ROM_END

 /****************
 Captain Commando
*******************/

ROM_START( captcommhack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_23d_hack01.8f", 0x000000, 0x80000, CRC(a5e73e49) SHA1(7bb75fa0e1122a85a421c50607c0ad57a387783e) )
	ROM_LOAD16_WORD_SWAP( "cc_22d_hack01.7f", 0x080000, 0x80000, CRC(919777c5) SHA1(2bd9b1527e8486ae89ddcdb0694c63c5859080b6) )
	ROM_LOAD16_BYTE( "cc_24d_hack01.9e", 0x100000, 0x20000, CRC(f3d6f147) SHA1(937822148c0f6f295d468024ce7887ee0353e669) )
	ROM_LOAD16_BYTE( "cc_28d_hack01.9f", 0x100001, 0x20000, CRC(f1c9bf8a) SHA1(545f494106ccce6ccbbe6fa042cf0ee6df03e8dc) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",     0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",     0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",     0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",     0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m_hack01.7a",   0x200000, 0x80000, CRC(e4282bc0) SHA1(fe6012a8afcaec5747194bedfa73284bb28300a4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m_hack01.9a",   0x200002, 0x80000, CRC(8b0ef34c) SHA1(13a696856432b2f345cd2b2059e95179c78bd70a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m_hack01.8a",   0x200004, 0x80000, CRC(2d7bee50) SHA1(a25bcfa99c4dda52469f7dc8fec24287c97deb84) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m_hack01.10a",   0x200006, 0x80000, CRC(0106bf6a) SHA1(8e23418c58c4ffb8dd4dac93b92b23c406d60a62) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",    0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",    0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",    0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_23d_hack02.rom",  0x000000, 0x80000, CRC(d97f921c) SHA1(451ab11ddd845ecddeaf60b3c46903d784c3389c) )
	ROM_LOAD16_WORD_SWAP( "cc_22d.7f",   0x080000, 0x80000, CRC(a91949b7) SHA1(c027af89cd8f6bd3aaed61114582322c42e0c74f) )
	ROM_LOAD16_BYTE( "cc_24d.9e",        0x100000, 0x20000, CRC(680e543f) SHA1(cfa963ab6329f615807db213bf53841860ed3149) )
	ROM_LOAD16_BYTE( "cc_28d.9f",        0x100001, 0x20000, CRC(8820039f) SHA1(d68ce0b34ade75b8c5214168b2b1e0cdff45cd52) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",   0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",   0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",   0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",   0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",   0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",   0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",   0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a",   0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",     0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",     0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",     0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_23d_hack03.8f", 0x000000, 0x80000, CRC(7ce0e051) SHA1(b8bdd1f4869ebb4f22ee188b208c8bf4a6a259e2) )
	ROM_LOAD16_WORD_SWAP( "cc_22d_hack03.7f",  0x080000, 0x80000, CRC(af6b49e8) SHA1(67be16bf54fbdf0aad6a5a4ce1a67eb3067c4c70) )
	ROM_LOAD16_BYTE( "cc_24d.9e",       0x100000, 0x20000, CRC(680e543f) SHA1(cfa963ab6329f615807db213bf53841860ed3149) )
	ROM_LOAD16_BYTE( "cc_28d.9f",       0x100001, 0x20000, CRC(8820039f) SHA1(d68ce0b34ade75b8c5214168b2b1e0cdff45cd52) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_23d_hack04.8f", 0x000000, 0x80000, CRC(e0b6eead) SHA1(1a58ecf473068e7ca6c32a50e59f7d3b22d5aed4) )
	ROM_LOAD16_WORD_SWAP( "cc_22f.7f",  0x080000, 0x80000, CRC(0fd34195) SHA1(fb2b9a53af43507f13c4f94eaebbf0b538b2e754) )
	ROM_LOAD16_BYTE( "cc_24d_hack04.9e",       0x100000, 0x20000, CRC(73a20e9d) SHA1(4c7310601dc509880e5fc4a4deaea9aa7a5ca6d6) )
	ROM_LOAD16_BYTE( "cc_28d_hack04.9f",       0x100001, 0x20000, CRC(437b346e) SHA1(b6c3d16a0caaeee566fadcc8346cfaffd014e21c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack05 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_23d_hack05.8f", 0x000000, 0x80000, CRC(f9d3ae1a) SHA1(b849160deeb8f5976bde9f6fb2b13cdaad0ea922) )
	ROM_LOAD16_WORD_SWAP( "cc_22f.7f",  0x080000, 0x80000, CRC(0fd34195) SHA1(fb2b9a53af43507f13c4f94eaebbf0b538b2e754) )
	ROM_LOAD16_BYTE( "cc_24d_hack05.9e",       0x100000, 0x20000, CRC(ce9af515) SHA1(05167d05a0bfe898a14457e58b82a3c90cc6438e) )
	ROM_LOAD16_BYTE( "cc_28d_hack05.9f",       0x100001, 0x20000, CRC(4ea6d4bd) SHA1(2361940aec4f101230747e844bb2d3cc3974da7e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack06 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_23d_hack06.8f", 0x000000, 0x80000, CRC(a9a6c9fd) SHA1(882c965b8767f7c5c5cfd4b0101fad1ab748cb0e) )
	ROM_LOAD16_WORD_SWAP( "cc_22d.7f",  0x080000, 0x80000, CRC(a91949b7) SHA1(c027af89cd8f6bd3aaed61114582322c42e0c74f) )
	ROM_LOAD16_BYTE( "cc_24d.9e",       0x100000, 0x20000, CRC(680e543f) SHA1(cfa963ab6329f615807db213bf53841860ed3149) )
	ROM_LOAD16_BYTE( "cc_28d.9f",       0x100001, 0x20000, CRC(8820039f) SHA1(d68ce0b34ade75b8c5214168b2b1e0cdff45cd52) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack07 ) //captcommr1bs
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack07.10f", 0x000000, 0x300000, CRC(3edc20bc) SHA1(fbdeaa2992c8e757650158ea1e8eeda2045b9ab7) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack08 ) //captcommzj
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_23d_hack08.8f", 0x000000, 0x80000, CRC(9014983d) SHA1(0204ff69f36c7f44188260ee28759ce1cdd80a77) )
	ROM_LOAD16_WORD_SWAP( "cc_22d_hack08.7f",  0x080000, 0x80000, CRC(00af068d) SHA1(d7017ede0a224390b0c85e894b219fe8109d1800) )
	ROM_LOAD16_BYTE( "cc_24d_hack08.9e",       0x100000, 0x20000, CRC(936ed25e) SHA1(fda6d96102a1720b361fb7ae1ffb88fc01c0cc83) )
	ROM_LOAD16_BYTE( "cc_28d_hack08.9f",       0x100001, 0x20000, CRC(c3448a39) SHA1(fe64bc3781752cbd2d9ac24bd43507ec400ec2f4) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack09 ) //captcommr1v4
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack09.10f", 0x000000, 0x300000, CRC(1fad7219) SHA1(d902b9816ca77e526e810d2b7329414fdfa3cb9c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack10 ) //captcommr1zs
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack10.10f", 0x000000, 0x302532, CRC(2ed24fe0) SHA1(2c7af8f71c4d30739145af6b316a391393d1321b) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack11 ) //captcommr1p
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack11.10f", 0x000000, 0x302532, CRC(9e90ca66) SHA1(d60b2d658dd8773b2c818d1cf07b48bb88ff9aa2) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack12 )  // captcommrds, captcommr1ws
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP("cc_28d_hack12.10f", 0x000000, 0x300000, CRC(79780368) SHA1(01677f68c04067a11f122c2f82e9fd213521910b) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack13 )  // captcommr1pwx
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP("cc_28d_hack13.10f", 0x000000, 0x302532, CRC(c60301c8) SHA1(25022c93ee29909fd00a40b3f31fc7147290b8d9) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack14 ) //captcommr1zt
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack14.10f", 0x000000, 0x300000, CRC(da6bb97d) SHA1(d46471bc33697fe2f31d4d594fb0881b64b0daad) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack15 ) //captcommr2y
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack15.10f", 0x000000, 0x3024FA, CRC(c012cd1e) SHA1(b9ea9e81c5fda6addd79a4fe0f7bdb5c7aa8d659) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack16 ) //captcommr1jy
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack16.10f", 0x000000, 0x300000, CRC(d10acced) SHA1(5175da267c3ccd4b45225027e9a3b6d763c5b2d6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack17 ) //captcommr1pmy
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack17.10f", 0x000000, 0x3024FA, CRC(a87eb50a) SHA1(7fdb9cc76b6d79d0e63d994dc400c5703019454c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack18 ) //captcommr1zs
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack18.10f", 0x000000, 0x302532, CRC(511fff26) SHA1(39bad01c2e11ccd049659be52f4f3586a748fd46) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhack19 ) //captcommr1ds
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hack19.10f", 0x000000, 0x300000, CRC(579521ce) SHA1(a3d680a05fef91de307171e1e15dfa10d52188cf) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

 /*******
 bootleg
**********/

ROM_START( captcoud )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP("captcoud.23", 0x000000, 0x80000, CRC(1d338c25) SHA1(4aba7e5a78bf20d887b3493e0d2a83098f877f9f) )
	ROM_LOAD16_WORD_SWAP("captcoud.22", 0x080000, 0x80000, CRC(c5310f13) SHA1(97a3751630f10cf67515200ce435c34fda1d9a52) )
	ROM_LOAD16_BYTE( "ccu_24b.9e",      0x100000, 0x20000, CRC(84ff99b2) SHA1(5b02c91f3d0f8fb46db9596136b683f5a22dc15f) )
	ROM_LOAD16_BYTE( "ccu_28b.9f",      0x100001, 0x20000, CRC(fbcec223) SHA1(daf484baece5b3a11f3dcabb758b8bdd736a1fb6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "captcoud.key", 0x00, 0x80, CRC(6a4c8ad9) SHA1(56912fc3387cf977e602d3e8dad31b64dadc6b4a) )
ROM_END

/***************
 Dai Makai-Mura
*****************/

/********
 bootleg
**********/

ROM_START( daimakaib )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "dmjb2.bin", 0x00000, 0x80000, CRC(7d5f9f84) SHA1(b334b3af610892ef4efe4764017659b8541a10c6) )
	ROM_LOAD16_BYTE( "dmjb1.bin", 0x00001, 0x80000, CRC(9b945cc4) SHA1(dfdfabfd8ef06cee6be27350f79c5db4c6ace611) )

	ROM_REGION( 0x300000, "gfx", 0 )
	ROMX_LOAD( "dm_02.4b",  0x000000, 0x20000, CRC(8b98dc48) SHA1(e827881e2ba5cccd907d1692a1945c1b75d46f12) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_01.4a",  0x000001, 0x20000, CRC(80896c33) SHA1(20ffc427c596828005e34cdd8e4efa0d332262e9) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_10.9b",  0x000002, 0x20000, CRC(c2e7d9ef) SHA1(52aae6cf373f8c7150833047be28b74dd5eb5af6) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_09.9a",  0x000003, 0x20000, CRC(c9c4afa5) SHA1(34571e3e49c86b87fa34eefbc5f9fe258aba5f1a) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_18.5e",  0x000004, 0x20000, CRC(1aa0db99) SHA1(69ac302b2f6f0b96f78cb57b0b4cdae464086262) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_17.5c",  0x000005, 0x20000, CRC(dc6ed8ad) SHA1(1ffc4a48a7ff9b542ab6f63a60bea3c1a7a6e63b) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_30.8h",  0x000006, 0x20000, CRC(d9d3f8bd) SHA1(6c6853a384f8d60ca46a0607fd47c76a83700fba) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_29.8f",  0x000007, 0x20000, CRC(49a48796) SHA1(76c18c684dba4aa91ee6caae0f38fe3e1cc50832) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_04.5b",  0x100000, 0x20000, CRC(a4f4f8f0) SHA1(edca0f61b40a18afe279f7007c233064130cfb4f) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_03.5a",  0x100001, 0x20000, CRC(b1033e62) SHA1(547fc281dd9e7a74ac86c3692508c7bde9b6167b) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_12.10b", 0x100002, 0x20000, CRC(10fdd76a) SHA1(aee774d6323292799dff7a30ef9559c92fe5507a) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_11.10a", 0x100003, 0x20000, CRC(9040cb04) SHA1(b32e9056fc20a5162868eade10f3ef5efc167a28) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_20.7e",  0x100004, 0x20000, CRC(281d0b3e) SHA1(70e1813de184ad0ec164145b7b843b5e387494e3) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_19.7c",  0x100005, 0x20000, CRC(2623b52f) SHA1(fc4200924452bfbff687934782398ed345dc0aa0) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_32.9h",  0x100006, 0x20000, CRC(99692344) SHA1(67dc70618568b7c0adcb00a612aaf5501f6c8c0f) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_31.9f",  0x100007, 0x20000, CRC(54acb729) SHA1(d1fca43db36253fd19db4337c49272a6cadff597) , ROM_SKIP(7) )
	ROMX_LOAD( "09.4a",     0x200000, 0x10000, CRC(ae24bb19) SHA1(aa91c6ffe657b878e10e4e930457b530f7bb529b) , ROM_SKIP(7) )
	ROMX_LOAD( "18.7a",     0x200001, 0x10000, CRC(d34e271a) SHA1(55211fc2861dce32951f41624c9c99c09bf3b184) , ROM_SKIP(7) )
	ROMX_LOAD( "13.4e",     0x200002, 0x10000, CRC(3f70dd37) SHA1(9ecb4dec9d131e9fca15ded7d71986a9fcb62c19) , ROM_SKIP(7) )
	ROMX_LOAD( "22.7e",     0x200003, 0x10000, CRC(7e69e2e6) SHA1(4e0b4d2474beaa5c869c8f1a91893c79ac6e7f39) , ROM_SKIP(7) )
	ROMX_LOAD( "11.4c",     0x200004, 0x10000, CRC(37c9b6c6) SHA1(b2bb82537e335339846dbf9588cfacfdbdd75ee6) , ROM_SKIP(7) )
	ROMX_LOAD( "20.7c",     0x200005, 0x10000, CRC(2f1345b4) SHA1(14c450abcf9defa29c6f48e5ffd0b9d1e4a66a1d) , ROM_SKIP(7) )
	ROMX_LOAD( "15.4g",     0x200006, 0x10000, CRC(3c2a212a) SHA1(f8fa0e0e2d09ea37c54d1c2493752b4e97e3f534) , ROM_SKIP(7) )
	ROMX_LOAD( "24.7g",     0x200007, 0x10000, CRC(889aac05) SHA1(9301dcecee699e7f7672bb498122e1f4831ce536) , ROM_SKIP(7) )
	ROMX_LOAD( "10.4b",     0x280000, 0x10000, CRC(bcc0f28c) SHA1(02f587aa4ae71631f27b0e3aaf1829cdded1bdc2) , ROM_SKIP(7) )
	ROMX_LOAD( "19.7b",     0x280001, 0x10000, CRC(2a40166a) SHA1(dc4e75d7ed87ae5386d721a09113bba364740465) , ROM_SKIP(7) )
	ROMX_LOAD( "14.4f",     0x280002, 0x10000, CRC(20f85c03) SHA1(86385139a9b42270aade758bfe338525936f5671) , ROM_SKIP(7) )
	ROMX_LOAD( "23.7f",     0x280003, 0x10000, CRC(8426144b) SHA1(2dbf9625413b302fcdad5bef8733a9dfbfaead52) , ROM_SKIP(7) )
	ROMX_LOAD( "12.4d",     0x280004, 0x10000, CRC(da088d61) SHA1(67229eff2827a42af97a60ceb252e132e7f307bc) , ROM_SKIP(7) )
	ROMX_LOAD( "21.7d",     0x280005, 0x10000, CRC(17e11df0) SHA1(42fb15e9300b07fc5f4bc21744484869859b130c) , ROM_SKIP(7) )
	ROMX_LOAD( "16.4h",     0x280006, 0x10000, CRC(f187ba1c) SHA1(6d9441d04ecef2a9d9c7a2cc7781acd7904c2061) , ROM_SKIP(7) )
	ROMX_LOAD( "25.7h",     0x280007, 0x10000, CRC(29f79c78) SHA1(26000a58454a06c3016f99ebc3a79c52911a7070) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "26.10a",     0x00000, 0x08000, CRC(3692f6e5) SHA1(61b8438d60a39b4cf5062dff0a53228e8a4e4b5f) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", ROMREGION_ERASEFF ) // to keep validation quiet

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "daimakb.key", 0x00, 0x80, CRC(c72cad61) SHA1(9036e06c84ff9189a83acd50a703fb6560ce5e98) )
ROM_END


/************************
 Cadillacs And Dinosaurs
**************************/

ROM_START( dinohack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack01.23", 0x000000, 0x80000, CRC(39ebeee2) SHA1(b48c3174e4ca26517958b3e58a3a693ce4e9ee88) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack01.22", 0x080000, 0x80000, CRC(09307e79) SHA1(cff0af94c6118a852351a7b624db65963c91f577) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack01.21", 0x100000, 0x80000, CRC(c2a0f051) SHA1(57e4a569824fb2a9d726ba610d13e451ab0b36cb) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack02.8f", 0x000000, 0x80000, CRC(a461dceb) SHA1(47496c09c27d7d630c8e4d7d53728f80f7eb9b5a) )
	ROM_LOAD16_WORD_SWAP( "cde_22a.7f", 0x080000, 0x80000, CRC(9278aa12) SHA1(58cbbd53a98abe640ccb233f8dbd8ca6d63475e7) )
	ROM_LOAD16_WORD_SWAP( "cde_21a.6f", 0x100000, 0x80000, CRC(66d23de2) SHA1(19b8a365f630411d524d055459020f4c8cf930f1) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack03.8f", 0x000000, 0x80000, CRC(0967584e) SHA1(a126d63e8d7ae89446c49a4d72648d5db9e584b4) )
	ROM_LOAD16_WORD_SWAP( "cde_22a.7f", 0x080000, 0x80000, CRC(9278aa12) SHA1(58cbbd53a98abe640ccb233f8dbd8ca6d63475e7) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack03.6f", 0x100000, 0x80000, CRC(b2a7cf75) SHA1(ea3a75144afb49fcd1a17226758810a55ae81f3b) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack04.8f", 0x000000, 0x80000, CRC(700105a1) SHA1(78e4b85bba154e3c788d853d9d3d0ffca55425c6) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack04.7f", 0x080000, 0x80000, CRC(ca1e9b0b) SHA1(62e8d82ec5f24e31467ecdf729f74e19ec5bf14b) )
	ROM_LOAD16_WORD_SWAP( "cde_21a.6f", 0x100000, 0x80000, CRC(66d23de2) SHA1(19b8a365f630411d524d055459020f4c8cf930f1) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack05 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kl2-r1.800",  0x080000, 0x080000, CRC(4c70dca7) SHA1(2e7a10c90924e0f87903eddb04313f61233a998f) )
	ROM_CONTINUE(               0x000000, 0x080000 )
	ROM_LOAD16_WORD_SWAP( "kl2-l2.800",  0x180000, 0x080000, CRC(c6ae7338) SHA1(4b8543cf1ac89ae95fe63e6d81c87d2bda52da69) )
	ROM_CONTINUE(               0x100000, 0x080000 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-a.161",   0x000000, 0x80000, CRC(4eb40692) SHA1(9d4bfc574c1e07d1569821e8053a7208ff83cbd1), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "cd-b.161",   0x000002, 0x80000, CRC(8a6920d8) SHA1(099bfc37b524f60c82332c83c3f1af411b14e35a), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinoh.key", 0x00, 0x80, CRC(67862673) SHA1(9ae7446231da7fd6355e1f22ac3fb974c3775600) )
ROM_END

ROM_START( dinohack06 ) //dinoslicews
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack06.10f", 0x000000, 0x200000, CRC(5fb39c2a) SHA1(2783c3011f7178f6bc0f88edfef221f525055a1f) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack07 )
	ROM_REGION( 0x12A08B8, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack07.8f", 0x000000, 0x78045C, CRC(45710f71) SHA1(a03df947d2cecbf9d7d638a763ef34f3507001e8) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack07.7f", 0x080000, 0x600117, CRC(3d7446f8) SHA1(8c1dc95ecdfaf53008e57a128c4701283547d76d) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack07.6f", 0x100000, 0x4A0345, CRC(973d7d2b) SHA1(ca956bb6fcea7af3111afa347092747b6c9dcac5) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack07.5f", 0x180000, 0x80000, CRC(1825ad2c) SHA1(a5a9d3786f16945bf0274b1afb4b197a5e2082fe) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack08 ) //dinohc
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack08.8f",  0x000000, 0x80000, CRC(8060821e) SHA1(9c3c986e4d9111b48195fe926f421c159ecd210d) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack08.7f",  0x080000, 0x80000, CRC(dcf68fb2) SHA1(e4b39cdf74152c4f6563ffa3f2f56e5984bc5bb3) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack08.6f",  0x100000, 0x80000, CRC(de0ed00d) SHA1(eedd03b3e0dead9f2cb45deb0c30593e4fa10a7c) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack08.5f",  0x180000, 0x80000, CRC(0bb2d85d) SHA1(99f4f10a4c2a19e09a0b7c4fd171cdbc42a2cd70) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m_hack08.3a",  0x000000, 0x80000, CRC(8318c1de) SHA1(102c4ce5ef3cfb5b0f93190e6b563ca322310edd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m_hack08.5a",  0x000002, 0x80000, CRC(2461424d) SHA1(6bd933f5cada64671e3a401681724f075f6c260c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m_hack08.4a",  0x000004, 0x80000, CRC(6cbac29d) SHA1(676893882172f8b9a281c887750387a683e09bb8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m_hack08.6a",  0x000006, 0x80000, CRC(2aa8bdd3) SHA1(5dca5d59ebefe0cb36101ea8f5f82550fe1f93b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m_hack08.7a",  0x200000, 0x80000, CRC(175d0862) SHA1(7ade0f1d7b2625e3bd0e8ceef5b41b91d90435c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m_hack08.9a",  0x200002, 0x80000, CRC(59c069b4) SHA1(9ff3abd0312545186c4c17f037174957df90a398) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m_hack08.8a",  0x200004, 0x80000, CRC(31d2b4e9) SHA1(e3242b62f6bfa9a4133a7ccd85d0cd5c41b2cea1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m_hack08.10a", 0x200006, 0x80000, CRC(c923b1b8) SHA1(60bc73b5ca94dc45aef3f440e96b16bfc4b83271) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinoh.key", 0x00, 0x80, CRC(67862673) SHA1(9ae7446231da7fd6355e1f22ac3fb974c3775600) )
ROM_END

ROM_START( dinohack09 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack09.10f", 0x000000, 0x200000, CRC(506e0655) SHA1(526999d9f05a7a668e98ebbdb7343681b90eced4) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m_hack08.3a",  0x000000, 0x80000, CRC(8318c1de) SHA1(102c4ce5ef3cfb5b0f93190e6b563ca322310edd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m_hack08.5a",  0x000002, 0x80000, CRC(2461424d) SHA1(6bd933f5cada64671e3a401681724f075f6c260c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m_hack08.4a",  0x000004, 0x80000, CRC(6cbac29d) SHA1(676893882172f8b9a281c887750387a683e09bb8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m_hack08.6a",  0x000006, 0x80000, CRC(2aa8bdd3) SHA1(5dca5d59ebefe0cb36101ea8f5f82550fe1f93b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m_hack08.7a",  0x200000, 0x80000, CRC(175d0862) SHA1(7ade0f1d7b2625e3bd0e8ceef5b41b91d90435c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m_hack08.9a",  0x200002, 0x80000, CRC(59c069b4) SHA1(9ff3abd0312545186c4c17f037174957df90a398) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m_hack08.8a",  0x200004, 0x80000, CRC(31d2b4e9) SHA1(e3242b62f6bfa9a4133a7ccd85d0cd5c41b2cea1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m_hack08.10a", 0x200006, 0x80000, CRC(c923b1b8) SHA1(60bc73b5ca94dc45aef3f440e96b16bfc4b83271) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack10 ) //dinotfzn
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack10.8f", 0x000000, 0x80000, CRC(0122db0a) SHA1(a50692e9fa21ff8b103bf0a0d0738b14325e285e) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack10.7f", 0x080000, 0x80000, CRC(c52c8b29) SHA1(bddc409ab95d9b709c68543c9b1c05f3ad283be4) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack10.6f", 0x100000, 0x80000, CRC(40c8621c) SHA1(e6f82ff3cdad75afc56f430e698f55e2d93d796b) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack11 ) //dinodyws
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack11.10f", 0x000000, 0x200000, CRC(74cdb28a) SHA1(ff2604a43fcb2dc4750b94d06eb325463c35d403) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack12 ) //dinoaddx3
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack12.10f", 0x000000, 0x200000, CRC(66b16979) SHA1(5653f3c8d742e59348e6a885c96620d2f07dd4ea) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m_hack08.3a",  0x000000, 0x80000, CRC(8318c1de) SHA1(102c4ce5ef3cfb5b0f93190e6b563ca322310edd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m_hack08.5a",  0x000002, 0x80000, CRC(2461424d) SHA1(6bd933f5cada64671e3a401681724f075f6c260c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m_hack08.4a",  0x000004, 0x80000, CRC(6cbac29d) SHA1(676893882172f8b9a281c887750387a683e09bb8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m_hack08.6a",  0x000006, 0x80000, CRC(2aa8bdd3) SHA1(5dca5d59ebefe0cb36101ea8f5f82550fe1f93b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m_hack12.7a",  0x200000, 0x80000, CRC(91888b4f) SHA1(e90cfcc4e18eff39000fbab28fab447196ec2ea5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m_hack12.9a",  0x200002, 0x80000, CRC(cb47177d) SHA1(5dc9d9b0e0be1665379a9f7f7cc4c37969959233) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m_hack12.8a",  0x200004, 0x80000, CRC(1b335cb9) SHA1(7b9103858a0627b0f46ec06c13c600513d492c33) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m_hack12.10a", 0x200006, 0x80000, CRC(a16fa3cf) SHA1(83edecfe0d009867b7a81218a1b4112f5bd788c4) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack13 ) //dinovr
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack13.10f", 0x000000, 0x200000, CRC(58d419b9) SHA1(80286030a664c6a801d827acc61d123bed725718) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack14 ) //dino7s
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack14.8f", 0x000000, 0x80000,  CRC(894b3f34) SHA1(c382c1b566e48bb08d1a054dc1b6345a3dca1462) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack14.7f", 0x080000, 0x80000,  CRC(c14680e6) SHA1(6fe25b6325e56ba4b2f6eac9d2c5ccb8607af60e) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack14.6f", 0x100000, 0x80000,  CRC(abda9f74) SHA1(d38ed99209c7b6431fa7ab4ded8e402a72b80254) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack14.5f", 0x180000, 0x400000, CRC(77b3d3c4) SHA1(05c26e8c5bc2e4d91307925a4dbb86a15fb7bebd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack15 ) //dinotxj, dinojps
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack15.8f", 0x000000, 0x80000, CRC(30e2827b) SHA1(6a014f6a325e79bbbcceb3d6bd0b73cbe48d0413) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack15.7f", 0x080000, 0x80000, CRC(94204e86) SHA1(e8dd4dbe8ce98704fd4dd4beffa423e9c63562b6) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack15.6f", 0x100000, 0x80000, CRC(cda75e95) SHA1(e1a6d3ca7d9144756ad10e21a4ad5478b41dc5d8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack16 ) //dinoslice
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack16.8f",  0x000000, 0x80000, CRC(9a19333d) SHA1(92c877c679dc4a5c8ef63864e3db0adb8511f0f5) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack16.7f",  0x080000, 0x80000, CRC(93e99b5b) SHA1(690dc5461d3a107c0ee0252a3d41abfa1cff3645) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack16.6f",  0x100000, 0x80000, CRC(09404458) SHA1(253b5eeb517f9682202110425e3859eb6e18ded5) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack16.5f",  0x180000, 0x80000, CRC(a0ecf669) SHA1(456b68a9b2291b025467fe316d2b2b3d289a3175) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack17 ) //dino2017cws, dinozjws
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack17.8f", 0x000000, 0x80000, CRC(0a2b6206) SHA1(9100670f71c5311468f9015b08cc8647f14563c3) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack17.7f", 0x080000, 0x80000, CRC(c67101e1) SHA1(158231a04b1255b0744cbb278f52a98e81e36094) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack17.6f", 0x100000, 0x80000, CRC(b8d4f296) SHA1(d03436b18372f36a0ecb27c55739cc9b75779585) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack18 ) //dinoyzlb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack18.8f", 0x000000, 0x80000, CRC(0df71e03) SHA1(37e7acf8bb9e9e8c6559f25a4ae77454be0f2a23) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack18.7f", 0x080000, 0x80000, CRC(64e8ebbc) SHA1(da41b84fc845e0e0a8dde9d0c9e97684981c148b) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack18.6f", 0x100000, 0x80000, CRC(61abf526) SHA1(34efd7b40b4d9377bac58705bbae23eb25150df4) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack19 ) //dinoaddx5
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack19.10f", 0x000000, 0x180000, CRC(afc2afaf) SHA1(92bc4150a680771bdfa6af484b9ff1a749f35e21) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack20 ) //dino2011ws2
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack20.10f", 0x000000, 0x200000, CRC(6e7907ee) SHA1(101db27cf7768f8986e3cfbef59a74af2759addd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack21 ) //dino2015ws
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack21.8f", 0x000000, 0x80000, CRC(22a63a9f) SHA1(0bae4d528983361c2a9171112ed860cc42cdaeff) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack21.7f", 0x080000, 0x80000, CRC(10c16933) SHA1(4256170cd6a69a2d4e5ff598c35e813190f6c5b0) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack21.6f", 0x100000, 0x80000, CRC(9a532f75) SHA1(c9997938d4b1b66208541d49c4b9ea67a867a109) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m_hack21.3a",  0x000000, 0x80000, CRC(da7d2d64) SHA1(a26a327eac6c0668da1e75d95335640db390bae6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m_hack21.5a",  0x000002, 0x80000, CRC(a6444fa8) SHA1(b41ef65927c42b42bbd06fb932dd9ea6c3d57f5f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m_hack21.4a",  0x000004, 0x80000, CRC(5e11285e) SHA1(8421ce6e4947b6ea28a4d407ff3e6e2da47bf502) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m_hack21.6a",  0x000006, 0x80000, CRC(a97b4a24) SHA1(58f7af720d3319bf091123704a07c02ca92ab6f9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m_hack08.7a",  0x200000, 0x80000, CRC(175d0862) SHA1(7ade0f1d7b2625e3bd0e8ceef5b41b91d90435c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m_hack08.9a",  0x200002, 0x80000, CRC(59c069b4) SHA1(9ff3abd0312545186c4c17f037174957df90a398) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m_hack08.8a",  0x200004, 0x80000, CRC(31d2b4e9) SHA1(e3242b62f6bfa9a4133a7ccd85d0cd5c41b2cea1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m_hack08.10a", 0x200006, 0x80000, CRC(c923b1b8) SHA1(60bc73b5ca94dc45aef3f440e96b16bfc4b83271) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack22 ) //dinotb
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack22.10f", 0x000000, 0x200000, CRC(9d7669ad) SHA1(af771653b128b1fbdf73fa8312fffda9546ccef8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "u1",   0x000000, 0x80000, CRC(a01a9fb5) SHA1(d1ab4c7ead04932c60923363a0a661d0d1472aaa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u2",   0x000002, 0x80000, CRC(bdf02c17) SHA1(046ba4c589a22a7ac65c86baaae18eff0bff6ecb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u3",   0x000004, 0x80000, CRC(058beefa) SHA1(0d09ab5a200643b5a16e0313228f7ea243752bd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u4",   0x000006, 0x80000, CRC(5028a9f1) SHA1(ff3a988153860e76beb79918ad896e702c3ecd3d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u5",   0x200000, 0x80000, CRC(d77f89ea) SHA1(1dd8c2a18742fd8483ecade31aed384c686ed244) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u6",   0x200002, 0x80000, CRC(bfbcb034) SHA1(c1eb4d420b10ffa05197d9a82c7adac4d265c546) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u7",   0x200004, 0x80000, CRC(a2544d4e) SHA1(def704055e041bc7c3b8cf7977249b69aa7924a8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u8",   0x200006, 0x80000, CRC(8869bbb1) SHA1(e53f77baffb913bf3ef5396d84fbfbaec6a90ca2) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack23 ) //dinoxa
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack23.8f", 0x000000, 0x80000, CRC(e15c6b88) SHA1(bb78979d2a776134f5b4f53c3247807992e4653b) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack23.7f", 0x080000, 0x80000, CRC(3e8d0903) SHA1(073203c83d730c0203224dd1c54474ddbea0f409) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack23.6f", 0x100000, 0x80000, CRC(6c1a4291) SHA1(2b6cbb7a7fb9b3f072e57bd8a3721170834f5bb4) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m_hack21.3a",  0x000000, 0x80000, CRC(da7d2d64) SHA1(a26a327eac6c0668da1e75d95335640db390bae6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m_hack21.5a",  0x000002, 0x80000, CRC(a6444fa8) SHA1(b41ef65927c42b42bbd06fb932dd9ea6c3d57f5f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m_hack21.4a",  0x000004, 0x80000, CRC(5e11285e) SHA1(8421ce6e4947b6ea28a4d407ff3e6e2da47bf502) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m_hack21.6a",  0x000006, 0x80000, CRC(a97b4a24) SHA1(58f7af720d3319bf091123704a07c02ca92ab6f9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m_hack08.7a",  0x200000, 0x80000, CRC(175d0862) SHA1(7ade0f1d7b2625e3bd0e8ceef5b41b91d90435c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m_hack08.9a",  0x200002, 0x80000, CRC(59c069b4) SHA1(9ff3abd0312545186c4c17f037174957df90a398) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m_hack08.8a",  0x200004, 0x80000, CRC(31d2b4e9) SHA1(e3242b62f6bfa9a4133a7ccd85d0cd5c41b2cea1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m_hack08.10a", 0x200006, 0x80000, CRC(c923b1b8) SHA1(60bc73b5ca94dc45aef3f440e96b16bfc4b83271) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack24 ) //dinoxc
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack24.8f", 0x000000, 0x80000, CRC(a5c8cd20) SHA1(2f2cbca0013058b8bfbc2695a234c11a934b9d35) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack24.7f", 0x080000, 0x80000, CRC(3a8ed567) SHA1(fc064de6a82f199669eb329294a972027e43b58a) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack24.6f", 0x100000, 0x80000, CRC(74c155b8) SHA1(46dbdfd56a50cc1bea23311d5b6c6f4c11a72817) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "u1",   0x000000, 0x80000, CRC(a01a9fb5) SHA1(d1ab4c7ead04932c60923363a0a661d0d1472aaa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u2",   0x000002, 0x80000, CRC(bdf02c17) SHA1(046ba4c589a22a7ac65c86baaae18eff0bff6ecb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u3",   0x000004, 0x80000, CRC(058beefa) SHA1(0d09ab5a200643b5a16e0313228f7ea243752bd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u4",   0x000006, 0x80000, CRC(5028a9f1) SHA1(ff3a988153860e76beb79918ad896e702c3ecd3d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u5",   0x200000, 0x80000, CRC(d77f89ea) SHA1(1dd8c2a18742fd8483ecade31aed384c686ed244) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u6",   0x200002, 0x80000, CRC(bfbcb034) SHA1(c1eb4d420b10ffa05197d9a82c7adac4d265c546) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u7",   0x200004, 0x80000, CRC(a2544d4e) SHA1(def704055e041bc7c3b8cf7977249b69aa7924a8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "u8",   0x200006, 0x80000, CRC(8869bbb1) SHA1(e53f77baffb913bf3ef5396d84fbfbaec6a90ca2) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack25 ) //dinowszh
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack25.10f", 0x000000, 0x200000, CRC(3d72a7d7) SHA1(d62013ddec7fea467e9620b6619726b4a21e8be7) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack26 ) //dinoyz 
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack26.8f", 0x000000, 0x80000, CRC(28fbf3dc) SHA1(6c9c2d094b535ef73aa1628d72fbc83d6f04ab82) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack26.7f", 0x080000, 0x80000, CRC(4289a7f9) SHA1(15a8245051ff40f0c3661ce608e0b88593cf53f8) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack26.6f", 0x100000, 0x80000, CRC(7e092acb) SHA1(87afe5556af2d97c0fdce6e9bd17a2543d25d88f) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack27 ) //dino2015ws
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack27.8f", 0x000000, 0x80000, CRC(539af6b2) SHA1(3b38a9d8842a6fa6d19df6f9f09203f843941b14) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack27.7f", 0x080000, 0x80000, CRC(e9edbf6d) SHA1(16675653cf3ab38500d89d721d61b182af673d3d) )
	ROM_IGNORE( 0x3D4F47 )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack21.6f", 0x100000, 0x80000, CRC(9a532f75) SHA1(c9997938d4b1b66208541d49c4b9ea67a867a109) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack28 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kl2-r1.801",  0x080000, 0x080000, CRC(b75cbdf8) SHA1(07fdea0f63f273ead99bc61ea648d49c82142f88) )
	ROM_CONTINUE(               0x000000, 0x080000 )
	ROM_LOAD16_WORD_SWAP( "kl2-l2.801",  0x180000, 0x080000, CRC(ecd87c98) SHA1(4361ebd13890452e0c901446442cd1e3bb2bef06) )
	ROM_CONTINUE(               0x100000, 0x080000 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-a.160",   0x000000, 0x80000, CRC(7e4f9fb3) SHA1(b985d925e0fb799cdf0a671e4800961d9872cd8f), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "cd-b.160",   0x000002, 0x80000, CRC(89532d85) SHA1(6743c4d9b4407421416c13878b8a1fae097dd7a7), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinoh.key", 0x00, 0x80, CRC(67862673) SHA1(9ae7446231da7fd6355e1f22ac3fb974c3775600) )
ROM_END

ROM_START( dinohack29 ) //dinotl
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack29.8f", 0x000000, 0x80000, CRC(ecdc1734) SHA1(656e7028d0f44a31281be0fee50d467c8eaffaef) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack29.7f", 0x080000, 0x80000, CRC(291ab913) SHA1(b8b54e91d085201de60ba94378cc991e0897cfa3) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack29.6f", 0x100000, 0x80000, CRC(27b721ef) SHA1(d020ca6a31ec45ff25635d0e9d453c151d5144be) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack14.5f", 0x180000, 0x400000, CRC(77b3d3c4) SHA1(05c26e8c5bc2e4d91307925a4dbb86a15fb7bebd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack30 ) //dinoxzb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack30.8f", 0x000000, 0x80000, CRC(9916b620) SHA1(52af0720431e545a3faabe6075be54f03678966c) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack30.7f", 0x080000, 0x80000, CRC(62e4de87) SHA1(2200993e2d51aa34d81465b4ebf0a7bdae90f3c1) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack30.6f", 0x100000, 0x80000, CRC(25bbba55) SHA1(68f5169f38f7965cb07dd1d10a19de4c003670f9) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack31 ) //dinoxc
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack31.8f", 0x000000, 0x80000, CRC(2ac412a6) SHA1(69d165ca68c52197d8d3cb0db0ce86fad973045f) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack31.7f", 0x080000, 0x80000, CRC(b1c2c14d) SHA1(e1e3a4f05ed94377fbbb838e01ec214982cf5374) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack31.6f", 0x100000, 0x80000, CRC(a0411261) SHA1(b807908f14ac9667ba2226e350f322ca73ecbb79) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack32 ) //dinoxe
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack32.8f", 0x000000, 0x80000, CRC(84f81abd) SHA1(cb7a1952fe033872cc38d804a95da57888b8c00b) )
	ROM_IGNORE( 0x3D4F48 )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack32.7f", 0x080000, 0x80000, CRC(c5515fdd) SHA1(36a1e5b30b1627ffa62f9584ca0a4f9392be3789) )
	ROM_IGNORE( 0x3D4F47 )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack32.6f", 0x100000, 0x80000, CRC(d07a8a55) SHA1(9ed0ee9afc3d78a60d08bfbb2923ca7a576cba1f) )
	ROM_IGNORE( 0x3D4F48 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack33 ) //dinoaddx3,dinoadd
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack33.10f", 0x000000, 0x200000, CRC(cfea2ba9) SHA1(7557b6d724f82ba6682c51f66f1a8209963faeb4) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack34 ) //dinoxc
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack34.8f", 0x000000, 0x80000, CRC(e53bbaeb) SHA1(a6f4501b6f930577b9afc4797196b3d75467b7c3) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack34.7f", 0x080000, 0x80000, CRC(8b08ba83) SHA1(9a1b5782a24f23fb784e6988421a8c5a3707436f) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack31.6f", 0x100000, 0x80000, CRC(a0411261) SHA1(b807908f14ac9667ba2226e350f322ca73ecbb79) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack35 ) //dinoplus
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack35.8f",   0x000000, 0x80000, CRC(45e40cd0) SHA1(a2304916d167663809d8fd1c66ecb9d635b03fd1) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack35.7f",   0x080000, 0x80000, CRC(7eeff2c6) SHA1(5d1c1f5e22f067f129c5d0e480c4a0c2d9eb84af) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack35.6f",  0x100000, 0x80000, CRC(a8191282) SHA1(3f7d5716095f0ac665ab700eebf33d3ada0a47d3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack36 ) //dinotfzn
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack36.8f", 0x000000, 0x80000, CRC(6397af83) SHA1(30aa7e11124bd37b279c10d21ba3e62e6afed1e9) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack36.7f", 0x080000, 0x80000, CRC(b1980b76) SHA1(a5556c85a772e321becf21b6d5c7beb903c1c298) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack10.6f", 0x100000, 0x80000, CRC(40c8621c) SHA1(e6f82ff3cdad75afc56f430e698f55e2d93d796b) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack37 ) //dino2015ws
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack21.8f", 0x000000, 0x80000, CRC(22a63a9f) SHA1(0bae4d528983361c2a9171112ed860cc42cdaeff) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack37.7f", 0x080000, 0x80000, CRC(6ab3fd22) SHA1(bd8f6c86f43690562e4fd4140fda434d576c4093) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack21.6f", 0x100000, 0x80000, CRC(9a532f75) SHA1(c9997938d4b1b66208541d49c4b9ea67a867a109) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m_hack21.3a",  0x000000, 0x80000, CRC(da7d2d64) SHA1(a26a327eac6c0668da1e75d95335640db390bae6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m_hack21.5a",  0x000002, 0x80000, CRC(a6444fa8) SHA1(b41ef65927c42b42bbd06fb932dd9ea6c3d57f5f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m_hack21.4a",  0x000004, 0x80000, CRC(5e11285e) SHA1(8421ce6e4947b6ea28a4d407ff3e6e2da47bf502) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m_hack21.6a",  0x000006, 0x80000, CRC(a97b4a24) SHA1(58f7af720d3319bf091123704a07c02ca92ab6f9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m_hack08.7a",  0x200000, 0x80000, CRC(175d0862) SHA1(7ade0f1d7b2625e3bd0e8ceef5b41b91d90435c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m_hack08.9a",  0x200002, 0x80000, CRC(59c069b4) SHA1(9ff3abd0312545186c4c17f037174957df90a398) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m_hack08.8a",  0x200004, 0x80000, CRC(31d2b4e9) SHA1(e3242b62f6bfa9a4133a7ccd85d0cd5c41b2cea1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m_hack08.10a", 0x200006, 0x80000, CRC(c923b1b8) SHA1(60bc73b5ca94dc45aef3f440e96b16bfc4b83271) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack38 ) //dinofx
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack38.8f", 0x000000, 0x80000, CRC(0cb5a9d7) SHA1(46b46583883fabca92d89977199feb927efb55e6) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack38.7f", 0x080000, 0x80000, CRC(5a54068a) SHA1(388a7b8e86e3e10d5b4e4af16a3e3fbdb039e6f9) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack38.6f", 0x100000, 0x80000, CRC(a427860d) SHA1(3e2dcafaa7b7252b310be1a540769872bc62a47e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack39 ) //dinogch
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack39.8f", 0x000000, 0x80000, CRC(b7dcc88a) SHA1(385004149a96ca6697740ad79ef395536c850b3a) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack39.7f", 0x080000, 0x80000, CRC(05f3e44f) SHA1(b597c8c8503209b28455fddd6dcc05f4242e2149) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack39.6f", 0x100000, 0x80000, CRC(3e5ac60d) SHA1(0123c924df51bf825363745d98ab8887792520ae) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack40 ) //dinolbws
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack40.8f", 0x000000, 0x80000, CRC(2327d53e) SHA1(4bf5dc932070883ff6639ce9f5e0b4569e4ca69a) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack40.7f", 0x080000, 0x80000, CRC(8890573f) SHA1(e1dace6e304f7736944ea125401b81fac73030e3) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack40.6f", 0x100000, 0x80000, CRC(9ce27308) SHA1(704f0378e337b3c6d1c7fa297dae7302fabfaa38) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack41 ) //dinoxcxxx
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack31.8f", 0x000000, 0x80000, CRC(2ac412a6) SHA1(69d165ca68c52197d8d3cb0db0ce86fad973045f) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack41.7f", 0x080000, 0x80000, CRC(6e47d2bf) SHA1(c6916119fe64d6917c304a169a07a6d2c82e9c69) )
	ROM_IGNORE( 0x3D4F47 )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack31.6f", 0x100000, 0x80000, CRC(a0411261) SHA1(b807908f14ac9667ba2226e350f322ca73ecbb79) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack42 ) //dinoxzb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack42.8f", 0x000000, 0x80000, CRC(5f96f9e5) SHA1(6308e1d96622026e7fcccdd78c4465e3f6df4e9f) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack42.7f", 0x080000, 0x80000, CRC(61e22311) SHA1(3fc6a49505f16eaec2c268a2b6c2c98df2d9a168) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack42.6f", 0x100000, 0x80000, CRC(ecf02256) SHA1(52a5230f3334be374ed8b5f6e6d881b188120acb) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack43 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack43.10f", 0x000000, 0x400000, CRC(bd5ee2c7) SHA1(b08b2a5dc37cd047e7210612c08b19b36df3f881) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack44 )  // dinows2019
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack44.23", 0x000000, 0x080000, CRC(73f203b7) SHA1(4937c76d6b1569beea2a4418486274c97d3c7145) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack44.22", 0x080000, 0x080000, CRC(f9e264dc) SHA1(745e81cfb46cd39d596470651035ffc85a75de4b) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack44.21", 0x100000, 0x080000, CRC(94d44390) SHA1(d34e35b1c84e83e9523d1f23bea5ac3c708efbea) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack45 ) //dinoxzb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack47.23", 0x000000, 0x080000, CRC(b159f3cb) SHA1(39cedeaa6c33fca5ee25d98a3f9d043de8fe75fc) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack47.22", 0x080000, 0x080000, CRC(afecd19e) SHA1(f12c63de6b4f65d698386905bf94447c70089072) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack47.21", 0x100000, 0x080000, CRC(d5c8db31) SHA1(be9a839b026b7e39b1f3cd6dc09294cb9048f105) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack46 ) //dinozszn
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack46.23", 0x000000, 0x080000, CRC(8eb860be) SHA1(f4feb88950920b1b55f9267af7d22aec8294c63c) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack46.22", 0x080000, 0x080000, CRC(d57af24a) SHA1(a5c2a98bf386bbeabe4f31bb42185449c5b47428) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack46.21", 0x100000, 0x080000, CRC(a8b8e348) SHA1(bb013a36ca7613960cfda6a553bab9122b4a8cc4) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack47 ) //dinoqmgw
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack47.23", 0x000000, 0x080000, CRC(4a474b29) SHA1(f06fef8a9e80e78889320a4d148f8f1f36295af4) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack47.22", 0x080000, 0x080000, CRC(5b60595c) SHA1(3d7dfdabb0a3501a8fe123a22ea795449f68c366) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack47.21", 0x100000, 0x080000, CRC(c211cf2f) SHA1(d848b37861837386ddf15fb3fb4664b1a647f7bb) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack48 ) //dinoly
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack48.23", 0x000000, 0x080000, CRC(6f992901) SHA1(b825b025073ec59c1e815f10ed907904ac05aa96) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack48.22", 0x080000, 0x080000, CRC(273dacc8) SHA1(9347986594c8e3b15ac6dc4efb1aaa36a5adcd95) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack48.21", 0x100000, 0x080000, CRC(982543a0) SHA1(9ec0da9ffd7bf324cd7ab377870b025a8c20ff1e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack49 ) //dinov3p
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack49.23", 0x000000, 0x080000, CRC(3894c5d8) SHA1(122434b4dfb597ffd7df0edcbb9c3e1d50a50770) )
	ROM_LOAD16_WORD_SWAP( "cde_22a.7f", 0x080000, 0x080000, CRC(9278aa12) SHA1(58cbbd53a98abe640ccb233f8dbd8ca6d63475e7) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack49.21", 0x100000, 0x080000, CRC(7873aab5) SHA1(6ead9a63d296412672c3fcbd19ea7ce1b6780a73) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack50 ) //dinojds
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack50.10f", 0x000000, 0x400000, CRC(76828cac) SHA1(7560a40e4fe928dbbc6b61266376890010a0aa93) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack51 ) //dinojps
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack51.10f", 0x000000, 0x400000, CRC(9592c1ef) SHA1(5f8eaa0a2e5c34ecf0aad7d544a7d10b06476996) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack52 ) //dinowtw
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack52.10f", 0x000000, 0x400000, CRC(f81cb033) SHA1(d94304eca7b3f826daaf3b113db105754d4f2364) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack53 ) //dinokrf
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack53.8f", 0x000000, 0x80000, CRC(53a9283c) SHA1(164e0866fae135da91f1c5e89b67ec569fabee54) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack53.7f", 0x080000, 0x80000, CRC(e74e5ce9) SHA1(54d372cf7dd1d50cac57db32bc536523d87b9bb0) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack53.6f", 0x100000, 0x80000, CRC(29734539) SHA1(aa1a56088fac90cd3e6742bc5e66091fce6a1031) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack54 ) //dinows2020
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack54.8f",  0x000000, 0x80000, CRC(aee45975) SHA1(c092a05050a5253393710c9a38e05416d0cbf9ed) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack54.7f",  0x080000, 0x80000, CRC(44ee0a81) SHA1(7cc9bf5a002a5506d401ca16cc45b1670b5093ca) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack54.6f",  0x100000, 0x80000, CRC(c4ee3bef) SHA1(f8b3bdfc9bef3d36703bec2fd47a0855e7bf851a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack55 ) //dino18ws
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack55.8f",  0x000000, 0x80000, CRC(67d2d499) SHA1(ef0a59bd2ba8dd506cb60a69beec3a4e7fad4b7b) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack55.7f",  0x080000, 0x80000, CRC(cb80f8e3) SHA1(adeab1f44cecff02925c9ce66e55e7b62c588433) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack55.6f",  0x100000, 0x80000, CRC(cc09bfa1) SHA1(b51bf069b8ae77d1bf70f7a44714b48baf5f99d6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack56 ) //dinozsb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack56.8f", 0x000000, 0x80000, CRC(489056b9) SHA1(f30b2368a0c105afc50a638f1577ea4531d01404) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack56.7f", 0x080000, 0x80000, CRC(5c265563) SHA1(aad94536438d3bd7e98b143e85d588be83fa49eb) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack56.6f", 0x100000, 0x80000, CRC(57113f04) SHA1(2f90baf996dc6c0cda2fcaa35d058e71c66bbb10) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack57 ) //dinoxzb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack57.8f", 0x000000, 0x80000, CRC(11309818) SHA1(8d71622314a1f2a42910bf231d3d341f6f5ce870) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack57.7f", 0x080000, 0x80000, CRC(8b303c00) SHA1(a99b5fd6acc1eedce33d6247b1a465b11db69701) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack57.6f", 0x100000, 0x80000, CRC(3935013b) SHA1(89faee64f7fa851fdea68f1749b37ab43526e4f0) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack58 ) //dino99jp
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cd-d_256.800",  0x000000, 0x100000, CRC(c8427f13) SHA1(0dbf0d33f9be2c2df6b8a223253e33e3d608dc55) )
	ROM_LOAD16_WORD_SWAP( "cd-e_256.800",  0x100000, 0x100000, CRC(c38a867e) SHA1(88ec643f7501aa91ab6826e617107381a6c2760e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-a.162",   0x000000, 0x80000, CRC(3f167412) SHA1(2636065b37998d5c3008edc1c13d073305132f4f), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "cd-b.161",   0x000002, 0x80000, CRC(8a6920d8) SHA1(099bfc37b524f60c82332c83c3f1af411b14e35a), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinob.key", 0x00, 0x80, CRC(171140c4) SHA1(d1db4e37e22fa6ae03c2bca4fdb698399d98c15f) )
ROM_END

ROM_START( dinohack59 ) //dino99j
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cd-d_257.800",  0x000000, 0x100000, CRC(3f713043) SHA1(90e81c651772e895a56146c986c64ff8c35826ac) )
	ROM_LOAD16_WORD_SWAP( "cd-e_257.800",  0x100000, 0x100000, CRC(e6294edf) SHA1(4f9515e2e060dad165f6cb513baee2568c82c1be) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-a.162",   0x000000, 0x80000, CRC(3f167412) SHA1(2636065b37998d5c3008edc1c13d073305132f4f), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "cd-b.161",   0x000002, 0x80000, CRC(8a6920d8) SHA1(099bfc37b524f60c82332c83c3f1af411b14e35a), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinob.key", 0x00, 0x80, CRC(171140c4) SHA1(d1db4e37e22fa6ae03c2bca4fdb698399d98c15f) )
ROM_END

ROM_START( dinohack60 ) //dinojdb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack60.8f",  0x000000, 0x80000, CRC(5eeeb115) SHA1(4711ee294dba6d2f3964a1df6ede74a4918e6684) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack60.7f",  0x080000, 0x80000, CRC(cca22a3b) SHA1(f999b2de5d119892cf2672ed1ebe1fe196fa1c0c) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack60.6f",  0x100000, 0x80000, CRC(8dd464e3) SHA1(e1751879cf182288900d6c346462744d6eb86b7c) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack60.5f",  0x180000, 0x80000, CRC(7708d032) SHA1(8ed41300286a12fc953cb0a247ce8b6ef802e4f1) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack61 ) //dinoplus
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack61.8f", 0x000000, 0x80000, CRC(dbce6bde) SHA1(2ee0f987878652ee66f818ab3813a5a2a35368ee) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack61.7f", 0x080000, 0x80000, CRC(7414d90a) SHA1(5ab41900f5e4230cfa04f14ea197691ab5cdf314) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack61.6f", 0x100000, 0x80000, CRC(39523a35) SHA1(b32b9051c03ad8cb0590136cf95944e0e72bb3e1) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack62 ) //dinosdj
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack62.8f",  0x000000, 0x80000, CRC(1d3ad91c) SHA1(055512f861b776e83d3a094dc1bfb8223791746c) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack62.7f",  0x080000, 0x80000, CRC(3dba531d) SHA1(285b32e7795a3a35c16d10b937aeb8a1b7c7900e) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack62.6f",  0x100000, 0x80000, CRC(991b6455) SHA1(b1f9362e35dad45d16e7e310e1f5802f9f33f0ca) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack62.5f",  0x180000, 0x80000, CRC(c3696440) SHA1(4044b00b29501c6ef8caf89d3dd907725b47adc9) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack63 ) //dinoyz
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack63.10f", 0x000000, 0x200000, CRC(60ccd121) SHA1(0857ce3d5eb127ec43e98d346a09deb2f39fa194) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack64 ) //dino3j
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack64.8f",  0x000000, 0x80000, CRC(280d91de) SHA1(552fab63e6668114a6bc42da1169f0f18ccf4c86) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack64.7f",  0x080000, 0x80000, CRC(73f65b56) SHA1(c4491f2552cd4b8ea20eaa65e1c78abdd038fdea) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack64.6f",  0x100000, 0x80000, CRC(ee9c8062) SHA1(cc1d10e8800bcff458cd81e6f3c72a64a7b1d70e) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack64.5f",  0x180000, 0x80000, CRC(199a9337) SHA1(25f99da6641cee1cb2db8e8bbe2a828ebb13d30c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack65 ) //dinotjb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack65.8f",  0x000000, 0x80000, CRC(d9febb86) SHA1(b73c13596749874166b6c12d363238e4804c280b) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack65.7f",  0x080000, 0x80000, CRC(e2d1c07d) SHA1(66699e26c416002e4452780dbfed012dc10fc38f) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack65.6f",  0x100000, 0x80000, CRC(c8aad032) SHA1(1efdae89bbd0ecddd7f2de98ecfb441ea5eb8455) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack65.5f",  0x180000, 0x80000, CRC(3f4fd835) SHA1(9d97a693341362be9432451590a47491496e5fdf) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack66 ) //dinotwb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack66.8f",  0x000000, 0x80000, CRC(d9e5f0f1) SHA1(ca5d33648c11d6918544614cfe928b65eb0e5236) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack66.7f",  0x080000, 0x80000, CRC(41c200ab) SHA1(0499c79cbe299faccef0f9f77ba2e125fa520ed3) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack66.6f",  0x100000, 0x80000, CRC(c537f377) SHA1(059e64603809af9d92b58f548b86cbe09b7e87b3) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack66.5f",  0x180000, 0x80000, CRC(5f1d95bd) SHA1(212ad9e545d514990b0f2995146728daeb784d07) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack67 ) //dinoxzb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack67.8f", 0x000000, 0x80000, CRC(e0847fde) SHA1(1b9dc5bfe7077b291d950d9e8b11159630095803) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack67.7f", 0x080000, 0x80000, CRC(f83366a9) SHA1(b2d25bc56b85c2e9d872c100e0bf9727c21e1455) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack67.6f", 0x100000, 0x80000, CRC(d54f06aa) SHA1(714dee3b8283ee68dfa19e46cc83fa164cf1c8d9) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack68 ) //dinoxlb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack68.8f",  0x000000, 0x80000, CRC(f9b0a08b) SHA1(c7c5e83f2be67ecc9437b96b6089f5523c0bc7dc) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack68.7f",  0x080000, 0x80000, CRC(bcedf0b5) SHA1(c7cff6202ff5f18b03a6891f33de839705571ffb) )
	ROM_LOAD16_WORD_SWAP( "cde_21a.6f", 0x100000, 0x80000, CRC(66d23de2) SHA1(19b8a365f630411d524d055459020f4c8cf930f1) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack68.5f",  0x180000, 0x80000, CRC(ab67f2ee) SHA1(2e8e86952370b2e14fb3529010d29a2c5d1ad917) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack69 ) //dinoxlb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack69.8f",  0x000000, 0x80000, CRC(c49bb3a0) SHA1(a441bd196447a98276b07076e8d552d7b46889e8) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack69.7f",  0x080000, 0x80000, CRC(efeb3970) SHA1(ab5fe2f37ecd8a97b60bbc81716533d44c06a03a) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack69.6f",  0x100000, 0x80000, CRC(5edc274b) SHA1(ee48dd73902ab40db4871e849a648f7aa1e3332d) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack68.5f",  0x180000, 0x80000, CRC(ab67f2ee) SHA1(2e8e86952370b2e14fb3529010d29a2c5d1ad917) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack70 ) //dinofrp
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack70.8f", 0x000000, 0x80000, CRC(e168bfa0) SHA1(3c1081a7a91e64327c5c692217040f7a08fcea77) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack70.7f", 0x080000, 0x80000, CRC(e9b97f67) SHA1(1ab3e5473c2533c46ee3e0a99b1dc2f259b203b0) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack70.6f", 0x100000, 0x80000, CRC(35ea21fc) SHA1(882ba8a5b0d965ce03a18f9f3a3fa35ee050bb8f) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack71 ) //dinowsxl
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack71.8f",  0x000000, 0x80000, CRC(caf23842) SHA1(b80a17c0446a4bb104df5283d5fb2c8aa78dfbc6) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack71.7f",  0x080000, 0x80000, CRC(ae22f6a2) SHA1(d5bab0e44d7c896196f64c228f4b0fa6d6f4e78e) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack71.6f", 0x100000, 0x80000, CRC(247f6aa5) SHA1(77aded2201b6be1ff6c23ba021e2265730b9ac91) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack68.5f",  0x180000, 0x80000, CRC(ab67f2ee) SHA1(2e8e86952370b2e14fb3529010d29a2c5d1ad917) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack72 ) //dinozsj
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack72.8f", 0x000000, 0x80000, CRC(4e857677) SHA1(74d59d4a80a28d44e739c5bbb3f2a539fad873ad) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack72.7f", 0x080000, 0x80000, CRC(ffabef5a) SHA1(13522de6a3d5697cd32254f744cf5a859f53542a) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack72.6f", 0x100000, 0x80000, CRC(35d48739) SHA1(6ed059f1c322e8c8ea7da30e29aef05793bf1560) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack73 ) //dinowjb2
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack73.8f", 0x000000, 0x80000, CRC(bda42e9c) SHA1(4c6f0125a8a659d6ca31be223072ea3ae0f30eac) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack73.7f", 0x080000, 0x80000, CRC(74f32a30) SHA1(b50172c8fc68ee460dc08528f249e377d2987246) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack73.6f", 0x100000, 0x80000, CRC(df41f884) SHA1(527ae190df3d17c86dac14ea8a64dfb24e400920) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack74 ) //dinods
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack74.10f", 0x000000, 0x200000, CRC(a32961d5) SHA1(3042dc8cb0118bf4c1f74a8998ce718754740439) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack75 ) //dinodw
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack75.8f",  0x000000, 0x80000, CRC(a655fbcb) SHA1(67a855cb41485e609a01b51d85ccbf358cb28d51) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack75.7f",  0x080000, 0x80000, CRC(cfb10915) SHA1(71d5d1d5a8a01da6864792d564cbb199e33fbafc) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack75.6f",  0x100000, 0x80000, CRC(f2cc3419) SHA1(41a7e69bc2fa415a146222533ff0991cac59c9c7) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack75.5f",  0x180000, 0x80000, CRC(75660aac) SHA1(6a521e1d2a632c26e53b83d2cc4b0edecfc1e68c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack76 ) //dinosyn
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack76.8f",  0x000000, 0x80000, CRC(dadaea15) SHA1(63aa75b8f8c889b1c96c66a18d2337c907057ea1) )
	ROM_LOAD16_WORD_SWAP( "cde_22a_hack76.7f",  0x080000, 0x80000, CRC(e14039db) SHA1(13d365baf3b95861722c0fd272fb8740eebae37a) )
	ROM_LOAD16_WORD_SWAP( "cde_21a_hack76.6f",  0x100000, 0x80000, CRC(e31b9eda) SHA1(4f87ed0d336f162648472b53e071c44e8c67b8da) )
	ROM_LOAD16_WORD_SWAP( "cde_20a_hack76.5f",  0x180000, 0x80000, CRC(a564c2ea) SHA1(189e8172bf8934419025431023e906513fa7b9e0) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohack77 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23a_hack77.10f", 0x000000, 0x200000, CRC(9da95eab) SHA1(370bf3bbd76de5ae638c6fdab67c7cea98744e7b) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

/********
 bootleg
**********/

ROM_START( dinoh ) //dino99p
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cda_23h.rom",  0x000000, 0x80000, CRC(8e2a9cf0) SHA1(01111582e579bd3b43b52d0e0c445c32fe5e053b) )
	ROM_LOAD16_WORD_SWAP( "cda_22h.rom",  0x080000, 0x80000, CRC(f72cd219) SHA1(a3f580bd328b54d2546ae7e94262c1a706d27172) )
	ROM_LOAD16_WORD_SWAP( "cda_21h.rom",  0x100000, 0x80000, CRC(bc275b76) SHA1(1f7f7533b4ccb511dc479f531d9d6740d3ca6712) )
	ROM_LOAD16_WORD_SWAP( "cda_20h.rom",  0x180000, 0x80000, CRC(8987c975) SHA1(3fd856805d627f855f72acc7aacc2e8ecf0f12bd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",   0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",   0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",   0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",   0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",   0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",   0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",   0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a",  0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinoh.key", 0x00, 0x80, CRC(67862673) SHA1(9ae7446231da7fd6355e1f22ac3fb974c3775600) )
ROM_END

ROM_START( dinoha )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kl2-r1.800",  0x080000, 0x080000, CRC(4c70dca7) SHA1(2e7a10c90924e0f87903eddb04313f61233a998f) )
	ROM_CONTINUE(               0x000000, 0x080000 )
	ROM_LOAD16_WORD_SWAP( "kl2-l2.800",  0x180000, 0x080000, CRC(c6ae7338) SHA1(4b8543cf1ac89ae95fe63e6d81c87d2bda52da69) )
	ROM_CONTINUE(               0x100000, 0x080000 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-a.160",   0x000000, 0x80000, CRC(7e4f9fb3) SHA1(b985d925e0fb799cdf0a671e4800961d9872cd8f), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "cd-b.160",   0x000002, 0x80000, CRC(89532d85) SHA1(6743c4d9b4407421416c13878b8a1fae097dd7a7), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinoh.key", 0x00, 0x80, CRC(67862673) SHA1(9ae7446231da7fd6355e1f22ac3fb974c3775600) )
ROM_END

ROM_START( dinotpic )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cd-d.800",  0x000000, 0x100000, CRC(2a7b2915) SHA1(817d24c5206a60c4d93affffc9bd5a72abccbb01) )
	ROM_LOAD16_WORD_SWAP( "cd-e.800",  0x100000, 0x100000, CRC(e8370226) SHA1(9c6915ad9e48ccd2020fcad58ec56e6f7cd0c25c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-a.160",   0x000000, 0x80000, CRC(7e4f9fb3) SHA1(b985d925e0fb799cdf0a671e4800961d9872cd8f), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "cd-b.160",   0x000002, 0x80000, CRC(89532d85) SHA1(6743c4d9b4407421416c13878b8a1fae097dd7a7), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinob.key", 0x00, 0x80, CRC(171140c4) SHA1(d1db4e37e22fa6ae03c2bca4fdb698399d98c15f) )
ROM_END

ROM_START( dinohc )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "hc.23",  0x000000, 0x80000, CRC(cecf4b12) SHA1(75f13fe91442b7c044e58a37d6e7b5bf05150be5) )
	ROM_LOAD16_WORD_SWAP( "hc.22",  0x080000, 0x80000, CRC(07eeb238) SHA1(b217625839108b826b3955ad675ab8ccd3aa424c) )
	ROM_LOAD16_WORD_SWAP( "hc.21",  0x100000, 0x80000, CRC(3bc3d57a) SHA1(cca8101d6171472f4f4c506aa0e3d789e5cbe785) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",   0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",   0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",   0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",   0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",   0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",   0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",   0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a",  0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(              0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",     0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",     0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinoh.key", 0x00, 0x80, CRC(67862673) SHA1(9ae7446231da7fd6355e1f22ac3fb974c3775600) )
ROM_END

/************
 Final Fight
**************/

ROM_START( ffighthack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "ffu_36b.11f",    0x00000, 0x20000, CRC(a9fa0174) SHA1(a6f669370f1f822b2988c297a8e26bcb6300692d) )
	ROM_LOAD16_BYTE( "ffu_42b.11h",    0x00001, 0x20000, CRC(d47cb6b7) SHA1(26c94b0d91a4343b58a7cc542417d8d36e9f2e34) )
	ROM_LOAD16_BYTE( "ffu_37b.12f",    0x40000, 0x20000, CRC(3fc9f9e3) SHA1(0982c40d5967e5068ec592db022eb16172f95005) )
	ROM_LOAD16_BYTE( "ffu_43b.12h",    0x40001, 0x20000, CRC(5ef051fa) SHA1(f72d45f9d03f78de8d081658098decbadc9e7828) )
	ROM_LOAD16_WORD_SWAP( "ff_22.7f",  0x80000, 0x80000, CRC(b2d5a3aa) SHA1(b60f7480d3d3ceebad4c21025394bacc154d7042) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "ff_1.3a",  0x000000, 0x80000, CRC(969d18e2) SHA1(7a30b7434e34ec98838a9ab8d953b2ef467d562e), ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ff_2.4a",  0x000002, 0x80000, CRC(02b59f99) SHA1(c1cb2bbf95c2006baad58b0a5a7278f1a8999901), ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ff_3.5a",  0x000004, 0x80000, CRC(01d507ae) SHA1(d7813daa5bd74bebdbbea578acb20ad3c8816997), ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ff_4.6a",  0x000006, 0x80000, CRC(f7c4ceb0) SHA1(3e9cf6379f06c5a736b4a0aadb7fbda914b91190), ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b", 0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c", 0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c", 0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "ffightb.key", 0x00, 0x80, CRC(328f442c) SHA1(f58a07458f00ee7fdd0471fa03f7859ae9e2629b) )
ROM_END

ROM_START( ffighthack02 ) //ffightp
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "ff_36_hack02.11f",      0x00000, 0x20000, CRC(d2649695) SHA1(7bc6d34d6b497a8d247577bd6c0427beb2a49b63) )
	ROM_LOAD16_BYTE( "ff_42_hack02.11h",      0x00001, 0x20000, CRC(2d21f32a) SHA1(7a9fea8869996a8342a52e521182e2cc7b157051) )
	ROM_LOAD16_BYTE( "ff_37_hack02.12f",      0x40000, 0x20000, CRC(465c9973) SHA1(2fc4f7c3dddfb3e7c14558844db6fba5f0e0a3e3) )
	ROM_LOAD16_BYTE( "ffe_43_hack02.12h",     0x40001, 0x20000, CRC(d8e7572b) SHA1(c106651ba7e02195d0936807541232f5c29c9132) )
	ROM_LOAD16_WORD_SWAP( "ff-32m.8h", 0x80000, 0x80000, CRC(c747696e) SHA1(d3362dadded31ccb7eaf71ef282d698d18edd722) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "ff-5m.7a", 0x000000, 0x80000, CRC(9c284108) SHA1(7868f5801347340867720255f8380548ad1a65a7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ff-7m.9a", 0x000002, 0x80000, CRC(a7584dfb) SHA1(f7b00a3ca8cb85264ab293089f9f540a8292b49c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ff-1m.3a", 0x000004, 0x80000, CRC(0b605e44) SHA1(5ce16af72858a57aefbf6efed820c2c51935882a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ff-3m.5a", 0x000006, 0x80000, CRC(52291cd2) SHA1(df5f3d3aa96a7a33ff22f2a31382942c4c4f1111) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b", 0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c", 0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c", 0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "ffight.key", 0x00, 0x80, CRC(df8b3ef6) SHA1(0dc2af5e95d729ac953405900a25243168251405) )
ROM_END

ROM_START( ffighthack03 ) //ffightj2
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "ffj_36a_hack03.12f", 0x00000, 0x20000, CRC(be4b1b78) SHA1(10523e9d77d247719727a8c762a2a3d87acfd7d4) )
	ROM_LOAD16_BYTE( "ffj_42a_hack03.12h", 0x00001, 0x20000, CRC(c025aaab) SHA1(1090626a0719426629c875dd005c1174f1518712) )
	ROM_LOAD16_BYTE( "ffj_37a_hack03.13f", 0x40000, 0x20000, CRC(b83525dd) SHA1(3b03e2bf9fe107a31739e2fb1918e39202895d15) )
	ROM_LOAD16_BYTE( "ffj_43a_hack03.13h", 0x40001, 0x20000, CRC(14359680) SHA1(f815194ea8cb5365493849e83d1ff82c0331f6b7) )
	ROM_LOAD16_BYTE( "ffj_34.10f",   0x80000, 0x20000, CRC(0c8dc3fc) SHA1(edcce3efd9cdd131ef0c96df15a68722d5c3498e) )
	ROM_LOAD16_BYTE( "ffj_40.10h",   0x80001, 0x20000, CRC(8075bab9) SHA1(f9c7405133f6fc5557c90e60e8ccc459e4f6fd7d) )
	ROM_LOAD16_BYTE( "ffj_35.11f",   0xc0000, 0x20000, CRC(4a934121) SHA1(3982c261582755a0eac340d6d7ed96e6c263c8b6) )
	ROM_LOAD16_BYTE( "ffj_41.11h",   0xc0001, 0x20000, CRC(2af68154) SHA1(7d549cb38650b4b79c68ad6d0dfcefdd62be4e99) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "ffj_09.4b",  0x000000, 0x20000, CRC(5b116d0d) SHA1(a24e829fdfa043bd27b508d7cc0788ad80fd180e) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_01.4a",  0x000001, 0x20000, CRC(815b1797) SHA1(549e5eefc8f607fec1c954ba715ff21b8e44a5aa) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_13.9b",  0x000002, 0x20000, CRC(8721a7da) SHA1(39b2b324fd7810342503f23695e423f364a6294d) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_05.9a",  0x000003, 0x20000, CRC(d0fcd4b5) SHA1(97ebcbead0cca7e425143c500c433dbcf9cadcc2) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_24.5e",  0x000004, 0x20000, CRC(a1ab607a) SHA1(56784c028b82d9e2affd9610f56fde57063e4c28) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_17.5c",  0x000005, 0x20000, CRC(2dc18cf4) SHA1(5e3bd895600cd30d561a75a2fcb6cc8bc84f4bd1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_38.8h",  0x000006, 0x20000, CRC(6535a57f) SHA1(f4da9ec13cad7e3287e34dcceb0eb2d20107bad6) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_32.8f",  0x000007, 0x20000, CRC(c8bc4a57) SHA1(3eaf2b4e910fe1f79154020122d786d23a2e594a) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_10.5b",  0x100000, 0x20000, CRC(624a924a) SHA1(48fd0498f9ed54003bf6578fbcbc8b7e90a195eb) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_02.5a",  0x100001, 0x20000, CRC(5d91f694) SHA1(e0ea9ec82dec985d8bf5e7cebf5fe3d8ef7557b1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_14.10b", 0x100002, 0x20000, CRC(0a2e9101) SHA1(6c8d550d2066cd53355ccf14ac1fd35914982094) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_06.10a", 0x100003, 0x20000, CRC(1c18f042) SHA1(f708296570fecad82a76dc59744873a2f5568ea1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_25.7e",  0x100004, 0x20000, CRC(6e8181ea) SHA1(2c32bc0364650ee6ca0d24754a7a3401295ffcd5) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_18.7c",  0x100005, 0x20000, CRC(b19ede59) SHA1(7e79ad9f17b36e042d774bef3bbb44018332ca01) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_39.9h",  0x100006, 0x20000, CRC(9416b477) SHA1(f2310dfcfe960e8b822c07849b594d54dfc2b2ca) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_33.9f",  0x100007, 0x20000, CRC(7369fa07) SHA1(3b2750fe33729395217c96909b4b6c5f3d6e9943) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b",  0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c",  0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c",  0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "ffightj2.key", 0x00, 0x80, CRC(1fbcac88) SHA1(b61a3ec619ec919b1bb999efa89d683d509c84d8) )
ROM_END

ROM_START( ffighthack04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "ffj_36a_hack04.12f", 0x00000, 0x20000, CRC(cb024f54) SHA1(f5a6f8fff5680eb157c7bb475a50da0a0ee4269b) )
	ROM_LOAD16_BYTE( "ffj_42a_hack04.12h", 0x00001, 0x20000, CRC(516fc7a6) SHA1(599bb1d22d43f9b3571e5bf4b836b95bbd63021a) )
	ROM_LOAD16_BYTE( "ffj_37a_hack04.13f", 0x40000, 0x20000, CRC(e1bd4c19) SHA1(5527fe8c8c49eebbacf0e67aec7e1de9ba477a50) )
	ROM_LOAD16_BYTE( "ffj_43a_hack04.13h", 0x40001, 0x20000, CRC(066c44ba) SHA1(8fba0ca434103615ce192d0f775a1354e67eddee) )
	ROM_LOAD16_BYTE( "ffj_34.10f",   0x80000, 0x20000, CRC(0c8dc3fc) SHA1(edcce3efd9cdd131ef0c96df15a68722d5c3498e) )
	ROM_LOAD16_BYTE( "ffj_40.10h",   0x80001, 0x20000, CRC(8075bab9) SHA1(f9c7405133f6fc5557c90e60e8ccc459e4f6fd7d) )
	ROM_LOAD16_BYTE( "ffj_35.11f",   0xc0000, 0x20000, CRC(4a934121) SHA1(3982c261582755a0eac340d6d7ed96e6c263c8b6) )
	ROM_LOAD16_BYTE( "ffj_41.11h",   0xc0001, 0x20000, CRC(2af68154) SHA1(7d549cb38650b4b79c68ad6d0dfcefdd62be4e99) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "ffj_09.4b",  0x000000, 0x20000, CRC(5b116d0d) SHA1(a24e829fdfa043bd27b508d7cc0788ad80fd180e) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_01.4a",  0x000001, 0x20000, CRC(815b1797) SHA1(549e5eefc8f607fec1c954ba715ff21b8e44a5aa) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_13.9b",  0x000002, 0x20000, CRC(8721a7da) SHA1(39b2b324fd7810342503f23695e423f364a6294d) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_05.9a",  0x000003, 0x20000, CRC(d0fcd4b5) SHA1(97ebcbead0cca7e425143c500c433dbcf9cadcc2) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_24.5e",  0x000004, 0x20000, CRC(a1ab607a) SHA1(56784c028b82d9e2affd9610f56fde57063e4c28) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_17.5c",  0x000005, 0x20000, CRC(2dc18cf4) SHA1(5e3bd895600cd30d561a75a2fcb6cc8bc84f4bd1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_38.8h",  0x000006, 0x20000, CRC(6535a57f) SHA1(f4da9ec13cad7e3287e34dcceb0eb2d20107bad6) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_32.8f",  0x000007, 0x20000, CRC(c8bc4a57) SHA1(3eaf2b4e910fe1f79154020122d786d23a2e594a) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_10.5b",  0x100000, 0x20000, CRC(624a924a) SHA1(48fd0498f9ed54003bf6578fbcbc8b7e90a195eb) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_02.5a",  0x100001, 0x20000, CRC(5d91f694) SHA1(e0ea9ec82dec985d8bf5e7cebf5fe3d8ef7557b1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_14.10b", 0x100002, 0x20000, CRC(0a2e9101) SHA1(6c8d550d2066cd53355ccf14ac1fd35914982094) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_06.10a", 0x100003, 0x20000, CRC(1c18f042) SHA1(f708296570fecad82a76dc59744873a2f5568ea1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_25.7e",  0x100004, 0x20000, CRC(6e8181ea) SHA1(2c32bc0364650ee6ca0d24754a7a3401295ffcd5) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_18.7c",  0x100005, 0x20000, CRC(b19ede59) SHA1(7e79ad9f17b36e042d774bef3bbb44018332ca01) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_39.9h",  0x100006, 0x20000, CRC(9416b477) SHA1(f2310dfcfe960e8b822c07849b594d54dfc2b2ca) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_33.9f",  0x100007, 0x20000, CRC(7369fa07) SHA1(3b2750fe33729395217c96909b4b6c5f3d6e9943) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b",  0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c",  0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c",  0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "ffightj2.key", 0x00, 0x80, CRC(1fbcac88) SHA1(b61a3ec619ec919b1bb999efa89d683d509c84d8) )
ROM_END

ROM_START( ffighthack05 ) //ffightj2
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "ffj_36a_hack05.12f", 0x00000, 0x20000, CRC(c3c49ad4) SHA1(3a3c2c1c4b75ebd68b236f0715a35c7f9a5af055) )
	ROM_LOAD16_BYTE( "ffj_42a_hack05.12h", 0x00001, 0x20000, CRC(a6693dbf) SHA1(c5d1b34c9840724036c672926e4ab5503ace8da6) )
	ROM_LOAD16_BYTE( "ffj_37a_hack05.13f", 0x40000, 0x20000, CRC(c3ed5ee4) SHA1(cea756eab22bc71876ded0dd82f7b5932695e7a8) )
	ROM_LOAD16_BYTE( "ffj_43a_hack05.13h", 0x40001, 0x20000, CRC(0dac920d) SHA1(1317c9887e1f818e6af7c77bd8efd6b93ebcbbcb) )
	ROM_LOAD16_BYTE( "ffj_34.10f",   0x80000, 0x20000, CRC(0c8dc3fc) SHA1(edcce3efd9cdd131ef0c96df15a68722d5c3498e) )
	ROM_LOAD16_BYTE( "ffj_40.10h",   0x80001, 0x20000, CRC(8075bab9) SHA1(f9c7405133f6fc5557c90e60e8ccc459e4f6fd7d) )
	ROM_LOAD16_BYTE( "ffj_35.11f",   0xc0000, 0x20000, CRC(4a934121) SHA1(3982c261582755a0eac340d6d7ed96e6c263c8b6) )
	ROM_LOAD16_BYTE( "ffj_41.11h",   0xc0001, 0x20000, CRC(2af68154) SHA1(7d549cb38650b4b79c68ad6d0dfcefdd62be4e99) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "ffj_09.4b",  0x000000, 0x20000, CRC(5b116d0d) SHA1(a24e829fdfa043bd27b508d7cc0788ad80fd180e) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_01.4a",  0x000001, 0x20000, CRC(815b1797) SHA1(549e5eefc8f607fec1c954ba715ff21b8e44a5aa) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_13.9b",  0x000002, 0x20000, CRC(8721a7da) SHA1(39b2b324fd7810342503f23695e423f364a6294d) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_05.9a",  0x000003, 0x20000, CRC(d0fcd4b5) SHA1(97ebcbead0cca7e425143c500c433dbcf9cadcc2) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_24.5e",  0x000004, 0x20000, CRC(a1ab607a) SHA1(56784c028b82d9e2affd9610f56fde57063e4c28) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_17.5c",  0x000005, 0x20000, CRC(2dc18cf4) SHA1(5e3bd895600cd30d561a75a2fcb6cc8bc84f4bd1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_38.8h",  0x000006, 0x20000, CRC(6535a57f) SHA1(f4da9ec13cad7e3287e34dcceb0eb2d20107bad6) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_32.8f",  0x000007, 0x20000, CRC(c8bc4a57) SHA1(3eaf2b4e910fe1f79154020122d786d23a2e594a) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_10.5b",  0x100000, 0x20000, CRC(624a924a) SHA1(48fd0498f9ed54003bf6578fbcbc8b7e90a195eb) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_02.5a",  0x100001, 0x20000, CRC(5d91f694) SHA1(e0ea9ec82dec985d8bf5e7cebf5fe3d8ef7557b1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_14.10b", 0x100002, 0x20000, CRC(0a2e9101) SHA1(6c8d550d2066cd53355ccf14ac1fd35914982094) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_06.10a", 0x100003, 0x20000, CRC(1c18f042) SHA1(f708296570fecad82a76dc59744873a2f5568ea1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_25.7e",  0x100004, 0x20000, CRC(6e8181ea) SHA1(2c32bc0364650ee6ca0d24754a7a3401295ffcd5) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_18.7c",  0x100005, 0x20000, CRC(b19ede59) SHA1(7e79ad9f17b36e042d774bef3bbb44018332ca01) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_39.9h",  0x100006, 0x20000, CRC(9416b477) SHA1(f2310dfcfe960e8b822c07849b594d54dfc2b2ca) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_33.9f",  0x100007, 0x20000, CRC(7369fa07) SHA1(3b2750fe33729395217c96909b4b6c5f3d6e9943) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b",  0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c",  0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c",  0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "ffightj2.key", 0x00, 0x80, CRC(1fbcac88) SHA1(b61a3ec619ec919b1bb999efa89d683d509c84d8) )
ROM_END

ROM_START( ffighthack06 ) //ffight1v2
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "ffj_36_hack06.12f", 0x00000, 0x20000, CRC(5d9b9222) SHA1(4db46e757f8ffad514ec9f3c27613d601b88f316) )
	ROM_LOAD16_BYTE( "ffj_42_hack06.12h", 0x00001, 0x20000, CRC(48986323) SHA1(004ace666449278aed2a69fdca4a3a0779083d4a) )
	ROM_LOAD16_BYTE( "ffj_37.13f", 0x40000, 0x20000, CRC(c371c667) SHA1(633977c91a8ff09b7fe83128eced7c4dee9aee1d) )
	ROM_LOAD16_BYTE( "ffj_43.13h", 0x40001, 0x20000, CRC(6f81f194) SHA1(2cddf75a0a607cf57395583876cf81bcca005871) )
	ROM_LOAD16_BYTE( "ffj_34.10f", 0x80000, 0x20000, CRC(0c8dc3fc) SHA1(edcce3efd9cdd131ef0c96df15a68722d5c3498e) )
	ROM_LOAD16_BYTE( "ffj_40.10h", 0x80001, 0x20000, CRC(8075bab9) SHA1(f9c7405133f6fc5557c90e60e8ccc459e4f6fd7d) )
	ROM_LOAD16_BYTE( "ffj_35.11f", 0xc0000, 0x20000, CRC(4a934121) SHA1(3982c261582755a0eac340d6d7ed96e6c263c8b6) )
	ROM_LOAD16_BYTE( "ffj_41.11h", 0xc0001, 0x20000, CRC(2af68154) SHA1(7d549cb38650b4b79c68ad6d0dfcefdd62be4e99) )
	ROM_LOAD16_BYTE( "ffj_45_hack06.8f", 0xE0000, 0x20000, CRC(37708588) SHA1(ab1a841d37b7cafc88e160dcde4d72b981033fdf) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "ffj_09.4b",  0x000000, 0x20000, CRC(5b116d0d) SHA1(a24e829fdfa043bd27b508d7cc0788ad80fd180e) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_01.4a",  0x000001, 0x20000, CRC(815b1797) SHA1(549e5eefc8f607fec1c954ba715ff21b8e44a5aa) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_13.9b",  0x000002, 0x20000, CRC(8721a7da) SHA1(39b2b324fd7810342503f23695e423f364a6294d) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_05.9a",  0x000003, 0x20000, CRC(d0fcd4b5) SHA1(97ebcbead0cca7e425143c500c433dbcf9cadcc2) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_24.5e",  0x000004, 0x20000, CRC(a1ab607a) SHA1(56784c028b82d9e2affd9610f56fde57063e4c28) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_17.5c",  0x000005, 0x20000, CRC(2dc18cf4) SHA1(5e3bd895600cd30d561a75a2fcb6cc8bc84f4bd1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_38.8h",  0x000006, 0x20000, CRC(6535a57f) SHA1(f4da9ec13cad7e3287e34dcceb0eb2d20107bad6) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_32.8f",  0x000007, 0x20000, CRC(c8bc4a57) SHA1(3eaf2b4e910fe1f79154020122d786d23a2e594a) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_10.5b",  0x100000, 0x20000, CRC(624a924a) SHA1(48fd0498f9ed54003bf6578fbcbc8b7e90a195eb) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_02.5a",  0x100001, 0x20000, CRC(5d91f694) SHA1(e0ea9ec82dec985d8bf5e7cebf5fe3d8ef7557b1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_14.10b", 0x100002, 0x20000, CRC(0a2e9101) SHA1(6c8d550d2066cd53355ccf14ac1fd35914982094) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_06.10a", 0x100003, 0x20000, CRC(1c18f042) SHA1(f708296570fecad82a76dc59744873a2f5568ea1) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_25.7e",  0x100004, 0x20000, CRC(6e8181ea) SHA1(2c32bc0364650ee6ca0d24754a7a3401295ffcd5) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_18.7c",  0x100005, 0x20000, CRC(b19ede59) SHA1(7e79ad9f17b36e042d774bef3bbb44018332ca01) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_39.9h",  0x100006, 0x20000, CRC(9416b477) SHA1(f2310dfcfe960e8b822c07849b594d54dfc2b2ca) , ROM_SKIP(7) )
	ROMX_LOAD( "ffj_33.9f",  0x100007, 0x20000, CRC(7369fa07) SHA1(3b2750fe33729395217c96909b4b6c5f3d6e9943) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b",   0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c",  0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c",  0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "ffightb.key", 0x00, 0x80, CRC(328f442c) SHA1(f58a07458f00ee7fdd0471fa03f7859ae9e2629b) )
ROM_END

ROM_START( ffighthack07 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ff-23m_hack07.8h", 0x00000, 0x80000, CRC(86DEF74F) SHA1(5206cc13bfe40fb4f9c3677629aee89099623ee6) )
	ROM_LOAD16_WORD_SWAP( "ff-22m_hack07.7h", 0x80000, 0x80000, CRC(CBDD8689) SHA1(a75918ee837dfccdd4fd02b716928a2de2003103) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD64_WORD( "ff-5m_hack07.7a", 0x000000, 0x80000, CRC(91a909bd) SHA1(09621cb33a9c26798b1bba186dceb02e5f126e1a) )
	ROM_LOAD64_WORD( "ff-7m_hack07.9a", 0x000002, 0x80000, CRC(89f8b4cd) SHA1(c169c445686d3c79eae2dc42460b8194c491ccb0) )
	ROM_LOAD64_WORD( "ff-1m_hack07.3a", 0x000004, 0x80000, CRC(d5469303) SHA1(0c1e33a87eb3ef79e6a5ba80753eb495284e666c) )
	ROM_LOAD64_WORD( "ff-3m_hack07.5a", 0x000006, 0x80000, CRC(0c6302bf) SHA1(03ee13a67a8a3b92fac462623ace752d77b9e9f1) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b", 0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c", 0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c", 0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "ffightae.key", 0x00, 0x80, CRC(8a7e5df2) SHA1(34a93d94ee4579826f5f91e7c1acfa6e0c80029a) )
ROM_END

ROM_START( ffighthack08 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ff-23m_hack08.8h", 0x00000, 0x80000, CRC(eabd1e7f) SHA1(a4133530d8da70288ee444e90cebb043fe6e2058) )
	ROM_LOAD16_WORD_SWAP( "ff-22m_hack07.7h", 0x80000, 0x80000, CRC(cbdd8689) SHA1(a75918ee837dfccdd4fd02b716928a2de2003103) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD64_WORD( "ff-5m_hack07.7a", 0x000000, 0x80000, CRC(91a909bd) SHA1(09621cb33a9c26798b1bba186dceb02e5f126e1a) )
	ROM_LOAD64_WORD( "ff-7m_hack07.9a", 0x000002, 0x80000, CRC(89f8b4cd) SHA1(c169c445686d3c79eae2dc42460b8194c491ccb0) )
	ROM_LOAD64_WORD( "ff-1m_hack07.3a", 0x000004, 0x80000, CRC(d5469303) SHA1(0c1e33a87eb3ef79e6a5ba80753eb495284e666c) )
	ROM_LOAD64_WORD( "ff-3m_hack07.5a", 0x000006, 0x80000, CRC(0c6302bf) SHA1(03ee13a67a8a3b92fac462623ace752d77b9e9f1) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b", 0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c", 0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c", 0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "ffightae.key", 0x00, 0x80, CRC(8a7e5df2) SHA1(34a93d94ee4579826f5f91e7c1acfa6e0c80029a) )
ROM_END

ROM_START( ffighthack09 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ff-23m_hack09.8h", 0x00000, 0x80000, CRC(530dcd58) SHA1(06e00a76c32a6ce6f90fdcdd32c43ef54bf2b7e6) )
	ROM_LOAD16_WORD_SWAP( "ff-22m_hack09.7h", 0x80000, 0x80000, CRC(ce6b88f8) SHA1(24e13dafb3d62c6bbf5873dc2b036d59644775eb) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD64_WORD( "ff-5m_hack07.7a", 0x000000, 0x80000, CRC(91a909bd) SHA1(09621cb33a9c26798b1bba186dceb02e5f126e1a) )
	ROM_LOAD64_WORD( "ff-7m_hack07.9a", 0x000002, 0x80000, CRC(89f8b4cd) SHA1(c169c445686d3c79eae2dc42460b8194c491ccb0) )
	ROM_LOAD64_WORD( "ff-1m_hack07.3a", 0x000004, 0x80000, CRC(d5469303) SHA1(0c1e33a87eb3ef79e6a5ba80753eb495284e666c) )
	ROM_LOAD64_WORD( "ff-3m_hack07.5a", 0x000006, 0x80000, CRC(0c6302bf) SHA1(03ee13a67a8a3b92fac462623ace752d77b9e9f1) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b", 0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c", 0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c", 0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "ffightae.key", 0x00, 0x80, CRC(8a7e5df2) SHA1(34a93d94ee4579826f5f91e7c1acfa6e0c80029a) )
ROM_END

ROM_START( ffighthack10 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ff-23m_hack10.8h", 0x00000, 0x80000, CRC(6d1378d0) SHA1(72589d244ed50c308f97ae5ad8124ae9e54cda2f) )
	ROM_LOAD16_WORD_SWAP( "ff-22m_hack10.7h", 0x80000, 0x80000, CRC(8ca53832) SHA1(70121baed976a8add6053b4ba6dec0b165a558bd) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD64_WORD( "ff-5m_hack07.7a", 0x000000, 0x80000, CRC(91a909bd) SHA1(09621cb33a9c26798b1bba186dceb02e5f126e1a) )
	ROM_LOAD64_WORD( "ff-7m_hack07.9a", 0x000002, 0x80000, CRC(89f8b4cd) SHA1(c169c445686d3c79eae2dc42460b8194c491ccb0) )
	ROM_LOAD64_WORD( "ff-1m_hack07.3a", 0x000004, 0x80000, CRC(d5469303) SHA1(0c1e33a87eb3ef79e6a5ba80753eb495284e666c) )
	ROM_LOAD64_WORD( "ff-3m_hack07.5a", 0x000006, 0x80000, CRC(0c6302bf) SHA1(03ee13a67a8a3b92fac462623ace752d77b9e9f1) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ff_09.12b", 0x00000, 0x08000, CRC(b8367eb5) SHA1(ec3db29fdd6200e9a8f4f8073a7e34aef731354f) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ff_18.11c", 0x00000, 0x20000, CRC(375c66e7) SHA1(36189e23209ce4ae5d9cbabd1574540d0591e7b3) )
	ROM_LOAD( "ff_19.12c", 0x20000, 0x20000, CRC(1ef137f9) SHA1(974b5e72aa28b87ebfa7438efbdfeda769dedf5e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "ffightae.key", 0x00, 0x80, CRC(8a7e5df2) SHA1(34a93d94ee4579826f5f91e7c1acfa6e0c80029a) )
ROM_END

/*********************
 Knights of the Round
***********************/

ROM_START( knightshack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack01.8f", 0x00000, 0x80000, CRC(bffdf6f6) SHA1(92a72036b9cb1de170a6727749bcfcdfd881cc08) )
	ROM_LOAD16_WORD_SWAP( "kr_22_hack01.7f", 0x80000, 0x80000, CRC(81d97121) SHA1(ce59234d73033c2db64b53525d21484b4d1de2a8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack02.8f", 0x00000, 0x80000, CRC(a1984e47) SHA1(2c9782c51931b9c365b001daa7c49671dd36147c) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack03 ) 
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack03.8f", 0x00000, 0x80000, CRC(19a77194) SHA1(109999d43bb6a5c1a81bad55905d3f4d45e151e4) )
	ROM_LOAD16_WORD_SWAP( "kr_22_hack03.7f", 0x80000, 0x80000, CRC(7a244171) SHA1(c7baab2e02be287ab67657e408229a09a464592d) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack04.8f", 0x00000, 0x80000, CRC(99fef934) SHA1(ebd8006230d302f7125c7f0037de163afa9520ab) )
	ROM_LOAD16_WORD_SWAP( "kr_22_hack04.7f", 0x80000, 0x80000, CRC(860953ee) SHA1(df8c49aa561c432287bc278cdf765723de23391d) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack05 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack05.8f", 0x00000, 0x80000, CRC(29ab6297) SHA1(449a587750120050561d4ea1b6027e2e7d9109cf) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack06 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack06.8f", 0x00000, 0x80000, CRC(c8106cb7) SHA1(d3473e9bc7debb1c456cfb2f7939f6692b1ad852) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack07 ) //knights1v3
	ROM_REGION( 0x4D4F93, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack07.8f", 0x00000, 0x454F93, CRC(2ad36ed1) SHA1(3d1169ee41b14232e74373ce93a93fd3b3c9fe35) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack08 ) //knightsu1v3
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack08.8f", 0x00000, 0x80000, CRC(cd53cbfa) SHA1(f8479eac96c47ff8ee34229534e05f7cc43f5360) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack09 ) //knightsb3
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack09.8f", 0x00000, 0x80000, CRC(55597d39) SHA1(ed8d20b12cd2965f2b7579490c98da9e1bd4f40f) )
	ROM_LOAD16_WORD_SWAP( "kr_22_hack09.7f", 0x80000, 0x80000, CRC(1438d070) SHA1(4f6fad844c3e8eb960bb6cb85ac570979c0ae973) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "1.096",  0x000000, 0x80000, CRC(91541596) SHA1(4aac23d826f64c6065271488e3b582b3c9e11703) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "2.096",  0x000002, 0x80000, CRC(5d332114) SHA1(d340be3aa93b2117bccc9b4a7088c65ca29925b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3.096",  0x000004, 0x80000, CRC(60488eba) SHA1(2117db67ed5c5d3225c3ab3d90932b9786e8060d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "4.096",  0x000006, 0x80000, CRC(394bdd11) SHA1(9b15abccc8372c04469b5472bd36d368965d1161) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "5.096",  0x200000, 0x80000, CRC(b52af98b) SHA1(3fb9b8fab8dc925d3d17f1428467df513d475d3d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "6.096",  0x200002, 0x80000, CRC(e44e5eac) SHA1(329649d381f1e48fcc37f5d64eb869833a5e0e18) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a",  0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18.010",  0x00000, 0x20000, CRC(9b9be3ab) SHA1(9a5283d71551e71660a4741a647f5aea7e5ba89b) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knightsh.key", 0x00, 0x80, CRC(68d9786b) SHA1(8721cda836d88c48ab07b96d66015832b5e561f7) )
ROM_END

ROM_START( knightshack10 ) //knightsh
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack10.8f", 0x00000, 0x80000, CRC(7d6e3cb9) SHA1(089ee26a479f0bbe6e032f8c162af5df61732146) )
	ROM_LOAD16_WORD_SWAP( "kr_22_hack09.7f", 0x80000, 0x80000, CRC(1438d070) SHA1(4f6fad844c3e8eb960bb6cb85ac570979c0ae973) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18.010",  0x00000, 0x20000, CRC(9b9be3ab) SHA1(9a5283d71551e71660a4741a647f5aea7e5ba89b) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knightsh.key", 0x00, 0x80, CRC(68d9786b) SHA1(8721cda836d88c48ab07b96d66015832b5e561f7) )
ROM_END

ROM_START( knightshack11 ) //knightsu
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack11.8f",0x00000, 0x80000, CRC(1c73393a) SHA1(06f546207f249c87f83d8885191fd5357843d1b0) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack12 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack12.8f",0x00000, 0x80000, CRC(e0d06498) SHA1(2bd84fc62b9c03f1daf321375ed234c1d54fbf0f) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack13 ) //knights1v3
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack13.8f",0x00000, 0x80000, CRC(598f9550) SHA1(7f9e4c06f209c7fbe4dfefa5a172a59a2844e549) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack14 ) //knightsp
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack14.8f",0x00000, 0x80000, CRC(43755bd9) SHA1(8734e3101c2cb7772c325edf2e08804668fe1c07) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack15 ) //knightsp
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack15.10f",0x00000, 0x200000, CRC(9edda7d0) SHA1(3203939f00ce23f1173d01fd70c38fffe5b2dcd8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack16 ) //knightss
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack16.10f",0x00000, 0x200000, CRC(db88baec) SHA1(b6ccd52e1401ec777b4e144b189218ca96adeccd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

ROM_START( knightshack17 ) //knightswsxl
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kr_23_hack17.10f",0x00000, 0x200000, CRC(abf2a2c6) SHA1(ebf83d6901bbe8523d0d161c73156019e3b1607f) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knights.key", 0x00, 0x80, CRC(a4851689) SHA1(0a96f22a655c3ff9d09d7b84abd7ab5ac5f137e2) )
ROM_END

/********
 bootleg
**********/

ROM_START( knightshb2 ) //knightsb2
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "040-z.02",   0x00000, 0x80000, CRC(95d00a7e) SHA1(2da1c47aa15d44aa842a8d79e030e7e7b69bec19) )
	ROM_LOAD16_BYTE( "040-r.02",   0x00001, 0x80000, CRC(5a9d0b64) SHA1(6ff312879c3d675ceee6fd3e262f797fabb9871e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a",  0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",     0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",     0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",     0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knightsb2.key", 0x00, 0x80, CRC(67017a7f) SHA1(d9db5b41b214539f71cc2f0d92a27285c27e38c4) )
ROM_END

ROM_START( knightsh )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "krh_23.rom",   0x00000, 0x80000, CRC(fa2ff63d) SHA1(f3800102aadeccd13ed49c88039732453266283a) )
	ROM_LOAD16_WORD_SWAP( "krh_22.rom",   0x80000, 0x80000, CRC(1438d070) SHA1(4f6fad844c3e8eb960bb6cb85ac570979c0ae973) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a",  0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",     0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",     0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",     0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knightsh.key", 0x00, 0x80, CRC(68d9786b) SHA1(8721cda836d88c48ab07b96d66015832b5e561f7) )
ROM_END

ROM_START( knightsha )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "krha_23.rom",  0x00000, 0x80000, CRC(a7fd309a) SHA1(b4f163d9588e9d8dd6f2ba6d6ae520efb620c1ac) )
	ROM_LOAD16_WORD_SWAP( "krh_22.rom",   0x80000, 0x80000, CRC(1438d070) SHA1(4f6fad844c3e8eb960bb6cb85ac570979c0ae973) )
	ROM_FILL(0xb7d,1,0x66)

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a",  0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",     0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",    0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",    0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knightsha.key", 0x00, 0x80, CRC(ab2dff46) SHA1(9bc8ec843ec9e8522858df8fb72e8c0e3fa1f023) )
ROM_END

ROM_START( knightsb5 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "23.096",   0x00000, 0x80000, CRC(7733b8a6) SHA1(ecf1a0d2b4631b9d4ba46e4987d226d938ee6628) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f", 0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "1.096",  0x000000, 0x80000, CRC(91541596) SHA1(4aac23d826f64c6065271488e3b582b3c9e11703) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "2.096",  0x000002, 0x80000, CRC(5d332114) SHA1(d340be3aa93b2117bccc9b4a7088c65ca29925b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3.096",  0x000004, 0x80000, CRC(60488eba) SHA1(2117db67ed5c5d3225c3ab3d90932b9786e8060d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "4.096",  0x000006, 0x80000, CRC(394bdd11) SHA1(9b15abccc8372c04469b5472bd36d368965d1161) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "5.096",  0x200000, 0x80000, CRC(b52af98b) SHA1(3fb9b8fab8dc925d3d17f1428467df513d475d3d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "6.096",  0x200002, 0x80000, CRC(e44e5eac) SHA1(329649d381f1e48fcc37f5d64eb869833a5e0e18) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a",  0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",   0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(        0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18.010",  0x00000, 0x20000, CRC(9b9be3ab) SHA1(9a5283d71551e71660a4741a647f5aea7e5ba89b) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knightsh.key", 0x00, 0x80, CRC(68d9786b) SHA1(8721cda836d88c48ab07b96d66015832b5e561f7) )
ROM_END

ROM_START( knightud )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "knightud.23", 0x00000, 0x80000, CRC(5fe98e7f) SHA1(3e01b9e06663ade831750de3ecd0d3925889a5da) )
	ROM_LOAD16_WORD_SWAP( "kr_22.7f",  0x80000, 0x80000, CRC(d0b671a9) SHA1(9865472c5fc3f617345e23b5de5a9ba177945b5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kr-5m.3a",  0x000000, 0x80000, CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-7m.5a",  0x000002, 0x80000, CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-1m.4a",  0x000004, 0x80000, CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-3m.6a",  0x000006, 0x80000, CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-6m.7a",  0x200000, 0x80000, CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-8m.9a",  0x200002, 0x80000, CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-2m.8a",  0x200004, 0x80000, CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kr-4m.10a", 0x200006, 0x80000, CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kr_09.11a",  0x00000, 0x08000, CRC(5e44d9ee) SHA1(47a7503321be8d52b5c44af838e3bb82ee15a415) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kr_18.11c",  0x00000, 0x20000, CRC(da69d15f) SHA1(9616207e693bae85705f786cef60b9f6951b5067) )
	ROM_LOAD( "kr_19.12c",  0x20000, 0x20000, CRC(bfc654e9) SHA1(01b3d92e4dedf55ea3933d387c7ddb9ba2549773) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "knightsh.key", 0x00, 0x80, CRC(68d9786b) SHA1(8721cda836d88c48ab07b96d66015832b5e561f7) )
ROM_END

/********************
 The King of Dragons
**********************/

ROM_START( kodhack01 ) //kodubs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "kde_30a_hack01.11e", 0x00000, 0x20000, CRC(13dff227) SHA1(037dac8b10ee83fb28b745035f66d78f9aa6d304) )
	ROM_LOAD16_BYTE( "kde_37a_hack01.11f", 0x00001, 0x20000, CRC(007d6dd9) SHA1(b83a627446d06a9715f39e16ef3bc79484f892f4) )
	ROM_LOAD16_BYTE( "kde_31a_hack01.12e", 0x40000, 0x20000, CRC(3b89dd96) SHA1(cd457b9148466c4032c006bf655155099a2a610d) )
	ROM_LOAD16_BYTE( "kde_38a_hack01.12f", 0x40001, 0x20000, CRC(3eceba92) SHA1(7ba31470ceb91ad644ea97f1fe740f62a9bae27f) )
	ROM_LOAD16_BYTE( "kd_28.9e",   0x80000, 0x20000, CRC(9367bcd9) SHA1(8243b4b9bb9756f3fa726717e19a166cb2f5b50a) )
	ROM_LOAD16_BYTE( "kd_35.9f",   0x80001, 0x20000, CRC(4ca6a48a) SHA1(9d440ecd8d2d0e293fecf64ca3915252b94e7aef) )
	ROM_LOAD16_BYTE( "kd_29.10e",  0xc0000, 0x20000, CRC(0360fa72) SHA1(274769c8717a874397cf37369e3ef80a682d9ef2) )
	ROM_LOAD16_BYTE( "kd_36a.10f", 0xc0001, 0x20000, CRC(95a3cef8) SHA1(9b75c1ed0eafacc230197ffd9b81e0c8f4f2c464) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kd-5m.4a", 0x000000, 0x80000, CRC(e45b8701) SHA1(604e39e455e81695ee4f899f102d0bcd789cedd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-7m.6a", 0x000002, 0x80000, CRC(a7750322) SHA1(3c583496a53cd64edf377db35f7f40f02b59b7e7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-1m.3a", 0x000004, 0x80000, CRC(5f74bf78) SHA1(b7c43eea9bf77a0fb571dcd53f8be719e6655fd9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-3m.5a", 0x000006, 0x80000, CRC(5e5303bf) SHA1(d9f90b898ffdf4398b2bbeb48247f06f728e7c00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c", 0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c", 0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-2m.3c", 0x200004, 0x80000, CRC(9ef36604) SHA1(b42ca0a910b65e1e7bb6e7d734e853ce67e821bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c", 0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_9.12a", 0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c", 0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c", 0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "kod.key", 0x00, 0x80, CRC(b79ea9b9) SHA1(cefded329a6ccc34d3b68e614c8f3a2c174e3fdd) )
ROM_END

/*******
 bootleg
*********/

// - Actor preview flickers instead of wriggling
// - No music in attract mode
ROM_START( kodh )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "23.096",  0x00000, 0x80000, CRC(daf89cfb) SHA1(de0944884d0e64c6b0410294d25308201508afbe) )
	ROM_LOAD16_WORD_SWAP( "22.096",  0x80000, 0x80000, CRC(c83e19d8) SHA1(8c342818a1c5337ad4b259700e184972f821aca4) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "1.096",        0x000000, 0x80000, CRC(09261881) SHA1(e65abce3d39224c2c94673900291a210c1d949cb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "2.096",        0x000002, 0x80000, CRC(bc121ff2) SHA1(1f75f93652bb6c521bc538e7c2d10920a7897aa2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3.096",        0x000004, 0x80000, CRC(f463ae22) SHA1(f8bc17814d38f3693a2a8dc64cc44e1f4fe3102c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "4.096",        0x000006, 0x80000, CRC(01308733) SHA1(8de29e7063d03493f197cee7a4e4edff3eee8e36) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c",    0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c",    0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	// Bad dump? Only 1 byte is different
	ROMX_LOAD( "kr-2m.8a",        0x200004, 0x80000, CRC(c7ab4704) SHA1(180852c4d59359c2094feb8ad1f05d70eafe6c55) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c",    0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_9.12a",      0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c",      0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c",      0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "kodh.key", 0x00, 0x80, CRC(9d65fe9c) SHA1(9671ee388d59a2d12cf38712620f5f598e93abfc) )
ROM_END

/*******
  Mercs
*********/

ROM_START( mercshack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "so2_30e_hack01.11f",     0x00000, 0x20000, CRC(bfabc8e3) SHA1(b9d575b30c43bfd90cdf4c5eeb25407f308fd729) )
	ROM_LOAD16_BYTE( "so2_35e_hack01.11h",     0x00001, 0x20000, CRC(6d8e2f7a) SHA1(8529e544558195cc170c1462c7ccc025b674e9a8) )
	ROM_LOAD16_BYTE( "so2_31e.12f",     0x40000, 0x20000, CRC(51204d36) SHA1(af288fc369d092f38ea73be967705aacade06f28) )
	ROM_LOAD16_BYTE( "so2_36e.12h",     0x40001, 0x20000, CRC(9cfba8b4) SHA1(df8ee5e3a68f056f68f096c46fdb548f63d29446) )
	ROM_LOAD16_WORD_SWAP( "so2-32m.8h", 0x80000, 0x80000, CRC(2eb5cf0c) SHA1(e0d765fb6957d156ffd40cabf51ba6098cbbeb19) )

	ROM_REGION( 0x300000, "gfx", 0 )
	ROMX_LOAD( "so2-6m.8a",  0x000000, 0x80000, CRC(aa6102af) SHA1(4a45f3547a3640f256e5e20bfd72784f880f03f5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "so2-8m.10a", 0x000002, 0x80000, CRC(839e6869) SHA1(7741141a9f1b1e2956edc1d11f9cc3974390c4ed) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "so2-2m.4a",  0x000004, 0x80000, CRC(597c2875) SHA1(440bd04db2c121a6976e5e1027071d28812942d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "so2-4m.6a",  0x000006, 0x80000, CRC(912a9ca0) SHA1(b226a4a388e57e23d7a7559773ebee434125a2e4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "so2_24.7d",  0x200000, 0x20000, CRC(3f254efe) SHA1(5db36eb98a6d3c7acccb561d92c1988d1330cbbf) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_14.7c",  0x200001, 0x20000, CRC(f5a8905e) SHA1(fada8b635d490c06b75711ed505a025bb0aa4454) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_26.9d",  0x200002, 0x20000, CRC(f3aa5a4a) SHA1(bcb3396de5524fffd4110bfbeeeca1c936990eb3) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_16.9c",  0x200003, 0x20000, CRC(b43cd1a8) SHA1(01c2bb802469848a172968802a674c0045a8b8dc) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_20.3d",  0x200004, 0x20000, CRC(8ca751a3) SHA1(e93bbe7311f14e7e3cbfb42b83fd7fee4bb9cefc) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_10.3c",  0x200005, 0x20000, CRC(e9f569fd) SHA1(39ae9eacdf1f35ef90d131444c37958d7aaf7238) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_22.5d",  0x200006, 0x20000, CRC(fce9a377) SHA1(5de5f696f63326f2cb4c38bcb05e07bcf2246071) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_12.5c",  0x200007, 0x20000, CRC(b7df8a06) SHA1(b42cb0d3f55a1e8fe8afbbd9aeae50074cdc5f08) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "so2_09.12b",  0x00000, 0x08000, CRC(d09d7c7a) SHA1(8e8532be08818c855d9c3ce45716eb07cfab5767) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "so2_18.11c",  0x00000, 0x20000, CRC(bbea1643) SHA1(d43d68a120550067bf0b181f88687ad230cd7908) )
	ROM_LOAD( "so2_19.12c",  0x20000, 0x20000, CRC(ac58aa71) SHA1(93102272e358bc49d3936302efdc5bb68df84d68) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "mercs.key", 0x00, 0x80, CRC(b0f59dee) SHA1(744e4239ddbfdc6d1b53dc1bd49a34df422c8886) )
ROM_END

ROM_START( mercshack02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "so2_36_hack02.12f", 0x00000, 0x20000, CRC(d4d34a1f) SHA1(c1543578f45e45d35fd761ae1abf3f8e5afc8e9b) )
	ROM_LOAD16_BYTE( "so2_42_hack02.12h", 0x00001, 0x20000, CRC(184d7739) SHA1(c70f5613336535b3ed7efe7120fd167865ca54cc) )
	ROM_LOAD16_BYTE( "so2_31e.12f", 0x40000, 0x20000, CRC(51204d36) SHA1(af288fc369d092f38ea73be967705aacade06f28) )
	ROM_LOAD16_BYTE( "so2_36e.12h", 0x40001, 0x20000, CRC(9cfba8b4) SHA1(df8ee5e3a68f056f68f096c46fdb548f63d29446) )
	ROM_LOAD16_BYTE( "so2_34.10f", 0x80000, 0x20000, CRC(b8dae95f) SHA1(2db4a20afd40b772a16f1bee999a0b82d3379ac7) )
	ROM_LOAD16_BYTE( "so2_40.10h", 0x80001, 0x20000, CRC(de37771c) SHA1(45e1e2ef4e46dbe8881e809d700fdd3d06a03c92) )
	ROM_LOAD16_BYTE( "so2_35_hack02.11f", 0xc0000, 0x20000, CRC(1e84d605) SHA1(9b1cdcc998d0624a158e14270c2785c5bfb250e4) )
	ROM_LOAD16_BYTE( "so2_41_hack02.11h", 0xc0001, 0x20000, CRC(831496b2) SHA1(811e3f300aa0f93a89a07e5ee9e419a73cba7395) )

	ROM_REGION( 0x300000, "gfx", 0 )
	ROMX_LOAD( "so2_09_hack02.4b",  0x000000, 0x20000, CRC(855d7524) SHA1(47b7a1aaa0833da56a4ce3f2e7101b998532f797) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_01_hack02.4a",  0x000001, 0x20000, CRC(a44d4196) SHA1(0e722802aacbd872eb94b1f1136e83b2d738b6e3) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_13_hack02.9b",  0x000002, 0x20000, CRC(8ba956f0) SHA1(9101ea35734cf4ebad3f7f862c4212d5e19ffc6f) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_05_hack02.9a",  0x000003, 0x20000, CRC(dfc0ccaa) SHA1(bffbef3575871174ca619a55b7eb83e5f06864fd) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_24_hack02.5e",  0x000004, 0x20000, CRC(94e7a3f2) SHA1(78ae47ba736665388a3f2fe073068872794d14a6) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_17_hack02.5c",  0x000005, 0x20000, CRC(723bd58b) SHA1(f8e772acba8421ac0f89b88a529b68c950d80901) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_38_hack02.8h",  0x000006, 0x20000, CRC(3e5d7dd0) SHA1(f8b138ad295229327f8198e5b42fe784349c8f2c) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_32_hack02.8f",  0x000007, 0x20000, CRC(fea1e81c) SHA1(6bb5096b42898991326075ddd71861d3b7fefdab) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_10.5b",  0x100000, 0x20000, CRC(2f871714) SHA1(8a39f120e3f50fc9a7e6cee659260b2f823fb0e0) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_02.5a",  0x100001, 0x20000, CRC(b4b2a0b7) SHA1(ee42ed3de9021e8d08d6c7115f2de73476b93452) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_14.10b", 0x100002, 0x20000, CRC(737a744b) SHA1(8e1477a67862f7c0c598d3d1a1f633946e7ab31b) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_06.10a", 0x100003, 0x20000, CRC(9d756f51) SHA1(4e9773ee25f6a952fb4f541d37e5e46e4089fd07) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_25.7e",  0x100004, 0x20000, CRC(6d0e05d6) SHA1(47cbec235bd4b250db007218dc357101ae453d1a) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_18.7c",  0x100005, 0x20000, CRC(96f61f4e) SHA1(954334bd8c2d2b02175de60d6a181a23e723d040) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_39.9h",  0x100006, 0x20000, CRC(d52ba336) SHA1(49550d316e575a4e64ea6a5f769f3cd716be6df5) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_33.9f",  0x100007, 0x20000, CRC(39b90d25) SHA1(1089cca168a4abeb398fa93eddd4d9fff70d5db5) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_11_hack02.7b",  0x200000, 0x20000, CRC(89322061) SHA1(da6f684125c0a3803aa83ffb08e984df90161848) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_03_hack02.7a",  0x200001, 0x20000, CRC(55ab0bde) SHA1(96f4df896f4500e7dab59956ad3deae91601241e) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_15_hack02.11b", 0x200002, 0x20000, CRC(542ecd0e) SHA1(f76e07eb19e1bda0dd3e079167d9f6afb0e6f34b) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_07_hack02.11a", 0x200003, 0x20000, CRC(db87495b) SHA1(49d67ea8995d0ed0d22e4df206505ebed5b72909) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_26_hack02.8e",  0x200004, 0x20000, CRC(7b07ea2a) SHA1(3c0f3a7302d32dc1dabd3d66df1d5de2f3d767dc) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_19_hack02.8c",  0x200005, 0x20000, CRC(690310cc) SHA1(bf8d68fd375bb3ca14114d44911bf962e490babb) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_28_hack02.10e", 0x200006, 0x20000, CRC(323e586e) SHA1(4ff383f28be69fccbe77aa8f928ac5b31089780d) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_21_hack02.10c", 0x200007, 0x20000, CRC(cb355a66) SHA1(84fc6b3815bed89a1d029a38d0cae0029025447c) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "so2_09.12b",  0x00000, 0x08000, CRC(d09d7c7a) SHA1(8e8532be08818c855d9c3ce45716eb07cfab5767) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "so2_18.11c",  0x00000, 0x20000, CRC(bbea1643) SHA1(d43d68a120550067bf0b181f88687ad230cd7908) )
	ROM_LOAD( "so2_19.12c",  0x20000, 0x20000, CRC(ac58aa71) SHA1(93102272e358bc49d3936302efdc5bb68df84d68) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "mercs.key", 0x00, 0x80, CRC(b0f59dee) SHA1(744e4239ddbfdc6d1b53dc1bd49a34df422c8886) )
ROM_END

/*************
 The Punisher
***************/

ROM_START( punisherhack01 ) //punisher1v2
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pse_26_hack01.11e",    0x000000, 0x20000, CRC(81cd5484) SHA1(fcb0f3aee08c564ed2b783f09b3e970f6866e3bf) )
	ROM_LOAD16_BYTE( "pse_30_hack01.11f",    0x000001, 0x20000, CRC(5e2b19f6) SHA1(bb9930469620705beb7f6f7b5319d6e3f8b7529e) )
	ROM_LOAD16_BYTE( "pse_27_hack01.12e",    0x040000, 0x20000, CRC(75580ff8) SHA1(6b130031c2984cb07961768e6bd9f1c77fb3b72f) )
	ROM_LOAD16_BYTE( "pse_31_hack01.12f",    0x040001, 0x20000, CRC(75e6e262) SHA1(48055a3b94cad0efdd762f515ca23ca18dd06f61) )
	ROM_LOAD16_BYTE( "pse_24_hack01.9e",     0x080000, 0x20000, CRC(c25ef92e) SHA1(d1e22820ded5f60bed529e6a3c1bf6285d63136f) )
	ROM_LOAD16_BYTE( "pse_28_hack01.9f",     0x080001, 0x20000, CRC(f3ff48fc) SHA1(d2c3ffabe326ecda09bf1ae926a68be98d7cf2b8) )
	ROM_LOAD16_BYTE( "pse_25_hack01.10e",    0x0c0000, 0x20000, CRC(ae1fb98e) SHA1(5d3ad62c2f1c6a4ac38f0f112ec7d1f090dd5089) )
	ROM_LOAD16_BYTE( "pse_29_hack01.10f",    0x0c0001, 0x20000, CRC(4a2ea384) SHA1(c5445fd761aef16cf2b24706071b5aa01c2553b8) )
	ROM_LOAD16_WORD_SWAP( "ps_21_hack01.6f", 0x100000, 0x80000, CRC(fc83f71d) SHA1(9113a7e2fad640116429f32ab868fc225f239686) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m_hack01.3a",  0x000000, 0x80000, CRC(726dbd2c) SHA1(fac53e7085407a7d1a9955964a17b73482011b92) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m_hack01.5a",  0x000002, 0x80000, CRC(907ffea8) SHA1(77e2508bc890c94d8f31d9e60154434c5bacfb9a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m_hack01.4a",  0x000004, 0x80000, CRC(61202953) SHA1(a217058cfc99c9c2771ff31db787ba3f7578c54b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m_hack01.6a",  0x000006, 0x80000, CRC(f187ce6b) SHA1(522dde0b92b310bf01384a65bc6fd68d845491b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhack02 ) //punisherhr
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pse_26_hack02.11e",    0x000000, 0x20000, CRC(7730f07f) SHA1(2498c90947d352e2228cc876e92bcd9dd81ddc5d) )
	ROM_LOAD16_BYTE( "pse_30_hack02.11f",    0x000001, 0x20000, CRC(adc62a92) SHA1(96197097e2baec0b1917a32daf84880c28919fa6) )
	ROM_LOAD16_BYTE( "pse_27_hack02.12e",    0x040000, 0x20000, CRC(e3694c47) SHA1(63ed5a96259a931b09d2dca78346accb21e4142c) )
	ROM_LOAD16_BYTE( "pse_31_hack02.12f",    0x040001, 0x20000, CRC(aa40c89d) SHA1(437c8c10bf7180e70dc1354e262dec843bc87c2b) )
	ROM_LOAD16_BYTE( "pse_24_hack02.9e",     0x080000, 0x20000, CRC(876bf007) SHA1(8f536d7e111925b3010deb4c3d46c5a6d7c41e43) )
	ROM_LOAD16_BYTE( "pse_28_hack02.9f",     0x080001, 0x20000, CRC(644392c9) SHA1(f0430b3decbcd90d188581075df68a2623380804) )
	ROM_LOAD16_BYTE( "pse_25_hack02.10e",    0x0c0000, 0x20000, CRC(7812ca13) SHA1(4d350680638e0a9ac9240eb4b34ccfdca2acb418) )
	ROM_LOAD16_BYTE( "pse_29_hack02.10f",    0x0c0001, 0x20000, CRC(9330cb5d) SHA1(db877b72b743b0dead28d331cc90bafa44147f31) )
	ROM_LOAD16_WORD_SWAP( "ps_21.6f", 0x100000, 0x80000, CRC(8affa5a9) SHA1(268760b83b1723ff50a019ec51ef7af2e49935bf) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m_hack02.3a",  0x000000, 0x80000, CRC(15bb2e4d) SHA1(16db940f983121cb1bbf1a80b925dfa011e3ba7f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m_hack02.5a",  0x000002, 0x80000, CRC(75ce5411) SHA1(4c1c22fb442728e8893ef2512030791c01f60374) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m_hack02.4a",  0x000004, 0x80000, CRC(06f6ba32) SHA1(b8b4b3be16fd55075bf9d6f0b21024258d7d740d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m_hack02.6a",  0x000006, 0x80000, CRC(143664d2) SHA1(24acacf18d1b3d34b1aff92c1ee3d05ddfbb5eb6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhack03 ) //punisherbs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pse_26_hack03.11e",    0x000000, 0x20000, CRC(b1a1035f) SHA1(98d5b9e54e3fa71a90f3d3eb557cdaa418282af5) )
	ROM_LOAD16_BYTE( "pse_30_hack03.11f",    0x000001, 0x20000, CRC(d58812f0) SHA1(a1d4488fce43e26d3d8e69bebd2986ed5a3880b6) )
	ROM_LOAD16_BYTE( "pse_27_hack03.12e",    0x040000, 0x20000, CRC(089c27cf) SHA1(62a2f9d4f3ec6719d761e989ab8de50733588e0d) )
	ROM_LOAD16_BYTE( "pse_31_hack03.12f",    0x040001, 0x20000, CRC(944a7b83) SHA1(586857b30df9bfd99ef776c48577220f32582e35) )
	ROM_LOAD16_BYTE( "pse_24_hack02.9e",     0x080000, 0x20000, CRC(876bf007) SHA1(8f536d7e111925b3010deb4c3d46c5a6d7c41e43) )
	ROM_LOAD16_BYTE( "pse_28_hack02.9f",     0x080001, 0x20000, CRC(644392c9) SHA1(f0430b3decbcd90d188581075df68a2623380804) )
	ROM_LOAD16_BYTE( "pse_25_hack02.10e",    0x0c0000, 0x20000, CRC(7812ca13) SHA1(4d350680638e0a9ac9240eb4b34ccfdca2acb418) )
	ROM_LOAD16_BYTE( "pse_29_hack02.10f",    0x0c0001, 0x20000, CRC(9330cb5d) SHA1(db877b72b743b0dead28d331cc90bafa44147f31) )
	ROM_LOAD16_WORD_SWAP( "ps_21_hack03.6f", 0x100000, 0x80000, CRC(98a1d1c2) SHA1(68f4ec5b70e213de0949e427f18d8f51d1da1853) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m_hack03.3a",  0x000000, 0x80000, CRC(bdd7db37) SHA1(8d39e3510e8b6ee4ea0f15823f209d35ab18ec8c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m_hack03.5a",  0x000002, 0x80000, CRC(9682d033) SHA1(1289cf7454f8b27c7fd0fe6c8955829002305218) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m_hack03.4a",  0x000004, 0x80000, CRC(ae9a4f48) SHA1(36a8ba1433f80204ab2f8c5f747514a3989a057f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m_hack03.6a",  0x000006, 0x80000, CRC(f77ae0f0) SHA1(775cf5a6e3c5ad601a7d1a843878b0502ece80f8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhack04 ) //punisherkd
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pse_26.11e",    0x000000, 0x20000, CRC(389a99d2) SHA1(e97f4225554e4603cb0e3edd296a90bb2e467ca7) )
	ROM_LOAD16_BYTE( "pse_30.11f",    0x000001, 0x20000, CRC(68fb06ac) SHA1(189e25ca7e4aaa80492c03ce06696952cc1b1553) )
	ROM_LOAD16_BYTE( "pse_27.12e",    0x040000, 0x20000, CRC(3eb181c3) SHA1(a2442449f4bbe3be03d2be7d4e2cbb69f9741dac) )
	ROM_LOAD16_BYTE( "pse_31.12f",    0x040001, 0x20000, CRC(37108e7b) SHA1(78aaa6e2913e6b1b852b39416557ac4a394d7d8b) )
	ROM_LOAD16_BYTE( "pse_24.9e",     0x080000, 0x20000, CRC(0f434414) SHA1(aaacf835a93551fc792571d6e824a01f3c5d4469) )
	ROM_LOAD16_BYTE( "pse_28.9f",     0x080001, 0x20000, CRC(b732345d) SHA1(472d84f846e9f73f129562d78352376194e0211e) )
	ROM_LOAD16_BYTE( "pse_25.10e",    0x0c0000, 0x20000, CRC(b77102e2) SHA1(2e39b2c2c0eed5ca2320a57e69bcf377f809a20c) )
	ROM_LOAD16_BYTE( "pse_29.10f",    0x0c0001, 0x20000, CRC(ec037bce) SHA1(f86e7feb63d7662a38048e6d51d7b5a69dafaffb) )
	ROM_LOAD16_WORD_SWAP( "ps_21_hack04.6f",   0x100000, 0x80000, CRC(33ee9f9c) SHA1(af58c857254a987deba9941f284588d966f336a8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m.3a",  0x000000, 0x80000, CRC(77b7ccab) SHA1(e08e5d55a79e4c0c8ca819d6d7d2a14f753c6ec3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m.5a",  0x000002, 0x80000, CRC(0122720b) SHA1(5f0d3097e097f64106048156fbb0d343fe78fffa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m.4a",  0x000004, 0x80000, CRC(64fa58d4) SHA1(d4a774285ed15273195b6b26d2965ce370e54e73) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m.6a",  0x000006, 0x80000, CRC(60da42c8) SHA1(95eec4a58d9628a2d9764951dd8dc11e4860a899) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhack05 ) //punisherbs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pse_26_hack05.11e",    0x000000, 0x20000, CRC(476143ea) SHA1(8d2965610950134a187e16533a2dd38d24a0ca11) )
	ROM_LOAD16_BYTE( "pse_30_hack05.11f",    0x000001, 0x20000, CRC(b5905af0) SHA1(b161384017dc85589f61d52651f6887261e48193) )
	ROM_LOAD16_BYTE( "pse_27_hack05.12e",    0x040000, 0x20000, CRC(ba7241c5) SHA1(d98a5029153592a6adeaee652df267d3aa661edb) )
	ROM_LOAD16_BYTE( "pse_31_hack05.12f",    0x040001, 0x20000, CRC(4d2d2857) SHA1(9026c4855d01cca4aa047596f901afa9c578b4db) )
	ROM_LOAD16_BYTE( "pse_24_hack05.9e",     0x080000, 0x20000, CRC(9eed52bb) SHA1(a2a6cdae471bfbcf1970e92aba85a3e40b5d6e0a) )
	ROM_LOAD16_BYTE( "pse_28_hack05.9f",     0x080001, 0x20000, CRC(adc281ed) SHA1(acb8cf37d6da12ce3576e3192af925cea7a9e7eb) )
	ROM_LOAD16_BYTE( "pse_25_hack05.10e",    0x0c0000, 0x20000, CRC(83d78978) SHA1(b88fd99d22b82077a4a912ca01eda1327388f9e3) )
	ROM_LOAD16_BYTE( "pse_29_hack05.10f",    0x0c0001, 0x20000, CRC(0fd7c434) SHA1(fc27551132cc293a6172a2a81ed37d04e9bffc90) )
	ROM_LOAD16_WORD_SWAP( "ps_21_hack05.6f", 0x100000, 0x80000, CRC(2bccb0ed) SHA1(44f45431d7ecca6eb8942be3d44b99cf856d12ab) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "psms16.3a",  0x000000, 0x80000, CRC(4d4111de) SHA1(f67002f6a9073f5aba33e31879fc7f4c1d60ffda) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "psms16.5a",  0x000002, 0x80000, CRC(2d346b82) SHA1(dfd48382fdc8d1da5ece31a8ed99a0fa9f58c1ed) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "psms16.4a",  0x000004, 0x80000, CRC(5e0c85a1) SHA1(3b2487d8ae60d2beabafd83007359a84d3d0079e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "psms16.6a",  0x000006, 0x80000, CRC(4ccc5b41) SHA1(1176458dccd129f19952fbafb85a7629b29b1ee3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5ms09.7a",  0x200000, 0x80000, CRC(ebb91780) SHA1(07a98ee8cde2fa0555baf6894312b8f2aba91ba3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7ms09.9a",  0x200002, 0x80000, CRC(f0c1d356) SHA1(821810342f662fb06cbe304651e2a965d7ca452c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6ms09.8a",  0x200004, 0x80000, CRC(51ca7a4b) SHA1(19a378e0b0f9e751902b86913e52188597dad940) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8ms09.10a", 0x200006, 0x80000, CRC(4a4854f9) SHA1(315c9f6d1dc0dee522424f92d6df647cae9992e9) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhack06 ) //punisherj1v2
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "psj_23_hack06.8f", 0x000000, 0x80000, CRC(fca1aaa9) SHA1(b5804ae74e416ac47696ab5a1b7c5b9fcfed7edd) )
	ROM_LOAD16_WORD_SWAP( "psj_22_hack06.7f", 0x080000, 0x80000, CRC(0d967580) SHA1(c415f77c720ed65af2bc8283a87e360b3c66e230) )
	ROM_LOAD16_WORD_SWAP( "psj_21_hack06.6f",   0x100000, 0x80000, CRC(e4e15e4a) SHA1(405d57983ed33276e6fde155d4c78c2973466483) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m.3a",  0x000000, 0x80000, CRC(77b7ccab) SHA1(e08e5d55a79e4c0c8ca819d6d7d2a14f753c6ec3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m.5a",  0x000002, 0x80000, CRC(0122720b) SHA1(5f0d3097e097f64106048156fbb0d343fe78fffa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m.4a",  0x000004, 0x80000, CRC(64fa58d4) SHA1(d4a774285ed15273195b6b26d2965ce370e54e73) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m.6a",  0x000006, 0x80000, CRC(60da42c8) SHA1(95eec4a58d9628a2d9764951dd8dc11e4860a899) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhack07 ) //punisher1v2bs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "psj_23_hack07.8f", 0x000000, 0x80000, CRC(81b23223) SHA1(665ae5dad9d85b74146265809c04eee0b76c9bbb) )
	ROM_LOAD16_WORD_SWAP( "psj_22_hack07.7f", 0x080000, 0x80000, CRC(f2a3fa5b) SHA1(fc831e232691bad90dd9a66825e7c589eb07b1a8) )
	ROM_LOAD16_WORD_SWAP( "psj_21_hack07.6f", 0x100000, 0x80000, CRC(be90fa83) SHA1(305e9f12f94d6bf16e16ccc2a67e4013219a0dd8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m_hack03.3a",  0x000000, 0x80000, CRC(bdd7db37) SHA1(8d39e3510e8b6ee4ea0f15823f209d35ab18ec8c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m_hack03.5a",  0x000002, 0x80000, CRC(9682d033) SHA1(1289cf7454f8b27c7fd0fe6c8955829002305218) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m_hack03.4a",  0x000004, 0x80000, CRC(ae9a4f48) SHA1(36a8ba1433f80204ab2f8c5f747514a3989a057f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m_hack03.6a",  0x000006, 0x80000, CRC(f77ae0f0) SHA1(775cf5a6e3c5ad601a7d1a843878b0502ece80f8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhack08 ) //punisherbs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "psj_23_hack08.10f", 0x000000, 0x180000, CRC(10ea3b27) SHA1(a4aa99addcee72975d80afb2d112df46387173d0) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m_hack03.3a",  0x000000, 0x80000, CRC(bdd7db37) SHA1(8d39e3510e8b6ee4ea0f15823f209d35ab18ec8c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m_hack03.5a",  0x000002, 0x80000, CRC(9682d033) SHA1(1289cf7454f8b27c7fd0fe6c8955829002305218) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m_hack03.4a",  0x000004, 0x80000, CRC(ae9a4f48) SHA1(36a8ba1433f80204ab2f8c5f747514a3989a057f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m_hack03.6a",  0x000006, 0x80000, CRC(f77ae0f0) SHA1(775cf5a6e3c5ad601a7d1a843878b0502ece80f8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

/********
 bootleg
**********/

ROM_START( punipic )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "3.bin",  0x000001, 0x80000, CRC(8c2593ac) SHA1(4261bc72b96c3a5690df35c5d8b71524765693d9) )
	ROM_LOAD16_BYTE( "5.bin",  0x000000, 0x80000, CRC(c3151563) SHA1(61d3a20c25fea8a94ae6e473a87c21968867cba0) )
	ROM_LOAD16_BYTE( "2.bin",  0x100001, 0x80000, CRC(d7b13f39) SHA1(eb7cd92b44fdef3b72672b0be6786c526421b627) )
	ROM_LOAD16_BYTE( "4.bin",  0x100000, 0x80000, CRC(665a5485) SHA1(c07920d110ca9c35f6cbff94a6a889c17300f994) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "9.bin",   0x000000, 0x40000, CRC(9b9a887a) SHA1(8805b36fc18837bd7c64c751b435d72b763b2235), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x000004, 0x40000 )
	ROMX_LOAD( "8.bin",   0x000001, 0x40000, CRC(2b94287a) SHA1(815d88e66f537e17550fc0483616f02f7126bfb1), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x000005, 0x40000 )
	ROMX_LOAD( "7.bin",   0x000002, 0x40000, CRC(e9bd74f5) SHA1(8ed7098c69d1c70093c99956bf82e532bd6fc7ac), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x000006, 0x40000 )
	ROMX_LOAD( "6.bin",   0x000003, 0x40000, CRC(a5e1c8a4) SHA1(3596265a45cf6bbf16c623f0fce7cdc65f9338ad), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x000007, 0x40000 )
	ROMX_LOAD( "13.bin",  0x200000, 0x40000, CRC(6d75a193) SHA1(6c5a89517926d7ba4a925a3df800d4bdb8a6938d), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x200004, 0x40000 )
	ROMX_LOAD( "12.bin",  0x200001, 0x40000, CRC(a3c205c1) SHA1(6317cc49434dbbb9a249ddd4b50bd791803b3ebe), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x200005, 0x40000 )
	ROMX_LOAD( "11.bin",  0x200002, 0x40000, CRC(22f2ec92) SHA1(9186bfc5db71dc5b099c9a985e8fdd5710772d1c), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x200006, 0x40000 )
	ROMX_LOAD( "10.bin",  0x200003, 0x40000, CRC(763974c9) SHA1(f9b93c7cf0cb8c212fc21c57c85459b7d2e4e2fd), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x200007, 0x40000 )

	//ROM_REGION( 0x200000, "oki", 0 )   // we don't use this
	//ROM_LOAD_OPTIONAL( "1.bin", 0x00000, 0x80000, CRC(aeec9dc6) SHA1(56fd62e8db8aa96cdd242d8c705849a413567780) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",       0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",      0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",      0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",      0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",      0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisherb.key", 0x00, 0x80, CRC(e1219963) SHA1(ba508a09095e9a37018a5a8c3a624713d7684582) )
ROM_END

ROM_START( punisherud1 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "psud1_26.11e", 0x000000, 0x20000, CRC(f820e620) SHA1(7c2e55b4dc7aaf27badceafd7bde483f33676351) )
	ROM_LOAD16_BYTE ( "psud1_30.11f", 0x000001, 0x20000, CRC(90afc70a) SHA1(73d5325a482becf46ef75456134242db7f1a31f8) )
	ROM_LOAD16_BYTE ( "psu_27.12e",   0x040000, 0x20000, CRC(61c960a1) SHA1(f8fe651283cc1f138d013cab65b833505de6df9f) )
	ROM_LOAD16_BYTE ( "psud1_31.12f", 0x040001, 0x20000, CRC(e1239351) SHA1(7437a5e93ed72b8a52292aeb71c678e1462c8578) )
	ROM_LOAD16_BYTE ( "psud1_24.9e",  0x080000, 0x20000, CRC(22ef4de9) SHA1(358acdce233182280e5eb77da178ec0f08beca7f) )
	ROM_LOAD16_BYTE ( "psud1_28.9f",  0x080001, 0x20000, CRC(e45f5b6d) SHA1(daf25f24f8955387086acd337b19dfea5507adb8) )
	ROM_LOAD16_BYTE ( "psu_25.10e",   0x0c0000, 0x20000, CRC(c51acc94) SHA1(34ffd6392914e3e67d7d0804215bd1193846b554) )
	ROM_LOAD16_BYTE ( "psu_29.10f",   0x0c0001, 0x20000, CRC(52dce1ca) SHA1(45277abe34feacdcaedaec56f513b7437d4260e9) )
	ROM_LOAD16_WORD_SWAP( "ps_21.6f", 0x100000, 0x80000, CRC(8affa5a9) SHA1(268760b83b1723ff50a019ec51ef7af2e49935bf) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m.3a",  0x000000, 0x80000, CRC(77b7ccab) SHA1(e08e5d55a79e4c0c8ca819d6d7d2a14f753c6ec3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m.5a",  0x000002, 0x80000, CRC(0122720b) SHA1(5f0d3097e097f64106048156fbb0d343fe78fffa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m.4a",  0x000004, 0x80000, CRC(64fa58d4) SHA1(d4a774285ed15273195b6b26d2965ce370e54e73) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m.6a",  0x000006, 0x80000, CRC(60da42c8) SHA1(95eec4a58d9628a2d9764951dd8dc11e4860a899) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisherud1.key", 0x00, 0x80, CRC(c22c07f9) SHA1(b726dfed90c288ee71ab6d6035b0efcba1f18f6a) )
ROM_END

ROM_START( punisherud2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "psud2.23", 0x000000, 0x80000, CRC(019efb28) SHA1(1790db51ce7cd1281932359de6e4e1e046db0369) )
	ROM_LOAD16_WORD_SWAP( "psud2.22", 0x080000, 0x80000, CRC(c0110a4e) SHA1(43f6086634c332a58d95b0b51995ba1ab8ed1367) )
	ROM_LOAD16_WORD_SWAP( "ps_21.6f", 0x100000, 0x80000, CRC(8affa5a9) SHA1(268760b83b1723ff50a019ec51ef7af2e49935bf) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m.3a",  0x000000, 0x80000, CRC(77b7ccab) SHA1(e08e5d55a79e4c0c8ca819d6d7d2a14f753c6ec3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m.5a",  0x000002, 0x80000, CRC(0122720b) SHA1(5f0d3097e097f64106048156fbb0d343fe78fffa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m.4a",  0x000004, 0x80000, CRC(64fa58d4) SHA1(d4a774285ed15273195b6b26d2965ce370e54e73) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m.6a",  0x000006, 0x80000, CRC(60da42c8) SHA1(95eec4a58d9628a2d9764951dd8dc11e4860a899) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisherud1.key", 0x00, 0x80, CRC(c22c07f9) SHA1(b726dfed90c288ee71ab6d6035b0efcba1f18f6a) )
ROM_END

/**************************************
 Street Fighter II': Champion Edition
****************************************/

ROM_START( sf2cehack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack01.8f", 0x000000, 0x80000, CRC(3b9131f5) SHA1(7dcdb437a237092d9417f026be22c684a63a4620) )
	ROM_LOAD16_WORD_SWAP( "s92_22b.7f",  0x080000, 0x80000, CRC(2bbe15ed) SHA1(a8e2edef62fa99c5ef701b28bfb6bc42f3af183d) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD( "sf2d__23_hack02.rom",      0x000000, 0x80000, CRC(b8e256d1) SHA1(629a404beda20720ec9c01690f65310dda81e75d) )
	ROM_LOAD16_WORD( "sf2d__22.rom",      0x080000, 0x80000, CRC(fe9d9cf5) SHA1(91afb25d8c0fd1a721f982cebf8fdf563fe11760) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack03 ) //sf2ce3q
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack03.8f", 0x000000, 0x80000, CRC(1a98a59b) SHA1(dbe968463aea1a173fe74416352df0300ee854dd) )
	ROM_LOAD16_WORD_SWAP( "s92_22b_hack03.7f",  0x080000, 0x80000, CRC(3a260c4f) SHA1(55455b60a36e75a96ea6f38d1d131489060a10df) )
	ROM_LOAD16_WORD_SWAP( "s92_21a_hack03.6f",  0x100000, 0x80000, CRC(73bf4606) SHA1(8b2489b88a781ab88387dffaafa39495f0a3c497) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m_hac03.3c", 0x400000, 0x80000, CRC(d823d171) SHA1(6716a0f94cd2801279d135b61190a6bdf93122ae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m_hac03.4c", 0x400002, 0x80000, CRC(4ca06110) SHA1(b121ed9bd741909c8f16d267b7b20b9ffc8b958b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m_hac03.5c", 0x400004, 0x80000, CRC(7cefb44f) SHA1(a15c0a297b17216ee78213c5694dc8dcb2945a8e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m_hac03.6c", 0x400006, 0x80000, CRC(f9d396d9) SHA1(d877695416b6fff957d378c989547fb52bc1c494) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack04 ) //sf2ce3q
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack04.8f", 0x000000, 0x80000, CRC(e65e524d) SHA1(15f4fe3328e74c41ca9e2c6af9a17fe3f6f081c8) )
	ROM_LOAD16_WORD_SWAP( "s92_22b_hack04.7f",  0x080000, 0x80000, CRC(c2a3d649) SHA1(bc200e637d4eb102f3e269d757ddae3357ddb191) )
	ROM_LOAD16_WORD_SWAP( "s92_21a_hack03.6f",  0x100000, 0x80000, CRC(73bf4606) SHA1(8b2489b88a781ab88387dffaafa39495f0a3c497) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m_hac03.3c", 0x400000, 0x80000, CRC(d823d171) SHA1(6716a0f94cd2801279d135b61190a6bdf93122ae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m_hac03.4c", 0x400002, 0x80000, CRC(4ca06110) SHA1(b121ed9bd741909c8f16d267b7b20b9ffc8b958b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m_hac03.5c", 0x400004, 0x80000, CRC(7cefb44f) SHA1(a15c0a297b17216ee78213c5694dc8dcb2945a8e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m_hac03.6c", 0x400006, 0x80000, CRC(f9d396d9) SHA1(d877695416b6fff957d378c989547fb52bc1c494) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack05 ) //sf2ce1q
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack05.8f", 0x000000, 0x80000, CRC(cca48622) SHA1(8796a9504e7d11b64b848fcd23239d00fb15c0ec) )
	ROM_LOAD16_WORD_SWAP( "s92_22b_hack05.7f",  0x080000, 0x80000, CRC(b9e810ec) SHA1(335742f3de206c090897ceac88011e09002ec245) )
	ROM_LOAD16_WORD_SWAP( "s92_21a_hack05.6f",  0x100000, 0x80000, CRC(706fbb6c) SHA1(cbb609444a793af3194b2705da9101668baaa382) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m_hack05.3c", 0x400000, 0x80000, CRC(c5e31ea7) SHA1(818a0a756d82965643462082b8762d401da4b23a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m_hack05.4c", 0x400002, 0x80000, CRC(65cf5801) SHA1(cf5fc40d52b55040da610481fbb71fff34ef845d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m_hack05.5c", 0x400004, 0x80000, CRC(4859584a) SHA1(648d97ab6e822a98bc981e96958899ac0be32cbe) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m_hack05.6c", 0x400006, 0x80000, CRC(718543af) SHA1(9bf7c456a4f0ee1ccb4ac78d0a6718a75bc5ec46) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack06 ) //sf2ce1q
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack06.8f", 0x000000, 0x80000, CRC(fd9faded) SHA1(068bcbef6bf8b1a105502718af1e0cb713402960) )
	ROM_LOAD16_WORD_SWAP( "s92_22b_hack05.7f",  0x080000, 0x80000, CRC(b9e810ec) SHA1(335742f3de206c090897ceac88011e09002ec245) )
	ROM_LOAD16_WORD_SWAP( "s92_21a_hack05.6f",  0x100000, 0x80000, CRC(706fbb6c) SHA1(cbb609444a793af3194b2705da9101668baaa382) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m_hack05.3c", 0x400000, 0x80000, CRC(c5e31ea7) SHA1(818a0a756d82965643462082b8762d401da4b23a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m_hack05.4c", 0x400002, 0x80000, CRC(65cf5801) SHA1(cf5fc40d52b55040da610481fbb71fff34ef845d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m_hack05.5c", 0x400004, 0x80000, CRC(4859584a) SHA1(648d97ab6e822a98bc981e96958899ac0be32cbe) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m_hack05.6c", 0x400006, 0x80000, CRC(718543af) SHA1(9bf7c456a4f0ee1ccb4ac78d0a6718a75bc5ec46) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack07 ) //sf2cezhv
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack07.8f", 0x000000, 0x80000, CRC(3b9131f5) SHA1(7dcdb437a237092d9417f026be22c684a63a4620) )
	ROM_LOAD16_WORD_SWAP( "s92_22b.7f",  0x080000, 0x80000, CRC(2bbe15ed) SHA1(a8e2edef62fa99c5ef701b28bfb6bc42f3af183d) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18_s33.11c",  0x00000, 0x20000, CRC(6cda9fc8) SHA1(cd846cc3074773ae96bba62a1709ecbb1f6135eb) )
	ROM_LOAD( "s92_19_s33.12c",  0x20000, 0x20000, CRC(d54dc6ae) SHA1(662d6a3260892376428b29d374d255f4cf7352b3) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack08 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack08.8f",  0x000000, 0x80000, CRC(22a4c364) SHA1(311a1fd2101ea68c3c8570ef65b11175921a1491) )
	ROM_LOAD16_WORD_SWAP( "s92_22b_hack08.7f",   0x080000, 0x80000, CRC(779b8751) SHA1(d4e52efaed3caef45f1ab246f5320a82d4d2d930) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m_hack08.7a",  0x200000, 0x80000, CRC(2e8de444) SHA1(29e2a70b299aa12da5f9bfa5ac9e29f74a469900) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m_hack08.9a",  0x200002, 0x80000, CRC(e414f027) SHA1(ffc5cde2e61b9c9c4d69243b8d4443fcb495aee3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m_hack08.8a",  0x200004, 0x80000, CRC(6b4e8fd5) SHA1(253b6bbd6cb76b45ae7debdd40c36a8df82bc90d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m_hack08.10a", 0x200006, 0x80000, CRC(d5078f30) SHA1(af326cdef5168a1adf72d778242eadd86e8b2250) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m_hack08.3c", 0x400000, 0x80000, CRC(12b79102) SHA1(61dc50c722d6e712d91bf14957fa9b61262e60af) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m_hack08.5c", 0x400002, 0x80000, CRC(cfbd83ee) SHA1(95e0d8d997e7385e410f85838a8bedd9e0937309) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m_hack08.4c", 0x400004, 0x80000, CRC(73c40b6d) SHA1(e73f1a4d73a591df124f0e1298eed074adeee3cd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m_hack08.6c", 0x400006, 0x80000, CRC(ff75a7cf) SHA1(7983773b1cb87d47192c0b4e478ed59693971bf7) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack09 ) //sf2celw
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack09.8f",  0x000000, 0x80000, CRC(139fe8ab) SHA1(8ff4dad9506768fdc28fb41ab10202dc98729ac9) )
	ROM_LOAD16_WORD_SWAP( "s92_22b_hack08.7f",   0x080000, 0x80000, CRC(779b8751) SHA1(d4e52efaed3caef45f1ab246f5320a82d4d2d930) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m_hack08.7a",  0x200000, 0x80000, CRC(2e8de444) SHA1(29e2a70b299aa12da5f9bfa5ac9e29f74a469900) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m_hack08.9a",  0x200002, 0x80000, CRC(e414f027) SHA1(ffc5cde2e61b9c9c4d69243b8d4443fcb495aee3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m_hack08.8a",  0x200004, 0x80000, CRC(6b4e8fd5) SHA1(253b6bbd6cb76b45ae7debdd40c36a8df82bc90d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m_hack08.10a", 0x200006, 0x80000, CRC(d5078f30) SHA1(af326cdef5168a1adf72d778242eadd86e8b2250) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m_hack08.3c",  0x400000, 0x80000, CRC(12b79102) SHA1(61dc50c722d6e712d91bf14957fa9b61262e60af) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m_hack08.5c",  0x400002, 0x80000, CRC(cfbd83ee) SHA1(95e0d8d997e7385e410f85838a8bedd9e0937309) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m_hack08.4c",  0x400004, 0x80000, CRC(73c40b6d) SHA1(e73f1a4d73a591df124f0e1298eed074adeee3cd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m_hack08.6c",  0x400006, 0x80000, CRC(ff75a7cf) SHA1(7983773b1cb87d47192c0b4e478ed59693971bf7) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18_s33.11c",  0x00000, 0x20000, CRC(6cda9fc8) SHA1(cd846cc3074773ae96bba62a1709ecbb1f6135eb) )
	ROM_LOAD( "s92_19_s33.12c",  0x20000, 0x20000, CRC(d54dc6ae) SHA1(662d6a3260892376428b29d374d255f4cf7352b3) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack10 ) //sf2ceub
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sf2pun_hack10.23",    0x000000, 0x80000, CRC(71ef3294) SHA1(98ea793915e32474b59ffc9be2aa8eeeb174f064) )
	ROM_LOAD16_WORD_SWAP( "sf2pun.22",    0x080000, 0x80000, CRC(0786f114) SHA1(4a6b52c98c839fcde2b7f425739569abc74c91f4) )
	ROM_LOAD16_WORD_SWAP( "sf2red.21",    0x100000, 0x80000, CRC(52c486bb) SHA1(b7df7b10faa4c9a2f86ebf64cd63ac148d62dd09) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack11 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack11.23",   0x000000, 0x80000, CRC(190f5419) SHA1(7fc7f3b6788d25b190bda3b3b6cf76a396d7d586) )
	ROM_LOAD16_WORD_SWAP( "s92_22b_hack11.22",    0x080000, 0x80000, CRC(2b329193) SHA1(b1576b610e384fbeaef7be711888fb3fa3f10b1a) )
	ROM_LOAD16_WORD_SWAP( "s92_21a_hack11.6f",    0x100000, 0x80000, CRC(b4f13bef) SHA1(5e6501c157890899848bccb34db06b3570e84c17) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack12 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack12.8f", 0x000000, 0x80000, CRC(997f551e) SHA1(44d907f868c400497b76b0e3328023b9f91c60a7) )
	ROM_LOAD16_WORD_SWAP( "s92_22b_hack12.7f",  0x080000, 0x80000, CRC(414ab00b) SHA1(44ff311280affa40fd4ea28dffc1a1cf65d5ea11) )
	ROM_LOAD16_WORD_SWAP( "s92_21a_hack12.6f",  0x100000, 0x80000, CRC(1221db31) SHA1(a68ff94c074af1bb51b3177f90f32be31c7982a4) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m_hack12.3a",  0x000000, 0x80000, CRC(a8f70643) SHA1(0d3ab7fe1d0d15397a79c9bd304f22593a9b8d87) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m_hack12.5a",  0x000002, 0x80000, CRC(f73f1913) SHA1(b36db11822f5601726892726f8505b7e8b676ab6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m_hack12.4a",  0x000004, 0x80000, CRC(a80234b4) SHA1(e8c3e8030fa2ce69465d97ccb02de622e9214b01) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m_hack12.6a",  0x000006, 0x80000, CRC(4d910b53) SHA1(1f28fe150ddf77c91c8ae998ee52e068327335d5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m_hack12.7a",  0x200000, 0x80000, CRC(01ae6240) SHA1(59391e9681497ac6ec8a2736e15864f83dffdb0e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m_hack12.9a",  0x200002, 0x80000, CRC(88dea20a) SHA1(d8e71ff94e796d7720fa0d73c261dca783262b5a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m_hack12.8a",  0x200004, 0x80000, CRC(7ea140b2) SHA1(2660ece5a443c6e32344627af9f81dc7c8cd3ea4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m_hack12.10a", 0x200006, 0x80000, CRC(fbc81a7e) SHA1(b950566052114da540a0893e733ca8c7e8847003) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m_hack12.3c",  0x400000, 0x80000, CRC(78e86cf4) SHA1(02de07c66d8a899f0d99c5f91b0795a7a22834ae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m_hack12.5c",  0x400002, 0x80000, CRC(2f8e6dc9) SHA1(b9ee9fd782cb23d6652f100f5c25944dfdd22a3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m_hack12.4c",  0x400004, 0x80000, CRC(70095fdc) SHA1(8fb4b22841847858c0ac30eca49109e99709c670) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m_hack12.6c",  0x400006, 0x80000, CRC(d14d18e5) SHA1(72aebfb2e589a3fa248e3ffa2723f77f1139b787) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09_hack12.11a",  0x00000, 0x08000, CRC(a379fdc5) SHA1(e9de38c13bd665698528bc102b1b16e9bdcae65b) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18_hack12.11c",  0x00000, 0x20000, CRC(6aa5d7fa) SHA1(87cfea3a9f62653fa236f49b5b25b927cff30a02) )
	ROM_LOAD( "s92_19_hack12.12c",  0x20000, 0x20000, CRC(f92f5a4f) SHA1(3f1d477ab0299d2783231c3bd9983513a85b2fe6) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cehack13 )  //sf2hf
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92e_23b_hack13.8f", 0x000000, 0x80000, CRC(7e5e9fa5) SHA1(eeddd2344a984bf3c386db4a200e2b1e9535343f) )
	ROM_LOAD16_WORD_SWAP( "s92_22b_hack13.7f", 0x080000, 0x80000, CRC(34a6a55f) SHA1(26978953bda0a764aa9d29dac61f71951719f69c) )
	ROM_LOAD16_WORD_SWAP( "s92_21a_hack13.6f", 0x100000, 0x80000, CRC(d47ed80a) SHA1(79e759e01fb79716bfdb85982b4de04d944b9cc2) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROM_LOAD64_WORD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) )
	ROM_LOAD64_WORD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) )
	ROM_LOAD64_WORD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) )
	ROM_LOAD64_WORD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) )
	ROM_LOAD64_WORD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) )
	ROM_LOAD64_WORD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) )
	ROM_LOAD64_WORD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) )
	ROM_LOAD64_WORD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) )
	ROM_LOAD64_WORD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) )
	ROM_LOAD64_WORD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) )
	ROM_LOAD64_WORD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) )
	ROM_LOAD64_WORD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

/********
 bootleg
**********/

ROM_START( sf2mega2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf3a-1.040", 0x000000, 0x80000, CRC(9e6d058a) SHA1(8c9adca7b65dc929c325c0a62304d24dc0902c08) )
	ROM_LOAD16_BYTE( "sf3a-3.040", 0x000001, 0x80000, CRC(518d8404) SHA1(635d8ac07126caf3c623d1f28aad38c5bc4c4bae) )
	ROM_LOAD16_BYTE( "sf3a-2", 0x100000, 0x20000, CRC(fca4fc1e) SHA1(2b05d67443af099f95ef50f5e25d7a74b957e7a5) )
	ROM_LOAD16_BYTE( "sf3a-4", 0x100001, 0x20000, CRC(cfdd6f54) SHA1(2aa3f5a7b36930185382c64712cc0cfceb6f1ab3) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2amf5 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sfu9-1.040", 0x000000, 0x80000, CRC(95306baf) SHA1(471d1578607ae1090aa46cb111a8c2745d1fd47b) )
	ROM_LOAD16_BYTE( "sfu9-3.040", 0x000001, 0x80000, CRC(21024d5f) SHA1(986b3910ce749f4ad42e1f86537a8fc3f0f3f867) )
	ROM_LOAD16_BYTE( "t-4.u54", 0x100000, 0x40000, CRC(0b3fe5dd) SHA1(9b66cb867da61595f53d1c9e6b48c6bb7e06e1e0) )
	ROM_LOAD16_BYTE( "t-3.u38", 0x100001, 0x40000, CRC(dbee7b18) SHA1(e56af12fc9d30e92d37e688ff621ea09abb94b53) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2cejabl )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sfu7-1.040", 0x000000, 0x80000, CRC(866a9b31) SHA1(92f89084293b69a9d5cd8d282ffaaca0739f1b03) )
	ROM_LOAD16_BYTE( "sfu7-3.040", 0x000001, 0x80000, CRC(f3a45593) SHA1(0ba0d05f904ac17cd34c0a7c9dd0a20759ff4e78) )
	ROM_LOAD16_BYTE( "u221.1m", 0x100000, 0x20000, CRC(d1707134) SHA1(5bfdf7bc57bdb85183647ebb175346070dd102ee) )
	ROM_LOAD16_BYTE( "u195.1m", 0x100001, 0x20000, CRC(cd1d5666) SHA1(8befd2c324eb29bdad6fc8fb2554cdfaf9808f9b) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2h11.key", 0x00, 0x80, CRC(822729a2) SHA1(acaadef38fd97dba215c13688061cee87d877c19) )
ROM_END

ROM_START( sf2rb5 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sfu8-1.040", 0x000000, 0x80000, CRC(10ec67fe) SHA1(9eb30a0f64bf29028f89f9af74cb9d840ed197e2) )
	ROM_LOAD16_BYTE( "sfu8-3.040", 0x000001, 0x80000, CRC(92eb3a1c) SHA1(0ee294c8b82b100f98da697562f9644b71cabcdd) )
	ROM_LOAD16_BYTE( "u221t.1m", 0x100000, 0x20000, CRC(1073b7b6) SHA1(81ca1eab65ceac69520584bb23a684ccb9d92f89) )
	ROM_LOAD16_BYTE( "sfu8-4.010", 0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2h11.key", 0x00, 0x80, CRC(822729a2) SHA1(acaadef38fd97dba215c13688061cee87d877c19) )
ROM_END

ROM_START( sf2hfjb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "222-040.13",   0x000000, 0x80000, CRC(ec6f5cb3) SHA1(24b3fc88a08a721985b053120997090bc394bc8e) )
	ROM_LOAD16_BYTE( "196-040.13",   0x000001, 0x80000, CRC(0e9ac52b) SHA1(2c5faf7d8b598f2110f389aefa1a02e2281382ee) )
	ROM_LOAD16_BYTE( "221-010.13",   0x100000, 0x20000, CRC(8226c11c) SHA1(9588bd64e338901394805aca8a234f880674dc60) )
	ROM_LOAD16_BYTE( "sfu8-4.010",   0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s2t_10.bin",   0x400000, 0x80000, CRC(3c042686) SHA1(307e1ca8ad0b11f3265b7e5467ba4c90f90ec97f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s2t_11.bin",   0x400002, 0x80000, CRC(8b7e7183) SHA1(c8eaedfbddbf0b83311d2dbb9e19a1efef0dffa9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s2t_12.bin",   0x400004, 0x80000, CRC(293c888c) SHA1(5992ea9aa90fdd8b9dacca9d2a1fdaf25ac2cb65) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s2t_13.bin",   0x400006, 0x80000, CRC(842b35a4) SHA1(35864a140a0c8d76501e69b2e01bc4ad76f27909) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2rbpr )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD( "sf2rbpr.23",       0x000000, 0x80000, CRC(450532b0) SHA1(14d5ff44ce97247ef4c42147157856d16c5fb4b8) )
	ROM_LOAD16_WORD( "sf2rbpr.22",       0x080000, 0x80000, CRC(20fd1382) SHA1(7b32b295ac4e61a7f7ae395d9dfc10d80747d833) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2amf6 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "u222",         0x000000, 0x80000, CRC(03991fba) SHA1(6c42bf15248640fdb3e98fb01b0a870649deb410) )
	ROM_LOAD16_BYTE( "4.amf",        0x000001, 0x80000, CRC(39f15a1e) SHA1(901c4fea76bf5bff7330ed07ffde54cdccdaa680) )
	ROM_LOAD16_BYTE( "u221.rom",     0x100000, 0x20000, CRC(64e6e091) SHA1(32ec05db955e538d4ada26d19ee50926f74b684f) )
	ROM_LOAD16_BYTE( "u195.rom",     0x100001, 0x20000, CRC(c95e4443) SHA1(28417dee9ccdfa65b0f4a92aa29b90279fe8cd85) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )
	// These map over 0x400000 to 0x4FFFFF
	ROMX_LOAD( "stf2th-10",  0x400000, 0x20000, CRC(84427d1b) SHA1(f988a2b53c8cc46eeb8032084f24966a539b3734) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-12",  0x400002, 0x20000, CRC(55bc790c) SHA1(a1114b89f6fa4487210477676984c77ad94b5ef8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-9",   0x400004, 0x20000, CRC(f8725add) SHA1(fa3fcf6637ee4dd7667bd89766074b3c6ba4f166) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-11",  0x400006, 0x20000, CRC(c2a5373e) SHA1(602b32e5ecc7007efe9ad30751040ee52b81f59a) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2amf7 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "t-2.u52", 0x000000, 0x80000, CRC(0d305e8b) SHA1(7094160abbf24c119a575d93e3fe1ab84b537de0) )
	ROM_LOAD16_BYTE( "t-1.u36", 0x000001, 0x80000, CRC(137d8665) SHA1(cf4805a11ab614ce5b7e1302ac14ba50fb01e5f4) )
	ROM_LOAD16_BYTE( "t-4.u54", 0x100000, 0x40000, CRC(0b3fe5dd) SHA1(9b66cb867da61595f53d1c9e6b48c6bb7e06e1e0) )
	ROM_LOAD16_BYTE( "t-3.u38", 0x100001, 0x40000, CRC(dbee7b18) SHA1(e56af12fc9d30e92d37e688ff621ea09abb94b53) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",  0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",  0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",  0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",  0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",  0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )
	// These map over 0x400000 to 0x4FFFFF
	ROMX_LOAD( "stf2th-10",   0x400000, 0x20000, CRC(84427d1b) SHA1(f988a2b53c8cc46eeb8032084f24966a539b3734) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-12",   0x400002, 0x20000, CRC(55bc790c) SHA1(a1114b89f6fa4487210477676984c77ad94b5ef8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-9",    0x400004, 0x20000, CRC(f8725add) SHA1(fa3fcf6637ee4dd7667bd89766074b3c6ba4f166) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-11",   0x400006, 0x20000, CRC(c2a5373e) SHA1(602b32e5ecc7007efe9ad30751040ee52b81f59a) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2tlona )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "tl4mt.1",   0x000000, 0x80000, CRC(158635ca) SHA1(878b56064861993ac92fbd88eb1117d3680fe7d7) )
	ROM_LOAD16_BYTE( "tl4m.2",    0x000001, 0x80000, CRC(882cd1c4) SHA1(0cb971756352b1022ecd309b1bc3688c1f1acbd8) )
	ROM_LOAD16_BYTE( "u221t.1m",  0x100000, 0x20000, CRC(1073b7b6) SHA1(81ca1eab65ceac69520584bb23a684ccb9d92f89) )
	ROM_LOAD16_BYTE( "u195t.1m",  0x100001, 0x20000, CRC(db7e1f72) SHA1(1ca99a3b425ac137f3c104cf4deb50d9431dacdd) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2tlonb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "tl4m.1",   0x000000, 0x80000, CRC(afc7bd18) SHA1(ef7af7fb3563073b96563274ec48783feb2be757) )
	ROM_LOAD16_BYTE( "tl4m.2",   0x000001, 0x80000, CRC(882cd1c4) SHA1(0cb971756352b1022ecd309b1bc3688c1f1acbd8) )
	ROM_LOAD16_BYTE( "u221.1m",  0x100000, 0x20000, CRC(d1707134) SHA1(5bfdf7bc57bdb85183647ebb175346070dd102ee) )
	ROM_LOAD16_BYTE( "u195.1m",  0x100001, 0x20000, CRC(cd1d5666) SHA1(8befd2c324eb29bdad6fc8fb2554cdfaf9808f9b) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2tlonc )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "tl4m.1",  0x000000, 0x80000, CRC(afc7bd18) SHA1(ef7af7fb3563073b96563274ec48783feb2be757) )
	ROM_LOAD16_BYTE( "tl4m.2",  0x000001, 0x80000, CRC(882cd1c4) SHA1(0cb971756352b1022ecd309b1bc3688c1f1acbd8) )
	ROM_LOAD16_BYTE( "sf11-2.010",  0x100000, 0x20000, CRC(f8a5cd53) SHA1(f474e6d24f25ca9a126bd68b02089a0161e2cc0d) )
	ROM_LOAD16_BYTE( "u195t.1m",  0x100001, 0x20000, CRC(db7e1f72) SHA1(1ca99a3b425ac137f3c104cf4deb50d9431dacdd) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2red2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf3d5-1040", 0x000000, 0x80000, CRC(bcdd2c3a) SHA1(eff98e425f283afc69064e8bc73f769e0aab93ed) )
	ROM_LOAD16_BYTE( "sf3d5-3040", 0x000001, 0x80000, CRC(01965987) SHA1(42abce3aa983ac4143490c0ab2e772a154905860) )
	ROM_LOAD16_BYTE( "sf3d5-2010", 0x100000, 0x20000, CRC(dd2e1d31) SHA1(22b341a7365ba4a52c9ee2244d68409c5e86bcf0) )
	ROM_RELOAD(                 0x140000, 0x20000 )
	ROM_LOAD16_BYTE( "u195.rom", 0x100001, 0x20000, CRC(c95e4443) SHA1(28417dee9ccdfa65b0f4a92aa29b90279fe8cd85) )
	ROM_RELOAD(                 0x140001, 0x20000 )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2v0042 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf3g-1040", 0x000000, 0x80000, CRC(c90559a5) SHA1(f45563c79cf5ce610f92ca84c96d337cf6c9a979) )
	ROM_LOAD16_BYTE( "sf3g-3040", 0x000001, 0x80000, CRC(81f36682) SHA1(53776084c973c0b7aafb203e8efcfd5f5c659c93) )
	ROM_LOAD16_BYTE( "sf3g-2010", 0x100000, 0x20000, CRC(9eee20a1) SHA1(a6769744094dc0e65f9f34ef36929e7e8ae6155b) )
	ROM_RELOAD(                 0x140000, 0x20000 )
	ROM_LOAD16_BYTE( "sf3g-4010", 0x100001, 0x20000, CRC(6ac3d875) SHA1(ab4384d7a9194b2628836013d3d9f275d55c77bb) )
	ROM_RELOAD(                 0x140001, 0x20000 )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2yyc2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf6-1040", 0x000000, 0x80000, CRC(ccd74822) SHA1(5f64585335ccc0fb1a97339532a6694076e2b6f2) )
	ROM_LOAD16_BYTE( "sf6-3040", 0x000001, 0x80000, CRC(2a48b557) SHA1(2e74925a925f86619d4f8e633af718a5eaa8c585) )
	ROM_LOAD16_BYTE( "u221.rom", 0x100000, 0x20000, CRC(64e6e091) SHA1(32ec05db955e538d4ada26d19ee50926f74b684f) )
	ROM_RELOAD(                 0x140000, 0x20000 )
	ROM_LOAD16_BYTE( "u195.rom", 0x100001, 0x20000, CRC(c95e4443) SHA1(28417dee9ccdfa65b0f4a92aa29b90279fe8cd85) )
	ROM_RELOAD(                 0x140001, 0x20000 )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

/**************************************
 Street Fighter II: The World Warrior
*****************************************/

ROM_START( sf2hack01 ) //sf2g12
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf2j_30h_hack01.11e", 0x00000, 0x20000, CRC(cba2236b) SHA1(f486c15b15f7fc0a70e9ad4cf7e4a062644889ca) )
	ROM_LOAD16_BYTE( "sf2j_37h_hack01.11f", 0x00001, 0x20000, CRC(5b80ffc0) SHA1(d36cffc958fbf1970f0f0ab4cb07e8107801ce26) )
	ROM_LOAD16_BYTE( "sf2j_31h_hack01.12e", 0x40000, 0x20000, CRC(7e4af671) SHA1(86391415edc6d6669eec586be91d78e9c6ce6d34) )
	ROM_LOAD16_BYTE( "sf2j_38h_hack01.12f", 0x40001, 0x20000, CRC(bf58df60) SHA1(694b6cfb5190f74825e53c6c601e5ca57c8dc2ec) )
	ROM_LOAD16_BYTE( "sf2j_28h_hack01.9e",  0x80000, 0x20000, CRC(3d96d4d2) SHA1(e525345b0ad81cb2dfdc2b229071c492068d5d52) )
	ROM_LOAD16_BYTE( "sf2j_35h_hack01.9f",  0x80001, 0x20000, CRC(c02a2be3) SHA1(eff499e7ddf0c8e0d357290db84acc3c3fb71945) )
	ROM_LOAD16_BYTE( "sf2j_29a_hack01.10e", 0xc0000, 0x20000, CRC(0bb77024) SHA1(71f501fd50a6658b1b2cb5f3c8d9961dce9beeb5) )
	ROM_LOAD16_BYTE( "sf2j_36a_hack01.10f", 0xc0001, 0x20000, CRC(48256574) SHA1(bc9b151000fd75233129a3dd1140e224734cab49) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2-5m.4a",  0x000000, 0x80000, CRC(22c9cc8e) SHA1(b9194fb337b30502c1c9501cd6c64ae4035544d4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-7m.6a",  0x000002, 0x80000, CRC(57213be8) SHA1(3759b851ac0904ec79cbb67a2264d384b6f2f9f9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-1m.3a",  0x000004, 0x80000, CRC(ba529b4f) SHA1(520840d727161cf09ca784919fa37bc9b54cc3ce) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-3m.5a",  0x000006, 0x80000, CRC(4b1b33a8) SHA1(2360cff890551f76775739e2d6563858bff80e41) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-6m.4c",  0x200000, 0x80000, CRC(2c7e2229) SHA1(357c2275af9133fd0bd6fbb1fa9ad5e0b490b3a2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-8m.6c",  0x200002, 0x80000, CRC(b5548f17) SHA1(baa92b91cf616bc9e2a8a66adc777ffbf962a51b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-2m.3c",  0x200004, 0x80000, CRC(14b84312) SHA1(2eea16673e60ba7a10bd4d8f6c217bb2441a5b0e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-4m.5c",  0x200006, 0x80000, CRC(5e9cd89a) SHA1(f787aab98668d4c2c54fc4ba677c0cb808e4f31e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_25_hack01.8d",  0x400000, 0x80000, CRC(4267b696) SHA1(af65e3b2cc3b7a7f39d5e7e598da7f4c9d351eea) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_27_hack01.10d", 0x400002, 0x80000, CRC(df9b9146) SHA1(2029aa59c1646af0fd7fa06f353edcbf7f7792de) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_24_hack01.7d",  0x400004, 0x80000, CRC(a08a9786) SHA1(80a79e45c003fbc95cc5cd0d037b55f2f7fec64c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_26_hack01.9d",  0x400006, 0x80000, CRC(80feac31) SHA1(f16ce88634d2328eae93f8128423bb311cac88e6) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",  0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sf2_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "sf2_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sf2.key",  0x00, 0x80, CRC(3cf6f06f) SHA1(7512a185d461f2b37edfc19e31a45d53600fbe44) )
ROM_END

ROM_START( sf2hack02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf2j_30h_hack02.11e", 0x00000, 0x20000, CRC(919d5964) SHA1(a7943517e9f4bdb65991ac4a5097425eddcc05ef) )
	ROM_LOAD16_BYTE( "sf2j_37h_hack02.11f", 0x00001, 0x20000, CRC(574a9966) SHA1(f42ecb8b57c615352d127cfc55ae0d70525c40f2) )
	ROM_LOAD16_BYTE( "sf2j31.bin", 0x40000, 0x20000, CRC(fe15cb39) SHA1(383478524881ea70d9e04c9b6143b8735b637eee) )
	ROM_LOAD16_BYTE( "sf2j38.bin", 0x40001, 0x20000, CRC(38614d70) SHA1(39c58096f3a8e01fb439639b742b83102bbaa7f6) )
	ROM_LOAD16_BYTE( "sf2j_28",    0x80000, 0x20000, CRC(2d4a1b8a) SHA1(9dce74c32fa9c63f38d33a03327b22e74d2118c1) )
	ROM_LOAD16_BYTE( "sf2j_35",    0x80001, 0x20000, CRC(5f622bdb) SHA1(4fe5797acc2645a1bd27d247457b6f24bfd60f96) )
	ROM_LOAD16_BYTE( "sf2_29b.10e", 0xc0000, 0x20000, CRC(bb4af315) SHA1(75f0827f4f7e9f292add46467f8d4fe19b2514c9) )
	ROM_LOAD16_BYTE( "sf2_36b.10f", 0xc0001, 0x20000, CRC(c02a13eb) SHA1(b807cc495bff3f95d03b061fc629c95f965cb6d8) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2_06",  0x000000, 0x80000, CRC(d3aab35d) SHA1(bc90464bc38b326b46f0da97008116ee639e2598) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_08",  0x000002, 0x80000, CRC(f6a68d56) SHA1(4ef2668a245fb207c599f0e72e979f8c0191df25) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_05",  0x000004, 0x80000, CRC(1ddcda55) SHA1(494338ac59e4253177b731bd6ad116a63f7ded8c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_07",  0x000006, 0x80000, CRC(d3274004) SHA1(a278e0740806cf8098058d1c33eb0964cc130ded) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_15",  0x200000, 0x80000, CRC(f8710c69) SHA1(a298117a7869b0891220c229d0dceba7ac6bf594) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_17",  0x200002, 0x80000, CRC(dd376567) SHA1(a817c999098b0274ed2c052b96c562bed407b7b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_14",  0x200004, 0x80000, CRC(c754e2c4) SHA1(7936eaa669c84742c1511768bb9039c26b2fb3c3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_16",  0x200006, 0x80000, CRC(0d4799bd) SHA1(5e63e889cabc4436c2a49997c9d0a47529d264ad) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_25",  0x400000, 0x80000, CRC(a6671144) SHA1(f4017ad15784078c00ef76220f4e5bdba61a6495) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_27",  0x400002, 0x80000, CRC(008b2bdd) SHA1(a048a70fe3c752b79e14eadf2369f068fc831439) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_24",  0x400004, 0x80000, CRC(0f8a9ec4) SHA1(cde0013df78333ebfbaacb9a9e212fbc0b2e04d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_26",  0x400006, 0x80000, CRC(0fb4241e) SHA1(f749daa6ecf018542ecf0f3711491eb85fac91b3) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",   0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sf2_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "sf2_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2c.key", 0x00, 0x80, CRC(fdc05d86) SHA1(f828e6171a271bc12a5c9ab5be237562e263ccdb) )
ROM_END

ROM_START( sf2hack03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf2e_30f_hack03.11e", 0x00000, 0x20000, CRC(481cc455) SHA1(cc7f0e6f0f31e654285b99ffff6559afefbd98bf) )
	ROM_LOAD16_BYTE( "sf2e_37f_hack03.11f", 0x00001, 0x20000, CRC(0e3ef26c) SHA1(596f7e7855acc2098597687f9f52188721ecd798) )
	ROM_LOAD16_BYTE( "sf2e_31g.12e", 0x40000, 0x20000, CRC(69a0a301) SHA1(86a3954335310865b14ce8b4e0e4499feb14fc12) )
	ROM_LOAD16_BYTE( "sf2e_38g.12f", 0x40001, 0x20000, CRC(5e22db70) SHA1(6565946591a18eaf46f04c1aa449ee0ae9ac2901) )
	ROM_LOAD16_BYTE( "sf2e_28g.9e",  0x80000, 0x20000, CRC(8bf9f1e5) SHA1(bbcef63f35e5bff3f373968ba1278dd6bd86b593) )
	ROM_LOAD16_BYTE( "sf2e_35g.9f",  0x80001, 0x20000, CRC(626ef934) SHA1(507bda3e4519de237aca919cf72e543403ec9724) )
	ROM_LOAD16_BYTE( "sf2_29b.10e",  0xc0000, 0x20000, CRC(bb4af315) SHA1(75f0827f4f7e9f292add46467f8d4fe19b2514c9) )
	ROM_LOAD16_BYTE( "sf2_36b.10f",  0xc0001, 0x20000, CRC(c02a13eb) SHA1(b807cc495bff3f95d03b061fc629c95f965cb6d8) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2-5m.4a",  0x000000, 0x80000, CRC(22c9cc8e) SHA1(b9194fb337b30502c1c9501cd6c64ae4035544d4) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "2" socket
	ROMX_LOAD( "sf2-7m.6a",  0x000002, 0x80000, CRC(57213be8) SHA1(3759b851ac0904ec79cbb67a2264d384b6f2f9f9) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "4" socket
	ROMX_LOAD( "sf2-1m.3a",  0x000004, 0x80000, CRC(ba529b4f) SHA1(520840d727161cf09ca784919fa37bc9b54cc3ce) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "1" socket
	ROMX_LOAD( "sf2-3m.5a",  0x000006, 0x80000, CRC(4b1b33a8) SHA1(2360cff890551f76775739e2d6563858bff80e41) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "3" socket
	ROMX_LOAD( "sf2-6m.4c",  0x200000, 0x80000, CRC(2c7e2229) SHA1(357c2275af9133fd0bd6fbb1fa9ad5e0b490b3a2) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "11" socket
	ROMX_LOAD( "sf2-8m.6c",  0x200002, 0x80000, CRC(b5548f17) SHA1(baa92b91cf616bc9e2a8a66adc777ffbf962a51b) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "13" socket
	ROMX_LOAD( "sf2-2m.3c",  0x200004, 0x80000, CRC(14b84312) SHA1(2eea16673e60ba7a10bd4d8f6c217bb2441a5b0e) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "10" socket
	ROMX_LOAD( "sf2-4m.5c",  0x200006, 0x80000, CRC(5e9cd89a) SHA1(f787aab98668d4c2c54fc4ba677c0cb808e4f31e) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "12" socket
	ROMX_LOAD( "sf2-13m.4d", 0x400000, 0x80000, CRC(994bfa58) SHA1(5669b845f624b10e7be56bfc89b76592258ce48b) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "21" socket
	ROMX_LOAD( "sf2-15m.6d", 0x400002, 0x80000, CRC(3e66ad9d) SHA1(9af9df0826988872662753e9717c48d46f2974b0) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "23" socket
	ROMX_LOAD( "sf2-9m.3d",  0x400004, 0x80000, CRC(c1befaa8) SHA1(a6a7f4725e52678cbd8d557285c01cdccb2c2602) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "20" socket
	ROMX_LOAD( "sf2-11m.5d", 0x400006, 0x80000, CRC(0627c831) SHA1(f9a92d614e8877d648449de2612fc8b43c85e4c2) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "22" socket

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",   0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sf2_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "sf2_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sf2.key",  0x00, 0x80, CRC(3cf6f06f) SHA1(7512a185d461f2b37edfc19e31a45d53600fbe44) )
ROM_END

ROM_START( sf2hack04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf2e_30f_hack04.11e", 0x00000, 0x20000, CRC(040af48a) SHA1(0e8d5b614934dad4f3fe75d267cee2fa8fd64c40) )
	ROM_LOAD16_BYTE( "sf2e_37f_hack04.11f", 0x00001, 0x20000, CRC(e028a8df) SHA1(336205ec0f27494e03afb1b6b1bf64bbbc8a3c40) )
	ROM_LOAD16_BYTE( "sf2e_31f_hack04.12e", 0x40000, 0x20000, CRC(6b57dab7) SHA1(7f8b1a540bef97dc1761e8d17051270edba31880) )
	ROM_LOAD16_BYTE( "sf2e_38f_hack04.12f", 0x40001, 0x20000, CRC(48d17918) SHA1(c122549cdf2a774af34a3ad39fe050e6c274e1af) )
	ROM_LOAD16_BYTE( "sf2e_28g.9e",  0x80000, 0x20000, CRC(8bf9f1e5) SHA1(bbcef63f35e5bff3f373968ba1278dd6bd86b593) )
	ROM_LOAD16_BYTE( "sf2e_35g.9f",  0x80001, 0x20000, CRC(626ef934) SHA1(507bda3e4519de237aca919cf72e543403ec9724) )
	ROM_LOAD16_BYTE( "sf2_29b.10e",  0xc0000, 0x20000, CRC(bb4af315) SHA1(75f0827f4f7e9f292add46467f8d4fe19b2514c9) )
	ROM_LOAD16_BYTE( "sf2_36b.10f",  0xc0001, 0x20000, CRC(c02a13eb) SHA1(b807cc495bff3f95d03b061fc629c95f965cb6d8) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2-5m.4a",  0x000000, 0x80000, CRC(22c9cc8e) SHA1(b9194fb337b30502c1c9501cd6c64ae4035544d4) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "2" socket
	ROMX_LOAD( "sf2-7m.6a",  0x000002, 0x80000, CRC(57213be8) SHA1(3759b851ac0904ec79cbb67a2264d384b6f2f9f9) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "4" socket
	ROMX_LOAD( "sf2-1m.3a",  0x000004, 0x80000, CRC(ba529b4f) SHA1(520840d727161cf09ca784919fa37bc9b54cc3ce) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "1" socket
	ROMX_LOAD( "sf2-3m.5a",  0x000006, 0x80000, CRC(4b1b33a8) SHA1(2360cff890551f76775739e2d6563858bff80e41) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "3" socket
	ROMX_LOAD( "sf2-6m.4c",  0x200000, 0x80000, CRC(2c7e2229) SHA1(357c2275af9133fd0bd6fbb1fa9ad5e0b490b3a2) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "11" socket
	ROMX_LOAD( "sf2-8m.6c",  0x200002, 0x80000, CRC(b5548f17) SHA1(baa92b91cf616bc9e2a8a66adc777ffbf962a51b) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "13" socket
	ROMX_LOAD( "sf2-2m.3c",  0x200004, 0x80000, CRC(14b84312) SHA1(2eea16673e60ba7a10bd4d8f6c217bb2441a5b0e) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "10" socket
	ROMX_LOAD( "sf2-4m.5c",  0x200006, 0x80000, CRC(5e9cd89a) SHA1(f787aab98668d4c2c54fc4ba677c0cb808e4f31e) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "12" socket
	ROMX_LOAD( "sf2-13m.4d", 0x400000, 0x80000, CRC(994bfa58) SHA1(5669b845f624b10e7be56bfc89b76592258ce48b) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "21" socket
	ROMX_LOAD( "sf2-15m.6d", 0x400002, 0x80000, CRC(3e66ad9d) SHA1(9af9df0826988872662753e9717c48d46f2974b0) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "23" socket
	ROMX_LOAD( "sf2-9m.3d",  0x400004, 0x80000, CRC(c1befaa8) SHA1(a6a7f4725e52678cbd8d557285c01cdccb2c2602) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "20" socket
	ROMX_LOAD( "sf2-11m.5d", 0x400006, 0x80000, CRC(0627c831) SHA1(f9a92d614e8877d648449de2612fc8b43c85e4c2) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "22" socket

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",   0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sf2_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "sf2_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sf2.key",  0x00, 0x80, CRC(3cf6f06f) SHA1(7512a185d461f2b37edfc19e31a45d53600fbe44) )
ROM_END

ROM_START( sf2hack05 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf2e_30f_hack05.11e", 0x00000, 0x20000, CRC(e523457c) SHA1(c18e4c644f4bd9c20312d654c6ca4431b0e853a1) )
	ROM_LOAD16_BYTE( "sf2e_37f_hack05.11f", 0x00001, 0x20000, CRC(8d5a9093) SHA1(28f6ce1b2fd65addccaadb7042d4f3e472688861) )
	ROM_LOAD16_BYTE( "sf2e_31g.12e", 0x40000, 0x20000, CRC(69a0a301) SHA1(86a3954335310865b14ce8b4e0e4499feb14fc12) )
	ROM_LOAD16_BYTE( "sf2e_38g.12f", 0x40001, 0x20000, CRC(5e22db70) SHA1(6565946591a18eaf46f04c1aa449ee0ae9ac2901) )
	ROM_LOAD16_BYTE( "sf2e_28g.9e",  0x80000, 0x20000, CRC(8bf9f1e5) SHA1(bbcef63f35e5bff3f373968ba1278dd6bd86b593) )
	ROM_LOAD16_BYTE( "sf2e_35g.9f",  0x80001, 0x20000, CRC(626ef934) SHA1(507bda3e4519de237aca919cf72e543403ec9724) )
	ROM_LOAD16_BYTE( "sf2_29b.10e",  0xc0000, 0x20000, CRC(bb4af315) SHA1(75f0827f4f7e9f292add46467f8d4fe19b2514c9) )
	ROM_LOAD16_BYTE( "sf2_36b.10f",  0xc0001, 0x20000, CRC(c02a13eb) SHA1(b807cc495bff3f95d03b061fc629c95f965cb6d8) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2-5m.4a",  0x000000, 0x80000, CRC(22c9cc8e) SHA1(b9194fb337b30502c1c9501cd6c64ae4035544d4) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "2" socket
	ROMX_LOAD( "sf2-7m.6a",  0x000002, 0x80000, CRC(57213be8) SHA1(3759b851ac0904ec79cbb67a2264d384b6f2f9f9) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "4" socket
	ROMX_LOAD( "sf2-1m.3a",  0x000004, 0x80000, CRC(ba529b4f) SHA1(520840d727161cf09ca784919fa37bc9b54cc3ce) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "1" socket
	ROMX_LOAD( "sf2-3m.5a",  0x000006, 0x80000, CRC(4b1b33a8) SHA1(2360cff890551f76775739e2d6563858bff80e41) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "3" socket
	ROMX_LOAD( "sf2-6m.4c",  0x200000, 0x80000, CRC(2c7e2229) SHA1(357c2275af9133fd0bd6fbb1fa9ad5e0b490b3a2) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "11" socket
	ROMX_LOAD( "sf2-8m.6c",  0x200002, 0x80000, CRC(b5548f17) SHA1(baa92b91cf616bc9e2a8a66adc777ffbf962a51b) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "13" socket
	ROMX_LOAD( "sf2-2m.3c",  0x200004, 0x80000, CRC(14b84312) SHA1(2eea16673e60ba7a10bd4d8f6c217bb2441a5b0e) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "10" socket
	ROMX_LOAD( "sf2-4m.5c",  0x200006, 0x80000, CRC(5e9cd89a) SHA1(f787aab98668d4c2c54fc4ba677c0cb808e4f31e) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "12" socket
	ROMX_LOAD( "sf2-13m.4d", 0x400000, 0x80000, CRC(994bfa58) SHA1(5669b845f624b10e7be56bfc89b76592258ce48b) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "21" socket
	ROMX_LOAD( "sf2-15m.6d", 0x400002, 0x80000, CRC(3e66ad9d) SHA1(9af9df0826988872662753e9717c48d46f2974b0) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "23" socket
	ROMX_LOAD( "sf2-9m.3d",  0x400004, 0x80000, CRC(c1befaa8) SHA1(a6a7f4725e52678cbd8d557285c01cdccb2c2602) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "20" socket
	ROMX_LOAD( "sf2-11m.5d", 0x400006, 0x80000, CRC(0627c831) SHA1(f9a92d614e8877d648449de2612fc8b43c85e4c2) , ROM_GROUPWORD | ROM_SKIP(6) )    // in "22" socket

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",   0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sf2_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "sf2_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sf2.key",  0x00, 0x80, CRC(3cf6f06f) SHA1(7512a185d461f2b37edfc19e31a45d53600fbe44) )
ROM_END

ROM_START( sf2hack06 ) //sf2jcnv
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf2j_30h_hack06.11e", 0x00000, 0x20000, CRC(919d5964) SHA1(a7943517e9f4bdb65991ac4a5097425eddcc05ef) )
	ROM_LOAD16_BYTE( "sf2j_37h_hack06.11f", 0x00001, 0x20000, CRC(574a9966) SHA1(f42ecb8b57c615352d127cfc55ae0d70525c40f2) )
	ROM_LOAD16_BYTE( "sf2j31.bin", 0x40000, 0x20000, CRC(fe15cb39) SHA1(383478524881ea70d9e04c9b6143b8735b637eee) )
	ROM_LOAD16_BYTE( "sf2j38.bin", 0x40001, 0x20000, CRC(38614d70) SHA1(39c58096f3a8e01fb439639b742b83102bbaa7f6) )
	ROM_LOAD16_BYTE( "sf2j_28", 0x80000, 0x20000, CRC(2d4a1b8a) SHA1(9dce74c32fa9c63f38d33a03327b22e74d2118c1) )
	ROM_LOAD16_BYTE( "sf2j_35", 0x80001, 0x20000, CRC(5f622bdb) SHA1(4fe5797acc2645a1bd27d247457b6f24bfd60f96) )
	ROM_LOAD16_BYTE( "sf2_29b.10e", 0xc0000, 0x20000, CRC(bb4af315) SHA1(75f0827f4f7e9f292add46467f8d4fe19b2514c9) )
	ROM_LOAD16_BYTE( "sf2_36b.10f", 0xc0001, 0x20000, CRC(c02a13eb) SHA1(b807cc495bff3f95d03b061fc629c95f965cb6d8) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2_06",  0x000000, 0x80000, CRC(d3aab35d) SHA1(bc90464bc38b326b46f0da97008116ee639e2598) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_08",  0x000002, 0x80000, CRC(f6a68d56) SHA1(4ef2668a245fb207c599f0e72e979f8c0191df25) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_05",  0x000004, 0x80000, CRC(1ddcda55) SHA1(494338ac59e4253177b731bd6ad116a63f7ded8c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_07",  0x000006, 0x80000, CRC(d3274004) SHA1(a278e0740806cf8098058d1c33eb0964cc130ded) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_15",  0x200000, 0x80000, CRC(f8710c69) SHA1(a298117a7869b0891220c229d0dceba7ac6bf594) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_17",  0x200002, 0x80000, CRC(dd376567) SHA1(a817c999098b0274ed2c052b96c562bed407b7b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_14",  0x200004, 0x80000, CRC(c754e2c4) SHA1(7936eaa669c84742c1511768bb9039c26b2fb3c3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_16",  0x200006, 0x80000, CRC(0d4799bd) SHA1(5e63e889cabc4436c2a49997c9d0a47529d264ad) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_25",  0x400000, 0x80000, CRC(a6671144) SHA1(f4017ad15784078c00ef76220f4e5bdba61a6495) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_27",  0x400002, 0x80000, CRC(008b2bdd) SHA1(a048a70fe3c752b79e14eadf2369f068fc831439) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_24",  0x400004, 0x80000, CRC(0f8a9ec4) SHA1(cde0013df78333ebfbaacb9a9e212fbc0b2e04d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_26",  0x400006, 0x80000, CRC(0fb4241e) SHA1(f749daa6ecf018542ecf0f3711491eb85fac91b3) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",   0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18_s33.11c",  0x00000, 0x20000, CRC(6cda9fc8) SHA1(cd846cc3074773ae96bba62a1709ecbb1f6135eb) )
	ROM_LOAD( "s92_19_s33.12c",  0x20000, 0x20000, CRC(d54dc6ae) SHA1(662d6a3260892376428b29d374d255f4cf7352b3) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2c.key", 0x00, 0x80, CRC(fdc05d86) SHA1(f828e6171a271bc12a5c9ab5be237562e263ccdb) )
ROM_END

/********
 bootleg
***********/

ROM_START( sf2c )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf2j_30", 0x00000, 0x20000, CRC(70813e5e) SHA1(39219a98d368dcb67cbd0a756f3e1fab7b9352f4) )
	ROM_LOAD16_BYTE( "sf2j_37", 0x00001, 0x20000, CRC(d0659611) SHA1(1368228cc2c41a361f0e8eb516610522a38394b2) )
	ROM_LOAD16_BYTE( "sf2j31.bin", 0x40000, 0x20000, CRC(fe15cb39) SHA1(383478524881ea70d9e04c9b6143b8735b637eee) )
	ROM_LOAD16_BYTE( "sf2j38.bin", 0x40001, 0x20000, CRC(38614d70) SHA1(39c58096f3a8e01fb439639b742b83102bbaa7f6) )
	ROM_LOAD16_BYTE( "sf2j_28", 0x80000, 0x20000, CRC(2d4a1b8a) SHA1(9dce74c32fa9c63f38d33a03327b22e74d2118c1) )
	ROM_LOAD16_BYTE( "sf2j_35", 0x80001, 0x20000, CRC(5f622bdb) SHA1(4fe5797acc2645a1bd27d247457b6f24bfd60f96) )
	ROM_LOAD16_BYTE( "sf2_29b.10e", 0xc0000, 0x20000, CRC(bb4af315) SHA1(75f0827f4f7e9f292add46467f8d4fe19b2514c9) )
	ROM_LOAD16_BYTE( "sf2_36b.10f", 0xc0001, 0x20000, CRC(c02a13eb) SHA1(b807cc495bff3f95d03b061fc629c95f965cb6d8) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2_06",  0x000000, 0x80000, CRC(d3aab35d) SHA1(bc90464bc38b326b46f0da97008116ee639e2598) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_08",  0x000002, 0x80000, CRC(f6a68d56) SHA1(4ef2668a245fb207c599f0e72e979f8c0191df25) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_05",  0x000004, 0x80000, CRC(1ddcda55) SHA1(494338ac59e4253177b731bd6ad116a63f7ded8c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_07",  0x000006, 0x80000, CRC(d3274004) SHA1(a278e0740806cf8098058d1c33eb0964cc130ded) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_15",  0x200000, 0x80000, CRC(f8710c69) SHA1(a298117a7869b0891220c229d0dceba7ac6bf594) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_17",  0x200002, 0x80000, CRC(dd376567) SHA1(a817c999098b0274ed2c052b96c562bed407b7b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_14",  0x200004, 0x80000, CRC(c754e2c4) SHA1(7936eaa669c84742c1511768bb9039c26b2fb3c3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_16",  0x200006, 0x80000, CRC(0d4799bd) SHA1(5e63e889cabc4436c2a49997c9d0a47529d264ad) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_25",  0x400000, 0x80000, CRC(a6671144) SHA1(f4017ad15784078c00ef76220f4e5bdba61a6495) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_27",  0x400002, 0x80000, CRC(008b2bdd) SHA1(a048a70fe3c752b79e14eadf2369f068fc831439) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_24",  0x400004, 0x80000, CRC(0f8a9ec4) SHA1(cde0013df78333ebfbaacb9a9e212fbc0b2e04d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_26",  0x400006, 0x80000, CRC(0fb4241e) SHA1(f749daa6ecf018542ecf0f3711491eb85fac91b3) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",   0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sf2_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "sf2_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2c.key", 0x00, 0x80, CRC(fdc05d86) SHA1(f828e6171a271bc12a5c9ab5be237562e263ccdb) )
ROM_END

// There is something special about this version but I don't remember what. The region can be
// selected via the dipswitches: Region DIP: 7-8 On On ETC, Off Off JPN, Off On USA
// Tested: stays in Japan region
ROM_START( sf2ly )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sf2r3.23", 0x00000, 0x80000, CRC(ca331c3c) SHA1(e6ff34f76256c2eff9a7677051d3e7279dc83550) )
	ROM_LOAD16_WORD_SWAP( "sf2r3.22", 0x80000, 0x80000, CRC(e446d96a) SHA1(68e39c6c1f89ce223366d37268041c5f1f56531c) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2-5m.4a",  0x000000, 0x80000, CRC(22c9cc8e) SHA1(b9194fb337b30502c1c9501cd6c64ae4035544d4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-7m.6a",  0x000002, 0x80000, CRC(57213be8) SHA1(3759b851ac0904ec79cbb67a2264d384b6f2f9f9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-1m.3a",  0x000004, 0x80000, CRC(ba529b4f) SHA1(520840d727161cf09ca784919fa37bc9b54cc3ce) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-3m.5a",  0x000006, 0x80000, CRC(4b1b33a8) SHA1(2360cff890551f76775739e2d6563858bff80e41) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-6m.4c",  0x200000, 0x80000, CRC(2c7e2229) SHA1(357c2275af9133fd0bd6fbb1fa9ad5e0b490b3a2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-8m.6c",  0x200002, 0x80000, CRC(b5548f17) SHA1(baa92b91cf616bc9e2a8a66adc777ffbf962a51b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-2m.3c",  0x200004, 0x80000, CRC(14b84312) SHA1(2eea16673e60ba7a10bd4d8f6c217bb2441a5b0e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-4m.5c",  0x200006, 0x80000, CRC(5e9cd89a) SHA1(f787aab98668d4c2c54fc4ba677c0cb808e4f31e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_25_hack01.8d",  0x400000, 0x80000, CRC(4267b696) SHA1(af65e3b2cc3b7a7f39d5e7e598da7f4c9d351eea) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_27_hack01.10d", 0x400002, 0x80000, CRC(df9b9146) SHA1(2029aa59c1646af0fd7fa06f353edcbf7f7792de) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_24_hack01.7d",  0x400004, 0x80000, CRC(a08a9786) SHA1(80a79e45c003fbc95cc5cd0d037b55f2f7fec64c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_26_hack01.9d",  0x400006, 0x80000, CRC(80feac31) SHA1(f16ce88634d2328eae93f8128423bb311cac88e6) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",  0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sf2_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "sf2_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sf2.key",  0x00, 0x80, CRC(3cf6f06f) SHA1(7512a185d461f2b37edfc19e31a45d53600fbe44) )
ROM_END

/******************************
 Saturday Night Slam Masters
*********************************/

ROM_START( slammasthack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mbe_23e_hack01.8f", 0x000000, 0x80000, CRC(11c3401a) SHA1(e13f4e2c0fca9c91587fd7a4b88bc1b3adf9304e) )
	ROM_LOAD16_BYTE( "mbe_24b.9e",      0x080000, 0x20000, CRC(95d5e729) SHA1(df3be896e55c92eb50887a4317178a3d11048433) )
	ROM_LOAD16_BYTE( "mbe_28b.9f",      0x080001, 0x20000, CRC(b1c7cbcb) SHA1(cf5ad72be4a055db876e7347b1826325b9bf81d9) )
	ROM_LOAD16_BYTE( "mbe_25b.10e",     0x0c0000, 0x20000, CRC(a50d3fd4) SHA1(dc3d108c3bc27f45b8b2e11919ba2a86e05b41d1) )
	ROM_LOAD16_BYTE( "mbe_29b.10f",     0x0c0001, 0x20000, CRC(08e32e56) SHA1(70ad78b079f777ec02089f0df20ce2baad7adce5) )
	ROM_LOAD16_WORD_SWAP( "mbe_21a.6f", 0x100000, 0x80000, CRC(d5007b05) SHA1(c55e55908aeda40ca2318c76ccbc05d333676875) )
	ROM_LOAD16_WORD_SWAP( "mbe_20a.5f", 0x180000, 0x80000, CRC(aeb557b0) SHA1(530551942961d776f0a85852e02bb243840ca671) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "mb-1m.3a",  0x000000, 0x80000, CRC(41468e06) SHA1(fb365798f2889a20eebaea2393c9c2c8827003c4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-3m.5a",  0x000002, 0x80000, CRC(f453aa9e) SHA1(24a103dc6f0dc96f8d0f6164ad732909c9cd2d6a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-2m.4a",  0x000004, 0x80000, CRC(2ffbfea8) SHA1(13e30133664a009686e1114c92b558bdbb91ea32) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-4m.6a",  0x000006, 0x80000, CRC(1eb9841d) SHA1(685da3e011a96b36be9f639a241b2f8f27da4629) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-5m.7a",  0x200000, 0x80000, CRC(506b9dc9) SHA1(933bf2fb9bcc1a408f961f0e7052da80144bddad) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-7m.9a",  0x200002, 0x80000, CRC(aff8c2fb) SHA1(ce37a6d5b1eb58c2d74f23f84ec824c214c93217) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-6m.8a",  0x200004, 0x80000, CRC(b76c70e9) SHA1(c21e255815ec9a985919dbd760ed266c28bd47cd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-8m.10a", 0x200006, 0x80000, CRC(e60c9556) SHA1(b91c14092aa8dbb0922d96998123ef1970a658f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-10m.3c", 0x400000, 0x80000, CRC(97976ff5) SHA1(ec9d3460816ab971a02fbce42960283091777e47) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-12m.5c", 0x400002, 0x80000, CRC(b350a840) SHA1(2b8b996cd08051e7e8e134bff5448775d78058a0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-11m.4c", 0x400004, 0x80000, CRC(8fb94743) SHA1(294f6182c8a41b640d1f57cb5e3a2abce3b06482) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-13m.6c", 0x400006, 0x80000, CRC(da810d5f) SHA1(392bbd405244b8c99024c9228cfec6a7ef0accdb) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "mb_qa.5k",   0x00000, 0x08000, CRC(e21a03c4) SHA1(98c03fd2c9b6bf8a4fc25a4edca87fff7c3c3819) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x8000, "user1", 0 )
	ROM_COPY( "audiocpu", 0x000000, 0x00000, 0x8000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD( "mb-q1.1k",   0x000000, 0x80000, CRC(0630c3ce) SHA1(520fc74c5c3638f611fa2f1b5efb08b91747e29b) )
	ROM_LOAD( "mb-q2.2k",   0x080000, 0x80000, CRC(354f9c21) SHA1(1dc6b39791fd0f760697f409a6b62361a7bf62e9) )
	ROM_LOAD( "mb-q3.3k",   0x100000, 0x80000, CRC(7838487c) SHA1(056b7da05cfca46873edacd674ca25c70855c6db) )
	ROM_LOAD( "mb-q4.4k",   0x180000, 0x80000, CRC(ab66e087) SHA1(066ea69a0157e8647eea3c44d0a1843898860678) )
	ROM_LOAD( "mb-q5.1m",   0x200000, 0x80000, CRC(c789fef2) SHA1(10d1e3d92288fccd4e064a3716a788a165efc3c9) )
	ROM_LOAD( "mb-q6.2m",   0x280000, 0x80000, CRC(ecb81b61) SHA1(e339f21ae47de4782f3b338befcdac659c3503f6) )
	ROM_LOAD( "mb-q7.3m",   0x300000, 0x80000, CRC(041e49ba) SHA1(3220b033a5c0cfbbe75c0c113cf2db39fb093a7e) )
	ROM_LOAD( "mb-q8.4m",   0x380000, 0x80000, CRC(59fe702a) SHA1(807178dfc6d864e49fd7aabb5c4895835cf0e85b) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "slammast.key", 0x00, 0x80, CRC(f099c4d6) SHA1(2a178a9d856d6ce0746408ec6de92f889fc9ddb6) )
ROM_END

/*******
 bootleg
*********/

ROM_START( slammastud )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mbu_23ed.8f", 0x000000, 0x80000, CRC(7697273f) SHA1(d42ce6414b42db14305f0497fb760e8a3e868b9d) )
	ROM_LOAD16_BYTE( "mbe_24b.9e",      0x080000, 0x20000, CRC(95d5e729) SHA1(df3be896e55c92eb50887a4317178a3d11048433) )
	ROM_LOAD16_BYTE( "mbe_28b.9f",      0x080001, 0x20000, CRC(b1c7cbcb) SHA1(cf5ad72be4a055db876e7347b1826325b9bf81d9) )
	ROM_LOAD16_BYTE( "mbe_25b.10e",     0x0c0000, 0x20000, CRC(a50d3fd4) SHA1(dc3d108c3bc27f45b8b2e11919ba2a86e05b41d1) )
	ROM_LOAD16_BYTE( "mbe_29b.10f",     0x0c0001, 0x20000, CRC(08e32e56) SHA1(70ad78b079f777ec02089f0df20ce2baad7adce5) )
	ROM_LOAD16_WORD_SWAP( "mbe_21a.6f", 0x100000, 0x80000, CRC(d5007b05) SHA1(c55e55908aeda40ca2318c76ccbc05d333676875) )
	ROM_LOAD16_WORD_SWAP( "mbu_20a.5f", 0x180000, 0x80000, CRC(fc848af5) SHA1(cd3f6e50779b89ee57a9d08bfa1d58dea286457c) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "mb-1m.3a",  0x000000, 0x80000, CRC(41468e06) SHA1(fb365798f2889a20eebaea2393c9c2c8827003c4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-3m.5a",  0x000002, 0x80000, CRC(f453aa9e) SHA1(24a103dc6f0dc96f8d0f6164ad732909c9cd2d6a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-2m.4a",  0x000004, 0x80000, CRC(2ffbfea8) SHA1(13e30133664a009686e1114c92b558bdbb91ea32) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-4m.6a",  0x000006, 0x80000, CRC(1eb9841d) SHA1(685da3e011a96b36be9f639a241b2f8f27da4629) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-5m.7a",  0x200000, 0x80000, CRC(506b9dc9) SHA1(933bf2fb9bcc1a408f961f0e7052da80144bddad) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-7m.9a",  0x200002, 0x80000, CRC(aff8c2fb) SHA1(ce37a6d5b1eb58c2d74f23f84ec824c214c93217) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-6m.8a",  0x200004, 0x80000, CRC(b76c70e9) SHA1(c21e255815ec9a985919dbd760ed266c28bd47cd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-8m.10a", 0x200006, 0x80000, CRC(e60c9556) SHA1(b91c14092aa8dbb0922d96998123ef1970a658f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-10m.3c", 0x400000, 0x80000, CRC(97976ff5) SHA1(ec9d3460816ab971a02fbce42960283091777e47) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-12m.5c", 0x400002, 0x80000, CRC(b350a840) SHA1(2b8b996cd08051e7e8e134bff5448775d78058a0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-11m.4c", 0x400004, 0x80000, CRC(8fb94743) SHA1(294f6182c8a41b640d1f57cb5e3a2abce3b06482) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-13m.6c", 0x400006, 0x80000, CRC(da810d5f) SHA1(392bbd405244b8c99024c9228cfec6a7ef0accdb) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "mb_qa.5k",   0x00000, 0x08000, CRC(e21a03c4) SHA1(98c03fd2c9b6bf8a4fc25a4edca87fff7c3c3819) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x8000, "user1", 0 )
	ROM_COPY( "audiocpu", 0x00000, 0x00000, 0x8000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD( "mb-q1.1k",   0x000000, 0x80000, CRC(0630c3ce) SHA1(520fc74c5c3638f611fa2f1b5efb08b91747e29b) )
	ROM_LOAD( "mb-q2.2k",   0x080000, 0x80000, CRC(354f9c21) SHA1(1dc6b39791fd0f760697f409a6b62361a7bf62e9) )
	ROM_LOAD( "mb-q3.3k",   0x100000, 0x80000, CRC(7838487c) SHA1(056b7da05cfca46873edacd674ca25c70855c6db) )
	ROM_LOAD( "mb-q4.4k",   0x180000, 0x80000, CRC(ab66e087) SHA1(066ea69a0157e8647eea3c44d0a1843898860678) )
	ROM_LOAD( "mb-q5.1m",   0x200000, 0x80000, CRC(c789fef2) SHA1(10d1e3d92288fccd4e064a3716a788a165efc3c9) )
	ROM_LOAD( "mb-q6.2m",   0x280000, 0x80000, CRC(ecb81b61) SHA1(e339f21ae47de4782f3b338befcdac659c3503f6) )
	ROM_LOAD( "mb-q7.3m",   0x300000, 0x80000, CRC(041e49ba) SHA1(3220b033a5c0cfbbe75c0c113cf2db39fb093a7e) )
	ROM_LOAD( "mb-q8.4m",   0x380000, 0x80000, CRC(59fe702a) SHA1(807178dfc6d864e49fd7aabb5c4895835cf0e85b) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "slammastud.key", 0x00, 0x80, CRC(ade2c2a3) SHA1(8d7a4249cf221ac24c4c66f7151a9edd7f263de5) )
ROM_END

/******
 Varth
********/

ROM_START( varthhack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "vae_30b_hack01.11f", 0x00000, 0x20000, CRC(214e4065) SHA1(2a6db38009a58baf10f2c297f585312852668267) )
	ROM_LOAD16_BYTE( "vae_35b_hack01.11h", 0x00001, 0x20000, CRC(2cdbcb3f) SHA1(39f3429bf70e36b640f1a70748c1779020bd2fc1) )
	ROM_LOAD16_BYTE( "vae_31b.12f", 0x40000, 0x20000, CRC(1749a71c) SHA1(bd9bfd5bbe2d426c94df755c977faa92a28f16ab) )
	ROM_LOAD16_BYTE( "vae_36b.12h", 0x40001, 0x20000, CRC(5f2e2450) SHA1(676e8d96406d81ceadd4a0a69959cdcb6d5d9ac8) )
	ROM_LOAD16_BYTE( "vae_28b.9f",  0x80000, 0x20000, CRC(e524ca50) SHA1(487d5ddabe852872f331362034c4fa16e0926e3d) )
	ROM_LOAD16_BYTE( "vae_33b.9h",  0x80001, 0x20000, CRC(c0bbf8c9) SHA1(447540b856776770af8022a291d46612c1bb5909) )
	ROM_LOAD16_BYTE( "vae_29b.10f", 0xc0000, 0x20000, CRC(6640996a) SHA1(3ed7bd947dc8224435680dedf4955ed6041c6028) )
	ROM_LOAD16_BYTE( "vae_34b.10h", 0xc0001, 0x20000, CRC(fa59be8a) SHA1(86a3d3a7126c021e2ca8ac20238695396367e098) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "va-5m.7a", 0x000000, 0x80000, CRC(b1fb726e) SHA1(5ac0876b6c49d0a99710dda68653664f4d8c1167) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "va-7m.9a", 0x000002, 0x80000, CRC(4c6588cd) SHA1(d14e8cf051ac934ccc989d8c571c6cc9eed34af5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "va-1m.3a", 0x000004, 0x80000, CRC(0b1ace37) SHA1(6f9493c22f667f683db2789972fd16bb94724679) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "va-3m.5a", 0x000006, 0x80000, CRC(44dfe706) SHA1(a013a434df3161a91aafbb35dc4e20dfb3f177f4) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "va_09.12b", 0x00000, 0x08000, CRC(7a99446e) SHA1(ca027f41e3e58be5abc33ad7380746658cb5380a) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "va_18.11c", 0x00000, 0x20000, CRC(de30510e) SHA1(8e878696192606b76a3a0e53553e638d9621cff7) )
	ROM_LOAD( "va_19.12c", 0x20000, 0x20000, CRC(0610a4ac) SHA1(3da02ea6a7a56c85de898806d2a1cf6bc526c1b3) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "varth.key", 0x00, 0x80, CRC(9af7013d) SHA1(6182dfe656c25cc5ef009bfb1b5820ad3ce71c77) )
ROM_END

/*******
 Willow
*********/

ROM_START( willowhack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "wle_30_hack01.11f",     0x00000, 0x20000, CRC(57f07aaf) SHA1(73e8b0e740fa20ae4743e08274a771cc6e528a06) )
	ROM_LOAD16_BYTE( "wle_35_hack01.11h",         0x00001, 0x20000, CRC(95ca6caa) SHA1(de07dbbc9c50d0282ead55283fd645eb8eb9793b) )
	ROM_LOAD16_BYTE( "wlu_31.12f",     0x40000, 0x20000, CRC(0eb48a83) SHA1(28c40c4b5d767f88922cd899e948abf11a85a864) )
	ROM_LOAD16_BYTE( "wlu_36.12h",     0x40001, 0x20000, CRC(36100209) SHA1(63c9338e71dba8b52daffba50b4bca31aaa10d9e) )
	ROM_LOAD16_WORD_SWAP( "wlm-32.8h", 0x80000, 0x80000, CRC(dfd9f643) SHA1(9c760c30af593a87e7fd39fb213a4c73c68ca440) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "wlm-7.7a", 0x000000, 0x80000, CRC(afa74b73) SHA1(09081926260c76986a13ac5351dddd2ea11d7a10) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "wlm-5.9a", 0x000002, 0x80000, CRC(12a0dc0b) SHA1(fea235ce9489f04919daf52f4d3f3bac9b558316) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "wlm-3.3a", 0x000004, 0x80000, CRC(c6f2abce) SHA1(ff5fcfe417c43b4747bbe12db6052fdb60f5f0e4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "wlm-1.5a", 0x000006, 0x80000, CRC(4aa4c6d3) SHA1(7dd6f18f6126c380821a2ca8955439fd6864f4c6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "wl_24.7d", 0x200000, 0x20000, CRC(6f0adee5) SHA1(07b18e51b376001f25173b78e0e816f252400210) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_14.7c", 0x200001, 0x20000, CRC(9cf3027d) SHA1(1e8eb20d51a54f6f756c0ab9395ac38b96e67fb2) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_26.9d", 0x200002, 0x20000, CRC(f09c8ecf) SHA1(b39f83e80af010d6481693d9ec8b1d7e258b531d) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_16.9c", 0x200003, 0x20000, CRC(e35407aa) SHA1(7ddae9cef96839da72488c1fe73268c50e0262ff) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_20.3d", 0x200004, 0x20000, CRC(84992350) SHA1(f0ebd810ce099337cda94222dccce8ab9b3c3281) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_10.3c", 0x200005, 0x20000, CRC(b87b5a36) SHA1(25fb8f9698142473233ee509d4146089920e94e1) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_22.5d", 0x200006, 0x20000, CRC(fd3f89f0) SHA1(51ff95cff56ac78682ea56401b35a0aa63cef8cb) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_12.5c", 0x200007, 0x20000, CRC(7da49d69) SHA1(b0ae7ac4f858ee8d72e6877c4275da7a631e2e4c) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "wl_09.12b", 0x00000, 0x08000, CRC(f6b3d060) SHA1(0ed2e2f64ba53ba2c371b66ab1e52e40b16d8baf) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "wl_18.11c", 0x00000, 0x20000, CRC(bde23d4d) SHA1(d1fee2f99c858dfb07edcd600da491c7b656afe0) )
	ROM_LOAD( "wl_19.12c", 0x20000, 0x20000, CRC(683898f5) SHA1(316a77b663d78c8b9ff6d85756cb05aaaeef4003) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "willow.key", 0x00, 0x80, CRC(ad3640c3) SHA1(0d9ffb6bc15f6207d154ded582d81c2cde0a396f) )
ROM_END

ROM_START( willowhack02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "wle_30_hack02.11f",   0x000000, 0x20000, CRC(05814ce1) SHA1(0da3d908117adb6d505ba843b914aa54597d3cff) )
	ROM_LOAD16_BYTE( "wle_35_hack02.11h",   0x000001, 0x20000, CRC(48bdd898) SHA1(851735cfc4d40bf533fc8199002c85c6ac9dcca8) )
	ROM_LOAD16_BYTE( "wlu_31_hack02.12f",   0x040000, 0x20000, CRC(b188553b) SHA1(49a0dfe97e1d2810bda891d5464d2634254f0247) )
	ROM_LOAD16_BYTE( "wlu_36_hack02.12h",   0x040001, 0x20000, CRC(8bba3252) SHA1(565a0119cc48628f6cb568c3db23f5a1f9d05d23) )
	ROM_LOAD16_WORD_SWAP( "wlm-32_hack02.8h",    0x080000, 0x80000, CRC(a64d6469) SHA1(b95cf4696767742505809a3d2b0767856e5a46d2) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "wlm-7_hack02.7a", 0x000000, 0x80000, CRC(0264d809) SHA1(a920da936294c1f861d0c38dd6630410ec14c5b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "wlm-5_hack02.9a", 0x000002, 0x80000, CRC(44da08d9) SHA1(ff8067c9035f9f4c702739bfc1b1127dc9503259) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "wlm-3_hack02.3a", 0x000004, 0x80000, CRC(3f54884c) SHA1(2eea03c189fe5cf542bab29b3302dc99680079c1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "wlm-1_hack02.5a", 0x000006, 0x80000, CRC(8fd41c4e) SHA1(4a066169719ccb88abf35f499791dab7350e4c34) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "wl_24_hack02.7d", 0x200000, 0x20000, CRC(c4d86fb2) SHA1(04df9c3c08c4325eeb03645715af2b75d5b4d199) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_14_hack02.7c", 0x200001, 0x20000, CRC(fa45c4d4) SHA1(d6c1e2e578bf631b728fc01340abdfcf8778cce3) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_26_hack02.9d", 0x200002, 0x20000, CRC(282f95b0) SHA1(afca63f4a501ea8c83464fd3b89f21a5df2435e3) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_16_hack02.9c", 0x200003, 0x20000, CRC(bf6a9d5c) SHA1(e10b5932b7c404933ec320799f6b5ceaa2359db9) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_20_hack02.3d", 0x200004, 0x20000, CRC(08cfa420) SHA1(030390e4368781ab9b12c53474477692a5baa4ad) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_10_hack02.3c", 0x200005, 0x20000, CRC(3cb28fed) SHA1(e8d5bd6ec36f7b0bee304a01b094f6061aad68e4) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_22_hack02.5d", 0x200006, 0x20000, CRC(ccebdbe6) SHA1(d05b349ce2a5238a0feb7ac0427e99b34778f2f5) , ROM_SKIP(7) )
	ROMX_LOAD( "wl_12_hack02.5c", 0x200007, 0x20000, CRC(332ecf17) SHA1(581ddc4b0ba0baa7b1eb504a785d23f9d3ce1e8d) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "wl_09.12b", 0x00000, 0x08000, CRC(f6b3d060) SHA1(0ed2e2f64ba53ba2c371b66ab1e52e40b16d8baf) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "wl_18.11c", 0x00000, 0x20000, CRC(bde23d4d) SHA1(d1fee2f99c858dfb07edcd600da491c7b656afe0) )
	ROM_LOAD( "wl_19.12c", 0x20000, 0x20000, CRC(683898f5) SHA1(316a77b663d78c8b9ff6d85756cb05aaaeef4003) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "willow.key", 0x00, 0x80, CRC(ad3640c3) SHA1(0d9ffb6bc15f6207d154ded582d81c2cde0a396f) )
ROM_END

/*******************
 Tenchi wo Kurau II
*********************/

ROM_START( twkhack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack01.8f", 0x000000, 0x80000, CRC(a8113500) SHA1(f59bf4108ab713e3d218c5469fbba7065ed472fb) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c.7f", 0x080000, 0x80000, CRC(b74b09ac) SHA1(3a44d6db5f51e1b5d2b43ef0ad1191da21e48427) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack02 ) // wofjxd Reviewed 30-05-2018
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack01.8f", 0x000000, 0x80000, CRC(1efb9db3) SHA1(f19fcb045b00713fcde235b5e1aae2ef3c1d9c4f) )
	ROM_IGNORE(0x3d4f61)
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack01.7f", 0x080000, 0x80000, CRC(eaf087c7) SHA1(92cdc073c045e4944b493b70ef60a6fd34cb7e01) )
	ROM_IGNORE(0x3d4f49)

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack03.8f", 0x000000, 0x80000, CRC(a9e52e66) SHA1(463758c91d421c8e52ddb555d9b223fff4b81938) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack03.7f", 0x080000, 0x80000, CRC(b5f39ae9) SHA1(a797b5485c4423d57db2288b3f12dbc79a93de5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack04 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack04.8f", 0x000000, 0x80000, CRC(311c2b48) SHA1(151f2ec4a8bfeabdb8448fc027d98bf230cef87a) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c.7f", 0x080000, 0x80000, CRC(b74b09ac) SHA1(3a44d6db5f51e1b5d2b43ef0ad1191da21e48427) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack05 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack05.8f", 0x000000, 0x80000, CRC(9cd80f64) SHA1(c6af2f2b6794d6ff708b01fbae2a6fb0fc2eab9b) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c.7f", 0x080000, 0x80000, CRC(b74b09ac) SHA1(3a44d6db5f51e1b5d2b43ef0ad1191da21e48427) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack06 ) //wofjzl
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack06.8f", 0x000000, 0x80000, CRC(74c37c24) SHA1(de3090e97578ee4ce5d39b64dc97c75dc32bdeb9) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack06.5f", 0x080000, 0x80000, CRC(8c15d367) SHA1(cbedb4695bdfa73669b39ddc16ebfc8254961917) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack07 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack07.8f", 0x000000, 0x80000, CRC(62935648) SHA1(eb9acd77c793e6543213b4947efd38adaee65d3b) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack07.7f", 0x080000, 0x80000, CRC(11a89813) SHA1(be5e307ad66b764a6a347fc3e9ab9613c386ad87) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack08 ) //wofjxb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack08.8f", 0x000000, 0x80000, CRC(c70a7931) SHA1(6c724f0d1821b35f6ec034bc25fce4afd2338462) )
	ROM_IGNORE(0x3d4f69)
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack08.7f", 0x080000, 0x80000, CRC(aef23f92) SHA1(dfbbfb87c3947eb17fc0dafa4539bc08e45a61e9) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack09 ) //wofjxa
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack09.8f", 0x000000, 0x80000, CRC(3538cdd7) SHA1(3c143e45dbccf575eb4ec6ddfeae602f8ddbe7e6) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack09.7f", 0x080000, 0x80000, CRC(126eabce) SHA1(8f7c5c7fb5ac09d4a282c9a028fba7d7d681f034) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack10 ) //wofjhe
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack10.8f", 0x000000, 0x80000, CRC(73eee179) SHA1(07030dbe964a46e3a16bec233694f682237f137a) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack10.7f", 0x080000, 0x80000, CRC(9d5f6b2b) SHA1(3927276ac2fdac041de8a0dcda590a7bd385c2ac) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack11 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack11.8f",  0x000000, 0x80000, CRC(d558ece3) SHA1(7cc01ef35e67a0de0567e6339146c3c4d9b79ce6) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack11.7f",  0x080000, 0x80000, CRC(83a722df) SHA1(b2d550f1434e9dc06d24ccb53dd57e7630f5feb6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a", 0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a", 0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a", 0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a", 0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",    0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",    0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",    0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a",   0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack12 ) //wofmmws
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack12.8f",  0x000000, 0x80000, CRC(31facd8f) SHA1(ce8c3a658c1c6f35f7b88b49f60a2b4ffad3a8c5) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack12.7f",  0x080000, 0x80000, CRC(addacdcb) SHA1(cba996b96fa073469ca186900132f1d0be64c402) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a", 0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a", 0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a", 0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a", 0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",    0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",    0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",    0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a",   0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack13 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack13.10f", 0x000000, 0x200000, CRC(73e8687b) SHA1(c0bf124a6bf3e6cd30f7403f676c67302a2bbdbf) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack14 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack14.8f",  0x000000, 0x80000, CRC(c1c0192c) SHA1(501225c58e25aaea4c0a4bb348f6a0150a742762) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c.7f", 0x080000, 0x80000, CRC(b74b09ac) SHA1(3a44d6db5f51e1b5d2b43ef0ad1191da21e48427) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack15 ) //wofjmzt
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack15.8f", 0x000000, 0x80000, CRC(3f0f42dd) SHA1(46d883ad4df62be93f551419411619a61b11e366) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack15.7f", 0x080000, 0x80000, CRC(f121df53) SHA1(69fb7aad5d234d55a9a490853f7f6a1bade5d2c7) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack16 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack16.8f", 0x000000, 0x80000, CRC(2b1b7fe2) SHA1(1194b964055db0f7299a20796f9e8159e4ec2f10) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack16.7f", 0x080000, 0x80000, CRC(f12bd6ad) SHA1(0ee16f5562c8dd8d86e912b1116fc422ab91093f) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05_hack16.7a",  0x200000, 0x80000, CRC(b1aeb378) SHA1(3ec068b9f9a810926a7b0dce66dc59fa6907ec9c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06_hack16.8a",  0x200002, 0x80000, CRC(4ade6423) SHA1(f13604ff150d96c5ae511236ceadc45f9705b620) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07_hack16.9a",  0x200004, 0x80000, CRC(feca816a) SHA1(f827ecaddc9af26706266653334a392b8e2917a6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08_hack16.10a", 0x200006, 0x80000, CRC(9fcde72b) SHA1(8d7e5a89d06530a6f45e9875b4be9aad88a0c9fd) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack17 ) //wofjxd
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack17.8f", 0x000000, 0x80000, CRC(4ccbc264) SHA1(70aac0abfc1d0b32fe7e0c89d7afd81f26e46747) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack17.7f", 0x080000, 0x80000, CRC(1bc4fe5a) SHA1(174fad3ccb585ac5c42d7a6dd6d61e2aaba09da6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack18 ) //woftz
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack18.8f", 0x000000, 0x80000, CRC(4c923657) SHA1(989c9185c9c78eeb35a6fec56d361ed801822e88) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack18.7f", 0x080000, 0x80000, CRC(5e3d0f9d) SHA1(900e01cd7fe409918625a69d097757cb1236daf6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack19 ) //wofjdrl
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack19.8f", 0x000000, 0x80000, CRC(00852edb) SHA1(0342ca914a9706c7cd2a27e6ceafd5503452b932) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack19.7f", 0x080000, 0x80000, CRC(d9297368) SHA1(e79a02f022a7b19829075d4b35a3d248270ce6ac) )
	ROM_LOAD16_WORD_SWAP( "tk2j_21c_hack19.6f", 0x100000, 0x80000, CRC(bc2a5fc5) SHA1(021602ff421aa7e2b0822d591254fb6397995ae0) )
	ROM_LOAD16_WORD_SWAP( "tk2j_20c_hack19.5f", 0x180000, 0x80000, CRC(661ac2c1) SHA1(2ff09487781b31dfb20921046bb34530a3e1fbca) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack20 ) //wofjhc
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack20.8f",  0x000000, 0x80000, CRC(938f6254) SHA1(9c5ad268edc89ab94a9d5fdcbd051ed3066b2c94) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c.7f",  0x080000, 0x80000, CRC(b74b09ac) SHA1(3a44d6db5f51e1b5d2b43ef0ad1191da21e48427) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a", 0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a", 0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a", 0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a", 0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a", 0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a", 0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a", 0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack21 ) //wofj
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack21.8f",  0x000000, 0x80000, CRC(1df170c7) SHA1(bb25017c8a71dfc40299df10067bfe5995368be6) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack21.7f",  0x080000, 0x80000, CRC(24de3a6d) SHA1(431b4e5712f0990b7f1aad82fabf96133845eca6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a", 0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a", 0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a", 0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a", 0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a", 0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a", 0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a", 0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack22 ) //wofjz
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack22.8f", 0x000000, 0x80000, CRC(65f16ccc) SHA1(6a210298bdd856080702eb4154dcfc4e858e0920) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack22.7f", 0x080000, 0x80000, CRC(de4c13c4) SHA1(bff0ba2147e938a8080f065f810975034acfa3c5) )
	ROM_LOAD16_WORD_SWAP( "tk2j_21c_hack22.6f", 0x100000, 0x80000, CRC(7a5f60c0) SHA1(b4d864e39811d1407ce2ba9580bd1e230edf37ff) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05_hack22.7a",  0x200000, 0x80000, CRC(ad7a65fe) SHA1(a56a275560fc00d947560b57eccdb1152753dfd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06_hack22.8a",  0x200002, 0x80000, CRC(03acddc1) SHA1(7ebe3b47d47cc298dc19539b3f3d6c1207f23230) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07_hack22.9a",  0x200004, 0x80000, CRC(39462940) SHA1(31bc092dcbb12022896f227e9f83b1d63cfdf8a7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08_hack22.10a", 0x200006, 0x80000, CRC(8a977564) SHA1(9c555d267c5433adabf6c5c2cb6294df018af92f) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack23 ) //wofjxz
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack23.23",  0x000000, 0x80000, CRC(5bf83942) SHA1(3fb4a7dcd3bc89677d8cb910e279eb1bbd7d4bf0) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack23.7f",  0x080000, 0x80000, CRC(96fc801e) SHA1(f24e7a05f2fe43ff9aa38407a4f32d3b70a858d6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a", 0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a", 0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a", 0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a", 0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05_hack23.7a",  0x200000, 0x80000, CRC(2d9c0bd4) SHA1(cd9046774203556274b4e1f59b54acd45a38f6fc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06_hack23.8a",  0x200002, 0x80000, CRC(45c3a4a1) SHA1(92563f7207bea29dccc68dabf950366c5abfb84b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07_hack23.9a",  0x200004, 0x80000, CRC(b905dc00) SHA1(b79add016f943f14dbf486bb7b34e06dbba6e4bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08_hack23.10a", 0x200006, 0x80000, CRC(6af56439) SHA1(65dc1048929c499bd6c3b7fbcec35a8ff0896cf7) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack24 ) //wofz
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack24.8f", 0x000000, 0x80000, CRC(6a704803) SHA1(98d08bad882dd016b0e6fe990611e1c8cc937560) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c.7f",  0x080000, 0x80000, CRC(b74b09ac) SHA1(3a44d6db5f51e1b5d2b43ef0ad1191da21e48427) )
	ROM_LOAD16_WORD_SWAP( "tk2j_21c_hack24.6f", 0x100000, 0x80000, CRC(9e8f14d7) SHA1(26913497be1d361fe3002fab8ee225024ec89165) )
	ROM_LOAD16_WORD_SWAP( "tk2j_20c_hack24.5f", 0x180000, 0x80000, CRC(a811cb6f) SHA1(a866d24f6285713ab715429ac9a456b5efb7cf58) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack25 ) //wofjdrdz
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack25.10f", 0x000000, 0x200000, CRC(58226b23) SHA1(598ca40223e816149c57ef0aef104a6952bc254e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",    0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",    0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",    0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",    0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h141.7a",    0x200000, 0x80000, CRC(6a1b1784) SHA1(dfb935c27c248d8ac50c6bba97eabef5bcbfc72d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h141.8a",    0x200002, 0x80000, CRC(266ee41f) SHA1(be8c63dd629940b8c52a5a2c1e2986a5b7992393) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h141.9a",    0x200004, 0x80000, CRC(e9a0468e) SHA1(68a1852e6419729dc67eaf758c9215af5a6c37a4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h141.10a",   0x200006, 0x80000, CRC(19d7d078) SHA1(8be71a7bb810c8f16024e490d597be4b40a0d1cd) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(              0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack26 ) //wofjdrl2
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack26.8f", 0x000000, 0x80000, CRC(832c3b95) SHA1(10c5ef952626b22c30c63d6d883f97c9b030a42e) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c_hack26.7f", 0x080000, 0x80000, CRC(5615a7ff) SHA1(674ce26dbb0ac82cb0f0d85c8c62614492280e84) )
	ROM_LOAD16_WORD_SWAP( "tk2j_21c_hack26.6f", 0x100000, 0x80000, CRC(0c4483ea) SHA1(ca0486e2b023568cb4234323d1c8db735519b1ff) )
	ROM_LOAD16_WORD_SWAP( "tk2j_20c_hack26.5f", 0x180000, 0x80000, CRC(2ed78fb8) SHA1(36f343cccff0ced0b87d2cad0519ec955a39702a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack27 ) //wofdrnboss
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack27.8f", 0x000000, 0x200000, CRC(604750e2) SHA1(592a0cba196c7e63a41917b8fdccab9a4ca53f37) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05_hack27.7a",    0x200000, 0x80000, CRC(c61917b7) SHA1(206bb0317e1019753ffed4557e390748c37f0004) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06_hack27.8a",    0x200002, 0x80000, CRC(f8c7a42b) SHA1(6f18589c89ce2b220651a27beac51cf48be13fa9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07_hack27.9a",    0x200004, 0x80000, CRC(e7860364) SHA1(70f130a023475f18be92f4aafc578d4d29d28f79) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08_hack27.10a",   0x200006, 0x80000, CRC(fd2b0dce) SHA1(658583fb9ad88cbc886e50a77276bb2b8e71c850) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( twkhack28 ) //wofjdrh
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23c_hack28.10f", 0x000000, 0x200000, CRC(ce8f5100) SHA1(4a603e8f231dd967b193948a94dcebf0c202f5cf) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05_hack28.7a",    0x200000, 0x80000, CRC(e3c8c198) SHA1(f31f9f5c41d94ff84d29ed787d9104ee3fc1a7aa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06_hack28.8a",    0x200002, 0x80000, CRC(5e3c0642) SHA1(8ee6834b1d497c4e4724b1db48d61df558fd0e93) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07_hack28.9a",    0x200004, 0x80000, CRC(d65a91d9) SHA1(4e1fa66c25fb4e28e49a458500089094cb54a308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08_hack28.10a",   0x200006, 0x80000, CRC(675d490e) SHA1(180deb2aff5c2e35cc0eaaed8e6d5d490beaa5ea) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

/********
 bootleg
**********/

ROM_START( wofh )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sgyx.800",  0x000000, 0x100000, CRC(3703a650) SHA1(6cb8d6f99df5e2e5cf04aee8737bb585f9328ffd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD("sgyx-1.160",    0x000000, 0x80000, CRC(a60be9f6) SHA1(2298a4b6a2c83b76dc106a1efa19606b298d378a), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD("sgyx-2.160",    0x000002, 0x80000, CRC(6ad9d048) SHA1(d47212d28d0a1ce349e4c59e5d0d99c541b3458e), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sgyxz_snd2.bin", 0x00000, 0x10000,  CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) )
	ROM_RELOAD(                0x8000, 0x10000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sgyxz_snd1.bin", 0x00000, 0x40000,  CRC(c15ac0f2) SHA1(8d9e5519d9820e4ac4f70555088c80e64d052c9d) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sk2h101.key",    0x00, 0x80, CRC(679300a3) SHA1(f3e8197955f6b2b54493a449386b804b0d5e15ed) ) // OK
ROM_END

ROM_START( wofha )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "fg-c.040",  0x000000, 0x80000, CRC(d046fc86) SHA1(0ae0b9310e3a122cb69df4bb23672149794242f0) )
	ROM_LOAD16_BYTE( "fg-a.040",  0x000001, 0x80000, CRC(f176ee8f) SHA1(fba357c31774aeecef88f70df4294514585df3a0) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD("sgyx-1.160",    0x000000, 0x80000, CRC(a60be9f6) SHA1(2298a4b6a2c83b76dc106a1efa19606b298d378a), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD("sgyx-2.160",    0x000002, 0x80000, CRC(6ad9d048) SHA1(d47212d28d0a1ce349e4c59e5d0d99c541b3458e), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sgyxz_snd2.bin", 0x00000, 0x10000,  CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) )
	ROM_RELOAD(           0x8000, 0x10000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sgyxz_snd1.bin", 0x00000, 0x40000,  CRC(c15ac0f2) SHA1(8d9e5519d9820e4ac4f70555088c80e64d052c9d) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sk2h101.key",     0x00, 0x80, CRC(679300a3) SHA1(f3e8197955f6b2b54493a449386b804b0d5e15ed) ) // OK
ROM_END

ROM_START( sgyxz )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sgyxz_prg2.bin", 0x000000, 0x20000, CRC(95429c83) SHA1(e981624d018132e5625a66113b6ac4fc44e55cf7) )
	ROM_CONTINUE( 0x80000, 0x20000 )
	ROM_CONTINUE( 0x40000, 0x20000 )
	ROM_CONTINUE( 0xc0000, 0x20000 )
	ROM_LOAD16_BYTE( "sgyxz_prg1.bin", 0x000001, 0x20000, CRC(d8511929) SHA1(4de9263778f327693f4d1e21b48e43806f673487) )
	ROM_CONTINUE( 0x80001, 0x20000 )
	ROM_CONTINUE( 0x40001, 0x20000 )
	ROM_CONTINUE( 0xc0001, 0x20000 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD("sgyx-1.160",    0x000000, 0x80000, CRC(a60be9f6) SHA1(2298a4b6a2c83b76dc106a1efa19606b298d378a), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD("sgyx-2.160",    0x000002, 0x80000, CRC(6ad9d048) SHA1(d47212d28d0a1ce349e4c59e5d0d99c541b3458e), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x20000, "audiocpu", 0 )
	ROM_LOAD( "sgyxz_snd2.bin", 0x00000, 0x10000,  CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) )
	ROM_RELOAD(           0x8000, 0x10000 )

	ROM_REGION( 0x040000, "oki", 0 )
	ROM_LOAD( "sgyxz_snd1.bin", 0x00000, 0x40000,  CRC(c15ac0f2) SHA1(8d9e5519d9820e4ac4f70555088c80e64d052c9d) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sk2h101.key",     0x00, 0x80, CRC(679300a3) SHA1(f3e8197955f6b2b54493a449386b804b0d5e15ed) ) // OK
ROM_END

ROM_START( wofah )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "htk2a_23b.rom",  0x000000, 0x80000, CRC(1b17fc85) SHA1(d8c2bd31474dce2330adb05b859ce3fd13040d23) )
	ROM_LOAD16_WORD_SWAP( "tk2a_22c.7f",  0x080000, 0x80000, CRC(900ad4cd) SHA1(988007447f93f3467029b9c29fd9670a7ecadaa3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",   0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",   0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",   0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a",   0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wofaha )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "htk2ah_23b.rom", 0x000000, 0x80000, CRC(6e3ff382) SHA1(14ef2c708da134f925efa0c3886a104c3ef9e5d7) )
	ROM_LOAD16_WORD_SWAP( "tk2a_22c.7f",  0x080000, 0x80000, CRC(900ad4cd) SHA1(988007447f93f3467029b9c29fd9670a7ecadaa3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",   0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",   0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",   0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a",   0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wofahb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2ah_23b.rom",  0x000000, 0x80000, CRC(48fd83c6) SHA1(8f33124979d7ca4c2af10f2a98b524e5463458cc) )
	ROM_LOAD16_WORD_SWAP( "tk2a_22c.7f",  0x080000, 0x80000, CRC(900ad4cd) SHA1(988007447f93f3467029b9c29fd9670a7ecadaa3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",   0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",   0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",   0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a",   0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wof3js )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3js_23.rom",  0x000000, 0x80000, CRC(1ebb76da) SHA1(a3d9643a03e964477abd5164202566fe4a11b902) )
	ROM_LOAD16_WORD_SWAP( "3js_22.rom",  0x080000, 0x80000, CRC(f41d6153) SHA1(a2cafea8402ab58e8022020242397e7cdce57aff) )
	ROM_LOAD16_BYTE( "3js_24.rom",       0x0c0000, 0x20000, CRC(06ead409) SHA1(7289afd15fecd185350d2705476d74baa6909782) )
	ROM_LOAD16_BYTE( "3js_28.rom",       0x0c0001, 0x20000, CRC(8ba934e6) SHA1(b9fb1d000a90cf2dbe2113130939c146f16a776e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3js_gfx5.rom",   0x200000, 0x80000, CRC(94b58f82) SHA1(937e7bb74e47f7ed670f63cdf7e502cf6ffe09c8), ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3js_gfx7.rom",   0x200002, 0x80000, CRC(df4fb386) SHA1(4eece42595084dbab1fa2c603f231fc67efb292d), ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3js_gfx6.rom",   0x200004, 0x80000, CRC(c22c5bd8) SHA1(4dd3598ca9cbbceabfb28b1b0d8a4879fcdb9a13), ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3js_gfx8.rom",   0x200006, 0x80000, CRC(f9cfd08b) SHA1(cd55ef014705d8b07c3eb9dafdbf2a831ea25b7c), ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "3js_09.rom",     0x00000, 0x08000, CRC(21ce044c) SHA1(425fd8d33d54f35ef90d68a7530db7a0eafb600d) )
	ROM_CONTINUE(               0x10000, 0x08000 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "3js_18.rom",     0x000000, 0x20000, CRC(ac6e307d) SHA1(b490ce625bb7ce0904b0fd121fbfbd5252790f7a) )
	ROM_LOAD( "3js_19.rom",     0x020000, 0x20000, CRC(068741db) SHA1(ab48aff639a7ac218b7d5304145e10e92d61fd9f) )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h21.key", 0x00, 0x80, CRC(287d8a40) SHA1(46aa717f599f88d32afb5ecc0bf43c2cbe6892d0) )
ROM_END

ROM_START( wof3jsa )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "cx2.040", 0x00000, 0x20000, CRC(c01a6d2f) SHA1(c1e69e075bb01141c026bf0722a64659e1802184) )
	ROM_CONTINUE(               0x80000, 0x20000 )
	ROM_CONTINUE(               0x40000, 0x20000 )
	ROM_CONTINUE(               0xc0000, 0x20000 )
	ROM_LOAD16_BYTE( "cx1.040", 0x00001, 0x20000, CRC(fd95e677) SHA1(42a10e73bd30498dc39cd66abf73680799ebe8b0) )
	ROM_CONTINUE(               0x80001, 0x20000 )
	ROM_CONTINUE(               0x40001, 0x20000 )
	ROM_CONTINUE(               0xc0001, 0x20000 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tx-a.160", 0x000000, 0x80000, CRC(ae348da2) SHA1(e86ab38e75c46ff2a4fa974fbbd3c2d2f67cef36), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(          0x000004, 0x80000 )
	ROM_CONTINUE(          0x200000, 0x80000 )
	ROM_CONTINUE(          0x200004, 0x80000 )
	ROMX_LOAD( "tx-b.160", 0x000002, 0x80000, CRC(384a6db0) SHA1(57273edce545a7fb4026cb4c705d97d71f24ea6f), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(          0x000006, 0x80000 )
	ROM_CONTINUE(          0x200002, 0x80000 )
	ROM_CONTINUE(          0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wof3sj )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "k6b.040",  0x000000, 0x80000, CRC(7b365108) SHA1(e4ef6e7267ecf36d8b15c7df0351b38777cd559d) )
	ROM_LOAD16_BYTE( "k6a.040",  0x000001, 0x80000, CRC(10488a51) SHA1(061d5139f4289cbca9e0a743954d9c65a9384c06) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "k6a.160",   0x000000, 0x80000, CRC(a121180d) SHA1(9501399479a5892db0c818637459f77540794b85), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "k6b.160",   0x000002, 0x80000, CRC(a4db96c4) SHA1(6798c0cbd9a1f8f4704c5cb9e19e8873149d3c33), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wof3sja )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3js.800",  0x000000, 0x100000, CRC(812f9200) SHA1(ddf4261c21762e8168d83393a59aa1450762a89a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "k6a.160",   0x000000, 0x80000, CRC(a121180d) SHA1(9501399479a5892db0c818637459f77540794b85), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "k6b.160",   0x000002, 0x80000, CRC(a4db96c4) SHA1(6798c0cbd9a1f8f4704c5cb9e19e8873149d3c33), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wofsj )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "c-c47b.040",  0x000000, 0x80000, CRC(b1809761) SHA1(99a17ed193654f61622eb721e20b69894c96d3d8) )
	ROM_LOAD16_BYTE( "a-2402.040",  0x000001, 0x80000, CRC(4fab4232) SHA1(d8ffd06cce73e1c4bc6abb69a2e81277ce901563) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",  0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",  0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",  0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a", 0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wofsja )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "one.800",  0x000000, 0x100000, CRC(0507584d) SHA1(5a9df64b7c2c54c5aa0d4c9486c7404157c6119e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",  0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",  0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",  0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a", 0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wofsjb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "c-d140.040",  0x000000, 0x80000, CRC(e6d933a6) SHA1(c1f08bbbfc855bbc96b844eed7b1e4f9a0a07fbf) )
	ROM_LOAD16_BYTE( "a-0050.040",  0x000001, 0x80000, CRC(403eaead) SHA1(ce6d061e5ee91de779c8d0c19bed273dc4769900) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",   0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",   0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",   0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a",   0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h21.key", 0x00, 0x80, CRC(287d8a40) SHA1(46aa717f599f88d32afb5ecc0bf43c2cbe6892d0) )
ROM_END

ROM_START( wofsjc )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cx2s43.040",  0x000000, 0x100000, CRC(cb28807e) SHA1(78312081ad95273ea04f1e16dc097bf5b54f88b3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",  0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",  0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",  0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a", 0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sgyxz_snd2.bin", 0x00000, 0x10000,  CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) )
	ROM_RELOAD(                0x8000, 0x10000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

/********************
  Tenchi wo Kurau II
*********************/

ROM_START( wofchhack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2=ch=_23_hack01.8f", 0x000000, 0x80000, CRC(2ac1693e) SHA1(3480d78d996f7f027b89dc549a606ddf6b05e7a0) )
	ROM_LOAD16_WORD_SWAP( "tk2=ch=_22_hack01.7f", 0x080000, 0x80000, CRC(50f889c5) SHA1(a15ba89cbdc54a8b1774ceea0fc270cf3786ad5a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",      0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",      0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",      0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",      0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_07.9a",  0x200004, 0x80000, CRC(cc9006c9) SHA1(cfcbec3a67052268a7739538aa28a6391fe5400e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wofchhack02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2=ch=_23_hack02.8f", 0x000000, 0x80000, CRC(bdea1fd1) SHA1(c667ddc5157927e813e357743f6ee6dd24cba100) )
	ROM_LOAD16_WORD_SWAP( "tk2=ch=_22_hack02.7f", 0x080000, 0x80000, CRC(d8512c40) SHA1(e36a7d670ffe592470337e031d06feb46f75684f) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",      0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",      0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",      0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",      0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_07.9a",  0x200004, 0x80000, CRC(cc9006c9) SHA1(cfcbec3a67052268a7739538aa28a6391fe5400e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wofchhack03 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2=ch=_23_hack03.8f", 0x000000, 0x80000, CRC(f848f5dd) SHA1(08d507f50597f5d9049ea34c1d5f7293fd3742f7) )
	ROM_LOAD16_WORD_SWAP( "tk2=ch=_22.7f", 0x080000, 0x80000, CRC(d0937a8d) SHA1(01d7be446e2e3ef8ca767f59c178240dfd52dd93) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",      0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",      0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",      0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",      0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_07.9a",  0x200004, 0x80000, CRC(cc9006c9) SHA1(cfcbec3a67052268a7739538aa28a6391fe5400e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

/***************
  Sangokushi II
****************/

ROM_START( sk3hack01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sk3_hack01.8f", 0x000000, 0x80000, CRC(214b8367) SHA1(4c18766aa54fe15341fd30f6d23a71129854a7df) )
	ROM_IGNORE(0x3d4fe8)
	ROM_LOAD16_WORD_SWAP( "sk3_hack01.7f", 0x080000, 0x80000, CRC(c6dbedec) SHA1(13289a2b2ea4d4fd5ae92c596b8be77894b6b2fc) )
	ROM_IGNORE(0x3d51a0)

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( sk3hack02 ) //wofaha
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sk3_hack02.8f", 0x000000, 0x80000, CRC(06c90133) SHA1(6b8e0334191358306633298563a87ccc7732ceb4) )
	ROM_IGNORE(0x3d4f4f)
	ROM_LOAD16_WORD_SWAP( "sk3_hack02.7f", 0x080000, 0x80000, CRC(bd03e00c) SHA1(694c9b0d9c90d487303834bfbafcbd080b7b2805) )
	ROM_IGNORE(0x3d5072)

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a",  0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( sk3hack03 ) //wofchdx
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sk3_hack03.8f", 0x000000, 0x80000, CRC(64b80f07) SHA1(7efd1636f875a8d029ae229d97b4e5d8f2065858) )
	ROM_LOAD16_WORD_SWAP( "sk3_hack03.7f", 0x080000, 0x80000, CRC(87b8f045) SHA1(83b8d261e993d7885ddd58282227b95a66e6f17f) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",      0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",      0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",      0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",      0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_07.9a",  0x200004, 0x80000, CRC(cc9006c9) SHA1(cfcbec3a67052268a7739538aa28a6391fe5400e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",       0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(                0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",       0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",       0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",       0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",       0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( sk3hack04 ) //wofaha
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sk3_hack04.8f", 0x000000, 0x80000, CRC(0207b37e) SHA1(7d475ab48d5403f1e7c9fbeb71b191cf93496fbf) )
	ROM_LOAD16_WORD_SWAP( "sk3_hack04.7f", 0x080000, 0x80000, CRC(2644b59f) SHA1(6cf541f7e43371146fddebdda7f7db1dff5878d4) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a",  0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a",  0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2=ch=_07.9a",  0x200004, 0x80000, CRC(cc9006c9) SHA1(cfcbec3a67052268a7739538aa28a6391fe5400e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h21.key", 0x00, 0x80, CRC(287d8a40) SHA1(46aa717f599f88d32afb5ecc0bf43c2cbe6892d0) )
ROM_END

/******************
  Warriors Of Fate
*******************/

ROM_START( wofhack01 ) //wof1v3
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2e_23c_hack01.8f", 0x000000, 0x80000, CRC(c436ef13) SHA1(e672c34efcf6b165dd1713fa33995b9cb0e72784) )
	ROM_LOAD16_WORD_SWAP( "tk2e_22c_hack01.7f", 0x080000, 0x80000, CRC(0894db63) SHA1(3f1374eb4b33af510af00ec0605f3457283e2501) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",  0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",  0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",  0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a", 0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wofhack02 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2e_23c_hack02.8f",  0x000000, 0x80000, CRC(e006e81e) SHA1(dad6cd3a1175b6f366e8bf02d1af35af5f1b50cc) )
	ROM_LOAD16_WORD_SWAP( "tk2e_22b.7f",  0x080000, 0x80000, CRC(479b3f24) SHA1(9fb8ae06856fe115addfb6794c28978a4f6716ec) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m_hack02.7a",   0x200000, 0x80000, CRC(1b6bc2b2) SHA1(3a5305d07271cffb9875fcbd2af52856a224548a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m_hack02.9a",   0x200002, 0x80000, CRC(3f1e5334) SHA1(a5c4795d65a916fc2d1a55153c4ca0ac5fbaf418) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m_hack02.8a",   0x200004, 0x80000, CRC(28c9d96f) SHA1(aa64a4572b10842b7f5f546e63493d501a16fd85) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m_hack02.10a",  0x200006, 0x80000, CRC(b3b9a29e) SHA1(fe425356545544a9cf50409972d2893999896191) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

/********
 bootleg
**********/

ROM_START( wofr1bl )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "3-f2ab.040",  0x000000, 0x80000, CRC(61fd0a01) SHA1(a7b5bdddd7b31645e33314c1d3649e1506cecfea) )
	ROM_LOAD16_BYTE( "1-9207.040",  0x000001, 0x80000, CRC(7f59e24c) SHA1(34c294328d00c65086622bd15e17210f07f37237) )
	ROM_LOAD16_BYTE( "4-d4d2.010",  0x100000, 0x20000, CRC(fe5eee87) SHA1(be1230f64c1e59ae3ff3e58593070613966ac79d) )
	ROM_LOAD16_BYTE( "2-6c41.010",  0x100001, 0x20000, CRC(739379be) SHA1(897f61527213902fda04bc28339f1f4278bf5ae9) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "5-caf3.040",   0x000000, 0x40000, CRC(c8dcaa95) SHA1(bcaeaefd40ffa1b32e80457cffcc1ceab461af1d), ROM_SKIP(7) )
	ROM_CONTINUE(              0x000004, 0x40000 )
	ROMX_LOAD( "6-034f.040",   0x000001, 0x40000, CRC(1ab0000c) SHA1(0d0004cc1725c38d140ecb8dc9666361b2d3e607), ROM_SKIP(7) )
	ROM_CONTINUE(              0x000005, 0x40000 )
	ROMX_LOAD( "7-b0fa.040",   0x000002, 0x40000, CRC(8425ff6b) SHA1(9a051089c2a492b8c63484582f95c578704b6820), ROM_SKIP(7) )
	ROM_CONTINUE(              0x000006, 0x40000 )
	ROMX_LOAD( "8-a6b7.040",   0x000003, 0x40000, CRC(24ce197b) SHA1(0ccdbd6f6a30e6d1479f8702c3e8561b16303550), ROM_SKIP(7) )
	ROM_CONTINUE(              0x000007, 0x40000 )
	ROMX_LOAD( "9-8a2c.040",   0x200000, 0x40000, CRC(9d20ef9b) SHA1(cbf3cb6bd7a73312e5061082554f2e17aae08621), ROM_SKIP(7) )
	ROM_CONTINUE(              0x200004, 0x40000 )
	ROMX_LOAD( "10-7d24.040",  0x200001, 0x40000, CRC(90c93dd2) SHA1(d3d2b0bcbcbb21a41f986eb752ab114697eb9402), ROM_SKIP(7) )
	ROM_CONTINUE(              0x200005, 0x40000 )
	ROMX_LOAD( "11-4171.040",  0x200002, 0x40000, CRC(219fd7e2) SHA1(af765eb7b275ed541c08e243b22b5c9f54c1a8ec), ROM_SKIP(7) )
	ROM_CONTINUE(              0x200006, 0x40000 )
	ROMX_LOAD( "12-f56b.040",  0x200003, 0x40000, CRC(efc17c9a) SHA1(26429a9039bb249e17945508c16645c82f7f412a), ROM_SKIP(7) )
	ROM_CONTINUE(              0x200007, 0x40000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wofpic )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "3-f2ab.040",  0x000000, 0x80000, CRC(61fd0a01) SHA1(a7b5bdddd7b31645e33314c1d3649e1506cecfea) )
	ROM_LOAD16_BYTE( "1-92bl.040",  0x000001, 0x80000, CRC(d2ae67a8) SHA1(34c294328d00c65086622bd15e17210f07f37237) )
	ROM_LOAD16_BYTE( "4-d4d2.010",  0x100000, 0x20000, CRC(fe5eee87) SHA1(be1230f64c1e59ae3ff3e58593070613966ac79d) )
	ROM_LOAD16_BYTE( "2-6c41.010",  0x100001, 0x20000, CRC(739379be) SHA1(897f61527213902fda04bc28339f1f4278bf5ae9) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "5-caf3.040",   0x000000, 0x40000, CRC(c8dcaa95) SHA1(bcaeaefd40ffa1b32e80457cffcc1ceab461af1d), ROM_SKIP(7) )
	ROM_CONTINUE(              0x000004, 0x40000 )
	ROMX_LOAD( "6-034f.040",   0x000001, 0x40000, CRC(1ab0000c) SHA1(0d0004cc1725c38d140ecb8dc9666361b2d3e607), ROM_SKIP(7) )
	ROM_CONTINUE(              0x000005, 0x40000 )
	ROMX_LOAD( "7-b0fa.040",   0x000002, 0x40000, CRC(8425ff6b) SHA1(9a051089c2a492b8c63484582f95c578704b6820), ROM_SKIP(7) )
	ROM_CONTINUE(              0x000006, 0x40000 )
	ROMX_LOAD( "8-a6b7.040",   0x000003, 0x40000, CRC(24ce197b) SHA1(0ccdbd6f6a30e6d1479f8702c3e8561b16303550), ROM_SKIP(7) )
	ROM_CONTINUE(              0x000007, 0x40000 )
	ROMX_LOAD( "9-8a2c.040",   0x200000, 0x40000, CRC(9d20ef9b) SHA1(cbf3cb6bd7a73312e5061082554f2e17aae08621), ROM_SKIP(7) )
	ROM_CONTINUE(              0x200004, 0x40000 )
	ROMX_LOAD( "10-7d24.040",  0x200001, 0x40000, CRC(90c93dd2) SHA1(d3d2b0bcbcbb21a41f986eb752ab114697eb9402), ROM_SKIP(7) )
	ROM_CONTINUE(              0x200005, 0x40000 )
	ROMX_LOAD( "11-4171.040",  0x200002, 0x40000, CRC(219fd7e2) SHA1(af765eb7b275ed541c08e243b22b5c9f54c1a8ec), ROM_SKIP(7) )
	ROM_CONTINUE(              0x200006, 0x40000 )
	ROMX_LOAD( "12-f56b.040",  0x200003, 0x40000, CRC(efc17c9a) SHA1(26429a9039bb249e17945508c16645c82f7f412a), ROM_SKIP(7) )
	ROM_CONTINUE(              0x200007, 0x40000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

// same as wofu except first rom
ROM_START( wofud )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "wofud.23",    0x000000, 0x80000, CRC(9bab998f) SHA1(6afe212d7816bde23aecb92f57d075c3e411d4c6) )
	ROM_LOAD16_WORD_SWAP( "tk2u_22c.7f", 0x080000, 0x80000, CRC(f5af4774) SHA1(f6d53cf5b330e6d68f84da3e8c831a475585b93e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",  0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",  0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",  0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a", 0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

/*    YEAR  NAME           PARENT    MACHINE     INPUT     INIT            MONITOR COMPANY         FULLNAME FLAGS */
// Three Wonders
HACK( 2019, 3wondershack01,  3wonders, cps1_10MHz, 3wonders, cps_state, cps1,     ROT0,   "huangxu", "Three Wonders (Ex Super Version 2019-04-19)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 1991, 3wondrud,        3wonders, cps1_10MHz, 3wonders, cps_state, cps1,     ROT0,   "bootleg", "Three Wonders (US 910520 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 1991, 3wondersha,      3wonders, cps1_10MHz, 3wonders, cps_state, cps1,     ROT0,   "bootleg", "Three Wonders (bootleg set 3, wonder 3 910520 etc)", MACHINE_SUPPORTS_SAVE )
// Captain Commando
HACK( 1991, captcommhack01,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Translation Chinese)", MACHINE_SUPPORTS_SAVE )
HACK( 2008, captcommhack02,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "Shinwa",  "Captain Commando (Ex Super version)" , MACHINE_SUPPORTS_SAVE )
HACK( 1991, captcommhack03,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Extreme Mode)", MACHINE_SUPPORTS_SAVE )
HACK( 1991, captcommhack04,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "DDJ",     "Captain Commando (Change Weapon)", MACHINE_SUPPORTS_SAVE )
HACK( 1991, captcommhack05,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "DDJ",     "Captain Commando (Stage Select)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, captcommhack06,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "DDJ",     "Captain Commando (Hit Anywhere 2018-08-09)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, captcommhack07,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Shape Shifting Version 2019-05-05)" , MACHINE_SUPPORTS_SAVE )
HACK( 2019, captcommhack08,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Summon Mount Edition 2019-08-02)" , MACHINE_SUPPORTS_SAVE )
HACK( 2019, captcommhack09,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (1V4 Edition 2019-09-16)" , MACHINE_SUPPORTS_SAVE )
HACK( 2019, captcommhack10,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (God Of War Edition Update 2019-09-16)" , MACHINE_SUPPORTS_SAVE )
HACK( 2019, captcommhack11,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Warriors Edition Update 2019-10-21)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, captcommhack12,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (99 Fighter Edition Update 2019-04-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, captcommhack13,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Unlimited Bullet Update 2020-02-19)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, captcommhack14,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Journey Version 2020-08-12)" , MACHINE_SUPPORTS_SAVE )
HACK( 2020, captcommhack15,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Master Second Edition 2020-08-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, captcommhack16,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Elite Edition Update 2020-08-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, captcommhack17,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Nightmare Edition Update 2020-08-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, captcommhack18,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Warlord Version 2020-08-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, captcommhack19,  captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (Masters Competition Edition 2020-10-18)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 1991, captcoud,        captcomm, cps1_10MHz, captcomm, cps_state, cps1,     ROT0,   "hack",    "Captain Commando (US 910928 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
// Dai Makai-Mura
HACK( 1988, daimakaib,       ghouls,   daimakb,    daimakai, cps_state, cps1,     ROT0,   "bootleg", "Dai Makai-Mura (bootleg, Japan)" , MACHINE_SUPPORTS_SAVE )
// Cadillacs And Dinosaurs
HACK( 2008, dinohack01,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "Pipi899", "Cadillacs and Dinosaurs (Enhanced Revision 2008 set 3 v2.0f 2008-10-17)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack02,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "DDJ",     "Cadillacs and Dinosaurs (Hit Anywhere)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack03,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "DDJ",     "Cadillacs and Dinosaurs (Call Out Weapon)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack04,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "DDJ",     "Cadillacs and Dinosaurs (Stage Select)" , MACHINE_SUPPORTS_SAVE )
HACK( 1993, dinohack05,      dino,     qsound,     dinohz,   cps_state, dinoh,    ROT0,   "hack",    "Cadillacs and Dinosaurs (99 Jurassic)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack06,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Phantom Musou Updated version 2017 2017-11-29)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack07,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Yong Chuang Tian Ya 2017-12-27)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack08,      dino,     qsound,     dinohz,   cps_state, dinoh,    ROT0,   "hack",    "Cadillacs and Dinosaurs (Second Generation Extreme Edition 1 2017-12-16)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack09,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Second Generation Extreme Edition 2 2017-12-17)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack10,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "Ngs",     "Cadillacs and Dinosaurs (Tu Fu Zhi Nu 2017-11-23)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack11,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Di Yu Wu Shuang 2017-12-24)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack12,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (99 Jurassic Plus 2017-11-13)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack13,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (E Gun De Fu Chou 2017-12-31)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack14,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Qi Sha Edition 2018-02-25)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack15,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Dewar Edition 2018-01-18)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack16,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Boss Phantom Edition 2018-04-08)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack17,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Super Musou 2017 2017-11-03)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack18,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (2017 Super Warriors Brawl 2017-11-12)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack19,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Zeng Xing X5 2017-11-08)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack20,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (2011 Musou 2018 2017-12-14)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack21,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Second Generation Warriors 2017 2017-11-19)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack22,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Dinosaur Hunter (Burst Edition 2017-12-14)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack23,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Second Generation Knight Edition 2017-11-19)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack24,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Dinosaur Hunter (Challenge Edition 2017-11-16)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack25,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (2018 Warrior Summoning Edition 2018-01-18)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack26,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Battered Edition 2017 2017-04-18)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack27,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (2015 Matchless 2017-09-09)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack28,      dino,     qsound,     dinohz,   cps_state, dinoh,    ROT0,   "hack",    "Cadillacs and Dinosaurs (Second Generation Extreme Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack29,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Iron Dragon 2018-07-31)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack30,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Fast Fight Blood Battle Version 2018 Tour Version 2018-06-11)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack31,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Multi Boss 2017-04-06)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack32,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (2017 Musou Combo Edition 2017-10-24)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack33,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Quickly Increased Edition X3 2017-10-30)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack34,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Warriors Bloody Edition 2017 2017-10-25)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack35,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Speed Enhanced Version 2017 2017-10-16)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack36,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (The 2017 Unparalleled Chaos 2017-11-10)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack37,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Second Generation Warriors 2017 2017-11-12)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack38,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Snow Version 2018-01-23)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack39,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Ghost Crying Godless Peerless Version 2018-01-18)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack40,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Chaos unparalleled 2018-08-16)" , MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack41,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Ji 2011 2017-05-21)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack42,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Fight bloody version 2018-09-19)" , MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack43,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Heaven And Earth Unparalleled 2018-12-21)" , MACHINE_SUPPORTS_SAVE )
HACK( 2019, dinohack44,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "Li Xili", "Cadillacs and Dinosaurs (Unrivalled Version 2019 2019-01-07)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, dinohack45,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (God of War Edition 2019-04-15)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, dinohack46,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Devil dance 2019-05-30)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, dinohack47,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Group Demon Dance Edition 2019-05-30)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, dinohack48,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Purgatory 2019-04-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, dinohack49,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (1V3 Enhanced Edition 2019 2019-08-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, dinohack50,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "NanGongSheng", "Cadillacs and Dinosaurs (Fighting God Version 2019-09-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, dinohack51,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "BinDi", "Cadillacs and Dinosaurs (Arena Version 2019-02-27)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, dinohack52,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "NanGongSheng", "Cadillacs and Dinosaurs (Sky King 2019-09-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, dinohack53,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Increase Enemy 5X 2017-11-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack54,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (The Warriors Edition 2020 2020-01-25)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, dinohack55,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Ruan Bu Wu Shuang 2018-07-29)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack56,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (The Beatless Hit Cool Version 2020-04-10)" , MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack57,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Ares Edition 2020-05-15)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack58,      dino,     qsound,     dino,     cps_state, dinohb,   ROT0,   "hack",    "Cadillacs and Dinosaurs (99 Jurassic Boss Edition 2020-06-17)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack59,      dino,     qsound,     dino,     cps_state, dinohb,   ROT0,   "hack",    "Cadillacs and Dinosaurs (99 Jurassic 2020-06-04)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack60,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (JD Versión 2020-06-07)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack61,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Military Commander Edition 2020-05-28)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack62,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Triassic Edition 2020-06-07)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack63,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Quick Warrior Edition 2020-06-07)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack64,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Three Forbidden Version 2020-06-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack65,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Tianjiang Edition 2020-06-29)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack66,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Uranus Edition 2020-06-29)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack67,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Xia Hou Dun Edition 2020-07-05)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack68,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Falling Dragon Edition 2020 2020-08-06)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack69,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Li Dianda Edition 2020-08-06)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack70,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Multi-Mode Enhanced Edition 2020-08-11)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack71,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Wushuang Jianglong Edition 2020-08-11)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack72,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Shinseiki Edition 2020-08-09)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack73,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Demon God Dance 2020-08-23)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack74,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Doushen 2020-10-18)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack75,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (The Warriors Edition Update 2020-10-18)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, dinohack76,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Commemorative Edition 2020-10-18)", MACHINE_SUPPORTS_SAVE )
HACK( 2014, dinohack77,      dino,     qsound,     dino,     cps_state, dino,     ROT0,   "hack",    "Cadillacs and Dinosaurs (Boss Improved Version 2014-10-04)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 1993, dinoh,           dino,     qsound,     dinohz,   cps_state, dinoh,    ROT0,   "bootleg", "Cadillacs and Dinosaurs (bootleg set 3, 930223 Asia TW)" , MACHINE_SUPPORTS_SAVE )
HACK( 1993, dinoha,          dino,     qsound,     dinohz,   cps_state, dinoh,    ROT0,   "bootleg", "Cadillacs and Dinosaurs (bootleg set 1, 930223 Asia TW)", MACHINE_SUPPORTS_SAVE )
HACK( 1993, dinotpic,        dino,     qsound,     dinohz,   cps_state, dinohb,   ROT0,   "bootleg", "Cadillacs and Dinosaurs (bootleg set 2 (with PIC16c57), 930201 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1993, dinohc,          dino,     qsound,     dinohz,   cps_state, dino,     ROT0,   "bootleg", "Cadillacs and Dinosaurs (Chinese bootleg, 930223 Asia TW)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )
// Final Fight
HACK( 1990, ffighthack01,    ffight,   cps1_10MHz, ffight,   cps_state, cps1,     ROT0,   "Whirlwind (Piracy)", "Final Fight (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, ffighthack02,    ffight,   cps1_10MHz, ffight,   cps_state, cps1,     ROT0,   "hack",     "Final Fight (Yong Chuang Tian Ya Version 2016-08-17)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, ffighthack03,    ffight,   cps1_10MHz, ffight,   cps_state, cps1,     ROT0,   "hack",     "Final Fight (Ming Yun Wu Shuang Edition 2016 2016-10-24 )", MACHINE_SUPPORTS_SAVE )
HACK( 2016, ffighthack04,    ffight,   cps1_10MHz, ffight,   cps_state, cps1,     ROT0,   "hack",     "Final Fight (Paced Whirlwind 2016-08-17)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, ffighthack05,    ffight,   cps1_10MHz, ffight,   cps_state, cps1,     ROT0,   "hack",     "Final Fight (Musou Edition 2020-06-08)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, ffighthack06,    ffight,   cps1_10MHz, ffight,   cps_state, cps1,     ROT0,   "hack",     "Final Fight (1V2 Enhanced Version 2017-11-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, ffighthack07,    ffight,   cps1_12MHz, ffightae, cps_state, cps1,     ROT0,   "Grego & Rotwang", "Final Fight 30th Anniversary Edition (2019-12-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2021, ffighthack08,    ffight,   cps1_12MHz, ffightae, cps_state, cps1,     ROT0,   "Zombie Master",   "Final Fight 30th Anniversary Edition Brutal Version (2021-05-28)", MACHINE_SUPPORTS_SAVE )
HACK( 2022, ffighthack09,    ffight,   cps1_12MHz, ffightae, cps_state, cps1,     ROT0,   "Zombie Master",   "Final Fight 30th Anniversary Edition Fair Challenge (2022-01-18)", MACHINE_SUPPORTS_SAVE )
HACK( 2021, ffighthack10,    ffight,   cps1_12MHz, ffightae, cps_state, cps1,     ROT0,   "Zombie Master",   "Final Fight 30th Anniversary Edition Real Threat (2021-11-01)", MACHINE_SUPPORTS_SAVE )
// Knights of the Round
HACK( 2021, knightshack01,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "Sebastian Mihai", "Knights of the Round (Death's Thread)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, knightshack02,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "Sebastian Mihai", "Knights of the Round (Translation Romanian)", MACHINE_SUPPORTS_SAVE )
HACK( 2021, knightshack03,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "Sebastian Mihai", "Knights of the Round (Squire's Aid)", MACHINE_SUPPORTS_SAVE )
HACK( 2021, knightshack04,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "Sebastian Mihai", "Knights of the Round (Warlock's Tower)", MACHINE_SUPPORTS_SAVE )
HACK( 1991, knightshack05,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (Extreme Mode Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 1991, knightshack06,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "Mr.L",     "Knights of the Round (Random Characters, Items, Chaos Into Version V6-3)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, knightshack07,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "doubledr", "Knights of the Round (1V3 Unparalleled Edition 2016-02-17)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, knightshack08,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (Super Plus 2016-08-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, knightshack09,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (Tie Jia Ying Hao 1 Vs 3 Edition 2018-03-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2014, knightshack10,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (Tie Jia Ying Hao 2 2018-03-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, knightshack11,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (Enhanced Edition 2016-07-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, knightshack12,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (Full Screen Attack 2018-02-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, knightshack13,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (1V3 Edition 2018-06-07)", MACHINE_SUPPORTS_SAVE )
HACK( 2012, knightshack14,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (Enemy Random 2011-12-20)", MACHINE_SUPPORTS_SAVE ) //Name of the unknown roms
HACK( 2020, knightshack15,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (The Warriors Enhanced Edition 2020 2020-08-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, knightshack16,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (The Falling Dragon Edition 2020 2020-08-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, knightshack17,   knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (Wushuang Jianglong Edition 2020-08-02)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 1991, knightshb2,      knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "bootleg",  "Knights of the Round (bootleg set 2, 911127 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1991, knightsh,        knights,  cps1_10MHz, knightsh, cps_state, cps1,     ROT0,   "hack",     "Knights of the Round (hack set 1)" , MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 1991, knightsha,       knights,  cps1_10MHz, knightsh, cps_state, cps1,     ROT0,   "Hack",     "Knights of the Round (hack set 2, 911127 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1991, knightsb5,       knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "bootleg",  "Knights of the Round (bootleg set 5, 911127 Japan)", MACHINE_SUPPORTS_SAVE )
HACK( 1991, knightud,        knights,  cps1_10MHz, knights,  cps_state, cps1,     ROT0,   "bootleg",  "Knights of the Round (US 911127 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
// The King of Dragons
HACK( 2015, kodhack01,       kod,      cps1_10MHz, kod,      cps_state, cps1,     ROT0,   "hack",     "The King of Dragons (Boss Battle Edition 2015-05-25)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 2002, kodh,            kod,      cps1_10MHz, kodh,     cps_state, cps1,     ROT0,   "hack",     "The King of Dragons (hack)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
// Mercs
HACK( 1990, mercshack01,     mercs,    cps1_10MHz, mercs,    cps_state, cps1,     ROT270, "LB70",     "Mercs (Crazy Fire Version)", MACHINE_SUPPORTS_SAVE )
HACK( 1990, mercshack02,     mercs,    cps1_10MHz, mercs,    cps_state, cps1,     ROT270, "hack",     "Senjou no Ookami II (Translation Chinese)", MACHINE_SUPPORTS_SAVE )
// The Punisher
HACK( 2018, punisherhack01,  punisher, qsound,     punisher, cps_state, punisher, ROT0,   "hack",     "The Punisher (1 Vs 2 Perfect 2018-03-30)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, punisherhack02,  punisher, qsound,     punisher, cps_state, punisher, ROT0,   "hack",     "The Punisher (Tie Jia Ying Hao 2018-04-11)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, punisherhack03,  punisher, qsound,     punisher, cps_state, punisher, ROT0,   "hack",     "The Punisher (Enemy Reset 2018-03-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, punisherhack04,  punisher, qsound,     punisher, cps_state, punisher, ROT0,   "hack",     "The Punisher (Warriors Fast Fighting 2017-12-13)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, punisherhack05,  punisher, qsound,     punisher, cps_state, punisher, ROT0,   "hack",     "The Punisher (Multi-Mode Enhancement 2020-06-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, punisherhack06,  punisher, qsound,     punisher, cps_state, punisher, ROT0,   "hack",     "The Punisher (Warriors Edition 2017-11-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, punisherhack07,  punisher, qsound,     punisher, cps_state, punisher, ROT0,   "hack",     "The Punisher (The Falling Dragon Edition 2019-05-30)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, punisherhack08,  punisher, qsound,     punisher, cps_state, punisher, ROT0,   "hack",     "The Punisher (Quick Warrior Competition Edition 2018-09-20)", MACHINE_SUPPORTS_SAVE )
// bootleg
//HACK( 1993, punipic,         punisher, qsound,     punisher, cps_state, punisherb,ROT0,   "bootleg",  "The Punisher (bootleg set 1 (with PIC16c57), 930422 etc)", MACHINE_SUPPORTS_SAVE)
HACK( 1993, punisherud1,     punisher, qsound,     punisher, cps_state, punisher, ROT0,   "bootleg",  "The Punisher (US 930422 Phoenix Edition (8b/32p))", MACHINE_SUPPORTS_SAVE )
HACK( 1993, punisherud2,     punisher, qsound,     punisher, cps_state, punisher, ROT0,   "bootleg",  "The Punisher (US 930422 Phoenix Edition (16b/40p))", MACHINE_SUPPORTS_SAVE )
// Street Fighter II': Champion Edition
HACK( 2016, sf2cehack01,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "DDJ",      "Street Fighter II': Champion Edition (Easy Move)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, sf2cehack02,     sf2ce,    cps1_12MHz, sf2,      cps_state, sf2rb,    ROT0,   "DDJ",      "Street Fighter II': Champion Edition (Easy Move / Rainbow, bootleg,)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, sf2cehack03,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "hack",     "Street Fighter II': Champion Edition (3 Questions Edition 2019-10-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, sf2cehack04,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "hack",     "Street Fighter II': Champion Edition (3 Questions Edition Simplify The Move 2019-10-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, sf2cehack05,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "hack",     "Street Fighter II': Champion Edition (Question Mark Edition 2019-10-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, sf2cehack06,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "hack",     "Street Fighter II': Champion Edition (Question Mark Edition Simplify The Move 2019-10-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, sf2cehack07,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "hack",     "Street Fighter II': Champion Edition (Chinese Voice Version Simplified 2020-06-30)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, sf2cehack08,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "hack",     "Street Fighter II': Champion Edition (Lowtax is a Wifebeater parody)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, sf2cehack09,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "hack",     "Street Fighter II': Champion Edition (Lowtax is a Wifebeater parody Simplified 2020-08-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, sf2cehack10,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "Drakon",   "Street Fighter II': Champion Edition (Punishment Edition Simplified 2018-06-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2012, sf2cehack11,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "Drakon",   "Street Fighter II': Champion Edition (Sheng Long Hack v7.3a)", MACHINE_SUPPORTS_SAVE )
HACK( 2022, sf2cehack12,     sf2ce,    cps1_12MHz, sf2mix,   cps_state, cps1,     ROT0,   "Zero800",  "Street Fighter II': Champion Edition (Mix 1.2)", MACHINE_SUPPORTS_SAVE )
HACK( 2022, sf2cehack13,     sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "Rotwang",  "Street Fighter II': Hyper Fighting (Ukraine version)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 1992, sf2mega2,        sf2ce,    cps1_12MHz, sf2,      cps_state, sf2h9,    ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Mega Co bootleg set 2, 920313 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2amf5,         sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Alpha Magic-F bootleg set 3, 920313 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2cejabl,       sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "bootleg",  "Street Fighter II': Champion Edition (920322 Japan bootleg set 1)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2rb5,          sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Rainbow bootleg set 5, 920322 Japan)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2hfjb,         sf2ce,    cps1_12MHz, sf2j,     cps_state, sf2h13,   ROT0,   "bootleg",  "Street Fighter II' Turbo: Hyper Fighting (bootleg set 1, 921209 Japan)", MACHINE_SUPPORTS_SAVE ) // bad tile for Blanka on player select screen
HACK( 2021, sf2rbpr,         sf2ce,    cps1_12MHz, sf2rb,    cps_state, cps1,     ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Rainbow, bootleg, set 1, protection removed)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2amf6,         sf2ce,    cps1_12MHz, sf2hack,  cps_state, sf2hack,  ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Alpha Magic-F bootleg set 4, 920313 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2amf7,         sf2ce,    cps1_12MHz, sf2hack,  cps_state, sf2hack,  ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Alpha Magic-F bootleg set 5, 920313 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2tlona,        sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Tu Long bootleg set 1, 811102 001)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2tlonb,        sf2ce,    cps1_12MHz, sf2,      cps_state, cps1,     ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Tu Long bootleg set 2, 811102 001)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2tlonc,        sf2ce,    cps1_12MHz, sf2hack,  cps_state, sf2hack,  ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Tu Long bootleg set 3, 811102 001)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2red2,         sf2ce,    cps1_12MHz, sf2hack,  cps_state, sf2hack,  ROT0,   "bootleg",  "Street Fighter II': Champion Edition (Red Wave bootleg set 2, 920313 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2v0042,        sf2ce,    cps1_12MHz, sf2hack,  cps_state, sf2hack,  ROT0,   "bootleg",  "Street Fighter II': Champion Edition (V004 bootleg set 2, 920313 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2yyc2,         sf2ce,    cps1_12MHz, sf2hack,  cps_state, sf2hack,  ROT0,   "bootleg",  "Street Fighter II': Champion Edition (YYC bootleg set 2, 920313 etc)", MACHINE_SUPPORTS_SAVE )
// Street Fighter II: The World Warrior
HACK( 2016, sf2hack01,       sf2,      cps1_10MHz, sf2j,     cps_state, cps1,     ROT0,   "hack",     "Street Fighter II: The World Warrior (12 Person Version 2016-01-01)", MACHINE_SUPPORTS_SAVE )
HACK( 2014, sf2hack02,       sf2,      cps1_10MHz, sf2j,     cps_state, cps1,     ROT0,   "hack",     "Street Fighter II: The World Warrior (Version Simplified 2014-03-24)", MACHINE_SUPPORTS_SAVE )
HACK( 1991, sf2hack03,       sf2,      cps1_10MHz, sf2,      cps_state, cps1,     ROT0,   "DDJ",      "Street Fighter II: The World Warrior (Easy Move)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, sf2hack04,       sf2,      cps1_10MHz, sf2,      cps_state, cps1,     ROT0,   "DDJ",      "Street Fighter II: The World Warrior (Hit Any Where 2018-08-22)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, sf2hack05,       sf2,      cps1_10MHz, sf2,      cps_state, cps1,     ROT0,   "DDJ",      "Street Fighter II: The World Warrior (Magic Throw 2018-08-22)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, sf2hack06,       sf2,      cps1_10MHz, sf2j,     cps_state, cps1,     ROT0,   "hack",     "Street Fighter II: The World Warrior (Chinese Voice Version Simplified 2020-06-30)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 1991, sf2c,            sf2,      cps1_10MHz, sf2j,     cps_state, cps1,     ROT0,   "bootleg",  "Street Fighter II: The World Warrior (Chinese 911210)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, sf2ly,           sf2,      cps1_10MHz, sf2j,     cps_state, cps1,     ROT0,   "bootleg",  "Street Fighter II': The World Warrior (with bosses like Champion Edition, 910522 Japan, CPS-B-11)", MACHINE_SUPPORTS_SAVE )
// Saturday Night Slam Masters
HACK( 1993, slammasthack01,  slammast, qsound,     slammast, cps_state, slammast, ROT0,   "ckc7213",  "Saturday Night Slam Masters (Easy Move)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 1994, slammastud,      slammast, qsound,     slammast, cps_state, slammast, ROT0,   "hack",     "Saturday Night Slam Masters (USA 930713 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
// Varth: Operation Thunderstorm
HACK( 1992, varthhack01,     varth,    cps1_12MHz, varth,    cps_state, cps1,     ROT270, "HOOOOOOK", "Varth: Operation Thunderstorm (Ex Super Version)", MACHINE_SUPPORTS_SAVE )
// Willow
HACK( 1989, willowhack01,    willow,   cps1_10MHz, willow,   cps_state, cps1,     ROT0,   "LB70",     "Willow (Ex Super Version)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, willowhack02,    willow,   cps1_10MHz, willow,   cps_state, cps1,     ROT0,   "Antigeno", "Willow (Translation Portuguese)", MACHINE_SUPPORTS_SAVE )
// Tenchi wo Kurau II
HACK( 1992, twkhack01,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "xyz555",   "Tenchi wo Kurau II (New Start Boss)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, twkhack02,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Boss Cho Unparalleled Edition 2016-02-28)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, twkhack03,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "Katana",   "Tenchi wo Kurau II (Warriors Version 2)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, twkhack04,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "wuzu2001", "Tenchi wo Kurau II (The First Pass In The World)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, twkhack05,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "wuzu2001", "Tenchi wo Kurau II (Portor (Kan-U)'s Horseback Energy Attack With Flaming Arrow Effect)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, twkhack06,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Wolf Edition 2017-12-23)", MACHINE_SUPPORTS_SAVE )
HACK( 2014, twkhack07,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Lidian)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, twkhack08,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Boss Cho Unparalleled Edition 2016-02-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, twkhack09,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Boss Cho Unparalleled Edition 2016-02-25)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, twkhack10,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Zhao Wei Edition 2017-01-27)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, twkhack11,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Warriors of Fate Plus 2 2018)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, twkhack12,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (San Mei Wu Shuang 2018)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, twkhack13,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "Bindi",    "Tenchi wo Kurau II (Da Ren Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, twkhack14,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "wuzu2001", "Tenchi wo Kurau II (Beauty Stage)(Ordinary Roms)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, twkhack15,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Ma Zhan Wu Shuang 2018-06-03)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, twkhack16,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Xia Hou Dun Plus)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, twkhack17,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Three Boss Edition 2017-11-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, twkhack18,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Iron Needle Edition 2016-09-13)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, twkhack19,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Li Dian Da Ren Edition 2018-06-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, twkhack20,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Full Attack Enhanced Version 2016-11-04)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, twkhack21,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Full Screen Attack Sanmei Wushuang version 2017-03-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, twkhack22,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (San Jian Sheng Super Edition 2018-02-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, twkhack23,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Xu Chu Wushuang Edition 2019-08-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, twkhack24,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Z Lu Bu 2019-08-24)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, twkhack25,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Master Fighting Edition 2019-09-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, twkhack26,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Li Dianda Random Edition 2019-07-27)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, twkhack27,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",     "Tenchi wo Kurau II (Dared Evil Boss Edition 2020-04-23)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, twkhack28,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "Bindi",    "Tenchi wo Kurau II (Master Edition 2020-09-28)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 1992, wofh,        wof,      sk2h3,      sk2h1,    cps_state, sk2h1,    ROT0,   "bootleg", "Sangokushi II: Sanguo Yingxiong Zhuan (Chinese bootleg set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofha,       wof,      sk2h3,      sk2h1,    cps_state, sk2h1,    ROT0,   "bootleg", "Sangokushi II: Sanguo Yingxiong Zhuan (Chinese bootleg set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
//HACK( 1992, sgyxz,       wof,      sk2h3,      sk2h3,    cps_state, sk2h3,    ROT0,   "bootleg", "Sangokushi II: Sanguo Yingxiong Zhuan (Chinese bootleg set 3, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofah,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "bootleg", "Sangokushi II (hack set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofaha,      wof,      qsound,     wof,      cps_state, wof,      ROT0,   "bootleg", "Sangokushi II (hack set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofahb,      wof,      qsound,     wof,      cps_state, wof,      ROT0,   "bootleg", "Sangokushi II (hack set 3, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wof3js,      wof,      qsound,     sk2h21,   cps_state, sk2h21,   ROT0,   "bootleg", "Sangokushi II: San Jian Sheng (Chinese bootleg set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wof3jsa,     wof,      sk2h3,      sk2h21,   cps_state, sk2h22,   ROT0,   "bootleg", "Sangokushi II: San Jian Sheng (Chinese bootleg set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wof3sj,      wof,      sk2h31,     sk2h31,   cps_state, sk2h22,   ROT0,   "bootleg", "Sangokushi II: San Sheng Jian (Chinese bootleg set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wof3sja,     wof,      sk2h31,     sk2h31,   cps_state, sk2h22,   ROT0,   "bootleg", "Sangokushi II: San Sheng Jian (Chinese bootleg set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofsj,       wof,      sk2h31,     sk2h31,   cps_state, sk2h22,   ROT0,   "bootleg", "Sangokushi II: Sheng Jian Sanguo (Chinese bootleg set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofsja,      wof,      sk2h31,     sk2h31,   cps_state, sk2h22,   ROT0,   "bootleg", "Sangokushi II: Sheng Jian Sanguo (Chinese bootleg set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofsjb,      wof,      sk2h35,     wof,      cps_state, sk2h35,   ROT0,   "bootleg", "Sangokushi II: Sheng Jian Sanguo (Chinese bootleg set 3, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofsjc,      wof,      sk2h31,     sk2h31,   cps_state, sk2h22,   ROT0,   "bootleg", "Sangokushi II: Sheng Jian Sanguo (Chinese bootleg set 4, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
// Tenchi wo Kurau II (wofch)
HACK( 1994, wofchhack01, wofch,    qsound,     wofch,    cps_state, wof,      ROT0,   "Katana", "Tenchi wo Kurau II (True Purgatory Edition 2016-02-28)", MACHINE_SUPPORTS_SAVE )
HACK( 1994, wofchhack02, wofch,    qsound,     wofch,    cps_state, wof,      ROT0,   "Katana", "Tenchi wo Kurau II (Sangokushi III Gaiden: Kakou-on's Revenge)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, wofchhack03, wofch,    qsound,     wofch,    cps_state, wof,      ROT0,   "hack",   "Tenchi wo Kurau II (Many Boss Extreme 2018-06-14)", MACHINE_SUPPORTS_SAVE )
// Sangokushi 3 Gaiden Kakou-On S Revence Dx
HACK( 2016, sk3hack01,   wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack", "Sangokushi 3 Gaiden Kakou_On S Revenge Prologue 1 2016-02-28)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, sk3hack02,   wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack", "Sangokushi 3 Gaiden Kakou-On S Revenge Prologue 2 2016-03-08)", MACHINE_SUPPORTS_SAVE )
HACK( 2010, sk3hack03,   wofch,    qsound,     wofch,    cps_state, wof,      ROT0,   "hack", "Sangokushi 3 Gaiden Kakou-On S Revence Dx 2010", MACHINE_SUPPORTS_SAVE )
HACK( 2017, sk3hack04,   wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack", "Sangokushi 3 (Xia Houen's revenge 2017 full attack 2017-04-03)", MACHINE_SUPPORTS_SAVE )
// Warriors of Fate
HACK( 2013, wofhack01,   wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",    "Warriors of Fate (1VS3 2013-04-05)", MACHINE_SUPPORTS_SAVE )
HACK( 2003, wofhack02,   wof,      qsound,     wof,      cps_state, wof,      ROT0,   "Shyma.X", "Warriors of Fate (Translation French 2003-07-28)", MACHINE_SUPPORTS_SAVE )
// bootleg
HACK( 1992, wofr1bl,     wof,      qsound,     wof,      cps_state, wofb,     ROT0,   "bootleg", "Warriors of Fate (bootleg, 921002 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofpic,      wof,      qsound,     wof,      cps_state, wofb,     ROT0,   "bootleg", "Warriors of Fate (bootleg with PIC16C57, 921002 etc)", MACHINE_SUPPORTS_SAVE )
HACK( 1992, wofud,       wof,      qsound,     wof,      cps_state, wof,      ROT0,   "hack",    "Warriors of Fate (USA 921031 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
