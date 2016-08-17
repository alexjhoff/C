//
//  BMI.h
//  BMI
//
//  Created by Alex Hoff on 2/9/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#ifndef BMI_BMI_h
#define BMI_BMI_h
#include <iostream>
using namespace std;

class people
{
public:
    people();   //constructor
    int age();  //age based on birthday
    void set_weight(double);   //sets weight
    void set_height(int);  //sets height
    void set_birthdate(int, int, int); //sets birthday
    double get_weight();  //retrieves weight
    int get_height();
    virtual double BMI() = 0;
    virtual double calorie(double) = 0;
protected:
    string name;
    int birth_day;
    int birth_month;
    int birth_year;
    double weight;
    int height;
    double BMR;
};

class male: public people
{
public:
    double BMI();
    double calorie(double);
};

class female: public people
{
public:
    double BMI();
    double calorie(double);
};

people::people()
{
    birth_day = 0;
    birth_month = 0;
    birth_year = 0;
    weight = 0;
    height = 0;
}

int people::age()
{
    int age = 2014 - birth_year;
    if (birth_month > 2) {
        age--;
    }
    return age;
}

void people::set_weight(double new_weight)
{
    weight = new_weight;
}

void people::set_height(int new_height)
{
    height = new_height;
}

void people::set_birthdate(int day, int month, int year)
{
    birth_day = day;
    birth_month = month;
    birth_year = year;
}

double people::get_weight()
{
    return weight;
}

int people::get_height()
{
    return height;
}

double male::BMI()
{
    BMR = 66 + (30.14 * get_weight()) + (1.97 * get_height()) - (6.8 * age());
    return BMR;
}

double female::BMI()
{
    BMR = 655 + (21.12 * get_weight()) + (.71 * get_height()) - (4.7 * age());
    return BMR;
}

double male::calorie(double cal)
{
    double calories;
    calories = BMR * cal;
    return calories;
}

double female::calorie(double cal)
{
    double calories;
    calories = BMR * cal;
    return calories;

}

#endif
