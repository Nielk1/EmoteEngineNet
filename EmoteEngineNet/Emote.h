// Emote.h

#pragma once
#include "Lock.h"
#include "iemote.h"
#include "EmoteDevice.h"
#include "EmotePlayer.h"
#include "Enums.h"
#include "Core.h"
#include "D3DX9Math.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace EmoteEngineNet {
	ref class EmoteDevice;
	ref class EmotePlayer;

	public ref class Emote
	{

	public:
		Emote(IntPtr dxHandle);
		Emote(IntPtr handle, bool useD3DSurface);
		Emote(IntPtr handle, int width, int height);
		Emote(IntPtr handle, int width, int height, bool useD3DSurface);
		Emote(IntPtr handle, int width, int height, bool useD3DSurface, bool setTransparent);

	protected:
		~Emote();

	public:
		void LoadEmoteEngine();

		void AttachCanvasTexture();
			
		EmotePlayer^ CreatePlayer(String^ name, String^ path);

		void D3DBeginScene();
		void D3DEndScene();
		void D3DInit(IntPtr handle, int width, int height, bool useD3DSurface, bool setTransparent);
		void D3DInitRenderState();
		void D3DInitRenderState(int screenWidth, int screenHeight, IntPtr handle);
		void D3DRelease();
		void D3DReset();
		UInt32 D3DTestCooperativeLevel();
			
		void DeletePlayer(String^ player);
		void DeletePlayer(EmotePlayer^ player);
			
		void DetachCanvasTexture();

		void Draw();
		void DrawCanvasTexture();

		EmoteDevice^ EmoteInit();

		void OnDeviceLost();
		void OnDeviceReset();

		void Show();
		void Skip();
		void Update(float frameCount);

	private:
		EmoteDevice^ EmoteInit(IntPtr dxHandle);
		void RequireCanvasTexture();
	
	public:
		property int D3DCanvasTexture
		{
			int get();
			void set(int value);
		}

		property int D3Device
		{
			int get();
			void set(int value);
		}

		property int D3DSurface
		{
			int get();
		}
			
		property EmoteDevice^ Device
		{
			EmoteDevice^ get();
		}

		property EmotePlayer^ default[String^]
		{
			EmotePlayer^ get(String^ name);
		}

		property int SurfaceHeight
		{
			int get();
		}

		property int SurfaceWidth
		{
			int get();
		}

		property bool UseD3DSurface
		{
			bool get();
		}

	private:
		EmoteDevice^ device;
		Dictionary<String^, EmotePlayer^>^ EmotePlayers;

		int sScreenHeight;
		int sScreenWidth;

		int sCanvasTextureHeight;
		int sCanvasTextureWidth;

		int sD3DeviceHandle;
		IDirect3DDevice9* sD3DDevice;

		bool useD3DEx = false;
		IDirect3DDevice9Ex* sD3DDeviceEx;

		bool useD3DSurface = false;
		IDirect3DSurface9* sSurface;

		IDirect3DTexture9* sCanvasTexture;

		IEmoteDevice__TYPE* sEmoteDevice;
	
		bool transparent = false;
};
}
