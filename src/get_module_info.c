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
		CloseHandle(hModSnap);
		return ( FALSE );
	}
	if (!Module32First(hModSnap, &me32))
	{
		CloseHandle(hModSnap);
		return ( FALSE );
	}
	//get information about the process
	printf("Name\t\t\tSize\n");
	do
	{
		_tprintf( TEXT("%s\t\t%d\n"), me32.szModule,me32.modBaseSize);
	} while (Module32Next(hModSnap, &me32));
	
	CloseHandle(hModSnap);
	return ( TRUE );
}
