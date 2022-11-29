#include <fstream>
#include <sstream>
#include"HuffmanTree.h"
#include"method.h"

Huffman myHuffman;//设置为全局变量，避免离开函数作用域后消亡

int main()
{
    char option='0';
    bool done=false;

    cout<<"操作命令说明："<<endl;
    cout<<"统计输入文件字符频度并对字符集编括码并输出至文件（基本要求）： 1"<<endl;
    cout<<"对整个文件编括码并保存编码结果到一个二进制文件（中级要求）： 2"<<endl;
    cout<<"文件解码并将解码结果保存为一个文本文件（高级要求）： 3"<<endl;
    cout<<"退出 ： 4"<<endl;
    do {
            cin.sync();
            printf("请输入你的选择：");
            fflush(stdout);//解决clion中printf()无法输出到控制台的问题
            scanf("%c", &option );//用户选择操作命令键入
            //根据用户选择调用相关函数完成指定操作
            switch(option) {
                //基本要求，输入文件，统计，编码字符集并输出
                case '1':
                {
                    init(myHuffman);
                    char_code(myHuffman);
                    done=true;
                    break;
                }
                //中级要求，编括码整个文件并保存至一个二进制文件
                case '2':
                    if(done){
                        File_Encode(myHuffman);
                    }
                    else{
                        printf("尚未建立编码表！\n");
                    }
                    break;
                //高级要求，解码并保存解码结果到一个文本文件，以便与原始的文件作对比
                case '3':
                    if(done){
                        File_Decode(myHuffman);
                    }
                    else{
                        printf("尚未建立编码表!\n");
                    }
                    break;
                case'4':
                    break;
                default:
                    printf("输入错误！请重新输入\n");
            }
    } while(option != '4' );

    return 0;
}
