//
//  main.cpp
//  GuessingGame
//
//  Created by Alex Hoff and Charles Mulloy on 2/10/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#include <iostream>
#include "Header.h"

using namespace std;

int main()
{
    Player* p1;
    Player* p2;
    ComputerPlayer x;
    ComputerPlayer y;
    HumanPlayer z;
    HumanPlayer w;
    string response = "yes";
    while(response == "yes")
    {
        
        int winning_answer;
        int num_hum_players;
        bool Game_Over = false;
        bool wasHigh;
        int oppGuess;
        
        srand (time(NULL));
        winning_answer = (rand() % 100 );
        
        cout << endl << "Welcome to the Number Guessing Game" << endl;
        cout << "How many human players are playing?" << endl;
        cin  >> num_hum_players;
        if (num_hum_players > 2 || num_hum_players < 0)
        {
            cout << "You cannot have " << num_hum_players << "players. Please choose either 0, 1, or 2 players" << endl;
            return 0;
        }
        if (num_hum_players == 0)
        {
            p1 = &x;
            p2 = &y;
        }
        if (num_hum_players == 1)
        {
            p1 = &z;
            p2 = &x;
            
        }
        if (num_hum_players == 2)
        {
            p1 = &z;
            p2 = &w;
        }
        
        while(Game_Over == false)
        {
            cout << endl << "Player 1's turn. What is your guess?" << endl;
            oppGuess = p1->getGuess();
            p2->set_current(oppGuess);
            if(oppGuess == winning_answer)
            {
                cout << " That is the correct number! Player 1 has won the game!" << endl << "It took Player 1 " << p1->get_num_guesses() << " turns to get the correct answer." << endl;
                Game_Over = true;
                break;
            }
            else
            {
                if (oppGuess > winning_answer) {
                    wasHigh = true;
                }
                else
                    wasHigh = false;
                cout << "Sorry that was the incorrect answer, your ";
                p1->lastWasTooHigh(wasHigh);
            }
            
            cout << endl << endl;
            p1->opponentsGuess(oppGuess, wasHigh);
            
            cout << endl << "Player 2's turn. What is your guess?" << endl;
            p2->set_high(wasHigh);
            oppGuess = p2->getGuess();
            p1->set_current(oppGuess);
            if(oppGuess == winning_answer)
            {
                cout << " That is the correct number! Player 2 has won the game!" << endl << "It took Player 2 " << p2->get_num_guesses() << " turn to get the correct answer." << endl;
                Game_Over = true;
                break;
            }
            else
            {
                if (oppGuess > winning_answer) {
                    wasHigh = true;
                }
                else
                    wasHigh = false;
                cout << "Sorry that was the incorrect answer, your ";
                p2->lastWasTooHigh(wasHigh);
            }
            cout << endl << endl;
            p2->opponentsGuess(oppGuess, wasHigh);
        }
        p1->reset();
        p2->reset();
        while (1) {
            cout << " Game over." << endl << "Type 'yes' if you would like to play again." << endl << "Type 'no' if you would like  to quit" << endl << "Answer:";
            cin >> response;
            if( response == "yes")
                break;
            else if(response == "no"){
                cout << "Thank you for playing";
                return 0;
            }
            else
                cout << endl << "invalid response, try again" << endl;
        }
        
    }
    return 0;
}