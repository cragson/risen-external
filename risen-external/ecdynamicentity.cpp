#include "ecdynamicentity.hpp"

#include "globals.hpp"

#include <algorithm>

vec3 eCDynamicEntity::get_world_pos() const noexcept
{
    return Globals::g_pProcess->read< vec3 >(this->m_ptr + offsetof(Creature_t, m_vecWorldPos1));
}

vec3 eCDynamicEntity::get_world_pos_up() const noexcept
{
    return Globals::g_pProcess->read< vec3 >(this->m_ptr + offsetof(Creature_t, m_vecWorldUpPos));
}


matrix4x4 eCDynamicEntity::get_local_matrix() const noexcept
{
    return Globals::g_pProcess->read< matrix4x4 >(this->m_ptr + offsetof(Creature_t, m_LocalMatrix));
}


std::string eCDynamicEntity::get_raw_name() const noexcept
{
    const auto name_ptr1 = Globals::g_pProcess->read< std::uintptr_t >(this->m_ptr + offsetof(Creature_t, m_ppName));

    if (!name_ptr1)
        return {};

    const auto name_ptr2 = Globals::g_pProcess->read< std::uintptr_t >(name_ptr1);

    if (!name_ptr2)
        return {};

    const auto name_ptr3 = Globals::g_pProcess->read< std::uintptr_t >(name_ptr2);

    if (!name_ptr3)
        return {};

    return Globals::g_pProcess->read_ascii_null_terminated_string(name_ptr3);
}

std::string eCDynamicEntity::get_simple_name() const noexcept
{
	if (!this->m_ptr)
		return {};

	const auto ent_name = this->get_raw_name();

	if (ent_name.empty())
		return {};

	const auto ent_type = this->get_type();

	std::string ret = ent_name;

	const std::string gamestart_sub = "_Gamestart";

	switch (ent_type)
	{
	case PC_HERO:
		ret = "Player";
		break;

	case NPC:
		std::ranges::replace(ret, '_', ' ');
		break;

	case CREATURE:
		if (ret.find(gamestart_sub) != std::string::npos)
			ret.erase(ret.find(gamestart_sub), gamestart_sub.length());
		break;

	case ITEM_COLLECTABLE_1:
	case ITEM_COLLECTABLE_2:
	case ITEM_OBJECT_INTERACT:
		if (ret.starts_with("It_"))
		{
			if (ret.find("It_") != std::string::npos)
				ret.erase(ret.find("It_"), 3);

			std::ranges::replace(ret, '_', ' ');

			std::erase_if(
				ret,
				[](const auto c)
				{
					return isdigit(c);
				}
			);
		}
		break;

	case TRIGGERSCRIPT:
	default:
		break;
	}

	return ret;
}

EEntityType eCDynamicEntity::get_type() const noexcept
{
	return Globals::g_pProcess->read< EEntityType >(this->m_ptr + 0x20);
}

bool eCDynamicEntity::is_creature() const noexcept
{
	return this->get_type() == CREATURE;
}

bool eCDynamicEntity::is_npc() const noexcept
{
	return this->get_type() == NPC;
}

bool eCDynamicEntity::is_player() const noexcept
{
	return this->get_type() == PC_HERO;
}
