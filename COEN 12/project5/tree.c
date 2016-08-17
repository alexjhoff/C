/*
 * File: tree.c
 *
 *
 * Description:This program implements a binary tree. The tree is
 * made up of a root node that points to two other nodes, a left
 * and right node. These nodes have parent nodes so that the left
 * and right nodes point back to the root. When inserting, 
 * the function must check if the root already has a
 * left or right pointer and must also check if the node that is
 * being inserted already has a parent node. The program must then
 * deassociate these nodes so that the node can be properly inserted.
 *
 */

# include <assert.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "tree.h"
# include "pack.h"
#define NODE struct tree

struct tree{
	int data;
	NODE *parent;
	NODE *left;
	NODE *right;
};

/* Function: check
 *
 * Description: Checks if the root already has a parent node
 * and if it does, the root is detached from the parent node.
 *
 * O(1)
 */
void check(struct tree *root){
		if (root->parent != NULL){
			if (root->parent->right == root)
				root->parent->right = NULL;
			else
				root->parent->left = NULL;
		}
}

/* Function: createTree
 *
 * Description: Creates the tree by allocating memory and assigning
 * values to the node. It first checks to make sure the nodes being
 * assigned to the root do not already have parents before assigning
 * the root as the parent node.
 *
 * O(1)
 */
struct tree *createTree(int data, struct tree *left, struct tree *right){
	struct tree *root;
	//allocate memory for the new tree root
	root = malloc(sizeof(struct tree));
	assert (root != NULL);
	//assign values to the node
	root->parent = NULL;
	root->left = left;
	root->right = right;
	root->data = data;
	if (left != NULL){
		check(left);
		left->parent = root;
	}
	if (right != NULL) {
		check(right);
		right->parent = root;
	}
	return root;
}

/* Function: destroyTree
 *
 * Description: Deallocates memory for the entire subtree
 * pointed to by root recursively.
 *
 * O(h)
 */
void destroyTree(struct tree *root){
	if(root != NULL)
		return;
	destroyTree(root->left);
	destroyTree(root->right);
	free(root);
}

/* Function: getData
 *
 * Description: Returns the data in the root of the subtree
 * pointed to by root.
 *
 * O(1)
 */
int getData(struct tree *root){
	return root->data;
}

/* Function: getLeft
 *
 * Description: Returns the left subtree of the subtree
 * pointed to by root.
 *
 * O(1)
 */
struct tree *getLeft(struct tree *root){
	return root->left;
}

/* Function: getRight
 *
 * Description: Returns the right subtree of the subtree
 * pointed to by root.
 *
 * O(1)
 */
struct tree *getRight(struct tree *root){
	return root->right;
}

/* Function: getParent
 *
 * Description: Return the parent tree of the subtree
 * pointed to by root.
 *
 * O(1)
 */
struct tree *getParent(struct tree *root){
	return root->parent;
}

/* Function: setLeft
 *
 * Description: Sets the left subtree of the root
 *
 * O(1)
 */
void setLeft(struct tree *root, struct tree *left){
	if (root->left != NULL){
		root->left->parent = NULL;
		root->left = NULL;
	}
	if (left != NULL){
		check(left);
		left->parent = root;
	}	
	root->left = left;
	left->parent = root;
	return;
}

/* Function: setRight
 *
 * Description: Sets the right subtree of the root
 *
 * O(1)
 */
void setRight(struct tree *root, struct tree *right){
	if (root->right != NULL){
		root->right->parent = NULL;
		root->right = NULL;
	}
	if (right != NULL) {
		check(right);
		right->parent = root;
	}	
	root->right = right;
	right->parent = root;
	return;
}
