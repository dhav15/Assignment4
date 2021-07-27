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

void readFile();
int resourceRequest(char *command);
int resourceRelease(char *command);
void printStatus();

int main(int argc, char *argv[]){

	printf("Number of Customers: 5\n");
	printf("Currently Available resources:");
	for (int i = 1; i < argc; i++) {
		available[i - 1] = atoi(argv[i]);
		printf(" %d", available[i - 1]);
	}
	printf("\nMaximum resources from file:\n");
	readFile();
	for (int i = 0; i < 5; i++){
		for(int j = 0; j < 4; j++){
			if(j != 3){
				printf("%c,", Max[i][j]);
			} else if(j == 3){
				printf("%c", Max[i][j]);
				printf("\n");
			}
		}
	}
	char command[20];
	while(1) {
		
		printf("Enter Command: ");
		fgets(command, 20, stdin); 
		command[strcspn(command, "\n")] = 0;
		int exit = strcmp(command, "exit");
		int RQ = strncmp(command, "RQ", 2);
		int RL = strncmp(command, "RL", 2);
		if (exit == 0){
			break;
		} else if (RQ == 0){
			resourceRequest(command);
		} else if (RL == 0) {
			resourceRelease(command);
		} else if (strncmp(command, "Status", 6) == 0) {
			printStatus();
		} else {
			printf("ERROR: Please enter valid command\n");
		}
		

	}
	return 0;
}

void readFile(){
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
}

int safetyAlgorithm(){

	return 0;
}

int resourceRequest(char *command) {
	//printf("Command: %s",command);
	//printf("\n");
	int resources[4];
	int i = 0, j, num, isAvail = 0;
	char *token = strtok(command, " ");
	if (strcmp(token, "RQ") == 0) {
		token = strtok(NULL, " ");
		num = atoi(token);
		printf("%d\n", num);
		while (token != NULL) {
			token = strtok(NULL, " ");
			resources[i] = atoi(token);
			i++;
		}
	}

	for (j = 0; j < 4; j++) {
		if (resources[j] > Max[num][j]) {
			printf("ERROR: Threads cannot request more than maximum number of resource\n");
			return -1;
		}
	}

	for (j = 0; j < 4; j++) {
		if (resources[j] > available[j]) {
			printf("ERROR: Resources are not available\n");
			//thread wait
			isAvail = 1;
		}
	}

	if (isAvail == 1) {
		for (j = 0; j < 4; j++) {
			available[j] = available[j] - resources[j];
			allocation[num][j] = allocation[num][j] + resources[j];
			need[num][j] = need[num][j] - resources[j];
		}
		printf("State is safe, and request is satisfied\n");
	}

	return 0; //if successful, else return -1
}

int resourceRelease(char *command) {
	int resources[4];
	int i = 0, j, num, isAvail = 0;
	char *token = strtok(command, " ");
	if (strcmp(token, "RL") == 0) {
		token = strtok(NULL, " ");
		num = atoi(token);
		printf("%d\n", num);
		while (token != NULL) {
			token = strtok(NULL, " ");
			resources[i] = atoi(token);
			i++;
		}
	}

	for (j = 0; j < 4; j++) {
		if (resources[j] > Max[num][j]) {
			printf("ERROR: Threads cannot request more than maximum number of resource\n");
			return -1;
		}
	}

	for (j = 0; j < 4; j++) {
		if (resources[j] > available[j]) {
			printf("ERROR: Resources are not available\n");
			//thread wait
			isAvail = 1;
		}
	}

	if (isAvail == 1) {
		for (j = 0; j < 4; j++) {
			available[j] = available[j] + resources[j];
			allocation[num][j] = allocation[num][j] - resources[j];
			need[num][j] = need[num][j] + resources[j];
		}
		printf("The resources have been released successfully\n");
	}

	return 0; //if successful, else return -1
}

void printStatus() {
	int i, j;
	printf("Available Resources:\n");
	for (i = 0; i < 4; i++) {
		printf("%d ", available[i]);
	}
	printf("\nMaximum Resources:\n");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d ", Max[i][j]);
		}
		printf("\n");
	}
	printf("Allocated Resources:\n");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d ", allocation[i][j]);
		}
		printf("\n");
	}
	printf("Need Resources:\n");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}
}
