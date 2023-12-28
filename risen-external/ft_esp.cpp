#include "ft_esp.hpp"

#include "globals.hpp"

#include <DirectXMath.h>

[[nodiscard]] inline bool world_to_screen( vec3 world, vec2& screen )
{
	const auto cam_base = Globals::g_ICApp->get_camera_base_ptr();

	if( !cam_base )
		return false;

	const auto mat_view = Globals::g_ICApp->get_view_matrix();

	const auto mat_proj = Globals::g_ICApp->get_projection_matrix();

	auto mat_viewproj = mat_view;
	mat_viewproj.multiply( mat_proj );

	const vec4 clip =
	{
		world.x * mat_viewproj.a.x + world.y * mat_viewproj.b.x + world.z * mat_viewproj.c.x + mat_viewproj.d.x,
		world.x * mat_viewproj.a.y + world.y * mat_viewproj.b.y + world.z * mat_viewproj.c.y + mat_viewproj.d.y,
		world.x * mat_viewproj.a.z + world.y * mat_viewproj.b.z + world.z * mat_viewproj.c.z + mat_viewproj.d.z,
		world.x * mat_viewproj.a.w + world.y * mat_viewproj.b.w + world.z * mat_viewproj.c.w + mat_viewproj.d.w
	};

	if( clip.z < 0.1f )
		return false;

	const vec2 NDC = { clip.x / clip.w, clip.y / clip.w };

	const auto overlay_width = Globals::g_pOverlay->get_overlay_width() * 1.f;
	const auto overlay_height = Globals::g_pOverlay->get_overlay_height() * 1.f;

	screen.x = ( overlay_width / 2 * NDC.x ) + ( NDC.x + overlay_width / 2 );
	screen.y = -1.f * ( overlay_height / 2 * NDC.y ) + ( NDC.y + overlay_height / 2 );
	return true;
}

void ft_esp::on_render()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Enable ESP" ) || !Globals::g_IEntities->
		initialize_pointer_to_lists() )
		return;

	const auto dents = Globals::g_IEntities->get_dynamic_entities();

	if( !dents.empty() )
	{
		for( const auto& dent : dents )
		{
			if( !dent )
				continue;

			const auto world_pos = Globals::g_IEntities->get_world_pos( dent );
			const auto top_world = Globals::g_pProcess->read< vec3 >( dent + 0x90 );

			vec2 screen_pos = {};
			vec2 top_screen = {};

			if( world_to_screen( world_pos, screen_pos ) && world_to_screen( top_world, top_screen ) )
			{
				const auto name = Globals::g_IEntities->get_simple_entity_name( dent );

				const auto type = Globals::g_IEntities->get_entity_type( dent );

				int32_t height, width;

				switch( type )
				{
					case PC_HERO:
						//printf("[%08X] Ignored player!\n", dent );
						break;

					case NPC:
						//printf("[%08X] Drawed NPC -> %s\n", dent, name.c_str());

						if( Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Glow NPC" ) )
							Globals::g_IEntities->glow_entity( dent );

						if( !Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Show NPC" ) )
							break;

						height = static_cast< int32_t >( top_screen.y - screen_pos.y );
						width = height / 2;

						Globals::g_pOverlay->draw_filled_rect(
							static_cast< int32_t >( screen_pos.x ),
							static_cast< int32_t >( screen_pos.y ),
							10,
							10,
							255,
							0,
							255
						);

						Globals::g_pOverlay->draw_string(
							name,
							top_screen.x - width / 2,
							top_screen.y + width,
							255,
							0,
							255
						);

						break;

					case CREATURE:
						//printf( "[%08X] Drawed Creature -> %s\n", dent, name.c_str() );


						if( !Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Show Creature" ) )
							break;

						height = static_cast< int32_t >( top_screen.y - screen_pos.y );
						width = height / 2;

						Globals::g_pOverlay->draw_rect( screen_pos.x, top_screen.y, width, height, 255, 0, 0, 2 );
						Globals::g_pOverlay->draw_string(
							name,
							screen_pos.x - width / 2,
							top_screen.y + width,
							255,
							0,
							0
						);
						{
							const auto health = Globals::g_IEntities->get_creature_health( dent );
							const auto maximum_health = Globals::g_IEntities->get_creature_health_maximum( dent );

							Globals::g_pOverlay->draw_string(
								std::vformat( "{}/{} LP", std::make_format_args( health, maximum_health ) ),
								screen_pos.x - width / 2,
								top_screen.y - width,
								255,
								0,
								0
							);
						}
						break;

					case ITEM_COLLECTABLE_1:
					case ITEM_COLLECTABLE_2:
					case ITEM_OBJECT_INTERACT:
						if( !Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Show Item" ) )
							break;

						Globals::g_pOverlay->draw_filled_rect( screen_pos.x, screen_pos.y, 8, 8, 255, 255, 0 );
						Globals::g_pOverlay->draw_string( name, screen_pos.x - 10, screen_pos.y + 10, 255, 255, 0 );
						break;

					case TRIGGERSCRIPT:
						//printf("[%08X] Ignored %s!\n", dent, name.c_str());
						break;

					default:
						printf("[%08X] Unimplemented %s type -> %d\n", dent, name.c_str(), type);
						Globals::g_pOverlay->draw_filled_rect(
							static_cast< int32_t >( screen_pos.x ),
							static_cast< int32_t >( screen_pos.y ),
							10,
							10,
							255,
							255,
							255
						);
						break;
				}
			}
		}
	}
}
