//
// Created by Dimitri on 07/12/2023.
//

#include "highRand.h"

int highRand() {
    int intRand = 0;
    //use bit shift to get a 32 bit positive random number from rand() which give a 15 bit random number
    intRand = (((rand() << 15) | rand()) << 1) | rand() % 2;
    return intRand;
}