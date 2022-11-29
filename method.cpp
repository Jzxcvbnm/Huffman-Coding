//
// Created by 籲������� on 2022/11/21.
//

#include <fstream>
#include <sstream>
#include "method.h"
#include "HuffmanTree.h"

//�ֽڻ���
struct Buffer{
    char ch;
    unsigned int bits;
};//ʵ�ʱ�����

struct Buffer buf={'0',0};
//ofstream�Ǵ��ڴ浽Ӳ�̣�ifstream�Ǵ�Ӳ�̵��ڴ棬��ʵ��ν������������ڴ�ռ�
ofstream outfp;
ifstream infp;
string sample;//��txt�ļ��е����ݶ�����ַ���
unsigned int cnt=0;

//��ʼ����������
//TODO:
// 1.����txt�ļ������ļ����ݶ���sample�ַ�����
// 2.ʵ����Huffman�ࣨHuffman(const string &sample)��
// 3.������BuildTree()�������루BuildCode()��
void init(Huffman &myHuffman)
{
    cout << "�������ļ�����";
    string filename;//�����ļ���
    cin >> filename;
    ifstream ifile(filename);//ofstream�Ǵ��ڴ浽Ӳ�̣�ifstream�Ǵ�Ӳ�̵��ڴ棬��ʵ��ν������������ڴ�ռ�
    ostringstream filebuf;//���ļ����뵽ostringstream����filebuf��
    char tempch;

    while (filebuf && ifile.get(tempch)) {
        filebuf.put(tempch);
    }

    sample.clear();
    sample = filebuf.str();//������������buf�������ַ���
    cout << sample << endl;//���Զ�ȡ�Ƿ���ȷ

    Huffman newHuffman(sample);
    myHuffman=newHuffman;
    myHuffman.BuildTree();
    myHuffman.BuildCode();
    ifile.close();
}

//�߼�Ҫ�󣬽��벢�����������һ���ı��ļ����Ա���ԭʼ���ļ����Ա�
//TODO:
// 1.�����ļ������������ļ��е�����ת��Ϊ�ַ���des
// 2.��ѹ����Expend(const string& des)��
// 3.����ѹ������ݱ�������txt�ļ���
// ע������ļ��ַ�����cnt=temp.size();��
void File_Decode(Huffman &myhuffman)
{
    string des;
    des.clear();
    cout << "������Ҫ��ѹ���ļ�����";
    string decode_filename;//����Ҫ��ѹ�Ķ������ļ���
    cin >> decode_filename;
    infp.open(decode_filename,ios::binary);//���ļ���infp����

    for (int i = 0; i < cnt; ++i) {
        unsigned int r = 0;//�洢��ȡ�ַ��ı���
        Read(r);
        char cur=r+'0';
        des+=cur;
    }

    infp.close();

    string temp=myhuffman.Expend(des);

    cout << "�����뱣���ѹ������ļ�����";
    string result_filename;//����Ҫ��ѹ�Ķ������ļ���
    cin >> result_filename;
    ofstream rfile(result_filename);
    rfile << temp;
    rfile.close();

    string test;
    ifstream testfile(result_filename);//�����Ƿ��ȡ�ɹ�
    ostringstream filebuf;//���ļ����뵽ostringstream����filebuf��
    char tempch;

    while (filebuf && testfile.get(tempch)) {
        filebuf.put(tempch);
    }

    test.clear();
    test = filebuf.str();//������������buf�������ַ���
    cout << test << endl;
    testfile.close();
}

//�м�Ҫ�󣬱��������ļ���������һ���������ļ�
//TODO:
// 1.ѹ����Compress(const string& sample)��
// 2.�����뱣����һ���������ļ�
// ע���ȡ�ļ��ַ�����cnt=temp.size();��
void File_Encode(Huffman &myhuffman)
{
    buf={'0',0};//ÿ�α���ǰ��Ҫ��ʼ������Ȼ�ظ������ļ���ػ��б������
    cout << "������Ҫ����Ķ������ļ�����";
    string filename;//����Ҫ����Ķ������ļ���
    cin >> filename;
    outfp.open(filename,ios::trunc);//���ļ���outfp����
    string temp=myhuffman.Compress(sample);
    cout<<temp<<endl;//����ѹ�����
    cnt=temp.size();

    for(auto cur:temp){
        unsigned int i=cur-'0';
        Write(i);
    }
    WriteToOutfp();
    outfp.close();

    
    cout<<"ѹ����Ϊ��"<<endl;
}

//����Ҫ�������ļ���ͳ�ƣ������ַ��������
//TODO:
// 1.������루map��
// ע������ļ��ַ���������ԭ��������cnt��
void char_code(Huffman &myHuffman)
{
    for(const auto& pair : myHuffman.map) {
        //�س���ֱ�����
        if(pair.first=='\n'){
            cout<<"\\n"<<" : "<< pair.second<< endl;
        }

        else{
            cout << pair.first << " : " << pair.second << endl;
        }
    }
}

//��infp�ж���һ������
//TODO:
// 1.�滻fgetc()����
// ע���ȡ�����ܳ���cnt
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

//��outfp��д��һ������
//TODO:
// 1.�滻fputc()����
void Write(unsigned int bit)
{
    buf.bits++;
    buf.ch=(buf.ch<<1)+bit;

    if(buf.bits==8) //����������,д��outfp
    {
        outfp<<buf.ch;
        buf.bits=0;
        buf.ch=0;
    }
}

//ǿ��д��outfp
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


