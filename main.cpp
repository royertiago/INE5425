/* main.cpp */
#include <stdio.h>
#include <iostream>
#include <limits>

#include "user_config.h"
#include "random.h"

void readkey() {
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
}

namespace { // global variables modified by the signal handlers.
    bool step_by_step = false;
    unsigned long long time_limit = std::numeric_limits<unsigned long long>::max();
    unsigned sleep_time = 100;
}

int main() {
    user::read_configuration( "user_config.txt" );
    Random::reset();
    printf( "Seed: %u\n", user::seed );

    // TODO: set the signal handlers

    std::cout << "Press [ENTER] to begin the simulation.\n"
                 "Hit CTRL-C anytime to stop the simulation.\n"
                 "The list of future events is printed when you stop the simulation;\n"
                 "you can also choose to advance by step or change the simulation speed.\n";

    readkey();
    
    while( clock::current_time() < time_limit ) {
        std::cout << clock::advance();
        // TODO: print statistics summary here, after event generation.

        if( step_by_step )
            readkey();
        else
            std::this_thread::sleep_for( std::chrono::milliseconds(sleep_time) );
    }

    std::cout << "End of simulation.\n";

#ifdef RWINDOWS
    std::cout << "\nPress [ENTER] to exit the system...";
    readkey();
#endif // RWINDOWS

    return 0;
}
