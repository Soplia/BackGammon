/*!
 @author Created by Jiarui XIE on 2018/12/30
 
 @note
 COMPLIER: Xcode - Version 9.0 beta 3
 Copyright © 2018 QM. All rights reserved.
 
 */

#include "ConstantFile.h"
#include "ChessBoard.hpp"
#define _DEBUG

/*!
 *@brief   Whether the _chessBoard matrix is full or Not.
 *
 *@return   true: full false: not Full
 */
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

/*!
 *@brief   Init the _chessBoard matrix to x.
 *
 *@param    x    The value to be Assigned.
 */
void ChessBoard::Init(int x)
{
   for (int i = 1; i<SIZE; i++)
   {
      for (int j = 1; j<SIZE; j++)
         _chessBoard[i][j] = x;
   }
}

/*!
 *@brief A constructor, init the _chessBoard matriz to Zero.
 */
void ChessBoard::CleanChessBoard()
{
   Init(0);
}

/*!
 *@brief   Display the _chessBoard Matrix.
 */
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

/*!
 *@brief   Display the _chessBoard matrix with symbols.
 */
void ChessBoard::Display2()
{
   cout << "The contents of _state:" << endl;
   for (int i = 1; i < SIZE; i++)
   {
      for (int j = 1; j < SIZE; j++)
         if (_chessBoard[i][j] == ATTACKER)
            cout << "⊕ ";
         else if (_chessBoard[i][j] == DEFENDER)
            cout << "⊙ ";
         else if (_chessBoard[i][j] == EMPTY)
            cout << "□ ";
      cout << endl;
   }
}

/*!
 *@brief   Play the chess point into the ChessBoard.
 *
 *@param    x    The x index of the _chessBoard Matrix.
 *@param    y    The y index of the _chessBoard Matrix.
 *@param    who  ATTACKER / DEFENDER
 */
void ChessBoard::Play(int x, int y, int who)
{
   _chessBoard[x][y] = who;
   _latestPosition.SetXY(x, y);
}


ChessBoard::ChessBoard()
{
   Init(0);
}

/*!
 *@brief   Whether the continue five position is played by the same User?
 *
 *@param    beginX    The begin x Index.
 *@param    beginY    The begin y Index.
 *@param    type    Represent the Direction.
 *@param    lengthToCompare    The continue Length.
 *
 *@return   true: yes, those are same / no, those are not Same.
 */
bool ChessBoard::IsSame(int beginX, int beginY , int type, int lengthToCompare)
{
   bool c = false;
   int i = 1;
   switch (type)
   {
      case HORIZON: if (beginY + lengthToCompare - 1<SIZE)
      {
         while (i<lengthToCompare && _chessBoard[beginX][beginY] == \
                _chessBoard[beginX][beginY + i])
         {
            i++;
         }
         if (i == lengthToCompare)
         {
            c = true;
         }
      }break;
         
      case VERTICAL: if (beginX + lengthToCompare - 1<SIZE)
      {
         while (i < lengthToCompare && _chessBoard[beginX][beginY] == \
                _chessBoard[beginX + i][beginY])
         {
            i++;
         }
         if (i == lengthToCompare)
         {
            c = true;
         }
      }break;
         
      case DIAGONAL2R: if (beginY + lengthToCompare - 1<SIZE && beginX + lengthToCompare - 1<SIZE)
      {
         while (i<lengthToCompare && _chessBoard[beginX][beginY] == \
                _chessBoard[beginX + i][beginY + i])
         {
            i++;
         }
         if (i == lengthToCompare)
         {
            c = true;
         }
      }break;
         
      case DIAGONAL2L: if (beginY - lengthToCompare + 1>0 && beginX + lengthToCompare - 1<SIZE)
      {
         while (i<lengthToCompare && _chessBoard[beginX][beginY] == \
                _chessBoard[beginX + i][beginY - i])
         {
            i++;
         }
         if (i == lengthToCompare)
         {
            c = true;
         }
      }break;
         
   }
   return c;
}

/*!
 *@brief   Whether win or Not
 *
 *@return   true: yes, someone win / false: no, nobady Win.
 */
int ChessBoard::IsWin() // Judge In four directions
{
#ifdef  _DEBUG
   cout << "ChessBoard_IsWin:" << endl;
#endif
   int x = _latestPosition._x;
   int y = _latestPosition._y;
   
   for (int i = (y - OFFSET < 1 ? 1 : y - OFFSET); i <= y; i++)
      if (IsSame(x, i, HORIZON, 5))
         return true;
   
   for (int i = (x - OFFSET < 1 ? 1 : x - OFFSET); i <= x; i++)
      if (IsSame(i, y, VERTICAL, 5))
         return true;
   
   for (int i = (x - OFFSET < 1 ? 1 : x - OFFSET),\
        j = (y - OFFSET < 1 ? 1 : y - OFFSET);\
        i <= x && j <= y; i++ , j++)
      if (IsSame(i, j, DIAGONAL2R, 5))
         return true;
   
   for (int i = (x - OFFSET < 1 ? 1 : x - OFFSET),\
        j = (y + OFFSET < SIZE ? y - OFFSET : SIZE);\
        i >= x && j >= y; i++ , j--)
      if (IsSame(i, i, DIAGONAL2L, 5))
         return true;
   
   return false;
}

/*!
 *@brief   Evaluate the ChessBoard then give a Mark.
 *
 *@return   The mark this evaluation Got.
 */
int EvaluateChessBoard()
{
   return 1;
}

/*!
 *@brief   Get the best Position.
 *
 *@return   The best Position.
 */
Position GetBestPosition()
{
   Position temp;
   return temp;
}

