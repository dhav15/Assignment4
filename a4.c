/*
 * Authors: Dhavani Patel (@dhav15) & Judy Praught (@Judy-Praught)
 * URL:
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

int available[5];
int Max[5][4];
int allocation[5][4];
int need[5][4];

int readFile();

int main(int argc, char *argv[]){

	printf("Number of Customers: 5\n");
	printf("Currently Available resources:");
	for (int i = 1; i < argc; i++) {
		available[i - 1] = atoi(argv[i]);
		printf(" %d", available[i - 1]);
	}
	printf("\nMaximum resources from file:\n");
	readFile();
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 4; j++){
			if(j != 3){
				printf("%c,", Max[i][j]);
			} else if(j == 3){
				printf("%c", Max[i][j]);
				printf("\n");
			}
		}
	}
	printf("Enter Command: ");
	return 0;
}

int readFile(){
	//Get input array
    	int one_dArray[39]= {0};
	int count = 0;
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
	int j = 0;
	for(int i = 0; i < 39; i = i +2){
		one_dArray[j++] = fileContent[i];
	}

	memcpy(Max, one_dArray, 20 * sizeof(int));
	return 0;
}

int safetyAlgorithm(){

	return 0;
}

int resourceRequest() {

	return 0; //if successful, else return -1
}

int resourceRelease() {

	return 0;
}
