
//User.cpp
#include <iostream>
#include <string>
#include "bank.h"
using namespace std;


void User::setUser(int acc,char nam[30], int pw, double bal,char ide[50] ,int sta,int y,int m,int d)
//功能：为User类的成员赋值
//参数：User类的成员，用户的个人信息，采用二进制文件储存，char型
{
    account=acc;
    password=pw;
    strcpy(name,nam);
    balance=bal;
    strcpy(id,ide);
    status=sta;
    BASE::year=y;
    BASE::month=m;
    BASE::day=d;
    // year=y;
    // month=m;
    // day=d;
}


void User::showName()
//功能：输出户主姓名
{
    cout<<"户主姓名："<<name<<endl;
}


void User::showBalance(string prompt)
//功能：输出存款
//输入参数：prompt
{
    cout<<prompt<<" "<<balance<<"元"<<endl;
}
bool User::validatePass()
//功能：验证密码是否正确
//调用inputPassword()函数
{
    int iPass;
    bool right = true;
    cout<<"输入密码:";
    iPass=inputPassword();
    if(iPass!=password)
    {
        right = false;
        cout<<"输入密码错误!"<<endl;
    }
    return right;
}


bool User::checkUserStatus()
//功能：输出用户状态
//返回值：如果status=0，状态正常，返回true，否则，返回false
//状态：0-正常  1-挂失  2-销户
{
    bool normal = true;
    if(status!=0)
    {
        normal = false;
        cout<<"该账户处于"<<(status==1?"挂失":"销户")<<"状态."<<endl;
    }
    return normal;
}

