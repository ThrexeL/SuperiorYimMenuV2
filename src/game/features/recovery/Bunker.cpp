#include "core/backend/ScriptMgr.hpp"
#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptGlobal.hpp"

namespace YimMenu::Features
{
	void SetGlobalValue(int global_index, int value)
	{
		if (auto global = ScriptGlobal(global_index); global.CanAccess())
		{
			*global.As<int*>() = value;
		}
	}
	class FillBunkerSupplies : public Command
	{
		using Command::Command;

	public:
		virtual void OnCall() override
		{
			SetGlobalValue(1663174 + 6, 1);
			Notifications::Show("Bunker", "Bunker supplies have been filled!", NotificationType::Success);
		}
	};

	class BunkerCooldownsReset : public Command
	{
		using Command::Command;

	public:
		virtual void OnCall() override
		{
			SetGlobalValue(1162393585 + 21018, 946764522);
			SetGlobalValue(1162393585 + 21264, 1);
			SetGlobalValue(1162393585 + 21265, 1);
			SetGlobalValue(1162393585 + 21266, 1);
			SetGlobalValue(1162393585 + 21268, 1485279815);
			SetGlobalValue(1162393585 + 21269, 2041812011);

			Notifications::Show("Bunker Cooldowns", "Cooldowns have been reset!", NotificationType::Success);
		}
	};

	static FillBunkerSupplies _fill_bunker_supplies{"fillbunkersupplies", "Fill Bunker Supplies", "Fills bunker supplies instantly"};

	static BunkerCooldownsReset _bunker_cooldowns_reset{"bunkercooldownsreset", "Reset Bunker Cooldowns", "Resets bunker unlocker cooldowns"};
}
