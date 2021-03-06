/* clock.h
 * Namespace that does the time management.
 *
 * Since there is a single global clock, there is no need for classes,
 * so it is a namespace.
 */
#ifndef CLOCK_H
#define CLOCK_H

#include "event_generator.h"
#include <string>
#include <vector>

namespace Clock {
    long long unsigned current_time();

    /* Inserts an event generator in the list of objects that
     * need time management. */
    void insert( EventGenerator * );

    /* Generate the next event. */
    std::vector< std::string > advance();

    /* Generate an ordered list with the next events. */
    std::vector< std::string > next_events();
};

#endif // CLOCK_H
