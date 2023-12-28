#pragma once

#include "ecdynamicentity.hpp"

class NPC : public eCDynamicEntity
{
public:

	NPC() = delete;

	explicit NPC( std::uintptr_t ptr ) : eCDynamicEntity( ptr ) { }

	[[nodiscard]] std::uintptr_t get_last_npc_ptr() const;

	[[nodiscard]] std::uintptr_t get_next_npc_ptr() const;

	[[nodiscard]] EntityClasses_NPC get_entity_classes() const;

};