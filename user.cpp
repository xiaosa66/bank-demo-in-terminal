
//User.cpp
#include <iostream>
#include <string>
#include "bank.h"
using namespace std;


void User::setUser(int acc,char nam[30], int pw, double bal,char ide[50] ,int sta,int y,int m,int d)
//���ܣ�ΪUser��ĳ�Ա��ֵ
//������User��ĳ�Ա���û��ĸ�����Ϣ�����ö������ļ����棬char��
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
//���ܣ������������
{
    cout<<"����������"<<name<<endl;
}


void User::showBalance(string prompt)
//���ܣ�������
//���������prompt
{
    cout<<prompt<<" "<<balance<<"Ԫ"<<endl;
}
bool User::validatePass()
//���ܣ���֤�����Ƿ���ȷ
//����inputPassword()����
{
    int iPass;
    bool right = true;
    cout<<"��������:";
    iPass=inputPassword();
    if(iPass!=password)
    {
        right = false;
        cout<<"�����������!"<<endl;
    }
    return right;
}


bool User::checkUserStatus()
//���ܣ�����û�״̬
//����ֵ�����status=0��״̬����������true�����򣬷���false
//״̬��0-����  1-��ʧ  2-����
{
    bool normal = true;
    if(status!=0)
    {
        normal = false;
        cout<<"���˻�����"<<(status==1?"��ʧ":"����")<<"״̬."<<endl;
    }
    return normal;
}

