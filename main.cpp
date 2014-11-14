/* main.cpp */
#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <limits>
#include <cstdio>
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
    volatile bool step_by_step = false;
    volatile unsigned long long time_limit = std::numeric_limits<unsigned long long>::max();
    volatile unsigned sleep_time = 100;
    volatile std::atomic_bool interrupt;
}

void print_time() {
    auto ms = Clock::current_time() / 1000;
    auto min = ms / 1000 / 60;
    ms %= 60*1000;
    auto sec = ms / 1000;
    ms %= 1000;
    std::cout << min << "min" << sec << "s" << ms << "ms";
}

void print_short_statistics() {
    // TODO
}

void signal_handler( int ) {
    ::interrupt = 1;

    /* Windows seems to reset the signal handler function at each interruption,
     * so we will set again. */
    signal( SIGINT, signal_handler );
}

void handle_interruption() {
    interrupt = 0;
    char op;
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << "Type any of the following:\n";
    std::cout << "l <number of seconds>     [change the execution time limit]\n";
    std::cout << "i <miliseconds>           [change screen update interval]\n";
    std::cout << "s                         [toggle step-by-step run]\n";
    std::cout << "q                         [quit the program]\n";
    std::cout << "r                         [resume the simulation]\n";
    /* Windows can't do both signal handling and input reading. */
    bool resume = false;
    while( !resume ) {
        op = std::cin.get();
        switch( op ) {
            case 'q': exit(0);

            case 'r': resume = true;
                      break;

            case 'l': {
                double secs;
                if( !(std::cin >> secs) ) {
                    std::cout << "Error reading the execution time. Ignoring...\n";
                    std::cin.clear();
                } else
                    time_limit = secs * 1000*1000;
            } break;

            case 's':
                step_by_step = !step_by_step;
                break;

            case 'i': {
                unsigned t;
                if( !(std::cin >> t) ) {
                    std::cout << "Error reading update interval. Ignoring...\n";
                    std::cin.clear();
                } else {
                    ::sleep_time = t;
                    if( step_by_step )
                        std::cout << "Run mode was step-by-step. Reventing to automatic...\n";
                    step_by_step = false;
                }
            } break;
        }
        readkey();
    }

    if( step_by_step )
        std::cout << "Running the simulation step-by-step. Press [ENTER] to go to next step,\n"
                  << "type 'a' [ENTER] to return to automatic execution,\n"
                  << "type 'o' [ENTER] to go back to the options menu.\n";
    
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
                 "Hit CTRL-C during the simulation to pause the simulation and access\n"
                 "the options menu.\n"
                 "The list of future events is also printed when you stop the simulation.\n\n"
                 "(You can also type 'o' and [ENTER] now to edit the option directly.)\n\n";

    char op = std::cin.get();
    if( op != '\n' ) {
        readkey();
        handle_interruption();
    }

    while( Clock::current_time() < time_limit ) {
        if( interrupt )
            handle_interruption();

        for( auto str : Clock::advance() ) {
            print_time();
            std::cout << " " << str << std::endl;
        }
        print_short_statistics();

        if( step_by_step ) {
            char op = std::cin.get();
            if( op != '\n' )
                readkey(); // clean the buffer
            if( op == 'a' )
                step_by_step = false;
            if( op == 'o' )
                handle_interruption();
        }
        else
            std::this_thread::sleep_for( std::chrono::milliseconds(sleep_time) );
    }

    std::cout << "End of simulation.\n";

    std::cout << "\nPress [ENTER] to exit the system...";
    readkey();

    return 0;
}
