#pragma once

using namespace System;

namespace EmoteEngineNet
{
	public enum class AlphaOp : uint32_t
	{
		ALPHA_OP_DESTALPHA_MULTIPLY_INVSRCALPHA_PLUS_SRCALPHA,
		ALPHA_OP_DESTALPHA_PLUS_SRCALPHA
	};

	public enum class MaskMode : uint32_t
	{
		MASK_MODE_STENCIL,
		MASK_MODE_ALPHA
	};

	public enum class ShaderModel : uint32_t
	{
		SHADER_MODEL_NO_SHADER,
		SHADER_MODEL_2,
		SHADER_MODEL_3
	};

	public enum class TimelinePlayFlags : uint32_t
	{
		NONE = 0u,
		TIMELINE_PLAY_PARALLEL = 1u,
		TIMELINE_PLAY_DIFFERENCE = 2u
	};

	public enum class InterfaceVersion : uint32_t
	{
		v3_4,
		NEKO1,
		v3_52,
		NEKO0,
	};

	public enum class ColorType : uint32_t
	{
		BGRA,
		RGBA
	};
}