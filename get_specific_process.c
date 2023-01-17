void delete_exe_char(char * process_name)
{

	int size = 0;
	for(int i = 0; i < strlen(process_name) - 3;i++)
	{	
		size++;
		printf("%c\n", process_name[i]);
	}

}


BOOL GetSpecificProcess(char * process_name)
{

    	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	char *extension = ".exe";
        strcat(process_name,extension);
        if( hProcessSnap == INVALID_HANDLE_VALUE )
  	    {
		    printf("Failed to create snapshot");
    		return ( FALSE );
  	    }

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (!Process32First(hProcessSnap, &pe32))
        {
            printf("error no process");
            CloseHandle( hProcessSnap );          // clean the snapshot object
            return( FALSE );

        }
        _tprintf("PID\tPPID \tPRI\tTHD\tHDN\tMemory Size\t\tName\tCreation Time\n");
        
        do 
        {
           	bool error_access = 1;
            	DWORD handleCount = 0;
         	
		if ()
		{

		} 	
		
				

        }while(Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);

}
