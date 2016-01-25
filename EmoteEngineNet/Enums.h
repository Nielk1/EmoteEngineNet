#pragma once

using namespace System;

namespace EmoteEngineNet
{
	public enum class AlphaOp : UInt32
	{
		ALPHA_OP_DESTALPHA_MULTIPLY_INVSRCALPHA_PLUS_SRCALPHA,
		ALPHA_OP_DESTALPHA_PLUS_SRCALPHA
	};

	public enum class MaskMode : UInt32
	{
		MASK_MODE_STENCIL,
		MASK_MODE_ALPHA
	};

	public enum class ShaderModel : UInt32
	{
		SHADER_MODEL_NO_SHADER,
		SHADER_MODEL_2,
		SHADER_MODEL_3
	};

	public enum class TimelinePlayFlags : UInt32
	{
		NONE = 0u,
		TIMELINE_PLAY_PARALLEL = 1u,
		TIMELINE_PLAY_DIFFERENCE = 2u
	};
}