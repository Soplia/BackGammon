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
 *@brief   Is the best node null or Not.
 *@return   true: NULL / false: not NULL.
 */
bool ChessBoard::IsBestNodeNull()
{
   return !_bestNode._x || !_bestNode._y;
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
 *@brief   Display the _chessBoard matrix with symbols.
 */
void ChessBoard::Display2()
{
   // 打印一下行标
   cout << "  ";
   for (int i = 1; i < SIZE; i++)
      cout << i << " ";
   cout << endl;
   
   //cout << "The contents of _chessBoard:" << endl;
   for (int i = 1; i < SIZE; i++)
   {
      //打印一下列标
      cout << i << " ";
      for (int j = 1; j < SIZE; j++)
         if (_chessBoard[i][j] == ATTACKER)
            cout << "+ "; //➊➋⊕⊙○●◆▼◎⊕▣∅●
         else if (_chessBoard[i][j] == DEFENDER)
            cout << "- ";
         else if (_chessBoard[i][j] == EMPTY)
            cout << ". "; //❉✿❀❁✪❂
      cout << endl;
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
//这一段是正确的
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
//这一段是正确的
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
//这一段是正确的
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
//这一段是正确的
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
//这一段是正确的
void ChessBoard::Play(int x, int y, int who)
{
   _chessBoard[x][y] = who;
   _latestPosition.SetXY(x, y);
   _latestPosition._player = who;
   
   if (IsWin2(x, y))
   {
      isFinished = true;
      if (_latestPosition._player == DEFENDER)
         cout << "DEFENDER WIN" << endl;
      else if(_latestPosition._player == ATTACKER)
         cout << "ATTACKER WIN" << endl;
      //Init(0);
   }
   else if (IsFull())
      cout << "The Chessboard is Full!" << endl;
   else
   {
      Position p(x, y);
      
      //如果已经下了就从待判断队列中移除
      if (ToJudgeContain(p))
         ToJudgeDelete(p);
      
      //不管是谁下的都把它周围八个方向未下的位置作为代下点
      for (int i = 0; i < 8; ++i)
      {
         Position now(x + DC[i], y + DR[i]);
         //if(1 <= now._x && now._x < SIZE && 1 <= now._y && now._y < SIZE && \
         _chessBoard[now._y][now._x] == EMPTY)
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

//这一段是正确的
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
void ChessBoard::GetBestPosition(int deep, int alpha, int beta, Node root)
{
   if (deep == SEARCH_DEEP)
   {
      //_bestNode._mark = EvaluateChessBoard();
      root._self._mark = EvaluateChessBoard();
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
      
      //**//_node.push_back(now);
      root.AddChild(now);
      
      //确定是本来就有的，还是在DFS中进行添加的（本来应该为空的位置）
      bool flag = ToJudgeContain(now);
      
      //向当前位置下棋
      _chessBoard[now._x][now._y] = (( deep & 1 ) == 1 ) ? DEFENDER : ATTACKER;
      
      //下完之后，立马进行判断
      if (IsWin2(now._x, now._y))
      {
         _bestNode = now;
         
         //**//_bestNode.SetXY(now._x, now._y);
         root._bestChild = now;
         //cout << "Win: " << _bestNode._x << " " << _bestNode._y << endl;
         
         root._bestChild._mark = MAXN * _chessBoard[now._x][now._y];
         //**//_bestNode._mark = MAXN * _chessBoard[now._x][now._y];
         
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
      
      GetBestPosition(deep + 1, alpha, beta, Node(root.GetLastChild()));
      
      //上面对now位置进行了模拟下棋,现在恢复到原始状态
      _chessBoard[now._x][now._y] = EMPTY;
      if (flag)
         _toJudge.push_back(now);
      //把now的八个方向也恢复到原始状态
      for (int i = 0; i < 8; i++)
         if (flags[i])
            ToJudgeDelete(Position(now._x + DC[i], now._y + DR[i]));
      
      // alpha beta剪枝
      // min层
      //cout << deep << "|root._childList| = " << root._childList.size() << endl;
      
      if ((deep & 1) == 1)
      {
         //**//Position temp = GetLastNode();
         if ( root.IsBestNodeNull() || root.GetLastChild()._mark < root._bestChild._mark)
         {
            root._bestChild = root.GetLastChild();
            _bestNode = root.GetLastChild();
            
            //做微调, 为后续min做铺垫
            if(root._bestChild._mark <= MINN)
               root._bestChild._mark += deep;
            
            beta = min(root._bestChild._mark, beta);
         }
         //cout << deep << " min = " << root._bestChild._x << " , " << root._bestChild._y << endl;
         
         if(root._bestChild._mark <= alpha)
            return;
      }
      // max层
      else
      {
         //**//Position temp = GetLastNode();
         if(root.IsBestNodeNull() || root.GetLastChild()._mark > root._bestChild._mark)
         {
            root._bestChild = root.GetLastChild();
            _bestNode = root.GetLastChild();
            
            if(_bestNode._mark >= MAXN)
               _bestNode._mark -= deep;
            
            alpha = max(root._bestChild._mark, alpha);
         }
         
         //cout << deep << " max = " << root._bestChild._x << " , " << root._bestChild._y << endl;
         
         if(root._bestChild._mark >= beta)
            return;
      }
   }
   
#ifdef _DEBUG_BEST
   if(deep == 0)
      cout << "******************************************\n";
#endif
}

/*!
 *@brief   The whole process of AI to Play.
 */
void ChessBoard::AI()
{
   Node root;
   GetBestPosition(0, MINN, MAXN, root);
   
   //cout << _bestNode._x << " " << _bestNode._y << endl;
   Play(_bestNode._x, _bestNode._y, ATTACKER);
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
      //x = _random.GenrandInt15();
      //y = _random.GenrandInt15();
      GetUserPosition(x,y);
   }while (_chessBoard[x][y] != EMPTY);
   
   //cout << "User: " << x << " " << y << endl;
   Play(x, y, DEFENDER);
}
