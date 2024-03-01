#include <stdio.h>

// Game of Life, the cells live within a universe in 3D, 
// Rules: 4555 or 5766

int main() {
    int sz = 4; // set size of tensor in 3D
    int el, eu, fl, fu, time_steps; // initialize rule variables and number of time steps
    el = 4;     // environment lower
    eu = 5;     // environment upper
    fl = 5;     // fertility lower
    fu = 5;     // fertility upper
    time_steps = 10;


    // create primordial soup
    
    for (int i = 0; i < time_steps; i++){
        // execute main part of code for each timestep.
        // check which ones should die or live
        // merge)
    }



    return 0;
}


