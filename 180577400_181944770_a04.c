/* 
 * ----------------------------------------------
 * Authors:
 *    Name:       Dhavani Patel
 *    Student ID: 180577400
 *    GitHub ID:  @dhav15
 *    Name:       Judy Praught
 *    Student ID: 181944770
 *    GitHub ID:  @Judy-Praught
 * URL: https://github.com/dhav15/Assignment4
 * ----------------------------------------------
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <ctype.h>

int available[5];
int Max[5][4];
int allocation[5][4];
int need[5][4];
int safeSeq[5];

void readFile();
int safetyAlgorithm();
int resourceRequest(char *command);
int resourceRelease(char *command);
void printStatus();
void run();
void *runner(void *param);

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

		if (strcmp(command, "Exit") == 0){
			break;
		} else if (strncmp(command, "RQ", 2) == 0){
			resourceRequest(command);
		} else if (strncmp(command, "RL", 2) == 0) {
			resourceRelease(command);
		} else if (strncmp(command, "Status", 6) == 0) {
			printStatus();
		} else if (strncmp(command, "Run", 3) == 0) {
			run();
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
	for (int i = 0; i < 39; i = i +2){
		one_dArray[j++] = fileContent[i];
	}

	memcpy(Max, one_dArray, 20 * sizeof(int));
}

int safetyAlgorithm(){
	int work[4], finish[5];
	int i, j, k, x = 0;
	for (i = 0; i < 4; i++) {
		work[i] = available[i];
	}
	for (j = 0; j < 5; j++) {
		finish[j] = 0;
	}
	while (x < 5) {
		for (i = 0; i < 5; i++) {
			if (finish[i] == 0) {
				for (j = 0; j < 4; j++) {
					if (need[i][j] > work[j]) {
						break;
					}
				}
				if (j == 4) {
					safeSeq[x] = i;
					for (k = 0; k < 4; k++) {
						work[k] += allocation[i][k];
					}
					finish[i] = 1;
					x++;
				}

			}
		}
	}
	return 0;
}

int resourceRequest(char *command) {

	char resources[4];
	int num;
	int success = 0;

	num = (command[3] - '0');
	int j = 0;
	for( int i = 0; i < 18; i++){
		if( i > 3 && isdigit(command[i])){
			resources[j] = (command[i] - '0');
			j++;

		}
	}
	for (j = 0; j < 4; j++) {
		if (resources[j] > available[j]) {
			printf("ERROR: Resources are not available\n");
			success = -1;
			break;
		}
		else if ((resources[j]) > (Max[num][j] - '0')) {
			printf("ERROR: Threads cannot request more than maximum number of resource\n");
			success = -1;
			break;
		}

	}

	if (success == 0) {
		for (j = 0; j < 4; j++) {
			available[j] = available[j] - resources[j];
			allocation[num][j] = allocation[num][j] + resources[j];
			need[num][j] = (Max[num][j] - '0') - allocation[num][j];
		}
		if (safetyAlgorithm() == 0)
			printf("State is safe, and request is satisfied\n");
	}

	return success; //return 0 if successful, else return -1
}

int resourceRelease(char *command) {

	char resources[4];
	int num;
	int success = 0;

	num = (command[3] - '0');
	int i, j = 0;
	for (i = 0; i < 18; i++) {
		if (i > 3 && isdigit(command[i])) {
			resources[j] = (command[i] - '0');
			j++;
		}
	}

	for (i = 0; i < 4; i++){
		if (resources[i] <= allocation[num][i]){
			available[i] = available[i] + resources[i];
			allocation[num][i] = allocation[num][i] - resources[i];
			need[num][i] = (Max[num][i] - '0') + allocation[num][i];
		} else {
			printf("ERROR: Cannot release unaquired resource\n");
			success = -1;
			break;
		}
	}

	if (success == 0 && safetyAlgorithm() == 0)
		printf("The resources have been released successfully\n");

	return success; //return 0 if successful, else return -1
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
			printf("%d ", (Max[i][j]-'0'));
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

void run() {
	int i;
	printf("Safe Sequence is:");
	for (i = 0; i < 5; i++) {
		printf(" %d", safeSeq[i]);
	}
	for (i = 0; i < 5; i++) {
		pthread_t tid;
		pthread_create(&tid, NULL, runner, (void*)&(safeSeq[i]));
		pthread_join(tid, NULL);
	}
	memset(allocation, 0, sizeof(allocation[0][0]) * 5 * 4);
	memset(need, 0, sizeof(need[0][0]) * 5 * 4);
	printf("\n");
}

void *runner(void *param) {
	int j;
	int* i = (int*)param;
	printf("\n--> Customer/Thread %d\n", *i);
	printf("    Allocated resources: ");
	for (j = 0; j < 4; j++) {
		printf(" %d", allocation[*i][j]);
	}
	printf("\n    Needed: ");
	for (j = 0; j < 4; j++) {
		printf(" %d", need[*i][j]);
	}
	printf("\n    Available: ");
	for (j = 0; j < 4; j++) {
		printf(" %d", available[j]);
	}
	printf("\n    Thread has started\n");
	printf("    Thread has finished\n");
	printf("    Thread is releasing resources\n");
	printf("    New Available: ");
	for (j = 0; j < 4; j++) {
		available[j] += allocation[*i][j];
		printf(" %d", available[j]);
	}
	pthread_exit(0);
	return NULL;
}
