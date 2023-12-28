#include "entity_manager.hpp"

#include "globals.hpp"
#include "offsets.hpp"

#include <algorithm>

bool entity_manager::initialize_pointer_to_lists() noexcept
{
	const auto ents_ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::entity_info );

	if( !ents_ptr )
		return false;

	const auto npcs_ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::entity_info + 0xC );

	if( !npcs_ptr )
		return false;

	this->m_ents_ptr = ents_ptr;
	this->m_npcs_ptr = npcs_ptr;

	return true;
}

std::uintptr_t entity_manager::get_dynamic_entity_by_index( const uint32_t index ) const noexcept
{
	if( !this->m_ents_ptr )
		return {};

	return Globals::g_pProcess->read< std::uintptr_t >( this->m_ents_ptr + index * sizeof( std::uintptr_t ) );
}

std::uintptr_t entity_manager::get_npc_by_index( const uint32_t index ) const noexcept
{
	if( !this->m_npcs_ptr )
		return false;

	return Globals::g_pProcess->read< std::uintptr_t >( this->m_npcs_ptr + index * sizeof( std::uintptr_t ) );
}

size_t entity_manager::get_entity_count() noexcept
{
	const auto ret = Globals::g_pProcess->read< size_t >( Offsets::entity_info + 0x4 );

	return ret > 0 ? ret - 1 : 0;
}

size_t entity_manager::get_npc_count() noexcept
{
	return Globals::g_pProcess->read< size_t >( Offsets::entity_info + 0x10 );
}

std::vector< std::uintptr_t > entity_manager::get_dynamic_entities() const noexcept
{
	if( !this->m_ents_ptr )
		return {};

	std::vector< std::uintptr_t > ents;

	const auto ents_count = get_entity_count();

	if( !ents_count )
		return {};

	ents.resize( ents_count );

	if(
		!ReadProcessMemory(
			Globals::g_pProcess->get_process_handle(),
			reinterpret_cast< LPCVOID >( this->m_ents_ptr ),
			ents.data(),
			ents_count * sizeof( std::uintptr_t ),
			nullptr
		)
	)
		return {};

	return ents;
}

std::vector< std::uintptr_t > entity_manager::get_npcs() const noexcept
{
	if( !this->m_npcs_ptr )
		return {};

	std::vector< std::uintptr_t > npcs;

	const auto npcs_count = get_npc_count();

	if( !npcs_count )
		return {};

	npcs.resize( npcs_count );

	if(
		!ReadProcessMemory(
			Globals::g_pProcess->get_process_handle(),
			reinterpret_cast< LPCVOID >( this->m_npcs_ptr ),
			npcs.data(),
			npcs_count * sizeof( std::uintptr_t ),
			nullptr
		)
	)
		return {};

	return npcs;
}

std::uintptr_t entity_manager::get_local_player() const noexcept
{
	const auto dents = this->get_dynamic_entities();

	if( dents.empty() )
		return {};

	for( const auto& dent : dents )
		if( Globals::g_pProcess->read< int32_t >( dent + 0x20 ) == 18 )
			return dent;

	return {};
}

std::string entity_manager::get_entity_state( const std::uintptr_t entity_ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( entity_ptr + 0x1C );

	if( !ptr1 )
		return {};

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x1C );

	if( !ptr2 )
		return {};

	const auto state_ptr = Globals::g_pProcess->read< std::uintptr_t >( ptr2 + 0x3C );

	if( !state_ptr )
		return {};

	return Globals::g_pProcess->read_ascii_null_terminated_string( state_ptr );
}

std::string entity_manager::get_entity_task( const std::uintptr_t entity_ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( entity_ptr + 0x1C );

	if( !ptr1 )
		return {};

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x1C );

	if( !ptr2 )
		return {};

	const auto task_ptr = Globals::g_pProcess->read< std::uintptr_t >( ptr2 + 0x18 );

	if( !task_ptr )
		return {};

	return Globals::g_pProcess->read_ascii_null_terminated_string( task_ptr );
}

int32_t entity_manager::get_anim_state( const std::uintptr_t entity_ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( entity_ptr + 0x1C );

	if( !ptr1 )
		return -1;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 );

	if( !ptr2 )
		return -1;

	return Globals::g_pProcess->read< int32_t >( ptr2 + 0x48 );
}

bool entity_manager::is_entity_weapon_blocking( const std::uintptr_t entity_ptr ) const noexcept
{
	return this->get_anim_state( entity_ptr ) != 5 ? false : true;
}

std::string entity_manager::get_npc_name( const std::uintptr_t npc_ptr ) const noexcept
{
	const auto name_ptr1 = Globals::g_pProcess->read< std::uintptr_t >( npc_ptr + 0x160 );

	if( !name_ptr1 )
		return {};

	const auto name_ptr2 = Globals::g_pProcess->read< std::uintptr_t >( name_ptr1 );

	if( !name_ptr2 )
		return {};

	const auto name_ptr3 = Globals::g_pProcess->read< std::uintptr_t >( name_ptr2 );

	if( !name_ptr3 )
		return {};

	return Globals::g_pProcess->read_ascii_null_terminated_string( name_ptr3 );
}

std::string entity_manager::get_npc_description( const std::uintptr_t npc_ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( npc_ptr + 0x1C );

	if( !ptr1 )
		return {};

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x14 );

	if( !ptr2 )
		return {};

	const auto ptr3 = Globals::g_pProcess->read< std::uintptr_t >( ptr2 + 0x14 );

	if( !ptr3 )
		return {};

	return Globals::g_pProcess->read_ascii_null_terminated_string( ptr3 );
}

int32_t entity_manager::get_entity_health( const std::uintptr_t ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return -1;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x3C );

	if( !ptr2 )
		return -1;

	return Globals::g_pProcess->read< int32_t >( ptr2 + 0x10 );
}

int32_t entity_manager::get_entity_health_maximum( const std::uintptr_t ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return -1;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x3C );

	if( !ptr2 )
		return -1;

	return Globals::g_pProcess->read< int32_t >( ptr2 + 0x24 );
}

bool entity_manager::set_entity_health_to_one( const std::uintptr_t ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return false;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x3C );

	if( !ptr2 )
		return false;

	return Globals::g_pProcess->write< int32_t >( ptr2 + 0x10, 1 );
}

int32_t entity_manager::get_entity_money( const std::uintptr_t ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return -1;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x18 );

	if( !ptr2 )
		return -1;

	const auto ptr3 = Globals::g_pProcess->read< std::uintptr_t >( ptr2 + 0x18 );

	if( !ptr3 )
		return -1;

	return Globals::g_pProcess->read< int32_t >( ptr3 + 0x68 );
}

bool entity_manager::set_entity_money( const std::uintptr_t ptr, const int32_t amount ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return false;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x18 );

	if( !ptr2 )
		return false;

	const auto ptr3 = Globals::g_pProcess->read< std::uintptr_t >( ptr2 + 0x18 );

	if( !ptr3 )
		return false;

	return Globals::g_pProcess->write< int32_t >( ptr3 + 0x68, amount );
}

EEntityType entity_manager::get_entity_type( const std::uintptr_t ptr ) const noexcept
{
	return Globals::g_pProcess->read< EEntityType >( ptr + 0x20 );
}

bool entity_manager::is_local_player( const std::uintptr_t ptr ) const noexcept
{
	return Globals::g_pProcess->read< int32_t >( ptr + 0x20 ) == 18;
}

vec3 entity_manager::get_world_pos( const std::uintptr_t ptr ) const noexcept
{
	return Globals::g_pProcess->read< vec3 >( ptr + 0x64 );
}

bool entity_manager::glow_entity( const std::uintptr_t ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return false;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x2C );

	if( !ptr2 )
		return false;

	return Globals::g_pProcess->write< float >( ptr2 + 0x40, 13337 );
}

std::string entity_manager::get_simple_entity_name( const std::uintptr_t ptr ) const noexcept
{
	if( !ptr )
		return {};

	const auto ent_name = this->get_npc_name( ptr );

	if( ent_name.empty() )
		return {};

	const auto ent_type = this->get_entity_type( ptr );

	std::string ret = ent_name;

	const std::string gamestart_sub = "_Gamestart";

	switch( ent_type )
	{
		case PC_HERO:
			ret = "Player";
			break;

		case NPC:
			std::ranges::replace( ret, '_', ' ' );
			break;

		case CREATURE:
			if( ret.find( gamestart_sub ) != std::string::npos )
				ret.erase( ret.find( gamestart_sub ), gamestart_sub.length() );
			break;

		case ITEM_COLLECTABLE_1:
		case ITEM_COLLECTABLE_2:
		case ITEM_OBJECT_INTERACT:
			if( ret.starts_with( "It_" ) )
			{
				if( ret.find( "It_" ) != std::string::npos )
					ret.erase( ret.find( "It_" ), 3 );

				std::ranges::replace( ret, '_', ' ' );

				std::erase_if(
					ret,
					[]( const auto c )
					{
						return isdigit( c );
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

int32_t entity_manager::get_creature_health( const std::uintptr_t ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return -1;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x38 );

	if( !ptr2 )
		return -1;

	return Globals::g_pProcess->read< int32_t >( ptr2 + 0x10 );
}

int32_t entity_manager::get_creature_health_maximum( const std::uintptr_t ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return -1;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x38 );

	if( !ptr2 )
		return -1;

	return Globals::g_pProcess->read< int32_t >( ptr2 + 0x24 );
}

bool entity_manager::make_harmless_creature( const std::uintptr_t ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return false;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x38 );

	if( !ptr2 )
		return false;

	// Health = 1
	if( Globals::g_pProcess->read< int32_t >( ptr2 + 0x10 ) > 1 )
		Globals::g_pProcess->write< int32_t >( ptr2 + 0x10, 1 );

	// HealthMaximum = 1
	Globals::g_pProcess->write< int32_t >( ptr2 + 0x24, 1 );

	// Strength, Dexterity, Wisdom and all protections = 0
	for( auto i = 0; i < 7; i++ )
		// Health = 1
		Globals::g_pProcess->write< int32_t >( ptr2 + 0x2C + i * sizeof( std::uintptr_t ), 0 );

	return true;
}

bool entity_manager::despawn_creature( const std::uintptr_t ptr ) const noexcept
{
	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( ptr + 0x1C );

	if( !ptr1 )
		return false;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x10 );

	if( !ptr2 )
		return false;

	return Globals::g_pProcess->write< float >( ptr2 + 0x1C, 0.f );
}
