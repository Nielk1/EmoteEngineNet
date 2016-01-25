#include "stdafx.h"
#include "EmotePlayer.h"

namespace EmoteEngineNet {
	EmotePlayer::EmotePlayer(IEmotePlayer__TYPE* player)
	{
		context = gcnew marshal_context();
		sPlayer = player;
	}

	void EmotePlayer::AddRef()
	{
		sPlayer->AddRef();
	}

	void EmotePlayer::AssignState(IEmotePlayer__TYPE* another)
	{
		sPlayer->AssignState(another);
	}

	void EmotePlayer::AssignState(EmotePlayer another)
	{
		sPlayer->AssignState(another.sPlayer);
	}

	IEmotePlayer__TYPE* EmotePlayer::Clone()
	{
		return sPlayer->Clone();
	}

	uint32_t EmotePlayer::CountDiffTimelines()
	{
		return sPlayer->CountDiffTimelines();
	}

	uint32_t EmotePlayer::CountMainTimelines()
	{
		return sPlayer->CountMainTimelines();
	}

	uint32_t EmotePlayer::CountPlayingTimelines()
	{
		return sPlayer->CountPlayingTimelines();
	}

	uint32_t EmotePlayer::CountVariableFrameAt(uint32_t variableIndex)
	{
		return sPlayer->CountVariableFrameAt(variableIndex);
	}

	uint32_t EmotePlayer::CountVariables()
	{
		return sPlayer->CountVariables();
	}

	void EmotePlayer::FadeInTimeline(String^ label, float frameCount, float easing)
	{
		sPlayer->FadeInTimeline(StringToCharPtr(label), frameCount, easing);
	}

	void EmotePlayer::FadeOutTimeline(String^ label, float frameCount, float easing)
	{
		sPlayer->FadeOutTimeline(StringToCharPtr(label), frameCount, easing);
	}

	float EmotePlayer::GetBustScale()
	{
		return sPlayer->GetBustScale();
	}

	uint32_t EmotePlayer::GetColor()
	{
		return sPlayer->GetColor();
	}

	void EmotePlayer::GetCoord(float &x, float &y)
	{
		float x_ = 0.f;
		float y_ = 0.f;
		sPlayer->GetCoord(x_, y_);
		x = x_;
		y = y_;
	}

	String^ EmotePlayer::GetDiffTimelineLabelAt(uint32_t index)
	{
		return gcnew String(sPlayer->GetDiffTimelineLabelAt(index));
	}

	float EmotePlayer::GetHairScale()
	{
		return sPlayer->GetHairScale();
	}

	String^ EmotePlayer::GetMainTimelineLabelAt(uint32_t index)
	{
		return gcnew String(sPlayer->GetMainTimelineLabelAt(index));
	}

	float EmotePlayer::GetMeshDivisionRatio()
	{
		return sPlayer->GetMeshDivisionRatio();
	}

	float EmotePlayer::GetPartsScale()
	{
		return sPlayer->GetPartsScale();
	}

	uint32_t EmotePlayer::GetPlayingTimelineFlagsAt(uint32_t index)
	{
		return sPlayer->GetPlayingTimelineFlagsAt(index);
	}

	String^ EmotePlayer::GetPlayingTimelineLabelAt(uint32_t index)
	{
		return gcnew String(sPlayer->GetPlayingTimelineLabelAt(index));
	}

	bool EmotePlayer::GetQueuing()
	{
		return sPlayer->GetQueuing();
	}

	float EmotePlayer::GetRot()
	{
		return sPlayer->GetRot();
	}

	float EmotePlayer::GetScale()
	{
		return sPlayer->GetScale();
	}

	bool EmotePlayer::GetSmoothing()
	{
		return sPlayer->GetSmoothing();
	}

	float EmotePlayer::GetTimelineBlendRatio(String^ label)
	{
		return sPlayer->GetTimelineBlendRatio(StringToCharPtr(label));
	}

	float EmotePlayer::GetVariable(String^ var)
	{
		return sPlayer->GetVariable(StringToCharPtr(var));
	}

	String^ EmotePlayer::GetVariableFrameLabelAt(uint32_t variableIndex, uint32_t frameIndex)
	{
		return gcnew String(sPlayer->GetVariableFrameLabelAt(variableIndex, frameIndex));
	}

	float EmotePlayer::GetVariableFrameValueAt(uint32_t variableIndex, uint32_t frameIndex)
	{
		return sPlayer->GetVariableFrameValueAt(variableIndex, frameIndex);
	}

	String^ EmotePlayer::GetVariableLabelAt(uint32_t index)
	{
		return gcnew String(sPlayer->GetVariableLabelAt(index));
	}

	void EmotePlayer::Hide()
	{
		sPlayer->Hide();
	}

	bool EmotePlayer::IsAnimating()
	{
		return sPlayer->IsAnimating();
	}

	bool EmotePlayer::IsHidden()
	{
		return sPlayer->IsHidden();
	}

	bool EmotePlayer::IsLoopTimeline(String^ label)
	{
		return sPlayer->IsLoopTimeline(StringToCharPtr(label));
	}

	bool EmotePlayer::IsModified()
	{
		return sPlayer->IsModified();
	}

	bool EmotePlayer::IsTimelinePlaying(String^ label)
	{
		return sPlayer->IsTimelinePlaying(StringToCharPtr(label));
	}

	void EmotePlayer::OffsetCoord(int ofsx, int ofsy)
	{
		float x;
		float y;
		sPlayer->GetCoord(x, y);
		sPlayer->SetCoord((float)((double)((float)ofsx) + (double)x), (float)((double)((float)ofsy) + (double)y), 0.f, 0.f);
	}

	void EmotePlayer::OffsetRot(float ofstRot)
	{
		float rot = sPlayer->GetRot();
		sPlayer->SetRot((float)((double)rot + (double)ofstRot), 0.f, 0.f);
	}

	void EmotePlayer::OffsetScale(float ofstScale)
	{
		float scale = sPlayer->GetScale();
		sPlayer->SetScale((float)((double)scale * (double)ofstScale), 0.f, 0.f);
	}

	void EmotePlayer::PlayTimeline(String^ label, TimelinePlayFlags flag)
	{
		sPlayer->PlayTimeline(StringToCharPtr(label), static_cast<emote_uint32_t>(flag));
	}

	void EmotePlayer::Progress(float ms)
	{
		sPlayer->Progress(ms);
	}

	void EmotePlayer::Release()
	{
		sPlayer->Release();
	}

	void EmotePlayer::Render()
	{
		sPlayer->Render();
	}

	void EmotePlayer::SetBustScale(float scale)
	{
		sPlayer->SetBustScale(scale);
	}

	void EmotePlayer::SetColor(uint32_t rgba, float frameCount, float easing)
	{
		sPlayer->SetColor(rgba, frameCount, easing);
	}

	void EmotePlayer::SetCoord(float x, float y, float frameCount, float easing)
	{
		sPlayer->SetCoord(x, y, frameCount, easing);
	}

	void EmotePlayer::SetHairScale(float scale)
	{
		sPlayer->SetHairScale(scale);
	}

	void EmotePlayer::SetMeshDivisionRatio(float ratio)
	{
		sPlayer->SetMeshDivisionRatio(ratio);
	}

	void EmotePlayer::SetPartsScale(float scale)
	{
		sPlayer->SetPartsScale(scale);
	}

	void EmotePlayer::SetQueuing(bool state)
	{
		sPlayer->SetQueuing(state);
	}

	void EmotePlayer::SetRot(float rot, float frameCount, float easing)
	{
		sPlayer->SetRot(rot, frameCount, easing);
	}

	void EmotePlayer::SetScale(float scale, float frameCount, float easing)
	{
		sPlayer->SetScale(scale, frameCount, easing);
	}

	void EmotePlayer::SetSmoothing(bool state)
	{
		sPlayer->SetSmoothing(state);
	}

	void EmotePlayer::SetTimelineBlendRatio(String^ label, float value, float frameCount, float easing, bool stopWhenBlendDone)
	{
		sPlayer->SetTimelineBlendRatio(StringToCharPtr(label), value, frameCount, easing, stopWhenBlendDone);
	}

	void EmotePlayer::SetVariable(String^ var, float value, float frameCount, float easing)
	{
		sPlayer->SetVariable(StringToCharPtr(var), value, frameCount, easing);
	}

	void EmotePlayer::SetVariables(IDictionary<String^, float>^ table, float time, float easing)
	{
		for each(KeyValuePair<String^, float> current in table)
		{
			sPlayer->SetVariable(StringToCharPtr(current.Key), current.Value, (float)((double)time * MSTOF60THS), easing);
		}
	}

	void EmotePlayer::Show()
	{
		sPlayer->Show();
	}

	void EmotePlayer::Skip()
	{
		sPlayer->Skip();
	}

	void EmotePlayer::StartWind(float start, float goal, float speed, float powMin, float powMax)
	{
		sPlayer->StartWind(start, goal, speed, powMin, powMax);
	}

	void EmotePlayer::StopTimeline(String^ label)
	{
		sPlayer->StopTimeline(StringToCharPtr(label));
	}

	void EmotePlayer::StopWind()
	{
		sPlayer->StopWind();
	}

	const char* EmotePlayer::StringToCharPtr(String^ str)
	{
		if (!String::IsNullOrWhiteSpace(str) && str->Length <= 50)
		{
			return context->marshal_as<char const *, System::String>(str);
		}
		return (char *)nulString;
	}

	EmotePlayer::~EmotePlayer()
	{
		if (sPlayer == NULL)
			return;
		sPlayer->Release();
	}

	IEmotePlayer__TYPE* EmotePlayer::NativePlayer::get()
	{
		return sPlayer;
	}
}