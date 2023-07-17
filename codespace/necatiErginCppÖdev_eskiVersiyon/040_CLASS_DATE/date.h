#ifndef DATE_H
#define DATE_H

#include <iosfwd>
#include <ctime>

namespace project {
	class Date {
	public:
		static constexpr int year_base = 1900;  //1
		static constexpr int random_min_year = 1940;  //2
		static constexpr int random_max_year = 2020;  //3
		enum class Weekday { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday }; //4
		Date(); //5 
		Date(int d, int m, int y);  //6
		Date(const char* p);  //7
		Date(std::time_t timer); //8
		int get_month_day()const; //9
		int get_month()const; //10
		int get_year()const; //11
		int get_year_day()const; //12
		Weekday get_week_day()const; //13

		Date& set_month_day(int day); //14
		Date& set_month(int month); //15
		Date& set_year(int year); //16
		Date& set(int day, int mon, int year); //17

		Date operator-(int day)const; //18
		Date& operator+=(int day); //19
		Date& operator-=(int day); //20
		Date& operator++(); //21
		Date operator++(int); //22
		Date& operator--(); //23
		Date operator--(int); //24

		friend bool operator<(const Date&, const Date&); //27
		friend bool operator==(const Date&, const Date&); //27

		static Date random_date(); //25
		static constexpr bool isleap(int y); //26

		friend std::ostream& operator<<(std::ostream&, const Date& date); //31
		friend std::istream& operator>>(std::istream&, Date& date); //32
	};

	bool operator<(const Date&, const Date&); //27
	bool operator<=(const Date&, const Date&); //27
	bool operator>(const Date&, const Date&); //27
	bool operator>=(const Date&, const Date&); //27
	bool operator==(const Date&, const Date&); //27
	bool operator!=(const Date&, const Date&); //27

	int operator-(const Date& d1, const Date& d2); //28
	Date operator+(const Date& date, int n); //29
	Date operator+(int n, const Date&); //29
	Date::Weekday& operator++(Date::Weekday&); //30
	Date::Weekday operator++(Date::Weekday&, int); //30
	Date::Weekday& operator--(Date::Weekday&); //30
	Date::Weekday operator--(Date::Weekday&, int); //30}
}
#endif
