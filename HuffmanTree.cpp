//
// Created by 籲������� on 2022/11/21.
//

#include "HuffmanTree.h"

//�����ַ������ɱ�����Լ�Ȩ������
Huffman::Huffman(const string &sample)
{
    int len = sample.length();
    if (len == 0) { cout << "��ʼ��ʧ�ܣ������������ַ�����" << endl; exit(-1); }

    for (int i = 0; i < len; ++i) {//���������ַ�����ʼ����ϣ��
        if (mymap.find(sample[i]) == mymap.end())
            //����ӳ��
            mymap[sample[i]] = 1;
        else
            mymap[sample[i]] += 1;//Ƶ��++
    }
    for (const auto& pair : mymap) {//������ϣ������key��value�ֱ�ѹ��������Ƶ��������
        //unordered_map<char, int>::const_iterator pair
        st.push_back(pair.first);
        freq.push_back(pair.second);
    }
}

Huffman::Huffman() {

}

//��������
Huffman::~Huffman()
{
    _del(Root);//������������
}

//�жϽڵ��Ƿ�ΪҶ�ӽ��
bool Huffman::IsLeaf(HFTNode* Root)
{
    if(Root==nullptr) return false;
    if (Root->leftchild == nullptr && Root->rightchild == nullptr)
        return true;
    else
        return false;
}

//����һ�Ź�������
void Huffman::BuildTree()
{
    priority_queue<HFTNode> myqueue;//ʹ����С���ȼ����д洢�ڵ�
    for (int i = 0; i < freq.size(); i++){//�ڵ��ʼ���������ڵ�ѹ����С���ȼ�������
        HFTNode* temp = new HFTNode(freq[i]);
        temp->ch = i;
        myqueue.push(*temp);
    }
    //�ϲ��ڵ㲢������
    while (myqueue.size() > 1) {
        //�Ӷ�����ȡ��������СԪ����Ϊ�����������Ӻ��Һ���
        HFTNode left = myqueue.top();
        myqueue.pop();
        HFTNode right = myqueue.top();
        myqueue.pop();
        //�����������ĸ��ڵ㣬������ѹ�������
        HFTNode* parent = new HFTNode(left.weight + right.weight);
        parent->ch = -1;//�趨�������ɵĸ�����±�ֵ��-1��ֻ��������
        parent->leftchild = &left;
        parent->rightchild = &right;
        myqueue.push(*parent);
    }
    //���ɹ��������ĸ����
    Root = new HFTNode();
    *Root = myqueue.top();
    myqueue.pop();
}

//���ݹ����������������
void Huffman::BuildCode()
{
    if (Root == nullptr) return;
    //string temp('\0');
    string temp;
    temp.clear();//��ʼ��Ϊ���ַ���
    _build(Root, temp);
}

//��ѹ��
string Huffman::Expend(const string& des)
{
    string res;
    int i(0), n(des.size());
    HFTNode* temp = new HFTNode();
    temp = Root;
    while (i < n) {
        if (des[i]=='0')
        {
            temp = temp->leftchild;
            i++;
            if (IsLeaf(temp)) {
                res += st[temp->ch];
                temp = Root;
                continue;
            }
        }
        if (des[i] == '1')
        {
            temp = temp->rightchild;
            i++;
            if (IsLeaf(temp)) {
                res += st[temp->ch];
                temp = Root;
                continue;
            }
        }
    }
    return res;
}

//ѹ��
string Huffman::Compress(const string& sample)
{
    string res;
    for (int i = 0; i < sample.length(); ++i) {
//        if (sample[i] == '\n'||sample[i]==' ')
//            continue;����Ҫ�������кͿո�
        res += map[sample[i]];
    }
    return res;
}

//ɾ����������
void Huffman::_del(HFTNode* root)
{
    if (root == nullptr)
        return;
    if (root->leftchild)
        _del(root->leftchild);
    if (root->rightchild)
        _del(root->rightchild);
}

void Huffman::_build(HFTNode* root, string str)
{
    if (IsLeaf(root) && root->ch >= 0) {
//        cout << str << "    ";//���Ա���
        map[st[root->ch]] = str;
        return;
    }
    if(root->leftchild) _build(root->leftchild, str + '0');
    if(root->rightchild) _build(root->rightchild, str + '1');
}

