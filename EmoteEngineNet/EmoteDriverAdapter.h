#pragma once

#include "iemote.h"
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
		ref class EmotePlayerBase
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
			EmotePlayerBase(IEmotePlayer__TYPE* player)
			{
				context = gcnew marshal_context();
				sPlayer = player;
			}
			~EmotePlayerBase()
			{
				if (sPlayer == NULL)
					return;
				sPlayer->Release();
			}
		private:
			IEmotePlayer__TYPE* sPlayer;
		public:
			void AddRef()
			{
				sPlayer->AddRef();
			}

			//void EmotePlayer::AssignState(IEmotePlayer__TYPE* another)
			void AssignState(Adapter::EmotePlayerBase^ another)
			{
				sPlayer->AssignState(another->sPlayer);
			}

			//void AssignState(EmotePlayer^ another)
			//{
			//	sPlayer->AssignState(another->sPlayer->sPlayer);
			//}

			//IEmotePlayer__TYPE* EmotePlayer::Clone()
			EmotePlayerBase^ Clone()
			{
				return gcnew EmotePlayerBase(sPlayer->Clone());
			}

			uint32_t CountDiffTimelines()
			{
				return sPlayer->CountDiffTimelines();
			}

			uint32_t CountMainTimelines()
			{
				return sPlayer->CountMainTimelines();
			}

			uint32_t CountPlayingTimelines()
			{
				return sPlayer->CountPlayingTimelines();
			}

			uint32_t CountVariableFrameAt(uint32_t variableIndex)
			{
				return sPlayer->CountVariableFrameAt(variableIndex);
			}

			uint32_t CountVariables()
			{
				return sPlayer->CountVariables();
			}

			void FadeInTimeline(String^ label, float frameCount, float easing)
			{
				sPlayer->FadeInTimeline(StringToCharPtr(label), frameCount, easing);
			}

			void FadeOutTimeline(String^ label, float frameCount, float easing)
			{
				sPlayer->FadeOutTimeline(StringToCharPtr(label), frameCount, easing);
			}

			float GetBustScale()
			{
				return sPlayer->GetBustScale();
			}

			uint32_t GetColor()
			{
				return sPlayer->GetColor();
			}

			void GetCoord(float &x, float &y)
			{
				float x_ = 0.f;
				float y_ = 0.f;
				sPlayer->GetCoord(x_, y_);
				x = x_;
				y = y_;
			}

			String^ GetDiffTimelineLabelAt(uint32_t index)
			{
				return gcnew String(sPlayer->GetDiffTimelineLabelAt(index));
			}

			float GetHairScale()
			{
				return sPlayer->GetHairScale();
			}

			String^ GetMainTimelineLabelAt(uint32_t index)
			{
				return gcnew String(sPlayer->GetMainTimelineLabelAt(index));
			}

			float GetMeshDivisionRatio()
			{
				return sPlayer->GetMeshDivisionRatio();
			}

			float GetPartsScale()
			{
				return sPlayer->GetPartsScale();
			}

			uint32_t GetPlayingTimelineFlagsAt(uint32_t index)
			{
				return sPlayer->GetPlayingTimelineFlagsAt(index);
			}

			String^ GetPlayingTimelineLabelAt(uint32_t index)
			{
				return gcnew String(sPlayer->GetPlayingTimelineLabelAt(index));
			}

			bool GetQueuing()
			{
				return sPlayer->GetQueuing();
			}

			float GetRot()
			{
				return sPlayer->GetRot();
			}

			float GetScale()
			{
				return sPlayer->GetScale();
			}

			bool GetSmoothing()
			{
				return sPlayer->GetSmoothing();
			}

			float GetTimelineBlendRatio(String^ label)
			{
				return sPlayer->GetTimelineBlendRatio(StringToCharPtr(label));
			}

			float GetVariable(String^ var)
			{
				return sPlayer->GetVariable(StringToCharPtr(var));
			}

			String^ GetVariableFrameLabelAt(uint32_t variableIndex, uint32_t frameIndex)
			{
				return gcnew String(sPlayer->GetVariableFrameLabelAt(variableIndex, frameIndex));
			}

			float GetVariableFrameValueAt(uint32_t variableIndex, uint32_t frameIndex)
			{
				return sPlayer->GetVariableFrameValueAt(variableIndex, frameIndex);
			}

			String^ GetVariableLabelAt(uint32_t index)
			{
				return gcnew String(sPlayer->GetVariableLabelAt(index));
			}

			void Hide()
			{
				sPlayer->Hide();
			}

			bool IsAnimating()
			{
				return sPlayer->IsAnimating();
			}

			bool IsHidden()
			{
				return sPlayer->IsHidden();
			}

			bool IsLoopTimeline(String^ label)
			{
				return sPlayer->IsLoopTimeline(StringToCharPtr(label));
			}

			bool IsModified()
			{
				return sPlayer->IsModified();
			}

			bool IsTimelinePlaying(String^ label)
			{
				return sPlayer->IsTimelinePlaying(StringToCharPtr(label));
			}

			void OffsetCoord(int ofsx, int ofsy)
			{
				float x;
				float y;
				sPlayer->GetCoord(x, y);
				sPlayer->SetCoord((float)((double)((float)ofsx) + (double)x), (float)((double)((float)ofsy) + (double)y), 0.f, 0.f);
			}

			void OffsetRot(float ofstRot)
			{
				float rot = sPlayer->GetRot();
				sPlayer->SetRot((float)((double)rot + (double)ofstRot), 0.f, 0.f);
			}

			void OffsetScale(float ofstScale)
			{
				float scale = sPlayer->GetScale();
				sPlayer->SetScale((float)((double)scale * (double)ofstScale), 0.f, 0.f);
			}

			void PlayTimeline(String^ label, TimelinePlayFlags flag)
			{
				sPlayer->PlayTimeline(StringToCharPtr(label), static_cast<emote_uint32_t>(flag));
			}

			void Progress(float ms)
			{
				sPlayer->Progress(ms);
			}

			void Release()
			{
				sPlayer->Release();
			}

			void Render()
			{
				sPlayer->Render();
			}

			void SetBustScale(float scale)
			{
				sPlayer->SetBustScale(scale);
			}

			void SetColor(uint32_t rgba, float frameCount, float easing)
			{
				sPlayer->SetColor(rgba, frameCount, easing);
			}

			void SetCoord(float x, float y, float frameCount, float easing)
			{
				sPlayer->SetCoord(x, y, frameCount, easing);
			}

			void SetHairScale(float scale)
			{
				sPlayer->SetHairScale(scale);
			}

			void SetMeshDivisionRatio(float ratio)
			{
				sPlayer->SetMeshDivisionRatio(ratio);
			}

			void SetPartsScale(float scale)
			{
				sPlayer->SetPartsScale(scale);
			}

			void SetQueuing(bool state)
			{
				sPlayer->SetQueuing(state);
			}

			void SetRot(float rot, float frameCount, float easing)
			{
				sPlayer->SetRot(rot, frameCount, easing);
			}

			void SetScale(float scale, float frameCount, float easing)
			{
				sPlayer->SetScale(scale, frameCount, easing);
			}

			void SetSmoothing(bool state)
			{
				sPlayer->SetSmoothing(state);
			}

			void SetTimelineBlendRatio(String^ label, float value, float frameCount, float easing, bool stopWhenBlendDone)
			{
				sPlayer->SetTimelineBlendRatio(StringToCharPtr(label), value, frameCount, easing, stopWhenBlendDone);
			}

			void SetVariable(String^ var, float value, float frameCount, float easing)
			{
				sPlayer->SetVariable(StringToCharPtr(var), value, frameCount, easing);
			}

			void SetVariables(IDictionary<String^, float>^ table, float time, float easing)
			{
				for each(KeyValuePair<String^, float> current in table)
				{
					sPlayer->SetVariable(StringToCharPtr(current.Key), current.Value, (float)((double)time * MSTOF60THS), easing);
				}
			}

			void Show()
			{
				sPlayer->Show();
			}

			void Skip()
			{
				sPlayer->Skip();
			}

			void StartWind(float start, float goal, float speed, float powMin, float powMax)
			{
				sPlayer->StartWind(start, goal, speed, powMin, powMax);
			}

			void StopTimeline(String^ label)
			{
				sPlayer->StopTimeline(StringToCharPtr(label));
			}

			void StopWind()
			{
				sPlayer->StopWind();
			}
		};

		ref class EmoteDeviceBase
		{
		internal:
			EmoteDeviceBase(IEmoteDevice__TYPE* _sEmoteDevice)
			{
				sEmoteDevice = _sEmoteDevice;
			}
			~EmoteDeviceBase()
			{
				if (sEmoteDevice != NULL)
				{
					sEmoteDevice->Release();
				}
			}
		private:
			IEmoteDevice__TYPE* sEmoteDevice;

		public:
			emote_uint32_t AddRef(void)
			{
				return sEmoteDevice->AddRef();
			}
			emote_uint32_t Release(void)
			{
				return sEmoteDevice->Release();
			}
			emote_uint32_t RefCount(void)
			{
				return sEmoteDevice->RefCount();
			}

			void SetMaskMode(MaskMode maskMode)
			{
				sEmoteDevice->SetMaskMode(static_cast<IEmoteDevice__TYPE::mask_mode_t>(maskMode));
			}
			MaskMode GetMaskMode(void)
			{
				return static_cast<MaskMode>(sEmoteDevice->GetMaskMode());
			}

			void SetMaskRegionClipping(bool state)
			{
				sEmoteDevice->SetMaskRegionClipping(state);
			}
			bool GetMaskRegionClipping(void)
			{
				return sEmoteDevice->GetMaskRegionClipping();
			}

			//void CreatePlayer(emote_image_ptr_t emoteObjectImage, emote_uint32_t emoteObjectSize, class IEmotePlayer__TYPE **player)
			EmotePlayerBase^ CreatePlayer(emote_image_ptr_t emoteObjectImage, emote_uint32_t emoteObjectSize)
			{
				IEmotePlayer__TYPE *player;
				sEmoteDevice->CreatePlayer(emoteObjectImage, emoteObjectSize, &player);
				return gcnew EmotePlayerBase(player);
			}
			//void CreatePlayer(emote_uint32_t emoteObjectNum, const emote_image_ptr_t *emoteObjectImage, const emote_uint32_t *emoteObjectSize, class IEmotePlayer__TYPE **player)
			EmotePlayerBase^ CreatePlayer(emote_uint32_t emoteObjectNum, const emote_image_ptr_t *emoteObjectImage, const emote_uint32_t *emoteObjectSize)
			{
				IEmotePlayer__TYPE *player;
				sEmoteDevice->CreatePlayer(emoteObjectNum, emoteObjectImage, emoteObjectSize, &player);
				return gcnew EmotePlayerBase(player);
			}

			ShaderModel GetAvailableShaderModel(void)
			{
				return static_cast<ShaderModel>(sEmoteDevice->GetAvailableShaderModel());
			}
			void SetShaderModel(ShaderModel model)
			{
				sEmoteDevice->SetShaderModel(static_cast<IEmoteDevice__TYPE::shader_model_t>(model));
			}
			ShaderModel GetShaderModel(void)
			{
				return static_cast<ShaderModel>(sEmoteDevice->GetShaderModel());
			}

			void SetMipMapEnabled(bool state)
			{
				sEmoteDevice->SetMipMapEnabled(state);
			}
			bool GetMipMapEnabled(void)
			{
				return sEmoteDevice->GetMipMapEnabled();
			}

			void SetAlphaOp(AlphaOp alphaOp)
			{
				sEmoteDevice->SetAlphaOp(static_cast<IEmoteDevice__TYPE::alpha_op_t>(alphaOp));
			}
			AlphaOp GetAlphaOp(void)
			{
				return static_cast<AlphaOp>(sEmoteDevice->GetAlphaOp());
			}

			void SetProtectTranslucentTextureColor(bool state)
			{
				sEmoteDevice->SetProtectTranslucentTextureColor(state);
			}
			bool GetProtectTranslucentTextureColor(void)
			{
				return sEmoteDevice->GetProtectTranslucentTextureColor();
			}

			void SetPixelateDivision(int division)
			{
				sEmoteDevice->SetPixelateDivision(division);
			}
			int GetPixelateDivision(void)
			{
				return sEmoteDevice->GetPixelateDivision();
			}

			void SetMaxTextureSize(emote_uint32_t width, emote_uint32_t height)
			{
				sEmoteDevice->SetMaxTextureSize(width, height);
			}

			void OnDeviceLost(void)
			{
				sEmoteDevice->OnDeviceLost();
			}
			void OnRenderTarget(LPDIRECT3DTEXTURE9 renderTargetTexture)
			{
				sEmoteDevice->OnRenderTarget(renderTargetTexture);
			}
		};

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
			EmoteDeviceBase^ EmoteCreate(IDirect3DDevice9* sD3DDevice)
			{
				IEmoteDevice__TYPE::InitParam initParam;
				ZeroMemory(&initParam, sizeof(initParam));
				initParam.d3dDevice = sD3DDevice;

				IEmoteDevice__TYPE* sEmoteDevice = EmoteCreate__TYPE(initParam);
				return gcnew EmoteDeviceBase(sEmoteDevice);
			}
		private:
			EmoteFactoryFunction__TYPE EmoteCreate__TYPE;
			HINSTANCE__* ptrEmoteCreate;
		};
	}
}