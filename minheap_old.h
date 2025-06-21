#define HEAP_MX 512
struct Heap {
	struct Node* arr[HEAP_MX];
	int size;
}

struct Heap* createHeap(struct Node* node_arr, int nodeN){
	struct Heap* newHeap = (struct Heap*)malloc(sizeof(struct Heap));
	for(int i=0;i<nodeN;i++){
		newHeap->arr[i] = node_arr[i];
	}
	newHeap->size = nodeN;
	for(int i=nodeN-1;i>=0;i--){
		heapify(newHeap, i);
	}
	return newHeap;
}

void freeHeap(struct Heap* h){
	free(h->arr);
	free(h);
}

void insert(struct Heap* h, struct Node* newNode){
	h->arr[h->size] = newNode;
	int newNodeIdx = h->size;
	while(h->arr[(newNodeIdxi-1)/2] > h->arr[newNodeIdx]){
		struct Node tmp = h->arr[(newNodeIdx-1)/2];
		h->arr[(newNodeIdx-1)/2] = h->arr[newNodeIdx];
		h->arr[newNodeIdx] = tmp;
		newNodeIdx = (newNodeIdx-1)/2;
	}
	h->size++;
}	

struct Node* peak(struct Heap* h){
	return h->arr[0];
}

void heapify(struct Heap* h, int index){
	int left = index*2+1;
	int right = index*2+2;
	int min = index;
	if(left > h->size){
		return;
	}
	else if(right > h->size){
		min = left;
	}
	else{
		min = (h->arr[left]->sum > h->arr[right]->sum)?right:left;
	}

	if(h->arr[min]->sum < h->arr[index]->sum){
		Node* tmp = h->arr[index];
		h->arr[index] = h->arr[min];
		h->arr[min] = tmp;
		
		heapify(h, min);
	}
}
struct Node* pop(struct Heap* h){
	struct Node* popResult = peak(h);
	for(int i=0;i<h->size-1;i++){
		h->arr[i] = h->arr[i+1];
	}
	h->size--;
	for(int i=0;i<h->size;i++){
		heapify(h, i);
	}

	return popResult;
}

