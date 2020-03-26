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
   
   /*!
    *@brief   A constructor.
    */
   Point();
   
   /*!
    *@brief   A constructor with parameters.
    *
    *@param    x    x index
    *@param    y    y index
    */
   Point(int x, int y);
   
   /*!
    *@brief   A setor.
    *
    *@param    x    x index
    *@param    y    y index
    */
   void SetXY(int x, int y);
   
   /*!
    *@brief   A getor for x.
    *
    *@return   x index
    */
   int GetX();

   /*!
    *@brief   A getor for y.
    *
    *@return   y index
    */
   int GetY();

   /*!
    *@brief   Display x and y.
    */
   void Display();

private:
   
   /*!
    *@brief   x index.
    */
   int _x;
   
   /*!
    *@brief   y index
    */
   int _y;
};
#endif /* Point_h */
