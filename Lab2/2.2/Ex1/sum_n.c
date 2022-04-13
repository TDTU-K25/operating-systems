#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main(int argc, char ** argv) {
	if (argc > 2) {
		printf("Co qua nhieu doi so\n");
	}
	else if (atoi(argv[1]) <= 0){
		printf("Doi so khong phai la so nguyen duong\n");
	}
	else {
		int n = atoi(argv[1]);
		int sum = 0; 
		int i;
		for (i = 1; i <= n; i++) {
			sum += i;
		}
		printf("S = %d\n", sum);
	}
}
