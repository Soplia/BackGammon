/*!
 @header MTRandom.hpp
 
 @abstract Github: https://github.com/Soplia
 
 @author Created by Jiarui XIE on 2019/1/2
 
 @version 1.00 2019/1/2 Creation
 
 @brief Header of Random Generator.
    COMPLIER: Xcode - Version 9.0 beta 3.
    Copyright © 2019 QM. All rights reserved.
 */

#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ConstantFile.h"
using namespace std;

class MTRandom
{
public:
   /*!@brief  Initializes mt[N] with a seed.
    * @param[in] s the seed.
    */
   void InitGenrand(unsigned long s);
   
   /*!@brief  Generates a random number on [0,0xffffffff]-interval.
    * @return The generated unsigned long number.
    */
   unsigned long GenrandInt32(void);
   
   /*!@brief  generates an integer number on [0,100] interval..
    * @return The generated integer number.
    */
   int GenrandInt15(void);
};

