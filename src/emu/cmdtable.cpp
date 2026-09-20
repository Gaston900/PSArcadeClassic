/*********************************************************************

    cmdtable.cpp

    Defined Game Commnad Font Color Array.

    This is an unofficial version based on MAME.
    Please do not send any reports from this build to the MAME team.

*********************************************************************/

#define BUTTON_COLOR_RED             rgb_t(255,64,64)
#define BUTTON_COLOR_YELLOW          rgb_t(255,238,0)
#define BUTTON_COLOR_GREEN           rgb_t(0,255,64)
#define BUTTON_COLOR_BLUE            rgb_t(0,170,255)
#define BUTTON_COLOR_PURPLE          rgb_t(170,0,255)
#define BUTTON_COLOR_PINK            rgb_t(255,0,170)
#define BUTTON_COLOR_AQUA            rgb_t(0,255,204)
#define BUTTON_COLOR_SILVER          rgb_t(255,0,255)
#define BUTTON_COLOR_NAVY            rgb_t(255,160,0)
#define BUTTON_COLOR_LIME            rgb_t(190,190,190)
#define BUTTON_COLOR_CAPCOM_BLUE     rgb_t(0,50,255)
#define BUTTON_COLOR_NEOGEO_ORANGE   rgb_t(255,110,0)
#define BUTTON_COLOR_OLIVE_GREEN     rgb_t(120,200,0)
#define BUTTON_COLOR_DARK_PURPLE     rgb_t(110,0,180)

#define BUTTON_COLOR_BASIC  	     BUTTON_COLOR_YELLOW

#ifndef COLOR_BUTTONS
#define COLOR_BUTTONS 200
#endif

#ifndef COMMAND_UNICODE
#define COMMAND_UNICODE 0xe000
#endif


// Defined Game Commnad Font Color Array
struct rgb_t color_table[COLOR_BUTTONS] =
{
	0,                      // dummy
	BUTTON_COLOR_RED,       // BTN_A
	BUTTON_COLOR_YELLOW,    // BTN_B
	BUTTON_COLOR_GREEN,     // BTN_C
	BUTTON_COLOR_BLUE,      // BTN_D
	BUTTON_COLOR_PINK,      // BTN_E
	BUTTON_COLOR_PURPLE,    // BTN_F
	BUTTON_COLOR_AQUA,      // BTN_G
	BUTTON_COLOR_SILVER,    // BTN_H
	BUTTON_COLOR_NAVY,      // BTN_I
	BUTTON_COLOR_LIME,      // BTN_J
	BUTTON_COLOR_RED,       // BTN_K
	BUTTON_COLOR_YELLOW,    // BTN_L
	BUTTON_COLOR_GREEN,     // BTN_M
	BUTTON_COLOR_BLUE,      // BTN_N
	BUTTON_COLOR_PINK,      // BTN_O
	BUTTON_COLOR_PURPLE,    // BTN_P
	BUTTON_COLOR_AQUA,      // BTN_Q
	BUTTON_COLOR_SILVER,    // BTN_R
	BUTTON_COLOR_NAVY,      // BTN_S
	BUTTON_COLOR_LIME,      // BTN_T
	BUTTON_COLOR_RED,       // BTN_U
	BUTTON_COLOR_YELLOW,    // BTN_V
	BUTTON_COLOR_GREEN,     // BTN_W
	BUTTON_COLOR_BLUE,      // BTN_X
	BUTTON_COLOR_PINK,      // BTN_Y
	BUTTON_COLOR_PURPLE,    // BTN_Z
	BUTTON_COLOR_RED,       // BTN_1
	BUTTON_COLOR_YELLOW,    // BTN_2
	BUTTON_COLOR_GREEN,     // BTN_3
	BUTTON_COLOR_BLUE,      // BTN_4
	BUTTON_COLOR_PINK,      // BTN_5
	BUTTON_COLOR_PURPLE,    // BTN_6
	BUTTON_COLOR_AQUA,      // BTN_7
	BUTTON_COLOR_SILVER,    // BTN_8
	BUTTON_COLOR_NAVY,      // BTN_9
	BUTTON_COLOR_LIME,      // BTN_10
	BUTTON_COLOR_BLUE,      // BTN_DEC
	BUTTON_COLOR_RED,       // BTN_INC
	BUTTON_COLOR_AQUA,      // BTN_+
	BUTTON_COLOR_BASIC,     // DIR_...
	BUTTON_COLOR_BASIC,     // DIR_1
	BUTTON_COLOR_BASIC,     // DIR_2
	BUTTON_COLOR_BASIC,     // DIR_3
	BUTTON_COLOR_BASIC,     // DIR_4
	BUTTON_COLOR_RED,       // Joystick Ball
	BUTTON_COLOR_BASIC,     // DIR_6
	BUTTON_COLOR_BASIC,     // DIR_7
	BUTTON_COLOR_BASIC,     // DIR_8
	BUTTON_COLOR_BASIC,     // DIR_9
	BUTTON_COLOR_BASIC,     // DIR_N
	BUTTON_COLOR_RED,       // BTN_START
	BUTTON_COLOR_YELLOW,    // BTN_SELECT
	BUTTON_COLOR_PINK,      // BTN_PUNCH
	BUTTON_COLOR_PURPLE,    // BTN_KICK
	BUTTON_COLOR_BLUE,      // BTN_GUARD
	0,
	BUTTON_COLOR_YELLOW,    // Light Punch
	BUTTON_COLOR_NAVY,      // Middle Punch
	BUTTON_COLOR_RED,       // Strong Punch
	BUTTON_COLOR_LIME,      // Light Kick
	BUTTON_COLOR_AQUA,      // Middle Kick
	BUTTON_COLOR_BLUE,      // Strong Kick
	BUTTON_COLOR_PURPLE,    // 3 Kick
	BUTTON_COLOR_PINK,      // 3 Punch
	BUTTON_COLOR_PURPLE,    // 2 Kick
	BUTTON_COLOR_PINK,      // 2 Punch
	BUTTON_COLOR_RED,       // CUSTOM_1
	BUTTON_COLOR_YELLOW,    // CUSTOM_2
	BUTTON_COLOR_GREEN,     // CUSTOM_3
	BUTTON_COLOR_BLUE,      // CUSTOM_4
	BUTTON_COLOR_PINK,      // CUSTOM_5
	BUTTON_COLOR_PURPLE,    // CUSTOM_6
	BUTTON_COLOR_AQUA,      // CUSTOM_7
	BUTTON_COLOR_SILVER,    // CUSTOM_8
	BUTTON_COLOR_RED,       // (Cursor Up)
	BUTTON_COLOR_YELLOW,    // (Cursor Down)
	BUTTON_COLOR_GREEN,     // (Cursor Left)
	BUTTON_COLOR_BLUE,      // (Cursor Right)
	0,                      // Non Player Lever
	BUTTON_COLOR_LIME,      // Gray Color Lever
	BUTTON_COLOR_RED,       // 1 Player Lever
	BUTTON_COLOR_YELLOW,    // 2 Player Lever
	BUTTON_COLOR_GREEN,     // 3 Player Lever
	BUTTON_COLOR_BLUE,      // 4 Player Lever
	BUTTON_COLOR_PINK,      // 5 Player Lever
	BUTTON_COLOR_PURPLE,    // 6 Player Lever
	BUTTON_COLOR_AQUA,      // 7 Player Lever
	BUTTON_COLOR_SILVER,    // 8 Player Lever     
	0,                      // 89
	BUTTON_COLOR_RED,       // 90  --> Arrow
	BUTTON_COLOR_YELLOW,    // 91  ==> Continue Arrow
	BUTTON_COLOR_BASIC,     // 92  Charge DIR_1
	BUTTON_COLOR_BASIC,     // 93  Charge DIR_2
	BUTTON_COLOR_BASIC,     // 94  Charge DIR_3
	BUTTON_COLOR_BASIC,     // 95  Charge DIR_4
	BUTTON_COLOR_BASIC,     // 96  Charge DIR_6
	BUTTON_COLOR_BASIC,     // 97  Charge DIR_7
	BUTTON_COLOR_BASIC,     // 98  Charge DIR_8
	BUTTON_COLOR_BASIC,     // 99  Charge DIR_9
	BUTTON_COLOR_GREEN,     // 100 hcb Half Circle Back
	BUTTON_COLOR_BLUE,      // 101 huf Half Circle Front
	BUTTON_COLOR_PINK,      // 102 hcf Half Circle Front
	BUTTON_COLOR_PURPLE,    // 103 hub Half Circle Back Up
	BUTTON_COLOR_AQUA,      // 104 qfd 1/4 Cir For 2 Down
	BUTTON_COLOR_SILVER,    // 105 qdb 1/4 Cir Down 2 Back
	BUTTON_COLOR_NAVY,      // 106 qbu 1/4 Cir Back 2 Up
	BUTTON_COLOR_LIME,      // 107 quf 1/4 Cir Up 2 For
	BUTTON_COLOR_RED,       // 108 qbd 1/4 Cir Back 2 Down
	BUTTON_COLOR_YELLOW,    // 109 qdf 1/4 Cir Down 2 For
	BUTTON_COLOR_GREEN,     // 110 qfu 1/4 Cir For 2 Up
	BUTTON_COLOR_BLUE,      // 111 qub 1/4 Cir Up 2 Back
	BUTTON_COLOR_RED,       // 112 fdf Full Clock Forward
	BUTTON_COLOR_YELLOW,    // 113 fub Full Clock Back
	BUTTON_COLOR_GREEN,     // 114 fuf Full Count Forward
	BUTTON_COLOR_BLUE,      // 115 fdb Full Count Back
	BUTTON_COLOR_PINK,      // 116 xff 2x Forward
	BUTTON_COLOR_PURPLE,    // 117 xbb 2x Back
	BUTTON_COLOR_AQUA,      // 118 dsf Dragon Screw Forward
	BUTTON_COLOR_SILVER,    // 119 dsb Dragon Screw Back
	0,                      // 120 (dummy)
	BUTTON_COLOR_AQUA,          // 121 AIR
	BUTTON_COLOR_NEOGEO_ORANGE, // 122 DIR
	BUTTON_COLOR_RED,           // 123 MAX
	BUTTON_COLOR_GREEN,         // 124 TAP
	BUTTON_COLOR_YELLOW,        // 125 jump
	BUTTON_COLOR_AQUA,          // 126 hold
	BUTTON_COLOR_BLUE,          // 127 air
	BUTTON_COLOR_PINK,          // 128 sit
	BUTTON_COLOR_PURPLE,        // 129 close
	BUTTON_COLOR_AQUA,          // 130 away
	BUTTON_COLOR_SILVER,        // 131 charge
	BUTTON_COLOR_OLIVE_GREEN,   // 132 tap
	BUTTON_COLOR_LIME,          // 133 button
	0,                          // 134 dummy
	BUTTON_COLOR_LIME,          // 135 Small Dot
	BUTTON_COLOR_AQUA,          // 136 Double Ball
	BUTTON_COLOR_GREEN,         // 137 Single Ball
	BUTTON_COLOR_YELLOW,        // 138 Círculo (○ / ●)
	BUTTON_COLOR_PINK,          // 139 Star Regular
	BUTTON_COLOR_PINK,          // 140 Estrella (★ / ☆)
	BUTTON_COLOR_NEOGEO_ORANGE, // 141 Triangle
	BUTTON_COLOR_NEOGEO_ORANGE, // 142 Solid Triangle
	BUTTON_COLOR_DARK_PURPLE,   // 143 Double Square
	BUTTON_COLOR_CAPCOM_BLUE,   // 144 Single Square
	BUTTON_COLOR_CAPCOM_BLUE,   // 145 Cuadrado (□ / ■)
	BUTTON_COLOR_RED,           // 146 Down Triangle
	BUTTON_COLOR_RED,           // 147 Solid Down Triangle
	BUTTON_COLOR_SILVER,        // 148 Diamond
	BUTTON_COLOR_SILVER,        // 149 Solid Diamond
};
