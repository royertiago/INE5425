/* user_config.cpp
 * Implementation of user_config.h. */
#include "user_config.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>

namespace user {
    double lambda[4] = {30, 60, 120, 120};
    double response_time[4] = {10, 8, 15, 30};

    const static std::map< std::string, double * > var_map = {
        {"lambda1",   lambda           },
        {"lambda2",   lambda + 1       },
        {"lambda3",   lambda + 2       },
        {"lambda4",   lambda + 3       },
        {"response1", response_time    },
        {"response2", response_time + 1},
        {"response3", response_time + 2},
        {"response4", response_time + 3},
    };

    void read_configuration( const char * filename ) {
        std::ifstream file( filename );

        if( !file ) {
            std::cerr << "Error opening " << filename << std::endl;
            return;
        }

        std::string var; double value;
        while( file >> var ) {
            if( var == "seed" ) {
                if(!(file >> user::seed) ) {
                    std::cerr << "Wrong number format for seed\n";
                    file.clear();
                }
                continue;
            }
            if( !(file >> value) ) {
                std::cerr << "Wrong number format for " << var << std::endl;
                file.clear();
                continue;
            }
            try {
                *user::var_map.at( var ) = value;
            } 
            catch( std::out_of_range& ) {
                std::cerr << "Unknown variable " << var << std::endl;
            }
        }
    }
}
