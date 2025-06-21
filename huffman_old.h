#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minheap.h"

#define ALPHABET_N 'z'-'a'

struct NodeVal{
	int freq;
	char val;
};

struct Node{
	struct Node *left, *right;
	struct NodeVal *val;
	int sum;
};	

struct Node* makeNewNode(struct Node *leftArg, struct Node *rightArg, struct NodeVal *valArg, int sumArg){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->left = leftArg;
	newNode->right = rightArg;
	newNode->val = valArg;
	newNode->sum = sumArg;
	return newNode;
}

void freeNode(struct Node *node){
	if(newNode->left!=NULL){
		freeNode(node->left);
	}
	if(newNode->right!=NULL){
		freeNode(node->right);
	}
	if(newNode->val!=NULL){
		free(node->val);
	}
	free(node);
}

struct Tree{
	struct NodeVal *root;
};

struct nodeVal* get_freq(char* str, int* nodeN){
	char freq[256];
	for(int i=0;i<256;i++){
		freq[i] = 0;
	}
	int diffCharCnt=0;
	for(int i=0;i<strlen(str);i++){
		if(freq[str[i]]==0){
			diffCharCnt++;
		}
		freq[str[i]]++;
	}

	struct NodeVal **freq_arr = (struct NodeVal**)malloc(sizeof(struct NodeVal*)*diffCharCnt);
	int valI = 0;
	for(int i=0;i<256;i++){
		if(freq[i]>0){
			freq_arr[valI] = (struct NodeVal*)malloc(sizeof(struct NodeVal));
			freq_arr[valI]->freq = freq[i];
			freq_arr[valI]->val = i;
			valI++;
		}
	}
	*nodeN = diffCharCnt;
	return freq_arr;
}

void free_freq(struct NodeVal **freq_arr, int nodeN){
	for(int i=0;i<nodeN;i++){
		free(freq_arr[i]);
	}
	free(freq_arr);
	return;
}

void sort_arr(struct NodeVal **freq_arr, int nodeN){
	for(int i=0;i<nodeN;i++){
		for(int j=i+1;j<nodeN;j++){
			if(freq_arr[i]->freq > freq_arr[j]->freq){
				struct NodeVal* tmp;
				tmp = freq_arr[i];
				freq_arr[i] = freq_arr[j];
				freq_arr[j] = tmp;
			}
		}
	}
	return;
}

void addToTree(Tree* tree, Node* root, Node* newLeaf){
	if(newLeaf->sum >= root->sum){
		NOde	

struct Tree* build_tree(struct NodeVal **freq_arr, int nodeN){
	for(int i=0;i<nodeN;i++){
		printf("%c %d\n",freq_arr[i]->val, freq_arr[i]->freq);
	}
	printf("__________________________________________\n");
	sort_arr(freq_arr, nodeN);
	for(int i=0;i<nodeN;i++){
		printf("%c %d\n",freq_arr[i]->val, freq_arr[i]->freq);
	}

	struct Node** node_arr = (struct Node**)malloc(sizeof(struct Node*)*nodeN);
	for(int i=0;i<nodeN;i++){
		node_arr[i] = (struct Node*)malloc(sizeof(struct Node));
		node_arr[i]->val = freq_arr[i];
		node_arr[i]->sum = freq_arr[i]->freq;
	}

	struct Heap* heap = create_heap(node_arr[i], nodeN);
	
	while(heap->size > 2){
		struct Node* left = pop(heap);
		struct Node* right = pop(heap);
		
		struct Node* newNode = makeNewNode(left, right, NULL, left->sum + right->sum);
		insert(heap, newNode);
	}
	
	struct Tree* tree = (struct Tree*)malloc(sizeof(struct Tree));
	tree->root = pop(heap);
	free_heap(heap);

	return tree;
