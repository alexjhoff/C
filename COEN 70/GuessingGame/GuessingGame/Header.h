//
//  Header.h
//  GuessingGame
//
//  Created by Alex Hoff and Charles Mulloy on 2/10/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifndef GuessingGame_Header_h
#define GuessingGame_Header_h

class Player {
public:
    Player(){}
    virtual ~Player(){}
    virtual int getGuess(){return 0;}
    // Returns the players next guess, an integer between
    // 0 and 99 (inclusive)
    virtual void lastWasTooHigh(bool tooHigh){}
    // Called to inform the player that their last guess
    // was too high (if the tooHigh argument is true) or
    // too low (if the tooHigh argument is false)
    virtual void opponentsGuess(int guess, bool tooHigh){}
    // Called to tell the player what the opponent's last
    // guess was, and whether it was too high or too low.
    virtual void reset(){}
    // Called to reset the player at the end //of the game.
    // Any stored state about the last guess //should be cleared.
    virtual int get_num_guesses(){return 0;}
    virtual void set_current(int guess){}
    virtual void set_high(bool){};
};



class HumanPlayer: public Player{
public:
    HumanPlayer();
    ~HumanPlayer(){};
    int getGuess();
    void lastWasTooHigh(bool);
    void opponentsGuess(int, bool);
    void set_current(int);
    void reset();
    int get_num_guesses(){return num_guesses;};
private:
    int num_guesses;
    int current_guess;
};

class ComputerPlayer: public Player{
public:
    ComputerPlayer();
    ~ComputerPlayer(){};
    void lastWasTooHigh(bool);
    void opponentsGuess(int, bool);
    int getGuess();
    void set_current(int);
    void reset();
    int get_num_guesses(){return num_guesses;};
    void set_high(bool);
private:
    int num_guesses;
    int current_guess;
    bool high;
};

HumanPlayer::HumanPlayer()
{
    num_guesses = 0;
    current_guess = 0;
}

ComputerPlayer::ComputerPlayer(){
    num_guesses = 0;
    current_guess = 0;
    high = NULL;
}

int HumanPlayer::getGuess(){
    int guess;
    cout << "Please enter a your guess from 0 to 99:";
    cin >> guess;
    cout << "Thank you, your guess of " << guess << " has been recieved" << endl;
    num_guesses++;
    current_guess = guess;
    return guess;
}

void HumanPlayer::lastWasTooHigh(bool tooHigh){
    if (tooHigh == true) {
        cout << "last guess was too high" << endl;
    }
    else if (tooHigh == false)
        cout << "last guess was too low" << endl;
}

void HumanPlayer::opponentsGuess(int guess, bool tooHigh){
    cout << "Your opponents guess was:" << guess << endl << "Your opponents ";
    lastWasTooHigh(tooHigh);
}

void HumanPlayer::reset(){
    num_guesses = 0;
    current_guess = NULL;
}

void ComputerPlayer::lastWasTooHigh(bool tooHigh){
    if (tooHigh == true) {
        cout << "Your last guess was too high" << endl;
    }
    else if (tooHigh == false)
        cout << "Your last guess was too low" << endl;
}

void ComputerPlayer::opponentsGuess(int guess, bool tooHigh){
    cout << "Your opponents guess was:" << guess << endl;
    lastWasTooHigh(tooHigh);
    current_guess = guess;
}


int ComputerPlayer::getGuess(){
    int answer = -1;
    srand (time(NULL));
    if (high == true) {     //last guess was too high
        answer = (rand() % current_guess);
    }
    else if (high == false){    //last guess was too low
        answer = ((rand() % (100-current_guess)) + current_guess);
    }
    else
        cout << "Invalid boolean value";
    current_guess = answer;
    num_guesses++;
    return answer;
}

void ComputerPlayer::reset(){
    num_guesses = 0;
    current_guess = NULL;
    high = NULL;
}

void HumanPlayer::set_current(int guess)
{
    current_guess = guess;
}

void ComputerPlayer::set_current(int guess)
{
    current_guess = guess;
}

void ComputerPlayer::set_high(bool fool){
    high = fool;
}

#endif
