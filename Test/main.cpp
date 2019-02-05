#include <iostream>
using namespace std;

unsigned int x = 123456789,
y = 362436000,
z = 521288629,
c = 7654321; /* Seed variables */

unsigned int KISS()
{
   unsigned long long t, A = 698769069ULL;
   
   x = 69069 * x + 12345;
   
   y ^= (y << 13);
   y ^= (y >> 17);
   y ^= (y << 5);
   
   t = (A * z + c);
   c = (t >> 32);
   z = t;
   
   return x + y + z;
}

int main(void)
{
   for (int i = 0; i < 10; i++)
      cout << KISS() << endl;
   return 0;
}
