/*!
 @author Created by Jiarui XIE on 2019/2/7
 
 COMPLIER: Xcode - Version 9.0 beta 3
 
 Copyright © 2019 QM. All rights reserved.
 */

#include "Node.hpp"

Node::Node()
{
   
   _bestChild.SetXY(0, 0);
   _childList.clear();
}

Node::Node(Position p)
{
   SetPosition(p);
   _bestChild.SetXY(0, 0);
   _childList.clear();
}

void Node::SetPosition(Position p)
{
   _self.SetXY(p._x, p._y);
}

void Node::AddChild(Position p)
{
   _childList.push_back(p);
}

Position Node::GetLastChild()
{
   //这个地方有问题那就进行尝试而已
   return  _childList.at(_childList.size() - 1);
}

bool Node::IsBestNodeNull()
{
   return !_bestChild._x || !_bestChild._y;
}
