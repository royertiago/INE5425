/* main.cpp */
#include <stdio.h>
#include "user_config.h"

int main() {
    user::read_configuration( "user_config.txt" );
    for( int i = 0; i < 4; i++ )
        printf( "lambda[%i] = %7.2lf, response_time[%i] = %7.2lf\n",
                i, user::lambda[i], i, user::response_time[i] );
    return 0;
}
