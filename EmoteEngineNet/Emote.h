// Emote.h

#pragma once
#include "Lock.h"
#include "iemote.h"
#include "EmoteDevice.h"
#include "EmotePlayer.h"
#include "Enums.h"
#include "Core.h"
#include "D3DX9Math.h"
#include "EmoteDriverAdapter.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace EmoteEngineNet {
	ref class EmoteDevice;
	ref class EmotePlayer;
	ref class EmoteDriverAdapater;

	public ref class Emote
	{

#pragma region Construction/Destruction
	public:
		Emote(IntPtr dxHandle);
		Emote(IntPtr dxHandle, String^ EnginePath);
		Emote(IntPtr handle, bool useD3DSurface);
		Emote(IntPtr handle, int width, int height);
		Emote(IntPtr handle, int width, int height, bool useD3DSurface);
		Emote(IntPtr handle, int width, int height, bool useD3DSurface, bool setTransparent);

	protected:
		~Emote();
#pragma endregion Construction/Destruction

#pragma region DirectX
	public:
		void D3DBeginScene();
		void D3DEndScene();

		void D3DInit(IntPtr handle, int width, int height, bool useD3DSurface, bool setTransparent);
		void D3DInitRenderState();
		void D3DInitRenderState(int screenWidth, int screenHeight, IntPtr handle);

		void D3DRelease();
		void D3DReset();

		uint32_t D3DTestCooperativeLevel();

		void OnDeviceLost();
		void OnDeviceReset();
#pragma endregion DirectX

#pragma region CanvasTexture
	public:
		void AttachCanvasTexture();
		void DetachCanvasTexture();
		void DrawCanvasTexture();
	private:
		void RequireCanvasTexture();
#pragma endregion CanvasTexture

#pragma region Add/Remove Player
	public:
		EmotePlayer^ CreatePlayer(String^ name, String^ path);
		EmotePlayer^ CreatePlayer(String^ name, Stream^ stream);
		void DeletePlayer(String^ player);
		void DeletePlayer(EmotePlayer^ player);
#pragma endregion Add/Remove Player

#pragma region PlayerCollectionFunctions
	public:
		void Draw();
		void Show();
		void Skip();
		void Update(float frameCount);
#pragma endregion PlayerCollectionFunctions




	public:
		void Emote::LoadEmoteEngine(String^ EnginePath);
		void LoadEmoteEngine();
		EmoteDevice^ EmoteInit();
	private:
		EmoteDevice^ EmoteInit(IntPtr dxHandle);

	
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

		//IEmoteDevice__TYPE* sEmoteDevice;
		Adapter::EmoteDeviceBase^ sEmoteDevice;
	
		bool transparent = false;

	public:
		//EmoteFactoryFunction_3_52 EmoteCreate_3_52;
		//EmoteFactoryFunction_3_4 EmoteCreate_3_4;
		//EmoteFactoryFunction_NEKO1 EmoteCreate_NEKO1;
		//EmoteFactoryFunction_NEKO0 EmoteCreate_NEKO0;
		//EmoteFactoryFunction__TYPE EmoteCreate__TYPE;

		EmoteFilterTextureFunction EmoteFilterTexture;

	private:
		Adapter::EmoteDriverBase^ driver;
};
}
