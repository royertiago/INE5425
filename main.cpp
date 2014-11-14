/* main.cpp */
#include <atomic>
#include <chrono>
#include <csignal>
#include <iomanip>
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

void print_time( long long unsigned time ) {
    auto ms = time / 1000;
    auto min = ms / 1000 / 60;
    ms %= 60*1000;
    auto sec = ms / 1000;
    ms %= 1000;
    std::cout << min << "min" << sec << "s" << ms << "ms";
}

void print_partial_statistics() {
    std::cout << "---------- Partial statistics ----------\n";
    std::cout << Requisition::alive << " requisitions and responses currently in the system\n";
    std::cout << "Queues - min/max/avg/current\n";
    std::cout << "Network - Client to Server - " << client_to_server.queue.entities
              << "/" << client_to_server.queue.current_queue() << std::endl;
    std::cout << "Network - Server to Client - " << server_to_client.queue.entities
              << "/" << server_to_client.queue.current_queue() << std::endl;
    std::cout << "Server process 1 - " << processes[0].queue.entities
              << "/" << processes[0].queue.current_queue() << std::endl;
    std::cout << "Server process 2 - " << processes[1].queue.entities
              << "/" << processes[1].queue.current_queue() << std::endl;

    std::cout << "Resource ocupation - respectively, "
              << std::setprecision( 2 )
              << 100 * client_to_server.queue.occupancy_rate() << "% / "
              << std::setprecision( 2 )
              << 100 * server_to_client.queue.occupancy_rate() << "% / "
              << std::setprecision( 2 )
              << 100 * processes[0].queue.occupancy_rate() << "% / "
              << std::setprecision( 2 )
              << 100 * processes[1].queue.occupancy_rate() << "%\n";

    std::cout << "Response times: min/avg/max ms - " << response_times << std::endl << std::endl;
}

void print_final_statistics() {
    std::cout << "---------- Full statistics report ----------\n";
    std::cout << Requisition::alive << " requisitions and responses currently in the system.\n";
    std::cout << Requisition::count << " total requisitions and responses.\n";
    std::cout << "Queue sizes - min/avg/max\n";
    std::cout << "Network - Client to Server - " << client_to_server.queue.entities << std::endl;
    std::cout << "Network - Server to Client - " << server_to_client.queue.entities << std::endl;
    std::cout << "Server process 1 - " << processes[0].queue.entities << std::endl;
    std::cout << "Server process 2 - " << processes[1].queue.entities << std::endl;

    std::cout << "Queue waiting times - min/avg/max ms\n";
    std::cout << "Network - Client to Server - " << client_to_server.queue.delays << std::endl;
    std::cout << "Network - Server to Client - " << server_to_client.queue.delays << std::endl;
    std::cout << "Server process 1 - " << processes[0].queue.delays << std::endl;
    std::cout << "Server process 2 - " << processes[1].queue.delays << std::endl;

    std::cout << "Resource ocupation - respectively, "
              << std::setprecision( 2 )
              << 100 * client_to_server.queue.occupancy_rate() << "% / "
              << std::setprecision( 2 )
              << 100 * server_to_client.queue.occupancy_rate() << "% / "
              << std::setprecision( 2 )
              << 100 * processes[0].queue.occupancy_rate() << "% / "
              << std::setprecision( 2 )
              << 100 * processes[1].queue.occupancy_rate() << "%\n";

    std::cout << "Response times: min/avg/max ms - " << response_times << std::endl;
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
    print_partial_statistics();
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << "Type any of the following:\n";
    std::cout << "f                         [print full statistics report]\n";
    std::cout << "i <miliseconds>           [change screen update interval]\n";
    std::cout << "l <number of seconds>     [change the execution time limit]\n";
    std::cout << "n                         [print next events]\n";
    std::cout << "q                         [quit the program]\n";
    std::cout << "r                         [resume the simulation]\n";
    std::cout << "s                         [toggle step-by-step run]\n";
    /* Windows can't do both signal handling and input reading. */
    bool resume = false;
    while( !resume ) {
        op = std::cin.get();
        switch( op ) {
            case 'q': 
                print_final_statistics();
                readkey();
                exit(0);
                
            case 'f':
                print_final_statistics();
                break;

            case 'r':
                resume = true;
                break;

            case 'n':
                for( auto str : Clock::next_events() )
                    std::cout << str << std::endl;
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
            print_time( Clock::current_time() );
            std::cout << " " << str << std::endl;
        }
        print_partial_statistics();

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

    print_final_statistics();

    std::cout << "\nPress [ENTER] to exit the system...";
    readkey();

    return 0;
}
