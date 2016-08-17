//
//  main.cpp
//  BMI
//
//  Created by Alex Hoff on 2/9/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#include <iostream>
#include "BMI.h"
using namespace std;

int main()
{
    people *y = nullptr;
    male x;
    female z;
    string name, gender;
    cout << "Welcome to your personal profile!" << endl << endl << "To begin, Please enter your name:";
    cin >> name;
    cout << endl << endl << "Thank you " << name << " please enter your gender:";
    while (1){
        cin >> gender;
        if (gender == "Male" || gender == "male"){
            y = &x;
            break;
        }
        if (gender == "Female" || gender == "female"){
            y = &z;
            break;
        }
        else{
            cout << "Invalid expression" << endl << "Please enter your gender again:";
        }
    }
        
    int day, month, year, height;
    cout << "Thank you!" << endl << endl << "Now please enter your" << endl << "Day of birth:";
    cin >> day;
    cout << endl << "Month of birth:";
    cin >> month;
    cout << endl << "Year of birth:";
    cin >> year;
    y->set_birthdate(day, month, year);
    
    double weight;
    if (gender == "Male" || gender == "male")
        cout << endl << "Weight in pounds:";
    if (gender == "Female" || gender == "female")
        cout << endl << "Weight in kilos:";
    cin >> weight;
    y->set_weight(weight);
    
    cout << endl << "Height in inches:";
    cin >> height;
    y->set_height(height);
 
    
    double cal = 0.0;
    string fitness;
    cout << endl << "Please enter the letter for your physical activity level:" << endl << "(a) Sedentary" << "(b) lightly active" << "(c) moderatley active" << "(d) highly active" << endl << "Physical activity level:";
    while (1){
        cin >> fitness;
        if (fitness == "a"){
            cal = 1.2;
            break;
        }
        else if (fitness == "b"){
            cal = 1.35;
            break;
        }
        else if (fitness == "c"){
            cal = 1.55;
            break;
        }
        else if (fitness == "d"){
            cal = 1.725;
            break;
        }
        else
            cout << "Invalid expression" << endl;
    }
    
    double calories = 0.0;
    calories = y->calorie(cal);
    cout << "Calories" << calories;
    
    
    cout << endl << endl << "Thank you!" << endl << "Your BMI is:" << y->BMI() << endl << "Your reccomended caloric intake is:" << (y->BMI() * cal) << "calories" << endl;
    
    return 0;
}

