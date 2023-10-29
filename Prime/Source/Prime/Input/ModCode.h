#pragma once

#include <cstdint>

using ModCode = uint32_t;

namespace Prime::Mod
{
	enum : ModCode
	{
		SHIFT = 0x0001,
		CONTROL = 0x0002,
		ALT = 0x0004,
		SUPER = 0x0008,
		CAPLOCKS = 0x0010,
		NUMLOCKS = 0x0020
	};
}