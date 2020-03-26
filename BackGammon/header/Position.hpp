/*!
 @header Position.hpp
 
 @abstract Github: https://github.com/Soplia/BackGammon
 
 @author Created by Jiarui XIE on 2018/12/30
 
 @version 1.00 2018/12/30 Creation
 
 @note
    Header file for Position.
    COMPLIER: Xcode - Version 9.0 beta 3.
    Copyright © 2018 QM. All rights reserved.
 
 */

#pragma once
#include <iostream>
using namespace std;

/*!
 *@class Position
 */
class Position
{
public:
   /*!
    *@brief   A Constructor.
    */
   Position();
   
   /*!
    *@brief   A Constructor.
    *
    *@param    x    The x Index.
    *@param    y    The y Index.
    */
   Position(int x, int y);
   
   /*!
    *@brief   Set _x and _y.
    *
    *@param    x    The target x.
    *@param    y    The target y.
    */
   void SetXY(int x, int y);
   
   /*!
    *@brief   Set _score
    *
    *@param    x    The target Score.
    */
   void SetScore(int x);
   
   /*!
    *@brief   Set _player
    *
    *@param    x    The target player Type.
    */
   void SetPlayer(int x);
   
   /*!
    *@brief   Display the contents of Positin.
    */
   void Display();
   
   bool operator == (const Position & obj) const
   {
      return _x == obj._x && _y == obj._y;
   }

public:
   /*!
    *@brief   The x Index.
    */
   int _x;

   /*!
    *@brief   The y Index.
    */
   int _y;

   /*!
    *@brief   The mark of this Position.
    */
   int _mark;

   /*!
    *@brief   Represent who played on this Position.
    */
   int _player;
};
