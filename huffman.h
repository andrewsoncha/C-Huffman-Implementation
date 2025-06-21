#pragma once
#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "minheap.h"

#define SYMBOL_N 128
#define MAX_CODE_LEN 20

void getCode(node* n, const char *str, char finalCode[SYMBOL_N][MAX_CODE_LEN]){
	char copyStr[MAX_CODE_LEN] = "";
	char leftStr[MAX_CODE_LEN] = "";
	char rightStr[MAX_CODE_LEN] = "";
	if(n==NULL){
		return;
	}
	if(str!=NULL){
		strncpy(copyStr, str, MAX_CODE_LEN);
	}
	if(n->val!=0){
		//printf("%c %d code: %s\n",n->val, n->val, copyStr);
		//printf("finalCode: %s\n",finalCode[n->val]);
		//printf("strlen(%s): %d %d\n",copyStr, strlen(copyStr), sizeof(copyStr));
		strncpy(finalCode[n->val], copyStr, strlen(copyStr));
		//strcpy(finalCode[n->val], copyStr);
		return;
	}
	strncpy(leftStr, copyStr, strlen(copyStr));
	strcat(leftStr, "0");
	getCode(n->left, leftStr, finalCode);

	strncpy(rightStr, copyStr, strlen(copyStr));
	strcat(rightStr, "1");
	getCode(n->right, rightStr, finalCode);
}

char* encode(const char *str, int strLen, char charToCode[SYMBOL_N][MAX_CODE_LEN], int codeLen[SYMBOL_N]){
	long long encodingLen=0;
	for(int i=0;i<strLen;i++){
		if(str[i]<0){  //For some reason str[i] is sometimes negative? Maybe a memory bug? This is a temporary measure
		//	printf("i: %d    str[%d]:%d\n",i,i,str[i]);
			continue;
		}
		// printf("str[i]: %d   codeLen: %d\n", str[i], codeLen[str[i]]);
		encodingLen += codeLen[str[i]];	
	}
	printf("strLen: %d    encodingLen: %d\n", strLen, encodingLen);
	char *encodedStr = (char*)malloc(encodingLen);
	memset(encodedStr, 0, encodingLen);
	for(int i=0;i<strLen;i++){
		if(strLen>100){
			if(i%(strLen/100)==0){
				printf("%d%% done!\n",i/(strLen/100));
			}
		}
		if(str[i]<0){
			continue;
		}
		strcat(encodedStr, charToCode[str[i]]);
	}

	return encodedStr;	
}

char* navigateTree(char* resultChr, node* node, char* encoded){
	if(node->val!=0){
		*resultChr = node->val;
		return encoded;
	}
	if(strlen(encoded)==0){ // ERROR! encoded string ran out!!
		*resultChr = NULL;
		return encoded;
	}
	if(encoded[0]=='0'){
		return navigateTree(resultChr, node->left, encoded+1);
	}
	else{
		return navigateTree(resultChr, node->right, encoded+1);
	}
}


char* decode(const char *encoded, int codeLen, node* tree){
	char* origEncoded = malloc(codeLen);
	memset(origEncoded, 0, codeLen);
	strncpy(origEncoded, encoded, codeLen);
	char* encodedString = origEncoded;
	int decodedStrLen = 0;
	
	//Decoding Twice. Once to know the length of the decoded string (to allocate the precise needed memory)
	//Once to actually save the results
	//TODO: is there a way to know the length of the decoded string without actually having to decode the entire string once more?
	while( (encodedString - origEncoded) < codeLen){
		char resultChr;
		encodedString = navigateTree(&resultChr, tree, encodedString);
		if(resultChr=='\01'){
			break;
		}
		if(resultChr==NULL){
			break;
		}
		decodedStrLen++;
	}
	char* decodedString = (char*)malloc(decodedStrLen);
	memset(decodedString, 0, decodedStrLen);
	int i=0;
	encodedString = origEncoded;

	for(int i=0;i<decodedStrLen;i++){	
		char resultChr;
		encodedString = navigateTree(&resultChr, tree, encodedString);
		if(resultChr==1){
			break;
		}
		decodedString[i] = resultChr;
	}

	free(origEncoded);

	return decodedString;
}

void get_freq(char* str, int strLen, int* freqArr){
	for(int i=0;i<256;i++){
		freqArr[i]=0;
	}
	for(int i=0;i<strLen;i++){
		freqArr[str[i]]++;
	}
}

void sort_arr(node** node_arr, int nodeN){
	for(int i=0;i<nodeN;i++){
		for(int j=i+1;j<nodeN;j++){
			if(node_arr[i]->sum > node_arr[j]->sum){
				node* tmp;
				tmp = node_arr[i];
				node_arr[i] = node_arr[j];
				node_arr[j] = tmp;
			}
		}
	}
}

void create_leaf_node(node* curr, char value, char* code){
	if(strlen(code)==1){
		if(code[0]=='0'){
			curr->left = makeNewNode(NULL, NULL, value, 1);
		}
		else if(code[0]=='1'){
			curr->right = makeNewNode(NULL, NULL, value, 1);
		}
	}
	else{
		if(code[0]=='0'){
			if(curr->left==NULL){
				curr->left = makeNewNode(NULL, NULL, 0, 0);
			}
			create_leaf_node(curr->left, value, code+1);
		}
		else if(code[0]=='1'){
			if(curr->right==NULL){
				curr->right = makeNewNode(NULL, NULL, 0, 0);
			}
			create_leaf_node(curr->right, value, code+1);
		}
	}
} 

node* build_tree_from_code(char charToCode[SYMBOL_N][MAX_CODE_LEN]){
	node* root = makeNewNode(NULL, NULL, 0, 0);
	for(int i=0;i<SYMBOL_N;i++){
		if(strlen(charToCode[i])>0){
			create_leaf_node(root, i, charToCode[i]);
		}
	}
	return root;
}

node* build_tree(int* freqArr){
	int nonZeroN = 0;
	for(int i=0;i<256;i++){
		if(freqArr[i]>0){
			nonZeroN++;
		}
	}

	node** node_arr = (node**)malloc(sizeof(node*)*nonZeroN);
	int nodeI=0;
	for(int i=0;i<256;i++){
		if(freqArr[i]>0){
			node_arr[nodeI++] = makeNewNode(NULL, NULL, i, freqArr[i]);
		}
	}
	
	/*for(int i=0;i<nonZeroN;i++){
		printf("%c %d\n", node_arr[i]->val, node_arr[i]->sum);
	}*/

	heap* h = createHeap(node_arr, nonZeroN);
	free(node_arr);

	while(h->size >= 2){
		node* left = pop(h);
		node* right = pop(h);

		node* newNode = makeNewNode(left, right, 0, left->sum + right->sum);
		insert(h, newNode);
	}

	node* root = h->arr[0];
	freeHeap(h);

	return root;
}
#endif
