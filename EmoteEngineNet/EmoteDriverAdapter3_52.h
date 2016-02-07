#pragma once

#include "iemote.h"
#include "EmoteDriverAdapter.h"
#include "Enums.h"
#include "Core.h"
#include "D3DX9Math.h"
#include <vcclr.h>
#include <msclr\marshal.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace msclr::interop;

namespace EmoteEngineNet {
	namespace Adapter {
		ref class EmotePlayer3_52 : EmotePlayerBase
		{
		private:
			marshal_context^ context;
			const char* StringToCharPtr(String^ str)
			{
				if (!String::IsNullOrWhiteSpace(str) && str->Length <= 50)
				{
					return context->marshal_as<char const *, System::String>(str);
				}
				return (char *)nulString;
			}
		internal:
			EmotePlayer3_52(IEmotePlayer_3_52* player)
			{
				context = gcnew marshal_context();
				sPlayer = player;
			}
			~EmotePlayer3_52()
			{
				if (sPlayer == NULL)
					return;
				sPlayer->Release();
			}
		private:
			IEmotePlayer_3_52* sPlayer;
		public:
			void AddRef() override
			{
				sPlayer->AddRef();
			}

			//void EmotePlayer::AssignState(IEmotePlayer__TYPE* another)
			//void AssignState(Adapter::EmotePlayerBase^ another) override
			//{
			//	sPlayer->AssignState(another->sPlayer);
			//}

			//void AssignState(EmotePlayer^ another)
			//{
			//	sPlayer->AssignState(another->sPlayer->sPlayer);
			//}

			//IEmotePlayer__TYPE* EmotePlayer::Clone()
			EmotePlayerBase^ Clone() override
			{
				return gcnew EmotePlayer3_52(sPlayer->Clone());
			}

			uint32_t CountDiffTimelines() override
			{
				return sPlayer->CountDiffTimelines();
			}

			uint32_t CountMainTimelines() override
			{
				return sPlayer->CountMainTimelines();
			}

			uint32_t CountPlayingTimelines() override
			{
				return sPlayer->CountPlayingTimelines();
			}

			uint32_t CountVariableFrameAt(uint32_t variableIndex) override
			{
				return sPlayer->CountVariableFrameAt(variableIndex);
			}

			uint32_t CountVariables() override
			{
				return sPlayer->CountVariables();
			}

			void FadeInTimeline(String^ label, float frameCount, float easing) override
			{
				sPlayer->FadeInTimeline(StringToCharPtr(label), frameCount, easing);
			}

			void FadeOutTimeline(String^ label, float frameCount, float easing) override
			{
				sPlayer->FadeOutTimeline(StringToCharPtr(label), frameCount, easing);
			}

			float GetBustScale() override
			{
				return sPlayer->GetBustScale();
			}

			uint32_t GetColor() override
			{
				return sPlayer->GetColor();
			}

			void GetCoord(float &x, float &y) override
			{
				float x_ = 0.f;
				float y_ = 0.f;
				sPlayer->GetCoord(x_, y_);
				x = x_;
				y = y_;
			}

			String^ GetDiffTimelineLabelAt(uint32_t index) override
			{
				return gcnew String(sPlayer->GetDiffTimelineLabelAt(index));
			}

			float GetHairScale() override
			{
				return sPlayer->GetHairScale();
			}

			String^ GetMainTimelineLabelAt(uint32_t index) override
			{
				return gcnew String(sPlayer->GetMainTimelineLabelAt(index));
			}

			float GetMeshDivisionRatio() override
			{
				return sPlayer->GetMeshDivisionRatio();
			}

			float GetPartsScale() override
			{
				return sPlayer->GetPartsScale();
			}

			uint32_t GetPlayingTimelineFlagsAt(uint32_t index) override
			{
				return sPlayer->GetPlayingTimelineFlagsAt(index);
			}

			String^ GetPlayingTimelineLabelAt(uint32_t index) override
			{
				return gcnew String(sPlayer->GetPlayingTimelineLabelAt(index));
			}

			bool GetQueuing() override
			{
				return sPlayer->GetQueuing();
			}

			float GetRot() override
			{
				return sPlayer->GetRot();
			}

			float GetScale() override
			{
				return sPlayer->GetScale();
			}

			bool GetSmoothing() override
			{
				return sPlayer->GetSmoothing();
			}

			float GetTimelineBlendRatio(String^ label) override
			{
				return sPlayer->GetTimelineBlendRatio(StringToCharPtr(label));
			}

			float GetVariable(String^ var) override
			{
				return sPlayer->GetVariable(StringToCharPtr(var));
			}

			String^ GetVariableFrameLabelAt(uint32_t variableIndex, uint32_t frameIndex) override
			{
				return gcnew String(sPlayer->GetVariableFrameLabelAt(variableIndex, frameIndex));
			}

			float GetVariableFrameValueAt(uint32_t variableIndex, uint32_t frameIndex) override
			{
				return sPlayer->GetVariableFrameValueAt(variableIndex, frameIndex);
			}

			String^ GetVariableLabelAt(uint32_t index) override
			{
				return gcnew String(sPlayer->GetVariableLabelAt(index));
			}

			void Hide() override
			{
				sPlayer->Hide();
			}

			bool IsAnimating() override
			{
				return sPlayer->IsAnimating();
			}

			bool IsHidden() override
			{
				return sPlayer->IsHidden();
			}

			bool IsLoopTimeline(String^ label) override
			{
				return sPlayer->IsLoopTimeline(StringToCharPtr(label));
			}

			bool IsModified() override
			{
				return sPlayer->IsModified();
			}

			bool IsTimelinePlaying(String^ label) override
			{
				return sPlayer->IsTimelinePlaying(StringToCharPtr(label));
			}

			void OffsetCoord(int ofsx, int ofsy) override
			{
				float x;
				float y;
				sPlayer->GetCoord(x, y);
				sPlayer->SetCoord((float)((double)((float)ofsx) + (double)x), (float)((double)((float)ofsy) + (double)y), 0.f, 0.f);
			}

			void OffsetRot(float ofstRot) override
			{
				float rot = sPlayer->GetRot();
				sPlayer->SetRot((float)((double)rot + (double)ofstRot), 0.f, 0.f);
			}

			void OffsetScale(float ofstScale) override
			{
				float scale = sPlayer->GetScale();
				sPlayer->SetScale((float)((double)scale * (double)ofstScale), 0.f, 0.f);
			}

			void PlayTimeline(String^ label, TimelinePlayFlags flag) override
			{
				sPlayer->PlayTimeline(StringToCharPtr(label), static_cast<emote_uint32_t>(flag));
			}

			void Progress(float ms) override
			{
				sPlayer->Progress(ms);
			}

			void Release() override
			{
				sPlayer->Release();
			}

			void Render() override
			{
				sPlayer->Render();
			}

			void SetBustScale(float scale) override
			{
				sPlayer->SetBustScale(scale);
			}

			void SetColor(uint32_t rgba, float frameCount, float easing) override
			{
				sPlayer->SetColor(rgba, frameCount, easing);
			}

			void SetCoord(float x, float y, float frameCount, float easing) override
			{
				sPlayer->SetCoord(x, y, frameCount, easing);
			}

			void SetHairScale(float scale) override
			{
				sPlayer->SetHairScale(scale);
			}

			void SetMeshDivisionRatio(float ratio) override
			{
				sPlayer->SetMeshDivisionRatio(ratio);
			}

			void SetPartsScale(float scale) override
			{
				sPlayer->SetPartsScale(scale);
			}

			void SetQueuing(bool state) override
			{
				sPlayer->SetQueuing(state);
			}

			void SetRot(float rot, float frameCount, float easing) override
			{
				sPlayer->SetRot(rot, frameCount, easing);
			}

			void SetScale(float scale, float frameCount, float easing) override
			{
				sPlayer->SetScale(scale, frameCount, easing);
			}

			void SetSmoothing(bool state) override
			{
				sPlayer->SetSmoothing(state);
			}

			void SetTimelineBlendRatio(String^ label, float value, float frameCount, float easing, bool stopWhenBlendDone) override
			{
				sPlayer->SetTimelineBlendRatio(StringToCharPtr(label), value, frameCount, easing, stopWhenBlendDone);
			}

			void SetVariable(String^ var, float value, float frameCount, float easing) override
			{
				sPlayer->SetVariable(StringToCharPtr(var), value, frameCount, easing);
			}

			void SetVariables(IDictionary<String^, float>^ table, float time, float easing) override
			{
				for each(KeyValuePair<String^, float> current in table)
				{
					sPlayer->SetVariable(StringToCharPtr(current.Key), current.Value, (float)((double)time * MSTOF60THS), easing);
				}
			}

			void Show() override
			{
				sPlayer->Show();
			}

			void Skip() override
			{
				sPlayer->Skip();
			}

			void StartWind(float start, float goal, float speed, float powMin, float powMax) override
			{
				sPlayer->StartWind(start, goal, speed, powMin, powMax);
			}

			void StopTimeline(String^ label) override
			{
				sPlayer->StopTimeline(StringToCharPtr(label));
			}

			void StopWind() override
			{
				sPlayer->StopWind();
			}
		};

		ref class EmoteDevice3_52 : EmoteDeviceBase
		{
		internal:
			EmoteDevice3_52(IEmoteDevice_3_52* _sEmoteDevice)
			{
				sEmoteDevice = _sEmoteDevice;
			}
			~EmoteDevice3_52()
			{
				if (sEmoteDevice != NULL)
				{
					sEmoteDevice->Release();
				}
			}
		private:
			IEmoteDevice_3_52* sEmoteDevice;

		public:
			emote_uint32_t AddRef(void) override
			{
				return sEmoteDevice->AddRef();
			}
			emote_uint32_t Release(void) override
			{
				return sEmoteDevice->Release();
			}
			emote_uint32_t RefCount(void) override
			{
				return sEmoteDevice->RefCount();
			}

			void SetMaskMode(MaskMode maskMode) override
			{
				sEmoteDevice->SetMaskMode(static_cast<IEmoteDevice_3_52::mask_mode_t>(maskMode));
			}
			MaskMode GetMaskMode(void) override
			{
				return static_cast<MaskMode>(sEmoteDevice->GetMaskMode());
			}

			void SetMaskRegionClipping(bool state) override
			{
				sEmoteDevice->SetMaskRegionClipping(state);
			}
			bool GetMaskRegionClipping(void) override
			{
				return sEmoteDevice->GetMaskRegionClipping();
			}

			//void CreatePlayer(emote_image_ptr_t emoteObjectImage, emote_uint32_t emoteObjectSize, class IEmotePlayer__TYPE **player)
			EmotePlayerBase^ CreatePlayer(emote_image_ptr_t emoteObjectImage, emote_uint32_t emoteObjectSize) override
			{
				IEmotePlayer_3_52 *player;
				sEmoteDevice->CreatePlayer(emoteObjectImage, emoteObjectSize, &player);
				return gcnew EmotePlayer3_52(player);
			}
			//void CreatePlayer(emote_uint32_t emoteObjectNum, const emote_image_ptr_t *emoteObjectImage, const emote_uint32_t *emoteObjectSize, class IEmotePlayer__TYPE **player)
			EmotePlayerBase^ CreatePlayer(emote_uint32_t emoteObjectNum, const emote_image_ptr_t *emoteObjectImage, const emote_uint32_t *emoteObjectSize) override
			{
				IEmotePlayer_3_52 *player;
				sEmoteDevice->CreatePlayer(emoteObjectNum, emoteObjectImage, emoteObjectSize, &player);
				return gcnew EmotePlayer3_52(player);
			}

			ShaderModel GetAvailableShaderModel(void) override
			{
				return static_cast<ShaderModel>(sEmoteDevice->GetAvailableShaderModel());
			}
			void SetShaderModel(ShaderModel model) override
			{
				sEmoteDevice->SetShaderModel(static_cast<IEmoteDevice_3_52::shader_model_t>(model));
			}
			ShaderModel GetShaderModel(void) override
			{
				return static_cast<ShaderModel>(sEmoteDevice->GetShaderModel());
			}

			void SetMipMapEnabled(bool state) override
			{
				sEmoteDevice->SetMipMapEnabled(state);
			}
			bool GetMipMapEnabled(void) override
			{
				return sEmoteDevice->GetMipMapEnabled();
			}

			void SetAlphaOp(AlphaOp alphaOp) override
			{
				sEmoteDevice->SetAlphaOp(static_cast<IEmoteDevice_3_52::alpha_op_t>(alphaOp));
			}
			AlphaOp GetAlphaOp(void) override
			{
				return static_cast<AlphaOp>(sEmoteDevice->GetAlphaOp());
			}

			void SetProtectTranslucentTextureColor(bool state) override
			{
				sEmoteDevice->SetProtectTranslucentTextureColor(state);
			}
			bool GetProtectTranslucentTextureColor(void) override
			{
				return sEmoteDevice->GetProtectTranslucentTextureColor();
			}

			void SetPixelateDivision(int division) override
			{
				sEmoteDevice->SetPixelateDivision(division);
			}
			int GetPixelateDivision(void) override
			{
				return sEmoteDevice->GetPixelateDivision();
			}

			void SetMaxTextureSize(emote_uint32_t width, emote_uint32_t height) override
			{
				sEmoteDevice->SetMaxTextureSize(width, height);
			}

			void OnDeviceLost(void) override
			{
				sEmoteDevice->OnDeviceLost();
			}
			void OnRenderTarget(LPDIRECT3DTEXTURE9 renderTargetTexture) override
			{
				sEmoteDevice->OnRenderTarget(renderTargetTexture);
			}
		};

		ref class EmoteDriver3_52 : EmoteDriverBase
		{
		internal:
			EmoteDriver3_52(String^ EnginePath)
			{
				IntPtr EnginePathPtr = System::Runtime::InteropServices::Marshal::StringToHGlobalUni(EnginePath);
				ptrEmoteCreate = LoadLibraryW((LPCWSTR)EnginePathPtr.ToPointer());
				EmoteCreate_3_52 = (EmoteFactoryFunction_3_52)GetProcAddress(ptrEmoteCreate, (LPCSTR)("?EmoteCreate@@YAPAVIEmoteDevice@@ABUInitParam@1@@Z"));
			}
			~EmoteDriver3_52()
			{
				if (ptrEmoteCreate != NULL)
				{
					::FreeLibrary(ptrEmoteCreate);
				}
			}

		public:
			EmoteDeviceBase^ EmoteCreate(IDirect3DDevice9* sD3DDevice) override
			{
				IEmoteDevice_3_52::InitParam initParam;
				ZeroMemory(&initParam, sizeof(initParam));
				initParam.d3dDevice = sD3DDevice;

				IEmoteDevice_3_52* sEmoteDevice = EmoteCreate_3_52(initParam);
				return gcnew EmoteDevice3_52(sEmoteDevice);
			}
		private:
			EmoteFactoryFunction_3_52 EmoteCreate_3_52;
			HINSTANCE__* ptrEmoteCreate;
		};
	}
}