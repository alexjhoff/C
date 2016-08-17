/*Alex Hoff
 Coen 70 MTW 11:45
 Homework Assignment 1: Employee
 */

#include <iostream>
#include <locale>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include "Employee.h"
using namespace std;


bool is_alphabetic(string c)
{
    bool holder = false;
    for(int i = 0; i<c.length(); i++)
    {
        int a = c[i];
        if(a < 'A' || a > 'z')
            holder = true;
    }
    if(holder == false)
        return true;
    else
        return false;

}


Employee::Employee()
{
    string emp_name = "1";
    int emp_id = -1;
    int emp_hours = -1;
    double emp_wage = -1;

    while(!is_alphabetic(emp_name))
    {
        cout << "Enter name: ";
        cin >> emp_name;
    }
    set_name(emp_name);
 
    while(emp_id < 0)
    {
        cout << "Enter ID Number" << endl << "(Warning alpha numeric characters will be accepted)" << endl << "ID Number: ";
        cin >> emp_id;
        cout << endl;
    }
    set_id(emp_id);
    while (emp_hours < 0)
    {
        cout << "Enter weekly hours:" << endl << "(Warning alpha numeric characters will be accepted)" << endl << "Weekly Hours: ";
        cin >> emp_hours;
        cout << endl;
    }
    while (emp_wage < 0) {
        cout << "Enter hourly wage:" << endl << "(Warning alpha numeric characters will be accepted)" << endl << "Hourly Wage: ";
        cin >> emp_wage;
        cout << endl;
    }
    set_salary(emp_hours, emp_wage);
    
    cout << "Thank you " << get_name() << " your profile has been created!" << endl ;
    cout << "Name:" << get_name() << endl << "ID Number:" << get_id() << endl << "Weekly Salary:$" << get_salary() << endl <<endl;

}

Employee::Employee(string i_name, int i_id, double i_salary)
{
    name = i_name;
    id = i_id;
    salary = i_salary;
    }


string Employee::get_name()
{
    return name;
}

int Employee::get_id()
{
    return id;
}

double Employee::get_salary()
{
    return salary;
}

void Employee::set_name(string new_name)
{
    name = new_name;
}

void Employee::set_id(int new_id)
{
    id = new_id;
}

void Employee::set_salary(int new_hours, double wage)
{
    int overtime;
    hours = new_hours;
    
    if (hours > 40) {
        cout << "Input overtime wage: ";
        cin >> overtime;
        salary = (40 * wage)+((hours-40) * overtime);
    }
    else
        salary = (hours * wage);
    
}

int main()
{
    string input;
    int sal_year;
    int biweekly;
    double new_salary;
    double percent;
    double new_percent;

    Employee Emp_1 = Employee();
    while(1){
        cout << "Enter 'Weekly' for weekly salary" << endl << "Enter'Yearly' for yearly salary" << endl << "Enter 'Biweekly' for biweekly paycheck information" << endl << "Enter 'Salary' to increase your salary by a certain percent" << endl << "Enter 'Exit' to exit the program" << endl << "Input:";
        cin >>  input;
        if (input == "weekly" || input == "Weekly") {
            cout << "Your montly salary is:" << Emp_1.get_salary() << endl;
        }
        if (input == "yearly" || input == "Yearly") {
            sal_year = Emp_1.get_salary() * 52;
            cout << "Your yearly salary is:" << sal_year << endl;
        }
        if (input == "biweekly" || input == "Biweekly"){
            biweekly = Emp_1.get_salary() / 2;
            cout << "Your biweekly paycheck will be $" << biweekly <<endl;
        }
        if (input == "salary" || input == "Salary") {
            cout << "Percent to change:";
            cin >> percent;
            new_percent = percent * 0.01;
            new_salary = Emp_1.get_salary() * (1 + new_percent);
            cout << "Your new salary is:" << new_salary << endl << "Percent increased:" << percent << "%" << endl;
        }
        if (input == "exit" || input == "Exit") {
            cout << "Have a nice day!" << endl;
            break;
        }
        cout << endl << endl;
    }
    
    return 0;
}
