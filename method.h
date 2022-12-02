//
// Created by 绫波真美丽 on 2022/11/21.
//

#ifndef HUFFMANTREE_METHOD_H
#define HUFFMANTREE_METHOD_H

#include "HuffmanTree.h"

void char_code(Huffman &newHuffman);

void File_Encode();

void File_Decode();

void Write(unsigned int bit);

void WriteToOutfp();

void Read(unsigned int &bit);

void init();

double compression_ratio(int num,Huffman &newhuffman);

string readFreqString(const string& codefilename);

#endif //HUFFMANTREE_METHOD_H
