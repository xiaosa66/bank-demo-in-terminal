

//Bank.h
#ifndef BANK_H_INCLUDED//��ֹ����ļ���ͷ�ļ���ͻ
#define BANK_H_INCLUDED
#include <cstring>
using namespace std;

class Bank;

const int upNum=2000; //ϵͳ������ɵ��û���


class BASE
//���࣬��¼����Ϣ������Ҫ�õ��ı���
{
public:
    int year;
    int month;
    int day;

public:
    int chooseInMenu();//��ʾ�˵����ɿͻ�ѡ��
    int inputPassword();//���ؼ������������
};


class User:public BASE
//���ܣ��û���Ϣ�����������룬ΪBank����׼��
//�����Ա����
{
public:
    void setUser(int acc, char nam[30], int pw, double bal,char ide[50],int sta,int y,int m,int d);
    void showName();
    void showBalance(string prompt); //��ʾ��ǰ�������ʾ��prompt
    bool validatePass();   //У�����룬�����������ȷ�򷵻�true
    bool checkUserStatus(); //��ȡ�ת�ʵȹ��ܣ���Ҫ�˻���������״̬
    friend class Bank;   //��Bank����Ϊ��Ԫ�࣬������������ݳ�Ա
    char id[50];

private:
    int account; //�˺�
    int password;  //����
    int year;  //����ʱ��
    int month;  //����ʱ��
    int day;  //����ʱ��
    char name[30];   //�û���
    double balance;  //�˻����
    int status;  //״̬ 0-����  1-��ʧ  2-����
};


class Bank:public User
//���ܣ���Ҫ����ҵ�������Ϣ��ȡ�ʹ洢
//User��ָ�����ڶ�̬�洢
{
public:
	 Bank();  //��ʼǰ���ļ��ж����ݣ�����������
	 ~Bank();   //�������ǰ���������е�����д�뵽�ļ���
    void work();  //ҵ��
    void createAccount(); //����
    void removeAccount();  //ע���˻�
    void save();   //���
    void withdraw();   //ȡ��
    void showAccount(); //��ѯ���
    void transferMoney();  //ת��
    void saveHooker();  // ���湳�Ӻ���
    void reportLoss();  //��ʧ
    void cancelLoss();  //�����ʧ
    void updatePassword();   //�������� ��Ҫ��֤���
    int getUser();//�����˺Ų�ѯ�û��������û��ڶ��������е��±�
    void saveLog(int usernum,string infor);//��¼�û���ҵ��

private:
    int N;  //ʵ�ʵ��û���Ŀ
    User *users;  //User����
};
#endif // BANK_H_INCLUDED
