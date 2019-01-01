/*!
 @header Node.hpp
 
 @abstract Github: https://github.com/Soplia
 
 @author Created by Jiarui XIE on 2019/1/1
 
 @version 1.00 2019/1/1 Creation
 
 COMPLIER: Xcode - Version 9.0 beta 3
 
 @brief
 
 Copyright © 2019 QM. All rights reserved.
 */


#ifndef Node_h
#define Node_h

#include <iostream>
using namespace std;
#include "Position.hpp"

class Node
{
   
   public int mark;
   Node()
   {
      this.child.clear();
      bestChild=null;
      mark=0;
   }
   public void setPoint(Point r)
   {
      p.x=r.x;
      p.y=r.y;
   }
   
}

#endif /* Node_h */
