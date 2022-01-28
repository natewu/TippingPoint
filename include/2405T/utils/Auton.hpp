#pragma once
#include "main.h"
#include "2405T/utils/Misc.hpp"

class Slew {
    public:
        /* 
            Constructor.
            
            @param max The maximum speed of the slew.
            @param rate The rate of acceleration.
        */
        Slew(int max, int rate = 1, direction dir = fwd);

        /* 
            Update the slew.
            
            @param input The input to the slew.
        */
        int update(int input);

    private:
        int max;
        int rate;
        int dir;
        int last_input;
        int last_output;
};