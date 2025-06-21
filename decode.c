#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "huffman.h"
#include "file.h"

int main(int argc, char *argv[]){
	int freq[256];
	if(argc<2){
		printf("decode [FILE_PATH]\n");
		return -1;
	}
	long fileSize;
	char *codePath, *encPath;
	codePath = malloc(strlen(argv[1])+4);
	memset(codePath, 0, strlen(argv[1])+4);
	encPath = malloc(strlen(argv[1]+4));
	memset(encPath, 0, strlen(argv[1]+4));
	strncpy(codePath, argv[1], strlen(argv[1]));
	strcat(codePath, ".code");
	strncpy(encPath, argv[1], strlen(argv[1]));
	strcat(encPath, ".enc");
	printf("codePath: %s\n",codePath);
	printf("encPath: %s\n",encPath);

	printf("readFromFile started!\n");
	char* binaryContent = readFromFile(encPath, 1, &fileSize);
	printf("readFromFile done!\n");

	int codeLen;
	char* encodedContent = binary2Code(binaryContent, fileSize, &codeLen);
	printf("encodedContent: %s\n",encodedContent);
	printf("readFromFile done!\n");
	
	char charToCode[SYMBOL_N][MAX_CODE_LEN];
	memset(charToCode, 0, SYMBOL_N*MAX_CODE_LEN);
	printf("readCode started!\n");
	readCode(codePath, charToCode);
	printf("readCode done!\n");

	for(int i=0;i<SYMBOL_N;i++){
		if(strlen(charToCode[i])>0){
			printf("%c %d: %s\n",i,i,charToCode[i]);
		}
	}

	printf("build_tree_from code started!\n");
	node* tree = build_tree_from_code(charToCode);
	printf("build tree from code done!\n");

	printf("decoding started!\n");
	char *decodedResult = decode(encodedContent, codeLen, tree);
	printf("decodedResult: %s\n",decodedResult);

	char *writePath;
	writePath = malloc(strlen(argv[1])+4);
	memset(writePath, 0, strlen(argv[1])+4);
	strncpy(writePath, argv[1], strlen(argv[1]));
	strcat(writePath, ".dec");
	writeToFile(writePath, decodedResult, strlen(decodedResult));
	printf("writePath: %s\n",writePath);

	freeNode(tree);
	free(decodedResult);

	free(codePath);
	free(encPath);
	free(writePath);
	free(binaryContent);
	free(encodedContent);
	return 0;
}
