#include "app_manager.hpp"

#include "globals.hpp"
#include "offsets.hpp"

bool capplication_manager::initialize_pointer() noexcept
{
	const auto ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::capplication );

	if( !ptr )
		return true;

	this->m_ptr = ptr;

	return true;
}

std::uintptr_t capplication_manager::get_camera_base_ptr() const noexcept
{
	return this->m_ptr ? Globals::g_pProcess->read< std::uintptr_t >( this->m_ptr + 0x6C ) : std::uintptr_t();
}

int32_t capplication_manager::get_game_width() const noexcept
{
	return this->m_ptr ? Globals::g_pProcess->read< int32_t >( this->m_ptr + 0x70 ) : int32_t();
}

int32_t capplication_manager::get_game_height() const noexcept
{
	return this->m_ptr ? Globals::g_pProcess->read< int32_t >( this->m_ptr + 0x74 ) : int32_t();
}

int32_t capplication_manager::get_game_refresh_rate() const noexcept
{
	return this->m_ptr ? Globals::g_pProcess->read< int32_t >( this->m_ptr + 0x78 ) : int32_t();
}

matrix4x4 capplication_manager::get_view_matrix() const noexcept
{
	const auto cam_base = this->get_camera_base_ptr();

	if( !cam_base )
		return {};

	return Globals::g_pProcess->read< matrix4x4 >( cam_base + 0x8 );
}

matrix4x4 capplication_manager::get_projection_matrix() const noexcept
{
	const auto cam_base = this->get_camera_base_ptr();

	if( !cam_base )
		return {};

	return Globals::g_pProcess->read< matrix4x4 >( cam_base + 0x48 );
}

vec2 capplication_manager::get_field_of_view() const noexcept
{
	const auto cam_base = this->get_camera_base_ptr();

	if( !cam_base )
		return {};

	return Globals::g_pProcess->read< vec2 >( cam_base + 0xCC );
}
