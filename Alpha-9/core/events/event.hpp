#pragma once

#include <queue>
#include <map>

#include "core.hpp"

#define TRIGGER_EVENT(e) ::Alpha9::GetEventManager().Add(&e)
#define BIND_EVENT(type, func) ::Alpha9::GetEventManager().Bind(::Alpha9::EventType::##type, func)

namespace Alpha9
{

	enum class EventType
	{
		None = 0,
		WindowCloseEvent, WindowMoveEvent, WindowFocusEvent, WindowResizeEvent, WindowMaximizeEvent,
		KeyDownEvent, KeyUpEvent,
		MouseButtonDownEvent, MouseButtonUpEvent, MouseMoveEvent, MouseScrollEvent
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
				virtual EventType GetEventType() const override { return GetStaticType(); }\
				virtual const char* GetName() const override { return #type; }\
				virtual Event *copy() const override { return new type(*this); }

	class A9_API Event
	{
		// ALL events MUST provide a copy-constructor!
	public:
		virtual EventType GetEventType() const { return EventType::None; }
		virtual const char *GetName() const = 0;
		virtual Event *copy() const = 0;
	};

	class A9_API EventManager
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		EventManager();
		~EventManager();

		void Resolve(); // Resolves all currently registered events
		void Resolve(size_t amount);
		//Resolves the specified amount of events
		//Taking priority to those registered first

		inline void Add(Event *e)
		{
			// Making a copy of the event in case the pointer gets deleted.
			Event *copy_e = e->copy();

			s_events.push(copy_e);
		}
		inline void Bind(EventType t, EventCallbackFn func) 
		{
			s_bindings.insert(std::make_pair(t, func));
		}
	private:
		void handle_event(Event *&e);
		std::vector<EventCallbackFn> find_event_callbacks(const EventType &t);
	private:
		static EventManager *s_instance;

		// TODO: implement m_events with std::shared_ptr
		static std::queue<Event *> s_events;
		static std::multimap<EventType, EventCallbackFn> s_bindings;
	};
}

#include "window_events.inl"
#include "input_events.inl"