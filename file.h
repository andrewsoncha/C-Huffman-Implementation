#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char bitIVal[8] = {
	0b10000000,
	0b01000000,
	0b00100000,
	0b00010000,
	0b00001000,
	0b00000100,
	0b00000010,
	0b00000001
};

void printBinary(char val){
	for(int i=0;i<8;i++){
		printf("%d",val&1);
		val = val>>1;
	}
	//printf("\n");
	return;
}

char* readFromFile(char* filePath, int readOption, long *size){
	FILE *fp;
	if(readOption==0){
		fp = fopen(filePath, "r");
		printf("opening filePath: %s   r\n",filePath);
	}
	else{
		fp = fopen(filePath, "rb");
		printf("opening filePath: %s    rb\n",filePath);
	}
	if(fp==NULL){
		printf("Error opening file!\n");
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	*size = ftell(fp);
	printf("size: %ld\n",*size);
	fseek(fp, 0, SEEK_SET);
	char *fcontent = malloc(*size+2);
	printf("fread started!\n");
	fread(fcontent, 1, *size,  fp);
	printf("fread ended!\n");
	//printf("fcontent: %s\n",fcontent);
	strcat(fcontent, "\01"); // adding \1 to indicate end of file/string when decoding
	*size++; // Adding 1 to strLen as the Last \0 won't be counted by strlen later
	fclose(fp);
	return fcontent;
}

char* code2Binary(char* code, int codeLen, int *binaryLen){

	*binaryLen = codeLen/8+1;
	//printf("binaryLen: %d\n",*binaryLen);
	char* binaryBuffer = malloc(*binaryLen);
	memset(binaryBuffer, 0, *binaryLen);
	int binaryI=0, bitI=0;
	for(int i=0;i<codeLen;i++){
		binaryI = i/8;
		bitI = i%8;
		//printf("binaryI: %d  bitI: %d    %c %d\n",binaryI, bitI, code[i], (code[i]!='0')?bitIVal[bitI]:0);
		binaryBuffer[binaryI] |= ((code[i]!='0')?bitIVal[7-bitI]:0);
		//printf("binaryBuffer[%d]: ", binaryI);
		//printBinary(binaryBuffer[binaryI]);
	}
	return binaryBuffer;
}

char* binary2Code(char* binaryBuffer, int binaryLen, int *codeLen){
	*codeLen = binaryLen*8;
	printf("codeLen: %d\n", *codeLen);

	char* code = malloc(*codeLen);
	for(int i=0;i<binaryLen;i++){
		for(int j=0;j<8;j++){
			code[i*8+j] = (binaryBuffer[i]&bitIVal[(7-j)])?'1':'0';
		}
	}
	return code;
}

void writeToFile(char* filePath, char* buffer, int size){
	FILE *fp = fopen(filePath, "wb");
	if(fp==NULL){
		printf("Error opening file to write!\n");
		exit(1);
	}
	fwrite(buffer, 1, size, fp);
	fclose(fp);
	return;
}

void writeCode(char* filePath, char charToCode[SYMBOL_N][MAX_CODE_LEN]){
	FILE *fp = fopen(filePath, "w");
	if(fp==NULL){
		printf("Error opening file to write the code! \n");
		exit(1);
	}
	int nonZeroN = 0;
	for(int i=0;i<SYMBOL_N;i++){
		if(strlen(charToCode[i])>0){
			nonZeroN++;
		}
	}
	fprintf(fp, "%d\n",nonZeroN);
	for(int i=0;i<SYMBOL_N;i++){
		if(strlen(charToCode[i])>0){
			fprintf(fp, "%d %s\n",i,charToCode[i]);
		}
	}
	fclose(fp);
	return;
}

void readCode(char* filePath, char charToCode[SYMBOL_N][MAX_CODE_LEN]){
	FILE *fp = fopen(filePath, "r");
	int nonZeroN = 0;
	fscanf(fp, "%d", &nonZeroN);
	fflush(fp);
	for(int i=0;i<nonZeroN;i++){
		int codeNum;
		char code[MAX_CODE_LEN]="";
		fscanf(fp, "%d %s", &codeNum, code);
		printf("codeNum: %d    ",codeNum);
		printf("codeLen: %d\n",strlen(code));
		strncpy(charToCode[codeNum], code, strlen(code));
		printf("%s \n",code);
	}
	fclose(fp);
	return;
}
