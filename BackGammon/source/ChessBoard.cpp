/*!
 @author Created by Jiarui XIE on 2018/12/30
 
 @note
 COMPLIER: Xcode - Version 9.0 beta 3
 Copyright © 2018 QM. All rights reserved.
 
 */
#include "ChessBoard.hpp"
//#define _DEBUG
//#define _DEBUG_MARK
#define _DEBUG_BEST

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
      std::cout << "|";
      for (int j = 1; j<SIZE; j++)
         std::cout << _chessBoard[i][j] << "|";
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
            cout << "⊕ "; //➊➋⊕⊙○●◆▼◎⊕▣∅●
         else if (_chessBoard[i][j] == DEFENDER)
            cout << "⊙ ";
         else if (_chessBoard[i][j] == EMPTY)
            cout << "∅ "; //❉✿❀❁✪❂
      cout << endl;
   }
}

/*!
 *@brief   Play the chess Position into the ChessBoard.
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
 *@brief   Evaluate the whole chessBoard then give a Mark.
 *
 *@return   The mark this evaluation Got.
 */
int ChessBoard::EvaluateChessBoard()
{
   int res = 0;
   for (int i = 1; i < SIZE; i++)
   {
      for (int j = 1; j< SIZE; j++)
      {
         if (_chessBoard[i][j] != EMPTY)
         {
            // 行
            bool flagL = false, flagR = false;
            int x = j, y = i;
            int cnt = 1;
            
            int col = x, row = y;
            //不能出界, 遇到与当前位置不同颜色的棋子便停止 ,向左搜索
            while (--col > 0 && _chessBoard[row][col] == _chessBoard[y][x])
               cnt++;
            if (col > 0 && _chessBoard[row][col] == EMPTY)
               flagL = true;
            
            col = x;
            row = y;
            
            while (++col < SIZE && _chessBoard[row][col] == _chessBoard[y][x])
               ++cnt;
            if (col < SIZE && _chessBoard[row][col] == EMPTY)
               flagR=true;
            
            if (flagL && flagR)
               res += _chessBoard[i][j] * cnt * cnt;
            else if (flagL || flagR)
               res += _chessBoard[i][j] * cnt * cnt / 4;
            if (cnt >= 5)
               res = MAXN * _chessBoard[i][j];
#ifdef _DEBUG_MARK
            cout << "HORIZON: " << res << endl;
#endif
            // 列
            col = x;
            row = y;
            cnt = 1;
            flagL = false;
            flagR = false;
            
            while (--row > 0 && _chessBoard[row][col] == _chessBoard[y][x])
               ++cnt;
            if (row > 0 && _chessBoard[row][col] == EMPTY)
               flagL=true;
            
            col = x;
            row = y;
            
            while (++row < SIZE && _chessBoard[row][col] == _chessBoard[y][x])
               ++cnt;
            if (row < SIZE && _chessBoard[row][col] == EMPTY)
               flagR = true;
            
            if (flagL && flagR)
               res += _chessBoard[i][j] * cnt * cnt;
            else if (flagL || flagR)
               res += _chessBoard[i][j] * cnt * cnt / 4;
            if (cnt >= 5)
               res = MAXN * _chessBoard[i][j];
#ifdef _DEBUG_MARK
            cout << "VERTICAL: " << res << endl;
#endif
            // 左对角线 '\'
            col = x;
            row = y;
            cnt = 1;
            flagL = false;
            flagR = false;
            
            while(--col > 0 && --row > 0 && _chessBoard[row][col] == _chessBoard[y][x])
               ++cnt;
            if(col > 0 && row > 0 && _chessBoard[row][col] == EMPTY)
               flagL = true;
            
            col = x;
            row = y;
            
            while (++col < SIZE && ++row < SIZE && _chessBoard[row][col] == _chessBoard[y][x])
               ++cnt;
            if (col < SIZE && row < SIZE && _chessBoard[row][col] == EMPTY)
               flagR=true;
            
            if (flagL && flagR)
               res += _chessBoard[i][j] * cnt * cnt;
            else if (flagL || flagR)
               res += _chessBoard[i][j] * cnt * cnt / 4;
            if (cnt >= 5)
               res = MAXN * _chessBoard[i][j];
#ifdef _DEBUG_MARK
            cout << "DIAGONAL2R: " << res << endl;
#endif
            // 右对角线 /
            col = x;
            row = y;
            cnt = 1;
            flagL = false;
            flagR = false;
            
            while (++row < SIZE && --col > 0 && _chessBoard[row][col] == _chessBoard[y][x])
               ++cnt;
            if(row < SIZE && col > 0 && _chessBoard[row][col] == 0)
               flagL = true;
            
            col = x;
            row = y;
            
            while (--row > 0 && ++col < SIZE && _chessBoard[row][col] == _chessBoard[y][x])
               ++cnt;
            if (row > 0 && col < SIZE && _chessBoard[row][col] == EMPTY)
               flagR = true;
#ifdef _DEBUG_MARK
            cout << "flagL: " << flagL << " flagR: " << flagR << endl;
#endif
            if (flagL && flagR)
               res += _chessBoard[i][j] * cnt * cnt;
            else if (flagL || flagR)
               res += _chessBoard[i][j] * cnt * cnt / 4;
            if (cnt >= 5)
               res = MAXN * _chessBoard[i][j];
#ifdef _DEBUG_MARK
            cout << "DIAGONAL2L:" << res << endl;
#endif
         }
      }
   }
   return res;
}

void ChessBoard::Debug()
{
   for (int i = 1; i < SIZE; ++i)
   {
      for (int j = 1; j < SIZE; ++j)
      {
         cout << _chessBoard[i][j] << " ";
      }
      cout << endl;
   }
}

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



Position ChessBoard::GetBestPosition(int deep, Position root, int alpha, int beta, Position p)
{
   if (deep == SEARCH_DEEP)
   {
      root._score = EvaluateChessBoard();
#ifdef _DEBUG_BEST
      cout << p._x << " " << p._y <<" " << root._score << endl;
#endif
      return;
   }
   
   //在已经落子的周围进行判断
   vector<Position> judgeSet;
   
   for (auto valP : toJudge)
      judgeSet.push_back(valP);
   
   for (auto it : judgeSet)
   {
      Position now = Position((Position)it);
      
      root.addChild(now);
      
      //确定是本来就有的，还是在DFS中，进行添加的（本来应该为空的位置）
      bool flag=toJudge .contains(now);
      
      _chessBoard[now.y][now.x]=((deep&1)==1)?-1:1;
      
      //下完之后，立马进行判断
      if(isEnd(now.x,now.y))
      {
         root.bestChild=node;
         root._score=MAXN*chessBoard[now.y][now.x];
         //恢复原样,并结束
         chessBoard[now.y][now.x]=0;
         return;
      }
      
      //没有结束
      bool flags[]=new bool[8]; //标记回溯时要不要删掉
      Arrays.fill(flags,true);
      
      for(int i=0;i<8;++i)
      {
         Position next=new Position(now.x+dc[i],now.y+dr[i]);
         if(1<=now.x+dc[i] && now.x+dc[i]<=size && 1<=now.y+dr[i] && now.y+dr[i]<=size && chessBoard[next.y][next.x]==0)
         {
            //再次进行扩展，合理，下次调用该函数便从给这里进行判断
            if(!toJudge.contains(next))
            {
               toJudge.add(next);
            }
            //如果本来就有则标记为假
            else
               flags[i]=false;
         }
      }
      //是得去了，要不然就没有结局了。如果不是在本轮中新加的，就把它去掉，要不然没玩。
      if(flag)
         toJudge.remove(now);
      
      dfs(deep+1,root.getLastChild(),alpha,beta,now);
      
      //从下一轮回到了现在，再给它加上
      chessBoard[now.y][now.x]=0;
      if(flag)
         toJudge.add(now);
      
      
      for(int i=0;i<8;++i)
         if(flags[i])
            toJudge.remove(new Position(now.x+dc[i],now.y+dr[i]));
      
      // alpha beta剪枝
      // min层
      if((deep&1)==1)
      {
         if(root.bestChild==null || root.getLastChild()._score<root.bestChild._score)
         {
            root.bestChild=root.getLastChild();
            root._score=root.bestChild._score;
            //这个是为什么
            if(root._score<=MINN)
               root._score+=deep;
            beta=Math.min(root._score,beta);
         }
         if(root._score<=alpha)
            return;
      }
      
      // max层
      else
      {
         if(root.bestChild==null || root.getLastChild()._score>root.bestChild._score)
         {
            root.bestChild=root.getLastChild();
            root._score=root.bestChild._score;
            //这个是为什么
            if(root._score==MAXN)
               root._score-=deep;
            alpha=Math.max(root._score,alpha);
         }
         if(root._score>=beta)
            return;
      }
   }
   // if(deep==0) System.out.printf("******************************************\n");
}
