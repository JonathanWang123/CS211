#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int read = 0;
int write = 0;
int hit = 0;
int miss = 0;

int readPre = 0;
int writePre = 0;
int hitPre = 0;
int missPre = 0;


struct block {
	long int tag;
    int position;
	struct block* next;
	struct block* prev;
};

struct block* newBlock(long int tag,int position, struct block* n, struct block* p) {
	struct block* ptr = (struct block*)malloc(sizeof(struct block));
	ptr->tag = tag;
    ptr->position = position;
	ptr->next = n;
	ptr->prev = p;
	return ptr;
}

int insert(struct block** cache, long int address, int blockSize, int numSets, int numLines, int pre) {
    long int offset = address >> (long int)log2(blockSize);
    long int set = offset & ((1 << (long int)log2(numSets)) - 1);
    long int tag = offset >> (long int)log2(numSets);

	struct block* ptr = cache[set];
	struct block* prev = NULL;
	struct block* overflow;

    int position = 0;
	while (ptr!=NULL) {
        if (ptr->tag == tag) {
            return 1;
        }
		if (ptr->position > position) {
			position=ptr->position;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	position++;

	struct block* temp = newBlock(tag, position, NULL, prev);
	prev->next = temp;

    struct block* head = cache[set];
	if (position>numLines) {
		overflow = head->next;
		ptr = overflow->next;
		head->next = ptr;
		ptr->prev = head;
		free(overflow);
	}
	return 0;
}

int main (int argc, char** argv) {
	int cacheSize = 0;
	int blockSize = 0;
	int numSets = 0;
    int numLines = 0;



	cacheSize = atoi(argv[1]);
	if (log2(cacheSize) != ceil(log2(cacheSize))) {
        printf("Invalid Cache Size");
        return -1;
    }
	blockSize = atoi(argv[4]);
	if (log2(blockSize) != ceil(log2(blockSize))) {
        printf("Invalid Block Size");
        return -1;
    }
    
    if (strcmp(argv[2], "direct") == 0) {
        numSets = cacheSize/blockSize;
        numLines = 1;
    }
    else if (strstr(argv[2], ":") != NULL) {
        sscanf(argv[2], "assoc:%d", &numLines);
        if (log2(numLines)!= ceil(log2(numLines))){
            printf("Invalid n");
           return -1;
        } 
        numSets = cacheSize / (blockSize* numLines);
    }
    else {
        numSets = 1;
        numLines = cacheSize / (blockSize);
    }
    
	struct block** cache = (struct block**) malloc (sizeof(struct block*)* numSets);
	struct block** cachePre = (struct block**) malloc (sizeof(struct block*)* numSets);
	for (int i=0; i<numSets; i++) {
		struct block* temp1 = newBlock(-1, -1, NULL, NULL);
		struct block* temp2 = newBlock(-1, -1, NULL, NULL);
		cache[i] = temp1;
		cachePre[i] = temp2;
	}
    
    char* file = argv[5];
	FILE* fp = fopen(file, "r");
    
	char* programCounter = (char*)malloc(sizeof(char)* 128);
	char instruction;
	long int address;
	while (fscanf(fp, "%s ", programCounter)==1) {
		if (strcmp("#eof", programCounter)==0) break;
		fscanf(fp, "%c %lx", &instruction, &address);
		
		if (insert(cache, address, blockSize, numSets, numLines, 0)) {
			hit++;
			if (instruction == 'W') {
				write++;
			}
		}else {
			miss++;
            read++;
			if (instruction == 'W') {
				write++;
			}
		}
		if (insert(cachePre, address, blockSize, numSets, numLines, 0)) {
			hitPre++;
			if (instruction == 'W') {
				writePre++;
			}
		}else {
			missPre++;
            readPre++;
			if (instruction == 'W') {
				writePre++;
			}
			if (!insert(cachePre, address+blockSize, blockSize, numSets, numLines, 1)) {
				readPre++;
			}
		}

	}
	printf("Prefetch 0\n");
    printf("Memory reads: %d\n", read);
	printf("Memory writes: %d\n", write);
	printf("Cache hits: %d\n", hit);
	printf("Cache misses: %d\n", miss);
    
	printf("Prefetch 1\n");
	printf("Memory reads: %d\n", readPre);
	printf("Memory writes: %d\n", writePre);
	printf("Cache hits: %d\n", hitPre);
	printf("Cache misses: %d\n", missPre);
	return 0;
}
