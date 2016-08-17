//
//  Employee.h
//  Employee
//
//  Created by Alex Hoff on 1/12/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#ifndef Employee_h
#define Employee_h


#include <iostream>
#include <locale>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

class Employee
{
public:
    // function calls used outside the scope of the object
    //default constructor
    Employee();
    Employee(string name, int id, double salary);//constructor
    //accessor functions
    string get_name();
    int get_id();
    double get_salary();
    //mutator functions
    void set_name(string new_name);
    void set_id(int new_id);
    void set_salary(int new_hours, double wage);
    
    
private:
    // function calls within public functions and any vars
    string name;
    int id;
    int hours; // changes weekely but might be consistant
    double salary; // changes only yearly (promotion)
    
};


#endif
