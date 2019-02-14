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
   Node(Position p);
   void SetPosition(Position p);
   void AddChild(Position p);
   Position GetLastChild();
   bool IsBestNodeNull();
   
public:
   Position _self;
   Position _bestChild;
   vector<Position> _childList;
};
#endif /* Node_h */
