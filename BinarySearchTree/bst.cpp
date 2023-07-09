/*
 * bst.cpp
 *
 *  Created on: Oct 13, 2022
 *      Author: karlthimm
 */

#include "bst.hpp"
#include "bstNode.hpp"
#include "Student.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;


bst::bst(){
	root = NULL;
}

bst::bst(string f, string l, int n, string j){
	root = new bstNode(f, l, n, j);
}

bool bst::insert(string f, string l, int n, string j){
	bstNode *insert = new bstNode(f, l, n, j);
	bstNode *temp2 = root;
	if(temp2 == NULL){
		root = insert;
		setHeight(insert);
		return true;
	}
	else{
		while(temp2 != NULL){
			if((insert->student->last) < (temp2->student->last)){
				if(temp2->left == NULL){
					temp2->left = insert;
					insert->parent = temp2;
					setHeight(insert);
					return true;
				}
				else{
					temp2 = temp2->left;
				}
			}
			else if((insert->student->last) > (temp2->student->last)){
				if(temp2->right == NULL){
					temp2->right = insert;
					insert->parent = temp2;
					setHeight(insert);
					return true;
				}
				else{
					temp2 = temp2->right;
				}
			}
			else if((insert->student->last) == (temp2->student->last)){
				if((insert->student->first) == (temp2->student->first)){
					return false;
				}
				else{
					if((insert->student->first) < (temp2->student->first)){
						if(temp2->left == NULL){
								temp2->left = insert;
								insert->parent = temp2;
								setHeight(insert);
								return true;
							}
							else{
								temp2 = temp2->left;
							}
					}
					else if((insert->student->first) > (temp2->student->first)){
						if(temp2->right == NULL){
							temp2->right = insert;
							insert->parent = temp2;
							setHeight(insert);
							return true;
						}
						else{
							temp2 = temp2->right;
						}
					}
					else {
						return false;
					}
				}
			}
		}
	}
	return false;
}

bstNode *bst::find(string l, string f){
	bstNode *now = root;
	if(now == NULL){
		return NULL;
	}
	else{
		while(now != NULL ){
			if(now->student->last < l){
				now = now->right;
			}
			else if(now->student->last > l){
				now= now->left;
			}
			else {
				if (now==NULL) {
					return NULL;
				}
				else {
					if((now->student->first == f) && (now->student->last == l)){
						now->printNode();
						return now;
					}
					else if(now->student->first > f){
						now=now->left;
					}
					else if(now->student->last == l && now->student->first != f){
						if(now->student->first < f){
							now = now->right;
						}
					}
				}
			}
		}
	}
	return now;
}

void bst::printTreeIO(){
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}

void bst::printTreeIO(bstNode *n){
	if(n == NULL){
			return;
	}
	else{
		printTreePre(n->left);
		n->printNode();
		printTreePre(n->right);
	}
}

void bst::printTreePre(){
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}

void bst::printTreePre(bstNode *n){
	if(n == NULL){
		return;
	}
	else{
		n->printNode();
		printTreePre(n->left);
		printTreePre(n->right);
	}
}

void bst::printTreePost(){
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}

void bst::printTreePost(bstNode *n){
	if(n == NULL){
		return;
	}
	else{
		printTreePre(n->left);
		printTreePre(n->right);
		n->printNode();
	}
}

void bst::clearTree(){
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void bst::clearTree(bstNode *tmp){
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}

}

void bst::setHeight(bstNode *n){
	while(n != root){
		n = n->parent;
		if((n->right != NULL) && (n->left != NULL)){
			if((n->right->height < n->left->height)){
				n->height = n->left->height+1;
			}
			else{
				n->height = n->right->height+1;
			}
		}
		else if((n->right == NULL) && (n->left != NULL)){
			n->height = n->left->height + 1;
		}
		else if((n->right != NULL) && (n->left == NULL)){
			n->height = n->right->height + 1;
		}
		else if((n->right == NULL) && (n->left == NULL)){
			n->height = 1;
		}
	}
}

bstNode *bst::removeNoKids(bstNode *tmp){
    if(tmp->parent->student->last == tmp->student->last){
    	if(tmp->student->first > tmp->parent->student->first){
				tmp->parent->right = NULL;
		}
    	else{
			 tmp->parent->left = NULL;
		 }
    }
    else if(tmp->student->last > tmp->parent->student->last){
    	tmp->parent->right = NULL;
    }
    else{
    	tmp->parent->left = NULL;
    }
    setHeight(tmp->parent);
    return tmp;
}

bstNode *bst::removeOneKid(bstNode *tmp, bool leftFlag){
	if(tmp->parent->left == tmp){
		if(leftFlag == true){
			tmp->parent->left = tmp->left;
			tmp->left->parent = tmp->parent;
		}else{
			tmp->parent->left = tmp->right;
			tmp->right->parent = tmp->parent;
		}
		bstNode *current = tmp;
		while(current->left != NULL){
			current = current->left;
		}
		setHeight(current);
	}else{
		if(leftFlag == true){
			tmp->parent->right = tmp->left;
			tmp->left->parent = tmp->parent;
		}
		else{
			tmp->parent->right = tmp->right;
			tmp->right->parent = tmp->parent;
		}
		bstNode *current = tmp;
		while(current->right != NULL){
			current = current->right;
		}
		setHeight(current);
	}
	return tmp;
}

bstNode *bst::remove(string l, string f){
	bstNode *current = find(l, f);
	if(current->left == NULL && current->right == NULL){
		return removeNoKids(current);
	}
	else if(current->left != NULL && current->right == NULL){
		return removeOneKid(current, true);
	}
	else if(current->left == NULL && current->right != NULL){
		return removeOneKid(current, false);
	}
	else if(current->left != NULL && current->right != NULL){

		bstNode *temp = current->left;
		while(temp->right != NULL){
				temp = temp->right;
		}
		cout << "hello" << endl;
		cout << temp->student->first << endl;
		if(temp->left == NULL && temp->right == NULL){
			removeNoKids(temp);
		}
		else if(temp->left != NULL && temp->right == NULL){
			removeOneKid(temp, true);
		}
		bstNode *copy=current;
		current->student=temp->student;
		current->parent=copy->parent;
		current->right=copy->right;
		current->left=copy->left;

	}
	return NULL;
}

/*
 * ########################################################
 * ########################################################
 * -------------- AVL EXTRA CRED --------------------------
 * ########################################################
 * ########################################################
 */

//need to find balance of tree initially and throughout

int bst::getBalance(bstNode *temp){
	if(temp->left != NULL && temp->right != NULL){
		return((temp->left->height)-(temp->right->height));
	}else if(temp->left == NULL && temp->right != NULL){
		return(temp->right->height);
	}else if(temp->left != NULL && temp->right == NULL){
		return temp->left->height;
	}
	return 0;
}

//fix the height of balanced nodes
void bst::fixHeight(bstNode *node){
	if(node->left != NULL && node->right != NULL){
		if (node->left->height > node->right->height) {
				node->height = node->left->height + 1;
		}else {
				node->height = node->right->height + 1;
		}
	}else if (node->left==NULL && node->right!=NULL) {
		node->height = node->right->height + 1;
	}else if(node->left!=NULL && node->right==NULL){
		node->height = node->left->height+1;
	}else{
		node->height = 1;
	}
}

//rotate left
bstNode *bst::rotateLeft(bstNode *temp){
	//initial
	bstNode *temp2 = temp->right;
	bstNode *temp3 = temp->left;
	bstNode *tempPar = temp->parent;

	//set to null
	temp2->left = NULL;
	temp2->left = temp;
	temp->right = NULL;
	temp->right = temp3;

	//rootcase
	if(temp == root){
		root = temp2;
		temp2->parent = NULL;
		temp->parent = NULL;
		temp->parent = temp2;

		if(temp3 != NULL){
			temp3->parent = temp;
		}
	}else{
		temp2->parent = temp->parent;

		if(tempPar->right == temp){
			tempPar->right = temp2;
		}else{
			tempPar->left = temp2;
		}

		temp->parent = NULL;
		temp->parent = temp2;

		if(temp3 != NULL){
			temp3->parent = temp;
		}
	}


	fixHeight(temp);
	fixHeight(temp2);

	return temp2;
}

//rotate right
bstNode *bst::rotateRight(bstNode *temp){
	//initial
	bstNode *temp2 = temp->left;
	bstNode *temp3 = temp->right;
	bstNode *tempPar = temp->parent;

	//set to null
	temp2->right = NULL;
	temp2->right = temp;
	temp->left = NULL;
	temp->left = temp3;

	//rootcase
	if(temp == root){
		root = temp2;
		temp2->parent = NULL;
		temp->parent = NULL;
		temp->parent = temp2;

		if(temp3 != NULL){
			temp3->parent = temp;
		}
	}else{
		temp2->parent = temp->parent;

		if(tempPar->right == temp){
			tempPar->right = temp2;
		}else{
			tempPar->left = temp2;
		}

		temp->parent = NULL;
		temp->parent = temp2;

		if(temp3 != NULL){
			temp3->parent = temp;
		}
	}

	fixHeight(temp);
	fixHeight(temp2);

	return temp2;
}



