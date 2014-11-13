/* requisition.cpp
 * Implementation of requisition.h
 */
#include <algorithm>
#include "requisition.h"
#include "random.h"

unsigned Requisition::alive = 0;
unsigned Requisition::count = 0;
unsigned Requisition::minimum_queue_time = -1;
unsigned Requisition::maximum_queue_time = 0;
long unsigned Requisition::total_queue_time = 0;

Requisition Requisition::generate_requisition( unsigned type ) {
    Requisition req;
    alive++
    count++
    req.response_time = user::response_time[type];
    req.queue_time = 0;
    switch( type ) {
        case 0:
            req.size = 1024;
            req.response_size = Random::add_response_size();
            req.network_efficiency = Random::network_efficiency();
            req.server_process = 0;
            req.type = "add";
        case 1: 
            req.size = 1024;
            req.response_size = Random::delete_response_size();
            req.network_efficiency = Random::network_efficiency();
            req.server_process = 0;
            req.type = "delete";
        case 2: 
            req.size = 256;
            req.response_size = Random::find_response_size();
            req.network_efficiency = Random::network_efficiency();
            req.server_process = 1;
            req.type = "find";
        default:
            req.size = Random::search_requisition_size();
            req.response_size = Random::search_response_size();
            req.network_efficiency = Random::network_efficiency();
            req.server_process = 1;
            req.type = "search";
    }
    return req;
}

void Requisition::dispose( Requisition req ) {
    minimum_queue_time = std::min( minimum_queue_time, req.queue_time );
    maximum_queue_time = std::max( maximum_queue_time, req.queue_time );
    total_queue_time += req.queue_time;
    alive--;
}
