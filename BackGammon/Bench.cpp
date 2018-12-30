/*!
 @header Bench.cpp
 
 @abstract Github: https://github.com/Soplia/BackGammon
 
 @author Created by Jiarui XIE on 2018/12/30
 
 @version 1.00 2018/12/30 Creation
 
 @note
 File for Validation
 COMPLIER: Xcode - Version 9.0 beta 3
 Copyright © 2018 QM. All rights reserved.
 */

#include <cstdlib>
#include "Position.hpp"
#include "ChessBoard.hpp"

int main(void)
{
   Position myPos;
   myPos.Display();
   
   myPos.SetXY(1, 2);
   myPos.Display();
   
   myPos.SetPlayer(2);
   myPos.Display();
   
   myPos.SetScore(4);
   myPos.Display();
   
   ChessBoard C;
   //C.Display();
   
   
   cout << endl << endl;
   
   for (int i = 5; i <=7; i++)
      C.Play(5, i, ATTACKER);
   C.Display2();
   if (C.IsWin())
      cout << "win" << endl;
   else
      cout << "false" << endl;
   
   
   return 0;
}


