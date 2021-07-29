#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#define MAX 100
int x = 0;
int y = 0;
int Max[5][4];
int Avalibe[MAX];

//Run with make runq1

void resourceRequest(char *command);

int main(int argc, char* argv[]){
    	//Get input array 
    	int one_dArray[39]= {0};

    	int i;
    	int count = 0;
    	for (i = 1; i < (argc); i++)
    	{
        Avalibe[i] = atoi(argv[i]);
    	}
	//Read file
	FILE *fp;
	fp = fopen("sample4_in.txt","r");
	struct stat st;
	fstat(fileno(fp), &st);
	char *fileContent = (char*) malloc(((int) st.st_size + 1) * sizeof(char));
	fileContent[0] = '\0';
	while (!feof(fp)) {
		count++;
		char line[100];
		if (fgets(line, 100, fp) != NULL) {
			strncat(fileContent, line, strlen(line));
		}
			

	}
	int j =0;
	for(int i = 0; i < 39; i = i +2){
		one_dArray[j++] = fileContent[i];
	}
	
	memcpy(Max, one_dArray, 20 * sizeof(int)); 
	
	
	//Use to view max array structure
	/*for(i=0; i<5; i++)
	   for(j=0; j<4; j++)
	      printf("bla[%d][%d] = %c\n",i,j,Max[i][j]);
	*/

	

	
	//Print start menu
	printf("Currentlly Alvaible resources: %d %d %d %d\n",Avalibe[1],Avalibe[2],Avalibe[3],Avalibe[4]); 
	printf("Number of customers: 5\n");
	printf("Maximum resources from file:\n");
	
	for(i=0; i<5; i++){
	   for(j=0; j<4; j++){
	      if(j != 3){ 
	      	printf("%c,",Max[i][j]);
	      }
	      else if(j == 3){
	      	printf("%c",Max[i][j]);
	      	printf("\n");
	      	}
	      }
	}	

	

	
	char command[20];
	while(1){
		
		printf("Enter Command: ");
		fgets(command, 20, stdin); 
		command[strcspn(command, "\n")] = 0;
		int exit = strcmp(command, "exit");
		int RQ = strncmp(command, "RQ", 1);
		if(exit == 0){
			break;
		}
		else if(RQ == 0){
			resourceRequest(command);
		}

	}
	
	
}



void resourceRequest(char *command){

	printf("Command: %s",command );
	printf("\n");


}





	



