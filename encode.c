#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "huffman.h"
#include "file.h"

int main(int argc, char *argv[]){
	int freq[256];
	if(argc<2){
		printf("encode [FILE_PATH]\n");
		return -1;
	}
	long fileSize;
	char* origContent = readFromFile(argv[1], "r", &fileSize); 

	int nodeN=0;

	get_freq(origContent, fileSize, freq);
	printf("get_freq done!\n");
	/*for(int i=0;i<256;i++){
		if(freq[i]>0){
			printf("%c: %d\n",i,freq[i]);
		}
	}*/

	printf("Building Tree!\n");
	node* root = build_tree(freq);

	char charToCode[SYMBOL_N][MAX_CODE_LEN];
	int codeLen[SYMBOL_N];
	for(int i=0;i<SYMBOL_N;i++){
		memset(charToCode[i], 0, MAX_CODE_LEN);
	}
	getCode(root, "", charToCode);
	printf("got code!\n");
	for(int i=0;i<SYMBOL_N;i++){
		printf("last checked i:%d %c\n",i,i);
		if(charToCode[i][0]!=0){
			codeLen[i] = strlen(charToCode[i]);
			printf("val: %d",i);
			printf("     code: %s %d\n",charToCode[i], codeLen[i]);
		}
	}

	printf("encoding!\n");
	char* result = encode(origContent, fileSize, charToCode, codeLen);
	printf("result: \n%s\n",result);

	int binaryLen=0;
	char* binaryBuffer = code2Binary(result, strlen(result), &binaryLen); 
	printf("binaryLen: %d\n",binaryLen);

	
	for(int i=0;i<binaryLen;i++){
		printBinary(binaryBuffer[i]);
		//printf(" ");
	}
	printf("\n");
	
	
	char* encWritePath = malloc(strlen(argv[1])+4);
	memset(encWritePath, 0, strlen(argv[1])+4);
	strncpy(encWritePath, argv[1], strlen(argv[1]));
	strcat(encWritePath, ".enc");

	char* codeWritePath = malloc(strlen(argv[1])+4);
	memset(codeWritePath, 0, strlen(argv[1])+4);
	strncpy(codeWritePath, argv[1], strlen(argv[1]));
	strcat(codeWritePath, ".code");

	printf("encWritePath: %s\n",encWritePath);
	writeToFile(encWritePath, binaryBuffer, binaryLen);

	printf("codeWritePath: %s\n", codeWritePath);
	writeCode(codeWritePath, charToCode);
	/*

	printf("decoding!\n");
	char* decodedResult = decode(result, strlen(result), root);
	printf("decoded Result: %s\n",decodedResult);
	free(decodedResult);
	*/
	free(binaryBuffer);

	free(result);

	freeNode(root);

	free(origContent);

	return 0;
}
