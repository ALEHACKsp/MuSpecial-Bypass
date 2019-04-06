#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include "functions.h"

constexpr auto m_rva = 0x127C7;

int main()
{
	uintptr_t m_address = 0x0;
	DWORD process_id = 0;
	HANDLE h_process = nullptr;
	BYTE m_jmp_integrity_crc[2] = {0xEB, 0x23};

	SetConsoleTitle(L"MHP UserMode AntiCheat");
	std::cout << "------------------------------------------\n";
	std::cout << "------------- Info / Feature -------------\n";
	std::cout << "------------------------------------------\n\n";
	std::cout << "- Disabled checking CRC integrity\n";
	std::cout << "- You can modify the MHPClient all you want\n\n";
	std::cout << "------------------------------------------\n";
	std::cout << "           Author: Define#5696\n";
	std::cout << "------------------------------------------";
	while (!process_id)
	{
		process_id = static_cast<DWORD>(get_process_id(L"main.exe"));
		Sleep(1);
	}
	while (!m_address)
	{
		m_address = get_module_base_address(process_id, L"main.dll");
		Sleep(1);
	}
	h_process = OpenProcess(MAXIMUM_ALLOWED, 0, process_id);
	m_address = get_module_base_address(process_id, L"main.dll") + m_rva;
	WriteProcessMemory(h_process, reinterpret_cast<PVOID>(m_address), m_jmp_integrity_crc, 2, nullptr);
	CloseHandle(h_process);
	getchar();
	return 0;
}
