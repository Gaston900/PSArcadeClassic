/*********************************************************************

    scale.c

    scale effects framework code.

    This is an unofficial version based on MAME.
    Please do not send any reports from this build to the MAME team.

*********************************************************************/
#include <windows.h>
#include <mmsystem.h>
#undef interface

//#include "../winui/winui.h"

// MAME headers
#include "emu.h"
#include "emuopts.h"
#include "osdscale.h"

// defines
enum
{
	SCALE_EFFECT_NONE = 0,
	SCALE_EFFECT_SCANLINESTV,
	SCALE_EFFECT_EPXB,
	SCALE_EFFECT_EPXC,
	SCALE_EFFECT_SCALE2X,
	SCALE_EFFECT_SCALE3X,
	SCALE_EFFECT_2XSAI,
	SCALE_EFFECT_SUPER2XSAI,
	SCALE_EFFECT_SUPEREAGLE,
	SCALE_EFFECT_2XPM,
	SCALE_EFFECT_HQ2X,
	SCALE_EFFECT_HQ2XS,
	SCALE_EFFECT_HQ2XBOLD,
	SCALE_EFFECT_HQ3X,
	SCALE_EFFECT_HQ3XS,
	SCALE_EFFECT_HQ3XBOLD,
	SCALE_EFFECT_2XBRZ,
	SCALE_EFFECT_3XBRZ,
	SCALE_EFFECT_LAST
};

/* fixme: No longer used by the core */
#ifndef MAX_SCREENS
/* maximum number of screens for one game */
#define MAX_SCREENS					8
#endif
#define MAX_SCALE_BANK				(MAX_SCREENS * 2)


//============================================================
//	GLOBAL VARIABLES
//============================================================

struct scale_effect scale_effect;

uint32_t RGBtoYUV[65536];
uint32_t LUT16to32[65536];

//============================================================
//	IMPORTS
//============================================================



//============================================================
//	LOCAL VARIABLES
//============================================================

static int use_mmx;

static uint8_t *scale_buffer[MAX_SCALE_BANK];

static int previous_depth[MAX_SCALE_BANK];
static int previous_width[MAX_SCALE_BANK];
static int previous_height[MAX_SCALE_BANK];

static const char *str_name[] =
{
	"none",
	"scanlinestv",
	"epxb",
	"epxc",
	"scale2x",
	"scale3x",
	"2xsai",
	"super2xsai",
	"supereagle",
	"2xpm",
	"hq2x",
	"hq2xs",
	"hq2xbold",
	"hq3x",
	"hq3xs",
	"hq3xbold",
	"2xbrz",
	"3xbrz",
	NULL
};

static const char *str_desc[] =
{
	"None",
	"Scanlines TV",
	"EPX-B",
	"EPX-C",
	"Scale2x",      // by AdvMAME v2.2
	"Scale3x",      // by AdvMAME v2.2
	"2xSaI",        // by Kreed v0.59
	"Super 2xSaI",  // by Kreed v0.59
	"Super Eagle",  // by Kreed v0.59
	"2xPM",         // by Pablo Medina v0.2
	"HQ2x",
	"HQ2xS",
	"HQ2xBold",
	"HQ3x",         // by Maxim Stepin
	"HQ3xS",
	"HQ3xBold",
	"2xBRZ",        // by HqMAME v2.1.4
	"3xBRZ",        // by HqMAME v2.1.4
	NULL
};



//============================================================
//	prototypes
//============================================================

// functions from scale2x
static int scale_perform_scale2x(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height, int depth, int bank);
static void (*scale_scale2x_line_16)(uint16_t *dst0, uint16_t *dst1, const uint16_t *src0, const uint16_t *src1, const uint16_t *src2, unsigned count);
static void (*scale_scale2x_line_32)(uint32_t *dst0, uint32_t *dst1, const uint32_t *src0, const uint32_t *src1, const uint32_t *src2, unsigned count);

static int scale_perform_scale3x(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height, int depth);

// functions from AdvMAME
void scale2x_16_def(uint16_t* dst0, uint16_t* dst1, const uint16_t* src0, const uint16_t* src1, const uint16_t* src2, unsigned count);
void scale2x_32_def(uint32_t* dst0, uint32_t* dst1, const uint32_t* src0, const uint32_t* src1, const uint32_t* src2, unsigned count);
#ifdef USE_MMX_INTERP_SCALE
void scale2x_16_mmx(uint16_t* dst0, uint16_t* dst1, const uint16_t* src0, const uint16_t* src1, const uint16_t* src2, unsigned count);
void scale2x_32_mmx(uint32_t* dst0, uint32_t* dst1, const uint32_t* src0, const uint32_t* src1, const uint32_t* src2, unsigned count);
#endif /* USE_MMX_INTERP_SCALE */

void scale3x_16_def(uint16_t* dst0, uint16_t* dst1, uint16_t* dst2, const uint16_t* src0, const uint16_t* src1, const uint16_t* src2, unsigned count);
void scale3x_32_def(uint32_t* dst0, uint32_t* dst1, uint32_t* dst2, const uint32_t* src0, const uint32_t* src1, const uint32_t* src2, unsigned count);

void hq2x_32_def(uint32_t*, uint32_t*, const uint32_t*, const uint32_t*, const uint32_t*, unsigned);
void hq3x_32_def(uint32_t*, uint32_t*, uint32_t*, const uint32_t*, const uint32_t*, const uint32_t*, unsigned);
static int scale_perform_hq2x(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height, int depth);
static int scale_perform_hq3x(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height, int depth);

// functions from vba-rerecording
int Init_2xSaI(uint32_t BitFormat, int);
void _2xSaI (uint8_t *srcPtr, uint32_t srcPitch, uint8_t *deltaPtr, uint8_t *dstPtr, uint32_t dstPitch, int width, int height);
void _2xSaI32 (uint8_t *srcPtr, uint32_t srcPitch, uint8_t *deltaPtr, uint8_t *dstPtr, uint32_t dstPitch, int width, int height);
void Super2xSaI (uint8_t *srcPtr, uint32_t srcPitch, uint8_t *deltaPtr, uint8_t *dstPtr, uint32_t dstPitch, int width, int height);
void Super2xSaI32 (uint8_t *srcPtr, uint32_t srcPitch, uint8_t *deltaPtr, uint8_t *dstPtr, uint32_t dstPitch, int width, int height);
void SuperEagle (uint8_t *srcPtr, uint32_t srcPitch, uint8_t *deltaPtr, uint8_t *dstPtr, uint32_t dstPitch, int width, int height);
void SuperEagle32 (uint8_t *srcPtr, uint32_t srcPitch, uint8_t *deltaPtr, uint8_t *dstPtr, uint32_t dstPitch, int width, int height);

void hqxx_init(unsigned bits_per_pixel);
void hq2xS(unsigned char*, unsigned int, unsigned char*, unsigned char*, unsigned int, int, int);
void hq2xS32(unsigned char*, unsigned int, unsigned char*, unsigned char*, unsigned int, int, int);
//void hq3xS(unsigned char*, unsigned int, unsigned char*, unsigned char*, unsigned int, int, int);
//void hq3xS32(unsigned char*, unsigned int, unsigned char*, unsigned char*, unsigned int, int, int);

void ScanlinesTV(unsigned char*, unsigned int, unsigned char*, unsigned char*, unsigned int, int, int);

// functions from SNES9x
void InitLUTs(void);
void RenderEPXB(unsigned char *src, unsigned int srcpitch, unsigned char *dst, unsigned int dstpitch, int nWidth, int nHeight);
void RenderEPXC(unsigned char *src, unsigned int srcpitch, unsigned char *dst, unsigned int dstpitch, int nWidth, int nHeight);
void RenderHQ2X(unsigned char *src, unsigned int srcpitch, unsigned char *dst, unsigned int dstpitch, int nWidth, int nHeight, int GuiScale);
void RenderHQ3X(unsigned char *src, unsigned int srcpitch, unsigned char *dst, unsigned int dstpitch, int nWidth, int nHeight, int GuiScale);

// functions from Kega Fusion
void _2xpm_555(void *SrcPtr, void *DstPtr, unsigned long SrcPitch, unsigned long DstPitch, unsigned long SrcW, unsigned long SrcH, int depth);

void InitXbrz(void);
void Render2xXbrz(unsigned char *src, int srcPitch, unsigned char *dst, int trgPitch, int nWidth, int nHeight);
void Render3xXbrz(unsigned char *src, int srcPitch, unsigned char *dst, int trgPitch, int nWidth, int nHeight);

#undef INTERP_RGB16_TABLE
static void interp_init(void)
{
	static int interp_inited = 0;
	int i, j, k, r, g, b, y, u, v;

	if (interp_inited) return;
	interp_inited = 1;

#ifdef INTERP_RGB16_TABLE
	for (i = 0; i < 65536; i++)
	{
		uint8_t r = (i & 0xF800) >> 11;
		uint8_t g = (i & 0x07E0) >> 5;
		uint8_t b = i & 0x001F;

		r = (r << 3) | (r >> 2);
		g = (g << 2) | (g >> 4);
		b = (b << 3) | (b >> 2);
		LUT16to32[i] = (r << 16) | (g << 8) | b;
	}

	for (i = 0; i < 32; i++)
		for (j = 0; j < 64; j++)
			for (k = 0; k < 32; k++)
			{
				r = (i << 3) | (i >> 2);
				g = (j << 2) | (j >> 4);
				b = (k << 3) | (k >> 2);
				y = (r + g + b) >> 2;
				u = 128 + ((r - b) >> 2);
				v = 128 + ((-r + 2*g -b) >> 3);
				RGBtoYUV[ (i << 11) + (j << 5) + k ] = (y << 16) + (u << 8) + v;
			}

#else /* INTERP_RGB16_TABLE */
	memset(LUT16to32 + 0x8000, 0, sizeof (*LUT16to32) * 0x8000);
	memset(RGBtoYUV + 0x8000, 0, sizeof (*RGBtoYUV) * 0x8000);

	for (i=0; i < 0x8000; i++)
	{
		uint32_t col = ((i & 0x7C00) << 9) + ((i & 0x03E0) << 6) + ((i & 0x001F) << 3);
		LUT16to32[i] = col | ((col >> 5) & 0x070707);
	}

	for (i = 0; i < 32; i++)
		for (j = 0; j < 32; j++)
			for (k = 0; k < 32; k++)
			{
				r = (i << 3) | (i >> 2);
				g = (j << 3) | (j >> 2);
				b = (k << 3) | (k >> 2);
				y = (r + g + b) >> 2;
				u = 128 + ((r - b) >> 2);
				v = 128 + ((-r + 2*g -b) >> 3);
				RGBtoYUV[ (i << 10) + (j << 5) + k ] = (y << 16) + (u << 8) + v;
			}
#endif /* INTERP_RGB16_TABLE */
}


//============================================================
//	scale_decode
//============================================================

int scale_decode(const char *arg)
{
	int i;

	for (i = 0; str_name[i]; i++)
		if (!strcmp(arg, str_name[i]))
		{
			scale_effect.effect = i;
			return 0;
		}

	return 0;
}

//============================================================
//	scale_name
//============================================================

const char *scale_name(int effect)
{
	return str_name[effect];
}

//============================================================
//	scale_desc
//============================================================

const char *scale_desc(int effect)
{
	return str_desc[effect];
}

//============================================================
//	scale_exit
//============================================================

int scale_exit(void)
{
	int i;

	for (i = 0; i < MAX_SCALE_BANK; i++)
	{
		previous_depth[i] = previous_width[i] = previous_height[i] = 0;

		if (scale_buffer[i] != nullptr)
		{
			delete[] scale_buffer[i];      // <-- Reemplazo moderno y seguro
			scale_buffer[i] = nullptr;
		}
	}

	return 0;
}

//============================================================
//	x86_get_features
//============================================================
static uint32_t x86_get_features(void)
{
    // Forzamos el flag de compatibilidad MMX (1 << 23) de forma directa.
    // Todas las CPUs de 64 bits del mundo soportan MMX, por lo que este chequeo por ensamblador es obsoleto.
    uint32_t features = (1 << 23); 
    return features;
}


//============================================================
//	scale_init
//============================================================

int scale_init(void)
{
	static char name[64];

#ifndef PTR64
	uint32_t features = x86_get_features();
	use_mmx = (features & (1 << 23));
#endif /* PTR64 */

	scale_exit();

	scale_effect.xsize = scale_effect.ysize = 1;
	sprintf(name, "none");
	scale_effect.name = name;

	switch (scale_effect.effect)
	{
		case SCALE_EFFECT_NONE:
		{
			break;
		}

		case SCALE_EFFECT_SCANLINESTV:
		{
			sprintf(name, "Scanlines TV");
			scale_effect.xsize = scale_effect.ysize = 2;
			break;
		}

		case SCALE_EFFECT_EPXB:
		case SCALE_EFFECT_EPXC:
		{
			sprintf(name, "EPX");
			scale_effect.xsize = scale_effect.ysize = 2;
			break;
		}

		case SCALE_EFFECT_SCALE2X:
		{
			sprintf(name, "Scale2x (%s)", use_mmx ? "mmx optimised" : "non-mmx version");
			scale_effect.xsize = scale_effect.ysize = 2;
			break;
		}

		case SCALE_EFFECT_SCALE3X:
		{
			sprintf(name, "Scale3x (non-mmx version)");
			scale_effect.xsize = scale_effect.ysize = 3;
			break;
		}

		case SCALE_EFFECT_2XSAI:
		case SCALE_EFFECT_SUPER2XSAI:
		case SCALE_EFFECT_SUPEREAGLE:
		{
			if (scale_effect.effect == SCALE_EFFECT_2XSAI)
				sprintf(name, "2xSaI");
			else if (scale_effect.effect == SCALE_EFFECT_SUPER2XSAI)
				sprintf(name, "Super 2xSaI");
			else if (scale_effect.effect == SCALE_EFFECT_SUPEREAGLE)
				sprintf(name, "Super Eagle");

			scale_effect.xsize = scale_effect.ysize = 2;
			break;
		}

		case SCALE_EFFECT_2XPM:
		{
			sprintf(name, "2xPM");
			scale_effect.xsize = scale_effect.ysize = 2;
			break;
		}

		case SCALE_EFFECT_HQ2X:
		case SCALE_EFFECT_HQ2XS:
		case SCALE_EFFECT_HQ2XBOLD:
		{
			sprintf(name, "HQ2x");
			scale_effect.xsize = scale_effect.ysize = 2;
			break;
		}

		case SCALE_EFFECT_HQ3X:
		case SCALE_EFFECT_HQ3XS:
		case SCALE_EFFECT_HQ3XBOLD:
		{
			sprintf(name, "HQ3x");
			scale_effect.xsize = scale_effect.ysize = 3;
			break;
		}

		case SCALE_EFFECT_2XBRZ:
		{
			sprintf(name, "2xXBRZ");
			scale_effect.xsize = scale_effect.ysize = 2;
			break;
		}

		case SCALE_EFFECT_3XBRZ:
		{
			sprintf(name, "3xXBRZ");
			scale_effect.xsize = scale_effect.ysize = 3;
			break;
		}

		default:
		{
			return 1;
		}
	}

	return 0;
}



//============================================================
//	scale_check
//============================================================

int scale_check(int depth)
{
	switch (scale_effect.effect)
	{
		case SCALE_EFFECT_NONE:
			return 0;

		case SCALE_EFFECT_SCALE2X:
		case SCALE_EFFECT_SCALE3X:
			if (depth == 15 || depth == 16 || depth == 32)
				return 0;
			else
				return 1;

		case SCALE_EFFECT_SCANLINESTV://fixme for 32
		case SCALE_EFFECT_EPXB:
		case SCALE_EFFECT_EPXC:
		case SCALE_EFFECT_2XPM:
			if (depth == 15)
				return 0;
			else
				return 1;

		case SCALE_EFFECT_2XSAI:
		case SCALE_EFFECT_SUPER2XSAI:
		case SCALE_EFFECT_SUPEREAGLE:
			if (depth == 15 || depth == 32)
			{
				Init_2xSaI(555, (depth == 15) ? 16 : 32);
				return 0;
			}
			else
				return 1;

		case SCALE_EFFECT_HQ2X:
		case SCALE_EFFECT_HQ3X:
			if (depth == 15)
			{
				InitLUTs();	//snes9x
				return 0;
			}
			else if (depth == 32)
				return 0;
			else
				return 1;

		case SCALE_EFFECT_HQ2XS:
			if (depth == 15)
			{
				InitLUTs();	//snes9x
				return 0;
			}
			else if (depth == 32)
			{
				hqxx_init(32);	//vba
				return 0;
			}
			else
				return 1;

		case SCALE_EFFECT_HQ2XBOLD:
		case SCALE_EFFECT_HQ3XS:
		case SCALE_EFFECT_HQ3XBOLD:
			if (depth == 15)
			{
				InitLUTs();
				return 0;
			}
			else
				return 1;

		case SCALE_EFFECT_2XBRZ:
		case SCALE_EFFECT_3XBRZ:
			if (depth == 32)
				return 0;
			else
				return 1;

		default:
			return 1;
	}
}



//============================================================
//	scale_perform_scale
//============================================================

int scale_perform_scale(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height, int depth, int update, int bank)
{
	switch (scale_effect.effect)
	{
		case SCALE_EFFECT_NONE:
			return 0;
		
		case SCALE_EFFECT_SCANLINESTV:
			ScanlinesTV((unsigned char*)src, (unsigned int)src_pitch, NULL, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			return 0;

		case SCALE_EFFECT_EPXC:
			RenderEPXC((unsigned char*)src, (unsigned int)src_pitch, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			return 0;		

		case SCALE_EFFECT_EPXB:
			RenderEPXB((unsigned char*)src, (unsigned int)src_pitch, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			return 0;

		case SCALE_EFFECT_SCALE2X:
			return scale_perform_scale2x(src, dst, src_pitch, dst_pitch, width, height, depth, bank);

		case SCALE_EFFECT_SCALE3X:
			return scale_perform_scale3x(src, dst, src_pitch, dst_pitch, width, height, depth);

		case SCALE_EFFECT_2XSAI:
			if (depth == 15)
				_2xSaI((unsigned char*)src, (unsigned int)src_pitch, NULL, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			else
				_2xSaI32((unsigned char*)src, (unsigned int)src_pitch, NULL, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			return 0;

		case SCALE_EFFECT_SUPER2XSAI:
			if (depth == 15)
				Super2xSaI((unsigned char*)src, (unsigned int)src_pitch, NULL, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			else
				Super2xSaI32((unsigned char*)src, (unsigned int)src_pitch, NULL, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			return 0;

		case SCALE_EFFECT_SUPEREAGLE:
			if (depth == 15)
				SuperEagle((unsigned char*)src, (unsigned int)src_pitch, NULL, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			else
				SuperEagle32((unsigned char*)src, (unsigned int)src_pitch, NULL, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			return 0;

		case SCALE_EFFECT_2XPM:
			if (depth != 15)
				return 1;

			_2xpm_555(src, dst, (unsigned long)src_pitch, (unsigned long)dst_pitch, (unsigned long)width, (unsigned long)height, depth);
			return 0;

		case SCALE_EFFECT_HQ2X:
			if (depth == 15)
				RenderHQ2X((unsigned char*)src, (unsigned int)src_pitch, (unsigned char*)dst, (unsigned int)dst_pitch, width, height, 2);
			else
				return scale_perform_hq2x(src, dst, src_pitch, dst_pitch, width, height, depth);

			return 0;

		case SCALE_EFFECT_HQ2XS:
			if (depth == 15)
				RenderHQ2X((unsigned char*)src, (unsigned int)src_pitch, (unsigned char*)dst, (unsigned int)dst_pitch, width, height, 1);
			else
				hq2xS32((unsigned char*)src, (unsigned int)src_pitch, NULL, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			return 0;

		case SCALE_EFFECT_HQ2XBOLD:
			RenderHQ2X((unsigned char*)src, (unsigned int)src_pitch, (unsigned char*)dst, (unsigned int)dst_pitch, width, height, 0);
			return 0;

		case SCALE_EFFECT_HQ3X:
			if (depth == 15)
				RenderHQ3X((unsigned char*)src, (unsigned int)src_pitch, (unsigned char*)dst, (unsigned int)dst_pitch, width, height, 2);
			else
				return scale_perform_hq3x(src, dst, src_pitch, dst_pitch, width, height, depth);

			return 0;

		case SCALE_EFFECT_HQ3XS:
//			hq3xS32((unsigned char*)src, (unsigned int)src_pitch, NULL, (unsigned char*)dst, (unsigned int)dst_pitch, width, height);
			RenderHQ3X((unsigned char*)src, (unsigned int)src_pitch, (unsigned char*)dst, (unsigned int)dst_pitch, width, height, 1);
			return 0;

		case SCALE_EFFECT_HQ3XBOLD:
			RenderHQ3X((unsigned char*)src, (unsigned int)src_pitch, (unsigned char*)dst, (unsigned int)dst_pitch, width, height, 0);
			return 0;
			
		case SCALE_EFFECT_2XBRZ:
			Render2xXbrz((unsigned char*)src, src_pitch, (unsigned char*)dst, dst_pitch, width, height);
			return 0;

		case SCALE_EFFECT_3XBRZ:
			Render3xXbrz((unsigned char*)src, src_pitch, (unsigned char*)dst, dst_pitch, width, height);
			return 0;

		default:
			return 1;
	}
}

//============================================================
//	scale_emms
//============================================================

inline void scale_emms(void)
{
#ifdef USE_MMX_INTERP_SCALE
	if (use_mmx)
	{
#ifdef __GNUC__
		__asm__ __volatile__ (
			"emms\n"
		);
#else
		__asm {
			emms;
		}
#endif
	}
#endif /* USE_MMX_INTERP_SCALE */
}


//============================================================
//	scale_perform_scale2x
//============================================================
static int scale_perform_scale2x(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height, int depth, int bank)
{
	int y;
	uint8_t *src_prev = src;
	uint8_t *src_curr = src;
	uint8_t *src_next = src + src_pitch;

	if (depth != 15 && depth != 16 && depth != 32)
		return 1;

	if (previous_depth[bank] != depth)
	{
#ifdef USE_MMX_INTERP_SCALE
		if (use_mmx)
		{
			scale_scale2x_line_16 = scale2x_16_mmx;
			scale_scale2x_line_32 = scale2x_32_mmx;
		}
		else
#endif /* USE_MMX_INTERP_SCALE */
		{
			scale_scale2x_line_16 = scale2x_16_def;
			scale_scale2x_line_32 = scale2x_32_def;
		}

		previous_depth[bank] = depth;
	}

	if (depth == 15 || depth == 16)
//		scale_scale2x_line_16((uint16_t *)dst, (uint16_t *)(dst + dst_pitch), (uint16_t *)src_prev, (uint16_t *)src_curr, (uint16_t *)src_next, width);
		scale2x_16_def((uint16_t *)dst, (uint16_t *)(dst + dst_pitch), (uint16_t *)src_prev, (uint16_t *)src_curr, (uint16_t *)src_next, width);
	else
//		scale_scale2x_line_32((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);
		scale2x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);

	if (depth == 15 || depth == 16)
	{
		for (y = 2; y < height; y++)
		{
			dst += 2 * dst_pitch;
			src_prev = src_curr;
			src_curr = src_next;
			src_next += src_pitch;
			scale_scale2x_line_16((uint16_t *)dst, (uint16_t *)(dst + dst_pitch), (uint16_t *)src_prev, (uint16_t *)src_curr, (uint16_t *)src_next, width);
		}
	}
	else
	{
		for (y = 2; y < height; y++)
		{
			dst += 2 * dst_pitch;
			src_prev = src_curr;
			src_curr = src_next;
			src_next += src_pitch;
			scale_scale2x_line_32((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);
		}
	}

	dst += 2 * dst_pitch;
	src_prev = src_curr;
	src_curr = src_next;
	if (depth == 15 || depth == 16)
		scale_scale2x_line_16((uint16_t *)dst, (uint16_t *)(dst + dst_pitch), (uint16_t *)src_prev, (uint16_t *)src_curr, (uint16_t *)src_next, width);
	else
		scale_scale2x_line_32((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);

	scale_emms();

	return 0;
}

//============================================================
//	scale_perform_scale3x
//============================================================

static int scale_perform_scale3x(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height, int depth)
{
	int y;
	uint8_t *src_prev = src;
	uint8_t *src_curr = src;
	uint8_t *src_next = src + src_pitch;

	if (depth != 15 && depth != 16 && depth != 32)
		return 1;

	if (depth == 15 || depth == 16)
		scale3x_16_def((uint16_t *)dst, (uint16_t *)(dst + dst_pitch), (uint16_t *)(dst + 2 * dst_pitch), (uint16_t *)src_prev, (uint16_t *)src_curr, (uint16_t *)src_next, width);
	else
		scale3x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)(dst + 2 * dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);

	if (depth == 15 || depth == 16)
	{
		for (y = 2; y < height; y++)
		{
			dst	+= 3 * dst_pitch;
			src_prev = src_curr;
			src_curr = src_next;
			src_next += src_pitch;
			scale3x_16_def((uint16_t *)dst, (uint16_t *)(dst + dst_pitch), (uint16_t *)(dst + 2 * dst_pitch), (uint16_t *)src_prev, (uint16_t *)src_curr, (uint16_t *)src_next, width);
		}
	}
	else
	{
		for (y = 2; y < height; y++)
		{
			dst += 3 * dst_pitch;
			src_prev = src_curr;
			src_curr = src_next;
			src_next += src_pitch;
			scale3x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)(dst + 2 * dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);
		}
	}

	dst += 3 * dst_pitch;
	src_prev = src_curr;
	src_curr = src_next;
	if (depth == 15 || depth == 16)
		scale3x_16_def((uint16_t *)dst, (uint16_t *)(dst + dst_pitch), (uint16_t *)(dst + 2 * dst_pitch), (uint16_t *)src_prev, (uint16_t *)src_curr, (uint16_t *)src_next, width);
	else
		scale3x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)(dst + 2 * dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);

	return 0;
}

//============================================================
//	scale_perform_hq2x
//============================================================

static int scale_perform_hq2x(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height, int depth)
{
	int y;
	uint8_t *src_prev = src;
	uint8_t *src_curr = src;
	uint8_t *src_next = src + src_pitch;

	interp_init();

	hq2x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);

	for (y = 2; y < height; y++)
	{
		dst += 2 * dst_pitch;
		src_prev = src_curr;
		src_curr = src_next;
		src_next += src_pitch;

		hq2x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);
	}

	dst += 2 * dst_pitch;
	src_prev = src_curr;
	src_curr = src_next;

	hq2x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);

	return 0;
}

//============================================================
//	scale_perform_hq3x
//============================================================

static int scale_perform_hq3x(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height, int depth)
{
	int y;
	uint8_t *src_prev = src;
	uint8_t *src_curr = src;
	uint8_t *src_next = src + src_pitch;

	interp_init();
	
	hq3x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)(dst + 2 * dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);

	for (y = 2; y < height; y++)
	{
		dst += 3 * dst_pitch;
		src_prev = src_curr;
		src_curr = src_next;
		src_next += src_pitch;

		hq3x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)(dst + 2 * dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);
	}

	dst += 3 * dst_pitch;
	src_prev = src_curr;
	src_curr = src_next;

	hq3x_32_def((uint32_t *)dst, (uint32_t *)(dst + dst_pitch), (uint32_t *)(dst + 2 * dst_pitch), (uint32_t *)src_prev, (uint32_t *)src_curr, (uint32_t *)src_next, width);

	return 0;
}
