#include <fstream>
#include <sstream>
#include"HuffmanTree.h"
#include"method.h"

Huffman myHuffman;//����Ϊȫ�ֱ����������뿪���������������

int main()
{
    char option='0';
    bool done=false;

    cout<<"��������˵����"<<endl;
    cout<<"ͳ�������ļ��ַ�Ƶ�Ȳ����ַ��������벢������ļ�������Ҫ�󣩣� 1"<<endl;
    cout<<"�������ļ������벢�����������һ���������ļ����м�Ҫ�󣩣� 2"<<endl;
    cout<<"�ļ����벢������������Ϊһ���ı��ļ����߼�Ҫ�󣩣� 3"<<endl;
    cout<<"�˳� �� 4"<<endl;
    do {
            cin.sync();
            printf("���������ѡ��");
            fflush(stdout);//���clion��printf()�޷����������̨������
            scanf("%c", &option );//�û�ѡ������������
            //�����û�ѡ�������غ������ָ������
            switch(option) {
                //����Ҫ�������ļ���ͳ�ƣ������ַ��������
                case '1':
                {
                    init(myHuffman);
                    char_code(myHuffman);
                    done=true;
                    break;
                }
                //�м�Ҫ�󣬱����������ļ���������һ���������ļ�
                case '2':
                    if(done){
                        File_Encode(myHuffman);
                    }
                    else{
                        printf("��δ���������\n");
                    }
                    break;
                //�߼�Ҫ�󣬽��벢�����������һ���ı��ļ����Ա���ԭʼ���ļ����Ա�
                case '3':
                    if(done){
                        File_Decode(myHuffman);
                    }
                    else{
                        printf("��δ���������!\n");
                    }
                    break;
                case'4':
                    break;
                default:
                    printf("�����������������\n");
            }
    } while(option != '4' );

    return 0;
}
