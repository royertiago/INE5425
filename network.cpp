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
    long long unsigned time = req.size * 5 / Random::network_efficiency();
    //printf( "ClientToServer::send() (this %p, time %llu), next_event %llu, ", (void*) this, time, queue.next_event() );
//    queue.insert( req, req.size * 5 / Random::network_efficiency() );
    queue.insert( req, time );
    //printf( "next event %llu\n", queue.next_event() );
}

void ServerToClient::send( Requisition req ) {
    queue.insert( req, req.response_size * 5 / Random::network_efficiency() );
}

long long unsigned ClientToServer::next_event() {
    //printf( "ClientToServer::next_event() (this %p)-> %llu\n", (void*)this, queue.next_event() );
    return queue.next_event();
}

long long unsigned ServerToClient::next_event() {
    return queue.next_event();
}

std::string ClientToServer::next_event_description() {
    //printf( "ClientToServer::next_event_description() (%llu)\n", queue.next_event() );
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
    //printf( "ClientToServer::advance(%llu) (this %p) - Next event = %llu\n", us, (void*)this, queue.next_event() );
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
