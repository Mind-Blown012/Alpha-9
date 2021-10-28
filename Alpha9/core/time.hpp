#pragma once

namespace Alpha9
{
	class Time
	{
	private:
		friend class Application;

		static float _deltaTime; // This is the actual time when the last delta was calculated
		static float deltaTime; // The amount of time between the prior frame
	public:
		static void Init();
		static float getTime();
		
		static inline float GetDeltaTime() { return deltaTime; };
	private:
		static float updateDeltaTime();
		static float startTime;

		Time() = default;
		~Time() = default;
	};
}