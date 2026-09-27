#include <cstring>
#include <cstdint>

// Blitter de velocidad pura por hardware para paletas de 15/16 bits (Formatos IND16/RGB15)
void scale_none_16(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height)
{
	for (int h = 0; h < height; h++)
	{
		std::memcpy(dst + (h * dst_pitch), src + (h * src_pitch), width * 2);
	}
}

// Blitter de velocidad pura por hardware para alta definición de 32 bits (Formato RGB32)
void scale_none_32(uint8_t *src, uint8_t *dst, int src_pitch, int dst_pitch, int width, int height)
{
	for (int h = 0; h < height; h++)
	{
		std::memcpy(dst + (h * dst_pitch), src + (h * src_pitch), width * 4);
	}
}
