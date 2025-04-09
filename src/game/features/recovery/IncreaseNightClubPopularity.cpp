#include "core/backend/ScriptMgr.hpp"
#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptGlobal.hpp"

namespace YimMenu::Features
{
	class IncreaseNightClubPopularity : public Command
	{
		using Command::Command;

	private:
		std::string GetCurrentCharacterPrefix()
		{
			int character_id = 0;
			Hash stat_hash   = MISC::GET_HASH_KEY("MPPLY_LAST_MP_CHAR");
			if (STATS::STAT_GET_INT(stat_hash, &character_id, true))
			{
				return "MP" + std::to_string(character_id) + "_";
			}
			return "MP0_";
		}

		void AdjustNightclubPopularity()
		{
			std::string popularity_stat = GetCurrentCharacterPrefix() + "CLUB_POPULARITY";
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY(popularity_stat.c_str()), 1000, true);
		}

	public:
		virtual void OnCall() override
		{
			AdjustNightclubPopularity();
			Notifications::Show("Nightclub Popularity", "Nightclub popularity boosted to maximum!", NotificationType::Success);
		}
	};

	static IncreaseNightClubPopularity _increase_nightclub_popularity{"increasenightclubpopularity", "Increase Nightclub Popularity", "Boosts nightclub popularity to maximum"};
}
