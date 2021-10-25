#pragma once

namespace Alpha9
{
	class Time
	{
	private:
		friend class Application;

		static float _deltaTime;
	public:
		static void init();
		static float getTime();

		static float& deltaTime;
	private:
		static float updateDeltaTime(float&);
		static float startTime;

		Time() = default;
		~Time() = default;
	};
}