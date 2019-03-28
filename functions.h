#pragma once
#include <TlHelp32.h>

inline uintptr_t get_module_base_address(const DWORD proc_id, const wchar_t* mod_name)
{
	uintptr_t mod_base_addr = 0;
	const auto h_snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc_id);
	if (h_snap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(h_snap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, mod_name))
				{
					mod_base_addr = reinterpret_cast<uintptr_t>(modEntry.modBaseAddr);
					break;
				}
			} while (Module32Next(h_snap, &modEntry));
		}
	}
	CloseHandle(h_snap);
	return mod_base_addr;
}

inline uintptr_t get_process_id(const wchar_t* proc)
{
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	auto pe = PROCESSENTRY32{ sizeof(PROCESSENTRY32) };
	if (Process32First(snapshot, &pe)) {
		do {
			if (!_tcscmp(proc, pe.szExeFile)) {
				CloseHandle(snapshot);
				return pe.th32ProcessID;
			}
		} while (Process32Next(snapshot, &pe));
	}
	CloseHandle(snapshot);
	return 0;
}
