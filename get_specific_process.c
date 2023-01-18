void delete_exe_char(char *process_name)
{
    printf("%s", process_name);
}


BOOL GetSpecificProcess(char * process_name)
{

	//Create a boolean to check if the process exist => This will be useful for create error message if process doesn't exist
	bool process_exist = 0;

	//Taking a snapshot of all process
    	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
        if( hProcessSnap == INVALID_HANDLE_VALUE )
  	    {
		    printf("Failed to create snapshot");
    		return ( FALSE );
  	    }
	
	
	char *extension = ".exe";
	strcat(process_name,extension);

	//Check if a process active exist
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (!Process32First(hProcessSnap, &pe32))
        {
            printf("error no process");
            CloseHandle( hProcessSnap );          // clean the snapshot object
            return( FALSE );

        }
       
        do 
        {
            	if(strcmp(pe32.szExeFile, process_name) == 0)
		{
		bool error_access = 1;
		process_exist = 1;
		//Need OpenProcess to get the Number of Handles
		DWORD handleCount = 0;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS , FALSE, pe32.th32ProcessID );
		
		//Erreur d'accè
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
		_tprintf("PID\tPPID \tPRI\tTHD\tHDN\tMemory Size\tName\tCreation Time\n");
		if (error_access)
		{
			_tprintf( TEXT("%ld\t%d\t%d\t%ld\t%d\t%zuKb\t%s\t%02d:%02d:%02d:%03d\n"),
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
		break;
		}

        }while(Process32Next(hProcessSnap, &pe32));
	
	if (process_exist == 0)
	{
		printf("Il n'y a pas de process portant ce nom");
	}

        CloseHandle(hProcessSnap);
	return ( TRUE );

}
