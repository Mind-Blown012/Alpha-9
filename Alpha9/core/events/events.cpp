#include "a9pch.hpp"

#include "events.hpp"

namespace Alpha9
{
	std::string EventTypeToString(const EventType& e)
	{
		int i = static_cast<int>(e);

		return EventTypeStrings[i];
	}
	EventType StringToEventType(const std::string& s)
	{
		int i = 0;
		// Find s in the EventTypeStrings array, will be one element ahead
		while (EventTypeStrings[i++] != s);
		i--;

		// convert to EventType
		EventType e = static_cast<EventType>(i);

		return e;
	}

	std::vector<EventFn> EventManager::findEventFns(EventType e)
	{
		using iter = std::unordered_multimap<EventType, EventFn>::iterator;

		std::vector<EventFn> result;

		// Finding all values in m_bindings with key of `e`
		std::pair<iter, iter> res = m_bindings.equal_range(e);
		// Going through all of the values with that key
		for (iter it = res.first; it != res.second; it++)
		{
			// ... and adding them to the vector
			result.insert(result.end(), it->second);
		}

		return result;
	}

	EventManager &EventManager::Instance()
	{
		static EventManager instance;

		return instance;
	}

	EventManager& EventManager::Bind(const EventType& e, const EventFn& fn)
	{
		m_bindings.emplace(e, fn);
		return *this;
	}
	EventManager& EventManager::Bind(const std::string& s, const EventFn& fn)
	{
		EventType e = StringToEventType(s);
		m_bindings.emplace(e, fn);
		return *this;
	}

	EventManager& EventManager::Unbind(const EventType& e, const EventFn& fn)
	{
		using iter = std::unordered_multimap<EventType, EventFn>::iterator;

		// Finding all values in m_bindings with key of `e`
		std::pair<iter, iter> result = m_bindings.equal_range(e);
		// Going through all of the values with that key
		for (iter it = result.first; it != result.second; it++)
		{
			// Only remove that key/value pair if BOTH the key and value
			// are equal to what was passed in to this method
			if (it->second.target<void(*)(Event&)>() == fn.target<void(*)(Event&)>()) // Compare raw pointers
			{
				m_bindings.erase(it);
				return *this;
			}
		}
		return *this;
	}
	EventManager& EventManager::Unbind(const std::string& s, const EventFn& fn)
	{
		Unbind(StringToEventType(s), fn);
		return *this;
	}

	EventManager& EventManager::Resolve()
	{
		Resolve(m_eventQueue.size());
		return *this;
	}
	EventManager& EventManager::Resolve(size_t s)
	{
		// Error handling
		if (s > m_eventQueue.size())
		{
			A9_CORE_WARN("EventManager::Resolve called with a larger value ({0})\
						than there are current events ({1}). Setting number of events\
						to resolve to the number of current events ({1}).", s, m_eventQueue.size());
			s = m_eventQueue.size();
		}
		else if (s < 0)
		{
			A9_CORE_WARN("EventManager::Resolve called with a negative number of events to resolve ({0}).\
						Not resolving any events.", s);
			return *this;
		}
		else if (s == 0)
		{
			return *this;
		}

		std::vector<EventFn> functions;
		while (m_eventQueue.size() > 0)
		{
			functions = findEventFns(m_eventQueue.front()->GetEventType());
			for (auto fn : functions)
				fn(*m_eventQueue.front());
			m_eventQueue.pop();
		}
		return *this;
	}

	EventManager& EventManager::operator()()
	{
		Resolve();
		return *this;
	}

	EventManager::~EventManager()
	{
		// Make sure that the event queue is empty when the EventManager is deleted
		for (size_t i = 0; i < m_eventQueue.size(); i++)
		{
			// Going through `m_events` and deleting all of the pointers
			delete (m_eventQueue.front());
			m_eventQueue.pop();
		}
	}
}