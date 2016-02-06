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
	namespace Adapter {
		// this will eventually be an abstract base
		ref class EmoteDriverBase
		{
		internal:
			EmoteDriverBase(String^ EnginePath)
			{
				IntPtr EnginePathPtr = System::Runtime::InteropServices::Marshal::StringToHGlobalUni(EnginePath);
				ptrEmoteCreate = LoadLibraryW((LPCWSTR)EnginePathPtr.ToPointer());
				EmoteCreate__TYPE = (EmoteFactoryFunction__TYPE)GetProcAddress(ptrEmoteCreate, (LPCSTR)("?EmoteCreate@@YAPAVIEmoteDevice@@ABUInitParam@1@@Z"));
			}
			~EmoteDriverBase()
			{
				if (ptrEmoteCreate != NULL)
				{
					::FreeLibrary(ptrEmoteCreate);
				}
			}

		public:
			IEmoteDevice__TYPE* EmoteCreate(IDirect3DDevice9* sD3DDevice)
			{
				IEmoteDevice__TYPE::InitParam initParam;
				ZeroMemory(&initParam, sizeof(initParam));
				initParam.d3dDevice = sD3DDevice;

				return EmoteCreate__TYPE(initParam);
			}
		private:
			EmoteFactoryFunction__TYPE EmoteCreate__TYPE;
			HINSTANCE__* ptrEmoteCreate;
		};
	}
}