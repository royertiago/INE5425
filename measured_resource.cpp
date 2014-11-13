/* measured_resource.cpp
 * Implementation of measured_resource.h.
 */
#include "measured_resource.h"

void MeasuredResource::insert( Requisition req, long long unsigned processing_time ) {
    if( queue.empty() ) next_event_time = processing_time;
    queue.push({ req, current_time, processing_time });
}

long long unsigned MeasuredResource::next_event() const {
    return next_event_time;
}

std::pair< bool, Requisition > MeasuredResource::advance( long long unsigned time ) {
    current_time += time;
    occupancy.insert( !queue.empty(), time );
    if( queue.empty() ) {
        entities.insert( 0, time );
        return std::make_pair( false, Requisition() );
    }

    next_event_time -= time;

    data_t & data = queue.front();
    entities.insert( queue.size() - 1, time );

    if( next_event_time != 0 )
        return std::make_pair( false, Requisition() );

    delays.insert( current_time - data.insertion_time - data.processing_time );
    auto pair = std::make_pair( true, data.req );
    queue.pop();

    if( queue.empty() )
        next_event_time = -1llu;
    else
        next_event_time = queue.front().processing_time;

    return pair;
}
