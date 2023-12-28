#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "math.hpp"
#include "structs.hpp"

class entity_manager
{
public:
	entity_manager()
		: m_ents_ptr( std::uintptr_t() )
	  , m_npcs_ptr( std::uintptr_t() ) {}

	[[nodiscard]] bool initialize_pointer_to_lists() noexcept;

	[[nodiscard]] std::uintptr_t get_dynamic_entity_by_index( uint32_t index ) const noexcept;

	[[nodiscard]] std::uintptr_t get_npc_by_index( uint32_t index ) const noexcept;

	[[nodiscard]] static size_t get_entity_count() noexcept;

	[[nodiscard]] static size_t get_npc_count() noexcept;

	[[nodiscard]] std::vector< std::uintptr_t > get_dynamic_entities() const noexcept;

	[[nodiscard]] std::vector< std::uintptr_t > get_npcs() const noexcept;

	[[nodiscard]] std::uintptr_t get_local_player() const noexcept;

	[[nodiscard]] std::string get_entity_state( std::uintptr_t entity_ptr ) const noexcept;

	[[nodiscard]] std::string get_entity_task( std::uintptr_t entity_ptr ) const noexcept;

	[[nodiscard]] int32_t get_anim_state( std::uintptr_t entity_ptr ) const noexcept;

	[[nodiscard]] bool is_entity_weapon_blocking( std::uintptr_t entity_ptr ) const noexcept;

	[[nodiscard]] std::string get_npc_name( std::uintptr_t npc_ptr ) const noexcept;

	[[nodiscard]] std::string get_npc_description( std::uintptr_t npc_ptr ) const noexcept;

	[[nodiscard]] int32_t get_entity_health( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] int32_t get_entity_health_maximum( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] bool set_entity_health_to_one( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] int32_t get_entity_money( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] bool set_entity_money( std::uintptr_t ptr, int32_t amount ) const noexcept;

	[[nodiscard]] EEntityType get_entity_type( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] bool is_local_player( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] vec3 get_world_pos( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] bool glow_entity( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] std::string get_simple_entity_name( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] int32_t get_creature_health( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] int32_t get_creature_health_maximum( std::uintptr_t ptr ) const noexcept;

	bool make_harmless_creature( std::uintptr_t ptr ) const noexcept;

	[[nodiscard]] bool despawn_creature( std::uintptr_t ptr ) const noexcept;

private:
	std::uintptr_t m_ents_ptr;

	std::uintptr_t m_npcs_ptr;
};
