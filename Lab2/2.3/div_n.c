#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void div_n(int n) {
	int i;
	printf("Divisor %d = ", n);
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
