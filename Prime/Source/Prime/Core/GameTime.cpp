
#include "pch.h"
#include "GameTime.h"
#include "GLFW/glfw3.h"

namespace Prime
{
	GameTime::GameTimeData* GameTime::s_Data;

	void GameTime::Initialize(uint32_t fps)
	{
		s_Data = new GameTime::GameTimeData;
		SetFps(fps);
	}

	void GameTime::SetFps(uint32_t fps)
	{
		{ if (fps > 0) { s_Data->Fps = (float)fps / 1000.0f; } }
	}

	void GameTime::Tick()
	{
		s_Data->DeltaTime = ((float)glfwGetTime() - s_Data->LastTime) * (s_Data->Fps);
		s_Data->LastTime = (float)glfwGetTime();
	}

	void GameTime::Shutdown()
	{
		delete s_Data;
		s_Data = nullptr;
	}
}