#pragma once

#include "Core.h"

namespace Prime
{
	class PRIME_API GameTime
	{
	public:
		static void Initialize(uint32_t fps);
		static void SetFps(uint32_t fps);

		static void Tick();
		static void Shutdown();

		static inline float GetDeltaTime() { return s_Data->DeltaTime; }
		static float GetSeconds() { return s_Data->DeltaTime * 1000.0f; }

	private:
		struct GameTimeData
		{
			float DeltaTime = 0.0f;
			float LastTime = 0.0f;
			float Fps = 0.0f;
		};

		static GameTimeData* s_Data;
	};
}