/* main.cpp */
#include <chrono>
#include <csignal>
#include <iostream>
#include <limits>
#include <stdio.h>
#include <thread>

#include "client.h"
#include "clock.h"
#include "network.h"
#include "random.h"
#include "server.h"
#include "user_config.h"

void readkey() {
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
}

namespace { // global variables modified by the signal handlers.
    bool step_by_step = false;
    unsigned long long time_limit = std::numeric_limits<unsigned long long>::max();
    unsigned sleep_time = 100;
}

void signal_handler( int ) {
    char op;
    std::cout << "Press [ENTER] to resume execution, or type any of the following:\n";
    std::cout << "l <number of seconds>     [change the execution time limit]\n";
    std::cout << "q                         [quit the program]\n";
    std::cin >> op;
    switch( op ) {
        case 'q': exit(0);
        case 'l': {
                      double secs;
                      if( !(std::cin >> secs) ) {
                          std::cout << "Error reading the execution time. Ignoring...\n";
                          std::cin.clear();
                      } else
                          time_limit = secs * 1000*1000;
                  }
              break;
    }
}

int main() {
    user::read_configuration( "user_config.txt" );
    Random::reset();
    Client::reset();
    printf( "Seed: %u\n", user::seed );

    Clock::insert( &server_to_client ); // Notice the order is important.
    Clock::insert( processes );
    Clock::insert( processes + 1 );
    Clock::insert( &client_to_server );
    Clock::insert( clients );
    Clock::insert( clients + 1 );
    Clock::insert( clients + 2 );
    Clock::insert( clients + 3 );

    signal( SIGINT, signal_handler );
    std::cout << "Press [ENTER] to begin the simulation.\n"
                 "Hit CTRL-C anytime to stop the simulation.\n"
                 "The list of future events is printed when you stop the simulation;\n"
                 "you can also choose to advance by step or change the simulation speed.\n";

    readkey();

    while( Clock::current_time() < time_limit ) {
        for( auto str : Clock::advance() ) {
            auto ms = Clock::current_time() / 1000;
            auto min = ms / 1000 / 60;
            ms %= 60*1000;
            auto sec = ms / 1000;
            ms %= 1000;
            std::cout << min << "m" << sec << "s" << ms << "ms " << str << std::endl;
        }
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
