# C-Huffman-Implementation
An Implementation of Huffman Coding in C language

# Usage
## Encoding
```
./encode [FILE_PATH]
```

The code file(containing the huffman code for each character) and the encoded file(the encoded result itself) will be created in paths `[FILE_PATH].code` and `[FILE_PATH].enc` respectfully.
## Decoding
```
./decode [FILE_PATH]
```

Run the above command in the same directory as the code and enc files with the original file paths
The decoded code file will be created in the path `[FILE_PATH].dec`.

# Test Results
Tales of Two Cities (807.2 kb) -> Code File (1.2 kb) + Encoded File (445.5 kb) = 446.7 kb (44.7% Compression)
