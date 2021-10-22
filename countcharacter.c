#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    minPriorityHeap->currentSize--;
    orderHeap(minPriorityHeap);
    return newNode;
}


/*Gets the frequency of each character*/
void getFrequency(char symbol[], int freq[]){
    int i;

    FILE *fp = fopen("database.txt","r");

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

void encode(char huffmanTable[], char huffmanTableB[][30]){
    FILE *fp = fopen("database.txt","r");
    FILE *fp2 = fopen("databaseCompressed.txt","wb"); 
    int currentBit = 0;
    unsigned char bit_buffer = 0 ;
    int c;
    int i;
    int f;
    while((c=fgetc(fp))){
        if (c == EOF) break;
        for(i = 0; i < strlen(huffmanTable) ;i++){
            if(huffmanTable[i] == c){
                if (huffmanTableB[i]){
                    for(f = 0;f < strlen(huffmanTableB[i]);f++){
                        if(huffmanTableB[i][f] == '1'){
                            bit_buffer |= 1UL << 1;
                            currentBit++;
                        }
                        if(huffmanTableB[i][f] == '0'){
                            bit_buffer &= ~(1UL << 0);
                            currentBit++;
                        }
                        if (currentBit == 8){
                            fwrite (&bit_buffer, 1, 1, fp2);
                            currentBit = 0;
                            bit_buffer = 0;
                        }
                    }
                }
            }
        }  
    }
    fclose(fp);
    fclose(fp2);
}

void decode(struct minNode* root){
    FILE *fp = fopen("databaseCompressed.txt","rb");
    FILE *fp2 = fopen ("databaseDecompressed.txt","w");
    int c;
    struct minNode* currentNode = root;
    while((c=fgetc(fp))){
        if (c == EOF) break;
        if(c == 0){
            currentNode = currentNode->left;
        }
        if(c == 1){
            currentNode = currentNode->left;
        }
        if(isLeaf(root) ==1){
            fwrite(&root->symbol,sizeof(char),1,fp2);
            currentNode = root;
        }
    }
    fclose(fp);
    fclose(fp2);
}

int main(){
    struct minHeap* minPriorityQ;
	char character[256] = {0};
    int frequency[256] = {0};
    char huffmanTable[256] = {};
    char huffmanTableB[256][30] = {};
    int i;
    int counter = 0;
    int counter2 = 0;
    getFrequency(character,frequency);
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
    while(isOneSize(minPriorityQ) == 0){
        extractMins(minPriorityQ);
    }
    int arr[256],top = 0;
    table(minPriorityQ->array[0],arr, top,huffmanTable,huffmanTableB,&counter2);
    encode(huffmanTable,huffmanTableB);
    decode(minPriorityQ->array[0]);
    return 0;
}