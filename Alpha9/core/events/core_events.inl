#pragma once

#include "macros.hpp"
#include "events.hpp"

// /GameTick/, /PhysicsTick/, EngineStart, EngineStop

// TODO: Add the GameTick and PhysicsTick events

namespace Alpha9
{
	/**********EngineStart**********/
	class A9_API EngineStartEvent : public Event
	{
	public:
		EngineStartEvent(float startTime)
			: m_startTime(startTime)
		{}
		EngineStartEvent(const EngineStartEvent& e)
			: m_startTime(e.GetStartTime())
		{}

		inline const float GetStartTime() const { return m_startTime; }

		EVENT_CLASS_TYPE(EngineStartEvent)
	private:
		const float m_startTime;
	};

	/**********EngineStop**********/
	class A9_API EngineStopEvent : public Event
	{
	public:
		EngineStopEvent(float stopTime)
			: m_stopTime(stopTime)
		{}
		EngineStopEvent(const EngineStopEvent& e)
			: m_stopTime(e.GetStopTime())
		{}

		inline const float GetStopTime() const { return m_stopTime; }

		EVENT_CLASS_TYPE(EngineStopEvent)
	private:
		const float m_stopTime;
	};
}