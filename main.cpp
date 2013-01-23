/* 
 * File:   main.cpp
 * Author: pj
 *
 * Created on January 7, 2013, 1:53 AM
 */

#include <cstdlib>
#include "Tests.h"
#include "Output.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    //static_assert(1ULL << 2 == 0ULL);
    cout << ((U32)(-5)) % 64 << endl;
    //cout << Output::bitboard(1ULL << 33) << endl;
    MoveGenerator::generate_move_lookup_tables();
    Tests::run();

    return 0;
}

