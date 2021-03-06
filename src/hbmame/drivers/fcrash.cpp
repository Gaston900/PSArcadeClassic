// license:BSD-3-Clause
// copyright-holders:David Haywood
/* Final Crash & other CPS1 bootlegs */

/*

Final Crash is a bootleg of Final Fight

Final Fight is by Capcom and runs on CPS1 hardware
The bootleg was manufactured by Playmark of Italy

this driver depends heavily on cps1.c, but has been
kept apart in an attempt to keep cps1.c clutter free

Sound is very different from CPS1.

---

Final Crash (bootleg of final fight)

1x 68k
1x z80
2x ym2203
2x oki5205
1x osc 10mhz
1x osc 24mhz

eproms:
1.bin sound eprom
from 2.bin to 9.bin program eproms
10.bin to 25.bin gfx eproms

---

kodb has various graphical issues, mainly with old info not being cleared away.
Also, it should be using a vblank irq value of 4. This triggers the following bootleg read/writes;
 - IN1 is read at 0x992000
 - IN0 is read of 0x992008
 - dips continue to be read at 0x80001a
 - sound command is wrote at 0x992006
 - scroll 1Y is wrote at 0x980000
 - scroll 1X is wrote at 0x980002
 - scroll 2Y is wrote at 0x980004
 - scroll 2X is wrote at 0x980006
 - scroll 3Y is wrote at 0x980008
 - scroll 3X is wrote at 0x98000a
 - the layer enable and layer mask writes continue at 0x98000c and 0x980020-2

These read/writes are identical to those used by a Knights of the Round bootleg which uses the all sf2mdt sound
hardware. This set is currently non-working.

This also prevents the game from toggling the sprite address at m_cps_a_regs[0], similar to other bootlegs.
Currently the game is working somewhat, but only using the code left over from the original. If anyone wants to
do any development work on the set, (eg, find the sprite clearing issue), then this should be changed as the game
likely won't write any sprite clearing values otherwise.

None of this is hooked up currently due to issues with row scroll on the scroll2 layer.



Status of each game:
--------------------
cawingb2, cawingbl: ok

dinopic: no sound

dinopic2: no sound, one bad gfx rom. Copying 8.bin from dinopic fixes it.

fcrash, kodb: old sprites show on next screen. Patch used.

kodb: gems are missing.

knightsb: sprites are entangled with the front layer.

punipic, punipic2: no sound. Problems in Central Park. Patches used.

punipic3: same as punipic, and doors are missing.

sf2m1: crowd is missing. Plane's tail comes off a bit. Patch used.

sf2mdt, sf2mdta: ok

sgyxz: garbage left behind. A priority problem can be seen in 3rd demo where
       the fighters walk through the crowd instead of behind.

slampic: no sound. A priority problem between sprites and crowd.

*/

#include "emu.h"
#include "cpu/z80/z80.h"
#include "cpu/m68000/m68000.h"
#include "includes/cps1.h"
#include "sound/ymopm.h"
#include "sound/ymopn.h"
#include "sound/msm5205.h"
#include "sound/okim6295.h"
#include "machine/eepromser.h"
#include "speaker.h"

void cps_state::fcrash_soundlatch_w(offs_t offset, u16 data, u16 mem_mask)
{
	if (ACCESSING_BITS_0_7)
	{
		m_soundlatch->write(data & 0xff);
		m_audiocpu->set_input_line(0, HOLD_LINE);
	}
}

void cps_state::cawingbl_soundlatch_w(offs_t offset, u16 data, u16 mem_mask)
{
	if (ACCESSING_BITS_8_15)
	{
		m_soundlatch->write(data  >> 8);
		m_audiocpu->set_input_line(0, HOLD_LINE);
		machine().scheduler().boost_interleave(attotime::zero, attotime::from_usec(50)); /* boost the interleave or some voices get dropped */
	}
}

void cps_state::fcrash_snd_bankswitch_w(u8 data)
{
	m_msm_1->set_output_gain(0, (data & 0x08) ? 0.0 : 1.0);
	m_msm_2->set_output_gain(0, (data & 0x10) ? 0.0 : 1.0);

	membank("bank1")->set_entry(data & 0x07);
}

void cps_state::sf2mdt_snd_bankswitch_w(u8 data)
{
	m_msm_1->set_output_gain(0, (data & 0x20) ? 0.0 : 1.0);
	m_msm_2->set_output_gain(0, (data & 0x10) ? 0.0 : 1.0);

	membank("bank1")->set_entry(data & 0x07);
}

void cps_state::knightsb_snd_bankswitch_w(u8 data)
{
	m_msm_1->set_output_gain(0, (data & 0x20) ? 0.0 : 1.0);
	m_msm_2->set_output_gain(0, (data & 0x10) ? 0.0 : 1.0);

	membank("bank1")->set_entry(data & 0x0f);
}

WRITE_LINE_MEMBER(cps_state::m5205_int1)
{
	m_msm_1->data_w(m_sample_buffer1 & 0x0f);
	m_sample_buffer1 >>= 4;
	m_sample_select1 ^= 1;
	if (m_sample_select1 == 0)
		m_audiocpu->pulse_input_line(INPUT_LINE_NMI, attotime::zero);
}

WRITE_LINE_MEMBER(cps_state::m5205_int2)
{
	m_msm_2->data_w(m_sample_buffer2 & 0x0f);
	m_sample_buffer2 >>= 4;
	m_sample_select2 ^= 1;
}



void cps_state::fcrash_msm5205_0_data_w(u8 data)
{
	m_sample_buffer1 = data;
}

void cps_state::fcrash_msm5205_1_data_w(u8 data)
{
	m_sample_buffer2 = data;
}

/* not verified */
#define CPS1_ROWSCROLL_OFFS     (0x20/2)    /* base of row scroll offsets in other RAM */

void cps_state::dinopic_layer_w(offs_t offset, u16 data)
{
	switch (offset)
	{
	case 0x00:
		m_cps_a_regs[0x0e / 2] = data;
		break;
	case 0x01:
		m_cps_a_regs[0x0c / 2] = data;
		break;
	case 0x02:
		m_cps_a_regs[0x12 / 2] = data;
		m_cps_a_regs[CPS1_ROWSCROLL_OFFS] = data; /* row scroll start */
		break;
	case 0x03:
		m_cps_a_regs[0x10 / 2] = data;
		break;
	case 0x04:
		m_cps_a_regs[0x16 / 2] = data;
		break;
	case 0x05:
		m_cps_a_regs[0x14 / 2] = data;
		break;
	default:
		logerror("%s: Unknown layer cmd %X %X\n",machine().describe_context(),offset<<1,data);

	}
}

void cps_state::dinopic_layer2_w(u16 data)
{
	m_cps_a_regs[0x06 / 2] = data;
}

void cps_state::kodb_layer_w(offs_t offset, u16 data)
{
	/* layer enable and mask 1&2 registers are written here - passing them to m_cps_b_regs for now for drawing routines */
	if (offset == 0x06)
		m_cps_b_regs[m_layer_enable_reg / 2] = data;
	else
	if (offset == 0x10)
		m_cps_b_regs[m_layer_mask_reg[1] / 2] = data;
	else
	if (offset == 0x11)
		m_cps_b_regs[m_layer_mask_reg[2] / 2] = data;
}

void cps_state::knightsb_layer_w(offs_t offset, u16 data)
{
	switch (offset)
	{
	case 0x00:
		m_cps_a_regs[0x0e / 2] = data;
		break;
	case 0x01:
		m_cps_a_regs[0x0c / 2] = data;
		break;
	case 0x02:
		m_cps_a_regs[0x12 / 2] = data;
		m_cps_a_regs[CPS1_ROWSCROLL_OFFS] = data; /* row scroll start */
		break;
	case 0x03:
		m_cps_a_regs[0x10 / 2] = data;
		break;
	case 0x04:
		m_cps_a_regs[0x16 / 2] = data;
		break;
	case 0x05:
		m_cps_a_regs[0x14 / 2] = data;
		break;
	case 0x06:
		{
			switch (data)
			{
			case 0x0000:
			case 0x001f:
			case 0x00ff:
				data = 0x12f2;
				break;
			case 0x2000:
				data = 0x06f2;
				break;
			case 0xa000:
				data = 0x24d0;
				break;
			default:
				printf ("Unknown control word = %X\n",data);
				data = 0x12c0;
			}
		m_cps_b_regs[m_layer_enable_reg / 2] = data;
		break;
		}
	case 0x10:
		m_cps_b_regs[m_layer_mask_reg[1] / 2] = data;
		break;
	case 0x11:
		m_cps_b_regs[m_layer_mask_reg[2] / 2] = data;
		break;
	case 0x12:
		m_cps_b_regs[m_layer_mask_reg[3] / 2] = data;
	}
}

void cps_state::punipic_layer_w(offs_t offset, u16 data)
{
	switch (offset)
	{
	case 0x00:
		m_cps_a_regs[0x0e / 2] = data;
		break;
	case 0x01:
		m_cps_a_regs[0x0c / 2] = data;
		break;
	case 0x02:
		m_cps_a_regs[0x12 / 2] = data;
		m_cps_a_regs[CPS1_ROWSCROLL_OFFS] = data; /* row scroll start */
		break;
	case 0x03:
		m_cps_a_regs[0x10 / 2] = data + 0xffc0;
		break;
	case 0x04:
		m_cps_a_regs[0x16 / 2] = data;
		break;
	case 0x05:
		m_cps_a_regs[0x14 / 2] = data;
		break;
	case 0x06:
			switch (data)
			{
			case 0x14:
			case 0x54:
				m_cps_a_regs[0x04 / 2] = 0x9100;
				break;
			case 0x24:
			case 0x64:
				m_cps_a_regs[0x04 / 2] = 0x90c0;
				break;
			case 0x3c:
			case 0x7c:
				m_cps_a_regs[0x04 / 2] = 0x9180;
				break;
			}

			m_cps_a_regs[0x08 / 2] = m_mainram[0xdb90 / 2]; // fixes split objects
			break;
	case 0x07:
		// unknown
		break;
	default:
		logerror("%s: Unknown layer cmd %X %X\n",machine().describe_context(),offset<<1,data);

	}
}

void cps_state::mtwinsb_layer_w(offs_t offset, u16 data)
{
	m_cps_a_regs[0x06 / 2] = 0x9100; // bit of a hack - the game never writes this, but does need it

	switch (offset)
	{
	case 0x00:
		m_cps_a_regs[0x0e / 2] = data;
		break;
	case 0x01:
		m_cps_a_regs[0x0c / 2] = data - 0x3e;
		break;
	case 0x02:
		m_cps_a_regs[0x12 / 2] = data;
		m_cps_a_regs[CPS1_ROWSCROLL_OFFS] = data; /* row scroll start */
		break;
	case 0x03:
		m_cps_a_regs[0x10 / 2] = data - 0x3c;
		break;
	case 0x04:
		m_cps_a_regs[0x16 / 2] = data;
		break;
	case 0x05:
		m_cps_a_regs[0x14 / 2] = data - 0x40;
		break;
	default:
		logerror("%s: Unknown layer cmd %X %X\n",machine().describe_context(),offset<<1,data);

	}
}

void cps_state::sf2m1_layer_w(offs_t offset, u16 data)
{
	switch (offset)
	{
	case 0x00:
		m_cps_a_regs[0x0e / 2] = data;
		break;
	case 0x01:
		m_cps_a_regs[0x0c / 2] = data;
		break;
	case 0x02:
		m_cps_a_regs[0x12 / 2] = data;
		m_cps_a_regs[CPS1_ROWSCROLL_OFFS] = data; /* row scroll start */
		break;
	case 0x03:
		m_cps_a_regs[0x10 / 2] = data;
		break;
	case 0x04:
		m_cps_a_regs[0x16 / 2] = data;
		break;
	case 0x05:
		m_cps_a_regs[0x14 / 2] = data;
		break;
	case 0x06:
			switch (data)
			{
			case 0:
				data = 0x078e;
				break;
			case 1:
				data = 0x12c0;
				break;
			case 2:
				data = 0x06ce;
				break;
			case 3:
				data = 0x09ce;
				break;
			case 4:
				data = 0x12ce;
				break;
			case 5:
				data = 0x0b4e;
				break;
			}
			[[fallthrough]];
	case 0xb3:
			m_cps_b_regs[m_layer_enable_reg / 2] = data;
			break;
	case 0x0b:
	case 0x1b:
		m_cps_a_regs[0x06 / 2] = data;
		break;
	default:
		logerror("%s: Unknown layer cmd %X %X\n",machine().describe_context(),offset<<1,data);

	}
}

void cps_state::sf2mdt_layer_w(offs_t offset, u16 data)
{
	/* layer enable and scroll registers are written here - passing them to m_cps_b_regs and m_cps_a_regs for now for drawing routines
	the scroll layers aren't buttery smooth, due to the lack of using the row scroll address tables in the rendering code, this is also
	supported by the fact that the game doesn't write the table address anywhere */

	switch (offset)
	{
	case 0x06:
		m_cps_a_regs[0x14 / 2] = data + 0xffce; /* scroll 3x */
		break;
	case 0x07:
		m_cps_a_regs[0x16 / 2] = data; /* scroll 3y */
		break;
	case 0x08:
		m_cps_a_regs[0x10 / 2] = data + 0xffce; /* scroll 2x */
		break;
	case 0x09:
		m_cps_a_regs[0x0c / 2] = data + 0xffca; /* scroll 1x */
		break;
	case 0x0a:
		m_cps_a_regs[0x12 / 2] = data; /* scroll 2y */
		m_cps_a_regs[CPS1_ROWSCROLL_OFFS] = data; /* row scroll start */
		break;
	case 0x0b:
		m_cps_a_regs[0x0e / 2] = data; /* scroll 1y */
		break;
	case 0x26:
		m_cps_b_regs[m_layer_enable_reg / 2] = data;
	}
}

void cps_state::sf2mdta_layer_w(offs_t offset, u16 data)
{
	/* layer enable and scroll registers are written here - passing them to m_cps_b_regs and m_cps_a_regs for now for drawing routines
	the scroll layers aren't buttery smooth, due to the lack of using the row scroll address tables in the rendering code, this is also
	supported by the fact that the game doesn't write the table address anywhere */

	switch (offset)
	{
	case 0x06:
		m_cps_a_regs[0x0c / 2] = data + 0xffbe; /* scroll 1x */
		break;
	case 0x07:
		m_cps_a_regs[0x0e / 2] = data; /* scroll 1y */
		break;
	case 0x08:
		m_cps_a_regs[0x14 / 2] = data + 0xffce; /* scroll 3x */
		break;
	case 0x09:
		m_cps_a_regs[0x12 / 2] = data; /* scroll 2y */
		m_cps_a_regs[CPS1_ROWSCROLL_OFFS] = data; /* row scroll start */
		break;
	case 0x0a:
		m_cps_a_regs[0x10 / 2] = data + 0xffce; /* scroll 2x */
		break;
	case 0x0b:
		m_cps_a_regs[0x16 / 2] = data; /* scroll 3y */
		break;
	case 0x26:
		m_cps_b_regs[m_layer_enable_reg / 2] = data;
	}
}

void cps_state::slampic_layer_w(offs_t offset, u16 data)
{
	switch (offset)
	{
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x03:
	case 0x04:
	case 0x05:
		dinopic_layer_w(offset, data);
		break;
	case 0x06: // scroll 2 base
		m_cps_a_regs[0x04/2] = data << 4;
		break;
	}
}


void cps_state::fcrash_update_transmasks()
{
	int i;

	for (i = 0; i < 4; i++)
	{
		int mask;

		/* Get transparency registers */
		if (m_layer_mask_reg[i])
			mask = m_cps_b_regs[m_layer_mask_reg[i] / 2] ^ 0xffff;
		else
			mask = 0xffff;  /* completely transparent if priority masks not defined (mercs, qad) */

		m_bg_tilemap[0]->set_transmask(i, mask, 0x8000);
		m_bg_tilemap[1]->set_transmask(i, mask, 0x8000);
		m_bg_tilemap[2]->set_transmask(i, mask, 0x8000);
	}
}

void cps_state::fcrash_render_sprites( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect )
{
	int pos;
	int base = m_sprite_base / 2;
	int num_sprites = m_gfxdecode->gfx(2)->elements();
	int last_sprite_offset = 0x1ffc;
	u16 *sprite_ram = m_gfxram;
	u16 tileno,colour,xpos,ypos;
	bool flipx, flipy;

	/* if we have separate sprite ram, use it */
	if (m_bootleg_sprite_ram) sprite_ram = m_bootleg_sprite_ram.get();

	/* get end of sprite list marker */
	for (pos = 0x1ffc - base; pos >= 0x0000; pos -= 4)
		if (sprite_ram[base + pos - 1] == m_sprite_list_end_marker) last_sprite_offset = pos;

	/* If we are using bootleg sprite ram, the index must be less than 0x2000 */
	if (((base + last_sprite_offset) < 0x2000) || (!m_bootleg_sprite_ram))
	{
		for (pos = last_sprite_offset; pos >= 0x0000; pos -= 4)
		{
			tileno = sprite_ram[base + pos];
			if (tileno >= num_sprites) continue; /* don't render anything outside our tiles */
			xpos   = sprite_ram[base + pos + 2] & 0x1ff;
			ypos   = sprite_ram[base + pos - 1] & 0x1ff;
			flipx  = BIT(sprite_ram[base + pos + 1], 5);
			flipy  = BIT(sprite_ram[base + pos + 1], 6);
			colour = sprite_ram[base + pos + 1] & 0x1f;
			ypos   = 256 - ypos - 16;
			xpos   = xpos + m_sprite_x_offset + 49;

			if (flip_screen())
				m_gfxdecode->gfx(2)->prio_transpen(bitmap, cliprect, tileno, colour, !flipx, !flipy, 512-16-xpos, 256-16-ypos, screen.priority(), 2, 15);
			else
				m_gfxdecode->gfx(2)->prio_transpen(bitmap, cliprect, tileno, colour, flipx, flipy, xpos, ypos, screen.priority(), 2, 15);
		}
	}
}

void cps_state::fcrash_render_layer( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int layer, int primask )
{
	switch (layer)
	{
		case 0:
			fcrash_render_sprites(screen, bitmap, cliprect);
			break;
		case 1:
		case 2:
		case 3:
			m_bg_tilemap[layer - 1]->draw(screen, bitmap, cliprect, TILEMAP_DRAW_LAYER1, primask);
			break;
	}
}

void cps_state::fcrash_render_high_layer( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int layer )
{
	bitmap_ind16 dummy_bitmap;

	switch (layer)
	{
		case 0:
			/* there are no high priority sprites */
			break;
		case 1:
		case 2:
		case 3:
			m_bg_tilemap[layer - 1]->draw(screen, dummy_bitmap, cliprect, TILEMAP_DRAW_LAYER0, 1);
			break;
	}
}

void cps_state::fcrash_build_palette()
{
	int offset;

	// all the bootlegs seem to write the palette offset as usual
	int palettebase = (m_cps_a_regs[0x0a / 2] << 8) & 0x1ffff;

	for (offset = 0; offset < 32 * 6 * 16; offset++)
	{
		int palette = m_gfxram[palettebase / 2 + offset];
		int r, g, b, bright;

		// from my understanding of the schematics, when the 'brightness'
		// component is set to 0 it should reduce brightness to 1/3

		bright = 0x0f + ((palette >> 12) << 1);

		r = ((palette >> 8) & 0x0f) * 0x11 * bright / 0x2d;
		g = ((palette >> 4) & 0x0f) * 0x11 * bright / 0x2d;
		b = ((palette >> 0) & 0x0f) * 0x11 * bright / 0x2d;

		m_palette->set_pen_color (offset, rgb_t(r, g, b));
	}
}

u32 cps_state::screen_update_fcrash(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	int layercontrol, l0, l1, l2, l3;
	int videocontrol = m_cps_a_regs[0x22 / 2];

	flip_screen_set(videocontrol & 0x8000);

	layercontrol = m_cps_b_regs[m_layer_enable_reg / 2];

	/* Get video memory base registers */
	cps1_get_video_base();

	/* Build palette */
	fcrash_build_palette();

	fcrash_update_transmasks();

	m_bg_tilemap[0]->set_scrollx(0, m_scroll1x - m_layer_scroll1x_offset);
	m_bg_tilemap[0]->set_scrolly(0, m_scroll1y);

	if (videocontrol & 0x01)    /* linescroll enable */
	{
		int scrly = -m_scroll2y;
		int i;
		int otheroffs;

		m_bg_tilemap[1]->set_scroll_rows(1024);

		otheroffs = m_cps_a_regs[CPS1_ROWSCROLL_OFFS];

		for (i = 0; i < 256; i++)
			m_bg_tilemap[1]->set_scrollx((i - scrly) & 0x3ff, m_scroll2x + m_other[(i + otheroffs) & 0x3ff]);
	}
	else
	{
		m_bg_tilemap[1]->set_scroll_rows(1);
		m_bg_tilemap[1]->set_scrollx(0, m_scroll2x - m_layer_scroll2x_offset);
	}
	m_bg_tilemap[1]->set_scrolly(0, m_scroll2y);
	m_bg_tilemap[2]->set_scrollx(0, m_scroll3x - m_layer_scroll3x_offset);
	m_bg_tilemap[2]->set_scrolly(0, m_scroll3y);


	/* turn all tilemaps on regardless of settings in get_video_base() */
	/* write a custom get_video_base for this bootleg hardware? */
	m_bg_tilemap[0]->enable(1);
	m_bg_tilemap[1]->enable(1);
	m_bg_tilemap[2]->enable(1);

	/* Blank screen */
	bitmap.fill(0xbff, cliprect);

	screen.priority().fill(0, cliprect);
	l0 = (layercontrol >> 0x06) & 03;
	l1 = (layercontrol >> 0x08) & 03;
	l2 = (layercontrol >> 0x0a) & 03;
	l3 = (layercontrol >> 0x0c) & 03;

	fcrash_render_layer(screen, bitmap, cliprect, l0, 0);

	if (l1 == 0)
		fcrash_render_high_layer(screen, bitmap, cliprect, l0);

	fcrash_render_layer(screen, bitmap, cliprect, l1, 0);

	if (l2 == 0)
		fcrash_render_high_layer(screen, bitmap, cliprect, l1);

	fcrash_render_layer(screen, bitmap, cliprect, l2, 0);

	if (l3 == 0)
		fcrash_render_high_layer(screen, bitmap, cliprect, l2);

	fcrash_render_layer(screen, bitmap, cliprect, l3, 0);

	return 0;
}


void cps_state::knightsb_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800001).portr("IN1");  /* Player input ports */
	map(0x800002,0x800003).portr("IN2");  /* Player 3 controls */
	map(0x800004,0x800005).nopw();  // writes 0000 here
	map(0x800006,0x800007).w(FUNC(cps_state::fcrash_soundlatch_w));  /* Sound command */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x800030,0x800037).nopw();  //AM_WRITE(cps1_coinctrl_w) only writes bit 15
	map(0x800100,0x80013f).ram().share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).ram().share("cps_b_regs");  /* CPS-B custom */
	map(0x800180,0x800181).nopw();  //AM_WRITE(cps1_soundlatch2_w)   /* Sound timer fade */
	map(0x880000,0x880001).nopw();  // unknown
	map(0x900000,0x93ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0x980000,0x98002f).w(FUNC(cps_state::knightsb_layer_w));
	map(0x990000,0x990001).nopw();  // same as 880000
	map(0xff0000,0xffffff).ram();
}

void cps_state::dinopic_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800007).portr("IN1");  /* Player input ports */
	map(0x800006,0x800007).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x800180,0x800181).nopr(); //w(FUNC(cps_state::fcrash_soundlatch_w)).lr8("sc", [this] { return 0xff; });  /* Sound command */
	map(0x800222,0x800223).w(FUNC(cps_state::dinopic_layer2_w));
	map(0x880000,0x880001).nopw();  // always 0
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0x980000,0x98000b).w(FUNC(cps_state::dinopic_layer_w));
	map(0xf18000,0xf19fff).ram();
	map(0xf1c000,0xf1c001).portr("IN2");  /* Player 3 controls (later games) */
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000,0xffffff).ram();
}

void cps_state::fcrash_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800030,0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).ram().share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).ram().share("cps_b_regs");  /* CPS-B custom */
	map(0x880000,0x880001).portr("IN1");  /* Player input ports */
	map(0x880006,0x880007).w(FUNC(cps_state::fcrash_soundlatch_w));  /* Sound command */
	map(0x880008,0x88000f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x890000,0x890001).nopw();  // palette related?
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xff0000,0xffffff).ram();
}

void cps_state::mtwinsb_map(address_map &map)
{
	map(0x000000, 0x3fffff).rom();
	map(0x800000, 0x800001).portr("IN1");
	map(0x800006, 0x800007).w(FUNC(cps_state::cps1_soundlatch_w));
	map(0x800018, 0x80001f).r(FUNC(cps_state::cps1_dsw_r));
	map(0x800030, 0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100, 0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");
	map(0x800140, 0x80017f).rw(FUNC(cps_state::cps1_cps_b_r), FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x980000, 0x98000b).w(FUNC(cps_state::mtwinsb_layer_w));
	map(0x900000, 0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xff0000, 0xffffff).ram().share("mainram");
}

void cps_state::punipic_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800007).portr("IN1");  /* Player input ports */
	map(0x800006,0x800007).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x880000,0x880001).nopw();  // same as 98000C
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0x980000,0x98000f).w(FUNC(cps_state::punipic_layer_w));
	map(0x990000,0x990001).nopw();  // unknown
	map(0x991000,0x991017).nopw();  // unknown
	map(0xf18000,0xf19fff).ram();
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000,0xffffff).ram().share("mainram");
}

void cps_state::sf2m1_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800007).portr("IN1");  /* Player input ports */
	map(0x800006,0x800007).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x800012,0x800013).r(FUNC(cps_state::cps1_in2_r));  /* Buttons 4,5,6 for both players */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x800180,0x800181).nopw();  // only once at boot, for 80010c
	map(0x800188,0x80018f).w(FUNC(cps_state::cps1_soundlatch2_w));  /* Sound timer fade */
	map(0x880000,0x880001).nopw();  // unknown
	map(0x900000,0x93ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0x980000,0x9801ff).w(FUNC(cps_state::sf2m1_layer_w));
	map(0x990000,0x990001).nopw();  // same as 880000
	map(0xff0000,0xffffff).ram();
}

void cps_state::sf2mdt_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x708100,0x7081ff).w(FUNC(cps_state::sf2mdta_layer_w));
	map(0x70c000,0x70c001).portr("IN1");
	map(0x70c008,0x70c009).portr("IN2");
	map(0x70c018,0x70c01f).r(FUNC(cps_state::cps1_hack_dsw_r));
	map(0x70c106,0x70c107).w(FUNC(cps_state::cawingbl_soundlatch_w));
	map(0x70d000,0x70d001).nopw();  // writes FFFF
	//AM_RANGE(0x800030, 0x800031) AM_WRITE(cps1_coinctrl_w)
	map(0x800100,0x80013f).ram().share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).ram().share("cps_b_regs");  /* CPS-B custom */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xff0000,0xffffff).ram();
}

void cps_state::sf2b_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x708100,0x7081ff).w(FUNC(cps_state::sf2mdta_layer_w));
	map(0x70c000,0x70c001).portr("IN1");
	map(0x70c008,0x70c009).portr("IN2");
	map(0x70c018,0x70c01f).r(FUNC(cps_state::cps1_hack_dsw_r));
	map(0x70c106,0x70c107).w(FUNC(cps_state::cawingbl_soundlatch_w));
	map(0x70d000,0x70d001).nopw();  // writes FFFF
	//AM_RANGE(0x800030, 0x800031) AM_WRITE(cps1_coinctrl_w)
	map(0x800100,0x80013f).ram().share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");  /* CPS-B custom */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xff0000,0xffffff).ram();
}

void cps_state::sgyxz_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800030,0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).ram().share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).ram().share("cps_b_regs");  /* CPS-B custom */
	map(0x880000,0x880001).portr("IN1");  /* Player input ports */
	map(0x880006,0x88000d).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x88000e,0x88000f).w(FUNC(cps_state::cps1_soundlatch_w));
	map(0x880e78,0x880e79).r(FUNC(cps_state::cps1_in2_r));  /* Player 3 controls (later games) */
	map(0x890000,0x890001).w(FUNC(cps_state::cps1_soundlatch2_w));
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000,0xffffff).ram();
}

void cps_state::slampic_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800006,0x800007).nopw();  //AM_WRITE(cps1_soundlatch2_w)
	map(0x800000,0x800007).portr("IN1");  /* Player input ports */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x880000,0x880001).nopw();  //AM_WRITE(cps1_soundlatch_w)    /* Sound command */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0x980000,0x98000d).w(FUNC(cps_state::slampic_layer_w));
	map(0xf00000,0xf0ffff).r(FUNC(cps_state::qsound_rom_r));  /* Slammasters protection */
	map(0xf18000,0xf19fff).ram();
	map(0xf1c000,0xf1c001).portr("IN2");  /* Player 3 controls (later games) */
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xf1f000,0xf1ffff).noprw();  // writes 0 to range, then reads F1F6EC
	map(0xff0000,0xffffff).ram();
}

void cps_state::sound_map(address_map &map) {
	map(0x0000,0x7fff).rom();
	map(0x8000,0xbfff).bankr("bank1");
	map(0xd000,0xd7ff).ram();
	map(0xd800,0xd801).rw("ym1",FUNC(ym2203_device::read),FUNC(ym2203_device::write));
	map(0xdc00,0xdc01).rw("ym2",FUNC(ym2203_device::read),FUNC(ym2203_device::write));
	map(0xe000,0xe000).w(FUNC(cps_state::fcrash_snd_bankswitch_w));
	map(0xe400,0xe400).r(m_soundlatch,FUNC(generic_latch_8_device::read));
	map(0xe800,0xe800).w(FUNC(cps_state::fcrash_msm5205_0_data_w));
	map(0xec00,0xec00).w(FUNC(cps_state::fcrash_msm5205_1_data_w));
}

void cps_state::kodb_sound_map(address_map &map) {
	map(0x0000,0x7fff).rom();
	map(0x8000,0xbfff).bankr("bank1");
	map(0xd000,0xd7ff).ram();
	map(0xe000,0xe001).rw("2151",FUNC(ym2151_device::read),FUNC(ym2151_device::write));
	map(0xe400,0xe400).rw("oki",FUNC(okim6295_device::read),FUNC(okim6295_device::write));
	map(0xe800,0xe800).r(m_soundlatch,FUNC(generic_latch_8_device::read));
}

void cps_state::sf2mdt_z80map(address_map &map) {
	map(0x0000,0x7fff).rom();
	map(0x8000,0xbfff).bankr("bank1");
	map(0xd000,0xd7ff).ram();
	map(0xd800,0xd801).rw("2151",FUNC(ym2151_device::read),FUNC(ym2151_device::write));
	map(0xdc00,0xdc00).r(m_soundlatch,FUNC(generic_latch_8_device::read));
	map(0xe000,0xe000).w(FUNC(cps_state::sf2mdt_snd_bankswitch_w));
	map(0xe400,0xe400).w(FUNC(cps_state::fcrash_msm5205_0_data_w));
	map(0xe800,0xe800).w(FUNC(cps_state::fcrash_msm5205_1_data_w));
}

void cps_state::knightsb_z80map(address_map &map) {
	map(0x0000,0x7fff).rom();
	map(0x8000,0xbfff).bankr("bank1");
	map(0xcffe,0xcfff).nopw();  // writes lots of data
	map(0xd000,0xd7ff).ram();
	map(0xd800,0xd801).rw("2151",FUNC(ym2151_device::read),FUNC(ym2151_device::write));
	map(0xdc00,0xdc00).r(m_soundlatch,FUNC(generic_latch_8_device::read));
	map(0xe000,0xe000).w(FUNC(cps_state::knightsb_snd_bankswitch_w));
	map(0xe400,0xe400).w(FUNC(cps_state::fcrash_msm5205_0_data_w));
	map(0xe800,0xe800).w(FUNC(cps_state::fcrash_msm5205_1_data_w));
}

void cps_state::sgyxz_sound_map(address_map &map) {
	map(0x0000,0x7fff).rom();
	map(0x8000,0xbfff).bankr("bank1");
	map(0xd000,0xd7ff).ram();
	map(0xf000,0xf001).rw("2151",FUNC(ym2151_device::read),FUNC(ym2151_device::write));
	map(0xf002,0xf002).rw("oki",FUNC(okim6295_device::read),FUNC(okim6295_device::write));
	map(0xf004,0xf004).w(FUNC(cps_state::cps1_snd_bankswitch_w));
	map(0xf006,0xf006).w(FUNC(cps_state::cps1_oki_pin7_w));  /* controls pin 7 of OKI chip */
	map(0xf008,0xf008).r(m_soundlatch,FUNC(generic_latch_8_device::read));
	map(0xf00a,0xf00a).r(m_soundlatch2,FUNC(generic_latch_8_device::read));
}


#define CPS1_COINAGE_1 \
	PORT_DIPNAME( 0x07, 0x07, DEF_STR( Coin_A ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 4C_1C ) ) \
	PORT_DIPSETTING(    0x01, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x02, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x07, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x06, DEF_STR( 1C_2C ) ) \
	PORT_DIPSETTING(    0x05, DEF_STR( 1C_3C ) ) \
	PORT_DIPSETTING(    0x04, DEF_STR( 1C_4C ) ) \
	PORT_DIPSETTING(    0x03, DEF_STR( 1C_6C ) ) \
	PORT_DIPNAME( 0x38, 0x38, DEF_STR( Coin_B ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 4C_1C ) ) \
	PORT_DIPSETTING(    0x08, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x10, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x38, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_2C ) ) \
	PORT_DIPSETTING(    0x28, DEF_STR( 1C_3C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 1C_4C ) ) \
	PORT_DIPSETTING(    0x18, DEF_STR( 1C_6C ) )


#define CPS1_COINAGE_2(diploc) \
	PORT_DIPNAME( 0x07, 0x07, DEF_STR( Coinage ) ) PORT_DIPLOCATION(diploc ":1,2,3") \
	PORT_DIPSETTING(    0x00, DEF_STR( 4C_1C ) ) \
	PORT_DIPSETTING(    0x01, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x02, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x07, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x06, DEF_STR( 1C_2C ) ) \
	PORT_DIPSETTING(    0x05, DEF_STR( 1C_3C ) ) \
	PORT_DIPSETTING(    0x04, DEF_STR( 1C_4C ) ) \
	PORT_DIPSETTING(    0x03, DEF_STR( 1C_6C ) )

#define CPS1_COINAGE_3(diploc) \
	PORT_DIPNAME( 0x07, 0x07, DEF_STR( Coin_A ) ) PORT_DIPLOCATION(diploc ":1,2,3") \
	PORT_DIPSETTING(    0x01, DEF_STR( 4C_1C ) ) \
	PORT_DIPSETTING(    0x02, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x03, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x00, "2 Coins/1 Credit (1 to continue)" ) \
	PORT_DIPSETTING(    0x07, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x06, DEF_STR( 1C_2C ) ) \
	PORT_DIPSETTING(    0x05, DEF_STR( 1C_3C ) ) \
	PORT_DIPSETTING(    0x04, DEF_STR( 1C_4C ) ) \
	PORT_DIPNAME( 0x38, 0x38, DEF_STR( Coin_B ) ) PORT_DIPLOCATION(diploc ":4,5,6") \
	PORT_DIPSETTING(    0x08, DEF_STR( 4C_1C ) ) \
	PORT_DIPSETTING(    0x10, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x18, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x00, "2 Coins/1 Credit (1 to continue)" ) \
	PORT_DIPSETTING(    0x38, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_2C ) ) \
	PORT_DIPSETTING(    0x28, DEF_STR( 1C_3C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 1C_4C ) )

#define CPS1_DIFFICULTY_1(diploc) \
	PORT_DIPNAME( 0x07, 0x04, DEF_STR( Difficulty ) ) PORT_DIPLOCATION(diploc ":1,2,3") \
	PORT_DIPSETTING(    0x07, "1 (Easiest)" ) \
	PORT_DIPSETTING(    0x06, "2" ) \
	PORT_DIPSETTING(    0x05, "3" ) \
	PORT_DIPSETTING(    0x04, "4 (Normal)" ) \
	PORT_DIPSETTING(    0x03, "5" ) \
	PORT_DIPSETTING(    0x02, "6" ) \
	PORT_DIPSETTING(    0x01, "7" ) \
	PORT_DIPSETTING(    0x00, "8 (Hardest)" )

#define CPS1_DIFFICULTY_2(diploc) \
	PORT_DIPNAME( 0x07, 0x07, DEF_STR( Difficulty ) ) PORT_DIPLOCATION(diploc ":1,2,3") \
	PORT_DIPSETTING(    0x04, "1 (Easiest)" ) \
	PORT_DIPSETTING(    0x05, "2" ) \
	PORT_DIPSETTING(    0x06, "3" ) \
	PORT_DIPSETTING(    0x07, "4 (Normal)" ) \
	PORT_DIPSETTING(    0x03, "5" ) \
	PORT_DIPSETTING(    0x02, "6" ) \
	PORT_DIPSETTING(    0x01, "7" ) \
	PORT_DIPSETTING(    0x00, "8 (Hardest)" )


static INPUT_PORTS_START( fcrash )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("DSWA")
	CPS1_COINAGE_1
	PORT_DIPNAME( 0x40, 0x40, "2 Coins to Start, 1 to Continue" )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPUNUSED( 0x80, IP_ACTIVE_LOW )

	PORT_START("DSWB")
	PORT_DIPNAME( 0x07, 0x04, "Difficulty Level 1" )
	PORT_DIPSETTING(    0x07, DEF_STR( Easiest ) )      // "01"
	PORT_DIPSETTING(    0x06, DEF_STR( Easier ) )       // "02"
	PORT_DIPSETTING(    0x05, DEF_STR( Easy ) )     // "03"
	PORT_DIPSETTING(    0x04, DEF_STR( Normal ) )       // "04"
	PORT_DIPSETTING(    0x03, DEF_STR( Medium ) )       // "05"
	PORT_DIPSETTING(    0x02, DEF_STR( Hard ) )     // "06"
	PORT_DIPSETTING(    0x01, DEF_STR( Harder ) )       // "07"
	PORT_DIPSETTING(    0x00, DEF_STR( Hardest ) )      // "08"
	PORT_DIPNAME( 0x18, 0x10, "Difficulty Level 2" )
	PORT_DIPSETTING(    0x18, DEF_STR( Easy ) )     // "01"
	PORT_DIPSETTING(    0x10, DEF_STR( Normal ) )       // "02"
	PORT_DIPSETTING(    0x08, DEF_STR( Hard ) )     // "03"
	PORT_DIPSETTING(    0x00, DEF_STR( Hardest ) )      // "04"
	PORT_DIPNAME( 0x60, 0x60, DEF_STR( Bonus_Life ) )
	PORT_DIPSETTING(    0x60, "100k" )
	PORT_DIPSETTING(    0x40, "200k" )
	PORT_DIPSETTING(    0x20, "100k and every 200k" )
	PORT_DIPSETTING(    0x00, DEF_STR( None ) )
	PORT_DIPUNUSED( 0x80, IP_ACTIVE_LOW )

	PORT_START("DSWC")
	PORT_DIPNAME( 0x03, 0x03, DEF_STR( Lives ) )
	PORT_DIPSETTING(    0x00, "1" )
	PORT_DIPSETTING(    0x03, "2" )
	PORT_DIPSETTING(    0x02, "3" )
	PORT_DIPSETTING(    0x01, "4" )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Free_Play ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, "Freeze" )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Flip_Screen ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x00, DEF_STR( Demo_Sounds ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Allow_Continue ) )
	PORT_DIPSETTING(    0x40, DEF_STR( No ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Yes ) )
	PORT_DIPNAME( 0x80, 0x80, "Game Mode")
	PORT_DIPSETTING(    0x80, "Game" )
	PORT_DIPSETTING(    0x00, DEF_STR( Test ) )

	PORT_START("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1) PORT_NAME ("P1 Button 3 (Cheat)")
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2) PORT_NAME ("P2 Button 3 (Cheat)")
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )
INPUT_PORTS_END

static INPUT_PORTS_START( cawingbl )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN1")
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

	PORT_START("DSWA")
	CPS1_COINAGE_1
	PORT_DIPNAME( 0x40, 0x40, "2 Coins to Start, 1 to Continue" )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )                          // Overrides all other coinage settings
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )                           // according to manual
	PORT_DIPUNUSED( 0x80, IP_ACTIVE_LOW )                       // This switch is not documented

	PORT_START("DSWB")
	PORT_DIPNAME( 0x07, 0x04, "Difficulty Level (Enemy's Strength)" )   PORT_DIPLOCATION("SW(B):1,2,3")
	PORT_DIPSETTING(    0x07, "1 (Easiest)" )
	PORT_DIPSETTING(    0x06, "2" )
	PORT_DIPSETTING(    0x05, "3" )
	PORT_DIPSETTING(    0x04, "4 (Normal)" )
	PORT_DIPSETTING(    0x03, "5" )
	PORT_DIPSETTING(    0x02, "6" )
	PORT_DIPSETTING(    0x01, "7" )
	PORT_DIPSETTING(    0x00, "8 (Hardest)" )
	PORT_DIPNAME( 0x18, 0x18, "Difficulty Level (Player's Strength)" )  PORT_DIPLOCATION("SW(B):4,5")
	PORT_DIPSETTING(    0x10, DEF_STR( Easy ) )
	PORT_DIPSETTING(    0x18, DEF_STR( Normal ) )
	PORT_DIPSETTING(    0x08, DEF_STR( Hard ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Hardest ) )
	PORT_DIPUNUSED_DIPLOC( 0x20, 0x20, "SW(B):6" )                      // This switch is not documented
	PORT_DIPUNUSED_DIPLOC( 0x40, 0x40, "SW(B):7" )                      // This switch is not documented
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(B):8" )                      // This switch is not documented

	PORT_START("DSWC")
	PORT_DIPUNUSED_DIPLOC( 0x01, 0x01, "SW(C):1" )                      // This switch is not documented
	PORT_DIPUNUSED_DIPLOC( 0x02, 0x02, "SW(C):2" )                      // This switch is not documented
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Free_Play ) )                    PORT_DIPLOCATION("SW(C):3")
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, "Freeze" )                                PORT_DIPLOCATION("SW(C):4")
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Flip_Screen ) )                  PORT_DIPLOCATION("SW(C):5")
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x00, DEF_STR( Demo_Sounds ) )                  PORT_DIPLOCATION("SW(C):6")
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Allow_Continue ) )               PORT_DIPLOCATION("SW(C):7")
	PORT_DIPSETTING(    0x40, DEF_STR( No ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Yes ) )
	PORT_DIPNAME( 0x80, 0x80, "Game Mode")                              PORT_DIPLOCATION("SW(C):8")
	PORT_DIPSETTING(    0x80, "Game" )
	PORT_DIPSETTING(    0x00, DEF_STR( Test ) )
INPUT_PORTS_END


static INPUT_PORTS_START( kodb )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("DSWA")
	CPS1_COINAGE_2( "SW(A)" )
	PORT_DIPNAME( 0x08, 0x08, "Coin Slots" )                        PORT_DIPLOCATION("SW(A):4")
	PORT_DIPSETTING(    0x00, "1" )
	PORT_DIPSETTING(    0x08, "3" )
	PORT_DIPNAME( 0x10, 0x10, "Play Mode" )                         PORT_DIPLOCATION("SW(A):5")
	PORT_DIPSETTING(    0x00, "2 Players" )
	PORT_DIPSETTING(    0x10, "3 Players" )
	PORT_DIPUNUSED_DIPLOC( 0x20, 0x20, "SW(A):6" )
	PORT_DIPNAME( 0x40, 0x40, "2 Coins to Start, 1 to Continue" )   PORT_DIPLOCATION("SW(A):7")
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(A):8" )

	PORT_START("DSWB")
	CPS1_DIFFICULTY_1( "SW(B)" )
	PORT_DIPNAME( 0x38, 0x38, DEF_STR( Lives ) )                    PORT_DIPLOCATION("SW(B):4,5,6")
	PORT_DIPSETTING(    0x30, "1" )
	PORT_DIPSETTING(    0x38, "2" )
	PORT_DIPSETTING(    0x28, "3" )
	PORT_DIPSETTING(    0x20, "4" )
	PORT_DIPSETTING(    0x18, "5" )
	PORT_DIPSETTING(    0x10, "6" )
	PORT_DIPSETTING(    0x08, "7" )
	PORT_DIPSETTING(    0x00, "8" )
	PORT_DIPNAME( 0xc0, 0xc0, DEF_STR( Bonus_Life ) )               PORT_DIPLOCATION("SW(B):7,8")
	PORT_DIPSETTING(    0x80, "80k and every 400k" )
	PORT_DIPSETTING(    0xc0, "100k and every 450k" )
	PORT_DIPSETTING(    0x40, "160k and every 450k" )
	PORT_DIPSETTING(    0x00, DEF_STR( None ) )

	PORT_START("DSWC")
	PORT_DIPUNUSED_DIPLOC( 0x01, 0x01, "SW(C):1" )
	PORT_DIPUNUSED_DIPLOC( 0x02, 0x02, "SW(C):2" )
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

	PORT_START("IN1")
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

	PORT_START("IN2")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )
INPUT_PORTS_END

static INPUT_PORTS_START( sf2mdt )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_NAME("P1 Jab Punch") PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_NAME("P1 Strong Punch") PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_NAME("P1 Fierce Punch") PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_NAME("P2 Jab Punch") PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_NAME("P2 Strong Punch") PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_NAME("P2 Fierce Punch") PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN2")      /* Extra buttons */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_NAME("P1 Short Kick") PORT_PLAYER(1)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_BUTTON5 ) PORT_NAME("P1 Forward Kick") PORT_PLAYER(1)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_BUTTON6 ) PORT_NAME("P1 Roundhouse Kick") PORT_PLAYER(1)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_NAME("P2 Short Kick") PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON5 ) PORT_NAME("P2 Forward Kick") PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_BUTTON6 ) PORT_NAME("P2 Roundhouse Kick") PORT_PLAYER(2)
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("DSWA")
	CPS1_COINAGE_1
	PORT_DIPNAME( 0x40, 0x40, "2 Coins to Start, 1 to Continue" )   PORT_DIPLOCATION("SW(A):7")
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(A):8" )

	PORT_START("DSWB")
	CPS1_DIFFICULTY_1( "SW(B)" )
	PORT_DIPUNUSED_DIPLOC( 0x08, 0x08, "SW(B):4" )
	PORT_DIPUNUSED_DIPLOC( 0x10, 0x10, "SW(B):5" )
	PORT_DIPUNUSED_DIPLOC( 0x20, 0x20, "SW(B):6" )
	PORT_DIPUNUSED_DIPLOC( 0x40, 0x40, "SW(B):7" )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(B):8" )

	PORT_START("DSWC")
	PORT_DIPUNUSED_DIPLOC( 0x01, 0x01, "SW(C):1" )
	PORT_DIPUNUSED_DIPLOC( 0x02, 0x02, "SW(C):2" )
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



static INPUT_PORTS_START( sf2mdtb )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_NAME("P1 Jab Punch") PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_NAME("P1 Strong Punch") PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_NAME("P1 Fierce Punch") PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_NAME("P2 Jab Punch") PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_NAME("P2 Strong Punch") PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_NAME("P2 Fierce Punch") PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN2")      /* Extra buttons */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_NAME("P1 Short Kick") PORT_PLAYER(1)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_BUTTON5 ) PORT_NAME("P1 Forward Kick") PORT_PLAYER(1)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_BUTTON6 ) PORT_NAME("P1 Roundhouse Kick") PORT_PLAYER(1)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_NAME("P2 Short Kick") PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON5 ) PORT_NAME("P2 Forward Kick") PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_BUTTON6 ) PORT_NAME("P2 Roundhouse Kick") PORT_PLAYER(2)
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("DSWA")
	CPS1_COINAGE_1
	PORT_DIPNAME( 0x40, 0x40, "2 Coins to Start, 1 to Continue" )   PORT_DIPLOCATION("SW(A):7")
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(A):8" )  //sort of debug mode...
													//depnding (???) of other DSW setting get different
													//"game" mode, autoplay, bonus round, ecc...
	PORT_START("DSWB")
	CPS1_DIFFICULTY_1( "SW(B)" )
	PORT_DIPUNUSED_DIPLOC( 0x08, 0x08, "SW(B):4" )
	PORT_DIPUNUSED_DIPLOC( 0x10, 0x10, "SW(B):5" )
	PORT_DIPUNUSED_DIPLOC( 0x20, 0x20, "SW(B):6" )
	PORT_DIPUNUSED_DIPLOC( 0x40, 0x40, "SW(B):7" )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(B):8" )

	PORT_START("DSWC")
	PORT_DIPUNUSED_DIPLOC( 0x01, 0x01, "SW(C):1" )
	PORT_DIPUNUSED_DIPLOC( 0x02, 0x02, "SW(C):2" )
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


static INPUT_PORTS_START( sgyxz )
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

static INPUT_PORTS_START( wofabl )
	PORT_START("IN0")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_START3 )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x4000, IP_ACTIVE_LOW )
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

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

	PORT_START("DSWA")
	PORT_DIPNAME( 0x0f, 0x0f, DEF_STR( Coinage ) ) PORT_DIPLOCATION("SW(A):1,2,3,4")
	PORT_DIPSETTING( 0x0f, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING( 0x0e, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING( 0x0d, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING( 0x0c, DEF_STR( 1C_4C ) )
	PORT_DIPSETTING( 0x0b, DEF_STR( 1C_6C ) )
	PORT_DIPSETTING( 0x0a, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING( 0x09, DEF_STR( 3C_1C ) )
	PORT_DIPSETTING( 0x08, DEF_STR( 4C_1C ) )
	PORT_DIPSETTING( 0x07, "2 Coins Start, 1 Coin Continue" )
	PORT_DIPSETTING( 0x06, DEF_STR( Free_Play ) )
	/* setting any of these crashes the test mode config menu */
	PORT_DIPUNKNOWN_DIPLOC( 0x10, 0x10, "SW(A):5" )  // free play?
	PORT_DIPUNKNOWN_DIPLOC( 0x20, 0x20, "SW(A):6" )  // 1c 8c?
	PORT_DIPUNKNOWN_DIPLOC( 0x40, 0x40, "SW(A):7" )  // 2 coins start?
	PORT_DIPUNKNOWN_DIPLOC( 0x80, 0x80, "SW(A):8" )  // 1c 7c?

	PORT_START("DSWB")
	PORT_DIPNAME( 0x07, 0x04, "Game Difficulty" ) PORT_DIPLOCATION("SW(B):1,2,3")
	PORT_DIPSETTING( 0x07, "0 (Extra Easy)" )
	PORT_DIPSETTING( 0x06, "1 (Very Easy)" )
	PORT_DIPSETTING( 0x05, "2 (Easy)" )
	PORT_DIPSETTING( 0x04, "3 (Normal)" )
	PORT_DIPSETTING( 0x03, "4 (Hard)" )
	PORT_DIPSETTING( 0x02, "5 (Very Hard)" )
	PORT_DIPSETTING( 0x01, "6 (Extra Hard)" )
	PORT_DIPSETTING( 0x00, "7 (Hardest)" )
	PORT_DIPUNKNOWN_DIPLOC( 0x08, 0x08, "SW(B):4" )
	PORT_DIPNAME( 0x70, 0x60, "Number of Players" ) PORT_DIPLOCATION("SW(B):5,6,7")
	PORT_DIPSETTING( 0x70, "Start 1, Continue 1" )
	PORT_DIPSETTING( 0x60, "Start 2, Continue 2" )
	PORT_DIPSETTING( 0x50, "Start 3, Continue 3" )
	PORT_DIPSETTING( 0x40, "Start 4, Continue 4" )
	PORT_DIPSETTING( 0x30, "Start 1, Continue 2" )
	PORT_DIPSETTING( 0x20, "Start 2, Continue 3" )
	PORT_DIPSETTING( 0x10, "Start 3, Continue 4" )
	PORT_DIPSETTING( 0x00, "Start 4, Continue 5" )
	PORT_DIPUNKNOWN_DIPLOC( 0x80, 0x80, "SW(B):8" )

	PORT_START("DSWC")
	PORT_DIPNAME( 0x03, 0x03, "Cabinet" ) PORT_DIPLOCATION("SW(C):1,2")
	PORT_DIPSETTING( 0x03, "3 Players, 3 Chutes" )
	PORT_DIPSETTING( 0x02, "3 Players, 1 Chute" )
	PORT_DIPSETTING( 0x01, "2 Players, 1 Chute" )
	PORT_DIPUNKNOWN_DIPLOC( 0x04, 0x04, "SW(C):3" )
	PORT_DIPUNKNOWN_DIPLOC( 0x08, 0x08, "SW(C):4" )
	PORT_DIPNAME( 0x30, 0x10, "Extend" ) PORT_DIPLOCATION("SW(C):5,6")
	PORT_DIPSETTING( 0x30, "No Extend" )
	PORT_DIPSETTING( 0x20, "100000 pts." )
	PORT_DIPSETTING( 0x10, "300000 pts." )
	PORT_DIPSETTING( 0x00, "100000, 300000, 500000, 1000000 pts." )
	PORT_DIPUNKNOWN_DIPLOC( 0x40, 0x40, "SW(C):7" )
	PORT_DIPUNKNOWN_DIPLOC( 0x80, 0x80, "SW(C):8" )  // crashes the test mode config menu if set
INPUT_PORTS_END


MACHINE_START_MEMBER(cps_state,fcrash)
{
	u8 *ROM = memregion("audiocpu")->base();

	membank("bank1")->configure_entries(0, 8, &ROM[0x10000], 0x4000);

	m_layer_enable_reg = 0x20;
	m_layer_mask_reg[0] = 0x26;
	m_layer_mask_reg[1] = 0x30;
	m_layer_mask_reg[2] = 0x28;
	m_layer_mask_reg[3] = 0x32;
	m_layer_scroll1x_offset = 62;
	m_layer_scroll2x_offset = 60;
	m_layer_scroll3x_offset = 64;
	m_sprite_base = 0x50c8;
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = 0;

	save_item(NAME(m_sample_buffer1));
	save_item(NAME(m_sample_buffer2));
	save_item(NAME(m_sample_select1));
	save_item(NAME(m_sample_select2));
}

MACHINE_START_MEMBER(cps_state,sgyxz)
{
	MACHINE_START_CALL_MEMBER(kodb);
	m_layer_scroll1x_offset = 0x40;
	m_layer_scroll2x_offset = 0x40;
	m_layer_scroll3x_offset = 0x40;
	m_sprite_list_end_marker = 0x8000;
	membank("bank1")->configure_entries(0, 2, memregion("audiocpu")->base() + 0x10000, 0x4000);
}

MACHINE_START_MEMBER(cps_state,kodb)
{
	m_layer_enable_reg = 0x20;
	m_layer_mask_reg[0] = 0x2e;
	m_layer_mask_reg[1] = 0x2c;
	m_layer_mask_reg[2] = 0x2a;
	m_layer_mask_reg[3] = 0x28;
	m_layer_scroll1x_offset = 0;
	m_layer_scroll2x_offset = 0;
	m_layer_scroll3x_offset = 0;
	m_sprite_base = 0x1000;
	m_sprite_list_end_marker = 0xffff;
	m_sprite_x_offset = 0;
}

MACHINE_START_MEMBER(cps_state,mtwinsb)
{
	u8 *ROM = memregion("audiocpu")->base();

	membank("bank1")->configure_entries(0, 8, &ROM[0x10000], 0x4000);

	m_layer_enable_reg = 0x12;
	m_layer_mask_reg[0] = 0x14;
	m_layer_mask_reg[1] = 0x16;
	m_layer_mask_reg[2] = 0x18;
	m_layer_mask_reg[3] = 0x1a;
	m_layer_scroll1x_offset = 0x00;
	m_layer_scroll2x_offset = 0x00;
	m_layer_scroll3x_offset = 0x00;
	m_sprite_base = 0x1000;
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = 0;
}

MACHINE_START_MEMBER(cps_state, cawingbl)
{
	MACHINE_START_CALL_MEMBER(fcrash);

	m_layer_enable_reg = 0x0c;
	m_layer_mask_reg[0] = 0x0a;
	m_layer_mask_reg[1] = 0x08;
	m_layer_mask_reg[2] = 0x06;
	m_layer_mask_reg[3] = 0x04;
	m_layer_scroll1x_offset = 63;
	m_layer_scroll2x_offset = 62;
	m_layer_scroll3x_offset = 65;
	m_sprite_base = 0x1000;
}

MACHINE_START_MEMBER(cps_state, sf2mdt)
{
	u8 *ROM = memregion("audiocpu")->base();

	membank("bank1")->configure_entries(0, 8, &ROM[0x10000], 0x4000);

	m_layer_enable_reg = 0x26;
	m_layer_mask_reg[0] = 0x28;
	m_layer_mask_reg[1] = 0x2a;
	m_layer_mask_reg[2] = 0x2c;
	m_layer_mask_reg[3] = 0x2e;
	m_layer_scroll1x_offset = 0;
	m_layer_scroll2x_offset = 0;
	m_layer_scroll3x_offset = 0;
	m_sprite_base = 0x1000;
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = 2;

	save_item(NAME(m_sample_buffer1));
	save_item(NAME(m_sample_buffer2));
	save_item(NAME(m_sample_select1));
	save_item(NAME(m_sample_select2));
}

MACHINE_START_MEMBER(cps_state, knightsb)
{
	u8 *ROM = memregion("audiocpu")->base();

	membank("bank1")->configure_entries(0, 16, &ROM[0x10000], 0x4000);

	m_layer_enable_reg = 0x28;
	m_layer_mask_reg[0] = 0x26;
	m_layer_mask_reg[1] = 0x24;
	m_layer_mask_reg[2] = 0x22;
	m_layer_mask_reg[3] = 0x30;
	m_layer_scroll1x_offset = 0x3e; //text
	m_layer_scroll2x_offset = 0x3c; //bricks around scores
	m_layer_scroll3x_offset = 0x40; //hill with sword going in
	m_sprite_base = 0x1000;
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = 0;
}

MACHINE_START_MEMBER(cps_state, sf2m1)
{
	u8 *ROM = memregion("audiocpu")->base();

	membank("bank1")->configure_entries(0, 8, &ROM[0x10000], 0x4000);

	m_layer_enable_reg = 0x26;
	m_layer_mask_reg[0] = 0x28;
	m_layer_mask_reg[1] = 0x2a;
	m_layer_mask_reg[2] = 0x2c;
	m_layer_mask_reg[3] = 0x2e;
	m_layer_scroll1x_offset = 0x3e;
	m_layer_scroll2x_offset = 0x3c;
	m_layer_scroll3x_offset = 0x40;
	m_sprite_base = 0x1000;
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = 0;
}

MACHINE_RESET_MEMBER(cps_state,fcrash)
{
	m_sample_buffer1 = 0;
	m_sample_buffer2 = 0;
	m_sample_select1 = 0;
	m_sample_select2 = 0;
}

void cps_state::fcrash(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 10000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::fcrash_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, 24000000/6); /* ? */
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::sound_map);

	MCFG_MACHINE_START_OVERRIDE(cps_state,fcrash)
	MCFG_MACHINE_RESET_OVERRIDE(cps_state,fcrash)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1 );
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(4096);

	MCFG_VIDEO_START_OVERRIDE(cps_state, cps1)

	// sound hardware
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);

	ym2203_device &ym1(YM2203(config, "ym1", 24000000/6));   /* ? */
	ym1.add_route(0, "mono", 0.10);
	ym1.add_route(1, "mono", 0.10);
	ym1.add_route(2, "mono", 0.10);
	ym1.add_route(3, "mono", 1.0);

	ym2203_device &ym2(YM2203(config, "ym2", 24000000/6));   /* ? */
	ym2.add_route(0, "mono", 0.10);
	ym2.add_route(1, "mono", 0.10);
	ym2.add_route(2, "mono", 0.10);
	ym2.add_route(3, "mono", 1.0);

	MSM5205(config, m_msm_1, 24000000/64);  /* ? */
	m_msm_1->vck_legacy_callback().set(FUNC(cps_state::m5205_int1)); /* interrupt function */
	m_msm_1->set_prescaler_selector(msm5205_device::S96_4B);    /* 4KHz 4-bit */
	m_msm_1->add_route(ALL_OUTPUTS, "mono", 0.25);

	MSM5205(config, m_msm_2, 24000000/64);  /* ? */
	m_msm_2->vck_legacy_callback().set(FUNC(cps_state::m5205_int2)); /* interrupt function */
	m_msm_2->set_prescaler_selector(msm5205_device::S96_4B);    /* 4KHz 4-bit */
	m_msm_2->add_route(ALL_OUTPUTS, "mono", 0.25);
}

// HBMAME start
void cps_state::cawingb(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, XTAL(10'000'000));    /* verified on pcb */
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::fcrash_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::irq6_line_hold));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, XTAL(3'579'545));  /* verified on pcb */
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::sub_map);

	MCFG_MACHINE_START_OVERRIDE(cps_state, cawingbl)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_raw(8'000'000, 518, 64, 448, 259, 16, 240);
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state,cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	GENERIC_LATCH_8(config, m_soundlatch);
	GENERIC_LATCH_8(config, m_soundlatch2);

	ym2151_device &ym2151(YM2151(config, "2151", XTAL(3'579'545)));
	ym2151.irq_handler().set_inputline(m_audiocpu, 0);
	ym2151.add_route(0, "mono", 0.35);
	ym2151.add_route(1, "mono", 0.35);

	OKIM6295(config, m_oki, XTAL(16'000'000)/4/4, okim6295_device::PIN7_HIGH).add_route(ALL_OUTPUTS, "mono", 0.30);
}
// HBMAME end
void cps_state::cawingbl(machine_config &config)
{
	fcrash(config);
	/* basic machine hardware */
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::irq6_line_hold)); /* needed to write to scroll values */

	MCFG_MACHINE_START_OVERRIDE(cps_state, cawingbl)
}

void cps_state::kodb(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 10000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::fcrash_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, 3579545);
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::kodb_sound_map);

	MCFG_MACHINE_START_OVERRIDE(cps_state,kodb)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1);
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state,cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);

	ym2151_device &ym2151(YM2151(config, "2151", XTAL(3'579'545)));  /* verified on pcb */
	ym2151.irq_handler().set_inputline(m_audiocpu, 0);
	ym2151.add_route(0, "mono", 0.35);
	ym2151.add_route(1, "mono", 0.35);

	/* CPS PPU is fed by a 16mhz clock,pin 117 outputs a 4mhz clock which is divided by 4 using 2 74ls74 */
	OKIM6295(config, m_oki, XTAL(16'000'000)/4/4, okim6295_device::PIN7_HIGH); // pin 7 can be changed by the game code, see f006 on z80
	m_oki->add_route(ALL_OUTPUTS, "mono", 0.30);
}

void cps_state::mtwinsb(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 10000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::mtwinsb_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, 3579545);
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::sgyxz_sound_map);

	MCFG_MACHINE_START_OVERRIDE(cps_state, mtwinsb)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1);
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette, palette_device::BLACK).set_entries(0xc00);

	/* sound hardware */
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);
	GENERIC_LATCH_8(config, m_soundlatch2);

	ym2151_device &ym2151(YM2151(config, "2151", XTAL(3'579'545)));
	ym2151.irq_handler().set_inputline(m_audiocpu, 0);
	ym2151.add_route(0, "mono", 0.35);
	ym2151.add_route(1, "mono", 0.35);

	OKIM6295(config, m_oki, XTAL(16'000'000)/4/4, okim6295_device::PIN7_HIGH);
	m_oki->add_route(ALL_OUTPUTS, "mono", 0.30);
}

void cps_state::sf2mdt(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 12000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sf2mdt_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::irq4_line_hold)); /* triggers the sprite ram and scroll writes */

	Z80(config, m_audiocpu, 3579545);
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::sf2mdt_z80map);

	MCFG_MACHINE_START_OVERRIDE(cps_state, sf2mdt)
	MCFG_MACHINE_RESET_OVERRIDE(cps_state,fcrash)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1);
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(4096);

	MCFG_VIDEO_START_OVERRIDE(cps_state,cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);

	YM2151(config, "2151", XTAL(3'579'545)).add_route(0, "mono", 0.35).add_route(1, "mono", 0.35);

	/* has 2x MSM5205 instead of OKI6295 */
	MSM5205(config, m_msm_1, 24000000/64);  /* ? */
	m_msm_1->vck_legacy_callback().set(FUNC(cps_state::m5205_int1));    /* interrupt function */
	m_msm_1->set_prescaler_selector(msm5205_device::S96_4B);    /* 4KHz 4-bit */
	m_msm_1->add_route(ALL_OUTPUTS, "mono", 0.25);

	MSM5205(config, m_msm_2, 24000000/64);  /* ? */
	m_msm_2->vck_legacy_callback().set(FUNC(cps_state::m5205_int2));    /* interrupt function */
	m_msm_2->set_prescaler_selector(msm5205_device::S96_4B);    /* 4KHz 4-bit */
	m_msm_2->add_route(ALL_OUTPUTS, "mono", 0.25);
}

void cps_state::sf2b(machine_config &config)
{
	sf2mdt(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sf2b_map);
}

void cps_state::knightsb(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 24000000 / 2);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::knightsb_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, 29821000 / 8);
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::knightsb_z80map);

	MCFG_MACHINE_START_OVERRIDE(cps_state, knightsb)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1);
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state,cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);

	ym2151_device &ym2151(YM2151(config, "2151", 29821000 / 8));
	ym2151.irq_handler().set_inputline(m_audiocpu, 0);
	ym2151.add_route(0, "mono", 0.35);
	ym2151.add_route(1, "mono", 0.35);

	/* has 2x MSM5205 instead of OKI6295 */
	MSM5205(config, m_msm_1, 24000000/64);  /* ? */
	m_msm_1->vck_legacy_callback().set(FUNC(cps_state::m5205_int1)); /* interrupt function */
	m_msm_1->set_prescaler_selector(msm5205_device::S96_4B);    /* 4KHz 4-bit */
	m_msm_1->add_route(ALL_OUTPUTS, "mono", 0.25);

	MSM5205(config, m_msm_2, 24000000/64);  /* ? */
	m_msm_2->vck_legacy_callback().set(FUNC(cps_state::m5205_int2)); /* interrupt function */
	m_msm_2->set_prescaler_selector(msm5205_device::S96_4B);    /* 4KHz 4-bit */
	m_msm_2->add_route(ALL_OUTPUTS, "mono", 0.25);
}

#define CODE_SIZE 0x400000

// ************************************************************************* FCRASH

ROM_START( fcrash )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "9.bin", 0x00000, 0x20000, CRC(c6854c91) SHA1(29f01cc65be5eaa3f86e99eebdd284104623abb0) )
	ROM_LOAD16_BYTE( "5.bin", 0x00001, 0x20000, CRC(77f7c2b3) SHA1(feea48d9555824a2e5bf5e99ce159edc015f0792) )
	ROM_LOAD16_BYTE( "8.bin", 0x40000, 0x20000, CRC(1895b3df) SHA1(415a26050c50ed79a7ee5ddd1b8d61593b1ce876) )
	ROM_LOAD16_BYTE( "4.bin", 0x40001, 0x20000, CRC(bbd411ee) SHA1(85d50ca72ec46d627f9c88ff0809aa30e164821a) )
	ROM_LOAD16_BYTE( "7.bin", 0x80000, 0x20000, CRC(5b23ebf2) SHA1(8c28c21a72a28ad249170026891c6bb865943f84) )
	ROM_LOAD16_BYTE( "3.bin", 0x80001, 0x20000, CRC(aba2aebe) SHA1(294109b5929ed63859a55bef16643e3ade7da16f) )
	ROM_LOAD16_BYTE( "6.bin", 0xc0000, 0x20000, CRC(d4bf37f6) SHA1(f47e1cc9aa3b3019ee57f59715e3a611acf9fe3e) )
	ROM_LOAD16_BYTE( "2.bin", 0xc0001, 0x20000, CRC(07ac8f43) SHA1(7a41b003c76adaabd3f94929cc163461b70e0ed9) )
	//ROM_FILL(0x2610, 1, 7)  // temporary patch to fix transitions

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* Audio CPU + Sample Data */
	ROM_LOAD( "1.bin", 0x00000, 0x20000, CRC(5b276c14) SHA1(73e53c077d4e3c1b919eee28b29e34176ee204f8) )
	ROM_RELOAD(        0x10000, 0x20000 )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD32_BYTE( "18.bin", 0x000000, 0x20000, CRC(f1eee6d9) SHA1(bee95efbff49c582cff1cc6d9bb5ef4ea5c4a074) )
	ROM_LOAD32_BYTE( "20.bin", 0x000001, 0x20000, CRC(675f4537) SHA1(acc68822da3aafbb62f76cbffa5f3389fcc91447) )
	ROM_LOAD32_BYTE( "22.bin", 0x000002, 0x20000, CRC(db8a32ac) SHA1(b95f73dff291acee239e22e5fd7efe15d0de23be) )
	ROM_LOAD32_BYTE( "24.bin", 0x000003, 0x20000, CRC(f4113e57) SHA1(ff1f443c13494a169b9be24abc361d27a6d01c09) )
	ROM_LOAD32_BYTE( "10.bin", 0x080000, 0x20000, CRC(d478853e) SHA1(91fcf8eb022ccea66d291bec84ace557181cf861) )
	ROM_LOAD32_BYTE( "12.bin", 0x080001, 0x20000, CRC(25055642) SHA1(578cf6a436489cc1f2d1acdb0cba6c1cbee2e21f) )
	ROM_LOAD32_BYTE( "14.bin", 0x080002, 0x20000, CRC(b77d0328) SHA1(42eb1ebfda301f2b09f3add5932e8331f4790706) )
	ROM_LOAD32_BYTE( "16.bin", 0x080003, 0x20000, CRC(ea111a79) SHA1(1b86aa984d2d6c527e96b61274a82263f34d0d89) )
	ROM_LOAD32_BYTE( "19.bin", 0x100000, 0x20000, CRC(b3aa1f48) SHA1(411f3855739992f5967e915f2a5255afcedeac2e) ) // only these 4 differ from ffightbla (new title logo)
	ROM_LOAD32_BYTE( "21.bin", 0x100001, 0x20000, CRC(04d175c9) SHA1(33e6e3fefae4e3977c8c954fbd7feff36e92d723) ) // ^
	ROM_LOAD32_BYTE( "23.bin", 0x100002, 0x20000, CRC(e592ba4f) SHA1(62559481e0da3954a90da0ab0fb51f87f1b3dd9d) ) // ^
	ROM_LOAD32_BYTE( "25.bin", 0x100003, 0x20000, CRC(b89a740f) SHA1(516d73c772e0a904dfb0bd84874919d78bbbd200) ) // ^
	ROM_LOAD32_BYTE( "11.bin", 0x180000, 0x20000, CRC(d4457a60) SHA1(9e956efafa81a81aca92837df03968f5670ffc15) )
	ROM_LOAD32_BYTE( "13.bin", 0x180001, 0x20000, CRC(3b26a37d) SHA1(58d8d0cdef81c938fb1a5595f2d02b228865893b) )
	ROM_LOAD32_BYTE( "15.bin", 0x180002, 0x20000, CRC(6d837e09) SHA1(b4a133ab96c35b689ee692bfcc04981791099b6f) )
	ROM_LOAD32_BYTE( "17.bin", 0x180003, 0x20000, CRC(c59a4d6c) SHA1(59e49c7d24dd333007de4bb621050011a5392bcc) )

	ROM_REGION( 0x8000, "gfx2", 0 )
	ROM_COPY( "gfx", 0x000000, 0x000000, 0x8000 )   /* stars */
ROM_END

ROM_START( ffightbl )
	ROM_REGION( 0x400000, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "fg-e.bin", 0x00000, 0x80000, CRC(f8ccf27e) SHA1(08ff445d946da81e7dc0cc021f686b5968fa34ab) )
	ROM_LOAD16_BYTE( "fg-f.bin", 0x00001, 0x80000, CRC(d96c76b2) SHA1(3f9ca4625491cab07cf4a1bf001f1325dc3652a3) )
    ROM_FILL(0x2610, 1, 7)  // fix transitions HBMAME
	
	ROM_REGION( 0x30000, "audiocpu", 0 ) /* Audio CPU + Sample Data */
	ROM_LOAD( "ff1.bin", 0x00000, 0x20000, CRC(5b276c14) SHA1(73e53c077d4e3c1b919eee28b29e34176ee204f8) )
	ROM_RELOAD(          0x10000, 0x20000 )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD32_BYTE( "fg-d.bin", 0x000000, 0x80000, CRC(4303f863) SHA1(72a3246e14f9c4d1fb4712bd67d087db42d722d9) )
	ROM_LOAD32_BYTE( "fg-c.bin", 0x000001, 0x80000, CRC(d1dfcd2d) SHA1(8796db70459e1e6232a75f5c3f4bf8b227b16f46) )
	ROM_LOAD32_BYTE( "fg-b.bin", 0x000002, 0x80000, CRC(22f2c097) SHA1(bbf2d30d31c5a7802b7f7f164dd51a4584511936) )
	ROM_LOAD32_BYTE( "fg-a.bin", 0x000003, 0x80000, CRC(16a89b2c) SHA1(4d0e1ec6ae9a2bd31fa77140532bbce64d3874e9) )

	ROM_REGION( 0x8000, "gfx2", 0 )
	ROM_COPY( "gfx", 0x000000, 0x000000, 0x8000 )   /* stars */
ROM_END

// this is identical to the Final Crash bootleg but without the modified gfx.
// it's less common than Final Crash, but is either the original bootleg, or the bootleggers wanted to restore the
// original title.
ROM_START( ffightbla )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "9.bin", 0x00000, 0x20000, CRC(c6854c91) SHA1(29f01cc65be5eaa3f86e99eebdd284104623abb0) )
	ROM_LOAD16_BYTE( "5.bin", 0x00001, 0x20000, CRC(77f7c2b3) SHA1(feea48d9555824a2e5bf5e99ce159edc015f0792) )
	ROM_LOAD16_BYTE( "8.bin", 0x40000, 0x20000, CRC(1895b3df) SHA1(415a26050c50ed79a7ee5ddd1b8d61593b1ce876) )
	ROM_LOAD16_BYTE( "4.bin", 0x40001, 0x20000, CRC(bbd411ee) SHA1(85d50ca72ec46d627f9c88ff0809aa30e164821a) )
	ROM_LOAD16_BYTE( "7.bin", 0x80000, 0x20000, CRC(5b23ebf2) SHA1(8c28c21a72a28ad249170026891c6bb865943f84) )
	ROM_LOAD16_BYTE( "3.bin", 0x80001, 0x20000, CRC(aba2aebe) SHA1(294109b5929ed63859a55bef16643e3ade7da16f) )
	ROM_LOAD16_BYTE( "6.bin", 0xc0000, 0x20000, CRC(d4bf37f6) SHA1(f47e1cc9aa3b3019ee57f59715e3a611acf9fe3e) )
	ROM_LOAD16_BYTE( "2.bin", 0xc0001, 0x20000, CRC(07ac8f43) SHA1(7a41b003c76adaabd3f94929cc163461b70e0ed9) )
	//ROM_FILL(0x2610, 1, 7)  // temporary patch to fix transitions

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* Audio CPU + Sample Data */
	ROM_LOAD( "1.bin", 0x00000, 0x20000, CRC(5b276c14) SHA1(73e53c077d4e3c1b919eee28b29e34176ee204f8) )
	ROM_RELOAD(        0x10000, 0x20000 )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD32_BYTE( "18.bin",    0x000000, 0x20000, CRC(f1eee6d9) SHA1(bee95efbff49c582cff1cc6d9bb5ef4ea5c4a074) )
	ROM_LOAD32_BYTE( "20.bin",    0x000001, 0x20000, CRC(675f4537) SHA1(acc68822da3aafbb62f76cbffa5f3389fcc91447) )
	ROM_LOAD32_BYTE( "22.bin",    0x000002, 0x20000, CRC(db8a32ac) SHA1(b95f73dff291acee239e22e5fd7efe15d0de23be) )
	ROM_LOAD32_BYTE( "24.bin",    0x000003, 0x20000, CRC(f4113e57) SHA1(ff1f443c13494a169b9be24abc361d27a6d01c09) )
	ROM_LOAD32_BYTE( "10.bin",    0x080000, 0x20000, CRC(d478853e) SHA1(91fcf8eb022ccea66d291bec84ace557181cf861) )
	ROM_LOAD32_BYTE( "12.bin",    0x080001, 0x20000, CRC(25055642) SHA1(578cf6a436489cc1f2d1acdb0cba6c1cbee2e21f) )
	ROM_LOAD32_BYTE( "14.bin",    0x080002, 0x20000, CRC(b77d0328) SHA1(42eb1ebfda301f2b09f3add5932e8331f4790706) )
	ROM_LOAD32_BYTE( "16.bin",    0x080003, 0x20000, CRC(ea111a79) SHA1(1b86aa984d2d6c527e96b61274a82263f34d0d89) )
	ROM_LOAD32_BYTE( "ff-19.bin", 0x100000, 0x20000, CRC(7bc03747) SHA1(6964e5c562d6af5b4327ff828f3d0522c34911bc) ) // only these 4 differ from fcrash
	ROM_LOAD32_BYTE( "ff-21.bin", 0x100001, 0x20000, CRC(0c248e2b) SHA1(28731fe25a8eb39c1e0822cf9074a7a32c6b2978) ) // ^
	ROM_LOAD32_BYTE( "ff-23.bin", 0x100002, 0x20000, CRC(53949d0e) SHA1(1b11134005a47c323917b9892fe44819c36c6ee2) ) // ^
	ROM_LOAD32_BYTE( "ff-25.bin", 0x100003, 0x20000, CRC(8d34a67d) SHA1(69e9f52efb73952313848a6d54dbdc17a2275c59) ) // ^
	ROM_LOAD32_BYTE( "11.bin",    0x180000, 0x20000, CRC(d4457a60) SHA1(9e956efafa81a81aca92837df03968f5670ffc15) )
	ROM_LOAD32_BYTE( "13.bin",    0x180001, 0x20000, CRC(3b26a37d) SHA1(58d8d0cdef81c938fb1a5595f2d02b228865893b) )
	ROM_LOAD32_BYTE( "15.bin",    0x180002, 0x20000, CRC(6d837e09) SHA1(b4a133ab96c35b689ee692bfcc04981791099b6f) )
	ROM_LOAD32_BYTE( "17.bin",    0x180003, 0x20000, CRC(c59a4d6c) SHA1(59e49c7d24dd333007de4bb621050011a5392bcc) )

	ROM_REGION( 0x8000, "gfx2", 0 )
	ROM_COPY( "gfx", 0x000000, 0x000000, 0x8000 )   /* stars */
ROM_END

// the following bootleg is very peculiar: the program ROMs are identical to those of ffightbl but is uses smaller ROMs for patching
// there is a full set of GFX ROMs matching ffightbl, additional ROMs matching 0x100000-0x1fffff of ffightbla and some smaller ROMs for overlaying
// for now the loading is the full set, overlayed by the 0x100000-0x1fffff, overlayed by the smaller ROMs. Should be checked though
// the sound system comprises a Z80 with bare bones sound code and a single OKI-M6295
#if 0
void cps_state::ffightblb(machine_config &config)

{		/* basic machine hardware */
	M68000(config, m_maincpu, 10000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::fcrash_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, 24000000/6); /* ? */
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::ffightblb_sound_map);

	MCFG_MACHINE_START_OVERRIDE(cps_state, ffightblb)
	MCFG_MACHINE_RESET_OVERRIDE(cps_state, fcrash)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1 );
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette, palette_device::BLACK).set_entries(4096);

	// sound hardware
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);

	OKIM6295(config, m_oki, 1000000 , okim6295_device::PIN7_HIGH);
	m_oki->set_addrmap(0, &cps_state::ffightblb_oki_map);
	m_oki->add_route(ALL_OUTPUTS, "mono", 0.30);
}


void cps_state::ffightblb_sound_map(address_map &map) // TODO: verify
{
	map(0x0000, 0x7fff).rom();
	map(0x8000, 0x87ff).ram();
	map(0x9000, 0x9000).lw8(NAME([this] (u8 data) { m_okibank->set_entry(data & 0x03); }));
	map(0x9800, 0x9800).rw(m_oki, FUNC(okim6295_device::read), FUNC(okim6295_device::write));
	map(0xa000, 0xa000).r(m_soundlatch, FUNC(generic_latch_8_device::read));
}

void cps_state::ffightblb_oki_map(address_map &map)
{
	map(0x00000, 0x1ffff).rom();
	map(0x20000, 0x3ffff).bankr(m_okibank);
}

MACHINE_START_MEMBER(cps_state,ffightblb)
{
	m_layer_enable_reg = 0x20;
	m_layer_mask_reg[0] = 0x26;
	m_layer_mask_reg[1] = 0x30;
	m_layer_mask_reg[2] = 0x28;
	m_layer_mask_reg[3] = 0x32;
	m_layer_scroll1x_offset = 0x00;
	m_layer_scroll2x_offset = 0x08;
	m_layer_scroll3x_offset = 0x04;
	m_sprite_base = 0x5008; // check this
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = -0x38;

	m_okibank->configure_entries(0, 4, memregion("oki")->base() + 0x20000, 0x20000);
}
#endif

ROM_START( ffightblb )
	ROM_REGION( 0x10000, "patch", 0 )
	ROM_LOAD16_BYTE( "pgm0h.4", 0x00000, 0x08000, CRC(b800c1be) SHA1(dc5c748e49c751c155d970d8a7e6c0fb20767d04) ) // these seem to patch some addresses (see below)
	ROM_LOAD16_BYTE( "pgm0l.3", 0x00001, 0x08000, CRC(a39f50d2) SHA1(a7b822f92a8eb412855bfb87a3083aa9082542ae) ) // they are empty after 0x5000 (interleaved)

	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "soonhwa_f-fightpgm.8h", 0x00000, 0x80000, CRC(f8ccf27e) SHA1(08ff445d946da81e7dc0cc021f686b5968fa34ab) )
	ROM_LOAD16_BYTE( "soonhwa_f-fightpgm.8l", 0x00001, 0x80000, CRC(d96c76b2) SHA1(3f9ca4625491cab07cf4a1bf001f1325dc3652a3) )
	ROM_COPY( "patch", 0x00000, 0x002000, 0x1000 )
	ROM_COPY( "patch", 0x01000, 0x016000, 0x1000 )
	ROM_COPY( "patch", 0x02000, 0x01f000, 0x1000 )
	ROM_COPY( "patch", 0x03000, 0x05e000, 0x1000 )
	ROM_COPY( "patch", 0x04000, 0x078000, 0x1000 )

	ROM_REGION( 0x8000, "audiocpu", 0 )
	ROM_LOAD( "sro.1", 0x00000, 0x8000, CRC(2b1c4c16) SHA1(8da39809df20a3fe4371573596285ea3297996e3) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD32_BYTE( "soonhwa_f-fight03.0r03",  0x000000, 0x80000, CRC(2126bec0) SHA1(c523e7e52c18177e2e967091a6acb231d52a3525) )
	ROM_IGNORE(0x80000) // 1ST AND 2ND HALF IDENTICAL
	ROM_LOAD32_BYTE( "soonhwa_f-fight02.0r02",  0x000001, 0x80000, CRC(fe326d39) SHA1(10e1e9b26a3ed2277f2016d040ce5b205a62096d) )
	ROM_IGNORE(0x80000) // 1ST AND 2ND HALF IDENTICAL
	ROM_LOAD32_BYTE( "soonhwa_f-fight01.0r01",  0x000002, 0x80000, CRC(09c47cae) SHA1(995546a72667fa25d7b3fd29643217acb6ff4fd5) )
	ROM_IGNORE(0x80000) // 1ST AND 2ND HALF IDENTICAL
	ROM_LOAD32_BYTE( "soonhwa_f-fight00.0r00",  0x000003, 0x80000, CRC(4b4390de) SHA1(30b38842116fc45c0d284f3b72c67fef33215ad7) )
	ROM_IGNORE(0x80000) // 1ST AND 2ND HALF IDENTICAL
	ROM_LOAD32_WORD_SWAP( "soonhwa_f-fight.9",  0x100000, 0x40000, CRC(11a7c515) SHA1(b4f32e1627fb2af15ec6a3d7cfd88ea6fa9ad15a) ) // here starts the first overlay of GFX ROMs
	ROM_IGNORE(0x40000) // 1ST AND 2ND HALF IDENTICAL
	ROM_LOAD32_WORD_SWAP( "soonhwa_f-fight.8",  0x100002, 0x40000, CRC(f1e18158) SHA1(2a4195002be4bcb1eda84fd876666f58c837e58e) )
	ROM_IGNORE(0x40000) // 1ST AND 2ND HALF IDENTICAL
	ROM_LOAD32_WORD_SWAP( "soonhwa_f-fight.11", 0x180000, 0x40000, CRC(52879243) SHA1(97fb84376334abb0cb0590e7b4d49adeeb17373d) )
	ROM_IGNORE(0x40000) // 1ST AND 2ND HALF IDENTICAL
	ROM_LOAD32_WORD_SWAP( "soonhwa_f-fight.10", 0x180002, 0x40000, CRC(7cce0ff5) SHA1(0048ddf8ac26b0cbd4b017634d308f0d6b631abc) )
	ROM_IGNORE(0x40000) // 1ST AND 2ND HALF IDENTICAL
	ROM_LOAD32_BYTE( "cr.00", 0x100000, 0x10000, CRC(e6bbd39b) SHA1(7c7c9fad7608f231172f011dd930399e6b72e57a) ) // here starts the second overlay of GFX ROMs
	ROM_LOAD32_BYTE( "cr.01", 0x100001, 0x10000, CRC(6c794ef4) SHA1(e7835ac5c52153ca333be154cd16f2162e936364) )
	ROM_LOAD32_BYTE( "cr.02", 0x100002, 0x10000, CRC(4d1d389d) SHA1(12c65c2f8027d4944f25d89d98a440be5422cb98) )
	ROM_LOAD32_BYTE( "cr.03", 0x100003, 0x10000, CRC(5282be3c) SHA1(ff32a501ee2d3f7476ff814aea302b1d780c35b7) )

	ROM_REGION( 0x8000, "gfx2", 0 )
	ROM_COPY( "gfx", 0x000000, 0x000000, 0x8000 )   /* stars */

	ROM_REGION( 0xa0000, "oki", ROMREGION_ERASE00 )
	ROM_LOAD( "vco.2",              0x00000, 0x20000, CRC(de0f0ef5) SHA1(18cb33f7990d7715d11d61e6db446ce935e799eb) )
	ROM_LOAD( "soonhwa_f-fight.14", 0x20000, 0x80000, CRC(319fbc2f) SHA1(263fc6b59cef6d110da35b36dde250a2e326dcbe) )
ROM_END

// ************************************************************************* KODB

/*
CPU

1x TS68000CP12 (main)
1x TPC1020AFN-084C
1x Z8400BB1-Z80CPU (sound)
1x YM2151 (sound)
1x YM3012A (sound)
1x OKI-M6295 (sound)
2x LM324N (sound)
1x TDA2003 (sound)
1x oscillator 10.0 MHz
1x oscillator 22.1184 MHz

ROMs

1x AM27C512 (1)(sound)
1x AM27C020 (2)(sound)
2x AM27C040 (3,4)(main)
1x Am27C040 (bp)(gfx)
7x maskrom (ai,bi,ci,di,ap,cp,dp)(gfx)
1x GAL20V8A (not dumped)
3x GAL16V8A (not dumped)
1x PALCE20V8H (not dumped)
1x GAL20V8S (not dumped)

Note

1x JAMMA edge connector
1x trimmer (volume)
3x 8 switches dip

*/

ROM_START( kodb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "3.ic172", 0x00000, 0x080000, CRC(036dd74c) SHA1(489344e56863429e86b4c362b82d89819c1d6afb) )
	ROM_LOAD16_BYTE( "4.ic171", 0x00001, 0x080000, CRC(3e4b7295) SHA1(3245640bae7d141238051dfe5c7683d05c6d3848) )
	ROM_FILL( 0x952, 1, 7)  // fix transitions HBMAME

	ROM_REGION( 0x18000, "audiocpu", 0 ) /* 64k for the audio CPU (+banks) */
	ROM_LOAD( "1.ic28", 0x00000, 0x08000, CRC(01cae60c) SHA1(b2cdd883fd859f0b701230831aca1f1a74ad6087) )
	ROM_CONTINUE(       0x10000, 0x08000 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROM_LOAD64_BYTE( "cp.ic90", 0x000000, 0x80000, CRC(e3b8589e) SHA1(775f97e43cb995b93da40063a1f1e4d73b34437c) )
	ROM_LOAD64_BYTE( "dp.ic89", 0x000001, 0x80000, CRC(3eec9580) SHA1(3d8d0cfbeae077544e514a5eb96cc83f716e494f) )
	ROM_LOAD64_BYTE( "ap.ic88", 0x000002, 0x80000, CRC(fdf5f163) SHA1(271ee96886c958accaca9a82484ab80fe32bd38e) )
	ROM_LOAD64_BYTE( "bp.ic87", 0x000003, 0x80000, CRC(4e1c52b7) SHA1(74570e7d577c999c62203c97b3d449e3b61a678a) )
	ROM_LOAD64_BYTE( "ci.ic91", 0x000004, 0x80000, CRC(22228bc5) SHA1(d48a09ee284d9e4b986f5c3c1c865930f76986e2) )
	ROM_LOAD64_BYTE( "di.ic92", 0x000005, 0x80000, CRC(ab031763) SHA1(5bcd89b1debf029b779aa1bb73b3a572d27154ec) )
	ROM_LOAD64_BYTE( "ai.ic93", 0x000006, 0x80000, CRC(cffbf4be) SHA1(f805bafc855d4a656c055a76eaeb26e36835541e) )
	ROM_LOAD64_BYTE( "bi.ic94", 0x000007, 0x80000, CRC(4a1b43fe) SHA1(7957f45b2862825c9509043c63c7da7108bd251b) )

	ROM_REGION( 0x8000, "gfx2", 0 )
	ROM_COPY( "gfx", 0x000000, 0x000000, 0x8000 )   /* stars */

	ROM_REGION( 0x40000, "oki", 0 ) /* Samples */
	ROM_LOAD( "2.ic19", 0x00000, 0x40000, CRC(a2db1575) SHA1(1a4a29e4b045af50700adf1665697feab12cc234) )
ROM_END

void cps_state::init_kodb()
{
	m_maincpu->space(AS_PROGRAM).install_read_port(0x800000, 0x800007, "IN1");
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x800018, 0x80001f, read16sm_delegate(*this, FUNC(cps_state::cps1_dsw_r)));
	m_maincpu->space(AS_PROGRAM).install_write_handler(0x800180, 0x800187, write16s_delegate(*this, FUNC(cps_state::cps1_soundlatch_w)));
	m_maincpu->space(AS_PROGRAM).install_write_handler(0x980000, 0x98002f, write16sm_delegate(*this, FUNC(cps_state::kodb_layer_w)));

	/* the original game alternates between 2 sprite ram areas to achieve flashing sprites - the bootleg doesn't do the write to the register to achieve this
	mapping both sprite ram areas to the same bootleg sprite ram - similar to how sf2mdt works */
	m_bootleg_sprite_ram = std::make_unique<u16[]>(0x2000);
	m_maincpu->space(AS_PROGRAM).install_ram(0x900000, 0x903fff, m_bootleg_sprite_ram.get());
	m_maincpu->space(AS_PROGRAM).install_ram(0x904000, 0x907fff, m_bootleg_sprite_ram.get()); /* both of these need to be mapped */

	init_cps1();
}



// ************************************************************************* KNIGHTSB

/*

CPU:

1x MC68000P12 ic65 main
1x Z0840006PSC ic1 sound
1x YM2151 ic29 sound
1x YM3012 ic30 sound
2x LM324 ic15,ic31 sound
2x M5205 ic184,ic185 sound
1x TDA2003 ic14 sound
1x oscillator 24.000000MHz (close to main)
1x oscillator 29.821000MHz (close to sound)

ROMs

5x M27C2001 1,2,3,4,5 dumped
4x maskrom KA,KB,KC,KD not dumped

RAMs:

4x KM62256ALP ic112,ic113,ic168,ic170
1x SYC6116L ic24
1x MCM2018AN ic7,ic8,ic51,ic56,ic70,ic71,ic77,ic78

PLDs:

1x TPC1020AFN ic116 read protected
3x GAL20V8A ic120,ic121,ic169 read protected
3x GAL16V8A ic7,ic72,ic80 read protected

Note:

1x JAMMA edge connector
2x 10 legs connector
1x trimmer (volume)
3x 8x2 switches DIP

*/
/* bootleg */
/* FIXME - GFX ROMs are wrong, copied from the other version */
/* ROMs missing are KA.IC91 KB.IC92 KC.IC93 KD.IC94 */
ROM_START( knightsb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "3.ic173",    0x00001, 0x40000, CRC(c9c6e720) SHA1(e8a1cd73458b548e88fc49d8f659e0dc33a8e756) )
	ROM_LOAD16_BYTE( "5.ic172",    0x00000, 0x40000, CRC(7fd91118) SHA1(d2832b21309a467938891946d7af35d8095787a4) )
	ROM_LOAD16_BYTE( "2.ic175",    0x80001, 0x40000, CRC(1eb91343) SHA1(e02cfbbd7689346f14f2e3455ed17e7f0b51bad0) )
	ROM_LOAD16_BYTE( "4.ic176",    0x80000, 0x40000, CRC(af352703) SHA1(7855ac65752203f45af4ef41af8c291540a1c8a8) )

	ROM_REGION( 0x400000, "gfx", 0 ) /* bootleg had 4x 1meg mask ROMs, these need dumping so that the format is known */
	ROM_LOAD64_WORD( "kr_gfx1.rom",  0x000000, 0x80000, BAD_DUMP CRC(9e36c1a4) SHA1(772daae74e119371dfb76fde9775bda78a8ba125) )
	ROM_LOAD64_WORD( "kr_gfx3.rom",  0x000002, 0x80000, BAD_DUMP CRC(c5832cae) SHA1(a188cf401cd3a2909b377d3059f14d22ec3b0643) )
	ROM_LOAD64_WORD( "kr_gfx2.rom",  0x000004, 0x80000, BAD_DUMP CRC(f095be2d) SHA1(0427d1574062f277a9d04440019d5638b05de561) )
	ROM_LOAD64_WORD( "kr_gfx4.rom",  0x000006, 0x80000, BAD_DUMP CRC(179dfd96) SHA1(b1844e69da7ab13474da569978d5b47deb8eb2be) )
	ROM_LOAD64_WORD( "kr_gfx5.rom",  0x200000, 0x80000, BAD_DUMP CRC(1f4298d2) SHA1(4b162a7f649b0bcd676f8ca0c5eee9a1250d6452) )
	ROM_LOAD64_WORD( "kr_gfx7.rom",  0x200002, 0x80000, BAD_DUMP CRC(37fa8751) SHA1(b88b39d1f08621f15a5620095aef998346fa9891) )
	ROM_LOAD64_WORD( "kr_gfx6.rom",  0x200004, 0x80000, BAD_DUMP CRC(0200bc3d) SHA1(c900b1be2b4e49b951e5c1e3fd1e19d21b82986e) )
	ROM_LOAD64_WORD( "kr_gfx8.rom",  0x200006, 0x80000, BAD_DUMP CRC(0bb2b4e7) SHA1(983b800925d58e4aeb4e5105f93ed5faf66d009c) )

	ROM_REGION( 0x50000, "audiocpu", 0 ) /* 64k for the audio CPU (+banks) */
	ROM_LOAD( "1.ic26",     0x00000, 0x40000, CRC(bd6f9cc1) SHA1(9f33cccef224d2204736a9eae761196866bd6e41) )
	ROM_RELOAD(            0x10000, 0x40000 )
ROM_END

ROM_START( knightsb3 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "5.bin", 0x00000, 0x80000, CRC(b818272c) SHA1(680b1539bbeebf26706c9367decce2a8de0144e4) )  // 27c040
	ROM_LOAD16_BYTE( "3.bin", 0x00001, 0x80000, CRC(b0b9a4c2) SHA1(7d49b260224756303f9c6cdb67e8c531b0f5689f) )  // 27c040

	ROM_REGION( 0x400000, "gfx", 0 ) // = knights but arranged differently
	ROM_LOAD64_BYTE( "svr-01.bin", 0x000000, 0x40000, CRC(b08dc61f) SHA1(9527636ba0ccc7f02db6ba7013e932582ff85a93) )
	ROM_CONTINUE(                  0x000004, 0x40000)
	ROM_LOAD64_BYTE( "svr-02.bin", 0x000001, 0x40000, CRC(cca262aa) SHA1(587b25a724a89095299bd1f655d833d26a420c30) )
	ROM_CONTINUE(                  0x000005, 0x40000)
	ROM_LOAD64_BYTE( "svr-03.bin", 0x000002, 0x40000, CRC(1fe7056c) SHA1(eb9e5955c6cf2cfef565672cd0efcfd6921fefc3) )
	ROM_CONTINUE(                  0x000006, 0x40000)
	ROM_LOAD64_BYTE( "svr-04.bin", 0x000003, 0x40000, CRC(b29ce7cf) SHA1(d8f99c57561c60bec260c6b5daef81ba7856b547) )
	ROM_CONTINUE(                  0x000007, 0x40000)
	ROM_LOAD64_BYTE( "svr-05.bin", 0x200000, 0x40000, CRC(1c774671) SHA1(d553b87e8a0f13f404cff64089847325a18d1afb) )
	ROM_CONTINUE(                  0x200004, 0x40000)
	ROM_LOAD64_BYTE( "svr-06.bin", 0x200001, 0x40000, CRC(05463aa3) SHA1(27cc2724e22bf74e972283d6c35d31cea2c1a943) )
	ROM_CONTINUE(                  0x200005, 0x40000)
	ROM_LOAD64_BYTE( "svr-07.bin", 0x200002, 0x40000, CRC(87944aaa) SHA1(57d4637d5cf10b9cef95e12c64362c04a604cf64) )
	ROM_CONTINUE(                  0x200006, 0x40000)
	ROM_LOAD64_BYTE( "svr-08.bin", 0x200003, 0x40000, CRC(aa9d82fb) SHA1(41ff75bc0cc3766c19d79080893b52d9c759a443) )
	ROM_CONTINUE(                  0x200007, 0x40000)

	// TODO: dump
	ROM_REGION( 0x50000, "audiocpu", 0 )
	ROM_LOAD( "1.ic26", 0x00000, 0x40000, CRC(bd6f9cc1) SHA1(9f33cccef224d2204736a9eae761196866bd6e41) )  // knightsb
	ROM_RELOAD( 0x10000, 0x40000 )

	ROM_REGION( 0x400, "user1", 0 )
	ROM_LOAD( "1_palce20v8.bin", 0x000, 0x157, CRC(a5078c38) SHA1(59558a514ec60cd7148ede78a5641f5e6c0479c8) )
	ROM_LOAD( "2_palce16v8.bin", 0x200, 0x117, CRC(bad3316b) SHA1(b25141540fbaab028ba563f4fe1796b6039a4d59) )
ROM_END

// ************************************************************************* CAWINGBL, CAWINGB2

ROM_START( cawingbl )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "caw2.bin", 0x00000, 0x80000, CRC(8125d3f0) SHA1(a0e48c326c6164ca189c9372f5c38a7c103772c1) )
	ROM_LOAD16_BYTE( "caw1.bin", 0x00001, 0x80000, CRC(b19b10ce) SHA1(3c71f1dc830d1e8b8ba26d8a71e12f477659480c) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD32_BYTE( "caw7.bin", 0x000000, 0x80000, CRC(a045c689) SHA1(8946c55635121282ea03586a278e50de20d92633) )
	ROM_LOAD32_BYTE( "caw6.bin", 0x000001, 0x80000, CRC(61192f7c) SHA1(86643c62653a62a5c7541d50cfdecae9b607440d) )
	ROM_LOAD32_BYTE( "caw5.bin", 0x000002, 0x80000, CRC(30dd78db) SHA1(e0295001d6f5fb4a9276c432f971e88f73c5e39a) )
	ROM_LOAD32_BYTE( "caw4.bin", 0x000003, 0x80000, CRC(4937fc41) SHA1(dac179715be483a521df8e515afc1fb7a2cd8f13) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* 64k for the audio CPU (+banks) */
	ROM_LOAD( "caw3.bin", 0x00000, 0x20000, CRC(ffe16cdc) SHA1(8069ea69f0b89d61c35995c8040a4989d7be9c1f) )
	ROM_RELOAD(           0x10000, 0x20000 )
ROM_END

ROM_START( cawingb2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "8.8", 0x00000, 0x20000, CRC(f655708c) SHA1(9962a1c96ea08bc71b25d4f58e5d1fb1beebf0dc) )
	ROM_LOAD16_BYTE( "4.4", 0x00001, 0x20000, CRC(a02fb5aa) SHA1(c9c064a83899c48f681ac803cfc5886503b9d992) )
	ROM_LOAD16_BYTE( "7.7", 0x40000, 0x20000, CRC(8c6c7430) SHA1(3ed5713caf774b050b41a6adea026e1307b570df) )
	ROM_LOAD16_BYTE( "3.3", 0x40001, 0x20000, CRC(f585bf2c) SHA1(3a3169791f8deace8d9bee1adb08f19fbcd309c6) )
	ROM_LOAD16_BYTE( "6.6", 0x80000, 0x20000, CRC(5fda906e) SHA1(7b3ef17d494a2f92e58ab7e34a3beaad8c149fca) )
	ROM_LOAD16_BYTE( "2.2", 0x80001, 0x20000, CRC(736c1835) SHA1(a91f479fab30603a111304adc0478d430faa80fc) )
	ROM_LOAD16_BYTE( "5.5", 0xc0000, 0x20000, CRC(76458083) SHA1(cbb4ef5f7615c834b2ee1ad3c86e7262f2f62c01) )
	ROM_LOAD16_BYTE( "1.1", 0xc0001, 0x20000, CRC(d3523f34) SHA1(005ea378c2b78782f85ecc591946c027ca2ca023) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD32_BYTE( "17.17", 0x000000, 0x20000, CRC(0b538062) SHA1(ac6e5dc82efdca311adfe6e6cdda160ad4a0d04d) )
	ROM_LOAD32_BYTE( "19.19", 0x000001, 0x20000, CRC(3ad62311) SHA1(1c132696b55191d16af30ebd36d2320d979eab36) )
	ROM_LOAD32_BYTE( "21.21", 0x000002, 0x20000, CRC(1b872a98) SHA1(7a3f72c6d384dfa8e224f93604997a7b6e5c8926) )
	ROM_LOAD32_BYTE( "23.23", 0x000003, 0x20000, CRC(ad49eecd) SHA1(39909996765391ed734a02c74f683e1bd9ce1561) )
	ROM_LOAD32_BYTE( "9.9",   0x080000, 0x20000, CRC(8cd4df5b) SHA1(771b6d6a6baa95a669335fe64e2219fe7226e140) )
	ROM_LOAD32_BYTE( "11.11", 0x080001, 0x20000, CRC(bf14418a) SHA1(7a0e1c65b8825a252338d6c1db59a88966ec6cfb) )
	ROM_LOAD32_BYTE( "13.13", 0x080002, 0x20000, CRC(cef1aab8) SHA1(677a889b939ff00e95737a4a53053744bb6744c0) )
	ROM_LOAD32_BYTE( "15.15", 0x080003, 0x20000, CRC(397725dc) SHA1(9450362bbf2f91b4225a088d6e283d7b16407b74) )
	ROM_LOAD32_BYTE( "18.18", 0x100000, 0x20000, CRC(9b14f7ed) SHA1(72b6e1174d4faab487261aa6739de842d2423e1a) )
	ROM_LOAD32_BYTE( "20.20", 0x100001, 0x20000, CRC(59bcc1bb) SHA1(c725060e068294dea1d962c54a9018050fa70297) )
	ROM_LOAD32_BYTE( "22.22", 0x100002, 0x20000, CRC(23dc647a) SHA1(2d8d4c4c7b2d0616430360d1639b07216dd731d6) )
	ROM_LOAD32_BYTE( "24.24", 0x100003, 0x20000, CRC(eda9fa6b) SHA1(4a3510ce71b015a1ea568fd0bbe61c5c093a2fbf) )
	ROM_LOAD32_BYTE( "10.10", 0x180000, 0x20000, CRC(17174249) SHA1(71c6424ab4629065dd6af8bb47b18f5b5d0fbe49) )
	ROM_LOAD32_BYTE( "12.12", 0x180001, 0x20000, CRC(490440b2) SHA1(2597bf16340308f84b32cfa048c426db571b4a35) )
	ROM_LOAD32_BYTE( "14.14", 0x180002, 0x20000, CRC(344a8270) SHA1(fdb588a7ba60783225e3b5c72446f79625de4f9c) )
	ROM_LOAD32_BYTE( "16.16", 0x180003, 0x20000, CRC(b991ad91) SHA1(5c59131ddf068cb54d23f8836293360fbc967d58) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* 64k for the audio CPU (+banks) */
	ROM_LOAD( "5.a", 0x00000, 0x20000, CRC(ffe16cdc) SHA1(8069ea69f0b89d61c35995c8040a4989d7be9c1f) )
	ROM_RELOAD(      0x10000, 0x20000 )
ROM_END

void cps_state::init_cawingbl()
{
	m_maincpu->space(AS_PROGRAM).install_read_port(0x882000, 0x882001, "IN1");
	m_maincpu->space(AS_PROGRAM).install_write_handler(0x882006, 0x882007, write16s_delegate(*this, FUNC(cps_state::cawingbl_soundlatch_w)));
	m_maincpu->space(AS_PROGRAM).install_read_handler(0x882008, 0x88200f, read16sm_delegate(*this, FUNC(cps_state::cps1_dsw_r)));

	init_cps1();
}

// HBMAME start
ROM_START( cawingb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "2.16d",  0x00000, 0x80000, CRC(8125d3f0) SHA1(a0e48c326c6164ca189c9372f5c38a7c103772c1) )
	ROM_LOAD16_BYTE( "1.19d",  0x00001, 0x80000, CRC(b19b10ce) SHA1(3c71f1dc830d1e8b8ba26d8a71e12f477659480c) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "ca-5m.7a", 0x000000, 0x80000, CRC(66d4cc37) SHA1(d355ea64ff29d228dcbfeee72bcf11882bf1cd9d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ca-7m.9a", 0x000002, 0x80000, CRC(b6f896f2) SHA1(bdb6820b81fbce77d7eacb01777af7c380490402) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ca-1m.3a", 0x000004, 0x80000, CRC(4d0620fd) SHA1(5f62cd551b6a230edefd81fa60c10c84186ca804) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ca-3m.5a", 0x000006, 0x80000, CRC(0b0341c3) SHA1(c31f0e78f49d94ea9dea20eb0cbd98a6c613bcbf) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 ) /* 64k for the audio CPU (+banks) */
	ROM_LOAD( "ca_9.12b",  0x00000, 0x08000, CRC(96fe7485) SHA1(10466889dfc6bc8afd3075385e241a16372efbeb) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 ) /* Samples */
	ROM_LOAD( "ca_18.11c", 0x00000, 0x20000, CRC(4a613a2c) SHA1(06e10644fc60925b85d2ca0888c9fa057bfe996a) )
	ROM_LOAD( "ca_19.12c", 0x20000, 0x20000, CRC(74584493) SHA1(5cfb15f1b9729323707972646313aee8ab3ac4eb) )
ROM_END
// HBMAME end


// ************************************************************************* DINOPIC, DINOPIC2

MACHINE_START_MEMBER(cps_state, dinopic)
{
	m_layer_enable_reg = 0x0a;
	m_layer_mask_reg[0] = 0x0c;
	m_layer_mask_reg[1] = 0x0e;
	m_layer_mask_reg[2] = 0x00;
	m_layer_mask_reg[3] = 0x02;
	m_layer_scroll1x_offset = 0x40;
	m_layer_scroll2x_offset = 0x40;
	m_layer_scroll3x_offset = 0x40;
	m_sprite_base = 0x1000;
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = 0;
}

void cps_state::dinopic(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 12000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::dinopic_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	//PIC16C57(config, m_audiocpu, 12000000).set_disable(); /* no valid dumps .. */

	MCFG_MACHINE_START_OVERRIDE(cps_state, dinopic)

	EEPROM_93C46_8BIT(config, "eeprom");

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1 );
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state,cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);

	OKIM6295(config, m_oki, 1000000, okim6295_device::PIN7_HIGH).add_route(ALL_OUTPUTS, "mono", 0.30);
}

/*

Cadillac Bootleg Hardware:

1x 68000p10
1x PIC16c57
1x AD-65
1x OSC 30mhz
1x OSC 24mhz
13x 27c4000 ROMS

*/
ROM_START( dinopic )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "3.bin", 0x000001, 0x80000, CRC(13dfeb08) SHA1(cd2f9dd64f4fabe93901247e36dff3763169716d) )
	ROM_LOAD16_BYTE( "5.bin", 0x000000, 0x80000, CRC(96dfcbf1) SHA1(a8bda6edae2c1b79db7ae8a8976fd2457f874373) )
	ROM_LOAD16_BYTE( "2.bin", 0x100001, 0x80000, CRC(0e4058ba) SHA1(346f9e34ea53dd1bf5cdafa1e38bf2edb09b9a7f) )
	ROM_LOAD16_BYTE( "7.bin", 0x100000, 0x80000, CRC(6133f349) SHA1(d13af99910623f62c090d25372a2253dbc2f8cbe) )

	ROM_REGION( 0x400000, "gfx", 0 ) // same data, different format, except for 8 which is a 99% match (bad ROM?)
	ROM_LOAD64_BYTE( "4.bin",  0x000000, 0x40000, CRC(f3c2c98d) SHA1(98ae51a67fa4159456a4a205eebdd8d1775888d1) )
	ROM_CONTINUE(              0x000004, 0x40000)
	ROM_LOAD64_BYTE( "8.bin",  0x000001, 0x40000, CRC(d574befc) SHA1(56482e7a9aa8439f30e3cf72311495ce677a083d) )
	ROM_CONTINUE(              0x000005, 0x40000)
	ROM_LOAD64_BYTE( "9.bin",  0x000002, 0x40000, CRC(55ef0adc) SHA1(3b5551ae76ae80882d37fc70a1031a57885d6840) )
	ROM_CONTINUE(              0x000006, 0x40000)
	ROM_LOAD64_BYTE( "6.bin",  0x000003, 0x40000, CRC(cc0805fc) SHA1(c512734c28b878a30a0de249929f69784d5d77a1) )
	ROM_CONTINUE(              0x000007, 0x40000)
	ROM_LOAD64_BYTE( "13.bin", 0x200000, 0x40000, CRC(1371f714) SHA1(d2c98096fab08e3d4fd2482e6ebfc970ead656ee) )
	ROM_CONTINUE(              0x200004, 0x40000)
	ROM_LOAD64_BYTE( "12.bin", 0x200001, 0x40000, CRC(b284c4a7) SHA1(166f571e0afa115f8e38ba427b40e30abcfd70ee) )
	ROM_CONTINUE(              0x200005, 0x40000)
	ROM_LOAD64_BYTE( "11.bin", 0x200002, 0x40000, CRC(b7ad3394) SHA1(58dec34d9d991ff2817c8a7847749716abae6c77) )
	ROM_CONTINUE(              0x200006, 0x40000)
	ROM_LOAD64_BYTE( "10.bin", 0x200003, 0x40000, CRC(88847705) SHA1(05dc90067921960e417b7436056a5e1f86abaa1a) )
	ROM_CONTINUE(              0x200007, 0x40000)

	ROM_REGION( 0x28000, "audiocpu", 0 ) /* PIC16c57 - protected, dump isn't valid */
	ROM_LOAD( "pic16c57-rp", 0x00000, 0x2d4c, BAD_DUMP CRC(5a6d393c) SHA1(1391a1590aff5f75bb6fae1c83eddb796b53135d) )

	ROM_REGION( 0x80000, "oki", 0 ) /* OKI6295 samples */
	ROM_LOAD( "1.bin", 0x000000, 0x80000,  CRC(7d921309) SHA1(d51e60e904d302c2516b734189e141aa171b2b82) )
ROM_END

/* this is basically the same set as above, from a different bootleg pcb, with a few extra pal dumps etc.
   the first dump will probably be removed eventually

  CPU
  1x TS68000CP10 (main)
  1x AD-65 (sound)(equivalent to M6295)
  1x PIC16C57-XT/P
  1x A1020B-PL84C
  1x oscillator 24.000MHz (close to main)
  1x oscillator 30.000MHz (close to sound)

  ROMs
  13x 27C4000
  3x GAL20V8A
  3x PALCE16V8H (1 broken not dumped)
  1x CAT93C46P

  Note
  1x JAMMA edge connector
  1x 10 legs connector
  1x trimmer (volume)
*/

ROM_START( dinopic2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "27c4000-m12374r-2.bin", 0x000001, 0x80000, CRC(13dfeb08) SHA1(cd2f9dd64f4fabe93901247e36dff3763169716d) )
	ROM_LOAD16_BYTE( "27c4000-m12481.bin",    0x000000, 0x80000, CRC(96dfcbf1) SHA1(a8bda6edae2c1b79db7ae8a8976fd2457f874373) )
	ROM_LOAD16_BYTE( "27c4000-m12374r-1.bin", 0x100001, 0x80000, CRC(0e4058ba) SHA1(346f9e34ea53dd1bf5cdafa1e38bf2edb09b9a7f) )
	ROM_LOAD16_BYTE( "27c4000-m12374r-3.bin", 0x100000, 0x80000, CRC(6133f349) SHA1(d13af99910623f62c090d25372a2253dbc2f8cbe) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROM_LOAD64_BYTE( "27c4000-m12481-4.bin", 0x000000, 0x40000, CRC(f3c2c98d) SHA1(98ae51a67fa4159456a4a205eebdd8d1775888d1) )
	ROM_CONTINUE(                            0x000004, 0x40000)
	ROM_LOAD64_BYTE( "27c4000-m12481-3.bin", 0x000001, 0x40000, CRC(a0e1f6e0) SHA1(119af72fb6e75933b6d39bc4a8030823ce9b7611) ) // this one is a perfect match, unlike dinopic set
	ROM_CONTINUE(                            0x000005, 0x40000)
	ROM_LOAD64_BYTE( "27c4000-m12481-2.bin", 0x000002, 0x40000, CRC(55ef0adc) SHA1(3b5551ae76ae80882d37fc70a1031a57885d6840) )
	ROM_CONTINUE(                            0x000006, 0x40000)
	ROM_LOAD64_BYTE( "27c4000-m12481-1.bin", 0x000003, 0x40000, CRC(cc0805fc) SHA1(c512734c28b878a30a0de249929f69784d5d77a1) )
	ROM_CONTINUE(                            0x000007, 0x40000)
	ROM_LOAD64_BYTE( "27c4000-m12481-8.bin", 0x200000, 0x40000, CRC(1371f714) SHA1(d2c98096fab08e3d4fd2482e6ebfc970ead656ee) )
	ROM_CONTINUE(                            0x200004, 0x40000)
	ROM_LOAD64_BYTE( "27c4000-m12481-7.bin", 0x200001, 0x40000, CRC(b284c4a7) SHA1(166f571e0afa115f8e38ba427b40e30abcfd70ee) )
	ROM_CONTINUE(                            0x200005, 0x40000)
	ROM_LOAD64_BYTE( "27c4000-m12481-6.bin", 0x200002, 0x40000, CRC(b7ad3394) SHA1(58dec34d9d991ff2817c8a7847749716abae6c77) )
	ROM_CONTINUE(                            0x200006, 0x40000)
	ROM_LOAD64_BYTE( "27c4000-m12481-5.bin", 0x200003, 0x40000, CRC(88847705) SHA1(05dc90067921960e417b7436056a5e1f86abaa1a) )
	ROM_CONTINUE(                            0x200007, 0x40000)

	ROM_REGION( 0x28000, "audiocpu", 0 ) /* PIC16c57 - protected, dump isn't valid */
	ROM_LOAD( "pic16c57-xt.hex", 0x00000, 0x26cc, BAD_DUMP CRC(a6a5eac4) SHA1(2039789084836769180f0bfd230c2553a37e2aaf) )

	ROM_REGION( 0x80000, "oki", 0 ) /* OKI6295 samples */
	ROM_LOAD( "27c4000-m12623.bin", 0x000000, 0x80000,  CRC(7d921309) SHA1(d51e60e904d302c2516b734189e141aa171b2b82) )

	ROM_REGION( 0xc00, "user1", 0 )
	ROM_LOAD( "gal20v8a-1.bin",   0x000, 0x157, CRC(cd99ca47) SHA1(ee1d990fd294aa46f56f31264134251569f6792e) )
	ROM_LOAD( "gal20v8a-2.bin",   0x200, 0x157, CRC(60d016b9) SHA1(add42c763c819f3fe6d7cf3adc7123a52c2a3be9) )
	ROM_LOAD( "gal20v8a-3.bin",   0x400, 0x157, CRC(049b7f4f) SHA1(6c6ea03d9a293db69a8bd10e042ee75e3c01313c) )
	ROM_LOAD( "palce16v8h-1.bin", 0x600, 0x117, CRC(48253c66) SHA1(8c94e655b768c45c3edf6ef39e62e3b7a4e57530) )
	ROM_LOAD( "palce16v8h-2.bin", 0x800, 0x117, CRC(9ae375ba) SHA1(6f227c2a5b1170a41e6419f12d1e1f98edc6f8e5) )
	ROM_LOAD( "palce16v8h-3.bin", 0xa00, 0x117, CRC(b0f10adf) SHA1(5136e9495ef6c37edb0ddf1fe70c0d48c4785c80) )
ROM_END

ROM_START( dinopic3 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 ) // = dinopic but arranged differently
	ROM_LOAD16_WORD_SWAP( "tk1-305_27c800.bin", 0x000000, 0x100000, CRC(aa468337) SHA1(496df3bd62cdea0b104f96a7988ad21c94a70c2b) )
	ROM_LOAD16_WORD_SWAP( "tk1-204_27c800.bin", 0x100000, 0x100000, CRC(0efd1ddb) SHA1(093cf7906eda36533c7021329c629ba5a995c5ee) )

	ROM_REGION( 0x400000, "gfx", 0 ) // = dino but arranged differently
	ROM_LOAD64_WORD("tb416-02_27c160.bin", 0x000000, 0x80000, CRC(bfd01d21) SHA1(945f2764b0ca7f9e1569a591363c70207e8efbd0) )
	ROM_CONTINUE( 0x200000, 0x80000 )
	ROM_CONTINUE( 0x000004, 0x80000 )
	ROM_CONTINUE( 0x200004, 0x80000 )
	ROM_LOAD64_WORD("tb415-01_27c160.bin", 0x000002, 0x80000, CRC(ef508ec5) SHA1(ebb521b51d7269b4a9b441bd44b6d5320a72aaaa) )
	ROM_CONTINUE( 0x200002, 0x80000 )
	ROM_CONTINUE( 0x000006, 0x80000 )
	ROM_CONTINUE( 0x200006, 0x80000 )

	ROM_REGION( 0x80000, "oki", 0 )
	ROM_LOAD( "ti-i_27c040.bin", 0x000000, 0x80000, CRC(7d921309) SHA1(d51e60e904d302c2516b734189e141aa171b2b82) )  // = dinopic, dinopic2

	ROM_REGION( 0xc00, "user1", 0 )
	ROM_LOAD( "1_palce20v8.bin", 0x000, 0x157, CRC(cd99ca47) SHA1(ee1d990fd294aa46f56f31264134251569f6792e) )  // dinopic2
	ROM_LOAD( "2_palce20v8.bin", 0x200, 0x157, CRC(60d016b9) SHA1(add42c763c819f3fe6d7cf3adc7123a52c2a3be9) )  // dinopic2
	ROM_LOAD( "3_palce20v8.bin", 0x400, 0x157, CRC(049b7f4f) SHA1(6c6ea03d9a293db69a8bd10e042ee75e3c01313c) )  // dinopic2
	ROM_LOAD( "4_palce16v8.bin", 0x600, 0x117, CRC(97a67c6d) SHA1(822411f878f1efe462a7a8e93960a1fc5140422e) )
	ROM_LOAD( "5_palce16v8.bin", 0x800, 0x117, CRC(48253c66) SHA1(8c94e655b768c45c3edf6ef39e62e3b7a4e57530) )  // dinopic2
	ROM_LOAD( "6_palce16v8.bin", 0xa00, 0x117, CRC(9ae375ba) SHA1(6f227c2a5b1170a41e6419f12d1e1f98edc6f8e5) )  // dinopic2
ROM_END

void cps_state::init_dinopic()
{
	m_bootleg_sprite_ram = std::make_unique<u16[]>(0x2000);
	m_maincpu->space(AS_PROGRAM).install_ram(0x990000, 0x993fff, m_bootleg_sprite_ram.get());
	init_cps1();
}

// The picture is offset to the left, no sound, no sprites. Most settings cannot be changed.
ROM_START( dinopic4 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "cad_28",   0x000000, 0x040000, CRC(97dc3d86) SHA1(8dbe9dab5682933b3ea2bfcd066f5f4503aad009) )
	ROM_LOAD16_BYTE( "cad_32",   0x000001, 0x040000, CRC(200a594f) SHA1(125bbf0f1cdc8740293cc3b73ac4bf82af24c0d5) )
	ROM_LOAD16_BYTE( "cad_29",   0x080000, 0x040000, CRC(302303c4) SHA1(42427215357f670d2943a8f09a2288cd4aacd14b) )
	ROM_LOAD16_BYTE( "cad_33",   0x080001, 0x040000, CRC(5bf6deda) SHA1(278f56a10db0f5975ac9ecc7b6e121c2f1dbfc94) )
	ROM_LOAD16_BYTE( "cad_31",   0x100000, 0x020000, CRC(f0110c8a) SHA1(eee714439a3802168c2cece91ed0e1e6ab630652) )
	ROM_LOAD16_BYTE( "cad_35",   0x100001, 0x020000, CRC(fbcf4314) SHA1(a59a1d867abea5216367220d8c9d005f451c9d88) )
	ROM_LOAD16_BYTE( "cad_30",   0x140000, 0x020000, CRC(bbcafc3b) SHA1(52ff5928b1da862813ef150ea77ac59cff82df5b) )
	ROM_LOAD16_BYTE( "cad_34",   0x140001, 0x020000, CRC(481369b8) SHA1(065b5f6b3d2f337def183c3ab5f0ef8c21d0c849) )
	ROM_FILL(0xbb3b8,1,0x4e) // kill protection
	ROM_FILL(0xbb3b9,1,0x71)

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cad_24",   0x000000, 0x040000, CRC(e59e0066) SHA1(de8868ac7c9323c9ce4a22d610f25e8932e09218), ROM_SKIP(7) )
	ROMX_LOAD( "cad_14",   0x000001, 0x040000, CRC(79b60fc5) SHA1(12519904ca235661a103f01918b8e713abbfb6f4), ROM_SKIP(7) )
	ROMX_LOAD( "cad_26",   0x000002, 0x040000, CRC(2db8cb57) SHA1(e4acc9e94067e3567e4a4b6c8439d5cc51cfbae0), ROM_SKIP(7) )
	ROMX_LOAD( "cad_16",   0x000003, 0x040000, CRC(569e5cf0) SHA1(c4b61d8c79d5d1dfd4079e57f444f7ac89a26422), ROM_SKIP(7) )
	ROMX_LOAD( "cad_20",   0x000004, 0x040000, CRC(779bffb2) SHA1(e591845761bf637d36764d84f7af84b1e3594f7b), ROM_SKIP(7) )
	ROMX_LOAD( "cad_10",   0x000005, 0x040000, CRC(9d5b2ed4) SHA1(4958fc59ca6dd45e82a1a9ea68ae40450f67badc), ROM_SKIP(7) )
	ROMX_LOAD( "cad_22",   0x000006, 0x040000, CRC(b58c4246) SHA1(fc3e705d025372edb3ded8840ff0157398897b8d), ROM_SKIP(7) )
	ROMX_LOAD( "cad_12",   0x000007, 0x040000, CRC(33ed501d) SHA1(f6f80e802444101bfcb38b1a27ed6a9b9e32ba3c), ROM_SKIP(7) )
	ROMX_LOAD( "cad_25",   0x200000, 0x040000, CRC(900b82b7) SHA1(c9b422daccaf793cd8fae5e3f88cbdfc757cc00b), ROM_SKIP(7) )
	ROMX_LOAD( "cad_15",   0x200001, 0x040000, CRC(aa54f07c) SHA1(b1a71d2efefec4fdf1eff61404d385d9f7d31468), ROM_SKIP(7) )
	ROMX_LOAD( "cad_27",   0x200002, 0x040000, CRC(27492fde) SHA1(2befbf43c316db072f63d771202c8e77b6e228ff), ROM_SKIP(7) )
	ROMX_LOAD( "cad_17",   0x200003, 0x040000, CRC(920df2fd) SHA1(7ad467e6ecf59a6b737ee5369ffcc4a5d203ea48), ROM_SKIP(7) )
	ROMX_LOAD( "cad_21",   0x200004, 0x040000, CRC(d65ee299) SHA1(bfad1473a05f4152dedefb5b8d10e7d27b4dc18a), ROM_SKIP(7) )
	ROMX_LOAD( "cad_11",   0x200005, 0x040000, CRC(8594b5e8) SHA1(10aca27488652da3c8421a8ea5acdfa7ec596e93), ROM_SKIP(7) )
	ROMX_LOAD( "cad_23",   0x200006, 0x040000, CRC(f07c16f2) SHA1(422ae1bcfe0a6704e374800d2af8cda69bd03138), ROM_SKIP(7) )
	ROMX_LOAD( "cad_13",   0x200007, 0x040000, CRC(07a564b4) SHA1(7be9f1a52eaa523a386d91d12ec0ddca716c363c), ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 ) // first and 2nd half identical
	ROM_LOAD( "cad_09",    0x00000, 0x08000, CRC(46546432) SHA1(c37527f663713464f837295625345d485855122e) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cad_18",    0x00000, 0x20000, CRC(bd12c2ce) SHA1(4bb4d854be7aff2516241ba56f431a5464854be2) )
	ROM_LOAD( "cad_19",    0x20000, 0x20000, CRC(9233de5a) SHA1(c20f596648963ddf62a4452741cc9ad8b11f2ca2) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( jurassic99 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "210204_rom2.bin",  0x000000, 0x100000, CRC(3f713043) SHA1(90e81c651772e895a56146c986c64ff8c35826ac) )
	ROM_LOAD16_WORD_SWAP( "210105a_rom1.bin", 0x100000, 0x100000, CRC(e6294edf) SHA1(4f9515e2e060dad165f6cb513baee2568c82c1be) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROM_LOAD64_WORD("210101a_cda2.bin", 0x000000, 0x80000, CRC(3f167412) SHA1(2636065b37998d5c3008edc1c13d073305132f4f) )
	ROM_CONTINUE( 0x000004, 0x80000 )
	ROM_CONTINUE( 0x200000, 0x80000 )
	ROM_CONTINUE( 0x200004, 0x80000 )
	ROM_LOAD64_WORD("210102_cdb2.bin",  0x000002, 0x80000, CRC(8a6920d8) SHA1(099bfc37b524f60c82332c83c3f1af411b14e35a) )
	ROM_CONTINUE( 0x000006, 0x80000 )
	ROM_CONTINUE( 0x200002, 0x80000 )
	ROM_CONTINUE( 0x200006, 0x80000 )

	// EMC EM78P447AP, secured
	//ROM_REGION( 0x3000, "audiocpu", 0 )
	//ROM_LOAD( "u28.bin", 0x0000, 0x2020, NO_DUMP )
	
	ROM_REGION( 0x80000, "oki", 0 )
	ROM_LOAD( "21003_u27.bin", 0x000000, 0x80000, CRC(7d921309) SHA1(d51e60e904d302c2516b734189e141aa171b2b82) )  // == dinopic, dinopic2, dinopic3

	ROM_REGION( 0x1600, "user1", 0 )
	ROM_LOAD( "1_atf20v8.u25",   0x0000, 0x157, CRC(cd99ca47) SHA1(ee1d990fd294aa46f56f31264134251569f6792e) )  // == dinopic2 #20-1, dinopic3 #1
	ROM_LOAD( "2_atf16v8.u66",   0x0200, 0x117, CRC(48253c66) SHA1(8c94e655b768c45c3edf6ef39e62e3b7a4e57530) )  // == dinopic2 #16-1, dinopic3 #5
	ROM_LOAD( "3_atf16v8.u100",  0x0400, 0x117, CRC(9ae375ba) SHA1(6f227c2a5b1170a41e6419f12d1e1f98edc6f8e5) )  // == dinopic2 #16-2, dinopic3 #6
	ROM_LOAD( "4_atf20v8.u118",  0x0600, 0x157, CRC(60d016b9) SHA1(add42c763c819f3fe6d7cf3adc7123a52c2a3be9) )  // == dinopic2 #20-2, dinopic3 #2
	ROM_LOAD( "5_atf20v8.u146",  0x0800, 0x157, CRC(049b7f4f) SHA1(6c6ea03d9a293db69a8bd10e042ee75e3c01313c) )  // == dinopic2 #20-3, dinopic3 #3
	ROM_LOAD( "6_atf16v8.u160",  0x0a00, 0x117, CRC(b0f10adf) SHA1(5136e9495ef6c37edb0ddf1fe70c0d48c4785c80) )  // == dinopic2 #16-3
	ROM_LOAD( "8_atf16v8.u96g",  0x0c00, 0x117, BAD_DUMP CRC(11f38ab7) SHA1(4c21b199410a57d6a6a0d9a528b590fefa844856) )  // hand-crafted, works ok on real board
	ROM_LOAD( "8_atf16v8.u97g",  0x0e00, 0x117, BAD_DUMP CRC(11f38ab7) SHA1(4c21b199410a57d6a6a0d9a528b590fefa844856) )
	ROM_LOAD( "8_atf16v8.u98g",  0x1000, 0x117, BAD_DUMP CRC(11f38ab7) SHA1(4c21b199410a57d6a6a0d9a528b590fefa844856) )
	ROM_LOAD( "8_atf16v8.u99g",  0x1200, 0x117, BAD_DUMP CRC(11f38ab7) SHA1(4c21b199410a57d6a6a0d9a528b590fefa844856) )
	ROM_LOAD( "8_atf16v8.u134g", 0x1400, 0x117, BAD_DUMP CRC(11f38ab7) SHA1(4c21b199410a57d6a6a0d9a528b590fefa844856) )
ROM_END

// ************************************************************************* MTWINSB

static INPUT_PORTS_START( cps1_3b )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN1")
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

static INPUT_PORTS_START( mtwins )
	PORT_INCLUDE( cps1_3b )

	PORT_MODIFY("IN0")
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )

	PORT_START("DSWA")
	CPS1_COINAGE_1
	PORT_DIPUNUSED_DIPLOC( 0x40, 0x40, "SW(A):7" )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(A):8" )

	PORT_START("DSWB")
	CPS1_DIFFICULTY_1( "SW(B)" )
	PORT_DIPNAME( 0x38, 0x18, DEF_STR( Lives ) )            PORT_DIPLOCATION("SW(B):4,5,6")
//  PORT_DIPSETTING(    0x30, "1" )                         // 0x38 energy, smallest damage
//  PORT_DIPSETTING(    0x38, "1" )                         // 0x38 energy, small damage
//  PORT_DIPSETTING(    0x28, "1" )                         // 0x38 energy, big damage
//  PORT_DIPSETTING(    0x20, "1" )                         // 0x38 energy, biggest damage
	PORT_DIPSETTING(    0x10, "1" )                         // 0x20 energy, smallest damage
	PORT_DIPSETTING(    0x18, "2" )                         // 0x20 energy, small damage
	PORT_DIPSETTING(    0x08, "3" )                         // 0x20 energy, big damage
	PORT_DIPSETTING(    0x00, "4" )                         // 0x20 energy, biggest damage
	PORT_DIPUNUSED_DIPLOC( 0x40, 0x40, "SW(B):7" )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(B):8" )

	PORT_START("DSWC")
	PORT_DIPUNUSED_DIPLOC( 0x01, 0x01, "SW(C):1" )
	PORT_DIPUNUSED_DIPLOC( 0x02, 0x02, "SW(C):2" )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Free_Play ) )        PORT_DIPLOCATION("SW(C):3")
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, "Freeze" )                    PORT_DIPLOCATION("SW(C):4")
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Flip_Screen ) )      PORT_DIPLOCATION("SW(C):5")
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x00, DEF_STR( Demo_Sounds ) )      PORT_DIPLOCATION("SW(C):6")
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Allow_Continue ) )   PORT_DIPLOCATION("SW(C):7")
	PORT_DIPSETTING(    0x40, DEF_STR( No ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Yes ) )
	PORT_DIPNAME( 0x80, 0x80, "Game Mode")                  PORT_DIPLOCATION("SW(C):8")
	PORT_DIPSETTING(    0x80, "Game" )
	PORT_DIPSETTING(    0x00, DEF_STR( Test ) )
INPUT_PORTS_END

ROM_START( mtwinsb ) // board marked MGT-026
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "1-prg-27c4001.bin",     0x00001, 0x80000, CRC(8938a029) SHA1(50104d2afaec8d69d317780c071a4f2248e23e62) )
	ROM_LOAD16_BYTE( "2-prg-27c4001.bin",     0x00000, 0x80000, CRC(7d5b8a97) SHA1(d3e456061a569765d400fc7c9b43e4fdacf17951) )

	ROM_REGION( 0x200000, "gfx", 0 ) // identical to the original, but differently arranged
	ROM_LOAD64_BYTE( "g4.bin",  0x000004, 0x40000, CRC(11493e55) SHA1(0e45f53b034d66ce8d029346d4d88e46021df1a7) )
	ROM_CONTINUE(               0x000000, 0x40000)
	ROM_LOAD64_BYTE( "g3.bin",  0x000005, 0x40000, CRC(feda0f8b) SHA1(59c740478791ce95bf06feeda5173cc283a1eaea) )
	ROM_CONTINUE(               0x000001, 0x40000)
	ROM_LOAD64_BYTE( "g2.bin",  0x000006, 0x40000, CRC(745f0eba) SHA1(1cb07be5df7cc43b5aa236f114d303bf92436c74) )
	ROM_CONTINUE(               0x000002, 0x40000)
	ROM_LOAD64_BYTE( "g1.bin",  0x000007, 0x40000, CRC(8069026f) SHA1(3d5e9b36a349328bcd93d83d8d2fe3cd40e68a3b) )
	ROM_CONTINUE(               0x000003, 0x40000)

	ROM_REGION( 0x18000, "audiocpu", 0 ) /* 64k for the audio CPU (+banks) */
	ROM_LOAD( "4-snd-z80-27c512.bin", 0x00000, 0x08000, CRC(4d4255b7) SHA1(81a76b58043af7252a854b7efc4109957ef0e679) ) // identical to the original
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 ) /* Samples */
	ROM_LOAD( "3-snd-27c208.bin", 0x00000, 0x40000, CRC(a0c3de92) SHA1(5135cd982564f898f799ff1bc2bb2a75154be0cd) ) // identical to the original, but one single bigger ROM
ROM_END

void cps_state::init_mtwinsb()
{
	m_bootleg_sprite_ram = std::make_unique<u16[]>(0x2000);
	m_maincpu->space(AS_PROGRAM).install_ram(0x990000, 0x993fff, m_bootleg_sprite_ram.get());
	init_cps1();
}


// ************************************************************************* SGYXZ

// 24mhz crystal (maincpu), 28.322 crystal (video), 3.579545 crystal (sound)
// sound cpu is (239 V 249521 VC5006 KABUKI DL-030P-110V) - recycled Kabuki Z80 from genuine Capcom HW?
// 3x8 dsws

void cps_state::sgyxz(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 12000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sgyxz_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, 3579545);
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::sgyxz_sound_map);

	MCFG_MACHINE_START_OVERRIDE(cps_state,sgyxz)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1 );
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);
	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state, cps1)

	EEPROM_93C46_8BIT(config, "eeprom");

	/* sound hardware */
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);
	GENERIC_LATCH_8(config, m_soundlatch2);

	ym2151_device &ym2151(YM2151(config, "2151", XTAL(3'579'545)));  /* verified on pcb */
	ym2151.irq_handler().set_inputline(m_audiocpu, 0);
	ym2151.add_route(0, "mono", 0.35);
	ym2151.add_route(1, "mono", 0.35);

	/* CPS PPU is fed by a 16mhz clock,pin 117 outputs a 4mhz clock which is divided by 4 using 2 74ls74 */
	OKIM6295(config, m_oki, XTAL(16'000'000)/4/4, okim6295_device::PIN7_HIGH).add_route(ALL_OUTPUTS, "mono", 0.30); // pin 7 can be changed by the game code, see f006 on z80
}

void cps_state::wofabl(machine_config &config)
{
	sgyxz(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::wofabl_map);
}

void cps_state::wofabl_map(address_map &map)
{
	map(0x000000, 0x1fffff).rom();
	map(0x800030, 0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100, 0x80013f).ram().share("cps_a_regs");  /* CPS-A custom */
	map(0x800140, 0x80017f).ram().share("cps_b_regs");  /* CPS-B custom */
	map(0x880000, 0x880001).portr("IN1");            /* Player input ports */
	map(0x880006, 0x880007).w(FUNC(cps_state::cps1_soundlatch_w));
	map(0x880008, 0x880009).portr("IN0");                                   /* System input ports + Player 3 controls */
	map(0x88000a, 0x88000f).r(FUNC(cps_state::cps1_dsw_r));            /* Dip Switches */
	map(0x890000, 0x890001).w(FUNC(cps_state::cps1_soundlatch2_w));
	map(0x900000, 0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf1c004, 0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));     /* Coin control2 (later games) */
	map(0xf1c006, 0xf1c007).noprw();  // doesn't have an eeprom
	map(0xff0000, 0xffffff).ram().share("mainram");
}

ROM_START( sgyxz )
	ROM_REGION( CODE_SIZE, "maincpu", 0 ) /* 68000 Code */
	ROM_LOAD16_BYTE( "sgyxz_prg1.bin", 0x000001, 0x20000, CRC(d8511929) SHA1(4de9263778f327693f4d1e21b48e43806f673487) )
	ROM_CONTINUE( 0x80001, 0x20000 )
	ROM_CONTINUE( 0x40001, 0x20000 )
	ROM_CONTINUE( 0xc0001, 0x20000 )
	ROM_LOAD16_BYTE( "sgyxz_prg2.bin", 0x000000, 0x20000, CRC(95429c83) SHA1(e981624d018132e5625a66113b6ac4fc44e55cf7) )
	ROM_CONTINUE( 0x80000, 0x20000 )
	ROM_CONTINUE( 0x40000, 0x20000 )
	ROM_CONTINUE( 0xc0000, 0x20000 )
	ROM_FILL(0x708da, 4, 0xff) // patch out protections
	ROM_FILL(0xf11ea, 1, 0x60)
	ROM_FILL(0x00007, 1, 0xa2) // start address
	ROM_FILL(0x02448, 1, 0x07) // transitions

	ROM_REGION( 0x400000, "gfx", 0 )
	ROM_LOAD64_WORD("sgyxz_gfx1.bin", 0x000000, 0x80000, CRC(a60be9f6) SHA1(2298a4b6a2c83b76dc106a1efa19606b298d378a) ) // 'picture 1'
	ROM_CONTINUE(                     0x000004, 0x80000 )
	ROM_CONTINUE(                     0x200000, 0x80000 )
	ROM_CONTINUE(                     0x200004, 0x80000 )
	ROM_LOAD64_WORD("sgyxz_gfx2.bin", 0x000002, 0x80000, CRC(6ad9d048) SHA1(d47212d28d0a1ce349e4c59e5d0d99c541b3458e) ) // 'picture 2'
	ROM_CONTINUE(                     0x000006, 0x80000 )
	ROM_CONTINUE(                     0x200002, 0x80000 )
	ROM_CONTINUE(                     0x200006, 0x80000 )

	ROM_REGION( 0x20000, "audiocpu", 0 ) /* Z80 code */
	ROM_LOAD( "sgyxz_snd2.bin", 0x00000, 0x10000, CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) )
	ROM_RELOAD(                 0x08000, 0x10000 )

	ROM_REGION( 0x040000, "oki", 0 ) /* Samples */
	ROM_LOAD( "sgyxz_snd1.bin", 0x00000, 0x40000, CRC(c15ac0f2) SHA1(8d9e5519d9820e4ac4f70555088c80e64d052c9d) )
ROM_END

ROM_START( wofabl )
	ROM_REGION( CODE_SIZE, "maincpu", 0 ) /* 68000 Code */
	ROM_LOAD16_BYTE( "5.prg.040", 0x000000, 0x80000, CRC(4d9d2327) SHA1(b8029b117083a1c31546455fa53d9ee83a4ff7ad) )
	ROM_LOAD16_BYTE( "3.prg.040", 0x000001, 0x80000, CRC(ef25fe49) SHA1(d45d3c94cb57187b2f6ac248e9c3c9989be38f99) )
	ROM_LOAD16_BYTE( "6.prg.010", 0x100000, 0x20000, CRC(93eeb161) SHA1(0b8efb7ace59791ffb8a3f7826f0ea74620d7a0f) ) // x111111xxxxxxxxxx = 0xFF
	ROM_LOAD16_BYTE( "4.prg.010", 0x100001, 0x20000, CRC(a0751944) SHA1(84f092992f0f94acffbbb43168fbcee2c45da789) ) // x111111xxxxxxxxxx = 0xFF

	ROM_REGION( 0x400000, "gfx", 0 )
	ROM_LOAD32_BYTE( "gfx13.040", 0x000000, 0x80000, CRC(8e8db215) SHA1(cc85e576bf09c3edab9afc1b5fa0a152f4140c06) )
	ROM_LOAD32_BYTE( "gfx14.040", 0x000001, 0x80000, CRC(f34a7f9d) SHA1(6d67623c93147a779f07ef103188f3e2cb6d6d6e) )
	ROM_LOAD32_BYTE( "gfx15.040", 0x000002, 0x80000, CRC(a5e4f449) SHA1(9956f82818ccc685367b5fe5e4bc8b59b65c31c1) )
	ROM_LOAD32_BYTE( "gfx16.040", 0x000003, 0x80000, CRC(49a3dfc7) SHA1(c14ea91745fd72be936b6db9981d12d958326757) )
	ROM_LOAD32_BYTE( "gfx9.040",  0x200000, 0x80000, CRC(f8f33a0e) SHA1(33f172b79499d4a76b53c070c0007bd1604a71bd) )
	ROM_LOAD32_BYTE( "gfx10.040", 0x200001, 0x80000, CRC(6a060c6c) SHA1(49e4da9373272e5889caa79a86c39ee34087c480) )
	ROM_LOAD32_BYTE( "gfx11.040", 0x200002, 0x80000, CRC(13324965) SHA1(979754ebd15a2989f92b5b7fc5bae99eb83c3593) )
	ROM_LOAD32_BYTE( "gfx12.040", 0x200003, 0x80000, CRC(c29f7b70) SHA1(95d22dcd9e2a48ddea7573d0be75225e0aae798f) )

	ROM_REGION( 0x20000, "audiocpu", 0 ) /* Z80 code */
	ROM_LOAD( "sound.512", 0x00000, 0x10000,  CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) ) // identical to sgyxz
	ROM_RELOAD(            0x08000, 0x10000 )

	ROM_REGION( 0x040000, "oki", 0 ) /* Samples */
	ROM_LOAD( "sound.020", 0x00000, 0x40000,  CRC(672dcb46) SHA1(e76c1ce81689a55b573fb6e5c9a860cb756cd876) ) // almost identical to sgyxz
ROM_END

// ************************************************************************* PUNIPIC, PUNIPIC2, PUNIPIC3

MACHINE_START_MEMBER(cps_state, punipic)
{
	m_layer_enable_reg = 0x12;
	m_layer_mask_reg[0] = 0x14;
	m_layer_mask_reg[1] = 0x16;
	m_layer_mask_reg[2] = 0x08;
	m_layer_mask_reg[3] = 0x0a;
	m_layer_scroll1x_offset = 0x46; // text
	m_layer_scroll3x_offset = 0x46; // green patch in the park
	m_sprite_base = 0x1000;
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = 0;
}

void cps_state::punipic(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 12000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::punipic_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	//PIC16C57(config, m_audiocpu, 12000000).set_disable(); /* no valid dumps .. */

	MCFG_MACHINE_START_OVERRIDE(cps_state, punipic)

	EEPROM_93C46_8BIT(config, "eeprom");

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1 );
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state, cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);

	OKIM6295(config, m_oki, 1000000, okim6295_device::PIN7_HIGH).add_route(ALL_OUTPUTS, "mono", 0.30);
}

/* bootleg with pic, like dinopic / dinopic2 */
ROM_START( punipic )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "cpu5.bin", 0x000000, 0x80000, CRC(c3151563) SHA1(61d3a20c25fea8a94ae6e473a87c21968867cba0) )
	ROM_LOAD16_BYTE( "cpu3.bin", 0x000001, 0x80000, CRC(8c2593ac) SHA1(4261bc72b96c3a5690df35c5d8b71524765693d9) )
	ROM_LOAD16_BYTE( "cpu4.bin", 0x100000, 0x80000, CRC(665a5485) SHA1(c07920d110ca9c35f6cbff94a6a889c17300f994) )
	ROM_LOAD16_BYTE( "cpu2.bin", 0x100001, 0x80000, CRC(d7b13f39) SHA1(eb7cd92b44fdef3b72672b0be6786c526421b627) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROM_LOAD64_BYTE( "gfx9.bin",  0x000000, 0x40000, CRC(9b9a887a) SHA1(8805b36fc18837bd7c64c751b435d72b763b2235) )
	ROM_CONTINUE(                 0x000004, 0x40000)
	ROM_LOAD64_BYTE( "gfx8.bin",  0x000001, 0x40000, CRC(2b94287a) SHA1(815d88e66f537e17550fc0483616f02f7126bfb1) )
	ROM_CONTINUE(                 0x000005, 0x40000)
	ROM_LOAD64_BYTE( "gfx7.bin",  0x000002, 0x40000, CRC(e9bd74f5) SHA1(8ed7098c69d1c70093c99956bf82e532bd6fc7ac) )
	ROM_CONTINUE(                 0x000006, 0x40000)
	ROM_LOAD64_BYTE( "gfx6.bin",  0x000003, 0x40000, CRC(a5e1c8a4) SHA1(3596265a45cf6bbf16c623f0fce7cdc65f9338ad) )
	ROM_CONTINUE(                 0x000007, 0x40000)
	ROM_LOAD64_BYTE( "gfx13.bin", 0x200000, 0x40000, CRC(6d75a193) SHA1(6c5a89517926d7ba4a925a3df800d4bdb8a6938d) )
	ROM_CONTINUE(                 0x200004, 0x40000)
	ROM_LOAD64_BYTE( "gfx12.bin", 0x200001, 0x40000, CRC(a3c205c1) SHA1(6317cc49434dbbb9a249ddd4b50bd791803b3ebe) )
	ROM_CONTINUE(                 0x200005, 0x40000)
	ROM_LOAD64_BYTE( "gfx11.bin", 0x200002, 0x40000, CRC(22f2ec92) SHA1(9186bfc5db71dc5b099c9a985e8fdd5710772d1c) )
	ROM_CONTINUE(                 0x200006, 0x40000)
	ROM_LOAD64_BYTE( "gfx10.bin", 0x200003, 0x40000, CRC(763974c9) SHA1(f9b93c7cf0cb8c212fc21c57c85459b7d2e4e2fd) )
	ROM_CONTINUE(                 0x200007, 0x40000)

	ROM_REGION( 0x28000, "audiocpu", 0 ) /* PIC16c57 - protected */
	ROM_LOAD( "pic16c57", 0x00000, 0x4000, NO_DUMP )

	ROM_REGION( 0x200000, "oki", 0 ) /* OKI6295 */
	ROM_LOAD( "sound.bin", 0x000000, 0x80000, CRC(aeec9dc6) SHA1(56fd62e8db8aa96cdd242d8c705849a413567780) )
ROM_END

/* alt bootleg with PIC, same program roms as above, bigger GFX roms

Punisher
1993, Capcom

This is a bootleg version running on a single PCB.

PCB Layout
----------

|-----------------------------------------|
|    93C46  SOUND   30MHz  PAL            |
|    M6295  PIC16C57                      |
|           6116     PAL   6116           |
|           6116           6116  ACTEL    |
|                          6116  A1020B   |
|J                         6116           |
|A   TEST                  6116           |
|M                         6116           |
|M                                        |
|A                                        |
|    62256  62256        62256  PU13478   |
|     PRG1   PRG2                         |
|     PRG3   PRG4        62256  PU11256   |
|                                      PAL|
|       68000      24MHz        PAL   PAL |
|-----------------------------------------|

Notes:
      Measured clocks
      ---------------
      68000 clock: 12.000MHz (24 / 2)
      M6295 clock: 937.5kHz  (30 / 32), sample rate = 30000000 / 32 / 132
      16C57 clock: 3.75MHz   (30 / 8)   NOTE! 4096 bytes internal ROM is protected and can't be read out.
      VSYNC      : 60Hz

      ROMs
      ----
      PRG*  - 4M  MASK ROM (read as 27C040)
      SOUND - 4M  MASK ROM (read as 27C040)
      PU*   - 16M MASK ROM (read as 27C160)

*/

ROM_START( punipic2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "prg4.bin", 0x000000, 0x80000, CRC(c3151563) SHA1(61d3a20c25fea8a94ae6e473a87c21968867cba0) )
	ROM_LOAD16_BYTE( "prg3.bin", 0x000001, 0x80000, CRC(8c2593ac) SHA1(4261bc72b96c3a5690df35c5d8b71524765693d9) )
	ROM_LOAD16_BYTE( "prg2.bin", 0x100000, 0x80000, CRC(665a5485) SHA1(c07920d110ca9c35f6cbff94a6a889c17300f994) )
	ROM_LOAD16_BYTE( "prg1.bin", 0x100001, 0x80000, CRC(d7b13f39) SHA1(eb7cd92b44fdef3b72672b0be6786c526421b627) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROM_LOAD64_WORD( "pu11256.bin", 0x000000, 0x80000, CRC(6581faea) SHA1(2b0e96998002a1df96c7869ec965257d2ecfb531) )
	ROM_CONTINUE(                   0x200000, 0x80000 )
	ROM_CONTINUE(                   0x000004, 0x80000 )
	ROM_CONTINUE(                   0x200004, 0x80000 )
	ROM_LOAD64_WORD( "pu13478.bin", 0x000002, 0x80000, CRC(61613de4) SHA1(8f8c46ce907be2b4c4715ad88bfd1456818bdd2c) )
	ROM_CONTINUE(                   0x200002, 0x80000 )
	ROM_CONTINUE(                   0x000006, 0x80000 )
	ROM_CONTINUE(                   0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 ) /* PIC16c57 - protected */
	ROM_LOAD( "pic16c57", 0x00000, 0x4000, NO_DUMP )

	ROM_REGION( 0x200000, "oki", 0 ) /* OKI6295 */
	ROM_LOAD( "sound.bin", 0x000000, 0x80000, CRC(aeec9dc6) SHA1(56fd62e8db8aa96cdd242d8c705849a413567780) )

	ROM_REGION( 0x200000, "user1", 0 ) /* other */
	ROM_LOAD( "93c46.bin", 0x00, 0x80, CRC(36ab4e7d) SHA1(60bea43051d86d9aefcbb7a390cf0c7d8b905a4b) )
ROM_END

/* the readme doesn't actually state this has a PIC, and there's no sound rom
   so it might be different */

ROM_START( punipic3 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "psb5b.rom", 0x000000, 0x80000, CRC(58f42c05) SHA1(e243928f0bbecdf2a8d07cf4a6fdea4440e46c01) )
	ROM_LOAD16_BYTE( "psb3b.rom", 0x000001, 0x80000, CRC(90113db4) SHA1(4decc203ae3ee4abcb2e017f11cd20eae2abf3f3) )
	ROM_LOAD16_BYTE( "psb4a.rom", 0x100000, 0x80000, CRC(665a5485) SHA1(c07920d110ca9c35f6cbff94a6a889c17300f994) )
	ROM_LOAD16_BYTE( "psb2a.rom", 0x100001, 0x80000, CRC(d7b13f39) SHA1(eb7cd92b44fdef3b72672b0be6786c526421b627) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROM_LOAD64_WORD( "psb-a.rom", 0x000000, 0x80000, CRC(57f0f5e3) SHA1(130b6e92181994bbe874261e0895db65d4f3d5d1) )
	ROM_CONTINUE(                 0x000004, 0x80000 )
	ROM_CONTINUE(                 0x200000, 0x80000 )
	ROM_CONTINUE(                 0x200004, 0x80000 )
	ROM_LOAD64_WORD( "psb-b.rom", 0x000002, 0x80000, CRC(d9eb867e) SHA1(9b6eaa4a780da5c9cf09658fcab3a1a6f632c2f4) )
	ROM_CONTINUE(                 0x000006, 0x80000 )
	ROM_CONTINUE(                 0x200002, 0x80000 )
	ROM_CONTINUE(                 0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", ROMREGION_ERASE00 ) /* PIC16c57 (maybe, not listed in readme) */
	//ROM_LOAD( "pic16c57", 0x00000, 0x4000, NO_DUMP )

	ROM_REGION( 0x200000, "oki", ROMREGION_ERASE00 ) /* OKI6295 */
	//ROM_LOAD( "sound.bin", 0x000000, 0x80000, CRC(aeec9dc6) SHA1(56fd62e8db8aa96cdd242d8c705849a413567780) )
ROM_END

void cps_state::init_punipic()
{
	u16 *mem16 = (u16 *)memregion("maincpu")->base();
	mem16[0x5A8/2] = 0x4E71; // set data pointers
	mem16[0x4DF0/2] = 0x33ED;
	mem16[0x4DF2/2] = 0xDB2E;
	mem16[0x4DF4/2] = 0x0080;
	mem16[0x4DF6/2] = 0x0152;
	mem16[0x4DF8/2] = 0x4E75;

	init_dinopic();
}

void cps_state::init_punipic3()
{
	u16 *mem16 = (u16 *)memregion("maincpu")->base();
	mem16[0x5A6/2] = 0x4E71; // set data pointers
	mem16[0x5A8/2] = 0x4E71;

	init_dinopic();
}

static INPUT_PORTS_START( slampic )
	PORT_INCLUDE(slammast)

	PORT_MODIFY("IN2")  // players 3 + 4  (player 4 doesn't work in test menu but ok in game)
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_START3 )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(4)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(4)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(4)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(4)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(4)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(4)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_COIN4 )
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_START4 )

	PORT_MODIFY("IN3")
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )
INPUT_PORTS_END

/*static INPUT_PORTS_START( slampic2 )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	//PORT_SERVICE( 0x40, IP_ACTIVE_LOW )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("DSWA")
	PORT_DIPNAME( 0x07, 0x07, DEF_STR( Coinage ) ) PORT_DIPLOCATION("SW(A):1,2,3")
	PORT_DIPSETTING( 0x07, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING( 0x06, DEF_STR( 1C_2C ) )  // A:cccxxx0x C:xx0xxxxx = coinage (freeplay + "2 coins start" must be off)
	PORT_DIPSETTING( 0x05, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING( 0x04, DEF_STR( 1C_4C ) )
	PORT_DIPSETTING( 0x03, DEF_STR( 1C_6C ) )
	PORT_DIPSETTING( 0x02, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING( 0x01, DEF_STR( 3C_1C ) )
	PORT_DIPSETTING( 0x00, DEF_STR( 4C_1C ) )
	PORT_DIPUNUSED_DIPLOC( 0x08, 0x08, "SW(A):4" )
	PORT_DIPUNUSED_DIPLOC( 0x10, 0x10, "SW(A):5" )
	PORT_DIPUNUSED_DIPLOC( 0x20, 0x20, "SW(A):6" )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Coinage ) ) PORT_DIPLOCATION("SW(A):7")
	PORT_DIPSETTING( 0x40, DEF_STR( Off ) )
	PORT_DIPSETTING( 0x00, "2 Coins Start" )  // A:000xxx1x C:xx0xxxxx = 2 coins start (other coinage + freeplay must be off)
	PORT_DIPNAME( 0x80, 0x80, "Chuter" ) PORT_DIPLOCATION("SW(A):8")
	PORT_DIPSETTING( 0x80, "Single Chuter" )
	PORT_DIPSETTING( 0x00, "Multi Chuters" )

	PORT_START("DSWB")
	PORT_DIPNAME( 0x07, 0x04, "Game Difficulty" ) PORT_DIPLOCATION("SW(B):1,2,3")
	PORT_DIPSETTING( 0x07, "(0) Extra Easy" )
	PORT_DIPSETTING( 0x06, "(1) Very Easy" )
	PORT_DIPSETTING( 0x05, "(2) Easy" )
	PORT_DIPSETTING( 0x04, "(3) Normal" )
	PORT_DIPSETTING( 0x03, "(4) Hard" )
	PORT_DIPSETTING( 0x02, "(5) Very Hard" )
	PORT_DIPSETTING( 0x01, "(6) Extra Hard" )
	PORT_DIPSETTING( 0x00, "(7) Hardest" )
	PORT_DIPUNUSED_DIPLOC( 0x08, 0x08, "SW(B):4" )
	PORT_DIPUNUSED_DIPLOC( 0x10, 0x10, "SW(B):5" )
	PORT_DIPNAME( 0x20, 0x20, "Join In") PORT_DIPLOCATION("SW(B):6")
	PORT_DIPSETTING( 0x00, DEF_STR( Off ) )
	PORT_DIPSETTING( 0x20, DEF_STR( On ) )
	PORT_DIPNAME( 0xc0, 0xc0, "Cabinet" ) PORT_DIPLOCATION("SW(B):7,8")
	PORT_DIPSETTING( 0xc0, "2 Players Cabinet" )
	//PORT_DIPSETTING( 0x80, "Invalid" )              // only coin 1 works, credits both player 1 and 2
	PORT_DIPSETTING( 0x40, "4 Players Cabinet" )
	PORT_DIPSETTING( 0x00, "2x2 Players Cabinet" )  // only coins 1,3 work, 1 credits 1+2, 2 credits 3+4

	PORT_START("DSWC")
	PORT_DIPUNUSED_DIPLOC( 0x01, 0x01, "SW(C):1" )
	PORT_DIPNAME( 0x02, 0x02, "Game Mode" ) PORT_DIPLOCATION("SW(C):2")
	PORT_DIPSETTING( 0x02, "For Business" )
	PORT_DIPSETTING( 0x00, "For Photographing" )  // doesn't seem to do anything?
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Free_Play ) ) PORT_DIPLOCATION("SW(C):3")
	PORT_DIPSETTING( 0x04, DEF_STR( Off ) )
	PORT_DIPSETTING( 0x00, DEF_STR( On ) )  // A:000xxx0x C:xx1xxxxx = freeplay (other coinage + "2 coins start" must be off)
	PORT_DIPNAME( 0x08, 0x08, "Freeze" ) PORT_DIPLOCATION("SW(C):4")
	PORT_DIPSETTING( 0x08, DEF_STR( Off ) )
	PORT_DIPSETTING( 0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Flip_Screen ) ) PORT_DIPLOCATION("SW(C):5")  // doesn't work
	PORT_DIPSETTING( 0x10, DEF_STR( Off ) )
	PORT_DIPSETTING( 0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x00, DEF_STR( Demo_Sounds ) ) PORT_DIPLOCATION("SW(C):6")
	PORT_DIPSETTING( 0x20, DEF_STR( Off ) )
	PORT_DIPSETTING( 0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Allow_Continue ) ) PORT_DIPLOCATION("SW(C):7")
	PORT_DIPSETTING( 0x00, DEF_STR( Off ) )
	PORT_DIPSETTING( 0x40, DEF_STR( On ) )
	PORT_DIPUNUSED_DIPLOC( 0x80, 0x80, "SW(C):8" )

	PORT_START("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(3)
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(4)

	PORT_START("IN2")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(4)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(4)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(4)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(4)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(4)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(4)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_COIN4 )
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_START4 )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_START3 )
INPUT_PORTS_END*/



// ************************************************************************* SF2M1

void cps_state::sf2m1(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, XTAL(12'000'000));
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sf2m1_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, XTAL(3'579'545));
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::sgyxz_sound_map);

	MCFG_MACHINE_START_OVERRIDE(cps_state,sf2m1)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_raw(CPS_PIXEL_CLOCK, CPS_HTOTAL, CPS_HBEND, CPS_HBSTART, CPS_VTOTAL, CPS_VBEND, CPS_VBSTART);
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state, cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	GENERIC_LATCH_8(config, m_soundlatch);
	GENERIC_LATCH_8(config, m_soundlatch2);
	ym2151_device &ym2151(YM2151(config, "2151", XTAL(3'579'545)));
	ym2151.irq_handler().set_inputline(m_audiocpu, 0);
	ym2151.add_route(0, "mono", 0.35);
	ym2151.add_route(1, "mono", 0.35);
	OKIM6295(config, m_oki, XTAL(16'000'000)/4/4, okim6295_device::PIN7_HIGH).add_route(ALL_OUTPUTS, "mono", 0.30);
}

ROM_START( sf2m1 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "222e",             0x000000, 0x80000, CRC(1e20d0a3) SHA1(5e05b52fd938aff5190bca7e178705d7236aef66) )
	ROM_LOAD16_BYTE( "196e",             0x000001, 0x80000, CRC(88cc38a3) SHA1(6049962f943bd37748a9531cc3254e8b59326eac) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.bin", 0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROM_LOAD64_WORD( "s92_01.bin", 0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) )
	ROM_LOAD64_WORD( "s92_02.bin", 0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) )
	ROM_LOAD64_WORD( "s92_03.bin", 0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) )
	ROM_LOAD64_WORD( "s92_04.bin", 0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) )
	ROM_LOAD64_WORD( "s92_05.bin", 0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) )
	ROM_LOAD64_WORD( "s92_06.bin", 0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) )
	ROM_LOAD64_WORD( "s92_07.bin", 0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) )
	ROM_LOAD64_WORD( "s92_08.bin", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) )
	ROM_LOAD64_WORD( "s92_10.bin", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) )
	ROM_LOAD64_WORD( "s92_11.bin", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) )
	ROM_LOAD64_WORD( "s92_12.bin", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) )
	ROM_LOAD64_WORD( "s92_13.bin", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) )

	ROM_REGION( 0x18000, "audiocpu", 0 ) /* 64k for the audio CPU (+banks) */
	ROM_LOAD( "s92_09.bin", 0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 ) /* Samples */
	ROM_LOAD( "s92_18.bin", 0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.bin", 0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )
ROM_END

void cps_state::init_sf2m1()
{
	u16 *mem16 = (u16 *)memregion("maincpu")->base();
	mem16[0x64E/2] = 0x6046; // fix priorities

	init_dinopic();
}



// ************************************************************************* SF2MDT, SF2MDTA


/*
CPU

1x MC68000P12 (main)
1x TPC1020AFN-084C (main)
1x Z0840006PSC-Z80CPU (sound)
1x YM2151 (sound)
1x YM3012 (sound)
2x M5205 (sound)
2x LM324N (sound)
1x TDA2003 (sound)
1x oscillator 24.000000MHz
1x oscillator 30.000MHz
ROMs

14x AM27C040 (1,3,6,7,8,9,10,11,12,13,14,15,16,17)
3x TMS27C010A (2,4,5)
3x PAL 16S20 (ic7,ic72, ic80) (read protected, not dumped)
3x GAL20V8A (ic120, ic121, ic169) (read protected, not dumped)

Note

1x JAMMA edge connector
1x trimmer (volume)
3x 8x2 switches dip
*/

ROM_START( sf2mdt )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "3.ic172", 0x000000, 0x80000, CRC(5301b41f) SHA1(6855a57b21e8c5d74e5cb18f9ce6af650d7fb422) )
	ROM_LOAD16_BYTE( "1.ic171", 0x000001, 0x80000, CRC(c1c803f6) SHA1(9fe18ae2553a63d8e4dcc20bafd5a4634f8b93c4) )
	ROM_LOAD16_BYTE( "4.ic176", 0x100000, 0x20000, CRC(1073b7b6) SHA1(81ca1eab65ceac69520584bb23a684ccb9d92f89) )
	ROM_LOAD16_BYTE( "2.ic175", 0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )

	ROM_REGION( 0x600000, "gfx", 0 ) /* rearranged in init */
	ROM_LOAD64_WORD( "7.ic90",  0x000000, 0x80000, CRC(896eaf48) SHA1(5a13ae8b554e05eed3d5749aaf5845d499bce45b) )
	ROM_LOAD64_WORD( "10.ic88", 0x000002, 0x80000, CRC(ef3f5be8) SHA1(d4e1de7d7caf6977e48544d6701618ae70c717f9) )
	ROM_LOAD64_WORD( "13.ic89", 0x000004, 0x80000, CRC(305dd72a) SHA1(c373b517c23f3b019abb06e21f6b9ab6e1e47909) )
	ROM_LOAD64_WORD( "16.ic87", 0x000006, 0x80000, CRC(e57f6db9) SHA1(b37f95737804002ec0e237472eaacf0bc1e868e8) )
	ROM_LOAD64_WORD( "6.ic91",  0x200000, 0x80000, CRC(054cd5c4) SHA1(07f275e118c141a84ca15a2e9edc81694af37cf2) )
	ROM_LOAD64_WORD( "9.ic93",  0x200002, 0x80000, CRC(818ca33d) SHA1(dfb707e17c83216f8a62e905f8c7cd6d406b417b) )
	ROM_LOAD64_WORD( "12.ic92", 0x200004, 0x80000, CRC(87e069e8) SHA1(cddd3be84f8379134590bfbbb080518f28120e49) )
	ROM_LOAD64_WORD( "15.ic94", 0x200006, 0x80000, CRC(5dfb44d1) SHA1(08e44b8efc84f9cfc829aabf704155ddc700de76) )
	ROM_LOAD64_WORD( "8.ic86",  0x400000, 0x80000, CRC(34bbb3fa) SHA1(7794e89258f12b17d38c3d302dc15c502a8c8eb6) )
	ROM_LOAD64_WORD( "11.ic84", 0x400002, 0x80000, CRC(cea6d1d6) SHA1(9c953db42f0d877e43c0c239f69a00df39a18295) )
	ROM_LOAD64_WORD( "14.ic85", 0x400004, 0x80000, CRC(7d9f1a67) SHA1(6deb7fff867c42b13a32bb11eda798cfdb4cbaa8) )
	ROM_LOAD64_WORD( "17.ic83", 0x400006, 0x80000, CRC(91a9a05d) SHA1(5266ceddd2df925e79b4200843dec2f7aa9297b3) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* Sound program + samples  */
	ROM_LOAD( "5.ic26", 0x00000, 0x20000, CRC(17d5ba8a) SHA1(6ff3b8860d7e1fdee3561846f645eb4d3a8965ec) )
	ROM_RELOAD(         0x10000, 0x20000 )
ROM_END

ROM_START( sf2mdta )
	/* unconfirmed if working on real hardware, pf4 is a bad dump (bad pin) */
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "3.mdta", 0x000000, 0x80000, CRC(9f544ef4) SHA1(f784809e59a5fcabd6d15d3f1c36250a5528c9f8) )
	ROM_LOAD16_BYTE( "5.mdta", 0x000001, 0x80000, CRC(d76d6621) SHA1(aa9cea9ddace212a7b3c535b8f6e3fbc50da1f94) )
	ROM_LOAD16_BYTE( "2.mdta", 0x100000, 0x20000, CRC(74844192) SHA1(99cd546c78cce7f632007af454d8a55eddb6b19b) )
	ROM_LOAD16_BYTE( "4.mdta", 0x100001, 0x20000, CRC(bd98ff15) SHA1(ed902d949b0b5c5beaaea78a4b418ffa6db9e1df) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROM_LOAD32_WORD( "pf4 sh058.ic89", 0x000000, 0x100000, CRC(16289710) SHA1(4f3236712b979a1eb2fa97740e32d7913cee0d0d) )
	ROM_LOAD32_WORD( "pf7 sh072.ic92", 0x000002, 0x100000, CRC(fb78022e) SHA1(b8974387056dd52db96b01cc4648edc814398c7e) )
	ROM_LOAD32_WORD( "pf5 sh036.ic90", 0x200000, 0x100000, CRC(0a6be48b) SHA1(b7e72c94d4e3eb4a6bba6608d9b9a093c8901ad9) )
	ROM_LOAD32_WORD( "pf8 sh074.ic93", 0x200002, 0x100000, CRC(6258c7cf) SHA1(4cd7519245c0aa816934a43e6743160f715d7dc2) )
	ROM_LOAD32_WORD( "pf6 sh070.ic88", 0x400000, 0x100000, CRC(9b5b09d7) SHA1(698a6aab41e495bd0c37a19aee16a84f04d15797) )
	ROM_LOAD32_WORD( "pf9 sh001.ic91", 0x400002, 0x100000, CRC(9f25090e) SHA1(12ff0431ef6550db446985c8914ac7d78eec6b6d) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* Sound program + samples  */
	ROM_LOAD( "1.ic28", 0x00000, 0x20000, CRC(d5bee9cc) SHA1(e638cb5ce7a22c18b60296a7defe8b03418da56c) )
	ROM_RELOAD(         0x10000, 0x20000 )
ROM_END

ROM_START( sf2mdtb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "3.ic172", 0x000000, 0x80000, CRC(0bdb9da2) SHA1(5224ee81d94be70a84ffaa3a56b8093aa36d6b4f) ) // sldh
	ROM_LOAD16_BYTE( "1.ic171", 0x000001, 0x80000, CRC(d88abbce) SHA1(57667a92710bb1d37daed09262c3064d09cbf4af) ) // sldh
	ROM_LOAD16_BYTE( "4.ic176", 0x100000, 0x20000, CRC(74844192) SHA1(99cd546c78cce7f632007af454d8a55eddb6b19b) ) // sldh
	ROM_LOAD16_BYTE( "2.ic175", 0x100001, 0x20000, CRC(bd98ff15) SHA1(ed902d949b0b5c5beaaea78a4b418ffa6db9e1df) ) // sldh

	ROM_REGION( 0x600000, "gfx", 0 ) /* rearranged in init */
	ROM_LOAD64_WORD( "7.ic90",  0x000000, 0x80000, CRC(896eaf48) SHA1(5a13ae8b554e05eed3d5749aaf5845d499bce45b) )
	ROM_LOAD64_WORD( "10.ic88", 0x000002, 0x80000, CRC(ef3f5be8) SHA1(d4e1de7d7caf6977e48544d6701618ae70c717f9) )
	ROM_LOAD64_WORD( "13.ic89", 0x000004, 0x80000, CRC(305dd72a) SHA1(c373b517c23f3b019abb06e21f6b9ab6e1e47909) )
	ROM_LOAD64_WORD( "16.ic87", 0x000006, 0x80000, CRC(e57f6db9) SHA1(b37f95737804002ec0e237472eaacf0bc1e868e8) )
	ROM_LOAD64_WORD( "6.ic91",  0x200000, 0x80000, CRC(054cd5c4) SHA1(07f275e118c141a84ca15a2e9edc81694af37cf2) )
	ROM_LOAD64_WORD( "9.ic93",  0x200002, 0x80000, CRC(818ca33d) SHA1(dfb707e17c83216f8a62e905f8c7cd6d406b417b) )
	ROM_LOAD64_WORD( "12.ic92", 0x200004, 0x80000, CRC(87e069e8) SHA1(cddd3be84f8379134590bfbbb080518f28120e49) )
	ROM_LOAD64_WORD( "15.ic94", 0x200006, 0x80000, CRC(5dfb44d1) SHA1(08e44b8efc84f9cfc829aabf704155ddc700de76) )
	ROM_LOAD64_WORD( "8.ic86",  0x400000, 0x80000, CRC(34bbb3fa) SHA1(7794e89258f12b17d38c3d302dc15c502a8c8eb6) )
	ROM_LOAD64_WORD( "11.ic84", 0x400002, 0x80000, CRC(cea6d1d6) SHA1(9c953db42f0d877e43c0c239f69a00df39a18295) )
	ROM_LOAD64_WORD( "14.ic85", 0x400004, 0x80000, CRC(7d9f1a67) SHA1(6deb7fff867c42b13a32bb11eda798cfdb4cbaa8) )
	ROM_LOAD64_WORD( "17.ic83", 0x400006, 0x80000, CRC(91a9a05d) SHA1(5266ceddd2df925e79b4200843dec2f7aa9297b3) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* Sound program + samples  */
	ROM_LOAD( "5.ic28", 0x00000, 0x20000, CRC(d5bee9cc) SHA1(e638cb5ce7a22c18b60296a7defe8b03418da56c) )
	ROM_RELOAD(         0x10000, 0x20000 )
ROM_END

ROM_START( sf2b )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_WORD_SWAP( "pf1-2-sg076.bin", 0x000000, 0x100000, CRC(1d15bc7a) SHA1(834627545f191f39de6beb008c89623f2b88c13b) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROM_LOAD32_WORD( "pf4-sg072.bin", 0x000000, 0x100000, CRC(16289710) SHA1(4f3236712b979a1eb2fa97740e32d7913cee0d0d) )
	ROM_LOAD32_WORD( "pf7-sg103.bin", 0x000002, 0x100000, CRC(fb78022e) SHA1(b8974387056dd52db96b01cc4648edc814398c7e) )
	ROM_LOAD32_WORD( "pf5-sg095.bin", 0x200000, 0x100000, CRC(0a6be48b) SHA1(b7e72c94d4e3eb4a6bba6608d9b9a093c8901ad9) )
	ROM_LOAD32_WORD( "pf8-sg101.bin", 0x200002, 0x100000, CRC(6258c7cf) SHA1(4cd7519245c0aa816934a43e6743160f715d7dc2) )
	ROM_LOAD32_WORD( "pf6-sg068.bin", 0x400000, 0x100000, CRC(9b5b09d7) SHA1(698a6aab41e495bd0c37a19aee16a84f04d15797) )
	ROM_LOAD32_WORD( "pf9-sh001.bin", 0x400002, 0x100000, CRC(9f25090e) SHA1(12ff0431ef6550db446985c8914ac7d78eec6b6d) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* Sound program + samples  */
	ROM_LOAD( "3snd.ic28", 0x00000, 0x20000, CRC(d5bee9cc) SHA1(e638cb5ce7a22c18b60296a7defe8b03418da56c) )
	ROM_RELOAD(            0x10000, 0x20000 )
ROM_END

ROM_START( sf2b2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "2.bin", 0x000000, 0x80000, CRC(42809e5a) SHA1(ee91ecfce29bc50cf3f492ff646109c60bf65551) )
	ROM_LOAD16_BYTE( "1.bin", 0x000001, 0x80000, CRC(e58db26c) SHA1(da1a4e063fa770257fd3df5fdb3785c1856511a5) )

	ROM_REGION( 0x600000, "gfx", 0 ) /* rearranged in init */
	ROM_LOAD64_WORD( "5.bin",  0x000000, 0x80000, CRC(47fab9ed) SHA1(1709becbe189b21f2c1920acef96f9412eb954e2) )
	ROM_LOAD64_WORD( "8.bin",  0x000002, 0x80000, CRC(b8c39d56) SHA1(ee2939f42e95c926bdd88adf326eee02cba3f37a) )
	ROM_LOAD64_WORD( "11.bin", 0x000004, 0x80000, CRC(6e8c98d8) SHA1(fbd7d788349fd418c48aedd906c40960e41c20f1) )
	ROM_LOAD64_WORD( "14.bin", 0x000006, 0x80000, CRC(672d4f85) SHA1(511a8878d14d3fd39c9a22efb983550098ea8760) )
	ROM_LOAD64_WORD( "4.bin",  0x200000, 0x80000, CRC(69d7b06b) SHA1(b428a0b5dfdee20d4d198673fe3b0147cad2d5bd) )
	ROM_LOAD64_WORD( "7.bin",  0x200002, 0x80000, CRC(ded88f5f) SHA1(71c63fed5a15f6ce1df878dca7aa5d53868e68ee) )
	ROM_LOAD64_WORD( "10.bin", 0x200004, 0x80000, CRC(8c2fca3c) SHA1(a84399e91dbf5790c3fe003385f6d9f4bc9d3366) )
	ROM_LOAD64_WORD( "13.bin", 0x200006, 0x80000, CRC(26f09d38) SHA1(3babc4f502ea9e07f79306b1abc9c94f484f9cc1) )
	ROM_LOAD64_WORD( "6.bin",  0x400000, 0x80000, CRC(b6215991) SHA1(5e20632e1a2d6eebe3b5d314cf2549bb74d7118e) )
	ROM_LOAD64_WORD( "9.bin",  0x400002, 0x80000, CRC(b6a71ed7) SHA1(1850b4b4aa4b5cafc594b174322afefbdf215221) )
	ROM_LOAD64_WORD( "12.bin", 0x400004, 0x80000, CRC(971903fa) SHA1(849ee7200815ef73f75456e656f061f1e852af59) )
	ROM_LOAD64_WORD( "15.bin", 0x400006, 0x80000, CRC(00983914) SHA1(4ead6bbce6ca8c4cc884d55c1f821242d0e67fae) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* Sound program + samples  */
	ROM_LOAD( "3.bin", 0x00000, 0x20000, CRC(17d5ba8a) SHA1(6ff3b8860d7e1fdee3561846f645eb4d3a8965ec) )
	ROM_RELOAD(        0x10000, 0x20000 )
ROM_END

ROM_START( sf2ceb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "3.ic171", 0x000000, 0x80000, CRC(a2355d90) SHA1(6c9e1294c55a5a9f244f6f1ce46224c51f910bb1) )
	ROM_LOAD16_BYTE( "5.ic171", 0x000001, 0x80000, CRC(c6f86e84) SHA1(546841fe7d423fff05a7772aa57fa3274515c32b) )
	ROM_LOAD16_BYTE( "2.ic171", 0x100000, 0x20000, CRC(74844192) SHA1(99cd546c78cce7f632007af454d8a55eddb6b19b) )
	ROM_LOAD16_BYTE( "4.ic171", 0x100001, 0x20000, CRC(bd98ff15) SHA1(ed902d949b0b5c5beaaea78a4b418ffa6db9e1df) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROM_LOAD32_WORD( "pf4-sg072.ic90", 0x000000, 0x100000, CRC(446575c7) SHA1(2bd769674fbe280d304b389daf74202cf9e4ac22) )
	ROM_LOAD32_WORD( "pf7-sg103.ic88", 0x000002, 0x100000, CRC(fb78022e) SHA1(b8974387056dd52db96b01cc4648edc814398c7e) )
	ROM_LOAD32_WORD( "pf5-sg063.ic91", 0x200000, 0x100000, CRC(0a6be48b) SHA1(b7e72c94d4e3eb4a6bba6608d9b9a093c8901ad9) )
	ROM_LOAD32_WORD( "pf8-sg101.ic93", 0x200002, 0x100000, CRC(6258c7cf) SHA1(4cd7519245c0aa816934a43e6743160f715d7dc2) )
	ROM_LOAD32_WORD( "pf6-sg070.ic86", 0x400000, 0x100000, CRC(9b5b09d7) SHA1(698a6aab41e495bd0c37a19aee16a84f04d15797) )
	ROM_LOAD32_WORD( "pf9-sh001.ic84", 0x400002, 0x100000, CRC(9f25090e) SHA1(12ff0431ef6550db446985c8914ac7d78eec6b6d) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) /* Sound program + samples  */
	ROM_LOAD( "3.ic28", 0x00000, 0x20000, CRC(d5bee9cc) SHA1(e638cb5ce7a22c18b60296a7defe8b03418da56c) )
	ROM_RELOAD(         0x10000, 0x20000 )
ROM_END

ROM_START( sf2ceb2 ) // sf2ceeab3 in FBNeo, all ROMs but the first two program ROMs match sf2mdt. Dump has been confirmed on 2 different PCBs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "3.ic172", 0x000000, 0x80000, CRC(11b5fe98) SHA1(6dda11e6c443a7c0ddf17a9840c93be00a424472) )
	ROM_LOAD16_BYTE( "1.ic171", 0x000001, 0x80000, CRC(6d948623) SHA1(0bcdda9ba2ef2051ad70277fbc383035a63540f3) )
	ROM_LOAD16_BYTE( "4.ic176", 0x100000, 0x20000, CRC(1073b7b6) SHA1(81ca1eab65ceac69520584bb23a684ccb9d92f89) )
	ROM_LOAD16_BYTE( "2.ic175", 0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )

	ROM_REGION( 0x600000, "gfx", 0 ) // rearranged in init
	ROM_LOAD64_WORD( "7.ic90",  0x000000, 0x80000, CRC(896eaf48) SHA1(5a13ae8b554e05eed3d5749aaf5845d499bce45b) )
	ROM_LOAD64_WORD( "10.ic88", 0x000002, 0x80000, CRC(ef3f5be8) SHA1(d4e1de7d7caf6977e48544d6701618ae70c717f9) )
	ROM_LOAD64_WORD( "13.ic89", 0x000004, 0x80000, CRC(305dd72a) SHA1(c373b517c23f3b019abb06e21f6b9ab6e1e47909) )
	ROM_LOAD64_WORD( "16.ic87", 0x000006, 0x80000, CRC(e57f6db9) SHA1(b37f95737804002ec0e237472eaacf0bc1e868e8) )
	ROM_LOAD64_WORD( "6.ic91",  0x200000, 0x80000, CRC(054cd5c4) SHA1(07f275e118c141a84ca15a2e9edc81694af37cf2) )
	ROM_LOAD64_WORD( "9.ic93",  0x200002, 0x80000, CRC(818ca33d) SHA1(dfb707e17c83216f8a62e905f8c7cd6d406b417b) )
	ROM_LOAD64_WORD( "12.ic92", 0x200004, 0x80000, CRC(87e069e8) SHA1(cddd3be84f8379134590bfbbb080518f28120e49) )
	ROM_LOAD64_WORD( "15.ic94", 0x200006, 0x80000, CRC(5dfb44d1) SHA1(08e44b8efc84f9cfc829aabf704155ddc700de76) )
	ROM_LOAD64_WORD( "8.ic86",  0x400000, 0x80000, CRC(34bbb3fa) SHA1(7794e89258f12b17d38c3d302dc15c502a8c8eb6) )
	ROM_LOAD64_WORD( "11.ic84", 0x400002, 0x80000, CRC(cea6d1d6) SHA1(9c953db42f0d877e43c0c239f69a00df39a18295) )
	ROM_LOAD64_WORD( "14.ic85", 0x400004, 0x80000, CRC(7d9f1a67) SHA1(6deb7fff867c42b13a32bb11eda798cfdb4cbaa8) )
	ROM_LOAD64_WORD( "17.ic83", 0x400006, 0x80000, CRC(91a9a05d) SHA1(5266ceddd2df925e79b4200843dec2f7aa9297b3) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) // Sound program + samples
	ROM_LOAD( "5.ic26", 0x00000, 0x20000, CRC(17d5ba8a) SHA1(6ff3b8860d7e1fdee3561846f645eb4d3a8965ec) )
	ROM_RELOAD(         0x10000, 0x20000 )
ROM_END

ROM_START( sf2ceb3 ) // sf2ceeab4 in FBNeo, all ROMs but the first match sf2ceb2. Changes do not seem a result of bit-rot
	ROM_REGION( CODE_SIZE, "maincpu", 0 ) // main CPU has a (sic) 'Street Figter III 00325' sticker
	ROM_LOAD16_BYTE( "3.ic172", 0x000000, 0x80000, CRC(30848e16) SHA1(b48809350f033010d33666a8cd5a610f9721f994) )
	ROM_LOAD16_BYTE( "1.ic171", 0x000001, 0x80000, CRC(6d948623) SHA1(0bcdda9ba2ef2051ad70277fbc383035a63540f3) )
	ROM_LOAD16_BYTE( "4.ic176", 0x100000, 0x20000, CRC(1073b7b6) SHA1(81ca1eab65ceac69520584bb23a684ccb9d92f89) )
	ROM_LOAD16_BYTE( "2.ic175", 0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )

	ROM_REGION( 0x600000, "gfx", 0 ) // rearranged in init
	ROM_LOAD64_WORD( "7.ic90",  0x000000, 0x80000, CRC(896eaf48) SHA1(5a13ae8b554e05eed3d5749aaf5845d499bce45b) )
	ROM_LOAD64_WORD( "10.ic88", 0x000002, 0x80000, CRC(ef3f5be8) SHA1(d4e1de7d7caf6977e48544d6701618ae70c717f9) )
	ROM_LOAD64_WORD( "13.ic89", 0x000004, 0x80000, CRC(305dd72a) SHA1(c373b517c23f3b019abb06e21f6b9ab6e1e47909) )
	ROM_LOAD64_WORD( "16.ic87", 0x000006, 0x80000, CRC(e57f6db9) SHA1(b37f95737804002ec0e237472eaacf0bc1e868e8) )
	ROM_LOAD64_WORD( "6.ic91",  0x200000, 0x80000, CRC(054cd5c4) SHA1(07f275e118c141a84ca15a2e9edc81694af37cf2) )
	ROM_LOAD64_WORD( "9.ic93",  0x200002, 0x80000, CRC(818ca33d) SHA1(dfb707e17c83216f8a62e905f8c7cd6d406b417b) )
	ROM_LOAD64_WORD( "12.ic92", 0x200004, 0x80000, CRC(87e069e8) SHA1(cddd3be84f8379134590bfbbb080518f28120e49) )
	ROM_LOAD64_WORD( "15.ic94", 0x200006, 0x80000, CRC(5dfb44d1) SHA1(08e44b8efc84f9cfc829aabf704155ddc700de76) )
	ROM_LOAD64_WORD( "8.ic86",  0x400000, 0x80000, CRC(34bbb3fa) SHA1(7794e89258f12b17d38c3d302dc15c502a8c8eb6) )
	ROM_LOAD64_WORD( "11.ic84", 0x400002, 0x80000, CRC(cea6d1d6) SHA1(9c953db42f0d877e43c0c239f69a00df39a18295) )
	ROM_LOAD64_WORD( "14.ic85", 0x400004, 0x80000, CRC(7d9f1a67) SHA1(6deb7fff867c42b13a32bb11eda798cfdb4cbaa8) )
	ROM_LOAD64_WORD( "17.ic83", 0x400006, 0x80000, CRC(91a9a05d) SHA1(5266ceddd2df925e79b4200843dec2f7aa9297b3) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) // Sound program + samples
	ROM_LOAD( "5.ic26", 0x00000, 0x20000, CRC(17d5ba8a) SHA1(6ff3b8860d7e1fdee3561846f645eb4d3a8965ec) )
	ROM_RELOAD(         0x10000, 0x20000 )
ROM_END

ROM_START( sf2ceb4 ) // sf2ceeab5 in FBNeo, all ROMs but ic171 match sf2ceb2. Dump has been confirmed on 3 different PCBs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "3.ic172", 0x000000, 0x80000, CRC(11b5fe98) SHA1(6dda11e6c443a7c0ddf17a9840c93be00a424472) )
	ROM_LOAD16_BYTE( "5.ic171", 0x000001, 0x80000, CRC(43e85f2c) SHA1(56026e5d0ba4e0fb1bc92b981f69d0fc9d7af1d2) )
	ROM_LOAD16_BYTE( "2.ic176", 0x100000, 0x20000, CRC(1073b7b6) SHA1(81ca1eab65ceac69520584bb23a684ccb9d92f89) )
	ROM_LOAD16_BYTE( "4.ic175", 0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )

	ROM_REGION( 0x600000, "gfx", 0 ) // rearranged in init
	ROM_LOAD64_WORD( "10.ic90", 0x000000, 0x80000, CRC(896eaf48) SHA1(5a13ae8b554e05eed3d5749aaf5845d499bce45b) )
	ROM_LOAD64_WORD( "7.ic88",  0x000002, 0x80000, CRC(ef3f5be8) SHA1(d4e1de7d7caf6977e48544d6701618ae70c717f9) )
	ROM_LOAD64_WORD( "16.ic89", 0x000004, 0x80000, CRC(305dd72a) SHA1(c373b517c23f3b019abb06e21f6b9ab6e1e47909) )
	ROM_LOAD64_WORD( "13.ic87", 0x000006, 0x80000, CRC(e57f6db9) SHA1(b37f95737804002ec0e237472eaacf0bc1e868e8) )
	ROM_LOAD64_WORD( "11.ic91", 0x200000, 0x80000, CRC(054cd5c4) SHA1(07f275e118c141a84ca15a2e9edc81694af37cf2) )
	ROM_LOAD64_WORD( "8.ic93",  0x200002, 0x80000, CRC(818ca33d) SHA1(dfb707e17c83216f8a62e905f8c7cd6d406b417b) )
	ROM_LOAD64_WORD( "17.ic92", 0x200004, 0x80000, CRC(87e069e8) SHA1(cddd3be84f8379134590bfbbb080518f28120e49) )
	ROM_LOAD64_WORD( "14.ic94", 0x200006, 0x80000, CRC(5dfb44d1) SHA1(08e44b8efc84f9cfc829aabf704155ddc700de76) )
	ROM_LOAD64_WORD( "9.ic86",  0x400000, 0x80000, CRC(34bbb3fa) SHA1(7794e89258f12b17d38c3d302dc15c502a8c8eb6) )
	ROM_LOAD64_WORD( "6.ic84",  0x400002, 0x80000, CRC(cea6d1d6) SHA1(9c953db42f0d877e43c0c239f69a00df39a18295) )
	ROM_LOAD64_WORD( "15.ic85", 0x400004, 0x80000, CRC(7d9f1a67) SHA1(6deb7fff867c42b13a32bb11eda798cfdb4cbaa8) )
	ROM_LOAD64_WORD( "12.ic83", 0x400006, 0x80000, CRC(91a9a05d) SHA1(5266ceddd2df925e79b4200843dec2f7aa9297b3) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) // Sound program + samples
	ROM_LOAD( "1.ic26", 0x00000, 0x20000, CRC(17d5ba8a) SHA1(6ff3b8860d7e1fdee3561846f645eb4d3a8965ec) )
	ROM_RELOAD(         0x10000, 0x20000 )
ROM_END

// main PCB is marked "110-09-91 CH35/1 COMP" on component side
// sub PCB is marked "LS 938" on solder side
ROM_START( sf2ceb5 ) // sf2ceba in FBNeo, it`s a mix between sf2ceb and sf2mdt
	ROM_REGION( CODE_SIZE, "maincpu", 0 ) // 68000 code
	ROM_LOAD16_BYTE( "3.ic171", 0x000000, 0x80000, CRC(a2355d90) SHA1(6c9e1294c55a5a9f244f6f1ce46224c51f910bb1) )
	ROM_LOAD16_BYTE( "5.ic171", 0x000001, 0x80000, CRC(c6f86e84) SHA1(546841fe7d423fff05a7772aa57fa3274515c32b) )
	ROM_LOAD16_BYTE( "2.ic171", 0x100000, 0x20000, CRC(74844192) SHA1(99cd546c78cce7f632007af454d8a55eddb6b19b) )
	ROM_LOAD16_BYTE( "4.ic171", 0x100001, 0x20000, CRC(bd98ff15) SHA1(ed902d949b0b5c5beaaea78a4b418ffa6db9e1df) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROM_LOAD32_WORD( "pf4-sh058.ic90", 0x000000, 0x100000, CRC(446575c7) SHA1(2bd769674fbe280d304b389daf74202cf9e4ac22) )
	ROM_LOAD32_WORD( "pf7-sh072.ic88", 0x000002, 0x100000, CRC(fb78022e) SHA1(b8974387056dd52db96b01cc4648edc814398c7e) )
	ROM_LOAD32_WORD( "pf5-sh036.ic91", 0x200000, 0x100000, CRC(0a6be48b) SHA1(b7e72c94d4e3eb4a6bba6608d9b9a093c8901ad9) )
	ROM_LOAD32_WORD( "pf8-sh074.ic93", 0x200002, 0x100000, CRC(6258c7cf) SHA1(4cd7519245c0aa816934a43e6743160f715d7dc2) )
	ROM_LOAD32_WORD( "pf6-sh071.ic86", 0x400000, 0x100000, CRC(9b5b09d7) SHA1(698a6aab41e495bd0c37a19aee16a84f04d15797) )
	ROM_LOAD32_WORD( "pf9-sh065.ic84", 0x400002, 0x100000, CRC(9f25090e) SHA1(12ff0431ef6550db446985c8914ac7d78eec6b6d) )

	ROM_REGION( 0x30000, "audiocpu", 0 ) // Sound program + samples
	ROM_LOAD( "5.ic26", 0x00000, 0x20000, CRC(17d5ba8a) SHA1(6ff3b8860d7e1fdee3561846f645eb4d3a8965ec) )
	ROM_RELOAD(         0x10000, 0x20000 )
ROM_END

ROM_START( sf2m9 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "27040.6", 0x000000, 0x80000, CRC(16c6372e) SHA1(5d5a49392f2fb806e66e0ac137df00425ca52e7f) )
	ROM_LOAD16_BYTE( "27040.5", 0x000001, 0x80000, CRC(137d5f2e) SHA1(835e9b767e6499f161c5c4fd9a31a9f54b3ee68f) )
	ROM_LOAD16_BYTE( "27010.4", 0x100000, 0x20000, CRC(8226c11c) SHA1(9588bd64e338901394805aca8a234f880674dc60) )
	ROM_LOAD16_BYTE( "27010.3", 0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )


	ROM_REGION( 0x600000, "gfx", 0 )
	ROM_LOAD64_BYTE( "tat-01.bin", 0x000000, 0x40000, CRC(a887f7d4) SHA1(d7e0c46b3ab1c6352f45033cb9e610d9c34d51fb) )
	ROM_CONTINUE(                  0x000004, 0x40000)
	ROM_LOAD64_BYTE( "tat-05.bin", 0x000001, 0x40000, CRC(9390ff23) SHA1(b234169615aa952e3b15c7b0dfb495e499ba49ef) )
	ROM_CONTINUE(                  0x000005, 0x40000)
	ROM_LOAD64_BYTE( "tat-02.bin", 0x000002, 0x40000, CRC(afb3b589) SHA1(9721fa705d62814e416c38a6c3e698efb9385a98) )
	ROM_CONTINUE(                  0x000006, 0x40000)
	ROM_LOAD64_BYTE( "tat-06.bin", 0x000003, 0x40000, CRC(90f2053e) SHA1(a78710421e702b410650c45c3dec21bf16799fb4) )
	ROM_CONTINUE(                  0x000007, 0x40000)

	ROM_LOAD64_BYTE( "tat-03.bin", 0x200000, 0x40000, CRC(79fa8bf0) SHA1(9f8f7b8dc54a75226beb017b9ca9fd62a9e42f6b) )
	ROM_CONTINUE(                  0x200004, 0x40000)
	ROM_LOAD64_BYTE( "tat-07.bin", 0x200001, 0x40000, CRC(6a5f153c) SHA1(f3d82ad01e2e4bdb2039815747fa14399c69753a) )
	ROM_CONTINUE(                  0x200005, 0x40000)
	ROM_LOAD64_BYTE( "tat-04.bin", 0x200002, 0x40000, CRC(32518120) SHA1(56ffa5fffb714cff8be8be5a3675b8a5fa29b2bc) )
	ROM_CONTINUE(                  0x200006, 0x40000)
	ROM_LOAD64_BYTE( "tat-08.bin", 0x200003, 0x40000, CRC(c16579ae) SHA1(42c9d6df9f3b015f5d1ad4fa2b34ea90bb37bcae) )
	ROM_CONTINUE(                  0x200007, 0x40000)

	ROM_LOAD64_BYTE( "tat-09.bin", 0x400000, 0x40000, CRC(169d85a6) SHA1(dd98c8807e80465858b2eac10825e598c37e1a93) )
	ROM_CONTINUE(                  0x400004, 0x40000)
	ROM_LOAD64_BYTE( "tat-11.bin", 0x400001, 0x40000, CRC(32a3a841) SHA1(6f9a13b8828998d194dd3933b032c75efed9cab3) )
	ROM_CONTINUE(                  0x400005, 0x40000)
	ROM_LOAD64_BYTE( "tat-10.bin", 0x400002, 0x40000, CRC(0c638630) SHA1(709d183d181a0509c7ed839c59214851468d2bb8) )
	ROM_CONTINUE(                  0x400006, 0x40000)
	ROM_LOAD64_BYTE( "tat-12.bin", 0x400003, 0x40000, CRC(6ee19b94) SHA1(c45119d04879b6ca23a3f7749175c56b381b43f2) )
	ROM_CONTINUE(                  0x400007, 0x40000)

	ROM_REGION( 0x18000, "audiocpu", 0 ) /* 64k for the audio CPU (+banks) */
	ROM_LOAD( "27512.1", 0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(        0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 ) /* Samples */
	ROM_LOAD( "27020.2", 0x00000, 0x40000, CRC(6cfffb11) SHA1(995526183ffd35f92e9096500a3fe6237faaa2dd) )

	ROM_REGION( 0x00c8d, "pld", 0 ) /* pal/gal */
	ROM_LOAD( "gal20v8.68kadd", 0x00000, 0x00c8d, CRC(27cdd376) SHA1(9fb5844b33002bec80fb92d3e5d1bbc779087300) )  //68k address decoder

ROM_END

void cps_state::init_sf2mdt()
{
	int i;
	u32 gfx_size = memregion( "gfx" )->bytes();
	u8 *rom = memregion( "gfx" )->base();
	u8 tmp;

	for( i = 0; i < gfx_size; i += 8 )
	{
		tmp = rom[i + 1];
		rom[i + 1] = rom[i + 4];
		rom[i + 4] = tmp;
		tmp = rom[i + 3];
		rom[i + 3] = rom[i + 6];
		rom[i + 6] = tmp;
	}

	m_maincpu->space(AS_PROGRAM).install_write_handler(0x708100, 0x7081ff, write16sm_delegate(*this, FUNC(cps_state::sf2mdt_layer_w)));
	init_sf2mdta();
}



void cps_state::init_sf2mdtb()
{
	int i;
	u32 gfx_size = memregion( "gfx" )->bytes();
	u8 *rom = memregion( "gfx" )->base();
	u8 tmp;

	for( i = 0; i < gfx_size; i += 8 )
	{
		tmp = rom[i + 1];
		rom[i + 1] = rom[i + 4];
		rom[i + 4] = tmp;
		tmp = rom[i + 3];
		rom[i + 3] = rom[i + 6];
		rom[i + 6] = tmp;
	}

	/* bootleg sprite ram */
	m_bootleg_sprite_ram = std::make_unique<u16[]>(0x2000);
	m_maincpu->space(AS_PROGRAM).install_ram(0x700000, 0x703fff, m_bootleg_sprite_ram.get());
	m_maincpu->space(AS_PROGRAM).install_ram(0x704000, 0x707fff, m_bootleg_sprite_ram.get()); /* both of these need to be mapped  */

	init_cps1();
}


void cps_state::init_sf2mdta()
{
	/* bootleg sprite ram */
	m_bootleg_sprite_ram = std::make_unique<u16[]>(0x2000);
	m_maincpu->space(AS_PROGRAM).install_ram(0x700000, 0x703fff, m_bootleg_sprite_ram.get());
	m_maincpu->space(AS_PROGRAM).install_ram(0x704000, 0x707fff, m_bootleg_sprite_ram.get()); /* both of these need to be mapped - see the "Magic Delta Turbo" text on the title screen */

	m_bootleg_work_ram = std::make_unique<u16[]>(0x8000);
	m_maincpu->space(AS_PROGRAM).install_ram(0xfc0000, 0xfcffff, m_bootleg_work_ram.get()); /* this has moved */

	init_cps1();
}

void cps_state::init_sf2b()
{
	/* bootleg sprite ram */
	m_bootleg_sprite_ram = std::make_unique<u16[]>(0x2000);
	m_maincpu->space(AS_PROGRAM).install_ram(0x700000, 0x703fff, m_bootleg_sprite_ram.get());
	m_maincpu->space(AS_PROGRAM).install_ram(0x704000, 0x707fff, m_bootleg_sprite_ram.get());

	init_cps1();
}

void cps_state::init_wofabl()
{
	u32 gfx_size = memregion( "gfx" )->bytes();
	u8 *rom = memregion( "gfx" )->base();
	for (int i = 0; i < gfx_size; i += 8)
	{
		u8 tmp = rom[i + 1];
		rom[i + 1] = rom[i + 4];
		rom[i + 4] = tmp;
		tmp = rom[i + 3];
		rom[i + 3] = rom[i + 6];
		rom[i + 6] = tmp;
	}

	init_cps1();
}

// ************************************************************************* SLAMPIC

MACHINE_START_MEMBER(cps_state, slampic)
{
	m_layer_enable_reg = 0x16;
	m_layer_mask_reg[0] = 0x00;
	m_layer_mask_reg[1] = 0x02;
	m_layer_mask_reg[2] = 0x28;
	m_layer_mask_reg[3] = 0x2a;
	m_layer_scroll1x_offset = 0x40;
	m_layer_scroll2x_offset = 0x40;
	m_layer_scroll3x_offset = 0x40;
	m_sprite_base = 0x1000;
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = 0;
}

void cps_state::slampic(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 12000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::slampic_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	//PIC16C57(config, m_audiocpu, 12000000).set_disable(); /* no valid dumps .. */

	MCFG_MACHINE_START_OVERRIDE(cps_state, slampic)

	EEPROM_93C46_8BIT(config, "eeprom");

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1 );
	m_screen->set_screen_update(FUNC(cps_state::screen_update_fcrash));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state, cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();

	OKIM6295(config, m_oki, 1000000, okim6295_device::PIN7_HIGH).add_route(ALL_OUTPUTS, "mono", 0.30);
}

ROM_START( slampic )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "5.bin", 0x000000, 0x80000,  CRC(7dba63cd) SHA1(222e781ffc40c5c23f5789c0682f549f00beeb8d) )
	ROM_LOAD16_BYTE( "3.bin", 0x000001, 0x80000,  CRC(d86671f3) SHA1(d95fae27b0f4d3688f1c2229c9d3780724a870a8) )
	ROM_LOAD16_BYTE( "4.bin", 0x100000, 0x80000,  CRC(d14d0e42) SHA1(b60c44193b247dc4856bd36d69cbbe9dcb2d21a7) )
	ROM_LOAD16_BYTE( "2.bin", 0x100001, 0x80000,  CRC(38063cd8) SHA1(e647433414ff4fdc0b2c4c7036b8995a95289efa) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROM_LOAD64_BYTE( "9.bin",  0x000000, 0x40000, CRC(dc140351) SHA1(0e69e1c8ded85ba26eb8236449d38ead0243ae78) )
	ROM_CONTINUE(              0x000004, 0x40000)
	ROM_LOAD64_BYTE( "8.bin",  0x000001, 0x40000, CRC(9ae88035) SHA1(3329e9582ca052940e115e759bb3d96f4a9c87fa) )
	ROM_CONTINUE(              0x000005, 0x40000)
	ROM_LOAD64_BYTE( "7.bin",  0x000002, 0x40000, CRC(5321f759) SHA1(7538a6587cf1077921b938070185e0a0ce5ca922) )
	ROM_CONTINUE(              0x000006, 0x40000)
	ROM_LOAD64_BYTE( "6.bin",  0x000003, 0x40000, CRC(c8eb5f76) SHA1(a361d2d2dfe71789736666b744ae5f1e4bf7e1b2) )
	ROM_CONTINUE(              0x000007, 0x40000)
	ROM_LOAD64_BYTE( "17.bin", 0x200000, 0x40000, CRC(21652214) SHA1(039335251f6553c4f36e2d33e8b43fb5726e833e) )
	ROM_CONTINUE(              0x200004, 0x40000)
	ROM_LOAD64_BYTE( "16.bin", 0x200001, 0x40000, CRC(d49d2eb0) SHA1(1af01575340730166975be93bae438e2b0492f98) )
	ROM_CONTINUE(              0x200005, 0x40000)
	ROM_LOAD64_BYTE( "15.bin", 0x200002, 0x40000, CRC(0d98bfd6) SHA1(c11fbf555880a933a4cbf6faa517f59f8443304f) )
	ROM_CONTINUE(              0x200006, 0x40000)
	ROM_LOAD64_BYTE( "14.bin", 0x200003, 0x40000, CRC(807284f1) SHA1(c747c3eaade31c2633fb0a0682dbea900bf2b092) )
	ROM_CONTINUE(              0x200007, 0x40000)
	ROM_LOAD64_BYTE( "13.bin", 0x400000, 0x40000, CRC(293579c5) SHA1(9adafe29664b20834365b339f7ae379cdb9ee138) )
	ROM_CONTINUE(              0x400004, 0x40000)
	ROM_LOAD64_BYTE( "12.bin", 0x400001, 0x40000, CRC(c3727ce7) SHA1(c4abc2c59152c59a45f85393e9525505bc2c9e6e) )
	ROM_CONTINUE(              0x400005, 0x40000)
	ROM_LOAD64_BYTE( "11.bin", 0x400002, 0x40000, CRC(2919883b) SHA1(44ad979daae673c77b3157d2b352797d4ad0ec24) )
	ROM_CONTINUE(              0x400006, 0x40000)
	ROM_LOAD64_BYTE( "10.bin", 0x400003, 0x40000, CRC(f538e620) SHA1(354cd0548b067dfc8782bbe13b0a9c2083dbd290) )
	ROM_CONTINUE(              0x400007, 0x40000)

	ROM_REGION( 0x2000, "audiocpu", 0 ) /* PIC16c57 - protected, dump isn't valid */
	ROM_LOAD( "pic16c57-xt-p.bin", 0x00000, 0x2000, BAD_DUMP CRC(aeae5ccc) SHA1(553afb68f7bf130cdf34e24512f72b4ecef1576f) )

	ROM_REGION( 0x80000, "oki", 0 ) /* OKI6295 samples */
	ROM_LOAD( "18.bin", 0x00000, 0x80000, CRC(73a0c11c) SHA1(a66e1a964313e21c4436200d36c598dcb277cd34) )

	ROM_REGION( 0x20000, "user1", 0 ) // not in the dump, but needed for protection
	ROM_LOAD( "mb_qa.5k", 0x00000, 0x20000, CRC(e21a03c4) SHA1(98c03fd2c9b6bf8a4fc25a4edca87fff7c3c3819) )

	ROM_REGION( 0xc00, "pld", 0 )
	ROM_LOAD( "1_palce16v8.bin", 0x000, 0x117, CRC(bac89609) SHA1(4796a476843b448059ed28ef735d9c6a7886fdef) )  // all unsecured
	ROM_LOAD( "2_palce16v8.bin", 0x200, 0x117, CRC(680edfd5) SHA1(b1b6ad4e2c4e23c384de32326986a58bc74a12ca) )
	ROM_LOAD( "3_palce20v8.bin", 0x400, 0x157, CRC(f1fe9368) SHA1(821b5ad60cd1aa1f325fd07af3b9c4d116aa227e) )
	ROM_LOAD( "4_palce20v8.bin", 0x600, 0x157, CRC(20946530) SHA1(307ad5644aca89d1462510f12fd10187a50376b6) )
	ROM_LOAD( "5_palce20v8.bin", 0x800, 0x157, CRC(44df0cc6) SHA1(b6c4249d6d173792d2736654c93dc30c15c9a4fb) )
	ROM_LOAD( "6_palce16v8.bin", 0xa00, 0x117, CRC(12516583) SHA1(990225b1a8fecb2b95011f25d7d3cc35840103f3) )
ROM_END

ROM_START( slampic2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "4.bin", 0x000000, 0x80000, CRC(105cfefd) SHA1(83a34bc83782ae04be1665a91b44625d24f99466) )
	ROM_LOAD16_BYTE( "2.bin", 0x000001, 0x80000, CRC(6026c95e) SHA1(8503587941ad14a757ad337dc36591fedcddaa41) )
	ROM_LOAD16_BYTE( "3.bin", 0x100000, 0x80000, CRC(0effa84a) SHA1(03342bd4cb1de8652bab874c11cb1ecb69a339c7) )
	ROM_LOAD16_BYTE( "1.bin", 0x100001, 0x80000, CRC(8fcb683a) SHA1(4648656bed010a0c27748df4a78c73c5cae07442) )

	ROM_REGION( 0x600000, "gfx", 0 )  // overall just 2 bytes diff vs official set (slammast)
	ROM_LOAD64_BYTE( "rom7.bin",  0x000000, 0x40000, CRC(b5669ad3) SHA1(ceb3d2a6d6c1443a40d37c8f2ba5f3cf03315908) )  // ~ slampic 9.bin  [1/2] 99.914551% [2/2] IDENTICAL
	ROM_CONTINUE(                 0x000004, 0x40000)
	ROM_LOAD64_BYTE( "rom8.bin",  0x000001, 0x40000, CRC(f07a6085) SHA1(68795a0f5151a45f053059bc2fe4a622d5e10d8a) )  // ~ slampic 8.bin  [1/2] 99.999237% [2/2] IDENTICAL  2 bytes diff
	ROM_CONTINUE(                 0x000005, 0x40000)
	ROM_LOAD64_BYTE( "rom5.bin",  0x000002, 0x40000, CRC(5321f759) SHA1(7538a6587cf1077921b938070185e0a0ce5ca922) )  // = slampic 7.bin
	ROM_CONTINUE(                 0x000006, 0x40000)
	ROM_LOAD64_BYTE( "rom6.bin",  0x000003, 0x40000, CRC(c8eb5f76) SHA1(a361d2d2dfe71789736666b744ae5f1e4bf7e1b2) )  // = slampic 6.bin
	ROM_CONTINUE(                 0x000007, 0x40000)
	ROM_LOAD64_BYTE( "rom11.bin", 0x200000, 0x40000, CRC(21652214) SHA1(039335251f6553c4f36e2d33e8b43fb5726e833e) )  // = slampic 17.bin
	ROM_CONTINUE(                 0x200004, 0x40000)
	ROM_LOAD64_BYTE( "rom12.bin", 0x200001, 0x40000, CRC(d49d2eb0) SHA1(1af01575340730166975be93bae438e2b0492f98) )  // = slampic 16.bin
	ROM_CONTINUE(                 0x200005, 0x40000)
	ROM_LOAD64_BYTE( "rom9.bin",  0x200002, 0x40000, CRC(0d98bfd6) SHA1(c11fbf555880a933a4cbf6faa517f59f8443304f) )  // = slampic 15.bin
	ROM_CONTINUE(                 0x200006, 0x40000)
	ROM_LOAD64_BYTE( "rom10.bin", 0x200003, 0x40000, CRC(807284f1) SHA1(c747c3eaade31c2633fb0a0682dbea900bf2b092) )  // = slampic 14.bin
	ROM_CONTINUE(                 0x200007, 0x40000)
	ROM_LOAD64_BYTE( "rom15.bin", 0x400000, 0x40000, CRC(293579c5) SHA1(9adafe29664b20834365b339f7ae379cdb9ee138) )  // = slampic 13.bin
	ROM_CONTINUE(                 0x400004, 0x40000)
	ROM_LOAD64_BYTE( "rom16.bin", 0x400001, 0x40000, CRC(c3727ce7) SHA1(c4abc2c59152c59a45f85393e9525505bc2c9e6e) )  // = slampic 12.bin
	ROM_CONTINUE(                 0x400005, 0x40000)
	ROM_LOAD64_BYTE( "rom13.bin", 0x400002, 0x40000, CRC(2919883b) SHA1(44ad979daae673c77b3157d2b352797d4ad0ec24) )  // = slampic 11.bin
	ROM_CONTINUE(                 0x400006, 0x40000)
	ROM_LOAD64_BYTE( "rom14.bin", 0x400003, 0x40000, CRC(f538e620) SHA1(354cd0548b067dfc8782bbe13b0a9c2083dbd290) )  // = slampic 10.bin
	ROM_CONTINUE(                 0x400007, 0x40000)

	ROM_REGION( 0x2000, "audiocpu", 0 ) // NO DUMP  -  protected PIC
	ROM_LOAD( "pic_u33.bin", 0x0000, 0x1007, BAD_DUMP CRC(6dba4094) SHA1(ca3362de83205fc6563d16a59b8e6e4bb7ebf4a6) )

	ROM_REGION( 0x140000, "oki", 0 )
	ROM_LOAD( "v1.bin", 0x000000, 0x40000, CRC(8962b469) SHA1(91dc12610a0b780ee2b314cd346182d97279c175) )  // 27c020 w/ sticker "7"
	ROM_LOAD( "v2.bin", 0x040000, 0x80000, CRC(6687df38) SHA1(d1015ae089fab5c5b4d1ab51b20f3aa6b77ed348) )  // 27c4000
	ROM_LOAD( "v3.bin", 0x0c0000, 0x80000, CRC(5782baee) SHA1(c01f8cd08d0c7b78c010ce3f1567383b7435de9f) )  // 27c4000

	ROM_REGION( 0x10000, "user1", 0 )
	ROM_LOAD( "24.bin", 0x00000, 0x10000, CRC(13ea1c44) SHA1(5b05fe4c3920e33d94fac5f59e09ff14b3e427fe) )  // = various sf2 bootlegs (sf2ebbl etc.) "unknown (bootleg priority?)"

	ROM_REGION( 0x0200, "pld", 0 )  // sound
	ROM_LOAD( "2_gal16v8.p1", 0x0000, 0x0117, CRC(a944ff96) SHA1(2871a1c70b91fcd8628e63497afa1275f3a27f93) )
ROM_END

void cps_state::varthb_layer_w(offs_t offset, u16 data)
{
	switch (offset)
	{
	case 0x00:
		m_cps_a_regs[0x0e / 2] = data;
		break;
	case 0x01:
		m_cps_a_regs[0x0c / 2] = data;
		break;
	case 0x02:
		m_cps_a_regs[0x12 / 2] = data;
		m_cps_a_regs[CPS1_ROWSCROLL_OFFS] = data; /* row scroll start */
		break;
	case 0x03:
		m_cps_a_regs[0x10 / 2] = data;
		break;
	case 0x04:
		m_cps_a_regs[0x16 / 2] = data;
		break;
	case 0x05:
		m_cps_a_regs[0x14 / 2] = data;
		break;
	default:
		logerror("%s: Unknown layer cmd %X %X\n",machine().describe_context(),offset<<1,data);
	}
}

void cps_state::varthb_layer2_w(u16 data)
{
	if (data > 0x9000)
		m_cps_a_regs[0x06 / 2] = data;
}

void cps_state::varthb_map(address_map &map)
{
	map(0x000000, 0x1fffff).rom();
	map(0x800000, 0x800001).portr("IN1");
	map(0x800006, 0x800007).w(FUNC(cps_state::cps1_soundlatch_w));
	map(0x800018, 0x80001f).r(FUNC(cps_state::cps1_dsw_r));
	map(0x800030, 0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100, 0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");
	map(0x800140, 0x80017f).rw(FUNC(cps_state::cps1_cps_b_r), FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x800188, 0x800189).w(FUNC(cps_state::varthb_layer2_w));
	map(0x980000, 0x98000b).w(FUNC(cps_state::varthb_layer_w));
	map(0x900000, 0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xff0000, 0xffffff).ram().share("mainram");
}

void cps_state::varthb(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 12000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::varthb_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, 3579545);
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::sgyxz_sound_map);

	MCFG_MACHINE_START_OVERRIDE(cps_state,cps1)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1 );
	m_screen->set_screen_update(FUNC(cps_state::screen_update_cps1));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette, palette_device::BLACK).set_entries(0xc00);

	/* sound hardware */
	SPEAKER(config, "mono").front_center();

	GENERIC_LATCH_8(config, m_soundlatch);
	GENERIC_LATCH_8(config, m_soundlatch2);

	ym2151_device &ym2151(YM2151(config, "2151", XTAL(3'579'545)));
	ym2151.irq_handler().set_inputline(m_audiocpu, 0);
	ym2151.add_route(0, "mono", 0.35);
	ym2151.add_route(1, "mono", 0.35);

	OKIM6295(config, m_oki, XTAL(16'000'000)/4/4, okim6295_device::PIN7_HIGH).add_route(ALL_OUTPUTS, "mono", 0.30);
}

ROM_START( varthb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "2",   0x000000, 0x80000, CRC(2f010023) SHA1(bf4b6c0cd82cf1b86e17d6ea2670110c06e6eabe) )
	ROM_LOAD16_BYTE( "1",   0x000001, 0x80000, CRC(0861dff3) SHA1(bf6dfe18ecaeaa1bbea09267014891c4a4a07943) )
	ROM_LOAD16_BYTE( "4",   0x100000, 0x10000, CRC(aa51e43b) SHA1(46b9dab844c55b50a47d048e5bb114911773699c) )
	ROM_LOAD16_BYTE( "3",   0x100001, 0x10000, CRC(f7e4f2f0) SHA1(2ce4eadb2d6a0e0d5745323eff2c899950ad4d3b) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROM_LOAD64_BYTE( "14",  0x000000, 0x40000, CRC(7ca73780) SHA1(26909db32f84157cd05719e5d1e715e76636d292)  )
	ROM_LOAD64_BYTE( "13",  0x000001, 0x40000, CRC(9fb11869) SHA1(a434fb0b588f934aaa68139495e1212a63ccf162)  )
	ROM_LOAD64_BYTE( "12",  0x000002, 0x40000, CRC(afeba416) SHA1(e722c65ea2e2bac3251c32208899484aa5ef6ad2)  )
	ROM_LOAD64_BYTE( "11",  0x000003, 0x40000, CRC(9eef3507) SHA1(ae03064ca5681fbdc43a34c54aaac11c8467428b)  )
	ROM_LOAD64_BYTE( "10",  0x000004, 0x40000, CRC(eeec6183) SHA1(40dc9c86e90d7c1a2ad600c195fe387180d95fd4)  )
	ROM_LOAD64_BYTE( "9",   0x000005, 0x40000, CRC(0e94f718) SHA1(249534f2323abcdb24099d0abc24c229c699ba94)  )
	ROM_LOAD64_BYTE( "8",   0x000006, 0x40000, CRC(c4ddc5b4) SHA1(79c2a42a664e387932b7804e7a80f5753338c3b0)  )
	ROM_LOAD64_BYTE( "7",   0x000007, 0x40000, CRC(8941ca12) SHA1(5ad5d47b8614c2899d05c65dc3b74947d4bac561)  )

	ROM_REGION( 0x18000, "audiocpu", 0 ) /* 64k for the audio CPU (+banks) */
	ROM_LOAD( "6",    0x00000, 0x08000, CRC(7a99446e) SHA1(ca027f41e3e58be5abc33ad7380746658cb5380a) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 ) /* Samples */
	ROM_LOAD( "5",    0x00000, 0x40000, CRC(1547e595) SHA1(27f47b1afd9700afd9e8167d7e4e2888be34a9e5) )

	ROM_REGION( 0x1000, "pals", 0 )
	ROM_LOAD_OPTIONAL( "varth1.bin",    0x00000, 0x157, CRC(4c6a0d99) SHA1(081a307ef38675de178dd6221e6c4e55a5bfbd87) )
	ROM_LOAD_OPTIONAL( "varth2.bin",    0x00200, 0x157, NO_DUMP ) // Registered
	ROM_LOAD_OPTIONAL( "varth3.bin",    0x00400, 0x157, NO_DUMP ) // Registered
	ROM_LOAD_OPTIONAL( "varth4.bin",    0x00600, 0x117, CRC(53317bf6) SHA1(f7b8f8b2c40429a517e3be63e5aed9573972ddfb) )
	ROM_LOAD_OPTIONAL( "varth5.bin",    0x00800, 0x157, NO_DUMP ) // Registered
	ROM_LOAD_OPTIONAL( "varth6.bin",    0x00a00, 0x157, NO_DUMP ) // Registered
ROM_END

// ******************************************************************************************************************/
#if 0
void wofpic_state::wofpic_layer_w(offs_t offset, u16 data)
{
	switch (offset)
	{
	case 0x00:
		m_cps_a_regs[0x0e / 2] = data;
		break;
	case 0x01:
		m_cps_a_regs[0x0c / 2] = data;
		break;
	case 0x02:
		m_cps_a_regs[0x12 / 2] = data;
		m_cps_a_regs[CPS1_ROWSCROLL_OFFS] = data; /* row scroll start */
		break;
	case 0x03:
		m_cps_a_regs[0x10 / 2] = data;
		break;
	case 0x04:
		m_cps_a_regs[0x16 / 2] = data;
		break;
	case 0x05:
		m_cps_a_regs[0x14 / 2] = data;
		break;
	case 0x06:
		{
			// see bootleggers routines starting at $101000
			// writes values 0-f to 98000c
			// how does this relate to layer control reg value?

			// original game values:
			// m_cps_b_regs[m_layer_enable_reg / 2] = m_mainram[0x6398 / 2];
			// m_cps_b_regs[m_layer_mask_reg[1] / 2] = m_mainram[0x639a / 2];
			// m_cps_b_regs[m_layer_mask_reg[2] / 2] = m_mainram[0x639c / 2];
			// m_cps_b_regs[m_layer_mask_reg[3] / 2] = m_mainram[0x639e / 2];

			m_cps_b_regs[0x3e / 2] = data;

			switch (data)
			{
			case 0:    // 12ce
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x12ce;  // attract lvl 1
				m_cps_b_regs[m_layer_mask_reg[1] / 2] = 0x1f;
				m_cps_b_regs[m_layer_mask_reg[2] / 2] = 0x1ff;
				m_cps_b_regs[m_layer_mask_reg[3] / 2] = 0x7fff;
				break;
			case 1:    // 12c2, 12c6, 270a, 138e, 18ce
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x138e;  // attract lvl 4
				m_cps_b_regs[m_layer_mask_reg[1] / 2] = 0x3f;
				m_cps_b_regs[m_layer_mask_reg[2] / 2] = 0x1ff;
				m_cps_b_regs[m_layer_mask_reg[3] / 2] = 0x7fff;
				break;
			case 2:
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x12ce; // ?
				m_cps_b_regs[m_layer_mask_reg[2] / 2] = 0x780;
				m_cps_b_regs[m_layer_mask_reg[3] / 2] = 0;
				break;
			case 3:    // 1c8e, 1c82, 1c86, 270a
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x1c8e;  // attract lvl 2
				m_cps_b_regs[m_layer_mask_reg[1] / 2] = 0x7ff;
				m_cps_b_regs[m_layer_mask_reg[2] / 2] = 0x780;
				m_cps_b_regs[m_layer_mask_reg[3] / 2] = 0;
				break;
			case 4:
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x12ce; // ?
				m_cps_b_regs[m_layer_mask_reg[2] / 2] = 0;
				m_cps_b_regs[m_layer_mask_reg[3] / 2] = 0x7fff;
				break;
			case 5:
				break;
			case 6:
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x12ce; // ?
				m_cps_b_regs[m_layer_mask_reg[2] / 2] = 0x781;
				m_cps_b_regs[m_layer_mask_reg[3] / 2] = 0x1f;
				break;
			case 7:
				break;
			case 8:
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x12ce; // ?
				m_cps_b_regs[m_layer_mask_reg[2] / 2] = 0;
				m_cps_b_regs[m_layer_mask_reg[3] / 2] = 0x1f;
				break;
			case 9:
				break;
			case 10:
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x12ce; // ?
				m_cps_b_regs[m_layer_mask_reg[2] / 2] = 0x40ff;
				m_cps_b_regs[m_layer_mask_reg[3] / 2] = 0x7fff;
				break;
			case 11:
				break;
			case 14:    // 12ce, 1b0e
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x12ce;
				break;
			case 15:    // 270a, 1e0e, 138e, 270e
				m_cps_b_regs[m_layer_enable_reg / 2] = 0x138e;  // attract lvl 3
				m_cps_b_regs[m_layer_mask_reg[1] / 2] = 0x7fff;
				m_cps_b_regs[m_layer_mask_reg[2] / 2] = 0x7fff;
				m_cps_b_regs[m_layer_mask_reg[3] / 2] = 0x7fff;
				break;
			}
		}
		break;
	default:
		logerror("%s: Unknown layer cmd %X %X\n",machine().describe_context(),offset<<1,data);
	}
}

void wofpic_state::wofpic_layer2_w(u16 data)
{
	m_cps_a_regs[0x06 / 2] = data;
}

void wofpic_state::wofpic_spr_base_w(u16 data)
{
	m_sprite_base = data ? 0x3000 : 0x1000;
}

void wofpic_state::wofpic(machine_config &config)
{
	dinopic(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &wofpic_state::wofpic_map);
	MCFG_MACHINE_START_OVERRIDE(wofpic_state, wofpic)
}

void wofpic_state::wofpic_map(address_map &map)
{
	map(0x000000, 0x3fffff).rom();
	map(0x800000, 0x800007).portr("IN1");            /* Player input ports */
	map(0x800006, 0x800007).w(FUNC(wofpic_state::cps1_soundlatch_w));    /* Sound command */
	map(0x800008, 0x800009).w(FUNC(wofpic_state::wofpic_layer2_w));
	map(0x800018, 0x80001f).r(FUNC(wofpic_state::cps1_dsw_r));            /* System input ports / Dip Switches */
	map(0x800030, 0x800037).w(FUNC(wofpic_state::cps1_coinctrl_w));
	map(0x800100, 0x80013f).w(FUNC(wofpic_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140, 0x80017f).rw(FUNC(wofpic_state::cps1_cps_b_r), FUNC(wofpic_state::cps1_cps_b_w)).share("cps_b_regs");  /* Only writes here at boot */
	map(0x880000, 0x880001).nopw(); // ?
	map(0x900000, 0x92ffff).ram().w(FUNC(wofpic_state::cps1_gfxram_w)).share("gfxram");
	map(0x980000, 0x98000d).w(FUNC(wofpic_state::wofpic_layer_w));
	map(0xf18000, 0xf19fff).nopw(); // few q-sound leftovers
	map(0xf1c000, 0xf1c001).portr("IN2");            /* Player 3 controls (later games) */
	map(0xf1c004, 0xf1c005).w(FUNC(wofpic_state::cpsq_coinctrl2_w));     /* Coin control2 (later games) */
	map(0xf1c006, 0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000, 0xffffff).ram().share("mainram");
}

MACHINE_START_MEMBER(wofpic_state, wofpic)
{
	m_layer_enable_reg = 0x26;
	m_layer_mask_reg[0] = 0x28;
	m_layer_mask_reg[1] = 0x2a;
	m_layer_mask_reg[2] = 0x2c;
	m_layer_mask_reg[3] = 0x2e;
	m_layer_scroll1x_offset = 0x40;
	m_layer_scroll2x_offset = 0x40;
	m_layer_scroll3x_offset = 0x40;
	m_sprite_base = 0x1000;
	m_sprite_list_end_marker = 0x8000;
	m_sprite_x_offset = 2;
}


void wofpic_state::init_wofpic()
{
	m_bootleg_sprite_ram = std::make_unique<u16s[]>(0x2000);
	m_maincpu->space(AS_PROGRAM).install_ram(0x990000, 0x993fff, m_bootleg_sprite_ram.get());
	m_maincpu->space(AS_PROGRAM).install_write_handler(0x990000, 0x990001, write16_delegate(*this, FUNC(wofpic_state::wofpic_spr_base_w)));
	init_cps1();
}
#endif

ROM_START( wofpic )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "1.4m", 0x000001, 0x80000, CRC(d2ae67a8) SHA1(cb1a9f8e6999598b9a1a7c449f147a0c5773b154) )
	ROM_LOAD16_BYTE( "2.4m", 0x000000, 0x80000, CRC(61fd0a01) SHA1(a7b5bdddd7b31645e33314c1d3649e1506cecfea) )
	ROM_LOAD16_BYTE( "3.1m", 0x100001, 0x20000, CRC(739379be) SHA1(897f61527213902fda04bc28339f1f4278bf5ae9) ) // 1xxxxxxxxxxxxxxxx = 0xFF
	ROM_LOAD16_BYTE( "4.1m", 0x100000, 0x20000, CRC(fe5eee87) SHA1(be1230f64c1e59ae3ff3e58593070613966ac79d) ) // 11xxxxxxxxxxxxxxx = 0x00

	ROM_REGION( 0x400000, "gfx", 0 )
	ROM_LOAD64_BYTE( "m12073-2", 0x000000, 0x40000, CRC(c8dcaa95) SHA1(bcaeaefd40ffa1b32e80457cffcc1ceab461af1d) )
	ROM_CONTINUE(                0x000004, 0x40000)
	ROM_LOAD64_BYTE( "m12223-2", 0x000001, 0x40000, CRC(1ab0000c) SHA1(0d0004cc1725c38d140ecb8dc9666361b2d3e607) )
	ROM_CONTINUE(                0x000005, 0x40000)
	ROM_LOAD64_BYTE( "m12223-1", 0x000002, 0x40000, CRC(8425ff6b) SHA1(9a051089c2a492b8c63484582f95c578704b6820) )
	ROM_CONTINUE(                0x000006, 0x40000)
	ROM_LOAD64_BYTE( "m12073-1", 0x000003, 0x40000, CRC(24ce197b) SHA1(0ccdbd6f6a30e6d1479f8702c3e8561b16303550) )
	ROM_CONTINUE(                0x000007, 0x40000)
	ROM_LOAD64_BYTE( "m12073-6", 0x200000, 0x40000, CRC(9d20ef9b) SHA1(cbf3cb6bd7a73312e5061082554f2e17aae08621) )
	ROM_CONTINUE(                0x200004, 0x40000)
	ROM_LOAD64_BYTE( "m12073-5", 0x200001, 0x40000, CRC(90c93dd2) SHA1(d3d2b0bcbcbb21a41f986eb752ab114697eb9402) )
	ROM_CONTINUE(                0x200005, 0x40000)
	ROM_LOAD64_BYTE( "m12073-4", 0x200002, 0x40000, CRC(219fd7e2) SHA1(af765eb7b275ed541c08e243b22b5c9f54c1a8ec) )
	ROM_CONTINUE(                0x200006, 0x40000)
	ROM_LOAD64_BYTE( "m12073-3", 0x200003, 0x40000, CRC(efc17c9a) SHA1(26429a9039bb249e17945508c16645c82f7f412a) )
	ROM_CONTINUE(                0x200007, 0x40000)

	ROM_REGION( 0x2000, "audiocpu", 0 ) // NO DUMP  -  protected PIC
	ROM_LOAD( "pic.bin", 0x0000, 0x1007, NO_DUMP )

	ROM_REGION( 0x080000, "oki", 0 )
	ROM_LOAD( "ma12073.4mm", 0x00000, 0x80000, CRC(ac421276) SHA1(56786c23b0d96e1a2540e7269aa20fd390f98b5b) )
ROM_END

// ************************************************************************* DRIVER MACROS

GAME( 1990, cawingbl,  cawing,   cawingbl,  cawingbl, cps_state, init_cawingbl, ROT0,   "bootleg", "Carrier Air Wing (bootleg with 2xYM2203 + 2xMSM205 set 1)", MACHINE_SUPPORTS_SAVE ) // 901012 ETC
GAME( 1990, cawingb2,  cawing,   cawingbl,  cawingbl, cps_state, init_cawingbl, ROT0,   "bootleg", "Carrier Air Wing (bootleg with 2xYM2203 + 2xMSM205 set 2)", MACHINE_SUPPORTS_SAVE ) // 901012 ETC

GAME( 1993, dinopic,   dino,     dinopic,   dino,     cps_state, init_dinopic,  ROT0,   "bootleg", "Cadillacs and Dinosaurs (bootleg with PIC16c57, set 1)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE ) // 930201 ETC
GAME( 1993, dinopic2,  dino,     dinopic,   dino,     cps_state, init_dinopic,  ROT0,   "bootleg", "Cadillacs and Dinosaurs (bootleg with PIC16c57, set 2)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE ) // 930201 ETC
GAME( 1993, dinopic3,  dino,     dinopic,   dino,     cps_state, init_dinopic,  ROT0,   "bootleg", "Cadillacs and Dinosaurs (bootleg with PIC16C57, set 3)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )     // 930201 ETC
//GAME( 1993, dinopic4,  dino,     dinopic,   dino,     cps_state, init_dinopic,  ROT0,   "bootleg", "Cadillacs and Dinosaurs (bootleg with PIC16C57, set 4)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE ) // 930201 ETC
GAME( 1993, jurassic99,dino,     dinopic,   dino,     cps_state, init_dinopic,  ROT0,   "bootleg", "Jurassic 99 (Cadillacs and Dinosaurs bootleg with EM78P447AP)",  MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )     // 930201 ?

GAME( 1990, fcrash,    ffight,   fcrash,    fcrash,   cps_state, init_cps1,     ROT0,   "bootleg (Playmark)", "Final Crash (bootleg of Final Fight)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, ffightbl,  ffight,   fcrash,    fcrash,   cps_state, init_cps1,     ROT0,   "bootleg", "Final Fight (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, ffightbla, ffight,   fcrash,    fcrash,   cps_state, init_cps1,     ROT0,   "bootleg", "Final Fight (bootleg on Final Crash PCB)", MACHINE_SUPPORTS_SAVE ) // same as Final Crash without the modified gfx
//GAME( 1990, ffightblb, ffight,   ffightblb, fcrash,   cps_state, init_cps1,     ROT0,   "bootleg (Soon Hwa)",  "Final Fight (bootleg with single OKI)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE ) // priority glitches

GAME( 1991, kodb,      kod,      kodb,      kodb,     cps_state, init_kodb,     ROT0,   "bootleg (Playmark)", "The King of Dragons (bootleg)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE ) // 910731  "ETC"

GAME( 1991, knightsb,  knights,  knightsb,  knights,  cps_state, init_dinopic,  ROT0,   "bootleg", "Knights of the Round (bootleg with 2xMSM5205, set 1)", MACHINE_SUPPORTS_SAVE )    // 911127 - based on World version
GAME( 1991, knightsb3, knights,  knightsb,  knights,  cps_state, init_dinopic,  ROT0,   "bootleg", "Knights of the Round (bootleg with 2xMSM5205, set 2)",  MACHINE_SUPPORTS_SAVE )  // 911127 ETC

GAME( 1993, mtwinsb,   mtwins,   mtwinsb,   mtwins,   cps_state, init_mtwinsb,  ROT0,   "David Inc. (bootleg)", "Twins (Mega Twins bootleg)", MACHINE_SUPPORTS_SAVE ) // based on World version

GAME( 1993, punipic,   punisher, punipic,   punisher, cps_state, init_punipic,  ROT0,   "bootleg", "The Punisher (bootleg with PIC16c57, set 1)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE ) // 930422 ETC
GAME( 1993, punipic2,  punisher, punipic,   punisher, cps_state, init_punipic,  ROT0,   "bootleg", "The Punisher (bootleg with PIC16c57, set 2)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE ) // 930422 ETC
GAME( 1993, punipic3,  punisher, punipic,   punisher, cps_state, init_punipic3, ROT0,   "bootleg", "The Punisher (bootleg with PIC16c57, set 3)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE ) // 930422 ETC

GAME( 1992, sf2m1,     sf2ce,    sf2m1,     sf2,      cps_state, init_sf2m1,    ROT0,   "bootleg", "Street Fighter II': Champion Edition (M1, bootleg)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE ) // 920313 ETC
GAME( 1992, sf2m9,     sf2ce,    sf2m1,     sf2,      cps_state, init_dinopic,  ROT0,   "bootleg", "Street Fighter II': Champion Edition (M9, bootleg)",  MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE ) // 920313 ETC

GAME( 1992, sf2mdt,    sf2ce,    sf2mdt,    sf2mdt,   cps_state, init_sf2mdt,   ROT0,   "bootleg", "Street Fighter II': Magic Delta Turbo (bootleg, set 1)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )   // 920313 - based on (heavily modified) World version
GAME( 1992, sf2mdta,   sf2ce,    sf2mdt,    sf2mdt,   cps_state, init_sf2mdta,  ROT0,   "bootleg", "Street Fighter II': Magic Delta Turbo (bootleg, set 2)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )   // 920313 - based on World version
GAME( 1992, sf2mdtb,   sf2ce,    sf2mdt,    sf2mdtb,  cps_state, init_sf2mdtb,  ROT0,   "bootleg", "Street Fighter II': Magic Delta Turbo (bootleg, set 3)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )   // 920313 - based on World version

GAME( 1992, sf2b,      sf2,      sf2b,      sf2mdt,   cps_state, init_sf2b,     ROT0,   "bootleg", "Street Fighter II: The World Warrior (bootleg)",  MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE ) //910204 - based on World version
GAME( 1992, sf2b2,     sf2,      sf2b,      sf2mdt,   cps_state, init_sf2mdtb,  ROT0,   "bootleg", "Street Fighter II: The World Warrior (bootleg, set 2)",  MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE ) //910204 - based on World version

GAME( 1992, sf2ceb,    sf2ce,    sf2mdt,    sf2mdt,   cps_state, init_sf2mdta,  ROT0,   "bootleg (Playmark)", "Street Fighter II': Champion Edition (Playmark bootleg, set 1)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )   // 920313 - based on World version
GAME( 1992, sf2ceb2,   sf2ce,    sf2mdt,    sf2mdt,   cps_state, init_sf2mdtb,  ROT0,   "bootleg", "Street Fighter II': Champion Edition (bootleg, set 1)",  MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )  // 920313 ETC
GAME( 1992, sf2ceb3,   sf2ce,    sf2mdt,    sf2mdt,   cps_state, init_sf2mdtb,  ROT0,   "bootleg", "Street Fighter II': Champion Edition (bootleg, set 2)",  MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )  // 920313 ETC
GAME( 1992, sf2ceb4,   sf2ce,    sf2mdt,    sf2mdt,   cps_state, init_sf2mdtb,  ROT0,   "bootleg (Playmark)", "Street Fighter II': Champion Edition (Playmark bootleg, set 2)",  MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )  // 920313 ETC
GAME( 1992, sf2ceb5,   sf2ce,    sf2mdt,    sf2mdt,   cps_state, init_sf2mdta,  ROT0,   "bootleg (Playmark)", "Street Fighter II': Champion Edition (Playmark bootleg, set 3)",  MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )  // 920313 ETC

GAME( 1993, slampic,   slammast, slampic,   slampic,  cps_state, init_dinopic,  ROT0,   "bootleg", "Saturday Night Slam Masters (bootleg with PIC16c57, set 1)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE ) // 930713 ETC
//GAME( 1993, slampic2,  slammast, slampic,   slampic2, cps_state, init_dinopic,  ROT0,   "bootleg", "Saturday Night Slam Masters (bootleg with PIC16C57, set 2)",  MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )  // 930713 ETC

GAME( 1999, sgyxz,     wof,      sgyxz,     sgyxz,    cps_state, init_cps1,     ROT0,   "bootleg", "Sangokushi II: Sanguo Yingxiong Zhuan (Chinese bootleg set 3, 921005 Asia)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )   // 921005 - Sangokushi 2
GAME( 1992, wofabl,    wof,      wofabl,    wofabl,   cps_state, init_cps1,     ROT0,   "bootleg", "Sangokushi II (bootleg)",  MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )   // 921005 - Sangokushi 2
//GAME( 1992, wofpic,    wof,      wofpic,    wof,      cps_state, init_wofpic,   ROT0,   "bootleg",  "Warriors of Fate (bootleg with PIC16C57)",  MACHINE_IMPERFECT_GRAPHICS | MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )  // 921002 ETC

GAME( 1992, varthb,    varth,    varthb,    varth,    cps_state, init_mtwinsb,  ROT270, "bootleg", "Varth: Operation Thunderstorm (bootleg)", MACHINE_SUPPORTS_SAVE )

// HBMAME **********************************************/


GAME( 1990, cawingb,   cawing,   cawingb, cawingbl,   cps_state, init_cawingbl,  ROT0,   "bootleg", "Carrier Air Wing (bootleg)", MACHINE_SUPPORTS_SAVE )

void cps_state::captcommb2_map(address_map &map) {
	map(0x000000,0x1fffff).rom();
	map(0x800000,0x800001).portr("IN1");  /* Player input ports */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x800180,0x800181).w(FUNC(cps_state::fcrash_soundlatch_w));  /* Sound command */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xff0000,0xffffff).ram();
}


MACHINE_START_MEMBER(cps_state, captcommb2)
{
	u8 *ROM = memregion("audiocpu")->base();

	membank("bank1")->configure_entries(0, 16, &ROM[0x10000], 0x4000);

	save_item(NAME(m_sample_buffer1));
	save_item(NAME(m_sample_buffer2));
	save_item(NAME(m_sample_select1));
	save_item(NAME(m_sample_select2));
}

void cps_state::captcommb2(machine_config &config)
{
	/* basic machine hardware */
	M68000(config, m_maincpu, 10000000);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::captcommb2_map);
	m_maincpu->set_vblank_int("screen", FUNC(cps_state::cps1_interrupt));
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &cps_state::cpu_space_map);

	Z80(config, m_audiocpu, 3579545);
	m_audiocpu->set_addrmap(AS_PROGRAM, &cps_state::sf2mdt_z80map);

	MCFG_MACHINE_START_OVERRIDE(cps_state, captcommb2)
	MCFG_MACHINE_RESET_OVERRIDE(cps_state, fcrash)

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(8*8, (64-8)*8-1, 2*8, 30*8-1 );
	m_screen->set_screen_update(FUNC(cps_state::screen_update_cps1));
	m_screen->screen_vblank().set(FUNC(cps_state::screen_vblank_cps1));
	m_screen->set_palette(m_palette);

	GFXDECODE(config, m_gfxdecode, m_palette, gfx_cps1);
	PALETTE(config, m_palette).set_entries(0xc00);

	MCFG_VIDEO_START_OVERRIDE(cps_state,cps1)

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	GENERIC_LATCH_8(config, m_soundlatch);

	ym2151_device &ym2151(YM2151(config, "2151", XTAL(3'579'545)));
	ym2151.add_route(0, "mono", 0.35);
	ym2151.add_route(1, "mono", 0.35);

	/* has 2x MSM5205 instead of OKI6295 */
	MSM5205(config, m_msm_1, 24000000/64);  /* ? */
	m_msm_1->vck_legacy_callback().set(FUNC(cps_state::m5205_int1)); /* interrupt function */
	m_msm_1->set_prescaler_selector(msm5205_device::S96_4B);    /* 4KHz 4-bit */
	m_msm_1->add_route(ALL_OUTPUTS, "mono", 0.25);

	MSM5205(config, m_msm_2, 24000000/64);  /* ? */
	m_msm_2->vck_legacy_callback().set(FUNC(cps_state::m5205_int2)); /* interrupt function */
	m_msm_2->set_prescaler_selector(msm5205_device::S96_4B);    /* 4KHz 4-bit */
	m_msm_2->add_route(ALL_OUTPUTS, "mono", 0.25);
}


ROM_START( captcommb2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )      /* 68000 code */
	ROM_LOAD16_BYTE( "5.bin",   0x000000, 0x80000, CRC(c3a6ed28) SHA1(f79fed35f7b0dc383837a2ead846acc686dd3487) )
	ROM_LOAD16_BYTE( "4.bin",   0x000001, 0x80000, CRC(28729335) SHA1(6dd23c2d41e4e182434fe80c03d5c90785e6c0ce) )
	ROM_LOAD16_BYTE( "3.bin",   0x100000, 0x40000, CRC(1b526d73) SHA1(3dd8dec61db4f4f5546937602a8fb01c639d72f8) )
	ROM_LOAD16_BYTE( "2.bin",   0x100001, 0x40000, CRC(73c99709) SHA1(e122e3771b698c44fb998589af0542b1f2a3876a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",     0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",     0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",     0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",     0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",     0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",     0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",     0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a",     0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x50000, "audiocpu", 0 ) /* Sound program + samples  */
	ROM_LOAD( "1.bin",        0x00000, 0x40000, CRC(aed2f4bd) SHA1(3bd567dc350bf6ac3a349548790ad49eb5bd8307) )
	ROM_RELOAD(               0x10000, 0x40000 )
ROM_END


GAME( 1991, captcommb2,captcomm, captcommb2,captcomm, cps_state, init_cps1,     ROT0,   "bootleg", "Captain Commando (bootleg with YM2151 + 2xMSM5205)", MACHINE_SUPPORTS_SAVE )

