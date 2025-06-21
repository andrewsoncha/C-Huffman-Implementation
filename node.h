#ifndef _NODE_DEF

#define _NODE_DEF
#include <stddef.h>
struct Node{
	struct Node *left, *right;
	char val;
	int sum;
};
typedef struct Node node;

node* makeNewNode(node *leftArg, node *rightArg, char valArg, int sumArg){
	node *newNode = (node*)malloc(sizeof(node));
	newNode->left = leftArg;
	newNode->right = rightArg;
	newNode->val = valArg;
	newNode->sum = sumArg;
	return newNode;
}

node* copyNode(node *origNode){
	node *newNode = (node*)malloc(sizeof(node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->val = origNode->val;
	newNode->sum = origNode->sum;
	return newNode;
}

freeNode(node *n){
	if(n->left!=NULL){
		freeNode(n->left);
	}
	if(n->right!=NULL){
		freeNode(n->right);
	}
	free(n);
}
#endif
