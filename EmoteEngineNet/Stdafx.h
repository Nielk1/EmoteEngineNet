// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"User32.lib")

//#define IEmoteDevice__TYPE IEmoteDevice_3_4_NEKO
//#define IEmotePlayer__TYPE IEmotePlayer_3_4_NEKO

//#define IEmoteDevice__TYPE IEmoteDevice_NEKO0
//#define IEmotePlayer__TYPE IEmotePlayer_NEKO0

//#define IEmoteDevice__TYPE IEmoteDevice_3_52
//#define IEmotePlayer__TYPE IEmotePlayer_3_52

//#define IEmoteDevice__TYPE IEmoteDevice_3_4
//#define IEmotePlayer__TYPE IEmotePlayer_3_4

#include <cstdint>
#include "EmoteDriverAdapter.h"
#include "iemote.h"
#include "Emote.h"
#include "EmoteDevice.h"
#include "EmotePlayer.h"
#include "Enums.h"
#include "TextureFilterFunction.h"

struct LVERTEX {
	float    x, y, z;
	D3DCOLOR color;
	float    tu, tv;
};

#define FVF_LVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

static uint32_t clp(uint32_t x)
{
	x--;
	uint32_t expr_06 = x;
	x = (expr_06 | expr_06 >> 1);
	uint32_t expr_0D = x;
	x = (expr_0D | expr_0D >> 2);
	uint32_t expr_14 = x;
	x = (expr_14 | expr_14 >> 4);
	uint32_t expr_1B = x;
	x = (expr_1B | expr_1B >> 8);
	return (x >> 16 | x) + 1;
}
