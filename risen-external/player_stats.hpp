#pragma once
#include <cstdint>


class PlayerStats
{
public:
	PlayerStats()
		: m_player_stats_ptr( std::uintptr_t() ) {}

	[[nodiscard]] bool initialize_stats_ptr() noexcept;

	[[nodiscard]] bool is_stats_ptr_valid() const noexcept
	{
		return this->m_player_stats_ptr;
	}

	[[nodiscard]] bool synchronize_stats();

	[[nodiscard]] int32_t get_Health() noexcept;
	void set_Health( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Mana() noexcept;
	void set_Mana( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Experience() noexcept;
	void set_Experience( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_HealthMaximum() noexcept;
	void set_HealthMaximum( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_ManaMaximum() noexcept;
	void set_ManaMaximum( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Strength() noexcept;
	void set_Strength( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Dexterity() noexcept;
	void set_Dexterity( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Wisdom() noexcept;
	void set_Wisdom( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_BladeProtection() noexcept;
	void set_BladeProtection( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_BluntProtection() noexcept;
	void set_BluntProtection( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_PiercingProtection() noexcept;
	void set_PiercingProtection( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_FireProtection() noexcept;
	void set_FireProtection( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_IceProtection() noexcept;
	void set_IceProtection( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_MagicProtection() noexcept;
	void set_MagicProtection( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_SwordFighting() noexcept;
	void set_SwordFighting( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_AxeFighting() noexcept;
	void set_AxeFighting( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_StaffCombat() noexcept;
	void set_StaffCombat( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Archery() noexcept;
	void set_Archery( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Crossbow() noexcept;
	void set_Crossbow( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_RuneSeal() noexcept;
	void set_RuneSeal( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Fireball() noexcept;
	void set_Fireball( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Frost() noexcept;
	void set_Frost( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_MagicBullet() noexcept;
	void set_MagicBullet( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Smithing() noexcept;
	void set_Smithing( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Prospecting() noexcept;
	void set_Prospecting( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Lockpicking() noexcept;
	void set_Lockpicking( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Pickpocket() noexcept;
	void set_Pickpocket( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Sneak() noexcept;
	void set_Sneak( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Acrobatics() noexcept;
	void set_Acrobatics( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_Alchemy() noexcept;
	void set_Alchemy( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_CreateScrolls() noexcept;
	void set_CreateScrolls( int32_t value ) noexcept;

	[[nodiscard]] int32_t get_GutAnimals() noexcept;
	void set_GutAnimals( int32_t value ) noexcept;

private:
	std::uintptr_t m_player_stats_ptr;
};
