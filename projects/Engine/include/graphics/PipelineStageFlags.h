#ifndef pipelinestageflags_h__
#define pipelinestageflags_h__

#include <cstdint>

using PipelineStageFlags = uint32_t;

enum EPipelineStageFlagBits : uint32_t
{
	PIPELINE_STAGE_TOP_OF_PIPE						= 0x00000001,
	PIPELINE_STAGE_DRAW_INDIRECT					= 0x00000002,
	PIPELINE_STAGE_VERTEX_INPUT						= 0x00000004,
	PIPELINE_STAGE_VERTEX_SHADER					= 0x00000008,
	PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER		= 0x00000010,
	PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER	= 0x00000020,
	PIPELINE_STAGE_GEOMETRY_SHADER					= 0x00000040,
	PIPELINE_STAGE_FRAGMENT_SHADER					= 0x00000080,
	PIPELINE_STAGE_EARLY_FRAGMENT_TESTS				= 0x00000100,
	PIPELINE_STAGE_LATE_FRAGMENT_TESTS				= 0x00000200,
	PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT			= 0x00000400,
	PIPELINE_STAGE_COMPUTE_SHADER					= 0x00000800,
	PIPELINE_STAGE_TRANSFER							= 0x00001000,
	PIPELINE_STAGE_BOTTOM_OF_PIPE					= 0x00002000,
	PIPELINE_STAGE_HOST								= 0x00004000,
	PIPELINE_STAGE_ALL_GRAPHICS						= 0x00008000,
	PIPELINE_STAGE_ALL_COMMANDS						= 0x00010000,
};

#endif // pipelinestageflags_h__