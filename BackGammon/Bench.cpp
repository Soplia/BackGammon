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
#include <fstream>
#include "Position.hpp"
#include "ChessBoard.hpp"
#include "Point.hpp"

const int size = 2000;
const int sizeOfCol = 300;
int amount[size] = {0};
double usedTime[size] = {0.0};
Point randSteps[size][sizeOfCol];
ofstream out;

void InitRandSteps()
{
   MTRandom myRand;
   myRand.InitGenrand((unsigned long)time(NULL));
   for (int i = 0; i < size; i++)
      for (int j = 0; j < sizeOfCol; j++)
      {
         int x = myRand.GenrandInt15();
         int y = myRand.GenrandInt15();
         Point p(x,y);
         
         /*
         if (x < 1 || x >15)
            cout << i << "-" << j << "-" << x << endl;
         if (y < 1 || y >15)
            cout << i << "-" << j << "-" << y << endl;
         */
         
         randSteps[i][j] = p;
      }
}

int WinTime()
{
   int sum = 0;
   for (int i = 0; i < size; i++)
      if (amount[i] != 0)
         sum++;
   return sum;
}


/*!
 *@brief   PlayChess
 *
 *@param    time    Get the time needed to Calculate
 *@param    mode    1: ai/not rand; 2: ai/rand; 3: not ai/not rand; 4: not ai/rand
 *
 *@return   The total Setps
 */
int PlayChess(double &time, int mode, int row)
{
   int i = 1;
   double sumOfTime = 0.0;
   ChessBoard C;
   
   cout << "The Initial state of Chessboard:" << endl;
   C.Display2();
   
   //sizeOfCol / 5 控制着计算机下棋的次数
   //基本上在 sizeOfCol / 5 步之内就能够获得胜利
   for (; i <= sizeOfCol / 5 && !C.isFinished; i++)
   {
      int j = 0;
      bool flag = false;
      Point temp;
      
      switch (mode)
      {
         case AI_NOTRAND:
            {
               C.User();
               double temp = C.WithAI();
               sumOfTime += temp;
               cout << endl << i << "th step: " << endl;
               C.Display2();
               //cout << "Used Time :" << temp << endl;
            }break;
            
         case AI_RAND: 
         {
            do
            {
               temp = randSteps[row][j];
               flag = C.ChessExist(temp.GetX(), temp.GetY());
               j++;
            }while(flag && j < sizeOfCol);
            
            //cout << "(" << temp.GetX() << "," << temp.GetY() << ")" << endl;
            
            C.User(temp.GetX(), temp.GetY());
            double temp1 = C.WithAI();
            sumOfTime += temp1;
            //cout << endl << i << "th step: " << endl;
            //C.Display2();
            //cout << "Used Time :" << temp1 << endl;
         }break;
            
         case NOTAI_RAND: // not ai / rand
         {
            do
            {
               temp = randSteps[row][j];
               flag = C.ChessExist(temp.GetX(), temp.GetY());
               j++;
            }while(flag && j < sizeOfCol);
            
            //cout << "(" << temp.GetX() << "," << temp.GetY() << ")" << endl;
            
            C.User(temp.GetX(), temp.GetY());
            
            double temp1 = C.WithoutAI();
            sumOfTime += temp1;
            
            //cout << endl << i << "th step: " << endl;
            //C.Display2();
            //cout << "Used Time :" << temp1 << endl;
         }break;
            
         case NOTAI_NOTRAND: // not ai / not rand
         {
            C.User();
            double temp = C.WithoutAI();
            sumOfTime += temp;
            
            cout << endl << i << "th step: " << endl;
            C.Display2();
            //cout << "Used Time :" << temp << endl;
         }break;
         default: cout << "Please input the right Mode!" << endl; break;
      }
   }
   time = sumOfTime / i;
   return i;
}

//time控制着模拟的次数
void Simulation(int time, int mode)
{
   double stepSum = 0.0;
   double timePer = 0.0;
   double timeSum = 0.0;
   
   if (time >= size)
   {
      cout << "Please Input a number less than " << size << endl;
      return ;
   }
   
   InitRandSteps();
   
   out.open("/Users/qingmang/JrX_Code/Xcode/BackGammon/Data.txt", ios::out | ios::app);
   if (!out)
   {
      cout << "Create File Fail" << endl;
      exit(0);
   }
   switch (mode)
   {
      case AI_RAND:
         out << "AI_RAND_" << time << endl;
         break;
      case AI_NOTRAND:
         out << "AI_NOTRAND" << endl;
         break;
      case NOTAI_RAND:
         out << "NOTAI_RAND_" << time << endl;
         break;
      case NOTAI_NOTRAND:
         out << "NOTAI_NOTRAND" << endl;
         break;
      default:
         break;
   }
   
   //进行time次仿真
   for (int i = 0; i < time; i++)
   {
      amount[i] = PlayChess(timePer, mode, i);
      usedTime[i] = timePer;
      out << i + 1 << "," << amount[i] << "," << usedTime[i] << endl;
   }
   out.close();
   
   cout << endl << "win/total: " << WinTime() <<"/" << time << endl;
   
   //cout << "The step needed:" << endl;
   for (int i = 0; i < time; i++)
   {
      stepSum += amount[i];
      timeSum += usedTime[i];
      //cout << usedTime[i] << " ";
      //if ((i + 1) % 5 == 0)
         //cout << endl;
   }
   cout << "Average step:" << stepSum / WinTime();
   cout << endl << "Average time:" << timeSum / time << endl;
}

int main(void)
{
   //Simulation(10, NOTAI_RAND);
   //Simulation(100, NOTAI_RAND);
   //Simulation(1000, NOTAI_RAND);
   //Simulation(10, AI_RAND);
   Simulation(1, AI_NOTRAND);
   //Simulation(1000, AI_RAND);
   
   return 0;
}
