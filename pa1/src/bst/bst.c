#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include<malloc.h>
struct Node {
	int val;
	struct Node* left;
	struct Node* right;
}; struct Node* newNode(int item)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->val = item;
	temp->left = temp->right = NULL;
	return temp;
}
struct Node* insertTreeNode(struct Node* head, int value) {
	if(head == NULL) {
		printf("inserted\n");
		return newNode(value);
	} 
	if (value == head->val) {
		printf("not inserted\n");
	} else if (value < head->val) {
		head->left = insertTreeNode(head->left, value);
	} else {
		head->right = insertTreeNode(head->right, value);
	}
	return head;
}
struct Node* deleteTreeNode(struct Node* head, int value) {
	if (head == NULL) {
		printf("absent\n");
		return head;
	}
	if (head->val < value) {
		head->right = deleteTreeNode(head->right, value);
	}
	else if(head->val > value){
		head->left = deleteTreeNode(head->left, value);
	}
	else {
		if (head->left == NULL && head->right == NULL) {
			free(head);
			printf("deleted\n");
			return NULL;
		}
		else if (head->left != NULL) {

			struct Node* current = head;
			while (current && current->left != NULL) {
				current = current->left;
				while(current && current->right != NULL){
					current = current->right;
				}
			}
			head->val = current->val;
			head->left = deleteTreeNode(head->left, head->val);
		}
		else{
			head->val = head->right->val;
			struct Node* temp = head->right;
			head->right = head->right->right;
			free(temp);
			printf("deleted\n");
		}
	}

	return head;
}
void searchTree(struct Node* head,int value) {
	if (head == NULL) {
		printf("absent\n");
		return;
	}
	if (head->val == value) {
		printf("present\n");
		return;
	}
	if (head->val > value) {
		searchTree(head->left, value);
	}
	else {
		searchTree(head->right, value);
	}
	return;
}
void printTree(struct Node* head) {
	if (head == NULL) {
		return;
	}
	printf("(");
	if (head->left != NULL) {
		printTree(head->left);
	}
	printf("%d",head->val);
	if (head->right != NULL) {
		printTree(head->right);
	}
	printf(")");
}
void freeTree(struct Node* head){
	if(head!=NULL){
		struct Node* left = head->left;
		struct Node* right = head->right;
		free(head);
		freeTree(left);
		freeTree(right);
	}
	return;	
}
int main(int argc, char* argv[]) {

	struct Node* tree = NULL;
	while (1) {
		char str[2];
		int value;
		if (scanf("%s", str) == EOF) {
			freeTree(tree);
			return 0;
		}
		if (str[0] == 'p') {
			printTree(tree);
			printf("\n");
			continue;
		}
		scanf(" %d", &value);
		if (str[0] == 'i') {
			if (tree == NULL) {
				tree = insertTreeNode(tree, value);
			}
			else {
				insertTreeNode(tree, value);
			}

		}
		else if (str[0] == 's') {
			searchTree(tree,value);
		}
		else if (str[0] == 'd') {
			if(tree == NULL){
				printf("absent\n");
			}
			else if (tree->val == value) {
				if (tree->left == NULL && tree->right == NULL) {
					struct Node* temp = tree;
					tree = NULL;
					free(temp);
					printf("deleted\n");
				}
				else if (tree->left != NULL) {

					struct Node* current = tree;
					while (current && current->left != NULL) {
						current = current->left;
						while(current->right != NULL){
							current = current->right;
						}	
					}
					tree->val = current->val;
					tree->left = deleteTreeNode(tree->left, tree->val);
				}
				else {
					tree->val = tree->right->val;
					struct Node* temp = tree->right;
					tree->right = tree->right->right;
					free(temp);
					printf("deleted\n");
				}

			}
			else {
				deleteTreeNode(tree, value);
			}
		}
		else {
			break;
		}
	}
	freeTree(tree);
	return 0;
}
