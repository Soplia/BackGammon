/*!
 @header Node.hpp
 
 @abstract Github: https://github.com/Soplia
 
 @author Created by Jiarui XIE on 2019/2/7
 
 @version 1.00 2019/2/7 Creation
 
 COMPLIER: Xcode - Version 9.0 beta 3
 
 @brief
 
 Copyright © 2019 QM. All rights reserved.
 */


#ifndef Node_h
#define Node_h

#include "Position.hpp"
#include "ConstantFile.h"
#include <vector>
#include <iostream>
using namespace std;

class Node
{
public:
   Node();
   Node(const Node &other);
   Node & operator = (const Node &other);
   void SetPoint(Position p);
   void AddChild(Node *r);
   Node *GetLastChild();
   
public:
   Node *_bestChild;
   vector<Node*> *_child;
   Position _point;
   int _mark;
   
};
#endif /* Node_h */
