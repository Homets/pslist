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

	//GET SNAPSHOT
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
	
	//Display information
	printf("TID\tPRI\tCreation Time\n");
	do
	{
		HANDLE hThread;
                hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);		

		//Get CreationTime
        	FILETIME threadCreationTime;
        	FILETIME threadExitTime;
        	FILETIME threadKernelTime;
        	FILETIME threadUserTime;
		SYSTEMTIME userSystemTime;
        	SYSTEMTIME creationSystemTime;
		SYSTEMTIME kernelSystemTime;


        if (!GetThreadTimes(hThread,&threadCreationTime, &threadExitTime, &threadKernelTime, &threadUserTime))
        {
		
        }
	FileTimeToSystemTime(&threadCreationTime, &creationSystemTime);
	FileTimeToSystemTime(&threadKernelTime, &kernelSystemTime);
	FileTimeToSystemTime(&threadUserTime, &userSystemTime);


		_tprintf( TEXT("%d\t%ld\t%02d:%02d:%02d:%03d\t%02d:%02d:%02d:%03d\t%02d:%02d:%02d:%03d\n"),
 		te32.th32ThreadID, 			// TID
		te32.tpBasePri,				//Priority
		creationSystemTime.wHour, creationSystemTime.wMinute, creationSystemTime.wSecond,creationSystemTime.wMilliseconds,
		kernelSystemTime.wHour, kernelSystemTime.wMinute, kernelSystemTime.wSecond, kernelSystemTime.wMilliseconds,
		userSystemTime.wHour, userSystemTime.wMinute, userSystemTime.wSecond, userSystemTime.wMilliseconds);



	} while(Thread32Next(hThreadSnapshot, &te32));


	CloseHandle(hThreadSnapshot);
	return (TRUE );

}
