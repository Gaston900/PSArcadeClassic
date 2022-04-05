// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/pgm.cpp"

#if 0
// unused code from mame plus

void pgm_arm_type1_state::kovplus_fix_patch()
{
	UINT8 *mem8 = (UINT8 *)(memregion("maincpu")->base());

	mem8[0x1085D4] = 0x1B;
	mem8[0x1085D5] = 0x3;
	mem8[0x1085D6] = 0x1B;
	mem8[0x1085D7] = 0xA4;
	mem8[0x10EBEE] = 0x10;
	mem8[0x10EBEF] = 0x15;
	mem8[0x10EBF0] = 0x1A;
	mem8[0x10EBF1] = 0x11;
	mem8[0x11D3E4] = 0xC9;
	mem8[0x11D3E5] = 0xF8;
	mem8[0x11D3E6] = 0xB4;
	mem8[0x11D3E7] = 0x9A;
	mem8[0x11D492] = 0xA;
	mem8[0x11D493] = 0x5A;
	mem8[0x11D494] = 0xA;
	mem8[0x11D495] = 0x6D;
	mem8[0x11DAC6] = 0x18;
	mem8[0x11DAC7] = 0x3B;
	mem8[0x11DAC8] = 0xD1;
	mem8[0x11DAC9] = 0xFE;
	mem8[0x11DACA] = 0xE9;
	mem8[0x11DACB] = 0xE;
	mem8[0x11DACC] = 0x90;
	mem8[0x11DACD] = 0x6B;
	mem8[0x11DACE] = 0x90;
	mem8[0x11DACF] = 0xF;
	mem8[0x11DAD1] = 0x41;
	mem8[0x11DE56] = 0x12;
	mem8[0x11DE57] = 0x7F;
	mem8[0x11DE58] = 0xD3;
	mem8[0x11DE59] = 0x1C;
	mem8[0x11DE5A] = 0xEB;
	mem8[0x11DE5B] = 0xEA;
	mem8[0x11DE5D] = 0x86;
	mem8[0x11DE60] = 0x10;
	mem8[0x11DE61] = 0x7F;
	mem8[0x11DE62] = 0xD1;
	mem8[0x11DE63] = 0x82;
	mem8[0x11DE64] = 0xE9;
	mem8[0x11DE65] = 0xB6;
	mem8[0x11DF72] = 0x12;
	mem8[0x11DF73] = 0x53;
	mem8[0x11DF74] = 0xD3;
	mem8[0x11DF75] = 0x84;
	mem8[0x11DF76] = 0xEB;
	mem8[0x11DF77] = 0xB8;
	mem8[0x11DF79] = 0x2A;
	mem8[0x11DF7C] = 0x12;
	mem8[0x11DF7D] = 0x23;
	mem8[0x11DF7E] = 0xD3;
	mem8[0x11DF7F] = 0xDC;
	mem8[0x11DF80] = 0x69;
	mem8[0x11DF81] = 0x7C;
	mem8[0x12E7A4] = 0x95;
	mem8[0x12E7A5] = 0xCA;
	mem8[0x12E7A6] = 0x54;
	mem8[0x12E7A8] = 0x6C;
	mem8[0x12E7A9] = 0x5;
	mem8[0x13B25E] = 0xBA;
	mem8[0x13B25F] = 0xBF;
	mem8[0x1463A0] = 0x95;
	mem8[0x1463A1] = 0x87;
	mem8[0x1463A2] = 0x7F;
	mem8[0x1463A3] = 0x95;
	mem8[0x1463A4] = 0xB4;
	mem8[0x1463A5] = 0x31;
	mem8[0x1463A6] = 0x15;
	mem8[0x1463A8] = 0x1D;
	mem8[0x162408] = 0xB9;
	mem8[0x162409] = 0x63;
	mem8[0x1655E0] = 0x54;
	mem8[0x1655E2] = 0x68;
	mem8[0x1655E4] = 0x4D;
	mem8[0x1655E5] = 0xBA;
	mem8[0x1655E6] = 0xD1;
	mem8[0x1655E7] = 0x23;
	mem8[0x1655E8] = 0xE9;
	mem8[0x1655EA] = 0x28;
	mem8[0x1655EB] = 0x6A;
	mem8[0x183476] = 0xDC;
	mem8[0x183477] = 0xE7;
	mem8[0x183DB6] = 0x3D;
	mem8[0x32A00A] = 0x21;
	mem8[0x32A00C] = 0x46;
	mem8[0x32A00D] = 0x93;
	mem8[0x32A01E] = 0x8B;
	mem8[0x32A020] = 0x7E;
	mem8[0x32A021] = 0xD0;
	mem8[0x381000] = 0x50;
	mem8[0x381001] = 0x45;
	mem8[0x381002] = 0xE9;
	mem8[0x381003] = 0x1C;
	mem8[0x381004] = 0x87;
	mem8[0x381005] = 0x3F;
	mem8[0x381006] = 0x50;
	mem8[0x381007] = 0xE;
	mem8[0x381008] = 0x43;
	mem8[0x381009] = 0x62;
	mem8[0x38100A] = 0xC9;
	mem8[0x38100B] = 0x59;
	mem8[0x38100C] = 0xA7;
	mem8[0x38100D] = 0x4B;
	mem8[0x38100E] = 0xB0;
	mem8[0x38100F] = 0x4;
	mem8[0x381010] = 0x78;
	mem8[0x381011] = 0x67;
	mem8[0x381012] = 0xB9;
	mem8[0x381013] = 0x97;
	mem8[0x382000] = 0x50;
	mem8[0x382001] = 0x1B;
	mem8[0x382002] = 0x63;
	mem8[0x382003] = 0x1C;
	mem8[0x382004] = 0xE9;
	mem8[0x382005] = 0xE3;
	mem8[0x382006] = 0x87;
	mem8[0x382007] = 0xDE;
	mem8[0x382008] = 0xB0;
	mem8[0x382009] = 0x2C;
	mem8[0x38200A] = 0x58;
	mem8[0x38200B] = 0x59;
	mem8[0x38200C] = 0x15;
	mem8[0x38200D] = 0x49;
	mem8[0x383000] = 0x50;
	mem8[0x383001] = 0x1B;
	mem8[0x383002] = 0x60;
	mem8[0x383003] = 0x1C;
	mem8[0x383004] = 0xE9;
	mem8[0x383005] = 0xE3;
	mem8[0x383006] = 0x87;
	mem8[0x383007] = 0xDE;
	mem8[0x383008] = 0xB0;
	mem8[0x383009] = 0x2C;
	mem8[0x38300A] = 0x58;
	mem8[0x38300B] = 0x59;
	mem8[0x38300C] = 0x2F;
	mem8[0x38300D] = 0x49;
	mem8[0x384000] = 0x50;
	mem8[0x384001] = 0x1B;
	mem8[0x384002] = 0x63;
	mem8[0x384003] = 0x1C;
	mem8[0x384004] = 0xE9;
	mem8[0x384005] = 0xE3;
	mem8[0x384006] = 0x87;
	mem8[0x384007] = 0xDE;
	mem8[0x384008] = 0x90;
	mem8[0x384009] = 0x2C;
	mem8[0x38400A] = 0x78;
	mem8[0x38400B] = 0x59;
	mem8[0x38400C] = 0x11;
	mem8[0x38400D] = 0x48;
	mem8[0x385000] = 0x50;
	mem8[0x385001] = 0x1B;
	mem8[0x385002] = 0x60;
	mem8[0x385003] = 0x1C;
	mem8[0x385004] = 0xE9;
	mem8[0x385005] = 0xE3;
	mem8[0x385006] = 0x87;
	mem8[0x385007] = 0xDE;
	mem8[0x385008] = 0x90;
	mem8[0x385009] = 0x2C;
	mem8[0x38500A] = 0x78;
	mem8[0x38500B] = 0x59;
	mem8[0x38500C] = 0xEB;
	mem8[0x38500D] = 0x48;
	mem8[0x386000] = 0x5;
	mem8[0x386001] = 0x5D;
	mem8[0x386002] = 0x71;
	mem8[0x386003] = 0x1C;
	mem8[0x386004] = 0x6D;
	mem8[0x386005] = 0x84;
	mem8[0x386006] = 0x5;
	mem8[0x386007] = 0x40;
	mem8[0x386008] = 0x71;
	mem8[0x386009] = 0x62;
	mem8[0x38600A] = 0xC5;
	mem8[0x38600B] = 0x51;
	mem8[0x38600C] = 0x6C;
	mem8[0x38600D] = 0x97;
	mem8[0x38600E] = 0x79;
	mem8[0x38600F] = 0x4B;
	mem8[0x386010] = 0x90;
	mem8[0x386011] = 0x29;
	mem8[0x386012] = 0x7B;
	mem8[0x386013] = 0x4D;
	mem8[0x386014] = 0xC3;
	mem8[0x386015] = 0xF8;
}

void pgm_arm_type1_state::kovboot_fix_patch()
{
	UINT8 *mem8 = (UINT8 *)(memregion("maincpu")->base());

	mem8[0x1085D4] = 0x71;
	mem8[0x1085D5] = 0x4E;
	mem8[0x1085D6] = 0x71;
	mem8[0x1085D7] = 0x4E;
	mem8[0x11D3E4] = 0x29;
	mem8[0x11D3E5] = 0x42;
	mem8[0x11D3E6] = 0x54;
	mem8[0x11D3E7] = 0x29;
	mem8[0x11D492] = 0x71;
	mem8[0x11D493] = 0x4E;
	mem8[0x11D494] = 0x71;
	mem8[0x11D495] = 0x4E;
	mem8[0x11DAC6] = 0xF9;
	mem8[0x11DAC7] = 0x4E;
	mem8[0x11DAC8] = 0x38;
	mem8[0x11DAC9] = 0x0;
	mem8[0x11DACA] = 0x0;
	mem8[0x11DACB] = 0xF;
	mem8[0x11DACC] = 0x71;
	mem8[0x11DACD] = 0x4E;
	mem8[0x11DACE] = 0x71;
	mem8[0x11DACF] = 0x4E;
	mem8[0x11DAD1] = 0x65;
	mem8[0x11DE56] = 0xF9;
	mem8[0x11DE57] = 0x4E;
	mem8[0x11DE58] = 0x38;
	mem8[0x11DE59] = 0x0;
	mem8[0x11DE5A] = 0x20;
	mem8[0x11DE5B] = 0xF;
	mem8[0x11DE5D] = 0x64;
	mem8[0x11DE60] = 0xF9;
	mem8[0x11DE61] = 0x4E;
	mem8[0x11DE62] = 0x38;
	mem8[0x11DE63] = 0x0;
	mem8[0x11DE64] = 0x30;
	mem8[0x11DE65] = 0x0F;
	mem8[0x11DF72] = 0xF9;
	mem8[0x11DF73] = 0x4E;
	mem8[0x11DF74] = 0x38;
	mem8[0x11DF75] = 0x0;
	mem8[0x11DF76] = 0x40;
	mem8[0x11DF77] = 0x0F;
	mem8[0x11DF79] = 0x64;
	mem8[0x11DF7C] = 0xF9;
	mem8[0x11DF7D] = 0x4E;
	mem8[0x11DF7E] = 0x38;
	mem8[0x11DF7F] = 0x0;
	mem8[0x11DF80] = 0x50;
	mem8[0x11DF81] = 0x0F;
	mem8[0x12E7A4] = 0xF9;
	mem8[0x12E7A5] = 0x4E;
	mem8[0x12E7A6] = 0x38;
	mem8[0x12E7A8] = 0x60;
	mem8[0x12E7A9] = 0x0F;
	mem8[0x13B25E] = 0x71;
	mem8[0x13B25F] = 0x4E;
	mem8[0x1463A0] = 0xF9;
	mem8[0x1463A1] = 0x4E;
	mem8[0x1463A2] = 0x13;
	mem8[0x1463A3] = 0x0;
	mem8[0x1463A4] = 0xD0;
	mem8[0x1463A5] = 0xB5;
	mem8[0x1463A6] = 0x71;
	mem8[0x1463A8] = 0x71;
	mem8[0x162408] = 0xD0;
	mem8[0x162409] = 0x1;
	mem8[0x1655E0] = 0x3C;
	mem8[0x1655E2] = 0x0;
	mem8[0x1655E4] = 0x25;
	mem8[0x1655E5] = 0x0;
	mem8[0x1655E6] = 0xB9;
	mem8[0x1655E7] = 0x90;
	mem8[0x1655E8] = 0x81;
	mem8[0x1655EA] = 0x40;
	mem8[0x1655EB] = 0xB2;
	mem8[0x183476] = 0xB5;
	mem8[0x183477] = 0x1;
	mem8[0x183DB6] = 0x50;
	mem8[0x32A00A] = 0x68;
	mem8[0x32A00C] = 0xF;
	mem8[0x32A00D] = 0x4;
	mem8[0x32A01E] = 0xC0;
	mem8[0x32A020] = 0x13;
	mem8[0x32A021] = 0x2;
	mem8[0x380F00] = 0x39;
	mem8[0x380F01] = 0x52;
	mem8[0x380F02] = 0x80;
	mem8[0x380F03] = 0x0;
	mem8[0x380F04] = 0xEE;
	mem8[0x380F05] = 0xDC;
	mem8[0x380F06] = 0x39;
	mem8[0x380F07] = 0xC;
	mem8[0x380F08] = 0xA;
	mem8[0x380F09] = 0x0;
	mem8[0x380F0A] = 0x80;
	mem8[0x380F0B] = 0x0;
	mem8[0x380F0C] = 0xEE;
	mem8[0x380F0D] = 0xDC;
	mem8[0x380F0E] = 0xF9;
	mem8[0x380F0F] = 0x4E;
	mem8[0x380F10] = 0x11;
	mem8[0x380F11] = 0x0;
	mem8[0x380F12] = 0xD0;
	mem8[0x380F13] = 0xDA;
	mem8[0x380F20] = 0x39;
	mem8[0x380F21] = 0xC;
	mem8[0x380F22] = 0xA;
	mem8[0x380F23] = 0x0;
	mem8[0x380F24] = 0x80;
	mem8[0x380F25] = 0x0;
	mem8[0x380F26] = 0xEE;
	mem8[0x380F27] = 0xDC;
	mem8[0x380F28] = 0xF9;
	mem8[0x380F29] = 0x4E;
	mem8[0x380F2A] = 0x11;
	mem8[0x380F2B] = 0x0;
	mem8[0x380F2C] = 0x5C;
	mem8[0x380F2D] = 0xDE;
	mem8[0x380F30] = 0x39;
	mem8[0x380F31] = 0xC;
	mem8[0x380F32] = 0x9;
	mem8[0x380F33] = 0x0;
	mem8[0x380F34] = 0x80;
	mem8[0x380F35] = 0x0;
	mem8[0x380F36] = 0xEE;
	mem8[0x380F37] = 0xDC;
	mem8[0x380F38] = 0xF9;
	mem8[0x380F39] = 0x4E;
	mem8[0x380F3A] = 0x11;
	mem8[0x380F3B] = 0x0;
	mem8[0x380F3C] = 0x66;
	mem8[0x380F3D] = 0xDE;
	mem8[0x380F40] = 0x39;
	mem8[0x380F41] = 0xC;
	mem8[0x380F42] = 0xA;
	mem8[0x380F43] = 0x0;
	mem8[0x380F44] = 0x80;
	mem8[0x380F45] = 0x0;
	mem8[0x380F46] = 0xEE;
	mem8[0x380F47] = 0xDC;
	mem8[0x380F48] = 0xF9;
	mem8[0x380F49] = 0x4E;
	mem8[0x380F4A] = 0x11;
	mem8[0x380F4B] = 0x0;
	mem8[0x380F4C] = 0x78;
	mem8[0x380F4D] = 0xDF;
	mem8[0x380F50] = 0x39;
	mem8[0x380F51] = 0xC;
	mem8[0x380F52] = 0x9;
	mem8[0x380F53] = 0x0;
	mem8[0x380F54] = 0x80;
	mem8[0x380F55] = 0x0;
	mem8[0x380F56] = 0xEE;
	mem8[0x380F57] = 0xDC;
	mem8[0x380F58] = 0xF9;
	mem8[0x380F59] = 0x4E;
	mem8[0x380F5A] = 0x11;
	mem8[0x380F5B] = 0x0;
	mem8[0x380F5C] = 0x82;
	mem8[0x380F5D] = 0xDF;
	mem8[0x380F60] = 0x6C;
	mem8[0x380F61] = 0x4A;
	mem8[0x380F62] = 0x18;
	mem8[0x380F63] = 0x0;
	mem8[0x380F64] = 0x4;
	mem8[0x380F65] = 0x67;
	mem8[0x380F66] = 0x6C;
	mem8[0x380F67] = 0x42;
	mem8[0x380F68] = 0x18;
	mem8[0x380F69] = 0x0;
	mem8[0x380F6A] = 0xAC;
	mem8[0x380F6B] = 0x8;
	mem8[0x380F6C] = 0x5;
	mem8[0x380F6D] = 0x0;
	mem8[0x380F6E] = 0x10;
	mem8[0x380F6F] = 0x1;
	mem8[0x380F70] = 0xF9;
	mem8[0x380F71] = 0x4E;
	mem8[0x380F72] = 0x12;
	mem8[0x380F73] = 0x0;
	mem8[0x380F74] = 0xAA;
	mem8[0x380F75] = 0xE7;
}

void pgm_arm_type1_state::kovshp_fix_patch()
{
	UINT8 *mem8 = (UINT8 *)(memregion("prot")->base());

	mem8[0x2892] = 0x1;
	mem8[0x2893] = 0x1;
	mem8[0x289F] = 0x1;
	mem8[0x28A5] = 0x1;
	mem8[0x28A8] = 0x1;
	mem8[0x28A9] = 0x1;
	mem8[0x2BF3] = 0x48;
	mem8[0x2BF5] = 0x80;
	mem8[0x2C92] = 0xF;
	mem8[0x2C93] = 0x40;
	mem8[0x2CE1] = 0x6C;
	mem8[0x2CE2] = 0x48;
}

DRIVER_INIT_MEMBER(pgm_arm_type1_state,kovshp)
{
	pgm_basic_init();
	kovshp_fix_patch();    // extra line here
	pgm_kovshp_decrypt(machine());
	pgm_arm7_type1_latch_init();
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x4f0008, 0x4f0009, read16_delegate(FUNC(pgm_arm_type1_state::kovsh_fake_region_r),this));
	m_maincpu->space(AS_PROGRAM).install_write_handler(0x500000, 0x500005, write16_delegate(FUNC(pgm_arm_type1_state::kovshp_asic27a_write_word),this));
}

DRIVER_INIT_MEMBER(pgm_arm_type1_state,kovassga)
{
	pgm_basic_init();
	kovshp_fix_patch();     // extra line here
//  pgm_kovshp_decrypt(machine());
	pgm_arm7_type1_latch_init();
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x4f0008, 0x4f0009, read16_delegate(FUNC(pgm_arm_type1_state::kovsh_fake_region_r),this));
	m_maincpu->space(AS_PROGRAM).install_write_handler(0x500000, 0x500005, write16_delegate(FUNC(pgm_arm_type1_state::kovshp_asic27a_write_word),this));
}

void pgm_arm_type1_state::pgm_decode_kovassg_program()
{
	int i;
	UINT16 *src = (UINT16 *)(memregion("maincpu")->base() + 0x100000);
	std::vector<UINT16> dst(0x400000);

	for (i = 0; i < 0x400000 / 2; i++)
	{
		int j = (i & ~0xffff) | (BITSWAP16(i, 15, 14, 13, 12,  11, 10, 7, 3,  1, 9, 4, 8,  6, 0, 2, 5) ^ 0x019c);

		dst[j] = BITSWAP16(src[j], 13, 9, 10, 11, 2, 0, 12 ,5, 4, 1, 14, 8, 15, 6, 3, 7) ^ 0x9d05;
	}

	memcpy( src, &dst[0], 0x400000 );
}

DRIVER_INIT_MEMBER(pgm_arm_type1_state,kovassg)
{
	pgm_decode_kovassg_program();
	pgm_decode_kovlsqh2_tiles();

	pgm_decode_kovlsqh2_sprites(memregion("sprcol")->base() + 0x0000000);
	pgm_decode_kovlsqh2_sprites(memregion("sprcol")->base() + 0x0800000);
	pgm_decode_kovlsqh2_sprites(memregion("sprcol")->base() + 0x1000000);
	pgm_decode_kovlsqh2_sprites(memregion("sprcol")->base() + 0x1800000);
	pgm_decode_kovlsqh2_sprites(memregion("sprcol")->base() + 0x2000000);
	pgm_decode_kovlsqh2_sprites(memregion("sprcol")->base() + 0x2800000);
	pgm_decode_kovlsqh2_sprites(memregion("sprmask")->base() + 0x0000000);
	pgm_decode_kovlsqh2_sprites(memregion("sprmask")->base() + 0x0800000);

	pgm_decode_kovlsqh2_samples();
	pgm_basic_init();
	pgm_arm7_type1_latch_init();
	/* we only have a china internal ROM dumped for now.. allow region to be changed for debugging (to ensure all alt titles / regions can be seen) */
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x4f0008, 0x4f0009, read16_delegate(FUNC(pgm_arm_type1_state::kovsh_fake_region_r),this));
}

DRIVER_INIT_MEMBER(pgm_arm_type1_state,kovplus)
{
	pgm_basic_init();
	kovplus_fix_patch();     // extra line here
	pgm_kov_decrypt(machine());
	pgm_arm7_type1_latch_init();
	m_curslots = 0;
	m_kov_c0_value = 0;
	m_kov_cb_value = 0;
	m_kov_fe_value = 0;
	arm_sim_handler = &pgm_arm_type1_state::command_handler_kov;
	m_maincpu->space(AS_PROGRAM).install_readwrite_handler(0x500000, 0x500005, read16_delegate(FUNC(pgm_arm_type1_state::pgm_arm7_type1_sim_r),this), write16_delegate(FUNC(pgm_arm_type1_state::pgm_arm7_type1_sim_w),this));
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x4f0000, 0x4f003f, read16_delegate(FUNC(pgm_arm_type1_state::pgm_arm7_type1_sim_protram_r),this));
}

DRIVER_INIT_MEMBER(pgm_arm_type1_state,kovboot)
{
	pgm_basic_init();
//  pgm_kov_decrypt(machine());
	kovboot_fix_patch();     // extra line here
	pgm_arm7_type1_latch_init();
	m_curslots = 0;
	m_kov_c0_value = 0;
	m_kov_cb_value = 0;
	m_kov_fe_value = 0;
	arm_sim_handler = &pgm_arm_type1_state::command_handler_kov;
	m_maincpu->space(AS_PROGRAM).install_readwrite_handler(0x500000, 0x500005, read16_delegate(FUNC(pgm_arm_type1_state::pgm_arm7_type1_sim_r),this), write16_delegate(FUNC(pgm_arm_type1_state::pgm_arm7_type1_sim_w),this));
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x4f0000, 0x4f003f, read16_delegate(FUNC(pgm_arm_type1_state::pgm_arm7_type1_sim_protram_r),this));

}
#endif

 /*****************
 The Killing Blade
********************/

ROM_START( killbldhack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0300_v109_hack01.rom", 0x100000, 0x200000, CRC(5f44677a) SHA1(b36ed941ad5617749fb0a2913e1718cb6707cf5b) )

	ROM_REGION( 0x010000, "igs022", 0 )
	ROM_LOAD( "kb_u2_v109.rom", 0x000000, 0x010000,  CRC(de3eae63) SHA1(03af767ef764055bda528b5cc6a24b9e1218cca8) )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0300.u14",    0x180000, 0x400000, CRC(0922f7d9) SHA1(4302b4b7369e13f315fad14f7d6cad1321101d24) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0300.u9",    0x0000000, 0x0400000,  CRC(3f9455d3) SHA1(3718ce00ad93975383aafc14e5a74dc297b011a1) )
	ROM_LOAD( "a0301.u10",   0x0400000, 0x0400000,  CRC(92776889) SHA1(6d677837fefff47bfd1c6166322f69f89989a5e2) )
	ROM_LOAD( "a0303.u11",   0x0800000, 0x0400000,  CRC(33f5cc69) SHA1(9cacd5058d4bb25b77f71658bbbbd4b38d0a6b6a) )
	ROM_LOAD( "a0306.u12",   0x0c00000, 0x0400000,  CRC(cc018a8e) SHA1(37752d46f238fb57c0ab5a4f96b1e013f2077347) )
	ROM_LOAD( "a0307.u2",    0x1000000, 0x0400000,  CRC(bc772e39) SHA1(079cc42a190cb916f02b59bca8fa90e524acefe9) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0300.u13",    0x0000000, 0x0400000, CRC(7f876981) SHA1(43555a200929ad5ecc42137fc9aeb42dc4f50d20) )
	ROM_LOAD( "b0302.u14",    0x0400000, 0x0400000, CRC(eea9c502) SHA1(04b3972c7111ea59a3cceab6ad124080c4ce3520) )
	ROM_LOAD( "b0303.u15",    0x0800000, 0x0200000, CRC(77a9652e) SHA1(2342f643d37945fbda224a5034c013796e5134ca) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0300.u1",     0x400000, 0x400000, CRC(93159695) SHA1(50c5976c9b681bd3d1ebefa3bfa9fe6e72dcb96f) )
ROM_END

ROM_START( killbldhack02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0300_v109_hack02.rom", 0x100000, 0x200000, CRC(1e8134e0) SHA1(023588da0da4f5d9edf5a66cb00529bf1aa65870) )

	ROM_REGION( 0x010000, "igs022", 0 )
	ROM_LOAD( "kb_u2_v109.rom", 0x000000, 0x010000,  CRC(de3eae63) SHA1(03af767ef764055bda528b5cc6a24b9e1218cca8) )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0300.u14",    0x180000, 0x400000, CRC(0922f7d9) SHA1(4302b4b7369e13f315fad14f7d6cad1321101d24) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0300.u9",    0x0000000, 0x0400000,  CRC(3f9455d3) SHA1(3718ce00ad93975383aafc14e5a74dc297b011a1) )
	ROM_LOAD( "a0301.u10",   0x0400000, 0x0400000,  CRC(92776889) SHA1(6d677837fefff47bfd1c6166322f69f89989a5e2) )
	ROM_LOAD( "a0303.u11",   0x0800000, 0x0400000,  CRC(33f5cc69) SHA1(9cacd5058d4bb25b77f71658bbbbd4b38d0a6b6a) )
	ROM_LOAD( "a0306.u12",   0x0c00000, 0x0400000,  CRC(cc018a8e) SHA1(37752d46f238fb57c0ab5a4f96b1e013f2077347) )
	ROM_LOAD( "a0307.u2",    0x1000000, 0x0400000,  CRC(bc772e39) SHA1(079cc42a190cb916f02b59bca8fa90e524acefe9) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0300.u13",    0x0000000, 0x0400000, CRC(7f876981) SHA1(43555a200929ad5ecc42137fc9aeb42dc4f50d20) )
	ROM_LOAD( "b0302.u14",    0x0400000, 0x0400000, CRC(eea9c502) SHA1(04b3972c7111ea59a3cceab6ad124080c4ce3520) )
	ROM_LOAD( "b0303.u15",    0x0800000, 0x0200000, CRC(77a9652e) SHA1(2342f643d37945fbda224a5034c013796e5134ca) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0300.u1",     0x400000, 0x400000, CRC(93159695) SHA1(50c5976c9b681bd3d1ebefa3bfa9fe6e72dcb96f) )
ROM_END

ROM_START( killbldhack03 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0300_v109_hack03.rom", 0x100000, 0x200000, CRC(d82a1938) SHA1(71ed4109d5e451fed359e826ca53a8ed48e827a7) )

	ROM_REGION( 0x010000, "igs022", 0 )
	ROM_LOAD( "kb_u2_v109.rom", 0x000000, 0x010000,  CRC(de3eae63) SHA1(03af767ef764055bda528b5cc6a24b9e1218cca8) )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0300.u14",    0x180000, 0x400000, CRC(0922f7d9) SHA1(4302b4b7369e13f315fad14f7d6cad1321101d24) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0300.u9",    0x0000000, 0x0400000,  CRC(3f9455d3) SHA1(3718ce00ad93975383aafc14e5a74dc297b011a1) )
	ROM_LOAD( "a0301.u10",   0x0400000, 0x0400000,  CRC(92776889) SHA1(6d677837fefff47bfd1c6166322f69f89989a5e2) )
	ROM_LOAD( "a0303.u11",   0x0800000, 0x0400000,  CRC(33f5cc69) SHA1(9cacd5058d4bb25b77f71658bbbbd4b38d0a6b6a) )
	ROM_LOAD( "a0306.u12",   0x0c00000, 0x0400000,  CRC(cc018a8e) SHA1(37752d46f238fb57c0ab5a4f96b1e013f2077347) )
	ROM_LOAD( "a0307.u2",    0x1000000, 0x0400000,  CRC(bc772e39) SHA1(079cc42a190cb916f02b59bca8fa90e524acefe9) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0300.u13",    0x0000000, 0x0400000, CRC(7f876981) SHA1(43555a200929ad5ecc42137fc9aeb42dc4f50d20) )
	ROM_LOAD( "b0302.u14",    0x0400000, 0x0400000, CRC(eea9c502) SHA1(04b3972c7111ea59a3cceab6ad124080c4ce3520) )
	ROM_LOAD( "b0303.u15",    0x0800000, 0x0200000, CRC(77a9652e) SHA1(2342f643d37945fbda224a5034c013796e5134ca) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0300.u1",     0x400000, 0x400000, CRC(93159695) SHA1(50c5976c9b681bd3d1ebefa3bfa9fe6e72dcb96f) )
ROM_END

ROM_START( killbldhack04 ) //killbldqy
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0300_v109_hack04.rom", 0x100000, 0x200000, CRC(6f2ca623) SHA1(a1ce4a83bbef10d7c3dd18e74472a97a50db89f4) )

	ROM_REGION( 0x010000, "igs022", 0 )
	ROM_LOAD( "kb_u2_v109.rom", 0x000000, 0x010000,  CRC(de3eae63) SHA1(03af767ef764055bda528b5cc6a24b9e1218cca8) )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0300.u14",    0x180000, 0x400000, CRC(0922f7d9) SHA1(4302b4b7369e13f315fad14f7d6cad1321101d24) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0300.u9",    0x0000000, 0x0400000,  CRC(3f9455d3) SHA1(3718ce00ad93975383aafc14e5a74dc297b011a1) )
	ROM_LOAD( "a0301.u10",   0x0400000, 0x0400000,  CRC(92776889) SHA1(6d677837fefff47bfd1c6166322f69f89989a5e2) )
	ROM_LOAD( "a0303.u11",   0x0800000, 0x0400000,  CRC(33f5cc69) SHA1(9cacd5058d4bb25b77f71658bbbbd4b38d0a6b6a) )
	ROM_LOAD( "a0306.u12",   0x0c00000, 0x0400000,  CRC(cc018a8e) SHA1(37752d46f238fb57c0ab5a4f96b1e013f2077347) )
	ROM_LOAD( "a0307.u2",    0x1000000, 0x0400000,  CRC(bc772e39) SHA1(079cc42a190cb916f02b59bca8fa90e524acefe9) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0300.u13",    0x0000000, 0x0400000, CRC(7f876981) SHA1(43555a200929ad5ecc42137fc9aeb42dc4f50d20) )
	ROM_LOAD( "b0302.u14",    0x0400000, 0x0400000, CRC(eea9c502) SHA1(04b3972c7111ea59a3cceab6ad124080c4ce3520) )
	ROM_LOAD( "b0303.u15",    0x0800000, 0x0200000, CRC(77a9652e) SHA1(2342f643d37945fbda224a5034c013796e5134ca) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0300.u1",     0x400000, 0x400000, CRC(93159695) SHA1(50c5976c9b681bd3d1ebefa3bfa9fe6e72dcb96f) )
ROM_END

 /**********************
 The Killing Blade Plus
*************************/

ROM_START( killbldphack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v300xx_u6.rom",     0x100000, 0x080000, CRC(b7fb8ec9) SHA1(e71b2d74269a82c7155b9818821156e128b68b28) )

	ROM_REGION( 0x4000, "prot", 0 )

	ROM_LOAD( "killbldp_igs027a_alt.bin", 0x000000, 0x04000, CRC(98316b06) SHA1(09be9fad24d68980a0a5beae60ced48012286216) )

	ROM_REGION32_LE( 0x800000, "user1", 0 )
	ROM_LOAD( "v300x_hack01.u26", 0x000000, 0x200000,  CRC(222488cc) SHA1(c5e74be25d86d4230da982c037f9da75d12b145f) )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t05701w032.bin",0x180000, 0x400000, CRC(567c714f) SHA1(b25b20e1ec9f077d6f7b9d41723a68d0d461bef2) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a05701w064.bin",   0x0000000, 0x0800000, CRC(8c0c992c) SHA1(28391e50ca4400060676f1524bd49ede373292da) )
	ROM_LOAD( "a05702w064.bin",   0x0800000, 0x0800000, CRC(7e5b0f27) SHA1(9e8d69f34c30216925fcb7af87f8b37f703317e7) )
	ROM_LOAD( "a05703w064.bin",   0x1000000, 0x0800000, CRC(accbdb44) SHA1(d59b2452c7a5b4e666473dc973b73a0f2b4edc13) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b05701w064.bin",   0x0000000, 0x0800000, CRC(a20cdcef) SHA1(029a49971adf1e72ab556a207172bdfbd0b86b03) )
	ROM_LOAD( "b05702w016.bin",   0x0800000, 0x0200000, CRC(fe7457df) SHA1(d66b1b31102b0210f9faf40e1473cd1511ccaf1f) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "w05701b032.bin",   0x400000, 0x400000, CRC(2d3ae593) SHA1(b9c1d2994be95ba974bc134a3bf115bc9c9c9c16) )
ROM_END

ROM_START( killbldphack02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v300xx_u6.rom",     0x100000, 0x080000, CRC(b7fb8ec9) SHA1(e71b2d74269a82c7155b9818821156e128b68b28) )

	ROM_REGION( 0x4000, "prot", 0 )

	ROM_LOAD( "killbldp_igs027a_alt.bin", 0x000000, 0x04000, CRC(98316b06) SHA1(09be9fad24d68980a0a5beae60ced48012286216) )

	ROM_REGION32_LE( 0x800000, "user1", 0 )
	ROM_LOAD( "v300x_hack02.u26", 0x000000, 0x200004,  CRC(2d50157e) SHA1(a3c4c8fcc8e5de22868beb533fab965029fdc16d) )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t05701w032.bin",0x180000, 0x400000, CRC(567c714f) SHA1(b25b20e1ec9f077d6f7b9d41723a68d0d461bef2) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a05701w064.bin",   0x0000000, 0x0800000, CRC(8c0c992c) SHA1(28391e50ca4400060676f1524bd49ede373292da) )
	ROM_LOAD( "a05702w064.bin",   0x0800000, 0x0800000, CRC(7e5b0f27) SHA1(9e8d69f34c30216925fcb7af87f8b37f703317e7) )
	ROM_LOAD( "a05703w064.bin",   0x1000000, 0x0800000, CRC(accbdb44) SHA1(d59b2452c7a5b4e666473dc973b73a0f2b4edc13) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b05701w064.bin",   0x0000000, 0x0800000, CRC(a20cdcef) SHA1(029a49971adf1e72ab556a207172bdfbd0b86b03) )
	ROM_LOAD( "b05702w016.bin",   0x0800000, 0x0200000, CRC(fe7457df) SHA1(d66b1b31102b0210f9faf40e1473cd1511ccaf1f) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "w05701b032.bin",   0x400000, 0x400000, CRC(2d3ae593) SHA1(b9c1d2994be95ba974bc134a3bf115bc9c9c9c16) )
ROM_END

 /*****************
 Knights of Valour
********************/

ROM_START( kovhack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600-hack01.115",    0x100000, 0x400000, CRC(87a2f3c1) SHA1(68245d64dd25f16c1a22ca0280659e45092a4f93) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

 /************************
 Knights of Valour 2 Plus
***************************/

ROM_START( kov2phack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack01.rom",    0x100000, 0x400000, CRC(50e13216) SHA1(37fce0b64f3c3d870993eb229df8b6a4bab6173f) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack02 )
	ROM_REGION( 0xA54F47, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack02.rom", 0x100000, 0x454F47, CRC(8015801f) SHA1(94c31381eb1f4c3e1752860194251c8b097ca8b5) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china_hack02.bin", 0x000000, 0x04000, CRC(06214503) SHA1(ddede08011ab723a92a6da690e38903c173de2fa) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200-16_hack02.rom", 0x000000, 0x200000,  CRC(c27d1ce1) SHA1(69b732b25cc8e127fa8cc36654b904c0f9f88554) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack03 )
	ROM_REGION( 0xA54F47, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack03.rom",    0x100000, 0x454F47, CRC(11c8152e) SHA1(44cb00bb90d341f682fea646c5f925990d40d67f) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china_hack02.bin", 0x000000, 0x04000, CRC(06214503) SHA1(ddede08011ab723a92a6da690e38903c173de2fa) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack04 )
	ROM_REGION( 0xA54F47, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack04.rom",    0x100000, 0x454F47, CRC(5f2fd667) SHA1(a4a27e1948c7df2a9a82cdbfdaf955fec141bb9f) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china_hack02.bin", 0x000000, 0x04000, CRC(06214503) SHA1(ddede08011ab723a92a6da690e38903c173de2fa) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200-16_hack04.rom", 0x000000, 0x200000,  CRC(114cefcf) SHA1(e4e3d040e09d90df040ed5cba974c67c7935b892) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000002, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200_hack04.rom",    0x800000, 0x800002, CRC(05dcaf3d) SHA1(c4e26b353f0c9cafabf22296d631165593167965) )
ROM_END

ROM_START( kov2phack05 ) //kov2phsqj
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack05.rom", 0x100000, 0x400000, CRC(491cc37a) SHA1(df100de38f106d5d6060e0f8c1fa102511ea706f) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack06 ) //kov2pqjn
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack06.rom", 0x100000, 0x400000, CRC(e65bfd61) SHA1(96a5d9c38c5b3e89b7b2fa4f2fae950d25b74720) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack07 ) //kov2psblq
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack07.rom", 0x100000, 0x400000, CRC(e3edc8c9) SHA1(391a1db238d347b09dcde95ae8e41ac772ee9d6d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack08 ) //kov2ppws2016
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack08.rom", 0x100000, 0x400000, CRC(2c59cc1c) SHA1(8aa8e84c4b070ad826c68a07fa8ddf555c81ac14) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack09 ) //kov2pjlcq
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack09.rom", 0x100000, 0x400000, CRC(836075b8) SHA1(0ee2b6455b44a1b932e3eb0f9b97a0fd0b8409cb) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202_hack09.rom",    0x1000000, 0x0800000, CRC(24a4315f) SHA1(168bc3d7d834683edcfb968794c28e30d9b0ea16) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201_hack09.rom",   0x0800000, 0x0800000,  CRC(07347997) SHA1(444a753229f9356570583ee71e58665b2763f561) )

	ROM_REGION( 0x1000002, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200_hack09.rom",    0x800000, 0x800000, CRC(4bc06a41) SHA1(de8f799c8f281da9e89e592e833f529e47f2b63e) )
ROM_END

ROM_START( kov2phack10 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack10.rom", 0x100000, 0x400000, CRC(a7724151) SHA1(99a6aade4500b265eeb0979c003617a5da4cca41) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china_hack02.bin", 0x000000, 0x04000, CRC(06214503) SHA1(ddede08011ab723a92a6da690e38903c173de2fa) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200-16_hack10.rom", 0x000000, 0x200000,  CRC(ef2bd23b) SHA1(754926548d9112da77f9b6929ad2e52e6c7bc3e4) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack11 ) //kov2psblq
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack11.rom",    0x100000, 0x400000, CRC(d18d5ca3) SHA1(27a6b8282df12e3f529cebee8e6ebeb70ff450af) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack12 ) //kov2pgsyx
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack12.rom",    0x100000, 0x400000, CRC(9e10c844) SHA1(65a65039aed5d934fee38cb7840aab73bfe56a28) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack13 ) //kov2plffw
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack13.rom",    0x100000, 0x400000, CRC(2b238d52) SHA1(a450360377fa28519491feea05134d6ab9cbce92) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2phack14 ) //kov2pzsws
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v204-32m_hack14.rom",    0x100000, 0x400000, CRC(9afd444d) SHA1(6de5d2a302abfe625ae52f445d27ebe57e632234) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2p_igs027a_china.bin", 0x000000, 0x04000, CRC(19a0bd95) SHA1(83e9f22512832a51d41c588debe8be7adb3b1df7) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v200_16m.rom", 0x000000, 0x200000,  CRC(16a0c11f) SHA1(ce449cef76ebd5657d49b57951e2eb0f132e203e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

 /*******************
 Knights of Valour 2
**********************/

ROM_START( kov2hack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack01.106", 0x100000, 0x400000, CRC(a6328b82) SHA1(535b583552b7fbb2cdc7ff91fd7a7a69474c6ea5) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.102", 0x000000, 0x200000, CRC(462e2980) SHA1(3da7c3d2c65b59f50c78be1c25922b71d40f6080) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom", 0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",     0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204.rom",    0x2000000, 0x0200000, CRC(14b4b5bb) SHA1(d7db5740eec971f2782fb2885ee3af8f2a796550) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack02.106",    0x100000, 0x400000, CRC(c0d5f63e) SHA1(ed571a0401bac2fa812862df1d10ee98aa12825d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.100", 0x000000, 0x200000,   CRC(edd59922) SHA1(09b14f20f685944a93292c83e5830849aade42c9) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201_hack02.rom",    0x0800000, 0x0800000, CRC(82f0a878) SHA1(ddd13e404252a71de1b2b3b974b910f899f51c38) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack02.rom",    0x2000000, 0x0800000, CRC(3a26b7df) SHA1(d39e451f956e7555069d274eb72ca464770fcac3) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack03 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack03.106",      0x100000, 0x400000, CRC(c09b22eb) SHA1(6a170611de180b8e4a8ff420dfddd1858dc5d4b6) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.100", 0x000000, 0x200000,   CRC(edd59922) SHA1(09b14f20f685944a93292c83e5830849aade42c9) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201_hack02.rom",    0x0800000, 0x0800000, CRC(82f0a878) SHA1(ddd13e404252a71de1b2b3b974b910f899f51c38) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack02.rom",    0x2000000, 0x0800000, CRC(3a26b7df) SHA1(d39e451f956e7555069d274eb72ca464770fcac3) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack04 ) //kov2102
	ROM_REGION( 0xE00000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack04.106", 0x100000, 0x454F4A, CRC(c8f583bd) SHA1(1c3f44a65e9c379c9e9a1638841f583eebac28ae) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.102", 0x000000, 0x200000, CRC(462e2980) SHA1(3da7c3d2c65b59f50c78be1c25922b71d40f6080) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom", 0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201_hack02.rom",    0x0800000, 0x0800000, CRC(82f0a878) SHA1(ddd13e404252a71de1b2b3b974b910f899f51c38) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack04.rom",    0x2000000, 0x0800000, CRC(27527099) SHA1(e23cf366bdeaca1e009a5cec6b13164310a34384) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack05 ) //kov2103
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack05.106",    0x100000, 0x400000, CRC(bcc8e78d) SHA1(439fdd4208d15f49cb8113b369052dfd947808ca) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.101", 0x000000, 0x200000, CRC(8c35f2fe) SHA1(d4858f97fcfad0f342fccbc9cf1590276cc3c69c) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201_hack02.rom",    0x0800000, 0x0800000, CRC(82f0a878) SHA1(ddd13e404252a71de1b2b3b974b910f899f51c38) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack04.rom",    0x2000000, 0x0800000, CRC(27527099) SHA1(e23cf366bdeaca1e009a5cec6b13164310a34384) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack06 ) //kov2106v4
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack06.106",    0x100000, 0x400000, CRC(f6fd591c) SHA1(b6a2d7c5e016da7e9e051ccacc97a13a75b6d86e) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.102", 0x000000, 0x200000,   CRC(462e2980) SHA1(3da7c3d2c65b59f50c78be1c25922b71d40f6080) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201_hack02.rom",    0x0800000, 0x0800000, CRC(82f0a878) SHA1(ddd13e404252a71de1b2b3b974b910f899f51c38) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack04.rom",    0x2000000, 0x0800000, CRC(27527099) SHA1(e23cf366bdeaca1e009a5cec6b13164310a34384) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack07 ) //kov2101
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack07.106",    0x100000, 0x400000, CRC(f6d32462) SHA1(ca087983fb0ac13e87e113b29249b3c76193cc07) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.102", 0x000000, 0x200000,   CRC(462e2980) SHA1(3da7c3d2c65b59f50c78be1c25922b71d40f6080) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201.rom",    0x0800000, 0x0800000, CRC(21063ca7) SHA1(cf561b44902425a920d5cbea5bf65dd9530b2289) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack04.rom",    0x2000000, 0x0800000, CRC(27527099) SHA1(e23cf366bdeaca1e009a5cec6b13164310a34384) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack08 ) //kov2103
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack08.106",    0x100000, 0x400000, CRC(d58d0c0b) SHA1(35e73476d5b0db41a1f3ac9e178c03609454aa1c) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.102", 0x000000, 0x200000,   CRC(462e2980) SHA1(3da7c3d2c65b59f50c78be1c25922b71d40f6080) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201_hack02.rom",    0x0800000, 0x0800000, CRC(82f0a878) SHA1(ddd13e404252a71de1b2b3b974b910f899f51c38) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack04.rom",    0x2000000, 0x0800000, CRC(27527099) SHA1(e23cf366bdeaca1e009a5cec6b13164310a34384) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack09 ) //kov2106cb
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack09.106",    0x100000, 0x400000, CRC(4e99c6f6) SHA1(8233bd956f418f9bbbe401f8c8efabe884ab4876) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.102", 0x000000, 0x200000,   CRC(462e2980) SHA1(3da7c3d2c65b59f50c78be1c25922b71d40f6080) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201_hack02.rom",    0x0800000, 0x0800000, CRC(82f0a878) SHA1(ddd13e404252a71de1b2b3b974b910f899f51c38) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack04.rom",    0x2000000, 0x0800000, CRC(27527099) SHA1(e23cf366bdeaca1e009a5cec6b13164310a34384) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack10 ) //kov2106s
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack10.106",    0x100000, 0x400000, CRC(cd0bb205) SHA1(e9943d2e4a52aeeb67415cf211e241b59d6f3887) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.102", 0x000000, 0x200000,   CRC(462e2980) SHA1(3da7c3d2c65b59f50c78be1c25922b71d40f6080) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201_hack02.rom",    0x0800000, 0x0800000, CRC(82f0a878) SHA1(ddd13e404252a71de1b2b3b974b910f899f51c38) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack04.rom",    0x2000000, 0x0800000, CRC(27527099) SHA1(e23cf366bdeaca1e009a5cec6b13164310a34384) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

ROM_START( kov2hack11 ) //kov2100v3
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "u18_hack11.106",    0x100000, 0x400000, CRC(d97d26e2) SHA1(af67e794d5caa8581968ba50aca7532ac6809ae6) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov2_v100_hongkong.asic", 0x000000, 0x04000,  CRC(e0d7679f) SHA1(e1c2d127eba4ddbeb8ad173c55b90ac1467e1ca8) )

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "u19.100", 0x000000, 0x200000,   CRC(edd59922) SHA1(09b14f20f685944a93292c83e5830849aade42c9) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1200.rom",    0x180000, 0x800000, CRC(d7e26609) SHA1(bdad810f82fcf1d50a8791bdc495374ec5a309c6) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1200.rom",    0x0000000, 0x0800000, CRC(ceeb81d8) SHA1(5476729443fc1bc9593ae10fbf7cbc5d7290b017) )
	ROM_LOAD( "a1201_hack02.rom",    0x0800000, 0x0800000, CRC(82f0a878) SHA1(ddd13e404252a71de1b2b3b974b910f899f51c38) )
	ROM_LOAD( "a1202.rom",    0x1000000, 0x0800000, CRC(4bb92fae) SHA1(f0b6d72ed425de1c69dc8f8d5795ea760a4a59b0) )
	ROM_LOAD( "a1203.rom",    0x1800000, 0x0800000, CRC(e73cb627) SHA1(4c6e48b845a5d1e8f9899010fbf273d54c2b8899) )
	ROM_LOAD( "a1204_hack04.rom",    0x2000000, 0x0800000, CRC(27527099) SHA1(e23cf366bdeaca1e009a5cec6b13164310a34384) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1200.rom",   0x0000000, 0x0800000,  CRC(bed7d994) SHA1(019dfba8154256d64cd249eb0fa4c451edce34b8) )
	ROM_LOAD( "b1201.rom",   0x0800000, 0x0800000,  CRC(f251eb57) SHA1(56a5fc14ab7822f83379cecb26638e5bb266349a) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1200.rom",    0x800000, 0x800000, CRC(b0d88720) SHA1(44ab137e3f8e15b7cb5697ffbd9b1143d8210c4f) )
ROM_END

 /***********************
 Knights of Valour Plus
**************************/

ROM_START( kovplushack01 ) //kovpluslssx
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack01.119",    0x100000, 0x400000, CRC(e8cea34d) SHA1(a9f79f76af25b94dae9d19268734a27352c72849) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack01.rom",    0x180000, 0x800000, CRC(a51f6c60) SHA1(e2c184d6e4bb1e6fc02ee2e5953693c7461746be) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack02.119",    0x100000, 0x454FBE, CRC(b669683f) SHA1(9b88c8c0658dd2b23e3428969f45d306d4d5ea32) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack02.rom",    0x180000, 0x800000, CRC(806cfc9a) SHA1(d092de39ca8c625c752473461eaca877fce80e7a) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack03 ) //kovpluswwz
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack03.119",    0x100000, 0x454F54, CRC(146e77f1) SHA1(b1ffe66f495362521f0f595ce08d25caedc71fe6) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack04 ) //kovplusqyb
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack04.119",    0x100000, 0x400000, CRC(1531a478) SHA1(16fbe359bdd92d4ac3068844eca8c3f1c7e0fc1d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack05 ) //kovplus2015qx
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack05.119",    0x100000, 0x454F8A, CRC(ef0a7668) SHA1(783e017a0b054c23e6cdf86d9b50488071a542d0) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_ph171.rom",    0x180000, 0x800000, CRC(4fc07af6) SHA1(3f108d9b150ea9c6dc0685e926576724f8489d31) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack06 ) //kovpluswxnz
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack06.119",    0x100000, 0x454F5C, CRC(fe8a5ed0) SHA1(48611e4eb30f1cdece378693ca6003c8e925450b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack01.rom",    0x180000, 0x800000, CRC(a51f6c60) SHA1(e2c184d6e4bb1e6fc02ee2e5953693c7461746be) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack07 ) //kov2012ms
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack07.119",    0x100000, 0x400000, CRC(fec5eef0) SHA1(bbcd569d356e91d4d9e73f3d7a1689bc2887bd6c) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack08 ) //kovplusyzfm
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack08.119",    0x100000, 0x454F8A, CRC(a95e96ed) SHA1(11d7cdf3483608efe9200300eba07a357cc0ae01) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack01.rom",    0x180000, 0x800000, CRC(a51f6c60) SHA1(e2c184d6e4bb1e6fc02ee2e5953693c7461746be) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack09 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack09.119",    0x100000, 0x400000, CRC(f5ee44ad) SHA1(003efd6e0e9c29a861b6b6e359bd025c5747216c) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack10 ) //kovytqx2
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack10.119",    0x100000, 0x400000, CRC(661ba90d) SHA1(35cfcd8e3c4882dd341dda0c45946dea30fe3f7a) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack10.rom",  0x0000000, 0x0800000, CRC(cca70135) SHA1(2d288df75907e50c7fc2beca5fb9fd895faece55) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack10.rom",  0x0000000, 0x0800000, CRC(a4155c55) SHA1(3146774f00dd4156b7423d9983dc6e678aca648d) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack11 ) //kovplusxb1
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack11.119",    0x100000, 0x400000, CRC(9935b99c) SHA1(13b6b2477d3a157e719cb5d4065a8e6987688756) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack11.rom",    0x180000, 0x800000, CRC(c70efb8c) SHA1(0254abce39cd85e163b26078d512babc45522e39) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack11.rom",    0x400000, 0x400000, CRC(25f4f240) SHA1(63c52b55da5c0dc4c9cc7db587bdd3fbfb128745) )
ROM_END

ROM_START( kovplushack12 ) //kovplusxb2
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack12.119",    0x100000, 0x400000, CRC(c94d20b9) SHA1(54e4d9dbf1d20e146400e33cf2a925120dfaddd1) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack13 ) //kovplusxb2ds
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack13.119",    0x100000, 0x400000, CRC(dabc2c66) SHA1(7513f5eccc3d35b39172097f615f17b09844160b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack11.rom",    0x180000, 0x800000, CRC(c70efb8c) SHA1(0254abce39cd85e163b26078d512babc45522e39) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack11.rom",    0x400000, 0x400000, CRC(25f4f240) SHA1(63c52b55da5c0dc4c9cc7db587bdd3fbfb128745) )
ROM_END

ROM_START( kovplushack14 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack14.119",    0x100000, 0x400000, CRC(4a1cd890) SHA1(9ae3c21e1496e3ac52ebb68e7d0e959375a14108) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack14.rom",    0x180000, 0x800000, CRC(84567fa4) SHA1(932fdd8095b499acbac69035c12929a2dc9a5564) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack14.rom",    0x400000, 0x400000, CRC(01059d4f) SHA1(a18a960afd90e2574b31ef8b347ba1d38a12ef89) )
ROM_END

ROM_START( kovplushack15 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack15.119",    0x100000, 0x400000, CRC(33eebcf8) SHA1(ea11a22dacb85443a8fc0cd87d40fd86e18c39e1) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack16 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack16.119",    0x100000, 0x400000, CRC(7b919a5b) SHA1(372d0a78556249c41adc1327be8a61e029c0d33d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack16.rom",    0x180000, 0x800000, CRC(f1b5ad3b) SHA1(b70827e57852308107192f16590fe569460e6051) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack10.rom",  0x0000000, 0x0800000, CRC(cca70135) SHA1(2d288df75907e50c7fc2beca5fb9fd895faece55) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack16.rom",  0x1000000, 0x0800000, CRC(3ff98a24) SHA1(15062bb92ffcb5b9305e651e8b8ede48e159dbb7) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack16.rom",  0x0000000, 0x0800000, CRC(062b72ce) SHA1(757fe110a55f870c30a597ddb388ebb0f9ec73f4) )
	ROM_LOAD( "b0601_hack16.rom",  0x0800000, 0x0400000, CRC(e2b94fea) SHA1(d9dcb089fc68226b3e346b2b37ceb909ef459cf8) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack17 ) //kovplus2015ws
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack17.119",    0x100000, 0x400000, CRC(c7a96121) SHA1(42454054ab917357c734b5cdec66f468ef41366b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0x1400000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack17.rom",    0x180000, 0xF0CBF1, CRC(77798793) SHA1(365de45c9c81472b8b1948fc12869e89dc5feb73) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack17.rom",    0x0000000, 0x0800000, CRC(5bd7ea9f) SHA1(0eb33bd0e23441394ae7c6fa28aafe11adf0b22f) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack17.rom",    0x1000000, 0x0800000, CRC(b64e6473) SHA1(d231b85d1a3466565a90b2bb1489ef3038377fd2) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack17.rom",    0x0000000, 0x0800000, CRC(07d91ea3) SHA1(8713409439eb4a2875baffbda711587f283a652b) )
	ROM_LOAD( "b0601_hack17.rom",    0x0800000, 0x0400000, CRC(3737c3f7) SHA1(ed01d926ac080991fd5b98b04977dde84152f8e1) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack17.rom",    0x400000, 0x400000, CRC(730640d6) SHA1(d0d7e7c85fd47e4c1cebc7953269979922da869d) )
ROM_END

ROM_START( kovplushack18 ) //kovplusly1
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack18.119",    0x100000, 0x454FBE, CRC(ef89f5fc) SHA1(148b2eded3af19bded96e95049da161fe707e988) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(5bafcba9) SHA1(5a30db15bd2148710dc0b9d2e6022b81c8ca44c3) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack17.rom",    0x0000000, 0x0800000, CRC(5bd7ea9f) SHA1(0eb33bd0e23441394ae7c6fa28aafe11adf0b22f) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack17.rom",    0x1000000, 0x0800000, CRC(b64e6473) SHA1(d231b85d1a3466565a90b2bb1489ef3038377fd2) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack17.rom",    0x0800000, 0x0400000, CRC(3737c3f7) SHA1(ed01d926ac080991fd5b98b04977dde84152f8e1) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m01s_bios=bh01.rom", 0x000000, 0x200000, CRC(692511a5) SHA1(b272fdd0aa3724ba8ff30d2568c3a6b63f1358b3) )
	ROM_LOAD( "m0600_hack17.rom",    0x400000, 0x400000, CRC(730640d6) SHA1(d0d7e7c85fd47e4c1cebc7953269979922da869d) )
ROM_END

ROM_START( kovplushack19 ) //kovplusmycs
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack19.119",    0x100000, 0x454FBE, CRC(7dff5c82) SHA1(f4cf18c41c731b377c13cc4abc060a23b4eb0f24) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_ph147.rom",    0x180000, 0x800000, CRC(657bc51d) SHA1(ecc451788779000009ff15c4895d93408a51c3ce) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack19.rom",    0x0000000, 0x0800000, CRC(098cd614) SHA1(663e8ad60d1bdbdea22f8b186454649b4e432092) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack19.rom",    0x0000000, 0x0800000, CRC(b3691ed3) SHA1(3664fbd8bd775817a5f51326ecc05180c83c5e19) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack20 ) //kovplusqs1
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack20.119",    0x100000, 0x400000, CRC(d1ba41e3) SHA1(a586d873aa29fbc76c5eb2d1e82a422bdc7980b2) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0x1400000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_ph191.rom",    0x180000, 0xF0CBF1, CRC(a39397d4) SHA1(b8afc89fc85a3dd6bb36c1628d89594446f6ec90) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack20.rom",    0x1000000, 0x0800000, CRC(d9ea9298) SHA1(abaab6400613c1f2ff534fc0a9625e7dcf88a351) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack20.rom",    0x0800000, 0x0400000, CRC(b0809a1e) SHA1(3e9a20d38afea5eedbe0e7fd790c3223c88e20f8) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack21 ) //kovpluszsws2
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack21.119",    0x100000, 0x454F8A, CRC(3fa3ca71) SHA1(727d0e61911e124b767be7bb6c94f70e2762b87d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack21.rom",    0x180000, 0x800000, CRC(a2b8c8b1) SHA1(a000402ecbe90d05f7dd3f933a31233ef482d09a) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack21.rom",    0x0000000, 0x0800000, CRC(24091941) SHA1(7fc28b716aa115815470add57f07d99c21e53f38) )
	ROM_LOAD( "a0601_hack21.rom",    0x0800000, 0x0800000, CRC(5f01af74) SHA1(a150902df6427463da17016d8263ee5e6ee52ae3) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack27.rom",    0x0000000, 0x0800000, CRC(1ce751b1) SHA1(6bb9297eb66d88ba4c6202bdc3b4142df51b13bd) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack22 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack22.119",    0x100000, 0x454fd6, CRC(2602c386) SHA1(24e6fdcb262c6f18c7e0e87a49f072fb5dbe13bd) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_ph205.rom",    0x180000, 0x800000, CRC(ff6b643b) SHA1(b6b75c0988165297cbbfe974c9f5a5c7c4d4c46f) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack22.rom",    0x1000000, 0x0800000, CRC(6fe3c258) SHA1(f8fcacd5ba2d13b32e867c8ef1cd2efb72a90208) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack22.rom",    0x0800000, 0x0454F4A, CRC(6044aadf) SHA1(239216d512f0909d2a1bab546389d64ddc1df001) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack23 ) //kovplusszfx2
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack23.119",    0x100000, 0x400000, CRC(0d296572) SHA1(f4b1676ebde8367b34237a04944ea69a91194eaf) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack24 ) //kovpluslttx
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack24.119",    0x100000, 0x400000, CRC(24306dff) SHA1(24729b7dde1ba18947625585584ff1ebd3e25c5d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack01.rom",    0x180000, 0x800000, CRC(a51f6c60) SHA1(e2c184d6e4bb1e6fc02ee2e5953693c7461746be) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack25 ) //kovzlzq
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack25.119",    0x100000, 0x400000, CRC(7e35a304) SHA1(3c957d9046ea0b3179f04f98d141618150a67fbd) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_ph77.rom",    0x180000, 0x800000, CRC(e7d4d577) SHA1(900796b2c88ac8d9e454380d17c811d37243452d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603_hack25.rom",    0x1800000, 0x0400000, CRC(59fadc06) SHA1(0c05749b4eb0bbc736904a060f3963047a3efb51) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack25.rom",    0x0800000, 0x0400000, CRC(b55f2ba8) SHA1(93be439535ff3adef3f7230b8c6ac71bdc57ef1a) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack25.rom",    0x400000, 0x400000, CRC(f38b622c) SHA1(0c2689b925fb26f341e0446fa6181a5b5cc93a54) )
ROM_END

ROM_START( kovplushack26 ) //kovplusem17
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack26.119",    0x100000, 0x400000, CRC(b7c20bac) SHA1(4f8214d085fc3fe1908c155df2c22298e850d52b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack14.rom",    0x180000, 0x800000, CRC(84567fa4) SHA1(932fdd8095b499acbac69035c12929a2dc9a5564) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack17.rom",    0x0000000, 0x0800000, CRC(5bd7ea9f) SHA1(0eb33bd0e23441394ae7c6fa28aafe11adf0b22f) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack17.rom",    0x0000000, 0x0800000, CRC(07d91ea3) SHA1(8713409439eb4a2875baffbda711587f283a652b) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack14.rom",    0x400000, 0x400000, CRC(01059d4f) SHA1(a18a960afd90e2574b31ef8b347ba1d38a12ef89) )
ROM_END

ROM_START( kovplushack27 ) //kovpluszsws
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack27.119",    0x100000, 0x400000, CRC(ca74bb81) SHA1(0f25bcf1706f3638216dd1185c6519b7a701d9a3) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack21.rom",    0x0000000, 0x0800000, CRC(24091941) SHA1(7fc28b716aa115815470add57f07d99c21e53f38) )
	ROM_LOAD( "a0601_hack27.rom",    0x0800000, 0x0800000, CRC(8998680f) SHA1(654769ca07780b9a3409a8191c1b43b0587bc692) )
	ROM_LOAD( "a0602_hack27.rom",    0x1000000, 0x0800000, CRC(27a93ff6) SHA1(749b1d9afe4847c5e781d04634c004a6111856cb) )
	ROM_LOAD( "a0603_hack27.rom",    0x1800000, 0x0400000, CRC(5e00a709) SHA1(310bfb0c5651fead86a17c1ffb570cd10d912fe6) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack27.rom",    0x0000000, 0x0800000, CRC(1ce751b1) SHA1(6bb9297eb66d88ba4c6202bdc3b4142df51b13bd) )
	ROM_LOAD( "b0601_hack27.rom",    0x0800000, 0x0400000, CRC(912acd06) SHA1(88f767752a69cc307ef22fd583dc672f961d9add) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack28 ) //kovplusbs
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack28.119",    0x100000, 0x400000, CRC(38406afc) SHA1(50271cc81f454628f01b83370cfe90695001aef2) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack01.rom",    0x180000, 0x800000, CRC(a51f6c60) SHA1(e2c184d6e4bb1e6fc02ee2e5953693c7461746be) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack28.rom",    0x0000000, 0x0800000, CRC(19822acf) SHA1(a1ab9119e4c0b914d977218304be2056cb6cd4e3) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack28.rom",    0x0000000, 0x0800000, CRC(a7e1f6fd) SHA1(795ca04655ecc9ed9ce91dc53434338d35f70fbe) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800001, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack28.rom",    0x400000, 0x400001, CRC(623b03cb) SHA1(671306d7463919e479e1e33dd960ad475be48eac) )
ROM_END

ROM_START( kovplushack29 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack29.119",    0x100000, 0x400000, CRC(c956d923) SHA1(829cf86a78882da0e93c4acd5bf123becf3dfd5c) )
	ROM_IGNORE( 0x54F8A )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack29.rom",    0x180000, 0x800000, CRC(14a294bc) SHA1(e1cb412612e98e143495f60208c6425224c2a183) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack29.rom",    0x0000000, 0x0800000, CRC(3a73f446) SHA1(102ac046ea44e704195105081d40125a54c42d69) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack29.rom",    0x0000000, 0x0800000, CRC(0b0ab3dc) SHA1(05e666b6c0dddafd531e7472db053b21ecc35ba8) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack30 ) //kovplusblcx
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack30.119",    0x100000, 0x400000, CRC(8b1b0a1a) SHA1(3fb6c25b3f1d9a05a88b6b8e30c8c8a6076fb6c4) )
	ROM_IGNORE( 0x54F8A )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack29.rom",    0x180000, 0x800000, CRC(14a294bc) SHA1(e1cb412612e98e143495f60208c6425224c2a183) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack29.rom",    0x0000000, 0x0800000, CRC(3a73f446) SHA1(102ac046ea44e704195105081d40125a54c42d69) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack29.rom",    0x0000000, 0x0800000, CRC(0b0ab3dc) SHA1(05e666b6c0dddafd531e7472db053b21ecc35ba8) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack31 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack31.119",    0x100000, 0x400000, CRC(933db110) SHA1(e083258c54b9a1d8760aecab4c9b1f7770997471) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack31.rom",    0x180000, 0x800000, CRC(86ae33c4) SHA1(1f47c99d3686dae9047908cee6df3b64fa1e088f) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack31.rom",    0x0000000, 0x0800000, CRC(d44d710e) SHA1(2a0e07b1c60b325e0ddd1c5ab85ef7c51a66d251) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack31.rom",    0x0000000, 0x0800000, CRC(37967518) SHA1(7be83d82d1fb9073ef4506df2fbfa5fa077f77ce) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack32 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack32.119",    0x100000, 0x400000, CRC(d1323d1f) SHA1(b9f2e9eb7308e92f3bac54a6ef3fd76b749559cf) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack32.rom",    0x180000, 0x800000, CRC(eeca2b53) SHA1(bd478a5ad5b9e3cc3880e2cff24097d7798c59c7) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack20.rom",    0x0800000, 0x0400000, CRC(b0809a1e) SHA1(3e9a20d38afea5eedbe0e7fd790c3223c88e20f8) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack33 ) //kovsgyyv
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack33.119",    0x100000, 0x400000, CRC(d38c3a91) SHA1(0dec8e95cec5492a254c57087ff6cd2b0dabc606) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_ph307.rom",    0x180000, 0x800000, CRC(baf28e34) SHA1(7cd02ade5200e7e85e6282a6caadfa2cd7082aaa) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack33.rom",    0x1000000, 0x0800000, CRC(4c59e36c) SHA1(f5ec1a375fcfde2d9b1c0dbf3784bfbfaf67f8f6) )
	ROM_LOAD( "a0603_hack33.rom",    0x1800000, 0x0400000, CRC(1e88f9b5) SHA1(091c63e333c218c58b45c955f0c145eb8e911d0b) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack33.rom",    0x0800000, 0x0400000, CRC(1f36d3d0) SHA1(04051be25a498ef521f284193134f57166602619) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack34 ) //kovpluszsws4
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack34.119",    0x100000, 0x400000, CRC(9ef0c625) SHA1(3a08ccf455f8da9a27dc49ee7cf5588e2f72067c) )
	ROM_IGNORE( 0x054F8A )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack34.rom",    0x180000, 0x800000, CRC(e451df7f) SHA1(123c7d9e9a3efdbd192e9da61ea64801744fc090) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack34.rom",    0x0000000, 0x0800000, CRC(e0a73add) SHA1(054f01cd06d743635305a7a9f4a9bcd3a3dc8d71) )
	ROM_LOAD( "a0601_hack34.rom",    0x0800000, 0x0800000, CRC(551e3563) SHA1(377951b13508103796baeb4097670aff187d1696) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack34.rom",    0x0000000, 0x0800000, CRC(6c14d658) SHA1(f7f70085d7cf0f67549143b2c77b4d12ebe7786b) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack35 ) //kovytqx
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack35.119",    0x100000, 0x400000, CRC(2cae0283) SHA1(925715c4aaaebaaa4f827f2f8d6cf207075e776b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack36 ) //kovplusxt
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack36.119",    0x100000, 0x400000, CRC(14f0b6fc) SHA1(aebec8f8a006cb502647eecc399114d214d096e7) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack34.rom",    0x180000, 0x800000, CRC(e451df7f) SHA1(123c7d9e9a3efdbd192e9da61ea64801744fc090) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack36.rom",    0x0000000, 0x0800000, CRC(783df23c) SHA1(5458a1b84d0d52ef0490bec0b1fe5b503b7965fc) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack36.rom",  0x1000000, 0x0800000, CRC(71c8a46c) SHA1(6391eb95e1f2933b0e02518232a4bbcf7c91b73f) )
	ROM_LOAD( "a0603_hack36.rom",  0x1800000, 0x0400000, CRC(4d755da5) SHA1(8b04020578e96030b86359a9f0ba892adb703bf5) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack36.rom",    0x0000000, 0x0800000, CRC(e3bf000f) SHA1(154753a31913b931878ea3aafbb677f7d6174a54) )
	ROM_LOAD( "b0601_hack36.rom",    0x0800000, 0x0400000, CRC(47a9af9c) SHA1(87596e64c2f6c4ed039928d2d69a04e669aeb930) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack36.rom",    0x400000, 0x400000, CRC(d84343ec) SHA1(c621a25a497cd58ec9af7374c5bd733d3d940937) )
ROM_END

ROM_START( kovplushack37 ) //kovplusdjjz
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack37.119",    0x100000, 0x400000, CRC(6be54539) SHA1(4ac994b877f62abb987340531089fd862b2f3bab) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack37.rom",    0x180000, 0x800000, CRC(169b4e8b) SHA1(dec35a62db009075fa4fc4181730985366b0df65) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack37.rom",    0x0000000, 0x0800000, CRC(4f287f85) SHA1(7ea2b432bc8f76a365086813ef09a9b4eb716c31) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack37.rom",  0x1000000, 0x0800000, CRC(11ecd0bf) SHA1(78ff855a9dfd67f2f2442625bfd81846b2ea09da) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack37.rom",    0x0000000, 0x0800000, CRC(9783ed2c) SHA1(b58f0536e4b406333eeca4767a9e5b1cba87021a) )
	ROM_LOAD( "b0601_hack37.rom",    0x0800000, 0x0400000, CRC(50d9c24c) SHA1(0fb32a8c1e36cd29f305896fd0a13396aff632c3) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack37.rom",    0x400000, 0x400000, CRC(b61b8214) SHA1(2dfcdc203d9c75df6a699cb7b9e119e1ea9d743a) )
ROM_END

ROM_START( kovplushack38 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack38.119",    0x100000, 0x400000, CRC(48751546) SHA1(1f310dee5c9cd03921e9b330c4ae5433d99b827b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack01.rom",    0x180000, 0x800000, CRC(a51f6c60) SHA1(e2c184d6e4bb1e6fc02ee2e5953693c7461746be) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack21.rom",    0x0000000, 0x0800000, CRC(24091941) SHA1(7fc28b716aa115815470add57f07d99c21e53f38) )
	ROM_LOAD( "a0601_hack21.rom",    0x0800000, 0x0800000, CRC(5f01af74) SHA1(a150902df6427463da17016d8263ee5e6ee52ae3) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack27.rom",    0x0000000, 0x0800000, CRC(1ce751b1) SHA1(6bb9297eb66d88ba4c6202bdc3b4142df51b13bd) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack39 ) //kovplus1v4
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack39.119",    0x100000, 0x400000, CRC(2a74a11d) SHA1(3c933f2b9a6665548d5d7d3969189b0d6e103a20) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack40 ) //kovplus2012mp
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack40.119",    0x100000, 0x400000, CRC(2d80798e) SHA1(7b809b1a85abe8388ac3bf0dd0289ce7ce06450f) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack40.rom",    0x180000, 0x800000, CRC(f7b6f432) SHA1(1c450f5eac830a41248c93b3e3f67abc217e18c3) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack40.rom",    0x0000000, 0x0800000, CRC(b2a208a1) SHA1(3c4191336aa760e6077eee9983c809dfbe3eb57a) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack40.rom",    0x0000000, 0x0800000, CRC(e0a70b54) SHA1(ad94e39fb418770af677083406c3db7a0279c865) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack40.rom",    0x400000, 0x454F47, CRC(132765c9) SHA1(b4f56dfeba59fea248ec4e04255033e2cb3ec8fb) )
ROM_END

ROM_START( kovplushack41 ) //kovplus2012sttw
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack41.119",    0x100000, 0x400000, CRC(8739afd3) SHA1(e28e649313b6a36b3d02c4c7e698f9a541140a61) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t01s_bios=bh01.rom",  0x000000, 0x200000, CRC(1a7123a0) SHA1(cc567f577bfbf45427b54d6695b11b74f2578af3) ) //BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack21.rom",    0x0000000, 0x0800000, CRC(24091941) SHA1(7fc28b716aa115815470add57f07d99c21e53f38) )
	ROM_LOAD( "a0601_hack27.rom",    0x0800000, 0x0800000, CRC(8998680f) SHA1(654769ca07780b9a3409a8191c1b43b0587bc692) )
	ROM_LOAD( "a0602_hack27.rom",    0x1000000, 0x0800000, CRC(27a93ff6) SHA1(749b1d9afe4847c5e781d04634c004a6111856cb) )
	ROM_LOAD( "a0603_hack27.rom",    0x1800000, 0x0400000, CRC(5e00a709) SHA1(310bfb0c5651fead86a17c1ffb570cd10d912fe6) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack27.rom",    0x0000000, 0x0800000, CRC(1ce751b1) SHA1(6bb9297eb66d88ba4c6202bdc3b4142df51b13bd) )
	ROM_LOAD( "b0601_hack27.rom",    0x0800000, 0x0400000, CRC(912acd06) SHA1(88f767752a69cc307ef22fd583dc672f961d9add) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack42 ) //kovplus2020ws
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack42.119",    0x100000, 0x200000, CRC(e31dd5cf) SHA1(e5499ac3876a13f95a563a491495eb478b3fd811) )
	ROM_LOAD16_WORD_SWAP( "p0600_hack42.118",    0x300000, 0x200000, CRC(3a832370) SHA1(bd43eae1589d0f121239f0f13eac3e0fd6506a31) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack43 ) //kovplusms
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack43.119",    0x100000, 0x200000, CRC(70c50121) SHA1(621e48ebaed454f0d7daadeb0a7e7a689c70708e) )
	ROM_LOAD16_WORD_SWAP( "p0600_hack43.118",    0x300000, 0x200000, CRC(8e49a7f2) SHA1(4a76e7187702048a00fda54e3c91e58dd020bd47) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack44 ) //kov8
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack44.119",    0x100000, 0x400000, CRC(f680fc22) SHA1(1a521a9c7491f1ab30a8795dc9a3002137c4fd39) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack45 ) //kovzscs2019
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack45.119",    0x100000, 0x200000, CRC(4fd175cc) SHA1(09acb29cb2a51e2dd2c5d7d3dbdf84b2c68f60b3) )
	ROM_LOAD16_WORD_SWAP( "p0601_hack45.118",    0x300000, 0x200000, CRC(33f00bf8) SHA1(cb7f3c3a6084adc247c9c01aec0a1d75148fc780) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack01.rom",    0x180000, 0x800000, CRC(a51f6c60) SHA1(e2c184d6e4bb1e6fc02ee2e5953693c7461746be) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack45.rom",    0x0000000, 0x1C00000, CRC(3455081f) SHA1(7f3085f5f5e1042d6e494a24daa5a058244d0476) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack45.rom",    0x0000000, 0x0C00000, CRC(216a2ff1) SHA1(63f7c08f2566c64b9d8e5076831c19af9a74f52e) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack46 ) //kovemzs2019
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack46.119",    0x100000, 0x200000, CRC(89b79e94) SHA1(220ed08ec4b580275410cc6239dc75d94bd2811d) )
	ROM_LOAD16_WORD_SWAP( "p0601_hack46.118",    0x300000, 0x200000, CRC(9697e436) SHA1(9b53cfb3e0ef86d3b36f9538bf3bc49c42703ef7) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack01.rom",    0x180000, 0x800000, CRC(a51f6c60) SHA1(e2c184d6e4bb1e6fc02ee2e5953693c7461746be) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack46.rom",    0x0000000, 0x1C00000, CRC(96dd05b7) SHA1(9224bcfa2c1c0517f0e7654dd4a777b543362884) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack46.rom",    0x0000000, 0xC00000, CRC(75ef71a8) SHA1(1dc6486ccb8ddf3890c534905953a716d7100c58) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack47 ) //kovplus2012st
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack47.119",    0x100000, 0x400000, CRC(8895f498) SHA1(8e0b4781ca79637ef2f60894f90ca39364d40bb0) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack21.rom",    0x0000000, 0x0800000, CRC(24091941) SHA1(7fc28b716aa115815470add57f07d99c21e53f38) )
	ROM_LOAD( "a0601_hack27.rom",    0x0800000, 0x0800000, CRC(8998680f) SHA1(654769ca07780b9a3409a8191c1b43b0587bc692) )
	ROM_LOAD( "a0602_hack27.rom",    0x1000000, 0x0800000, CRC(27a93ff6) SHA1(749b1d9afe4847c5e781d04634c004a6111856cb) )
	ROM_LOAD( "a0603_hack27.rom",    0x1800000, 0x0400000, CRC(5e00a709) SHA1(310bfb0c5651fead86a17c1ffb570cd10d912fe6) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack27.rom",    0x0000000, 0x0800000, CRC(1ce751b1) SHA1(6bb9297eb66d88ba4c6202bdc3b4142df51b13bd) )
	ROM_LOAD( "b0601_hack27.rom",    0x0800000, 0x0400000, CRC(912acd06) SHA1(88f767752a69cc307ef22fd583dc672f961d9add) )
	ROM_LOAD( "b0602_hack47.rom",    0x0C00000, 0x0800000, CRC(2407290e) SHA1(cf5ae033eaafb79b96d509782635371060754a10) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack48 ) //kovsgyyv
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack48.119",    0x100000, 0x400000, CRC(b90acf78) SHA1(4cdf8e585faf96b49434410b1d25911670cd9533) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack48.rom",    0x180000, 0x800000, CRC(954551ff) SHA1(97d1fc65334c9aec093275a45fedb8dcb8a3cc34) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack48.rom",    0x1000000, 0x0800000, CRC(0d2b7d23) SHA1(22c84c48bedb0d109179c1347b1dcbece02f8f88) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack48.rom",    0x0800000, 0x0400000, CRC(05f4c1da) SHA1(30b0543beac5a200e05aa71cf16743561e0b7dc0) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovplushack49 ) //kovplus2012dw
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack49.119",    0x100000, 0x400000, CRC(90455769) SHA1(560f1004c68fd4202a8085e169534fde1180095a) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack49.rom",    0x180000, 0x800000, CRC(842b7711) SHA1(b999d55e6e304b4057c66d57bf970f7b181ddac8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack17.rom",    0x0000000, 0x0800000, CRC(5bd7ea9f) SHA1(0eb33bd0e23441394ae7c6fa28aafe11adf0b22f) )
	ROM_LOAD( "a0601_hack34.rom",    0x0800000, 0x0800000, CRC(551e3563) SHA1(377951b13508103796baeb4097670aff187d1696) )
	ROM_LOAD( "a0602_hack49.rom",    0x1000000, 0x0800000, CRC(f68a56b7) SHA1(fb5a77476cb5a30533a528ddc454517cc6428043) )
	ROM_LOAD( "a0603_hack49.rom",    0x1800000, 0x0400000, CRC(4fcbb71b) SHA1(25c563256456f36d8c431904fee83452ecfaaa2d) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack17.rom",    0x0000000, 0x0800000, CRC(07d91ea3) SHA1(8713409439eb4a2875baffbda711587f283a652b) )
	ROM_LOAD( "b0601_hack49.rom",    0x0800000, 0x0400000, CRC(a8fc03a0) SHA1(1e48d52b30463c142221683e1ffa7523fb70a10b) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m01s_bios=bh01.rom", 0x000000, 0x200000, CRC(692511a5) SHA1(b272fdd0aa3724ba8ff30d2568c3a6b63f1358b3) )
	ROM_LOAD( "m0600_hack49.rom",    0x400000, 0x400000, CRC(acadac0d) SHA1(f6b195b7cd33a197d377c750a1f9f5bee2900779) )
ROM_END

ROM_START( kovplushack50 ) //kovplus2020tx
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack50.119",    0x100000, 0x400000, CRC(1564ca87) SHA1(1e0c88b6ee1dbea9bc0cc2625a395731ba204469) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack34.rom",    0x180000, 0x800000, CRC(e451df7f) SHA1(123c7d9e9a3efdbd192e9da61ea64801744fc090) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack36.rom",    0x0000000, 0x0800000, CRC(783df23c) SHA1(5458a1b84d0d52ef0490bec0b1fe5b503b7965fc) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack50.rom", 0x1000000, 0x0800000, CRC(58615616) SHA1(3d088bc88e0905e4a4a74d2feb839bc1db0fdbdd) )
	ROM_LOAD( "a0603_hack36.rom", 0x1800000, 0x0400000, CRC(4d755da5) SHA1(8b04020578e96030b86359a9f0ba892adb703bf5) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack36.rom",    0x0000000, 0x0800000, CRC(e3bf000f) SHA1(154753a31913b931878ea3aafbb677f7d6174a54) )
	ROM_LOAD( "b0601_hack50.rom",    0x0800000, 0x0400000, CRC(c91abed0) SHA1(d91b9bcacf1806967984f0b6f0249e4196d6d6d9) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack36.rom",    0x400000, 0x400000, CRC(d84343ec) SHA1(c621a25a497cd58ec9af7374c5bd733d3d940937) )
ROM_END

 /******************************
 Knights of Valour Super Heroes
*********************************/

ROM_START( kovshhack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack01.322",    0x100000, 0x400000, CRC(15ff59de) SHA1(1583053c16c9837079f5571f114ddf6ebf4bc234) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000,  CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack01.rom",    0x180000, 0x800000, CRC(28dd8d3a) SHA1(b872e026d9f0df87365e9ced275dd4683c280b11) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack02 ) //kovshlsqy2
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack02.322",    0x100000, 0x400000, CRC(adac24c7) SHA1(386bcc440cd4595e661479faf743795722f422a4) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack02.asic", 0x000000, 0x04000,  CRC(0f97efea) SHA1(af4b7222dbd774af759cf59f3277d6a784110afe) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack02.rom",    0x180000, 0x800000, CRC(809b5eaa) SHA1(b492781c7a13b39cccfa4f28a9660c8577360fbc) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack02.rom",    0x1000000, 0x0800000, CRC(ab94d8a0) SHA1(f54843fc3ec6f2e0d56da5f8e2a55880bf603109) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack02.rom",    0x1a00000, 0x0400000, CRC(8e3c32bc) SHA1(296376cefcf2d04e8c62a9131ca141162fafa3b0) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack02.rom",    0x0800000, 0x0400000, CRC(1e917e36) SHA1(480c691c0c3df7225145e163848c46404306fcb4) )
	ROM_LOAD( "b0602_hack02.rom",    0x0c00000, 0x0400000, CRC(caec6b2c) SHA1(c27805d016c8ba7c35ffa01a3ccc4fa8ae900ead) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack03 ) //kovshlsqy
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack03.322",    0x100000, 0x400000, CRC(e1e08bec) SHA1(a432c1b2518977f6da1cc49c0a67c45298e9f04b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack03.asic", 0x000000, 0x04000,  CRC(d79943df) SHA1(d3c32b30aed245fec3ce18e7cd0fcab1de06d74d) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack02.rom",    0x180000, 0x800000, CRC(809b5eaa) SHA1(b492781c7a13b39cccfa4f28a9660c8577360fbc) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack03.rom",    0x0000000, 0x0800000, CRC(b41159b2) SHA1(3f563fda2984aa9db14203fd8ba482db1a8ad0af) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack02.rom",    0x1000000, 0x0800000, CRC(ab94d8a0) SHA1(f54843fc3ec6f2e0d56da5f8e2a55880bf603109) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack02.rom",    0x1a00000, 0x0400000, CRC(8e3c32bc) SHA1(296376cefcf2d04e8c62a9131ca141162fafa3b0) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack03.rom",    0x0000000, 0x0800000, CRC(895a1902) SHA1(d84fd403fdc8f4d707135fdecfe05eca950bb67b) )
	ROM_LOAD( "b0601_hack02.rom",    0x0800000, 0x0400000, CRC(1e917e36) SHA1(480c691c0c3df7225145e163848c46404306fcb4) )
	ROM_LOAD( "b0602_hack02.rom",    0x0c00000, 0x0400000, CRC(caec6b2c) SHA1(c27805d016c8ba7c35ffa01a3ccc4fa8ae900ead) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack04 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack04.322",    0x100000, 0x400000, CRC(53455237) SHA1(1a57ee6e6a4c1ab6bc095e4a4f53606e12fd8ab6) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack04.asic", 0x000000, 0x04000,  CRC(9d8ecc0c) SHA1(51f288e8aa3dd1d4b7f24155fea9c6a7f4cd1144) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack04.rom",    0x1000000, 0x0800000, CRC(a2534511) SHA1(06ade64cc805d81ca4ff66d4e57cce426fea4030) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack04.rom",    0x0800000, 0x0400000, CRC(44aad7c8) SHA1(7c17dfe2c9e09c3949cfe87351c7efd2140b58ca) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack05 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack05.322",    0x100000, 0x400000, CRC(581d32a8) SHA1(d51c8af315553f5f1ac26b28e583853372302f4c) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack04.asic", 0x000000, 0x04000,  CRC(9d8ecc0c) SHA1(51f288e8aa3dd1d4b7f24155fea9c6a7f4cd1144) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600lb.rom",    0x180000, 0x800000, CRC(9920e650) SHA1(1d46233869d4e65fd8b84ec520fc7e7e3840c7aa) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack03.rom",    0x0000000, 0x0800000, CRC(b41159b2) SHA1(3f563fda2984aa9db14203fd8ba482db1a8ad0af) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack05.rom",    0x1a00000, 0x0400000, CRC(93798795) SHA1(a178c6554c5034a670e882390587a101d4289872) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack03.rom",    0x0000000, 0x0800000, CRC(895a1902) SHA1(d84fd403fdc8f4d707135fdecfe05eca950bb67b) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602_hack05.rom",    0x0c00000, 0x0100000, CRC(0f39414a) SHA1(0e8daa5c73f86e26da7c702b35d20112ebe91cf0) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack06 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack06.322",    0x100000, 0x400000, CRC(1082bacc) SHA1(ecfa43a17cec7ccf2b4c21e8eb149db2ef83c86b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000,  CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack07 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack07.322",    0x100000, 0x400000, CRC(2a6b4287) SHA1(34da0dd9e8d8fe80211f61ef4e7fe3b30e9fc5a6) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack07.asic", 0x000000, 0x04000,  CRC(32b780dd) SHA1(423f51dd4470fb521dbb8702640dcbde2c559454) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack07.rom",    0x1a00000, 0x0400000, CRC(410f3a5e) SHA1(93e854d128bd354f50021a60fbf5f5a38fe8c481) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack07.rom",    0x0800000, 0x0400000, CRC(88f01bfb) SHA1(df14e280eb5b22c1bcedc16112ead97a3c344ab1) )
	ROM_LOAD( "b0602_hack07.rom",    0x0c00000, 0x0100000, CRC(a81a7b61) SHA1(290764a49703db8ab7b682084bc12619f4c29796) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack08 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack08.322",    0x100000, 0x400000, CRC(724cbc3e) SHA1(2de57fb14c2b0c5bd9071324665ea7e0f4caa7f2) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack08.322", 0x000000, 0x04000,  CRC(a09af141) SHA1(fa7430874cb2f18437ea1192445fcd85fb2b3211) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack08.rom",    0x180000, 0x800000, CRC(12097ed8) SHA1(b154e025c77f54109c442822158fdf5cc0320e11) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack03.rom",    0x0000000, 0x0800000, CRC(b41159b2) SHA1(3f563fda2984aa9db14203fd8ba482db1a8ad0af) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack08.rom",    0x1000000, 0x0800000, CRC(f86395c0) SHA1(86db74a862ea316cb7ac30ed0ddd90181809f6f4) )
	ROM_LOAD( "a0603_hack08.rom",    0x1800000, 0x0400000, CRC(fc061deb) SHA1(2f6906117c63dd6ee13c5aad70d8b9e7541c23cc) )
	ROM_LOAD( "a0604_hack08.rom",    0x1a00000, 0x0400000, CRC(87ff1a5e) SHA1(02a6f4d6976f0b3ca3fe993725e4419231697f07) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack03.rom",    0x0000000, 0x0800000, CRC(895a1902) SHA1(d84fd403fdc8f4d707135fdecfe05eca950bb67b) )
	ROM_LOAD( "b0601_hack08.rom",    0x0800000, 0x0400000, CRC(388ab398) SHA1(bff124d2ed3b74cb460433dea1317b88d3b4d22d) )
	ROM_LOAD( "b0602_hack08.rom",    0x0c00000, 0x0100000, CRC(3346e6c7) SHA1(e0a59a81918118f8da5ad382a6f0071d5309f3dc) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack08.rom",    0x400000, 0x400000, CRC(baf0b56e) SHA1(ed6f30a7f62aee1f263efc12ffd3f908191cd171) )
ROM_END

ROM_START( kovshhack09 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack09.322",    0x100000, 0x400000, CRC(d088bf6e) SHA1(806c1713f80f83529e6a344d46be52caeda0696f) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack03.asic", 0x000000, 0x04000,  CRC(d79943df) SHA1(d3c32b30aed245fec3ce18e7cd0fcab1de06d74d) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack08.rom",    0x180000, 0x800000, CRC(12097ed8) SHA1(b154e025c77f54109c442822158fdf5cc0320e11) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack02.rom",    0x1000000, 0x0800000, CRC(ab94d8a0) SHA1(f54843fc3ec6f2e0d56da5f8e2a55880bf603109) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack02.rom",    0x1a00000, 0x0400000, CRC(8e3c32bc) SHA1(296376cefcf2d04e8c62a9131ca141162fafa3b0) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack02.rom",    0x0800000, 0x0400000, CRC(1e917e36) SHA1(480c691c0c3df7225145e163848c46404306fcb4) )
	ROM_LOAD( "b0602_hack09.rom",    0x0c00000, 0x0100000, CRC(aa64ac60) SHA1(e9291715e691c09dfc2889e1c2f6e423aa3f1409) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack10 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack10.322",    0x100000, 0x400000, CRC(428d65c8) SHA1(b6194de62e9a0e0acd0559ff2d6316ad504ac2a0) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack10.asic", 0x000000, 0x04000,  CRC(367875c5) SHA1(f8bb234cc4e0561635b927240f375b17ee201e1d) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(d049c5bf) SHA1(8f75b6f3171d5dda9010be325a4c8f880b8fc645) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack03.rom",    0x0000000, 0x0800000, CRC(b41159b2) SHA1(3f563fda2984aa9db14203fd8ba482db1a8ad0af) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack05.rom",    0x1a00000, 0x0400000, CRC(93798795) SHA1(a178c6554c5034a670e882390587a101d4289872) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack03.rom",    0x0000000, 0x0800000, CRC(895a1902) SHA1(d84fd403fdc8f4d707135fdecfe05eca950bb67b) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602_hack05.rom",    0x0c00000, 0x0100000, CRC(0f39414a) SHA1(0e8daa5c73f86e26da7c702b35d20112ebe91cf0) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack11 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack11.322",    0x100000, 0x400000, CRC(114f3284) SHA1(e3e8006c3c728cb7634abe24d9da67dd974d4612) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack11.asic", 0x000000, 0x04000,  CRC(Cb86ca41) SHA1(A60cf5101b7a3161e550d3d6005813b04a9e2904) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(d049c5bf) SHA1(8f75b6f3171d5dda9010be325a4c8f880b8fc645) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m01s_bios=bh04.rom", 0x000000, 0x200000, CRC(a490380c) SHA1(f3ef016d984251740f867e22934b5d81eb7ec744) )
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack12 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack12.322",    0x100000, 0x400000, CRC(6727489b) SHA1(713173002315f368b6dbef1022cb51d9595d5736) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000,  CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack12.rom",    0x0000000, 0x0800000, CRC(b364f569) SHA1(6b552283885e19f097a35ac62381f30119ca715c) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack12.rom",    0x0000000, 0x0800000, CRC(df975d7c) SHA1(6be54b52d443a74193baafc3e10abff9ab7c7e91) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack12.rom",    0x400000, 0x400000, CRC(efc1d26d) SHA1(382ec011c27b1b357a16863a53235c6935fa0b27) )
ROM_END

ROM_START( kovshhack13 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack13.322",    0x100000, 0x400000, CRC(da73d8f1) SHA1(b8e0524659488cdad4b36eead7732452af952069) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack13.asic", 0x000000, 0x04000,  CRC(b96547bd) SHA1(cf9b19384ac3e18690e67303feab3442ddf0d2ca) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack13.rom",    0x180000, 0x800000, CRC(89132886) SHA1(25eb92a174a7e7d6c5768c125806b22799946e97) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack14 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack14.322",    0x100000, 0x400000, CRC(0d25a1eb) SHA1(bf26252d0886b3667b99213047afe2fd39f4ec03) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack14.asic", 0x000000, 0x04000,  CRC(e77e03d6) SHA1(cd779f8761c9a684d098f858de16bea2a4b74c53) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack14.rom",    0x1a00000, 0x0400000, CRC(6407ca44) SHA1(454ff5471f3a2116bfa80ed7a3fb7d2598b2d208) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602_hack14.rom",    0x0c00000, 0x0100000, CRC(d128397f) SHA1(07d7d17f03f36e58669ab32e7e2ec4dd99f5dbfd) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack15 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack15.322",    0x100000, 0x400000, CRC(07f125b3) SHA1(3ac9286cbbbe703a34ef7ee53f373abe82e86d53) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack15.asic", 0x000000, 0x04000,  CRC(95b190a7) SHA1(6379acd02919fbf0dd77d86648cf17a3c3b81546) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack15.rom",    0x0000000, 0x0800000, CRC(4a60c44f) SHA1(eb410468b96f7b8675f85372d7040f0b08a45e99) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack15.rom",    0x0000000, 0x0800000, CRC(dbd1edcb) SHA1(8d4869a03cddf6997b9a13d7bb3763e0c36b85d6) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack16 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack16.322",    0x100000, 0x400000, CRC(798d60c8) SHA1(4c81dd1b2c0f7c74d7c52e1c4bf9f3c159c87bcf) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000,  CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack16.rom",    0x180000, 0x800000, CRC(d103dc1b) SHA1(947cc29f81f5ea73523861ea39493da2942265f4) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack16.rom",    0x0000000, 0x0800000, CRC(6210cee7) SHA1(48d798181e7934c3280378fc66b02f79a44716c5) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack16.rom",    0x1000000, 0x0800000, CRC(efb30f14) SHA1(ab5b4232b2dfc9f4e3a77112028a903f30b41fb9) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack16.rom",    0x1a00000, 0x0400000, CRC(05c533a8) SHA1(c63d5c9d9dda2aa2da152f4d65a66409ee3cc567) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack16.rom",    0x0000000, 0x0800000, CRC(055af9fc) SHA1(014e762be88c1feeba166e58635cfada3f1123be) )
	ROM_LOAD( "b0601_hack16.rom",    0x0800000, 0x0400000, CRC(f43e4276) SHA1(b0ad317f70681e4300228f34bb8f4bead50111ea) )
	ROM_LOAD( "b0602_hack16.rom",    0x0c00000, 0x0100000, CRC(45e63003) SHA1(55ee40bd81be895d897e4514e0b30df2e3efbd8b) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack16.rom",    0x400000, 0x400000, CRC(511e835f) SHA1(9506fd07de2d5a4d39887d1f7ba44c071dd6831f) )
ROM_END

ROM_START( kovshhack17 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack17.322",    0x100000, 0x400000, CRC(9845122d) SHA1(54fc2d4f3e62e82f6797448d370afcb4a2d2dde5) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000,  CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack18 ) //kovshfy6
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack18.322",    0x100000, 0x400000, CRC(2380ff69) SHA1(a1e7f69baff73763129f4a1467def81e56fd961c) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000,  CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack19 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack19.322",    0x100000, 0x400000, CRC(7b258e76) SHA1(54ad020b38e9c88934bfa1fb9e37ecc687b30358) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000,  CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack19.rom",    0x180000, 0x800000, CRC(db5ffd0b) SHA1(a5a237d56348b8b665fe03ef0abc79a280d88076) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack19.rom",    0x0000000, 0x0800000, CRC(f96de31a) SHA1(b93a8683ef0437f92a946cc7fa425e748b669730) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack19.rom",    0x1000000, 0x0800000, CRC(a9662e72) SHA1(1d8e10eb6b79399d2685c9678807a01743d6f8a8) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack19.rom",    0x1a00000, 0x0400000, CRC(cf060122) SHA1(587858e0aac2d703b0a94358c24e29d0832b2329) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack19.rom",    0x0000000, 0x0800000, CRC(7db37aa0) SHA1(d43f31551c9b0531cde51e5c77331c592e5c23b8) )
	ROM_LOAD( "b0601_hack19.rom",    0x0800000, 0x0400000, CRC(89a894d7) SHA1(5ae7cd79c7e80453b064cca82292537be76b7b54) )
	ROM_LOAD( "b0602_hack19.rom",    0x0c00000, 0x0400000, CRC(7638b82e) SHA1(14263da02ee20b382962039728550888005c6e10) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack40.rom",    0x400000, 0x454F47, CRC(132765c9) SHA1(b4f56dfeba59fea248ec4e04255033e2cb3ec8fb) )
ROM_END

ROM_START( kovshhack20 ) //kovshlsqy2
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack20.322",    0x100000, 0x400000, CRC(4ab24f4f) SHA1(16027e1802830254bc74c454c04a317bff3d9dc1) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000,  CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack20.rom",   0x0000000, 0x0800000, CRC(7bd1a62d) SHA1(8dee71a336a21b8ba967066477f0285e310686e4) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack20.rom",   0x0000000, 0x0800000, CRC(52f5ba74) SHA1(05abef7cdfc9632601628bc2e8df142fc348b914) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack21 ) //kovshzlzymy
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack21.322",    0x100000, 0x400000, CRC(21bffcf1) SHA1(126033e9050ccac052ad3520eb893cdb77eeadbc) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack21.asic", 0x000000, 0x04000,  CRC(5c1c9305) SHA1(ba789c2c5df60def95faaf9607fbbba712afc0e8) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604_hack21.rom",    0x1a00000, 0x0400000, CRC(17a67ffa) SHA1(44dc2b7df6680beeef03d25c4306f37851073ba4) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )
	ROM_LOAD( "b0602_hack21",    0x0c00000, 0x0100000, CRC(1f79f118) SHA1(b5d1ed2acb9b22ec3bc662c0557b70524996cabd) )
	ROM_LOAD( "b0603_hack21",    0x0D00000, 0x0800000, CRC(d9da8cba) SHA1(aa509a7b8ab84edc35f7677b8dacf2c7e6c8fd66) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshhack22 ) //kovshzscs
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hack22.322",    0x100000, 0x200000, CRC(53eaa0c6) SHA1(e91353361aa6091aa8f3cf7d04f3d6b8bca688eb) )
	ROM_LOAD16_WORD_SWAP( "p0601_hack22.321",    0x300000, 0x200000, CRC(d0725ac0) SHA1(31b8caaa84bb977b2bca3ee2bf4cb6a4b02852e2) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000,  CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack22.rom",    0x180000, 0x800000, CRC(355eb28d) SHA1(dd3aa7b7d8d7d7ffa631a63eecd33173cad5fe6f) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",    0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )
	ROM_LOAD( "a0604.rom",    0x1a00000, 0x0400000, CRC(26b59fd3) SHA1(53219376056f4766dc5236735599d982ceb56b84) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0601_hack16.rom",    0x0800000, 0x0400000, CRC(f43e4276) SHA1(b0ad317f70681e4300228f34bb8f4bead50111ea) )
	ROM_LOAD( "b0602.rom",    0x0c00000, 0x0100000, CRC(9df77934) SHA1(99a3fe337c13702c9aa2373bcd1bb1befd0e2a13) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack22.rom",    0x400000, 0x400000, CRC(7a50501b) SHA1(1af6be69f3133ed56d4a132a1910cf562da83dac) )
ROM_END

 /**************************
 Quanhuang Sanguo Tebie Ban
*****************************/

ROM_START( kovqhsghack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "qhsg_c51_hack01.rom", 0x100000, 0x400000, CRC(4c5ea070) SHA1(1f7db4e4c7e407d2994adc1ddbc8458688f64df2) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000, CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "lsqh2_t01.rom",0x180000, 0x800000, CRC(d498d97f) SHA1(97a7b6d2ed1170449e7c2899448af7cbbca4c94f) )
	ROM_IGNORE( 0x800000 )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "lsqh2_a01.rom", 0x0000000, 0x1000000, CRC(25ae3efd) SHA1(083d977602ddb5ad54fbdcba000cd4287de8d463) )
	ROM_LOAD( "lsqh2_a23.rom", 0x1000000, 0x1000000, CRC(7a779112) SHA1(0a7d36b3715063d8eac629b95a9bb3ecd8e54fca) )
	ROM_LOAD( "lsqh2_a45.rom", 0x2000000, 0x1000000, CRC(5d7de052) SHA1(7663b6cf09f65c4644661005a38f9aba84a32913) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "lsqh2_b01.rom", 0x0000000, 0x1000000, CRC(df7ca696) SHA1(7af3d27957a39de7e4873867c9972c05af7e7964) )

	ROM_REGION( 0xc00000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "lsqh2_m01.rom",0x400000, 0x400000, CRC(01af1b65) SHA1(6cf523fa8f1e03f974771611bb9a4e08a4d4443f) )
	ROM_IGNORE( 0x400000 )
	ROM_CONTINUE( 0x800000, 0x400000 )
	ROM_IGNORE( 0x400000 )
ROM_END

 /***********************************
 Knights of Valour Super Heroes Plus
**************************************/

ROM_START( kovshphack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack01.rom",   0x100000, 0x454F48, CRC(645f924f) SHA1(7d5ce45910a6ead39b0d0457d9e98e7609b0c3cb) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack01.asic", 0x000000, 0x04000, BAD_DUMP CRC(8427c690) SHA1(e08ac566e98fa604fb819ce6c7871e112969f305) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack01.rom",    0x0000000, 0x0800000, CRC(0f73015a) SHA1(8d41f1892163b38bf1531283e867ced985304679) )
	ROM_LOAD( "a0601_hack01.rom",    0x0800000, 0x0800000, CRC(cd391de8) SHA1(c593f61ba9e0c42c4a48e549b217c396099ca840) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack01.rom",    0x1800000, 0x1000000, CRC(7d85204b) SHA1(b73fa7fa576089d510f73cc6c79bac5e5ed8cc20) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack01.rom",    0x0000000, 0x0800000, CRC(437a3c51) SHA1(f1d444fe6e66e22aa3ce412de7ef34a647a43554) )
	ROM_LOAD( "b0540_hack01.rom",    0x0800000, 0x0800000, CRC(6e21727b) SHA1(1b23ec0beca8daf8020a4bbab42961c8f5557e1e) )
	ROM_LOAD( "b0601_hack01.rom",    0x1000000, 0x0400000, CRC(184fb667) SHA1(532aab9ad823d4eb6c21b143c6d5be429bcc1f38) )

	ROM_REGION( 0x900000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack01.rom",    0x400000, 0x40001C, CRC(ae740508) SHA1(86d79163028d4615e7f34e4eaea499126a2db7dd) )
ROM_END

ROM_START( kovshphack02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack02.rom",   0x100000, 0x400000, CRC(e8050027) SHA1(fdb3b95b333086af94ea8da5f9124a8f1bbf117e) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000, BAD_DUMP CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack02.rom",    0x0000000, 0x0800000, CRC(e9c2610a) SHA1(93b20fb2e06b20ec5aa14bfa3bc3af64f4c41629) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack02.rom",    0x1800000, 0x0800000, CRC(4fd3413e) SHA1(5e8f3e421342bf558c77e59635f9b5d713e825c2) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack02.rom",    0x0000000, 0x0800000, CRC(7f17c867) SHA1(00ecfd6ad0b53d3839ef025b28d760045bd1ad57) )
	ROM_LOAD( "b0540_hack02.rom",    0x0800000, 0x0800000, CRC(60999757) SHA1(118cf058e67858958bcb931e14f5d160c7de87cc) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack03 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack03.rom",   0x100000, 0x400000, CRC(1ca558a7) SHA1(46d842443bfd6cf2527c6cec3acf07ecc55ab070) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000, BAD_DUMP CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack03.rom",    0x0000000, 0x0800000, CRC(9262f949) SHA1(2c03c14466640814eabfb2aba851a3d768a11173) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack03.rom",    0x1800000, 0x0800000, CRC(732fac87) SHA1(d0106472c9114199892e14ddc8a173c2156525d1) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack03.rom",    0x0000000, 0x0800000, CRC(49378fe7) SHA1(370349b4d278bb69d0362652a6cee557045ed4f7) )
	ROM_LOAD( "b0540_hack03.rom",    0x0800000, 0x0800000, CRC(cafe39a8) SHA1(6870d3e9b141e084bb22c9122c365106ec1c8147) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack04 ) //kovshpa2
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack04.rom",   0x100000, 0x454F84, CRC(a75c3b16) SHA1(cd5d99743295181bf9481b1b2fcccde0ed137940) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000, BAD_DUMP CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack04.rom",    0x1800000, 0x0800000, CRC(bd947a6b) SHA1(eea290dec1fbf3ac066f090d6939f29554a935ef) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack04.rom",    0x0800000, 0x0800000, CRC(15ef8e41) SHA1(775833ddfe2af1ad29ac05b856586dc9b670cb07) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack05 ) //kovshp1v4
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack05.rom",   0x100000, 0x400000, CRC(abf18981) SHA1(bf9aa24110756773051ab3099e67309bbe8ca38e) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack05.asic", 0x000000, 0x04000, BAD_DUMP CRC(e844fede) SHA1(bd5328be9b07c2296a148e6f63851e9d864be25a) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack05.rom",    0x1800000, 0x0800000, CRC(f9b4bbd5) SHA1(e4df7ffc86464915a95bed2c87f08ba438024d4a) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack05.rom",    0x0800000, 0x0800000, CRC(106eb7c0) SHA1(0f050ac974f388dbcfa103e615906ad60017af63) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack06 ) //kovshpd
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack06.322",    0x100000, 0x400000, CRC(4ad43d5e) SHA1(e56b431de3e20018ad7cbbcfcc25aab30a8ba1e5) )
	ROM_IGNORE( 0x054F84 )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack06.asic", 0x000000, 0x04000, BAD_DUMP CRC(9af4d680) SHA1(5512504272a0940274f3cf7cd8e15ff4fa9d594b) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t01s_bios=bh01.rom",  0x000000, 0x200000, CRC(1a7123a0) SHA1(cc567f577bfbf45427b54d6695b11b74f2578af3) ) //BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack06.rom",    0x0000000, 0x0800000, CRC(eaa46772) SHA1(b70b2b7aaf87cd1c56f860eb2a88aed3564996da) )
	ROM_LOAD( "a0601_hack01.rom",    0x0800000, 0x0800000, CRC(cd391de8) SHA1(c593f61ba9e0c42c4a48e549b217c396099ca840) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack01.rom",    0x1800000, 0x1000000, CRC(7d85204b) SHA1(b73fa7fa576089d510f73cc6c79bac5e5ed8cc20) )
	ROM_LOAD( "a0603.rom",    0x2800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack06.rom",    0x0000000, 0x0800000, CRC(8e650b67) SHA1(cfd600a2cf1d86d493af50e2759022aaa1b61ac6) )
	ROM_LOAD( "b0540_hack01.rom",    0x0800000, 0x0800000, CRC(6e21727b) SHA1(1b23ec0beca8daf8020a4bbab42961c8f5557e1e) )
	ROM_LOAD( "b0601.rom",    0x1000000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x900000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack06.rom",    0x400000, 0x40001C, CRC(c68e36b6) SHA1(690b5f4734a4f48fa010df0611d7188f3dff4deb) )
ROM_END

ROM_START( kovshphack07 ) //kovshpd3x
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack07.rom",   0x100000, 0x400000, CRC(c7885c6b) SHA1(16768af5def199e234fcb11e17ea9a2f47a28b65) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack07.asic", 0x000000, 0x04000,  CRC(d9a43086) SHA1(089a9ff2b5a67c6e74df4826501a366db84b0b9a) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack07.rom",    0x0000000, 0x0800000, CRC(72643288) SHA1(632f4a24f4f6a65f38dfbb9af1d624bc5c1d01f1) )
	ROM_LOAD( "a0601_hack07.rom",    0x0800000, 0x0800000, CRC(5334333b) SHA1(034425196f17fef422646e89aae86df014496e69) )
	ROM_LOAD( "a0602_hack07.rom",    0x1000000, 0x0800000, CRC(7b437e0f) SHA1(b3daa3c7d02ec79457e6a2e661daa1c6a9a8388c) )
	ROM_LOAD( "a0540_hack07.rom",    0x1800000, 0x0800000, CRC(612306ed) SHA1(ff29e784ca062b1c9295bacc02c30db0097ef8cf) )
	ROM_LOAD( "a0541_hack07.rom",    0x2000000, 0x0800000, CRC(fac5160e) SHA1(021ee624c5840f82c5838800f8eb6284cfcab979) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack07.rom",    0x0000000, 0x0800000, CRC(efd47825) SHA1(8027430b58cc21f2459dbd4a8c9b53286e2cfd0d) )
	ROM_LOAD( "b0540_hack07.rom",    0x0800000, 0x0800000, CRC(b7032905) SHA1(4a0e003c58567769421c56b9626513dfb10afae4) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack07.rom",    0x400000, 0x400000, CRC(ec3f335d) SHA1(f81e2238eae4bb5154afa28ff07e69b8f10c5ee2) )
ROM_END

ROM_START( kovshphack08 ) //kovytzyp
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack08.rom",   0x100000, 0x400000, CRC(a0ba0f05) SHA1(79e6d63f30252081d23bed22d0910e1d3e806313) )
	ROM_IGNORE( 0x0551EE )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack08.asic", 0x000000, 0x04000, BAD_DUMP CRC(ddb852e9) SHA1(51fe27e869855f52c2a8b3a4a8e07e6c364e9d4f) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack08.rom",    0x1000000, 0x0800000, CRC(f25b6930) SHA1(b29bf150ba7cee93a345cbf931ae108628d3bd83) )
	ROM_LOAD( "a0540_hack08.rom",    0x1800000, 0x0800000, CRC(9d30ffbc) SHA1(e6fea881974e7ab17d1fbaa4cf34badf6a5bee78) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack08.rom",    0x0800000, 0x0800000, CRC(2de11691) SHA1(a8be72f85c839b34a4cebf3beea047370ce515d6) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack08.rom",    0x400000, 0x400000, CRC(1f981f2c) SHA1(da3949e38e6ff8e6f84704ac9edff19dab2b8964) )
ROM_END

ROM_START( kovshphack09 ) //kovshpqszltw, kovshpqszlxb
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack09.rom",    0x100000, 0x4006F8, CRC(4c2be2a2) SHA1(6c33f22dba4ea01bd37653c5aab006b4448d80ba) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack09.asic", 0x000000, 0x04000, BAD_DUMP CRC(4627f36f) SHA1(c4daf33bcf2b3a8a8cd4c53fa0ede594170ab326) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack07.rom",    0x0000000, 0x0800000, CRC(72643288) SHA1(632f4a24f4f6a65f38dfbb9af1d624bc5c1d01f1) )
	ROM_LOAD( "a0601_hack09.rom",    0x0800000, 0x0800000, CRC(9c1d1bea) SHA1(f1fba1e71493b2f6755095b9a655c5d038f1ca0d) )
	ROM_LOAD( "a0602_hack07.rom",    0x1000000, 0x0800000, CRC(7b437e0f) SHA1(b3daa3c7d02ec79457e6a2e661daa1c6a9a8388c) )
	ROM_LOAD( "a0540_hack09.rom",    0x1800000, 0x0800000, CRC(b038e568) SHA1(67ae413771279cce95622025ef6be5b50983bc39) )
	ROM_LOAD( "a0541_hack09.rom",    0x2000000, 0x0800000, CRC(1fa3c921) SHA1(44f053826c50e762af6de9b3017563e485a4c5de) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack09.rom",    0x0000000, 0x0800000, CRC(0646c5ef) SHA1(062261023538da5d647e17a4fa47b4e4ebc4614d) )
	ROM_LOAD( "b0540_hack09.rom",    0x0800000, 0x0800000, CRC(03a1641e) SHA1(38934c2eb18fa75011de68f92bfccee7ec044524) )
	ROM_LOAD( "b0601_hack09.rom",    0x1000000, 0x0800000, CRC(5a9defbb) SHA1(67a8a322cf2fcfa0f0c857a4a5b6d9e0353c03cb) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack07.rom",    0x400000, 0x400000, CRC(ec3f335d) SHA1(f81e2238eae4bb5154afa28ff07e69b8f10c5ee2) )
ROM_END

ROM_START( kovshphack10 ) //kovwsqxzb
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack10.rom",    0x100000, 0x400000, CRC(1bb44834) SHA1(5f6ff2943a3eabc735379e3bcfc4b1c679df4d77) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack10.asic", 0x000000, 0x04000,  CRC(5aa832c1) SHA1(ccd7c7553050cbd94faf6a70dc1e3bc79bbecafb) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(de7fdc0c) SHA1(67cf82401d44336ea6b41fb60eb36028d0236a7d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack08.rom",   0x1000000, 0x0800000, CRC(f25b6930) SHA1(b29bf150ba7cee93a345cbf931ae108628d3bd83) )
	ROM_LOAD( "a0540_hack10.rom",   0x1800000, 0x0800000, CRC(e88ea35e) SHA1(74887ab676857073476987c1090823a9eeb4a000) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack10.rom",    0x0800000, 0x0800000, CRC(2556bf16) SHA1(0a82878c206ee9c074e0ff328885b34e87d94319) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack10.rom",    0x400000, 0x400000, CRC(53532587) SHA1(e1562903c6bc6fc278d6ed6448bb715736e6d129) )
ROM_END

ROM_START( kovshphack11 ) //kovytzywstw
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack11.rom",    0x100000, 0x400000, CRC(93a23c94) SHA1(e5668761f865cb5d09f98cd479a1b4f463c37106) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack10.asic", 0x000000, 0x04000,  CRC(5aa832c1) SHA1(ccd7c7553050cbd94faf6a70dc1e3bc79bbecafb) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(de7fdc0c) SHA1(67cf82401d44336ea6b41fb60eb36028d0236a7d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack08.rom",   0x1000000, 0x0800000, CRC(f25b6930) SHA1(b29bf150ba7cee93a345cbf931ae108628d3bd83) )
	ROM_LOAD( "a0540_hack11.rom",   0x1800000, 0x0800000, CRC(5e8e9406) SHA1(38c13c624087976617f8aef34bde1c3f62f08d21) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack11.rom",   0x0800000, 0x0800000, CRC(da995981) SHA1(9a4207bc5b02bdc6e0adcc3372ffa65fc8a2e99b) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack10.rom",    0x400000, 0x400000, CRC(53532587) SHA1(e1562903c6bc6fc278d6ed6448bb715736e6d129) )
ROM_END

ROM_START( kovshphack12 ) //kovwsqxzb2
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack12.rom",    0x100000, 0x400000, CRC(ab716e87) SHA1(2e1390230f1e739147c7152f85b70d9b8088a434) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack10.asic", 0x000000, 0x04000,  CRC(5aa832c1) SHA1(ccd7c7553050cbd94faf6a70dc1e3bc79bbecafb) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(de7fdc0c) SHA1(67cf82401d44336ea6b41fb60eb36028d0236a7d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack08.rom",   0x1000000, 0x0800000, CRC(f25b6930) SHA1(b29bf150ba7cee93a345cbf931ae108628d3bd83) )
	ROM_LOAD( "a0540_hack12.rom",   0x1800000, 0x0800000, CRC(cd17f5d1) SHA1(27ce1281e97515cf39bb1834448a16fe1f535045) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack12.rom",   0x0800000, 0x0800000, CRC(2e92acde) SHA1(0d00f25ccba142f2a32cacf5822f83006f62d7ba) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack10.rom",    0x400000, 0x400000, CRC(53532587) SHA1(e1562903c6bc6fc278d6ed6448bb715736e6d129) )
ROM_END

ROM_START( kovshphack13 ) //kovwslswz
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack13.rom",    0x100000, 0x40089A, CRC(2b2ece8c) SHA1(668fbc67ab19a9006b19d123fea82d15626d8e4c) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack10.asic", 0x000000, 0x04000,  CRC(5aa832c1) SHA1(ccd7c7553050cbd94faf6a70dc1e3bc79bbecafb) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(de7fdc0c) SHA1(67cf82401d44336ea6b41fb60eb36028d0236a7d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack13.rom",   0x1000000, 0x0800000, CRC(f7bac06b) SHA1(9252cb2dc080814fb72438b4b4b64a22fecaefc3) )
	ROM_LOAD( "a0540_hack13.rom",   0x1800000, 0x0800000, CRC(3aff2125) SHA1(efe5746f8280d2b87e6b3a048e7bfa153e56ffbf) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack13.rom",   0x0800000, 0x0800000, CRC(12c0ab5b) SHA1(4bad455c96c6f017f5b7fd48dcf8be438db269b3) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack22.rom",    0x400000, 0x400000, CRC(7a50501b) SHA1(1af6be69f3133ed56d4a132a1910cf562da83dac) )
ROM_END

ROM_START( kovshphack14 ) //kovytzyhjb
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack14.rom",    0x100000, 0x400000, CRC(a3776799) SHA1(fab91f0cc89ba9ba231565e7b7a42bce8372f632) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack14.asic", 0x000000, 0x04000,  CRC(9d352b6f) SHA1(9a9737478cc5aed4e60d341569c866854a3fca81) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack14.rom",    0x180000, 0x800000, CRC(fb5a543a) SHA1(2bdefe367ce3112de38b01be0d860bf7107b42fa) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601_hack14.rom",   0x0800000, 0x0800000, CRC(b252c4ba) SHA1(a167a805017d37889e3b2faa03a7daa113836405) )
	ROM_LOAD( "a0602_hack14.rom",   0x1000000, 0x0800000, CRC(6a65f8a8) SHA1(039b54c2bef270307235ba9cea05fc48e1c27d6b) )
	ROM_LOAD( "a0540_hack14.rom",   0x1800000, 0x0800000, CRC(ec1b5760) SHA1(a58be9a5e38a5346f3ac1e51c3e14e155ea81181) )
	ROM_LOAD( "a0541_hack14.rom",   0x2000000, 0x0800000, CRC(a723f320) SHA1(b4d4576d0748e9d40a81c0ccabd2d7ee46cf999d) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack14.rom",   0x0800000, 0x0800000, CRC(94fc8287) SHA1(885b85afd0a730e74bd2e83a271f45c2d90e183f) )

	ROM_REGION( 0x800041, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack14.rom",    0x400000, 0x400041, CRC(858ab94e) SHA1(9674110a943dd2cd0408a4cdeb0b08b9e6f3ce9f) )
ROM_END

ROM_START( kovshphack15 ) //kovwsqxzb3
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack15.rom",    0x100000, 0x400000, CRC(178e341e) SHA1(15adae0669ccda7265af4fe39eec8caef9222afd) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack10.asic", 0x000000, 0x04000,  CRC(5aa832c1) SHA1(ccd7c7553050cbd94faf6a70dc1e3bc79bbecafb) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(de7fdc0c) SHA1(67cf82401d44336ea6b41fb60eb36028d0236a7d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack08.rom",   0x1000000, 0x0800000, CRC(f25b6930) SHA1(b29bf150ba7cee93a345cbf931ae108628d3bd83) )
	ROM_LOAD( "a0540_hack12.rom",   0x1800000, 0x0800000, CRC(cd17f5d1) SHA1(27ce1281e97515cf39bb1834448a16fe1f535045) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack12.rom",    0x0800000, 0x0800000, CRC(2e92acde) SHA1(0d00f25ccba142f2a32cacf5822f83006f62d7ba) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack10.rom",    0x400000, 0x400000, CRC(53532587) SHA1(e1562903c6bc6fc278d6ed6448bb715736e6d129) )
ROM_END

ROM_START( kovshphack16 ) //kovshpd3gs
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack16.rom",    0x100000, 0x200000, CRC(07575b97) SHA1(6262630d61bdc2f08a1eb31b956cdd784520254e) )
	ROM_LOAD16_WORD_SWAP( "p0601h_hack16.rom",    0x300000, 0x200000, CRC(889587ee) SHA1(830320d012357c590b85401a1367dd8a5aa6eef0) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack07.asic", 0x000000, 0x04000,  CRC(d9a43086) SHA1(089a9ff2b5a67c6e74df4826501a366db84b0b9a) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack07.rom",    0x0000000, 0x0800000, CRC(72643288) SHA1(632f4a24f4f6a65f38dfbb9af1d624bc5c1d01f1) )
	ROM_LOAD( "a0601_hack09.rom",    0x0800000, 0x0800000, CRC(9c1d1bea) SHA1(f1fba1e71493b2f6755095b9a655c5d038f1ca0d) )
	ROM_LOAD( "a0602_hack07.rom",    0x1000000, 0x0800000, CRC(7b437e0f) SHA1(b3daa3c7d02ec79457e6a2e661daa1c6a9a8388c) )
	ROM_LOAD( "a0540_hack07.rom",    0x1800000, 0x0800000, CRC(612306ed) SHA1(ff29e784ca062b1c9295bacc02c30db0097ef8cf) )
	ROM_LOAD( "a0541_hack07.rom",    0x2000000, 0x0800000, CRC(fac5160e) SHA1(021ee624c5840f82c5838800f8eb6284cfcab979) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack09.rom",    0x0000000, 0x0800000, CRC(0646c5ef) SHA1(062261023538da5d647e17a4fa47b4e4ebc4614d) )
	ROM_LOAD( "b0540_hack07.rom",    0x0800000, 0x0800000, CRC(b7032905) SHA1(4a0e003c58567769421c56b9626513dfb10afae4) )
	ROM_LOAD( "b0601_hack16.rom",    0x1000000, 0x0800000, CRC(095378f3) SHA1(b068db120ff8d7c52a9553cd58f2382a58943114) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack07.rom",    0x400000, 0x400000, CRC(ec3f335d) SHA1(f81e2238eae4bb5154afa28ff07e69b8f10c5ee2) )
ROM_END

ROM_START( kovshphack17 ) //kovshptplscs
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack17.rom",    0x100000, 0x200000, CRC(86322d6a) SHA1(fcfa7691615e1d785aa95b0336d531b7dd102043) )
	ROM_LOAD16_WORD_SWAP( "p0601h_hack17.rom",    0x300000, 0x200000, CRC(b673c954) SHA1(367d40cfdc64fc44742e17ff64cb8c5c544171f1) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack17.asic", 0x000000, 0x04000, BAD_DUMP CRC(0d87d4a1) SHA1(bc981c20da426143c5e49d9fadf680b185002dd1) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack17.rom",    0x0000000, 0x2000000, CRC(dab91337) SHA1(3e81510afc25702a32baae81f8569335312ee278) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack17.rom",          0x0000000, 0x1000000, CRC(22b3beb8) SHA1(f35fbcfc28fcd12f30e1af7e6de4da8bccf0b8f9) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack18 ) //kovshpwsb
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack18.rom",    0x100000, 0x200000, CRC(82579022) SHA1(b15f1f1950c3c35c336371005a039e3559e52aed) )
	ROM_LOAD16_WORD_SWAP( "p0601h_hack18.rom",    0x300000, 0x200000, CRC(69c260ba) SHA1(bdb5fbe61c900958bef5cc5d3ee2a4dfec428c4b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack18.asic", 0x000000, 0x04000, CRC(7ece721c) SHA1(3aa11f11803643f9aa4bdafa35421626d066c4e9) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack18.rom",    0x0000000, 0x2000000, CRC(a3f903ca) SHA1(e717489adf89f4769cf2583526b9a42d60db3cd0) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack18.rom",    0x0000000, 0x1000000, CRC(7d4930d4) SHA1(93246fee290f2034a0af120bd22e253005cc80cf) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack19 ) //kovshpjgtm
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack19.rom",    0x100000, 0x200000, CRC(3ba88b2c) SHA1(9c37a963024bb43b196608393bb69e27fe75996e) )
	ROM_LOAD16_WORD_SWAP( "p0601h_hack19.rom",    0x300000, 0x200000, CRC(7ca150c7) SHA1(6b01ff9a4eaeedf519fde06cb2b851e0233f1539) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000, BAD_DUMP CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack19.rom",    0x0000000, 0x2000000, CRC(6f06104e) SHA1(f21f0f87fcbd3aedea55f12e8552b028e16ecd36) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack19.rom",    0x0000000, 0x1000000, CRC(8235d4ba) SHA1(e194bf83f6581bc851b3f3a70d07eb7a547a65c4) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack20 ) //kovshp1v4x
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack20.rom",    0x100000, 0x200000, CRC(1dbd4769) SHA1(2ebf0c8f1fe13796ae9c4abd9ee8f70713dcdf54) )
	ROM_LOAD16_WORD_SWAP( "p0601h_hack20.rom",    0x300000, 0x200000, CRC(8172bd64) SHA1(3b0919b08a37e999a337650eb2d97fcde431f4f2) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack17.asic", 0x000000, 0x04000, BAD_DUMP CRC(0d87d4a1) SHA1(bc981c20da426143c5e49d9fadf680b185002dd1) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack20.rom",    0x0000000, 0x2000000, CRC(92444dcd) SHA1(0c10f5d2e6f4a58c647153df535756b08e47e0d9) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack20.rom",    0x0000000, 0x1000000, CRC(5d5d9512) SHA1(212620d0156ce3daed88a62f0cd941d6cad31ee9) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack07.rom",    0x400000, 0x400000, CRC(ec3f335d) SHA1(f81e2238eae4bb5154afa28ff07e69b8f10c5ee2) )
ROM_END

ROM_START( kovshphack21 ) //kovytzyftxq
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack21.rom",    0x100000, 0x400000, CRC(b2e375cb) SHA1(4a2f272eadbdff7a04d2f4ff98ed4a4731d7c651) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack21.asic", 0x000000, 0x04000,  CRC(36a4ecc8) SHA1(c1475b56dc5de44c2c9de8717dfe92ebc3221b95) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack08.rom",    0x1000000, 0x0800000, CRC(f25b6930) SHA1(b29bf150ba7cee93a345cbf931ae108628d3bd83) )
	ROM_LOAD( "a0540_hack21.rom",    0x1800000, 0x0800000, CRC(0acdd7f2) SHA1(382649c6798195527cf96768e7df12f931b29d7e) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack21.rom",   0x0800000, 0x0800000, CRC(767bf47a) SHA1(15d2ce1a720d52e2c01e32771f0d7e0300a5a360) )
	ROM_LOAD( "b0601.rom",          0x1000000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack08.rom",    0x400000, 0x400000, CRC(1f981f2c) SHA1(da3949e38e6ff8e6f84704ac9edff19dab2b8964) )
ROM_END

ROM_START( kovshphack22 ) //kovshpxy
	ROM_REGION( 0x700000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack22.rom",    0x100000, 0x200000, CRC(4d972b05) SHA1(30ce31f7b9ca82b006d6279f313990f0a60e47fc) )
	ROM_LOAD16_WORD_SWAP( "p0601h_hack22.rom",    0x300000, 0x200000, CRC(60071bdd) SHA1(49013eb0847c552bd9ba335e7d352ef1ec857e6b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000, BAD_DUMP CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack22.rom",    0x0000000, 0x0800000, CRC(9f98ed76) SHA1(b4ceab1d10c8214f7e19302fca9d4a469f35b078) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack22.rom",    0x1800000, 0x0800000, CRC(f5f5d7fc) SHA1(150eac16162b1f8830b16e326f2584d7190413f9) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack22.rom",    0x0000000, 0x0800000, CRC(7d1eacc7) SHA1(ef759850110cc121504be58fbc3bc4aca3fa5b62) )
	ROM_LOAD( "b0540_hack22.rom",    0x0800000, 0x0800000, CRC(9708e8b8) SHA1(8d304ee075171adf4963b60cd457a88a0de78ac0) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack23 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack23.rom",    0x100000, 0x400000, CRC(fc5972b7) SHA1(04694b0f0c8c14b92330dd1c31978bf86374d2de) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack07.asic", 0x000000, 0x04000,  CRC(d9a43086) SHA1(089a9ff2b5a67c6e74df4826501a366db84b0b9a) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack07.rom",    0x0000000, 0x0800000, CRC(72643288) SHA1(632f4a24f4f6a65f38dfbb9af1d624bc5c1d01f1) )
	ROM_LOAD( "a0601_hack09.rom",    0x0800000, 0x0800000, CRC(9c1d1bea) SHA1(f1fba1e71493b2f6755095b9a655c5d038f1ca0d) )
	ROM_LOAD( "a0602_hack07.rom",    0x1000000, 0x0800000, CRC(7b437e0f) SHA1(b3daa3c7d02ec79457e6a2e661daa1c6a9a8388c) )
	ROM_LOAD( "a0540_hack23.rom",    0x1800000, 0x1000000, CRC(dff33658) SHA1(90a989435dd63593249e7b23b1633040f2a62e3f) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack09.rom",    0x0000000, 0x0800000, CRC(0646c5ef) SHA1(062261023538da5d647e17a4fa47b4e4ebc4614d) )
	ROM_LOAD( "b0540_hack07.rom",    0x0800000, 0x0800000, CRC(b7032905) SHA1(4a0e003c58567769421c56b9626513dfb10afae4) )
	ROM_LOAD( "b0601_hack16.rom",    0x1000000, 0x0800000, CRC(095378f3) SHA1(b068db120ff8d7c52a9553cd58f2382a58943114) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack07.rom",    0x400000, 0x400000, CRC(ec3f335d) SHA1(f81e2238eae4bb5154afa28ff07e69b8f10c5ee2) )
ROM_END

ROM_START( kovshphack24 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack24.322",    0x100000, 0x400000, CRC(404621d0) SHA1(d0302638517f99ac7e409ff9fbd623d0443200cc) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack24.asic", 0x000000, 0x04000,  CRC(c7663203) SHA1(3fa5c5dd805aa555361c5ee4bd230f0c5417d433) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack07.rom",    0x0000000, 0x0800000, CRC(72643288) SHA1(632f4a24f4f6a65f38dfbb9af1d624bc5c1d01f1) )
	ROM_LOAD( "a0601_hack09.rom",    0x0800000, 0x0800000, CRC(9c1d1bea) SHA1(f1fba1e71493b2f6755095b9a655c5d038f1ca0d) )
	ROM_LOAD( "a0602_hack07.rom",    0x1000000, 0x0800000, CRC(7b437e0f) SHA1(b3daa3c7d02ec79457e6a2e661daa1c6a9a8388c) )
	ROM_LOAD( "a0540_hack24.rom",    0x1800000, 0x1000000, CRC(358f2c24) SHA1(e9438bc7d32897564cf4325b3d97894666d63b25) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack09.rom",    0x0000000, 0x0800000, CRC(0646c5ef) SHA1(062261023538da5d647e17a4fa47b4e4ebc4614d) )
	ROM_LOAD( "b0540_hack09.rom",    0x0800000, 0x0800000, CRC(03a1641e) SHA1(38934c2eb18fa75011de68f92bfccee7ec044524) )
	ROM_LOAD( "b0601_hack09.rom",    0x1000000, 0x0800000, CRC(5a9defbb) SHA1(67a8a322cf2fcfa0f0c857a4a5b6d9e0353c03cb) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack07.rom",    0x400000, 0x400000, CRC(ec3f335d) SHA1(f81e2238eae4bb5154afa28ff07e69b8f10c5ee2) )
ROM_END

ROM_START( kovshphack25 ) //kovlsqh3
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack25.322",    0x100000, 0x400000, CRC(6c61f80f) SHA1(2797971c5a53c983284525603e2d41b2efd8f26d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china.asic", 0x000000, 0x04000, BAD_DUMP CRC(0f09a5c1) SHA1(621b38c05f33277608d58b49822aebc930ae4870) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t01s_bios=bh01.rom", 0x000000, 0x200000, CRC(1a7123a0) SHA1(cc567f577bfbf45427b54d6695b11b74f2578af3) ) //BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack25.rom",   0x1800000, 0x0800000, CRC(eadc7955) SHA1(7ae5acded2a5c47ccbeb1726f93f14afdd1ede86) )
	ROM_LOAD( "a0603.rom",    0x2000000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack25.rom",    0x0800000, 0x0800000, CRC(bf30ea67) SHA1(9d8049307c4084765eb1a1adb0530811347f2695) )
	ROM_LOAD( "b0601_hack01.rom",    0x1000000, 0x0400000, CRC(184fb667) SHA1(532aab9ad823d4eb6c21b143c6d5be429bcc1f38) )

	ROM_REGION( 0x900000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m01s_bios=bh05.rom", 0x000000, 0x200000, CRC(ef3a23ab) SHA1(5f0b73a1b8dfa5a19aa471e832a6f619c4bd4db1) ) //BIOS
	ROM_LOAD( "m0600_hack25.rom",   0x400000, 0x400000, CRC(eae5bf80) SHA1(5052849cb1ea573ee98188c594b4a449c195e441) )
ROM_END

ROM_START( kovshphack26 ) //kovassga
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack26.rom",    0x100000, 0x400000, CRC(54f6c5d9) SHA1(9abf1fed12261fdddd2e40d30d6ce536e91c1c55) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack26.asic", 0x000000, 0x04000, BAD_DUMP CRC(62d4c604) SHA1(9f40aa8508f6f6e7ae0dcd17f7adcf5d6f10559e) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack26.rom",    0x1800000, 0x0800000, CRC(cbc57bc1) SHA1(ae1ef43a5caaa1e1a0be6ba7a6598eeaeb284a1e) )
	ROM_LOAD( "a0603.rom",    0x2000000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack26.rom",   0x0800000, 0x0800000, CRC(1885039b) SHA1(23f832ee7493d11f78ea06954da748ff1fa3c595) )
	ROM_LOAD( "b0601.rom",          0x1000000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack25.rom",    0x400000, 0x400000, CRC(eae5bf80) SHA1(5052849cb1ea573ee98188c594b4a449c195e441) )
ROM_END

ROM_START( kovshphack27 ) //kovshpqxzqex
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack27.rom",    0x100000, 0x200000, CRC(c0071469) SHA1(00519b033d67fe38394b006beaa61543ab290c7e) )
	ROM_LOAD16_WORD_SWAP( "p0601h_hack27.rom",    0x300000, 0x200000, CRC(09d0b85f) SHA1(1c6e99a2f651afc7027951fe2c270629c2e8c64d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack14.asic", 0x000000, 0x04000,  CRC(9d352b6f) SHA1(9a9737478cc5aed4e60d341569c866854a3fca81) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(de7fdc0c) SHA1(67cf82401d44336ea6b41fb60eb36028d0236a7d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601_hack14.rom",   0x0800000, 0x0800000, CRC(b252c4ba) SHA1(a167a805017d37889e3b2faa03a7daa113836405) )
	ROM_LOAD( "a0602_hack14.rom",   0x1000000, 0x0800000, CRC(6a65f8a8) SHA1(039b54c2bef270307235ba9cea05fc48e1c27d6b) )
	ROM_LOAD( "a0540_hack14.rom",   0x1800000, 0x0800000, CRC(ec1b5760) SHA1(a58be9a5e38a5346f3ac1e51c3e14e155ea81181) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack14.rom",    0x0800000, 0x0800000, CRC(94fc8287) SHA1(885b85afd0a730e74bd2e83a271f45c2d90e183f) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack27.rom",    0x400000, 0x400000, CRC(968a15b9) SHA1(a335cb0e0bea1e6d3abd330a5ffb588eac0edba4) )
ROM_END

ROM_START( kovshphack28 ) //kovshpzqhl
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack28.rom",    0x100000, 0x200000, CRC(396b0f14) SHA1(f661b5b32249382f0ae06ab27e359f374b755b30) )
	ROM_LOAD16_WORD_SWAP( "p0601h_hack28.rom",    0x300000, 0x200000, CRC(b9ad393f) SHA1(56683259014c1157dfc28c817353e7eb18221d21) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack28.asic", 0x000000, 0x04000, BAD_DUMP CRC(39abc15f) SHA1(f839eb7ddf3c30ad05373fc54fae8a12f0d4cda9) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(de7fdc0c) SHA1(67cf82401d44336ea6b41fb60eb36028d0236a7d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack28.rom",    0x0000000, 0x2000000, CRC(8cee9b01) SHA1(4a3bb08844846b9217170d08d6ea3fff18b1b49a) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack28.rom",    0x0000000, 0x1000000, CRC(82a43111) SHA1(9ce61e51d3ebfcb7acd2eb32087acc1137a1723a) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack29 ) //kovshpzqhl1v4
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack29.rom",    0x100000, 0x200000, CRC(42e29952) SHA1(4c974685f01161a3b1c8dbc85ed4f66829f80422) )
	ROM_LOAD16_WORD_SWAP( "p0601h_hack29.rom",    0x300000, 0x200000, CRC(dabf844a) SHA1(e5ae6c6316beb8a6628b4e84f4c6fb5b8688f84e) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack17.asic", 0x000000, 0x04000, BAD_DUMP CRC(0d87d4a1) SHA1(bc981c20da426143c5e49d9fadf680b185002dd1) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(de7fdc0c) SHA1(67cf82401d44336ea6b41fb60eb36028d0236a7d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack29.rom",    0x1800000, 0x0800000, CRC(7bfda264) SHA1(94f3ba6101ae57e3c225b3d59c94f0f984892862) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack29.rom",   0x0800000, 0x0800000, CRC(5e9ff06a) SHA1(093cce8223af79d717dff18f036a4e9b01c22793) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

ROM_START( kovshphack30 ) //kovwsqxzs
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack30.rom",    0x100000, 0x400000, CRC(5556e8ba) SHA1(1c917940c835e9259dc98c69a6e0211befcdf1e9) )
	ROM_IGNORE( 0x400000 )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack10.asic", 0x000000, 0x04000,  CRC(5aa832c1) SHA1(ccd7c7553050cbd94faf6a70dc1e3bc79bbecafb) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack10.rom",    0x180000, 0x800000, CRC(de7fdc0c) SHA1(67cf82401d44336ea6b41fb60eb36028d0236a7d) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hack08.rom",    0x1000000, 0x0800000, CRC(f25b6930) SHA1(b29bf150ba7cee93a345cbf931ae108628d3bd83) )
	ROM_LOAD( "a0540_hack30.rom",    0x1800000, 0x0800000, CRC(0c175a59) SHA1(bad17288e375926772818c2adc5db31c0a1cebd9) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",          0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack30.rom",   0x0800000, 0x0800000, CRC(43f63c0f) SHA1(aeeb5d5f5c9c96f756f48286c171245c9cf799c2) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hack10.rom",    0x400000, 0x400000, CRC(53532587) SHA1(e1562903c6bc6fc278d6ed6448bb715736e6d129) )
ROM_END

ROM_START( kovshphack31 ) //kovshpds
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack31.rom",    0x100000, 0x400000, CRC(9c446f36) SHA1(d98cd30fd92b70b7749a9af0cc6886766031a10d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack31.asic", 0x000000, 0x04000,  CRC(c5494399) SHA1(77a1bdd68e6eaaa9a00d41123cbc71d4f3018612) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t01s_bios=bh01.rom", 0x000000, 0x200000, CRC(1a7123a0) SHA1(cc567f577bfbf45427b54d6695b11b74f2578af3) ) //BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack31.rom",    0x0000000, 0x0800000, CRC(8bccc3ba) SHA1(5511109abf8dd6e69d167c021ae6a7a9fd08b026) )
	ROM_LOAD( "a0601_hack01.rom",    0x0800000, 0x0800000, CRC(cd391de8) SHA1(c593f61ba9e0c42c4a48e549b217c396099ca840) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack31.rom",    0x1800000, 0x1000000, CRC(3b11c9b3) SHA1(3244d263c0a1aea3b619670b47c21220a42a7d10) )
	ROM_LOAD( "a0603.rom",    0x2800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack31.rom",    0x0000000, 0x0800000, CRC(32cb43ef) SHA1(96e20d08506b94a345cfc2681da24ae68fe15ed2) )
	ROM_LOAD( "b0540_hack31.rom",    0x0800000, 0x0800000, CRC(127085a9) SHA1(aeddde5212f7f0dc9478ec1503e925dc54b0eac8) )
	ROM_LOAD( "b0601_hack01.rom",    0x1000000, 0x0400000, CRC(184fb667) SHA1(532aab9ad823d4eb6c21b143c6d5be429bcc1f38) )

	ROM_REGION( 0x900000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m01s_bios=bh03.rom", 0x000000, 0x200000, CRC(81a6aeca) SHA1(9b77df457566209fdbf47ed3f62c5d3249b03ec7) ) //BIOS
	ROM_LOAD( "m0600_hack06.rom",    0x400000, 0x40001C, CRC(c68e36b6) SHA1(690b5f4734a4f48fa010df0611d7188f3dff4deb) )
ROM_END

ROM_START( kovshphack32 ) //kovlsyx
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack32.rom",   0x100000, 0x400000, CRC(4809af14) SHA1(ffc06af435d5fcc099d3b995b5b0fa0d253c2ce3) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack32.asic", 0x000000, 0x04000, BAD_DUMP CRC(8598d603) SHA1(41644cd252a7a457fc36f95d5287c93873abf543) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hack18.rom",    0x180000, 0x800000, CRC(a919ec0f) SHA1(b464490abba8a5e651c407a7833c3a2e3befa5b8) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hack32.rom",    0x0000000, 0x0800000, CRC(47794602) SHA1(be1916d3501f7946348833fd5860d129900769f1) )
	ROM_LOAD( "a0601_hack32.rom",    0x0800000, 0x0800000, CRC(d94abe4b) SHA1(58ee22308ca8eaa73ee6532cefbb574f0a994eee) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack32.rom",    0x1800000, 0x0800000, CRC(6afd8e35) SHA1(01ff4c433d8d85780f78fcf4e419c9036bc61707) )
	ROM_LOAD( "a0541_hack32.rom",    0x2000000, 0x0800000, CRC(164de1a8) SHA1(25febeef8cd058772daa4e7fb12c886f0585864e) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hack32.rom",    0x0000000, 0x0800000, CRC(f48a3b3d) SHA1(b54b49a3cf02575febda48d1deb5ed8f1370adb8) )
	ROM_LOAD( "b0540_hack32.rom",    0x0800000, 0x0800000, CRC(c3eefa33) SHA1(0d4a47e3c5661268e2f32d3b982b95e765c9b2ad) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m01s_bios=bh03.rom", 0x000000, 0x200000, CRC(81a6aeca) SHA1(9b77df457566209fdbf47ed3f62c5d3249b03ec7) ) //BIOS
	ROM_LOAD( "m0600_hack32.rom",    0x400000, 0x400000, CRC(459ad15f) SHA1(6dda85c32e5472db60551870cb522e9333013b32) )
ROM_END

ROM_START( kovshphack33 ) //kovshpsjb
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_hack33.rom",   0x100000, 0x400000, CRC(e9163584) SHA1(79329c69f2e8dbe21257baec32103695f98cc51c) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hack33.asic", 0x000000, 0x04000, BAD_DUMP CRC(aba16d49) SHA1(8c160541f74daf446f8094c3ba42489322c9ee74) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600.rom",    0x180000, 0x800000, CRC(4acc1ad6) SHA1(0668dbd5e856c2406910c6b7382548b37c631780) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",    0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0540_hack02.rom",    0x1800000, 0x0800000, CRC(4fd3413e) SHA1(5e8f3e421342bf558c77e59635f9b5d713e825c2) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",    0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540_hack02.rom",    0x0800000, 0x0800000, CRC(60999757) SHA1(118cf058e67858958bcb931e14f5d160c7de87cc) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600.rom",    0x400000, 0x400000, CRC(3ada4fd6) SHA1(4c87adb25d31cbd41f04fbffe31f7bc37173da76) )
ROM_END

 /***************
 Martial Masters
******************/

ROM_START( martmasthack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v104_32m_hack01.rom",    0x100000, 0x400000, CRC(c8b39568) SHA1(f377a3ba3461f2b84f3acf8febf98707a7f2a62b) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "martial_masters_v101_cn.asic", 0x000000, 0x04000, CRC(b3e25b7d) SHA1(6147d7ee2e11636521df1bb96ed5da8ad21b2a57) ) // not verified, could be bad

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v102_16m.rom", 0x000000, 0x200000,  CRC(18b745e6) SHA1(7bcb58dd3a2d6072f492cf0dd7181cb061c1f49d) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1000.rom",    0x180000, 0x800000, CRC(bbf879b5) SHA1(bd9a6aea34ad4001e89e62ff4b7a2292eb833c00) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1000.rom",    0x0000000, 0x0800000, CRC(43577ac8) SHA1(6eea8b455985d5bac74dcc9943cdc3c0902de6cc) )
	ROM_LOAD( "a1001.rom",    0x0800000, 0x0800000, CRC(fe7a476f) SHA1(a8c7f1f0dd3e53141aed6d927eb88a3ceebb81e4) )
	ROM_LOAD( "a1002.rom",    0x1000000, 0x0800000, CRC(62e33d38) SHA1(96163d583e25073594f8413ce263e56b66bd69a1) )
	ROM_LOAD( "a1003.rom",    0x1800000, 0x0800000, CRC(b2c4945a) SHA1(7b18287a2db56db3651cfd4deb607af53522fefd) )
	ROM_LOAD( "a1004.rom",   0x2000000, 0x0400000, CRC(9fd3f5fd) SHA1(057531f91062be51589c6cf8f4170089b9be6380) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1000.rom",    0x0000000, 0x0800000,  CRC(c5961f6f) SHA1(a68060b10edbd084cbde79d2ed1c9084777beb10) )
	ROM_LOAD( "b1001.rom",   0x0800000, 0x0800000,  CRC(0b7e1c06) SHA1(545e15e0087f8621d593fecd8b4013f7ca311686) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1000.rom",    0x400000, 0x800000, CRC(ed407ae8) SHA1(a6e9c09b39c13e8fb7fbc89fa9f823cbeb66e901) )
	ROM_LOAD( "m1001.rom",    0xc00000, 0x400000, CRC(662d2d48) SHA1(2fcc3099d9c04456cae3b13035fb28eaf709e7d8) )
ROM_END

ROM_START( martmasthack02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v104_32m_hack02.rom",    0x100000, 0x400000, CRC(5f51a4e5) SHA1(8e3ae6f70699912572e6f3d0e1ba7f9d80b5d656) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "martial_masters_v101_cn.asic", 0x000000, 0x04000, CRC(b3e25b7d) SHA1(6147d7ee2e11636521df1bb96ed5da8ad21b2a57) ) // not verified, could be bad

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v102_16m.rom", 0x000000, 0x200000,  CRC(18b745e6) SHA1(7bcb58dd3a2d6072f492cf0dd7181cb061c1f49d) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1000.rom",    0x180000, 0x800000, CRC(bbf879b5) SHA1(bd9a6aea34ad4001e89e62ff4b7a2292eb833c00) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1000.rom",    0x0000000, 0x0800000, CRC(43577ac8) SHA1(6eea8b455985d5bac74dcc9943cdc3c0902de6cc) )
	ROM_LOAD( "a1001.rom",    0x0800000, 0x0800000, CRC(fe7a476f) SHA1(a8c7f1f0dd3e53141aed6d927eb88a3ceebb81e4) )
	ROM_LOAD( "a1002.rom",    0x1000000, 0x0800000, CRC(62e33d38) SHA1(96163d583e25073594f8413ce263e56b66bd69a1) )
	ROM_LOAD( "a1003.rom",    0x1800000, 0x0800000, CRC(b2c4945a) SHA1(7b18287a2db56db3651cfd4deb607af53522fefd) )
	ROM_LOAD( "a1004.rom",   0x2000000, 0x0400000, CRC(9fd3f5fd) SHA1(057531f91062be51589c6cf8f4170089b9be6380) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1000.rom",    0x0000000, 0x0800000,  CRC(c5961f6f) SHA1(a68060b10edbd084cbde79d2ed1c9084777beb10) )
	ROM_LOAD( "b1001.rom",   0x0800000, 0x0800000,  CRC(0b7e1c06) SHA1(545e15e0087f8621d593fecd8b4013f7ca311686) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1000.rom",    0x400000, 0x800000, CRC(ed407ae8) SHA1(a6e9c09b39c13e8fb7fbc89fa9f823cbeb66e901) )
	ROM_LOAD( "m1001.rom",    0xc00000, 0x400000, CRC(662d2d48) SHA1(2fcc3099d9c04456cae3b13035fb28eaf709e7d8) )
ROM_END

ROM_START( martmasthack03 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v104_32m_hack03.rom",    0x100000, 0x400000, CRC(39010ca0) SHA1(51cc7b57b4670a5ac77f019c2b652e63fbaab9c4) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "martial_masters_v101_cn.asic", 0x000000, 0x04000, CRC(b3e25b7d) SHA1(6147d7ee2e11636521df1bb96ed5da8ad21b2a57) ) // not verified, could be bad

	ROM_REGION32_LE( 0x400000, "user1", 0 )
	ROM_LOAD( "v102_16m.rom", 0x000000, 0x200000,  CRC(18b745e6) SHA1(7bcb58dd3a2d6072f492cf0dd7181cb061c1f49d) )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t1000.rom",    0x180000, 0x800000, CRC(bbf879b5) SHA1(bd9a6aea34ad4001e89e62ff4b7a2292eb833c00) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a1000.rom",    0x0000000, 0x0800000, CRC(43577ac8) SHA1(6eea8b455985d5bac74dcc9943cdc3c0902de6cc) )
	ROM_LOAD( "a1001.rom",    0x0800000, 0x0800000, CRC(fe7a476f) SHA1(a8c7f1f0dd3e53141aed6d927eb88a3ceebb81e4) )
	ROM_LOAD( "a1002.rom",    0x1000000, 0x0800000, CRC(62e33d38) SHA1(96163d583e25073594f8413ce263e56b66bd69a1) )
	ROM_LOAD( "a1003.rom",    0x1800000, 0x0800000, CRC(b2c4945a) SHA1(7b18287a2db56db3651cfd4deb607af53522fefd) )
	ROM_LOAD( "a1004.rom",   0x2000000, 0x0400000, CRC(9fd3f5fd) SHA1(057531f91062be51589c6cf8f4170089b9be6380) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b1000.rom",    0x0000000, 0x0800000,  CRC(c5961f6f) SHA1(a68060b10edbd084cbde79d2ed1c9084777beb10) )
	ROM_LOAD( "b1001.rom",   0x0800000, 0x0800000,  CRC(0b7e1c06) SHA1(545e15e0087f8621d593fecd8b4013f7ca311686) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m1000.rom",    0x400000, 0x800000, CRC(ed407ae8) SHA1(a6e9c09b39c13e8fb7fbc89fa9f823cbeb66e901) )
	ROM_LOAD( "m1001.rom",    0xc00000, 0x400000, CRC(662d2d48) SHA1(2fcc3099d9c04456cae3b13035fb28eaf709e7d8) )
ROM_END

 /***********************
 Oriental Legend Special
**************************/

ROM_START( oldshack01 ) //oldsdsgl
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack01.v10",    0x100000, 0x400000, CRC(fd55142c) SHA1(5c76d85d3867428568b81f8f92035337f9e47ae1) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack01.rom",    0x180000, 0x400000, CRC(434ddae8) SHA1(6a439dfd169b83bbd8ed442e72cf6fc27c142e80) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION16_LE( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack01.rom",    0x1800000, 0x400000, CRC(1c174e4a) SHA1(e1e01e54837c306c32424f61090edf45dd614866) )

	ROM_REGION16_LE( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack01.rom6",    0x0c00000, 0x400000, CRC(4922301f) SHA1(a9822daff33b1ef95d7e087ffd47265b4259120b) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack02.v10",    0x100000, 0x400000, CRC(01e8414c) SHA1(ec50a4ff4de7b0321a4171abc17f41a52d0296a9) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x40000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump_hack02", 0x000000, 0x40000, CRC(619cc52d) SHA1(f249a0b58c8790a42d042ad09eb28d8d4eeb20eb) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack03 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack03.v10",    0x100000, 0x400000, CRC(98c26fce) SHA1(5372f81b7075f4b8cc5ab4149dd47e5e6035ca95) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack04 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack04.v10",    0x100000, 0x400000, CRC(cdce5db9) SHA1(db1ee341141b933e2969f201bc478726c908c0fd) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack05 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack05.v10",    0x100000, 0x400000, CRC(754c3fbf) SHA1(a765501b933c11b58f51051737da7b60fc982ddd) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack06 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack06.v10",    0x100000, 0x400000, CRC(adc0df6f) SHA1(8d603e90ab361d3d4f230150c0897fba5954a590) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack06.rom",    0x180000, 0x400000, CRC(090f1697) SHA1(6a9696beb8b838de1566bdb9e195235ff4eb5cd4) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500_hack06.rom",    0x0000000, 0x400000, CRC(bbc06d42) SHA1(09399a556327bd93035654c7e2e51ccd8f352358) )
	ROM_LOAD( "a0501_hack06.rom",    0x0400000, 0x400000, CRC(f0b6af8a) SHA1(2872ca14c7e03af32b4420e9dd3f74cc2f616b17) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505_hack06.rom",    0x1400000, 0x400000, CRC(9d378b0c) SHA1(228f8ac3cb3486faa8721d54be74ef1d603b0983) )
	ROM_LOAD( "a0506_hack06.rom",    0x1800000, 0x400000, CRC(e2dace7d) SHA1(374640a3faf5c824944b7a495d37a59afb7bcb70) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500_hack06.rom",    0x0000000, 0x400000, CRC(1b68c121) SHA1(323fc40cbf3556e7f9fda65059aee5fc1d1b6065) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502_hack06.rom",    0x0800000, 0x400000, CRC(6b22373b) SHA1(004f266e3525320899e8b87cde530f964081e4ae) )
	ROM_LOAD( "b0503_hack06.rom",    0x0c00000, 0x400000, CRC(cb813cab) SHA1(970f074755114fd219091ae86dcb3590aa583e01) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500_ah27.rom",    0x400000, 0x200000, CRC(5a462366) SHA1(e7a6cf66dfc9e822c799e78fbba08a910f50c504) )
ROM_END

ROM_START( oldshack07 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack07.v10",    0x100000, 0x400000, CRC(119dcb89) SHA1(19618ea167eab9cbabd0343a166a2b6ce060deda) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack08 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack08.v10",    0x100000, 0x400000, CRC(d94a3c07) SHA1(b69c2028bdba7c2b901c8117193d4c5f8652f6cc) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack09 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack09.v10",    0x100000, 0x400000, CRC(d8b762e3) SHA1(36d3b5b4bd957db861252448adb29d8d6f0fe692) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack10 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack10.v10",    0x100000, 0x400000, CRC(a02bf3c3) SHA1(23c76c9226fb571b13b58cf0c228b1ea584c3adb) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x40000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump_hack02", 0x000000, 0x40000, CRC(619cc52d) SHA1(f249a0b58c8790a42d042ad09eb28d8d4eeb20eb) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500_hack10.rom",    0x0000000, 0x400000, CRC(292202eb) SHA1(8b8d51515b7eedcc9d1e03e0bf50af01450e9d71) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500_hack10.rom",    0x0000000, 0x400000, CRC(b7eb219f) SHA1(06923215030b4e4640eebf9ffff6a7b43965de45) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500_hack10.rom",    0x400000, 0x200000, CRC(cf5ffc59) SHA1(1c76101afc3e44d189c890cd52e5d905975a2e53) )
ROM_END

ROM_START( oldshack11 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack11.v10",    0x100000, 0x400000, CRC(d56475e6) SHA1(a31cb41239393af9f7c772666299898b659df1c5) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack12 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack12.v10",    0x100000, 0x400000, CRC(35381d67) SHA1(3a58e99d6d902b4c3efb7d837ea1312c8fe164aa) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack13 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack13.v10",    0x100000, 0x400000, CRC(efd59c5e) SHA1(3d86bd7ebe41d1dfbef707dc9d656d47b1a8f29c) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500_hack13.rom",    0x0000000, 0x400000, CRC(934284ca) SHA1(b54aaef0cdc92aaa77eb11286f2ba69ca9809bf6) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500_hack13.rom",    0x0000000, 0x400000, CRC(0ad692b4) SHA1(087e4a33b991efeb5d064324adfafdb82f8556ce) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack14 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack14.v10",    0x100000, 0x400000, CRC(6ecd8e4b) SHA1(a9a24d1b2c5f275b85acd79c1e57b4cec43cbea3) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack15 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack15.v10",    0x100000, 0x400000, CRC(407b5aa3) SHA1(5ba7e74ba52191a0c163744119e653ce435bf47c) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack16 ) //oldskof
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack16.v10",    0x100000, 0x400000, CRC(da40ae72) SHA1(0c5fe59799e931f49c3f3f000485f9cf7bf7b0af) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack16.rom",    0x180000, 0x400000, CRC(78cb3c1f) SHA1(ae04e1e508015f4bb5c35c053dfc76627de0c523) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500_hack16.rom",    0x0000000, 0x400000, CRC(f4cc4b57) SHA1(b3877e2cd03ddaabee6302b0b19dd7db75174a63) )
	ROM_LOAD( "a0501_hack16.rom",    0x0400000, 0x400000, CRC(6957bbe6) SHA1(871a76f66b12ee7dd00346045ef68ca4ddc44cc0) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500_hack16.rom",    0x0000000, 0x400000, CRC(28c48da5) SHA1(433ec883b5501ed45c43c4fdeef9d5fda3f510d8) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack17 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack17.v10",    0x100000, 0x400000, CRC(86aa9332) SHA1(036cf2d3fbe0354fd5b052f57b8f1f520a7cca27) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack18 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack18.v10",    0x100000, 0x400000, CRC(47ce8562) SHA1(8465ef44f027d9e017a59d33990be6da17098997) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack18.rom",    0x180000, 0x400000, CRC(1a8e3cec) SHA1(60f2b84762893826dff93a72c28547995c69bcc7) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501_hack18.rom",    0x0400000, 0x400000, CRC(b6266e02) SHA1(d8ffc5ca209fa08165e84d11c5e2f1028ee14616) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack18.rom",    0x1800000, 0x400000, CRC(69adc397) SHA1(ec44f4d1494c1128706636284196ae0b6016f789) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500_hack18.rom",    0x0000000, 0x400000, CRC(d3b2d80d) SHA1(32eef56c4785b04b74dcf1aa813e153bc1dba060) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack18.rom6",    0x0c00000, 0x400000, CRC(b9569fb9) SHA1(3311e15e41537af1eed23cad62c0e42ec9de3e7e) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500_ah125.rom",    0x400000, 0x200000, CRC(256f2e79) SHA1(ba1ccadf85ce6ed7c8de1c112ba87385683239ad) )
ROM_END

ROM_START( oldshack19 ) //olds100a2009
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack19.v10",    0x100000, 0x400000, CRC(9f6865cd) SHA1(48c029865896206e6afd9dc78809b7187a2399a3) )
	ROM_IGNORE( 0x54F47 )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x40000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump_hack02", 0x000000, 0x40000, CRC(619cc52d) SHA1(f249a0b58c8790a42d042ad09eb28d8d4eeb20eb) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack19.rom",    0x180000, 0x400000, CRC(502b4044) SHA1(fcb96d4960e09906fe27a7c668885ee28b65e2ef) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500_hack19.rom",    0x0000000, 0x400000, CRC(d6008de3) SHA1(5d306ba738441d26956084ecf1de09c23b2d988c) )
	ROM_LOAD( "a0501_hack18.rom",    0x0400000, 0x400000, CRC(b6266e02) SHA1(d8ffc5ca209fa08165e84d11c5e2f1028ee14616) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack19.rom",    0x1800000, 0x400000, CRC(1539faa1) SHA1(7d9615c16ad0282640ebb1035fce0e887f0707f6) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500_hack18.rom",    0x0000000, 0x400000, CRC(d3b2d80d) SHA1(32eef56c4785b04b74dcf1aa813e153bc1dba060) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack19.rom",    0x0c00000, 0x400000, CRC(7d777b31) SHA1(3621b9a6767cfa5a899dbd441565e09b4ef13204) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack20 ) //olds100afm
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack20.v10",    0x100000, 0x400000, CRC(f059dfb5) SHA1(b6aaa9479a421257c8a7412618277aacacebce3c) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506.rom",    0x1800000, 0x400000, CRC(087ac60c) SHA1(3d5bf7dd40c8a3c1224cf82e12410ca904c0c5db) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503.rom",    0x0c00000, 0x400000, CRC(e41d98e4) SHA1(f80b27fcee81762993e09bf1b3cad6e85274760c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack21 ) //olds100asr
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack21.v10",    0x100000, 0x400000, CRC(9fa9540f) SHA1(43bc0b474ac0975eaa5af9f589f21240eb5aa9a5) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack21.rom",    0x1800000, 0x400000, CRC(d76bdbad) SHA1(6785ffc0acd3b9b04eba550b243b6125d0ee6c9f) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack21.rom",    0x0c00000, 0x400000, CRC(d5c55bd3) SHA1(11aa795d20a6efeb0dcd240214ff4983c48061e4) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack22 ) //olds100aem2015
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack22.v10",    0x100000, 0x400000, CRC(17ca6649) SHA1(87b5128d0e6376c8ff4297e84f1e8bbad24bb28a) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack21.rom",    0x1800000, 0x400000, CRC(d76bdbad) SHA1(6785ffc0acd3b9b04eba550b243b6125d0ee6c9f) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack21.rom",    0x0c00000, 0x400000, CRC(d5c55bd3) SHA1(11aa795d20a6efeb0dcd240214ff4983c48061e4) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack23 ) //olds100asm
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack23.v10",    0x100000, 0x400000, CRC(d77ee880) SHA1(7dbf1f03781d3f468e586654ec48c1cd200bc802) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack21.rom",    0x1800000, 0x400000, CRC(d76bdbad) SHA1(6785ffc0acd3b9b04eba550b243b6125d0ee6c9f) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack21.rom",    0x0c00000, 0x400000, CRC(d5c55bd3) SHA1(11aa795d20a6efeb0dcd240214ff4983c48061e4) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack24 ) //olds100aem2015
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack24.v10",    0x100000, 0x400000, CRC(fbf9e737) SHA1(fe04230499fa4b9b833e1d97986f22d02659f688) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack21.rom",    0x1800000, 0x400000, CRC(d76bdbad) SHA1(6785ffc0acd3b9b04eba550b243b6125d0ee6c9f) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack21.rom",    0x0c00000, 0x400000, CRC(d5c55bd3) SHA1(11aa795d20a6efeb0dcd240214ff4983c48061e4) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack25 ) //olds100afybh
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack25.v10",    0x100000, 0x400000, CRC(fc1bcd42) SHA1(e16bc382df78b71672c352bf19965755ce562244) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack25.rom",    0x180000, 0x400000, CRC(4d8063e6) SHA1(2be2fbf50abf11348d6e03c2500b87857d83b124) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500_hack25.rom",    0x0000000, 0x400000, CRC(4d0c685f) SHA1(8fa33b5d18a0e96cc645a5d891997cac8ff3d194) )
	ROM_LOAD( "a0501_hack25.rom",    0x0400000, 0x400000, CRC(c352d1c0) SHA1(1f44ae8ab64d5b764a61480e8fcdbdc75d98d7aa) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack25.rom",    0x1800000, 0x400000, CRC(212f9bec) SHA1(87c144e893e1a84370519df7aeeb23c0a0fe3dec) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500_hack25.rom",    0x0000000, 0x400000, CRC(cb608609) SHA1(fc17bbd10fe270bc7c84080246cf1ff940f4c996) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack25.rom",    0x0c00000, 0x400000, CRC(c5beb6f8) SHA1(0d6eb085b1fe38c1842edc189fe5a3786c23b8a8) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack26 ) //olds100aylzx
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack26.v10",    0x100000, 0x400000, CRC(3541e3b5) SHA1(67cbdee7be4e210a7ecc1ebe70e825ac54bcfdd9) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack26.rom",    0x1800000, 0x400000, CRC(8a050a47) SHA1(c84ea6674cfcacb09453b8946d97345eabfcd12e) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack26.rom6",    0x0c00000, 0x400000, CRC(659ea5d5) SHA1(7383d9ea87f746d9e4bf956b9f4b026ddd44a374) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack27 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack27.v10",    0x100000, 0x400000, CRC(a7c39af7) SHA1(f0004e3d221ff6060531cc6931fb2cf59caafaae) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack27.rom",    0x180000, 0x400000, CRC(d6e659d2) SHA1(5161b6462ecb6192c7e5494ce63bc962fce01844) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500_hack27.rom",    0x0000000, 0x400000, CRC(3bd1f686) SHA1(44924f2fede3f539fe7b61a88beda62c21bac0f1) )
	ROM_LOAD( "a0501_hack27.rom",    0x0400000, 0x400000, CRC(66761144) SHA1(a371c765886067c8d75202438172ca81dc6db96d) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack27.rom",    0x1800000, 0x400000, CRC(cdc61ba7) SHA1(2f3c52d2ba801780ad5c94b76000d885a136ac3e) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500_hack27.rom",    0x0000000, 0x400000, CRC(37efad3a) SHA1(48a552d7a5ef45d4a44cfc848b4b6da1a99f2a48) )
	ROM_LOAD( "b0501_hack27.rom",    0x0400000, 0x400000, CRC(e79b47bf) SHA1(588af08a8ebeab2ff202cdf289b7b8fd35976655) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack27.rom",    0x0c00000, 0x400000, CRC(83d3f7b4) SHA1(33dc746ea3e415424e69f966e881808109475aa7) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack28 ) //olds100ahxwj
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack28.v10",    0x100000, 0x400000, CRC(ec4efc5a) SHA1(27e7aeb1b674d34a0ea6258c69364d74273e47d3) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack01.rom",    0x180000, 0x400000, CRC(434ddae8) SHA1(6a439dfd169b83bbd8ed442e72cf6fc27c142e80) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack28.rom",    0x1800000, 0x400000, CRC(5d36a5ed) SHA1(0403e1a7001e3daa2f22bec2886853d80c32727b) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack28.rom6",    0x0c00000, 0x400000, CRC(7445851e) SHA1(6510e06a80379aa81f48b4f8449a2e7884e38f35) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack29 ) //olds100azero
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack29.v10",    0x100000, 0x400000, CRC(98c35ddd) SHA1(a418c3e2798287d689af26c80538314a359d0f35) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500.rom",    0x180000, 0x400000, CRC(d881726c) SHA1(a82517e665996f7b7017c940f1fcf016fccb65c2) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack29.rom",    0x1800000, 0x400000, CRC(f5e5cce3) SHA1(8672e1a3282b2738dcc3d04c8deba13e4e79005d) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack29.rom6",    0x0c00000, 0x400000, CRC(9679f77d) SHA1(a35fd4a130a9083a5edf0f98b1f9f01ff4f7844b) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500_hack29.rom",    0x400000, 0x200000, CRC(8d10c3a6) SHA1(4efd78ae2bbdf0e6de7375b17f32e11c9c67e6fb) )
ROM_END

ROM_START( oldshack30 ) //olds100am
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack30.v10",    0x100000, 0x400000, CRC(3b94c0ac) SHA1(c6ef873f9e41d215ee97378a584813c0caab2355) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack01.rom",    0x180000, 0x400000, CRC(434ddae8) SHA1(6a439dfd169b83bbd8ed442e72cf6fc27c142e80) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack30.rom",    0x1800000, 0x400000, CRC(b88991f9) SHA1(760ee8b6d3e418ada1c433ffc97673eacb81d8ba) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack30.rom",    0x0c00000, 0x400000, CRC(d1d330e8) SHA1(38ad585299fc5f4b7b78cac8db6ee0bb9e5b329c) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

ROM_START( oldshack31 ) //olds100adsgl
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0500_hack31.v10",    0x100000, 0x400000, CRC(9db0d56b) SHA1(53684a0fdc013402edb78e9631b61481585866c1) )

	ROM_REGION( 0x010000, "user1", ROMREGION_ERASEFF )
	ROM_LOAD( "sp_data.rom", 0x000000, 0x010000,  CRC(e7613dda) SHA1(0d7c043b90e2f9a36a45066f22e3e305dc716676) )

	ROM_REGION( 0x4000, "user2", ROMREGION_ERASEFF )
	ROM_LOAD( "ram_dump", 0x000000, 0x04000, CRC(280cfb4e) SHA1(cd2bdcaa21347952c2bf38b105a204d327fde39e) )

	ROM_REGION( 0xc00000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0500_hack01.rom",    0x180000, 0x400000, CRC(434ddae8) SHA1(6a439dfd169b83bbd8ed442e72cf6fc27c142e80) )
	ROM_LOAD( "t0501.rom",    0x580000, 0x200000, CRC(d2106864) SHA1(65d827135b87d82196433aea3279608ee263feca) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0500.rom",    0x0000000, 0x400000, CRC(80a59197) SHA1(7d0108e2f0d0347d43ace2d96c0388202c05fdfb) )
	ROM_LOAD( "a0501.rom",    0x0400000, 0x400000, CRC(98c931b1) SHA1(9b70d1a7beb4c3a0c1436c25fd1fb76e47539538) )
	ROM_LOAD( "a0502.rom",    0x0800000, 0x400000, CRC(c3fcdf1d) SHA1(107585fd103fcd0af0fb7db283be4f7c7058aef7) )
	ROM_LOAD( "a0503.rom",    0x0c00000, 0x400000, CRC(066dffec) SHA1(f023032a7202b7090fb609a39e0f19018e664bf3) )
	ROM_LOAD( "a0504.rom",    0x1000000, 0x400000, CRC(45337583) SHA1(c954d0e5bf7fa99c90b0d154e7119d2b0c461f1c) )
	ROM_LOAD( "a0505.rom",    0x1400000, 0x400000, CRC(5b8cf3a5) SHA1(856d1e47b5d9a66dcfbdc74a51ed646fd7d96a35) )
	ROM_LOAD( "a0506_hack01.rom",    0x1800000, 0x400000, CRC(1c174e4a) SHA1(e1e01e54837c306c32424f61090edf45dd614866) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0500.rom",    0x0000000, 0x400000, CRC(cde07f74) SHA1(1fe90db7c57faa28f3a054b2c07909bef89e3efb) )
	ROM_LOAD( "b0501.rom",    0x0400000, 0x400000, CRC(1546c2e9) SHA1(a7b9c8b44203db54a59d49fe469bb52bba807ba2) )
	ROM_LOAD( "b0502.rom",    0x0800000, 0x400000, CRC(e97b31c3) SHA1(1a7ca4f6c8644e84a33ae41cd4637f21046b14c5) )
	ROM_LOAD( "b0503_hack01.rom6",    0x0c00000, 0x400000, CRC(4922301f) SHA1(a9822daff33b1ef95d7e087ffd47265b4259120b) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0500.rom",    0x400000, 0x200000, CRC(37928cdd) SHA1(e80498cabc2a6a54d4f3ebcb097d4b3fad96fe55) )
ROM_END

 /****************************
 Oriental Legend Special Plus
*******************************/

ROM_START( oldsplushack01 ) //oldsplushmf
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p05301_hack01.rom",   0x100000, 0x400000, CRC(c2e70cae) SHA1(a676917846504fbdac6970021faa730a59c95d27) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "oldsplus_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0x800000, "user1", ROMREGION_ERASE00 )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t05301.rom",   0x180000, 0x800000, CRC(8257bbb0) SHA1(b48067b7e7081a15fddf21739b641d677c2df3d9) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a05301.rom",   0x0000000, 0x0800000, CRC(57946fd2) SHA1(5d79bc71a1881f3099821a9b255a5f271e0eeff6) )
	ROM_LOAD( "a05302_hack01.rom",   0x0800000, 0x0800000, CRC(65acdbf7) SHA1(008346d963e67e858d91a9cd1206e125e2eddec6) )
	ROM_LOAD( "a05303.rom",   0x1000000, 0x0800000, CRC(13475d85) SHA1(4683a3bf304fdc15ffb1c61b7957ad68b023fa33) )
	ROM_LOAD( "a05304_hack01.rom",   0x1800000, 0x0800000, CRC(b92e10a4) SHA1(f6e323187a46ff72dbba0618b0abd1b05208ba1a) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b05301_hack01.rom",   0x0000000, 0x0800000, CRC(7aedd210) SHA1(f974d4800d61dcdf779b52c190384ec3c6ef12e5) )
	ROM_LOAD( "b05302_hack01.rom",   0x0800000, 0x0800000, CRC(059d9ad8) SHA1(9375a9c71fdde23eabd302c116b4e50a766d9d27) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m05301_hack01.rom",   0x400000, 0x400000, CRC(61a1413c) SHA1(f5a739226dfb95005543aa6cf7132b6fec3d8b43) )
ROM_END

ROM_START( oldsplushack02 ) //oldsplusp
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p05301_hack02.rom",   0x100000, 0x400000, CRC(d97004a3) SHA1(e8144d68e92e132e5aa5af662737d16f7576419c) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "oldsplus_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0x800000, "user1", ROMREGION_ERASE00 )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t05301.rom",   0x180000, 0x800000, CRC(8257bbb0) SHA1(b48067b7e7081a15fddf21739b641d677c2df3d9) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a05301.rom",   0x0000000, 0x0800000, CRC(57946fd2) SHA1(5d79bc71a1881f3099821a9b255a5f271e0eeff6) )
	ROM_LOAD( "a05302.rom",   0x0800000, 0x0800000, CRC(3459a0b8) SHA1(94ab6f980b5582f1db9bb12019d03f0b6e0a06df) )
	ROM_LOAD( "a05303.rom",   0x1000000, 0x0800000, CRC(13475d85) SHA1(4683a3bf304fdc15ffb1c61b7957ad68b023fa33) )
	ROM_LOAD( "a05304.rom",   0x1800000, 0x0800000, CRC(f03ef7a6) SHA1(c18b1b622b430d5e031e65daa6819b84c3e12ef5) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b05301.rom",   0x0000000, 0x0800000, CRC(fd98f503) SHA1(02046ab1aa89f63bff149003d9d61776e025a92a) )
	ROM_LOAD( "b05302.rom",   0x0800000, 0x0800000, CRC(9f6094a8) SHA1(69f6f2003ab975eae13ea6b5c2ffa40df6e6bdf6) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m05301.rom",   0x400000, 0x400000, CRC(86ec83bc) SHA1(067cb7ec449eacd1f49298f45a364368934db5dd) )
ROM_END

ROM_START( oldsplushack03 ) //oldsplusnr
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p05301_hack03.rom",   0x100000, 0x400000, CRC(97a7cf98) SHA1(4adf2104e5de92ffd7e4e15cd3933b1d85daaf04) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "oldsplus_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0x800000, "user1", ROMREGION_ERASE00 )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t05301.rom",   0x180000, 0x800000, CRC(8257bbb0) SHA1(b48067b7e7081a15fddf21739b641d677c2df3d9) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a05301_hack03.rom",   0x0000000, 0x0800000, CRC(3d3125ff) SHA1(fef80d4ae377e391e2fb7a296fb4b49df42a6687) )
	ROM_LOAD( "a05302_hack03.rom",   0x0800000, 0x0800000, CRC(4ed9028c) SHA1(9c4038097b225c331618dbf0dac3fb9d37a25e9f) )
	ROM_LOAD( "a05303.rom",   0x1000000, 0x0800000, CRC(13475d85) SHA1(4683a3bf304fdc15ffb1c61b7957ad68b023fa33) )
	ROM_LOAD( "a05304.rom",   0x1800000, 0x0800000, CRC(f03ef7a6) SHA1(c18b1b622b430d5e031e65daa6819b84c3e12ef5) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b05301_hack03.rom",   0x0000000, 0x0800000, CRC(13702bbf) SHA1(564bd59bf30531577321bbe0583609a5ceecfbad) )
	ROM_LOAD( "b05302_hack03.rom",   0x0800000, 0x0800000, CRC(b9f75120) SHA1(b087cfd02cbaa22e3c4732b5fc50a385f2d5d4a7) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m05301.rom",   0x400000, 0x400000, CRC(86ec83bc) SHA1(067cb7ec449eacd1f49298f45a364368934db5dd) )
ROM_END

ROM_START( oldsplushack04 ) //oldsplushm
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p05301_hack04.rom",   0x100000, 0x400000, CRC(488b20f5) SHA1(7e1e1cbc5e062bf3bce59d13f6a579cddc6cd4ef) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "oldsplus_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0x800000, "user1", ROMREGION_ERASE00 )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t05301.rom",   0x180000, 0x800000, CRC(8257bbb0) SHA1(b48067b7e7081a15fddf21739b641d677c2df3d9) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a05301.rom",   0x0000000, 0x0800000, CRC(57946fd2) SHA1(5d79bc71a1881f3099821a9b255a5f271e0eeff6) )
	ROM_LOAD( "a05302_hack01.rom",   0x0800000, 0x0800000, CRC(65acdbf7) SHA1(008346d963e67e858d91a9cd1206e125e2eddec6) )
	ROM_LOAD( "a05303.rom",   0x1000000, 0x0800000, CRC(13475d85) SHA1(4683a3bf304fdc15ffb1c61b7957ad68b023fa33) )
	ROM_LOAD( "a05304_hack01.rom",   0x1800000, 0x0800000, CRC(b92e10a4) SHA1(f6e323187a46ff72dbba0618b0abd1b05208ba1a) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b05301_hack01.rom",   0x0000000, 0x0800000, CRC(7aedd210) SHA1(f974d4800d61dcdf779b52c190384ec3c6ef12e5) )
	ROM_LOAD( "b05302_hack01.rom",   0x0800000, 0x0800000, CRC(059d9ad8) SHA1(9375a9c71fdde23eabd302c116b4e50a766d9d27) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m05301_hack01.rom",   0x400000, 0x400000, CRC(61a1413c) SHA1(f5a739226dfb95005543aa6cf7132b6fec3d8b43) )
ROM_END

ROM_START( oldsplushack05 ) //oldsplusnr
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p05301_hack05.rom",   0x100000, 0x400000, CRC(ce6893ae) SHA1(486f6dcc5c99538a489a663409ddd1a15ea7c8f6) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "oldsplus_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0x800000, "user1", ROMREGION_ERASE00 )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t05301.rom",   0x180000, 0x800000, CRC(8257bbb0) SHA1(b48067b7e7081a15fddf21739b641d677c2df3d9) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a05301_hack03.rom",   0x0000000, 0x0800000, CRC(3d3125ff) SHA1(fef80d4ae377e391e2fb7a296fb4b49df42a6687) )
	ROM_LOAD( "a05302_hack03.rom",   0x0800000, 0x0800000, CRC(4ed9028c) SHA1(9c4038097b225c331618dbf0dac3fb9d37a25e9f) )
	ROM_LOAD( "a05303.rom",   0x1000000, 0x0800000, CRC(13475d85) SHA1(4683a3bf304fdc15ffb1c61b7957ad68b023fa33) )
	ROM_LOAD( "a05304.rom",   0x1800000, 0x0800000, CRC(f03ef7a6) SHA1(c18b1b622b430d5e031e65daa6819b84c3e12ef5) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b05301_hack03.rom",   0x0000000, 0x0800000, CRC(13702bbf) SHA1(564bd59bf30531577321bbe0583609a5ceecfbad) )
	ROM_LOAD( "b05302_hack03.rom",   0x0800000, 0x0800000, CRC(b9f75120) SHA1(b087cfd02cbaa22e3c4732b5fc50a385f2d5d4a7) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m05301.rom",   0x400000, 0x400000, CRC(86ec83bc) SHA1(067cb7ec449eacd1f49298f45a364368934db5dd) )
ROM_END

ROM_START( oldsplushack06 ) //oldsplusnew
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p05301_hack06.rom",   0x100000, 0x400000, CRC(a3cd1b1d) SHA1(d9db407ebb15b826f6c57f9b938d1258e98aac12) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "oldsplus_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0x800000, "user1", ROMREGION_ERASE00 )

	ROM_REGION( 0xc00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t05301.rom",   0x180000, 0x800000, CRC(8257bbb0) SHA1(b48067b7e7081a15fddf21739b641d677c2df3d9) )

	ROM_REGION16_LE( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a05301.rom",   0x0000000, 0x0800000, CRC(57946fd2) SHA1(5d79bc71a1881f3099821a9b255a5f271e0eeff6) )
	ROM_LOAD( "a05302.rom",   0x0800000, 0x0800000, CRC(3459a0b8) SHA1(94ab6f980b5582f1db9bb12019d03f0b6e0a06df) )
	ROM_LOAD( "a05303.rom",   0x1000000, 0x0800000, CRC(13475d85) SHA1(4683a3bf304fdc15ffb1c61b7957ad68b023fa33) )
	ROM_LOAD( "a05304.rom",   0x1800000, 0x0800000, CRC(f03ef7a6) SHA1(c18b1b622b430d5e031e65daa6819b84c3e12ef5) )

	ROM_REGION16_LE( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b05301.rom",   0x0000000, 0x0800000, CRC(fd98f503) SHA1(02046ab1aa89f63bff149003d9d61776e025a92a) )
	ROM_LOAD( "b05302.rom",   0x0800000, 0x0800000, CRC(9f6094a8) SHA1(69f6f2003ab975eae13ea6b5c2ffa40df6e6bdf6) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m05301.rom",   0x400000, 0x400000, CRC(86ec83bc) SHA1(067cb7ec449eacd1f49298f45a364368934db5dd) )
ROM_END

 /********************
 Oriental Legend Plus
***********************/

ROM_START( orlegendhack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack01.160",    0x100000, 0x200000, CRC(a4db5335) SHA1(1e5de478e5304fc4b5a7575d7d5eff944965e816) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100_hack01.u8",     0x180000, 0x400000, CRC(d69009ed) SHA1(ac5834a082d7912fe9b36722490446d13ca23c83) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100_hack01.u5",     0x0000000, 0x400000, CRC(1bc35928) SHA1(a7898a69fab119501b6107214d35c5971ba4dac2) )
	ROM_LOAD( "a0101_hack01.u6",     0x0400000, 0x400000, CRC(97cf4912) SHA1(0c7a908b09cddf4ba5887cedc599c6197b325b9c) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100_hack01.u9",     0x0000000, 0x400000, CRC(5a914019) SHA1(8fa854f8546e09e60dabd80647974eefe4971cac) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack02 ) //orlegndcyxgl
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack02.160",    0x100000, 0x200000, CRC(f9b2b569) SHA1(858bbf0ad12a099b2d88b6b6cad27ba32da32abf) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100_hack01.u8",     0x180000, 0x400000, CRC(d69009ed) SHA1(ac5834a082d7912fe9b36722490446d13ca23c83) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100_hack01.u5",     0x0000000, 0x400000, CRC(1bc35928) SHA1(a7898a69fab119501b6107214d35c5971ba4dac2) )
	ROM_LOAD( "a0101_hack01.u6",     0x0400000, 0x400000, CRC(97cf4912) SHA1(0c7a908b09cddf4ba5887cedc599c6197b325b9c) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100_hack01.u9",     0x0000000, 0x400000, CRC(5a914019) SHA1(8fa854f8546e09e60dabd80647974eefe4971cac) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack03 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack03.160",    0x100000, 0x200000, CRC(182adf6b) SHA1(8dafdf92c47c54b597957cc01dca27f27cdae163) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100_hack01.u8",     0x180000, 0x400000, CRC(d69009ed) SHA1(ac5834a082d7912fe9b36722490446d13ca23c83) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100_hack01.u5",     0x0000000, 0x400000, CRC(1bc35928) SHA1(a7898a69fab119501b6107214d35c5971ba4dac2) )
	ROM_LOAD( "a0101_hack01.u6",     0x0400000, 0x400000, CRC(97cf4912) SHA1(0c7a908b09cddf4ba5887cedc599c6197b325b9c) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100_hack01.u9",     0x0000000, 0x400000, CRC(5a914019) SHA1(8fa854f8546e09e60dabd80647974eefe4971cac) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack04 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack04.160",    0x100000, 0x200000, CRC(0708d53e) SHA1(8e78acd3946509ec22465a7d6f79b22e86cc5977) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100_hack01.u8",     0x180000, 0x400000, CRC(d69009ed) SHA1(ac5834a082d7912fe9b36722490446d13ca23c83) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100_hack01.u5",     0x0000000, 0x400000, CRC(1bc35928) SHA1(a7898a69fab119501b6107214d35c5971ba4dac2) )
	ROM_LOAD( "a0101_hack01.u6",     0x0400000, 0x400000, CRC(97cf4912) SHA1(0c7a908b09cddf4ba5887cedc599c6197b325b9c) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100_hack01.u9",     0x0000000, 0x400000, CRC(5a914019) SHA1(8fa854f8546e09e60dabd80647974eefe4971cac) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack05 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack05.160",    0x100000, 0x200000, CRC(f1c9ad47) SHA1(d7caedf53b7aac4ab108d1f6e68c9a71695e582c) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack06 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack06.160",    0x100000, 0x200000, CRC(eeea25b9) SHA1(310a61bd676140ae2e9712f37f8c4137932926aa) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100_hack01.u8",     0x180000, 0x400000, CRC(d69009ed) SHA1(ac5834a082d7912fe9b36722490446d13ca23c83) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100_hack01.u5",     0x0000000, 0x400000, CRC(1bc35928) SHA1(a7898a69fab119501b6107214d35c5971ba4dac2) )
	ROM_LOAD( "a0101_hack01.u6",     0x0400000, 0x400000, CRC(97cf4912) SHA1(0c7a908b09cddf4ba5887cedc599c6197b325b9c) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100_hack01.u9",     0x0000000, 0x400000, CRC(5a914019) SHA1(8fa854f8546e09e60dabd80647974eefe4971cac) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack07 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack07.160",    0x100000, 0x200000, CRC(100e1078) SHA1(38f70bfcb74a5dd07a324945edfd73eb7dbccefd) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack08 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack08.160",    0x100000, 0x200000, CRC(f0bd1554) SHA1(1109b1a5cc16985cb41f4ad642001ac45f30a917) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack09 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack09.160",    0x100000, 0x200000, CRC(607ca005) SHA1(ecc04e2ea02209b3641103ded47a90e3df0c14ac) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack10 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack10.160",    0x100000, 0x200000, CRC(a2b42ca4) SHA1(89bb3363004d134185180294eb568a738cdba06a) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack11 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack11.160",    0x100000, 0x200000, CRC(011a8274) SHA1(3a32a8914a6a90f0a24dabef26bf7dba94b9e3e6) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack12 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0103_hack12.s160",    0x100000, 0x200000, CRC(da526a83) SHA1(7572f1cc07061f017c1d009a509efbdae6b1e176) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100_hack01.u8",     0x180000, 0x400000, CRC(d69009ed) SHA1(ac5834a082d7912fe9b36722490446d13ca23c83) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100_hack01.u5",     0x0000000, 0x400000, CRC(1bc35928) SHA1(a7898a69fab119501b6107214d35c5971ba4dac2) )
	ROM_LOAD( "a0101_hack01.u6",     0x0400000, 0x400000, CRC(97cf4912) SHA1(0c7a908b09cddf4ba5887cedc599c6197b325b9c) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100_hack01.u9",     0x0000000, 0x400000, CRC(5a914019) SHA1(8fa854f8546e09e60dabd80647974eefe4971cac) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack13 ) //orlegndcqgp
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack13.s160",  0x100000, 0x200000, CRC(0a7601b6) SHA1(3cb2f17deb6041a54a568127766a153fac4c7bc7) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100_hack01.u8",     0x180000, 0x400000, CRC(d69009ed) SHA1(ac5834a082d7912fe9b36722490446d13ca23c83) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100_hack01.u5",     0x0000000, 0x400000, CRC(1bc35928) SHA1(a7898a69fab119501b6107214d35c5971ba4dac2) )
	ROM_LOAD( "a0101_hack01.u6",     0x0400000, 0x400000, CRC(97cf4912) SHA1(0c7a908b09cddf4ba5887cedc599c6197b325b9c) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100_hack01.u9",     0x0000000, 0x400000, CRC(5a914019) SHA1(8fa854f8546e09e60dabd80647974eefe4971cac) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack14 ) //orlegend1v4
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack14.s160",  0x100000, 0x200000, CRC(aec1ba2d) SHA1(84ebfbe1e11f93bb2c6a91cea3bf4ba2ac4c7f41) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack15 ) //orlegndcjhcs
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack15.s160",  0x100000, 0x200000, CRC(b022ede5) SHA1(6787c8135297fb71c2594fa4d392e96b4ad51783) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack16 ) //orlegendl
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack16.s160",  0x100000, 0x200000, CRC(7b0dfe13) SHA1(3b6d6709a62965bdc3669cbcbeefe753f3d007f2) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack17 ) //orlegendne
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0101_hack17.s160",  0x100000, 0x200000, CRC(61d386aa) SHA1(db2422145e9484585d8f732f93a25ffe8ae6a9bf) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

ROM_START( orlegendhack18 ) //orlegendyj
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0103_hack18.s160",  0x100000, 0x200000, CRC(8f4aa6b1) SHA1(59d116f719941c9421af2447673c7a51a2475444) )

	ROM_REGION( 0x800000, "tiles",  0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0100.u8",     0x180000, 0x400000, CRC(61425e1e) SHA1(20753b86fc12003cfd763d903f034dbba8010b32) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0100.u5",     0x0000000, 0x400000, CRC(8b3bd88a) SHA1(42db3a60c6ba9d83ebe2008c8047d094027f65a7) )
	ROM_LOAD( "a0101.u6",     0x0400000, 0x400000, CRC(3b9e9644) SHA1(5b95ec1d25c3bc3504c93547f5adb5ce24376405) )
	ROM_LOAD( "a0102.u7",     0x0800000, 0x400000, CRC(069e2c38) SHA1(9bddca8c2f5bd80f4abe4e1f062751736dc151dd) )
	ROM_LOAD( "a0103.u8",     0x0c00000, 0x400000, CRC(4460a3fd) SHA1(cbebdb65c17605853f7d0b298018dd8801a25a58) )
	ROM_LOAD( "a0104.u11",    0x1000000, 0x400000, CRC(5f8abb56) SHA1(6c1ddc0309862a141aa0c0f63b641aec9257aaee) )
	ROM_LOAD( "a0105.u12",    0x1400000, 0x400000, CRC(a17a7147) SHA1(44eeb43c6b0ebb829559a20ae357383fbdeecd82) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0100.u9",     0x0000000, 0x400000, CRC(69d2e48c) SHA1(5b5f759007264c07b3b39be8e03a713698e1fc2a) )
	ROM_LOAD( "b0101.u10",    0x0400000, 0x400000, CRC(0d587bf3) SHA1(5347828b0a6e4ddd7a263663d2c2604407e4d49c) )
	ROM_LOAD( "b0102.u15",    0x0800000, 0x400000, CRC(43823c1e) SHA1(e10a1a9a81b51b11044934ff702e35d8d7ab1b08) )

	ROM_REGION( 0x600000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0100.u1",     0x400000, 0x200000, CRC(e5c36c83) SHA1(50c6f66770e8faa3df349f7d68c407a7ad021716) )
ROM_END

 /*************
 The Gladiator
****************/

ROM_START( thegladhack01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v101_u6.rom",       0x100000, 0x080000, CRC(f799e866) SHA1(dccc3c903357c40c3cf85ac0ae8fc12fb0f853a6) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "theglad_igs027a_execute_only_area", 0x0000, 0x00188, NO_DUMP )
	ROM_LOAD( "thegladpcb_igs027a_v100_japan.bin", 0x0188, 0x3e78, CRC(d7f06e2d) SHA1(9c3aca7a487f5329d84731e2c63d5ed591bf9d24) )

	ROM_REGION32_LE( 0x800000, "user1", 0 )
	ROM_LOAD( "u2_hack01.rom", 0x000000, 0x200000,  CRC(e9ebb722) SHA1(03a4f4c9541b7c605381537f4490b236d6993f2f) )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t04601.u33",   0x180000, 0x800000, CRC(e5dab371) SHA1(2e3c93958eb0326b6b84b95c2168626f26bbac76) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a04601.u2",    0x0000000, 0x0800000,  CRC(d9b2e004) SHA1(8e1882b800fe9f12d7d49303e7417ba5b6f8ef85) )
	ROM_LOAD( "a04602.u4",    0x0800000, 0x0800000,  CRC(14f22308) SHA1(7fad54704e8c97eab723f53dfb50fb3e7bb606d2) )
	ROM_LOAD( "a04603.u6",    0x1000000, 0x0800000,  CRC(8f621e17) SHA1(b0f87f378e0115d0c95017ca0f1b0d508827a7c6) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b04601.u11",   0x0000000, 0x0800000, CRC(ee72bccf) SHA1(73c25fe659f6c903447066e4ef83d2f580449d76) )
	ROM_LOAD( "b04602.u12",   0x0800000, 0x0400000, CRC(7dba9c38) SHA1(a03d509274e8f6a500a7ebe2da5aab8bed4e7f2f) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "w04601.u1",    0x400000, 0x800000, CRC(5f15ddb3) SHA1(c38dcef8e06802a84e42a7fc9fa505475fc3ac65) )
ROM_END

ROM_START( thegladhack02 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "v101_u6.rom",       0x100000, 0x080000, CRC(f799e866) SHA1(dccc3c903357c40c3cf85ac0ae8fc12fb0f853a6) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "theglad_igs027a_execute_only_area", 0x0000, 0x00188, NO_DUMP )
	ROM_LOAD( "thegladpcb_igs027a_v100_japan.bin", 0x0188, 0x3e78, CRC(d7f06e2d) SHA1(9c3aca7a487f5329d84731e2c63d5ed591bf9d24) )

	ROM_REGION32_LE( 0x800000, "user1", 0 )
	ROM_LOAD( "u2_hack02.rom", 0x000000, 0x200000,  CRC(8ec8724b) SHA1(bd11dc3be6e1277e612a7c159f5a4f5d84742b12) )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t04601.u33",   0x180000, 0x800000, CRC(e5dab371) SHA1(2e3c93958eb0326b6b84b95c2168626f26bbac76) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a04601.u2",    0x0000000, 0x0800000,  CRC(d9b2e004) SHA1(8e1882b800fe9f12d7d49303e7417ba5b6f8ef85) )
	ROM_LOAD( "a04602.u4",    0x0800000, 0x0800000,  CRC(14f22308) SHA1(7fad54704e8c97eab723f53dfb50fb3e7bb606d2) )
	ROM_LOAD( "a04603.u6",    0x1000000, 0x0800000,  CRC(8f621e17) SHA1(b0f87f378e0115d0c95017ca0f1b0d508827a7c6) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b04601.u11",   0x0000000, 0x0800000, CRC(ee72bccf) SHA1(73c25fe659f6c903447066e4ef83d2f580449d76) )
	ROM_LOAD( "b04602.u12",   0x0800000, 0x0400000, CRC(7dba9c38) SHA1(a03d509274e8f6a500a7ebe2da5aab8bed4e7f2f) )

	ROM_REGION( 0x1000000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "w04601.u1",    0x400000, 0x800000, CRC(5f15ddb3) SHA1(c38dcef8e06802a84e42a7fc9fa505475fc3ac65) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// The Killing Blade
HACK( 1998, killbldhack01,  killbld,   pgm_022_025_killbld,killbld,  pgm_022_025_state,   killbld,    ROT0,   "DDJ",  "The Killing Blade (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, killbldhack02,  killbld,   pgm_022_025_killbld,killbld,  pgm_022_025_state,   killbld,    ROT0,   "DDJ",  "The Killing Blade (Always Have Super Move)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, killbldhack03,  killbld,   pgm_022_025_killbld,killbld,  pgm_022_025_state,   killbld,    ROT0,   "DDJ",  "The Killing Blade (Easy Move)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, killbldhack04,  killbld,   pgm_022_025_killbld,killbld,  pgm_022_025_state,   killbld,    ROT0,   "hack", "The Killing Blade (Simplified 2018-08-24)", MACHINE_IMPERFECT_SOUND | MACHINE_SUPPORTS_SAVE )
// The Killing Blade Plus
HACK( 2005, killbldphack01, killbldp,  pgm_arm_type3,      pgm,      pgm_arm_type3_state, killbldp,   ROT0,   "DDJ",  "The Killing Blade Plus (Easy Move)", MACHINE_IMPERFECT_SOUND | MACHINE_SUPPORTS_SAVE )
HACK( 2005, killbldphack02, killbldp,  pgm_arm_type3,      pgm,      pgm_arm_type3_state, killbldp,   ROT0,   "DDJ",  "The Killing Blade Plus (Always Have Super Move)",  MACHINE_NOT_WORKING | MACHINE_IMPERFECT_SOUND | MACHINE_SUPPORTS_SAVE )
// Knights of Valour
HACK( 2018, kovhack01,      kov,       pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour (The Latest 2018-8-12)", MACHINE_SUPPORTS_SAVE )
// Knights of Valour 2 Plus
HACK( 2001, kov2phack01,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Gai Shi Wu Shen First Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kov2phack02,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Qun Mo Luan Wu Fu Mo Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kov2phack03,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Ming Yue Hua Cai)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kov2phack04,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Tian Wai Shen Bing)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kov2phack05,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (King of the world 2016-10-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kov2phack06,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Full attack version 2016-11-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kov2phack07,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Gods weapon version 2016-11-23)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kov2phack08,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (World Warriors 2016 2018-07-27)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kov2phack09,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Kowloon Legend 2018-09-24)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kov2phack10,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Ching Ying 2019-01-05)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kov2phack11,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Shenbing Mushuang 2020-05-07)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kov2phack12,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Heroes of the World 2020-05-13)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kov2phack13,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (Dragon And Phoenix Dance 2020-05-13)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kov2phack14,    kov2p,     pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2p,      ROT0,   "hack", "Knights of Valour 2 Plus (God of War Musou 2020-09-14)", MACHINE_SUPPORTS_SAVE )
// Knights of Valour 2
HACK( 2000, kov2hack01,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Ex Super Version 1)", MACHINE_SUPPORTS_SAVE )
HACK( 2000, kov2hack02,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Ex Super Version 2)", MACHINE_SUPPORTS_SAVE )
HACK( 2000, kov2hack03,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Ex Super Version 3)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kov2hack04,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Gods and Soldiers will be the second edition 2016-01-16)",  MACHINE_SUPPORTS_SAVE )
HACK( 2017, kov2hack05,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Frosty Edition 2017-02-04)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kov2hack06,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Full Attack Version 2018-07-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kov2hack07,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Enhanced Edition 2017-08-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kov2hack08,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Frosty Edition 2 2017-06-28)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kov2hack09,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Enemy Reset Edition 2017-06-17)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kov2hack10,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Items 2017-06-09)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kov2hack11,     kov2,      pgm_arm_type2,      kov2,     pgm_arm_type2_state, kov2,       ROT0,   "hack", "Knights of Valour 2 (Green Edition 2020-10-15)", MACHINE_SUPPORTS_SAVE )
// Knights of Valour Plus
HACK( 2016, kovplushack01,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 1.0 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovplushack02,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 1.1 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack03,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 2 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovplushack04,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 3 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack05,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 3.1 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack06,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 4 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovplushack07,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 4.1 Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovplushack08,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 5 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack09,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 6 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2017, kovplushack10,  kovplus,   pgm_arm_type1_sim,  sango_ch, pgm_arm_type1_state, kovboot,    ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 7 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovplushack11,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 8 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovplushack12,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 9 Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovplushack13,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Small Soldiers Series 9.1 Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 2012, kovplushack14,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Authentic 2012 Nightmare Version Swim Gather Version)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovplushack15,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Dragon And The World)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovplushack16,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Really War Of The Flies Fluttering The Three Kingdoms West Tour Fix It)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack17,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus 2015 (Wars Musou 2015 2015-08-09)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack18,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Musou 2015 Unparalleled Purgatory 2015-12-23)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack19,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Authentic Moxie Legend 2015-12-23)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack20,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Qin Double Love 2015 Enhanced Edition 2015-08-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovplushack21,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (God of War Musou 2016 2016-01-30)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovplushack22,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Piano Double Boss)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovplushack23,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Revived 2016 Edition 2016-04-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kovplushack24,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Three Kingdoms Ares St Dragon World Test 2017-07-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kovplushack25,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Dragon Finch Update 2017-05-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kovplushack26,  kovplus,   pgm_arm_type1_sim,  sango_ch, pgm_arm_type1_state, kovboot,    ROT0,   "hack", "Knights of Valour Plus (Warfare Nightmare Falls +S 201 2017-06-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2012, kovplushack27,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Authentic 2012 God Of War ST 1V4)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovplushack28,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Authentic Plus Eight Gods Edition 2016-08-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack29,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Hegemony 2015-07-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack30,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Liu Bei Legend New Edition 2015-07-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack31,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Single Ride Savior Mode Hard 2015-02-04)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, kovplushack32,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Qin Double Love 2015-02-13)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovplushack33,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (1V4 2016-10-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovplushack34,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (God of War 2016 Hero 2 New Edition 2016-09-27)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kovplushack35,  kovplus,   pgm_arm_type1_sim,  sango_ch, pgm_arm_type1_state, kovboot,    ROT0,   "hack", "Knights of Valour Plus (One Kings 1 2017-05-15)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovplushack36,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus 2012 (Days Next 2018 New Edition 2018-05-18)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovplushack37,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Single Ride Savior 2018 Final Edition 2018-03-08)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovplushack38,  kovplus,   pgm_arm_type1_sim,  sango_ch, pgm_arm_type1_state, kovboot,    ROT0,   "hack", "Knights of Valour Plus (2017 Nightmare God of War Version 1.1 2019-04-15)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovplushack39,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (1V4 2018-01-30)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovplushack40,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Nightmare Kings Edition 2019-10-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovplushack41,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus 2012 (God of War ST Uranus Edition 2020-01-10)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovplushack42,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Edition 2020-01-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovplushack43,  kovplus,   pgm_arm_type1_sim,  sango_ch, pgm_arm_type1_state, kovboot,    ROT0,   "hack", "Knights of Valour Plus (2012S Edition 2019-09-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kovplushack44,  kovplus,   pgm_arm_type1_sim,  sango_ch, pgm_arm_type1_state, kovboot,    ROT0,   "hack", "Knights of Valour Plus (Authentic 1V8 Edition 2017-02-18)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovplushack45,  kovplus,   pgm_arm_type1_sim,  sango_ch, pgm_arm_type1_state, kovboot,    ROT0,   "hack", "Knights of Valour Plus 2012 (God of War 2019 2019-05-22)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovplushack46,  kovplus,   pgm_arm_type1_sim,  sango_ch, pgm_arm_type1_state, kovboot,    ROT0,   "hack", "Knights of Valour Plus 2012 (Nightmare Ares 2019-04-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovplushack47,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (God of War Edition ST 2018-07-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovplushack48,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus (Tu Tuo legend plus 2020-05-15)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovplushack49,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus 2012 (Warriors Edition 2020-09-10)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovplushack50,  kovplus,   pgm_arm_type1_sim,  sango,    pgm_arm_type1_state, kov,        ROT0,   "hack", "Knights of Valour Plus 2012 (Heroes Dance 2020 2020-09-10)", MACHINE_SUPPORTS_SAVE )
// Knights of Valour Super Heroes
HACK( 1999, kovshhack01,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Three Wars Chaotic Situation 3 Mode)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovshhack02,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Sanguozhanji Revival Really Troubled Heroes 2016-02-15)", MACHINE_SUPPORTS_SAVE )  
HACK( 2015, kovshhack03,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Sanguozhanji Revival New Heroes Troubled Times 2015-08-24)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack04,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Xie Feng Tianchi (V106) B3 Revised Version)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack05,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Chaos Of The World 3.25)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack06,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Storm Clouds Re-Launch Version Of The Military Will Compete For The Beta2 Miracle Of The Three Kingdoms)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack07,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (The World Is In Turmoil)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack08,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Liu Bei Legend New Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack09,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Storm Rising Fusion Version - Qunxiong Hegemony Beta 8)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack10,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (True And Chaotic Days 5.12 Beautiful Revision)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack11,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Wu Shen Legend Challenge Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack12,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Bloody Clouds)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack13,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Evil Feng Xiong, The Military Commander (0524 Version))", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack14,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Original Character Generals Score Enhancement)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack15,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (2000 Boss Zero Chun Li Fire Fighting)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack16,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (True Evil Spirits Dance - God of War Legend Beta 2)", MACHINE_SUPPORTS_SAVE )
HACK( 1999, kovshhack17,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Random Level Edition)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kovshhack18,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Fengyun 2017 Edition 2017-01-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2014, kovshhack19,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Wang Zhe Zhi Zhan Double Dragon 2014-05-27)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovshhack20,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (Fengyun Street Fighter 2016 2016-10-06)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshhack21,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (The Central Plains 2019-01-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshhack22,    kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovsh,      ROT0,   "hack", "Knights of Valour Super Heroes (The Legend of Ares 2019 2019-08-03)", MACHINE_SUPPORTS_SAVE )
// Quanhuang Sanguo Tebie Ban
HACK( 1999, kovqhsghack01,  kovsh,     pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovqhsgs,   ROT0,   "hack", "Quanhuang Sanguo Tebie Ban (Three Kingdoms Wars)", MACHINE_SUPPORTS_SAVE )
// Knights of Valour Super Heroes Plus
HACK( 2004, kovshphack01,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Three Troubled Times King Of Fighter Version)", MACHINE_SUPPORTS_SAVE )
HACK( 2004, kovshphack02,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Q Version Of The Three Kingdoms)", MACHINE_SUPPORTS_SAVE )
HACK( 2004, kovshphack03,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Rockman G)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovshphack04,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Luan Shi Xiao Xiong Ne Zhe Huo Lun 2018-01-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, kovshphack05,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Full Attack Edition 2017-10-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, kovshphack06,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Nightmare Edition 2016-07-01)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovshphack07,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Chaotic hero god cloud VS dog god 2018-08-27)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack08,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Qunxiong New Version 2019-02-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack09,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (The Road to Survival True King Version 2020-01-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack10,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Warriors Warlords 2019-11-20)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack11,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Warriors Edition 2020-03-13)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack12,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Musou Combo Edition 2019-12-13)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack13,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Warriors World War II 2019-12-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack14,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Central Plains Gold Edition 2019-10-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack15,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Heavenly Kingdom Protoss 2020-01-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack16,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Heroes Of The Destroyer 2019-05-01)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack17,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Taiping Chaos Legend Edition 2019-03-21)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack18,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Gone With The Wind Warriors 2019 2019-03-19)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack19,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Ginger Iron Horse 2019-12-26)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack20,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (God of War 2019-07-20)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack21,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Green Edition 2020-07-31)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, kovshphack22,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Journey To The West 2019 2019-08-18)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovshphack23,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Luan Shi Ying Xiong Qiu Sheng Qun Xiong Zhu Lu Edition 2018-09-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, kovshphack24,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Luan Shi Ying Xiong Qiu Sheng Zhi Lu Tian Wang Edition 2018-09-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2012, kovshphack25,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Heavenly King Edition 2012-11-17)", MACHINE_SUPPORTS_SAVE )
HACK( 2012, kovshphack26,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (KOF Pirated Version 3 2012-08-03)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack27,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (EX 2020-02-06)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack28,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (The Best Firepower In 2020 2020-02-06)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack29,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (The Best firepower 1V4 2020-02-06)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack30,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (2020 Seven Stars Reincarnation Athena Edition 2020-02-06)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack31,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Heavenly King Edition 2.7s 2020-02-11)", MACHINE_SUPPORTS_SAVE )
HACK( 2004, kovshphack32,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshxas,   ROT0,   "hack", "Knights of Valour Super Heroes Plus (Luan Shi Ying Xiong 20XX-0X-0X)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, kovshphack33,   kovshp,    pgm_arm_type1,      kovsh,    pgm_arm_type1_state, kovshp,     ROT0,   "hack", "Knights of Valour Super Heroes Plus (Random Edition 2020-09-17)", MACHINE_SUPPORTS_SAVE )
//Martial Masters
HACK( 2001, martmasthack01, martmast,  pgm_arm_type2,      martmast, pgm_arm_type2_state, martmast,   ROT0,   "0 Days", "Martial Masters (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
HACK( 2016, martmasthack02, martmast,  pgm_arm_type2,      martmast, pgm_arm_type2_state, martmast,   ROT0,   "DDJ",   "Martial Masters (All Super Move)", MACHINE_SUPPORTS_SAVE ) //press ac or bd
HACK( 2016, martmasthack03, martmast,  pgm_arm_type2,      martmast, pgm_arm_type2_state, martmast,   ROT0,   "DDJ",   "Martial Masters (Always Have Super Move)", MACHINE_SUPPORTS_SAVE )
//Oriental Legend Super
HACK( 2020, oldshack01,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Hack of Xi You Shi E Zhuan Super 2020-01-11)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack02,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (West S Heavenly Double Devil)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack03,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Boss Battle Mode)", MACHINE_SUPPORTS_SAVE )//
HACK( 1998, oldshack04,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Enemy Wukong)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack05,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Dance Soul 2011 West S Is The Most Powerful Version)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack06,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Magician Zhao Yun Fast Gas Storage Version)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack07,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Magic Legend B2 Repair)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack08,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (New Group Of Magical Dance 2011 Edition B1)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack09,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Heavenly Double Devil)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack10,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Haunted Street Fighter Version)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack11,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Sun Wukong Changed The Devil)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack12,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Journey To The West Super Nightmare Survival 2015 Tour Edition)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack13,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Ghost Sword Tour)", MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack14,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (West S Heaven And Earth Double Magic Edition)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 1998, oldshack15,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Unlimited Energy And Speed For All)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
HACK( 2009, oldshack16,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (The King Of Fighters Westward B2 Repair Most 2009-08-17)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, oldshack17,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Wu Kong Da Luan Dou 2015-01-29)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, oldshack18,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (The Immortal Devil Dance 2015 Enhanced Version 2015-01-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2009, oldshack19,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Super Dance Macabre 2009 Edition 2009-12-29)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, oldshack20,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Super Edition Volvo Edition 2017-02-14)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, oldshack21,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Remix 2017-03-07)", MACHINE_SUPPORTS_SAVE )
HACK( 2015, oldshack22,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Dream Survival 2015 Final 2015-06-07)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
HACK( 2017, oldshack23,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Wu Zhi Shuang Mo 2017-03-07)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, oldshack24,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Nightmare Survival 2015 2018-08-23)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
HACK( 2015, oldshack25,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (No match, Travel Edition 2015-02-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, oldshack26,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Yuanling 2019-01-29)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, oldshack27,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Street Fighter 2 2017-09-29)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, oldshack28,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Promise of Magic 2019-09-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, oldshack29,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Zero 2020-07-12)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, oldshack30,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Dreaming of Spiritual Mountain 2020-08-04)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, oldshack31,     olds,      pgm_028_025_ol,     olds,     pgm_028_025_state,   olds,       ROT0,   "hack", "Oriental Legend Special (Return of the Great Saint 2020-10-14)", MACHINE_SUPPORTS_SAVE )
// Oriental Legend Special Plus
HACK( 2018, oldsplushack01, oldsplus,  pgm_arm_type1_sim,  oldsplus, pgm_arm_type1_state, oldsplus,   ROT0,   "hack", "Oriental Legend 2 (Yellow Hat Version 2018-08-02)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, oldsplushack02, oldsplus,  pgm_arm_type1_sim,  oldsplus, pgm_arm_type1_state, oldsplus,   ROT0,   "hack", "Oriental Legend 2 (Combo Plus 2019-07-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, oldsplushack03, oldsplus,  pgm_arm_type1_sim,  oldsplus, pgm_arm_type1_state, oldsplus,   ROT0,   "hack", "Oriental Legend 2 (Xinqun Magic Ranwu 208 2019-12-31)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, oldsplushack04, oldsplus,  pgm_arm_type1_sim,  oldsplus, pgm_arm_type1_state, oldsplus,   ROT0,   "hack", "Oriental Legend 2 (Yellow Hat Version 2020-03-20)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, oldsplushack05, oldsplus,  pgm_arm_type1_sim,  oldsplus, pgm_arm_type1_state, oldsplus,   ROT0,   "hack", "Oriental Legend 2 (Qun Mo Luan Wu New 208 Revision 2020-06-09)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, oldsplushack06, oldsplus,  pgm_arm_type1_sim,  oldsplus, pgm_arm_type1_state, oldsplus,   ROT0,   "hack", "Oriental Legend 2 (One Key Edition 215 2020-12-10)", MACHINE_SUPPORTS_SAVE )
// Oriental Legend Plus
HACK( 1997, orlegendhack01, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Super Return 2 Funny Innocence Plus)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack02, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Super Return 5 Very Skynet EX-3)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack03, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Super Return 5 Very Skynet EX-3 Easy)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack04, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Super World - Red Dragon Dance 2)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack05, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Thousands Of Machines Change. Variety Unparalleled 3)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack06, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Return Of Evil Winds Beta 3)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack07, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Full-Featured Pig Journey)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack08, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Full Featured Dragon Horse)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack09, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Full Color Little Dragon Girl)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack10, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Full Role Of Sand Wu Net)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack11, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Full Role Of The Monkey King)", MACHINE_SUPPORTS_SAVE )
HACK( 1997, orlegendhack12, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Super Return 5 Very Skynet Ex)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, orlegendhack13, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Westward Full Attack Enhanced Version 2017-03-06)", MACHINE_SUPPORTS_SAVE )
HACK( 2017, orlegendhack14, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Westward Tour 1v4 2017-03-19)", MACHINE_SUPPORTS_SAVE )
HACK( 2019, orlegendhack15, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Five Elements 2019-09-16)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, orlegendhack16, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (4v1 Simplified Edition 2018-06-06)", MACHINE_SUPPORTS_SAVE )
HACK( 2018, orlegendhack17, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Note version 2018-06-03)", MACHINE_SUPPORTS_SAVE )
HACK( 2020, orlegendhack18, orlegend,  pgm_asic3,          orlegend, pgm_asic3_state,     orlegend,   ROT0,   "hack", "Oriental Legend (Marriage Together Edition 2020-05-15)", MACHINE_SUPPORTS_SAVE )
// The Gladiator
HACK( 2017, thegladhack01,  theglad,  pgm_arm_type3,       theglad, pgm_arm_type3_state,  theglada,   ROT0,   "hack", "The Gladiator (Excalibur 2017-10-11)", MACHINE_IMPERFECT_SOUND | MACHINE_SUPPORTS_SAVE )
HACK( 2020, thegladhack02,  theglad,  pgm_arm_type3,       theglad, pgm_arm_type3_state,  theglada,   ROT0,   "hack", "The Gladiator (Full Attack Enhanced Edition 2020 2020-09-18)", MACHINE_IMPERFECT_SOUND | MACHINE_SUPPORTS_SAVE )
