/*!
 @header ConstantFile.h
 
 @abstract Github: https://github.com/Soplia/BackGammon
 
 @author Created by Jiarui XIE on 2018/12/30
 
 @version 1.00 2018/12/30 Creation
 
 @note
    File for Constant.
    COMPLIER: Xcode - Version 9.0 beta 3.
    Copyright © 2018 QM. All rights reserved.
 */

#pragma once

/*!
 *@brief   Represent the row direction Offset.
 */
const int DR[] = {-1,1,-1,1,0,0,-1,1};

/*!
 *@brief   Represent the col direction Offset.
 */
const int DC[] = {1,-1,-1,1,-1,1,0,0};

/*!
 *@brief   Represent the search Deep.
 */
const int SEARCH_DEEP = 4;

/*!
 *@brief   Represent the max value in this Project.
 */
const int MAXN = 1 << 28;

/*!
 *@brief   Represent the min value in this Project.
 */
const int MINN = -MAXN;

/*!
 *@brief   The size of the Chessboard.
 */
const int SIZE = 16;

/*!
 *@brief   Represent the Offset (5-1).
 */
const int OFFSET = 4;

/*!
 *@brief   Represent the empty Position. "□"
 */
const int EMPTY = 0;

/*!
 *@brief   Represent the Computer. "+"
 */
const int ATTACKER = 1;

/*!
 *@brief   Represent the User. "-"
 */
const int DEFENDER = -1;

/*!
 *@brief   Represent the horizon Direction.
 */
const int HORIZON = 1;

/*!
 *@brief   Represent the veritical Direction.
 */
const int VERTICAL = 2;

/*!
 *@brief   Represent the diagonal from left to right (up to down \).
 */
const int DIAGONAL2R = 3;

/*!
 *@brief   Represent the diagonal from right to left (up to down /).
 */
const int DIAGONAL2L = 4;

const int AI_NOTRAND = 1;
const int AI_RAND = 2;
const int NOTAI_NOTRAND = 3;
const int NOTAI_RAND = 4;

/*************************************************************************************/
#define N 624
#define M 397
/** @brief  Constant vector A. */
#define MATRIX_A 0x9908b0dfUL
/** @brief  Most significant w-r bits. */
#define UPPER_MASK 0x80000000UL
/** @brief  Least significant r bits. */
#define LOWER_MASK 0x7fffffffUL
/** @brief  The array for the state vector. */
static unsigned long mt[N];
/** @brief  mti==N+1 means mt[N] is not initialized. */
static int mti = N + 1;
/*************************************************************************************/
