#include "menu.hpp"

#include "globals.hpp"
#include "utils.hpp"

void menu::on_first_activation()
{
	auto visuals = std::make_unique< SettingPrimary >( "Visuals" );
	visuals->add_secondary< bool >( "Enable ESP", false );
	visuals->add_secondary< bool >( "Show Creature", false );
	visuals->add_secondary< bool >( "Show NPC", false );
	visuals->add_secondary< bool >( "Show Item", false );
	visuals->add_secondary< bool >( "Glow NPC", false );

	auto play = std::make_unique< SettingPrimary >( "Player" );
	play->add_secondary< bool >( "Godmode", false );
	play->add_secondary< bool >( "Infinite Mana", false );
	play->add_secondary< bool >( "Infinite XP", false );

	auto ents = std::make_unique< SettingPrimary >( "Entities" );
	ents->add_secondary< bool >( "All Creatures Harmless", false );
	ents->add_secondary< bool >( "Despawn near Creatures", false );

	auto stats = std::make_unique< SettingPrimary >( "StatsEditor" );
	stats->add_secondary< bool >( "Read Stats", false );
	stats->add_secondary< bool >( "Write Stats", false );
	stats->add_secondary< int32_t >( "Health", 1 );
	stats->add_secondary< int32_t >( "Mana", 1 );
	stats->add_secondary< int32_t >( "Experience", 1 );
	stats->add_secondary< int32_t >( "HealthMaximum", 1 );
	stats->add_secondary< int32_t >( "ManaMaximum", 1 );
	stats->add_secondary< int32_t >( "Strength", 1 );
	stats->add_secondary< int32_t >( "Dexterity", 1 );
	stats->add_secondary< int32_t >( "Wisdom", 1 );
	stats->add_secondary< int32_t >( "BladeProtection", 1 );
	stats->add_secondary< int32_t >( "BluntProtection", 1 );
	stats->add_secondary< int32_t >( "PiercingProtection", 1 );
	stats->add_secondary< int32_t >( "FireProtection", 1 );
	stats->add_secondary< int32_t >( "IceProtection", 1 );
	stats->add_secondary< int32_t >( "MagicProtection", 1 );
	stats->add_secondary< int32_t >( "SwordFighting", 1 );
	stats->add_secondary< int32_t >( "AxeFighting", 1 );
	stats->add_secondary< int32_t >( "StaffCombat", 1 );
	stats->add_secondary< int32_t >( "Archery", 1 );
	stats->add_secondary< int32_t >( "Crossbow", 1 );
	stats->add_secondary< int32_t >( "RuneSeal", 1 );
	stats->add_secondary< int32_t >( "Fireball", 1 );
	stats->add_secondary< int32_t >( "Frost", 1 );
	stats->add_secondary< int32_t >( "MagicBullet", 1 );
	stats->add_secondary< int32_t >( "Smithing", 1 );
	stats->add_secondary< int32_t >( "Prospecting", 1 );
	stats->add_secondary< int32_t >( "Lockpicking", 1 );
	stats->add_secondary< int32_t >( "Pickpocket", 1 );
	stats->add_secondary< int32_t >( "Sneak", 1 );
	stats->add_secondary< int32_t >( "Acrobatics", 1 );
	stats->add_secondary< int32_t >( "Alchemy", 1 );
	stats->add_secondary< int32_t >( "CreateScrolls", 1 );
	stats->add_secondary< int32_t >( "GutAnimals", 1 );


	this->m_Settings.push_back( std::move( visuals ) );
	this->m_Settings.push_back( std::move( play ) );
	this->m_Settings.push_back( std::move( ents ) );
	this->m_Settings.push_back( std::move( stats ) );
}

void menu::on_enable() {}

void menu::on_disable() {}

void menu::tick()
{
	if( !this->m_status )
		return;

	const auto primary_amount = this->get_amount_of_primaries();

	static int32_t last_primary_index = 0;

	SettingNone* current_setting = nullptr;

	if( this->m_SelectedPrimaryName.empty() )
		current_setting = this->m_Settings.at( this->m_SelectedIndex ).get();
	else
		current_setting = reinterpret_cast< SettingPrimary* >( this->m_Settings.at( last_primary_index ).get() )->
		                  get_secondaries_ptr()->at( this->m_SelectedIndex );

	if( utils::is_key_pressed( VK_TAB ) )
	{
		if( current_setting->is_primary() && !last_primary_index && this->m_SelectedPrimaryName.empty() &&
			reinterpret_cast< SettingPrimary* >( current_setting )->get_num_of_secondaries() > 0 )
		{
			this->m_SelectedPrimaryName = this->m_Settings.at( this->m_SelectedIndex )->get_name();

			last_primary_index = this->m_SelectedIndex;

			this->m_SelectedIndex = 0;
		}

		Sleep( 200 );
	}

	if( utils::is_key_pressed( VK_SHIFT ) && !this->m_SelectedPrimaryName.empty() )
	{
		this->m_SelectedPrimaryName = "";

		this->m_SelectedIndex = last_primary_index;

		last_primary_index = 0;

		Sleep( 200 );
	}

	if( utils::is_key_pressed( VK_DOWN ) )
	{
		if( this->m_SelectedPrimaryName.empty() )
			this->m_SelectedIndex = this->m_SelectedIndex < primary_amount - 1
			                        ? this->m_SelectedIndex + 1
			                        : this->m_SelectedIndex;
		else
			this->m_SelectedIndex = this->m_SelectedIndex < reinterpret_cast< SettingPrimary* >( this->m_Settings.
				                        at( last_primary_index ).get() )->get_num_of_secondaries() - 1
			                        ? this->m_SelectedIndex + 1
			                        : this->m_SelectedIndex;

		Sleep( 200 );
	}

	if( utils::is_key_pressed( VK_UP ) )
	{
		if( this->m_SelectedPrimaryName.empty() )
			this->m_SelectedIndex = this->m_SelectedIndex > 0 ? this->m_SelectedIndex - 1 : this->m_SelectedIndex;
		else
			this->m_SelectedIndex = this->m_SelectedIndex > 0 ? this->m_SelectedIndex - 1 : this->m_SelectedIndex;

		Sleep( 200 );
	}

	if( utils::is_key_pressed( VK_LEFT ) )
	{
		if( !this->m_SelectedPrimaryName.empty() )
		{
			if( current_setting->get_type() == ESettingType::SET_BOOL )
				reinterpret_cast< SettingBool* >( current_setting )->set_value( false );

			if( current_setting->get_type() == ESettingType::SET_INT )
				reinterpret_cast< SettingInt* >( current_setting )->set_value(
					reinterpret_cast< SettingInt* >( current_setting )->get_value() - 1
				);

			if( current_setting->get_type() == ESettingType::SET_FLOAT )
				reinterpret_cast< SettingFloat* >( current_setting )->set_value(
					reinterpret_cast< SettingFloat* >( current_setting )->get_value() - 1.f
				);

			Sleep( 80 );
		}
	}

	if( utils::is_key_pressed( VK_RIGHT ) )
	{
		if( !this->m_SelectedPrimaryName.empty() )
		{
			if( current_setting->get_type() == ESettingType::SET_BOOL )
				reinterpret_cast< SettingBool* >( current_setting )->set_value( true );

			if( current_setting->get_type() == ESettingType::SET_INT )
				reinterpret_cast< SettingInt* >( current_setting )->set_value(
					reinterpret_cast< SettingInt* >( current_setting )->get_value() + 1
				);

			if( current_setting->get_type() == ESettingType::SET_FLOAT )
				reinterpret_cast< SettingFloat* >( current_setting )->set_value(
					reinterpret_cast< SettingFloat* >( current_setting )->get_value() + 1.f
				);

			Sleep( 80 );
		}
	}
}

void menu::on_render()
{
	constexpr auto off_x = 240;
	auto off_y = 80;

	const auto mid_w = Globals::g_pOverlay->get_overlay_width() / 2;

	const auto primary_amount = this->get_amount_of_primaries();

	// draw outline
	if( this->m_SelectedPrimaryName.empty() )
	{
		const auto height = this->m_Settings.size() * 50;

		Globals::g_pOverlay->draw_filled_rect(
			mid_w - ( off_x / 2 ) - 15,
			off_y - 50,
			off_x * 2 + 30,
			height + 30,
			255,
			255,
			120
		);
	}
	else
	{
		for( const auto& setting : this->m_Settings )
			if( setting->get_name() == this->m_SelectedPrimaryName )
			{
				const auto secondary_amount = reinterpret_cast< SettingPrimary* >( setting.get() )->
						get_num_of_secondaries();
				constexpr auto height =
						710; // this shit gettin' really late this time, so fuck the dynamic calculation and make it static :evilgrin:

				if( this->m_SelectedPrimaryName == "Player" )
					Globals::g_pOverlay->draw_filled_rect(
						mid_w - ( off_x / 2 ) - 15,
						off_y - 50,
						off_x * 2 + 30,
						height + 30,
						255,
						0,
						0
					);
				else if( this->m_SelectedPrimaryName == "Visuals" )
					Globals::g_pOverlay->draw_filled_rect(
						mid_w - ( off_x / 2 ) - 15,
						off_y - 50,
						off_x * 2 + 30,
						height + 30,
						0,
						255,
						0
					);
				else if( this->m_SelectedPrimaryName == "Entities" )
					Globals::g_pOverlay->draw_filled_rect(
						mid_w - ( off_x / 2 ) - 15,
						off_y - 50,
						off_x * 2 + 30,
						height + 30,
						255,
						120,
						130
					);
				else if (this->m_SelectedPrimaryName == "StatsEditor")
					Globals::g_pOverlay->draw_filled_rect(
						mid_w - (off_x / 2) - 15,
						off_y - 50,
						off_x * 2 + 30,
						height + 30,
						255,
						0,
						255
					);
			}
	}

	// draw header
	Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ), off_y - 40, off_x * 2, 40, 150, 150, 150 );
	Globals::g_pOverlay->draw_string( "risen-external by cragson", mid_w + ( off_x / 2 ) - 96, off_y - 30, 0, 0, 0 );

	// if no primary was selected
	if( this->m_SelectedPrimaryName.empty() )
	{
		// draw background
		Globals::g_pOverlay->draw_filled_rect(
			mid_w - ( off_x / 2 ),
			off_y,
			off_x * 2,
			primary_amount * 50 - off_y,
			200,
			200,
			200
		);

		// draw settings
		for( auto i = 0; i < this->m_Settings.size(); i++ )
		{
			const auto setting = this->m_Settings.at( i ).get();

			constexpr auto off_x_dot = 24;

			Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ), off_y, off_x * 2, 20, 140, 140, 140 );

			const auto is_selected = this->m_SelectedIndex == i;

			Globals::g_pOverlay->draw_filled_rect(
				mid_w - ( off_x / 2 ) + 5,
				off_y + 5,
				10,
				10,
				is_selected ? 255 : 200,
				is_selected ? 0 : 200,
				is_selected ? 0 : 200
			);

			Globals::g_pOverlay->draw_string( setting->get_name(), mid_w + ( off_x / 2 ) - off_x_dot, off_y, 0, 0, 0 );

			off_y = off_y + 30 < Globals::g_pOverlay->get_overlay_height()
			        ? off_y + 30
			        : Globals::g_pOverlay->get_overlay_height();
		}
	}
	else
	{
		// get selected primary
		for( auto i = 0; i < this->m_Settings.size(); i++ )
			if( this->m_Settings.at( i )->get_name() == this->m_SelectedPrimaryName )
			{
				const auto current_setting = reinterpret_cast< SettingPrimary* >( this->m_Settings.at( i ).get() );

				const auto secondary_amount = current_setting->get_num_of_secondaries();

				for( auto j = 0; j < current_setting->get_num_of_secondaries(); j++ )
				{
					const auto sec_setting = current_setting->get_secondaries_ptr()->at( j );

					/* draw background
					Globals::g_pOverlay->draw_filled_rect(
						mid_w - (off_x / 2),
						off_y,
						off_x * 2,
						secondary_amount * 21 + off_y,
						200,
						200,
						200
					);*/

					// draw settings
					constexpr auto off_x_dot = 100;

					Globals::g_pOverlay->draw_filled_rect( mid_w - ( off_x / 2 ), off_y, off_x * 2, 20, 140, 140, 140 );

					const auto is_selected = this->m_SelectedIndex == j;

					Globals::g_pOverlay->draw_filled_rect(
						mid_w - ( off_x / 2 ) + 5,
						off_y + 5,
						10,
						10,
						is_selected ? 255 : 200,
						is_selected ? 0 : 200,
						is_selected ? 0 : 200
					);

					Globals::g_pOverlay->draw_string(
						sec_setting->get_name(),
						mid_w + ( off_x / 2 ) - off_x_dot,
						off_y,
						0,
						0,
						0
					);

					if( sec_setting->get_type() == ESettingType::SET_BOOL )
						Globals::g_pOverlay->draw_string(
							std::vformat(
								"< {} >",
								std::make_format_args(
									reinterpret_cast< SettingBool* >( sec_setting )->get_value() ? "true" : "false"
								)
							),
							mid_w + ( off_x / 2 ) + 100,
							off_y,
							20,
							20,
							20
						);

					if( sec_setting->get_type() == ESettingType::SET_INT )
						Globals::g_pOverlay->draw_string(
							std::vformat(
								"< {} >",
								std::make_format_args( reinterpret_cast< SettingInt* >( sec_setting )->get_value() )
							),
							mid_w + ( off_x / 2 ) + 100,
							off_y,
							20,
							20,
							20
						);

					if( sec_setting->get_type() == ESettingType::SET_FLOAT )
						Globals::g_pOverlay->draw_string(
							std::vformat(
								"< {.2f} >",
								std::make_format_args( reinterpret_cast< SettingFloat* >( sec_setting )->get_value() )
							),
							mid_w + ( off_x / 2 ) + 100,
							off_y,
							20,
							20,
							20
						);
					const auto test = std::vformat( "{}", std::make_format_args( sec_setting->get_type_as_str() ) );
					off_y += 20;
				}
			}
	}
}
