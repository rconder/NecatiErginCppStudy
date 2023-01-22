#include <iostream>
#include <ctime>
#define CRT_SECURE_NO_WARNINGS

void process_date(int day = -1, int mon = -1, int year = -1 );

int main()
{
    process_date(3,5,1987);
    process_date(3,5);
    process_date(3);
    process_date();

}

//void process_date(int day = -1, int mon = -1, int year = -1 ) sentaks hatası
void process_date(int day , int mon , int year )
{
    std::time_t timer;
    std::time(&timer);

    std::tm * p = std::localtime(&timer);

    if(year == -1 )
    {
        year = p->tm_year + 1900;
        if(mon == -1 )
        {
            mon = p->tm_mon;
            if(day == -1 )
            {
                day = p->tm_mday;
            }
        }
    }

    //test
    std::cout << day << "-" << mon << "-" << year << "\n"; 
}