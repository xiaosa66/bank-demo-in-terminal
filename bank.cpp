

//Bank.cpp
#include <iostream>
#include <fstream>//文件流头文件
#include <cstdlib>
#include "bank.h"
#include <string>
#include <ctype.h>//
#include <time.h>
using namespace std;


Bank::Bank()
//功能：用构造函数读取文件中保存的业务数据
{
    ifstream infile("accounts.myUser",ios::in|ios::binary);
    if(infile)   //检测文件是否成功打开
    {
    infile.seekg (0, ios::end);   //将文件指针标记在文件末尾
    int length = infile.tellg();  //计算出文件的长度
    N=length/sizeof(User);        //计算出对象的个数，然后用静态数据成员保存用户个数
    users=new User[N+1];          //动态数组建立对象数组
    infile.seekg(0,ios::beg);     //操作完文件指针后将指针重新定义在文件首的位置
    int i=0;      //用户数目
    while(infile.read((char *)&users[i],sizeof(users[i])))
    {
        infile.read((char *)&users[i],sizeof(users[i]));
        ++i;
    }
    //用静态数据成员保存用户个数
    infile.close();
       cout<<"dataBase Loaded";
    }
    else {
        ofstream outfile("accounts.myUser",ios::binary);
        cout<<"dataBase Inited";
        outfile.close();
    }
}


Bank::~Bank()
//功能：使用析构函数实现在退出系统时将数据保存到文件中
{
    saveHooker();
    free(users);      //对应realloc()函数
    delete[] users;   //释放动态数组占用的空间
}
void Bank::saveHooker(){
    ofstream outfile("accounts.myUser",ios::binary);
    if(!outfile)    //测试文件打开操作是否成功，不成功则提示后退出。
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    int i;		//将users数组内的内容写回文件
    for(i=0; i<N; i++)
    {
        outfile.write((char *)&users[i],sizeof(users[i]));
    }
    outfile.close();
}

void Bank::work()
//功能：办理业务
{
    int iChoice;   //用于选择系统功能
    do
    {
        iChoice = chooseInMenu();  //从菜单中获得功能代码
        switch(iChoice)
        {
        case 1:
            createAccount(); //开户
            break;
        case 2:
            removeAccount();  //注销账户
            break;
        case 3:
            save();  //存款
            break;
        case 4:
            withdraw();   //取款
            break;
        case 5:
            showAccount(); //查询余额
            break;
        case 6:
            transferMoney();  //转账
            break;
        case 7:
            reportLoss();  //挂失
            break;
        case 8:
            cancelLoss();  //解除挂失
            break;
        case 9:
            updatePassword();   //更改密码
            break;
        case 0:
            cout<<"期待您下次使用! "<<endl;
        }
    }
    while(iChoice);
}


void Bank::createAccount()
//功能：开户

{
    if(N==upNum)
    {
        cout<<"银行用户数已经达到上限，不能再开户";
        return;
    }
    int acc;		//账号
    char nam[30];   //姓名
    int pw;			//密码
    double bal;		//金额
    char ide[50];	//身份证
    int sta;		//状态
    int y,m,d;		//开户日期
    cout<<"正在开户"<<endl;
    acc=0+N;
    cout<<"账号:"<<acc<<endl;
    cout<<"户主姓名:";
    cin>>nam;
    cout<<"身份证号:";
    cin>>ide;
    // cout<<"开户日期:";
    // cin>>y>>m>>d;
    int iPass1, iPass2;
    cout<<"密码:";
    iPass1=inputPassword();  //输入密码
    cout<<"确认密码：";
    iPass2=inputPassword();  //确认密码
    if(iPass1==iPass2)
	//若密码一致则开户成功
    {
        pw=iPass1;
        sta=0; //账户状态为“正常”
        cout<<"存入金额:";
        cin>>bal;
        users=(User *)realloc(users,(N+2)*sizeof(User));  //增加一个对象的数组长度，以防止数据溢出

        time_t t;// 获取当前的系统时间，返回的结果是一个time_t类型,一个整数，其值表示从时间1970年1月1日00:00:00到当前时刻的秒数
        tm *lt;//获取日期和时间
        t = time(NULL);
        lt = localtime(&t);//获取秒数并转换为本地时间
         y= lt->tm_year+1900;
         m = lt->tm_mon+1;
         d = lt->tm_mday;

        users[N].setUser(acc, nam, pw, bal,ide, sta,y,m,d);
        N++; //正式用户数增加1，确认了新用户已经加入
        cout<<"成功开户!"<<endl;
    }
    else
    {
        cout<<"两次密码不一致,开户失败!"<<endl; //没有N++，则读入的值无效
    }
    saveLog(acc,"开户成功!");
}


void Bank::removeAccount()
//功能：注销账户
//找到账户并将其状态改为2-注销。
{
    int who;  //查找到该账号在数组中对应的下标
    char a[50],b[50];
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        users[who].showName();
        if(users[who].validatePass())
        {
            //cout<<users[who].id;
            strcpy(b,users[who].id);
            users[who].showBalance("余额");   //显示余额
            cout<<"确认销户(y/n)?";
            if(tolower(getchar())=='y')
            {
                cout<<"请输入身份证号码:";
                cin>>a;
                if(!strcmp(a,b))
                {
                    users[who].showBalance("销户成功!本次取款金额为");
                    users[who].balance=0;  //取款后余额变0
                    users[who].status=2;  //状态变为注销
                    saveLog(users[who].account,"销户成功！");
                }
                else
                {
                    cout<<"身份验证失败，销户失败!"<<endl;
                }
            }
            else
            {
                cout<<"你已取消操作，销户失败!"<<endl;
            }
            fflush(stdin);  //清除了getchar()时在键盘缓存的遗留
        }
    }
}


void Bank::save()
//功能：存款
{
    int who;
    double money;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        if(users[who].status==0)
        {
            users[who].showName();
            cout<<"输入存款额:";
            cin>>money;
            users[who].balance+=money;
            users[who].showBalance("存款后，您有");
            saveLog(users[who].account,"存款成功!");
        }
        else if(users[who].status==1)
        {
            cout<<"该用户处于挂失状态，存款失败!"<<endl;
        }
        else
        {
            cout<<"该用户已经销户，存款失败!"<<endl;
        }
    }
    return;
}


void Bank::withdraw()
//功能：取款
{
    int who;
    double money;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        if(users[who].checkUserStatus())
        {
            users[who].showName();
            if(users[who].validatePass())
            {
                cout<<"输入取款额:";
                cin>>money;
                if(money>users[who].balance)  //验证是否透支
                {
                    cout<<"余额不足，取款失败!"<<endl;
                }
                else
                {
                    users[who].balance-=money;
                    users[who].showBalance("取款后，还有");
                    saveLog(users[who].account,"取款成功!");
                }
            }
        }
    }
    return;
}


void Bank::showAccount()
//功能：查询账户
{
    int who;
    string sta[3]= {"正常","挂失","已经销户"};
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        users[who].showName();
        if(users[who].validatePass())
        {
            users[who].showBalance("余额");
            cout<<"状态:"<<sta[users[who].status]<<endl;
            // cout<<"开户时间:"<<sta[users[who].year]<<sta[users[who].month]<<sta[users[who].day]<<endl;
        }
    }
    return;
}


void Bank::transferMoney()
//功能：转账
{
    int whoout, whoin;
    double money;
    cout<<"转出自";
    whoout = getUser();  //根据账号查询用户，返回用户的下标
    if(whoout>=0)   //说明id账户存在
    {
        if(users[whoout].checkUserStatus())
        {
            users[whoout].showName();
            if(users[whoout].validatePass())
            {
                cout<<"输入转账金额:";
                cin>>money;
                if(money>users[whoout].balance)  //验证是否透支
                {
                    cout<<"余额不足，转账失败!"<<endl;
                }
                else
                {
                    cout<<"转出到";
                    whoin = getUser();  //根据账号查询用户，返回用户的下标
                    if(whoin>=0)   //说明id账户存在
                    {
                        if(users[whoin].checkUserStatus())
                        {
                            users[whoout].balance-=money;
                            users[whoin].balance+=money;
                            users[whoout].showBalance("转账后，您还有");
                            saveLog(users[whoout].account,"转账成功!");
                        }
                    }
                }
            }
        }
    }
    return;
}


void Bank::reportLoss()
//功能：挂失账户
{
    int who;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        users[who].showName();
        if(users[who].validatePass())
        {
            if(users[who].status==0)
            {
                users[who].status=1;
                cout<<"挂失成功"<<endl;
                saveLog(users[who].account,"挂失成功!");
            }
            else if(users[who].status==1)
            {
                cout<<"该账户已经处于挂失状态"<<endl;
            }
            else
            {
                cout<<"该账户已销户，不能挂失"<<endl;
            }
        }
    }
    return;
}


void Bank::cancelLoss()
//功能：解除挂失
{
    int who;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        users[who].showName();
        if(users[who].validatePass())
        {
            if(users[who].status==0)
            {
                cout<<"该账户处于正常状态，不需要解除挂失"<<endl;
            }
            else if(users[who].status==1)
            {
                users[who].status=0;
                cout<<"解除挂失成功"<<endl;
                saveLog(users[who].account,"解除挂失成功!");
            }
            else
            {
                cout<<"该账户已销户，操作无效"<<endl;
            }
        }
    }
    return;
}


void Bank::updatePassword()
//功能：改密码
{
    int who;
    int iPass1, iPass2;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在 验证身份ID是否正确
    {
        users[who].showName();
        if(users[who].validatePass())
        {
            cout<<"新密码:";
            iPass1=inputPassword();  //输入密码
            cout<<"确认密码:";
            iPass2=inputPassword();  //确认密码
            if(iPass1==iPass2)
            {
                users[who].password=iPass1;
                cout<<"修改成功!"<<endl;
            }
            else
            {
                cout<<"输入密码不一致，修改失败!"<<endl;
            }
        }
    }
    return;
}


int Bank::getUser()
//功能：输入账号查询用户
//采用二分查找。如果用户存在，返回该用户在数组中的下标，否则，返回一个负数（-1）。
{
    int id;
    cout<<"账号:";
    cin>>id;
    int index=-1;
    int low=0, high=N-1, mid;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(users[mid].account==id)
        {
            index=mid;
            break;   //找到账户，退出循环
        }
        else if (users[mid].account>id)
            high=mid-1;
        else
            low=mid+1;
    }
    if (index<0)
        cout<<"该用户不存在，本次操作失败!"<<endl;
    return index; //若找到，其值在0~N-1间，否则，保持-1
}


void Bank::saveLog(int usernum,string infor)
//功能：记录用户的每项业务
{
    time_t t;// 获取当前的系统时间，返回的结果是一个time_t类型,一个整数，其值表示从时间1970年1月1日00:00:00到当前时刻的秒数
    tm *lt;//获取日期和时间
    t = time(NULL);
    lt = localtime(&t);//获取秒数并转换为本地时间
    ofstream workfile("accounts.log",ios::binary);
    if(!workfile)
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    workfile<<lt->tm_year+1900<<"/"<<lt->tm_mon+1<<"/"<<lt->tm_mday<<" "<<lt->tm_hour<<":"<<lt->tm_min<<":"<<lt->tm_sec<<'\t';//年份，其值从1900开始，月份从一月开始，0代表一月
    workfile<<"用户"<<usernum<<"进行"<<infor<<endl;
    workfile.close();
    saveHooker();
}
