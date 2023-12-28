#pragma once
#include <cstdint>

#include "math.hpp"

class capplication_manager
{
public:
	capplication_manager()
		: m_ptr( std::uintptr_t() ) {}

	[[nodiscard]] bool initialize_pointer() noexcept;

	[[nodiscard]] std::uintptr_t get_camera_base_ptr() const noexcept;

	[[nodiscard]] int32_t get_game_width() const noexcept;

	[[nodiscard]] int32_t get_game_height() const noexcept;

	[[nodiscard]] int32_t get_game_refresh_rate() const noexcept;

	[[nodiscard]] matrix4x4 get_view_matrix() const noexcept;

	[[nodiscard]] matrix4x4 get_projection_matrix() const noexcept;

	[[nodiscard]] vec2 get_field_of_view() const noexcept;

private:
	std::uintptr_t m_ptr;
};
