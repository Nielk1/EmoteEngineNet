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
		ref class EmotePlayerBase abstract
		{
		public:
			virtual void AddRef() abstract = 0;
			//virtual void AssignState(Adapter::EmotePlayerBase^ another) abstract = 0;
			virtual EmotePlayerBase^ Clone() abstract = 0;
			virtual uint32_t CountDiffTimelines() abstract = 0;
			virtual uint32_t CountMainTimelines() abstract = 0;
			virtual uint32_t CountPlayingTimelines() abstract = 0;
			virtual uint32_t CountVariableFrameAt(uint32_t variableIndex) abstract = 0;
			virtual uint32_t CountVariables() abstract = 0;
			virtual void FadeInTimeline(String^ label, float frameCount, float easing) abstract = 0;
			virtual void FadeOutTimeline(String^ label, float frameCount, float easing) abstract = 0;
			virtual float GetBustScale() abstract = 0;
			virtual uint32_t GetColor() abstract = 0;
			virtual void GetCoord(float &x, float &y) abstract = 0;
			virtual String^ GetDiffTimelineLabelAt(uint32_t index) abstract = 0;
			virtual float GetHairScale() abstract = 0;
			virtual String^ GetMainTimelineLabelAt(uint32_t index) abstract = 0;
			virtual float GetMeshDivisionRatio() abstract = 0;
			virtual float GetPartsScale() abstract = 0;
			virtual uint32_t GetPlayingTimelineFlagsAt(uint32_t index) abstract = 0;
			virtual String^ GetPlayingTimelineLabelAt(uint32_t index) abstract = 0;
			virtual bool GetQueuing() abstract = 0;
			virtual float GetRot() abstract = 0;
			virtual float GetScale() abstract = 0;
			virtual bool GetSmoothing() abstract = 0;
			virtual float GetTimelineBlendRatio(String^ label) abstract = 0;
			virtual float GetVariable(String^ var) abstract = 0;
			virtual String^ GetVariableFrameLabelAt(uint32_t variableIndex, uint32_t frameIndex) abstract = 0;
			virtual float GetVariableFrameValueAt(uint32_t variableIndex, uint32_t frameIndex) abstract = 0;
			virtual String^ GetVariableLabelAt(uint32_t index) abstract = 0;
			virtual void Hide() abstract = 0;
			virtual bool IsAnimating() abstract = 0;
			virtual bool IsHidden() abstract = 0;
			virtual bool IsLoopTimeline(String^ label) abstract = 0;
			virtual bool IsModified() abstract = 0;
			virtual bool IsTimelinePlaying(String^ label) abstract = 0;
			virtual void OffsetCoord(int ofsx, int ofsy) abstract = 0;
			virtual void OffsetRot(float ofstRot) abstract = 0;
			virtual void OffsetScale(float ofstScale) abstract = 0;
			virtual void PlayTimeline(String^ label, TimelinePlayFlags flag) abstract = 0;
			virtual void Progress(float ms) abstract = 0;
			virtual void Release() abstract = 0;
			virtual void Render() abstract = 0;
			virtual void SetBustScale(float scale) abstract = 0;
			virtual void SetColor(uint32_t rgba, float frameCount, float easing) abstract = 0;
			virtual void SetCoord(float x, float y, float frameCount, float easing) abstract = 0;
			virtual void SetHairScale(float scale) abstract = 0;
			virtual void SetMeshDivisionRatio(float ratio) abstract = 0;
			virtual void SetPartsScale(float scale) abstract = 0;
			virtual void SetQueuing(bool state) abstract = 0;
			virtual void SetRot(float rot, float frameCount, float easing) abstract = 0;
			virtual void SetScale(float scale, float frameCount, float easing) abstract = 0;
			virtual void SetSmoothing(bool state) abstract = 0;
			virtual void SetTimelineBlendRatio(String^ label, float value, float frameCount, float easing, bool stopWhenBlendDone) abstract = 0;
			virtual void SetVariable(String^ var, float value, float frameCount, float easing) abstract = 0;
			virtual void SetVariables(IDictionary<String^, float>^ table, float time, float easing) abstract = 0;
			virtual void Show() abstract = 0;
			virtual void Skip() abstract = 0;
			virtual void StartWind(float start, float goal, float speed, float powMin, float powMax) abstract = 0;
			virtual void StopTimeline(String^ label) abstract = 0;
			virtual void StopWind() abstract = 0;
		};

		ref class EmoteDeviceBase abstract
		{
		public:
			virtual emote_uint32_t AddRef(void) abstract = 0;
			virtual emote_uint32_t Release(void) abstract = 0;
			virtual emote_uint32_t RefCount(void) abstract = 0;

			virtual void SetMaskMode(MaskMode maskMode) abstract = 0;
			virtual MaskMode GetMaskMode(void) abstract = 0;

			virtual void SetMaskRegionClipping(bool state) abstract = 0;
			virtual bool GetMaskRegionClipping(void) abstract = 0;

			virtual EmotePlayerBase^ CreatePlayer(emote_image_ptr_t emoteObjectImage, emote_uint32_t emoteObjectSize) abstract = 0;
			virtual EmotePlayerBase^ CreatePlayer(emote_uint32_t emoteObjectNum, const emote_image_ptr_t *emoteObjectImage, const emote_uint32_t *emoteObjectSize) abstract = 0;

			virtual ShaderModel GetAvailableShaderModel(void) abstract = 0;
			virtual void SetShaderModel(ShaderModel model) abstract = 0;
			virtual ShaderModel GetShaderModel(void) abstract = 0;

			virtual void SetMipMapEnabled(bool state) abstract = 0;
			virtual bool GetMipMapEnabled(void) abstract = 0;

			virtual void SetAlphaOp(AlphaOp alphaOp) abstract = 0;
			virtual AlphaOp GetAlphaOp(void) abstract = 0;

			virtual void SetProtectTranslucentTextureColor(bool state) abstract = 0;
			virtual bool GetProtectTranslucentTextureColor(void) abstract = 0;

			virtual void SetPixelateDivision(int division) abstract = 0;
			virtual int GetPixelateDivision(void) abstract = 0;

			virtual void SetMaxTextureSize(emote_uint32_t width, emote_uint32_t height) abstract = 0;

			virtual void OnDeviceLost(void) abstract = 0;
			virtual void OnRenderTarget(LPDIRECT3DTEXTURE9 renderTargetTexture) abstract = 0;
		};

		ref class EmoteDriverBase abstract
		{
		public:
			virtual EmoteDeviceBase^ EmoteCreate(IDirect3DDevice9* sD3DDevice) abstract = 0;
		};
	}
}