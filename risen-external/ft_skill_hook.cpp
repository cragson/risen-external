#include "ft_skill_hook.hpp"

#include "globals.hpp"
#include "offsets.hpp"

#include <algorithm>

void ft_skill_hook::on_first_activation()
{
	this->m_original.resize( 5 );

	if( !ReadProcessMemory(
		Globals::g_pProcess->get_process_handle(),
		reinterpret_cast< LPCVOID >( Offsets::skill_hook ),
		this->m_original.data(),
		5 * sizeof( uint8_t ),
		nullptr
	) )
	{
		printf( "[!] Could not read the original bytes @ skill hook address.\n" );

		ExitProcess( 0xABBA1 );
	}

	const auto ret = Globals::g_pProcess->create_register_dumper_x86( Offsets::skill_hook );

	if( ret )
		printf( "[+] RegisterDumper was successfully created!\n" );
	else
	{
		printf( "[!] Could not create the RegisterDumper!\n" );

		this->disable();
	}
}

void ft_skill_hook::tick()
{
	const auto reg_data = Globals::g_pProcess->get_data_from_registers_x86( Offsets::skill_hook );

	const auto is_active = Globals::g_pProcess->is_active_register_dumper_x86( Offsets::skill_hook );

	if( reg_data != nullptr && is_active )
	{
		/*printf("[+] Dumped Registers from: 0x%08X\n", Offsets::skill_hook);

		printf("EAX -> 0x%08X\n", reg_data->EAX.eax);
		printf("\tAX -> 0x%04X\n", reg_data->EAX.ax);
		printf("\tAH, AL -> 0x%02X, 0x%02X\n", reg_data->EAX.a[0], reg_data->EAX.a[1]);

		printf("EBX -> 0x%08X\n", reg_data->EBX.ebx);
		printf("\tBX -> 0x%04X\n", reg_data->EBX.bx);
		printf("\tBH, BL -> 0x%02X, 0x%02X\n", reg_data->EBX.b[0], reg_data->EBX.b[1]);

		printf("ECX -> 0x%08X\n", reg_data->ECX.ecx);
		printf("\tCX -> 0x%04X\n", reg_data->ECX.cx);
		printf("\tCH, CL -> 0x%02X, 0x%02X\n", reg_data->ECX.c[0], reg_data->ECX.c[1]);

		printf("EDX -> 0x%08X\n", reg_data->EDX.edx);
		printf("\tDX -> 0x%04X\n", reg_data->EDX.dx);
		printf("\tDH, DL -> 0x%02X, 0x%02X\n", reg_data->EDX.d[0], reg_data->EDX.d[1]);

		printf("ESP -> 0x%08X\n", reg_data->ESP.esp);
		printf("\tSP -> 0x%04X\n", reg_data->ESP.sp);

		printf("EBP -> 0x%08X\n", reg_data->EBP.ebp);
		printf("\tBP -> 0x%04X\n", reg_data->EBP.bp);

		printf("ESI -> 0x%08X\n", reg_data->ESI.esi);
		printf("\tSI -> 0x%04X\n", reg_data->ESI.si);

		printf("EDI -> 0x%08X\n", reg_data->EDI.edi);
		printf("\tDI -> 0x%04X\n", reg_data->EDI.di);
		*/

		const std::uintptr_t ent_ptr = reg_data->ESI.esi;

		if( std::ranges::none_of(
			this->m_esi_ptr,
			[&ent_ptr]( const std::uintptr_t ptr )
			{
				return ptr == ent_ptr;
			}
		) )
		{
			this->m_esi_ptr.push_back( ent_ptr );

			printf( "[+] Found new skill ptr: 0x%08X\n", ent_ptr );
		}
	}
}

void ft_skill_hook::on_enable()
{
	if( !Globals::g_pProcess->is_active_register_dumper_x86( Offsets::skill_hook ) )
		if( Globals::g_pProcess->start_register_dumper_x86( Offsets::skill_hook ) )
			printf( "[+] RegisterDumper was started!\n" );
		else
			printf( "[!] Could not start the RegisterDumper!\n" );

	Globals::g_pProcess->nop_bytes( Offsets::skill_hook + 11, 4 );
}

void ft_skill_hook::on_disable()
{
	//const auto ret = Globals::g_pProcess->destroy_hook_x86( Offsets::skill_hook );

	const auto ret = Globals::g_pProcess->stop_register_dumper_x86( Offsets::skill_hook );

	if( ret )
		printf( "[+] RegisterDumper was stopped!\n" );
	else
		printf( "[!] Could not stop the RegisterDumper!\n" );

	Globals::g_pProcess->write_to_protected_memory< uint32_t >( Offsets::skill_hook + 11, 0x10AE7C89 );
}

void ft_skill_hook::on_shutdown() {}
