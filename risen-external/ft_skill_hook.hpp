#pragma once
#include "osmium/Cheat/Feature/feature.hpp"

class ft_skill_hook : public feature
{
public:
	void on_first_activation() override;

	void on_render() override {}

	void tick() override;

	void on_enable() override;
	void on_disable() override;
	void on_shutdown() override;

private:
	std::vector< uint8_t > m_original;

	std::vector< std::uintptr_t > m_esi_ptr;
};
