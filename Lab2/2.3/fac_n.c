#include <stdio.h>
#include <stdlib.h>
void fac_n(int n) {
	int product = 1; 
	int i;
	for (i = 1; i <= n; i++) {
		product *= i;
	}
	printf("Fac %d! = %d\n", n, product);	
}

