

//Bank.h
#ifndef BANK_H_INCLUDED//防止多个文件中头文件冲突
#define BANK_H_INCLUDED
#include <cstring>
using namespace std;

class Bank;

const int upNum=2000; //系统最多容纳的用户数


class BASE
//基类，登录和信息界面需要用到的变量
{
public:
    int year;
    int month;
    int day;

public:
    int chooseInMenu();//显示菜单并由客户选择
    int inputPassword();//返回键盘输入的密码
};


class User:public BASE
//功能：用户信息的声明和输入，为Bank类做准备
//加入成员函数
{
public:
    void setUser(int acc, char nam[30], int pw, double bal,char ide[50],int sta,int y,int m,int d);
    void showName();
    void showBalance(string prompt); //显示余额，前面加上提示词prompt
    bool passwordIsRight();   //校验密码，输入的密码正确则返回true
    bool isNormalUser(); //存款、取款、转帐等功能，需要账户处于正常状态
    friend class Bank;   //将Bank声明为友元类，方便其访问数据成员
    char id[50];

private:
    int account; //账号
    int password;  //密码
    char name[30];   //用户名
    double balance;  //账户余额
    int status;  //状态 0-正常  1-挂失  2-销户
};


class Bank:public User
//功能：主要用于业务办理，信息读取和存储
//User类指针用于动态存储
{
public:
	 Bank();  //开始前从文件中读数据，存在数组中
	 ~Bank();   //程序结束前，将数组中的数据写入到文件中
    void work();  //业务
    void openAccount(); //开户
    void cancelAccount();  //注销账户
    void save();   //存款
    void withdraw();   //取款
    void showAccount(); //查询余额
    void transferAccounts();  //转账
    void reportLoss();  //挂失
    void cancelLoss();  //解除挂失
    void updatePassword();   //更改密码 需要验证身份
    int getUser();//输入账号查询用户，返回用户在对象数组中的下标
    void savework(int usernum,string infor);//记录用户的业务

private:
    int N;  //实际的用户数目
    User *users;  //User数组
};
#endif // BANK_H_INCLUDED
