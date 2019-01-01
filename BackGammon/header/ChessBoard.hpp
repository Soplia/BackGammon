/*!
 @header ChessBoard.hpp
 
 @abstract Github: https://github.com/Soplia/BackGammon
 
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
#include <vector>
using namespace std;

/*!
 *@class ChessBoard
 */
class ChessBoard
{
public:
   /*!
    *@brief A constructor, init the _chessBoard matriz to Zero.
    */
   ChessBoard();

   /*!
    *@brief   Init the _chessBoard matrix to x.
    *
    *@param    x    The value to be Assigned.
    */
   void Init(int x);

   /*!
    *@brief   Display the _chessBoard Matrix.
    */
   void Display();

   /*!
    *@brief   Display the _chessBoard matrix with symbols.
    */
   void Display2();
   
   /*!
    *@brief   Set the _chessBoard matrix to Zero.
    */
   void CleanChessBoard();

   /*!
    *@brief   Whether the _chessBoard matrix is full or Not.
    *
    *@return   true: full false: not Full
    */
   bool IsFull();

   /*!
    *@brief   Play the chess point into the ChessBoard.
    *
    *@param    x    The x index of the _chessBoard Matrix.
    *@param    y    The y index of the _chessBoard Matrix.
    *@param    who  ATTACKER / DEFENDER
    */
   void Play(int x, int y, int who);

   /*!
    *@brief   Whether win or Not
    *
    *@return   true: yes, someone win / false: no, nobady Win.
    */
   int IsWin();

   /*!
    *@brief   Whether the "lengthToCompare" positions are played by the same User?
    *
    *@param    beginX    The begin x Index.
    *@param    beginY    The begin y Index.
    *@param    type    Represent the Direction.
    *@param    lengthToCompare    The continue Length.
    *
    *@return   true: yes, those are same / no, those are not Same.
    */
   bool IsSame(int beginX, int beginY, int type, int lengthToCompare);
   
   /*!
    *@brief   Evaluate the whole chessBoard then give a Mark.
    *
    *@return   The mark this evaluation Got.
    */
   int EvaluateChessBoard();
   
   /*!
    *@brief   Get the best Position.
    *
    *@param    deep    The Current search Deep.
    *@param    root    Root of the GameTree.
    *@param    alpha   Alpha
    *@param    beta    Beta
    *
    *@return   The best Position.
    */
   Position GetBestPosition(int deep, Position root, int alpha, int beta, Position p);

   void Debug();
public:
   /*!
    *@brief   Matrix contain the whole ChessBoard
    */
   int _chessBoard[SIZE][SIZE];

   /*!
    *@brief   Keep the latest Step
    */
   Position _latestPosition;
   
   /*!
    *@brief   Keep the global Mark
    */
   int _globalScore;
   
   /*!
    *@brief   Positions are going to Judge.
    */
   vector<Position> toJudge;
};


