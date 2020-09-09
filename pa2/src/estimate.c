#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
void printMatrix(double s[], int x,int y) {
	for (int i = 0; i < x * y; i++) {
		printf("%lf ", s[i]);
		if (i % x == x - 1) {
			printf("\n");
		}
	}
}
double* multiplyM(double a[],int x1, int y1, double b[], int x2, int y2) {
	double* result = (double*)malloc((sizeof(double)) * y1 * x2);
	for (int i = 0; i < y1 * x2;i++) {
		result[i] = 0;
	}
	if (x1 != y2) {
		return NULL;
	}
	int index = 0;
	for (int i = 0; i < y1; i++) {
		for (int k = 0; k < x2; k++) {
			double temp = 0;
			for (int j = 0; j < x1; j++) {
				temp += a[j + (i * x1)] * b[x2 * j + k];
			}
			result[index++] = temp;

		}
	}
	return result;
}double* transposeM(double a[], int x1, int y1) {
	double* result = (double*)malloc((sizeof(double)) * y1 * x1);
	for (int i = 0; i < y1*x1; i++) {
			result[i] = a[i/y1+(i%y1)*x1];
	}
	return result;
}
double* inverseM(double mat[], int n) {
	
	double* result = (double*)malloc((sizeof(double)) * n * n);
	result[0] = 1;
	for (int i = 1; i < n * n; i++) {
		for (int j = 0; j < n; j++) {
			result[i++] = 0;
		}
		result[i] = 1;
	}

	for (int p = 0; p < n; p++) {
		double f = mat[p + p*n];

		for(int i = p*n; i < p*n+n; i++){
			result[i] = result[i] / f;
			mat[i] = mat[i] / f;
		}
		for (int i = p + 1; i < n; i++) {
			f = mat[p + i * n];
			for (int j = i * n; j < i * n + n; j++) {
				if (i * n == 0) {
					result[j] = result[j] - result[p * n + j ] * f;
					mat[j] = mat[j] - mat[p * n + j ] * f;
				}
				else {
					result[j] = result[j] - result[p * n + j % (i * n)] * f;
					mat[j] = mat[j] - mat[p * n + j % (i * n)] * f;
				}
			}
		}
	}

	for (int p = n - 1; p >= 0; p--) {
		for (int i = p - 1; i >= 0; i--) {
			double f = mat[i*n + p];
			
			for (int j = i * n; j < i * n + n; j++) {
				if (i * n == 0) {
					result[j] = result[j] - result[p * n + j] * f;
					mat[j] = mat[j] - mat[p * n + j] * f;
				}
				else {
					result[j] = result[j] - result[p * n + j % (i * n)] * f;
					mat[j] = mat[j] - mat[p * n + j % (i * n)] * f;
				}
			}
		}
	}

	return result;
}
int main(int argc, char* argv[]) {
		FILE* f1 = fopen(argv[1],"r");

		char train[6];
		fscanf(f1,"%s",train);
		int k[2];
		fscanf(f1,"%d", &k[0]);
		fscanf(f1,"%d", &k[1]);
		double* x = (double*)malloc((sizeof(double)) * (k[0] + 1) * k[1]);
		double* y = (double*)malloc((sizeof(double)) * k[1]);
		int xIndex = 1;
		int yIndex = 0;

		x[0] = 1;
		int i = 0;
		while (i < ((k[0] + 1) * k[1]) - 1) {
			if (i % (k[0] + 1) == k[0]) {
				fscanf(f1,"%lf", &y[yIndex++]);
				x[xIndex++] = 1;
			}
			else {
				fscanf(f1,"%lf", &x[xIndex++]);
			}
			i++;
		}
		fscanf(f1,"%lf", &y[yIndex]);

		FILE* f2 = fopen(argv[2],"r");
		char data[5];
		fscanf(f2,"%s",data);
		int a[2];
		fscanf(f2,"%d", &a[0]);
		fscanf(f2,"%d", &a[1]);
		int j = 0;
		double* testData = (double*)malloc((sizeof(double)) * (a[0] * a[1]+a[1]));
		while (j < (a[0]) * a[1] + a[1]) {
			if (j % (a[0]+1) == 0) {
				testData[j++] = 1;
			}
			else {
				fscanf(f2,"%lf", &testData[j++]);
			}
		}
	
	
	 
	double* xT = transposeM(x,k[0]+1,k[1]);
	double* w = multiplyM(xT,k[1],k[0]+1,x,k[0]+1,k[1]);
	
	double* temp = w;
	w = inverseM(w,k[0]+1);
	free(temp);
	double* temp2 = w;
	w = multiplyM(w,k[0]+1,k[0]+1,xT,k[1],k[0]+1);
	free(temp2);
	double* temp3 = w;
	w = multiplyM(w,k[1],k[0]+1,y,1,k[1]);
	free(temp3);
	free(xT);	
	/* w = (multiplyM(multiplyM(inverseM(multiplyM(transposeM(x, k[0] + 1, k[1]), k[1], k[0] + 1, x, k[0] + 1, k[1]), k[0] + 1),k[0]+1, k[0] + 1, transposeM(x, k[0] + 1, k[1]), k[1], k[0] + 1), k[1], k[0] + 1, y, 1, k[1]));
	*/

	
	
	 
	double* finalAnswer = (multiplyM(testData, a[0]+1, a[1], w, 1, k[0]+1));
	for (int k = 0; k < a[1]; k++) {
		printf("%.0f\n", finalAnswer[k]);
	}

	free(x);
	free(y);
	free(w);
	free(finalAnswer);
	free(testData);
	return 0;
}
