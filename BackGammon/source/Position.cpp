/*!
 @author Created by Jiarui XIE on 2018/12/30
 
 @note
 COMPLIER: Xcode - Version 9.0 beta 3
 Copyright © 2018 QM. All rights reserved.
 
 */

#include "Position.hpp"
#define _DEBUG

/*!
 *@brief   A Constructor.
 */
Position::Position()
{
   _x = 0;
   _y = 0;
   _score = 0;
   _player = 0;
}

/*!
 *@brief   A Constructor.
 *
 *@param    x    The x Index.
 *@param    y    The y Index.
 */
Position::Position(int x, int y)
{
   SetXY(x, y);
}

/*!
 *@brief   Display the contents of Positin.
 */
void Position::Display()
{
#ifdef  _DEBUG
   cout << "Position_Display:" << endl;
#endif
   cout << "_x = " << _x << "; _y = " << _y << \
   "; _socre " << _score << "; _player = " << _player << endl;
}

/*!
 *@brief   Set _player
 *
 *@param    x    The target player Type.
 */
void Position::SetPlayer(int x)
{
#ifdef  _DEBUG
   cout << "Position_SetPlayer:" << endl;
#endif
   _player = x;
}

/*!
 *@brief   Set _x and _y.
 *
 *@param    x    The target x.
 *@param    y    The target y.
 */
void Position::SetXY(int x, int y)
{
#ifdef  _DEBUG
   cout << "Position_SetXY:" << endl;
#endif
   _x = x;
   _y = y;
}

/*!
 *@brief   Set _score
 *
 *@param    x    The target Score.
 */
void Position::SetScore(int x)
{
#ifdef  _DEBUG
   cout << "Position_SetScore:" << endl;
#endif
   _score = x;
}
