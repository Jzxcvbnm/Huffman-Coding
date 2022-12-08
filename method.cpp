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
unsigned int cnt=0;

//��ʼ����������
//TODO:
// 1.����txt�ļ������ļ����ݶ���sample�ַ�����
// 2.ʵ����Huffman�ࣨHuffman(const string &sample)��
// 3.������BuildTree()�������루BuildCode()��
void init()
{
    cout << "�������ļ�����";
    string filename;//�����ļ���
    cin >> filename;
    ifstream ifile;//ofstream�Ǵ��ڴ浽Ӳ�̣�ifstream�Ǵ�Ӳ�̵��ڴ棬��ʵ��ν������������ڴ�ռ�
    ifile.open(filename);
    if (ifile.fail()) {
        cout<< "���ܴ��ļ�:" << filename;
        exit(-1);
    }
    ostringstream filebuf;//���ļ����뵽ostringstream����filebuf��
    char tempch;

    while (filebuf && ifile.get(tempch)) {
        filebuf.put(tempch);
    }

    string sample;
    sample.clear();
    sample = filebuf.str();//������������buf�������ַ���
    cout << sample << endl;//���Զ�ȡ�Ƿ���ȷ

    Huffman newHuffman(sample);
    newHuffman.BuildTree();
    newHuffman.BuildCode();
    ifile.close();
    char_code(newHuffman);
    //�������д���ļ�
    string codefilename;
    cout << "������Ҫ����ı�����ļ�����";
    cin>>codefilename;
    ofstream codefile(codefilename);
    for(const auto& pair : newHuffman.mymap) {
        codefile<<pair.first<<","<<pair.second<<",";
    }
    codefile.close();
}

//�߼�Ҫ�󣬽��벢�����������һ���ı��ļ����Ա���ԭʼ���ļ����Ա�
//TODO:
// 1.�����ļ������������ļ��е�����ת��Ϊ�ַ���des
// 2.��ѹ����Expend(const string& des)��
// 3.����ѹ������ݱ�������txt�ļ���
// ע������ļ��ַ�����cnt=temp.size();��
void File_Decode()
{
    string codefilename;
    cout << "����������Ҫ�ı�����ļ�����";
    cin >> codefilename;
    string freqstring = readFreqString(codefilename);
    //��������
    Huffman newHuffman(freqstring);
    newHuffman.BuildTree();
    newHuffman.BuildCode();

    string des;//��ȡ�ı����ַ���
    des.clear();
    cout << "������Ҫ��ѹ���ļ�����";
    string decode_filename;//����Ҫ��ѹ�Ķ������ļ���
    cin >> decode_filename;
    infp.open(decode_filename, ios::binary);//���ļ���infp����

    //����cnt
    string codelength = newHuffman.Compress(freqstring);
    cnt = codelength.size();

    buf = { 0,0 };//ÿ�α���ǰ��Ҫ��ʼ������Ȼ�ظ������ļ���ػ��б������
    for (int i = 0; i < cnt; ++i) {
        unsigned int r = 0;//�洢��ȡ�ַ��ı���
        Read(r);
        char cur = r + '0';
        des += cur;
    }
    infp.close();

    string temp;//��Ž�����
    temp.clear();
    temp = newHuffman.Expend(des);

    cout << "�����뱣���ѹ������ļ�����";
    string result_filename;//����Ҫ��ѹ�Ķ������ļ���
    cin >> result_filename;
    ofstream rfile(result_filename);
    rfile << temp;
    rfile.close();

    //�����Ƿ��ȡ�ɹ�
    string test;
    ifstream testfile(result_filename);
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
void File_Encode()
{
    string codefilename;
    cout<<"����������Ҫ�ı�����ļ�����";
    cin>>codefilename;
    string freqstring= readFreqString(codefilename);
    //��������
    Huffman newHuffman(freqstring);
    newHuffman.BuildTree();
    newHuffman.BuildCode();

    //��ȡҪѹ�����ļ�����
    cout << "������Ҫѹ�����ļ�����";
    string filename;//�����ļ���
    cin >> filename;
    ifstream ifile;//ofstream�Ǵ��ڴ浽Ӳ�̣�ifstream�Ǵ�Ӳ�̵��ڴ棬��ʵ��ν������������ڴ�ռ�
    ifile.open(filename);
    if (ifile.fail()) {
        cout<< "���ܴ��ļ�:" << filename;
        exit(-1);
    }
    ostringstream filebuf;//���ļ����뵽ostringstream����filebuf��
    char tempch;

    while (filebuf && ifile.get(tempch)) {
        filebuf.put(tempch);
    }

    string sample;
    sample.clear();
    sample = filebuf.str();//������������buf�������ַ���

    //���б������
    cout << "������Ҫ����Ķ������ļ�����";
    string bfilename;//����Ҫ����Ķ������ļ���
    cin >> bfilename;
    outfp.open(bfilename,ios::trunc|ios::binary);//���ļ���outfp����
    string temp=newHuffman.Compress(sample);
    cout<<temp<<endl;//����ѹ�����
    cnt=temp.size();

    buf={0,0};//ÿ�α���ǰ��Ҫ��ʼ������Ȼ�ظ������ļ���ػ��б������
    for(auto cur:temp){
        unsigned int i=cur-'0';
        Write(i);
    }
    WriteToOutfp();
    outfp.close();

    cout<<"ѹ����Ϊ��"<<compression_ratio(newHuffman.mymap.size(),newHuffman)<<endl;
}

//��ȡ�����
//TODO��
// 1.�����ļ������ҵ�Ƶ���ļ���ת����AAABBB
string readFreqString(const string& codefilename)
{
//    string freqstring;
//    freqstring.clear();
//    ifstream codefile;//ofstream�Ǵ��ڴ浽Ӳ�̣�ifstream�Ǵ�Ӳ�̵��ڴ棬��ʵ��ν������������ڴ�ռ�
//    codefile.open(codefilename);
//    if (codefile.fail()) {
//        cout<< "���ܴ��ļ�:" << codefilename;
//        exit(-1);
//    }
//    char curch;
//    char prech;
//    string temp;//�洢�ַ�������
//    temp.clear();
//
//    //��ȡ�����
//    int comma_cnt=0;
//    bool now_num=false;
//    for (int i=0 ; codefile.get(curch); ++i) {
//        //��������ʱ����֮ǰ�Ļ���
//        if(curch==','){
//            //�ж϶���
//            comma_cnt++;
//            if(comma_cnt==2){
//                temp+=curch;
//                comma_cnt=0;
//                now_num=false;
//                continue;
//            }
//
//            //��������
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
//            //�����ַ�
//            else{
//                char tempch=temp[0];
//                prech=tempch;
//                temp.clear();
//                now_num=true;
//            }
//        }
//
//        //���涺��ǰ���ַ�
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
        printf("��Ƶ���ļ�ʧ�ܣ�\n");
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

//����Ҫ�������ļ���ͳ�ƣ������ַ��������
//TODO:
// 1.������루map��
void char_code(Huffman &newHuffman)
{
    for(const auto& pair : newHuffman.map) {
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

//����ѹ����
//numΪ�������ַ���
double compression_ratio(int num,Huffman &newhuffman)
{
    double ret=0;
    //����С������
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

