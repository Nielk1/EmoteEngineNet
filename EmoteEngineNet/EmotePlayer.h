#pragma once
#include "Lock.h"
#include "iemote.h"
#include "EmoteDriverAdapter.h"
#include "Emote.h"
#include "EmoteDevice.h"
#include "Enums.h"
#include <vcclr.h>
#include <msclr\marshal.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace msclr::interop;

namespace EmoteEngineNet {
	//static const float MSTOF60THS = 60.0f / 1000.0f;
	//static const float F60THSTOMS = 1000.0f / 60.0f;


	public ref class EmotePlayer
	{
	internal:
		//EmotePlayer(IEmotePlayer__TYPE* player);
		EmotePlayer(Adapter::EmotePlayerBase^ player);
		//IEmotePlayer__TYPE* Clone();
		Adapter::EmotePlayerBase^ Clone();
	private:
		~EmotePlayer();
	public:
		void AddRef();
		//void AssignState(EmotePlayer another);
		uint32_t CountDiffTimelines();
		uint32_t CountMainTimelines();
		uint32_t CountPlayingTimelines();
		uint32_t CountVariableFrameAt(uint32_t variableIndex);
		uint32_t CountVariables();
		void FadeInTimeline(String^ label, float frameCount, float easing);
		void FadeOutTimeline(String^ label, float frameCount, float easing);
		float GetBustScale();
		uint32_t GetColor();
		void GetCoord(float &x, float &y);
		String^ GetDiffTimelineLabelAt(uint32_t index);
		float GetHairScale();
		String^ GetMainTimelineLabelAt(uint32_t index);
		float GetMeshDivisionRatio();
		float GetPartsScale();
		uint32_t GetPlayingTimelineFlagsAt(uint32_t index);
		String^ GetPlayingTimelineLabelAt(uint32_t index);
		bool GetQueuing();
		float GetRot();
		float GetScale();
		bool GetSmoothing();
		float GetTimelineBlendRatio(String^ label);
		float GetVariable(String^ var);
		String^ GetVariableFrameLabelAt(uint32_t variableIndex, uint32_t frameIndex);
		float GetVariableFrameValueAt(uint32_t variableIndex, uint32_t frameIndex);
		String^ GetVariableLabelAt(uint32_t index);
		void Hide();
		bool IsAnimating();
		bool IsHidden();
		bool IsLoopTimeline(String^ label);
		bool IsModified();
		bool IsTimelinePlaying(String^ label);
		void OffsetCoord(int ofsx, int ofsy);
		void OffsetRot(float ofstRot);
		void OffsetScale(float ofstScale);
		void PlayTimeline(String^ label, TimelinePlayFlags flag);
		void Progress(float ms);
		void Release();
		void Render();
		void SetBustScale(float scale);
		void SetColor(uint32_t rgba, float frameCount, float easing);
		void SetCoord(float x, float y, float frameCount, float easing);
		void SetHairScale(float scale);
		void SetMeshDivisionRatio(float ratio);
		void SetPartsScale(float scale);
		void SetQueuing(bool state);
		void SetRot(float rot, float frameCount, float easing);
		void SetScale(float scale, float frameCount, float easing);
		void SetSmoothing(bool state);
		void SetTimelineBlendRatio(String^ label, float value, float frameCount, float easing, bool stopWhenBlendDone);
		void SetVariable(String^ var, float value, float frameCount, float easing);
		void SetVariables(IDictionary<String^, float>^ table, float time, float easing);
		void Show();
		void Skip();
		void StartWind(float start, float goal, float speed, float powMin, float powMax);
		void StopTimeline(String^ label);
		void StopWind();

	internal:
		////void AssignState(IEmotePlayer__TYPE* another);
		//void AssignState(Adapter::EmotePlayerBase^ another);

	internal:
		//property IEmotePlayer__TYPE* NativePlayer
		//{
		//	IEmotePlayer__TYPE* get();
		//}

	private:
		//const char* StringToCharPtr(String^ str);
		//marshal_context^ context;
		int sMouthIndex;
		//IEmotePlayer__TYPE* sPlayer;
		Adapter::EmotePlayerBase^ sPlayer;
		int sPoseIndex;
	};
}