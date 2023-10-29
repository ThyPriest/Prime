#pragma once

#include "Application.h"
#include "Prime/Config/Config.h"

#ifdef PRIME_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	PRIME_PROFILE_BEGIN("Application-startup", "startup.log");
	auto App = Prime::CreateApplication();
	PRIME_PROFILE_END();

	PRIME_PROFILE_BEGIN("Application-Runtime", "Runtime.log");
	App->Run();
	PRIME_PROFILE_END();

	PRIME_PROFILE_BEGIN("Application-shutdown", "Shutdown.log");
	delete App;
	PRIME_PROFILE_END();
}

#endif // PRIME_PLATFORM_WINDOWS
