#ifndef CompressionGuard
#define CompressionGuard


#include <stdio.h>/* fopen,printf,scanf,fclose,fwrite,fgetc,fseek,fread*/
#include <stdlib.h>/*malloc,exit*/
#include <string.h>/*strlen*/

#define MAX_TABLE 256
/*
struct of a node to store an character and its frequency
*/
struct minNode{
    char symbol;
    int frequency;
    struct minNode* left, *right;
};
typedef struct minNode minNode;
/*
struct of a min heap to store the nodes
*/
struct minHeap{
    int currentSize;
    int capacity;
    struct minNode **array;
};
typedef struct minHeap minHeap;

/*
this function creates nodes 
INPUT: char symbol,int frequency
OUTPUT:struct minNode*
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
    struct minHeap *minPriorityHeap = (struct minHeap *)
    malloc(sizeof(struct minHeap));
    minPriorityHeap->currentSize=0;
    minPriorityHeap->capacity = capacity;
    minPriorityHeap->array = (struct minNode**)malloc(minPriorityHeap->capacity
    * sizeof(struct minNode *));
    return minPriorityHeap;
}

/*
this function orderd the min heap into the smallest to the largest nodes
INPUT: struct minHeap *minPriorityHeap
OUTPUT:
*/
void orderHeap(struct minHeap *minPriorityHeap){
    int i;
    int f;
    for(i = 0; i < minPriorityHeap->currentSize; i ++){
        for(f = 0; f < minPriorityHeap->currentSize; f ++){
            if(minPriorityHeap->array[i]->frequency < minPriorityHeap->
            array[f]->frequency){
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
INPUT: struct minHeap *minPriorityHeap, struct minNode *minHeapNode 
OUTPUT:
*/
void insertInHeap(struct minHeap *minPriorityHeap,struct minNode *minHeapNode){
    minPriorityHeap->array[minPriorityHeap->currentSize] = minHeapNode;
    minPriorityHeap->currentSize++;
    orderHeap(minPriorityHeap);
}
/*
this function finds if the min heap has a root 
INPUT: struct minHeap* minPriorityHeap
OUTPUT:int
*/
int isOneSize(struct minHeap* minPriorityHeap){
    if(minPriorityHeap->currentSize == 1){
        return 1;
    }
    return 0;
}
/*
this function extracts the two smallest nodes from the heap and combine them under 
an different node
INPUT: struct minHeap* minPriorityHeap
OUTPUT:struct minNode* 
*/
struct minNode* extractMins(struct minHeap* minPriorityHeap){
    struct minNode *newNode = (struct minNode *)malloc(sizeof(struct minNode));
    newNode->left = minPriorityHeap->array[0];
    newNode->right = minPriorityHeap->array[1];
    newNode->frequency = minPriorityHeap->array[0]->frequency + 
    minPriorityHeap->array[1]->frequency;
    minPriorityHeap->array[0] = newNode;
    minPriorityHeap->array[1] = minPriorityHeap->
    array[minPriorityHeap->currentSize - 1];
    minPriorityHeap->currentSize--;
    orderHeap(minPriorityHeap);
    return newNode;
}


/*
this function get the frequency of each character in a file
INPUT: char symbol[], int freq[],char filename[] 
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
/*
this function determines if a node is a leaf node
INPUT: struct minNode *node
OUTPUT:int
*/

int isLeaf(struct minNode *node){
    if(node->left == NULL && node->right == NULL){
        return 1;
    }
    return 0;
}
/*
this function creates an huffman table based on the frequency of the characters
INPUT: struct minNode *node,int arr[], int top,char huffmanTable[], 
char huffmanTableB[][30],int *counter2
OUTPUT:
*/
void table(struct minNode *node,int arr[], int top,char huffmanTable[], 
char huffmanTableB[][30],int *counter2){
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
/*
this function counts the number of nodes in the huffman tree
INPUT: struct minNode *node,int arr[], int top,int *counter2
OUTPUT:
*/
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



/*
this function compressed a file
INPUT:char huffmanTable[], char huffmanTableB[][30],struct minNode* tree
,char filename[],char character[], int frequency[],int counter
OUTPUT:
*/
void encode(char huffmanTable[], char huffmanTableB[][30],struct minNode* tree
,char filename[],char character[], int frequency[],int counter){
    char comFile[MAX_TABLE];
    printf("What would you like to name your compressed file:");
    scanf("%s",comFile);
    FILE *fp = fopen(filename,"r");
    FILE *fp2 = fopen(comFile,"wb"); 
    int currentBit = 0;
    char bit_buffer = 0 ;/*buffer to toggle bits for compression*/
    int totalBits = 0;
    int nodeCounter = 0;
    int arr[MAX_TABLE],top = 0;
    int c;
    long i;
    int f;
    nodeCounterF(tree,arr,top, &nodeCounter);
    while((c=fgetc(fp))){
        /*counts the number of total bits to be put in the compressed file*/
        if (c == EOF) break;
        for(i = 0; i < strlen(huffmanTable) ;i++){
            if(huffmanTable[i] == c){
                         totalBits++;
            }
        }
    }
    fwrite(&totalBits,sizeof(int),1,fp2);
    /*storing the number of bits into the header*/
    fwrite(&counter, sizeof(int),1,fp2);
    /*storing the size of the character and frequency table into the header*/
    fwrite(&nodeCounter, sizeof(int),1,fp2);
    /*storing the number of nodes into the header*/
    for(i = 0; i < MAX_TABLE; i++){
        if(frequency[i]> 0){
            fwrite(&character[i],sizeof(char),1,fp2);
        }
    }
    for(i = 0; i < MAX_TABLE; i++){
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
                            /*setting a bit of a byte */
                        }else if(huffmanTableB[i][f] == '0'){
                            bit_buffer &= ~(1 << currentBit);
                            /*clearing a bit of a byte */
                        }
                        currentBit++;
                        if (currentBit == 8){
                            fwrite (&bit_buffer, 1, 1, fp2);
                            /*writing the byte*/
                            currentBit = 0;
                            bit_buffer = 0;
                        }
                    }
            }
        }  
    }
    /*writing the last byte if it doesn't reach 8 byte*/
    fwrite (&bit_buffer, 1, 1, fp2);
    fclose(fp);
    fclose(fp2);
    printf("File successfully compressed\n");
}
/*
this function decompress the compressed file 
INPUT: char encodedFile[]
OUTPUT:
*/
void decode(char encodedFile[]){
    char comFile[MAX_TABLE];
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
    /*get the beginning of the file*/
    fseek(fp, 0, SEEK_SET);
    /*get the length of the file from the header*/
    fread(&length,sizeof(int),1,fp);
    /*get the tableSize from the header*/
    fread(&tableSize,sizeof(int),1,fp);
    /*get the capacity from the header*/
    fread(&capacity,sizeof(int),1,fp);
    char character[tableSize];
    int frequency[tableSize];
    minPriorityQ = createMinHeap(capacity);
    /*getting the character array from header*/
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
    /*creating the huffman tree the exact same*/
    for(i = 0; i < tableSize; i++){
            insertInHeap(minPriorityQ,createNode(character[i],frequency[i]));
    }
    while(isOneSize(minPriorityQ) == 0){
        extractMins(minPriorityQ);
    }
    struct minNode* root =minPriorityQ->array[0];
    struct minNode* currentNode = minPriorityQ->array[0];
    /*traversing the huffman tree to determine character*/
    while(length != currentBit){
        c=fgetc(fp);
        for(h = 0; h< 8; h ++){
	    /*if bit is 0 go to the left node*/	
            if(((c >> h) & 0x01) == 0){
                currentNode = currentNode->left;
            }
	    /*if bit is 1 go to the left node*/	
            else{
                currentNode = currentNode->right;
            }
	    /*if current node is leaf get the character and restart*/	
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
    printf("File successfully decompressed\n");
}

/*
this function creates the huffmanTree
INPUT:char filename[],char character[],int frequency[],int *counter
OUTPUT:struct minHeap*
*/
struct minHeap* huffmanTree(char filename[],char character[],int frequency[]
,int *counter){
    struct minHeap* minPriorityQ;
    int i;
    /*get size of min heap needed*/
    getFrequency(character,frequency,filename);
    for(i = 0; i < MAX_TABLE; i++){
        if(frequency[i]> 0){
        (*counter)++;
        }
    }
    minPriorityQ = createMinHeap(*counter);
    /*insert each node into minheap*/
    for(i = 0; i < MAX_TABLE; i++){
        if(frequency[i]> 0){
            insertInHeap(minPriorityQ,createNode(character[i],frequency[i]));
        }
    }
    /*group the lowest nodes together to a parent node till there is a root*/
    while(isOneSize(minPriorityQ) == 0){
        extractMins(minPriorityQ);
    }
    return minPriorityQ;
}
/*
this function uses the huffman tree to compress the file
*/
void huffmanEncoding(){
    int counter = 0;
    int counter2 = 0;
    char character[MAX_TABLE] = {0};
    int frequency[MAX_TABLE] = {0};
    char huffmanTable[MAX_TABLE] = {};
    char huffmanTableB[MAX_TABLE][30] = {};
    char filename[MAX_TABLE];
    struct minHeap* minPriorityQ;
    FILE *fp;
    printf("Enter the name of the file you want to compress:");
    do{
        scanf("%s",filename);
        if(!(fp = fopen(filename,"r"))){
            printf("File does not exist\nEnter a valid file name:");
        }
    }while(!(fp = fopen(filename,"r")));
    fclose(fp);
    minPriorityQ = huffmanTree(filename, character , frequency, &counter2);
    int arr[MAX_TABLE],top = 0; 
    table(minPriorityQ->array[0],arr, top,huffmanTable,huffmanTableB,&counter);
    encode(huffmanTable,huffmanTableB,minPriorityQ->array[0],
    filename,character,frequency,counter2);
}

/*
this function decodes the encoded file
*/
void huffmanDecoding(){
    char filename[MAX_TABLE];
    FILE *fp;
    printf("Enter the name of the file you want to decompress:");
    do{
        scanf("%s",filename);
        if(!(fp = fopen(filename,"rb"))){
            printf("File does not exist\nEnter a valid file name:");
        }
    }while(!(fp = fopen(filename,"rb")));
    fclose(fp);
    decode(filename);
}
/*
this function prints the menu
*/
void compressionMenu(){
    printf("Enter 1 to compress a file\n");
    printf("Enter 2 to decompress a file \n");
    printf("Enter 3 to exit the program\n");
}

void compression(){
    int choice = 0;
    do{
        compressionMenu();
        printf("Enter your choice:");
        scanf("%i",&choice);
        switch(choice){
            case 1:
            huffmanEncoding();
            break;
            case 2:
            huffmanDecoding();
            break;
            case 3:
            choice = 3;
	    break;
            default:
            printf("Enter a valid option\n");
        }
    }
    while(choice != 3);
}

#endif /*CompressionGuard*/
