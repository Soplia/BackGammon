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

const int size = 200;
int amount[size] = {0};


int WinTime()
{
   int sum = 0;
   for (int i = 0; i < size; i++)
      if (amount[i] != 0)
         sum++;
   return sum;
}

int PlayChess()
{
   int i = 1;
   ChessBoard C;
   //20控制着计算机下棋的次数
   //基本上在20步之内就能够获得胜利
   cout << "The Initial state of Chessboard:" << endl;
   C.Display2();
   
   for (; i <= 20 && !C.isFinished; i++)
   {
      cout << endl << i << "th step: " << endl;
      C.User();
      
       /*if (i == 4)
       {
          cout << endl;
          C.Display2();
          cout << endl;
       }
       */
      C.WithoutAI();
      //cout << "The mark of ChessBoard: " << C.EvaluateChessBoard() << endl;
      C.Display2();
     // cout << endl;
   }
   return i;
}

//time控制着模拟的次数
void Simulation(int time)
{
   double sum = 0.0;
   if (time >= size)
   {
      cout << "Please Input a number less than " << size << endl;
      return ;
   }
   
   for (int i = 0; i < time; i++)
      amount[i] = PlayChess();
   
   cout << "win/total: " << WinTime() <<"/" << time << endl;
   cout << "The step needed:" << endl;
   
   for (int i = 0; i < time; i++)
   {
      sum += amount[i];
      cout << amount[i] << " ";
      if ((i + 1) % 5 == 0)
         cout << endl;
   }
   
   cout << endl << "The average step is:" << sum / WinTime() << endl;
}

int main(void)
{
   Simulation(1);
   return 0;
}


