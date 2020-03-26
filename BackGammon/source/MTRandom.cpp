/*!
 @author Created by Jiarui XIE on 2019/1/2
 
 @note
   COMPLIER: Xcode - Version 9.0 beta 3.
   Copyright © 2019 QM. All rights reserved.
 */

#include "../header/MTRandom.hpp"

/*!@brief  Initializes mt[N] with a seed.
 * @param[in] s the seed.
 */
void MTRandom::InitGenrand(unsigned long s)
{

   mt[0] = s & 0xffffffffUL;
   for (mti = 1; mti<N; mti++)
   {
      mt[mti] =
      (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
      /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
      /* In the previous versions, MSBs of the seed affect   */
      /* only MSBs of the array mt[].                        */
      /* 2002/01/09 modified by Makoto Matsumoto             */
      mt[mti] &= 0xffffffffUL;
      /* for >32 bit machines */
   }
}

/*!@brief  Generates a random number on [0,0xffffffff]-interval.
 * @return The generated unsigned long number.
 */
unsigned long MTRandom::GenrandInt32(void)
{
   unsigned long y;
   static unsigned long mag01[2] = { 0x0UL, MATRIX_A };
   /* mag01[x] = x * MATRIX_A  for x=0,1 */
   
   if (mti >= N)
   { /* generate N words at one time */
      int kk;
      
      if (mti == N + 1)   /* if init_genrand() has not been called, */
         InitGenrand(5489UL); /* a default initial seed is used */
      
      for (kk = 0; kk<N - M; kk++)
      {
         y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
         mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
      }
      for (; kk<N - 1; kk++)
      {
         y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
         mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
      }
      y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
      mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];
      
      mti = 0;
   }
   
   y = mt[mti++];
   
   /* Tempering */
   y ^= (y >> 11);
   y ^= (y << 7) & 0x9d2c5680UL;
   y ^= (y << 15) & 0xefc60000UL;
   y ^= (y >> 18);
   
   return y;
}

/*!@brief  generates an integer number on [1,15] interval, use Gaussian Distribution.
 * @return The generated integer number.
 */
int MTRandom::GenrandInt15(void)
{
   return (int)(GenrandInt32()*(1.0 / 4294967295.0) * 6) + 1;
   /* divided by 2^32-1 */
}
