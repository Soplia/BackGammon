/*!
 @header ChessBoard.hpp
 
 @abstract Github: https://github.com/Soplia/BackGammon
 
 @author Created by Jiarui XIE on 2018/12/30
 
 @version 1.00 2018/12/30 Creation
 
 @note
    Header file for ChessBoard.
    COMPLIER: Xcode - Version 9.0 beta 3.
    Copyright © 2018 QM. All rights reserved.
 */


#pragma once
#include "Position.hpp"
#include "ConstantFile.h"
#include "MTRandom.hpp"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*!
 *@class ChessBoard
 *@note User First.
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
    *@param    x    The value assigned to the _chessBoard.
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
    *@brief   Whether win or Not.
    *@param    p    The latsest played Position.
    *@return   true: yes, someone win / false: no, nobady Win.
    */
   bool IsWin(Position p);
   
   /*!
    *@brief   Whether win or Not.
    *
    *@param    x    x index of Position.
    *@param    y    y index of Position.
    *
    *@return   true: yes, someone win / false: no, nobady Win.
    */
   bool IsWin2(int x, int y);


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
    *@param    alpha   Alpha
    *@param    beta    Beta
    */
   void GetBestPosition(int deep, int alpha, int beta, Position p);

   /*!
    *@brief   Get the last node from _node.
    *
    *@return   The last Node.
    */
   Position GetLastNode();
   
   /*!
    *@brief   Find the index of the specific position in _toJudge.
    *
    *@param    p    The specific Position.
    *
    *@return   1 ~ SIZE-1: Finded / -1: does not Finded.
    */
   int ToJudgeFind(Position p);
   
   /*!
    *@brief   Whether _toJudge contain the specific Position.
    *
    *@param    p    The specific Position.
    *
    *@return   true: contain / false: do not Contain.
    */
   bool ToJudgeContain(Position p);
   
   /*!
    *@brief   Delete p in _toJudge.
    *
    *@param    p    The specific Position.
    *
    *@return   true: delete / false: do not Delete.
    */
   bool ToJudgeDelete(Position p);
   
   /*!
    *@brief   Is the best node null or Not.
    *@return   true: NULL / false: not NULL.
    */
   bool IsBestNodeNull();
   
   /*!
    *@brief   The whole process of AI to Play.
    */
   void AI();

   /*!
    *@brief   The whole process of User to Play.
    */
   void User();

   /*!
    *@brief   Get the user's wanted positions.
    */
   void GetUserPosition(int &x ,int &y);
   
public:
   /*!
    *@brief   Matrix contain the whole ChessBoard
    */
   int _chessBoard[SIZE][SIZE];

   /*!
    *@brief   Keep the latest play step, use it to judge whether win or Not.
    */
   Position _latestPosition;
   
   /*!
    *@brief   Keep the latest Node.
    */
   Position  _bestNode;
   
   /*!
    *@brief   Keep the global Mark, It seems useless.
    */
   int _globalScore;
   
   /*!
    *@brief   Represent the finish of this Game.
    */
   bool isFinished;
   
   /*!
    *@brief   Positions are going to Judge.
    */
   vector<Position> _toJudge;
   
   /*!
    *@brief   Nodes generated during DFS.
    */
   vector<Position> _node;
   
   MTRandom _random;
};


