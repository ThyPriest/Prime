
#include "pch.h"
#include "Dispatcher.h"

namespace Prime
{
	Dispatcher::DispatcherData* Dispatcher::s_Data = new Dispatcher::DispatcherData();;

	void Dispatcher::Shutdown()
	{
		delete s_Data;
		s_Data = nullptr;
	}
}