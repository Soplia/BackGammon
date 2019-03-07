/*!
 @author Created by Jiarui XIE on 2019/3/7
 
 COMPLIER: Xcode - Version 9.0 beta 3
 
 Copyright © 2019 QM. All rights reserved.
 */

#include "Point.hpp"

Point::Point()
{
   _x = 1;
   _y = 1;
}

Point::Point(int x, int y)
{
   SetXY(x,y);
}

void Point::SetXY(int x, int y)
{
   _x = x;
   _y = y;
}

int Point::GetX()
{
   return _x;
}

int Point::GetY()
{
   return _y;
}

void Point::Display()
{
   cout << "(" << _x << "," << _y << ")" << endl;
}
