#include "player_stats.hpp"

#include "globals.hpp"

bool PlayerStats::initialize_stats_ptr() noexcept
{
	const auto player = Globals::g_IEntities->get_local_player();

	const auto ptr1 = Globals::g_pProcess->read< std::uintptr_t >( player + 0x1C );

	if( !ptr1 )
		return false;

	const auto ptr2 = Globals::g_pProcess->read< std::uintptr_t >( ptr1 + 0x3C );

	if( !ptr2 )
		return false;

	this->m_player_stats_ptr = ptr2;

	return true;
}

bool PlayerStats::synchronize_stats()
{
	if( !this->m_player_stats_ptr )
		return false;

	const auto Health = this->get_Health();
	const auto Mana = this->get_Mana();
	const auto Experience = this->get_Experience();
	const auto HealthMaximum = this->get_HealthMaximum();
	const auto ManaMaximum = this->get_ManaMaximum();
	const auto Strength = this->get_Strength();
	const auto Dexterity = this->get_Dexterity();
	const auto Wisdom = this->get_Wisdom();
	const auto BladeProtection = this->get_BladeProtection();
	const auto BluntProtection = this->get_BluntProtection();
	const auto PiercingProtection = this->get_PiercingProtection();
	const auto FireProtection = this->get_FireProtection();
	const auto IceProtection = this->get_IceProtection();
	const auto MagicProtection = this->get_MagicProtection();
	const auto SwordFighting = this->get_SwordFighting();
	const auto AxeFighting = this->get_AxeFighting();
	const auto StaffCombat = this->get_StaffCombat();
	const auto Archery = this->get_Archery();
	const auto Crossbow = this->get_Crossbow();
	const auto RuneSeal = this->get_RuneSeal();
	const auto Fireball = this->get_Fireball();
	const auto Frost = this->get_Frost();
	const auto MagicBullet = this->get_MagicBullet();
	const auto Smithing = this->get_Smithing();
	const auto Prospecting = this->get_Prospecting();
	const auto Lockpicking = this->get_Lockpicking();
	const auto Pickpocket = this->get_Pickpocket();
	const auto Sneak = this->get_Sneak();
	const auto Acrobatics = this->get_Acrobatics();
	const auto Alchemy = this->get_Alchemy();
	const auto CreateScrolls = this->get_CreateScrolls();
	const auto GutAnimals = this->get_GutAnimals();

	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Health", Health );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Mana", Mana );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Experience", Experience );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "HealthMaximum", HealthMaximum );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "ManaMaximum", ManaMaximum );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Strength", Strength );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Dexterity", Dexterity );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Wisdom", Wisdom );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "BladeProtection", BladeProtection );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "BluntProtection", BluntProtection );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "PiercingProtection", PiercingProtection );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "FireProtection", FireProtection );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "IceProtection", IceProtection );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "MagicProtection", MagicProtection );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "SwordFighting", SwordFighting );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "AxeFighting", AxeFighting );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "StaffCombat", StaffCombat );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Archery", Archery );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Crossbow", Crossbow );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "RuneSeal", RuneSeal );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Fireball", Fireball );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Frost", Frost );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "MagicBullet", MagicBullet );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Smithing", Smithing );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Prospecting", Prospecting );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Lockpicking", Lockpicking );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Pickpocket", Pickpocket );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Sneak", Sneak );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Acrobatics", Acrobatics );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "Alchemy", Alchemy );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "CreateScrolls", CreateScrolls );
	Globals::g_pMenu->set_value_of_setting< int32_t >( "StatsEditor", "GutAnimals", GutAnimals );

	return true;
}

int32_t PlayerStats::get_Health() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x10 );
}

void PlayerStats::set_Health( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x10, value );
}

int32_t PlayerStats::get_Mana() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x14 );
}

void PlayerStats::set_Mana( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x14, value );
}

int32_t PlayerStats::get_Experience() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x1c );
}

void PlayerStats::set_Experience( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x1c, value );
}

int32_t PlayerStats::get_HealthMaximum() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x24 );
}

void PlayerStats::set_HealthMaximum( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x24, value );
}

int32_t PlayerStats::get_ManaMaximum() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x28 );
}

void PlayerStats::set_ManaMaximum( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x28, value );
}

int32_t PlayerStats::get_Strength() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x2c );
}

void PlayerStats::set_Strength( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x2c, value );
}

int32_t PlayerStats::get_Dexterity() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x30 );
}

void PlayerStats::set_Dexterity( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x30, value );
}

int32_t PlayerStats::get_Wisdom() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x34 );
}

void PlayerStats::set_Wisdom( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x34, value );
}

int32_t PlayerStats::get_BladeProtection() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x38 );
}

void PlayerStats::set_BladeProtection( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x38, value );
}

int32_t PlayerStats::get_BluntProtection() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x3c );
}

void PlayerStats::set_BluntProtection( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x3c, value );
}

int32_t PlayerStats::get_PiercingProtection() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x40 );
}

void PlayerStats::set_PiercingProtection( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x40, value );
}

int32_t PlayerStats::get_FireProtection() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x44 );
}

void PlayerStats::set_FireProtection( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x44, value );
}

int32_t PlayerStats::get_IceProtection() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x48 );
}

void PlayerStats::set_IceProtection( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x48, value );
}

int32_t PlayerStats::get_MagicProtection() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x4c );
}

void PlayerStats::set_MagicProtection( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x4c, value );
}

int32_t PlayerStats::get_SwordFighting() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x50 );
}

void PlayerStats::set_SwordFighting( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x50, value );
}

int32_t PlayerStats::get_AxeFighting() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x54 );
}

void PlayerStats::set_AxeFighting( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x54, value );
}

int32_t PlayerStats::get_StaffCombat() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x58 );
}

void PlayerStats::set_StaffCombat( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x58, value );
}

int32_t PlayerStats::get_Archery() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x5c );
}

void PlayerStats::set_Archery( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x5c, value );
}

int32_t PlayerStats::get_Crossbow() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x60 );
}

void PlayerStats::set_Crossbow( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x60, value );
}

int32_t PlayerStats::get_RuneSeal() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x64 );
}

void PlayerStats::set_RuneSeal( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x64, value );
}

int32_t PlayerStats::get_Fireball() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x68 );
}

void PlayerStats::set_Fireball( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x68, value );
}

int32_t PlayerStats::get_Frost() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x6c );
}

void PlayerStats::set_Frost( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x6c, value );
}

int32_t PlayerStats::get_MagicBullet() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x70 );
}

void PlayerStats::set_MagicBullet( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x70, value );
}

int32_t PlayerStats::get_Smithing() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x74 );
}

void PlayerStats::set_Smithing( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x74, value );
}

int32_t PlayerStats::get_Prospecting() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x78 );
}

void PlayerStats::set_Prospecting( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x78, value );
}

int32_t PlayerStats::get_Lockpicking() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x7c );
}

void PlayerStats::set_Lockpicking( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x7c, value );
}

int32_t PlayerStats::get_Pickpocket() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x80 );
}

void PlayerStats::set_Pickpocket( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x80, value );
}

int32_t PlayerStats::get_Sneak() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x84 );
}

void PlayerStats::set_Sneak( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x84, value );
}

int32_t PlayerStats::get_Acrobatics() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x88 );
}

void PlayerStats::set_Acrobatics( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x88, value );
}

int32_t PlayerStats::get_Alchemy() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x8c );
}

void PlayerStats::set_Alchemy( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x8c, value );
}

int32_t PlayerStats::get_CreateScrolls() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x90 );
}

void PlayerStats::set_CreateScrolls( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x90, value );
}

int32_t PlayerStats::get_GutAnimals() noexcept
{
	return Globals::g_pProcess->read< int32_t >( this->m_player_stats_ptr + 0x94 );
}

void PlayerStats::set_GutAnimals( const int32_t value ) noexcept
{
	Globals::g_pProcess->write< int32_t >( this->m_player_stats_ptr + 0x94, value );
}
