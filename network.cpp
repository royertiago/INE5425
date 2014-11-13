/* network.cpp
 * Implementation of network.h.
 */
#include "random.h"
#include "network.h"

extern ServerToClient server_to_client;
extern ClientToServer client_to_server;
extern measurer response_times;

void ClientToServer::send( Requisition req ) {
    queue.insert( req, req.processing_time );
}

void ServerToClient::send( Requisition req ) {
    queue.insert( req, req.processing_time );
}

void ClientToServer::next_event() {
    return queue.next_event();
}

void ServerToClient::next_event() {
    return queue.next_event();
}

std::string ClientToServer::next_event_description() {
    if( queue.next_event() == -1llu ) return "";
    static char str[1024];
    Requisition req = queue.front();
    int end = std::sprintf( "Dispatch %6s requisition to server\n",
            to_client.front().type );
    return std::string( begin, begin + end );
}

std::string ServerToClient::next_event_description() {
    if( queue.next_event() == -1llu ) return "";
    static char str[1024];
    Requisition req = queue.front();
    int end = std::sprintf( "Dispatch %6s requisition back to client\n",
            to_server.front().type );
    return std::string( begin, begin + end );
}

std::string ClientToServer::advance( unsigned us ) {
    auto pair = queue.advance( us );
    if( pair.first == false ) return "";
    Requisition req = pair.second;
    int end = std::sprintf( "Dispatched %6s requisition to server\n", req.type );
    server[req.server_process].process( req );
    return std::string( begin, begin + end );
}

std::string ServerToClient::advance( unsigned us ) {
    auto pair = queue.advance( us );
    if( pair.first == false ) return "";
    Requisition req = pair.second;
    int end = std::sprintf( "Dispatched %6s answer to client\n", req.type );
    Requisition::alive--;
    response_times.insert( Clock::current_time() - req.creation_time );
    return std::string( begin, begin + end );
}
