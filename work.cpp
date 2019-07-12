
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
//功能：显示菜单并由业务员选择
{
    int i;
    while(1)
    {
        cout<<endl;;
        cout<<" ____________________________ "<<endl;
		cout<<"|                            |"<<endl;
		cout<<"|                            |"<<endl;
        cout<<"| 1 开户    2 销户    3 存款 |"<<endl;
        cout<<"| 4 取款    5 查询    6 转账 |"<<endl;
        cout<<"| 7 挂失    8 解挂    0 退出 |"<<endl;
        cout<<"|____________________________|"<<endl;
        cout<<"请输入操作指令:";
        cin>>i;
        if(i>=0 && i<=9)
            break;
        else
            cout<<"请重新选择功能:"<<endl;;
    }
    return i;
}


int BASE::inputPassword()
//功能：输入密码
{
    char ch;  //接收字符形式密码
    int iPass=0;   //要转换为数字
    int i;
    while(1)
    {
        for(i=0; i<6; i++)
        {
            ch=getch();  //输入但不显示
            putchar('*');   //输出*
            if(isdigit(ch))
                iPass=iPass*10+(ch-'0');//检验是否为十进制的数
            else
            {
                iPass=0;
                break; 
            }
        }
        fflush(stdin); 
        cout<<endl;;
        if(iPass==0)  
        {
            cout<<"密码要求全为数字，且不能全0!"<<endl;;
            cout<<"请重新输入密码:";
        }
        else
            break;
    }
    return iPass;
}
