//
//  main.cpp
//  Test
//
//  Created by QM on 2019/1/2.
//  Copyright © 2019 QM. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
   vector<int> a;
   for (int i = 0; i < 5; i++)
      a.push_back(i+10);
   //cout << a.back() << endl;
   

   
   long count = a.size();
   for (int i = 0; i < count;i++)
   {
      cout << i << endl;
      cout << a[i] << endl;
   }
   
   vector<int>::iterator it = find(a.begin(), a.end(), 1);
   cout << *it << endl;
   

   return 0;
}
