/* server.cpp
 * Implementation of server.h.
 */
#include <cstdio>
#include "client.h"
#include "server.h"
#include "network.h"

Server processes[2];

void Server::process( Requisition req ) {
    queue.insert( req, req.processing_time );
}

long long unsigned int Server::next_event() {
    return queue.next_event();
}

std::string Server::next_event_description() {
    if( queue.next_event() == -1llu ) return "";

    Requisition req = queue.front();
    static char str[1024];
    int end = std::sprintf( str, "Send back %4d bytes answer to answer a %6s "
                                 "requisition from client %i",
                                 req.response_size, req.type, req.source->i() );
    return std::string( str, str + end );
}

std::string Server::advance( long long unsigned us ) {
    auto pair = queue.advance( us );
    if( pair.first == false ) return "";

    Requisition req = pair.second;
    server_to_client.send( req );

    static char str[1024];
    int end = std::sprintf( str, "Sent back %4d bytes answer to answer a %6s "
                                 "requisition from client %i",
                                 req.response_size, req.type, req.source->i() );
    return std::string( str, str + end );
}
