// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/taito_f3.cpp"

 /*****************
 Cleopatra Fortune
********************/

ROM_START( cleopatrhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("e28-10_hack01.bin", 0x000000, 0x80000, CRC(20bb1f31) SHA1(48e24d0b2aa3cc06db8ccbe05e5d48e0a46de239) )
	ROM_LOAD32_BYTE("e28-09_hack01.bin", 0x000001, 0x80000, CRC(a5811b99) SHA1(0ce61e9e093f002d331a5b822b19b86fb3cc6d40) )
	ROM_LOAD32_BYTE("e28-08_hack01.bin", 0x000002, 0x80000, CRC(32f4bd9d) SHA1(8b7aa973cc4db466c791ee61633a76e5ec1f1897) )
	ROM_LOAD32_BYTE("e28-07_hack01.bin", 0x000003, 0x80000, CRC(16eab942) SHA1(b2cf401ade7280f1789c27a24046421fea5e8a94) )

	ROM_REGION(0x100000, "sprites" , 0)
	ROM_LOAD16_BYTE("e28-02_hack01.bin", 0x000000, 0x080000, CRC(1f9eda37) SHA1(9288df554eaeccbcf231fc2245d87aebf8e0c137) )
	ROM_LOAD16_BYTE("e28-01_hack01.bin", 0x000001, 0x080000, CRC(e1fab776) SHA1(933d83685d1c5585d7b5799759ce38c5df98a709) )

	EMPTY_SPRITE_HIDATA(0x080000)

	ROM_REGION(0x200000, "tilemap" , 0)
	ROM_LOAD32_WORD("e28-06_hack01.bin", 0x000000, 0x100000, CRC(07f83157) SHA1(b39edbb4de4790b808a4be7d0761b7666006e6b4) )
	ROM_LOAD32_WORD("e28-05_hack01.bin", 0x000002, 0x100000, CRC(e40904c9) SHA1(90291ca27a592adf493a459a89cb43b166857157) )

	ROM_REGION( 0x100000, "tilemap_hi", 0 )
	ROM_LOAD       ("e28-04.bin", 0x000000, 0x100000, CRC(57aef029) SHA1(5c07209015d4749d1ffb3e9c1a890e6cfeec8cb0) )

	ROM_REGION(0x140000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("e28-11.bin", 0x100000, 0x20000, CRC(01a06950) SHA1(94d22cd839f9027e9d45264c366e0cb5d698e0b6) )
	ROM_LOAD16_BYTE("e28-12.bin", 0x100001, 0x20000, CRC(dc19260f) SHA1(fa0ca03a236326652e4f9898d07cd837c1507a9d) )

	ROM_REGION16_BE(0x400000, "ensoniq.0" , ROMREGION_ERASE00 ) // V2: 4 banks, only 1 populated
	ROM_LOAD16_BYTE("e28-03.bin", 0x000000, 0x200000, CRC(15c7989d) SHA1(7cc63d93e5c1f9f52f889e973bbefd5e6f7ce807) )
ROM_END

ROM_START( cleopatrhack02 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("e28-10.bin", 0x000000, 0x80000, CRC(013fbc39) SHA1(d36ac44609b88e1da35c98dda381042e0112ea00) )
	ROM_LOAD32_BYTE("e28-09.bin", 0x000001, 0x80000, CRC(1c48a1f9) SHA1(791d321c03073cdd0269b970f926897446d2a6fb) )
	ROM_LOAD32_BYTE("e28-08.bin", 0x000002, 0x80000, CRC(7564f199) SHA1(ec4b19edb0660ad478f6c0ec27d701368696a2e4) )
	ROM_LOAD32_BYTE("e28-07_hack02.bin", 0x000003, 0x80000, CRC(544dd2e9) SHA1(11ad1ce4202937108f23c44de2244da570452ce1) )

	ROM_REGION(0x100000, "sprites" , 0)
	ROM_LOAD16_BYTE("e28-02.bin", 0x000000, 0x080000, CRC(b20d47cb) SHA1(6888e5564688840fed1c123ab38467066cd59c7f) )
	ROM_LOAD16_BYTE("e28-01.bin", 0x000001, 0x080000, CRC(4440e659) SHA1(71dece81bac8d638473c6531fed5c32798096af9) )

	EMPTY_SPRITE_HIDATA(0x080000)

	ROM_REGION(0x200000, "tilemap" , 0)
	ROM_LOAD32_WORD("e28-06.bin", 0x000000, 0x100000, CRC(21d0c454) SHA1(f4c815984b19321cfab303fa6f21d9cad35b09f2) )
	ROM_LOAD32_WORD("e28-05.bin", 0x000002, 0x100000, CRC(2870dbbc) SHA1(4e412b90cbd9a05956cde3d8cff615ebadca9db6) )

	ROM_REGION( 0x100000, "tilemap_hi", 0 )
	ROM_LOAD       ("e28-04.bin", 0x000000, 0x100000, CRC(57aef029) SHA1(5c07209015d4749d1ffb3e9c1a890e6cfeec8cb0) )

	ROM_REGION(0x140000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("e28-11.bin", 0x100000, 0x20000, CRC(01a06950) SHA1(94d22cd839f9027e9d45264c366e0cb5d698e0b6) )
	ROM_LOAD16_BYTE("e28-12.bin", 0x100001, 0x20000, CRC(dc19260f) SHA1(fa0ca03a236326652e4f9898d07cd837c1507a9d) )

	ROM_REGION16_BE(0x400000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("e28-03.bin", 0x000000, 0x200000, CRC(15c7989d) SHA1(7cc63d93e5c1f9f52f889e973bbefd5e6f7ce807) )
ROM_END

 /**********
 Akkanbeder
*************/

ROM_START( akkanvdrhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("e06-14_hack01.20", 0x000000, 0x20000, CRC(f1f71f95) SHA1(b0d44fb3972f3b844855a9778df2d4bd026e5403) )
	ROM_LOAD32_BYTE("e06-13_hack01.19", 0x000001, 0x20000, CRC(5e94d31b) SHA1(631607d4283dbbb9c8e6b3a71d742ef8f24887c5) )
	ROM_LOAD32_BYTE("e06-12_hack01.18", 0x000002, 0x20000, CRC(eccc4cc4) SHA1(1d7317c8c58db9e4a95b3eed4474e8c04ece7444) )
	ROM_LOAD32_BYTE("e06-11_hack01.17", 0x000003, 0x20000, CRC(ee3e952d) SHA1(5fd7db1bcb060b2efcb8ab0805f8e15c456cfb2c) )

	ROM_REGION(0x200000, "sprites" , 0)
	ROM_LOAD16_BYTE("e06-03_hack01", 0x000000, 0x100000, CRC(6565b5c7) SHA1(5dc548dfd498ef6771b942168eb6d7d6e262912c) )
	ROM_LOAD16_BYTE("e06-02_hack01", 0x000001, 0x100000, CRC(eae1fe61) SHA1(90f9477883ae3d4f7a2947acf748de4364b63384) )

	ROM_REGION( 0x100000, "sprites_hi", 0 )
	ROM_LOAD       ("e06-01_hack01", 0x000000, 0x100000, CRC(b2091836) SHA1(a849fbe0f6db36e76ca20de7f5b96bd60a139905) )

	ROM_REGION(0x200000, "tilemap" , 0)
	ROM_LOAD32_WORD("e06-08_hack01", 0x000000, 0x100000, CRC(882c4fe4) SHA1(f5b80d498fcd42725b8c96afdfb2cb7e0a4195fb) )
	ROM_LOAD32_WORD("e06-07_hack01", 0x000002, 0x100000, CRC(c11cd737) SHA1(d597b53ad7739665fd4265177719fc57a1af0199) )

	ROM_REGION( 0x100000, "tilemap_hi", 0 )
	ROM_LOAD       ("e06-06_hack01", 0x000000, 0x100000, CRC(c1cd5367) SHA1(0560f033169145f12d80211e4210399abda2a0e5) )

	ROM_REGION(0x180000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("e06-09.32", 0x100000, 0x40000, CRC(9bcafc87) SHA1(10b3f6da00a41550fe6a705232f0e33fda3c7e7c) )
	ROM_LOAD16_BYTE("e06-10.33", 0x100001, 0x40000, CRC(b752b61f) SHA1(e948a8af19c70ba8b8e908c869bc88ed0cac8420) )

	ROM_REGION16_BE(0x800000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("e06-04", 0x000000, 0x200000, CRC(1dac29df) SHA1(ed68a41def148dcf4057cfac87a2a563c6882e1d) )
	ROM_LOAD16_BYTE("e06-05", 0x400000, 0x200000, CRC(f370ff15) SHA1(4bc464d1c3a28326c8b1ae2036387954cb1dd813) )
ROM_END

 /**********
 Akkanbeder
*************/

ROM_START( arabianmhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("d29-23_hack01.ic40", 0x000000, 0x40000, CRC(dd54b8ed) SHA1(2584ae22e52d2f5990cf0857ddd5707f8df4beb0) )
	ROM_LOAD32_BYTE("d29-22_hack01.ic38", 0x000001, 0x40000, CRC(4605b9e1) SHA1(0d050754c37fdab7596385daf242054d50882872) )
	ROM_LOAD32_BYTE("d29-21_hack01.ic36", 0x000002, 0x40000, CRC(b3b115c1) SHA1(31a7abf491c8cc568415d8684584137041c7c6b9) )
	ROM_LOAD32_BYTE("d29-20_hack01.ic34", 0x000003, 0x40000, CRC(e2725176) SHA1(fe738d76efd491cf449909470a5c7f5023de6e38) )

	ROM_REGION(0x200000, "sprites" , 0)
	ROM_LOAD16_BYTE("d29-03_hack01.ic66", 0x000000, 0x100000, CRC(281fd530) SHA1(6db5095ae49b12709086010fa112500e45901081) )
	ROM_LOAD16_BYTE("d29-04_hack01.ic67", 0x000001, 0x100000, CRC(29dc7a2d) SHA1(2cf49f7680fead656f474442a4f0c8fd403d79a1) )

	ROM_REGION( 0x100000, "sprites_hi", 0 )
	ROM_LOAD       ("d29-05_hack01.ic68", 0x000000, 0x100000, CRC(445b2514) SHA1(2fd20bab02bd0bf242ef6c35ea2dc65c0e44ee91) )

	ROM_REGION(0x100000, "tilemap" , 0)
	ROM_LOAD32_WORD("d29-06_hack01.ic49", 0x000000, 0x080000, CRC(7dc3841a) SHA1(fb13be3adf2d6eea628cda3b374c7c42766dfb76) )
	ROM_LOAD32_WORD("d29-07_hack01.ic50", 0x000002, 0x080000, CRC(1716b706) SHA1(629698dcc7be88dffb70a9eb065542b7f2848812) )

	ROM_REGION( 0x080000, "tilemap_hi", 0 )
	ROM_LOAD       ("d29-08_hack01.ic51", 0x000000, 0x080000, CRC(531ef983) SHA1(89d072c285677f35ca3564f7dc4018e2f0410ee6) )

	ROM_REGION(0x140000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("d29-18.ic5", 0x100000, 0x20000, CRC(d97780df) SHA1(d0f9d2fd7ce13f620bb44083bf012f67dda4b10b) )
	ROM_LOAD16_BYTE("d29-19.ic6", 0x100001, 0x20000, CRC(b1ad365c) SHA1(1cd26d8feaaa06b50dfee32e9b7950b8ee92ac55) )

	ROM_REGION16_BE(0x800000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("d29-01.ic17", 0x000000, 0x200000, CRC(545ac4b3) SHA1(f89513fca8a03cab11160aa1f0a9c3adbc8bda08) )
	ROM_LOAD16_BYTE("d29-02.ic18", 0x600000, 0x100000, CRC(ed894fe1) SHA1(5bf2fb6abdcf25bc525a2c3b29dbf7aca0b18fea) )

	ROM_REGION( 0x1200, "plds", 0 )
	ROM_LOAD( "d29-11.ic15.bin", 0x0000, 0x0157, CRC(5dd5c8f9) SHA1(5e6153d9e08985b2326dfd6d73f7b90136a7a4b1) )
	ROM_LOAD( "pal20l8b.2",      0x0200, 0x0144, CRC(c91437e2) SHA1(5bd6fb57fd7e0ff957a6ef9509b8f2e35a8ca29a) )
	ROM_LOAD( "d29-13.ic14.bin", 0x0400, 0x0157, CRC(74d61d36) SHA1(c34d8b2d227f69c167d1516dea53e4bcb76491d1) )
	ROM_LOAD( "palce16v8h.11",   0x0600, 0x0117, CRC(51088324) SHA1(b985835b92c9d1e1dae6ae7cba9fa83c4db58bbb) )
	ROM_LOAD( "pal16l8b.22",     0x0800, 0x0104, CRC(3e01e854) SHA1(72f48982673ac8337dac3358b7a79e45c60b9601) )
	ROM_LOAD( "palce16v8h.31",   0x0a00, 0x0117, CRC(e0789727) SHA1(74add02cd194741de5ca6e36a99f9dd3e756fbdf) )
	ROM_LOAD( "pal16l8b.62",     0x0c00, 0x0104, CRC(7093e2f3) SHA1(62bb0085ed93cc8a5fb3a1b08ce9c8071ebda657) )
	ROM_LOAD( "d29-14.ic28.bin", 0x0e00, 0x0157, CRC(25d205d5) SHA1(8859fd498e4d84a55424899d23db470be217eaba) )
	ROM_LOAD( "pal20l8b.70",     0x1000, 0x0144, CRC(92b5b97c) SHA1(653ab0467f71d93eceb8143b124cdedaf1ede750) )
ROM_END

 /***************
 Bubble Symphony
******************/

ROM_START( bubsymphhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("d90_hack01-12", 0x000000, 0x40000, CRC(1ae40f57) SHA1(56cfcfc69b0f29a2f13745f47462dd442c422260) )
	ROM_LOAD32_BYTE("d90_hack01-11", 0x000001, 0x40000, CRC(bc2ad86a) SHA1(3bbc20396fa328901747dcd6c88cf2a90e852ccb) )
	ROM_LOAD32_BYTE("d90_hack01-10", 0x000002, 0x40000, CRC(db7c9cc2) SHA1(11786688b5525b0429532e53580e93dba2afd18a) )
	ROM_LOAD32_BYTE("d90_hack01-09", 0x000003, 0x40000, CRC(20a5f8a1) SHA1(50070b30c166350b397bec3ffc4038adcb3289b5) )

	ROM_REGION(0x200000, "sprites" , 0)
	ROM_LOAD16_BYTE("d90_hack01-03", 0x000000, 0x100000, CRC(9e610be0) SHA1(d8663197e052c17f6cd507a9e0fc5be53060b483) )
	ROM_LOAD16_BYTE("d90_hack01-02", 0x000001, 0x100000, CRC(881e91a1) SHA1(3e273c831b1d620bfc97d803636988d397b494ad) )

	ROM_REGION( 0x100000, "sprites_hi", 0 )
	ROM_LOAD       ("d90_hack01-01", 0x000000, 0x100000, CRC(4a577d64) SHA1(37acf59c3d3dd2fe9dda30c30cbbc4cad548af8f) )

	ROM_REGION(0x200000, "tilemap" , 0)
	ROM_LOAD32_WORD("d90_hack01-08", 0x000000, 0x100000, CRC(f57f521d) SHA1(7e40352dc6a5d2423d79e5d4ebe8b70b66c94fe8) )
	ROM_LOAD32_WORD("d90_hack01-07", 0x000002, 0x100000, CRC(fe765764) SHA1(a8c466eac3516468ff694b6a487ae7722f373a50) )

	ROM_REGION( 0x100000, "tilemap_hi", 0 )
	ROM_LOAD       ("d90_hack01-06", 0x000000, 0x100000, CRC(f3a70b9c) SHA1(5fd676db3783dbd905b53b0e9e6199371dca88a7) )

	ROM_REGION(0x180000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("d90-13.ic32", 0x100000, 0x40000, CRC(6762bd90) SHA1(771db0382bc8dab2caf13d0fc20648366c685829) )
	ROM_LOAD16_BYTE("d90-14.ic33", 0x100001, 0x40000, CRC(8e33357e) SHA1(68b81693c22e6357e37244f2a416818a81338138) )

	ROM_REGION16_BE(0x800000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("d90-04", 0x000000, 0x200000, CRC(feee5fda) SHA1(b89354013ec4d34bcd51ecded412effa66dd2f2f) )
	ROM_LOAD16_BYTE("d90-05", 0x400000, 0x200000, CRC(c192331f) SHA1(ebab05b3681c70b373bc06c1826be1cc397d3af7) )

	ROM_REGION( 0x0a00, "plds", 0 )
	ROM_LOAD( "pal16l8a-d77-09.bin",   0x0000, 0x0104, CRC(b371532b) SHA1(7f875f380e69d14326a036a09d2fda7554b73664) )
	ROM_LOAD( "pal16l8a-d77-10.bin",   0x0200, 0x0104, CRC(42f59227) SHA1(1f0db7489b49c00603ea51d130c9dfc237545390) )
	ROM_LOAD( "palce16v8q-d77-11.bin", 0x0400, 0x0117, CRC(eacc294e) SHA1(90679d523d90c1f8d2ecbd7b6fac2861f94cf107) )
	ROM_LOAD( "palce16v8q-d77-12.bin", 0x0600, 0x0117, CRC(e9920cfe) SHA1(58b73fe65f118d57fdce56d781593fc70c797f1b) )
	ROM_LOAD( "palce16v8q-d77-14.bin", 0x0800, 0x0117, CRC(7427e777) SHA1(e692cedb13e5bc02edc4b25e9dcea51e6715de85) )
ROM_END

 /*********
 Dan-Ku-Ga
************/

ROM_START( dankugahack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("dkg_mpr3_hack01.20", 0x000000, 0x80000, CRC(1da88664) SHA1(d9569ad4b20776521db937f70986a72364a03eb8) )
	ROM_LOAD32_BYTE("dkg_mpr2_hack01.19", 0x000001, 0x80000, CRC(db215d0e) SHA1(2b46e9b523feb4efcf032ce2feafeb1c9d929c49) )
	ROM_LOAD32_BYTE("dkg_mpr1_hack01.18", 0x000002, 0x80000, CRC(da6345f8) SHA1(9ec64f3ad6a0135aa35dcd4aeff183856adaf35a) )
	ROM_LOAD32_BYTE("dkg_mpr0_hack01.17", 0x000003, 0x80000, CRC(6e54b3af) SHA1(473c7ca4096a9a71f3bd7fb52334ea7a0ee08726) )

	ROM_REGION(0xD00000, "sprites" , 0)
	ROM_LOAD16_BYTE("d84-03.rom", 0x000000, 0x200000, CRC(d786f552) SHA1(f73146892f714b5706d568fc8a135fddaa656570) )
	ROM_LOAD16_BYTE("d84-04.rom", 0x000001, 0x200000, CRC(d1f32b5d) SHA1(35289cce64fdbb8d966dd1d5307b5393be5e7799) )
	ROM_LOAD16_BYTE("d84-06.rom", 0x400000, 0x200000, CRC(fa924dab) SHA1(28a8c3cd701f8df0c53069bb576bb2a820f3a331) )
	ROM_LOAD16_BYTE("d84-07.rom", 0x400001, 0x200000, CRC(54517a6b) SHA1(6e2c213c7ec1a3b78ad7e71db2326602557fd0f8) )
	ROM_LOAD16_BYTE("d84-09.rom", 0x800000, 0x200000, CRC(faa78d98) SHA1(da3a2c5a45dd169743f113aa08e574f732e1f0fd) )
	ROM_LOAD16_BYTE("d84-10.rom", 0x800001, 0x200000, CRC(b84b7320) SHA1(f5de0d6da50d8ed753607b51e46bc9a4572ef431) )
	ROM_LOAD16_BYTE("d84-19.rom", 0xc00000, 0x080000, CRC(6ddf77e5) SHA1(a1323acaed37fce62a19e63a0800d9d1dc2cfff7) )
	ROM_LOAD16_BYTE("d84-20.rom", 0xc00001, 0x080000, CRC(f85041e5) SHA1(6b2814514338f550d6aa14dbe39e848e8e64edee) )

	ROM_REGION( 0x680000, "sprites_hi", 0 )
	ROM_LOAD       ("d84-05.rom", 0x000000, 0x200000, CRC(31a3c75d) SHA1(1a16ccb6a0a03ab715e5b016ab3b1b2cd0f1ae41) )
	ROM_LOAD       ("d84-08.rom", 0x200000, 0x200000, CRC(07347bf1) SHA1(34bd359933acdec7fd1ce047092a30d1177afc2c) )
	ROM_LOAD       ("d84-11.rom", 0x400000, 0x200000, CRC(a062c1d4) SHA1(158912aa3dd75c3961bf738f9ac9034f0b005b60) )
	ROM_LOAD       ("d84-21.rom", 0x600000, 0x080000, CRC(89f68b66) SHA1(95916f02f71357324effe59da4f847f2f30ea34a) )

	ROM_REGION(0x600000, "tilemap" , 0)
	ROM_LOAD32_WORD("d84-12.rom", 0x000000, 0x200000, CRC(66a7a9aa) SHA1(a7d21f8b6370d16de3c1569019f2ad71d36e7a61) )
	ROM_LOAD32_WORD("d84-13.rom", 0x000002, 0x200000, CRC(ae125516) SHA1(d54e76e398ab0b0fb82f3154ba54fc823ff49a1a) )
	ROM_LOAD32_WORD("d84-16.rom", 0x400000, 0x100000, CRC(bcff9b2d) SHA1(0ca50ec809564eddf0ba7448a8fae9087d3b600b) )
	ROM_LOAD32_WORD("d84-17.rom", 0x400002, 0x100000, CRC(0be37cc3) SHA1(b10c10b93858cad0c962ef614cfd6daea712ef6b) )

	ROM_REGION( 0x300000, "tilemap_hi", 0 )
	ROM_LOAD       ("d84-14.rom", 0x000000, 0x200000, CRC(2b2e693e) SHA1(03eb37fa7dc68d54bf0f1800b8c0b581c344a40f) )
	ROM_LOAD       ("d84-18.rom", 0x200000, 0x100000, CRC(e812bcc5) SHA1(3574e4a99232d9fc7989ec5d1e8fe76b4b30784a) )

	ROM_REGION(0x180000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("d84-26.32", 0x100000, 0x40000, CRC(4f5b8563) SHA1(1d4e06cbea7bc73a99d6e30be714fff420151bbc) )
	ROM_LOAD16_BYTE("d84-27.33", 0x100001, 0x40000, CRC(fb0cb1ba) SHA1(16a79b53651a6131f7636db19738b456b7c28bff) )

	ROM_REGION16_BE(0x1000000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("d84-01.rom", 0x400000, 0x200000, CRC(9ad22149) SHA1(48055822e0cea228cdecf3d05ac24e50979b6f4d) )
	ROM_LOAD16_BYTE("d84-02.rom", 0x800000, 0x200000, CRC(9e1827e4) SHA1(1840881b0f8f7b6225e6ffa12a8d4b463554988e) )
	ROM_LOAD16_BYTE("d84-15.rom", 0xe00000, 0x100000, CRC(31ceb152) SHA1(d9d0bc631a6a726376f566a49605b50485ac7bf4) )
ROM_END

 /*************
 Darius Gaiden
***************/

ROM_START( dariusghack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("dge_mpr3.bin", 0x000000, 0x80000, CRC(1c1e24a7) SHA1(eafde331c3be5be55d0d838a84017f357ff92634) )
	ROM_LOAD32_BYTE("dge_mpr2.bin", 0x000001, 0x80000, CRC(7be23e23) SHA1(4764355f51e207f4538dd753aea59bf2689835de) )
	ROM_LOAD32_BYTE("dge_mpr1.bin", 0x000002, 0x80000, CRC(bc030f6f) SHA1(841396911d26ddfae0c9863431e02e0b5e762ac6) )
	ROM_LOAD32_BYTE("dge_mpr0_hack01.bin",  0x000003, 0x80000, CRC(2bb37270) SHA1(98bc07894e92ca9cce34fc7390f40d3357783e3f) )

	ROM_REGION(0x400000, "sprites" , 0)
	ROM_LOAD16_BYTE("d87-03.bin", 0x000000, 0x200000, CRC(4be1666e) SHA1(35ba7bcf29ec7a8f8b6944ee3544693d4df1bfc2) )
	ROM_LOAD16_BYTE("d87-04.bin", 0x000001, 0x200000, CRC(2616002c) SHA1(003f98b740a697274385b8da03c78f3c6f7b5e89) )

	ROM_REGION( 0x200000, "sprites_hi", 0 )
	ROM_LOAD       ("d87-05.bin", 0x000000, 0x200000, CRC(4e5891a9) SHA1(fd08d848079841c9237fa359a850980fd00114d8) )

	ROM_REGION(0x400000, "tilemap" , 0)
	ROM_LOAD32_WORD("d87-06.bin", 0x000000, 0x200000, CRC(3b97a07c) SHA1(72cdeffedeab0c1bd0e47f03172085390a2be393) )
	ROM_LOAD32_WORD("d87-17.bin", 0x000002, 0x200000, CRC(e601d63e) SHA1(256a6aeb5633fe1db407fad567169a9d0c911219) )

	ROM_REGION( 0x200000, "tilemap_hi", 0 )
	ROM_LOAD       ("d87-08.bin", 0x000000, 0x200000, CRC(76d23602) SHA1(ca53ea6641182c44a4038bbeaa5effb1687f1980) )

	ROM_REGION(0x180000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("d87-13.bin", 0x100000, 0x40000, CRC(15b1fff4) SHA1(28692b731ae98a47c2c5e11a8a71b61a813d9a64) )
	ROM_LOAD16_BYTE("d87-14.bin", 0x100001, 0x40000, CRC(eecda29a) SHA1(6eb238e47bc7bf635ffbdbb25fb06a37db980ef8) )

	ROM_REGION16_BE(0x800000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("d87-01.bin", 0x000000, 0x200000, CRC(3848a110) SHA1(802e91695a526f665c7fd261f0a7639a0b883c9e) )
	ROM_LOAD16_BYTE("d87-02.bin", 0x400000, 0x200000, CRC(9250abae) SHA1(07cae8edbc3cca0a95022d9b40a5c18a55350b67) )
ROM_END

 /***********************
 Elevator Action Returns
**************************/

ROM_START( elvactrhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("e02-12_hack01.20", 0x000000, 0x80000, CRC(eaaefe10) SHA1(d13e41ea42fd3d7915a1391925a1029c88c40b12) )
	ROM_LOAD32_BYTE("e02-11_hack01.19", 0x000001, 0x80000, CRC(990c1409) SHA1(3922137958d54715941c612425567f23e74d17ae) )
	ROM_LOAD32_BYTE("e02-10_hack01.18", 0x000002, 0x80000, CRC(b9a54080) SHA1(0999662fed8c36d96186114384d68dc9251b9262) )
	ROM_LOAD32_BYTE("e02-09_hack01.17", 0x000003, 0x80000, CRC(7fb5f049) SHA1(a40a79c06a855695769cd5e59729be85dd74c7b1) )

	ROM_REGION(0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE("e02-03_hack01.12", 0x000000, 0x200000, CRC(86ec9f36) SHA1(d989742bdd9237fa37730090ceb2324c83c1675f) )
	ROM_LOAD16_BYTE("e02-02_hack01.8",  0x000001, 0x200000, CRC(3484fa1d) SHA1(06573ac3738dbceb7812cd0666f1b5fd24fb65c1) )

	ROM_REGION( 0x200000, "sprites_hi", 0 )
	ROM_LOAD       ("e02-01_hack01.4",  0x000000, 0x200000, CRC(9dd378b7) SHA1(9f9a08da225288287993ddcd165d442a777d1af6) )

	ROM_REGION(0x400000, "tilemap", 0 )
	ROM_LOAD32_WORD("e02-08_hack01.47", 0x000000, 0x200000, CRC(e884fad1) SHA1(b95f53b1a413fe39b83ec850b45366c4fd8cadf5) )
	ROM_LOAD32_WORD("e02-07_hack01.45", 0x000002, 0x200000, CRC(b1553a44) SHA1(12d8f008bb3311c9de529d459a5e4e3c256ba1ae) )

	ROM_REGION( 0x200000, "tilemap_hi", 0 )
	ROM_LOAD       ("e02-06_hack01.43", 0x000000, 0x200000, CRC(44ef81a0) SHA1(e7a32fe6302a12d5cc061671ad192fbadd4cdec6) )

	ROM_REGION(0x180000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("e02-13.32", 0x100000, 0x40000, CRC(80932702) SHA1(c468234d03aa31b2aa0c3bd6bec32034216c2ae4) )
	ROM_LOAD16_BYTE("e02-14.33", 0x100001, 0x40000, CRC(706671a5) SHA1(1ac90647d617e73f12a67274a025ae43a6b3a316) )

	ROM_REGION16_BE(0x800000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("e02-04.38", 0x000000, 0x200000, CRC(b74307af) SHA1(deb42415049efa2df70e7b25ba8b1b716aa227f1) )
	ROM_LOAD16_BYTE("e02-05.39", 0x400000, 0x200000, CRC(eb729855) SHA1(85253efe794e8b5ffaf16bcb1123bca831e776a5) )
ROM_END

 /************
  Gekirindan
***************/

ROM_START( gekiridnhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("e11-12_hack01.bin", 0x000000, 0x40000, CRC(448308ce) SHA1(22eac25158bd3a0349aa4f1f041473b93030ee43) )
	ROM_LOAD32_BYTE("e11-11_hack01.bin", 0x000001, 0x40000, CRC(8ae457c4) SHA1(f1d74d99c916df90a74be0ff80b05b0f31284306) )
	ROM_LOAD32_BYTE("e11-10_hack01.bin", 0x000002, 0x40000, CRC(b1ff4529) SHA1(9e8366d9d90ad4155aab3828523daff09e3d400d) )
	ROM_LOAD32_BYTE("e11-09_hack01.bin", 0x000003, 0x40000, CRC(24d884ff) SHA1(35ddb21608c781a0674a4244c8e5c0aa6dc220eb) )

	ROM_REGION(0x400000, "sprites" , 0)
	ROM_LOAD16_BYTE("e11-03_hack01.bin", 0x000000, 0x200000, CRC(2b0dab58) SHA1(7c70a2104fbbfde32fa006bfafe30c3d9708cb10) )
	ROM_LOAD16_BYTE("e11-02_hack01.bin", 0x000001, 0x200000, CRC(a2c4fa4f) SHA1(2ad73ce8431f1199dd32df83352dc4f85345529f) )

	ROM_REGION( 0x200000, "sprites_hi", 0 )
	ROM_LOAD       ("e11-01_hack01.bin", 0x000000, 0x200000, CRC(e19874b3) SHA1(a8d6806133977a7decefafff5d7b249803add70b) )

	ROM_REGION(0x400000, "tilemap" , 0)
	ROM_LOAD32_WORD("e11-08_hack01.bin", 0x000000, 0x200000, CRC(93884253) SHA1(6d0530db64c84bf7b2ad47e94036ecd8c81418b6) )
	ROM_LOAD32_WORD("e11-07_hack01.bin", 0x000002, 0x200000, CRC(15ca8ac2) SHA1(33cbcc96e5144e5910c67c99815958d8f004287e) )

	ROM_REGION( 0x200000, "tilemap_hi", 0 )
	ROM_LOAD       ("e11-06_hack01.bin", 0x000000, 0x200000, CRC(0acc71d3) SHA1(455c70ec8f1087189170160d5683545bbea1fe9a) )

	ROM_REGION(0x140000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("e11-13.bin",  0x100000, 0x20000, CRC(51a11ff7) SHA1(c03042489d71423667f25856d15aa6a363ea6c92) )
	ROM_LOAD16_BYTE("e11-14.bin",  0x100001, 0x20000, CRC(dce2ba91) SHA1(00bc353c7747a7954365b587d7bc759ee5dc09c2) )

	ROM_REGION16_BE(0x800000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("e11-04.ic38", 0x000000, 0x200000, CRC(e0ff4fb1) SHA1(81e186e3a692af1da316b8085a729c4f103d9a52) )
	ROM_LOAD16_BYTE("e11-05.ic41", 0x400000, 0x200000, CRC(a4d08cf1) SHA1(ae2cabef7b7bcb8a788988c73d7af6fa4bb2c444) )
ROM_END

 /**********************************
  Grid Seeker: Project Storm Hammer
*************************************/

ROM_START( gseekerhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("d40_12_hack01.rom", 0x000000, 0x40000, CRC(63894ca7) SHA1(2d8821a088c7d2cfc1a4d117b723d5a40c2a12b6) )
	ROM_LOAD32_BYTE("d40_11_hack01.rom", 0x000001, 0x40000, CRC(287358f1) SHA1(a57f53b7093d5db856f136bb11be3508133559a7) )
	ROM_LOAD32_BYTE("d40_10_hack01.rom", 0x000002, 0x40000, CRC(af11d645) SHA1(fe5b8068b6263ece28892efa51bd0e2b0df5bb50) )
	ROM_LOAD32_BYTE("d40-09_hack01.34",  0x000003, 0x40000, CRC(2d8f3978) SHA1(f9d6548b44f33017430d31c94756e2b5516e492b) )

	ROM_REGION(0x200000, "sprites" , 0)
	ROM_LOAD16_BYTE("d40_03_hack01.rom", 0x000000, 0x100000, CRC(644f60c1) SHA1(9af611a3efb115bab17b7aa4f4c87ede1426731d) )
	ROM_LOAD16_BYTE("d40_04_hack01.rom", 0x100001, 0x080000, CRC(23a6a9e1) SHA1(ecf1ff6a21991d3596a3a6924134f4ebb8a996fd) )
	ROM_CONTINUE(0,0x80000)
	ROM_LOAD16_BYTE("d40_15_hack01.rom", 0x000000, 0x080000, CRC(277f6629) SHA1(4f8c1dc9c2c62da52212dfde40d03c40672eed1a) )
	ROM_LOAD16_BYTE("d40_16_hack01.rom", 0x000001, 0x080000, CRC(ec221d06) SHA1(d524c990e4c81d12fa82792064944e9f76c9df08) )

	EMPTY_SPRITE_HIDATA(0x100000)

	ROM_REGION(0x200000, "tilemap" , 0)
	ROM_LOAD32_WORD("d40_05_hack01.rom", 0x000000, 0x100000, CRC(b30e97e2) SHA1(ba187ac7f0cc1904adc75350dd2d6fc1cee0b0ce) )
	ROM_LOAD32_WORD("d40_06_hack01.rom", 0x000002, 0x100000, CRC(5a5c7d5a) SHA1(4f37c3ece53eb9f94b49fd2b215101a72a7055d0) )

	EMPTY_TILEMAP_HIDATA(0x100000)

	ROM_REGION(0x140000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("d40_07.rom", 0x100000, 0x20000, CRC(7e9b26c2) SHA1(d88ad39a9d70b4a5bd3f83e0d4d0725f659f1d2a) )
	ROM_LOAD16_BYTE("d40_08.rom", 0x100001, 0x20000, CRC(9c926a28) SHA1(9d9ee75eb895edc381c3ab4df5af941f84cd2073) )

	ROM_REGION16_BE(0x800000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("d40_01.rom", 0x000000, 0x200000, CRC(ee312e95) SHA1(885553950c2b2195d664639bf7e0d1ffa3e8346a) )
	ROM_LOAD16_BYTE("d40_02.rom", 0x600000, 0x100000, CRC(ed894fe1) SHA1(5bf2fb6abdcf25bc525a2c3b29dbf7aca0b18fea) )
ROM_END

 /**************
 Kaiser Knuckle
*****************/

ROM_START( kaiserknhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("d84-25_hack01.20", 0x000000, 0x80000, CRC(e55c530c) SHA1(4114b6ff4204fafe25a654a0411ebaa1cfed9f3e) )
	ROM_LOAD32_BYTE("d84-24_hack01.19", 0x000001, 0x80000, CRC(6e55c3d2) SHA1(c2c0d3cc2c5f0b2cbef2f09eb678a7b8ade176f2) )
	ROM_LOAD32_BYTE("d84-23_hack01.18", 0x000002, 0x80000, CRC(15ac582b) SHA1(a4af2f641360b9551539d73ff113a8dc70e15f0c) )
	ROM_LOAD32_BYTE("d84-22_hack01.17", 0x000003, 0x80000, CRC(5d44734c) SHA1(be9dd23227d27815366d615b2680bd48c6e896bd) )

	ROM_REGION(0xd00000, "sprites" , 0)
	ROM_LOAD16_BYTE("d84-03.rom", 0x000000, 0x200000, CRC(d786f552) SHA1(f73146892f714b5706d568fc8a135fddaa656570) )
	ROM_LOAD16_BYTE("d84-04.rom", 0x000001, 0x200000, CRC(d1f32b5d) SHA1(35289cce64fdbb8d966dd1d5307b5393be5e7799) )
	ROM_LOAD16_BYTE("d84-06.rom", 0x400000, 0x200000, CRC(fa924dab) SHA1(28a8c3cd701f8df0c53069bb576bb2a820f3a331) )
	ROM_LOAD16_BYTE("d84-07.rom", 0x400001, 0x200000, CRC(54517a6b) SHA1(6e2c213c7ec1a3b78ad7e71db2326602557fd0f8) )
	ROM_LOAD16_BYTE("d84-09.rom", 0x800000, 0x200000, CRC(faa78d98) SHA1(da3a2c5a45dd169743f113aa08e574f732e1f0fd) )
	ROM_LOAD16_BYTE("d84-10.rom", 0x800001, 0x200000, CRC(b84b7320) SHA1(f5de0d6da50d8ed753607b51e46bc9a4572ef431) )
	ROM_LOAD16_BYTE("d84-19.rom", 0xc00000, 0x080000, CRC(6ddf77e5) SHA1(a1323acaed37fce62a19e63a0800d9d1dc2cfff7) )
	ROM_LOAD16_BYTE("d84-20.rom", 0xc00001, 0x080000, CRC(f85041e5) SHA1(6b2814514338f550d6aa14dbe39e848e8e64edee) )

	ROM_REGION( 0x680000, "sprites_hi", 0 )
	ROM_LOAD       ("d84-05.rom", 0x000000, 0x200000, CRC(31a3c75d) SHA1(1a16ccb6a0a03ab715e5b016ab3b1b2cd0f1ae41) )
	ROM_LOAD       ("d84-08.rom", 0x200000, 0x200000, CRC(07347bf1) SHA1(34bd359933acdec7fd1ce047092a30d1177afc2c) )
	ROM_LOAD       ("d84-11.rom", 0x400000, 0x200000, CRC(a062c1d4) SHA1(158912aa3dd75c3961bf738f9ac9034f0b005b60) )
	ROM_LOAD       ("d84-21.rom", 0x600000, 0x080000, CRC(89f68b66) SHA1(95916f02f71357324effe59da4f847f2f30ea34a) )

	ROM_REGION(0x600000, "tilemap" , 0)
	ROM_LOAD32_WORD("d84-12.rom", 0x000000, 0x200000, CRC(66a7a9aa) SHA1(a7d21f8b6370d16de3c1569019f2ad71d36e7a61) )
	ROM_LOAD32_WORD("d84-13.rom", 0x000002, 0x200000, CRC(ae125516) SHA1(d54e76e398ab0b0fb82f3154ba54fc823ff49a1a) )
	ROM_LOAD32_WORD("d84-16.rom", 0x400000, 0x100000, CRC(bcff9b2d) SHA1(0ca50ec809564eddf0ba7448a8fae9087d3b600b) )
	ROM_LOAD32_WORD("d84-17.rom", 0x400002, 0x100000, CRC(0be37cc3) SHA1(b10c10b93858cad0c962ef614cfd6daea712ef6b) )

	ROM_REGION( 0x300000, "tilemap_hi", 0 )
	ROM_LOAD       ("d84-14.rom", 0x000000, 0x200000, CRC(2b2e693e) SHA1(03eb37fa7dc68d54bf0f1800b8c0b581c344a40f) )
	ROM_LOAD       ("d84-18.rom", 0x200000, 0x100000, CRC(e812bcc5) SHA1(3574e4a99232d9fc7989ec5d1e8fe76b4b30784a) )

	ROM_REGION(0x180000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("d84-26.32", 0x100000, 0x40000, CRC(4f5b8563) SHA1(1d4e06cbea7bc73a99d6e30be714fff420151bbc) )
	ROM_LOAD16_BYTE("d84-27.33", 0x100001, 0x40000, CRC(fb0cb1ba) SHA1(16a79b53651a6131f7636db19738b456b7c28bff) )

	ROM_REGION16_BE(0x1000000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("d84-01.rom", 0x400000, 0x200000, CRC(9ad22149) SHA1(48055822e0cea228cdecf3d05ac24e50979b6f4d) )
	ROM_LOAD16_BYTE("d84-02.rom", 0x800000, 0x200000, CRC(9e1827e4) SHA1(1840881b0f8f7b6225e6ffa12a8d4b463554988e) )
	ROM_LOAD16_BYTE("d84-15.rom", 0xe00000, 0x100000, CRC(31ceb152) SHA1(d9d0bc631a6a726376f566a49605b50485ac7bf4) )
ROM_END

 /**********
 Land Maker
*************/

ROM_START( landmakrhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("e61-13_hack01.20", 0x000000, 0x80000, CRC(ff7afcc8) SHA1(a3c8d1c3987c3266c62c056656fd3ea456749080) )
	ROM_LOAD32_BYTE("e61-12_hack01.19", 0x000001, 0x80000, CRC(2be4297d) SHA1(fb1ab2e39755317ebf084df349fa0ab6a641d7e2) )
	ROM_LOAD32_BYTE("e61-11_hack01.18", 0x000002, 0x80000, CRC(dbc10844) SHA1(2cf377cad0837cc3a25a679a6fe41beff38b20b4) )
	ROM_LOAD32_BYTE("e61-10_hack01.17", 0x000003, 0x80000, CRC(42d37d39) SHA1(adb10fcd33a7d8daef111405b596858fe2da6452) )

	ROM_REGION(0x400000, "sprites" , 0)
	ROM_LOAD16_BYTE("e61-03_hack01.12",0x000000, 0x200000, CRC(08e6acb4) SHA1(1edaf0810682f6e3932a69942c4a83169329baf1) )
	ROM_LOAD16_BYTE("e61-02_hack01.08",0x000001, 0x200000, CRC(e2f9d072) SHA1(bf47ad233d6cceb552b8e5efadb5130f2529a59f) )

	ROM_REGION( 0x200000, "sprites_hi", 0 )
	ROM_LOAD       ("e61-01_hack01.04",0x000000, 0x200000, CRC(cb6b638c) SHA1(eceea8404f71aaaf8b81aaa6601967d130cb9fd2) )

	ROM_REGION(0x400000, "tilemap" , 0)
	ROM_LOAD32_WORD("e61-09_hack01.47", 0x000000, 0x200000, CRC(d2e78354) SHA1(3a6e67da77970a69051828a4fb82131d74b5595e) )
	ROM_LOAD32_WORD("e61-08_hack01.45", 0x000002, 0x200000, CRC(831bf12a) SHA1(41ac84ff13454caf9eec29a01e974123e2eb8e54) )

	ROM_REGION( 0x200000, "tilemap_hi", 0 )
	ROM_LOAD       ("e61-07.43", 0x000000, 0x200000, CRC(4a57965d) SHA1(8e80788e0f47fb242da9af3aa19077dc0ec829b8) )

	ROM_REGION(0x140000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("eh61-14.32", 0x100000, 0x20000, CRC(b905f4a7) SHA1(613b954e3e129fd44b4ce64958f16e5636012d6e) )
	ROM_LOAD16_BYTE("eh61-15.33", 0x100001, 0x20000, CRC(87909869) SHA1(7b90c23899a673966cac3352d375d17b83e66596) )

	ROM_REGION16_BE(0x1000000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("e61-04.38", 0x400000, 0x200000, CRC(c27aec0c) SHA1(e95da2db07a20a53662ebd45c033966e8a22a15a) )
	ROM_LOAD16_BYTE("e61-05.39", 0x800000, 0x200000, CRC(83920d9d) SHA1(019e39ae85d1129f6d3b8460c4b1bd925f868ee2) )
	ROM_LOAD16_BYTE("e61-06.40", 0xc00000, 0x200000, CRC(2e717bfe) SHA1(1be54cd2ec65d8fd49a5c09b5d27791fd7a320d4) )
ROM_END

 /*************
 Light Bringer
****************/

ROM_START( lightbrhack01 )
	ROM_REGION(0x200000, "maincpu", 0)
	ROM_LOAD32_BYTE("d69-20_hack01.bin", 0x000000, 0x80000, CRC(5b29e745) SHA1(a20ffaf53cb7572217ad5e92d3641927b1998eab) )
	ROM_LOAD32_BYTE("d69-13_hack01.bin", 0x000001, 0x80000, CRC(0764221f) SHA1(1465f51396348c12c7d272232699eb69bd46bf9b) )
	ROM_LOAD32_BYTE("d69-15_hack01.bin", 0x000002, 0x80000, CRC(66c3a572) SHA1(122bdab9becdd2df0f43c2a34e079cf1625159b9) )
	ROM_LOAD32_BYTE("d69-14_hack01.bin", 0x000003, 0x80000, CRC(c1588074) SHA1(0e5c1677f89953791837d1293cc924cfa7fe54e5) )

	ROM_REGION(0x600000, "sprites" , 0)
	ROM_LOAD16_BYTE("d69-06.bin", 0x000000, 0x200000, CRC(cb4aac81) SHA1(15d315c6b9695cc2fe07defc67c7a4fb26de1950) )
	ROM_LOAD16_BYTE("d69-07.bin", 0x000001, 0x200000, CRC(b749f984) SHA1(39fd662bdc42e812519181a640a83e29e300826a) )
	ROM_LOAD16_BYTE("d69-09_hack01.bin", 0x400000, 0x100000, CRC(dbac0bf3) SHA1(ff17a43fc0b2f6b41b8394ad00e00b2683e2287a) )
	ROM_LOAD16_BYTE("d69-10_hack01.bin", 0x400001, 0x100000, CRC(50673c49) SHA1(62f3fa18c39c0149ec021c5617d2989d546550aa) )

	ROM_REGION( 0x300000, "sprites_hi", 0 )
	ROM_LOAD       ("d69-08.bin", 0x000000, 0x200000, CRC(5b68d7d8) SHA1(f2ee3dd7100a3c9d8f402fe36dae2bc66cb17be3) )
	ROM_LOAD       ("d69-11_hack01.bin", 0x200000, 0x100000, CRC(1988fb12) SHA1(790bfaf765bad2665381b6b752d2c26c010b4e4e) )

	ROM_REGION(0x400000, "tilemap" , 0)
	ROM_LOAD32_WORD("d69-03_hack01.bin", 0x000000, 0x200000, CRC(36fab42f) SHA1(6e3f78eda7aaa3b565b495dfe4b40a5abb3c3449) )
	ROM_LOAD32_WORD("d69-04_hack01.bin", 0x000002, 0x200000, CRC(4a63f543) SHA1(37748b843bb001a4ceb5f10e3a3ab409d242395f) )

	ROM_REGION( 0x200000, "tilemap_hi", 0 )
	ROM_LOAD       ("d69-05_hack01.bin", 0x000000, 0x200000, CRC(f84c9c40) SHA1(2e1945ecd904d41d4bca9fbde0083b0c78037b2f) )

	ROM_REGION(0x140000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("d69-18.bin", 0x100000, 0x20000, CRC(04600d7b) SHA1(666cfab09b61fd6e0bc4ff277018ebf1cda01b0e) )
	ROM_LOAD16_BYTE("d69-19.bin", 0x100001, 0x20000, CRC(1484e853) SHA1(4459c18ba005786483c652857e527c6093efb036) )

	ROM_REGION16_BE(0x800000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("d69-01.bin", 0x000000, 0x200000, CRC(9ac93ac2) SHA1(1c44f6ba95505f85b0c8a90395f09d2a49da3553) )
	ROM_LOAD16_BYTE("d69-02.bin", 0x400000, 0x200000, CRC(dce28dd7) SHA1(eacfc98349b0608fc1a944c11f0483fb6caa4445) )
ROM_END

 /****************
 Puzzle Bobble 2
*******************/

ROM_START( pbobble2hack01 )
	ROM_REGION(0x200000, "maincpu", 0)
 	ROM_LOAD32_BYTE("e10-29.20", 0x000000, 0x40000, CRC(f1e9ad3f) SHA1(8689d85f30e075d21e4be01a2a097a850a921c47) )
	ROM_LOAD32_BYTE("e10-28.19", 0x000001, 0x40000, CRC(412a3602) SHA1(d754e6ac886676d2c1eb52de3a727894f316e6b5) )
	ROM_LOAD32_BYTE("e10-27.18", 0x000002, 0x40000, CRC(88cc0b5c) SHA1(bb08a7b8b37356376052ed03f8515677811823c0) )
	ROM_LOAD32_BYTE("e10-26_hack01.17", 0x000003, 0x40000, CRC(4bcc216b) SHA1(45e9250414201fa5ad866b32b0285973fd06367c) )

	ROM_REGION(0x200000, "sprites" , 0)
	ROM_LOAD16_BYTE("e10-02.rom", 0x000000, 0x100000, CRC(c0564490) SHA1(cbe9f880192c08f4d1db21d5ba14073b97e5f1d3) )
	ROM_LOAD16_BYTE("e10-01.rom", 0x000001, 0x100000, CRC(8c26ff49) SHA1(cbb514c061106003d2ae2b6c43958b24feaad656) )

	EMPTY_SPRITE_HIDATA(0x100000)

	ROM_REGION(0x200000, "tilemap" , ROMREGION_ERASE00)
	ROM_LOAD32_WORD("e10-07.rom", 0x000000, 0x100000, CRC(dcb3c29b) SHA1(b80c3a8ce53d696c57675e654c9927ef8687759e) )
	ROM_LOAD32_WORD("e10-06.rom", 0x000002, 0x100000, CRC(1b0f20e2) SHA1(66b44d059c2896abac2f0e7fc932489dee440ba0) )

	ROM_REGION( 0x100000, "tilemap_hi", 0 )
	ROM_LOAD       ("e10-05.rom", 0x000000, 0x100000, CRC(81266151) SHA1(aa3b144f32995425db97efce440e234a3c7a6715) )

	ROM_REGION(0x180000, "taito_en:audiocpu", 0)
	ROM_LOAD16_BYTE("e10-30.32", 0x100000, 0x40000, CRC(bb090c1e) SHA1(af2ff23d6f9bd56c25530cb9bf9f452b6f5210f5) )
	ROM_LOAD16_BYTE("e10-31.33", 0x100001, 0x40000, CRC(f4b88d65) SHA1(c74dcb4bed979039fad1d5c7528c14ce4db1d5ec) )

	ROM_REGION16_BE(0x800000, "ensoniq.0" , ROMREGION_ERASE00 )
	ROM_LOAD16_BYTE("e10-04.rom", 0x000000, 0x200000, CRC(5c0862a6) SHA1(f916f63b8629239e3221e1e231e1b39962ef38ba) )
	ROM_LOAD16_BYTE("e10-03.rom", 0x400000, 0x200000, CRC(46d68ac8) SHA1(ad014e9f0d458308014959ca6823077f581ab088) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Cleopatra Fortune
GAME( 1996, cleopatrhack01,       cleopatr, f3_224a, f3, taito_f3_state, init_cleopatr, ROT0,   "hack",        "Cleopatra Fortune (Translation Chinese)", 0 )
GAME( 1996, cleopatrhack02,       cleopatr, f3_224a, f3, taito_f3_state, init_cleopatr, ROT0,   "hack",        "Cleopatra Fortune (Translation English)", 0 )
// Akkanbeder
GAME( 1995, akkanvdrhack01,       spcinv95, f3_224a, f3, taito_f3_state, init_spcinv95, ROT270, "hack",        "Akkanbeder (Translation Chinese)", 0 )
// Arabian Magic
GAME( 2017, arabianmhack01,       arabianm, f3_224a, f3, taito_f3_state, init_arabianm, ROT0,   "hack",        "Arabian Magic (Translation Chinese)", 0 )
// Bubble Symphony
GAME( 1994, bubsymphhack01,       bublbob2, f3_224a, f3, taito_f3_state, init_bubsymph, ROT0,   "hack",        "Bubble Symphony (Translation Chinese)", 0 )
// Dan-Ku-Ga
GAME( 1994, dankugahack01,        dankuga,  f3_224a, kn, taito_f3_state, init_kaiserkn, ROT0,   "hack",        "Dan-Ku-Ga (Enable Hidden Characters)", 0 )
// Darius Gaiden
GAME( 1994, dariusghack01,        dariusg,  f3,      f3, taito_f3_state, init_dariusg,  ROT0,   "hack",        "Darius Gaiden (Ex Super Version)", 0 )
// Elevator Action Returns
GAME( 1994, elvactrhack01,        elvactr,  f3,      f3, taito_f3_state, init_elvactr,  ROT0,   "hack",        "Elevator Action Returns (Translation Chinese)", 0 )
// Gekirindan
GAME( 1995, gekiridnhack01,       gekiridn, f3,      f3, taito_f3_state, init_gekirido, ROT270, "hack",        "Gekirindan (Translation Chinese)", 0 )
// Grid Seeker: Project Storm Hammer
GAME( 1992, gseekerhack01,        gseeker,  f3_224b_eeprom, f3, taito_f3_state, init_gseeker,  ROT90,  "hack",  "Grid Seeker: Project Storm Hammer (Translation Chinese)", 0 )
// Kaiser Knuckle
GAME( 1994, kaiserknhack01,       kaiserkn, f3_224a, kn, taito_f3_state, init_kaiserkn, ROT0,   "hack",        "Kaiser Knuckle (Enable Hidden Characters)", 0 )
// Land Maker
GAME( 1998, landmakrhack01,       landmakr, f3,      f3, taito_f3_state, init_landmakr, ROT0,   "hack",        "Land Maker (Translation Chinese)", 0 )
// Light Bringer
GAME( 2017, lightbrhack01,        lightbr,  f3_224a, f3, taito_f3_state, init_lightbr,  ROT0,   "hack",        "Light Bringer (Translation Chinese)", 0 )
// Puzzle Bobble 2
GAME( 1995, pbobble2hack01,       pbobble2, f3,      f3, taito_f3_state, init_pbobbl2x, ROT0,   "hack",        "Puzzle Bobble 2 (2X Edition)", 0 )
