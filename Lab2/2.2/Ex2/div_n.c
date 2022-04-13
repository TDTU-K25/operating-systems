#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main(int argc, char ** argv) {
	if (argc > 2) {
		printf("Co qua nhieu doi so\n");
	}
	else if (atoi(argv[1]) == 0){
		printf("Doi so khong phai la so nguyen\n");
	}
	else {
		int n = atoi(argv[1]);
		int i;
		printf("Cac uoc so cua %d la ", n);
		for (i = 1; i <= n; i++) {
			if (n % i == 0) {
				if (n == i) {
					printf("%d\n",i);
				}
				else
					printf("%d, ",i);
			}
		}
	}
}
