#include "core/commands/BoolCommand.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptGlobal.hpp"

#include <chrono>
#include <random>
#include <thread>

namespace YimMenu::Features
{
	class NightClubSafeLoop : public BoolCommand
	{
		using BoolCommand::BoolCommand;

	private:
		bool m_is_running = false;
		std::thread m_loop_thread;

		const int SAFE_AMOUNT_MIN = 200000;
		const int SAFE_AMOUNT_MAX = 250000;
		const int SAFE_CAPACITY   = 23680;
		const int INCOME_START    = 23657;
		const int INCOME_END      = 23676;

		std::random_device rd;
		std::mt19937 gen{rd()};
		std::uniform_int_distribution<int> delay_dist{4500, 7000};
		std::uniform_int_distribution<int> amount_dist{SAFE_AMOUNT_MIN, SAFE_AMOUNT_MAX};

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

		void SafeLoop()
		{
			while (m_is_running)
			{
				int randomized_amount = amount_dist(gen);

				for (int i = INCOME_START; i <= INCOME_END; i++)
				{
					if (auto global = ScriptGlobal(262145).At(i); global.CanAccess())
					{
						*global.As<int*>() = randomized_amount;
					}
				}

				if (auto global = ScriptGlobal(262145).At(SAFE_CAPACITY); global.CanAccess())
				{
					*global.As<int*>() = 250000;
				}

				std::string club_time = GetCurrentCharacterPrefix() + "CLUB_PAY_TIME_LEFT";
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY(club_time.c_str()), -1, true);

				std::this_thread::sleep_for(std::chrono::milliseconds(delay_dist(gen)));
			}
		}

	public:
		virtual void OnEnable() override
		{
			m_is_running = true;
			if (m_loop_thread.joinable())
				m_loop_thread.join();

			m_loop_thread = std::thread(&NightClubSafeLoop::SafeLoop, this);
		}

		virtual void OnDisable() override
		{
			m_is_running = false;
			if (m_loop_thread.joinable())
				m_loop_thread.join();
		}

		virtual ~NightClubSafeLoop()
		{
			OnDisable();
		}
	};

	static NightClubSafeLoop _nightclub_safe_loop{"nightclubsafeloop", "Nightclub Safe Loop*", "Fills the nightclub safe with random amounts"};
}
