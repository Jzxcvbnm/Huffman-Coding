#include <fstream>
#include <sstream>
#include"HuffmanTree.h"
#include"method.h"

int main()
{
    char option='0';

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
                    init();
                    break;
                //�м�Ҫ�󣬱����������ļ���������һ���������ļ�
                case '2':
                    File_Encode();
                    break;
                //�߼�Ҫ�󣬽��벢�����������һ���ı��ļ����Ա���ԭʼ���ļ����Ա�
                case '3':
                    File_Decode();
                    break;
                case'4':
                    break;
                default:
                    printf("�����������������\n");
            }
    } while(option != '4' );

    return 0;
}
