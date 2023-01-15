#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>



BOOL processThreadInfo(DWORD processID)
{

	HANDLE hThreadSnapshot;
	THREADENTRY32 te32;
	te32.dwSize = sizeof(THREADENTRY32 );

	// get snapshot and check error
	hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processID);
	
	if (hThreadSnapshot == INVALID_HANDLE_VALUE)
	{
		printf("Invalid processID");
		return ( FALSE );
	}

	if (!Thread32First(hThreadSnapshot, &te32))
	{
		printf("Thread error");
		CloseHandle(hThreadSnapshot);
		return ( FALSE );
	}

	//display information
	do
	{
		
		_tprintf( TEXT("%d\t\t%ld"), te32.th32ThreadID, );


	} while(Thread32Next(hThreadSnapshot, &te32));


	CloseHandle(hThreadSnaoshot);
	return (TRUE );

}
