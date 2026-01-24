// license:BSD-3-Clause
// copyright-holders:Bryan McPhail,Ernesto Corvi,Andrew Prime,Zsolt Vasvari
// thanks-to:Fuzz
/*************************************************************************

    Neo-Geo hardware

*************************************************************************/

#include "emu.h"
#include "cpu/m68000/m68000.h"
#include "cpu/z80/z80.h"
#include "machine/nvram.h"
#include "machine/watchdog.h"
#include "sound/ymopn.h"
#include "machine/upd1990a.h"
#include "machine/ng_memcard.h"
#include "machine/gen_latch.h"
#include "video/neogeo_spr.h"
#include "imagedev/snapquik.h"
#include "bus/neogeo/prot.h"
#include "bus/neogeo/banked_cart.h"
#include "bus/neogeo_ctrl/ctrl.h"
#include "emupal.h"
#include "screen.h"
#include "speaker.h"

// On scanline 224, /VBLANK goes low 56 mclks (14 pixels) from the rising edge of /HSYNC.
// Two mclks after /VBLANK goes low, the hardware sets a pending IRQ1 flip-flop.
#define NEOGEO_VBLANK_IRQ_HTIM (attotime::from_ticks(56+2, NEOGEO_MASTER_CLOCK))
	// macros allow code below to be copy+pasted into slot devices more easily
#define cpuregion memregion("maincpu")->base()
#define cpuregion_size memregion("maincpu")->bytes()
#define spr_region memregion("sprites")->base()
#define spr_region_size memregion("sprites")->bytes()
#define fix_region memregion("fixed")->base()
#define fix_region_size memregion("fixed")->bytes()
#define ym_region memregion("ymsnd:adpcma")->base()
#define ym_region_size memregion("ymsnd:adpcma")->bytes()
#define audiocpu_region memregion("audiocpu")->base()
#define audio_region_size memregion("audiocpu")->bytes()
#define audiocrypt_region memregion("audiocrypt")->base()
#define audiocrypt_region_size memregion("audiocrypt")->bytes()


class neogeo_state : public driver_device
{
public:
	neogeo_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_banked_cart(*this, "banked_cart")
		, m_audiocpu(*this, "audiocpu")
		, m_ym(*this, "ymsnd")
		, m_region_maincpu(*this, "maincpu")
		, m_region_sprites(*this, "sprites")
		, m_region_fixed(*this, "fixed")
		, m_region_fixedbios(*this, "fixedbios")
		, m_bank_audio_main(*this, "audio_main")
		, m_upd4990a(*this, "upd4990a")
		, m_save_ram(*this, "saveram")
		, m_screen(*this, "screen")
		, m_palette(*this, "palette")
		, m_memcard(*this, "memcard")
		, m_dsw(*this, "DSW")
		, m_trackx(*this, "TRACK_X")
		, m_tracky(*this, "TRACK_Y")
		, m_edge(*this, "edge")
		, m_ctrl1(*this, "ctrl1")
		, m_ctrl2(*this, "ctrl2")
		, m_sprgen(*this, "spritegen")
		, m_soundlatch(*this, "soundlatch")
		, m_soundlatch2(*this, "soundlatch2")
		, m_mslugx_prot(*this, "mslugx_prot")
		, m_sma_prot(*this, "sma_prot")
		, m_cmc_prot(*this, "cmc_prot")
		, m_pcm2_prot(*this, "pcm2_prot")
		, m_pvc_prot(*this, "pvc_prot")
		, m_bootleg_prot(*this, "bootleg_prot")
		, m_kof2002_prot(*this, "kof2002_prot")
		, m_fatfury2_prot(*this, "fatfury2_prot")
		, m_kof98_prot(*this, "kof98_prot")
		, m_sbp_prot(*this, "sbp_prot")
		, m_kog_prot(*this, "kog_prot")
		, m_out_digit(*this, "digit%u", 0U)
		, m_bios_bank(*this, "bankedbios")
	{ }

	// Mainboard Configurations
	void mvs(machine_config &config);
	void neogeo_arcade(machine_config &config);
	void neogeo_base(machine_config &config);
	void neogeo_dial(machine_config &config);
	void neogeo_imaze(machine_config &config);
	void neogeo_kiz4p(machine_config &config);
	void neogeo_kog(machine_config &config);
	void neogeo_mahjong(machine_config &config);
	void neogeo_noctrl(machine_config &config);
	void neogeo_noslot(machine_config &config);
    void no_watchdog(machine_config &config);
	void gsc2007(machine_config &config);
	void gsc(machine_config &config);
	void neogeo_68kram(machine_config &config);
    void multimvs(machine_config &config);
	void neosd(machine_config &config);

	// Mainboard Configurations CPUX2
    void neoclock_arcade(machine_config &config);
	void neoclock_base(machine_config &config);
	void neoclock_noslot(machine_config &config);

	// Fixed MVS/AES Software Configurations
	void init_neogeo();
	void init_bangbead();
	void init_ct2k3sp();
	void init_ct2k3spd();
	void init_ct2k3sa();
	void init_ct2k3sad();
	void init_cthd2003();
	void init_cthd2k3a();
	void init_fatfury2();
	void init_ganryu();
	void init_garou();
	void init_garoud();
	void init_garouh();
	void init_garouhd();
	void init_garoubl();
	void init_jockeygp();
	void init_kf10thep();
	void init_kf2k1pa();
	void init_kf2k2pla();
	void init_kf2k2plb();
	void init_kf2k2plc();
	void init_kf2k2mp();
	void init_kf2k2mp2();
	void init_kf2k3pcb();
	void init_kf2k3pl();
	void init_kf2k3pld();
	void init_kf2k3upl();
	void init_kf2k3upld();
	void init_kf2k5uni();
	void init_kof10th();
	void init_kof10thu();
	void init_kof2k3pcd();
	void init_kof2k4pls();
	void init_kof2k4se();
	void init_kof96ep();
	void init_kof97oro();
	void init_kof97pla();
	void init_kof98();
	void init_kof99();
	void init_kof99d();
	void init_kof2000();
	void init_kof2000d();
	void init_kof2001();
	void init_kof2002();
	void init_kof2002b();
	void init_kof2003();
	void init_kof2003d();
	void init_kof2003h();
	void init_kof2003b();
	void init_kog();
	void init_kogd();
	void init_lans2004();
	void init_matrim();
	void init_matrima();
	void init_matrimbl();
	void init_matrimd();
	void init_matrimnd();
	void init_ms5pcb();
	void init_ms5plus();
	void init_mslug3();
	void init_mslug3a();
    void init_mslug3b6();
	void init_mslug3d();
	void init_mslug4();
	void init_mslug4e();
	void init_mslug5();
	void init_mslug5b();
	void init_mslug5d();
	void init_mslug5nd();
	void init_mslugx();
	void init_nitd();
	void init_pnyaa();
	void init_preisle2();
	void init_rotd();
	void init_rotdnd();
	void init_s1945p();
	void init_samsh5sp();
	void init_samsho5();
	void init_samsho5b();
	void init_sbp();
	void init_sengoku3();
	void init_shockt2w();
	void init_svc();
	void init_svcd();
	void init_svcboot();
	void init_svcpcb();
	void init_svcplus();
	void init_svcplusa();
	void init_svcsplus();
	void init_vliner();
	void init_zupapa();

	// Fixed Neo CD conversion MVS Software Configurations
	void init_cd();
	void init_fr2cd();

	// Fixed MVS/AES Decrypted Darksoft Software Configurations
	void init_darksoft();
	void init_ct2k3sadd();
	void init_ct2k3spdd();
	void init_cthd2003dd();
	void init_fatfury2dd();
	void init_garoudd();
	void init_garouhdd();
	void init_jockeygpdd();
	void init_kf2k3pldd();
	void init_kf2k3upldd();
	void init_kof2000dd();
	void init_kof2002dd();
	void init_kof2003dd();
	void init_kof98dd();
	void init_kof99dd();
	void init_matrimdd();
	void init_mslug3dd();
    void init_mslug4dd();
	void init_mslug5dd();
	void init_svcdd();
	void init_vlinerdd();

	DECLARE_CUSTOM_INPUT_MEMBER(get_memcard_status);
	DECLARE_CUSTOM_INPUT_MEMBER(get_audio_result);
	DECLARE_CUSTOM_INPUT_MEMBER(kizuna4p_start_r);
	DECLARE_INPUT_CHANGED_MEMBER(select_bios);

	// Public For kf2k2ps2re
	int m_use_cart_audio = 0;
	void gsc_map(address_map &map);
	virtual void machine_start() override;
	required_device<cpu_device> m_maincpu;

private:
	u32 mvs_open7z(std::string zip_name, std::string filename, uint8_t *region_name, u32 region_size);
	void io_control_w(offs_t offset, u8 data);
	u16 memcard_r(offs_t offset);
	void memcard_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void audio_command_w(u8 data);
	u8 audio_command_r();
	u8 audio_cpu_bank_select_r(offs_t offset);
	void audio_cpu_enable_nmi_w(offs_t offset, u8 data);
	void system_control_w(offs_t offset, u8 data);
	u16 neogeo_unmapped_r(address_space &space);
	u16 neogeo_paletteram_r(offs_t offset);
	void neogeo_paletteram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	u16 neogeo_video_register_r(address_space &space, offs_t offset, u16 mem_mask = ~0);
	void neogeo_video_register_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	u16 banked_vectors_r(offs_t offset);
	u16 in0_r();
	u16 in1_r();
	void save_ram_w(offs_t offset, u16 data, u16 mem_mask = ~0);

	TIMER_CALLBACK_MEMBER(display_position_interrupt_callback);
	TIMER_CALLBACK_MEMBER(display_position_vblank_callback);
	TIMER_CALLBACK_MEMBER(vblank_interrupt_callback);
    DECLARE_QUICKLOAD_LOAD_MEMBER(mvs_q_cb);
	DECLARE_QUICKLOAD_LOAD_MEMBER(neo_q_cb);

	u32 screen_update_neogeo(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	void neogeo_main_map(address_map &map);
	void main_map_slot(address_map &map);
	void audio_map(address_map &map);
	void audio_io_map(address_map &map);
	void main_map_noslot(address_map &map);
	void gsc2007_map(address_map &map);
    void neogeo_68kram_map(address_map &map);

	void neogeo_postload();
	void update_interrupts();
	void create_interrupt_timers();
	void start_interrupt_timers();
	void neogeo_acknowledge_interrupt(u16  data);

	void neogeo_main_cpu_banking_init();
	void neogeo_audio_cpu_banking_init(int set_entry);
	void adjust_display_position_interrupt_timer();
	void neogeo_set_display_position_interrupt_control(u16  data);
	void neogeo_set_display_counter_msb(u16  data);
	void neogeo_set_display_counter_lsb(u16  data);
	void set_video_control( u16  data );

	void create_rgb_lookups();
	void set_pens();
	void neogeo_set_screen_shadow( int data );
	void neogeo_set_palette_bank( int data );

	void audio_cpu_check_nmi();
	void set_save_ram_unlock( u8 data );
	void set_outputs(  );
	void set_output_latch( u8 data );
	void set_output_data( u8 data );

	virtual void machine_reset() override;

	memory_bank           *m_bank_audio_cart[4]{};

	// configuration
	enum {NEOGEO_MVS, NEOGEO_AES, NEOGEO_CD} m_type;

	// internal state
	bool       m_recurse = 0;
	bool       m_audio_cpu_nmi_enabled = 0;
	bool       m_audio_cpu_nmi_pending = 0;

	// MVS-specific state
	u8      m_save_ram_unlocked = 0U;
	u8      m_output_data = 0U;
	u8      m_output_latch = 0U;
	u8      m_el_value = 0U;
	u8      m_led1_value = 0U;
	u8      m_led2_value = 0U;

	virtual void video_start() override;

	emu_timer  *m_display_position_interrupt_timer = nullptr;
	emu_timer  *m_display_position_vblank_timer = nullptr;
	emu_timer  *m_vblank_interrupt_timer = nullptr;
	u32     m_display_counter = 0U;
	u8      m_vblank_interrupt_pending = 0U;
	u8      m_display_position_interrupt_pending = 0U;
	u8      m_irq3_pending = 0U;
	u8      m_display_position_interrupt_control = 0U;
	u8      m_vblank_level = 0U;
	u8      m_raster_level = 0U;

	u16  get_video_control(  );

	// color/palette related
	std::vector<u16 > m_paletteram{};
	u8        m_palette_lookup[32][4]{};
	const pen_t *m_bg_pen;
	int          m_screen_shadow = 0;
	int          m_palette_bank = 0;

	u16 neogeo_slot_rom_low_r();
	u16 neogeo_slot_rom_low_vectors_r(offs_t offset);

	void install_banked_bios();

	int m_use_cart_vectors = 0;
	optional_device<neogeo_banked_cart_device> m_banked_cart;
	required_device<cpu_device> m_audiocpu;
	required_device<ym2610_device> m_ym;
	required_memory_region m_region_maincpu;
	required_memory_region m_region_sprites;
	required_memory_region m_region_fixed;
	optional_memory_region m_region_fixedbios;
	optional_memory_bank   m_bank_audio_main; // optional because of neocd
	optional_device<upd4990a_device> m_upd4990a;
	optional_shared_ptr<u16 > m_save_ram;
	required_device<screen_device> m_screen;
	optional_device<palette_device> m_palette;
	optional_device<ng_memcard_device> m_memcard;
	optional_ioport m_dsw;
	optional_ioport m_trackx;
	optional_ioport m_tracky;
	optional_device<neogeo_ctrl_edge_port_device> m_edge;
	optional_device<neogeo_control_port_device> m_ctrl1;
	optional_device<neogeo_control_port_device> m_ctrl2;
	required_device<neosprite_device> m_sprgen;
	optional_device<generic_latch_8_device> m_soundlatch;
	optional_device<generic_latch_8_device> m_soundlatch2;
	optional_device<mslugx_prot_device> m_mslugx_prot;
	optional_device<sma_prot_device> m_sma_prot;
	optional_device<cmc_prot_device> m_cmc_prot;
	optional_device<pcm2_prot_device> m_pcm2_prot;
	optional_device<pvc_prot_device> m_pvc_prot;
	optional_device<ngbootleg_prot_device> m_bootleg_prot;
	optional_device<kof2002_prot_device> m_kof2002_prot;
	optional_device<fatfury2_prot_device> m_fatfury2_prot;
	optional_device<kof98_prot_device> m_kof98_prot;
	optional_device<sbp_prot_device> m_sbp_prot;
	optional_device<kog_prot_device> m_kog_prot;
	output_finder<5> m_out_digit;
	memory_bank_creator m_bios_bank;
	std::unique_ptr<uint16_t[]> m_extra_ram;
};

/********
  HBMAME
 *********/

// This uses 4 audio cpus, with sounds and M1 taken from other games.
// Everything is hooked up as far as I can tell, but there's no extra sounds. No idea which fighters need them.
// The 'result_r' functions are never called, and so 'soundlatch2' never gets read.

class neogeo_kf2k2ps2 : public neogeo_state
{
public:
	neogeo_kf2k2ps2(const machine_config &mconfig, device_type type, const char *tag)
		: neogeo_state(mconfig, type, tag)
		, m2_audiocpu(*this, "audiocpu_m2")
		, m2_ym(*this, "ymsnd_m2")
		, m2_soundlatch(*this, "soundlatch_m2")
		, m2_soundlatch2(*this, "soundlatch2_m2")
		, m2_bank_audio_main(*this, "audio2_main")
		, m3_audiocpu(*this, "audiocpu_m3")
		, m3_ym(*this, "ymsnd_m3")
		, m3_soundlatch(*this, "soundlatch_m3")
		, m3_soundlatch2(*this, "soundlatch2_m3")
		, m3_bank_audio_main(*this, "audio3_main")
		, m4_audiocpu(*this, "audiocpu_m4")
		, m4_ym(*this, "ymsnd_m4")
		, m4_soundlatch(*this, "soundlatch_m4")
		, m4_soundlatch2(*this, "soundlatch2_m4")
		, m4_bank_audio_main(*this, "audio4_main")
	{ }

	void ps2(machine_config &config);

private:
    void ps2_map(address_map &map);

	void audio2_map(address_map &map);
	void audio2_io(address_map &map);
	void audio2_command_w(u8 data);
	u16 audio2_result_r();
	u8 audio2_command_r();
	u8 audio2_bank_select_r(offs_t offset);
	void audio2_check_nmi();
	void audio2_enable_nmi_w(offs_t offset, u8 data);

	void audio3_map(address_map &map);
	void audio3_io(address_map &map);
	void audio3_command_w(u8 data);
	u16 audio3_result_r();
	u8 audio3_command_r();
	u8 audio3_bank_select_r(offs_t offset);
	void audio3_check_nmi();
	void audio3_enable_nmi_w(offs_t offset, u8 data);

	void audio4_map(address_map &map);
	void audio4_io(address_map &map);
	void audio4_command_w(u8 data);
	u16 audio4_result_r();
	u8 audio4_command_r();
	u8 audio4_bank_select_r(offs_t offset);
	void audio4_check_nmi();
	void audio4_enable_nmi_w(offs_t offset, u8 data);

	void machine_start() override;

	required_device<cpu_device> m2_audiocpu;
	required_device<ym2610_device> m2_ym;
	required_device<generic_latch_8_device> m2_soundlatch;
	required_device<generic_latch_8_device> m2_soundlatch2;
	required_memory_bank   m2_bank_audio_main;
	memory_bank           *m2_bank_audio_cart[4]{};
	bool       m2_nmi_enabled = 0;
	bool       m2_nmi_pending = 0;
	required_device<cpu_device> m3_audiocpu;
	required_device<ym2610_device> m3_ym;
	required_device<generic_latch_8_device> m3_soundlatch;
	required_device<generic_latch_8_device> m3_soundlatch2;
	required_memory_bank   m3_bank_audio_main;
	memory_bank           *m3_bank_audio_cart[4]{};
	bool       m3_nmi_enabled = 0;
	bool       m3_nmi_pending = 0;
	required_device<cpu_device> m4_audiocpu;
	required_device<ym2610_device> m4_ym;
	required_device<generic_latch_8_device> m4_soundlatch;
	required_device<generic_latch_8_device> m4_soundlatch2;
	required_memory_bank   m4_bank_audio_main;
	memory_bank           *m4_bank_audio_cart[4]{};
	bool       m4_nmi_enabled = 0;
	bool       m4_nmi_pending = 0;
};

/*----------- defined in drivers/neogeo.c -----------*/

INPUT_PORTS_EXTERN(neogeo);
INPUT_PORTS_EXTERN(jockeygp);
INPUT_PORTS_EXTERN(dualbios);

/*************************************
 *
 *  Neo-Geo bios
 *
 *************************************

    These are the known Bios Roms, Set options.bios to the one you want.

    The Universe bios roms are supported because they're now used on enough PCBs
    to be considered 'in active arcade use' rather than just homebrew hacks.
    Some may be missing, there have been multiple CRCs reported for the same
    revision in some cases (the Universe bios has an option for entering / displaying
    a serial number; these should be noted as such if they're added).
    Universe bios prior to version 1.3 was incompatible with AES.

    The 'japan-hotel' BIOS is a dump of an MVS which could be found in some japanese
    hotels. it is a custom MVS mobo which uses MVS carts but it hasn't jamma
    connector and it's similar to a console with a coin mechanism, so it's a sort
    of little coin op console installed in hotels.

    The sp-45.sp1 bios is the latest 'ASIA' revision. Japan-j3.bin is the latest 'JAPAN'
    revision. Both of them are also used in the sp-4x.sp1 bios of the Jamma PCB boards.

    The current Neo-Geo MVS system set (SFIX/SM1/000-LO) used is from a NEO-MVH MV1FS board.
    Other boards (MV1xx / MV2x / MV4x /MV6x) other system sets?

    Zoom ROM (LO)    128K   TC531000CP      1x 128Kx8   Zoom look-up table ROM
    Fix ROM (SFIX)   128K   27C1000         1x 128Kx8   Text layer graphics ROM
    Sound ROM (SM1)  128K   27C1000/23C1000 1x 128Kx8   Z80 program ROM

*/

#define ROM_LOAD16_WORD_SWAP_BIOS(bios,name,offset,length,hash) \
		ROMX_LOAD(name, offset, length, hash, ROM_GROUPWORD | ROM_REVERSE | ROM_BIOS(bios))

#define NEOGEO_UNIBIOS(x) \
	ROM_SYSTEM_BIOS( x+ 0, "unibios40", "Universe Bios (Hack, Ver. 4.0)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 0, "uni-bios_4_0.rom",  0x00000, 0x020000, CRC(a7aab458) SHA1(938a0bda7d9a357240718c2cec319878d36b8f72) ) /* Universe Bios v4.0 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 1, "unibios33", "Universe Bios (Hack, Ver. 3.3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 1, "uni-bios_3_3.rom",  0x00000, 0x020000, CRC(24858466) SHA1(0ad92efb0c2338426635e0159d1f60b4473d0785) ) /* Universe Bios v3.3 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 2, "unibios32", "Universe Bios (Hack, Ver. 3.2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 2, "uni-bios_3_2.rom",  0x00000, 0x020000, CRC(a4e8b9b3) SHA1(c92f18c3f1edda543d264ecd0ea915240e7c8258) ) /* Universe Bios v3.2 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 3, "unibios31", "Universe Bios (Hack, Ver. 3.1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 3, "uni-bios_3_1.rom",  0x00000, 0x020000, CRC(0c58093f) SHA1(29329a3448c2505e1ff45ffa75e61e9693165153) ) /* Universe Bios v3.1 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 4, "unibios30", "Universe Bios (Hack, Ver. 3.0)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 4, "uni-bios_3_0.rom",  0x00000, 0x020000, CRC(a97c89a9) SHA1(97a5eff3b119062f10e31ad6f04fe4b90d366e7f) ) /* Universe Bios v3.0 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 5, "unibios23", "Universe Bios (Hack, Ver. 2.3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 5, "uni-bios_2_3.rom",  0x00000, 0x020000, CRC(27664eb5) SHA1(5b02900a3ccf3df168bdcfc98458136fd2b92ac0) ) /* Universe Bios v2.3 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 6, "unibios23o", "Universe Bios (Hack, Ver. 2.3, older?)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 6, "uni-bios_2_3o.rom", 0x00000, 0x020000, CRC(601720ae) SHA1(1b8a72c720cdb5ee3f1d735bbcf447b09204b8d9) ) /* Universe Bios v2.3 (hack) alt version, withdrawn? */ \
	ROM_SYSTEM_BIOS( x+ 7, "unibios22", "Universe Bios (Hack, Ver. 2.2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 7, "uni-bios_2_2.rom",  0x00000, 0x020000, CRC(2d50996a) SHA1(5241a4fb0c63b1a23fd1da8efa9c9a9bd3b4279c) ) /* Universe Bios v2.2 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 8, "unibios21", "Universe Bios (Hack, Ver. 2.1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 8, "uni-bios_2_1.rom",  0x00000, 0x020000, CRC(8dabf76b) SHA1(c23732c4491d966cf0373c65c83c7a4e88f0082c) ) /* Universe Bios v2.1 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 9, "unibios20", "Universe Bios (Hack, Ver. 2.0)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 9, "uni-bios_2_0.rom",  0x00000, 0x020000, CRC(0c12c2ad) SHA1(37bcd4d30f3892078b46841d895a6eff16dc921e) ) /* Universe Bios v2.0 (hack) */ \
	ROM_SYSTEM_BIOS( x+10, "unibios13", "Universe Bios (Hack, Ver. 1.3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+10, "uni-bios_1_3.rom",  0x00000, 0x020000, CRC(b24b44a0) SHA1(eca8851d30557b97c309a0d9f4a9d20e5b14af4e) ) /* Universe Bios v1.3 (hack) */
#define NEOGEO_UNIBIOS_1_2_AND_OLDER(x) \
	ROM_SYSTEM_BIOS( x+11, "unibios12", "Universe Bios (Hack, Ver. 1.2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+11, "uni-bios_1_2.rom",  0x00000, 0x020000, CRC(4fa698e9) SHA1(682e13ec1c42beaa2d04473967840c88fd52c75a) ) /* Universe Bios v1.2 (hack) */ \
	ROM_SYSTEM_BIOS( x+12, "unibios12o", "Universe Bios (Hack, Ver. 1.2, older)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+12, "uni-bios_1_2o.rom", 0x00000, 0x020000, CRC(e19d3ce9) SHA1(af88ef837f44a3af2d7144bb46a37c8512b67770) ) /* Universe Bios v1.2 (hack) alt version */ \
	ROM_SYSTEM_BIOS( x+13, "unibios11", "Universe Bios (Hack, Ver. 1.1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+13, "uni-bios_1_1.rom",  0x00000, 0x020000, CRC(5dda0d84) SHA1(4153d533c02926a2577e49c32657214781ff29b7) ) /* Universe Bios v1.1 (hack) */ \
	ROM_SYSTEM_BIOS( x+14, "unibios10", "Universe Bios (Hack, Ver. 1.0)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+14, "uni-bios_1_0.rom",  0x00000, 0x020000, CRC(0ce453a0) SHA1(3b4c0cd26c176fc6b26c3a2f95143dd478f6abf9) ) /* Universe Bios v1.0 (hack) */
#define NEOGEO_UNIBIOS_THE_REGION_IS_CHANGED(x) \
	ROM_SYSTEM_BIOS( x+15, "bios_defecto", "Universe Bios 4.0 (Defecto)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+15, "uni-bios_defecto.rom",  0x00000, 0x020000, CRC(6327bb3b) SHA1(70ffe05ca37fb55871aca5ec449006e708c41141) ) /* Universe Bios v4.0 Defecto (hack) */ \
	ROM_SYSTEM_BIOS( x+16, "mslug_forever", "Universe Bios 4.0 (Metal Slug Forever)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+16, "metalslug_forever.rom",  0x00000, 0x020000, CRC(a17e6518) SHA1(5a6ba89bdf577599612cffaedce7feac76349331) ) /* Universe Bios v4.0 Metal Slug Forever (hack) */ \
	ROM_SYSTEM_BIOS( x+17, "console_mode", "Universe Bios 4.0 (Ver.Regions: Europe Mode: Console)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+17, "console_mode.rom",  0x00000, 0x020000, CRC(6d649877) SHA1(3339e1e10c9b20af3df5e1b29bf7198be651661a) ) /* Universe Bios v4.0 Regions: Europe Mode: Console "Disabled Command Region Selection Menu, Start+A+B+C, Start+Select And Start+Coin" (hack) */

#define NEOGEO_BIOS \
	ROM_REGION16_BE( 0x80000, "mainbios", 0 ) \
	ROMX_LOAD( "sp-s2.sp1", 0x00000, 0x020000, CRC(9036d879) SHA1(4f5ed7105b7128794654ce82b51723e16e389543), ROM_GROUPWORD | ROM_REVERSE ) \
	ROM_SYSTEM_BIOS( 0, "euro", "Europe MVS (Ver. 2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 0, "sp-s2.sp1",         0x00000, 0x020000, CRC(9036d879) SHA1(4f5ed7105b7128794654ce82b51723e16e389543) ) /* 5 Dark Blue - Europe, 1 Slot, has also been found on 2 Slot and 4 Slot (the old hacks were designed for this one) */ \
	ROM_SYSTEM_BIOS( 1, "euro-s1", "Europe MVS (Ver. 1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 1, "sp-s.sp1",          0x00000, 0x020000, CRC(c7f2fa45) SHA1(09576ff20b4d6b365e78e6a5698ea450262697cd) ) /* 3 Dark Blue - Europe, 4 Slot */ \
	ROM_SYSTEM_BIOS( 2, "asia-mv1c", "Asia NEO-MVH MV1C" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 2, "sp-45.sp1",         0x00000, 0x080000, CRC(03cc9f6a) SHA1(cdf1f49e3ff2bac528c21ed28449cf35b7957dc1) ) /* 6 Dark Blue - Latest Asia bios (MV1C - mask ROM) */ \
	ROM_SYSTEM_BIOS( 3, "asia-mv1b", "Asia MV1B" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 3, "sp-s3.sp1",         0x00000, 0x020000, CRC(91b64be3) SHA1(720a3e20d26818632aedf2c2fd16c54f213543e1) ) /* 6 Dark Blue - Asia (MV1B) */ \
	\
	ROM_SYSTEM_BIOS( 4, "us", "US MVS (Ver. 2?)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 4, "sp-u2.sp1",         0x00000, 0x020000, CRC(e72943de) SHA1(5c6bba07d2ec8ac95776aa3511109f5e1e2e92eb) ) /* 5 Cyan - US, 2 Slot */ \
	ROM_SYSTEM_BIOS( 5, "us-e", "US MVS (Ver. 1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 5, "sp-e.sp1",          0x00000, 0x020000, CRC(2723a5b5) SHA1(5dbff7531cf04886cde3ef022fb5ca687573dcb8) ) /* 5 Yellow - US, 6 Slot (V5?) */ \
	ROM_SYSTEM_BIOS( 6, "us-v2", "US MVS (4 slot, Ver 2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 6, "sp1-u2",            0x00000, 0x020000, CRC(62f021f4) SHA1(62d372269e1b3161c64ae21123655a0a22ffd1bb) ) /* 3 Cyan - US, 4 slot - also seen with "v2" label*/ \
	ROM_SYSTEM_BIOS( 7, "us-u4", "US MVS (U4)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 7, "sp1-u4.bin",        0x00000, 0x020000, CRC(1179a30f) SHA1(866817f47aa84d903d0b819d61f6ef356893d16a) ) /* 3 Green - 4 Slot (MV-4F) */ \
	ROM_SYSTEM_BIOS( 8, "us-u3", "US MVS (U3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 8, "sp1-u3.bin",        0x00000, 0x020000, CRC(2025b7a2) SHA1(73d774746196f377111cd7aa051cc8bb5dd948b3) ) /* 2 Green - 6 Slot */ \
	\
	ROM_SYSTEM_BIOS( 9, "japan", "Japan MVS (Ver. 3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 9, "vs-bios.rom",       0x00000, 0x020000, CRC(f0e8f27d) SHA1(ecf01eda815909f1facec62abf3594eaa8d11075) ) /* 6 Red - Japan, Ver 6 VS Bios */ \
	ROM_SYSTEM_BIOS( 10, "japan-s2", "Japan MVS (Ver. 2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 10, "sp-j2.sp1",        0x00000, 0x020000, CRC(acede59c) SHA1(b6f97acd282fd7e94d9426078a90f059b5e9dd91) ) /* 5 Red - Japan, Older */ \
	ROM_SYSTEM_BIOS( 11, "japan-s1", "Japan MVS (Ver. 1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 11, "sp1.jipan.1024",   0x00000, 0x020000, CRC(9fb0abe4) SHA1(18a987ce2229df79a8cf6a84f968f0e42ce4e59d) ) /* 3 Red - Japan, Older */ \
	ROM_SYSTEM_BIOS( 12, "japan-mv1b", "Japan MV1B" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 12, "japan-j3.bin",     0x00000, 0x020000, CRC(dff6d41f) SHA1(e92910e20092577a4523a6b39d578a71d4de7085) ) /* 6 Red - Latest Japan bios (MV1B) */ \
	ROM_SYSTEM_BIOS( 13, "japan-j3a", "Japan MVS (J3, alt)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 13, "sp1-j3.bin",       0x00000, 0x020000, CRC(fbc6d469) SHA1(46b2b409b5b68869e367b40c846373623edb632a) ) /* 2 Red - 6 Slot */ \
	ROM_SYSTEM_BIOS( 14, "japan-mv1c", "Japan NEO-MVH MV1C" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 14, "sp-j3.sp1",        0x00000, 0x080000, CRC(486cb450) SHA1(52c21ea817928904b80745a8c8d15cbad61e1dc1) ) /* 6 Red - Latest Japan bios (MV1C - mask ROM) */ \
	\
	ROM_SYSTEM_BIOS( 15, "japan-hotel", "Custom Japanese Hotel" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 15, "sp-1v1_3db8c.bin", 0x00000, 0x020000, CRC(162f0ebe) SHA1(fe1c6dd3dfcf97d960065b1bb46c1e11cb7bf271) ) /* 6 Red - 'rare MVS found in japanese hotels' shows v1.3 in test mode */ \
	\
	NEOGEO_UNIBIOS(16) \
	NEOGEO_UNIBIOS_1_2_AND_OLDER(16) \
	NEOGEO_UNIBIOS_THE_REGION_IS_CHANGED(16) \
	ROM_DEFAULT_BIOS("euro")

#define NEO_BIOS_AUDIO(size, name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_BIOS_AUDIO_32K(name, hash) \
	NEO_BIOS_AUDIO(0x8000, name, hash)

#define NEO_BIOS_AUDIO_64K(name, hash) \
	NEO_BIOS_AUDIO(0x10000, name, hash)

#define NEO_BIOS_AUDIO_128K(name, hash) \
    NEO_BIOS_AUDIO(0x20000, name, hash)

#define NEO_BIOS_AUDIO_256K(name, hash) \
	NEO_BIOS_AUDIO(0x40000, name, hash)

#define NEO_BIOS_AUDIO_512K(name, hash) \
	NEO_BIOS_AUDIO(0x80000, name, hash)

#define NEO_JAPAN_BIOS_AUDIO(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("vs-bios.rom",  0x00000, 0x20000, CRC(f0e8f27d) SHA1(ecf01eda815909f1facec62abf3594eaa8d11075) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION(size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_BIOS_AUDIO_ENCRYPTED(size, name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash )

#define NEO_BIOS_AUDIO_ENCRYPTED_64K(name, hash) \
	NEO_BIOS_AUDIO_ENCRYPTED(0x10000, name, hash)

#define NEO_BIOS_AUDIO_ENCRYPTED_128K(name, hash) \
	NEO_BIOS_AUDIO_ENCRYPTED(0x20000, name, hash)

#define NEO_BIOS_AUDIO_ENCRYPTED_256K(name, hash) \
	NEO_BIOS_AUDIO_ENCRYPTED(0x40000, name, hash)

#define NEO_BIOS_AUDIO_ENCRYPTED_512K(name, hash) \
	NEO_BIOS_AUDIO_ENCRYPTED(0x80000, name, hash)

#define ROM_Y_ZOOM \
	ROM_REGION( 0x20000, "zoomy", 0 ) \
	ROM_LOAD( "000-lo.lo", 0x00000, 0x20000, CRC(5a86cff2) SHA1(5992277debadeb64d1c1c64b0a92d9293eaf7e4a) )

#define NEO_SFIX_MT(size) \
	ROM_Y_ZOOM \
	ROM_REGION( 0x20000, "fixedbios", 0 ) \
	ROM_LOAD( "sfix.sfix",  0, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) ) \
	ROM_REGION( size, "fixed", ROMREGION_ERASE00 )

#define NEO_SFIX_MT_64K \
	NEO_SFIX_MT( 0x10000 )

#define NEO_SFIX_MT_128K \
	NEO_SFIX_MT( 0x20000 )

#define NEO_SFIX_MT_256K \
	NEO_SFIX_MT( 0x40000 )

#define NEO_SFIX_MT_512K \
	NEO_SFIX_MT( 0x80000 )

#define NEO_SFIX(bytes, name, hash) \
	NEO_SFIX_MT( bytes ) \
	ROM_LOAD( name, 0x00000, bytes, hash )

#define NEO_SFIX_64K(name, hash) \
	NEO_SFIX( 0x10000, name, hash )

#define NEO_SFIX_128K(name, hash) \
	NEO_SFIX( 0x20000, name, hash )

#define NEO_SFIX_256K(name, hash) \
	NEO_SFIX( 0x40000, name, hash )

#define NEO_SFIX_512K(name, hash) \
	NEO_SFIX( 0x80000, name, hash )

#define NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(size, name, hash) \
	ROM_REGION16_BE( 0x80000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-3.sp1",  0x00000, 0x80000, CRC(b4590283) SHA1(47047ed5b6062babc0a0bebcc30e4b3f021e115a) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash )

#define NEO_JAPAN_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_64K(name, hash) \
	NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(0x10000, name, hash)

#define NEO_JAPAN_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_128K(name, hash) \
	NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(0x20000, name, hash)

#define NEO_JAPAN_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_256K(name, hash) \
	NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(0x40000, name, hash)

#define NEO_JAPAN_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_512K(name, hash) \
	NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(0x80000, name, hash)

#define NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-s2.sp1",  0x00000, 0x20000, CRC(9b1a7cbe) SHA1(1695d3c488961a0f3667bd9b94ff678fd7c56d76) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash )

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_64K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(0x10000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_128K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(0x20000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_256K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(0x40000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_512K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(0x80000, name, hash)

#define NEO_EUROPE_MVS_BIOS_AUDIO(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-s4.sp1",  0x00000, 0x20000, CRC(9b1a7cbe) SHA1(1695d3c488961a0f3667bd9b94ff678fd7c56d76) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_64K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO(0x10000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_128K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO(0x20000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_256K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO(0x40000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_512K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO(0x80000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-1.sp1",  0x00000, 0x20000, CRC(98f34e99) SHA1(ff63c492d11d0f26533d6e73d331e15152e62cc7) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO_64K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(0x10000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO_128K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(0x20000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO_256K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(0x40000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO_512K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(0x80000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-1.sp2",  0x00000, 0x20000, CRC(0161e81d) SHA1(2cd9e13f85070651a6ca6a3727fc6312efffd3cf) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO_64K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(0x10000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO_128K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(0x20000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO_256K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(0x40000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO_512K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(0x80000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-1.sp1",  0x00000, 0x20000, CRC(98f34e99) SHA1(ff63c492d11d0f26533d6e73d331e15152e62cc7) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash )

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED_64K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(0x10000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED_128K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(0x20000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED_256K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(0x40000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED_512K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(0x80000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-1.sp1",  0x00000, 0x20000, CRC(98f34e99) SHA1(ff63c492d11d0f26533d6e73d331e15152e62cc7) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_64K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(0x10000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_128K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(0x20000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_256K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(0x40000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_512K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(0x80000, name, hash)

/***********************************************
   Specific Code For The Soft Dip Modification
 ************************************************/

#define TWOTHOUSANDTWENTYBB_MVS_FILL \
    ROM_FILL(0X0464,1,0X05)\
    ROM_FILL(0X0466,1,0X05)

#define THREECOUNTB_MVS_FILL \
    ROM_FILL(0X0B04,1,0X9F)\
    ROM_FILL(0X0B05,1,0X9F)\
    ROM_FILL(0X0B06,1,0X6F)\
    ROM_FILL(0X0B08,1,0X58)\
    ROM_FILL(0X0B0D,1,0X12)

#define ALPHAM2_MVS_FILL \
    ROM_FILL(0X7F95C,1,0X63)\
    ROM_FILL(0X7F95E,1,0X5F)\
    ROM_FILL(0X7F960,1,0X78)\
    ROM_FILL(0X7F965,1,0X56)

#define ALPHAM2P_MVS_FILL \
    ROM_FILL(0X019A,1,0X63)\
    ROM_FILL(0X019C,1,0X58)\
    ROM_FILL(0X019E,1,0X34)\
    ROM_FILL(0X01A1,1,0X56)

#define ANDRODUN_MVS_FILL \
    ROM_FILL(0X0330,1,0X63)\
    ROM_FILL(0X0332,1,0X24)\
    ROM_FILL(0X0335,1,0X34)

#define AODK_MVS_FILL \
    ROM_FILL(0X99AC,1,0X05)\
    ROM_FILL(0X99B4,1,0X58)\
    ROM_FILL(0X99B8,1,0X12)

#define AOF_MVS_FILL \
    ROM_FILL(0X04FE,1,0X63)\
    ROM_FILL(0X0500,1,0X23)\
	ROM_FILL(0X0503,1,0X58)

#define AOFBR_MVS_FILL \
    ROM_FILL(0X04FE,1,0X63)\
	ROM_FILL(0X0503,1,0X58)

#define AOFKR_MVS_FILL \
    ROM_FILL(0X01A6,1,0X63)\
	ROM_FILL(0X01AB,1,0X58)

#define AOF2_MVS_FILL \
    ROM_FILL(0XF750E,1,0X63)\
    ROM_FILL(0XF7510,1,0X23)\
    ROM_FILL(0XF7513,1,0X58)

#define AOF3_MVS_FILL \
    ROM_FILL(0X552,1,0X63)\
    ROM_FILL(0X554,1,0X13)\
    ROM_FILL(0X557,1,0X58)

#define AOF3K_MVS_FILL \
    ROM_FILL(0X01A6,1,0X63)\
    ROM_FILL(0X01A8,1,0X13)\
    ROM_FILL(0X01AB,1,0X58)

#define B2B_MVS_FILL \
    ROM_FILL(0X04A3,1,0X58)\

#define BAKATONO_MVS_FILL \
    ROM_FILL(0X0217,1,0X58)\

#define BANGBEAD_MVS_FILL \
    ROM_FILL(0X05A4,1,0X58)\
    ROM_FILL(0X05A7,1,0X12)\
	ROM_FILL(0X05AA,1,0X02)\
	ROM_FILL(0X05AB,1,0X12)

#define BJOURNEY_MVS_FILL \
    ROM_FILL(0X09693,1,0X64)\
    ROM_FILL(0X09696,1,0X58)\
    ROM_FILL(0X09698,1,0X78)\
	ROM_FILL(0X09699,1,0X78)

#define BLAZSTAR_MVS_FILL \
    ROM_FILL(0X0216,1,0X34)\
    ROM_FILL(0X021A,1,0X58)\
	ROM_FILL(0X021C,1,0X02)

#define BREAKERS_MVS_FILL \
    ROM_FILL(0X045F,1,0X58)\
    ROM_FILL(0X0460,1,0X15)\
	ROM_FILL(0X0461,1,0X55)

#define BREAKREV_MVS_FILL \
    ROM_FILL(0X045F,1,0X58)\
    ROM_FILL(0X0460,1,0X15)\
	ROM_FILL(0X0461,1,0X55)\
	ROM_FILL(0X0466,1,0X14)

#define BSTARS_MVS_FILL \
    ROM_FILL(0X1BF82,1,0X05)\
    ROM_FILL(0X1BF88,1,0X89)\
	ROM_FILL(0X1BF89,1,0X89)

#define BSTARS2_MVS_FILL \
    ROM_FILL(0X0554,1,0X05)\
    ROM_FILL(0X0556,1,0X05)\
	ROM_FILL(0X055A,1,0X9F)

#define BURNINGF_MVS_FILL \
    ROM_FILL(0X0416,1,0X63)\
    ROM_FILL(0X0419,1,0X34)\
	ROM_FILL(0X041A,1,0X24)

#define BURNINGFP_MVS_FILL \
    ROM_FILL(0X0416,1,0X63)\
    ROM_FILL(0X0418,1,0X34)\
	ROM_FILL(0X0419,1,0X24)

#define CRSWORD_MVS_FILL \
    ROM_FILL(0XB0C0,1,0X58)\

#define CRSWD2BL_MVS_FILL \
    ROM_FILL(0X95FE,1,0X58)\

#define CTOMADAY_MVS_FILL \
    ROM_FILL(0X0F32,1,0X58)\
    ROM_FILL(0X0F35,1,0X12)

#define CYBERLIP_MVS_FILL \
    ROM_FILL(0X0600,1,0X63)\
	ROM_FILL(0X0604,1,0X58)\
    ROM_FILL(0X0606,1,0XEF)

#define DIGGERMA_MVS_FILL \
    ROM_FILL(0X0216,1,0X58)\
    ROM_FILL(0X021B,1,0X02)

#define DOUBLEDR_MVS_FILL \
    ROM_FILL(0X3201,1,0X58)\
    ROM_FILL(0X3202,1,0X58)

#define EIGHTMAN_MVS_FILL \
    ROM_FILL(0X0346,1,0X63)\
	ROM_FILL(0X034A,1,0X58)\
    ROM_FILL(0X034D,1,0X78)

#define FATFURSP_MVS_FILL \
    ROM_FILL(0X04AC,1,0X63)\
	ROM_FILL(0X04B1,1,0X58)\
	ROM_FILL(0X04B6,1,0X12)

#define FATFURY1_MVS_FILL \
    ROM_FILL(0X02ED,1,0X58)\
	ROM_FILL(0X02EF,1,0X03)

#define FATFURY2_MVS_FILL \
    ROM_FILL(0X04F9,1,0X58)\
	ROM_FILL(0X04FB,1,0X03)\
	ROM_FILL(0X04FF,1,0X12)

#define FATFURY3_MVS_FILL \
	ROM_FILL(0X04F4,1,0X63)\
    ROM_FILL(0X04F9,1,0X58)\
	ROM_FILL(0X04FF,1,0X23)

#define FBFRENZY_MVS_FILL \
	ROM_FILL(0X02B2,1,0X05)\
    ROM_FILL(0X02B4,1,0X05)\
	ROM_FILL(0X02B9,1,0X24)\
    ROM_FILL(0X02BB,1,0X33)\
	ROM_FILL(0X02BC,1,0X33)

#define FIGHTFEV_MVS_FILL \
	ROM_FILL(0X0360,1,0X33)\
	ROM_FILL(0X0364,1,0X58)

#define FLIPSHOT_MVS_FILL \
	ROM_FILL(0X059C,1,0X58)\
    ROM_FILL(0X059F,1,0X12)

#define FLIPSHOTKR_MVS_FILL \
	ROM_FILL(0X02D4,1,0X58)\
    ROM_FILL(0X02DA,1,0X12)

#define FROMAN2B_MVS_FILL \
	ROM_FILL(0X08A6,1,0X07)\
    ROM_FILL(0X08AD,1,0X24)\
	ROM_FILL(0X08B5,1,0X12)

#define FSWORDS_MVS_FILL \
	ROM_FILL(0X7436F,1,0X58)\
	ROM_FILL(0X74372,1,0X12)

#define GALAXYFG_MVS_FILL \
	ROM_FILL(0X04B8,1,0X63)\
    ROM_FILL(0X04BB,1,0X58)\
	ROM_FILL(0X04C0,1,0X12)

#define GANRYU_MVS_FILL \
	ROM_FILL(0X04E4,1,0X58)\
    ROM_FILL(0X04E7,1,0X12)\
	ROM_FILL(0X04EA,1,0X02)\
	ROM_FILL(0X04EB,1,0X12)

#define GAROU_MVS_FILL \
	ROM_FILL(0X05FC,1,0X63)\
	ROM_FILL(0X05FE,1,0X02)\
	ROM_FILL(0X0601,1,0X58)\
	ROM_FILL(0X0603,1,0X02)\
	ROM_FILL(0X0604,1,0X12)\
	ROM_FILL(0X0605,1,0X89)\
	ROM_FILL(0X0607,1,0X12)

//BOTH GAROUBL VERSIONS WORK.
#define GAROU_AES_FILL \
	ROM_FILL(0XCB60,1,0X4E)\
	ROM_FILL(0XCB61,1,0X71)\
	ROM_FILL(0XCB62,1,0X4E)\
	ROM_FILL(0XCB63,1,0X71)

#define GAROUDD_MVS_FILL \
	ROM_FILL(0X05FC,1,0X63)\
	ROM_FILL(0X05FE,1,0X02)\
	ROM_FILL(0X0601,1,0X58)\
	ROM_FILL(0X0603,1,0X02)\
	ROM_FILL(0X0604,1,0X02)\
	ROM_FILL(0X0605,1,0X89)\
	ROM_FILL(0X0607,1,0X12)

//BOTH GAROUHDD, GAROUHADD VERSIONS WORK.
#define GAROUDD_AES_FILL \
	ROM_FILL(0XCBD2,1,0X4E)\
	ROM_FILL(0XCBD3,1,0X71)\
	ROM_FILL(0XCBD4,1,0X4E)\
	ROM_FILL(0XCBD5,1,0X71)

#define GHOSTLOP_MVS_FILL \
	ROM_FILL(0XD139,1,0X99)\
    ROM_FILL(0XD13B,1,0X58)

#define GOALX3_MVS_FILL \
    ROM_FILL(0X04D6,1,0X7C)\
	ROM_FILL(0X04D7,1,0X7C)\
    ROM_FILL(0X04DB,1,0X58)

#define GOWCAIZR_MVS_FILL \
    ROM_FILL(0X05D8,1,0X55)\
	ROM_FILL(0X05DA,1,0X58)

#define GPILOTS_MVS_FILL \
    ROM_FILL(0X0214,1,0X63)\
	ROM_FILL(0X0216,1,0X58)\
    ROM_FILL(0X0218,1,0X34)

#define GPILOTSH_MVS_FILL \
    ROM_FILL(0X0214,1,0X63)\
	ROM_FILL(0X0216,1,0X58)\
    ROM_FILL(0X0218,1,0X34)\
    ROM_FILL(0X021B,1,0X02)

#define GURURIN_MVS_FILL \
    ROM_FILL(0X0216,1,0X58)\
	ROM_FILL(0X021B,1,0X02)

#define IRONCLAD_MVS_FILL \
    ROM_FILL(0X05E8,1,0X34)\
	ROM_FILL(0X05EA,1,0x23)\
	ROM_FILL(0X05EB,1,0X58)

#define JANSHIN_MVS_FILL \
    ROM_FILL(0X0216,1,0X58)

#define JOYJOY_MVS_FILL \
    ROM_FILL(0X027E,1,0X58)

#define KABUKIKL_MVS_FILL \
    ROM_FILL(0X059D,1,0X58)\
	ROM_FILL(0X059F,1,0X03)\
    ROM_FILL(0X05A3,1,0X12)

#define KARNOVR_MVS_FILL \
    ROM_FILL(0X04F7,1,0X58)\
	ROM_FILL(0X04FB,1,0X03)

#define KIZUNA_MVS_FILL \
    ROM_FILL(0X4A39E,1,0X35)\
	ROM_FILL(0X4A39F,1,0X58)\
    ROM_FILL(0X4A3A6,1,0X13)

#define KF2K3UPL_MVS_FILL \
    ROM_FILL(0X760416,1,0X15)\
	ROM_FILL(0X760419,1,0X58)\
    ROM_FILL(0X76041C,1,0X04)\
    ROM_FILL(0X76041D,1,0X14)\
    ROM_FILL(0X76041E,1,0X12)\
    ROM_FILL(0X76041F,1,0X02)

#define KOF94_MVS_FILL \
    ROM_FILL(0X4F3E6,1,0X05)\
	ROM_FILL(0X4F3EA,1,0X58)\
    ROM_FILL(0X4F3EF,1,0X12)\

#define KOF94KR_MVS_FILL \
    ROM_FILL(0X4F016,1,0X05)\
	ROM_FILL(0X4F01A,1,0X58)

#define KOF94_AES_FILL \
	ROM_FILL(0X32461,1,0X99)\
	ROM_FILL(0X32467,1,0X99)

#define KOF95_MVS_FILL \
    ROM_FILL(0X576E6,1,0X05)\
	ROM_FILL(0X576EA,1,0X58)\
    ROM_FILL(0X576EF,1,0X13)

#define KOF95KR_MVS_FILL \
    ROM_FILL(0X57316,1,0X05)\
	ROM_FILL(0X5731A,1,0X58)

#define KOF95_AES_FILL \
	ROM_FILL(0X38C59,1,0X99)\
	ROM_FILL(0X38C5F,1,0X99)

#define KOF95H_AES_FILL \
	ROM_FILL(0X38EFD,1,0X99)\
	ROM_FILL(0X38F03,1,0X99)

#define KOF96_MVS_FILL \
    ROM_FILL(0X6C356,1,0X05)\
	ROM_FILL(0X6C35A,1,0X58)\
    ROM_FILL(0X6C35E,1,0X13)\

#define KOF96KR_MVS_FILL \
    ROM_FILL(0X6C016,1,0X05)\
	ROM_FILL(0X6C01A,1,0X58)

#define KOF96_AES_FILL \
	ROM_FILL(0X8C5F,1,0X99)\
	ROM_FILL(0X8C65,1,0X99)

#define KOF97_MVS_FILL \
    ROM_FILL(0XA0DE6,1,0X05)\
	ROM_FILL(0XA0DEA,1,0X58)\
    ROM_FILL(0XA0DEB,1,0X34)\
    ROM_FILL(0XA0DEF,1,0X13)

#define KOF97KR_MVS_FILL \
    ROM_FILL(0XA0A16,1,0X05)\
	ROM_FILL(0XA0A1A,1,0X58)\
    ROM_FILL(0XA0A1B,1,0X34)

#define KOF97_AES_FILL \
	ROM_FILL(0X98D9,1,0X99)\
	ROM_FILL(0X98DF,1,0X99)

#define KOF98_MVS_FILL \
    ROM_FILL(0XA8E76,1,0X05)\
	ROM_FILL(0XA8E7A,1,0X58)\
    ROM_FILL(0XA8E7B,1,0X34)\
    ROM_FILL(0XA8E7E,1,0X14)\
    ROM_FILL(0XA8E7F,1,0X13)

#define KOF98KR_MVS_FILL \
    ROM_FILL(0XA8A16,1,0X05)\
	ROM_FILL(0XA8A1A,1,0X58)\
    ROM_FILL(0XA8A1B,1,0X34)\
    ROM_FILL(0XA8A1E,1,0X14)

#define KOF98_AES_FILL \
	ROM_FILL(0X9C93,1,0X99)\
	ROM_FILL(0X9C99,1,0X99)

#define KOF99_MVS_FILL \
    ROM_FILL(0XB0E16,1,0X05)\
	ROM_FILL(0XB0E19,1,0X58)\
    ROM_FILL(0XB0E1A,1,0X34)\
    ROM_FILL(0XB0E1D,1,0X14)\
    ROM_FILL(0XB0E1E,1,0X13)\
    ROM_FILL(0XB0E1F,1,0X12)

#define KOF99KR_MVS_FILL \
    ROM_FILL(0XB0A16,1,0X05)\
	ROM_FILL(0XB0A19,1,0X58)\
    ROM_FILL(0XB0A1A,1,0X34)\
    ROM_FILL(0XB0A1D,1,0X14)

#define KOF99_AES_FILL \
	ROM_FILL(0X853B,1,0X99)\
	ROM_FILL(0X8541,1,0X99)

#define KOF2000_MVS_FILL \
    ROM_FILL(0XC0E16,1,0X05)\
	ROM_FILL(0XC0E19,1,0X58)\
    ROM_FILL(0XC0E1A,1,0X34)\
    ROM_FILL(0XC0E1D,1,0X14)\
    ROM_FILL(0XC0E1E,1,0X13)\
    ROM_FILL(0XC0E1F,1,0X12)

#define KOF2000KR_MVS_FILL \
    ROM_FILL(0XC0A16,1,0X05)\
	ROM_FILL(0XC0A19,1,0X58)\
    ROM_FILL(0XC0A1A,1,0X34)\
    ROM_FILL(0XC0A1D,1,0X14)

#define KOF2000_AES_FILL \
	ROM_FILL(0X9283,1,0X99)\
	ROM_FILL(0X9289,1,0X99)

#define KOF2001_MVS_FILL \
    ROM_FILL(0XB0E16,1,0X05)\
	ROM_FILL(0XB0E19,1,0X58)\
    ROM_FILL(0XB0E1A,1,0X34)\
    ROM_FILL(0XB0E1D,1,0X14)\
    ROM_FILL(0XB0E1E,1,0X14)\
    ROM_FILL(0XB0E1F,1,0X12)

#define KOF2001_AES_FILL \
	ROM_FILL(0X91D7,1,0X99)\
	ROM_FILL(0X91DD,1,0X99)

#define KOF2001H_AES_FILL \
	ROM_FILL(0X91E9,1,0X99)\
	ROM_FILL(0X91EF,1,0X99)

#define KOF2002_MVS_FILL \
    ROM_FILL(0XB0E46,1,0X05)\
    ROM_FILL(0XB0E49,1,0X58)\
    ROM_FILL(0XB0E4A,1,0X34)\
	ROM_FILL(0XB0E4D,1,0X14)\
    ROM_FILL(0XB0E4E,1,0X13)\
    ROM_FILL(0XB0E4F,1,0X12)

#define KOF2002_AES_FILL \
	ROM_FILL(0X8F1F,1,0X99)\
	ROM_FILL(0X8F25,1,0X99)

#define KOF2003_MVS_FILL \
    ROM_FILL(0X60416,1,0X05)\
	ROM_FILL(0X60419,1,0X58)\
    ROM_FILL(0X6041C,1,0X04)\
    ROM_FILL(0X6041D,1,0X14)\
    ROM_FILL(0X6041E,1,0X12)\
    ROM_FILL(0X6041F,1,0X02)

#define KOF2003_AES_FILL \
	ROM_FILL(0X1D79,1,0X99)\
	ROM_FILL(0X1D7F,1,0X99)

#define KOTM_MVS_FILL \
    ROM_FILL(0X025E,1,0X09)\
	ROM_FILL(0X0265,1,0X58)

#define KOTMH_MVS_FILL \
    ROM_FILL(0X0282,1,0X09)\
	ROM_FILL(0X0289,1,0X58)

#define KOTM2_MVS_FILL \
    ROM_FILL(0X4036E,1,0X9A)\
	ROM_FILL(0X40370,1,0X58)\
	ROM_FILL(0X40375,1,0X12)

//BOTH SHOCKTR2 VERSIONS WORK.
#define LANS2004_MVS_FILL \
    ROM_FILL(0X05BB,1,0X58)\
	ROM_FILL(0X05BC,1,0X45)\
	ROM_FILL(0X05BD,1,0X34)\
	ROM_FILL(0X05BE,1,0X12)\
    ROM_FILL(0X05BF,1,0X23)

#define LASTBLAD_MVS_FILL \
    ROM_FILL(0X05F2,1,0X23)\
	ROM_FILL(0X05F3,1,0X58)\
	ROM_FILL(0X05F6,1,0X02)\
    ROM_FILL(0X05FA,1,0X04)\
	ROM_FILL(0X05FB,1,0X13)

#define LASTSOLD_MVS_FILL \
    ROM_FILL(0X01AA,1,0X23)\
	ROM_FILL(0X01AB,1,0X58)\
	ROM_FILL(0X01AE,1,0X02)\
    ROM_FILL(0X01B2,1,0X04)

#define LASTBLD2_MVS_FILL \
    ROM_FILL(0X05F2,1,0X23)\
	ROM_FILL(0X05F3,1,0X58)\
	ROM_FILL(0X05F6,1,0X12)\
    ROM_FILL(0X05F9,1,0X02)\
    ROM_FILL(0X05FA,1,0X04)\
	ROM_FILL(0X05FB,1,0X13)

#define LBOWLING_MVS_FILL \
    ROM_FILL(0X0451,1,0X58)\
	ROM_FILL(0X0453,1,0X78)\
	ROM_FILL(0X0454,1,0XEF)\
	ROM_FILL(0X0455,1,0X78)\
    ROM_FILL(0X0456,1,0X02)

#define LEGENDOS_MVS_FILL \
    ROM_FILL(0XF640,1,0X58)\
	ROM_FILL(0XF644,1,0X02)

#define LRESORT_MVS_FILL \
    ROM_FILL(0X019C,1,0X63)\
	ROM_FILL(0X019F,1,0X34)\
	ROM_FILL(0X01A0,1,0X68)

#define MAGDROP2_MVS_FILL \
    ROM_FILL(0X0623,1,0X58)\
	ROM_FILL(0X0628,1,0X34)\
	ROM_FILL(0X0629,1,0X34)

#define MAGDROP3_MVS_FILL \
    ROM_FILL(0X0623,1,0X58)\
	ROM_FILL(0X0628,1,0X34)\
	ROM_FILL(0X0629,1,0X34)

#define MAGLORD_MVS_FILL \
    ROM_FILL(0X70AE,1,0X58)\
	ROM_FILL(0X70B0,1,0X78)\
	ROM_FILL(0X70B1,1,0X78)\
	ROM_FILL(0X70B2,1,0X23)\
	ROM_FILL(0X70B3,1,0X12)

#define MAHRETSU_MVS_FILL \
    ROM_FILL(0X0196,1,0X05)\
	ROM_FILL(0X0198,1,0X05)\
	ROM_FILL(0X019E,1,0X58)

#define MARUKODQ_MVS_FILL \
    ROM_FILL(0X0216,1,0X58)\

#define MATRIM_MVS_FILL \
    ROM_FILL(0X09BE,1,0X58)\
	ROM_FILL(0X09C1,1,0X34)\
	ROM_FILL(0X09C2,1,0X15)\
	ROM_FILL(0X09C4,1,0X02)\
    ROM_FILL(0X09C6,1,0X12)

#define MIEXCHNG_MVS_FILL \
    ROM_FILL(0X064F,1,0X58)\
	ROM_FILL(0X0654,1,0X13)\
	ROM_FILL(0X0655,1,0X02)\
	ROM_FILL(0X0657,1,0X14)

#define MSLUG_FLASHOFF_MODS_FILL \
    ROM_FILL(0x13830,1,0x4E)\
	ROM_FILL(0x13831,1,0x71)\
	ROM_FILL(0x13832,1,0x4E)\
	ROM_FILL(0x13833,1,0x71)

#define MSLUG_ENABLE_HP_DAMAGE_FIX_FILL \
    ROM_FILL(0x0FB9E2,1,0x66)\
	ROM_FILL(0x0FE068,1,0x0C)\
	ROM_FILL(0x0FE069,1,0x69)\
    ROM_FILL(0x0FE06A,1,0x00)\
    ROM_FILL(0x0FE06B,1,0x0A)\
    ROM_FILL(0x0FE06C,1,0x00)\
    ROM_FILL(0x0FE06D,1,0x66)\
    ROM_FILL(0x0FE06E,1,0x6D)\
	ROM_FILL(0x0FE06F,1,0x00)\
    ROM_FILL(0x0FE070,1,0x00)\
    ROM_FILL(0x0FE071,1,0x08)\
    ROM_FILL(0x0FE072,1,0x13)\
	ROM_FILL(0x0FE073,1,0x7C)\
    ROM_FILL(0x0FE074,1,0x00)\
	ROM_FILL(0x0FE075,1,0x01)\
    ROM_FILL(0x0FE076,1,0x00)\
	ROM_FILL(0x0FE077,1,0x6E)\
	ROM_FILL(0x0FE078,1,0x32)\
    ROM_FILL(0x0FE079,1,0x29)\
    ROM_FILL(0x0FE07A,1,0x00)\
    ROM_FILL(0x0FE07B,1,0x66)\
    ROM_FILL(0x0FE07C,1,0x92)\
    ROM_FILL(0x0FE07D,1,0x40)\
	ROM_FILL(0x0FE07E,1,0x0C)\
	ROM_FILL(0x0FE07F,1,0x29)\
    ROM_FILL(0x0FE080,1,0x00)\
	ROM_FILL(0x0FE081,1,0x01)\
    ROM_FILL(0x0FE082,1,0x00)\
    ROM_FILL(0x0FE083,1,0x6E)\
	ROM_FILL(0x0FE084,1,0x66)\
	ROM_FILL(0x0FE085,1,0x00)\
    ROM_FILL(0x0FE086,1,0x00)\
    ROM_FILL(0x0FE087,1,0x08)\
    ROM_FILL(0x0FE088,1,0x33)\
    ROM_FILL(0x0FE089,1,0xC1)\
    ROM_FILL(0x0FE08A,1,0x00)\
	ROM_FILL(0x0FE08B,1,0x10)\
    ROM_FILL(0x0FE08C,1,0xFF)\
    ROM_FILL(0x0FE08D,1,0x42)\
    ROM_FILL(0x0FE08E,1,0x4E)\
	ROM_FILL(0x0FE08F,1,0xB9)\
    ROM_FILL(0x0FE090,1,0x00)\
	ROM_FILL(0x0FE091,1,0x0F)\
    ROM_FILL(0x0FE092,1,0xE1)\
	ROM_FILL(0x0FE093,1,0x00)\
	ROM_FILL(0x0FE094,1,0x4E)\
    ROM_FILL(0x0FE095,1,0x71)\
    ROM_FILL(0x0FE096,1,0x4E)\
    ROM_FILL(0x0FE097,1,0x71)\
    ROM_FILL(0x0FE098,1,0x4E)\
    ROM_FILL(0x0FE099,1,0x71)\
	ROM_FILL(0x0FE09A,1,0x4E)\
	ROM_FILL(0x0FE09B,1,0x71)\
    ROM_FILL(0x0FE09C,1,0x4E)\
    ROM_FILL(0x0FE09D,1,0x71)\
    ROM_FILL(0x0FE09E,1,0x32)\
    ROM_FILL(0x0FE09F,1,0x29)\
    ROM_FILL(0x0FE0A0,1,0x00)\
	ROM_FILL(0x0FE0A1,1,0x66)\
	ROM_FILL(0x0FE0A2,1,0x92)\
    ROM_FILL(0x0FE0A3,1,0x40)\
    ROM_FILL(0x0FE0A4,1,0x4E)\
    ROM_FILL(0x0FE0A5,1,0x71)\
    ROM_FILL(0x0FE0A6,1,0x4E)\
    ROM_FILL(0x0FE0A7,1,0x71)\
	ROM_FILL(0x0FE0A8,1,0x4E)\
	ROM_FILL(0x0FE0A9,1,0x71)\
    ROM_FILL(0x0FE0AA,1,0x4E)\
    ROM_FILL(0x0FE0AB,1,0x71)\
    ROM_FILL(0x0FE0AC,1,0x4E)\
    ROM_FILL(0x0FE0AD,1,0x71)\
    ROM_FILL(0x0FE0AE,1,0x4E)\
	ROM_FILL(0x0FE0AF,1,0x71)\
    ROM_FILL(0x0FE0B0,1,0x4E)\
    ROM_FILL(0x0FE0B1,1,0x71)\
    ROM_FILL(0x0FE0B2,1,0x4E)\
	ROM_FILL(0x0FE0B3,1,0x71)\
    ROM_FILL(0x0FE0B4,1,0x4E)\
    ROM_FILL(0x0FE0B5,1,0x75)

#define MSLUG_RESTORING_TITLE_FIX_FILL \
	ROM_FILL(0x1785C4,1,0x49)\
	ROM_FILL(0x1785C5,1,0x4E)\
    ROM_FILL(0x1785C6,1,0x53)\
    ROM_FILL(0x1785C7,1,0x45)\
    ROM_FILL(0x1785C8,1,0x52)\
    ROM_FILL(0x1785C9,1,0x54)\
    ROM_FILL(0x1785CA,1,0x20)\
	ROM_FILL(0x1785CB,1,0x43)\
	ROM_FILL(0x1785CC,1,0x4F)\
    ROM_FILL(0x1785CD,1,0x49)\
	ROM_FILL(0x1785CE,1,0x4E)\
    ROM_FILL(0x1785CF,1,0xFF)\
    ROM_FILL(0x1785D0,1,0x50)\
	ROM_FILL(0x1785D1,1,0x55)\
	ROM_FILL(0x1785D2,1,0x53)\
    ROM_FILL(0x1785D3,1,0x48)\
    ROM_FILL(0x1785D4,1,0x20)\
    ROM_FILL(0x1785D5,1,0x53)\
    ROM_FILL(0x1785D6,1,0x54)\
    ROM_FILL(0x1785D7,1,0x41)\
	ROM_FILL(0x1785D8,1,0x52)\
    ROM_FILL(0x1785D9,1,0x54)\
    ROM_FILL(0x1785DA,1,0x20)\
    ROM_FILL(0x1785DB,1,0xFF)\
	ROM_FILL(0x1785F4,1,0x50)\
    ROM_FILL(0x1785F5,1,0x4C)\
	ROM_FILL(0x1785F6,1,0x45)\
    ROM_FILL(0x1785F7,1,0x41)\
	ROM_FILL(0x1785F8,1,0x53)\
	ROM_FILL(0x1785F9,1,0x45)\
    ROM_FILL(0x1785FA,1,0x20)\
    ROM_FILL(0x1785FB,1,0x57)\
    ROM_FILL(0x1785FC,1,0x41)\
    ROM_FILL(0x1785FD,1,0x49)\
    ROM_FILL(0x1785FE,1,0x54)\
	ROM_FILL(0x1785FF,1,0xFF)\
    ROM_FILL(0x1F4C9C,1,0x52)\
	ROM_FILL(0x1F4C9D,1,0x41)\
	ROM_FILL(0x1F4C9E,1,0x4E)\
    ROM_FILL(0x1F4C9F,1,0x44)\
    ROM_FILL(0x1F4CA0,1,0x4F)\
    ROM_FILL(0x1F4CA1,1,0x4D)\
    ROM_FILL(0x1F4CA2,1,0x00)\
    ROM_FILL(0x1F4CA3,1,0x49)\
	ROM_FILL(0x1F4CA4,1,0x54)\
    ROM_FILL(0x1F4CA5,1,0x45)\
    ROM_FILL(0x1F4CA6,1,0x4D)\
    ROM_FILL(0x1F4CA7,1,0x00)\
	ROM_FILL(0x1F4CA8,1,0x56)\
    ROM_FILL(0x1F4CA9,1,0x32)\
	ROM_FILL(0x1F4CAA,1,0x2E)\
    ROM_FILL(0x1F4CAB,1,0x30)\
	ROM_FILL(0x1F54A0,1,0x4E)\
    ROM_FILL(0x1F54A1,1,0x41)\
	ROM_FILL(0x1F54A2,1,0x5A)\
    ROM_FILL(0x1F54A3,1,0x43)\
	ROM_FILL(0x1F54A4,1,0x41)\
	ROM_FILL(0x1F54A5,1,0x20)\
    ROM_FILL(0x1F54A6,1,0x43)\
    ROM_FILL(0x1F54A7,1,0x4F)\
    ROM_FILL(0x1F54A8,1,0x52)\
    ROM_FILL(0x1F54A9,1,0x50)\
    ROM_FILL(0x1F54AA,1,0x4F)\
	ROM_FILL(0x1F54AB,1,0x52)\
	ROM_FILL(0x1F54AC,1,0x41)\
    ROM_FILL(0x1F54AD,1,0x54)\
    ROM_FILL(0x1F54AE,1,0x49)\
    ROM_FILL(0x1F54AF,1,0x4F)\
	ROM_FILL(0x1F54B0,1,0x4E)\
	ROM_FILL(0x1F54B1,1,0xFE)\
    ROM_FILL(0x1FA100,1,0x46)\
    ROM_FILL(0x1FA101,1,0x49)\
    ROM_FILL(0x1FA102,1,0x47)\
    ROM_FILL(0x1FA103,1,0x48)\
    ROM_FILL(0x1FA104,1,0x54)\
	ROM_FILL(0x1FA105,1,0x43)\
	ROM_FILL(0x1FA106,1,0x41)\
    ROM_FILL(0x1FA107,1,0x44)\
    ROM_FILL(0x1FA108,1,0x45)\
    ROM_FILL(0x1FA109,1,0xFE)

#define MSLUG_MVS_FILL \
	ROM_FILL(0x1783E4,1,0x63)\
    ROM_FILL(0x1783E7,1,0x58)\
	ROM_FILL(0x1783EB,1,0x12)\
	ROM_FILL(0x1783E8,1,0x34)\
	ROM_FILL(0x1783EE,1,0x23)

#define MSLUG_AES_FILL \
	ROM_FILL(0x100B,1,0x99)

#define MSLUG2AT_SOLDIERSHIELD_CHANGING_UNIFORM_MODS_FILL \
    ROM_FILL(0x202E24,1,0x6F)\
	ROM_FILL(0x202E25,1,0xDF)\
	ROM_FILL(0x202E26,1,0x4E)\
    ROM_FILL(0x202E27,1,0xD9)\
    ROM_FILL(0x202E28,1,0x31)\
    ROM_FILL(0x202E29,1,0xF3)\
    ROM_FILL(0x202E2A,1,0x1D)\
    ROM_FILL(0x202E2B,1,0x2E)\
    ROM_FILL(0x2073E4,1,0x6F)\
	ROM_FILL(0x2073E5,1,0xDF)\
	ROM_FILL(0x2073E6,1,0x4E)\
    ROM_FILL(0x2073E7,1,0xD9)\
    ROM_FILL(0x2073E8,1,0x31)\
    ROM_FILL(0x2073E9,1,0xF3)\
    ROM_FILL(0x2073EA,1,0x1D)\
    ROM_FILL(0x2073EB,1,0x2E)\
    ROM_FILL(0x207404,1,0x6F)\
	ROM_FILL(0x207405,1,0xDF)\
	ROM_FILL(0x207406,1,0x4E)\
    ROM_FILL(0x207407,1,0xD9)\
    ROM_FILL(0x207408,1,0x31)\
    ROM_FILL(0x207409,1,0xF3)\
    ROM_FILL(0x20740A,1,0x1D)\
    ROM_FILL(0x20740B,1,0x2E)\
    ROM_FILL(0x207424,1,0x6F)\
	ROM_FILL(0x207425,1,0xDF)\
	ROM_FILL(0x207426,1,0x4E)\
    ROM_FILL(0x207427,1,0xD9)\
    ROM_FILL(0x207428,1,0x31)\
    ROM_FILL(0x207429,1,0xF3)\
    ROM_FILL(0x20742A,1,0x1D)\
    ROM_FILL(0x20742B,1,0x2E)\
    ROM_FILL(0x207444,1,0x6F)\
	ROM_FILL(0x207445,1,0xDF)\
	ROM_FILL(0x207446,1,0x4E)\
    ROM_FILL(0x207447,1,0xD9)\
    ROM_FILL(0x207448,1,0x31)\
    ROM_FILL(0x207449,1,0xF3)\
    ROM_FILL(0x20744A,1,0x1D)\
    ROM_FILL(0x20744B,1,0x2E)\
    ROM_FILL(0x207464,1,0x6F)\
	ROM_FILL(0x207465,1,0xDF)\
	ROM_FILL(0x207466,1,0x4E)\
    ROM_FILL(0x207467,1,0xD9)\
    ROM_FILL(0x207468,1,0x31)\
    ROM_FILL(0x207469,1,0xF3)\
    ROM_FILL(0x20746A,1,0x1D)\
    ROM_FILL(0x20746B,1,0x2E)\
    ROM_FILL(0x207484,1,0x6F)\
	ROM_FILL(0x207485,1,0xDF)\
	ROM_FILL(0x207486,1,0x4E)\
    ROM_FILL(0x207487,1,0xD9)\
    ROM_FILL(0x207488,1,0x31)\
    ROM_FILL(0x207489,1,0xF3)\
    ROM_FILL(0x20748A,1,0x1D)\
    ROM_FILL(0x20748B,1,0x2E)\
    ROM_FILL(0x2074A4,1,0x6F)\
	ROM_FILL(0x2074A5,1,0xDF)\
	ROM_FILL(0x2074A6,1,0x4E)\
    ROM_FILL(0x2074A7,1,0xD9)\
    ROM_FILL(0x2074A8,1,0x31)\
    ROM_FILL(0x2074A9,1,0xF3)\
    ROM_FILL(0x2074AA,1,0x1D)\
    ROM_FILL(0x2074AB,1,0x2E)\
    ROM_FILL(0x2078E4,1,0x6F)\
	ROM_FILL(0x2078E5,1,0xDF)\
	ROM_FILL(0x2078E6,1,0x4E)\
    ROM_FILL(0x2078E7,1,0xD9)\
    ROM_FILL(0x2078E8,1,0x31)\
    ROM_FILL(0x2078E9,1,0xF3)\
    ROM_FILL(0x2078EA,1,0x1D)\
    ROM_FILL(0x2078EB,1,0x2E)

#define MSLUG2AT_PLAYERS_CHANGING_UNIFORM_MODS_FILL \
	ROM_FILL(0x200F78,1,0x40)\
    ROM_FILL(0x200F79,1,0x76)\
    ROM_FILL(0x200F7A,1,0x64)\
    ROM_FILL(0x200F7B,1,0x7F)\
	ROM_FILL(0x200F7C,1,0x61)\
    ROM_FILL(0x200F7D,1,0xA0)\
    ROM_FILL(0x200F7E,1,0x40)\
    ROM_FILL(0x200F7F,1,0xE0)\
	ROM_FILL(0x200F98,1,0x40)\
    ROM_FILL(0x200F99,1,0x76)\
    ROM_FILL(0x200F9A,1,0x64)\
    ROM_FILL(0x200F9B,1,0x7F)\
	ROM_FILL(0x200F9C,1,0x61)\
    ROM_FILL(0x200F9D,1,0xA0)\
    ROM_FILL(0x200F9E,1,0x40)\
    ROM_FILL(0x200F9F,1,0xE0)\
	ROM_FILL(0x200FF8,1,0x59)\
    ROM_FILL(0x200FF9,1,0x00)\
    ROM_FILL(0x200FFA,1,0x3C)\
    ROM_FILL(0x200FFB,1,0x00)\
	ROM_FILL(0x200FFC,1,0x7F)\
    ROM_FILL(0x200FFD,1,0x89)\
    ROM_FILL(0x200FFE,1,0x72)\
    ROM_FILL(0x200FFF,1,0x65)\
	ROM_FILL(0x201018,1,0x59)\
    ROM_FILL(0x201019,1,0x00)\
    ROM_FILL(0x20101A,1,0x3C)\
    ROM_FILL(0x20101B,1,0x00)\
	ROM_FILL(0x20101C,1,0x7F)\
    ROM_FILL(0x20101D,1,0x89)\
    ROM_FILL(0x20101E,1,0x72)\
    ROM_FILL(0x20101F,1,0x65)\
	ROM_FILL(0x200FB8,1,0x02)\
    ROM_FILL(0x200FB9,1,0x30)\
    ROM_FILL(0x200FBA,1,0x01)\
    ROM_FILL(0x200FBB,1,0x30)\
	ROM_FILL(0x200FBC,1,0x7F)\
    ROM_FILL(0x200FBD,1,0x89)\
    ROM_FILL(0x200FBE,1,0x72)\
    ROM_FILL(0x200FBF,1,0x65)\
	ROM_FILL(0x200FD8,1,0x02)\
    ROM_FILL(0x200FD9,1,0x30)\
    ROM_FILL(0x200FDA,1,0x01)\
    ROM_FILL(0x200FDB,1,0x30)\
	ROM_FILL(0x200FDC,1,0x7F)\
    ROM_FILL(0x200FDD,1,0x89)\
    ROM_FILL(0x200FDE,1,0x72)\
    ROM_FILL(0x200FDF,1,0x65)\
	ROM_FILL(0x200F38,1,0x7F)\
    ROM_FILL(0x200F39,1,0x80)\
    ROM_FILL(0x200F3A,1,0x72)\
    ROM_FILL(0x200F3B,1,0x60)\
	ROM_FILL(0x200F3C,1,0x61)\
    ROM_FILL(0x200F3D,1,0xA0)\
    ROM_FILL(0x200F3E,1,0x40)\
    ROM_FILL(0x200F3F,1,0xE0)\
	ROM_FILL(0x200F58,1,0x7F)\
    ROM_FILL(0x200F59,1,0x80)\
    ROM_FILL(0x200F5A,1,0x72)\
    ROM_FILL(0x200F5B,1,0x60)\
	ROM_FILL(0x200F5C,1,0x61)\
    ROM_FILL(0x200F5D,1,0xA0)\
    ROM_FILL(0x200F5E,1,0x40)\
    ROM_FILL(0x200F5F,1,0xE0)

#define MSLUG2_BOSS_MODS_FILL \
	ROM_FILL(0xB00F2,1,0x50)

#define MSLUG2_CUZTOMWEAPONANIMATION_MODS_FILL \
	ROM_FILL(0xF7769,1,0x0A)\
	ROM_FILL(0x4D139,1,0x07)\
	ROM_FILL(0x4D159,1,0x07)\
	ROM_FILL(0x4D169,1,0x07)\
	ROM_FILL(0x4D199,1,0x07)\
	ROM_FILL(0x4D1A9,1,0x07)\
	ROM_FILL(0x4D1B9,1,0x07)\
	ROM_FILL(0x4D8BD,1,0x0D)\
	ROM_FILL(0x4D8CD,1,0x0D)\
	ROM_FILL(0x4D8DD,1,0x0D)\
	ROM_FILL(0x4DE13,1,0x0B)\
	ROM_FILL(0x4DE23,1,0x0B)\
	ROM_FILL(0x38B7,1,0x0A)\
	ROM_FILL(0x38C7,1,0x0A)\
	ROM_FILL(0x38D7,1,0x0A)\
	ROM_FILL(0x38E7,1,0x0A)\
	ROM_FILL(0x38F7,1,0x0A)\
	ROM_FILL(0x3907,1,0x0A)\
	ROM_FILL(0x3917,1,0x0A)\
	ROM_FILL(0x3927,1,0x0A)\
	ROM_FILL(0x3937,1,0x0A)\
	ROM_FILL(0x3947,1,0x0A)\
	ROM_FILL(0x3957,1,0x0A)\
	ROM_FILL(0x3967,1,0x0A)\
	ROM_FILL(0x3977,1,0x0A)\
	ROM_FILL(0x3987,1,0x0A)\
	ROM_FILL(0x3997,1,0x0A)\
	ROM_FILL(0x39A7,1,0x0A)\
	ROM_FILL(0x8F61,1,0x09)\
	ROM_FILL(0x8F81,1,0x09)\
	ROM_FILL(0x8FB1,1,0x09)\
	ROM_FILL(0x8FC1,1,0x09)

#define MSLUG2_DISABLEMODTURBO_MODS_FILL \
	ROM_FILL(0xD8000,1,0x00)\
	ROM_FILL(0xD8001,1,0x00)\
	ROM_FILL(0xD8002,1,0x00)\
	ROM_FILL(0xD8003,1,0x00)\
    ROM_FILL(0xD8004,1,0x00)\
	ROM_FILL(0xD8005,1,0x00)\
	ROM_FILL(0xD8006,1,0x00)\
	ROM_FILL(0xD8007,1,0x00)\
	ROM_FILL(0xD8008,1,0x00)\
    ROM_FILL(0xD8009,1,0x00)\
	ROM_FILL(0xD800A,1,0x00)\
	ROM_FILL(0xD800B,1,0x00)\
	ROM_FILL(0xD800C,1,0x00)\
    ROM_FILL(0xD800D,1,0x00)\
	ROM_FILL(0xD800E,1,0x00)\
	ROM_FILL(0xD800F,1,0x00)\
	ROM_FILL(0xD8010,1,0x00)\
	ROM_FILL(0xD8011,1,0x00)\
	ROM_FILL(0xD8012,1,0x00)\
	ROM_FILL(0xD8013,1,0x00)\
    ROM_FILL(0x11F7,1,0x20)\
	ROM_FILL(0x11F8,1,0x20)\
	ROM_FILL(0x11F9,1,0x20)\
	ROM_FILL(0x11FA,1,0x20)\
	ROM_FILL(0x1450,1,0x10)\
    ROM_FILL(0x1451,1,0x2D)\
	ROM_FILL(0x1452,1,0x80)\
	ROM_FILL(0x1453,1,0x8A)\
	ROM_FILL(0x1454,1,0x52)\
    ROM_FILL(0x1455,1,0x00)\
	ROM_FILL(0x1456,1,0x65)\
	ROM_FILL(0x1457,1,0x00)\
	ROM_FILL(0x1458,1,0x00)\
	ROM_FILL(0x1459,1,0x0C)\
	ROM_FILL(0x1464,1,0x08)\
	ROM_FILL(0x1465,1,0xED)\
    ROM_FILL(0x1466,1,0x00)\
	ROM_FILL(0x1467,1,0x07)\
	ROM_FILL(0x1468,1,0x80)\
	ROM_FILL(0x1469,1,0x8C)\
	ROM_FILL(0x146A,1,0x66)\
    ROM_FILL(0x146B,1,0x00)\
	ROM_FILL(0x146C,1,0x00)\
	ROM_FILL(0x146D,1,0x78)\
	ROM_FILL(0x147D,1,0x5C)\
    ROM_FILL(0x1487,1,0x52)\
	ROM_FILL(0x14D2,1,0x1B)\
	ROM_FILL(0x14D3,1,0x7C)\
	ROM_FILL(0x14D4,1,0x00)\
	ROM_FILL(0x14D5,1,0xFF)\
	ROM_FILL(0x14D6,1,0x80)\
	ROM_FILL(0x14D7,1,0x8D)\
    ROM_FILL(0x1650,1,0x08)\
	ROM_FILL(0x1651,1,0xAD)\
	ROM_FILL(0x1652,1,0x00)\
	ROM_FILL(0x1653,1,0x07)\
	ROM_FILL(0x1654,1,0x80)\
	ROM_FILL(0x1655,1,0x8D)\
	ROM_FILL(0x1656,1,0x67)\
    ROM_FILL(0x1657,1,0xF8)\
	ROM_FILL(0x165E,1,0x1B)\
	ROM_FILL(0x165F,1,0x7C)\
	ROM_FILL(0x1660,1,0x00)\
    ROM_FILL(0x1661,1,0x00)\
	ROM_FILL(0x1662,1,0x80)\
	ROM_FILL(0x1663,1,0x8A)\
	ROM_FILL(0x108,1,0x02)\

#define MSLUG2_THEYTEARYOUAPARTWHENITDIES_MODS_FILL \
    ROM_FILL(0x9434D,1,0x0B)\
    ROM_FILL(0x9434E,1,0x5D)\
	ROM_FILL(0x9434F,1,0xB4)\
    ROM_FILL(0x943B7,1,0x0B)\
    ROM_FILL(0x943B8,1,0x5D)\
	ROM_FILL(0x943B9,1,0xB4)\
    ROM_FILL(0x94463,1,0x0B)\
    ROM_FILL(0x94464,1,0x5D)\
	ROM_FILL(0x94465,1,0xB4)\
    ROM_FILL(0x94703,1,0x0B)\
    ROM_FILL(0x94704,1,0x5D)\
	ROM_FILL(0x94705,1,0xB4)

#define MSLUG2_FLASHOFF_MODS_FILL \
    ROM_FILL(0x859E6,1,0x4E)\
	ROM_FILL(0x859E7,1,0x71)\
	ROM_FILL(0x859E8,1,0x4E)\
	ROM_FILL(0x859E9,1,0x71)

#define MSLUG2_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
    ROM_FILL(0x19F6,1,0x49)\
    ROM_FILL(0x19F7,1,0x4E)\
    ROM_FILL(0x19F8,1,0x56)\
	ROM_FILL(0x19F9,1,0x45)\
	ROM_FILL(0x19FA,1,0x4E)\
    ROM_FILL(0x19FB,1,0x54)\
    ROM_FILL(0x19FC,1,0x4F)\
    ROM_FILL(0x19FD,1,0x52)\
    ROM_FILL(0x19FE,1,0x59)\
    ROM_FILL(0x19FF,1,0x00)\
	ROM_FILL(0x1A00,1,0x43)\
    ROM_FILL(0x1A01,1,0x4C)\
    ROM_FILL(0x1A02,1,0x4F)\
    ROM_FILL(0x1A03,1,0x53)\
	ROM_FILL(0x1A04,1,0x5C)\
    ROM_FILL(0x1A05,1,0x45)\
	ROM_FILL(0x1A06,1,0x20)\
	ROM_FILL(0x1A07,1,0x4D)\
	ROM_FILL(0x1A08,1,0x45)\
	ROM_FILL(0x1A09,1,0x4E)\
    ROM_FILL(0x1A0A,1,0x55)\
    ROM_FILL(0x1A0B,1,0x20)\
    ROM_FILL(0x1A0C,1,0x28)\
    ROM_FILL(0x1A0D,1,0x49)\
    ROM_FILL(0x1A0E,1,0x4E)\
	ROM_FILL(0x1A0F,1,0x2D)\
	ROM_FILL(0x1A10,1,0x50)\
	ROM_FILL(0x1A11,1,0x41)\
	ROM_FILL(0x1A12,1,0x55)\
	ROM_FILL(0x1A13,1,0x53)\
	ROM_FILL(0x1A14,1,0x45)\
    ROM_FILL(0x1A15,1,0x29)\
	ROM_FILL(0x1A16,1,0x00)\
	ROM_FILL(0x1ED8,1,0x49)\
    ROM_FILL(0x1ED9,1,0x4E)\
    ROM_FILL(0x1EDA,1,0x56)\
	ROM_FILL(0x1EDB,1,0x49)\
	ROM_FILL(0x1EDC,1,0x4E)\
    ROM_FILL(0x1EDD,1,0x43)\
    ROM_FILL(0x1EDE,1,0x49)\
    ROM_FILL(0x1EDF,1,0x42)\
    ROM_FILL(0x1EE0,1,0x49)\
    ROM_FILL(0x1EE1,1,0x4C)\
	ROM_FILL(0x1EE2,1,0x49)\
    ROM_FILL(0x1EE3,1,0x54)\
    ROM_FILL(0x1EE4,1,0x59)\
    ROM_FILL(0x1EE5,1,0x20)\
    ROM_FILL(0x1F03,1,0x41)\
    ROM_FILL(0x1F04,1,0x4E)\
	ROM_FILL(0x1F05,1,0x59)\
    ROM_FILL(0x1F06,1,0x54)\
	ROM_FILL(0x1F07,1,0x49)\
	ROM_FILL(0x1F08,1,0x4D)\
    ROM_FILL(0x1F09,1,0x45)\
    ROM_FILL(0x1F0A,1,0x20)\
    ROM_FILL(0x1F0B,1,0x50)\
    ROM_FILL(0x1F0C,1,0x41)\
    ROM_FILL(0x1F0D,1,0x55)\
	ROM_FILL(0x1F0E,1,0x53)\
	ROM_FILL(0x1F0F,1,0x45)\
	ROM_FILL(0x1F10,1,0x20)\
    ROM_FILL(0x1F8E,1,0x49)\
	ROM_FILL(0x1F8F,1,0x4E)\
	ROM_FILL(0x1F90,1,0x46)\
    ROM_FILL(0x1F91,1,0x49)\
	ROM_FILL(0x1F92,1,0x4E)\
    ROM_FILL(0x1F93,1,0x49)\
    ROM_FILL(0x1F94,1,0x54)\
    ROM_FILL(0x1F95,1,0x45)\
	ROM_FILL(0x1F96,1,0x20)\
	ROM_FILL(0x1F97,1,0x41)\
    ROM_FILL(0x1F98,1,0x4D)\
    ROM_FILL(0x1F99,1,0x4D)\
    ROM_FILL(0x1F9A,1,0x4F)\
    ROM_FILL(0x1F9B,1,0x20)\
    ROM_FILL(0x1F76,1,0x00)\
	ROM_FILL(0x1F77,1,0x49)\
    ROM_FILL(0x1F78,1,0x4E)\
    ROM_FILL(0x1F79,1,0x46)\
    ROM_FILL(0x1F7A,1,0x49)\
	ROM_FILL(0x1F7B,1,0x4E)\
    ROM_FILL(0x1F7C,1,0x49)\
	ROM_FILL(0x1F7D,1,0x54)\
    ROM_FILL(0x1F7E,1,0x45)\
	ROM_FILL(0x1F7F,1,0x20)\
	ROM_FILL(0x1F80,1,0x42)\
    ROM_FILL(0x1F81,1,0x4F)\
    ROM_FILL(0x1F82,1,0x4D)\
	ROM_FILL(0x1F83,1,0x42)\
    ROM_FILL(0x1F84,1,0x20)\
    ROM_FILL(0x1F85,1,0x20)\
    ROM_FILL(0x1FA5,1,0x44)\
	ROM_FILL(0x1FA6,1,0x2D)\
	ROM_FILL(0x1FA7,1,0x42)\
	ROM_FILL(0x1FA8,1,0x55)\
    ROM_FILL(0x1FA9,1,0x54)\
    ROM_FILL(0x1FAA,1,0x54)\
	ROM_FILL(0x1FAB,1,0x4F)\
	ROM_FILL(0x1FAC,1,0x4E)\
    ROM_FILL(0x1FAD,1,0x20)\
    ROM_FILL(0x1FAE,1,0x57)\
    ROM_FILL(0x1FAF,1,0x49)\
    ROM_FILL(0x1FB0,1,0x50)\
    ROM_FILL(0x1FB1,1,0x45)\
	ROM_FILL(0x1FB2,1,0x4F)\
    ROM_FILL(0x1FB3,1,0x55)\
    ROM_FILL(0x1FB4,1,0x54)\
    ROM_FILL(0x1FB5,1,0x20)\
    ROM_FILL(0x1FC1,1,0x52)\
    ROM_FILL(0x1FC2,1,0x45)\
	ROM_FILL(0x1FC3,1,0x53)\
    ROM_FILL(0x1FC4,1,0x50)\
	ROM_FILL(0x1FC5,1,0x41)\
	ROM_FILL(0x1FC6,1,0x57)\
    ROM_FILL(0x1FC7,1,0x4E)

#define MSLUG2_MVS_FILL \
	ROM_FILL(0x100A,1,0x63)\
    ROM_FILL(0x100D,1,0x58)\
	ROM_FILL(0x1011,1,0x12)\
	ROM_FILL(0x1013,1,0x34)\
	ROM_FILL(0x100E,1,0x34)\
	ROM_FILL(0x1014,1,0x34)

#define MSLUG2CT_MVS_FILL \
    ROM_FILL(0x100D,1,0x58)\
	ROM_FILL(0x1011,1,0x12)\
	ROM_FILL(0x1013,1,0x34)\
	ROM_FILL(0x100E,1,0x34)\
	ROM_FILL(0x1014,1,0x34)

#define MSLUG2AT_MVS_FILL \
    ROM_FILL(0x100D,1,0x58)\
	ROM_FILL(0x1011,1,0x12)\
	ROM_FILL(0x1013,1,0x34)\
	ROM_FILL(0x100E,1,0x34)\
	ROM_FILL(0x1014,1,0x34)\
	ROM_FILL(0x1010,1,0x12)\
	ROM_FILL(0x100A,1,0x99)

#define MSLUG2_AES_FILL \
	ROM_FILL(0x902,1,0x99) \
	ROM_FILL(0x903,1,0x99) \
	ROM_FILL(0x1954,1,0x60)

#define MSLUG3CQI_RESTORELVXCODE_MODS_FILL \
    ROM_FILL(0X23FFBD,1,0x02)\
    ROM_FILL(0X23FFCF,1,0x02)\
	ROM_FILL(0X23FFE1,1,0x02)\
	ROM_FILL(0X23FFF3,1,0x02)\
    ROM_FILL(0X4DA0A0,1,0x08)\
    ROM_FILL(0X4DA0A1,1,0x39)

#define MSLUG3ND_FIX_FILL \
    ROM_FILL(0x39527,1,0x53)

#define MSLUG3G_SOLDIER_CHANGING_UNIFORM_MODS_FILL \
    ROM_FILL(0x4613E4,1,0x73)\
	ROM_FILL(0x4613E5,1,0x9A)\
	ROM_FILL(0x4613E6,1,0x63)\
    ROM_FILL(0x4613E7,1,0x15)\
    ROM_FILL(0x4613E8,1,0x46)\
    ROM_FILL(0x4613E9,1,0x2F)\
    ROM_FILL(0x4613EA,1,0x25)\
    ROM_FILL(0x4613EB,1,0x27)\
	ROM_FILL(0x461484,1,0x73)\
    ROM_FILL(0x461485,1,0x9A)\
    ROM_FILL(0x461486,1,0x63)\
    ROM_FILL(0x461487,1,0x15)\
	ROM_FILL(0x461488,1,0x46)\
    ROM_FILL(0x461489,1,0x2F)\
	ROM_FILL(0x46148A,1,0x25)\
    ROM_FILL(0x46148B,1,0x27)\
	ROM_FILL(0x462044,1,0x73)\
	ROM_FILL(0x462045,1,0x9A)\
    ROM_FILL(0x462046,1,0x63)\
    ROM_FILL(0x462047,1,0x15)\
    ROM_FILL(0x462048,1,0x46)\
    ROM_FILL(0x462049,1,0x2F)\
    ROM_FILL(0x46204A,1,0x25)\
	ROM_FILL(0x46204B,1,0x27)\
	ROM_FILL(0x4641C4,1,0x73)\
    ROM_FILL(0x4641C5,1,0x9A)\
	ROM_FILL(0x4641C6,1,0x63)\
    ROM_FILL(0x4641C7,1,0x15)\
    ROM_FILL(0x4641C8,1,0x46)\
	ROM_FILL(0x4641C9,1,0x2F)\
	ROM_FILL(0x4641CA,1,0x25)\
    ROM_FILL(0x4641CB,1,0x27)\
    ROM_FILL(0x464284,1,0x73)\
    ROM_FILL(0x464285,1,0x9A)\
    ROM_FILL(0x464286,1,0x63)\
    ROM_FILL(0x464287,1,0x15)\
	ROM_FILL(0x464288,1,0x46)\
    ROM_FILL(0x464289,1,0x2F)\
    ROM_FILL(0x46428A,1,0x25)\
    ROM_FILL(0x46428B,1,0x27)\
	ROM_FILL(0x4642E4,1,0x73)\
    ROM_FILL(0x4642E5,1,0x9A)\
	ROM_FILL(0x4642E6,1,0x63)\
    ROM_FILL(0x4642E7,1,0x15)\
	ROM_FILL(0x4642E8,1,0x46)\
	ROM_FILL(0x4642E9,1,0x2F)\
    ROM_FILL(0x4642EA,1,0x25)\
    ROM_FILL(0x4642EB,1,0x27)\
    ROM_FILL(0x464344,1,0x73)\
    ROM_FILL(0x464345,1,0x9A)\
    ROM_FILL(0x464346,1,0x63)\
	ROM_FILL(0x464347,1,0x15)\
    ROM_FILL(0x464348,1,0x46)\
	ROM_FILL(0x464349,1,0x2F)\
	ROM_FILL(0x46434A,1,0x25)\
    ROM_FILL(0x46434B,1,0x27)\
    ROM_FILL(0x4643A4,1,0x73)\
    ROM_FILL(0x4643A5,1,0x9A)\
    ROM_FILL(0x4643A6,1,0x63)\
    ROM_FILL(0x4643A7,1,0x15)\
	ROM_FILL(0x4643A8,1,0x46)\
    ROM_FILL(0x4643A9,1,0x2F)\
    ROM_FILL(0x4643AA,1,0x25)\
    ROM_FILL(0x4643AB,1,0x27)\
	ROM_FILL(0x464404,1,0x73)\
    ROM_FILL(0x464405,1,0x9A)\
    ROM_FILL(0x464406,1,0x63)\
	ROM_FILL(0x464407,1,0x15)\
	ROM_FILL(0x464408,1,0x46)\
    ROM_FILL(0x464409,1,0x2F)\
    ROM_FILL(0x46440A,1,0x25)\
    ROM_FILL(0x46440B,1,0x27)\
    ROM_FILL(0x464424,1,0x73)\
    ROM_FILL(0x464425,1,0x9A)\
	ROM_FILL(0x464426,1,0x63)\
    ROM_FILL(0x464427,1,0x15)\
    ROM_FILL(0x464428,1,0x46)\
    ROM_FILL(0x464429,1,0x2F)\
	ROM_FILL(0x46442A,1,0x25)\
    ROM_FILL(0x46442B,1,0x27)\
	ROM_FILL(0x464504,1,0x73)\
    ROM_FILL(0x464505,1,0x9A)\
	ROM_FILL(0x464506,1,0x63)\
	ROM_FILL(0x464507,1,0x15)\
    ROM_FILL(0x464508,1,0x46)\
    ROM_FILL(0x464509,1,0x2F)\
    ROM_FILL(0x46450A,1,0x25)\
    ROM_FILL(0x46450B,1,0x27)\
    ROM_FILL(0x4645E4,1,0x73)\
	ROM_FILL(0x4645E5,1,0x9A)\
	ROM_FILL(0x4645E6,1,0x63)\
    ROM_FILL(0x4645E7,1,0x15)\
	ROM_FILL(0x4645E8,1,0x46)\
    ROM_FILL(0x4645E9,1,0x2F)\
    ROM_FILL(0x4645EA,1,0x25)\
	ROM_FILL(0x4645EB,1,0x27)\
	ROM_FILL(0x464704,1,0x73)\
    ROM_FILL(0x464705,1,0x9A)\
    ROM_FILL(0x464706,1,0x63)\
    ROM_FILL(0x464707,1,0x15)\
    ROM_FILL(0x464708,1,0x46)\
    ROM_FILL(0x464709,1,0x2F)\
	ROM_FILL(0x46470A,1,0x25)\
    ROM_FILL(0x46470B,1,0x27)\
    ROM_FILL(0x466964,1,0x73)\
    ROM_FILL(0x466965,1,0x9A)\
	ROM_FILL(0x466966,1,0x63)\
    ROM_FILL(0x466967,1,0x15)\
	ROM_FILL(0x466968,1,0x46)\
    ROM_FILL(0x466969,1,0x2F)\
	ROM_FILL(0x46696A,1,0x25)\
	ROM_FILL(0x46696B,1,0x27)\
    ROM_FILL(0x466B84,1,0x73)\
    ROM_FILL(0x466B85,1,0x9A)\
    ROM_FILL(0x466B86,1,0x63)\
    ROM_FILL(0x466B87,1,0x15)\
    ROM_FILL(0x466B88,1,0x46)\
	ROM_FILL(0x466B89,1,0x2F)\
    ROM_FILL(0x466B8A,1,0x25)\
	ROM_FILL(0x466B8B,1,0x27)\
	ROM_FILL(0x466C04,1,0x73)\
    ROM_FILL(0x466C05,1,0x9A)\
    ROM_FILL(0x466C06,1,0x63)\
    ROM_FILL(0x466C07,1,0x15)\
    ROM_FILL(0x466C08,1,0x46)\
    ROM_FILL(0x466C09,1,0x2F)\
	ROM_FILL(0x466C0A,1,0x25)\
    ROM_FILL(0x466C0B,1,0x27)\
    ROM_FILL(0x467184,1,0x73)\
    ROM_FILL(0x467185,1,0x9A)\
	ROM_FILL(0x467186,1,0x63)\
    ROM_FILL(0x467187,1,0x15)\
	ROM_FILL(0x467188,1,0x46)\
    ROM_FILL(0x467189,1,0x2F)\
	ROM_FILL(0x46718A,1,0x25)\
	ROM_FILL(0x46718B,1,0x27)\
    ROM_FILL(0x470F84,1,0x73)\
    ROM_FILL(0x470F85,1,0x9A)\
    ROM_FILL(0x470F86,1,0x63)\
    ROM_FILL(0x470F87,1,0x15)\
    ROM_FILL(0x470F88,1,0x46)\
	ROM_FILL(0x470F89,1,0x2F)\
	ROM_FILL(0x470F8A,1,0x25)\
    ROM_FILL(0x470F8B,1,0x27)\
    ROM_FILL(0x471344,1,0x73)\
    ROM_FILL(0x471345,1,0x9A)\
    ROM_FILL(0x471346,1,0x63)\
    ROM_FILL(0x471347,1,0x15)\
    ROM_FILL(0x471348,1,0x46)\
	ROM_FILL(0x471349,1,0x2F)\
	ROM_FILL(0x47134A,1,0x25)\
    ROM_FILL(0x47134B,1,0x27)\
    ROM_FILL(0x471B84,1,0x73)\
    ROM_FILL(0x471B85,1,0x9A)\
    ROM_FILL(0x471B86,1,0x63)\
    ROM_FILL(0x471B87,1,0x15)\
    ROM_FILL(0x471B88,1,0x46)\
	ROM_FILL(0x471B89,1,0x2F)\
	ROM_FILL(0x471B8A,1,0x25)\
    ROM_FILL(0x471B8B,1,0x27)\
    ROM_FILL(0x473E86,1,0x73)\
	ROM_FILL(0x473E87,1,0x9A)\
	ROM_FILL(0x473E88,1,0x63)\
    ROM_FILL(0x473E89,1,0x15)\
    ROM_FILL(0x473E8A,1,0x46)\
    ROM_FILL(0x473E8B,1,0x2F)\
    ROM_FILL(0x473E8C,1,0x25)\
    ROM_FILL(0x473E8D,1,0x27)

#define MSLUG3H_JUMPATLEVEL5X3_MODS_FILL \
    ROM_FILL(0x4147FE,1,0x00) \
    ROM_FILL(0x4147FF,1,0x03)

#define MSLUG3H_JUMPATLEVEL5X7_MODS_FILL \
    ROM_FILL(0xDF1FB,1,0x06)

#define MSLUG3H_LEVELGAME_PLAYERS_FIX_FILL \
	ROM_FILL(0x41C9CE,1,0x05)\
	ROM_FILL(0x41C9CF,1,0xA8)\
	ROM_FILL(0x40B81A,1,0x05)\
	ROM_FILL(0x40B81B,1,0xA8)

#define MSLUG3H_CHANGEMOVINGPLAYERS_MODS_FILL \
    ROM_FILL(0x235B4,1,0x05)\
    ROM_FILL(0x235B8,1,0x05)\
    ROM_FILL(0x2363B,1,0x0C)\
	ROM_FILL(0x23AFA,1,0x06)\
	ROM_FILL(0x23AFE,1,0x05)\
	ROM_FILL(0x23B87,1,0x0C)\
	ROM_FILL(0x23FDE,1,0x06)\
    ROM_FILL(0x23FE2,1,0x05)\
    ROM_FILL(0x2405B,1,0x0C)\
    ROM_FILL(0x22829,1,0x03)\
    ROM_FILL(0x2282D,1,0x03)\
    ROM_FILL(0x22831,1,0x03)\
	ROM_FILL(0x22839,1,0x04)\
    ROM_FILL(0x223D4,1,0x02)\
	ROM_FILL(0x22845,1,0x04)\
	ROM_FILL(0x22851,1,0x0E)\
	ROM_FILL(0x22855,1,0x06)

#define MSLUG3H_FLASHOFF_MODS_FILL \
    ROM_FILL(0xD300,1,0x4E)\
	ROM_FILL(0xD301,1,0x71)\
	ROM_FILL(0xD302,1,0x4E)\
	ROM_FILL(0xD303,1,0x71)

#define MSLUG3H_LIFEMORE_MODS_FILL \
    ROM_FILL(0x433A6,1,0x52)

#define MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
    ROM_FILL(0x614C,1,0x49)\
    ROM_FILL(0x614D,1,0x4E)\
    ROM_FILL(0x614E,1,0x56)\
	ROM_FILL(0x614F,1,0x45)\
	ROM_FILL(0x6150,1,0x4E)\
    ROM_FILL(0x6151,1,0x54)\
    ROM_FILL(0x6152,1,0x4F)\
    ROM_FILL(0x6153,1,0x52)\
    ROM_FILL(0x6154,1,0x59)\
    ROM_FILL(0x6155,1,0x00)\
	ROM_FILL(0x6156,1,0x43)\
    ROM_FILL(0x6157,1,0x4C)\
    ROM_FILL(0x6158,1,0x4F)\
    ROM_FILL(0x6159,1,0x53)\
	ROM_FILL(0x615A,1,0x45)\
    ROM_FILL(0x615B,1,0x20)\
	ROM_FILL(0x615C,1,0x4D)\
	ROM_FILL(0x615D,1,0x45)\
	ROM_FILL(0x615E,1,0x4E)\
	ROM_FILL(0x615F,1,0x55)\
    ROM_FILL(0x6160,1,0x20)\
    ROM_FILL(0x6161,1,0x28)\
    ROM_FILL(0x6162,1,0x49)\
    ROM_FILL(0x6163,1,0x4E)\
    ROM_FILL(0x6164,1,0x2D)\
	ROM_FILL(0x6165,1,0x50)\
	ROM_FILL(0x6166,1,0x41)\
	ROM_FILL(0x6167,1,0x55)\
	ROM_FILL(0x6168,1,0x53)\
	ROM_FILL(0x6169,1,0x45)\
	ROM_FILL(0x616A,1,0x29)\
    ROM_FILL(0x616B,1,0x00)\
	ROM_FILL(0x616C,1,0x53)\
	ROM_FILL(0x616D,1,0x45)\
    ROM_FILL(0x616E,1,0x54)\
    ROM_FILL(0x616F,1,0x20)\
	ROM_FILL(0x6170,1,0x44)\
	ROM_FILL(0x6171,1,0x45)\
    ROM_FILL(0x6172,1,0x42)\
    ROM_FILL(0x6173,1,0x55)\
    ROM_FILL(0x6174,1,0x47)\
    ROM_FILL(0x6175,1,0x20)\
    ROM_FILL(0x6176,1,0x44)\
	ROM_FILL(0x6177,1,0x49)\
    ROM_FILL(0x6178,1,0x50)\
    ROM_FILL(0x6179,1,0x00)\
    ROM_FILL(0x617A,1,0x53)\
	ROM_FILL(0x617B,1,0x54)\
    ROM_FILL(0x617C,1,0x41)\
	ROM_FILL(0x617D,1,0x47)\
    ROM_FILL(0x617E,1,0x45)\
	ROM_FILL(0x617F,1,0x20)\
	ROM_FILL(0x6180,1,0x53)\
    ROM_FILL(0x6181,1,0x45)\
    ROM_FILL(0x6182,1,0x4C)\
    ROM_FILL(0x6183,1,0x45)\
    ROM_FILL(0x6184,1,0x43)\
    ROM_FILL(0x6185,1,0x54)\
	ROM_FILL(0x6186,1,0x00)\
	ROM_FILL(0x6187,1,0x54)\
	ROM_FILL(0x6188,1,0x45)\
	ROM_FILL(0x6189,1,0x53)\
	ROM_FILL(0x618A,1,0x54)\
	ROM_FILL(0x618B,1,0x20)\
    ROM_FILL(0x618C,1,0x53)\
	ROM_FILL(0x618D,1,0x54)\
    ROM_FILL(0x618E,1,0x41)\
    ROM_FILL(0x618F,1,0x47)\
    ROM_FILL(0x6190,1,0x45)\
	ROM_FILL(0x6191,1,0x20)\
	ROM_FILL(0x6192,1,0x00)\
    ROM_FILL(0x6193,1,0x53)\
    ROM_FILL(0x6194,1,0x4F)\
    ROM_FILL(0x6195,1,0x55)\
    ROM_FILL(0x6196,1,0x4E)\
    ROM_FILL(0x6197,1,0x44)\
	ROM_FILL(0x6198,1,0x20)\
    ROM_FILL(0x6199,1,0x54)\
    ROM_FILL(0x619A,1,0x45)\
    ROM_FILL(0x619B,1,0x53)\
	ROM_FILL(0x619C,1,0x54)\
    ROM_FILL(0x619D,1,0x00)\
	ROM_FILL(0x619E,1,0x52)\
    ROM_FILL(0x619F,1,0x45)\
	ROM_FILL(0x61A0,1,0x53)\
	ROM_FILL(0x61A1,1,0x45)\
    ROM_FILL(0x61A2,1,0x54)\
    ROM_FILL(0x61A3,1,0x00)\
	ROM_FILL(0x61A4,1,0x00)\
    ROM_FILL(0x61A5,1,0x00)\
    ROM_FILL(0x61A6,1,0x00)\
    ROM_FILL(0x61A7,1,0x00)\
	ROM_FILL(0x61A8,1,0x00)\
	ROM_FILL(0x61A9,1,0x00)\
	ROM_FILL(0x61AA,1,0x00)\
    ROM_FILL(0x61AB,1,0x00)\
    ROM_FILL(0x61AC,1,0x00)\
	ROM_FILL(0x61CB,1,0x6C)\
	ROM_FILL(0x61D5,1,0x7A)\
    ROM_FILL(0x61DF,1,0x87)\
    ROM_FILL(0x61E9,1,0x93)\
    ROM_FILL(0x61F3,1,0x9E)\
    ROM_FILL(0x67BF,1,0x6C)\
	ROM_FILL(0x635B,1,0x7A)\
    ROM_FILL(0x655B,1,0x7A)\
	ROM_FILL(0x6658,1,0x49)\
    ROM_FILL(0x6659,1,0x4E)\
    ROM_FILL(0x665A,1,0x56)\
	ROM_FILL(0x665B,1,0x49)\
	ROM_FILL(0x665C,1,0x4E)\
    ROM_FILL(0x665D,1,0x43)\
    ROM_FILL(0x665E,1,0x49)\
    ROM_FILL(0x665F,1,0x42)\
    ROM_FILL(0x6660,1,0x49)\
    ROM_FILL(0x6661,1,0x4C)\
	ROM_FILL(0x6662,1,0x49)\
    ROM_FILL(0x6663,1,0x54)\
    ROM_FILL(0x6664,1,0x59)\
    ROM_FILL(0x6665,1,0x20)\
	ROM_FILL(0x6686,1,0x41)\
    ROM_FILL(0x6687,1,0x4E)\
	ROM_FILL(0x6688,1,0x59)\
    ROM_FILL(0x6689,1,0x54)\
	ROM_FILL(0x668A,1,0x49)\
	ROM_FILL(0x668B,1,0x4D)\
    ROM_FILL(0x668C,1,0x45)\
    ROM_FILL(0x668D,1,0x20)\
    ROM_FILL(0x668E,1,0x50)\
    ROM_FILL(0x668F,1,0x41)\
    ROM_FILL(0x6690,1,0x55)\
	ROM_FILL(0x6691,1,0x53)\
	ROM_FILL(0x6692,1,0x45)\
	ROM_FILL(0x6693,1,0x20)\
	ROM_FILL(0x6710,1,0x49)\
	ROM_FILL(0x6711,1,0x4E)\
	ROM_FILL(0x6712,1,0x46)\
    ROM_FILL(0x6713,1,0x49)\
	ROM_FILL(0x6714,1,0x4E)\
    ROM_FILL(0x6715,1,0x49)\
    ROM_FILL(0x6716,1,0x54)\
    ROM_FILL(0x6717,1,0x45)\
	ROM_FILL(0x6718,1,0x20)\
	ROM_FILL(0x6719,1,0x41)\
    ROM_FILL(0x671A,1,0x4D)\
    ROM_FILL(0x671B,1,0x4D)\
    ROM_FILL(0x671C,1,0x4F)\
    ROM_FILL(0x671D,1,0x20)\
    ROM_FILL(0x6726,1,0x00)\
	ROM_FILL(0x6727,1,0x49)\
    ROM_FILL(0x6728,1,0x4E)\
    ROM_FILL(0x6729,1,0x46)\
    ROM_FILL(0x672A,1,0x49)\
	ROM_FILL(0x672B,1,0x4E)\
    ROM_FILL(0x672C,1,0x49)\
	ROM_FILL(0x672D,1,0x54)\
    ROM_FILL(0x672E,1,0x45)\
	ROM_FILL(0x672F,1,0x20)\
	ROM_FILL(0x6730,1,0x42)\
    ROM_FILL(0x6731,1,0x4F)\
    ROM_FILL(0x6732,1,0x4D)\
	ROM_FILL(0x6733,1,0x42)\
    ROM_FILL(0x6734,1,0x20)\
    ROM_FILL(0x6735,1,0x20)\
    ROM_FILL(0x673E,1,0x44)\
	ROM_FILL(0x673F,1,0x2D)\
	ROM_FILL(0x6740,1,0x42)\
	ROM_FILL(0x6741,1,0x55)\
    ROM_FILL(0x6742,1,0x54)\
    ROM_FILL(0x6743,1,0x54)\
	ROM_FILL(0x6744,1,0x4F)\
	ROM_FILL(0x6745,1,0x4E)\
    ROM_FILL(0x6746,1,0x20)\
    ROM_FILL(0x6747,1,0x57)\
    ROM_FILL(0x6748,1,0x49)\
    ROM_FILL(0x6749,1,0x50)\
    ROM_FILL(0x674A,1,0x45)\
	ROM_FILL(0x674B,1,0x4F)\
    ROM_FILL(0x674C,1,0x55)\
    ROM_FILL(0x674D,1,0x54)\
    ROM_FILL(0x674E,1,0x20)\
	ROM_FILL(0x675A,1,0x52)\
    ROM_FILL(0x675B,1,0x45)\
	ROM_FILL(0x675C,1,0x53)\
    ROM_FILL(0x675D,1,0x50)\
	ROM_FILL(0x675E,1,0x41)\
	ROM_FILL(0x675F,1,0x57)\
    ROM_FILL(0x6760,1,0x4E)\
    ROM_FILL(0x6761,1,0x20)\
    ROM_FILL(0x6762,1,0x53)\
    ROM_FILL(0x6763,1,0x50)\
    ROM_FILL(0x6764,1,0x4F)\
	ROM_FILL(0x6765,1,0x54)\
	ROM_FILL(0x6766,1,0x20)\
	ROM_FILL(0x676C,1,0x44)\
	ROM_FILL(0x676D,1,0x49)\
	ROM_FILL(0x676E,1,0x53)\
	ROM_FILL(0x676F,1,0x41)\
    ROM_FILL(0x6770,1,0x42)\
	ROM_FILL(0x6771,1,0x4C)\
    ROM_FILL(0x6772,1,0x45)\
    ROM_FILL(0x6773,1,0x20)\
    ROM_FILL(0x6774,1,0x50)\
	ROM_FILL(0x6775,1,0x41)\
	ROM_FILL(0x6776,1,0x55)\
    ROM_FILL(0x6777,1,0x53)\
    ROM_FILL(0x6778,1,0x45)\
    ROM_FILL(0x6779,1,0x20)\
    ROM_FILL(0x677A,1,0x20)\
    ROM_FILL(0x677B,1,0x20)\
	ROM_FILL(0x677C,1,0x20)\
	ROM_FILL(0x679E,1,0x20)\
    ROM_FILL(0x679F,1,0x50)\
    ROM_FILL(0x67A0,1,0x41)\
	ROM_FILL(0x67A1,1,0x4C)\
    ROM_FILL(0x67A2,1,0x45)\
	ROM_FILL(0x67A3,1,0x54)\
    ROM_FILL(0x67A4,1,0x54)\
	ROM_FILL(0x67A5,1,0x45)\
	ROM_FILL(0x67A6,1,0x2D)\
    ROM_FILL(0x67A7,1,0x4F)\
    ROM_FILL(0x67A8,1,0x56)\
    ROM_FILL(0x67A9,1,0x45)\
    ROM_FILL(0x67AA,1,0x52)\
	ROM_FILL(0x67AB,1,0x20)\
	ROM_FILL(0x67AC,1,0x20)

#define MSLUG3H_MVS_FILL \
    ROM_FILL(0x2EA4,1,0x63)\
    ROM_FILL(0x2EA7,1,0x58)\
	ROM_FILL(0x2EAE,1,0x12)\
	ROM_FILL(0x2EAF,1,0x12)\
	ROM_FILL(0x2EAB,1,0x34)\
	ROM_FILL(0x2EA8,1,0x34)\
	ROM_FILL(0x2EAD,1,0x23)

#define MSLUG3B6_MVS_FILL \
	ROM_FILL(0x2EA4,1,0x63)\
    ROM_FILL(0x2EA7,1,0x58)\
	ROM_FILL(0x2EAE,1,0x12)\
	ROM_FILL(0x2EAB,1,0x34)\
	ROM_FILL(0x2EA8,1,0x34)\
	ROM_FILL(0x2EAD,1,0x23)

#define MSLUG3SC_MVS_FILL \
    ROM_FILL(0x2EA7,1,0x58)\
	ROM_FILL(0x2EAE,1,0x12)\
	ROM_FILL(0x2EAF,1,0x12)\
	ROM_FILL(0x2EAB,1,0x34)\
	ROM_FILL(0x2EA8,1,0x34)\
	ROM_FILL(0x2EAD,1,0x23)

#define MSLUG3H_AES_FIX_FILL \
    ROM_FILL(0x2BD7B,1,0x53)\
    ROM_FILL(0x2BD7C,1,0x50)\
    ROM_FILL(0x2BD7D,1,0x45)\
	ROM_FILL(0x2BD7E,1,0x43)\
	ROM_FILL(0x2BD7F,1,0x49)\
    ROM_FILL(0x2BD80,1,0x41)\
    ROM_FILL(0x2BD81,1,0x4C)\
    ROM_FILL(0x2BD82,1,0x20)\
    ROM_FILL(0x2BD83,1,0x41)\
    ROM_FILL(0x2BD84,1,0x54)\
	ROM_FILL(0x2BD85,1,0x54)\
    ROM_FILL(0x2BD86,1,0x41)\
    ROM_FILL(0x2BD87,1,0x43)\
    ROM_FILL(0x2BD88,1,0x4B)\
	ROM_FILL(0x2BD89,1,0x20)\
	ROM_FILL(0x2BC64,1,0x03)\
    ROM_FILL(0x2BC65,1,0x05)\
    ROM_FILL(0x2BC66,1,0x07)\
    ROM_FILL(0x2BC81,1,0x02)\
	ROM_FILL(0x2BC83,1,0x03)

#define MSLUG3DD_AES_FIX_FILL \
    ROM_FILL(0x2BD7B,1,0x53)\
    ROM_FILL(0x2BD7C,1,0x50)\
    ROM_FILL(0x2BD7D,1,0x45)\
	ROM_FILL(0x2BD7E,1,0x43)\
	ROM_FILL(0x2BD7F,1,0x49)\
    ROM_FILL(0x2BD80,1,0x41)\
    ROM_FILL(0x2BD81,1,0x4C)\
    ROM_FILL(0x2BD82,1,0x20)\
    ROM_FILL(0x2BD83,1,0x41)\
    ROM_FILL(0x2BD84,1,0x54)\
	ROM_FILL(0x2BD85,1,0x54)\
    ROM_FILL(0x2BD86,1,0x41)\
    ROM_FILL(0x2BD87,1,0x43)\
    ROM_FILL(0x2BD88,1,0x4B)\
	ROM_FILL(0x2BD89,1,0x20)\
	ROM_FILL(0x2BC64,1,0x03)\
    ROM_FILL(0x2BC65,1,0x05)\
    ROM_FILL(0x2BC66,1,0x07)\
    ROM_FILL(0x2BC81,1,0x02)\
	ROM_FILL(0x2BC83,1,0x03)\
	ROM_FILL(0x2BC6E,1,0x03)\
    ROM_FILL(0x2BC6F,1,0x05)\
    ROM_FILL(0x2BC70,1,0x07)\
    ROM_FILL(0x2BC8B,1,0x02)\
	ROM_FILL(0x2BC8D,1,0x03)

#define MSLUG3H_AES_FILL \
	ROM_FILL(0x27C6,1,0x99)\
	ROM_FILL(0x27C7,1,0x99)\
	ROM_FILL(0x6058,1,0x60)

#define MSLUG4_SKIPLEVEL6_FIX_FILL \
	ROM_FILL(0xEABCB,1,0x03)

#define MSLUG4_CHANGEMOVINGPLAYERS_MODS_FILL \
	ROM_FILL(0xC5A95,1,0x03)\
	ROM_FILL(0xC5AA5,1,0x04)\
	ROM_FILL(0xC5572,1,0x02)\
	ROM_FILL(0xC5AB1,1,0x04)\
	ROM_FILL(0xC5ABD,1,0x0E)\
	ROM_FILL(0xC5AC1,1,0x06)\
	ROM_FILL(0xC5ACD,1,0x03)\
	ROM_FILL(0xC5ADD,1,0x04)\
	ROM_FILL(0xCC627,1,0x03)\
	ROM_FILL(0xCC6A3,1,0xFB)\
	ROM_FILL(0xCC80B,1,0xFC)\
	ROM_FILL(0xCC81F,1,0x03)\
	ROM_FILL(0xCC80C,1,0xA0)\
	ROM_FILL(0xCC820,1,0x60)

#define MSLUG4CQI_RESTORELVXCODE_MODS_FILL \
    ROM_FILL(0X601E1D,1,0x02)\
    ROM_FILL(0X601E2F,1,0x02)\
	ROM_FILL(0X601E41,1,0x02)\
	ROM_FILL(0X601E53,1,0x02)\
    ROM_FILL(0X6466D0,1,0x08)\
    ROM_FILL(0X6466D1,1,0x39)

#define MSLUG4_LIFEMORE_MODS_FILL \
    ROM_FILL(0x81B00,1,0x52)

#define MSLUG4_FIX_BLACK_BLOCK_ON_THE_SELECTION_SCREEN_MODS_FILL \
    ROM_FILL(0x118C68,1,0x1E)\
    ROM_FILL(0x118C69,1,0x10)\
    ROM_FILL(0x118C6A,1,0x15)\
	ROM_FILL(0x118C6B,1,0x40)\
	ROM_FILL(0x118C6C,1,0x1E)\
	ROM_FILL(0x118C6D,1,0x11)\
	ROM_FILL(0x118C6E,1,0x15)\
	ROM_FILL(0x118C6F,1,0x40)\
	ROM_FILL(0x118C70,1,0x1E)\
	ROM_FILL(0x118C71,1,0x12)\
	ROM_FILL(0x118C72,1,0x15)\
    ROM_FILL(0x118C73,1,0x40)\
    ROM_FILL(0x118C74,1,0x1E)\
    ROM_FILL(0x118C75,1,0x13)\
	ROM_FILL(0x118C76,1,0x15)\
	ROM_FILL(0x118C77,1,0x40)\
	ROM_FILL(0x118C78,1,0x1E)\
	ROM_FILL(0x118C79,1,0x14)\
	ROM_FILL(0x118C7A,1,0x15)\
	ROM_FILL(0x118C7B,1,0x40)\
	ROM_FILL(0x118C7C,1,0x1E)\
	ROM_FILL(0x118C7D,1,0x15)\
    ROM_FILL(0x118C7E,1,0x15)\
    ROM_FILL(0x118C7F,1,0x40)\
    ROM_FILL(0x118C80,1,0x1E)\
	ROM_FILL(0x118C81,1,0x16)\
	ROM_FILL(0x118C82,1,0x15)\
	ROM_FILL(0x118C83,1,0x40)\
	ROM_FILL(0x118C84,1,0x1E)\
	ROM_FILL(0x118C85,1,0x16)\
	ROM_FILL(0x118C86,1,0x15)\
	ROM_FILL(0x118C87,1,0x42)\
	ROM_FILL(0x118C88,1,0x1E)\
    ROM_FILL(0x118C89,1,0x15)\
	ROM_FILL(0x118C8A,1,0x15)\
	ROM_FILL(0x118C8B,1,0x42)\
	ROM_FILL(0x118C8C,1,0x1E)\
	ROM_FILL(0x118C8D,1,0x14)\
    ROM_FILL(0x118C8E,1,0x15)\
	ROM_FILL(0x118C8F,1,0x42)\
	ROM_FILL(0x118C90,1,0x1E)\
	ROM_FILL(0x118C91,1,0x13)\
	ROM_FILL(0x118C92,1,0x15)\
	ROM_FILL(0x118C93,1,0x42)\
	ROM_FILL(0x118C94,1,0x1E)\
	ROM_FILL(0x118C95,1,0x12)\
	ROM_FILL(0x118C96,1,0x15)\
	ROM_FILL(0x118C97,1,0x42)\
    ROM_FILL(0x118C98,1,0x1E)\
	ROM_FILL(0x118C99,1,0x11)\
	ROM_FILL(0x118C9A,1,0x15)\
	ROM_FILL(0x118C9B,1,0x42)\
	ROM_FILL(0x118C9C,1,0x1E)\
    ROM_FILL(0x118C9D,1,0x10)\
	ROM_FILL(0x118C9E,1,0x15)\
	ROM_FILL(0x118C9F,1,0x42)\

#define MSLUG4_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
    ROM_FILL(0xA81AA,1,0x49)\
    ROM_FILL(0xA81AB,1,0x4E)\
    ROM_FILL(0xA81AC,1,0x56)\
	ROM_FILL(0xA81AD,1,0x45)\
	ROM_FILL(0xA81AE,1,0x4E)\
    ROM_FILL(0xA81AF,1,0x54)\
    ROM_FILL(0xA81B0,1,0x4F)\
    ROM_FILL(0xA81B1,1,0x52)\
    ROM_FILL(0xA81B2,1,0x59)\
    ROM_FILL(0xA81B3,1,0x00)\
	ROM_FILL(0xA81B4,1,0x43)\
    ROM_FILL(0xA81B5,1,0x4C)\
    ROM_FILL(0xA81B6,1,0x4F)\
    ROM_FILL(0xA81B7,1,0x53)\
	ROM_FILL(0xA81B8,1,0x5C)\
    ROM_FILL(0xA81B9,1,0x45)\
	ROM_FILL(0xA81BA,1,0x20)\
	ROM_FILL(0xA81BB,1,0x4D)\
	ROM_FILL(0xA81BC,1,0x45)\
	ROM_FILL(0xA81BD,1,0x4E)\
    ROM_FILL(0xA81BE,1,0x55)\
    ROM_FILL(0xA81BF,1,0x20)\
    ROM_FILL(0xA81C0,1,0x28)\
    ROM_FILL(0xA81C1,1,0x49)\
    ROM_FILL(0xA81C2,1,0x4E)\
	ROM_FILL(0xA81C3,1,0x2D)\
	ROM_FILL(0xA81C4,1,0x50)\
	ROM_FILL(0xA81C5,1,0x41)\
	ROM_FILL(0xA81C6,1,0x55)\
	ROM_FILL(0xA81C7,1,0x53)\
	ROM_FILL(0xA81C8,1,0x45)\
    ROM_FILL(0xA81C9,1,0x29)\
	ROM_FILL(0xA81CA,1,0x00)\
    ROM_FILL(0xA81F2,1,0x53)\
    ROM_FILL(0xA81F3,1,0x4F)\
    ROM_FILL(0xA81F4,1,0x55)\
	ROM_FILL(0xA81F5,1,0x4E)\
	ROM_FILL(0xA81F6,1,0x44)\
	ROM_FILL(0xA81F7,1,0x20)\
	ROM_FILL(0xA81F8,1,0x54)\
	ROM_FILL(0xA81F9,1,0x45)\
	ROM_FILL(0xA81FA,1,0x53)\
    ROM_FILL(0xA81FB,1,0x54)\
	ROM_FILL(0xA81FC,1,0x00)\
	ROM_FILL(0xA8206,1,0x52)\
	ROM_FILL(0xA8207,1,0x45)\
	ROM_FILL(0xA8208,1,0x53)\
    ROM_FILL(0xA8209,1,0x45)\
	ROM_FILL(0xA820A,1,0x54)\
	ROM_FILL(0xA86B6,1,0x49)\
    ROM_FILL(0xA86B7,1,0x4E)\
    ROM_FILL(0xA86B8,1,0x56)\
	ROM_FILL(0xA86B9,1,0x49)\
	ROM_FILL(0xA86BA,1,0x4E)\
    ROM_FILL(0xA86BB,1,0x43)\
    ROM_FILL(0xA86BC,1,0x49)\
    ROM_FILL(0xA86BD,1,0x42)\
    ROM_FILL(0xA86BE,1,0x49)\
    ROM_FILL(0xA86BF,1,0x4C)\
	ROM_FILL(0xA86C0,1,0x49)\
    ROM_FILL(0xA86C1,1,0x54)\
    ROM_FILL(0xA86C2,1,0x59)\
    ROM_FILL(0xA86C3,1,0x20)\
    ROM_FILL(0xA86E4,1,0x41)\
    ROM_FILL(0xA86E5,1,0x4E)\
	ROM_FILL(0xA86E6,1,0x59)\
    ROM_FILL(0xA86E7,1,0x54)\
	ROM_FILL(0xA86E8,1,0x49)\
	ROM_FILL(0xA86E9,1,0x4D)\
    ROM_FILL(0xA86EA,1,0x45)\
    ROM_FILL(0xA86EB,1,0x20)\
    ROM_FILL(0xA86EC,1,0x50)\
    ROM_FILL(0xA86ED,1,0x41)\
    ROM_FILL(0xA86EE,1,0x55)\
	ROM_FILL(0xA86EF,1,0x53)\
	ROM_FILL(0xA86F0,1,0x45)\
	ROM_FILL(0xA86F1,1,0x20)\
    ROM_FILL(0xA876E,1,0x49)\
	ROM_FILL(0xA876F,1,0x4E)\
	ROM_FILL(0xA8770,1,0x46)\
    ROM_FILL(0xA8771,1,0x49)\
	ROM_FILL(0xA8772,1,0x4E)\
    ROM_FILL(0xA8773,1,0x49)\
    ROM_FILL(0xA8774,1,0x54)\
    ROM_FILL(0xA8775,1,0x45)\
	ROM_FILL(0xA8776,1,0x20)\
	ROM_FILL(0xA8777,1,0x41)\
    ROM_FILL(0xA8778,1,0x4D)\
    ROM_FILL(0xA8779,1,0x4D)\
    ROM_FILL(0xA877A,1,0x4F)\
    ROM_FILL(0xA877B,1,0x20)\
    ROM_FILL(0xA8784,1,0x00)\
	ROM_FILL(0xA8785,1,0x49)\
    ROM_FILL(0xA8786,1,0x4E)\
    ROM_FILL(0xA8787,1,0x46)\
    ROM_FILL(0xA8788,1,0x49)\
	ROM_FILL(0xA8789,1,0x4E)\
    ROM_FILL(0xA878A,1,0x49)\
	ROM_FILL(0xA878B,1,0x54)\
    ROM_FILL(0xA878C,1,0x45)\
	ROM_FILL(0xA878D,1,0x20)\
	ROM_FILL(0xA878E,1,0x42)\
    ROM_FILL(0xA878F,1,0x4F)\
    ROM_FILL(0xA8790,1,0x4D)\
	ROM_FILL(0xA8791,1,0x42)\
    ROM_FILL(0xA8792,1,0x20)\
    ROM_FILL(0xA8793,1,0x20)\
    ROM_FILL(0xA879C,1,0x44)\
	ROM_FILL(0xA879D,1,0x2D)\
	ROM_FILL(0xA879E,1,0x42)\
	ROM_FILL(0xA879F,1,0x55)\
    ROM_FILL(0xA87A0,1,0x54)\
    ROM_FILL(0xA87A1,1,0x54)\
	ROM_FILL(0xA87A2,1,0x4F)\
	ROM_FILL(0xA87A3,1,0x4E)\
    ROM_FILL(0xA87A4,1,0x20)\
    ROM_FILL(0xA87A5,1,0x57)\
    ROM_FILL(0xA87A6,1,0x49)\
    ROM_FILL(0xA87A7,1,0x50)\
    ROM_FILL(0xA87A8,1,0x45)\
	ROM_FILL(0xA87A9,1,0x4F)\
    ROM_FILL(0xA87AA,1,0x55)\
    ROM_FILL(0xA87AB,1,0x54)\
    ROM_FILL(0xA87AC,1,0x20)\
    ROM_FILL(0xA87B8,1,0x52)\
    ROM_FILL(0xA87B9,1,0x45)\
	ROM_FILL(0xA87BA,1,0x53)\
    ROM_FILL(0xA87BB,1,0x50)\
	ROM_FILL(0xA87BC,1,0x41)\
	ROM_FILL(0xA87BD,1,0x57)\
    ROM_FILL(0xA87BE,1,0x4E)\
    ROM_FILL(0xA87BF,1,0x20)\
    ROM_FILL(0xA87C0,1,0x53)\
    ROM_FILL(0xA87C1,1,0x50)\
    ROM_FILL(0xA87C2,1,0x4F)\
	ROM_FILL(0xA87C3,1,0x54)\
	ROM_FILL(0xA87C4,1,0x20)\
	ROM_FILL(0xA87CA,1,0x44)\
	ROM_FILL(0xA87CB,1,0x49)\
	ROM_FILL(0xA87CC,1,0x53)\
	ROM_FILL(0xA87CD,1,0x41)\
    ROM_FILL(0xA87CE,1,0x42)\
	ROM_FILL(0xA87CF,1,0x4C)\
    ROM_FILL(0xA87D0,1,0x45)\
    ROM_FILL(0xA87D1,1,0x20)\
    ROM_FILL(0xA87D2,1,0x50)\
	ROM_FILL(0xA87D3,1,0x41)\
	ROM_FILL(0xA87D4,1,0x55)\
    ROM_FILL(0xA87D5,1,0x53)\
    ROM_FILL(0xA87D6,1,0x45)\
    ROM_FILL(0xA87D7,1,0x20)\
    ROM_FILL(0xA87D8,1,0x20)\
    ROM_FILL(0xA87D9,1,0x20)\
	ROM_FILL(0xA87DA,1,0x20)\
    ROM_FILL(0xA87FC,1,0x20)\
    ROM_FILL(0xA87FD,1,0x50)\
    ROM_FILL(0xA87FE,1,0x41)\
	ROM_FILL(0xA87FF,1,0x4C)\
    ROM_FILL(0xA8800,1,0x45)\
	ROM_FILL(0xA8801,1,0x54)\
    ROM_FILL(0xA8802,1,0x54)\
	ROM_FILL(0xA8803,1,0x45)\
	ROM_FILL(0xA8804,1,0x2D)\
    ROM_FILL(0xA8805,1,0x4F)\
    ROM_FILL(0xA8806,1,0x56)\
    ROM_FILL(0xA8807,1,0x45)\
    ROM_FILL(0xA8808,1,0x52)\
	ROM_FILL(0xA8809,1,0x20)\
	ROM_FILL(0xA880A,1,0x20)	

#define MSLUG4_FLASHOFF_MODS_FILL \
    ROM_FILL(0xA7530,1,0x4E)\
	ROM_FILL(0xA7531,1,0x71)\
	ROM_FILL(0xA7532,1,0x4E)\
	ROM_FILL(0xA7533,1,0x71)

#define MSLUG4H_FLASHOFF_MODS_FILL \
    ROM_FILL(0xA7ACA,1,0x4E)\
	ROM_FILL(0xA7ACB,1,0x71)\
	ROM_FILL(0xA7ACC,1,0x4E)\
	ROM_FILL(0xA7ACD,1,0x71)\

#define MSLUG4ND_MVS_FILL \
	ROM_FILL(0x173E,1,0x63)\
    ROM_FILL(0x1741,1,0x58)\
	ROM_FILL(0x1748,1,0x12)\
	ROM_FILL(0x1749,1,0x12)\
	ROM_FILL(0x1745,1,0x34)\
	ROM_FILL(0x1742,1,0x34)\
	ROM_FILL(0x1747,1,0x23)

#define MSLUG4_MVS_FILL \
	ROM_FILL(0x173E,1,0x63)\
    ROM_FILL(0x1741,1,0x58)\
	ROM_FILL(0x1748,1,0x12)\
	ROM_FILL(0x1745,1,0x34)\
	ROM_FILL(0x1742,1,0x34)\
	ROM_FILL(0x1747,1,0x23)

#define MSLUG4CQI_MVS_FILL \
    ROM_FILL(0x1741,1,0x58)\
	ROM_FILL(0x1748,1,0x12)\
	ROM_FILL(0x1749,1,0x12)\
	ROM_FILL(0x1745,1,0x34)\
	ROM_FILL(0x1742,1,0x34)\
	ROM_FILL(0x1747,1,0x23)

#define MSLUG4_AES_FIX_FILL \
    ROM_FILL(0xA2441,1,0x53)\
    ROM_FILL(0xA2442,1,0x50)\
    ROM_FILL(0xA2443,1,0x45)\
	ROM_FILL(0xA2444,1,0x43)\
	ROM_FILL(0xA2445,1,0x49)\
    ROM_FILL(0xA2446,1,0x41)\
    ROM_FILL(0xA2447,1,0x4C)\
    ROM_FILL(0xA2448,1,0x20)\
    ROM_FILL(0xA2449,1,0x41)\
    ROM_FILL(0xA244A,1,0x54)\
	ROM_FILL(0xA244B,1,0x54)\
    ROM_FILL(0xA244C,1,0x41)\
    ROM_FILL(0xA244D,1,0x43)\
    ROM_FILL(0xA244E,1,0x4B)\
	ROM_FILL(0xA244F,1,0x20)\
	ROM_FILL(0xA232A,1,0x03)\
    ROM_FILL(0xA232B,1,0x05)\
    ROM_FILL(0xA232C,1,0x07)\
    ROM_FILL(0xA2347,1,0x02)\
	ROM_FILL(0xA2349,1,0x03)

#define MSLUG4_AES_FILL \
	ROM_FILL(0x7FE,1,0x99)\
	ROM_FILL(0x7FF,1,0x99)

#define MSLUG4H_AES_FILL \
	ROM_FILL(0x7FE,1,0x99)\
	ROM_FILL(0x7FF,1,0x99)\
	ROM_FILL(0xA864C,1,0x60)

#define MSLUG5ZH_JUMPATLEVEL5X5_FIX_FILL \
	ROM_FILL(0xFB420,1,0x00)\
	ROM_FILL(0xFB421,1,0x06)

#define MSLUG5CQI_RESTORELVXCODE_MODS_FILL \
    ROM_FILL(0X2DEF6D,1,0x02)\
    ROM_FILL(0X2DEF7F,1,0x02)\
	ROM_FILL(0X2DEF91,1,0x02)\
	ROM_FILL(0X2DEFA3,1,0x02)\
    ROM_FILL(0X64A400,1,0x08)\
    ROM_FILL(0X64A401,1,0x39)

#define MSLUG5ND_LIFEMORE_MODS_FILL \
    ROM_FILL(0x4E90E,1,0x52)

#define MSLUG5_FLASHOFF_MODS_FILL \
    ROM_FILL(0x8724,1,0x7A)\
	ROM_FILL(0x8725,1,0x7A)\
	ROM_FILL(0x8726,1,0x99)\
	ROM_FILL(0x8727,1,0x9A)

#define MSLUG5ND_FLASHOFF_MODS_FILL \
    ROM_FILL(0x8724,1,0x4E)\
	ROM_FILL(0x8725,1,0x71)\
	ROM_FILL(0x8726,1,0x4E)\
	ROM_FILL(0x8727,1,0x71)	

#define MSLUG5ND_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
    ROM_FILL(0x937E,1,0x49)\
    ROM_FILL(0x937F,1,0x4E)\
    ROM_FILL(0x9380,1,0x56)\
	ROM_FILL(0x9381,1,0x45)\
	ROM_FILL(0x9382,1,0x4E)\
    ROM_FILL(0x9383,1,0x54)\
    ROM_FILL(0x9384,1,0x4F)\
    ROM_FILL(0x9385,1,0x52)\
    ROM_FILL(0x9386,1,0x59)\
    ROM_FILL(0x9387,1,0x00)\
	ROM_FILL(0x9388,1,0x43)\
    ROM_FILL(0x9389,1,0x4C)\
    ROM_FILL(0x938A,1,0x4F)\
    ROM_FILL(0x938B,1,0x53)\
	ROM_FILL(0x938C,1,0x5C)\
    ROM_FILL(0x938D,1,0x45)\
	ROM_FILL(0x938E,1,0x20)\
	ROM_FILL(0x938F,1,0x4D)\
	ROM_FILL(0x9390,1,0x45)\
	ROM_FILL(0x9391,1,0x4E)\
    ROM_FILL(0x9392,1,0x55)\
    ROM_FILL(0x9393,1,0x20)\
    ROM_FILL(0x9394,1,0x28)\
    ROM_FILL(0x9395,1,0x49)\
    ROM_FILL(0x9396,1,0x4E)\
	ROM_FILL(0x9397,1,0x2D)\
	ROM_FILL(0x9398,1,0x50)\
	ROM_FILL(0x9399,1,0x41)\
	ROM_FILL(0x939A,1,0x55)\
	ROM_FILL(0x939B,1,0x53)\
	ROM_FILL(0x939C,1,0x45)\
    ROM_FILL(0x939D,1,0x29)\
	ROM_FILL(0x939E,1,0x00)\
    ROM_FILL(0x93C6,1,0x53)\
    ROM_FILL(0x93C7,1,0x4F)\
    ROM_FILL(0x93C8,1,0x55)\
	ROM_FILL(0x93C9,1,0x4E)\
	ROM_FILL(0x93CA,1,0x44)\
	ROM_FILL(0x93CB,1,0x20)\
	ROM_FILL(0x93CC,1,0x54)\
	ROM_FILL(0x93CD,1,0x45)\
	ROM_FILL(0x93CE,1,0x53)\
    ROM_FILL(0x93CF,1,0x54)\
	ROM_FILL(0x93D0,1,0x00)\
	ROM_FILL(0x93DA,1,0x52)\
	ROM_FILL(0x93DB,1,0x45)\
	ROM_FILL(0x93DC,1,0x53)\
    ROM_FILL(0x93DD,1,0x45)\
	ROM_FILL(0x93DE,1,0x54)\
	ROM_FILL(0x988A,1,0x49)\
    ROM_FILL(0x988B,1,0x4E)\
    ROM_FILL(0x988C,1,0x56)\
	ROM_FILL(0x988D,1,0x49)\
	ROM_FILL(0x988E,1,0x4E)\
    ROM_FILL(0x988F,1,0x43)\
    ROM_FILL(0x9890,1,0x49)\
    ROM_FILL(0x9891,1,0x42)\
    ROM_FILL(0x9892,1,0x49)\
    ROM_FILL(0x9893,1,0x4C)\
	ROM_FILL(0x9894,1,0x49)\
    ROM_FILL(0x9895,1,0x54)\
    ROM_FILL(0x9896,1,0x59)\
    ROM_FILL(0x9897,1,0x20)\
    ROM_FILL(0x98B8,1,0x41)\
    ROM_FILL(0x98B9,1,0x4E)\
	ROM_FILL(0x98BA,1,0x59)\
    ROM_FILL(0x98BB,1,0x54)\
	ROM_FILL(0x98BC,1,0x49)\
	ROM_FILL(0x98BD,1,0x4D)\
    ROM_FILL(0x98BE,1,0x45)\
    ROM_FILL(0x98BF,1,0x20)\
    ROM_FILL(0x98C0,1,0x50)\
    ROM_FILL(0x98C1,1,0x41)\
    ROM_FILL(0x98C2,1,0x55)\
	ROM_FILL(0x98C3,1,0x53)\
	ROM_FILL(0x98C4,1,0x45)\
	ROM_FILL(0x98C5,1,0x20)\
    ROM_FILL(0x9942,1,0x49)\
	ROM_FILL(0x9943,1,0x4E)\
	ROM_FILL(0x9944,1,0x46)\
    ROM_FILL(0x9945,1,0x49)\
	ROM_FILL(0x9946,1,0x4E)\
    ROM_FILL(0x9947,1,0x49)\
    ROM_FILL(0x9948,1,0x54)\
    ROM_FILL(0x9949,1,0x45)\
	ROM_FILL(0x994A,1,0x20)\
	ROM_FILL(0x994B,1,0x41)\
    ROM_FILL(0x994C,1,0x4D)\
    ROM_FILL(0x994D,1,0x4D)\
    ROM_FILL(0x994E,1,0x4F)\
    ROM_FILL(0x994F,1,0x20)\
    ROM_FILL(0x9958,1,0x00)\
	ROM_FILL(0x9959,1,0x49)\
    ROM_FILL(0x995A,1,0x4E)\
    ROM_FILL(0x995B,1,0x46)\
    ROM_FILL(0x995C,1,0x49)\
	ROM_FILL(0x995D,1,0x4E)\
    ROM_FILL(0x995E,1,0x49)\
	ROM_FILL(0x995F,1,0x54)\
    ROM_FILL(0x9960,1,0x45)\
	ROM_FILL(0x9961,1,0x20)\
	ROM_FILL(0x9962,1,0x42)\
    ROM_FILL(0x9963,1,0x4F)\
    ROM_FILL(0x9964,1,0x4D)\
	ROM_FILL(0x9965,1,0x42)\
    ROM_FILL(0x9966,1,0x20)\
    ROM_FILL(0x9967,1,0x20)\
    ROM_FILL(0x9970,1,0x44)\
	ROM_FILL(0x9971,1,0x2D)\
	ROM_FILL(0x9972,1,0x42)\
	ROM_FILL(0x9973,1,0x55)\
    ROM_FILL(0x9974,1,0x54)\
    ROM_FILL(0x9975,1,0x54)\
	ROM_FILL(0x9976,1,0x4F)\
	ROM_FILL(0x9977,1,0x4E)\
    ROM_FILL(0x9978,1,0x20)\
    ROM_FILL(0x9979,1,0x57)\
    ROM_FILL(0x997A,1,0x49)\
    ROM_FILL(0x997B,1,0x50)\
    ROM_FILL(0x997C,1,0x45)\
	ROM_FILL(0x997D,1,0x4F)\
    ROM_FILL(0x997E,1,0x55)\
    ROM_FILL(0x997F,1,0x54)\
    ROM_FILL(0x9980,1,0x20)\
    ROM_FILL(0x998C,1,0x52)\
    ROM_FILL(0x998D,1,0x45)\
	ROM_FILL(0x998E,1,0x53)\
    ROM_FILL(0x998F,1,0x50)\
	ROM_FILL(0x9990,1,0x41)\
	ROM_FILL(0x9991,1,0x57)\
    ROM_FILL(0x9992,1,0x4E)\
    ROM_FILL(0x9993,1,0x20)\
    ROM_FILL(0x9994,1,0x53)\
    ROM_FILL(0x9995,1,0x50)\
    ROM_FILL(0x9996,1,0x4F)\
	ROM_FILL(0x9997,1,0x54)\
	ROM_FILL(0x9998,1,0x20)\
	ROM_FILL(0x999E,1,0x44)\
	ROM_FILL(0x999F,1,0x49)\
	ROM_FILL(0x99A0,1,0x53)\
	ROM_FILL(0x99A1,1,0x41)\
    ROM_FILL(0x99A2,1,0x42)\
	ROM_FILL(0x99A3,1,0x4C)\
    ROM_FILL(0x99A4,1,0x45)\
    ROM_FILL(0x99A5,1,0x20)\
    ROM_FILL(0x99A6,1,0x50)\
	ROM_FILL(0x99A7,1,0x41)\
	ROM_FILL(0x99A8,1,0x55)\
    ROM_FILL(0x99A9,1,0x53)\
    ROM_FILL(0x99AA,1,0x45)\
    ROM_FILL(0x99AB,1,0x20)\
    ROM_FILL(0x99AC,1,0x20)\
    ROM_FILL(0x99AD,1,0x20)\
	ROM_FILL(0x99AE,1,0x20)\
    ROM_FILL(0x99D0,1,0x20)\
    ROM_FILL(0x99D1,1,0x50)\
    ROM_FILL(0x99D2,1,0x41)\
	ROM_FILL(0x99D3,1,0x4C)\
    ROM_FILL(0x99D4,1,0x45)\
	ROM_FILL(0x99D5,1,0x54)\
    ROM_FILL(0x99D6,1,0x54)\
	ROM_FILL(0x99D7,1,0x45)\
	ROM_FILL(0x99D8,1,0x2D)\
    ROM_FILL(0x99D9,1,0x4F)\
    ROM_FILL(0x99DA,1,0x56)\
    ROM_FILL(0x99DB,1,0x45)\
    ROM_FILL(0x99DC,1,0x52)\
	ROM_FILL(0x99DD,1,0x20)\
	ROM_FILL(0x99DE,1,0x20)

#define MSLUG5HDD_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
    ROM_FILL(0x9382,1,0x49)\
    ROM_FILL(0x9383,1,0x4E)\
    ROM_FILL(0x9384,1,0x56)\
	ROM_FILL(0x9385,1,0x45)\
	ROM_FILL(0x9386,1,0x4E)\
    ROM_FILL(0x9387,1,0x54)\
    ROM_FILL(0x9388,1,0x4F)\
    ROM_FILL(0x9389,1,0x52)\
    ROM_FILL(0x938A,1,0x59)\
    ROM_FILL(0x938B,1,0x00)\
	ROM_FILL(0x938C,1,0x43)\
    ROM_FILL(0x938D,1,0x4C)\
    ROM_FILL(0x938E,1,0x4F)\
    ROM_FILL(0x938F,1,0x53)\
	ROM_FILL(0x9390,1,0x5C)\
    ROM_FILL(0x9391,1,0x45)\
	ROM_FILL(0x9392,1,0x20)\
	ROM_FILL(0x9393,1,0x4D)\
	ROM_FILL(0x9394,1,0x45)\
	ROM_FILL(0x9395,1,0x4E)\
    ROM_FILL(0x9396,1,0x55)\
    ROM_FILL(0x9397,1,0x20)\
    ROM_FILL(0x9398,1,0x28)\
    ROM_FILL(0x9399,1,0x49)\
    ROM_FILL(0x939A,1,0x4E)\
	ROM_FILL(0x939B,1,0x2D)\
	ROM_FILL(0x939C,1,0x50)\
	ROM_FILL(0x939D,1,0x41)\
	ROM_FILL(0x939E,1,0x55)\
	ROM_FILL(0x939F,1,0x53)\
	ROM_FILL(0x93A0,1,0x45)\
    ROM_FILL(0x93A1,1,0x29)\
	ROM_FILL(0x93A2,1,0x00)\
    ROM_FILL(0x93CA,1,0x53)\
    ROM_FILL(0x93CB,1,0x4F)\
    ROM_FILL(0x93CC,1,0x55)\
	ROM_FILL(0x93CD,1,0x4E)\
	ROM_FILL(0x93CE,1,0x44)\
	ROM_FILL(0x93CF,1,0x20)\
	ROM_FILL(0x93D0,1,0x54)\
	ROM_FILL(0x93D1,1,0x45)\
	ROM_FILL(0x93D2,1,0x53)\
    ROM_FILL(0x93D3,1,0x54)\
	ROM_FILL(0x93D4,1,0x00)\
	ROM_FILL(0x93DE,1,0x52)\
	ROM_FILL(0x93DF,1,0x45)\
	ROM_FILL(0x93E0,1,0x53)\
	ROM_FILL(0x93E1,1,0x45)\
    ROM_FILL(0x93E2,1,0x54)\
	ROM_FILL(0x988E,1,0x49)\
    ROM_FILL(0x988F,1,0x4E)\
    ROM_FILL(0x9890,1,0x56)\
	ROM_FILL(0x9891,1,0x49)\
	ROM_FILL(0x9892,1,0x4E)\
    ROM_FILL(0x9893,1,0x43)\
    ROM_FILL(0x9894,1,0x49)\
    ROM_FILL(0x9895,1,0x42)\
    ROM_FILL(0x9896,1,0x49)\
    ROM_FILL(0x9897,1,0x4C)\
	ROM_FILL(0x9898,1,0x49)\
    ROM_FILL(0x9899,1,0x54)\
    ROM_FILL(0x989A,1,0x59)\
    ROM_FILL(0x989B,1,0x20)\
    ROM_FILL(0x98BC,1,0x41)\
    ROM_FILL(0x98BD,1,0x4E)\
	ROM_FILL(0x98BE,1,0x59)\
    ROM_FILL(0x98BF,1,0x54)\
	ROM_FILL(0x98C0,1,0x49)\
	ROM_FILL(0x98C1,1,0x4D)\
    ROM_FILL(0x98C2,1,0x45)\
    ROM_FILL(0x98C3,1,0x20)\
    ROM_FILL(0x98C4,1,0x50)\
    ROM_FILL(0x98C5,1,0x41)\
    ROM_FILL(0x98C6,1,0x55)\
	ROM_FILL(0x98C7,1,0x53)\
	ROM_FILL(0x98C8,1,0x45)\
	ROM_FILL(0x98C9,1,0x20)\
    ROM_FILL(0x9946,1,0x49)\
	ROM_FILL(0x9947,1,0x4E)\
	ROM_FILL(0x9948,1,0x46)\
    ROM_FILL(0x9949,1,0x49)\
	ROM_FILL(0x994A,1,0x4E)\
    ROM_FILL(0x994B,1,0x49)\
    ROM_FILL(0x994C,1,0x54)\
    ROM_FILL(0x994D,1,0x45)\
	ROM_FILL(0x994E,1,0x20)\
	ROM_FILL(0x994F,1,0x41)\
    ROM_FILL(0x9950,1,0x4D)\
    ROM_FILL(0x9951,1,0x4D)\
    ROM_FILL(0x9952,1,0x4F)\
    ROM_FILL(0x9953,1,0x20)\
    ROM_FILL(0x995C,1,0x00)\
	ROM_FILL(0x995D,1,0x49)\
    ROM_FILL(0x995E,1,0x4E)\
    ROM_FILL(0x995F,1,0x46)\
    ROM_FILL(0x9960,1,0x49)\
	ROM_FILL(0x9961,1,0x4E)\
    ROM_FILL(0x9962,1,0x49)\
	ROM_FILL(0x9963,1,0x54)\
    ROM_FILL(0x9964,1,0x45)\
	ROM_FILL(0x9965,1,0x20)\
	ROM_FILL(0x9966,1,0x42)\
    ROM_FILL(0x9967,1,0x4F)\
    ROM_FILL(0x9968,1,0x4D)\
	ROM_FILL(0x9969,1,0x42)\
    ROM_FILL(0x996A,1,0x20)\
    ROM_FILL(0x996B,1,0x20)\
    ROM_FILL(0x9974,1,0x44)\
	ROM_FILL(0x9975,1,0x2D)\
	ROM_FILL(0x9976,1,0x42)\
	ROM_FILL(0x9977,1,0x55)\
    ROM_FILL(0x9978,1,0x54)\
    ROM_FILL(0x9979,1,0x54)\
	ROM_FILL(0x997A,1,0x4F)\
	ROM_FILL(0x997B,1,0x4E)\
    ROM_FILL(0x997C,1,0x20)\
    ROM_FILL(0x997D,1,0x57)\
    ROM_FILL(0x997E,1,0x49)\
    ROM_FILL(0x997F,1,0x50)\
    ROM_FILL(0x9980,1,0x45)\
	ROM_FILL(0x9981,1,0x4F)\
    ROM_FILL(0x9982,1,0x55)\
    ROM_FILL(0x9983,1,0x54)\
    ROM_FILL(0x9984,1,0x20)\
    ROM_FILL(0x9990,1,0x52)\
    ROM_FILL(0x9991,1,0x45)\
	ROM_FILL(0x9992,1,0x53)\
    ROM_FILL(0x9993,1,0x50)\
	ROM_FILL(0x9994,1,0x41)\
	ROM_FILL(0x9995,1,0x57)\
    ROM_FILL(0x9996,1,0x4E)\
    ROM_FILL(0x9997,1,0x20)\
    ROM_FILL(0x9998,1,0x53)\
    ROM_FILL(0x9999,1,0x50)\
    ROM_FILL(0x999A,1,0x4F)\
	ROM_FILL(0x999B,1,0x54)\
	ROM_FILL(0x999C,1,0x20)\
	ROM_FILL(0x99A2,1,0x44)\
	ROM_FILL(0x99A3,1,0x49)\
	ROM_FILL(0x99A4,1,0x53)\
	ROM_FILL(0x99A5,1,0x41)\
    ROM_FILL(0x99A6,1,0x42)\
	ROM_FILL(0x99A7,1,0x4C)\
    ROM_FILL(0x99A8,1,0x45)\
    ROM_FILL(0x99A9,1,0x20)\
    ROM_FILL(0x99AA,1,0x50)\
	ROM_FILL(0x99AB,1,0x41)\
	ROM_FILL(0x99AC,1,0x55)\
    ROM_FILL(0x99AD,1,0x53)\
    ROM_FILL(0x99AE,1,0x45)\
    ROM_FILL(0x99AF,1,0x20)\
    ROM_FILL(0x99B0,1,0x20)\
    ROM_FILL(0x99B1,1,0x20)\
	ROM_FILL(0x99B2,1,0x20)\
    ROM_FILL(0x99D4,1,0x20)\
    ROM_FILL(0x99D5,1,0x50)\
    ROM_FILL(0x99D6,1,0x41)\
	ROM_FILL(0x99D7,1,0x4C)\
    ROM_FILL(0x99D8,1,0x45)\
	ROM_FILL(0x99D9,1,0x54)\
    ROM_FILL(0x99DA,1,0x54)\
	ROM_FILL(0x99DB,1,0x45)\
	ROM_FILL(0x99DC,1,0x2D)\
    ROM_FILL(0x99DD,1,0x4F)\
    ROM_FILL(0x99DE,1,0x56)\
    ROM_FILL(0x99DF,1,0x45)\
    ROM_FILL(0x99C0,1,0x52)\
	ROM_FILL(0x99C1,1,0x20)\
	ROM_FILL(0x99C2,1,0x20)

#define MSLUG5_MVS_FILL \
	ROM_FILL(0x2CD0,1,0xDD)\
    ROM_FILL(0x2CD3,1,0x55)\
	ROM_FILL(0x2CD7,1,0x3B)\
	ROM_FILL(0x2CDA,1,0x8B)\
    ROM_FILL(0x2CD4,1,0x71)\
	ROM_FILL(0x2CDB,1,0x09)
//	ROM_FILL(0x2CD6,1,0x26)
//	ROM_FILL(0x2CD5,1,0x70)
//	ROM_FILL(0x2CD2,1,0x80)

#define MSLUG5ND_MVS_FILL \
	ROM_FILL(0x2CD0,1,0x63)\
    ROM_FILL(0x2CD3,1,0x58)\
	ROM_FILL(0x2CDA,1,0x12)\
	ROM_FILL(0x2CDB,1,0x12)\
	ROM_FILL(0x2CD7,1,0x34)\
	ROM_FILL(0x2CD4,1,0x34)\
	ROM_FILL(0x2CD9,1,0x23)

#define MSLUG5SC_MVS_FILL \
    ROM_FILL(0x2CD3,1,0x58)\
	ROM_FILL(0x2CDA,1,0x12)\
	ROM_FILL(0x2CDB,1,0x12)\
	ROM_FILL(0x2CD7,1,0x34)\
	ROM_FILL(0x2CD4,1,0x34)\
	ROM_FILL(0x2CD9,1,0x23)

#define MSLUG5_AES_FILL \
	ROM_FILL(0x84A,1,0x57)\
	ROM_FILL(0x84B,1,0x60)

#define MSLUG5H_AES_FILL \
	ROM_FILL(0x84A,1,0x57)\
	ROM_FILL(0x84B,1,0x60)\
	ROM_FILL(0x928E,1,0x49)

#define MSLUG5ND_AES_FILL \
	ROM_FILL(0x84A,1,0x99)\
	ROM_FILL(0x84B,1,0x99)

#define MSLUG5ND_AES_FIX_FILL \
    ROM_FILL(0xAD8D,1,0x53)\
    ROM_FILL(0xAD8E,1,0x50)\
    ROM_FILL(0xAD8F,1,0x45)\
	ROM_FILL(0xAD91,1,0x43)\
	ROM_FILL(0xAD92,1,0x49)\
    ROM_FILL(0xAD93,1,0x41)\
    ROM_FILL(0xAD94,1,0x4C)\
    ROM_FILL(0xAD95,1,0x20)\
    ROM_FILL(0xAD96,1,0x41)\
    ROM_FILL(0xAD97,1,0x54)\
	ROM_FILL(0xAD98,1,0x54)\
    ROM_FILL(0xAD99,1,0x41)\
    ROM_FILL(0xAD9A,1,0x43)\
    ROM_FILL(0xAD9B,1,0x4B)\
	ROM_FILL(0xAD9C,1,0x00)\
	ROM_FILL(0xAC76,1,0x03)\
    ROM_FILL(0xAC77,1,0x05)\
    ROM_FILL(0xAC78,1,0x07)\
    ROM_FILL(0xAC93,1,0x02)\
	ROM_FILL(0xAC95,1,0x03)

#define MSLUG5HDD_AES_FIX_FILL \
    ROM_FILL(0xAD91,1,0x53)\
    ROM_FILL(0xAD92,1,0x50)\
    ROM_FILL(0xAD93,1,0x45)\
	ROM_FILL(0xAD94,1,0x43)\
	ROM_FILL(0xAD95,1,0x49)\
    ROM_FILL(0xAD96,1,0x41)\
    ROM_FILL(0xAD97,1,0x4C)\
    ROM_FILL(0xAD98,1,0x20)\
    ROM_FILL(0xAD99,1,0x41)\
    ROM_FILL(0xAD9A,1,0x54)\
	ROM_FILL(0xAD9B,1,0x54)\
    ROM_FILL(0xAD9C,1,0x41)\
    ROM_FILL(0xAD9D,1,0x43)\
    ROM_FILL(0xAD9E,1,0x4B)\
	ROM_FILL(0xAD9F,1,0x00)\
	ROM_FILL(0xAC7A,1,0x03)\
    ROM_FILL(0xAC7B,1,0x05)\
    ROM_FILL(0xAC7C,1,0x07)\
    ROM_FILL(0xAC97,1,0x02)\
	ROM_FILL(0xAC99,1,0x03)

#define MSLUG5HDD_AES_FILL \
	ROM_FILL(0x84A,1,0x99)\
	ROM_FILL(0x84B,1,0x99)\
	ROM_FILL(0x928E,1,0x60)

#define MSLUGX_HELICOPTER_FIX_FILL \
	ROM_FILL(0x2DAD58,1,0x06)\
    ROM_FILL(0x2DAD59,1,0xC5)\
	ROM_FILL(0x2DAD76,1,0x06)\
    ROM_FILL(0x2DAD77,1,0xC5)

#define MSLUGXC2_ENEMYRESET_FIX_FILL \
	ROM_FILL(0x2D756C,1,0x04)\
    ROM_FILL(0x2D756D,1,0xB8)\
	ROM_FILL(0x2D764C,1,0x04)\
    ROM_FILL(0x2D764D,1,0xB8)\
	ROM_FILL(0x2D765C,1,0x04)\
    ROM_FILL(0x2D765D,1,0xB8)\
    ROM_FILL(0x2D76C0,1,0x02)\
	ROM_FILL(0x2D76C1,1,0xE8)\
	ROM_FILL(0x2D76D4,1,0x02)\
	ROM_FILL(0x2D76D5,1,0xE8)\
    ROM_FILL(0x2D9A90,1,0x05)\
	ROM_FILL(0x2D9A91,1,0x10)\
    ROM_FILL(0x2D9A95,1,0x00)\
    ROM_FILL(0x2D9AA0,1,0x05)\
	ROM_FILL(0x2D9AA1,1,0x10)\
	ROM_FILL(0x2D9AA5,1,0x00)\
	ROM_FILL(0x2DB6A7,1,0x04)\
    ROM_FILL(0x2DB6A8,1,0x01)\
	ROM_FILL(0x2DB6A9,1,0x80)\
    ROM_FILL(0x2DB6AA,1,0x00)\
	ROM_FILL(0x2DB6AB,1,0x50)\
    ROM_FILL(0x2DB6AC,1,0x00)\
	ROM_FILL(0x2DB6AD,1,0x00)\
    ROM_FILL(0x2DB6AE,1,0x00)\
	ROM_FILL(0x2DB6AF,1,0x00)\
	ROM_FILL(0x2DBFB4,1,0x01)\
    ROM_FILL(0x2DBFB5,1,0xA8)

#define MSLUGX_CUZTOMPATCH_MODS_FILL \
    ROM_FILL(0xA7E45,1,0x47)\
	ROM_FILL(0xA7E46,1,0x41)\
	ROM_FILL(0xA7E47,1,0x53)\
    ROM_FILL(0xA7E48,1,0x54)\
    ROM_FILL(0xA7E49,1,0x4F)\
    ROM_FILL(0xA7E4A,1,0x4E)\
    ROM_FILL(0xA7E4B,1,0x39)\
    ROM_FILL(0xA7E4C,1,0x30)\
	ROM_FILL(0xA7E4D,1,0x20)\
    ROM_FILL(0xA7E4E,1,0x45)\
    ROM_FILL(0xA7E4F,1,0x44)\
    ROM_FILL(0xA7E50,1,0x49)\
	ROM_FILL(0xA7E51,1,0x54)\
    ROM_FILL(0xA7E52,1,0x49)\
	ROM_FILL(0xA7E53,1,0x4F)\
    ROM_FILL(0xA7E54,1,0x4E)\
	ROM_FILL(0xA7E55,1,0x20)\
	ROM_FILL(0xA7E56,1,0x32)\
    ROM_FILL(0xA7E57,1,0x30)\
    ROM_FILL(0xA7E58,1,0x32)\
    ROM_FILL(0xA7E59,1,0x33)\
    ROM_FILL(0xA7E5A,1,0x2E)\
    ROM_FILL(0xA7E5B,1,0x20)\
	ROM_FILL(0xA7E5C,1,0x20)

#define MSLUGX_CUZTOMWEAPONANIMATION_MODS_FILL \
    ROM_FILL(0x2D0AFD,1,0x0A) \
    ROM_FILL(0x1B4CB,1,0x0A)\
    ROM_FILL(0x1B4DB,1,0x0A)\
    ROM_FILL(0x1B4EB,1,0x0A)\
    ROM_FILL(0x1B4FB,1,0x0A)\
    ROM_FILL(0x1B50B,1,0x0A)\
    ROM_FILL(0x1B51B,1,0x0A)\
    ROM_FILL(0x1B52B,1,0x0A)\
    ROM_FILL(0x1B53B,1,0x0A)\
    ROM_FILL(0x1B54B,1,0x0A)\
    ROM_FILL(0x1B55B,1,0x0A)\
    ROM_FILL(0x1B56B,1,0x0A)\
    ROM_FILL(0x1B57B,1,0x0A)\
    ROM_FILL(0x1B58B,1,0x0A)\
    ROM_FILL(0x1B59B,1,0x0A)\
    ROM_FILL(0x1B5AB,1,0x0A)\
    ROM_FILL(0x1B5BB,1,0x0A)\
    ROM_FILL(0xA714F,1,0x08)\
    ROM_FILL(0xA715F,1,0x08)\
    ROM_FILL(0x1F09F,1,0x09)\
    ROM_FILL(0x1F0BF,1,0x09)\
    ROM_FILL(0x1F0DF,1,0x09)\
    ROM_FILL(0x1F0EF,1,0x09)\
    ROM_FILL(0x1F10F,1,0x09)\
    ROM_FILL(0x1F13F,1,0x09)\
    ROM_FILL(0x1F14F,1,0x09)\
    ROM_FILL(0x1F15F,1,0x09)\
    ROM_FILL(0x635E9,1,0x07)\
    ROM_FILL(0x63609,1,0x07)\
    ROM_FILL(0x63629,1,0x07)\
    ROM_FILL(0x63639,1,0x07)\
    ROM_FILL(0x63649,1,0x07)\
    ROM_FILL(0x63659,1,0x07)\
    ROM_FILL(0x63689,1,0x07)\
    ROM_FILL(0x63699,1,0x07)\
    ROM_FILL(0x636A9,1,0x07)\
    ROM_FILL(0xE133B,1,0x0D)\
    ROM_FILL(0xE134B,1,0x0D)\
    ROM_FILL(0xE135B,1,0x0D)\
    ROM_FILL(0xE136B,1,0x0D)\
    ROM_FILL(0xE137B,1,0x0D)\
    ROM_FILL(0xE138B,1,0x0D)\
    ROM_FILL(0xE139B,1,0x0D)\
    ROM_FILL(0xE13AB,1,0x0D)\
    ROM_FILL(0xE13BB,1,0x0D)\
    ROM_FILL(0xE13CB,1,0x0D)\
    ROM_FILL(0xE13DB,1,0x0D)\
    ROM_FILL(0xE13EB,1,0x0D)\
    ROM_FILL(0xEB5DF,1,0x0B)\
    ROM_FILL(0xEB5EF,1,0x0B)\
    ROM_FILL(0xEB5FF,1,0x0B)\
    ROM_FILL(0xEB60F,1,0x0B)\
    ROM_FILL(0xEB61F,1,0x0B)\
    ROM_FILL(0xEB62F,1,0x0B)\
    ROM_FILL(0xEB63F,1,0x0B)\
    ROM_FILL(0xEB64F,1,0x0B)\
    ROM_FILL(0xE4E4D,1,0x0E)\
    ROM_FILL(0xE4E5D,1,0x05)\
    ROM_FILL(0xE4E6D,1,0x05)\
    ROM_FILL(0xE4E7D,1,0x05)

#define MSLUGX_DISABLE_COLORPALETTE_MODS_FILL \
    ROM_FILL(0x5E000,1,0x03)\
	ROM_FILL(0x2BA14,1,0x02)\
	ROM_FILL(0x2BA15,1,0x46)\
	ROM_FILL(0x5563A,1,0x04)\
	ROM_FILL(0x5563B,1,0x77)

#define MSLUGX_DISABLE_ENEMYSPEEDUP_MODS_FILL \
	ROM_FILL(0x426E,1,0x31)\
	ROM_FILL(0x426F,1,0x7C)\
	ROM_FILL(0x4270,1,0x00)\
	ROM_FILL(0x4271,1,0x00)\
	ROM_FILL(0x4272,1,0x00)\
    ROM_FILL(0x4273,1,0x04)\
	ROM_FILL(0x3182,1,0xF3)

#define MSLUGXAT_PLAYERS_CHANGING_UNIFORM_MODS_FILL \
	ROM_FILL(0x200F78,1,0x40)\
    ROM_FILL(0x200F79,1,0x76)\
    ROM_FILL(0x200F7A,1,0x64)\
    ROM_FILL(0x200F7B,1,0x7F)\
	ROM_FILL(0x200F7C,1,0x61)\
    ROM_FILL(0x200F7D,1,0xA0)\
    ROM_FILL(0x200F7E,1,0x40)\
    ROM_FILL(0x200F7F,1,0xE0)\
	ROM_FILL(0x200F98,1,0x40)\
    ROM_FILL(0x200F99,1,0x76)\
    ROM_FILL(0x200F9A,1,0x64)\
    ROM_FILL(0x200F9B,1,0x7F)\
	ROM_FILL(0x200F9C,1,0x61)\
    ROM_FILL(0x200F9D,1,0xA0)\
    ROM_FILL(0x200F9E,1,0x40)\
    ROM_FILL(0x200F9F,1,0xE0)\
	ROM_FILL(0x200FF8,1,0x59)\
    ROM_FILL(0x200FF9,1,0x00)\
    ROM_FILL(0x200FFA,1,0x3C)\
    ROM_FILL(0x200FFB,1,0x00)\
	ROM_FILL(0x200FFC,1,0x7F)\
    ROM_FILL(0x200FFD,1,0x89)\
    ROM_FILL(0x200FFE,1,0x72)\
    ROM_FILL(0x200FFF,1,0x65)\
	ROM_FILL(0x201018,1,0x59)\
    ROM_FILL(0x201019,1,0x00)\
    ROM_FILL(0x20101A,1,0x3C)\
    ROM_FILL(0x20101B,1,0x00)\
	ROM_FILL(0x20101C,1,0x7F)\
    ROM_FILL(0x20101D,1,0x89)\
    ROM_FILL(0x20101E,1,0x72)\
    ROM_FILL(0x20101F,1,0x65)\
	ROM_FILL(0x200FB8,1,0x02)\
    ROM_FILL(0x200FB9,1,0x30)\
    ROM_FILL(0x200FBA,1,0x01)\
    ROM_FILL(0x200FBB,1,0x30)\
	ROM_FILL(0x200FBC,1,0x7F)\
    ROM_FILL(0x200FBD,1,0x89)\
    ROM_FILL(0x200FBE,1,0x72)\
    ROM_FILL(0x200FBF,1,0x65)\
	ROM_FILL(0x200FD8,1,0x02)\
    ROM_FILL(0x200FD9,1,0x30)\
    ROM_FILL(0x200FDA,1,0x01)\
    ROM_FILL(0x200FDB,1,0x30)\
	ROM_FILL(0x200FDC,1,0x7F)\
    ROM_FILL(0x200FDD,1,0x89)\
    ROM_FILL(0x200FDE,1,0x72)\
    ROM_FILL(0x200FDF,1,0x65)\
	ROM_FILL(0x200F38,1,0x7F)\
    ROM_FILL(0x200F39,1,0x80)\
    ROM_FILL(0x200F3A,1,0x72)\
    ROM_FILL(0x200F3B,1,0x60)\
	ROM_FILL(0x200F3C,1,0x61)\
    ROM_FILL(0x200F3D,1,0xA0)\
    ROM_FILL(0x200F3E,1,0x40)\
    ROM_FILL(0x200F3F,1,0xE0)\
	ROM_FILL(0x200F58,1,0x7F)\
    ROM_FILL(0x200F59,1,0x80)\
    ROM_FILL(0x200F5A,1,0x72)\
    ROM_FILL(0x200F5B,1,0x60)\
	ROM_FILL(0x200F5C,1,0x61)\
    ROM_FILL(0x200F5D,1,0xA0)\
    ROM_FILL(0x200F5E,1,0x40)\
    ROM_FILL(0x200F5F,1,0xE0)

#define MSLUGXAT_SOLDIERSHIELD_CHANGING_UNIFORM_MODS_FILL \
    ROM_FILL(0x202E24,1,0x73)\
	ROM_FILL(0x202E25,1,0x9A)\
	ROM_FILL(0x202E26,1,0x63)\
    ROM_FILL(0x202E27,1,0x15)\
    ROM_FILL(0x202E28,1,0x46)\
    ROM_FILL(0x202E29,1,0x2F)\
    ROM_FILL(0x202E2A,1,0x25)\
    ROM_FILL(0x202E2B,1,0x27)\
    ROM_FILL(0x2073E4,1,0x73)\
	ROM_FILL(0x2073E5,1,0x9A)\
	ROM_FILL(0x2073E6,1,0x63)\
    ROM_FILL(0x2073E7,1,0x15)\
    ROM_FILL(0x2073E8,1,0x46)\
    ROM_FILL(0x2073E9,1,0x2F)\
    ROM_FILL(0x2073EA,1,0x25)\
    ROM_FILL(0x2073EB,1,0x27)\
    ROM_FILL(0x207404,1,0x73)\
	ROM_FILL(0x207405,1,0x9A)\
	ROM_FILL(0x207406,1,0x63)\
    ROM_FILL(0x207407,1,0x15)\
    ROM_FILL(0x207408,1,0x46)\
    ROM_FILL(0x207409,1,0x2F)\
    ROM_FILL(0x20740A,1,0x25)\
    ROM_FILL(0x20740B,1,0x27)\
    ROM_FILL(0x207424,1,0x73)\
	ROM_FILL(0x207425,1,0x9A)\
	ROM_FILL(0x207426,1,0x63)\
    ROM_FILL(0x207427,1,0x15)\
    ROM_FILL(0x207428,1,0x46)\
    ROM_FILL(0x207429,1,0x2F)\
    ROM_FILL(0x20742A,1,0x25)\
    ROM_FILL(0x20742B,1,0x27)\
    ROM_FILL(0x207444,1,0x73)\
	ROM_FILL(0x207445,1,0x9A)\
	ROM_FILL(0x207446,1,0x63)\
    ROM_FILL(0x207447,1,0x15)\
    ROM_FILL(0x207448,1,0x46)\
    ROM_FILL(0x207449,1,0x2F)\
    ROM_FILL(0x20744A,1,0x25)\
    ROM_FILL(0x20744B,1,0x27)\
    ROM_FILL(0x207464,1,0x73)\
	ROM_FILL(0x207465,1,0x9A)\
	ROM_FILL(0x207466,1,0x63)\
    ROM_FILL(0x207467,1,0x15)\
    ROM_FILL(0x207468,1,0x46)\
    ROM_FILL(0x207469,1,0x2F)\
    ROM_FILL(0x20746A,1,0x25)\
    ROM_FILL(0x20746B,1,0x27)\
    ROM_FILL(0x207484,1,0x73)\
	ROM_FILL(0x207485,1,0x9A)\
	ROM_FILL(0x207486,1,0x63)\
    ROM_FILL(0x207487,1,0x15)\
    ROM_FILL(0x207488,1,0x46)\
    ROM_FILL(0x207489,1,0x2F)\
    ROM_FILL(0x20748A,1,0x25)\
    ROM_FILL(0x20748B,1,0x27)\
    ROM_FILL(0x2074A4,1,0x73)\
	ROM_FILL(0x2074A5,1,0x9A)\
	ROM_FILL(0x2074A6,1,0x63)\
    ROM_FILL(0x2074A7,1,0x15)\
    ROM_FILL(0x2074A8,1,0x46)\
    ROM_FILL(0x2074A9,1,0x2F)\
    ROM_FILL(0x2074AA,1,0x25)\
    ROM_FILL(0x2074AB,1,0x27)\
    ROM_FILL(0x2078E4,1,0x73)\
	ROM_FILL(0x2078E5,1,0x9A)\
	ROM_FILL(0x2078E6,1,0x63)\
    ROM_FILL(0x2078E7,1,0x15)\
    ROM_FILL(0x2078E8,1,0x46)\
    ROM_FILL(0x2078E9,1,0x2F)\
    ROM_FILL(0x2078EA,1,0x25)\
    ROM_FILL(0x2078EB,1,0x27)

#define MSLUGX_FLASHOFF_MODS_FILL \
    ROM_FILL(0x9744,1,0x4E)\
	ROM_FILL(0x9745,1,0x71)\
    ROM_FILL(0x9746,1,0x4E)\
	ROM_FILL(0x9747,1,0x71)

#define MSLUGX_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
    ROM_FILL(0x15D62,1,0x49)\
    ROM_FILL(0x15D63,1,0x4E)\
    ROM_FILL(0x15D64,1,0x56)\
	ROM_FILL(0x15D65,1,0x45)\
	ROM_FILL(0x15D66,1,0x4E)\
    ROM_FILL(0x15D67,1,0x54)\
    ROM_FILL(0x15D68,1,0x4F)\
    ROM_FILL(0x15D69,1,0x52)\
    ROM_FILL(0x15D6A,1,0x59)\
    ROM_FILL(0x15D6B,1,0x00)\
	ROM_FILL(0x15D6C,1,0x43)\
    ROM_FILL(0x15D6D,1,0x4C)\
    ROM_FILL(0x15D6E,1,0x4F)\
    ROM_FILL(0x15D6F,1,0x53)\
	ROM_FILL(0x15D70,1,0x5C)\
    ROM_FILL(0x15D71,1,0x45)\
	ROM_FILL(0x15D72,1,0x20)\
	ROM_FILL(0x15D73,1,0x4D)\
	ROM_FILL(0x15D74,1,0x45)\
	ROM_FILL(0x15D75,1,0x4E)\
    ROM_FILL(0x15D76,1,0x55)\
    ROM_FILL(0x15D77,1,0x20)\
    ROM_FILL(0x15D78,1,0x28)\
    ROM_FILL(0x15D79,1,0x49)\
    ROM_FILL(0x15D7A,1,0x4E)\
	ROM_FILL(0x15D7B,1,0x2D)\
	ROM_FILL(0x15D7C,1,0x50)\
	ROM_FILL(0x15D7D,1,0x41)\
	ROM_FILL(0x15D7E,1,0x55)\
	ROM_FILL(0x15D7F,1,0x53)\
	ROM_FILL(0x15D80,1,0x45)\
    ROM_FILL(0x15D81,1,0x29)\
	ROM_FILL(0x15D82,1,0x00)\
	ROM_FILL(0x162C0,1,0x49)\
    ROM_FILL(0x162C1,1,0x4E)\
    ROM_FILL(0x162C2,1,0x56)\
	ROM_FILL(0x162C3,1,0x49)\
	ROM_FILL(0x162C4,1,0x4E)\
    ROM_FILL(0x162C5,1,0x43)\
    ROM_FILL(0x162C6,1,0x49)\
    ROM_FILL(0x162C7,1,0x42)\
    ROM_FILL(0x162C8,1,0x49)\
    ROM_FILL(0x162C9,1,0x4C)\
	ROM_FILL(0x162CA,1,0x49)\
    ROM_FILL(0x162CB,1,0x54)\
    ROM_FILL(0x162CC,1,0x59)\
    ROM_FILL(0x162CD,1,0x20)\
    ROM_FILL(0x162EB,1,0x41)\
    ROM_FILL(0x162EC,1,0x4E)\
	ROM_FILL(0x162ED,1,0x59)\
    ROM_FILL(0x162EE,1,0x54)\
	ROM_FILL(0x162EF,1,0x49)\
	ROM_FILL(0x162F0,1,0x4D)\
    ROM_FILL(0x162F1,1,0x45)\
    ROM_FILL(0x162F2,1,0x20)\
    ROM_FILL(0x162F3,1,0x50)\
    ROM_FILL(0x162F4,1,0x41)\
    ROM_FILL(0x162F5,1,0x55)\
	ROM_FILL(0x162F6,1,0x53)\
	ROM_FILL(0x162F7,1,0x45)\
	ROM_FILL(0x162F8,1,0x20)\
    ROM_FILL(0x16376,1,0x49)\
	ROM_FILL(0x16377,1,0x4E)\
	ROM_FILL(0x16378,1,0x46)\
    ROM_FILL(0x16379,1,0x49)\
	ROM_FILL(0x1637A,1,0x4E)\
    ROM_FILL(0x1637B,1,0x49)\
    ROM_FILL(0x1637C,1,0x54)\
    ROM_FILL(0x1637D,1,0x45)\
	ROM_FILL(0x1637E,1,0x20)\
	ROM_FILL(0x1637F,1,0x41)\
    ROM_FILL(0x16380,1,0x4D)\
    ROM_FILL(0x16381,1,0x4D)\
    ROM_FILL(0x16382,1,0x4F)\
    ROM_FILL(0x16383,1,0x20)\
    ROM_FILL(0x1635E,1,0x00)\
	ROM_FILL(0x1635F,1,0x49)\
    ROM_FILL(0x16360,1,0x4E)\
    ROM_FILL(0x16361,1,0x46)\
    ROM_FILL(0x16362,1,0x49)\
	ROM_FILL(0x16363,1,0x4E)\
    ROM_FILL(0x16364,1,0x49)\
	ROM_FILL(0x16365,1,0x54)\
    ROM_FILL(0x16366,1,0x45)\
	ROM_FILL(0x16367,1,0x20)\
	ROM_FILL(0x16368,1,0x42)\
    ROM_FILL(0x16369,1,0x4F)\
    ROM_FILL(0x1636A,1,0x4D)\
	ROM_FILL(0x1636B,1,0x42)\
    ROM_FILL(0x1636C,1,0x20)\
    ROM_FILL(0x1636D,1,0x20)\
    ROM_FILL(0x1638D,1,0x44)\
	ROM_FILL(0x1638E,1,0x2D)\
	ROM_FILL(0x1638F,1,0x42)\
	ROM_FILL(0x16390,1,0x55)\
    ROM_FILL(0x16391,1,0x54)\
    ROM_FILL(0x16392,1,0x54)\
	ROM_FILL(0x16393,1,0x4F)\
	ROM_FILL(0x16394,1,0x4E)\
    ROM_FILL(0x16395,1,0x20)\
    ROM_FILL(0x16396,1,0x57)\
    ROM_FILL(0x16397,1,0x49)\
    ROM_FILL(0x16398,1,0x50)\
    ROM_FILL(0x16399,1,0x45)\
	ROM_FILL(0x1639A,1,0x4F)\
    ROM_FILL(0x1639B,1,0x55)\
    ROM_FILL(0x1639C,1,0x54)\
    ROM_FILL(0x1639D,1,0x20)\
    ROM_FILL(0x163A9,1,0x52)\
    ROM_FILL(0x163AA,1,0x45)\
	ROM_FILL(0x163AB,1,0x53)\
    ROM_FILL(0x163AC,1,0x50)\
	ROM_FILL(0x163AD,1,0x41)\
	ROM_FILL(0x163AE,1,0x57)\
    ROM_FILL(0x163AF,1,0x4E)

#define MSLUGXSC_FIX_FILL \
	ROM_FILL(0x2ED35A,1,0x00)\
    ROM_FILL(0x2ED35B,1,0x20)\
	ROM_FILL(0xEB930,1,0x00)\
    ROM_FILL(0xEB931,1,0x01)\
	ROM_FILL(0xEB936,1,0x00)\
    ROM_FILL(0xEB937,1,0x01)\
    ROM_FILL(0xEB993,1,0x05)\
	ROM_FILL(0xEB9A0,1,0xFF)\
	ROM_FILL(0xEB9A1,1,0xFB)\
	ROM_FILL(0xEBA30,1,0x00)\
    ROM_FILL(0xEBA31,1,0x01)\
	ROM_FILL(0xEBA36,1,0x00)\
    ROM_FILL(0xEBA37,1,0x01)\
    ROM_FILL(0xEBA93,1,0x05)\
	ROM_FILL(0xEBAA0,1,0xFF)\
	ROM_FILL(0xEBAA1,1,0xFB)

#define MSLUGXCQI_RESTORELVXCODE_MODS_FILL \
    ROM_FILL(0X0EEDA5,1,0x02)\
    ROM_FILL(0X0EEDB7,1,0x02)\
	ROM_FILL(0X0EEDC9,1,0x02)\
	ROM_FILL(0X0EEDDB,1,0x02)\
    ROM_FILL(0X2B80B0,1,0x08)\
    ROM_FILL(0X2B80B1,1,0x39)

#define MSLUGX_MVS_FILL \
	ROM_FILL(0x3182,1,0x63)\
    ROM_FILL(0x3185,1,0x58)\
	ROM_FILL(0x3189,1,0x12)\
	ROM_FILL(0x318D,1,0x12)\
	ROM_FILL(0x318B,1,0x34)\
	ROM_FILL(0x3186,1,0x34)\
	ROM_FILL(0x318C,1,0x34)

#define MSLUGXSC_MVS_FILL \
    ROM_FILL(0x3185,1,0x58)\
	ROM_FILL(0x3189,1,0x12)\
	ROM_FILL(0x318D,1,0x12)\
	ROM_FILL(0x318B,1,0x34)\
	ROM_FILL(0x3186,1,0x34)\
	ROM_FILL(0x318C,1,0x34)

#define MSLUGXAT_MVS_FILL \
    ROM_FILL(0x3188,1,0x12)

#define MSLUGX_AES_FILL \
    ROM_FILL(0x24F6,1,0x99)\
    ROM_FILL(0x24F7,1,0x99)\
    ROM_FILL(0x156F4,1,0x60)

#define MSLUGX_AES_FIX_FILL \
    ROM_FILL(0x664F3,1,0x53)\
    ROM_FILL(0x664F4,1,0x50)\
    ROM_FILL(0x664F5,1,0x45)\
	ROM_FILL(0x664F6,1,0x43)\
	ROM_FILL(0x664F7,1,0x49)\
    ROM_FILL(0x664F8,1,0x41)\
    ROM_FILL(0x664F9,1,0x4C)\
    ROM_FILL(0x664FA,1,0x20)\
    ROM_FILL(0x664FB,1,0x41)\
    ROM_FILL(0x664FC,1,0x54)\
	ROM_FILL(0x664FD,1,0x54)\
    ROM_FILL(0x664FE,1,0x41)\
    ROM_FILL(0x664FF,1,0x43)\
    ROM_FILL(0x66500,1,0x4B)\
	ROM_FILL(0x66501,1,0x20)\
	ROM_FILL(0x663F8,1,0x03)\
    ROM_FILL(0x663F9,1,0x05)\
    ROM_FILL(0x663FA,1,0x07)\
    ROM_FILL(0x66415,1,0x02)\
	ROM_FILL(0x66417,1,0x03)

#define MINASAN_MVS_FILL \
    ROM_FILL(0X0217,1,0X58)

#define MOSHOUGI_MVS_FILL \
    ROM_FILL(0X2BB70,1,0X58)

#define MUTNAT_MVS_FILL \
    ROM_FILL(0X1132,1,0X58)

#define NAM1975_MVS_FILL \
    ROM_FILL(0X0660,1,0X58)\
	ROM_FILL(0X0662,1,0XEF)\
	ROM_FILL(0X0663,1,0X89)

#define NCOMBAT_MVS_FILL \
    ROM_FILL(0X90D8,1,0X08)\
	ROM_FILL(0X90DF,1,0X34)\
	ROM_FILL(0X90E0,1,0X58)\
	ROM_FILL(0X90E1,1,0X34)

#define NCOMMAND_MVS_FILL \
    ROM_FILL(0X10680,1,0X29)\
	ROM_FILL(0X10684,1,0X63)\
	ROM_FILL(0X10688,1,0X58)\
	ROM_FILL(0X1068A,1,0X78)\
	ROM_FILL(0X1068B,1,0X58)

#define NEOBOMBE_MVS_FILL \
    ROM_FILL(0X02DD,1,0X58)

#define NEOCUP98_MVS_FILL \
    ROM_FILL(0X08F2,1,0X9F)\
	ROM_FILL(0X08F3,1,0X9F)\
	ROM_FILL(0X08F8,1,0X5F)\
	ROM_FILL(0X08F9,1,0X44)\
	ROM_FILL(0X08FA,1,0X12)\
	ROM_FILL(0X08FB,1,0X26)

#define NEOCUP98KR_MVS_FILL \
    ROM_FILL(0X01AA,1,0X9F)\
	ROM_FILL(0X01AB,1,0X9F)\
	ROM_FILL(0X01B0,1,0X5F)\
	ROM_FILL(0X01B1,1,0X44)\
	ROM_FILL(0X01B2,1,0X12)

#define NEODRIFT_MVS_FILL \
    ROM_FILL(0X0562,1,0X58)

#define NEOMRDO_MVS_FILL \
    ROM_FILL(0X063A,1,0X63)\
	ROM_FILL(0X063D,1,0X58)

#define NINJAMAS_MVS_FILL \
	ROM_FILL(0X2164,1,0X9A)\
    ROM_FILL(0X216A,1,0X58)\
	ROM_FILL(0X216D,1,0X12)

#define NITD_MVS_FILL \
	ROM_FILL(0X033E,1,0X58)\
    ROM_FILL(0X0341,1,0X02)\
	ROM_FILL(0X0343,1,0X12)

#define OVERTOP_MVS_FILL \
    ROM_FILL(0X140C,1,0X58)\
	ROM_FILL(0X1411,1,0X12)

#define PANICBOM_MVS_FILL \
    ROM_FILL(0X30E,1,0X58)\

#define PBOBBL2N_MVS_FILL \
    ROM_FILL(0X904FA,1,0X58)\
	ROM_FILL(0X904FD,1,0X12)\
	ROM_FILL(0X90500,1,0X12)

#define PBOBBLEN_MVS_FILL \
    ROM_FILL(0X04AE,1,0X58)\
	ROM_FILL(0X04B2,1,0X32)\
	ROM_FILL(0X04B3,1,0X13)

#define PGOAL_MVS_FILL \
    ROM_FILL(0X0550,1,0X9F)\
	ROM_FILL(0X0551,1,0X9F)\
	ROM_FILL(0X0556,1,0X58)\
	ROM_FILL(0X0559,1,0X25)

#define PNYAA_MVS_FILL \
    ROM_FILL(0X0A8A,1,0X58)\
	ROM_FILL(0X0A8C,1,0X02)

#define POPBOUNC_MVS_FILL \
    ROM_FILL(0XE268,1,0X63)\
	ROM_FILL(0XE26A,1,0X58)\
	ROM_FILL(0XE26B,1,0XBC)\
	ROM_FILL(0XE26D,1,0X23)\
	ROM_FILL(0XE271,1,0X12)

#define PREISLE2_MVS_FILL \
    ROM_FILL(0X0693,1,0X58)\
	ROM_FILL(0X0694,1,0X3D)\
	ROM_FILL(0X0695,1,0X14)\
	ROM_FILL(0X0696,1,0X12)\
	ROM_FILL(0X0698,1,0X02)\
	ROM_FILL(0X0699,1,0X12)

#define PSPIKES2_MVS_FILL \
    ROM_FILL(0X0FCA,1,0X07)\
    ROM_FILL(0X0FD1,1,0X58)

#define PSPIKES2CD_MVS_FILL \
    ROM_FILL(0X0FF4,1,0X07)\
    ROM_FILL(0X0FFB,1,0X58)

#define PULSTAR_MVS_FILL \
    ROM_FILL(0X0216,1,0X34)\
	ROM_FILL(0X021A,1,0X58)\
	ROM_FILL(0X021D,1,0X34)

#define PUZZLDPR_MVS_FILL \
    ROM_FILL(0X117E,1,0X58)

#define PUZZLDPRKR_MVS_FILL \
    ROM_FILL(0X0E86,1,0X58)

#define PUZZLEDP_MVS_FILL \
    ROM_FILL(0X1162,1,0X58)

#define PUZZLEDPKR_MVS_FILL \
    ROM_FILL(0X0E6A,1,0X58)

#define QUIZDAI2_MVS_FILL \
    ROM_FILL(0X0382,1,0X63)\
	ROM_FILL(0X0386,1,0X58)\
	ROM_FILL(0X0389,1,0X78)

#define QUIZDAIS_MVS_FILL \
    ROM_FILL(0X03B6,1,0X63)\
	ROM_FILL(0X03B8,1,0X58)\
	ROM_FILL(0X03BA,1,0X78)

#define QUIZKOF_MVS_FILL \
    ROM_FILL(0X0218,1,0X23)\
	ROM_FILL(0X021A,1,0X58)\
	ROM_FILL(0X0221,1,0X34)

#define RAGNAGRD_MVS_FILL \
    ROM_FILL(0X5286,1,0X63)\
	ROM_FILL(0X528B,1,0X58)\
	ROM_FILL(0X5290,1,0X12)\
	ROM_FILL(0X5291,1,0X12)

#define RBFF1_MVS_FILL \
    ROM_FILL(0X04F4,1,0X63)\
	ROM_FILL(0X04F9,1,0X58)\
	ROM_FILL(0X04FF,1,0X23)

#define RBFF2_MVS_FILL \
    ROM_FILL(0X0584,1,0X63)\
	ROM_FILL(0X0589,1,0X58)\
	ROM_FILL(0X058B,1,0X02)\
	ROM_FILL(0X058D,1,0X34)\
	ROM_FILL(0X058E,1,0X12)

#define RBFFSPEC_MVS_FILL \
    ROM_FILL(0X04F4,1,0X63)\
	ROM_FILL(0X04F9,1,0X58)\
	ROM_FILL(0X04FF,1,0X23)

#define RIDHERO_MVS_FILL \
    ROM_FILL(0X0558,1,0X58)

#define ROBOARMY_MVS_FILL \
    ROM_FILL(0X05BA,1,0X63)\
	ROM_FILL(0X05BE,1,0X58)\
	ROM_FILL(0X05C0,1,0X23)

 /* The rotd and rotdh versions are encrypted (modification of the roms is not allowed) */ 
#define ROTDH_MVS_FILL \
	ROM_FILL(0X098C,1,0X58)\
	ROM_FILL(0X098F,1,0X34)\
	ROM_FILL(0X0992,1,0X02)\
	ROM_FILL(0X0995,1,0X12)

#define S1945P_MVS_FILL \
	ROM_FILL(0X06C1,1,0X58)\
	ROM_FILL(0X06C4,1,0X34)\
	ROM_FILL(0X06C5,1,0X78)\
	ROM_FILL(0X06C6,1,0X23)\
	ROM_FILL(0X06C8,1,0X12)

#define SAMSH5SP_AES_FILL \
	ROM_FILL(0X11A20,1,0X4E)\
	ROM_FILL(0X11A21,1,0X71)\
	ROM_FILL(0X11A22,1,0X4E)\
	ROM_FILL(0X11A23,1,0X71)

#define SAMSH5SPH_AES_FILL \
	ROM_FILL(0X11C60,1,0X4E)\
	ROM_FILL(0X11C61,1,0X71)\
	ROM_FILL(0X11C62,1,0X4E)\
	ROM_FILL(0X11C63,1,0X71)

#define SAMSHO_MVS_FILL \
	ROM_FILL(0X0531,1,0X58)\
	ROM_FILL(0X0532,1,0X23)\
	ROM_FILL(0X0539,1,0X12)

#define SAMSHO_AES_FILL \
	ROM_FILL(0X0C4C,1,0X4E)\
	ROM_FILL(0X0C4D,1,0X71)\
	ROM_FILL(0X0C4E,1,0X4E)\
	ROM_FILL(0X0C4F,1,0X71)

#define SAMSHO2_MVS_FILL \
	ROM_FILL(0X054A,1,0X23)\
	ROM_FILL(0X0549,1,0X58)\
	ROM_FILL(0X0551,1,0X12)

#define SAMSHO2_AES_FILL \
	ROM_FILL(0X1810,1,0X4E)\
	ROM_FILL(0X1811,1,0X71)\
	ROM_FILL(0X1812,1,0X4E)\
	ROM_FILL(0X1813,1,0X71)

#define SAMSHO3_MVS_FILL \
	ROM_FILL(0X74363,1,0X58)\
	ROM_FILL(0X7436B,1,0X23)

#define SAMSHO3_AES_FILL \
	ROM_FILL(0X197C,1,0X4E)\
	ROM_FILL(0X197D,1,0X71)\
	ROM_FILL(0X197E,1,0X4E)\
	ROM_FILL(0X197F,1,0X71)\
	ROM_FILL(0X19E0,1,0X4E)\
	ROM_FILL(0X19E1,1,0X71)\
	ROM_FILL(0X19E2,1,0X4E)\
	ROM_FILL(0X19E3,1,0X71)

//BOTH FSWORDS VERSIONS WORK.
#define SAMSHO3H_AES_FILL \
	ROM_FILL(0X19B0,1,0X4E)\
	ROM_FILL(0X19B1,1,0X71)\
	ROM_FILL(0X19B2,1,0X4E)\
	ROM_FILL(0X19B3,1,0X71)\
	ROM_FILL(0X1A14,1,0X4E)\
	ROM_FILL(0X1A15,1,0X71)\
	ROM_FILL(0X1A16,1,0X4E)\
	ROM_FILL(0X1A17,1,0X71)

#define SAMSHO4_MVS_FILL \
	ROM_FILL(0X0457,1,0X58)\
	ROM_FILL(0X045C,1,0X9F)\
	ROM_FILL(0X045E,1,0X25)\
	ROM_FILL(0X045F,1,0X13)

#define SAMSHO4_AES_FILL \
	ROM_FILL(0XDDDA,1,0X4E)\
	ROM_FILL(0XDDDB,1,0X71)\
	ROM_FILL(0XDDDC,1,0X4E)\
	ROM_FILL(0XDDDD,1,0X71)

#define SAMSHO4K_MVS_FILL \
	ROM_FILL(0X01A3,1,0X58)\
	ROM_FILL(0X01A8,1,0X9F)\
	ROM_FILL(0X01AA,1,0X25)

#define SAMSHO4K_AES_FILL \
	ROM_FILL(0XDCE0,1,0X4E)\
	ROM_FILL(0XDCE1,1,0X71)\
	ROM_FILL(0XDCE2,1,0X4E)\
	ROM_FILL(0XDCE3,1,0X71)

//BOTH SAMSH5SP VERSIONS WORK.
#define SAMSHO5_MVS_FILL \
	ROM_FILL(0X0457,1,0X58)\
	ROM_FILL(0X045C,1,0X9F)\
	ROM_FILL(0X045E,1,0X25)\
	ROM_FILL(0X045F,1,0X13)

#define SAMSHO5_AES_FILL \
	ROM_FILL(0X1187A,1,0X4E)\
	ROM_FILL(0X1187B,1,0X71)\
	ROM_FILL(0X1187C,1,0X4E)\
	ROM_FILL(0X1187D,1,0X71)

//BOTH SAMSHO5A VERSIONS WORK.
#define SAMSHO5H_AES_FILL \
	ROM_FILL(0X11844,1,0X4E)\
	ROM_FILL(0X11845,1,0X71)\
	ROM_FILL(0X11846,1,0X4E)\
	ROM_FILL(0X11847,1,0X71)

#define SAVAGERE_MVS_FILL \
	ROM_FILL(0X5A3C2,1,0X03)\
	ROM_FILL(0X5A3C3,1,0X58)\
	ROM_FILL(0X5A3CB,1,0X12)

#define SDODGEB_MVS_FILL \
	ROM_FILL(0X4C6,1,0X23)\
	ROM_FILL(0X4C7,1,0X58)\
	ROM_FILL(0X4CD,1,0X12)

#define SENGOKU_MVS_FILL \
	ROM_FILL(0X9B3C,1,0X63)\
	ROM_FILL(0X9B3F,1,0X23)\
	ROM_FILL(0X9B41,1,0X23)

#define SENGOKUH_MVS_FILL \
	ROM_FILL(0X9D88,1,0X63)\
	ROM_FILL(0X9D8B,1,0X23)\
	ROM_FILL(0X9D8D,1,0X23)

#define SENGOKU2_MVS_FILL \
	ROM_FILL(0X0B6C,1,0X63)\
	ROM_FILL(0X0B6E,1,0X58)\
	ROM_FILL(0X0B70,1,0X23)\
	ROM_FILL(0X0B76,1,0X12)

#define SENGOKU3_MVS_FILL \
	ROM_FILL(0X0674,1,0X58)\
	ROM_FILL(0X0677,1,0X34)\
	ROM_FILL(0X0678,1,0X89)\
	ROM_FILL(0X067A,1,0X12)

#define SHOCKTRO_MVS_FILL \
	ROM_FILL(0X0603,1,0X58)\
	ROM_FILL(0X0604,1,0X78)\
	ROM_FILL(0X0605,1,0X34)\
	ROM_FILL(0X0606,1,0X12)\
	ROM_FILL(0X0607,1,0X23)

#define SHOCKTROA_MVS_FILL \
	ROM_FILL(0X052B,1,0X58)\
	ROM_FILL(0X052C,1,0X34)\
	ROM_FILL(0X052D,1,0X12)\
	ROM_FILL(0X052E,1,0X23)

#define SOCBRAWL_MVS_FILL \
	ROM_FILL(0X0344,1,0X05)\
	ROM_FILL(0X0346,1,0X05)\
	ROM_FILL(0X034A,1,0X04)\
	ROM_FILL(0X0350,1,0X58)

#define SONICWI2_MVS_FILL \
	ROM_FILL(0X7BDE,1,0X63)\
	ROM_FILL(0X7BE0,1,0X58)\
	ROM_FILL(0X7BE1,1,0X12)

#define SONICWI3_MVS_FILL \
	ROM_FILL(0X7CF6,1,0X63)\
	ROM_FILL(0X7CF8,1,0X58)\
	ROM_FILL(0X7CF9,1,0X12)

#define SPINMAST_MVS_FILL \
	ROM_FILL(0X3C476,1,0X63)\
	ROM_FILL(0X3C479,1,0X58)\
	ROM_FILL(0X3C47A,1,0X45)\
	ROM_FILL(0X3C47B,1,0X45)

#define SSIDEKI_MVS_FILL \
	ROM_FILL(0X08AA,1,0XAF)\
	ROM_FILL(0X08AB,1,0X4F)\
	ROM_FILL(0X08AC,1,0XAF)\
	ROM_FILL(0X08AE,1,0X58)\
	ROM_FILL(0X08B3,1,0X12)

#define SSIDEKI2_MVS_FILL \
	ROM_FILL(0X07C6,1,0X9F)\
	ROM_FILL(0X07C7,1,0X9F)\
	ROM_FILL(0X07CA,1,0X58)\
	ROM_FILL(0X07CE,1,0X12)\
	ROM_FILL(0X07CF,1,0X12)

#define SSIDEKI3_MVS_FILL \
	ROM_FILL(0X08F2,1,0X9F)\
	ROM_FILL(0X08F3,1,0X9F)\
	ROM_FILL(0X08F8,1,0X5F)\
	ROM_FILL(0X08FA,1,0X12)\
	ROM_FILL(0X08FB,1,0X26)

#define SSIDEKI4_MVS_FILL \
	ROM_FILL(0X0528,1,0X9F)\
	ROM_FILL(0X0529,1,0X9F)\
	ROM_FILL(0X052B,1,0X5F)\
	ROM_FILL(0X052F,1,0X28)

#define STAKWIN_MVS_FILL \
	ROM_FILL(0X0216,1,0X58)

#define STAKWIN2_MVS_FILL \
	ROM_FILL(0X0468,1,0X58)

#define STRHOOP_MVS_FILL \
	ROM_FILL(0X0B70,1,0X6D)\
	ROM_FILL(0X0B71,1,0X6D)\
	ROM_FILL(0X0B74,1,0X58)

#define STRHOOPCD_MVS_FILL \
	ROM_FILL(0X0BDC,1,0X6D)\
	ROM_FILL(0X0BDD,1,0X6D)\
	ROM_FILL(0X0BE0,1,0X58)

#define SUPERSPY_MVS_FILL \
	ROM_FILL(0X05E2,1,0X58)

#define SVC_MVS_FILL \
	ROM_FILL(0XA03FE,1,0X05)\
	ROM_FILL(0XA0401,1,0X58)\
	ROM_FILL(0XA0402,1,0X34)\
	ROM_FILL(0XA0403,1,0X23)\
	ROM_FILL(0XA0405,1,0X14)\
	ROM_FILL(0XA0406,1,0X12)\
	ROM_FILL(0XA0407,1,0X12)

#define SVC_AES_FILL \
	ROM_FILL(0X9B73,1,0X99)\
	ROM_FILL(0X9B79,1,0X99)

#define TOPHUNTR_MVS_FILL \
	ROM_FILL(0X0650,1,0X63)\
	ROM_FILL(0X0654,1,0X58)\
	ROM_FILL(0X0656,1,0X78)\
	ROM_FILL(0X0659,1,0X78)\
	ROM_FILL(0X065B,1,0X12)

#define TOPHUNTRKR_MVS_FILL \
	ROM_FILL(0X01A8,1,0X63)\
	ROM_FILL(0X01AC,1,0X58)\
	ROM_FILL(0X01AE,1,0X78)\
	ROM_FILL(0X01B1,1,0X78)

#define TPGOLF_MVS_FILL \
	ROM_FILL(0X035A,1,0X05)\
	ROM_FILL(0X0362,1,0X58)\
	ROM_FILL(0X0365,1,0X89)

#define TRALLY_MVS_FILL \
	ROM_FILL(0XA0D0,1,0X34)

#define TRALLYCD_MVS_FILL \
	ROM_FILL(0XA0DC,1,0X34)

#define TURFMAST_MVS_FILL \
	ROM_FILL(0XDF78,1,0X63)\
	ROM_FILL(0XDF7A,1,0XEF)\
	ROM_FILL(0XDF7E,1,0X58)\
	ROM_FILL(0XDF83,1,0X13)

#define TWINSPRI_MVS_FILL \
	ROM_FILL(0X1914,1,0X63)\
	ROM_FILL(0X1917,1,0X58)\
	ROM_FILL(0X191E,1,0X12)

#define TWSOC96_MVS_FILL \
	ROM_FILL(0X150B,1,0X58)\
	ROM_FILL(0X150C,1,0X68)

#define VIEWPOIN_MVS_FILL \
	ROM_FILL(0X10E00,1,0X63)\
	ROM_FILL(0X10E03,1,0X12)\
	ROM_FILL(0X10E04,1,0X24)

#define WAKUWAK7_MVS_FILL \
	ROM_FILL(0X0518,1,0X63)\
	ROM_FILL(0X051B,1,0X58)\
	ROM_FILL(0X0520,1,0X12)

#define WH1_MVS_FILL \
	ROM_FILL(0XF4DEA,1,0X08)\
	ROM_FILL(0XF4DEC,1,0X58)\
	ROM_FILL(0XF4DEF,1,0X12)

#define WH2_MVS_FILL \
    ROM_FILL(0X104EE6,1,0X08)\
	ROM_FILL(0X104EE8,1,0X58)\
	ROM_FILL(0X104EEC,1,0X12)

#define WH2J_MVS_FILL \
    ROM_FILL(0XFED5,1,0X58)\
	ROM_FILL(0XFEDA,1,0X12)

#define WHP_MVS_FILL \
    ROM_FILL(0XDD44,1,0X02)\
	ROM_FILL(0XDD46,1,0X58)\
	ROM_FILL(0XDD49,1,0X12)

#define WJAMMERS_MVS_FILL \
    ROM_FILL(0X04AC,1,0X63)\
	ROM_FILL(0X04AF,1,0X58)

#define WJAMMERSKR_MVS_FILL \
    ROM_FILL(0X0214,1,0X63)\
	ROM_FILL(0X0217,1,0X58)

#define ZEDBLADE_MVS_FILL \
    ROM_FILL(0X5D30,1,0X63)\
	ROM_FILL(0X5D32,1,0X58)

#define ZINTRCKB_MVS_FILL \
    ROM_FILL(0X2ACE,1,0X58)\
	ROM_FILL(0X2AD4,1,0X12)\
	ROM_FILL(0X2AD5,1,0X12)

#define ZUPAPA_MVS_FILL \
    ROM_FILL(0X04AC,1,0X63)\
	ROM_FILL(0X04AE,1,0X58)\
	ROM_FILL(0X04B4,1,0X12)

/*********************************************************
   Specific Structured Code For The Soft Dip Modification
 **********************************************************/

#define TWOTHOUSANDTWENTYBB_ESSENTIALPATCH_MODS_FILL \
    TWOTHOUSANDTWENTYBB_MVS_FILL

#define THREECOUNTB_ESSENTIALPATCH_MODS_FILL \
    THREECOUNTB_MVS_FILL

#define ALPHAM2_ESSENTIALPATCH_MODS_FILL \
    ALPHAM2_MVS_FILL

#define ALPHAM2P_ESSENTIALPATCH_MODS_FILL \
    ALPHAM2P_MVS_FILL

#define ANDRODUN_ESSENTIALPATCH_MODS_FILL \
    ANDRODUN_MVS_FILL

#define AODK_ESSENTIALPATCH_MODS_FILL \
    AODK_MVS_FILL

#define AOF_ESSENTIALPATCH_MODS_FILL \
    AOF_MVS_FILL

#define AOFBR_ESSENTIALPATCH_MODS_FILL \
    AOFBR_MVS_FILL

#define AOFKR_ESSENTIALPATCH_MODS_FILL \
    AOFKR_MVS_FILL

#define AOF2_ESSENTIALPATCH_MODS_FILL \
    AOF2_MVS_FILL

#define AOF3_ESSENTIALPATCH_MODS_FILL \
    AOF3_MVS_FILL

#define AOF3K_ESSENTIALPATCH_MODS_FILL \
    AOF3K_MVS_FILL

#define B2B_ESSENTIALPATCH_MODS_FILL \
    B2B_MVS_FILL

#define BAKATONO_ESSENTIALPATCH_MODS_FILL \
    BAKATONO_MVS_FILL

#define BANGBEAD_ESSENTIALPATCH_MODS_FILL \
    BANGBEAD_MVS_FILL

#define BJOURNEY_ESSENTIALPATCH_MODS_FILL \
    BJOURNEY_MVS_FILL

#define BLAZSTAR_ESSENTIALPATCH_MODS_FILL \
    BLAZSTAR_MVS_FILL

#define BREAKERS_ESSENTIALPATCH_MODS_FILL \
    BREAKERS_MVS_FILL

#define BREAKREV_ESSENTIALPATCH_MODS_FILL \
    BREAKREV_MVS_FILL

#define BSTARS_ESSENTIALPATCH_MODS_FILL \
    BSTARS_MVS_FILL

#define BSTARS2_ESSENTIALPATCH_MODS_FILL \
    BSTARS2_MVS_FILL

#define BURNINGF_ESSENTIALPATCH_MODS_FILL \
    BURNINGF_MVS_FILL

#define BURNINGFP_ESSENTIALPATCH_MODS_FILL \
    BURNINGFP_MVS_FILL

#define CRSWORD_ESSENTIALPATCH_MODS_FILL \
    CRSWORD_MVS_FILL

#define CRSWD2BL_ESSENTIALPATCH_MODS_FILL \
    CRSWD2BL_MVS_FILL

#define CTOMADAY_ESSENTIALPATCH_MODS_FILL \
    CTOMADAY_MVS_FILL

#define CYBERLIP_ESSENTIALPATCH_MODS_FILL \
    CYBERLIP_MVS_FILL

#define DIGGERMA_ESSENTIALPATCH_MODS_FILL \
    DIGGERMA_MVS_FILL

#define DOUBLEDR_ESSENTIALPATCH_MODS_FILL \
    DOUBLEDR_MVS_FILL

#define EIGHTMAN_ESSENTIALPATCH_MODS_FILL \
    EIGHTMAN_MVS_FILL

#define FATFURSP_ESSENTIALPATCH_MODS_FILL \
    FATFURSP_MVS_FILL

#define FATFURY1_ESSENTIALPATCH_MODS_FILL \
    FATFURY1_MVS_FILL

#define FATFURY2_ESSENTIALPATCH_MODS_FILL \
    FATFURY2_MVS_FILL

#define FATFURY3_ESSENTIALPATCH_MODS_FILL \
    FATFURY3_MVS_FILL

#define FBFRENZY_ESSENTIALPATCH_MODS_FILL \
    FBFRENZY_MVS_FILL

#define FIGHTFEV_ESSENTIALPATCH_MODS_FILL \
    FIGHTFEV_MVS_FILL

#define FLIPSHOT_ESSENTIALPATCH_MODS_FILL \
    FLIPSHOT_MVS_FILL

#define FLIPSHOTKR_ESSENTIALPATCH_MODS_FILL \
    FLIPSHOTKR_MVS_FILL

#define FROMAN2B_ESSENTIALPATCH_MODS_FILL \
    FROMAN2B_MVS_FILL

#define FSWORDS_ESSENTIALPATCH_MODS_FILL \
    FSWORDS_MVS_FILL

#define GALAXYFG_ESSENTIALPATCH_MODS_FILL \
    GALAXYFG_MVS_FILL

#define GANRYU_ESSENTIALPATCH_MODS_FILL \
    GANRYU_MVS_FILL

#define GAROUDD_ESSENTIALPATCH_MODS_FILL \
    GAROUDD_MVS_FILL

#define GAROU_ESSENTIALPATCH_MODS_FILL \
    GAROU_MVS_FILL

#define GHOSTLOP_ESSENTIALPATCH_MODS_FILL \
    GHOSTLOP_MVS_FILL

#define GOALX3_ESSENTIALPATCH_MODS_FILL \
    GOALX3_MVS_FILL

#define GOWCAIZR_ESSENTIALPATCH_MODS_FILL \
    GOWCAIZR_MVS_FILL

#define GPILOTS_ESSENTIALPATCH_MODS_FILL \
    GPILOTS_MVS_FILL

#define GPILOTSH_ESSENTIALPATCH_MODS_FILL \
    GPILOTSH_MVS_FILL

#define GURURIN_ESSENTIALPATCH_MODS_FILL \
    GURURIN_MVS_FILL

#define IRONCLAD_ESSENTIALPATCH_MODS_FILL \
    IRONCLAD_MVS_FILL

#define JANSHIN_ESSENTIALPATCH_MODS_FILL \
    JANSHIN_MVS_FILL

#define JOYJOY_ESSENTIALPATCH_MODS_FILL \
    JOYJOY_MVS_FILL

#define KABUKIKL_ESSENTIALPATCH_MODS_FILL \
    KABUKIKL_MVS_FILL

#define KARNOVR_ESSENTIALPATCH_MODS_FILL \
    KARNOVR_MVS_FILL

#define KIZUNA_ESSENTIALPATCH_MODS_FILL \
    KIZUNA_MVS_FILL

#define KF2K3UPL_ESSENTIALPATCH_MODS_FILL \
    KF2K3UPL_MVS_FILL

#define KOF94_ESSENTIALPATCH_MODS_FILL \
    KOF94_MVS_FILL

#define KOF94KR_ESSENTIALPATCH_MODS_FILL \
    KOF94KR_MVS_FILL

#define KOF95_ESSENTIALPATCH_MODS_FILL \
    KOF95_MVS_FILL

#define KOF95H_ESSENTIALPATCH_MODS_FILL \
    KOF95_MVS_FILL

#define KOF95KR_ESSENTIALPATCH_MODS_FILL \
    KOF95KR_MVS_FILL

#define KOF96_ESSENTIALPATCH_MODS_FILL \
    KOF96_MVS_FILL

#define KOF96KR_ESSENTIALPATCH_MODS_FILL \
    KOF96KR_MVS_FILL

#define KOF97_ESSENTIALPATCH_MODS_FILL \
    KOF97_MVS_FILL

#define KOF97KR_ESSENTIALPATCH_MODS_FILL \
    KOF97KR_MVS_FILL

#define KOF98_ESSENTIALPATCH_MODS_FILL \
    KOF98_MVS_FILL

#define KOF98KR_ESSENTIALPATCH_MODS_FILL \
    KOF98KR_MVS_FILL

#define KOF99_ESSENTIALPATCH_MODS_FILL \
    KOF99_MVS_FILL

#define KOF99KR_ESSENTIALPATCH_MODS_FILL \
    KOF99KR_MVS_FILL

#define KOF2000_ESSENTIALPATCH_MODS_FILL \
    KOF2000_MVS_FILL

#define KOF2000KR_ESSENTIALPATCH_MODS_FILL \
    KOF2000KR_MVS_FILL

#define KOF2001_ESSENTIALPATCH_MODS_FILL \
    KOF2001_MVS_FILL

#define KOF2002_ESSENTIALPATCH_MODS_FILL \
    KOF2002_MVS_FILL

#define KOF2003_ESSENTIALPATCH_MODS_FILL \
    KOF2003_MVS_FILL

#define KOTM_ESSENTIALPATCH_MODS_FILL \
    KOTM_MVS_FILL

#define KOTMH_ESSENTIALPATCH_MODS_FILL \
    KOTMH_MVS_FILL

#define KOTM2_ESSENTIALPATCH_MODS_FILL \
    KOTM2_MVS_FILL

#define LANS2004_ESSENTIALPATCH_MODS_FILL \
    LANS2004_MVS_FILL

#define LASTBLAD_ESSENTIALPATCH_MODS_FILL \
    LASTBLAD_MVS_FILL

#define LASTSOLD_ESSENTIALPATCH_MODS_FILL \
    LASTSOLD_MVS_FILL

#define LASTBLD2_ESSENTIALPATCH_MODS_FILL \
    LASTBLD2_MVS_FILL

#define LBOWLING_ESSENTIALPATCH_MODS_FILL \
    LBOWLING_MVS_FILL

#define LEGENDOS_ESSENTIALPATCH_MODS_FILL \
    LEGENDOS_MVS_FILL

#define LRESORT_ESSENTIALPATCH_MODS_FILL \
    LRESORT_MVS_FILL

#define MAGDROP2_ESSENTIALPATCH_MODS_FILL \
    MAGDROP2_MVS_FILL

#define MAGDROP3_ESSENTIALPATCH_MODS_FILL \
    MAGDROP3_MVS_FILL

#define MAGLORD_ESSENTIALPATCH_MODS_FILL \
    MAGLORD_MVS_FILL

#define MAHRETSU_ESSENTIALPATCH_MODS_FILL \
    MAHRETSU_MVS_FILL

#define MARUKODQ_ESSENTIALPATCH_MODS_FILL \
    MARUKODQ_MVS_FILL

#define MATRIM_ESSENTIALPATCH_MODS_FILL \
    MATRIM_MVS_FILL

#define MIEXCHNG_ESSENTIALPATCH_MODS_FILL \
    MIEXCHNG_MVS_FILL

#define MSLUG_ESSENTIALPATCH_MODS_FILL \
    MSLUG_FLASHOFF_MODS_FILL \
	MSLUG_MVS_FILL \
    MSLUG_AES_FILL

#define MSLUGFC_ESSENTIALPATCH_MODS_FILL \
    MSLUG_FLASHOFF_MODS_FILL \
    MSLUG_ENABLE_HP_DAMAGE_FIX_FILL \
	MSLUG_MVS_FILL \
    MSLUG_AES_FILL

#define MSLUGALI_ESSENTIALPATCH_MODS_FILL \
    MSLUG_FLASHOFF_MODS_FILL \
    MSLUG_RESTORING_TITLE_FIX_FILL \
	MSLUG_MVS_FILL \
    MSLUG_AES_FILL

#define MSLUG2_ESSENTIALPATCH_MODS_FILL \
    MSLUG2_FLASHOFF_MODS_FILL \
	MSLUG2_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG2_MVS_FILL \
	MSLUG2_AES_FILL

#define MSLUG2CT_ESSENTIALPATCH_MODS_FILL \
    MSLUG2_FLASHOFF_MODS_FILL \
	MSLUG2_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG2CT_MVS_FILL \
	MSLUG2_AES_FILL

#define MSLUG2AT_ESSENTIALPATCH_MODS_FILL \
    MSLUG2_DISABLEMODTURBO_MODS_FILL \
	MSLUG2_THEYTEARYOUAPARTWHENITDIES_MODS_FILL \
	MSLUG2_CUZTOMWEAPONANIMATION_MODS_FILL \
	MSLUG2AT_PLAYERS_CHANGING_UNIFORM_MODS_FILL \
	MSLUG2AT_SOLDIERSHIELD_CHANGING_UNIFORM_MODS_FILL \
	MSLUG2_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG2_BOSS_MODS_FILL \
	MSLUG2AT_MVS_FILL \
    MSLUG2_AES_FILL

#define MSLUG3H_ESSENTIALPATCH_MODS_FILL \
    MSLUG3H_FLASHOFF_MODS_FILL \
    MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3H_MVS_FILL \
    MSLUG3H_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3B6_ESSENTIALPATCH_MODS_FILL \
    MSLUG3H_FLASHOFF_MODS_FILL \
    MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3B6_MVS_FILL \
    MSLUG3H_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3DD_ESSENTIALPATCH_MODS_FILL \
    MSLUG3H_FLASHOFF_MODS_FILL \
	MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3H_MVS_FILL \
    MSLUG3DD_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3ND_ESSENTIALPATCH_MODS_FILL \
    MSLUG3ND_FIX_FILL \
	MSLUG3H_FLASHOFF_MODS_FILL \
    MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3H_MVS_FILL \
    MSLUG3H_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3G_ESSENTIALPATCH_MODS_FILL \
    MSLUG3G_SOLDIER_CHANGING_UNIFORM_MODS_FILL \
	MSLUG3H_FLASHOFF_MODS_FILL \
    MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3H_MVS_FILL \
    MSLUG3H_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3SD_ESSENTIALPATCH_MODS_FILL \
    MSLUG3H_CHANGEMOVINGPLAYERS_MODS_FILL \
	MSLUG3H_FLASHOFF_MODS_FILL \
    MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3H_MVS_FILL \
    MSLUG3H_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3GW_ESSENTIALPATCH_MODS_FILL \
    MSLUG3H_JUMPATLEVEL5X3_MODS_FILL \
	MSLUG3H_JUMPATLEVEL5X7_MODS_FILL \
    MSLUG3H_FLASHOFF_MODS_FILL \
    MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3H_MVS_FILL \
    MSLUG3H_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3CF_ESSENTIALPATCH_MODS_FILL \
    MSLUG3H_LEVELGAME_PLAYERS_FIX_FILL \
	MSLUG3H_FLASHOFF_MODS_FILL \
    MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3H_MVS_FILL \
    MSLUG3H_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3SC_ESSENTIALPATCH_MODS_FILL \
    MSLUG3H_LIFEMORE_MODS_FILL \
	MSLUG3H_FLASHOFF_MODS_FILL \
    MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3SC_MVS_FILL \
    MSLUG3H_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3CQI_ESSENTIALPATCH_MODS_FILL \
    MSLUG3CQI_RESTORELVXCODE_MODS_FILL \
	MSLUG3H_LIFEMORE_MODS_FILL \
	MSLUG3H_FLASHOFF_MODS_FILL \
    MSLUG3H_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG3SC_MVS_FILL \
    MSLUG3H_AES_FIX_FILL \
	MSLUG3H_AES_FILL

#define MSLUG3ESL_ESSENTIALPATCH_MODS_FILL \
	MSLUG3H_FLASHOFF_MODS_FILL \
	MSLUG3H_MVS_FILL \
	MSLUG3H_AES_FILL

#define MSLUG4_ESSENTIALPATCH_MODS_FILL \
    MSLUG4_FIX_BLACK_BLOCK_ON_THE_SELECTION_SCREEN_MODS_FILL \
    MSLUG4_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG4_FLASHOFF_MODS_FILL \
    MSLUG4_MVS_FILL \
	MSLUG4_AES_FIX_FILL \
	MSLUG4_AES_FILL

#define MSLUG4H_ESSENTIALPATCH_MODS_FILL \
    MSLUG4_FIX_BLACK_BLOCK_ON_THE_SELECTION_SCREEN_MODS_FILL \
    MSLUG4H_FLASHOFF_MODS_FILL \
    MSLUG4_MVS_FILL \
    MSLUG4H_AES_FILL

#define MSLUG4H_NDESSENTIALPATCH_MODS_FILL \
    MSLUG4_FIX_BLACK_BLOCK_ON_THE_SELECTION_SCREEN_MODS_FILL \
    MSLUG4H_FLASHOFF_MODS_FILL \
    MSLUG4_MVS_FILL \
    MSLUG4H_AES_FILL

#define MSLUG4ND_ESSENTIALPATCH_MODS_FILL \
    MSLUG4_FIX_BLACK_BLOCK_ON_THE_SELECTION_SCREEN_MODS_FILL \
    MSLUG4_FLASHOFF_MODS_FILL \
    MSLUG4_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG4ND_MVS_FILL \
    MSLUG4_AES_FIX_FILL \
	MSLUG4_AES_FILL

#define MSLUG4SD_ESSENTIALPATCH_MODS_FILL \
    MSLUG4_CHANGEMOVINGPLAYERS_MODS_FILL \
	MSLUG4_SKIPLEVEL6_FIX_FILL \
	MSLUG4_FIX_BLACK_BLOCK_ON_THE_SELECTION_SCREEN_MODS_FILL \
    MSLUG4_FLASHOFF_MODS_FILL \
    MSLUG4_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG4ND_MVS_FILL \
    MSLUG4_AES_FIX_FILL \
	MSLUG4_AES_FILL

#define MSLUG4CQI_ESSENTIALPATCH_MODS_FILL \
    MSLUG4CQI_RESTORELVXCODE_MODS_FILL \
	MSLUG4_LIFEMORE_MODS_FILL \
	MSLUG4_FIX_BLACK_BLOCK_ON_THE_SELECTION_SCREEN_MODS_FILL \
    MSLUG4_FLASHOFF_MODS_FILL \
    MSLUG4_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG4CQI_MVS_FILL \
    MSLUG4_AES_FIX_FILL \
	MSLUG4_AES_FILL

#define MSLUG5_ESSENTIALPATCH_MODS_FILL \
    MSLUG5_FLASHOFF_MODS_FILL \
	MSLUG5_MVS_FILL \
    MSLUG5_AES_FILL

#define MSLUG5H_ESSENTIALPATCH_MODS_FILL \
    MSLUG5_FLASHOFF_MODS_FILL \
	MSLUG5_MVS_FILL \
    MSLUG5H_AES_FILL

#define MSLUG5ND_ESSENTIALPATCH_MODS_FILL \
    MSLUG5ND_FLASHOFF_MODS_FILL \
    MSLUG5ND_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG5ND_MVS_FILL \
    MSLUG5ND_AES_FIX_FILL \
	MSLUG5ND_AES_FILL

#define MSLUG5HDD_ESSENTIALPATCH_MODS_FILL \
    MSLUG5ND_FLASHOFF_MODS_FILL \
    MSLUG5HDD_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG5ND_MVS_FILL \
    MSLUG5HDD_AES_FIX_FILL \
	MSLUG5HDD_AES_FILL

#define MSLUG5SC_ESSENTIALPATCH_MODS_FILL \
    MSLUG5ND_FLASHOFF_MODS_FILL \
    MSLUG5ND_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG5SC_MVS_FILL \
    MSLUG5ND_AES_FIX_FILL \
	MSLUG5ND_AES_FILL

#define MSLUG5CQ_ESSENTIALPATCH_MODS_FILL \
    MSLUG5CQI_RESTORELVXCODE_MODS_FILL \
	MSLUG5ND_FLASHOFF_MODS_FILL \
    MSLUG5ND_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG5SC_MVS_FILL \
    MSLUG5ND_AES_FIX_FILL \
	MSLUG5ND_AES_FILL

#define MSLUG5MG_ESSENTIALPATCH_MODS_FILL \
    MSLUG5ND_LIFEMORE_MODS_FILL \
	MSLUG5ND_FLASHOFF_MODS_FILL \
    MSLUG5ND_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG5SC_MVS_FILL \
    MSLUG5ND_AES_FIX_FILL \
	MSLUG5ND_AES_FILL

#define MSLUG5ZH_ESSENTIALPATCH_MODS_FILL \
    MSLUG5ZH_JUMPATLEVEL5X5_FIX_FILL \
	MSLUG5ND_FLASHOFF_MODS_FILL \
    MSLUG5ND_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUG5ND_MVS_FILL \
    MSLUG5ND_AES_FIX_FILL \
	MSLUG5ND_AES_FILL

#define MSLUGX_ESSENTIALPATCH_MODS_FILL \
    MSLUGX_FLASHOFF_MODS_FILL \
	MSLUGX_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUGX_MVS_FILL \
    MSLUGX_AES_FIX_FILL \
	MSLUGX_AES_FILL

#define MSLUGXC2_ESSENTIALPATCH_MODS_FILL \
    MSLUGX_HELICOPTER_FIX_FILL \
	MSLUGXC2_ENEMYRESET_FIX_FILL \
	MSLUGX_FLASHOFF_MODS_FILL \
	MSLUGX_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUGX_MVS_FILL \
    MSLUGX_AES_FIX_FILL \
	MSLUGX_AES_FILL

#define MSLUGXLB_ESSENTIALPATCH_MODS_FILL \
    MSLUGX_HELICOPTER_FIX_FILL \
	MSLUGX_FLASHOFF_MODS_FILL \
	MSLUGX_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUGX_MVS_FILL \
    MSLUGX_AES_FIX_FILL \
	MSLUGX_AES_FILL

#define MSLUGXV_ESSENTIALPATCH_MODS_FILL \
    MSLUGX_FLASHOFF_MODS_FILL \
	MSLUGX_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUGXSC_MVS_FILL \
    MSLUGX_AES_FIX_FILL \
	MSLUGX_AES_FILL

#define MSLUGXSC_ESSENTIALPATCH_MODS_FILL \
    MSLUGXSC_FIX_FILL \
	MSLUGX_FLASHOFF_MODS_FILL \
	MSLUGX_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUGXSC_MVS_FILL \
    MSLUGX_AES_FIX_FILL \
	MSLUGX_AES_FILL

#define MSLUGXCQI_ESSENTIALPATCH_MODS_FILL \
    MSLUGXCQI_RESTORELVXCODE_MODS_FILL \
	MSLUGX_FLASHOFF_MODS_FILL \
	MSLUGX_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUGXSC_MVS_FILL \
    MSLUGX_AES_FIX_FILL \
	MSLUGX_AES_FILL

#define MSLUGXAT_ESSENTIALPATCH_MODS_FILL \
    MSLUGX_CUZTOMPATCH_MODS_FILL \
    MSLUGX_CUZTOMWEAPONANIMATION_MODS_FILL \
    MSLUGX_DISABLE_COLORPALETTE_MODS_FILL \
    MSLUGX_DISABLE_ENEMYSPEEDUP_MODS_FILL \
    MSLUGXAT_PLAYERS_CHANGING_UNIFORM_MODS_FILL \
	MSLUGXAT_SOLDIERSHIELD_CHANGING_UNIFORM_MODS_FILL \
	MSLUGX_HELICOPTER_FIX_FILL \
    MSLUGX_DEBUGMENUENGLISHTRANSLATION_MODS_FILL \
	MSLUGXAT_MVS_FILL \
	MSLUGX_AES_FIX_FILL \
	MSLUGX_AES_FILL

#define MINASAN_ESSENTIALPATCH_MODS_FILL \
    MINASAN_MVS_FILL

#define MOSHOUGI_ESSENTIALPATCH_MODS_FILL \
    MOSHOUGI_MVS_FILL

#define MUTNAT_ESSENTIALPATCH_MODS_FILL \
    MUTNAT_MVS_FILL

#define NAM1975_ESSENTIALPATCH_MODS_FILL \
    NAM1975_MVS_FILL

#define NCOMBAT_ESSENTIALPATCH_MODS_FILL \
    NCOMBAT_MVS_FILL

#define NCOMMAND_ESSENTIALPATCH_MODS_FILL \
    NCOMMAND_MVS_FILL

#define NEOBOMBE_ESSENTIALPATCH_MODS_FILL \
    NEOBOMBE_MVS_FILL

#define NEOCUP98_ESSENTIALPATCH_MODS_FILL \
    NEOCUP98_MVS_FILL

#define NEOCUP98KR_ESSENTIALPATCH_MODS_FILL \
    NEOCUP98KR_MVS_FILL

#define NEODRIFT_ESSENTIALPATCH_MODS_FILL \
    NEODRIFT_MVS_FILL

#define NEOMRDO_ESSENTIALPATCH_MODS_FILL \
    NEOMRDO_MVS_FILL

#define NINJAMAS_ESSENTIALPATCH_MODS_FILL \
    NINJAMAS_MVS_FILL

#define NITD_ESSENTIALPATCH_MODS_FILL \
    NITD_MVS_FILL

#define OVERTOP_ESSENTIALPATCH_MODS_FILL \
    OVERTOP_MVS_FILL

#define PANICBOM_ESSENTIALPATCH_MODS_FILL \
    PANICBOM_MVS_FILL

#define PBOBBL2N_ESSENTIALPATCH_MODS_FILL \
    PBOBBL2N_MVS_FILL

#define PBOBBLEN_ESSENTIALPATCH_MODS_FILL \
    PBOBBLEN_MVS_FILL

#define PGOAL_ESSENTIALPATCH_MODS_FILL \
    PGOAL_MVS_FILL

#define PNYAA_ESSENTIALPATCH_MODS_FILL \
    PNYAA_MVS_FILL

#define POPBOUNC_ESSENTIALPATCH_MODS_FILL \
    POPBOUNC_MVS_FILL

#define PREISLE2_ESSENTIALPATCH_MODS_FILL \
    PREISLE2_MVS_FILL

#define PSPIKES2_ESSENTIALPATCH_MODS_FILL \
    PSPIKES2_MVS_FILL

#define PSPIKES2CD_ESSENTIALPATCH_MODS_FILL \
    PSPIKES2CD_MVS_FILL

#define PULSTAR_ESSENTIALPATCH_MODS_FILL \
    PULSTAR_MVS_FILL

#define PUZZLDPR_ESSENTIALPATCH_MODS_FILL \
    PUZZLDPR_MVS_FILL

#define PUZZLDPRKR_ESSENTIALPATCH_MODS_FILL \
    PUZZLDPRKR_MVS_FILL

#define PUZZLEDP_ESSENTIALPATCH_MODS_FILL \
    PUZZLEDP_MVS_FILL

#define PUZZLEDPKR_ESSENTIALPATCH_MODS_FILL \
    PUZZLEDPKR_MVS_FILL

#define QUIZDAI2_ESSENTIALPATCH_MODS_FILL \
    QUIZDAI2_MVS_FILL

#define QUIZDAIS_ESSENTIALPATCH_MODS_FILL \
    QUIZDAIS_MVS_FILL

#define QUIZKOF_ESSENTIALPATCH_MODS_FILL \
    QUIZKOF_MVS_FILL

#define RAGNAGRD_ESSENTIALPATCH_MODS_FILL \
    RAGNAGRD_MVS_FILL

#define RBFF1_ESSENTIALPATCH_MODS_FILL \
    RBFF1_MVS_FILL

#define RBFF2_ESSENTIALPATCH_MODS_FILL \
    RBFF2_MVS_FILL

#define RBFFSPEC_ESSENTIALPATCH_MODS_FILL \
    RBFFSPEC_MVS_FILL

#define RIDHERO_ESSENTIALPATCH_MODS_FILL \
    RIDHERO_MVS_FILL

#define ROBOARMY_ESSENTIALPATCH_MODS_FILL \
    ROBOARMY_MVS_FILL

#define ROTDH_ESSENTIALPATCH_MODS_FILL \
    ROTDH_MVS_FILL

#define S1945P_ESSENTIALPATCH_MODS_FILL \
    S1945P_MVS_FILL

#define SAMSH5SP_ESSENTIALPATCH_MODS_FILL \
    SAMSHO5_MVS_FILL

#define SAMSHO_ESSENTIALPATCH_MODS_FILL \
    SAMSHO_MVS_FILL

#define SAMSHO2_ESSENTIALPATCH_MODS_FILL \
    SAMSHO2_MVS_FILL

#define SAMSHO3_ESSENTIALPATCH_MODS_FILL \
    SAMSHO3_MVS_FILL

#define SAMSHO4_ESSENTIALPATCH_MODS_FILL \
    SAMSHO4_MVS_FILL

#define SAMSHO4K_ESSENTIALPATCH_MODS_FILL \
    SAMSHO4K_MVS_FILL

#define SAMSHO5_ESSENTIALPATCH_MODS_FILL \
    SAMSHO5_MVS_FILL

#define SAVAGERE_ESSENTIALPATCH_MODS_FILL \
    SAVAGERE_MVS_FILL

#define SDODGEB_ESSENTIALPATCH_MODS_FILL \
    SDODGEB_MVS_FILL

#define SENGOKU_ESSENTIALPATCH_MODS_FILL \
    SENGOKU_MVS_FILL

#define SENGOKUH_ESSENTIALPATCH_MODS_FILL \
    SENGOKUH_MVS_FILL

#define SENGOKU2_ESSENTIALPATCH_MODS_FILL \
    SENGOKU2_MVS_FILL

#define SENGOKU3_ESSENTIALPATCH_MODS_FILL \
    SENGOKU3_MVS_FILL

#define SHOCKTRO_ESSENTIALPATCH_MODS_FILL \
    SHOCKTRO_MVS_FILL

#define SHOCKTROA_ESSENTIALPATCH_MODS_FILL \
    SHOCKTROA_MVS_FILL

#define SOCBRAWL_ESSENTIALPATCH_MODS_FILL \
    SOCBRAWL_MVS_FILL

#define SONICWI2_ESSENTIALPATCH_MODS_FILL \
    SONICWI2_MVS_FILL

#define SONICWI3_ESSENTIALPATCH_MODS_FILL \
    SONICWI3_MVS_FILL

#define SPINMAST_ESSENTIALPATCH_MODS_FILL \
    SPINMAST_MVS_FILL

#define SSIDEKI_ESSENTIALPATCH_MODS_FILL \
    SSIDEKI_MVS_FILL

#define SSIDEKI2_ESSENTIALPATCH_MODS_FILL \
    SSIDEKI2_MVS_FILL

#define SSIDEKI3_ESSENTIALPATCH_MODS_FILL \
    SSIDEKI3_MVS_FILL

#define SSIDEKI4_ESSENTIALPATCH_MODS_FILL \
    SSIDEKI4_MVS_FILL

#define STAKWIN_ESSENTIALPATCH_MODS_FILL \
    STAKWIN_MVS_FILL

#define STAKWIN2_ESSENTIALPATCH_MODS_FILL \
    STAKWIN2_MVS_FILL

#define STRHOOP_ESSENTIALPATCH_MODS_FILL \
    STRHOOP_MVS_FILL

#define STRHOOPCD_ESSENTIALPATCH_MODS_FILL \
    STRHOOPCD_MVS_FILL

#define SUPERSPY_ESSENTIALPATCH_MODS_FILL \
    SUPERSPY_MVS_FILL

#define SVC_ESSENTIALPATCH_MODS_FILL \
    SVC_MVS_FILL

#define TOPHUNTR_ESSENTIALPATCH_MODS_FILL \
    TOPHUNTR_MVS_FILL

#define TOPHUNTRKR_ESSENTIALPATCH_MODS_FILL \
    TOPHUNTRKR_MVS_FILL

#define TPGOLF_ESSENTIALPATCH_MODS_FILL \
    TPGOLF_MVS_FILL

#define TRALLY_ESSENTIALPATCH_MODS_FILL \
    TRALLY_MVS_FILL

#define TRALLYCD_ESSENTIALPATCH_MODS_FILL \
    TRALLYCD_MVS_FILL

#define TURFMAST_ESSENTIALPATCH_MODS_FILL \
    TURFMAST_MVS_FILL

#define TWINSPRI_ESSENTIALPATCH_MODS_FILL \
    TWINSPRI_MVS_FILL

#define TWSOC96_ESSENTIALPATCH_MODS_FILL \
    TWSOC96_MVS_FILL

#define VIEWPOIN_ESSENTIALPATCH_MODS_FILL \
    VIEWPOIN_MVS_FILL

#define WAKUWAK7_ESSENTIALPATCH_MODS_FILL \
    WAKUWAK7_MVS_FILL

#define WH1_ESSENTIALPATCH_MODS_FILL \
    WH1_MVS_FILL

#define WH2_ESSENTIALPATCH_MODS_FILL \
    WH2_MVS_FILL

#define WH2J_ESSENTIALPATCH_MODS_FILL \
    WH2J_MVS_FILL

#define WHP_ESSENTIALPATCH_MODS_FILL \
    WHP_MVS_FILL

#define WJAMMERS_ESSENTIALPATCH_MODS_FILL \
    WJAMMERS_MVS_FILL

#define WJAMMERSKR_ESSENTIALPATCH_MODS_FILL \
    WJAMMERSKR_MVS_FILL

#define ZEDBLADE_ESSENTIALPATCH_MODS_FILL \
    ZEDBLADE_MVS_FILL

#define ZINTRCKB_ESSENTIALPATCH_MODS_FILL \
    ZINTRCKB_MVS_FILL

#define ZUPAPA_ESSENTIALPATCH_MODS_FILL \
    ZUPAPA_MVS_FILL

/*************************************
    Game specific input definitions
 *************************************/
 
INPUT_PORTS_START( dualbios )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x04, 0x00, DEF_STR( Region ) ) PORT_DIPLOCATION("SW:3") PORT_CHANGED_MEMBER(DEVICE_SELF, neogeo_state, select_bios, 0)
	PORT_DIPSETTING(    0x00, DEF_STR( Asia ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Japan ) )
INPUT_PORTS_END

/* The default Joystick mod has been changed because it causes a bug in the commands Mahjong due to conflicts with autofire. */
INPUT_PORTS_START( mahjong )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Controller ) ) PORT_DIPLOCATION("SW:3")
	PORT_DIPSETTING(    0x00, DEF_STR( Joystick ) )
	PORT_DIPSETTING(    0x00, "Mahjong Panel" )
INPUT_PORTS_END

INPUT_PORTS_START( kizuna4p )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x02, 0x00, DEF_STR( Players ) ) PORT_DIPLOCATION("SW:2")
	PORT_DIPSETTING(    0x02, "2" )
	PORT_DIPSETTING(    0x00, "4" )

	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x0f00, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_CUSTOM_MEMBER(neogeo_state, kizuna4p_start_r)
INPUT_PORTS_END

INPUT_PORTS_START( irrmaze )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_UNUSED )
INPUT_PORTS_END

INPUT_PORTS_START( vliner )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN )
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT )
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_NAME("View Payout Table/Big")
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_NAME("Bet/Small")
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_NAME("Stop/Double Up")
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_NAME("Start/Collect")

	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_UNKNOWN ) /* this bit is used.. */
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_UNKNOWN ) /* this bit is used.. */

	PORT_MODIFY("AUDIO_COIN")
	PORT_BIT( 0x003f, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN5")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Operator Menu") PORT_CODE(KEYCODE_F1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON5 ) PORT_NAME("Clear Credit")
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_BUTTON6 ) PORT_NAME("Hopper Out")
	PORT_BIT( 0xff00, IP_ACTIVE_LOW, IPT_UNKNOWN )

	/* not sure what any of these bits are */
	PORT_START("IN6")
	PORT_BIT( 0x0003, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0xffc0, IP_ACTIVE_HIGH, IPT_UNKNOWN )
INPUT_PORTS_END

INPUT_PORTS_START( jockeygp )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_UNKNOWN ) /* game freezes with this bit enabled */
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_UNKNOWN ) /* game freezes with this bit enabled */
INPUT_PORTS_END
