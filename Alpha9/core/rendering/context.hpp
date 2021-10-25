#pragma once

namespace Alpha9
{
	class Context
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void SetVSync(bool) = 0;
		virtual bool IsVSync() const = 0;
	protected:
		bool m_isUsingVSync = false;
	};
}