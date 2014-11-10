/* rancom.cpp
 * Definition of user::seed.
 */
#include <chrono>
#include "user_config.h"

namespace user {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count(); 
}
