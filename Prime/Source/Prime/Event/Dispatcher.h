#pragma once

#include "Prime/Core/Core.h"
#include "Event.h"
#include <functional>
#include <map>
#include <vector>

namespace Prime
{
	class PRIME_API Dispatcher
	{
		using EventCallbackFunc = std::function<void(const Event&)>;

	public:
		static void Shutdown();

		template<typename TEvent>
		static void SubscribeToEvent(EventCallbackFunc&& callback)
		{
			s_Data->Callbacks[TEvent::GetStaticType()].push_back(callback);
		}

		template<typename TEvent, typename TClass>
		static void SubscribeToEvent(TClass* instance, void (TClass::* callbackFunc)(const Event&))
		{
			EventCallbackFunc callback = std::bind(callbackFunc,
				instance, std::placeholders::_1);

			s_Data->Callbacks[TEvent::GetStaticType()].push_back(callback);
		}

		template<typename TEvent>
		static const TEvent& CastToEvent(const Event& event)
		{
			return static_cast<const TEvent&>(event);
		}

		template<typename TEvent, typename ... TArgs>
		static void PostEvent(TArgs ... args)
		{
			const EventType type = TEvent::GetStaticType();

			if (s_Data->Callbacks.find(type) == s_Data->Callbacks.end()) { return; }

			for (auto&& callback : s_Data->Callbacks.at(type))
			{
				TEvent event(std::forward<TArgs>(args)...);
				callback(event);
			}
		}

	private:
		struct DispatcherData
		{
			std::map<EventType, std::vector<EventCallbackFunc>> Callbacks;
		};

		static DispatcherData* s_Data;
	};
}