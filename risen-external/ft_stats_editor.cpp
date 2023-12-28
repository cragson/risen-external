#include "ft_stats_editor.hpp"

#include "globals.hpp"

void ft_stats_editor::tick()
{
	if (!Globals::g_IEntities->initialize_pointer_to_lists())
	{
		printf("[!] Could not initialize pointer to entity list, some features may not work properly!\n");

		return;
	}

	const auto a0 = Globals::g_pMenu->get_value_of_setting< bool >( "Entities", "All Creatures Harmless" );
	const auto a1 = Globals::g_pMenu->get_value_of_setting< bool >( "Entities", "Despawn near Creatures" );

	const auto a2 = Globals::g_IEntities->get_local_player();
	const auto a3 = Globals::g_IEntities->get_world_pos( a2 );

	if( a0 || a1 )
		for( const auto& dent : Globals::g_IEntities->get_dynamic_entities() )
			if( dent )
				if( Globals::g_IEntities->get_entity_type( dent ) == CREATURE )
				{
					if( a1 )
					{
						auto a4 = Globals::g_IEntities->get_world_pos( dent );

						const auto a5 = a4 - a3;

						const auto dist = sqrtf( a5.x * a5.x + a5.y * a5.y + a5.z * a5.z );

						if( dist <= 500.f )
							if( !Globals::g_IEntities->despawn_creature( dent ) )
								printf( "[!] Could not despawn 0x%08X\n!\n", dent );
					}


					if( a0 && !a1 )
						if( !Globals::g_IEntities->make_harmless_creature( dent ) )
							printf( "[!] Could not make 0x%08X harmless!\n", dent );
				}


	if( !Globals::g_pStats->initialize_stats_ptr() )
		return;

	if( Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Godmode" ) )
		Globals::g_pStats->set_Health( Globals::g_pStats->get_HealthMaximum() );

	if( Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Infinite Mana" ) )
		Globals::g_pStats->set_Mana( Globals::g_pStats->get_ManaMaximum() );

	if( Globals::g_pMenu->get_value_of_setting< bool >( "Player", "Infinite XP" ) )
		Globals::g_pStats->set_Experience( 999999 );

	if( Globals::g_pMenu->get_value_of_setting< bool >( "StatsEditor", "Read Stats" ) )
	{
		Globals::g_pMenu->set_value_of_setting< bool >( "StatsEditor", "Read Stats", false );

		Sleep( 150 );

		if( !Globals::g_pStats->synchronize_stats() )
		{
			printf( "[!] Could not read the player stats!\n" );

			return;
		}
	}

	if( Globals::g_pMenu->get_value_of_setting< bool >( "StatsEditor", "Write Stats" ) )
	{
		Globals::g_pMenu->set_value_of_setting< bool >( "StatsEditor", "Write Stats", false );

		Sleep( 150 );

		Globals::g_pStats->set_Health( Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Health" ) );
		Globals::g_pStats->set_Mana( Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Mana" ) );
		Globals::g_pStats->set_Experience(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Experience" )
		);
		Globals::g_pStats->set_HealthMaximum(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "HealthMaximum" )
		);
		Globals::g_pStats->set_ManaMaximum(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "ManaMaximum" )
		);
		Globals::g_pStats->set_Strength(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Strength" )
		);
		Globals::g_pStats->set_Dexterity(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Dexterity" )
		);
		Globals::g_pStats->set_Wisdom( Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Wisdom" ) );
		Globals::g_pStats->set_BladeProtection(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "BladeProtection" )
		);
		Globals::g_pStats->set_BluntProtection(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "BluntProtection" )
		);
		Globals::g_pStats->set_PiercingProtection(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "PiercingProtection" )
		);
		Globals::g_pStats->set_FireProtection(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "FireProtection" )
		);
		Globals::g_pStats->set_IceProtection(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "IceProtection" )
		);
		Globals::g_pStats->set_MagicProtection(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "MagicProtection" )
		);
		Globals::g_pStats->set_SwordFighting(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "SwordFighting" )
		);
		Globals::g_pStats->set_AxeFighting(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "AxeFighting" )
		);
		Globals::g_pStats->set_StaffCombat(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "StaffCombat" )
		);
		Globals::g_pStats->set_Archery( Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Archery" ) );
		Globals::g_pStats->set_Crossbow(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Crossbow" )
		);
		Globals::g_pStats->set_RuneSeal(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "RuneSeal" )
		);
		Globals::g_pStats->set_Fireball(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Fireball" )
		);
		Globals::g_pStats->set_Frost( Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Frost" ) );
		Globals::g_pStats->set_MagicBullet(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "MagicBullet" )
		);
		Globals::g_pStats->set_Smithing(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Smithing" )
		);
		Globals::g_pStats->set_Prospecting(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Prospecting" )
		);
		Globals::g_pStats->set_Lockpicking(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Lockpicking" )
		);
		Globals::g_pStats->set_Pickpocket(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Pickpocket" )
		);
		Globals::g_pStats->set_Sneak( Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Sneak" ) );
		Globals::g_pStats->set_Acrobatics(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Acrobatics" )
		);
		Globals::g_pStats->set_Alchemy( Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "Alchemy" ) );
		Globals::g_pStats->set_CreateScrolls(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "CreateScrolls" )
		);
		Globals::g_pStats->set_GutAnimals(
			Globals::g_pMenu->get_value_of_setting< int32_t >( "StatsEditor", "GutAnimals" )
		);
	}
}
