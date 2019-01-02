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
   ChessBoard C;
   
   for (int i = 1; i <=1; i++)
   {
      cout << i << "th step: " << endl;
      C.User();
      C.Display2();
      cout << endl;
      C.AI();
      cout << "The mark of ChessBoard: " << C.EvaluateChessBoard() << endl;
      C.Display2();
   }
   
   return 0;
}


