#include <stdio.h>
#include <stdlib.h>
void sum_n(int n) {
	int sum = 0; 
	int i;
	for (i = 1; i <= n; i++) {
		sum += i;
	}
	printf("Sum %d = %d\n", n, sum);
}

