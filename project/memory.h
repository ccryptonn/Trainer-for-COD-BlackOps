
#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>
#include <iostream>
#include <vector>

class memory
{
public:
	size_t _module = 0;
	HANDLE pHandle = 0;
	DWORD pID = 0;
	bool Attach(const wchar_t* ProcessName, DWORD rights)
	{
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);

		do
			if (!lstrcmp(entry.szExeFile, ProcessName)) {
				pID = entry.th32ProcessID;
				CloseHandle(handle);
				pHandle = OpenProcess(rights, false, pID);
				return true;
			}
		while (Process32Next(handle, &entry));
		return false;
	}
	uintptr_t GetModule(const wchar_t* modName)
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32,
			pID);
		if (hSnap != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 modEntry;
			modEntry.dwSize = sizeof(modEntry);
			do
			{
				if (!lstrcmpW(modEntry.szModule, modName))
				{
					_module = (size_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
		CloseHandle(hSnap);
		return 0;
	}

	template <class T> T Read(const uintptr_t addr) {
		T _read;
		ReadProcessMemory(pHandle, reinterpret_cast<LPVOID>(addr), &_read, sizeof(_read), NULL);
		return _read;
	}

	template <class T> void Write(const uintptr_t addr,  T val) {
		WriteProcessMemory(pHandle, reinterpret_cast<LPVOID>(addr), &val, sizeof(T), NULL);
	}
	void Exit()
	{
		CloseHandle(pHandle);
	}
};