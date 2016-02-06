#pragma once

//http://stackoverflow.com/questions/27096103/managed-directx-sharpdx-slimdx-working-without-installer

//#pragma comment(lib,"emotedriver.lib")

#include "stdafx.h"

using namespace System;
using namespace EmoteEngineNet;



typedef HRESULT (WINAPI *pfnCreate9Ex)(UINT SDKVersion, IDirect3D9Ex**);
static pfnCreate9Ex g_pfnCreate9Ex;
static IDirect3DSurface9* g_psysSurface;
static tagWNDCLASSEXW g_wc;
static IDirect3DSurface9* sBackBufferSurface;
static IDirect3D9* sD3D;
static D3DCAPS9 sD3DCaps;
static IDirect3D9Ex* sD3DEx;
static D3DPRESENT_PARAMETERS sD3Dpp;
static HWND__* sHwnd;
static int sLeftMouseDragging;
static int sPrevMouseX;
static int sPrevMouseY;
static int sRightMouseDragging;



//static HINSTANCE__* ptrEmoteCreate__TYPE;


static unsigned int GetVertexProcessingCaps()
{
	unsigned int num = 32;
	_D3DCAPS9 d3DCAPS;
	if (SUCCEEDED(sD3DEx->GetDeviceCaps(0, D3DDEVTYPE::D3DDEVTYPE_HAL, &d3DCAPS)) >= 0)
	{
		num = (((d3DCAPS.DevCaps & 0x10000) != 0) ? 64 : num);
	}
	return num;
}

static void InitializeD3D(HWND__* hWnd, _D3DPRESENT_PARAMETERS_ d3dpp, IDirect3DDevice9** sD3DDevice)
{
	sD3D = Direct3DCreate9(32u);
	if (sD3D != NULL)
	{
		sD3D->CreateDevice(0, D3DDEVTYPE::D3DDEVTYPE_HAL, hWnd, 70, &d3dpp, sD3DDevice);
	}
}

static void InitializeD3DEx(HWND__* hWnd, _D3DPRESENT_PARAMETERS_ d3dpp, IDirect3DDevice9Ex** sD3DDeviceEx, IDirect3DDevice9** sD3DDevice, bool rewrite)
{
	d3dpp.BackBufferCount = 2;
	d3dpp.SwapEffect = D3DSWAPEFFECT::D3DSWAPEFFECT_FLIPEX;
	d3dpp.BackBufferFormat = D3DFORMAT::D3DFMT_A8R8G8B8;

	if (g_pfnCreate9Ex(32, &sD3DEx) >= 0 && (!rewrite || SUCCEEDED(sD3DEx->QueryInterface(__uuidof(IDirect3D9), (void**)&sD3D))))
	{
		unsigned int num = GetVertexProcessingCaps();
		if (SUCCEEDED(sD3DEx->CreateDeviceEx(0, D3DDEVTYPE::D3DDEVTYPE_HAL, hWnd, num | 6, &d3dpp, 0, sD3DDeviceEx)) && rewrite)
		{
			(*sD3DDeviceEx)->QueryInterface(__uuidof(IDirect3DDevice9), (void**)&sD3DDevice);
		}
	}
}