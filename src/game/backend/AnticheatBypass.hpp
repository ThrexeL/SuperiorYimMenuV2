#pragma once

namespace YimMenu
{
	class AnticheatBypass
	{
	private:
		static AnticheatBypass& GetInstance()
		{
			static AnticheatBypass instance;
			return instance;
		}

		void RunScriptImpl();

		bool m_IsFSLLoaded = false;
		bool m_BattlEyeRunning = false;

	public:
		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static bool IsFSLLoaded()
		{
			return GetInstance().m_IsFSLLoaded;
		}

		// actual battleye, as opposed to the FSL shim
		static bool IsBattlEyeRunning()
		{
			return GetInstance().m_BattlEyeRunning;
		}
	};
}