#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

int ave, max, min;

struct array {
	int a[100];
	int n;
};

void* average(void* ar) {
	int count, sum = 0;
	struct array *ap = (struct array*) ar;
	for (count = 0; count < ap->n; count++) {
		sum += ap->a[count];
	}
	ave = sum / ap->n;
}

void* maxValue(void* ar) {
	struct array *ap = (struct array*) ar;
	int count;
	max = ap->a[0];
	for (count = 1; count < ap->n; count++) {
		if (max < ap->a[count]) {
			max = ap->a[count];
		}
	}
}

void* minValue(void* ar) {
	struct array *ap = (struct array*) ar;
	int count;
	min = ap->a[0];
	for (count = 1; count < ap->n; count++) {
		if (min > ap->a[count]) {
			min = ap->a[count];
		}
	}
}

int main (int argc, char ** argv) {
	struct array ar;
	ar.n = argc - 1;
	int i;
	for (i = 1; i < argc; i++) {
		ar.a[i-1] = atoi(argv[i]);
	}
	
	pthread_t tid[3];
	pthread_create(&tid[0], NULL, average, (void*) &ar);
	pthread_create(&tid[1], NULL, maxValue, (void*) &ar);
	pthread_create(&tid[2], NULL, minValue, (void*) &ar);
	
	for (i = 0; i < 3; i++) {
		pthread_join(tid[i], NULL);
	}
	
	printf("Gia tri trung binh: %d\n", ave);
	printf("Gia tri lon nhat: %d\n", max);
	printf("Gia tri nho nhat: %d\n", min);
}
