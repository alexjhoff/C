//
//  main.cpp
//  prisoner
//
//  Created by Alex Hoff on 1/28/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//


#include <iostream>
#include "prisoner.h"
using namespace std;

int main()
{
    Prisoner p;
    int num;
    int i, j;
    
    cout << "Enter the number of Prisoners:";
    cin >> num;
    cout << endl;
    
    for (i=num; i>0; i--) {
        p.insert(i);
    }
    
    cout << "The Prisoners who are still in line are:" << endl;
    p.print();
    cout << endl;
    
    cout << "Enter the number of passes:";
    cin >> j;
    cout << endl;
    
    while (num != 1) {
        p.move(j);
        p.eliminate();
        num--;
    }
    
    cout << endl << "The Prisoners who are still in line are:" << endl;
    p.print();
    cout << endl;
    
    cout << endl;
    cout << "Winning player:";
    p.print();
    cout << endl;
    
    return 0;
}