#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;


extern BOOL singleProcessInfo(DWORD processID);


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
				printf("Veuillez renseigner un utilisateur avec l'option -u");
			} else
			{
				const char *username = argv[2];
				GetProcessInfo(username);
			}

		}else if (strcmp(argv[1], "--module") == 0) 	//pslist.exe -p 105
		{
			if (!argv[2])
                        {
                                printf("Veuillez renseigner un process avec l'option -u");
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

		_tprintf( TEXT("\n%ld\t%d\t%d\t%ld\t%d\t%s"),pe32.th32ProcessID,pe32.th32ParentProcessID, pe32.pcPriClassBase,pe32.cntThreads, handleCount, pe32.szExeFile);
		CloseHandle(hProcess);
	}while (Process32Next ( hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);

	return 0;
}
