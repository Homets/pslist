#include "pslist.h"
#include "single_process_info.c"
#include "get_process_thread.c"
#include "get_process_list.c"
#include "get_specific_process.c"



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
				GetProcessInfo();
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

		} else { 		//pslist.exe explorer
			if (!argv[2])
			{
				char *process_name = argv[1];
				GetSpecificProcess(process_name);
			}else {
				printf("  Erreur arguement \"%s\".\t Essayer pslist.exe -h pour plus d'informations", argv[2]);

			}
			
		}
		
	}else { // no argument provided
		GetProcessInfo();
	}
	return 0;
}
