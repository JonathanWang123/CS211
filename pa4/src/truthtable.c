#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>

struct queueNode {
	char* string;
	struct queueNode* next;
};
struct queueNode* newQueueNode(char* string) {
	struct queueNode* temp = (struct queueNode*)malloc(sizeof(struct queueNode));
	temp->string = string;
	temp->next = NULL;
	return temp;
}
struct queueNode* enqueue(struct queueNode* head, char* string) {
	if (head == NULL) {
		return newQueueNode(string);;
	}
	struct queueNode* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newQueueNode(string);
	return head;
}
struct queueNode* dequeue(struct queueNode* head, char* string) {
	if (head == NULL) {
		return NULL;
	}
	struct queueNode* temp = head;
	struct queueNode* prev = NULL;
	while (temp != NULL && strcmp(temp->string, string) != 0) {
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) {
		return NULL;
	}
	if (prev == NULL) {
		return head->next;
	}
	else {
		prev->next = temp->next;
	}
	return head;
}
void printQueue(struct queueNode* head) {
	struct queueNode* temp = head;
	while (temp != NULL) {
		printf("%s\n", temp->string);
		temp = temp->next;
	}
	return;
}
struct multiplexNode {
	int val;
	struct multiplexNode* next;
};
struct multiplexNode* newMultiplexNode(int val) {
	struct multiplexNode* temp = (struct multiplexNode*)malloc(sizeof(struct multiplexNode));
	temp->val = val;
	temp->next = NULL;
	return temp;
}
struct multiplexNode* addToMultiplexList(struct multiplexNode* head, int val) {
	if (head == NULL) {
		return newMultiplexNode(val);
	}
	struct multiplexNode* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newMultiplexNode(val);
	return head;
}
typedef enum { Output, Input, Temp } varType;
struct listNode {
	char* name;
	varType type;
	int val;
	struct listNode* next;
};
struct listNode* newListNode(char* name, varType type, int val) {
	struct listNode* temp = (struct listNode*)malloc(sizeof(struct listNode));
	temp->name = name;
	temp->type = type;
	temp->val = val;
	temp->next = NULL;
	return temp;
}
struct listNode* addToList(struct listNode* head, char* name, varType type, int val) {
	if (head == NULL) {
		return newListNode(name, type, val);
	}
	struct listNode* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newListNode(name, type, val);
	return head;
}
struct listNode* searchList(struct listNode* head, char* name) {
	struct listNode* temp = head;
	while (strcmp(temp->name, name) != 0 && temp->next != NULL) {
		temp = temp->next;
	}
	if (strcmp(temp->name, name) == 0) {
		return temp;
	}
	return NULL;
}
void printList(struct listNode* head) {
	struct listNode* temp = head;
	while (temp->next != NULL) {
		printf("%s : %d \n", temp->name, temp->val);
		temp = temp->next;
	}
	printf("%s : %d \n", temp->name, temp->val);
	return;
}
char* unknownStringSize(FILE* fp) {
	int len_max = 1;

	char* inputs = malloc(len_max);
	int cur_size_inputs = len_max;
	if (inputs != NULL) {
		int c = EOF;
		int i = 0;
		while ((c = fgetc(fp)) != '\n' && (c) != ' ' && c != EOF) {
			inputs[i++] = (char)c;
			if (i == cur_size_inputs)
			{
				cur_size_inputs = i + len_max;
				inputs = realloc(inputs, cur_size_inputs);
			}
		}
		inputs[i] = '\0';
	}
	return inputs;
}
char* unknownLineSize(FILE* fp) {
	int len_max = 1;

	char* inputs = malloc(len_max);
	int cur_size_inputs = len_max;
	if (inputs != NULL) {
		int c = fgetc(fp);
		int i = 0;
		while (c != '\n' && c != EOF) {
			inputs[i++] = (char)c;
			if (i == cur_size_inputs)
			{
				cur_size_inputs = i + len_max;
				inputs = realloc(inputs, cur_size_inputs);
			}
		}
	
		inputs[i] = '\0';
	}
	return inputs;
}
int getLength(char* str) {
	int count = 0;
	while (str[count] != '\0') {
		count++;
	}
	return count;
}
void runGates(struct listNode* head,struct queueNode* queueHead) {
	struct queueNode* temp = queueHead;
	while (temp != NULL) {
		char* str = malloc(getLength(temp->string));
		strcpy(str, temp->string);
		char* typing = strtok(str, " ");
		if (strcmp(typing, "AND") == 0) {
			char* input1 = strtok(NULL, " ");
			char* input2 = strtok(NULL, " ");
			char* output = strtok(NULL, " ");

			struct listNode* input1Node = searchList(head, input1);
			struct listNode* input2Node = searchList(head, input2);
			struct listNode* outputNode = searchList(head, output);


			if ((input1Node == NULL && strcmp(input1,"1") != 0 && strcmp(input1, "0") != 0) || (input2Node == NULL && strcmp(input2, "0") != 0 && strcmp(input2, "0") != 0)) {
				struct queueNode* temp2 = temp;
				temp = temp->next;
				queueHead = dequeue(queueHead, temp2->string);
				queueHead = enqueue(queueHead, temp2->string);
				continue;
			}

			if ((strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) && (strcmp(input2, "0") == 0 && strcmp(input2, "0") == 0)) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, atoi(input1) && atoi(input2));
				}
				else {
					outputNode->val = atoi(input1) && atoi(input2);
				}
			}
			else if (strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, atoi(input1) && input2Node->val);
				}
				else {
					outputNode->val = atoi(input1) && input2Node->val;
				}
			}
			else if(strcmp(input2, "1") == 0 && strcmp(input2, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, input1Node->val && atoi(input2));
				}
				else {
					outputNode->val = input1Node->val && atoi(input2);
				}
			}
			if (outputNode == NULL) {
				addToList(head, output, Temp, input1Node->val && input2Node->val);
			}
			else {
				outputNode->val = input1Node->val && input2Node->val;
			}
		}
		else if (strcmp(typing, "OR") == 0) {
			char* input1 = strtok(NULL, " ");
			char* input2 = strtok(NULL, " ");
			char* output = strtok(NULL, " ");

			struct listNode* input1Node = searchList(head, input1);
			struct listNode* input2Node = searchList(head, input2);
			struct listNode* outputNode = searchList(head, output);


			if ((input1Node == NULL && strcmp(input1, "1") != 0 && strcmp(input1, "0") != 0) || (input2Node == NULL && strcmp(input2, "0") != 0 && strcmp(input2, "0") != 0)) {
				
				struct queueNode* temp2 = temp;
				temp = temp->next;
				queueHead = dequeue(queueHead, temp2->string);
				queueHead = enqueue(queueHead, temp2->string);
				continue;
			}
			if ((strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) && (strcmp(input2, "0") == 0 && strcmp(input2, "0") == 0)) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, atoi(input1) || atoi(input2));
				}
				else {
					outputNode->val = atoi(input1) || atoi(input2);
				}
			}
			else if (strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, atoi(input1) || input2Node->val);
				}
				else {
					outputNode->val = atoi(input1) || input2Node->val;
				}
			}
			else if (strcmp(input2, "1") == 0 && strcmp(input2, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, input1Node->val || atoi(input2));
				}
				else {
					outputNode->val = input1Node->val || atoi(input2);
				}
			}
			if (outputNode == NULL) {
				addToList(head, output, Temp, input1Node->val || input2Node->val);
			}
			else {
				outputNode->val = input1Node->val || input2Node->val;
			}
		}
		else if (strcmp(typing, "NAND") == 0) {
			char* input1 = strtok(NULL, " ");
			char* input2 = strtok(NULL, " ");
			char* output = strtok(NULL, " ");

			struct listNode* input1Node = searchList(head, input1);
			struct listNode* input2Node = searchList(head, input2);
			struct listNode* outputNode = searchList(head, output);

			if ((input1Node == NULL && strcmp(input1, "1") != 0 && strcmp(input1, "0") != 0) || (input2Node == NULL && strcmp(input2, "0") != 0 && strcmp(input2, "0") != 0)) {
				struct queueNode* temp2 = temp;
				temp = temp->next;
				queueHead = dequeue(queueHead, temp2->string);
				queueHead = enqueue(queueHead, temp2->string);
				continue;
			}
			if ((strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) && (strcmp(input2, "0") == 0 && strcmp(input2, "0") == 0)) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, !(atoi(input1) && atoi(input2)));
				}
				else {
					outputNode->val = !(atoi(input1) && atoi(input2));
				}
			}
			else if (strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, !(atoi(input1) && input2Node->val));
				}
				else {
					outputNode->val = !(atoi(input1) && input2Node->val);
				}
			}
			else if (strcmp(input2, "1") == 0 && strcmp(input2, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, !(input1Node->val && atoi(input2)));
				}
				else {
					outputNode->val = !(input1Node->val && atoi(input2));
				}
			}
			if (outputNode == NULL) {
				addToList(head, output, Temp, !(input1Node->val && input2Node->val));
			}
			else {
				outputNode->val = !(input1Node->val && input2Node->val);
			}
		}
		else if (strcmp(typing, "NOR") == 0) {
			char* input1 = strtok(NULL, " ");
			char* input2 = strtok(NULL, " ");
			char* output = strtok(NULL, " ");

			struct listNode* input1Node = searchList(head, input1);
			struct listNode* input2Node = searchList(head, input2);
			struct listNode* outputNode = searchList(head, output);


			if ((input1Node == NULL && strcmp(input1, "1") != 0 && strcmp(input1, "0") != 0) || (input2Node == NULL && strcmp(input2, "0") != 0 && strcmp(input2, "0") != 0)) {
				struct queueNode* temp2 = temp;
				temp = temp->next;
				queueHead = dequeue(queueHead, temp2->string);
				queueHead = enqueue(queueHead, temp2->string);
				continue;
			}
			if ((strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) && (strcmp(input2, "0") == 0 && strcmp(input2, "0") == 0)) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, !(atoi(input1) || atoi(input2)));
				}
				else {
					outputNode->val = !(atoi(input1) || atoi(input2));
				}
			}
			else if (strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, !(atoi(input1) || input2Node->val));
				}
				else {
					outputNode->val = !(atoi(input1) || input2Node->val);
				}
			}
			else if (strcmp(input2, "1") == 0 && strcmp(input2, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, !(input1Node->val || atoi(input2)));
				}
				else {
					outputNode->val = !(input1Node->val || atoi(input2));
				}
			}
			if (outputNode == NULL) {
				addToList(head, output, Temp, !(input1Node->val || input2Node->val));
			}
			else {
				outputNode->val = !(input1Node->val || input2Node->val);
			}
		}
		else if (strcmp(typing, "XOR") == 0) {
			char* input1 = strtok(NULL, " ");
			char* input2 = strtok(NULL, " ");
			char* output = strtok(NULL, " ");

			struct listNode* input1Node = searchList(head, input1);
			struct listNode* input2Node = searchList(head, input2);
			struct listNode* outputNode = searchList(head, output);

			if ((input1Node == NULL && strcmp(input1, "1") != 0 && strcmp(input1, "0") != 0) || (input2Node == NULL && strcmp(input2, "0") != 0 && strcmp(input2, "0") != 0)) {
				struct queueNode* temp2 = temp;
				temp = temp->next;
				queueHead = dequeue(queueHead, temp2->string);
				queueHead = enqueue(queueHead, temp2->string);
				continue;
			}
			if ((strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) && (strcmp(input2, "0") == 0 && strcmp(input2, "0") == 0)) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, (atoi(input1) != atoi(input2)));
				}
				else {
					outputNode->val = (atoi(input1) != atoi(input2));
				}
			}
			else if (strcmp(input1, "1") == 0 && strcmp(input1, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, (atoi(input1) != input2Node->val));
				}
				else {
					outputNode->val = (atoi(input1) != input2Node->val);
				}
			}
			else if (strcmp(input2, "1") == 0 && strcmp(input2, "0") == 0) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, (input1Node->val != atoi(input2)));
				}
				else {
					outputNode->val = (input1Node->val != atoi(input2));
				}
			}
			int val = (input1Node->val != input2Node->val);
			if (outputNode == NULL) {
				addToList(head, output, Temp, val);
			}
			else {
				outputNode->val = val;
			}
		}
		else if (strcmp(typing, "DECODER") == 0) {
			int sum = 0;
			char* numIns = strtok(NULL, " ");
			int n = atoi(numIns);
			for (int i = 0; i < n; i++) {
				char* in = strtok(NULL, " ");
				
				struct listNode* inNode = searchList(head, in);
				if (inNode == NULL && strcmp(in, "1") != 0 && strcmp(in, "0") != 0) {
					struct queueNode* temp2 = temp;
					temp = temp->next;
					queueHead = dequeue(queueHead, temp2->string);
					queueHead = enqueue(queueHead, temp2->string);
					continue;
				}
				if (strcmp(in, "1") == 0 || strcmp(in, "0") == 0) {
					sum += atoi(in) * pow(2, n - i - 1);
				}
				else {
					sum += inNode->val * pow(2, n - i - 1);
				}
				
			}
			for (int i = 0; i < pow(2,n); i++) {
				char* out = strtok(NULL, " ");

				struct listNode* outNode = searchList(head, out);
				if (i == sum) {
					if (outNode == NULL) {
						addToList(head, out, Temp, 1);
					}
					else {
						outNode->val = 1;
					}
				}
				else {
					if (outNode == NULL) {
						addToList(head, out, Temp, 0);
					}
					else {
						outNode->val = 0;
					}
				}
			}
		}
		else if (strcmp(typing, "MULTIPLEXER") == 0) {
			int sum = 0;
			char* numIns = strtok(NULL, " ");
			int n = atoi(numIns);
			struct multiplexNode* multiHead = NULL;
			for (int i = 0; i < pow(2, n); i++) {
				
				char* in = strtok(NULL, " ");

				struct listNode* inNode = searchList(head, in);
				if (inNode == NULL && strcmp(in, "1") != 0 && strcmp(in, "0") != 0) {
					struct queueNode* temp2 = temp;
					temp = temp->next;
					queueHead = dequeue(queueHead, temp2->string);
					queueHead = enqueue(queueHead, temp2->string);
					continue;
				}
				if (strcmp(in, "1") == 0 || strcmp(in, "0") == 0) {
					multiHead = addToMultiplexList(multiHead, atoi(in));
				}
				else {
					multiHead = addToMultiplexList(multiHead, inNode->val);
				}
			}
			for (int i = 0; i < n; i++) {
				char* out = strtok(NULL, " ");

				struct listNode* outNode = searchList(head, out);
				if (strcmp(out, "1") == 0 || strcmp(out, "0") == 0) {
					sum += atoi(out) * pow(2, n - i - 1);
				}
				else {
					
					sum += outNode->val * pow(2, n - i - 1);
				}
			}
			struct multiplexNode* temp = multiHead;
			for (int i = 0; i < pow(2, n)-sum-1; i++) {
				temp = temp->next;
			}
			
			char* output = strtok(NULL, " ");
			struct listNode* outputNode = searchList(head, output);
			if (outputNode == NULL) {
				addToList(head, output, Temp, temp->val);
			}
			else {
				outputNode->val = temp->val;
			}
		}
		else if (strcmp(typing, "PASS") == 0) {
			char* input1 = strtok(NULL, " ");
			char* output = strtok(NULL, " ");

			struct listNode* input1Node = searchList(head, input1);
			struct listNode* outputNode = searchList(head, output);

			if ((input1Node == NULL && (atoi(input1) != 1 && atoi(input1) != 0))) {
				struct queueNode* temp2 = temp;
				temp = temp->next;
				queueHead = dequeue(queueHead, temp2->string);
				queueHead = enqueue(queueHead, temp2->string);
				continue;
			}
			if ((atoi(input1) == 1 || atoi(input1) == 0) ) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, (atoi(input1)));
				}
				else {
					outputNode->val = (atoi(input1));
				}
			}
			if (outputNode == NULL) {
				addToList(head, output, Temp, input1Node->val);
			}
			else {
				outputNode->val = input1Node->val;
			}
		}
		else if (strcmp(typing, "NOT") == 0) {
			char* input1 = strtok(NULL, " ");
			char* output = strtok(NULL, " ");

			struct listNode* input1Node = searchList(head, input1);
			struct listNode* outputNode = searchList(head, output);

			if ((input1Node == NULL && (atoi(input1) != 1 && atoi(input1) != 0))) {
				struct queueNode* temp2 = temp;
				temp = temp->next;
				queueHead = dequeue(queueHead, temp2->string);
				queueHead = enqueue(queueHead, temp2->string);
				continue;
			}
			if ((atoi(input1) == 1 || atoi(input1) == 0)) {
				if (outputNode == NULL) {
					addToList(head, output, Temp, !(atoi(input1)));
				}
				else {
					outputNode->val = !(atoi(input1));
				}
			}
			if (outputNode == NULL) {
				addToList(head, output, Temp, !input1Node->val);
			}
			else {
				outputNode->val = !input1Node->val;
			}
		}
		temp = temp->next;
	}
	
	return;
}
void printTable(int n, struct listNode* head, struct listNode* temp, struct queueNode* queueHead) {
	if (temp == NULL) {
		temp = head;
	}
	if (n == 0) {
		runGates(head,queueHead);
		struct listNode* temp = head;
		while (temp != NULL) {
			if (temp->type == Input) {
				printf("%d ", temp->val);

			}
			temp = temp->next;
		}
		printf("| ");
		struct listNode* temp2 = head;
		while (temp2 != NULL) {
			if (temp2->type == Output) {
				printf("%d ", temp2->val);

			}
			temp2 = temp2->next;
		}
		printf("\n");
		return;
	}
	while (temp->type != Input && temp->next != NULL) {
		temp = temp->next;
	}
	temp->val = 0;
	printTable(n - 1,head, temp->next,queueHead);
	temp->val = 1;
	printTable(n - 1,head, temp->next,queueHead);
	return;
}

int main(int argc, char* argv[]) {
	FILE* f1 = fopen(argv[1], "r");
	char typing[8];
	int numInputs = 0;
	struct listNode* head = NULL;
	for (int line = 0; line < 2; line++) {
		fscanf(f1,"%s", typing);
		if (strcmp(typing, "INPUT") == 0) {
			fscanf(f1,"%d ", &numInputs);
			for (int i = 0; i < numInputs; i++) {
				char* name = unknownStringSize(f1);
				head = addToList(head, name, Input, 0);
			}
		}
		if (strcmp(typing, "OUTPUT") == 0) {
			int numOutputs = 0;
			fscanf(f1,"%d ", &numOutputs);
			for (int i = 0; i < numOutputs; i++) {
				char* name = unknownStringSize(f1);
				head = addToList(head, name, Output, 0);
			}
		}
	}
	struct queueNode* headQueue = NULL;
	int c = EOF;
	while(1) {
		headQueue = enqueue(headQueue,unknownLineSize(f1));
		if((c=fgetc(f1))==EOF){
			break;
		}
	}
	printTable(numInputs,head,head, headQueue);
	return 1;
}
