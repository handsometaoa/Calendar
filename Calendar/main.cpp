#include <iostream>
#include "Date.h"
using namespace std;

int main()
{

    int num;
    char solar_Terms[3];
    int year,month,day;
    print();
    while(1)
    {

        cout<<"\n��ѡ�������ţ�";
        cin>>num;
        switch(num)
        {
        case 1:
            cout<<"������Ҫ��ѯ����ݣ�";
            cin>>year;
            print_annual_calendar(year);
            break;
        case 2:
            cout<<"������Ҫ��ѯ���ꡢ�£�";
            cin>>year>>month;
            print_monthly_calendar(year,month);
            break;
        case 3:
            cout<<"������Ҫ��ѯ���ꡢ�¡��գ�";
            cin>>year>>month>>day;
            print_number_week(year,month,day);
            break;
        case 4:
            cout<<"������Ҫ��ѯ���ꡢ�¡��գ�";
            cin>>year>>month>>day;
            gregorian_to_lunar (year,month,day);
            break;
        case 5:
            cout<<"������Ҫ��ѯ����ݼ�������";
            cin>>year>>solar_Terms;
            solar_term(year,solar_Terms);
            break;
        case 0:
            return 0;
        }
    }
    return 0;
}
