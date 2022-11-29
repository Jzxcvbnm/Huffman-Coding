//
// Created by 绫波真美丽 on 2022/11/21.
//

#ifndef HUFFMANTREE_METHOD_H
#define HUFFMANTREE_METHOD_H

#include "HuffmanTree.h"

//基本要求，输入文件，统计，编码字符集并输出
//TODO:
// 1.输出编码（map）
// 注意读取文件字符数（cnt=sample.size()）
void char_code(Huffman &myHuffman);

//中级要求，编码整个文件并保存至一个二进制文件
//TODO:
// 1.输入文件，将txt文件中的内容转化为字符串
// 2.压缩（Compress(const string& sample)）
// 3.将编码保存至一个二进制文件
// 注意读取文件字符数（cnt=sample.size()）
void File_Encode(Huffman &myhuffman);

//高级要求，解码并保存解码结果到一个文本文件，以便与原始的文件作对比
//TODO:
// 1.输入文件，将二进制文件中的内容转化为字符串
// 2.解压缩（Expend(const string& des)）
// 3.将解压后的内容保存至新txt文件中
// 注意读取文件字符数（cnt=sample.size()）
void File_Decode(Huffman &myhuffman);

//向outfp中写入一个比特
//TODO:
// 1.替换fputc()函数
void Write(unsigned int bit);

//强行写入outfp
//TODO:
void WriteToOutfp();

//从infp中读出一个比特
//TODO:
// 1.替换fgetc()函数
// 注意读取数不能超过cnt
void Read(unsigned int &bit);

//初始化哈夫曼树
//TODO:
// 1.输入txt文件，将文件内容读入sample字符串中
// 2.实例化Huffman类（Huffman(const string &sample)）
// 3.建树（BuildTree()），编码（BuildCode()）
void init(Huffman &myHuffman);

#endif //HUFFMANTREE_METHOD_H
