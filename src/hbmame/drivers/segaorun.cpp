// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/segaorun.cpp"

/***************************** OUTRUNM *********************************************/

//  sound_bank0_w and sound_bank1_w -
//  handle sound board banking the entire z80 60k rom space
//  to the first or second half of the 128k sound rom space
//  This does not work on the original outrun boardset;
//  The PAL/GAL/PLS chip which handles the z80 address/io
//  decoding has to be replaced and 3 flying wires added.

#include "machine/bankdev.h"

class outrunm_state : public segaorun_state
{
public:
	outrunm_state(const machine_config &mconfig, device_type type, const char *tag)
		: segaorun_state(mconfig, type, tag)
		, m_soundbank(*this, "soundbank")
		{ }

	void init_init();
	void outrunm(machine_config &config);

private:

	void sound_map_banked(address_map &map);
	void sound_portmap_banked(address_map &map);
	void soundbank_map(address_map &map);
	required_device<address_map_bank_device> m_soundbank;
};


void outrunm_state::sound_map_banked(address_map &map) {
	map.unmap_value_high();
	map(0x0000,0xefff).m(m_soundbank,FUNC(address_map_bank_device::amap8));
	map(0xf000,0xf0ff).mirror(0x0700).rw("pcm",FUNC(segapcm_device::read),FUNC(segapcm_device::write));
	map(0xf800,0xffff).ram();
}

void outrunm_state::sound_portmap_banked(address_map &map) {
	map.unmap_value_high();
	map.global_mask(0xff);
	map(0x00,0x01).mirror(0x3e).rw("ymsnd",FUNC(ym2151_device::read),FUNC(ym2151_device::write));
	map(0x40,0x7f).r("mapper",FUNC(sega_315_5195_mapper_device::pread));
	map(0x80,0xbf).lw8(NAME([this](u8 data) { m_soundbank->set_bank(0); } ));
	map(0xc0,0xff).lw8(NAME([this](u8 data) { m_soundbank->set_bank(1); } ));
}

void outrunm_state::soundbank_map(address_map &map) {
	map.unmap_value_high();
	map(0x0000,0x1ffff).rom().region("soundcpu",0);
}

void outrunm_state::outrunm(machine_config &config)
{
	outrun(config);
	m_soundcpu->set_addrmap(AS_PROGRAM, &outrunm_state::sound_map_banked);
	m_soundcpu->set_addrmap(AS_IO, &outrunm_state::sound_portmap_banked);

	ADDRESS_MAP_BANK(config, m_soundbank, 0);
	m_soundbank->set_map(&outrunm_state::soundbank_map);
	m_soundbank->set_endianness(ENDIANNESS_LITTLE);
	m_soundbank->set_data_width(8);
	m_soundbank->set_addr_width(17);
	m_soundbank->set_stride(0x10000);
}

void outrunm_state::init_init()
{
	init_generic();
	m_custom_io_r = read16m_delegate(*this, FUNC(outrunm_state::outrun_custom_io_r));
	m_custom_io_w = write16s_delegate(*this, FUNC(outrunm_state::outrun_custom_io_w));
}

 /*******
 Out Run
**********/

ROM_START( outrunm )
	ROM_REGION( 0x60000, "maincpu", 0 ) // 68000 code
	ROM_LOAD16_BYTE( "music-epr-10380b.133", 0x00000, 0x10000, CRC(9bf1d4df) SHA1(4d4be736c25f0e2f60851d26150ed6807014466a) ) // new
	ROM_LOAD16_BYTE( "music-epr-10382b.118", 0x00001, 0x10000, CRC(86f90666) SHA1(e6a40afdbd5390266e9b43073cb41ec38b01d67c) ) // new
	ROM_LOAD16_BYTE( "music-epr-10381b.132", 0x20000, 0x10000, CRC(cbec3f7e) SHA1(094d23afccf52bd25ae9ae9fdb9087cf3ac41709) ) // new
	ROM_LOAD16_BYTE( "music-epr-10383b.117", 0x20001, 0x10000, CRC(e3c5cdca) SHA1(629dac90615deb2f68368012d5c67442b93c39b3) ) // new

	ROM_REGION( 0x60000, "subcpu", 0 ) // second 68000 CPU
	ROM_LOAD16_BYTE( "epr-10327a.76", 0x00000, 0x10000, CRC(e28a5baf) SHA1(f715bde96c73ed47035acf5a41630fdeb41bb2f9) )
	ROM_LOAD16_BYTE( "epr-10329a.58", 0x00001, 0x10000, CRC(da131c81) SHA1(57d5219bd0e2fd886217e37e8773fd76be9b40eb) )
	ROM_LOAD16_BYTE( "epr-10328a.75", 0x20000, 0x10000, CRC(d5ec5e5d) SHA1(a4e3cfca4d803e72bc4fcf91ab00e21bf3f8959f) )
	ROM_LOAD16_BYTE( "epr-10330a.57", 0x20001, 0x10000, CRC(ba9ec82a) SHA1(2136c9572e26b7ae6de402c0cd53174407cc6018) )

	ROM_REGION( 0x30000, "gfx1", 0 ) // tiles
	ROM_LOAD( "opr-10268.99",  0x00000, 0x08000, CRC(95344b04) SHA1(b3480714b11fc49b449660431f85d4ba92f799ba) )
	ROM_LOAD( "opr-10232.102", 0x08000, 0x08000, CRC(776ba1eb) SHA1(e3477961d19e694c97643066534a1f720e0c4327) )
	ROM_LOAD( "opr-10267.100", 0x10000, 0x08000, CRC(a85bb823) SHA1(a7e0143dee5a47e679fd5155e58e717813912692) )
	ROM_LOAD( "opr-10231.103", 0x18000, 0x08000, CRC(8908bcbf) SHA1(8e1237b640a6f26bdcbfd5e201dadb2687c4febb) )
	ROM_LOAD( "opr-10266.101", 0x20000, 0x08000, CRC(9f6f1a74) SHA1(09164e858ebeedcff4d389524ddf89e7c216dcae) )
	ROM_LOAD( "opr-10230.104", 0x28000, 0x08000, CRC(686f5e50) SHA1(03697b892f911177968aa40de6c5f464eb0258e7) )

	ROM_REGION32_LE( 0x100000, "sprites", 0 ) // sprites
	// VIDEO BD 837-6064-02 uses mask roms four times the size of those used on VIDEO BD 837-6064-01, same data
	ROM_LOAD32_BYTE( "mpr-10371.9",  0x00000, 0x20000, CRC(7cc86208) SHA1(21320f945f7c8e990c97c9b1232a0f4b6bd00f8f) )
	ROM_LOAD32_BYTE( "mpr-10373.10", 0x00001, 0x20000, CRC(b0d26ac9) SHA1(3a9ce8547cd43b7b04abddf9a9ab5634e0bbfaba) )
	ROM_LOAD32_BYTE( "mpr-10375.11", 0x00002, 0x20000, CRC(59b60bd7) SHA1(e5d8c67e020608edd24ba87b7687b2ac2483ee7f) )
	ROM_LOAD32_BYTE( "mpr-10377.12", 0x00003, 0x20000, CRC(17a1b04a) SHA1(9f7210cb4153ac9029a785dcd4b45f4513a4b008) )
	ROM_LOAD32_BYTE( "mpr-10372.13", 0x80000, 0x20000, CRC(b557078c) SHA1(a3746a2da077a8df4932348f650a061f413e8430) )
	ROM_LOAD32_BYTE( "mpr-10374.14", 0x80001, 0x20000, CRC(8051e517) SHA1(9c8509fbed170b4ac74c169da573393e54774f49) )
	ROM_LOAD32_BYTE( "mpr-10376.15", 0x80002, 0x20000, CRC(f3b8f318) SHA1(a5f2532613f33a64441e0f75443c10ba78dccc6e) )
	ROM_LOAD32_BYTE( "mpr-10378.16", 0x80003, 0x20000, CRC(a1062984) SHA1(4399030a155caf71f2dec7f75c4b65531ab53576) )

	ROM_REGION( 0x10000, "segaic16road", 0 ) // road gfx (2 identical roms, 1 for each road)
	ROM_LOAD( "opr-10186.47", 0x0000, 0x8000, CRC(22794426) SHA1(a554d4b68e71861a0d0da4d031b3b811b246f082) )
	ROM_LOAD( "opr-10185.11", 0x8000, 0x8000, CRC(22794426) SHA1(a554d4b68e71861a0d0da4d031b3b811b246f082) )

	ROM_REGION( 0x20000, "soundcpu", 0 ) // sound CPU
	ROM_LOAD( "music-epr-10187.88", 0x00000, 0x20000, CRC(9f89439e) SHA1(a7c7610327e91647b41d73635a87ef2b95eee698) ) // new

	ROM_REGION( 0x80000, "pcm", ROMREGION_ERASEFF ) // sound PCM data
	ROM_LOAD( "opr-10193.66", 0x00000, 0x08000, CRC(bcd10dde) SHA1(417ce1d7242884640c5b14f4db8ee57cde7d085d) )
	ROM_RELOAD(               0x08000, 0x08000 )
	ROM_LOAD( "opr-10192.67", 0x10000, 0x08000, CRC(770f1270) SHA1(686bdf44d45c1d6002622f6658f037735382f3e0) )
	ROM_RELOAD(               0x18000, 0x08000 )
	ROM_LOAD( "opr-10191.68", 0x20000, 0x08000, CRC(20a284ab) SHA1(7c9027416d4122791ba53782fe2230cf02b7d506) )
	ROM_RELOAD(               0x28000, 0x08000 )
	ROM_LOAD( "opr-10190.69", 0x30000, 0x08000, CRC(7cab70e2) SHA1(a3c581d2b438630d0d4c39481dcfd85681c9f889) )
	ROM_RELOAD(               0x38000, 0x08000 )
	ROM_LOAD( "opr-10189.70", 0x40000, 0x08000, CRC(01366b54) SHA1(f467a6b807694d5832a985f5381c170d24aaee4e) )
	ROM_RELOAD(               0x48000, 0x08000 )
	ROM_LOAD( "opr-10188a.71", 0x50000, 0x08000, CRC(c2de09b2) SHA1(00777e08ad8eddd48fe58686d4d1db68a78d3d6f) ) // new, recovered data from sega development disk
	ROM_RELOAD(               0x58000, 0x08000 )
ROM_END

ROM_START( outrunen )
	ROM_REGION( 0x60000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "outrunen.133", 0x000000, 0x10000, CRC(90e6ecec) SHA1(a2dfb4934770c107504f358e0b0c1ed6b4dece40) )
	ROM_LOAD16_BYTE( "outrunen.118", 0x000001, 0x10000, CRC(e227af3c) SHA1(f5387d50b6c1cfa426b89aaaef521217e8c6530a) )
	ROM_LOAD16_BYTE( "outrunen.132", 0x020000, 0x10000, CRC(0c87bce3) SHA1(25bdbd94d4574d90214a1df9d5a9c56f43675aaf) )
	ROM_LOAD16_BYTE( "outrunen.117", 0x020001, 0x10000, CRC(28a5e93e) SHA1(7dda2eef158783562b17fd57ad1a94f061e34d5d) )

	ROM_REGION( 0x60000, "subcpu", 0 )
	ROM_LOAD16_BYTE( "epr-10327a.76", 0x00000, 0x10000, CRC(e28a5baf) SHA1(f715bde96c73ed47035acf5a41630fdeb41bb2f9) )
	ROM_LOAD16_BYTE( "epr-10329a.58", 0x00001, 0x10000, CRC(da131c81) SHA1(57d5219bd0e2fd886217e37e8773fd76be9b40eb) )
	ROM_LOAD16_BYTE( "epr-10328a.75", 0x20000, 0x10000, CRC(d5ec5e5d) SHA1(a4e3cfca4d803e72bc4fcf91ab00e21bf3f8959f) )
	ROM_LOAD16_BYTE( "epr-10330a.57", 0x20001, 0x10000, CRC(ba9ec82a) SHA1(2136c9572e26b7ae6de402c0cd53174407cc6018) )

	ROM_REGION( 0x30000, "gfx1", 0 )
	ROM_LOAD( "opr-10268.99",  0x00000, 0x08000, CRC(95344b04) SHA1(b3480714b11fc49b449660431f85d4ba92f799ba) )
	ROM_LOAD( "opr-10232.102", 0x08000, 0x08000, CRC(776ba1eb) SHA1(e3477961d19e694c97643066534a1f720e0c4327) )
	ROM_LOAD( "opr-10267.100", 0x10000, 0x08000, CRC(a85bb823) SHA1(a7e0143dee5a47e679fd5155e58e717813912692) )
	ROM_LOAD( "opr-10231.103", 0x18000, 0x08000, CRC(8908bcbf) SHA1(8e1237b640a6f26bdcbfd5e201dadb2687c4febb) )
	ROM_LOAD( "opr-10266.101", 0x20000, 0x08000, CRC(9f6f1a74) SHA1(09164e858ebeedcff4d389524ddf89e7c216dcae) )
	ROM_LOAD( "opr-10230.104", 0x28000, 0x08000, CRC(686f5e50) SHA1(03697b892f911177968aa40de6c5f464eb0258e7) )

	ROM_REGION32_LE( 0x100000, "sprites", 0 )
	ROM_LOAD32_BYTE( "mpr-10371.9",  0x00000, 0x20000, CRC(7cc86208) SHA1(21320f945f7c8e990c97c9b1232a0f4b6bd00f8f) )
	ROM_LOAD32_BYTE( "mpr-10373.10", 0x00001, 0x20000, CRC(b0d26ac9) SHA1(3a9ce8547cd43b7b04abddf9a9ab5634e0bbfaba) )
	ROM_LOAD32_BYTE( "mpr-10375.11", 0x00002, 0x20000, CRC(59b60bd7) SHA1(e5d8c67e020608edd24ba87b7687b2ac2483ee7f) )
	ROM_LOAD32_BYTE( "mpr-10377.12", 0x00003, 0x20000, CRC(17a1b04a) SHA1(9f7210cb4153ac9029a785dcd4b45f4513a4b008) )
	ROM_LOAD32_BYTE( "mpr-10372.13", 0x80000, 0x20000, CRC(b557078c) SHA1(a3746a2da077a8df4932348f650a061f413e8430) )
	ROM_LOAD32_BYTE( "mpr-10374.14", 0x80001, 0x20000, CRC(8051e517) SHA1(9c8509fbed170b4ac74c169da573393e54774f49) )
	ROM_LOAD32_BYTE( "mpr-10376.15", 0x80002, 0x20000, CRC(f3b8f318) SHA1(a5f2532613f33a64441e0f75443c10ba78dccc6e) )
	ROM_LOAD32_BYTE( "mpr-10378.16", 0x80003, 0x20000, CRC(a1062984) SHA1(4399030a155caf71f2dec7f75c4b65531ab53576) )

	ROM_REGION( 0x10000, "segaic16road", 0 ) // road gfx (2 identical roms, 1 for each road)
	ROM_LOAD( "opr-10186.47", 0x0000, 0x8000, CRC(22794426) SHA1(a554d4b68e71861a0d0da4d031b3b811b246f082) )
	ROM_LOAD( "opr-10185.11", 0x8000, 0x8000, CRC(22794426) SHA1(a554d4b68e71861a0d0da4d031b3b811b246f082) )

	ROM_REGION( 0x10000, "soundcpu", 0 )
	ROM_LOAD( "epr-10187.88", 0x00000, 0x8000, CRC(a10abaa9) SHA1(01c8a819587a66d2ee4d255656e36fa0904377b0) )

	ROM_REGION( 0x80000, "pcm", ROMREGION_ERASEFF )
	ROM_LOAD( "opr-10193.66", 0x00000, 0x08000, CRC(bcd10dde) SHA1(417ce1d7242884640c5b14f4db8ee57cde7d085d) )
	ROM_RELOAD(               0x08000, 0x08000 )
	ROM_LOAD( "opr-10192.67", 0x10000, 0x08000, CRC(770f1270) SHA1(686bdf44d45c1d6002622f6658f037735382f3e0) )
	ROM_RELOAD(               0x18000, 0x08000 )
	ROM_LOAD( "opr-10191.68", 0x20000, 0x08000, CRC(20a284ab) SHA1(7c9027416d4122791ba53782fe2230cf02b7d506) )
	ROM_RELOAD(               0x28000, 0x08000 )
	ROM_LOAD( "opr-10190.69", 0x30000, 0x08000, CRC(7cab70e2) SHA1(a3c581d2b438630d0d4c39481dcfd85681c9f889) )
	ROM_RELOAD(               0x38000, 0x08000 )
	ROM_LOAD( "opr-10189.70", 0x40000, 0x08000, CRC(01366b54) SHA1(f467a6b807694d5832a985f5381c170d24aaee4e) )
	ROM_RELOAD(               0x48000, 0x08000 )
	ROM_LOAD( "outrunen.71",  0x50000, 0x08000, CRC(37598616) SHA1(e7c8ae6c59742e1de7ec5a95c5aebfab5716d959) )
	ROM_RELOAD(               0x58000, 0x08000 )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Out Run
GAMEL(2016, outrunm,   outrun, outrunm, outrun, outrunm_state,  init_init,   ROT0, "cmonkey",                      "Out Run (Added Music)(sitdown/upright, Rev B)", 0, layout_outrun ) // March? 2016
GAMEL(2012, outrunen,  outrun, outrun,  outrun, segaorun_state, init_outrun, ROT0, "Chris White and Darren Finck", "Out Run (Enhanced Edition v1.0.3)(sitdown/upright, Rev B)", 0, layout_outrun )
