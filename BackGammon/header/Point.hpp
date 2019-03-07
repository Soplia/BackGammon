/*!
 @header Point.hpp
 
 @abstract Github: https://github.com/Soplia
 
 @author Created by Jiarui XIE on 2019/3/7
 
 @version 1.00 2019/3/7 Creation
 
 COMPLIER: Xcode - Version 9.0 beta 3
 
 @brief
 
 Copyright © 2019 QM. All rights reserved.
 */


#ifndef Point_h
#define Point_h

#include <iostream>
using namespace std;

class Point
{
public:
   Point();
   Point(int x, int y);
   void SetXY(int x, int y);
   int GetX();
   int GetY();
   void Display();
private:
   int _x;
   int _y;
};
#endif /* Point_h */
