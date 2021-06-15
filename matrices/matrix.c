#include <stdlib.h>
#include <stdio.h>
#include "matrix.h" 

void mx_free(TMatrix *m) {
	if (m != NULL)
		if (m->a != NULL) {
			free(m->a);
			free(m);
		}
}

void mx_print(TMatrix *m) {
	unsigned int i, j;

	if (m != NULL) {
		if (m->a != NULL) {
			for (i = 0; i < m->m; i++) {
				for (j = 0; j < m->n; j++)
					printf("%8.2lf", m->a[i * m->n + j]);
				printf("\n");
			}
		}
	}
}



int mx_det(TMatrix* m) {
	int x;
	if (m->m == 3 && m->n == 3) {
		x = m->a[0] * m->a[4] * m->a[8] + m->a[1] * m->a[5] * m->a[6] + m->a[2] * m->a[3] * m->a[7] - m->a[0] * m->a[5] * m->a[7] - m->a[1] * m->a[3] * m->a[8] - m->a[2] * m->a[4] * m->a[6];
		printf("%d", x);
		return x;
	}
	printf("Det is calculated only for 3x3 matrix\n");
	return -1;
}