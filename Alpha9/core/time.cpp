#include "a9pch.hpp"

#include "time.hpp"
#include "events/events.hpp"

namespace Alpha9
{
	float Time::_deltaTime = 0.0f;
	float& Time::deltaTime = Time::_deltaTime;
	float Time::startTime = 0.0f;

	void Time::init()
	{
		using namespace std::chrono;
		auto nanosSinceEpoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch());
		Time::startTime = (float)((float)nanosSinceEpoch.count()/(float)1000000000);
		
		EngineStartEvent e{ startTime };
		TRIGGER_EVENT(e);
	}

	float Time::getTime()
	{
		using namespace std::chrono;
		auto nanosSinceEpoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch());
		float currentTime = (float)((float)nanosSinceEpoch.count() / (float)1000000000);
		A9_CORE_WARN("{}", Time::startTime);
		return (currentTime - Time::startTime);
	}

	float Time::updateDeltaTime(float&)
	{
		return 0.0f;
	}
}
