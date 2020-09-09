#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
int main(int argc, char *argv[]) {
	char* s1 = argv[1];
	int length = 0;
	while(s1[length] != '\0'){
	length++;
	}
	
	char* string = (char*)malloc(sizeof(char) * (length * 2 + 1));
	char* num = (char*)malloc(sizeof(char)*length);
	int stringCount = 0;
	int letterCount;
	for (int i = 0; i < length; i++) {
		if(isdigit(s1[i])){
			printf("error\n");
			free(string);
			free(num);
			return 0;
		}
		string[stringCount++] = s1[i];
		letterCount = 1;
		while (s1[i] == s1[i + 1] && i < (int)strlen(s1) - 1) {
			letterCount++;
			i++;
		}
		sprintf(num, "%d", letterCount);
		for (int j = 0; j < strlen(num); j++) {
			string[stringCount++] = num[j];
		}
	}
	string[stringCount] = '\0';
	if (strlen(s1) >= strlen(string)) {
		printf("%s", string);
	}
	else {
		printf("%s", s1);
	}
	printf("\n");
	free(string);
	free(num);
	return 0;
}
