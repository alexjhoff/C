//
//  main.cpp
//  power
//
//  Created by Alex Hoff on 2/17/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;

//Precondition: If x is zero then n must be positive.
//Postcondition: The value returned is x raised to the power n.
double pow(double x, int n)
{
    if (x == 0) { //x is zero and n should be positive
        assert(n > 0);
        return 0;
    }
    else if (n == 0)
        return 1;
    else if (n == 1)
        return x;
    else if (n > 1){
        double j = pow(x, n/2);
        return (j*j);
    }
    else
        return 1/pow(x, -n);
}


int main()
{
    double x;
    int n;
    cout << "Hello and welcome to the power function calculator!" << endl << "Please enter a number X followed by the power you would like to raise it to." << endl << "X:";
    cin >> x;
    cout << "N:";
    cin >> n;
    cout << endl << "Thank your for your inputs!" << endl << "The power of " << x << "^" << n << " is:" << pow(x, n) << endl;
    return 0;
}

