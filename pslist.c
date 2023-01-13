#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <time.h>
#include <processthreadsapi.h>
int main(int argc, char *argv[])
{



	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

	if( hProcessSnap == INVALID_HANDLE_VALUE )
  	{
		printf("Failed to create snapshot");
    		return ( FALSE );
  	}


	PROCESSENTRY32 pe32;
	pe32.dwSize =sizeof(PROCESSENTRY32);
	_tprintf( TEXT("PID\tPPID \tPRI\tTHD\tHDN\tName"));

	if( !Process32First( hProcessSnap, &pe32 ) )
  	{	
		printf("error no process");
    		CloseHandle( hProcessSnap );          // clean the snapshot object
    		return( FALSE );
  	}

	do
	{	

		//Need OpenProcess to get the Number of Handles
		DWORD handleCount = 0;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS , FALSE, pe32.th32ProcessID );
		
		//ProcessTime

		//TODO GERER ERREUR
		if (hProcess == NULL)
		{
		}else
		{

			GetProcessHandleCount(hProcess, &handleCount);
		}
		_tprintf( TEXT("\n%ld\t%d\t%d\t%ld\t%d\t%s"),pe32.th32ProcessID,pe32.th32ParentProcessID, pe32.pcPriClassBase,pe32.cntThreads, handleCount, pe32.szExeFile);

	}while (Process32Next ( hProcessSnap, &pe32));

}
