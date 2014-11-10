/* rancom.cpp
 * Definition of user::seed.
 * Implementation of random.h
 */
#include <chrono>
#include <random>
#include "random.h"
#include "user_config.h"

namespace user {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count(); 
}

namespace {
    std::mt19937 rng;
}

namespace Random {
    void reset() {
        rng.seed( user::seed );
    }

    unsigned add_response_size() {
        static std::uniform_int_distribution<unsigned> d( 256, 512 );
        return d( rng );
    }

    unsigned delete_response_size() {
        static std::uniform_int_distribution<unsigned> d( 512, 1024 );
        return d( rng );
    }

    unsigned find_response_size() {
        const static int i[] = {256, 512, 1024}; // intervals
        const static int w[] = {0, 1, 0}; // wights
        static std::piecewise_linear_distribution<double> d( i, i + 3, w );
        return d( rng ) + 0.5; // rounding
    }

    unsigned search_response_size() {
        const static int w[] = {20, 30, 30, 20};
        static std::discrete_distribution<unsigned> d( w, w+4 );
        switch( d(rng) ) {
            case 0: return 64;
            case 1: return 512;
            case 2: return 1024;
            default: return 2048;
        }
    }
}
