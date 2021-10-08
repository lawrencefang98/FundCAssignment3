/*  

compression algorithm based on huffman coding to compress text files 

Steps: 

1.Calculate the frequency of each character in the text file 

2.Sort the characters in increasing order of the frequency.These are stored in a priority queue. 

3.Make each unqiue character as a leaf node. 

4.Create an empty node. Assign the minimum frequency to the leftr child of z and assign the second minimum frequency to t 

*/ 

 

Structures; 

Struct MinHeapNode{}; 

Struct MinHeap{}’ 

 

Functions: 

/* 

Create a new min heap node for character assigned with it’s frequency 

INPUT: char data, unsigned frequency  

OUTPUT: Struct MinHeapNode* 

*/ 

Struct MinHeapNode* newNode(char data, unsigned frequency); 

/* 

Create a min heap with input capacity 

INPUT: unsigned Capacity 

OUTPUT: Struct MinHeap* 

*/ 

Struct MinHeap* createMinHeap(unsigned capacity); 

/* 

 

*/ 

Struct MinHeap* createAndBuildMinHeap(char data[],int freq], int size); 

Struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size); 

Struct MinHeapNode* extractMin(struct MinHeap* minHeap); 

/* 

Function to swap two min heap nodes  

INPUT: struct MinHeap** a, struct MinHeap** B 

*/ 

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b); 

/* 

Function to order tree into an min heap tree 

INPUT: Struct MinHeap*, int idx 

*/ 

void minHeapify(struct MinHeap* minHeap, int idx); 

int isSizeOne(struct MinHeap* minHeap); 

/* 

Insert a MinHeapNode into the  MinHeap 

INPUT: Strucy MinHeap* minHeap, MinHeapNode* minHeapNode 

*/ 

void insertMinHeap(struct MInHeap* minHeap, struct MinHeapNode* minHeapNode); 

void buildMinHeap(struct MinHeap* minHeap); 

void printArr(int arr[], int n); 

int isLeaf(struct MinHeapNode* root); 

void printCodes(struct MinHeapNode* root, int arr[], int top); 

void HuffmanCodes(char data[],int freq[], int size); 