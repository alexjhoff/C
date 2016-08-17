//
//  RBTree.h
//  RBTree
//
//  Created by Alex Hoff and Eric Beckmann on 3/3/14.
//  Copyright (c) 2014 Alex Hoff. All rights reserved.
//  Lab 9
//  Tues 2:15
//


#include "RBNode.h"
#include <iostream>

class RBTree {
public:
    RBTree();
    ~RBTree();
    void printTree();
    void addNode(int);
    void preorder(RBNode<int>*);
    RBNode<int>* getSibling(RBNode<int>*);
    RBNode<int>* getAunt(RBNode<int>*);
    RBNode<int>* getGrandparent(RBNode<int>*);
    void rotateLeft(RBNode<int>*);
    void rotateRight(RBNode<int>*);
    void fixTree(RBNode<int>*);
    
private:
    RBNode<int>* root;
};


RBTree::RBTree(){
    root = NULL;
}

RBTree::~RBTree(){
    delete root;
}

void RBTree::addNode(int input){
    RBNode<int>* temp = root;
    
    if (root == NULL) {
        root = new RBNode<int>();
        root->set_data(input);
        fixTree(root);
        return;
    }
    
    RBNode<int>* newnode = new RBNode<int>();
    while (true) {

        if (temp->data() > input){
            if (temp->left() == NULL){
                newnode->set_data(input);
                newnode->set_parent(temp);
                temp->set_left(newnode);
                break;
            }
            else
                temp = temp->left();
        }
        else{
            if (temp->right() == NULL){
                newnode->set_data(input);
                newnode->set_parent(temp);
                temp->set_right(newnode);
                break;
            }
            else
                temp = temp->right();
        }
    }
    fixTree(newnode);
}

void RBTree::preorder(RBNode<int>* p){
	cout << p->data() << " ";
    
	if(p->left() != NULL)
		preorder(p->left());
    
	if(p->right() != NULL)
		preorder(p->right());
}

void RBTree::printTree(){
	preorder(root);
}

RBNode<int>* RBTree::getSibling(RBNode<int>* p){
	RBNode<int>* sibling = NULL;
    
	if(p->parent() != NULL){
		if(p->parent()->left() == p) sibling = p->parent()->right();
		else sibling = p->parent()->left();
	}
    
	return sibling;
}

RBNode<int>* RBTree::getAunt(RBNode<int>* input){
    if (input->parent() != NULL) {
        return getSibling(input->parent());
    }
    return NULL;
}

RBNode<int>* RBTree::getGrandparent(RBNode<int>* p){
	RBNode<int>* grandparent = NULL;
    
	if(p->parent() != NULL){
		grandparent = p->parent()->parent();
	}
	return grandparent;
}


void RBTree::rotateLeft(RBNode<int>* x){
	RBNode<int>* top = x->parent();
	RBNode<int>* y = x->right();
	RBNode<int>* b = y->left();
    
	if(b != NULL) b->set_parent(x);
	y->set_left(x);
	y->set_parent(top);
	x->set_right(b);
	x->set_parent(y);
    
	if(x == root) root = y;
	else{
		if(top->left() == x) top->set_left(y);
		else top->set_right(y);
	}
}

void RBTree::rotateRight(RBNode<int>* y){
	RBNode<int>* top = y->parent();
	RBNode<int>* x = y->left();
	RBNode<int>* b = x->right();
    
	if(b != NULL) b->set_parent(y);
	x->set_right(y);
	x->set_parent(top);
	y->set_left(b);
	y->set_parent(x);
    
	if(y == root) root = x;
	else{
		if(top->left() == y) top->set_left(x);
		else top->set_right(x);
	}
}



void RBTree::fixTree(RBNode<int>* current){
	if(current == root){
		current->set_color(RBNode<int>::BLACK);
		return;
	}
	else if(current->parent()->color() == RBNode<int>::BLACK){
		return;
	}
	else if((current->color() == RBNode<int>::RED) && (current->parent()->color() == RBNode<int>::RED)){
		if((getAunt(current) == NULL) || (getAunt(current)->color() == RBNode<int>::BLACK)){
            if((getGrandparent(current)->left() == current->parent()) && (current->parent()->right() == current)){
                RBNode<int>* originalParent = current->parent();
                rotateLeft(current->parent());
                fixTree(originalParent);
            }
            else if((getGrandparent(current)->right() == current->parent()) && (current->parent()->left() == current)){
                RBNode<int>* originalParent = current->parent();
                rotateRight(current->parent());
                fixTree(originalParent);
            }
            else if((getGrandparent(current)->left() == current->parent()) && (current->parent()->left() == current)){
                current->parent()->set_color(RBNode<int>::BLACK);
                getGrandparent(current)->set_color(RBNode<int>::RED);
                rotateRight(getGrandparent(current));
                return;
            }
            else{
                current->parent()->set_color(RBNode<int>::BLACK);
                getGrandparent(current)->set_color(RBNode<int>::RED);
                rotateLeft(getGrandparent(current));
                return;
            }
		}
		else{
			current->parent()->set_color(RBNode<int>::BLACK);
			getAunt(current)->set_color(RBNode<int>::BLACK);
			getGrandparent(current)->set_color(RBNode<int>::RED);
			fixTree(getGrandparent(current));
		}
	}
}
