/* main.cpp */
#include <stdio.h>
#include <iostream>

#ifdef RWINDOWS
#   include <limits>
#endif

#include "user_config.h"
#include "random.h"

int main() {
    user::read_configuration( "user_config.txt" );
    Random::reset();
    printf( "Seed: %u\n", user::seed );

    printf( "Random numbers - add: %5u, delete %5u, find %5u, search %5u\n",
            Random::add_response_size(),
            Random::delete_response_size(),
            Random::find_response_size(),
            Random::search_response_size() );

#ifdef RWINDOWS
    std::cout << "\nPress [ENTER] to exit the system...";
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
#endif // RWINDOWS

    return 0;
}
