/*!
 @header Position.hpp
 
 @abstract Github: https://github.com/Soplia
 
 @author Created by Jiarui XIE on 2018/12/30
 
 @version 1.00 2018/12/30 Creation
 
 @note
 Header file for Position
 COMPLIER: Xcode - Version 9.0 beta 3
 Copyright © 2018 QM. All rights reserved.
 
 */


#pragma once
#include <iostream>
using namespace std;

class Position
{
public:
   Position();
   Position(int x, int y);
   void SetXY(int x, int y);
   void SetScore(int x);
   void SetPlayer(int x);
   void Display();
   //int EvaluatePosition();
public:
   int _x;
   int _y;
   int _score;
   int _player;
};


