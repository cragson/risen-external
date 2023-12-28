#include "risen_cheat.hpp"

#include "ft_esp.hpp"
#include "ft_skill_hook.hpp"
#include "ft_stats_editor.hpp"
#include "Globals.hpp"
#include "Offsets.hpp"
#include "utils.hpp"

bool risen_cheat::setup_features()
{
	//auto sk = std::make_unique< ft_skill_hook >();
	//sk->set_name( L"Skill Hook" );
	//sk->disable_drawing();
	//sk->set_status(true);

	//this->m_features.push_back( std::move( sk ) );

	auto esp = std::make_unique< ft_esp >();
	esp->set_name( L"ESP" );
	esp->enable_drawing();
	esp->set_status( true );

	this->m_features.push_back( std::move( esp ) );

	auto edit = std::make_unique< ft_stats_editor >();
	edit->set_name( L"StatsEditor" );
	edit->enable_drawing();
	edit->set_status( true );

	this->m_features.push_back( std::move( edit ) );

	Globals::g_pMenu->set_virtual_key_code( VK_INSERT );
	Globals::g_pMenu->enable_drawing();

	return true;
}

bool risen_cheat::setup_offsets()
{
	if( !Globals::g_pProcess->does_image_exist_in_map( L"Game.dll" ) || !Globals::g_pProcess->
		does_image_exist_in_map( L"Script.dll" ) || !Globals::g_pProcess->does_image_exist_in_map( L"Engine.dll" )
		|| !Globals::g_pProcess->does_image_exist_in_map( L"SharedBase.dll" ) )
		return false;

	const auto game = Globals::g_pProcess->get_image_ptr_by_name( L"Game.dll" );
	const auto script = Globals::g_pProcess->get_image_ptr_by_name( L"Script.dll" );
	const auto engine = Globals::g_pProcess->get_image_ptr_by_name( L"Engine.dll" );
	const auto base = Globals::g_pProcess->get_image_ptr_by_name( L"SharedBase.dll" );

	const auto hk_skill = game->find_pattern( L"B9 ? ? ? ? FF 15 ? ? ? ? 89 7C AE 10", false );

	if( !hk_skill )
		return false;

	Offsets::skill_hook = hk_skill;

	const auto ent_mgr = script->find_pattern( L"A1 ? ? ? ? 50 E8", false );

	if( !ent_mgr )
		return false;

	Offsets::entity_info = script->deref_address< std::uintptr_t >( ent_mgr + 1 );

	const auto capp = engine->find_pattern( L"8B 0D ? ? ? ? 57 53", false );

	if( !capp )
		return false;

	Offsets::capplication = engine->deref_address< std::uintptr_t >( capp + 2 );

	const auto session = game->find_pattern( L"8B 0D ? ? ? ? 53 8B 1D", false );

	if( !session )
		return false;

	Offsets::csession_ptr = game->deref_address< std::uintptr_t >( session + 2 );

	const auto purchase = script->find_pattern(
		L"74 33 8B 01 8B 90 ? ? ? ? 6A 1F",
		false
	);

	if( !purchase)
		return false;

	Offsets::vendor_free_purchase = purchase;

	return true;
}

void risen_cheat::print_features()
{
	printf( "\n" );

	printf( "Feature-Name -> Feature-Hotkey\n" );

	for( const auto& feature : this->m_features )
		printf(
			"[>] %-25ws -> %s\n",
			feature->get_name().c_str(),
			utils::virtual_key_as_string( feature->get_virtual_key_code() ).c_str()
		);

	printf( "\n" );
}

void risen_cheat::print_offsets()
{
	printf( "\n" );

	const auto msg = []( const std::string& name, const std::uintptr_t value )
	{
		printf( "[>] %-35s -> 0x%08X\n", name.c_str(), value );
	};

	msg( "Skill Hook", Offsets::skill_hook );
	msg( "Entity Manager", Offsets::entity_info );
	msg( "CApplication", Offsets::capplication );
	msg( "CSession Pointer", Offsets::csession_ptr );
	msg( "Vendor Free Purchase", Offsets::vendor_free_purchase );

	printf( "\n" );
}

void risen_cheat::run()
{
	for( const auto& feature : this->m_features )
	{
		// before tick'ing the feature, check first if the state will eventually change
		if( GetAsyncKeyState( feature->get_virtual_key_code() ) & 0x8000 )
			feature->toggle();

		// let the feature tick() when active
		if( feature->is_active() )
			feature->tick();
	}
}

void risen_cheat::shutdown()
{
	// disable every feature here
	for( const auto& feature : this->m_features )
	{
		if( feature->is_active() )
			feature->disable();

		feature->on_shutdown();
	}
}
