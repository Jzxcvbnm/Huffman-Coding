//
// Created by 绫波真美丽 on 2022/11/21.
//

#include "HuffmanTree.h"

//依据字符串生成编码表以及权重数组
Huffman::Huffman(const string &sample)
{
    int len = sample.length();
    if (len == 0) { cout << "初始化失败，请重新输入字符串！" << endl; exit(-1); }

    for (int i = 0; i < len; ++i) {//依据输入字符串初始化哈希表
        if (mymap.find(sample[i]) == mymap.end())
            //插入映射
            mymap[sample[i]] = 1;
        else
            mymap[sample[i]] += 1;//频数++
    }
    for (const auto& pair : mymap) {//遍历哈希表，并将key与value分别压入编码表与频率数组中
        //unordered_map<char, int>::const_iterator pair
        st.push_back(pair.first);
        freq.push_back(pair.second);
    }
}

Huffman::Huffman() {

}

//析构函数
Huffman::~Huffman()
{
    _del(Root);//遍历哈夫曼树
}

//判断节点是否为叶子结点
bool Huffman::IsLeaf(HFTNode* Root)
{
    if(Root==nullptr) return false;
    if (Root->leftchild == nullptr && Root->rightchild == nullptr)
        return true;
    else
        return false;
}

//构建一颗哈夫曼树
void Huffman::BuildTree()
{
    priority_queue<HFTNode> myqueue;//使用最小优先级队列存储节点
    for (int i = 0; i < freq.size(); i++){//节点初始化，并将节点压入最小优先级队列中
        HFTNode* temp = new HFTNode(freq[i]);
        temp->ch = i;
        myqueue.push(*temp);
    }
    //合并节点并生成树
    while (myqueue.size() > 1) {
        //从队列中取出两个最小元素作为新子树的左孩子和右孩子
        HFTNode left = myqueue.top();
        myqueue.pop();
        HFTNode right = myqueue.top();
        myqueue.pop();
        //创建新子树的根节点，并将其压入队列中
        HFTNode* parent = new HFTNode(left.weight + right.weight);
        parent->ch = -1;//设定子树生成的根结点下标值是-1，只做区分用
        parent->leftchild = &left;
        parent->rightchild = &right;
        myqueue.push(*parent);
    }
    //生成哈夫曼树的根结点
    Root = new HFTNode();
    *Root = myqueue.top();
    myqueue.pop();
}

//根据哈夫曼树构建编码表
void Huffman::BuildCode()
{
    if (Root == nullptr) return;
    //string temp('\0');
    string temp;
    temp.clear();//初始化为空字符串
    _build(Root, temp);
}

//解压缩
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

//压缩
string Huffman::Compress(const string& sample)
{
    string res;
    for (int i = 0; i < sample.length(); ++i) {
//        if (sample[i] == '\n'||sample[i]==' ')
//            continue;不需要跳过换行和空格
        res += map[sample[i]];
    }
    return res;
}

//删除哈夫曼树
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
//        cout << str << "    ";//测试编码
        map[st[root->ch]] = str;
        return;
    }
    if(root->leftchild) _build(root->leftchild, str + '0');
    if(root->rightchild) _build(root->rightchild, str + '1');
}

