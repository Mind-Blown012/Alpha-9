#pragma once

#include "macros.hpp"

namespace Alpha9
{
	class A9_API Game
	{
	public:
		virtual void Awake() {};
		virtual void Start() {};
		virtual void Update() {};
		virtual void Render() {};
		virtual void FixedUpdate() {};
	};
}
// Defined by client
extern Alpha9::Game* CreateGame();