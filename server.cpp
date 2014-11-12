/* server.cpp
 * Implementation of server.h.
 */
#include <cstdio>
#include "server.h"
#include "network.h"

void Server::process( Requisition req ) {
    queue.push(req);
    req.last_queue_timestamp = Clock::current_time();
}

unsigned int Server::next_event() {
    if( queue.empty() ) return -1;
    return queue.front().processing_time;
}

std::string Server::next_event_description() {
    if( queue.empty() ) return "";

    static char str[1024];
    int end = std::sprintf( str, "Send back %4d bytes answer to answer a %6s requisition from client %i\n",
            queue.front().response_size, queue.front().type, queue.front().source->i() );
    return std::string( str, str + end );
}

std::string Requisition::advance( unsigned us ) {
    if( queue.empty() ) return "";

    queue.front().processing_time -= us;
    if( queue.front().processing_time != 0 ) return "";
    Requisition req = queue.front();
    queue.pop();
    req.queue_time = Clock::current_time() - req.last_queue_timestamp;
    network.send_to_client( req );

    static char str[1024];
    int end = std::sprintf( str, "Sent back %4d bytes answer to answer a %6s requisition from client %i\n",
            queue.front().response_size, queue.front().type, queue.front().source->i() );

}
