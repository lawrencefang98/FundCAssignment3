/* 
compression algorithm based on hufferman coding to compress text files
Steps:
1.Calculate the frequency of each character in the text file
2.Sort the characters in increasing order of the frequency.These are stored in a priority queue.
3.Make each unqiue character as a leaf node.
4.Create an empty node. Assign the minimum frequency to the leftr child of z and assign the second minimum frequency to t
*/


void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
int isSizeOne(struct MinHeap* minHeap);
void insertMinHeap(struct MInHeap* minHeap, struct MinHeapNode* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
void printArr(int arr[], int n);
int isLeaf(struct MinHeapNode* root);
void printCodes(struct MinHeapNode* root, int arr[], int top);
void HuffmanCodes(char data[],int freq[], int size);
