//
//  main.cpp
//  palindrome
//
//  Created by Alex Hoff on 2/3/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "palindrome.h"
using namespace std;


int main (){
    Stack main;
    Stack back;
    Stack reverse;
    
    char letter;
    cout << "Enter a line to see if it is a palindrome:";
    
    while (cin.peek() != '\n') {
        cin >> letter;
        if (isalpha(letter))
        {
            main.push(letter);
            back.push(letter);
        }
    }
    int inc1=0;
    char man[20];
    while (char j = main.pop()) {
        reverse.push(j);
        man[inc1] = j;
        inc1++;
    }
    
    int inc=0;
    char rev[20];
    while (char f = reverse.pop()) {
        rev[inc] = f;
        inc++;
    }
    
    for (int w=0; w<=inc; w++) {
        if (rev[w] != man[w]) {
            cout << "That is not a palindrome." << endl;
            return 0;
        }
        cout << "That is a palindrome." << endl;
        return 1;
    }
}