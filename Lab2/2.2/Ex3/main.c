#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void interchangeSort(int arr[], int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (arr[i] > arr[j]) {
				swap(&arr[i], &arr[j]);
			}
		}
	}
}

void selectionSort(int arr[], int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		swap(&arr[i],&arr[minIndex]);
		}
	}
}

void bubbleSort(int arr[], int n) {
	int i, j;
	for (i = 0; i < n; i++) {   
        for (j = 0; j < n - 1 - i; j++) { 
            if (arr[j] > arr[j + 1]) {  
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}

void printArray(int arr[], int n) {
	int i;
	printf("Day tang la: ");
	for(i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}

void main(int argc, char ** argv) {
	int i;
	int count = 0;
	for (i = 0; i < argc; i++) {
		if (atoi(argv[i]) != 0) {
			count++;
		}
	}
	int n = count;
	int arr[n];
	int j, k = 0;
	for (j = 0; j < argc; j++) {
		if (atoi(argv[j]) != 0) {
			arr[k] = atoi(argv[j]);
			k++;
		}
		else {
			continue;
		}
	}
	interchangeSort(arr, n);
	//selectionSort(arr, n);
	//bubbleSort(arr, n);
	printArray(arr, n);
	printf("\n");
}
