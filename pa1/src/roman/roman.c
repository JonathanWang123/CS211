
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char *s = argv[1];
	int num = atoi(s);
	for (int i = 0; i < num / 1000; i++) {
		printf("M");
	}
	num = num % 1000;
	if (num / 100 == 9) {
		printf("CM");
		num -= 900;
	}
	else if (num / 100 >= 5) {
		printf("D");
		num -= 500;
	}
	else if (num / 100 == 4) {
		printf("CD");
		num -= 400;
	}
	for (int i = 0; i < num / 100; i++) {
		printf("C");
	}
	num = num % 100;
	if (num / 10 == 9) {
		printf("XC");
		num -= 90;
	}
	else if (num / 10 >= 5) {
		printf("L");
		num -= 50;
	}
	else if (num / 10 == 4) {
		printf("XL");
		num -= 40;
	}
	for (int i = 0; i < num / 10; i++) {
		printf("X");
	}
	num = num % 10;
	if (num == 9) {
		printf("IX");
		num -= 9;
	}
	else if (num >= 5) {
		printf("V");
		num -= 5;
	}
	else if (num == 4) {
		printf("IV");
		num -= 4;
	}
	for (int i = 0; i < num; i++) {
		printf("I");
	}
	printf("\n");
	return 0;
}
