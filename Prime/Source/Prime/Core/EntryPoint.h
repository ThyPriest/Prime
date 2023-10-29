#pragma once

#include "Application.h"

#ifdef PRIME_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	auto App = Prime::CreateApplication();
	App->Run();
	delete App;
}

#endif // PRIME_PLATFORM_WINDOWS
