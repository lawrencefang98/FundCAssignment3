#include <stdio.h>
#include <stdlib.h>

struct minNode{
    char symbol;
    int frequency;
    struct minNode* left, *right;
};
typedef struct minNode minNode;

struct minHeap{
    int currentSize;
    int capacity;
    struct minNode *array;
};
typedef struct minHeap minHeap;


struct minNode* createNode(char symbol,int frequency){
    struct minNode *newNode = (struct minNode *)malloc(sizeof(struct minNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->symbol = symbol;
#include <stdio.h>
#include <stdlib.h>

struct minNode{
    char symbol;
    int frequency;
    struct minNode* left, *right;
};
typedef struct minNode minNode;

struct minHeap{
    int currentSize;
    int capacity;
    struct minNode **array;
};
typedef struct minHeap minHeap;


struct minNode* createNode(char symbol,int frequency){
    struct minNode *newNode = (struct minNode *)malloc(sizeof(struct minNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->symbol = symbol;
    newNode->frequency = frequency;
    return newNode;
}

struct minHeap* createMinHeap(int capacity){
    struct minHeap *minPriorityHeap = (struct minHeap *)malloc(sizeof(struct minHeap));
    minPriorityHeap->currentSize=0;
    minPriorityHeap->capacity = capacity;
    minPriorityHeap->array = (struct minNode **)malloc(minPriorityHeap->capacity * sizeof(struct minNode *));
    return minPriorityHeap;
}


void orderHeap(struct minHeap *minPriorityHeap){
    int i;
    int f;
    for(i = 0; i < minPriorityHeap->currentSize; i ++){
        for(f = 0; f < minPriorityHeap->currentSize; f ++){
            if(minPriorityHeap->array[i]->frequency < minPriorityHeap->array[f]->frequency){
                struct minNode* temp;
                temp = minPriorityHeap->array[i];
                minPriorityHeap->array[i] = minPriorityHeap->array[f];
                minPriorityHeap->array[f] = temp;
            }
        }
    }
}

void insertInHeap(struct minHeap *minPriorityHeap, struct minNode *minHeapNode ){
    minPriorityHeap->array[minPriorityHeap->currentSize] = minHeapNode;
    minPriorityHeap->currentSize++;
    orderHeap(minPriorityHeap);
}

int isOneSize(struct minHeap* minPriorityHeap){
    if(minPriorityHeap->currentSize == 1){
        return 1;
    }
    return 0;
}

struct minNode* extractMins(struct minHeap* minPriorityHeap){
    struct minNode *newNode = (struct minNode *)malloc(sizeof(struct minNode));
    newNode->left = minPriorityHeap->array[0];
    newNode->right = minPriorityHeap->array[1];
    newNode->frequency = minPriorityHeap->array[0]->frequency + minPriorityHeap->array[1]->frequency;
    minPriorityHeap->array[0] = newNode;
    minPriorityHeap->array[1] = minPriorityHeap->array[minPriorityHeap->currentSize - 1];
    --minPriorityHeap->currentSize;
    orderHeap(minPriorityHeap);
    return newNode;
}


/*Gets the frequency of each character*/
void getFrequency(char symbol[], int freq[]){
    char character[256] = {0};
    int frequency[256] = {0}; /*array for frequency for character*/
    int i;

    FILE *fp = fopen("database.txt","r");

    int c;

    while((c=fgetc(fp))){
        if (c == EOF) break;
        frequency[c]+=1;
    }
    for(i=0; i<256; i++) {
		if(frequency[i] > 0){
			character[i] = i;
            symbol[i] = character[i];
            freq[i] = frequency[i];
		}
    }

    /* close the file */
    fclose(fp);
}

void encode(struct minHeap *root){
    
}

int main(){
    struct minHeap* minPriorityQ;
	char character[256] = {0};
    int frequency[256] = {0};
    int i;
    int counter = 0;
    getFrequency(character,frequency);
    for(i = 0; i < 256; i++){
        if(frequency[i]> 0){
        counter++;
        }
    }
    minPriorityQ = createMinHeap(256);
    for(i = 0; i < 256; i++){
        if(frequency[i]> 0){
            insertInHeap(minPriorityQ,createNode(character[i],frequency[i]));
        }
    }
    while(isOneSize(minPriorityQ) == 0){
        extractMins(minPriorityQ);
    }
    for(i = 0; i < minPriorityQ->currentSize; i ++){
        printf("%c%d ", minPriorityQ->array[i]->symbol,minPriorityQ->array[i]->frequency);
    }
    
    return 0;
}