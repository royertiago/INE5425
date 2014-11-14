/* clock.cpp
 * Implementation of clock.h.
 */
#include <algorithm>
#include <stdio.h>
#include "clock.h"

namespace {
    std::vector< EventGenerator * > event_generators;
    long long unsigned current_time = 0;
}

namespace Clock {
    long long unsigned current_time() {
        return ::current_time;
    }

    void insert( EventGenerator * generator ) {
        event_generators.push_back( generator );
    }

    std::vector< std::string > advance() {
        std::vector< std::string > events;
        long long unsigned earlier_time = -1;

        for( auto generator : event_generators )
            earlier_time = std::min( generator->next_event(), earlier_time );

        for( auto generator : event_generators ) {
            std::string event = generator->advance( earlier_time );
            if( event != "" ) events.push_back( event );
        }

        return events;
    }

    std::vector< std::string > next_events() {
        std::vector< std::pair<unsigned, std::string> > event_list;
        for( auto generator : event_generators )
            event_list.push_back({
                    generator->next_event(),
                    generator->next_event_description()
                });
        std::sort( event_list.begin(), event_list.end() );

        std::vector< std::string > ret_val;
        for( auto pair : event_list )
            ret_val.push_back( pair.second );
        return ret_val;
    }
};

