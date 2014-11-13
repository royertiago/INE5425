/* network.cpp
 * Implementation of network.h.
 */
#include <algorithm>
#include "random.h"
#include "network.h"

void Network::send_to_server( Requisition req ) {
    req.last_queue_timestamp = Clock::current_time();
    req.network_time_us = Random::network_efficiency() * req.size;
    to_server.push_back( req );
}

void Network::send_to_client( Requisition req ) {
    req.last_queue_timestamp = Clock::current_time();
    req.network_time_us = Random::network_efficiency() * req.response_size;
    to_client.push_back( req );
}

unsigned Network::next_event() {
    if( to_server.empty() && to_client.empty() ) return -1;
    if( to_server.empty() && !to_client.empty() )
        return to_server.front().network_time_us;
    if( !to_server.empty() && to_client.empty() )
        return to_server.front().network_time_us;

    return std::min( to_server.front().network_time_us,
                     to_client.front().network_time_us );
}

std::string Network::next_event_description() {
    static char str[1024];
    if( to_server.empty() ) {
        if( to_client.empty() ) return "";
        int end = std::sprintf( "Dispatch %6s requisition to server\n",
                to_client.front().type );
        return std::string( begin, begin + end );
    }
    if( to_client.empty() ) {
        int end = std::sprintf( "Dispatch %6s requisition back to client\n",
                to_server.front().type );
        return std::string( begin, begin + end );
    }
    if( to_client.front().network_time_us < to_server.front().network_time_us ) {
        int end = std::sprintf( "Dispatch %6s requisition back to client\n",
                to_server.front().type );
        return std::string( begin, begin + end );
    }
    int end = std::sprintf( "Dispatch %6s requisition to server\n",
            to_client.front().type );
    return std::string( begin, begin + end );
}

std::string Network::advance( unsigned us ) {
    static char str[1024];
    if( to_server.empty() && to_client.empty() ) return "";

    if( to_server.empty() ) {
        to_client.front().network_time_us -= us;
        if( to_client.front().network_time_us != 0 ) return "";

        Requisition req = to_client.front();
        to_client.pop();

        int end = std::sprintf( "Dispatched %6s answer to client\n", req.type );
        req.queue_time += Clock::current_time() - req.last_queue_timestamp;
        Requisition::dispose( req );
        return std::string( begin, begin + end );
    }
    if( to_client.empty() ) {
        to_server.front().network_time_us -= us;
        if( to_server.front().network_time_us != 0 ) return "";

        Requisition req = to_server.front();
        to_server.pop();

        int end = std::sprintf( "Dispatched %6s requisition to server\n", req.type );
        req.queue_time += Clock::current_time();
        server[req.server_process].process( req );
        return std::string( begin, begin + end );
    }

    to_server.front().network_time_us -= us;
    to_client.front().network_time_us -= us;

    if( to_client.front().network_time_us == 0 ) {
        Requisition req = to_client.front();
        to_client.pop();
        int end = std::sprintf( "Dispatched %6s answer to client\n", req.type );
        req.queue_time += Clock::current_time() - req.last_queue_timestamp;
        Requisition::dispose( req );
        return std::string( str, str + end );
    }
    if( to_server.front().network_time_us == 0 ) {
        Requisition req = to_server.front();
        to_server.pop();

        int end = std::sprintf( "Dispatched %6s requisition to server\n", req.type );
        req.queue_time += Clock::current_time();
        server[req.server_process].process( req );
        return std::string( begin, begin + end );
    }
    return "";
}
