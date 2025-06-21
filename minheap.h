#ifndef _MINHEAP_H 
#define _MINHEAP_H 

#include "node.h"
struct Heap {
	node** arr;
	int size;
};

typedef struct Heap heap;

heap* createHeap(node** node_arr, int nodeN){
	heap* newHeap = (heap*)malloc(sizeof(heap));
	newHeap->arr = malloc(sizeof(node*)*nodeN);
	for(int i=0;i<nodeN;i++){
		newHeap->arr[i] = node_arr[i];
	}
	newHeap->size = nodeN;
	for(int i=nodeN-1;i>=0;i--){
		heapify(newHeap, i);
	}
	return newHeap;
}

void freeHeap(heap* h){
	free(h->arr);
	free(h);
}

void insert(heap* h, node* newnode){
	h->arr[h->size] = newnode;
	int newNodeIdx = h->size;
	while(h->arr[(newNodeIdx-1)/2]->sum > h->arr[newNodeIdx]->sum){
		node *tmp = h->arr[(newNodeIdx-1)/2];
		h->arr[(newNodeIdx-1)/2] = h->arr[newNodeIdx];
		h->arr[newNodeIdx] = tmp;
		newNodeIdx = (newNodeIdx-1)/2;
	}
	h->size++;
}	

node* peak(heap* h){
	return h->arr[0];
}

void heapify(heap* h, int index){
	int left = index*2+1;
	int right = index*2+2;
	int min = index;
	if(left >= h->size){
		return;
	}
	else if(right >= h->size){
		min = left;
	}
	else{
		min = (h->arr[left]->sum > h->arr[right]->sum)?right:left;
	}

	if(h->arr[min]->sum < h->arr[index]->sum){
		node* tmp = h->arr[index];
		h->arr[index] = h->arr[min];
		h->arr[min] = tmp;
		
		heapify(h, min);
	}
}
node* pop(heap* h){
	node* popResult = peak(h);
	for(int i=0;i<h->size-1;i++){
		h->arr[i] = h->arr[i+1];
	}
	h->size--;
	for(int i=0;i<h->size;i++){
		heapify(h, i);
	}

	return popResult;
}
#endif
