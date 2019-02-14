//
//  main.cpp
//  Test1
//
//  Created by Jerome on 2019/2/14.
//  Copyright © 2019 QM. All rights reserved.
//

#include <iostream>
using namespace std;

typedef struct student
{
   int number;
   student *bro;
}stu;

int main(void)
{
   cout << "Hello World" << endl;
   bool flags[8];
   for (int i = 0; i < 8; i++)
      if (flags[i])
         cout << "true" << endl;
      else
         cout << "false" << endl;
   memset(flags, true, sizeof(bool) * 8);
   cout << "***********" << endl;
   for (int i = 0; i < 8; i++)
      if (flags[i])
         cout << "true" << endl;
      else
         cout << "false" << endl;
   return 0;
}
