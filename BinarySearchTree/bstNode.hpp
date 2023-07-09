/*
 * bstNode.hpp
 *
 *  Created on: Oct 13, 2022
 *      Author: karlthimm
 */

#ifndef BSTNODE_HPP_
#define BSTNODE_HPP_
#include "Student.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

class bstNode{

	friend class bst;
	friend class TreeInterface;
	bstNode *parent;
	bstNode *right;
	bstNode *left;
	int height;
	Student *student;

public:
	bstNode();
	bstNode(string f, string l, int n, string j);
	~bstNode();
	void printNode();
};

#endif /* BSTNODE_HPP_ */
