

//Bank.cpp
#include <iostream>
#include <fstream>//�ļ���ͷ�ļ�
#include <cstdlib>
#include "bank.h"
#include <string>
#include <ctype.h>//
#include <time.h>
using namespace std;


Bank::Bank()
//���ܣ��ù��캯����ȡ�ļ��б����ҵ������
{
    ifstream infile("account.txt",ios::in|ios::binary);
    if(!infile)   //����ļ��Ƿ�ɹ���
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    infile.seekg (0, ios::end);   //���ļ�ָ�������ļ�ĩβ
    int length = infile.tellg();  //������ļ��ĳ���
    N=length/sizeof(User);        //���������ĸ�����Ȼ���þ�̬���ݳ�Ա�����û�����
    users=new User[N+1];          //��̬���齨����������
    infile.seekg(0,ios::beg);     //�������ļ�ָ���ָ�����¶������ļ��׵�λ��
    int i=0;      //�û���Ŀ
    while(infile.read((char *)&users[i],sizeof(users[i])))
    {
        infile.read((char *)&users[i],sizeof(users[i]));
        ++i;
    }
    //�þ�̬���ݳ�Ա�����û�����
    infile.close();
}


Bank::~Bank()
//���ܣ�ʹ����������ʵ�����˳�ϵͳʱ�����ݱ��浽�ļ���
{
    ofstream outfile("account.txt",ios::binary);
    if(!outfile)    //�����ļ��򿪲����Ƿ�ɹ������ɹ�����ʾ���˳���
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    int i;		//��users�����ڵ�����д���ļ�
    for(i=0; i<N; i++)
    {
        outfile.write((char *)&users[i],sizeof(users[i]));
    }
    outfile.close();
    free(users);      //��Ӧrealloc()����
    delete[] users;   //�ͷŶ�̬����ռ�õĿռ�
}


void Bank::work()
//���ܣ�����ҵ��
{
    int iChoice;   //����ѡ��ϵͳ����
    do
    {
        iChoice = chooseInMenu();  //�Ӳ˵��л�ù��ܴ���
        switch(iChoice)
        {
        case 1:
            openAccount(); //����
            break;
        case 2:
            cancelAccount();  //ע���˻�
            break;
        case 3:
            save();  //���
            break;
        case 4:
            withdraw();   //ȡ��
            break;
        case 5:
            showAccount(); //��ѯ���
            break;
       /* case 6:
            transferAccounts();  //ת��
            break;
        case 7:
            reportLoss();  //��ʧ
            break;
        case 8:
            cancelLoss();  //�����ʧ
            break;
        case 9:
            updatePassword();   //��������
            break;*/
        case 0:
            cout<<"�ڴ����´�ʹ��! "<<endl;
        }
    }
    while(iChoice);
}


void Bank::openAccount()
//���ܣ�����
//˵�����ڽ���ϵͳʱ�������ݹ����У��Ѿ���¼�û���ΪN���������ж�Ӧ�±�Ϊ0~N-1��
//		����ʱҪ����һ���û���ֻҪΪ�±�ΪN������Ԫ����ֵ�����ڳɹ�֮����N++���ɡ�
//		�˺���ϵͳ�Զ�����(101+���)����˳�����ӵ�ʱ�򣬾ͱ�֤���������ԡ�
{
    if(N==upNum)
    {
        cout<<"�����û����Ѿ��ﵽ���ޣ������ٿ���";
        return;
    }
    int acc;		//�˺�
    char nam[30];   //����
    int pw;			//����
    double bal;		//���
    char ide[50];	//����֤
    int sta;		//״̬
    int y,m,d;		//��������
    cout<<"���ڿ���"<<endl;
    acc=101+N;
    cout<<"�˺�:"<<acc<<endl;
    cout<<"��������:";
    cin>>nam;
    cout<<"����֤��:";
    cin>>ide;
    cout<<"��������:";
    cin>>y>>m>>d;
    int iPass1, iPass2;
    cout<<"����:";
    iPass1=inputPassword();  //��������
    cout<<"ȷ�����룺";
    iPass2=inputPassword();  //ȷ������
    if(iPass1==iPass2)
	//������һ���򿪻��ɹ�
    {
        pw=iPass1;
        sta=0; //�˻�״̬Ϊ��������
        cout<<"������:";
        cin>>bal;
        users=(User *)realloc(users,(N+2)*sizeof(User));  //����һ����������鳤�ȣ��Է�ֹ�������
        users[N].setUser(acc, nam, pw, bal,ide, sta,y,m,d);
        N++; //��ʽ�û�������1��ȷ�������û��Ѿ�����
        cout<<"�ɹ�����!"<<endl;
    }
    else
    {
        cout<<"�������벻һ��,����ʧ��!"<<endl; //û��N++��������ֵ��Ч
    }
    savework(acc,"�����ɹ�!");
}


void Bank::cancelAccount()
//���ܣ�ע���˻�
//�ҵ��˻�������״̬��Ϊ2-ע����
{
    int who;  //���ҵ����˺��������ж�Ӧ���±�
    char a[50],b[50];
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            //cout<<users[who].id;
            strcpy(b,users[who].id);
            users[who].showBalance("���");   //��ʾ���
            cout<<"ȷ������(y/n)?";
            if(tolower(getchar())=='y')
            {
                cout<<"����������֤����:";
                cin>>a;
                if(!strcmp(a,b))
                {
                    users[who].showBalance("�����ɹ�!����ȡ����Ϊ");
                    users[who].balance=0;  //ȡ�������0
                    users[who].status=2;  //״̬��Ϊע��
                    savework(users[who].account,"�����ɹ���");
                }
                else
                {
                    cout<<"������֤ʧ�ܣ�����ʧ��!"<<endl;
                }
            }
            else
            {
                cout<<"����ȡ������������ʧ��!"<<endl;
            }
            fflush(stdin);  //�����getchar()ʱ�ڼ��̻��������
        }
    }
}


void Bank::save()
//���ܣ����
{
    int who;
    double money;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        if(users[who].status==0)
        {
            users[who].showName();
            cout<<"�������:";
            cin>>money;
            users[who].balance+=money;
            users[who].showBalance("��������");
            savework(users[who].account,"���ɹ�!");
        }
        else if(users[who].status==1)
        {
            cout<<"���û����ڹ�ʧ״̬�����ʧ��!"<<endl;
        }
        else
        {
            cout<<"���û��Ѿ����������ʧ��!"<<endl;
        }
    }
    return;
}


void Bank::withdraw()
//���ܣ�ȡ��
{
    int who;
    double money;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        if(users[who].isNormalUser())
        {
            users[who].showName();
            if(users[who].passwordIsRight())
            {
                cout<<"����ȡ���:";
                cin>>money;
                if(money>users[who].balance)  //��֤�Ƿ�͸֧
                {
                    cout<<"���㣬ȡ��ʧ��!"<<endl;
                }
                else
                {
                    users[who].balance-=money;
                    users[who].showBalance("ȡ��󣬻���");
                    savework(users[who].account,"ȡ��ɹ�!");
                }
            }
        }
    }
    return;
}


void Bank::showAccount()
//���ܣ���ѯ�˻�
{
    int who;
    string sta[3]= {"����","��ʧ","�Ѿ�����"};
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            users[who].showBalance("���");
            cout<<"״̬:"<<sta[users[who].status]<<endl;
        }
    }
    return;
}


/*void Bank::transferAccounts()
//���ܣ�ת��
{
    int whoout, whoin;
    double money;
    cout<<"ת����";
    whoout = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(whoout>=0)   //˵��id�˻�����
    {
        if(users[whoout].isNormalUser())
        {
            users[whoout].showName();
            if(users[whoout].passwordIsRight())
            {
                cout<<"����ת�˽��:";
                cin>>money;
                if(money>users[whoout].balance)  //��֤�Ƿ�͸֧
                {
                    cout<<"���㣬ת��ʧ��!"<<endl;
                }
                else
                {
                    cout<<"ת����";
                    whoin = getUser();  //�����˺Ų�ѯ�û��������û����±�
                    if(whoin>=0)   //˵��id�˻�����
                    {
                        if(users[whoin].isNormalUser())
                        {
                            users[whoout].balance-=money;
                            users[whoin].balance+=money;
                            users[whoout].showBalance("ת�˺�������");
                            savework(users[whoout].account,"ת�˳ɹ�!");
                        }
                    }
                }
            }
        }
    }
    return;
}


void Bank::reportLoss()
//���ܣ���ʧ�˻�
{
    int who;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            if(users[who].status==0)
            {
                users[who].status=1;
                cout<<"��ʧ�ɹ�"<<endl;
                savework(users[who].account,"��ʧ�ɹ�!");
            }
            else if(users[who].status==1)
            {
                cout<<"���˻��Ѿ����ڹ�ʧ״̬"<<endl;
            }
            else
            {
                cout<<"���˻������������ܹ�ʧ"<<endl;
            }
        }
    }
    return;
}


void Bank::cancelLoss()
//���ܣ������ʧ
{
    int who;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            if(users[who].status==0)
            {
                cout<<"���˻���������״̬������Ҫ�����ʧ"<<endl;
            }
            else if(users[who].status==1)
            {
                users[who].status=0;
                cout<<"�����ʧ�ɹ�"<<endl;
                savework(users[who].account,"�����ʧ�ɹ�!");
            }
            else
            {
                cout<<"���˻���������������Ч"<<endl;
            }
        }
    }
    return;
}


void Bank::updatePassword()
//���ܣ�������
{
    int who;
    int iPass1, iPass2;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻����� ��֤����ID�Ƿ���ȷ
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            cout<<"������:";
            iPass1=inputPassword();  //��������
            cout<<"ȷ������:";
            iPass2=inputPassword();  //ȷ������
            if(iPass1==iPass2)
            {
                users[who].password=iPass1;
                cout<<"�޸ĳɹ�!"<<endl;
            }
            else
            {
                cout<<"�������벻һ�£��޸�ʧ��!"<<endl;
            }
        }
    }
    return;
}
*/

int Bank::getUser()
//���ܣ������˺Ų�ѯ�û�
//���ö��ֲ��ҡ�����û����ڣ����ظ��û��������е��±꣬���򣬷���һ��������-1����
{
    int id;
    cout<<"�˺�:";
    cin>>id;
    int index=-1;
    int low=0, high=N-1, mid;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(users[mid].account==id)
        {
            index=mid;
            break;   //�ҵ��˻����˳�ѭ��
        }
        else if (users[mid].account>id)
            high=mid-1;
        else
            low=mid+1;
    }
    if (index<0)
        cout<<"���û������ڣ����β���ʧ��!"<<endl;
    return index; //���ҵ�����ֵ��0~N-1�䣬���򣬱���-1
}


void Bank::savework(int usernum,string infor)
//���ܣ���¼�û���ÿ��ҵ��
{
    time_t t;// ��ȡ��ǰ��ϵͳʱ�䣬���صĽ����һ��time_t����,һ����������ֵ��ʾ��ʱ��1970��1��1��00:00:00����ǰʱ�̵�����
    tm *lt;//��ȡ���ں�ʱ��
    t = time(NULL);
    lt = localtime(&t);//��ȡ������ת��Ϊ����ʱ��
    ofstream workfile("accounts.txt",ios::app);
    if(!workfile)
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    workfile<<lt->tm_year+1900<<"/"<<lt->tm_mon+1<<"/"<<lt->tm_mday<<" "<<lt->tm_hour<<":"<<lt->tm_min<<":"<<lt->tm_sec<<'\t';//��ݣ���ֵ��1900��ʼ���·ݴ�һ�¿�ʼ��0����һ��
    workfile<<"�û�"<<usernum<<"����"<<infor<<endl;
    workfile.close();
}