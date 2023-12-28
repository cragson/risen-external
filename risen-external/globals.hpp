#pragma once

#include "app_manager.hpp"
#include "entity_manager.hpp"
#include "menu.hpp"
#include "player_stats.hpp"
#include "risen_cheat.hpp"
#include "risen_overlay.hpp"

#include "osmium/Memory/Process/process.hpp"


namespace Globals
{
	inline auto g_pCheat = std::make_unique< risen_cheat >();

	inline auto g_pOverlay = std::make_unique< risen_overlay >();

	inline auto g_pProcess = std::make_unique< process >();

	inline auto g_IEntities = std::make_unique< entity_manager >();

	inline auto g_ICApp = std::make_unique< capplication_manager >();

	inline auto g_pMenu = std::make_unique< menu >();

	inline auto g_pStats = std::make_unique< PlayerStats >();
}
