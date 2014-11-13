/* measured_resource.h
 * A requisition queue that is able to record and report usage statistics.
 *
 * This class represents both the resource queue and the resource processing.
 */
#ifndef MEASURED_RESOURCE_H
#define MEASURED_RESOURCE_H

#include <queue>
#include <utility>
#include "measurer.h"
#include "requisition.h"

struct MeasuredResource {
    long long unsigned current_time = 0;
    long long unsigned next_event_time = -1llu;
    struct data_t {
        Requisition req;
        long long unsigned insertion_time;
        long long unsigned processing_time;
    };
    std::queue< data_t > queue;
    measurer delays;
    measurer entities;
    measurer occupancy;

public:
    /* Inserts a new requisition to be processed by the server.
     * Note that the statistics about queue size will be updated only
     * in the following call to advance, and statistics about delays
     * are updated only when an entity exists the server. */
    void insert( Requisition req, long long unsigned processing_time );

    /* Advance the time in `time` time units. If any entity finishes
     * processing, pair.first is true and pair.second is the specified
     * requisition. Otherwise, pair.first is false and pair.second
     * is meaningless.
     *
     * time must be at most next_event(). */
    std::pair< bool, Requisition > advance( long long unsigned time );

    /* time until current entity finishes processing.
     * If there is no entity in the server, -1llu is returned. */
    long long unsigned next_event() const;

    /* Returns the next requisition to be sent. */
    Requisition front() const { return queue.front().req; }

    // Queue statistics and resource occupancy rate
    int    min_entities()     const { return entities.min();      }
    int    max_entities()     const { return entities.max();      }
    double average_entities() const { return entities.average();  }
    int    min_delay()        const { return delays.min();        }
    int    max_delay()        const { return delays.max();        }
    double average_delay()    const { return delays.average();    }
    double occupancy_rate()   const { return occupancy.average(); }
};

#endif //  MEASURED_RESOURCE_H
