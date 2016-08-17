//
//  main.cpp
//  postfix
//
//  Created by Alex Hoff and Zoe Demertzis on 1/27/14.
//  Copyright (c) 2014 Alex Hoff and Zoe. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "header.h"
#include <cstring>
#include <string>
#include <ctype.h>


using namespace std;

int main()
{
    List postfix;
    string line;
    
    
    
    
    for(int z=0; z<10; z++){
        cout << "Please enter a postfix expression" << endl << endl;
        int length=0;
        int j;
        getline(cin, line);
        for(int i=0; i<line.length(); i++){
            
            if (isdigit(line[i])){
                j=i;
                while (line[j] != ' '){
                    length++;
                    j++;
                }
                string sub;
                sub=line.substr(i, length);
                double n;
                n=atof(sub.c_str());
                postfix.insert(n);
                i+=length;
                length=0;
            }
            
            if(line[i] == '*'){
                double x=postfix.pop();
                double y=postfix.pop();
                postfix.insert(x*y);
            }
            else if (line[i] == '/'){
                double x=postfix.pop();
                double y=postfix.pop();
                postfix.insert(y/x);
            }
            else if (line[i] == '+'){
                double x=postfix.pop();
                double y=postfix.pop();
                postfix.insert(x+y);
            }
            else if(line[i] == '-'){
                double x=postfix.pop();
                double y=postfix.pop();
                postfix.insert(y-x);
            }
            
            
        }
        
        cout << "Your answer is " << postfix.pop() << endl << endl;
    }
    
    return 0;
}



