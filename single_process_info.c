#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string.h>


BOOL singleProcessInfo(DWORD processID)
{

	HANDLE hModSnap;
	MODULEENTRY32 me32;
	me32.dwSize = sizeof( MODULEENTRY32 );
	//GET a snapshot of a specific process
	hModSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,processID);
	if (hmodSnap == INVALID_HANDLE_VALUE)
	{
		printf("Error retrieve information about Process");
	}
	
	do
	{
	} while ()

}
