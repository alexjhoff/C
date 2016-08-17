//
//  main.cpp
//  practice
//
//  Created by Alex Hoff on 2/5/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#include <iostream>
using namespace std;

class Animal
{
public:
    virtual void talk()
    {
        cout << "OOPS\n";
    }
};

class Cat : public Animal
{
public:
    virtual void talk() //dont need to add if already virtual in Animal
    {
        cout << "Meow\n";
    }
};

class Dog: public Animal
{
public:
    virtual void talk()
    {
        cout << "Woof\n";
    }
};

class Fox: public Animal
{
public:
    virtual void talk()
    {
        cout << "Ring ding ding a ding dang ding dong\n";
    }
};

int main()
{
    Animal* Farm[3];
    Farm[0] = new Cat;
    Farm[1] = new Dog;
    Farm[2] = new Fox;
    
    Farm[0] -> talk();
    Farm[1] -> talk();
    Farm[2] -> talk();
    
    //delete[] Farm;
    int i;
    cin >> i;
    return 0;
}