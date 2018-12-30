/*!
 @author Created by Jiarui XIE on 2018/12/30
 
 @note
 COMPLIER: Xcode - Version 9.0 beta 3
 Copyright © 2018 QM. All rights reserved.
 
 */

#include "ConstantFile.h"
#include "ChessBoard.hpp"
#define _DEBUG

bool ChessBoard::IsFull()
{
   bool f = true;
   for (int i = 1; i<SIZE; i++)
   {
      for (int j = 1; j<SIZE; j++)
      {
         if (_chessBoard[i][j] == 0)
         {
            f = false;
         }
      }
   }
   return f;
}
void ChessBoard::Init(int x)
{
   for (int i = 1; i<SIZE; i++)
   {
      for (int j = 1; j<SIZE; j++)
         _chessBoard[i][j] = x;
   }
}

void ChessBoard::CleanChessBoard()
{
   Init(0);
}

void ChessBoard::Display()
{
   for (int i = 1; i<SIZE; i++)
   {
      std::cout << " | ";
      for (int j = 1; j<SIZE; j++)
         std::cout << _chessBoard[i][j] << " | ";
      std::cout << std::endl;
   }
   
}

ChessBoard::ChessBoard() {
   Init(0);
   
}

bool ChessBoard::IsSame(int x, int y, int type, int length)
{
   bool c = false;
   int i = 1;
   switch (type)
   {
      case 1: if (y + length - 1<SIZE)
      {
         while (i<length && _chessBoard[x][y] == _chessBoard[x][y + i])
         {
            i++;
         }
         if (i == length)
         {
            c = true;
         }
      }
         break;
         
         
         
      case 2: if (x + length - 1<SIZE)
      {
         while (i<length && _chessBoard[x][y] == _chessBoard[x + i][y])
         {
            i++;
         }
         if (i == length)
         {
            c = true;
         }
      }
         break;
         
         
      case 3: if (y + length - 1<SIZE && x + length - 1<SIZE)
      {
         while (i<length && _chessBoard[x][y] == _chessBoard[x + i][y + i])
         {
            i++;
         }
         if (i == length)
         {
            c = true;
         }
      }
         break;
         
      case 4: if (y - length + 1>0 && x + length - 1<SIZE)
      {
         while (i<length && _chessBoard[x][y] == _chessBoard[x + i][y - i])
         {
            i++;
         }
         if (i == length)
         {
            c = true;
         }
      }
         break;
         
   }
   return c;
}

void ChessBoard::Play(int x, int y, int who)
{
   _chessBoard[x][y] = who;
   _latestPosition.SetXY(x, y);
}

int ChessBoard::IsWin() // Judge In four directions
{
#ifdef  _DEBUG
   cout << "ChessBoard_IsWin:" << endl;
#endif
   int x = _latestPosition._x;
   int y = _latestPosition._y;
   
   for (int i = (x - 4 < 1 ? 1 : x - 4); i <= x; i++)
      if (IsSame(x, i, HORIZON, 5))
         return true;
   
   for (int i = (y - 4 < 1 ? 1 : y - 4); i <= y; i++)
      if (IsSame(i, y, VERTICAL, 5))
         return true;
   
   for (int i = (x - 4 < 1 ? 1 : x - 4); i < x; i++)
      if (IsSame(i, i, DIAGONAL2L, 5))
         return true;
   
   for (int i = (x + 4 > SIZE ? SIZE : x + 4); i > x; i--)
      if (IsSame(i, i, DIAGONAL2R, 5))
         return true;
   
   return false;
   
   
   
}
