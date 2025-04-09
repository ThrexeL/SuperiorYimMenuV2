#include "Recovery.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto shopping        = std::make_shared<Category>("Shopping");
		auto vehiclesGroup   = std::make_shared<Group>("Vehicles");
		auto money           = std::make_shared<Category>("Money");
		auto nightclubGroup  = std::make_shared<Group>("Nightclub");
		auto bunkerGroup     = std::make_shared<Group>("Bunker");
		auto missions        = std::make_shared<Category>("Missions");
		auto generalGroup    = std::make_shared<Group>("General");
		auto cayoPericoGroup = std::make_shared<Group>("Cayo Perico");

		vehiclesGroup->AddItem(std::make_shared<BoolCommandItem>("dlcvehicles"_J));

		vehiclesGroup->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Save This Vehicle as Personal Vehicle"))
			{
				if (GiveVehicleReward::IsSafeToRunScript())
				{
					GiveVehicleReward::SetShouldRunScript(true);
				}
			}
		}));

		// Rockstar loves this!
		nightclubGroup->AddItem(std::make_shared<BoolCommandItem>("nightclubsafeloop"_J));
		nightclubGroup->AddItem(std::make_shared<CommandItem>("increasenightclubpopularity"_J));

		bunkerGroup->AddItem(std::make_shared<CommandItem>("fillbunkersupplies"_J));
		bunkerGroup->AddItem(std::make_shared<CommandItem>("bunkercooldownsreset"_J));

		generalGroup->AddItem(std::make_shared<CommandItem>("playallmissionssolo"_J));

		cayoPericoGroup->AddItem(std::make_shared<CommandItem>("skipcayosetup"_J));
		cayoPericoGroup->AddItem(std::make_shared<CommandItem>("skipcayocooldown"_J));

		shopping->AddItem(vehiclesGroup);

		money->AddItem(nightclubGroup);
		money->AddItem(bunkerGroup);

		missions->AddItem(generalGroup);
		missions->AddItem(cayoPericoGroup);

		AddCategory(std::move(money));
		AddCategory(std::move(missions));
		AddCategory(std::move(shopping));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
	}
}