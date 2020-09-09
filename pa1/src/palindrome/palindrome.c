#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char *argv[]) {
	char* s1 = argv[1];
	int length = 0;
	while(s1[length] != '\0'){
	length++;
	}
	char* s2=(char*)malloc(sizeof(char*)*(length+1));
	char* s3=(char*)malloc(sizeof(char*)*(length+1));
	bool palindrome = true;

	int count = 0;
	for (int i = 0; i < length; i++) {
		if ((s1[i] >= 'a' && s1[i] <= 'z') || (s1[i] >= 'A' && s1[i] <= 'Z'))  {
			s2[count] = tolower(s1[i]);
			count++;
		}
	}
	s2[count] = '\0';

	count = 0;
	for (int i = length-1; i >= 0; i--) {
		if ((s1[i] >= 'a' && s1[i] <= 'z') || (s1[i] >= 'A' && s1[i] <= 'Z')) {
			s3[count] = tolower(s1[i]);
			count++;
		}
	}
	s3[count] = '\0';
	for (int i = 0; i < sizeof(s1) - 1; i++) {
		if (s2[i] != s3[i]) {
			palindrome = false;
		}
	}
	if (palindrome) {
		printf("yes");
	}
	else {
		printf("no");
	}
	printf("\n");
	free(s2);
	free(s3);	
	return 0; 
}
