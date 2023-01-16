#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include "single_process_info.c"
#include "process_thread_info.c"

typedef int bool;



int main(int argc, char *argv[])
{	

	bool show_user = 0;

	if (argc > 1)
	{	
		if (strcmp(argv[1], "-h") == 0) 	//pslist.exe -h
		{
			printf("Usage => jfjfkf");

		} else if (strcmp(argv[1],"-u") == 0) 	//pslist.exe -u username
		{
			show_user = 1;
			if (!argv[2])
			{
				printf("L'option -u nécessitede renseigner un nom d'utilisateur");
			} else
			{
				const char *username = argv[2];
				GetProcessInfo(username);
			}

		}else if (strcmp(argv[1], "--module") == 0) 	//pslist.exe -p 105
		{
			if (!argv[2])
                        {
                                printf("L'option --module nécessite de renseigner un PID");
                        } else
                        {
				unsigned int processId = atoi(argv[2]);
				if (processId != 0)
				{
                                	singleProcessInfo(processId);
				} else
				{
					printf("Erreur au niveau du PID");
				}
                        }			
		}else if (strcmp(argv[1], "-p") == 0)
		{
			if (!argv[2])
			{
				printf("L'option -p nécessite de renseigner un PID");

			} else
			{
				unsigned int processId = atoi(argv[2]);
				if (processId != 0)
				{
					processThreadInfo(processId);
				}else
				{
					printf("Erreur au niveau du PID");
				}

			}

		}
		
	}else // no argument provided
	{
		GetProcessInfo();
	}
	return 0;
}

BOOL GetProcessInfo(const char *username)
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

		//Get KernelTime and UserTime
		FILETIME processCreationTime;
		FILETIME processExitTime;
		FILETIME processKernelTime;
		FILETIME processUserTime;
		SYSTEMTIME creationSystemTime;
			

		if(!GetProcessTime(hProcess, &processCreationTime, &processExitTime, &processKernelTime, &processUserTime))
		{
			
			printf("Error retrieving time");
		}

		FileTimeToSystemTime(&processCreationTime, &creationSystemTime);

		



		_tprintf( TEXT("\n%ld\t%d\t%d\t%ld\t%d\t%s\t%02d:%02d:%02d:%03d"),
				pe32.th32ProcessID,  		//PID
				pe32.th32ParentProcessID, 	//PPID
				pe32.pcPriClassBase,		//Priority
				pe32.cntThreads,		//Thread Number
				handleCount,			//Count of Handle
				pe32.szExeFile,
				creationSystemTime.wHour, creationSystemTime.wMinute, creationSystemTime.wSecond, creationSystemTime.wMilliseconds);		//Executable name
		CloseHandle(hProcess);
	}while (Process32Next ( hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);

	return 0;
}
