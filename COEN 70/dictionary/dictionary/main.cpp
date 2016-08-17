//
//  main.cpp
//  dictionary
//
//  Created by Alex Hoff on 3/9/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#include "dictionary.h"
#include <iostream>

using namespace std;

class word{
public:
    word();
    word(string, string);
    string key;
    string defenition;
};

word::word(){
    key = "NEVER_USED";
    defenition = "NEVER_USED";
}

word::word(string in_key, string in_defenition){
    key = in_key;
    defenition = in_defenition;
}

int main()
{
    string input_word;
    string input_defenition;
    string empty;
    table<word> dictionary;
    int capacity;
    
    cout << "Welcome to dictionary!" << endl;
    
    cout << "First lets add some words into your dictionary" << endl << "How many words would you like to add?" << endl << "Number of words:";
    cin >> capacity;
    cout << endl << "Great! We'll add " << capacity << " words!" << endl;
    
    for (int i = 0; i < capacity; i++) {
        cout << endl << "Word:";
        cin >> input_word;
        //cin >> empty;
        cout << "Defenition:";
        getline(cin, input_defenition); //this doesnt work for some reason
        getline(cin, input_defenition);
        word temp = *new word(input_word, input_defenition);
        dictionary.insert(temp);
    }
    
    bool found;
    word result;
    cout << endl << "Now enter a word to get its defenition." << endl << "Input:";
    cin >> input_word;
    dictionary.find(input_word, found, result);
    if (found) {
        cout << "Defenition: " << result.defenition << endl;
    }
    else
        cout << "The word you entered could not be found" << endl;
    
    

}

