/* network.cpp
 * Implementation of network.h.
 */
#include <cstdio>
#include "clock.h"
#include "network.h"
#include "server.h"
#include "random.h"

ServerToClient server_to_client;
ClientToServer client_to_server;
measurer response_times;

void ClientToServer::send( Requisition req ) {
    queue.insert( req, req.response_size * 5 / Random::network_efficiency() + 1000 );
}

void ServerToClient::send( Requisition req ) {
    queue.insert( req, req.response_size * 5 / Random::network_efficiency() + 1000 );
}

long long unsigned ClientToServer::next_event() {
    return queue.next_event();
}

long long unsigned ServerToClient::next_event() {
    return queue.next_event();
}

std::string ClientToServer::next_event_description() {
    if( queue.next_event() == -1llu ) return "";
    static char str[1024];
    Requisition req = queue.front();
    int end = std::sprintf( str, "Dispatch %6s requisition to server\n",
            req.type );
    return std::string( str, str + end );
}

std::string ServerToClient::next_event_description() {
    if( queue.next_event() == -1llu ) return "";
    static char str[1024];
    Requisition req = queue.front();
    int end = std::sprintf( str, "Dispatch %6s requisition back to client\n",
            req.type );
    return std::string( str, str + end );
}

std::string ClientToServer::advance( long long unsigned us ) {
    auto pair = queue.advance( us );
    if( pair.first == false ) return "";

    static char str[1024];
    Requisition req = pair.second;
    int end = std::sprintf( str, "Dispatched %6s requisition to server", req.type );

    processes[req.server_process].process( req );
    return std::string( str, str + end );
}

std::string ServerToClient::advance( long long unsigned us ) {
    auto pair = queue.advance( us );
    if( pair.first == false ) return "";

    static char str[1024];
    Requisition req = pair.second;
    int end = std::sprintf( str, "Dispatched %6s answer back to client", req.type );

    Requisition::alive--;
    response_times.insert( Clock::current_time() - req.creation_timestamp );
    return std::string( str, str + end );
}
