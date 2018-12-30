/*!
 @author Created by Jiarui XIE on 2018/12/30
 
 @note
 COMPLIER: Xcode - Version 9.0 beta 3
 Copyright © 2018 QM. All rights reserved.
 
 */

#include "Position.hpp"
#define _DEBUG

Position::Position()
{
   _x = 0;
   _y = 0;
   _score = 0;
   _player = 0;
}

Position::Position(int x, int y)
{
   SetXY(x, y);
}

void Position::Display()
{
#ifdef  _DEBUG
   cout << "Position_Display:" << endl;
#endif
   cout << "_x = " << _x << "; _y = " << _y << \
   "; _socre " << _score << "; _player = " << _player << endl;
}
void Position::SetPlayer(int x)
{
#ifdef  _DEBUG
   cout << "Position_SetPlayer:" << endl;
#endif
   _player = x;
}

void Position::SetXY(int x, int y)
{
#ifdef  _DEBUG
   cout << "Position_SetXY:" << endl;
#endif
   _x = x;
   _y = y;
}
void Position::SetScore(int x)
{
#ifdef  _DEBUG
   cout << "Position_SetScore:" << endl;
#endif
   _score = x;
}
