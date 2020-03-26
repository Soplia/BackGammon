/*!
 @author Created by Jiarui XIE on 2019/3/7
 
 COMPLIER: Xcode - Version 9.0 beta 3
 
 Copyright © 2019 QM. All rights reserved.
 */

#include "Point.hpp"

/*!
 *@brief   A constructor.
 */
Point::Point()
{
   _x = 1;
   _y = 1;
}

/*!
 *@brief   A constructor with parameters.
 *
 *@param    x    x index
 *@param    y    y index
 */
Point::Point(int x, int y)
{
   SetXY(x,y);
}

/*!
 *@brief   A setor.
 *
 *@param    x    x index
 *@param    y    y index
 */
void Point::SetXY(int x, int y)
{
   _x = x;
   _y = y;
}

/*!
 *@brief   A getor for x.
 *
 *@return   x index
 */
int Point::GetX()
{
   return _x;
}

/*!
 *@brief   A getor for y.
 *
 *@return   y index
 */
int Point::GetY()
{
   return _y;
}

/*!
 *@brief   Display x and y.
 */
void Point::Display()
{
   cout << "(" << _x << "," << _y << ")" << endl;
}
