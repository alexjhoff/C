//
//  ExpressionTree.h
//  ExpressionTree
//
//  Created by Alex Hoff and Nathan Tucker on 2/24/14.
//  Copyright (c) 2014 Alex Hoff and Nathan Tucker. All rights reserved.
//

#ifndef ExpressionTree_ExpressionTree_h
#define ExpressionTree_ExpressionTree_h

#include <iostream>
#include <string>
using namespace std;

class Tree
{
public:
    ~Tree();
    Tree();
    void build(string&);
    int evaluate();
    void print_preorder();
    void print_postorder();
    void print_inorder();
    int operand;
    char opertor;
    Tree* right_field;
    Tree* left_field;
};

Tree::Tree(){
    operand = -1;
    opertor = '\0';
    right_field = NULL;
    left_field = NULL;
}

Tree::~Tree(){
    delete left_field;
    delete right_field;
}

void Tree::build(string &temp){
    if (isdigit(temp[0])){
        operand = temp[0] - '0';
        return;
    }
    else{
        opertor = temp[0];
        left_field = new Tree();
        right_field = new Tree();
        left_field->build(temp.erase(0,2));
        if (temp.length() <= 2) {
            right_field->build(temp);
            return;
        }
        right_field->build(temp.erase(0,2));
    }
}

int Tree::evaluate(){
    
    if (opertor != '\0') {
        if(opertor == '*'){
            return (left_field->evaluate() * right_field->evaluate());
        }
        else if (opertor == '/'){
            return (left_field->evaluate() / right_field->evaluate());
        }
        else if (opertor == '+'){
            return (left_field->evaluate() + right_field->evaluate());
        }
        else if(opertor == '-'){
            return (right_field->evaluate() - left_field->evaluate());
        }
    }
    return operand;
}



//We have no clue why our prints are not working
//We talked to you in lab and you couldnt figure it out either
//we are taking it to prof. potika
void Tree::print_inorder(){
    if(left_field) left_field->print_inorder();
    if (opertor == '\0') {
        cout << operand;
    }
    else
        cout << opertor;
    if(right_field) right_field->print_inorder();
}

void Tree::print_preorder(){
    if (opertor == '\0') {
        cout << operand;
    }
    else
        cout << opertor;
    if(left_field) left_field->print_preorder();
    if(right_field) right_field->print_preorder();
}

void Tree::print_postorder(){
    if(left_field) left_field->print_postorder();
    if(right_field) right_field->print_postorder();
    if (opertor == '\0') {
        cout << operand;
    }
    else
        cout << opertor;
}

#endif
