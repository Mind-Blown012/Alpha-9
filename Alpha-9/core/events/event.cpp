#include "a9pch.hpp"

#include "event.hpp"

namespace Alpha9
{

	EventManager *EventManager::s_instance = nullptr;
	std::queue<Event *> EventManager::s_events = std::queue<Event *>();
	std::multimap<EventType, EventManager::EventCallbackFn> EventManager::s_bindings = std::multimap<EventType, EventManager::EventCallbackFn>();

	EventManager::EventManager()
	{
		A9_CORE_ASSERT(!s_instance, "There can only be one event manager!");
		s_instance = this;
	}
	EventManager::~EventManager()
	{
		for (size_t i = 0; i < s_events.size(); i++)
		{
			// Going through `m_events` and deleting all of the pointers
			delete (s_events.front());
			s_events.pop();
		}
	}

	std::vector<EventManager::EventCallbackFn> EventManager::find_event_callbacks(const EventType &t)
	{
		// TODO: Test whether `EventManager::` is needed in front of typedef in declaration

		// The return value
		std::vector<EventCallbackFn> ret{};

		// Iterator type
		using it_type = std::multimap<EventType, EventCallbackFn>::iterator;

		// All of the matches for this event type
		std::pair<it_type, it_type> result = s_bindings.equal_range(t);

		// How many matches
		size_t count = std::distance(result.first, result.second);

		// Looping through the results
		for (it_type it = result.first; it != result.second; it++)
			ret.insert(ret.end(), it->second);

		return ret;
	}
	void EventManager::handle_event(Event *&e)
	{
		// Get all of the functions relating to the event type
		EventType t = e->GetEventType();
		std::vector<EventManager::EventCallbackFn> event_fns{};
		event_fns = find_event_callbacks(t);

		for(auto &fn : event_fns)
			fn((*e));
	}
	
	void EventManager::Resolve()
	{
		Resolve(s_events.size());
	}
	void EventManager::Resolve(size_t amount)
	{
		// Making sure that `amount` is constrained
		// between 0 and the size of the queue.
		if (amount > s_events.size())
		{
			A9_CORE_WARN("Resolve called with amount larger than amount of events!");
			amount = s_events.size();
		}
		else if (amount == 0)
			return;
		
		for (size_t i = 0; i < amount; i++)
		{
			Event *&e = s_events.front();
			handle_event(e);
			s_events.pop();
		}
	}

}