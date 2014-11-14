/* client.cpp
 * Implementation of client.h
 */
#include <cstdio>
#include "client.h"
#include "network.h"
#include "random.h"
#include "user_config.h"

int distributions[4][4] = {
    {20, 15, 40, 25},
    {40, 60,  0,  0},
    { 0,  0, 60, 40},
    { 0,  0, 60, 40},
};

Client clients[4] = {
    Client( user::lambda[0], distributions[0], 0 ),
    Client( user::lambda[1], distributions[1], 1 ),
    Client( user::lambda[2], distributions[2], 2 ),
    Client( user::lambda[3], distributions[3], 3 ),
};

Client::Client( double l, int * t, int i ) :
    lambda( l ),
    type_distribution( t ),
    index( i )
{}

void Client::generate() {
    next_event_time_us = Random::next_requisition_time( lambda );
    next_requisition = Requisition::generate_requisition(
            Random::next_requisition_type( type_distribution ) );
    next_requisition.creation_timestamp += next_event_time_us;
    next_requisition.source = this;
}

long long unsigned Client::next_event() {
    return next_event_time_us;
}

std::string Client::next_event_description() {
    static char buffer[1024];
    int end = std::sprintf( buffer, "Send %6s requisition of size %4d from client %d",
            next_requisition.type, next_requisition.size, index );
    return std::string( buffer, buffer + end );
}

std::string Client::advance( long long unsigned us ) {
    next_event_time_us -= us;
    if( next_event_time_us != 0 ) return "";
    static char buffer[1024];
    int end = std::sprintf( buffer, "Sent %6s requisition of size %4d from client %d to network",
            next_requisition.type, next_requisition.size, index );
    
    client_to_server.send( next_requisition );
    generate();
    return std::string( buffer, buffer + end );
}

void Client::reset() {
    Requisition::count -= 4;
    Requisition::alive -= 4;
    for( int i = 0; i < 4; i++ ) {
        clients[i].lambda = user::lambda[i];
        clients[i].generate();
    }
}
