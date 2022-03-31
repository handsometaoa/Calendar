#include "Date.h"
#include <stdio.h>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string.h>

using namespace std;


/*ũ����ѯ��  ��Դ��https://www.jianshu.com/p/57e7bd43c00b    */
/*��1λ    ��ʾ���������£�0������С�£�1���������
 *��2-4λ  ��ʾ12��������λ һλ��ʾһ�����Ǵ��»���С��
 *���1λ  ��ʾ���ĸ��£�0��ʾ����*/
unsigned int LunarCalendar[199] =
{
    /*1900�꿪ʼ*/
    /*0x04bd8,0x04ae0,0x0a570,0x054d5,0x0d260,0x0d950,0x16554,0x056a0,0x09ad0,0x055d2,
    0x04ae0,0x0a5b6,0x0a4d0,0x0d250,0x1d255,0x0b540,0x0d6a0,0x0ada2,0x095b0,0x14977,
    0x04970,0x0a4b0,0x0b4b5,0x06a50,0x06d40,0x1ab54,0x02b60,0x09570,0x052f2,0x04970,
    0x06566,0x0d4a0,0x0ea50,0x06e95,0x05ad0,0x02b60,0x186e3,0x092e0,0x1c8d7,*/
    /*�ҵ�����Ҫ��1940-2040�� �����ò���*/

    0x0c950,/*1939��*/   /*��ѯ����1940��1�£�ũ����ʵ��1939��*/
    0x0d4a0,0x1d8a6,0x0b550,0x056a0,0x1a5b4,0x025d0,0x092d0,0x0d2b2,0x0a950,0x0b557,
    0x06ca0,0x0b550,0x15355,0x04da0,0x0a5d0,0x14573,0x052d0,0x0a9a8,0x0e950,0x06aa0,
    0x0aea6,0x0ab50,0x04b60,0x0aae4,0x0a570,0x05260,0x0f263,0x0d950,0x05b57,0x056a0,
    0x096d0,0x04dd5,0x04ad0,0x0a4d0,0x0d4d4,0x0d250,0x0d558,0x0b540,0x0b5a0,0x195a6,
    0x095b0,0x049b0,0x0a974,0x0a4b0,0x0b27a,0x06a50,0x06d40,0x0af46,0x0ab60,0x09570,
    0x04af5,0x04970,0x064b0,0x074a3,0x0ea50,0x06b58,0x055c0,0x0ab60,0x096d5,0x092e0,
    0x0c960,0x0d954,0x0d4a0,0x0da50,0x07552,0x056a0,0x0abb7,0x025d0,0x092d0,0x0cab5,
    0x0a950,0x0b4a0,0x0baa4,0x0ad50,0x055d9,0x04ba0,0x0a5b0,0x15176,0x052b0,0x0a930,
    0x07954,0x06aa0,0x0ad50,0x05b52,0x04b60,0x0a6e6,0x0a4e0,0x0d260,0x0ea65,0x0d530,
    0x05aa0,0x076a3,0x096d0,0x04bd7,0x04ad0,0x0a4d0,0x1d0b6,0x0d250,0x0d520,0x0dd45,
    0x0b5a0,0x056d0,0x055b2,0x049b0,0x0a577,0x0a4b0,0x0aa50,0x1b255,0x06d20,0x0ada0
};

/*��ȡϵͳʱ��*/
void gettime(int &year,int &month,int &day)
{
    time_t time1;
    struct tm *ptime;
    time(&time1);
    ptime = localtime(&time1);
    year=ptime->tm_year + 1900;
    month=ptime->tm_mon + 1;
    day=ptime->tm_mday;
}

/*�ж�year���Ƿ�������*/
bool isLeapYear(int year)
{
    /*���Ա�4��100�������߿��Ա�400����*/
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*��ȡyear��month���ж�����*/
int getDaysOfMonth(int year,int month)
{
    /*ƽ����¹�������*/
    int days[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    if(isLeapYear(year)&&month==2)
        return 29;
    else
        return days[month-1];
}

/*��ȡyear��month��day�յ�1939��1��1�յ�����*/
int getDayTo1939(int year,int month,int day)
{
    int days=0;
    /*��1939�꿪ʼ���㣬ֱ��year-1�꣬���Ƕ���������*/
    for(int i=year-1; i>=1939; i--)
    {
        if(isLeapYear(i))
            days+=366;
        else
            days+=365;
    }
    /*����year��1�µ�year��month-1��  ������������*/
    for(int i=month-1; i>0; i--)
    {
        days+=getDaysOfMonth(year,i);
    }
    /*����year��month��1�յ�yera��month��day������*/
    days+=day;
    return days-1;
}

/*��ȡyear��month��day�������ڼ�*/
string getDayOfWeek(int year,int month,int day)
{
    string weeks[7]= {"������","����һ","���ڶ�","������","������","������","������"};
    /*��ȡyear��month��day�յ�1939��1��1�յ�����*/
    int days=getDayTo1939(year,month,day);
    int week=days%7;
    return weeks[week];
}
/*���Ͱ����ڼ�*/
int getDayOfWeek1(int year,int month,int day)
{
    int days=getDayTo1939(year,month,day);
    int week=days-(days/7)*7;
    return week;
}

/*��ȡyear��month��day�յ����ڵ����� ��ֵΪ��ȥ����ֵΪδ��*/
int getDaysOfMonthToToday(int year,int month,int day)
{
    int nowyear;
    int nowmonth;
    int nowday;
    gettime(nowyear,nowmonth,nowday);
    /*����ʱ�䵽1939��1��1�յ�����*/
    int nowto1939=getDayTo1939(nowyear,nowmonth,nowday);
    /*�����ʱ�䵽1939��1��1�յ�����*/
    int tempto1939=getDayTo1939(year,month,day);
    /*����Ϊ��ȥ������Ϊδ��*/
    return nowto1939-tempto1939;
}

/*��������պϷ���*/
bool checkDate(int year,int month,int day)
{
    /*����Ҫ�ж� year��month��  �Ƿ�day�죬����4����30�죬����31���Ǵ����*/
    if(year<1939||year>2041||month<0||month>12||day<0||day>getDaysOfMonth(year,month))
        return false;
    else
        return true;
}


void print_number_week(int year,int month,int day)
{
    if(!checkDate(year,month,day))
    {
        cout<<"�������������ȷ��������ȷ�ԣ�"<<endl;
        return;
    }
    if(getDaysOfMonthToToday(year,month,day)>0)
        cout<<year<<"��"<<month<<"��"<<day<<"��\t"<<getDayOfWeek(year,month,day)<<"\t�������ѹ�ȥ"<<getDaysOfMonthToToday(year,month,day)<<"��"<<endl;
    else
        cout<<year<<"��"<<month<<"��"<<day<<"��\t"<<getDayOfWeek(year,month,day)<<"\t�����ڻ���"<<-getDaysOfMonthToToday(year,month,day)<<"��"<<endl;
}

/*��������·������������*/
void print_monthly_calendar(int year,int month)
{
    if(year>2041||year<1939||month>12||month<1)
    {
        cout<<"�������������ȷ��������ȷ�ԣ�"<<endl;
        return;
    }
    cout<<"\t"<<year<<"��"<<month<<"��"<<endl;
    cout<<" SUN MON TUE WED THU FRI SAT"<<endl;
    /*����year��month��1�����ڼ�*/
    int week=getDayOfWeek1(year,month,1);
    /*����1�յ���Ӧ��������*/
    for(int i=1; i<=week&&week!=7; i++)
        cout<<"    ";
    /*��ӡ������Ϣ*/
    for(int i=1; i<=getDaysOfMonth(year,month); i++)
    {
        cout<<setw(3)<<i<<" ";
        if((week+i)%7==0)
            cout<<endl;
    }
}


/*������ݡ����� һ�����3����*/
void print_seasons_calendar(int year,int num)
{
    if(num>4||num<0)
    {
        cout<<"���뼾�ȳ���"<<endl;
        return;
    }
    int month=1+3*(num-1);
    /*��ӡ����ͷ*/
    cout<<month<<" SUN MON TUE WED THU FRI SAT\t"<<month+1<<" SUN MON TUE WED THU FRI SAT\t"<<month+2<<" SUN MON TUE WED THU FRI SAT"<<endl;
    /*week1��week2��week3 �ֱ����һ�����ȵ������µ�һ�ն�Ӧ������*/
    int week1=getDayOfWeek1(year,month,1);
    int week2=getDayOfWeek1(year,month+1,1);
    int week3=getDayOfWeek1(year,month+2,1);
    /*tmp1��tmp2��tmp3�ֱ���������µ��������*/
    int tmp1=getDaysOfMonth(year,month),tmp2=getDaysOfMonth(year,month+1),tmp3=getDaysOfMonth(year,month+2);

    int day1,day2,day3;

    /*���������һ����Ϣ*/
    cout<<"  ";
    for(int i=1; i<=week1 &&week1!=7; i++)
        cout<<"    ";
    for(int i=1; i<=tmp1; i++)
    {
        cout<<setw(3)<<i<<" ";
        if((week1+i)%7==0)
        {
            day1=i+1;
            break;
        }
    }
    cout<<"    ";
    for(int i=1; i<=week2 && week2!=7; i++)
        cout<<"    ";
    for(int i=1; i<=tmp2; i++)
    {
        cout<<setw(3)<<i<<" ";
        if((week2+i)%7==0)
        {
            day2=i+1;
            break;
        }
    }
    cout<<"    ";
    for(int i=1; i<=week3 && week3!=7; i++)
        cout<<"    ";
    for(int i=1; i<=tmp3; i++)
    {
        cout<<setw(3)<<i<<" ";
        if((week3+i)%7==0)
        {
            day3=i+1;
            cout<<endl;
            break;
        }
    }

    /*��ӡ������Ϣ*/
    for(int j=0; j<5; j++)
    {
        /*�����������Ϣȫ����ӡ�꣬���˳�*/
        if(day1>tmp1&&day2>tmp2&&day3>tmp3)
            break;
        /*����21����һ�������ܣ�������21��*/
        for(int i=0; i<21;)
        {
            cout<<"  ";
            while(i<7)
            {
                i++;
                /*���û��ӡ��ʹ�ӡ���֣�������������Ѿ���ӡ�꣬������ո�*/
                if(day1<=tmp1)
                    cout<<setw(3)<<day1++<<" ";
                else
                    cout<<setw(3)<<" "<<" ";
            }
            /*��ӡ�·����·�֮��ļ��*/
            cout<<"    ";
            while(i<14&&i>=7)
            {
                i++;
                if(day2<=tmp2)
                    cout<<setw(3)<<day2++<<" ";
                else
                    cout<<setw(3)<<" "<<" ";
            }
            cout<<"    ";
            while(i<21&&i>=14)
            {
                i++;
                if(day3<=tmp3)
                    cout<<setw(3)<<day3++<<" ";
                else
                    cout<<setw(3)<<" "<<" ";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

/*��ʾ��ӭ����*/
void print()
{
    cout<<"\n\t\t��ӭ�����ҵ�������1940-2040�꣩"<<endl;
    cout<<"\t\t����ѡ��"<<endl;
    cout<<"\t\t1.��ѯ��������"<<endl;
    cout<<"\t\t2.��ѯ��������"<<endl;
    cout<<"\t\t3.��ѯ�������죿���ڼ���"<<endl;
    cout<<"\t\t4.���빫����ѯũ��"<<endl;
    cout<<"\t\t5.���������ѯ��Ӧ������ũ��"<<endl;
    cout<<"\t\t*****��0�˳�*****"<<endl;
}

/*�����������*/
void print_annual_calendar(int year)
{
    if(year>2041||year<1939)
    {
        cout<<"�������������ȷ��������ȷ�ԣ�"<<endl;
        return;
    }
    cout<<"\t\t\t\t\t  "<<"------------"<<endl;
    cout<<"\t\t\t\t\t  "<<year<<"��������"<<endl;
    cout<<"\t\t\t\t\t  "<<"------------"<<endl;

    /*ѭ������ĸ����� ��ӡ����������*/
    for(int i=1; i<=4; i++)
    {
        print_seasons_calendar(year,i);
    }
}


string nongMonth[]= {" ","����","����","����","����","����","����","����","����","����","ʮ��","����","����"};
string nongday[]= {"��","һ","��","��","��","��","��","��","��","��","ʮ"};
string nongday2[]= {"��","ʮ","إ","ئ"};


/*�ж����С��*/
bool is_large_month(int year)
{
    /*����ҳ��Ƿ�Ϊ���� �ж�high�ǲ���Ϊ0*/
    int high =(LunarCalendar[year-1939]>>16);
    if(high==0x00)
        return false;
    else
        return true;
}
/*���� ����  0������*/
int isNongLeapYear(int year)
{
    /*���ũ������*/
    int low = LunarCalendar[year-1939] & 0xF;
    return low;
}

/*�ж�ũ��ĳ��ĳ�¶�����*/      /*LunarCalendar ��ʾũ�����ձ�*/
int getDaysOfMonthOfNongMonth(int year,int month)
{
    /*������ݴ�С�£�����ũ��������*/
    int bit=1 << (16-month);
    if((LunarCalendar[year-1939]/*&0x0000FFFF*/&bit)==0)
        return 29;
    else
        return 30;
}

/*�ж�ĳ��ũ��������*/
int getDayOfNongYear(int year)
{
    int days=0;
    /*ũ��ʮ����������*/
    for(int i=1; i<=12; i++)
    {
        days+=getDaysOfMonthOfNongMonth(year,i);
    }
    /*���������£�������������*/
    if(isNongLeapYear(year)!=0)
    {
        if(is_large_month(year))
            days+=30;
        else
            days+=29;
    }
    return days;
}


/*���ũ������*/
void printNong(int days)
{
    int year=1939,month=1,day=1;
    /*����1939��1��1��������ũ��1938�꣬���Լ�ȥ48�죬��1939�����³�һ���㣬��Ϊ�����������㷶ΧΪ1940��-2040�� ���Կ�������*/
    days-=48;

    /*�жϼ�ȥ��һ����������᲻���Ǹ�ֵ�����Ǳ��ȥ������ũ����*/
    for(int i=1939; (days-getDayOfNongYear(i))>0; i++)
    {
        days-=getDayOfNongYear(i);
        year=i+1;
    }
    int num;
    int signal=0;
    /*�жϼ�ȥ��һ���������᲻���Ǹ�ֵ�������ũ���¼�1*/
    for(int j=1; ((days-getDaysOfMonthOfNongMonth(year,j))>0)&&j<12; j++)
    {
        days-=getDaysOfMonthOfNongMonth(year,j);
        if(j==isNongLeapYear(year))
        {
            if(is_large_month(year))
            {
                days-=30;
                num=30;
            }
            else
            {
                days-=29;
                num=29;
            }
        }
        /*����ȥũ���µ�ʱ�򣬼����Ϊ��ֵ����ô�ټӻ���*/
        if(days<0)
        {
            /*ũ�����±��*/
            signal=1;
            days +=num;
            month=j;
            break;
        }
        month=month+1;
    }
    /*ʣ����������ũ����*/
    day=days;
    cout<<year<<"��";
    if(signal==1)
        cout<<" ��";
    cout<<nongMonth[month];
    if(day>0&&day<=10)
    {
        cout<<"��"<<nongday[day];
    }
    else if(day>10&&day<20)
    {
        cout<<"ʮ"<<nongday[day%10];
    }
    else if(day==20)
    {
        cout<<"��ʮ";
    }
    else if(day>20 && day<30)
    {
        cout<<"إ"<<nongday[day%10];
    }
    else if(day==30)
    {
        cout<<"��ʮ";
    }
    cout<<endl;
}

/*��ӡũ��*/
void gregorian_to_lunar (int year,int month,int day)
{
    if(!checkDate(year,month,day))
    {
        cout<<"�������������ȷ��������ȷ�ԣ�"<<endl;
        return;
    }
    cout<<"����:"<<year<<"��"<<month<<"��"<<day<<"��"<<"   "<<"ũ��:";
    int days=getDayTo1939(year,month,day);
    /*����������ӡũ��*/
    printNong(days);
}

/*ͨʽ���ǹ�ʽ �����ʮ�Ľ���  ��ʽ��Դ��https://www.jianshu.com/p/1f814c6bb475*/
/*20,21����Cֵ*/
float C_value_21[]= {3.87,18.73,5.63,20.646,4.81,20.1,5.52,21.04,5.678,21.37,7.108,22.83,7.5,23.13,7.646,23.042,8.318,23.438,7.438,22.36,7.18,21.94,5.4055,20.12};
float C_value_20[]= {4.6295,19.4599,6.3826,21.4155,5.59,20.888,6.318,21.86,6.5,22.2,7.928,23.65,28.35,23.95,8.44,23.822,9.098,24.218,8.218,23.08,7.9,22.6,6.11,20.84};
/*����������*/
float C_month[]= {2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
void solar_term(int year1,char* str)
{
    int year,month,day;
    year=year1;
    int tmp=-1;//��ʾ����˳��
    const char* temp[24]= {"����","��ˮ","����","����","����","����","����","С��","â��","����","С��","����","����","����","��¶","���","��¶","˪��","����","Сѩ","��ѩ","����","С��","��"};
    /*�Ƚ��ַ�����ֵtmp �磺0�ʹ�������*/
    for(int i=0; i<24; i++)
    {
        if(strcmp(str,temp[i])==0)
        {
            tmp=i;
            break;
        }
    }
    if(tmp==-1)
    {
        cout<<"����ƴд����"<<endl;
        return;
    }

    if(tmp==0||tmp==1||tmp==22||tmp==23)
    {
        if(year>=2000)
        {
            month=C_month[tmp];
            day=floor((year%100)*0.2422+C_value_21[tmp])-floor((year%100-1)/4);
        }
        else
        {
            month=C_month[tmp];
            day=floor((year%100)*0.2422+C_value_20[tmp])-floor((year%100-1)/4);
        }
    }
    else
    {
        if(year>=2000)
        {
            month=C_month[tmp];
            day=floor((year%100)*0.2422+C_value_21[tmp])-floor((year%100)/4);
        }
        else
        {
            month=C_month[tmp];
            day=floor((year%100)*0.2422+C_value_20[tmp])-floor((year%100)/4);
        }
    }

//�������
    if((year==2026 && tmp==1)||(year==1918 && tmp==21)||(year==2021 && tmp==21)||(year==2019 && tmp==22))
    {
        day--;
    }
    if((year==2084 && tmp==3)||(year==1911 && tmp==6)||(year==2008 && tmp==7)||(year==1902 && tmp==8)||(year==1928 && tmp==9)||(year==1925 && tmp==10)||(year==2016 && tmp==10)||(year==1922&& tmp==11)||(year==2002&&tmp==12)||(year==1927&&tmp==14)||(year==1942&&tmp==15)||(year==2089 && tmp==17)||(year==2089&&tmp==18)||(year==1978&&tmp==19)||(year==2054 && tmp==20)||(year==1982&&tmp==22)||(year==2000 && tmp==23)||(year==2082&&tmp==23))
    {
        day++;
    }
    if(C_month[tmp]>12)
    {
        month=1;
    }
    cout<<temp[tmp]<<": ";
    /*���ݹ�ʽ����������գ�����ת��Ϊũ��*/
    gregorian_to_lunar (year,month,day);
}
