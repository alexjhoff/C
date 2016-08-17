//
//  main.cpp
//  maze
//
//  Created by Alex Hoff on 3/10/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//

//Charles Mulloy
//Alex Hoff
//Eric Beckmann

//COEN 70 2:15 Lab
//Lab 10

#include <iostream>
#include "Cell.h"
#include "CellStack.h"
#include <cstdlib>
#include <time.h>
using namespace std;


int r;

Cell* cell;


void top(int r, int i){
	cout << "+";
	for (int j = 0; j < r; j++) {
		if (cell[j+(i*r)].getUp() == NULL)
			cout << "-";
		else
			cout << " ";
		cout << "+";
	}
	cout << endl;
}

void sides(int r, int i){
	cout << "|";
	for (int j = 0; j < r; j++) {
		if(cell[j+(i*r)].getIndex() > -1) cout << cell[j+(i*r)].getIndex();
		else cout << " ";
		if (cell[j+(i*r)].getRight() == NULL)
			cout << "|";
		else
			cout << " ";
	}
	cout << endl;
}

void sides2(int r, int i){
	cout << "|";
	for (int j = 0; j < r; j++) {
		if(cell[j+(i*r)].getIndex() > -1) cout << "#";
		else cout << " ";
		if (cell[j+(i*r)].getRight() == NULL)
			cout << "|";
		else
			cout << " ";
	}
	cout << endl;
}



int getUp(int index){
	if(index - r >= 0) return index - r;
	else return -1;
}

int getLeft(int index){
	if(index % r != 0) return index - 1;
	else return -1;
}

int getRight(int index){
	if(index % r != r - 1) return index + 1;
	else return -1;
}

int getDown(int index){
	if(index + r < (r*r)) return index + r;
	else return -1;
}

int main(){
    
	srand(time(NULL));
    
	int i;
    
	cout << "Welcome to Mazy-Hazy-Lazy-Yo-Crazy." << endl << "How many rows/columns would you like to have?" << endl << "Rows/Columns:";
	cin >> r;
    
	int n = r * r;
    
	Cell *graph = new Cell[n];
	cell = graph;
    
	CellStack stack;
	int TotalCells = r*r;
	int CurrentCell = 0;
	int VisitedCells = 1;
    
	int visitOrder = 0;
    
	while(VisitedCells < TotalCells){
		int numberOfNeighborsWithAllWallsIntact = 0;
		int whichNeighborsWithAllWallsIntact[4];
        
		for(int i = 0; i < 4; i++){
			whichNeighborsWithAllWallsIntact[i] = 0;
		}
        
		if(getUp(CurrentCell) > -1){
			if(graph[getUp(CurrentCell)].getWalls() == 4){
				numberOfNeighborsWithAllWallsIntact++;
				whichNeighborsWithAllWallsIntact[0] = 1;
			}
		}
		if(getLeft(CurrentCell) > -1){
			if(graph[getLeft(CurrentCell)].getWalls() == 4){
				numberOfNeighborsWithAllWallsIntact++;
				whichNeighborsWithAllWallsIntact[1] = 1;
			}
		}
		if(getRight(CurrentCell) > -1){
			if(graph[getRight(CurrentCell)].getWalls() == 4){
				numberOfNeighborsWithAllWallsIntact++;
				whichNeighborsWithAllWallsIntact[2] = 1;
			}
		}
		if(getDown(CurrentCell) > -1){
			if(graph[getDown(CurrentCell)].getWalls() == 4){
				numberOfNeighborsWithAllWallsIntact++;
				whichNeighborsWithAllWallsIntact[3] = 1;
			}
		}
        
		Cell** neighborsWithAllWallsIntact = new Cell*[numberOfNeighborsWithAllWallsIntact];
        
		int index = 0;
        
		for(int i = 0; i < 4; i++){
			if(whichNeighborsWithAllWallsIntact[i] == 1){
				switch(i){
					case 0:
						neighborsWithAllWallsIntact[index] = &graph[getUp(CurrentCell)];
						break;
					case 1:
						neighborsWithAllWallsIntact[index] = &graph[getLeft(CurrentCell)];
						break;
					case 2:
						neighborsWithAllWallsIntact[index] = &graph[getRight(CurrentCell)];
						break;
					case 3:
						neighborsWithAllWallsIntact[index] = &graph[getDown(CurrentCell)];
						break;
				}
				index++;
			}
		}
        
		if(numberOfNeighborsWithAllWallsIntact >= 1){
			int randomChoice = rand() % numberOfNeighborsWithAllWallsIntact;
			Cell* randomCell = neighborsWithAllWallsIntact[randomChoice];
            
			if(&graph[getUp(CurrentCell)] == randomCell){
				graph[CurrentCell].knockUp(randomCell);
			}
			else if(&graph[getLeft(CurrentCell)] == randomCell){
				graph[CurrentCell].knockLeft(randomCell);
			}
			else if(&graph[getRight(CurrentCell)] == randomCell){
				graph[CurrentCell].knockRight(randomCell);
			}
			else if(&graph[getDown(CurrentCell)] == randomCell){
				graph[CurrentCell].knockDown(randomCell);
			}
            
			stack.push(CurrentCell);
            
            
			if(graph[CurrentCell].getUp() == randomCell){
				CurrentCell = CurrentCell - r;
			}
			else if(graph[CurrentCell].getLeft() == randomCell){
				CurrentCell = CurrentCell - 1;
                
			}
			else if(graph[CurrentCell].getRight() == randomCell){
				CurrentCell = CurrentCell + 1;
			}
			else if(graph[CurrentCell].getDown() == randomCell){
				CurrentCell = CurrentCell +r;
			}
			VisitedCells++;
		}
		else{
			CurrentCell = stack.pop();
		}
        
        
	}
    
    
	for (i = 0; i < r; i++) {
		top(r, i);
		sides(r, i);
	}
	for (i = 0; i < (r-1); i++) {
		cout << "+";
		cout << "-";
	}
	cout << "+ +";
    
	cout << endl;
    
	CellStack finalstack;
    
	CurrentCell = 0;
	while(true){
		graph[CurrentCell].setIndex(visitOrder);
		visitOrder++;
		graph[CurrentCell].setVisited();
		if(CurrentCell == n - 1) break;
        
		if((graph[CurrentCell].getRight() != NULL) && (!graph[getRight(CurrentCell)].wasVisited())){
			finalstack.push(CurrentCell);
			CurrentCell++;
		}
		else if((graph[CurrentCell].getDown() != NULL) && (!graph[getDown(CurrentCell)].wasVisited())){
			finalstack.push(CurrentCell);
			CurrentCell += r;
		}
		else if((graph[CurrentCell].getUp() != NULL) && (!graph[getUp(CurrentCell)].wasVisited())){
			finalstack.push(CurrentCell);
			CurrentCell -= r;
		}
		else if((graph[CurrentCell].getLeft() != NULL) && (!graph[getLeft(CurrentCell)].wasVisited())){
			finalstack.push(CurrentCell);
			CurrentCell--;
		}
		else{
			CurrentCell = finalstack.pop();
		}
	}
    
    
	cout << endl << endl << "DFS solution: " << endl;
    
	for (i = 0; i < r; i++) {
		top(r, i);
		sides(r, i);
	}
	for (i = 0; i < (r-1); i++) {
		cout << "+";
		cout << "-";
	}
	cout << "+ +";
    
	cout << endl;
    
	cout << endl << endl << "solution: " << endl;
    
	for (i = 0; i < r; i++) {
		top(r, i);
		sides2(r, i);
	}
	for (i = 0; i < (r-1); i++) {
		cout << "+";
		cout << "-";
	}
	cout << "+ +";
    
	cout << endl;
    
	system("pause");
    
	return 1;
    
}