#include "stdafx.h"

#include "EmoteDevice.h"
#include <assert.h>
namespace EmoteEngineNet {

	EmoteDevice::EmoteDevice(::IEmoteDevice__TYPE* sDevice, Emote^ _emote)
	{
		device = sDevice;
		backing_store__UseTextureFilter = false;

		emote = _emote;
	}

	uint32_t EmoteDevice::AddRef() {
		return device->AddRef();
	}

	EmotePlayer^ EmoteDevice::CreatePlayer(String^ path)
	{
		if (!File::Exists(path))
		{
			throw gcnew FileNotFoundException("File not exist.");
		}
		IntPtr ptr = System::Runtime::InteropServices::Marshal::StringToHGlobalUni(path);
		HANDLE hFile = CreateFileW((LPCWSTR)ptr.ToPointer(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD fileSize = GetFileSize(hFile, NULL);
		//OM's improvement to this cluster fuck: std::vector<uint8> ptr3(fileStart, fileEnd);
		//Or just std::vector<uint8> ptr3; ptr3.resize(fileSize); inline
		//Or rather std::vector<uint8> ptr3(fileSize); // In modern versions
		BYTE* buf = new BYTE[fileSize];
		DWORD bytesRead;
		ReadFile(hFile, buf, fileSize, &bytesRead, NULL);
		CloseHandle(hFile);
		if (backing_store__UseTextureFilter && backing_store__TextureFilter != nullptr)
		{
			emote->EmoteFilterTexture(buf, fileSize, (FP_EMOTE_FILTER_FUNC)(Marshal::GetFunctionPointerForDelegate(backing_store__TextureFilter).ToPointer()));
		}
		IEmotePlayer__TYPE* player;
		device->CreatePlayer(buf, fileSize, &player);
		EmotePlayer^ returnPlayer = gcnew EmotePlayer(player);
		delete buf;
		return returnPlayer;
	}

	EmotePlayer^ EmoteDevice::CreatePlayer(Stream^ stream)
	{
		DWORD fileSize = stream->Length;
		//Console::WriteLine(stream->Length);
		BYTE* buf = new BYTE[fileSize];

		CopyStreamToNativePtr(stream, buf);

		if (backing_store__UseTextureFilter && backing_store__TextureFilter != nullptr)
		{
			emote->EmoteFilterTexture(buf, fileSize, (FP_EMOTE_FILTER_FUNC)(Marshal::GetFunctionPointerForDelegate(backing_store__TextureFilter).ToPointer()));
		}
		IEmotePlayer__TYPE* player;
		device->CreatePlayer(buf, fileSize, &player);
		EmotePlayer^ returnPlayer = gcnew EmotePlayer(player);
		delete buf;
		return returnPlayer;
	}

	void EmoteDevice::CopyStreamToNativePtr(Stream^ src, unsigned char* dst)
	{
		// Assuming we want to start the copy at the beginning of src
		src->Seek(0, SeekOrigin::Begin);

		// Create an UnmanagedMemoryStream on top of the destination
		// with an appropriate size and capacity (We assume the buffer is
		// is sized to the source data in this function!)
		UnmanagedMemoryStream target(dst, src->Length, src->Length, FileAccess::Write);

		// Copy to your heart's content!
		src->CopyTo(%target);

		// We made the UnmanagedMemoryStream local so that we wouldn't have
		// to explicitly Dispose() of it.
	}

	AlphaOp EmoteDevice::GetAlphaOp()
	{
		return static_cast<AlphaOp>(device->GetAlphaOp());
	}

	MaskMode EmoteDevice::GetMaskMode()
	{
		return static_cast<MaskMode>(device->GetMaskMode());
	}

	bool EmoteDevice::GetMaskRegionClipping()
	{
		return device->GetMaskRegionClipping();
	}

	bool EmoteDevice::GetMipMapEnabled()
	{
		return device->GetMipMapEnabled();
	}

	int EmoteDevice::GetPixelateDivision()
	{
		return device->GetPixelateDivision();
	}

	bool EmoteDevice::GetProtectTranslucentTextureColor()
	{
		return device->GetProtectTranslucentTextureColor();
	}

	ShaderModel EmoteDevice::GetShaderModel()
	{
		return static_cast<ShaderModel>(device->GetShaderModel());
	}

	void EmoteDevice::OnDeviceLost()
	{
		device->OnDeviceLost();
	}

	void EmoteDevice::OnRenderTarget(IDirect3DTexture9* renderTargetTexture)
	{
		device->OnRenderTarget(renderTargetTexture);
	}

	void EmoteDevice::OnRenderTarget(IntPtr renderTargetTexture)
	{
		device->OnRenderTarget((LPDIRECT3DTEXTURE9)(renderTargetTexture.ToPointer()));
	}

	void EmoteDevice::Release()
	{
		device->Release();
	}

	void EmoteDevice::SetAlphaOp(AlphaOp op)
	{
		device->SetAlphaOp(static_cast<IEmoteDevice__TYPE::alpha_op_t>(op));
	}

	void EmoteDevice::SetMaskMode(MaskMode mask)
	{
		device->SetMaskMode(static_cast<IEmoteDevice__TYPE::mask_mode_t>(mask));
	}

	void EmoteDevice::SetMaskRegionClipping(bool state)
	{
		device->SetMaskRegionClipping(state);
	}

	void EmoteDevice::SetMaxTextureSize(uint32_t width, uint32_t height)
	{
		device->SetMaxTextureSize(width, height);
	}

	void EmoteDevice::SetMipMapEnabled(bool state)
	{
		device->SetMipMapEnabled(state);
	}

	void EmoteDevice::SetPixelateDivision(int division)
	{
		device->SetPixelateDivision(division);
	}

	void EmoteDevice::SetProtectTranslucentTextureColor(bool state)
	{
		device->SetProtectTranslucentTextureColor(state);
	}

	void EmoteDevice::SetShaderModel(ShaderModel shaderModel)
	{
		device->SetShaderModel(static_cast<IEmoteDevice__TYPE::shader_model_t>(shaderModel));
	}

	EmoteDevice::~EmoteDevice()
	{
		if (device != NULL)
		{
			device->Release();
		}
	}

	IEmoteDevice__TYPE* EmoteDevice::NativeDevice::get() {
		return device;
	}

	TextureFilterFunction^ EmoteDevice::TextureFilter::get()
	{
		return backing_store__TextureFilter;
	}

	void EmoteDevice::TextureFilter::set(TextureFilterFunction^ value)
	{
		backing_store__TextureFilter = value;
	}

	bool EmoteDevice::UseTextureFilter::get() {
		return backing_store__UseTextureFilter;
	}

	void EmoteDevice::UseTextureFilter::set(bool value)
	{
		backing_store__UseTextureFilter = value;
	}
}