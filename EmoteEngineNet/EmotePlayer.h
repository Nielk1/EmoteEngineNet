#pragma once
#include "Lock.h"
#include "iemote.h"
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
	static const float MSTOF60THS = 60.0f / 1000.0f;
	static const float F60THSTOMS = 1000.0f / 60.0f;


	public ref class EmotePlayer
	{
	internal:
		EmotePlayer(IEmotePlayer__TYPE* player);
		IEmotePlayer__TYPE* Clone();
	private:
		~EmotePlayer();
	public:
		void AddRef();
		void AssignState(EmotePlayer another);
		UInt32 CountDiffTimelines();
		UInt32 CountMainTimelines();
		UInt32 CountPlayingTimelines();
		UInt32 CountVariableFrameAt(UInt32 variableIndex);
		UInt32 CountVariables();
		void FadeInTimeline(String^ label, float frameCount, float easing);
		void FadeOutTimeline(String^ label, float frameCount, float easing);
		float GetBustScale();
		UInt32 GetColor();
		void GetCoord(float &x, float &y);
		String^ GetDiffTimelineLabelAt(UInt32 index);
		float GetHairScale();
		String^ GetMainTimelineLabelAt(UInt32 index);
		float GetMeshDivisionRatio();
		float GetPartsScale();
		UInt32 GetPlayingTimelineFlagsAt(UInt32 index);
		String^ GetPlayingTimelineLabelAt(UInt32 index);
		bool GetQueuing();
		float GetRot();
		float GetScale();
		bool GetSmoothing();
		float GetTimelineBlendRatio(String^ label);
		float GetVariable(String^ var);
		String^ GetVariableFrameLabelAt(UInt32 variableIndex, UInt32 frameIndex);
		float GetVariableFrameValueAt(UInt32 variableIndex, UInt32 frameIndex);
		String^ GetVariableLabelAt(UInt32 index);
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
		void SetColor(UInt32 rgba, float frameCount, float easing);
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
		void AssignState(IEmotePlayer__TYPE* another);

	internal:
		property IEmotePlayer__TYPE* NativePlayer
		{
			IEmotePlayer__TYPE* get();
		}

	private:
		const char* StringToCharPtr(String^ str);
		marshal_context^ context;
		int sMouthIndex;
		IEmotePlayer__TYPE* sPlayer;
		int sPoseIndex;
	};
}