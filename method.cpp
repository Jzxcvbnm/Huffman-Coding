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
unsigned int cnt=0;

//初始化哈夫曼树
//TODO:
// 1.输入txt文件，将文件内容读入sample字符串中
// 2.实例化Huffman类（Huffman(const string &sample)）
// 3.建树（BuildTree()），编码（BuildCode()）
void init()
{
    cout << "请输入文件名：";
    string filename;//输入文件名
    cin >> filename;
    ifstream ifile;//ofstream是从内存到硬盘，ifstream是从硬盘到内存，其实所谓的流缓冲就是内存空间
    ifile.open(filename);
    if (ifile.fail()) {
        cout<< "不能打开文件:" << filename;
        exit(-1);
    }
    ostringstream filebuf;//将文件读入到ostringstream对象filebuf中
    char tempch;

    while (filebuf && ifile.get(tempch)) {
        filebuf.put(tempch);
    }

    string sample;
    sample.clear();
    sample = filebuf.str();//返回与流对象buf关联的字符串
    cout << sample << endl;//测试读取是否正确

    Huffman newHuffman(sample);
    newHuffman.BuildTree();
    newHuffman.BuildCode();
    ifile.close();
    char_code(newHuffman);
    //将编码表写入文件
    string codefilename;
    cout << "请输入要保存的编码表文件名：";
    cin>>codefilename;
    ofstream codefile(codefilename);
    for(const auto& pair : newHuffman.mymap) {
        codefile<<pair.first<<","<<pair.second<<",";
    }
    codefile.close();
}

//高级要求，解码并保存解码结果到一个文本文件，以便与原始的文件作对比
//TODO:
// 1.输入文件，将二进制文件中的内容转化为字符串des
// 2.解压缩（Expend(const string& des)）
// 3.将解压后的内容保存至新txt文件中
// 注意控制文件字符数（cnt=temp.size();）
void File_Decode()
{
    string codefilename;
    cout << "请输入所需要的编码表文件名：";
    cin >> codefilename;
    string freqstring = readFreqString(codefilename);
    //建立新树
    Huffman newHuffman(freqstring);
    newHuffman.BuildTree();
    newHuffman.BuildCode();

    string des;//读取的编码字符串
    des.clear();
    cout << "请输入要解压的文件名：";
    string decode_filename;//输入要解压的二进制文件名
    cin >> decode_filename;
    infp.open(decode_filename, ios::binary);//将文件与infp关联

    //计算cnt
    string codelength = newHuffman.Compress(freqstring);
    cnt = codelength.size();

    buf = { 0,0 };//每次编码前都要初始化，不然重复输入文件后必会有编码错误
    for (int i = 0; i < cnt; ++i) {
        unsigned int r = 0;//存储读取字符的变量
        Read(r);
        char cur = r + '0';
        des += cur;
    }
    infp.close();

    string temp;//存放解码结果
    temp.clear();
    temp = newHuffman.Expend(des);

    cout << "请输入保存解压结果的文件名：";
    string result_filename;//输入要解压的二进制文件名
    cin >> result_filename;
    ofstream rfile(result_filename);
    rfile << temp;
    rfile.close();

    //测试是否读取成功
    string test;
    ifstream testfile(result_filename);
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
void File_Encode()
{
    string codefilename;
    cout<<"请输入所需要的编码表文件名：";
    cin>>codefilename;
    string freqstring= readFreqString(codefilename);
    //建立新树
    Huffman newHuffman(freqstring);
    newHuffman.BuildTree();
    newHuffman.BuildCode();

    //读取要压缩的文件内容
    cout << "请输入要压缩的文件名：";
    string filename;//输入文件名
    cin >> filename;
    ifstream ifile;//ofstream是从内存到硬盘，ifstream是从硬盘到内存，其实所谓的流缓冲就是内存空间
    ifile.open(filename);
    if (ifile.fail()) {
        cout<< "不能打开文件:" << filename;
        exit(-1);
    }
    ostringstream filebuf;//将文件读入到ostringstream对象filebuf中
    char tempch;

    while (filebuf && ifile.get(tempch)) {
        filebuf.put(tempch);
    }

    string sample;
    sample.clear();
    sample = filebuf.str();//返回与流对象buf关联的字符串

    //进行编码操作
    cout << "请输入要保存的二进制文件名：";
    string bfilename;//输入要保存的二进制文件名
    cin >> bfilename;
    outfp.open(bfilename,ios::trunc|ios::binary);//将文件与outfp关联
    string temp=newHuffman.Compress(sample);
    cout<<temp<<endl;//测试压缩结果
    cnt=temp.size();

    buf={0,0};//每次编码前都要初始化，不然重复输入文件后必会有编码错误
    for(auto cur:temp){
        unsigned int i=cur-'0';
        Write(i);
    }
    WriteToOutfp();
    outfp.close();

    cout<<"压缩比为："<<compression_ratio(newHuffman.mymap.size(),newHuffman)<<endl;
}

//读取编码表
//TODO：
// 1.输入文件名，找到频度文件，转化成AAABBB
string readFreqString(const string& codefilename)
{
//    string freqstring;
//    freqstring.clear();
//    ifstream codefile;//ofstream是从内存到硬盘，ifstream是从硬盘到内存，其实所谓的流缓冲就是内存空间
//    codefile.open(codefilename);
//    if (codefile.fail()) {
//        cout<< "不能打开文件:" << codefilename;
//        exit(-1);
//    }
//    char curch;
//    char prech;
//    string temp;//存储字符或数字
//    temp.clear();
//
//    //读取编码表
//    int comma_cnt=0;
//    bool now_num=false;
//    for (int i=0 ; codefile.get(curch); ++i) {
//        //遇到逗号时处理之前的缓存
//        if(curch==','){
//            //判断逗号
//            comma_cnt++;
//            if(comma_cnt==2){
//                temp+=curch;
//                comma_cnt=0;
//                now_num=false;
//                continue;
//            }
//
//            //处理数字
//            if(now_num) {
//                stringstream string_num;
//                string_num << temp;
//                int tempn = 0;
//                string_num >> tempn;
//                for (int j = 0; j < tempn; ++j) {
//                    freqstring += prech;
//                }
//                string_num.clear();
//                temp.clear();
//                now_num=false;
//            }
//
//            //处理字符
//            else{
//                char tempch=temp[0];
//                prech=tempch;
//                temp.clear();
//                now_num=true;
//            }
//        }
//
//        //缓存逗号前的字符
//        else{
//            temp+=curch;
//            comma_cnt=0;
//        }
//
//    }
//
//    return freqstring;

    string out;
    FILE* fp;
    if ((fp = fopen(codefilename.c_str(), "r+")) == NULL) {
        printf("打开频数文件失败！\n");
        exit(-1);
    }
    else {
        char ch1 = 0;
        int num1 = 0;
        string str_temp = "";
        while (fscanf(fp, "%c,%d,", &ch1, &num1) != -1) {
            str_temp = ch1;
            for (int i = 0; i < num1; i++) {
                out.append(str_temp);
            }
        }
    }
    fclose(fp);
    return out;
}

//基本要求，输入文件，统计，编码字符集并输出
//TODO:
// 1.输出编码（map）
void char_code(Huffman &newHuffman)
{
    for(const auto& pair : newHuffman.map) {
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

//计算压缩比
//num为多少种字符数
double compression_ratio(int num,Huffman &newhuffman)
{
    double ret=0;
    //求最小二次幂
    int max = 1 << 30;
    int n = num - 1;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    int temp = n < 0 ? 1 : (n >= max ? max : n + 1);
    int origin_digit = 0;
    for (int i = temp; i != 1; i/=2) {
        origin_digit++;
    }

    double present_digit = 0;
    double freq_sum=0;
    double digit_sum=0;
    for (const auto& pair : newhuffman.mymap) {
        //unordered_mymap<char, int>::const_iterator pair
        freq_sum+=pair.second;
    }
    for (const auto& pair : newhuffman.map) {
        //unordered_map<char, string>::const_iterator pair
        digit_sum+=pair.second.size()*newhuffman.mymap[pair.first];
    }
    present_digit=digit_sum/freq_sum;
    ret=(origin_digit-present_digit)/origin_digit;
    return ret;
}

