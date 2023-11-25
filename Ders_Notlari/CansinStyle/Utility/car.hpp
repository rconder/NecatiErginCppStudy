#pragma once
#include <iostream>

class Car{
    public:
        virtual void start(){std::cout<<"Car has just started\n";}
        virtual void run(){std::cout<<"Car is running now\n";}
        virtual void stop(){std::cout<<"Car has stopped \n";}
};
class Bmw:public  Car{
    public:
        void start(){std::cout<<"Bmw has just started\n";}
        void run(){std::cout<<"Bmw is running now\n";}
        void stop(){std::cout<<"Bmw has stopped \n";}
};
class Fiat:public Car{
    public:
        void start(){std::cout<<"fiat has just started\n";}
        void run(){std::cout<< "fiat is running now\n";}
        void stop(){std::cout<<"fiat has stopped \n";}
};
class Volvo:public Car{
    public:
        void start(){std::cout<<"Volvo has just started\n";}
        void run(){std::cout<<"Volvo is running now\n";}
        void stop(){std::cout<<"Volvo has stopped \n";}
        void open_sunroof(){    std::cout<<"Sun roof is openning for Volvo\n";}//Run time identification ile ekledik
};
class VolvoS60:public Volvo{
    public:
        void start(){std::cout<<"VolvoS60 has just started\n";}
        void run(){std::cout<<"VolvoS60 is running now\n";}
        void stop(){std::cout<<"VolvoS60 has stopped \n";}
};
class VolvoXC90:public Volvo{
    public:
        void start(){std::cout<<"VolvoXC90 has just started\n";}
        void run(){std::cout<<"VolvoXC90 is running now\n";}
        void stop(){std::cout<<"VolvoXC90 has stopped \n";}
};
class Toyota :public Car{
    public:
        void start(){std::cout<<"Toyota has just started\n";}
        void run(){std::cout<<"Toyota is running now\n";}
        void stop(){std::cout<<"Toyota has stopped \n";}
};
class Dacia:public Car{
public:
        void start(){std::cout<<"Dacia has just started\n";}
        void run(){std::cout<<"Dacia is running now\n";}
        void stop(){std::cout<<"Dacia has stopped \n";}
};

Car *create_random_car()
{
    static std::mt19937 eng{std::random_device{}()};
    static std::uniform_int_distribution dist{1,7};
    switch (dist(eng))
{
    case 1: std::cout<<"Bmw uretildi";return new Bmw;
    case 2: std::cout<<"Fiat uretildi"; return new Fiat;
    case 3: std::cout<<"Volvo uretildi"; return new Volvo;
    case 4: std::cout<<"Toyota uretildi"; return new Toyota;
    case 5: std::cout<<"Dacia uretildi";return new Dacia;
    case 6: std::cout<<"VolvoS60 uretildi"; return new VolvoS60;
    case 7: std::cout<<"VolvoXC90 uretildi";return new VolvoXC90;
    default:
    break;
}
}

inline std::ostream& operator<<(std::ostream& os, const Car& other;)