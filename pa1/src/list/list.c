#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
struct Node {
	int val;
	struct Node* next;
};
struct Node* insertNode(struct Node* head, int value) {
	if (head == NULL) {
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->val = value;
		newNode->next = NULL;
		return newNode;
	}
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->val = value;
	struct Node* curr = head;
	struct Node* prev = NULL;
	while (curr != NULL && curr->val < value) {
		prev = curr;
		curr = curr->next;
	}
	if(curr != NULL && curr->val == value){
	free(newNode);
	return head;
	}
	if (prev == NULL) {
		newNode->next = head;
		return newNode;
	}
	newNode->next = curr;
	prev->next = newNode;
	return head;
}

struct Node* deleteNode(struct Node* head, int value) {
	if (head == NULL) {
		return NULL;
	}
	struct Node* curr = head;
	struct Node* prev = NULL;
	while (curr != NULL && curr->val != value) {
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL) {
		prev->next = NULL;
		return head;
	}
	if (prev == NULL) {
		head = curr->next;
		free(curr);
		return head;
	}
	prev->next = curr->next;
	free(curr);
	return head;
}
int printList(struct Node* head) {
	if(head == NULL){
	printf("0 :\n");
	return 0;
	}
	struct Node* curr = head;
	int count = 0;
	while (curr != NULL) {
		count++;
		curr = curr->next;
	}
	printf("%d", count);
	printf(" : ");
	curr = head;
	while (curr->next != NULL) {
		printf("%d", curr->val);
		printf(" ");
		curr = curr->next;
	}
	printf("%d", curr->val);
	printf("\n");
	return 0;
}
int main(int argc, char *argv[]) {
	
	struct Node* head = NULL;
	int closer = 1;
	while (closer) {		
		char str[2];
		int value;
		if(scanf("%s %d", str, &value) == EOF){
			break;
		}
		if (str[0] == 'i') {
			head = insertNode(head, value);
		}
		else if (str[0] == 'd') {
			head = deleteNode(head, value);
		}
		else {
			break;
		}
		printList(head);
	}
	struct Node* curr = head;
	struct Node* prev = curr;
	while(curr != NULL){
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	return 0;
}
