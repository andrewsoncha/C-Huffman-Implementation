#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(int argc, char *argv[]){
	int freq[256];
	if(argc<2){
		printf("Usage: huffman [CONTENT]\n");
		return -1;
	}
	
	printf("argv[1]: %s\n", argv[1]);
	int nodeN=0;
	struct NodeVal **freq_arr;
	freq_arr = get_freq(argv[1], &nodeN);
	build_tree(freq_arr, nodeN);

	return 0;
}
