/* requisition.cpp
 * Implementation of requisition.h
 */
#include "clock.h"
#include "random.h"
#include "requisition.h"
#include "user_config.h"

unsigned Requisition::alive = 0;
unsigned Requisition::count = 0;

Requisition Requisition::generate_requisition( unsigned type ) {
    Requisition req;
    alive++;
    count++;
    req.creation_timestamp = Clock::current_time();
    req.processing_time = user::processing_time[type] * 1000;
    switch( type ) {
        case 0:
            req.size = 1024;
            req.response_size = Random::add_response_size();
            req.server_process = 0;
            req.type = "add";
        break;
        case 1: 
            req.size = 1024;
            req.response_size = Random::delete_response_size();
            req.server_process = 0;
            req.type = "delete";
        break;
        case 2: 
            req.size = 256;
            req.response_size = Random::find_response_size();
            req.server_process = 1;
            req.type = "find";
        break;
        default:
            req.size = Random::search_requisition_size();
            req.response_size = Random::search_response_size();
            req.server_process = 1;
            req.type = "search";
    }
    return req;
}
