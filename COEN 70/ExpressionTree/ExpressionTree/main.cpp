//
//  main.cpp
//  ExpressionTree
//
//  Created by Alex Hoff and Nathan Tucker on 2/24/14.
//  Copyright (c) 2014 Alex Hoff and Nathan Tucker. All rights reserved.
//

#include <iostream>
#include "ExpressionTree.h"
#include <algorithm>
using namespace std;

int main()
{
    Tree x;
    string line;
    cout << "Please enter a postfix expression" << endl;
    getline(cin, line);
    cout << "line:" << line <<endl;
    reverse(line.begin(), line.end());
    cout << "new line:" << line << endl;
    x.build(line);
    
    
     cout << "Preorder:" << endl;
     x.print_preorder();
     cout << endl;
     
     cout << "Postorder:" << endl;;
     x.print_postorder();
     cout << endl;
     
     cout << "Inorder:" << endl;
     x.print_inorder();
     cout << endl;
     
     
    cout << "Evaluate:" << x.evaluate() << endl;
}

