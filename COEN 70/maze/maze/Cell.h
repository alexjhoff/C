//
//  Cell.h
//  maze
//
//  Created by Alex Hoff on 3/10/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

#ifndef maze_Header_h
#define maze_Header_h

//Charles Mulloy
//Alex Hoff
//Eric Beckmann

//COEN 70 2:15 Lab
//Lab 10

using namespace std;

class Cell
{
    
public:
    
    
    /* Function: Constructors */
    Cell()
    {
        up = NULL;
        down = NULL;
        left = NULL;
        right =NULL;
        
        visited = false;
        walls = 4;
        dfs = 0;
		index = -1;
        
    };
    
    /* Function: Destructor */
    //~Cell();
    
    // The Demolition Team
    void knockUp(Cell *c);
    void knockDown(Cell *c);
    void knockLeft(Cell *c);
    void knockRight(Cell *c);
    
    //Them Getters
    int getWalls(){return walls;};
    int getDFS(){return dfs;};
    bool wasVisited(){return visited;};
    
	void setVisited(){visited = true;};
    
    Cell* getUp(){return this->up;};       //get up, stand up, stand up for your rights
    Cell* getDown(){return this->down;};  // get down tonight, lets boogey!
    Cell* getLeft(){return this->left;};
    Cell* getRight(){return this->right;}
	int getIndex(){return index;}
    
	void setIndex(int num){
		index = num % 10;
	}
    
    
    // Get Ready, Get Set
    void setUp(Cell *c){this->up = c;};
    void setDown(Cell *c){this->down = c;};
    void setLeft(Cell * c){this->left = c;};
    void setRight(Cell *c){this->right = c;};
    
    
    
    
protected:
    
    Cell *up;
    Cell *down;
    Cell *left;
    Cell *right;
    
    bool visited;
    int walls;
    int dfs;
	int index;
    
    
};



void Cell::knockUp(Cell *c)
{
    c->down = this;
    this->up = c;
    
    c->walls--;
    this->walls--;
}

void Cell::knockDown(Cell *c)
{
    c->up = this;
    this->down = c;
    
    c->walls--;
    this->walls--;
}

void Cell::knockLeft(Cell *c)
{
    c->right = this;
    this->left = c;
    
    c->walls--;
    this->walls--;
    
}

void Cell::knockRight(Cell *c)
{
    c->left = this;
    this->right = c;
    
    c->walls--;
    this->walls--;
    
}



#endif
