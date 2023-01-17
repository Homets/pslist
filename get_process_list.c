#include "pslist.h"

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
	pe32.dwSize = sizeof(PROCESSENTRY32);
	
	if( !Process32First( hProcessSnap, &pe32 ) )
  	{	
		printf("error no process");
    		CloseHandle( hProcessSnap );          // clean the snapshot object
    		return( FALSE );
  	}
	_tprintf( TEXT("PID\tPPID \tPRI\tTHD\tHDN\tMemory Size\t\tName\tCreation Time\n"));

	do
	{	
		bool error_access = 1;
		//Need OpenProcess to get the Number of Handles
		DWORD handleCount = 0;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS , FALSE, pe32.th32ProcessID );
		
		//TODO GERER ERREUR
		if (hProcess == NULL)
		{	
			error_access = 0;
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
		if(!GetProcessTimes(hProcess, &processCreationTime, &processExitTime, &processKernelTime, &processUserTime))
		{
			//printf("Error retrieving time");
		}
		FileTimeToSystemTime(&processCreationTime, &creationSystemTime);
		

		//Get Memory virtual information
		PROCESS_MEMORY_COUNTERS ppsmemscounters;

		if (!GetProcessMemoryInfo(hProcess, &ppsmemscounters, sizeof(ppsmemscounters)))
		{
			
		}		
		
		if (error_access)
		{
			_tprintf( TEXT("%ld\t%d\t%d\t%ld\t%d\t%zuKb\t\t%s\t%02d:%02d:%02d:%03d\n"),
				pe32.th32ProcessID,  			//PID
				pe32.th32ParentProcessID, 		//PPID
				pe32.pcPriClassBase,			//Priority
				pe32.cntThreads,			//Thread Number
				handleCount,				//Count of Handle
				ppsmemscounters.WorkingSetSize / 1000, 	//Working set size
				pe32.szExeFile,				//Executable name
				creationSystemTime.wHour, creationSystemTime.wMinute, creationSystemTime.wSecond, creationSystemTime.wMilliseconds);		//Creation Time
		}else
		{
			        _tprintf( TEXT("%ld\t%d\t%d\t%ld\t%s\t%s\t\t%s\t%s\n"),
                                	pe32.th32ProcessID,
                                	pe32.th32ParentProcessID,
                                	pe32.pcPriClassBase,
                                	pe32.cntThreads,
                                	ERROR_PROCESS_ACCESS,
                                	ERROR_PROCESS_ACCESS,
                                	pe32.szExeFile,
                                	ERROR_TIME_ACCESS);        
		}
		CloseHandle(hProcess);

	}while (Process32Next ( hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);

	return 0;
}
