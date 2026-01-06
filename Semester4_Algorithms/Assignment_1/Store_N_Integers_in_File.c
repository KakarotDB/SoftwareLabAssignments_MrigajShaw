#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main() {
	//variable declaration zone 
	int value;
	int n = 0;
	int *array = NULL;
	FILE *file = NULL;
	printf("Enter value of n : ");
	scanf("%d", &n);
	array = (int *) malloc(n * sizeof(int));
	if(array == NULL) {
		printf("[ERROR] Malloc malfunctioned");
		return -1;
	}
	srand(time(NULL));
	for(int i = 0; i < n; i++) {
		array[i] = rand();		
	}
	file = fopen("numbers.txt", "w");
	if(file == NULL) {
		printf("[ERROR] Couldn't write to file!");
		fclose(file);
		return -2;
	}
	for(int i = 0; i < n; i++) {
		fprintf(file, "%d ", *(array + i));
	}
	fprintf(file, "\n");
	printf("Successfully wrote to file numbers.txt!\n");
	fclose(file);
	file = fopen("numbers.txt", "r");
	if(file == NULL) {
		printf("[ERROR] Couldn't read file!");
		fclose(file);
		return -3;
	}
	printf("Reading from file numbers.txt : \n");
	for(int i = 0; i < n ;i++) {
		if(fscanf(file, "%d ", &value) == 1) {
			printf("%d ", value);
		}
		else {
			printf("\n");
		}
	}
	printf("\n");
	fclose(file);
	return 0;
}

