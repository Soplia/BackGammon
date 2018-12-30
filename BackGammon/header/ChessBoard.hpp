/*!
 @header ChessBoard.hpp
 
 @abstract Github: https://github.com/Soplia
 
 @author Created by Jiarui XIE on 2018/12/30
 
 @version 1.00 2018/12/30 Creation
 
 @note
 Header file for ChessBoard
 COMPLIER: Xcode - Version 9.0 beta 3
 Copyright © 2018 QM. All rights reserved.
 */


#pragma once
#include "Position.hpp"
#include "ConstantFile.h"
#include <iostream>
using namespace std;

class ChessBoard
{
public:
   ChessBoard();
   void Init(int x);
   void Display();
   void CleanChessBoard();
   bool IsFull();
   void Play(int x, int y, int who);
   int IsWin();
   bool IsSame(int beginX, int beginY, int tyep, int lengthToCompare);
   int EvaluateChessBoard();
   Position GetBestPosition();
public:
   int _chessBoard[SIZE][SIZE];
   Position _latestPosition;
   int _globalScore;
};

