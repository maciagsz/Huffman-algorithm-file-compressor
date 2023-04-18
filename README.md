# Huffman algorithm file compressor

## 1. Task analysis
Main goal of the project was to write a program for file compression using Huffman algorithm.
When launched in compression mode, the program will create an encrypted binary file and a character dictionary. 
When the program is launched in decompression mode, the input binary file will be decoded using the dictionary file and saved to its original form.

## 2. Data structures
String type data is used to store the contents of the loaded file. Map of characters and integers stores the frequency of each character. Map of characters and strings assigns the appropriate code to each character.
Additionally, custom data structure Node is useed to store information about the character, its frequency, its corresponding code, and pointers to the left and right node. 
Furthermore, an adapter was created for the priority queue container to store elements of type pointer to Node in a vector container, sorting them based on the ```NodeComparator``` structure.

## 3. Algorithms
After selecting the compression option, the program reads the contents of the file, then creates a dictionary of character frequency based on the information read from the files. 
This dictionary is then saved to a file. The next step is to create a Huffman tree in the form of a priority queue. 
Then, codes are calculated for each character based on the previously created tree. 
The final step is to save the calculated codes to files.

In the case of decompression, the dictionary file is read, and based on it, the program creates a priority queue with the data from the dictionary. The next step is to calculate the codes for each character. Finally, a decompressed file is created using the created codes.

## 4. Internal specifications
The program was written according to the structural paradigm. Functions used in the program are implemented in a ```functions.cpp```file. Custom structures are defined in the ```node.cpp``` file. The file reading interface is located in the ```utils.cpp```.
The program begins its operation by calling the function that reads the command-line arguments. 
After successfully provided information by the user, the compress or decompress function is called depending on the selected mode.
Both of the above functions are callers to specific set of functions to perform the compression algorithm.

Detailed internal specifications can be found in ```Doxygen.pdf``` file in the repository.

## 5. External specifications
The program is launched from the command line. To run the executable file, the user needs to provide the location of the input file, output file, and dictionary, and select the mode - compression or decompression. The program is controlled by switches - i, o, s, t, which can be provided in any order. 
If incorrect switches are provided or the program is called without arguments, a function displaying instructions for using the program will be executed.


Example program call:
```
./Huffman -i 'input_file.txt' -o 'compressed_file.bin' -s 'dictionary.huf' -t k
```

In compression mode, the program accepts input files with any extension and creates a binary-encoded output file and dictionary. 
In the case of decompression, binary files are read, and an output file with the specified name is generated.
