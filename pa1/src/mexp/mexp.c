#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
void printMatrix(int s[],int k) {
	for (int i = 0; i < k*k; i++) {
		printf("%d", s[i]);
		if (i % k == k-1) {
			printf("\n");
		} else{
			printf(" ");
		}
	}
}
int* multiplyM(int a[], int b[], int k) {
	int* result = (int*)malloc((sizeof(int)) * k * k);
	for (int i = 0; i < k * k; i++) {
		int temp = 0;
		for (int j = 0; j < k; j++) {
			temp += a[j+(i/k)*k] * b[k * j + i%k];
		}
		result[i] = temp;
	}
	return result;
}
int main(int argc, char* argv[]) {
	FILE* f = fopen(argv[1], "r");
	int k[1];
	fscanf(f,"%d", k);

	int* s = (int*)malloc((sizeof(int)) * k[0] * k[0]);
	int i = 0;
	while (i < k[0]*k[0] && fscanf(f,"%d", &s[i++]) == 1);
	int n[1];
	fscanf(f,"%d", n);

	if (n[0] <= 1) {
		printMatrix(s, k[0]);
		return 0;
	}
	int* ans = multiplyM(s, s, k[0]);
	for (int i = 0; i < n[0]-2; i++) {
		int* temp = ans;
		ans = multiplyM(temp, s, k[0]);	
		free(temp);
	}
	printMatrix(ans,k[0]);
	free(s);
	free(ans);
	return 0;
}
