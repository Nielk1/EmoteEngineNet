#include "stdafx.h"
#include "Emote.h"

namespace EmoteEngineNet {

	Emote::Emote(IntPtr dxHandle) {
		LoadEmoteEngine();
		EmoteInit(dxHandle);
	}
	Emote::Emote(IntPtr handle, bool useD3DSurface) {
		D3DInit(handle, -1, -1, false, false);
	}
	Emote::Emote(IntPtr handle, int width, int height) {
		D3DInit(handle, width, height, false, false);
	}
	Emote::Emote(IntPtr handle, int width, int height, bool useD3DSurface) {
		D3DInit(handle, width, height, useD3DSurface, false);
	}
	Emote::Emote(IntPtr handle, int width, int height, bool useD3DSurface, bool setTransparent) {
		D3DInit(handle, width, height, useD3DSurface, setTransparent);
	}

	Emote::~Emote()
	{
		Dictionary<String^, EmotePlayer^>::ValueCollection::Enumerator^ enumerator = EmotePlayers->Values->GetEnumerator();
		while (enumerator->MoveNext())
		{
			EmotePlayer^ current = enumerator->Current;
			try
			{
				if (current != nullptr)
				{
					current = nullptr;
				}
				continue;
			}
			catch (Exception^)
			{
				continue;
			}
		}
		EmoteDevice^ emoteDevice = device;
		if (emoteDevice != nullptr)
		{
			device = nullptr;
		}

		if (ptrEmoteCreate__TYPE != NULL)
			FreeLibrary(ptrEmoteCreate__TYPE);
	}

	void Emote::LoadEmoteEngine()
	{
		if (EmoteCreate__TYPE == NULL)
		{
			ptrEmoteCreate__TYPE = LoadLibraryW((LPCWSTR)(L"emotedriver.dll"));
			EmoteCreate__TYPE = (EmoteFactoryFunction__TYPE)GetProcAddress(ptrEmoteCreate__TYPE, (LPCSTR)("?EmoteCreate@@YAPAVIEmoteDevice@@ABUInitParam@1@@Z"));
		}
	}

	void Emote::AttachCanvasTexture()
	{
		RequireCanvasTexture();

		if (!sCanvasTexture)
			return;

		sD3DDevice->GetRenderTarget(0, &sBackBufferSurface);
		LPDIRECT3DSURFACE9 surface;
		sCanvasTexture->GetSurfaceLevel(0, &surface);
		sD3DDevice->SetRenderTarget(0, surface);
		surface->Release();
		D3DVIEWPORT9 vp = { 0, 0, sScreenWidth, sScreenHeight, 0.0f, 1.0f };
		sD3DDevice->SetViewport(&vp);
		sD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);
	}

	EmotePlayer^ Emote::CreatePlayer(String^ name, String^ path)
	{
		Lock lock(EmotePlayers);
		if (!EmotePlayers->ContainsKey(name))
		{
			EmotePlayer^ emotePlayer = device->CreatePlayer(path);
			EmotePlayers->Add(name, emotePlayer);
			return emotePlayer;
		}
		return EmotePlayers[name];
	}

	void Emote::D3DBeginScene()
	{
		sD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		if (sD3DDevice->BeginScene() < 0)
		{
			throw gcnew Exception("D3D Begin Scene Failed.");
		}
		if (useD3DEx)
		{
			sD3DDeviceEx->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
			if (sD3DDeviceEx->BeginScene() < 0)
			{
				throw gcnew Exception("D3DEx Begin Scene Failed.");
			}
		}
	}

	void Emote::D3DEndScene() {
		sD3DDevice->EndScene();
		if (useD3DEx)
		{
			sD3DDevice->Present(0, 0, 0, 0);
			if (useD3DEx && useD3DSurface)
			{
				if (sD3DDeviceEx->StretchRect(sSurface, 0, sBackBufferSurface, 0, D3DTEXTUREFILTERTYPE::D3DTEXF_NONE) < 0)
				{
					return;
				}
			}
			sD3DDeviceEx->EndScene();
		}
	}

	void Emote::D3DInit(IntPtr handle, int width, int height, bool _useD3DSurface, bool setTransparent) {
		if (handle != IntPtr::Zero)
		{
			sHwnd = (HWND)handle.ToInt32();
		}
		sScreenHeight = height;
		sScreenWidth = width;
		useD3DSurface = _useD3DSurface;
		transparent = setTransparent;
		if (width < 0 || height < 0)
		{
			tagRECT tagRECT;
			GetClientRect(sHwnd, &tagRECT);
			sScreenWidth = Math::Abs(tagRECT.right - tagRECT.left);
			sScreenHeight = Math::Abs(tagRECT.bottom - tagRECT.top);
		}
		
		HINSTANCE__* ptr = LoadLibraryW((LPCWSTR)(L"d3d9.dll"));
		g_pfnCreate9Ex = (pfnCreate9Ex) GetProcAddress(ptr, (LPCSTR)("Direct3DCreate9Ex"));
		useD3DEx = (g_pfnCreate9Ex != 0);
		FreeLibrary(ptr);
		useD3DEx = false;
		
		ZeroMemory(&sD3Dpp, sizeof(sD3Dpp));
		sD3Dpp.BackBufferWidth = sScreenWidth;
		sD3Dpp.BackBufferHeight = sScreenHeight;
		sD3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		sD3Dpp.Windowed = true;
		sD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		sD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		if (useD3DEx)
		{
			pin_ptr<IDirect3DDevice9Ex*> p1 = &sD3DDeviceEx;
			pin_ptr<IDirect3DDevice9*> p2  = &sD3DDevice;
			InitializeD3DEx(sHwnd, sD3Dpp, p1, p2, true);
		}
		else
		{
			pin_ptr<IDirect3DDevice9*> p1 = &sD3DDevice;
			InitializeD3D(sHwnd, sD3Dpp, p1);
		}
		sD3DeviceHandle = (int)sD3DDevice;
		if (useD3DEx)
		{
			sD3DeviceHandle = (int)sD3DDeviceEx;
		}
		if (useD3DSurface)
		{
			if (useD3DEx)
			{
				if (sD3DDeviceEx->CreateRenderTarget(sScreenWidth, sScreenHeight, D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, 0, &sBackBufferSurface, 0) < 0)
				{
					return;
				}
				pin_ptr<IDirect3DSurface9*> p1 = &sSurface;
				if (sD3DDevice->CreateOffscreenPlainSurface(sScreenWidth, sScreenHeight, D3DFMT_UNKNOWN, D3DPOOL_SYSTEMMEM, p1, 0) < 0)
				{
					return;
				}
				if (useD3DSurface)
				{
					sD3DDevice->SetRenderTarget(0, sSurface);
				}
			}
			else
			{
				pin_ptr<IDirect3DSurface9*> p1 = &sSurface;
				if (sD3DDevice->CreateRenderTarget(sScreenWidth, sScreenHeight, D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, 1, p1, 0) < 0)
				{
					return;
				}
				sD3DDevice->SetRenderTarget(0, sSurface);
				sD3DDevice->SetRenderState(D3DRS_CULLMODE, 1);
				sD3DDevice->SetRenderState(D3DRS_LIGHTING, 0);
				sD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
			}
		}
		D3DInitRenderState();
		if (setTransparent)
		{
			// do... something?
		}
	}



	void Emote::D3DInitRenderState(void)
	{
		if (sD3DDevice == NULL)
			return;

		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);

		D3DXMATRIX matProj;
		D3DXMatrixIdentity(&matProj);

		float aspect = 1.0f * sScreenWidth / sScreenHeight;
		matProj._11 = 1.0f / aspect;
		matProj._34 = 1.0f;
		matProj._44 = 0.0f;
		matProj._41 = 0.0f;
		matProj._42 = 0.0f;

		float scale = 1.0f;
		float fw = sScreenWidth;
		float fh = sScreenHeight;

		D3DXMATRIX matView;
		D3DXMatrixLookAtLH(&matView,
			&D3DXVECTOR3(-0.5f, 0.5f, -fh / 2),
			&D3DXVECTOR3(-0.5f, 0.5f, 0),
			&D3DXVECTOR3(0, -1, 0));

		matView._11 = -matView._11;

		sD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		sD3DDevice->SetTransform(D3DTS_VIEW, &matView);
		sD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

		sD3DDevice->SetFVF(FVF_LVERTEX);
		sD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		sD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		sD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		sD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		sD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		sD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		sD3DDevice->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
		sD3DDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
		sD3DDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
		sD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		sD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		sD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		sD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		sD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		sD3DDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
		sD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		sD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		sD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		sD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		sD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	}


	void Emote::D3DInitRenderState(int screenWidth, int screenHeight, IntPtr handle)
	{
		sScreenWidth = screenWidth;
		sScreenHeight = screenHeight;
		IDirect3DDevice9* ptr;
		if (handle != IntPtr::Zero && handle.ToInt64() > 0L)
		{
			ptr = (IDirect3DDevice9*)handle.ToPointer();
		}
		else
		{
			ptr = sD3DDevice;
		}
		if (ptr == NULL)
			return;

		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);

		D3DXMATRIX matProj;
		D3DXMatrixIdentity(&matProj);

		float aspect = 1.0f * sScreenWidth / sScreenHeight;
		matProj._11 = 1.0f / aspect;
		matProj._34 = 1.0f;
		matProj._44 = 0.0f;
		matProj._41 = 0.0f;
		matProj._42 = 0.0f;

		float scale = 1.0f;
		float fw = sScreenWidth;
		float fh = sScreenHeight;

		D3DXMATRIX matView;
		D3DXMatrixLookAtLH(&matView,
			&D3DXVECTOR3(-0.5f, 0.5f, -fh / 2),
			&D3DXVECTOR3(-0.5f, 0.5f, 0),
			&D3DXVECTOR3(0, -1, 0));

		matView._11 = -matView._11;

		sD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		sD3DDevice->SetTransform(D3DTS_VIEW, &matView);
		sD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

		sD3DDevice->SetFVF(FVF_LVERTEX);
		sD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		sD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		sD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		sD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		sD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		sD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		sD3DDevice->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
		sD3DDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
		sD3DDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
		sD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		sD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		sD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		sD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		sD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		sD3DDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
		sD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		sD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		sD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		sD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		sD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		sD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	}

	void Emote::D3DRelease() {
		if (sCanvasTexture != NULL)
		{
			sCanvasTexture->Release();
			sCanvasTexture = NULL;
		}
		if (sBackBufferSurface != NULL)
		{
			sBackBufferSurface->Release();
			sBackBufferSurface = NULL;
		}
		if (sD3DDevice != NULL)
		{
			sD3DDevice->Release();
			sD3DDevice = NULL;
		}
		if (sD3DDeviceEx != NULL)
		{
			sD3DDeviceEx->Release();
			sD3DDeviceEx = NULL;
		}
		if (sD3D != NULL)
		{
			sD3D->Release();
			sD3D = NULL;
		}
		if (sD3DEx != NULL)
		{
			sD3DEx->Release();
			sD3DEx = NULL;
		}
		if (sSurface != NULL)
		{
			sSurface->Release();
			sSurface = NULL;
		}
	}

	void Emote::D3DReset()
	{
		_D3DPRESENT_PARAMETERS_ d3DPRESENT_PARAMETERS_;

		memset(&d3DPRESENT_PARAMETERS_, 0, sizeof(d3DPRESENT_PARAMETERS_));
		d3DPRESENT_PARAMETERS_.BackBufferWidth = sScreenWidth;
		d3DPRESENT_PARAMETERS_.BackBufferHeight = sScreenHeight;
		d3DPRESENT_PARAMETERS_.BackBufferFormat = D3DFMT_UNKNOWN;
		d3DPRESENT_PARAMETERS_.Windowed = true;
		d3DPRESENT_PARAMETERS_.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3DPRESENT_PARAMETERS_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		
		sD3DDevice->Reset(&d3DPRESENT_PARAMETERS_);
	}

	UInt32 Emote::D3DTestCooperativeLevel()
	{
		return sD3DDevice->TestCooperativeLevel();
	}

	void Emote::DeletePlayer(EmotePlayer^ player)
	{
		if (player != nullptr)
		{
			Lock lock(EmotePlayers);
			if (EmotePlayers->ContainsValue(player))
			{
				List<String^>^ list = gcnew List<String^>();
				Dictionary<String^, EmotePlayer^>::Enumerator^ enumerator = EmotePlayers->GetEnumerator();
				if (enumerator->MoveNext())
				{
					do
					{
						KeyValuePair<String^, EmotePlayer^>^ current = enumerator->Current;
						if (current->Value == player)
						{
							list->Add(current->Key);
						}
					} while (enumerator->MoveNext());
				}
				List<String^>::Enumerator^ enumerator2 = list->GetEnumerator();
				if (enumerator2->MoveNext())
				{
					do
					{
						String^ current2 = enumerator2->Current;
						EmotePlayers->Remove(current2);
					} while (enumerator2->MoveNext());
				}
			}
		}
	}

	void Emote::DeletePlayer(String^ player)
	{
		Lock lock(EmotePlayers);
		if (EmotePlayers->ContainsKey(player))
		{
			EmotePlayer^ emotePlayer = EmotePlayers[player];
			EmotePlayers->Remove(player);
		}
	}


	void Emote::DetachCanvasTexture(void)
	{
		if (!sCanvasTexture)
			return;

		useD3DSurface = false;

		sD3DDevice->SetRenderTarget(0, sBackBufferSurface);
		sBackBufferSurface->Release();
	}

	void Emote::Draw()
	{
		Lock lock(EmotePlayers);
		Dictionary<String^, EmotePlayer^>::ValueCollection::Enumerator^ enumerator = EmotePlayers->Values->GetEnumerator();
		if (enumerator->MoveNext())
		{
			do
			{
				EmotePlayer^ current = enumerator->Current;
				if (current != nullptr)
				{
					sEmoteDevice->OnRenderTarget(sCanvasTexture);
					current->Render();
				}
			} while (enumerator->MoveNext());
		}
	}

	void Emote::DrawCanvasTexture()
	{
		if (!sCanvasTexture)
			return;

		float vl = -sScreenWidth / 2;
		float vt = -sScreenHeight / 2;
		float vr = sScreenWidth / 2;
		float vb = sScreenHeight / 2;
		float tl = 0.0f;
		float tt = 0.0f;
		float tr = float(sScreenWidth) / sCanvasTextureWidth;
		float tb = float(sScreenHeight) / sCanvasTextureHeight;

		LVERTEX vtx[4] = {
			{ vl, vt, 0, D3DCOLOR_ARGB(255, 255, 255, 255), tl, tt },
			{ vr, vt, 0, D3DCOLOR_ARGB(255, 255, 255, 255), tr, tt },
			{ vl, vb, 0, D3DCOLOR_ARGB(255, 255, 255, 255), tl, tb },
			{ vr, vb, 0, D3DCOLOR_ARGB(255, 255, 255, 255), tr, tb }
		};


		sD3DDevice->SetTexture(0, sCanvasTexture);
		sD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(LVERTEX));
		sD3DDevice->SetTexture(0, NULL);
	}

	EmoteDevice^ Emote::EmoteInit() {
		IEmoteDevice__TYPE::InitParam initParam;
		ZeroMemory(&initParam, sizeof(initParam));
		initParam.d3dDevice = sD3DDevice;
		IEmoteDevice__TYPE* sDevice = EmoteCreate__TYPE(initParam);
		sEmoteDevice = sDevice;
		device = gcnew EmoteDevice(sDevice);
		EmotePlayers = gcnew Dictionary<String^, EmotePlayer^>();
		return device;
	}
	EmoteDevice^ Emote::EmoteInit(IntPtr dxHandle) {
		IEmoteDevice__TYPE::InitParam initParam;
		ZeroMemory(&initParam, sizeof(initParam));
		void* ptr = dxHandle.ToPointer();
		sD3DDevice = (IDirect3DDevice9*)ptr;
		initParam.d3dDevice = (LPDIRECT3DDEVICE9)ptr;
		IEmoteDevice__TYPE* sDevice = EmoteCreate__TYPE(initParam);
		sEmoteDevice = sDevice;
		device = gcnew EmoteDevice(sDevice);
		EmotePlayers = gcnew Dictionary<String^, EmotePlayer^>();
		return device;
	}


	void Emote::OnDeviceLost()
	{
		if (sCanvasTexture != NULL)
		{
			sCanvasTexture->Release();
			sCanvasTexture = NULL;
		}
		if (sBackBufferSurface != NULL)
		{
			sBackBufferSurface->Release();
			sBackBufferSurface = NULL;
		}
		if (sSurface != NULL)
		{
			sSurface->Release();
			sSurface = NULL;
		}
		device->OnDeviceLost();
	}


	void Emote::OnDeviceReset()
	{
		if (useD3DSurface)
		{
			if (useD3DEx)
			{
				if (sD3DDeviceEx->CreateRenderTarget(sScreenWidth, sScreenHeight, D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, 0, &sBackBufferSurface, 0) < 0)
				{
					return;
				}
				pin_ptr<IDirect3DSurface9*> p1 = &sSurface;
				if (sD3DDevice->CreateOffscreenPlainSurface(sScreenWidth, sScreenHeight, D3DFMT_UNKNOWN, D3DPOOL_SYSTEMMEM, p1, 0) < 0)
				{
					return;
				}
				if (useD3DSurface)
				{
					sD3DDevice->SetRenderTarget(0, sSurface);
				}
			}
			else
			{
				pin_ptr<IDirect3DSurface9*> p1 = &sSurface;
				if (sD3DDevice->CreateRenderTarget(sScreenWidth, sScreenHeight, D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, 1, p1, 0) < 0)
				{
					return;
				}
				sD3DDevice->SetRenderTarget(0, sSurface);
				sD3DDevice->SetRenderState(D3DRS_CULLMODE, 1);
				sD3DDevice->SetRenderState(D3DRS_LIGHTING, 0);
				sD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
			}
		}
		D3DInitRenderState();
	}

	void Emote::RequireCanvasTexture() {
		if (sCanvasTexture == NULL)
		{
			sCanvasTextureWidth = clp(sScreenWidth);
			sCanvasTextureHeight = clp(sScreenWidth);
			pin_ptr<IDirect3DTexture9*> p1 = &sCanvasTexture;
			sD3DDevice->CreateTexture(sCanvasTextureWidth, sCanvasTextureHeight, 1, 1, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, p1, 0);
		}
	}

	void Emote::Show()
	{
		Dictionary<String^, EmotePlayer^>::ValueCollection::Enumerator^ enumerator = EmotePlayers->Values->GetEnumerator();
		if (enumerator->MoveNext())
		{
			do
			{
				EmotePlayer^ current = enumerator->Current;
				if (current != nullptr)
				{
					current->Show();
				}
			} while (enumerator->MoveNext());
		}
	}

	void Emote::Skip()
	{
		Dictionary<String^, EmotePlayer^>::ValueCollection::Enumerator^ enumerator = EmotePlayers->Values->GetEnumerator();
		if (enumerator->MoveNext())
		{
			do
			{
				EmotePlayer^ current = enumerator->Current;
				if (current != nullptr)
				{
					current->Skip();
				}
			} while (enumerator->MoveNext());
		}
	}

	void Emote::Update(float frameCount)
	{
		Dictionary<String^, EmotePlayer^>::ValueCollection::Enumerator^ enumerator = EmotePlayers->Values->GetEnumerator();
		if (enumerator->MoveNext())
		{
			do
			{
				EmotePlayer^ current = enumerator->Current;
				if (current != nullptr)
				{
					current->Progress((float)((double)frameCount * MSTOF60THS));
				}
			} while (enumerator->MoveNext());
		}
	}

	int Emote::D3DCanvasTexture::get()
	{
		int valueType = 0;
		valueType = (int)((void*)sCanvasTexture);
		return valueType;
	}

	void Emote::D3DCanvasTexture::set(int value)
	{
		sCanvasTexture = (IDirect3DTexture9*)((IntPtr)value).ToPointer();
	}

	int Emote::D3Device::get()
	{
		return sD3DeviceHandle;
	}

	void Emote::D3Device::set(int value)
	{
		sD3DeviceHandle = value;
	}

	int Emote::D3DSurface::get()
	{
		if (sSurface != NULL)
		{
			return (int)sSurface;
		}
		if (sD3DDevice != NULL)
		{
			IDirect3DSurface9* result;
			sD3DDevice->GetRenderTarget(0, &result);
			return (int)result;
		}
		return 0;
	}

	EmoteDevice^ Emote::Device::get()
	{
		return device;
	}

	EmotePlayer^ Emote::default::get(String^ name)
	{
		if (EmotePlayers->ContainsKey(name))
		{
			return EmotePlayers[name];
		}
		throw gcnew KeyNotFoundException("Can not find any player named " + name);
	}

	int Emote::SurfaceHeight::get()
	{
		return sScreenHeight;
	}

	int Emote::SurfaceWidth::get()
	{
		return sScreenWidth;
	}

	bool Emote::UseD3DSurface::get()
	{
		return useD3DSurface;
	}
}