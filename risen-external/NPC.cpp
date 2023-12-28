#include "NPC.h"

#include "globals.hpp"

std::uintptr_t NPC::get_last_npc_ptr() const
{
    return Globals::g_pProcess->read< std::uintptr_t >(this->m_ptr + offsetof(NPC_t, m_pLastCreature));
}

std::uintptr_t NPC::get_next_npc_ptr() const
{
    return Globals::g_pProcess->read< std::uintptr_t >(this->m_ptr + offsetof(NPC_t, m_pNextCreature));
}

EntityClasses_NPC NPC::get_entity_classes() const
{
    return Globals::g_pProcess->read< EntityClasses_NPC >(this->m_ptr + offsetof(NPC_t, m_pEntityClasses));
}
