#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>

BOOL singleProcessInfo(DWORD processID)
{
	HANDLE hModSnap;
	MODULEENTRY32 me32;
	me32.dwSize = sizeof( MODULEENTRY32 );

	//GET a snapshot of a specific process
	hModSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,processID);
	if (hModSnap == INVALID_HANDLE_VALUE)
	{
		printf("Le PID n'existe pas ou vous n'avez pas les droits suffisant");
	}
	if (!Module32First(hModSnap, &me32))
	{
		CloseHandle(hModSnap);
	}
	//get information about the process
	do
	{
		_tprintf( TEXT("\n\n     MODULE NAME:     %s"),   me32.szModule );
    		_tprintf( TEXT("\n     Executable     = %s"),     me32.szExePath );
    		_tprintf( TEXT("\n     Process ID     = 0x%08X"),         me32.th32ProcessID );
    		_tprintf( TEXT("\n     Ref count (g)  = 0x%04X"),     me32.GlblcntUsage );
		_tprintf( TEXT("\n     Ref count (p)  = 0x%04X"),     me32.ProccntUsage );
	} while (Module32Next(hModSnap, &me32));
	
	CloseHandle(hModSnap);
	return ( FALSE );
}
