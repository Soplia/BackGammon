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
   /*!
    *@brief   A constructor.
    */
   Node();

   /*!
    *@brief   A copy constructor.
    *
    *@param    other    the parameter
    */
   Node(const Node &other);

   /*!
    *@brief   Operator =
    *
    *@param    other    the parameter used to assignment
    */
   Node & operator = (const Node &other);

   /*!
    *@brief   A setor
    *
    *@param    p    set p to the member of Node
    */
   void SetPoint(Position p);

   /*!
    *@brief   Add the node into the verctor _child.
    *
    *@param    r    the node which is going to be added into _child.
    */
   void AddChild(Node *r);

   /*!
    *@brief   Get the last child.
    *
    *@return   the last object in _child.
    */
   Node *GetLastChild();

public:
   /*!
    *@brief   The best children.
    */
   Node *_bestChild;

   /*!
    *@brief   The vector used to stroe the child.
    */
   vector<Node*> *_child;

   /*!
    *@brief   The position of current node.
    */
   Position _point;

   /*!
    *@brief   The mark of current node.
    */
   int _mark;

};
#endif /* Node_h */
