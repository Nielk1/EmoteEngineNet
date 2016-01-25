#pragma once

#include "iemote.h"
#include "Emote.h"
#include "EmotePlayer.h"
#include "Enums.h"
#include "TextureFilterFunction.h"
#include <vcclr.h>

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace EmoteEngineNet {
	ref class EmotePlayer;

	public ref class EmoteDevice
	{

	public:
		~EmoteDevice();
		UInt32 AddRef();

		AlphaOp GetAlphaOp();
		MaskMode GetMaskMode();
		bool GetMaskRegionClipping();
		bool GetMipMapEnabled();
		int GetPixelateDivision();
		bool GetProtectTranslucentTextureColor();
		ShaderModel GetShaderModel();

		void OnDeviceLost();

		void OnRenderTarget(IntPtr renderTargetTexture);

		void Release();

		void SetAlphaOp(AlphaOp op);
		void SetMaskMode(MaskMode mask);
		void SetMaskRegionClipping(bool state);
		void SetMaxTextureSize(UInt32 width, UInt32 height);
		void SetMipMapEnabled(bool state);
		void SetPixelateDivision(int division);
		void SetProtectTranslucentTextureColor(bool state);
		void SetShaderModel(ShaderModel shaderModel);


	internal:
		EmoteDevice(::IEmoteDevice__TYPE* sDevice);
		void OnRenderTarget(IDirect3DTexture9* renderTargetTexture);
		EmotePlayer ^CreatePlayer(String^ path);

	internal:
		property ::IEmoteDevice__TYPE* NativeDevice {
			::IEmoteDevice__TYPE* get();
		}


	public:
		property TextureFilterFunction^ TextureFilter {
			TextureFilterFunction^ get();
			void set(TextureFilterFunction^ value);
		}

		property bool UseTextureFilter {
			bool get();
			void set(bool value);
		}

	private:
		TextureFilterFunction^ backing_store__TextureFilter;
		bool backing_store__UseTextureFilter;
		IEmoteDevice__TYPE* device = NULL;
	};
}