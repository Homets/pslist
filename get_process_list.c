#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string.h>
#include <processthreadsapi.h>
#include <stdlib.h>

BOOL GetProcessInfo()
{
	
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if( hProcessSnap == INVALID_HANDLE_VALUE )
  	{
		printf("Failed to create snapshot");
    		return ( FALSE );
  	}

	//Get an entry to the each process
	PROCESSENTRY32 pe32;
	pe32.dwSize =sizeof(PROCESSENTRY32);
	
	if( !Process32First( hProcessSnap, &pe32 ) )
  	{	
		printf("error no process");
    		CloseHandle( hProcessSnap );          // clean the snapshot object
    		return( FALSE );
  	}
	_tprintf( TEXT("PID\tPPID \tPRI\tTHD\tHDN\tName"));

	do
	{	
		//Need OpenProcess to get the Number of Handles
		DWORD handleCount = 0;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS , FALSE, pe32.th32ProcessID );
		
		//TODO GERER ERREUR
		if (hProcess == NULL)
		{
		}else
		{
			GetProcessHandleCount(hProcess, &handleCount);
		}

		//Get CreationTime
		FILETIME processCreationTime;
		FILETIME processExitTime;
		FILETIME processKernelTime;
		FILETIME processUserTime;
		SYSTEMTIME creationSystemTime;
		char *cmdline = GetCommandLineA();
		if(!GetProcessTimes(hProcess, &processCreationTime, &processExitTime, &processKernelTime, &processUserTime))
		{
			printf("Error retrieving time");
		}
		FileTimeToSystemTime(&processCreationTime, &creationSystemTime);

		
		_tprintf( TEXT("\n%ld\t%d\t%d\t%ld\t%d\t%s\t%02d:%02d:%02d:%03d\t%s"),
				pe32.th32ProcessID,  		//PID
				pe32.th32ParentProcessID, 	//PPID
				pe32.pcPriClassBase,		//Priority
				pe32.cntThreads,		//Thread Number
				handleCount,			//Count of Handle
				pe32.szExeFile,
				creationSystemTime.wHour, creationSystemTime.wMinute, creationSystemTime.wSecond, creationSystemTime.wMilliseconds, cmdline);		//Executable name
		CloseHandle(hProcess);
	}while (Process32Next ( hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);

	return 0;
}
