
//work.cpp
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include "bank.h"
using namespace std;
int BASE::chooseInMenu()
//���ܣ���ʾ�˵�����ҵ��Աѡ��
{
    int i;
    while(1)
    {
        cout<<endl;;
        cout<<" ____________________________ "<<endl;
		cout<<"|                            |"<<endl;
		cout<<"|                            |"<<endl;
        cout<<"| 1 ����    2 ����    3 ���   |"<<endl;
        cout<<"| 4 ȡ��    5 ��ѯ    0 �˳�   |"<<endl;
        cout<<"|                            |"<<endl;
        cout<<"|____________________________|"<<endl;
        cout<<"���������ָ��:";
        cin>>i;
        if(i>=0 && i<=5)
            break;
        else
            cout<<"������ѡ����:"<<endl;;
    }
    return i;
}


int BASE::inputPassword()
//���ܣ���������
{
    char ch;  //�����ַ���ʽ����
    int iPass=0;   //Ҫת��Ϊ����
    int i;
    while(1)
    {
        for(i=0; i<6; i++)
        {
            ch=getch();  //���뵫����ʾ
            putchar('*');   //���*
            if(isdigit(ch))
                iPass=iPass*10+(ch-'0');//�����Ƿ�Ϊʮ���Ƶ���
            else
            {
                iPass=0;
                break;  //�˳�forѭ�����ٴν���
            }
        }
        fflush(stdin); //������̻��������Ѿ��е�����
        cout<<endl;;
        if(iPass==0)  //��������������������������������˷������ַ���ֱ������Ϊ0����6λȫ0�������˳�forѭ��
        {
            cout<<"����Ҫ��ȫΪ���֣��Ҳ���ȫ0!"<<endl;;
            cout<<"��������������:";
        }
        else
            break;
    }
    return iPass;
}
