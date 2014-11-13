/* requisition.cpp
 * Implementation of requisition.h
 */

#include "clock.h"
#include "random.h"
#include "requisition.h"

unsigned Requisition::alive = 0;
unsigned Requisition::count = 0;

Requisition Requisition::generate_requisition( unsigned type ) {
    Requisition req;
    alive++
    count++
    req.creation_timestamp = Clock::current_time();
    switch( type ) {
        case 0:
            req.size = 1024;
            req.response_size = Random::add_response_size();
            req.processing_time = 10;
            req.network_efficiency = Random::network_efficiency();
            req.server_process = 0;
        case 1: 
            req.size = 1024;
            req.response_size = Random::delete_response_size();
            req.processing_time = 8;
            req.network_efficiency = Random::network_efficiency();
            req.server_process = 0;
        case 2: 
            req.size = 256;
            req.response_size = Random::find_response_size();
            req.processing_time = 15;
            req.network_efficiency = Random::network_efficiency();
            req.server_process = 1;
        default:
            req.size = Random::search_requisition_size();
            req.response_size = Random::search_response_size();
            req.processing_time = 30;
            req.network_efficiency = Random::network_efficiency();
            req.server_process = 1;
    }
    return req;
}
