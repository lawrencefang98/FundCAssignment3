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
    newNode->frequency = frequency;
    return newNode;
}

struct minHeap createMinHeap(int capacity){
    struct minHeap *minPriorityHeap = (struct minHeap *)malloc(sizeof(struct minHeap));
    minPriorityHeap->currentSize=0;
    minPriorityHeap->capacity = capacity;
    minPriorityHeap->array = (struct minNode **)malloc(minPriorityHeap->capacity * sizeof(struct minNode *));
    return minPriorityHeap;
}

void insertInHeap(struct minHeap *minPriorityHeap, struct minNode *minHeapNode ){
    int i;
    minPriorityHeap->currentSize++;
    while (i && minHeapNode->frequency < minPriorityHeap->array[(i - 1) / 2]->frequency) {
    minPriorityHeap->array[i] = minPriorityHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
    }
    minPriorityHeap->array[i] = minHeapNode;
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

void sortArray(char character[], int frequency[]){
    char unSortedCharacter[256];
    int unSortedFrequency[256];
    int i;
    int f;
    int tempInt = 0;
    char tempChar;

    for(i = 0; i < 256; i++){
        for(f = 1+i; f < 256; f++){
            if(unSortedFrequency[i] > unSortedFrequency[f]){
                tempInt = unSortedFrequency[i];
                unSortedFrequency[i] = unSortedFrequency[f];
                unSortedFrequency[f] = tempInt;
                tempChar = unSortedCharacter[i];
                unSortedCharacter[i] = unSortedCharacter[f];
                unSortedCharacter[f] = tempChar;
            }
        }
    }
    for(i= 0; i <256; i++){
        character[i] = unSortedCharacter[i];
        frequency[i] = unSortedFrequency[i];
    }
}


int main(){
    struct minHeap minPriorityQ;
	char character[256] = {0};
    int frequency[256] = {0};
    int i;
    int counter = 0;
    getFrequency(character,frequency);
    sortArray(character, frequency);
    for(i = 0; i < 256; i++){
        if(frequency[i]> 0){
        counter++;
        }
    }
    minPriorityQ = createMinHeap(counter);
    for(i = 0; i < 256; i++){
        if(frequency[i]> 0){
            insertInHeap(minPriorityQ,createNode(character[i],frequency[i]));
        }
    }
    return 0;
}