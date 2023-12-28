#pragma once

#include <cstdint>
#include <string>

#include "math.hpp"
#include "structs.hpp"

class eCGeomtryEntity {};
class eCEntity {};
class eCNode {};
class bCObjectRefBase {};
class bCOjectBase {};

class eCDynamicEntity : public eCGeomtryEntity, eCEntity, eCNode, bCObjectRefBase, bCOjectBase
{

public:

	eCDynamicEntity() = delete;

	explicit eCDynamicEntity( const std::uintptr_t ptr ) : m_ptr( ptr ) {}

	[[nodiscard]] vec3 get_world_pos() const noexcept;

	[[nodiscard]] vec3 get_world_pos_up() const noexcept;

	bool glow_entity( const float value = 13337 ) const noexcept;

	[[nodiscard]] matrix4x4 get_local_matrix() const noexcept;

	[[nodiscard]] std::string get_raw_name() const noexcept;

	[[nodiscard]] std::string get_simple_name() const noexcept;

	[[nodiscard]] EEntityType get_type() const noexcept;

	[[nodiscard]] bool is_creature() const noexcept;

	[[nodiscard]] bool is_npc() const noexcept;

	[[nodiscard]] bool is_player() const noexcept;

	[[nodiscard]] bool freeze_entity() const noexcept;

	[[nodiscard]] bool make_harmless() const noexcept;

	[[nodiscard]] Skills_PS get_skills() const noexcept;

	[[nodiscard]] int32_t get_health() const noexcept;

	[[nodiscard]] int32_t get_maximum_health() const noexcept;

	[[nodiscard]] bool set_health(const int32_t value) const noexcept;

	[[nodiscard]] bool is_dead() const noexcept;

	[[nodiscard]] bool despawn() const noexcept;

protected:

	std::uintptr_t m_ptr;

};