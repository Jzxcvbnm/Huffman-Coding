//
// Created by 绫波真美丽 on 2022/11/21.
//
#ifndef HUFFMANTREE_HUFFMANTREE_H
#define HUFFMANTREE_HUFFMANTREE_H

#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;

//哈夫曼树结点类
class HFTNode{
public:
    int weight;//节点的权重
    int ch;//存储节点的下标
    HFTNode* leftchild, * rightchild;//创建该结点的左右孩子指针
    HFTNode() ://哈夫曼树节点类初始化
            leftchild(nullptr), rightchild(nullptr) {}
    HFTNode(int data) ://哈夫曼树节点类初始化
            leftchild(nullptr), rightchild(nullptr), weight(data) {}
    //拷贝构造函数
    HFTNode(const HFTNode& N) {
        ch = N.ch;
        weight = N.weight;
        if (N.leftchild) {
            leftchild = new HFTNode();
            *leftchild = *(N.leftchild);
        }
        else
            leftchild = nullptr;
        if (N.rightchild) {
            rightchild = new HFTNode();
            *rightchild = *(N.rightchild);
        }
        else
            rightchild = nullptr;
    }
    // 重载"<"符号，令其为最小值优先
    bool operator < (const HFTNode& N) const{
        return weight > N.weight;
    }
};

//哈夫曼树类
class Huffman{
public:
    Huffman();

    Huffman(const string &sample);//构造函数，传入字符串引用，减少调用开支
    ~Huffman();// 析构函数

    bool IsLeaf(HFTNode* Root);//判断节点是否为叶子结点
    void GetFreq(vector<int> &des);//获取当前的权重数组
    void BuildTree();//构建一颗哈夫曼树
    void BuildCode();//根据哈夫曼树构建编码表
    void GetCodeList();//遍历编码表和编码表对应的编码

    //前序遍历和中序遍历是为了确定哈夫曼树的形状是否正确
    void PreOrder();
    void InOrder();

    string Expend(const string &des);//解压缩
    string Compress(const string &des);//压缩

    unordered_map<char, string> map;

private:
    void _del(HFTNode* root);//删除哈夫曼树
    void _build(HFTNode* root, string str);//生成map的key与value值
    void _PreOrder(HFTNode* root);
    void _InOrder(HFTNode* root);
    //key为编码表的字符，value为编码表的字符对应的编码形式例如“101”，“111”
    unordered_map<char, int> mymap;
    vector<int> freq; // 权重数组
    vector<char> st; // 编码表

    HFTNode* Root; // 哈夫曼树根节点
};

#endif //HUFFMANTREE_HUFFMANTREE_H
