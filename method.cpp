//
// Created by 绫波真美丽 on 2022/11/21.
//

#include <fstream>
#include <sstream>
#include "method.h"
#include "HuffmanTree.h"

//字节缓冲
struct Buffer{
    char ch;
    unsigned int bits;
};//实际比特数

struct Buffer buf={'0',0};
//ofstream是从内存到硬盘，ifstream是从硬盘到内存，其实所谓的流缓冲就是内存空间
ofstream outfp;
ifstream infp;
string sample;//将txt文件中的内容读入此字符串
unsigned int cnt=0;

//初始化哈夫曼树
//TODO:
// 1.输入txt文件，将文件内容读入sample字符串中
// 2.实例化Huffman类（Huffman(const string &sample)）
// 3.建树（BuildTree()），编码（BuildCode()）
void init(Huffman &myHuffman)
{
    cout << "请输入文件名：";
    string filename;//输入文件名
    cin >> filename;
    ifstream ifile(filename);//ofstream是从内存到硬盘，ifstream是从硬盘到内存，其实所谓的流缓冲就是内存空间
    ostringstream filebuf;//将文件读入到ostringstream对象filebuf中
    char tempch;

    while (filebuf && ifile.get(tempch)) {
        filebuf.put(tempch);
    }

    sample.clear();
    sample = filebuf.str();//返回与流对象buf关联的字符串
    cout << sample << endl;//测试读取是否正确

    Huffman newHuffman(sample);
    myHuffman=newHuffman;
    myHuffman.BuildTree();
    myHuffman.BuildCode();
    ifile.close();
}

//高级要求，解码并保存解码结果到一个文本文件，以便与原始的文件作对比
//TODO:
// 1.输入文件，将二进制文件中的内容转化为字符串des
// 2.解压缩（Expend(const string& des)）
// 3.将解压后的内容保存至新txt文件中
// 注意控制文件字符数（cnt=temp.size();）
void File_Decode(Huffman &myhuffman)
{
    string des;
    des.clear();
    cout << "请输入要解压的文件名：";
    string decode_filename;//输入要解压的二进制文件名
    cin >> decode_filename;
    infp.open(decode_filename,ios::binary);//将文件与infp关联

    for (int i = 0; i < cnt; ++i) {
        unsigned int r = 0;//存储读取字符的变量
        Read(r);
        char cur=r+'0';
        des+=cur;
    }

    infp.close();

    string temp=myhuffman.Expend(des);

    cout << "请输入保存解压结果的文件名：";
    string result_filename;//输入要解压的二进制文件名
    cin >> result_filename;
    ofstream rfile(result_filename);
    rfile << temp;
    rfile.close();

    string test;
    ifstream testfile(result_filename);//测试是否读取成功
    ostringstream filebuf;//将文件读入到ostringstream对象filebuf中
    char tempch;

    while (filebuf && testfile.get(tempch)) {
        filebuf.put(tempch);
    }

    test.clear();
    test = filebuf.str();//返回与流对象buf关联的字符串
    cout << test << endl;
    testfile.close();
}

//中级要求，编码整个文件并保存至一个二进制文件
//TODO:
// 1.压缩（Compress(const string& sample)）
// 2.将编码保存至一个二进制文件
// 注意读取文件字符数（cnt=temp.size();）
void File_Encode(Huffman &myhuffman)
{
    buf={'0',0};//每次编码前都要初始化，不然重复输入文件后必会有编码错误
    cout << "请输入要保存的二进制文件名：";
    string filename;//输入要保存的二进制文件名
    cin >> filename;
    outfp.open(filename,ios::trunc);//将文件与outfp关联
    string temp=myhuffman.Compress(sample);
    cout<<temp<<endl;//测试压缩结果
    cnt=temp.size();

    for(auto cur:temp){
        unsigned int i=cur-'0';
        Write(i);
    }
    WriteToOutfp();
    outfp.close();

    
    cout<<"压缩比为："<<endl;
}

//基本要求，输入文件，统计，编码字符集并输出
//TODO:
// 1.输出编码（map）
// 注意解码文件字符数不超过原读入数（cnt）
void char_code(Huffman &myHuffman)
{
    for(const auto& pair : myHuffman.map) {
        //回车不直接输出
        if(pair.first=='\n'){
            cout<<"\\n"<<" : "<< pair.second<< endl;
        }

        else{
            cout << pair.first << " : " << pair.second << endl;
        }
    }
}

//从infp中读出一个比特
//TODO:
// 1.替换fgetc()函数
// 注意读取数不能超过cnt
void Read(unsigned int &bit)
{
    if (buf.bits==0)
    {
        infp.get(buf.ch);
        buf.bits=8;
    }

    bit=(buf.ch & 128)>>7;
    buf.ch=buf.ch<<1;
    buf.bits--;
}

//向outfp中写入一个比特
//TODO:
// 1.替换fputc()函数
void Write(unsigned int bit)
{
    buf.bits++;
    buf.ch=(buf.ch<<1)+bit;

    if(buf.bits==8) //缓冲区已满,写入outfp
    {
        outfp<<buf.ch;
        buf.bits=0;
        buf.ch=0;
    }
}

//强行写入outfp
//TODO:
void WriteToOutfp()
{
    unsigned int l=buf.bits;
    if (l>0)
    {
        for(unsigned int i=0;i<8-l;i++)
        {
            Write(0);
        }
    }
}


