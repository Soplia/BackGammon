/*!
 @author Created by Jiarui XIE on 2018/12/30
 
 @note
    COMPLIER: Xcode - Version 9.0 beta 3.
    Copyright © 2018 QM. All rights reserved.
 */
#include "ChessBoard.hpp"
//#define _DEBUG
//#define _DEBUG_MARK
//#define _DEBUG_BEST
//#define _DEBUG_WIN


/*!
 *@brief A constructor, init the _chessBoard matriz to Zero.
 */
ChessBoard::ChessBoard()
{
   Init(0);
}

/*!
 *@brief A constructor, init the _chessBoard matriz to Zero.
 */
void ChessBoard::CleanChessBoard()
{
   Init(0);
}

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
         if (_chessBoard[i][j] == EMPTY)
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
 *@param    x    The value assigned to the _chessBoard.
 */
void ChessBoard::Init(int x)
{
   for (int i = 1; i<SIZE; i++)
   {
      for (int j = 1; j<SIZE; j++)
         _chessBoard[i][j] = x;
   }
   
   _toJudge.clear();
   _node.clear();
   
   //都在(0,0)即为NULL
   _bestNode.SetXY(0, 0);
   
   isFinished = false;
   
   //随机的开关
   _random.InitGenrand((unsigned long)time(NULL));
}

/*!
 *@brief   Is the best node null or Not.
 *@return   true: NULL / false: not NULL.
 */
bool ChessBoard::IsBestNodeNull()
{
   return !_bestNode._x || !_bestNode._y;
}

/*!
 *@brief   Display the _chessBoard matrix with symbols.
 */
void ChessBoard::Display2()
{
   // 打印一下行标
   cout << "  ";
   for (int i = 1; i < SIZE; i++)
      //printf(" %02d", i);
      printf(" %x", i);
   cout << endl;
   
   //cout << "The contents of _chessBoard:" << endl;
   for (int i = 1; i < SIZE; i++)
   {
      //打印一下列标
      //printf("%02d ", i);
      printf(" %x", i);
      for (int j = 1; j < SIZE; j++)
         if (_chessBoard[i][j] == ATTACKER)
            cout << " +"; //➊➋⊕⊙○●◆▼◎⊕▣∅●
         else if (_chessBoard[i][j] == DEFENDER)
            cout << " -";
         else if (_chessBoard[i][j] == EMPTY)
            cout << " ."; //❉✿❀❁✪❂
      cout << endl;
   }
}

/*!
 *@brief   Display the _toJudge was used for debug.
 */
void ChessBoard::DisplayToJudge()
{
   for (auto it : _toJudge)
   {
      ((Position)it).Display();
   }
}

/*!
 *@brief   Get the last node from _node.
 *
 *@return   The last Node.
 */
Position ChessBoard::GetLastNode()
{
   //这个地方写的有问题
   return _node.back();
}

/*!
 *@brief   Find the index of the specific position in _toJudge.
 *
 *@param    p    The specific Position.
 *
 *@return   1 ~ SIZE-1: Finded / -1: does not Finded.
 */
int ChessBoard::ToJudgeFind(Position p)
{
   bool flag = false;
   int i = 0;
   long count = _toJudge.size();
   for (; i < count; i++)
      if (_toJudge[i] == p)
      {
         flag = true;
         break;
      }
   if (flag)
      return i;
   else
      return -1;
}

/*!
 *@brief   Whether _toJudge contain the specific Position.
 *
 *@param    p    The specific Position.
 *
 *@return   true: contain / false: do not Contain.
 */
bool ChessBoard::ToJudgeContain(Position p)
{
   int index = ToJudgeFind(p);
   if (index == -1)
      return false;
   else
      return true;
}

/*!
 *@brief   Delete p in _toJudge.
 *
 *@param    p    The specific Position.
 *
 *@return   true: delete / false: do not Delete.
 */
bool ChessBoard::ToJudgeDelete(Position p)
{
   if (_toJudge.empty())
      return false;
   else
   {
      int index = ToJudgeFind(p);
      if (index == -1)
         return false;
      else
      {
         _toJudge.erase(_toJudge.begin() + index);
         return true;
      }
   }
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
   cout << "IsSame: " << beginX << " " << beginY << " " << type << endl;
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
 *@brief   Whether win or Not.
 *
 *@param    x    x index of Position.
 *@param    y    y index of Position.
 *
 *@return   true: yes, someone win / false: no, nobady Win.
 */
bool ChessBoard::IsWin2(int x,int y)
{
   
#ifdef _DEBUG_MARK
   cout << x <<" " << y << endl;
#endif
   
   //先保存这吧,可能会用到
   
   // 判断一行是否五子连珠
   int cnt = 1;
   int col = y, row = x;
   while (--col > 0 && _chessBoard[row][col] == _chessBoard[x][y])
      ++cnt;
   col = y;
   row = x;
   while (++col < SIZE && _chessBoard[row][col] == _chessBoard[x][y])
      ++cnt;
   
#ifdef _DEBUG_MARK
   cout << "H: " << cnt << endl;
#endif
   
   if (cnt >= 5)
   {
      //cout << "Win2: " << endl;
      //isFinished = true;
      return true;
   }
   
   
   // 判断一列是否五子连珠
   col = y;
   row = x;
   cnt = 1;
   while (--row > 0 && _chessBoard[row][col] == _chessBoard[x][y])
      ++cnt;
   col = y;
   row = x;
   while (++row < SIZE && _chessBoard[row][col] == _chessBoard[x][y])
      ++cnt;
   
#ifdef _DEBUG_MARK
   cout << "V: " << cnt << endl;
#endif
   
   if (cnt >= 5)
   {
      //cout << "Win2: " << endl;
      //isFinished = true;
      return true;
   }
   
   
   // 判断左对角线是否五子连珠
   col = y;
   row = x;
   cnt = 1;
   while (--col > 0 && --row > 0 && _chessBoard[row][col] == _chessBoard[x][y])
      ++cnt;
   col = y;
   row = x;
   while (++col < SIZE && ++row < SIZE && _chessBoard[row][col] == _chessBoard[x][y])
      ++cnt;
   
#ifdef _DEBUG_MARK
   cout << "DR: " << cnt << endl;
#endif
   
   if (cnt >= 5)
   {
      //cout << "Win2: " << endl;
      //isFinished = true;
      return true;
   }
   
   
   // 判断右对角线是否五子连珠
   col = y;
   row = x;
   cnt = 1;
   while (++row < SIZE && --col>0 && _chessBoard[row][col]==_chessBoard[x][y])
      ++cnt;
   col = y;
   row = x;
   while (--row>0 && ++col < SIZE && _chessBoard[row][col]==_chessBoard[x][y])
      ++cnt;
   
#ifdef _DEBUG_MARK
   cout << "DL: " << cnt << endl;
#endif
   
   if (cnt >= 5)
   {
      //cout << "Win2: " << endl;
      //isFinished = true;
      return true;
   }
   
   return false;
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
   _latestPosition._player = who;
   
   if (IsWin2(x, y))
   {
      isFinished = true;
      if (_latestPosition._player == DEFENDER)
         cout << "YOU WIN!!!! ^_^" << endl;
      else if(_latestPosition._player == ATTACKER)
         cout << "YOU LOSE!!! v_v" << endl;
      //Init(0);
   }
   else if (IsFull())
      cout << "The Chessboard is Full!" << endl;
   else
   {
      Position p(x, y);
      
      //cout << "The contents of _toJudge: " << endl;
      //DisplayToJudge();
      //如果已经下了就从待判断队列中移除
      while (ToJudgeContain(p))
      {
         ToJudgeDelete(p);
         //cout << "Delect position: (" << x << " , " << y << ")" << endl << endl;
      }
      
      //cout << "The contents of _toJudge after Delete: " << endl;
      //DisplayToJudge();
      
      //不管是谁下的都把它周围八个方向未下的位置作为代下点
      for (int i = 0; i < 8; ++i)
      {
         Position now(x + DC[i], y + DR[i]);
         if (1 <= now._x && now._x < SIZE && 1 <= now._y && now._y < SIZE && \
             _chessBoard[now._x][now._y] == EMPTY)
            _toJudge.push_back(now);
      }
   }
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

/*!
 *@brief   Get the best Position.
 *
 *@param    deep    The Current search Deep.
 *@param    alpha   Alpha
 *@param    beta    Beta
 */
void ChessBoard::GetBestPosition(int deep, int alpha, int beta, Node &root)
{
   if (deep == SEARCH_DEEP)
   {
      root._mark = EvaluateChessBoard();
#ifdef _DEBUG_BEST
      cout << root._self._x << " " << root._self._y <<" " << root._self_mark << endl;
#endif
      return;
   }
   
   //对上一层的落子进行判断,因为 _toJudge会进行更新
   vector<Position> judgeSet;
   for (auto valP : _toJudge)
      judgeSet.push_back(valP);
   
   for (auto it : judgeSet)
   {
      Position now = Position((Position)it);
      Node *node = new Node();
      node -> SetPoint(now);
      root.AddChild(node);
      
      //确定是本来就有的，还是在DFS中进行添加的（本来应该为空的位置）
      bool flag = ToJudgeContain(now);
      
      //向当前位置下棋
      _chessBoard[now._x][now._y] = (( deep & 1 ) == 1 ) ? DEFENDER : ATTACKER;
      
      //下完之后，立马进行判断
      if (IsWin2(now._x, now._y))
      {
         root._bestChild = node;
         root._mark = MAXN * _chessBoard[now._x][now._y];
         //恢复原样,并结束
         _chessBoard[now._x][now._y] = EMPTY;
         return;
      }
      
      //对now的八个方向进行判断
      bool flags[8];
      memset(flags, true, sizeof(bool) * 8);
      
      for (int i = 0; i < 8; i++)
      {
         Position next(now._x + DC[i], now._y + DR[i]);
         
         if(1 <= next._x && next._x < SIZE && 1 <= next._y \
            && next._y < SIZE && _chessBoard[next._x][next._y] == EMPTY)
         {
            //在下一层进行判断
            if(!ToJudgeContain(next))
            {
               _toJudge.push_back(next);
            }
            //如果本来就有被包含在_toJudge中则标记为假
            else
               flags[i]=false;
         }
      }
      //对now已经进行了判断,现在就把now从_toJudge中删除
      if(flag)
         ToJudgeDelete(now);
      
      //希望没有错
      GetBestPosition(deep + 1, alpha, beta, *(root.GetLastChild()));
      
      //上面对now位置进行了模拟下棋,现在恢复到原始状态
      _chessBoard[now._x][now._y] = EMPTY;
      //cout << "Now: (" << now._x << ":" << now._y << ") Depth: " << deep << endl;
      
      if (flag)
         _toJudge.push_back(now);
      //把now的八个方向也恢复到原始状态
      for (int i = 0; i < 8; i++)
         if (flags[i])
            ToJudgeDelete(Position(now._x + DC[i], now._y + DR[i]));
      
      // alpha beta剪枝
      // min层
      // cout << deep << "|root._childList| = " << root._childList.size() << endl;
      
      if ((deep & 1) == 1)
      {
         if ( root._bestChild == nullptr || root.GetLastChild() -> _mark < root._bestChild -> _mark)
         {
            root._bestChild = root.GetLastChild();
            root._mark = root._bestChild -> _mark;
            //做微调, 为后续min做铺垫
            if(root._mark <= MINN)
               root._mark += deep;
            beta = min(root._mark, beta);
            /*
            if (root._bestChild == nullptr)
               cout << "A :root._bestChild == nullptr" << endl;
            else
            {
               cout << root._bestChild -> _point._x << " A " << root._bestChild -> _point._y << endl;
               
            }
             */
         }
         //cout << deep << " min = " << root._bestChild._x << " , " << root._bestChild._y << endl;
         
         if(root._mark <= alpha)
            return;
      }
      // max层
      else
      {

         if(root._bestChild == nullptr || root.GetLastChild() -> _mark > root._bestChild -> _mark)
         {
            root._bestChild = root.GetLastChild();
            root._mark = root._bestChild -> _mark;
            if(root._mark >= MAXN)
               root._mark -= deep;
            alpha = max(root._mark, alpha);
            /*
            if (root._bestChild == nullptr)
               cout << "B :root._bestChild == nullptr" << endl;
            else
            {
               cout << root._bestChild -> _point._x << " B " << root._bestChild -> _point._y << endl;
               
            }
             */
         }
         //cout << deep << " max = " << root._bestChild._x << " , " << root._bestChild._y << endl;
         
         if(root._mark >= beta)
            return;
      }
   }
   
#ifdef _DEBUG_BEST
   if(deep == 0)
      cout << "******************************************\n";
#endif
}

/*!
 *@brief   Whether has been played or Not
 *
 *@param    i    The index of X
 *@param    j    The index of Y
 *
 *@return   true: has been played; false: has not been Played.
 */
bool ChessBoard::ChessExist(int i, int j)
{
   if (_chessBoard[i][j] == ATTACKER || _chessBoard[i][j] == DEFENDER)
      return true;
   return false;
}

/*!
 *@brief   Calculate the value of position with the same Type.
 *
 *@param    x    The start position of X
 *@param    y    The start position of Y
 *@param    attacker_defender    The type which is going to be Judged
 *
 *@return   The number of the psotion with the same Type.
 */
int ChessBoard::CheckMax(int x, int y, int attacker_defender)
{
   int num = 0, max_num, max_temp = 0;
   int x_temp = x, y_temp = y;
   int x_temp1 = x_temp, y_temp1 = y_temp; // judge right
   for (int i = 1; i < 5; i++)
   {
      x_temp1 += 1;
      if (x_temp1 >= SIZE)
         break;
      
      if (_chessBoard[x_temp1][y_temp1] == attacker_defender)
         num++;
      else
         break;
   }
   // judge left
   x_temp1 = x_temp;
   for (int i = 1; i < 5; i++)
   {
      x_temp1 -= 1;
      if (x_temp1 < 0)
         break;
      if (_chessBoard[x_temp1][y_temp1] == attacker_defender)
         num++;
      else
         break;
   }
   if (num < 5)
      max_temp = num;
   // judge up
   x_temp1 = x_temp;
   y_temp1 = y_temp;
   num = 0;
   for (
        
        int i = 1; i < 5; i++)
   {
      y_temp1 -= 1;
      if (y_temp1 < 0)
         break;
      if (_chessBoard[x_temp1][y_temp1] == attacker_defender)
         num++;
      else
         break;
   }
   // judge down
   y_temp1 = y_temp;
   for (int i = 1; i < 5; i++)
   {
      y_temp1 += 1;
      if (y_temp1 >= SIZE)
         break;
      if (_chessBoard[x_temp1][y_temp1] == attacker_defender)
         num++;
      else
         break;
   }
   if (num > max_temp && num < 5)
      
      max_temp = num;
   // judge left_up
   x_temp1 = x_temp;
   y_temp1 = y_temp;
   num = 0;
   for (int i = 1; i < 5; i++)
   {
      x_temp1 -= 1;
      y_temp1 -= 1;
      if (y_temp1 < 0 || x_temp1 < 0)
         break;
      if (_chessBoard[x_temp1][y_temp1] == attacker_defender)
         num++;
      else
         break;
   }
   // judge right_down
   x_temp1 = x_temp;
   y_temp1 = y_temp;
   for (int i = 1; i < 5; i++)
   {
      x_temp1 += 1;
      y_temp1 += 1;
      if (y_temp1 >= SIZE || x_temp1 >= SIZE)
         break;
      if (_chessBoard[x_temp1][y_temp1] == attacker_defender)
         num++;
      else
         break;
   }
   if (num > max_temp && num < 5)
      max_temp = num;
   // judge right_up
   x_temp1 = x_temp;
   y_temp1 = y_temp;
   num = 0;
   for (int i = 1; i < 5; i++)
   {
      x_temp1 += 1;
      y_temp1 -= 1;
      if (y_temp1 < 0 || x_temp1 >= SIZE)
         break;
      if (_chessBoard[x_temp1][y_temp1] == attacker_defender)
         num++;
      else
         
         break;
   }
   // judge left_down
   x_temp1 = x_temp;
   y_temp1 = y_temp;
   for (int i = 1; i < 5; i++)
   {
      x_temp1 -= 1;
      y_temp1 += 1;
      if (y_temp1 >= SIZE || x_temp1 < 0)
         break;
      if (_chessBoard[x_temp1][y_temp1] == attacker_defender)
         num++;
      else
         break;
   }
   if (num > max_temp && num < 5)
      max_temp = num;
   max_num = max_temp;
   return max_num;
}

/*!
 *@brief   Use the exhaustive method to determine the maximum number of pieces in each of the four directions of the coordinate point
 *
 *@param    row    The best position of X
 *@param    col    The best position of Y
 */
void ChessBoard::ComputerDo(int &row, int &col)
{
   int max_a, max_d, max_temp, max = 0;
   
   for (int i = 0; i < SIZE; i++)
   {
      for (int j = 0; j < SIZE; j++)
      {
         if (!ChessExist(i, j))
         {// 算法判断是否下子
            max_a = CheckMax(i, j, ATTACKER);// 判断白子的最大值
            max_d = CheckMax(i, j, DEFENDER);//判断黑子的最大值
            //攻守兼备
            max_temp= max_a > max_d ? max_a : max_d;
            
            if (max_temp > max)
            {
               max = max_temp;
               row = i;
               col = j;
            }
         }
      }
   }
}

/*!
 *@brief   The whole process of WithAI to Play.
 *
 *@return   The time used to make a Decision.
 */
double ChessBoard::WithAI()
{
   Node root;
   auto startTime = std::chrono::high_resolution_clock::now();
   
   GetBestPosition(0, MINN, MAXN, root);
   
   Play(root._bestChild -> _point._x, root._bestChild -> _point._y, ATTACKER);
   
   auto endTime = std::chrono::high_resolution_clock::now();
   return  std::chrono::duration<float, std::milli>(endTime - startTime).count();
}

/*!
 *@brief   The whole process of WithoutAI to Play.
 *
 *@return   The time used to make a Decision.
 */
double ChessBoard::WithoutAI()
{
   int x, y;
   auto startTime = std::chrono::high_resolution_clock::now();
   ComputerDo(x, y);
   Play(x, y, ATTACKER);
   auto endTime = std::chrono::high_resolution_clock::now();
   return  std::chrono::duration<float, std::milli>(endTime - startTime).count();
}

/*!
 *@brief   Get the user's wanted positions.
 */
void ChessBoard::GetUserPosition(int &x ,int &y)
{
   do
   {
      cout << "Please input a Location(1<=x,y<=" << SIZE - 1 << "),like 4 5 :" << endl;
      //这个cin有问题,经常性的出现问题
      //cin >> x >> y;
      scanf("%d %d", &x, &y);
   }while (x < 1 || y < 1 || x >= SIZE || y >= SIZE);
}

/*!
 *@brief   The whole process of User to Play.
 */
void ChessBoard::User()
{
   int x, y;
   do
   {
      x = _random.GenrandInt15();
      y = _random.GenrandInt15();
      //GetUserPosition(x,y);
      
   }while (_chessBoard[x][y] != EMPTY);
   
   //cout << "User: " << x << " " << y << endl;
   Play(x, y, DEFENDER);
}
