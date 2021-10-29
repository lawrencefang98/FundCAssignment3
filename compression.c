#include <stdio.h>/*  */
#include <stdlib.h>
#include <string.h>
/*
*/
struct minNode{
    char symbol;
    int frequency;
    struct minNode* left, *right;
};
typedef struct minNode minNode;
/*
structure 
*/
struct minHeap{
    int currentSize;
    int capacity;
    struct minNode **array;
};
typedef struct minHeap minHeap;

/*
this function creates nodes 
INPUT: 
OUTPUT:
*/
struct minNode* createNode(char symbol,int frequency){
    struct minNode *newNode = (struct minNode *)malloc(sizeof(struct minNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->symbol = symbol;
    newNode->frequency = frequency;
    return newNode;
}
/*
this function creates an min heap to store the nodes
INPUT: int capacity
OUTPUT: struct minHeap
*/
struct minHeap* createMinHeap(int capacity){
    struct minHeap *minPriorityHeap = (struct minHeap *)malloc(sizeof(struct minHeap));
    minPriorityHeap->currentSize=0;
    minPriorityHeap->capacity = capacity;
    minPriorityHeap->array = (struct minNode **)malloc(minPriorityHeap->capacity * sizeof(struct minNode *));
    return minPriorityHeap;
}

/*
this function orderd the min heap into the smallest to the largest nodes
INPUT: 
OUTPUT:
*/
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
/*
this function inserts a node in the min heap
INPUT: 
OUTPUT:
*/
void insertInHeap(struct minHeap *minPriorityHeap, struct minNode *minHeapNode ){
    minPriorityHeap->array[minPriorityHeap->currentSize] = minHeapNode;
    minPriorityHeap->currentSize++;
    orderHeap(minPriorityHeap);
}
/*
this function finds if the min heap has a root 
INPUT: 
OUTPUT:
*/
int isOneSize(struct minHeap* minPriorityHeap){
    if(minPriorityHeap->currentSize == 1){
        return 1;
    }
    return 0;
}
/*
this function extracts the two smallest nodes from the heap and combine them under an different node
INPUT: 
OUTPUT:
*/
struct minNode* extractMins(struct minHeap* minPriorityHeap){
    struct minNode *newNode = (struct minNode *)malloc(sizeof(struct minNode));
    newNode->left = minPriorityHeap->array[0];
    newNode->right = minPriorityHeap->array[1];
    newNode->frequency = minPriorityHeap->array[0]->frequency + minPriorityHeap->array[1]->frequency;
    minPriorityHeap->array[0] = newNode;
    minPriorityHeap->array[1] = minPriorityHeap->array[minPriorityHeap->currentSize - 1];
    minPriorityHeap->currentSize--;
    orderHeap(minPriorityHeap);
    return newNode;
}


/*
this function get the frequency of each character in a file
INPUT: 
OUTPUT:
*/
void getFrequency(char symbol[], int freq[],char filename[] ){
    int i;

    FILE *fp = fopen(filename,"r");

    int c;

    while((c=fgetc(fp))){
        if (c == EOF) break;
        freq[c]+=1;
    }
    for(i=0; i<256; i++) {
		if(freq[i] > 0){
            symbol[i] = i;
		}
    }
    fclose(fp);
}
int isLeaf(struct minNode *node){
    if(node->left == NULL && node->right == NULL){
        return 1;
    }
    return 0;
}
/*
this function creates an huffman table based on the frequency of the characters
INPUT: 
OUTPUT:
*/
void table(struct minNode *node,int arr[], int top,char huffmanTable[], char huffmanTableB[][30],int *counter2){
    if(node->left != NULL){
        arr[top] = 0;
        table(node->left,arr,top+1,huffmanTable,huffmanTableB,counter2);
    }

    if(node->right != NULL){
        arr[top] = 1;
        table(node->right,arr,top+1,huffmanTable,huffmanTableB,counter2);
    }

    if(isLeaf(node) ==1){
        int i;
        huffmanTable[*counter2] = node->symbol;
        for(i = 0;i < top;i++){
            char charValue  = arr[i]+'0';
            huffmanTableB[*counter2][i] = charValue;
        }
        (*counter2)++;
    }

}

void nodeCounterF(struct minNode *node,int arr[], int top,int *counter2){
    if(node->left != NULL){
        arr[top] = 0;
        nodeCounterF(node->left,arr,top+1,counter2);
    }

    if(node->right != NULL){
        arr[top] = 1;
        nodeCounterF(node->right,arr,top+1,counter2);
    }

    if(isLeaf(node) ==1){
        (*counter2)++;
    }

}

void nodeFile(struct minNode *node,int arr[], int top,FILE *fp){
    if(node->left != NULL){
        arr[top] = 0;
        nodeFile(node->left,arr,top+1,fp);
    }

    if(node->right != NULL){
        arr[top] = 1;
        nodeFile(node->right,arr,top+1,fp);
    }

    if(isLeaf(node) ==1){
        fwrite(node,sizeof(minNode),1,fp);
    }

}

/*
this function encodes a file
INPUT:
OUTPUT:
*/
void encode(char huffmanTable[], char huffmanTableB[][30],struct minNode* tree,char filename[],char character[], int frequency[],int counter){
    char comFile[256];
    printf("What would you like to name your compressed file:");
    scanf("%s",comFile);
    FILE *fp = fopen(filename,"r");
    FILE *fp2 = fopen(comFile,"wb"); 
    int currentBit = 0;
    char bit_buffer = 0 ;
    int totalBits = 0;
    int nodeCounter = 0;
    int arr[256],top = 0;
    int c;
    long i;
    int f;
    arr[256] =0;
    top = 0;
    nodeCounterF(tree,arr,top, &nodeCounter);
    while((c=fgetc(fp))){
        if (c == EOF) break;
        for(i = 0; i < strlen(huffmanTable) ;i++){
            if(huffmanTable[i] == c){
                         totalBits++;
            }
        }
    }
    fwrite(&totalBits,sizeof(int),1,fp2);
    fwrite(&counter, sizeof(int),1,fp2);
    fwrite(&nodeCounter, sizeof(int),1,fp2);
    for(i = 0; i < 256; i++){
        if(frequency[i]> 0){
            fwrite(&character[i],sizeof(char),1,fp2);
        }
    }
    for(i = 0; i < 256; i++){
        if(frequency[i]> 0){
            fwrite(&frequency[i],sizeof(int),1,fp2);
        }
    }
    fseek(fp, 0, SEEK_SET);
    while((c=fgetc(fp))){
        if (c == EOF) break;
        for(i = 0; i < strlen(huffmanTable) ;i++){
            if(huffmanTable[i] == c){
                    for(f = 0;f < strlen(huffmanTableB[i]);f++){
                        if(huffmanTableB[i][f] == '1'){
                            bit_buffer |= 1 << currentBit;
                        }else if(huffmanTableB[i][f] == '0'){
                            bit_buffer &= ~(1 << currentBit);
                        }
                        currentBit++;
                        if (currentBit == 8){
                            fwrite (&bit_buffer, 1, 1, fp2);
                            currentBit = 0;
                            bit_buffer = 0;
                        }
                    }
            }
        }  
    }
    fwrite (&bit_buffer, 1, 1, fp2);
    fclose(fp);
    fclose(fp2);
}
/*
this function decodes the encoded file
INPUT:
OUTPUT:
*/
void decode(char encodedFile[]){
    char comFile[256];
    printf("What would you like to name your decompressed file:");
    scanf("%s",comFile);
    FILE *fp = fopen(encodedFile,"rb");
    FILE *fp2 = fopen(comFile,"w");
    int length;
    int capacity;
    int tableSize;
    int currentBit = 0;
    struct minHeap* minPriorityQ;
    int i;
    int c;
    int h;
    fseek(fp, 0, SEEK_SET);
    fread(&length,sizeof(int),1,fp);
    fread(&tableSize,sizeof(int),1,fp);
    fread(&capacity,sizeof(int),1,fp);
    char character[tableSize];
    int frequency[tableSize];
    minPriorityQ = createMinHeap(capacity);
    for(i = 0; i < tableSize; i++){
        char f;
        fread(&f, sizeof(char),1,fp);
        character[i] = f;
    }
    for(i = 0; i < tableSize; i++){
        int f;
        fread(&f, sizeof(int),1,fp);
        frequency[i] = f;
    }
    for(i = 0; i < tableSize; i++){
            insertInHeap(minPriorityQ,createNode(character[i],frequency[i]));
    }
    while(isOneSize(minPriorityQ) == 0){
        extractMins(minPriorityQ);
    }
    struct minNode* root =minPriorityQ->array[0];
    struct minNode* currentNode = minPriorityQ->array[0];
    while(length != currentBit){
        c=fgetc(fp);
        for(h = 0; h< 8; h ++){
            if(((c >> h) & 0x01) == 0){
                currentNode = currentNode->left;
            }
            else{
                currentNode = currentNode->right;
            }
            if(isLeaf(currentNode) == 1){
                fwrite(&currentNode->symbol, sizeof(char),1,fp2);
                currentNode= root;
                currentBit++;
                if(currentBit == length){
                break;
            }
            }
        }
    }
    fclose(fp);
    fclose(fp2);
}

struct minHeap* huffmanTree(char filename[],char character[],int frequency[],int *counter){
    struct minHeap* minPriorityQ;
    int i;
    getFrequency(character,frequency,filename);
    for(i = 0; i < 256; i++){
        if(frequency[i]> 0){
        (*counter)++;
        }
    }
    minPriorityQ = createMinHeap(*counter);
    for(i = 0; i < 256; i++){
        if(frequency[i]> 0){
            insertInHeap(minPriorityQ,createNode(character[i],frequency[i]));
        }
    }
    while(isOneSize(minPriorityQ) == 0){
        extractMins(minPriorityQ);
    }
    return minPriorityQ;
}

void huffmanEncoding(){
    int counter = 0;
    int counter2 = 0;
    int i;
    char character[256] = {0};
    int frequency[256] = {0};
    char huffmanTable[256] = {};
    char huffmanTableB[256][30] = {};
    char filename[256];
    struct minHeap* minPriorityQ;
    printf("Enter the name of the file you want to encode:");
    scanf("%s",filename);
    minPriorityQ = huffmanTree(filename, character , frequency, &counter2);
    int arr[256],top = 0; 
    table(minPriorityQ->array[0],arr, top,huffmanTable,huffmanTableB,&counter);
    for(i = 0; i < counter ;i++){
        printf("%c %s \n",huffmanTable[i],huffmanTableB[i]);
    }
    encode(huffmanTable,huffmanTableB,minPriorityQ->array[0],filename,character,frequency,counter2);
}

void huffmanDecoding(){
    char filename[256];
    printf("Enter the name of the file you want to decode:");
    scanf("%s",filename);
    decode(filename);
}

void printMenu(){
    printf("Enter 1 to encode a file\n");
    printf("Enter 2 to decode a file \n");
    printf("Enter 3 to exit the program\n");
}
int main(){
    int choice = 0;
    do{
        printMenu();
        printf("Enter your choice:");
        scanf("%i",&choice);
        switch(choice){
            case 1:
            huffmanEncoding();
            break;
            case 2:
            huffmanDecoding();
            case 3:
            exit(0);
        }
    }
    while(choice != 3);
    return 0;
}