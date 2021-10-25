#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <queue>
#include <memory>

#include "macros.hpp"

namespace Alpha9
{
	enum class A9_API EventType
	{
		None = 0,
		WindowCloseEvent, WindowMoveEvent, WindowResizeEvent, WindowMaximizeEvent, WindowFocusEvent,
		KeyDownEvent, KeyUpEvent,
		MouseButtonDownEvent, MouseButtonUpEvent, MouseMoveEvent, MouseScrollEvent,
		GameTickEvent, PhysicsTickEvent, EngineStartEvent, EngineStopEvent
	};
	static const std::string EventTypeStrings[] =
	{
		"None",
		"WindowCloseEvent", "WindowMoveEvent", "WindowResizeEvent", "WindowMaximizeEvent", "WindowFocusEvent",
		"KeyDownEvent", "KeyUpEvent",
		"MouseButtonDownEvent", "MouseButtonUpEvent", "MouseMoveEvent", "MouseScrollEvent",
		"GameTickEvent", "PhysicsTickEvent", "EngineStartEvent", "EngineStopEvent"
	};

	static std::string EventTypeToString(const EventType&);
	static EventType StringToEventType(const std::string&);

	class A9_API Event
	{
	public:
		static EventType GetStaticType() { return EventType::None; }
		virtual EventType GetEventType() const { return GetStaticType(); }
		virtual const char* GetName() const { return "None"; }
		virtual Event* copy() const { return new Event(*this); }
	};

	using EventFn = std::function<void(Event&)>;
	/* Singleton class A9_API with methods and data managing the
	   Alpha-9 event system.
	 */
	class A9_API EventManager final
	{
	public:
		static EventManager &Instance();

		// Returns reference to EventManager so that bind can be called like:
		// EventManager.Bind("KeyPress", &foo).Bind("MouseDown", &bar);
		virtual EventManager& Bind(const EventType&, const EventFn&);
		virtual EventManager& Bind(const std::string&, const EventFn&);


		virtual EventManager& Unbind(const EventType&, const EventFn&);
		virtual EventManager& Unbind(const std::string&, const EventFn&);

		virtual inline EventManager& Trigger(Event *e)
		{
			// Making a copy of the event in case the pointer gets deleted.
			Event* copy_e = e->copy();

			m_eventQueue.push(copy_e);
			return *this;
		}

		virtual EventManager& Resolve();
		virtual EventManager& Resolve(size_t);

		// operator() is the same as resolve all
		virtual EventManager& operator()();
	public:
		EventManager(const EventManager&) = delete;
		EventManager& operator=(const EventManager&) = delete;
	protected:
		std::vector<EventFn> findEventFns(EventType);
	private:
		EventManager() = default;
		virtual ~EventManager();

		std::queue<Event*> m_eventQueue;
		std::unordered_multimap<EventType, EventFn> m_bindings;
	};
}

#include "window_events.inl"
#include "input_events.inl"
#include "core_events.inl"