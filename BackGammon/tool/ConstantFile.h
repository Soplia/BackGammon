/*!
 @header ConstantFile.h
 
 @abstract Github: https://github.com/Soplia/BackGammon
 
 @author Created by Jiarui XIE on 2018/12/30
 
 @version 1.00 2018/12/30 Creation
 
 @note
 File for Constant
 COMPLIER: Xcode - Version 9.0 beta 3
 Copyright © 2018 QM. All rights reserved.
 */

#pragma once

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
 *@brief   Represent the Computer. "⊕"
 */
const int ATTACKER = 1;

/*!
 *@brief   Represent the User. "⊙"
 */
const int DEFENDER = 2;

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
