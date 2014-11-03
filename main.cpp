/* main.cpp */
#include <stdio.h>
#include <iostream>

#ifdef RWINDOWS
#   include <limits>
#endif

#include "user_config.h"

int main() {
    user::read_configuration( "user_config.txt" );
    for( int i = 0; i < 4; i++ )
        printf( "lambda[%i] = %7.2lf, response_time[%i] = %7.2lf\n",
                i, user::lambda[i], i, user::response_time[i] );

#ifdef RWINDOWS
    std::cout << "\nPress [ENTER] to exit the system...";
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
#endif // RWINDOWS

    return 0;
}
