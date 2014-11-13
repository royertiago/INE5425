/* client.cpp
 * Implementation of client.h
 */
#include <cstdio>
#include "client.h"
#include "user.h"
#include "random.h"

int distributions[4][4] = {
    {20, 15, 40, 25},
    {40, 60,  0,  0},
    { 0,  0, 60, 40},
    { 0,  0, 60, 40},
};

Client Client::clients[4] = {
    Client( user::lambda[0], distributions[0], 0 ),
    Client( user::lambda[1], distributions[1], 1 ),
    Client( user::lambda[2], distributions[2], 2 ),
    Client( user::lambda[3], distributions[3], 3 ),
};

Client::Client( double l, int * t, int i ) :
    lambda( l ),
    type_distribution( t ),
    index( i )
{
    generate();
}

void Client::generate() {
    next_event_time_us = random::next_requisition_time( lambda );
    next_requisition = Requisition::generate_requisition(
            random::next_requisition_type( type_distribution ) );
    next_requisition.creation_timestamp += next_event_time_us;
}

unsigned Client::next_event() {
    return next_event_time_us;
}

std::string Client::next_event_description() {
    static char buffer[1024];
    int end = std::sprintf( buffer, "Send %6s requisition of size %4d from client %d\n",
            next_requisition.type, next_requisition.size, index );
    return std::string( buffer, buffer + end );
}

std::string Client::advance( unsigned us ) {
    next_event_time_us -= us;
    if( next_event_time_us != 0 ) return "";
    static char buffer[1024];
    int end = std::sprintf( buffer, "Sent %6s requisition of size %4d from client %d to network.\n",
            next_requisition.type, next_requisition.size, index );
    
    network.send_to_server( next_requisition );
    generate();
    return std::string( buffer, buffer + end );
}

void Client::reset() {
    for( int i = 0; i < 4; i++ ) {
        clients[i].labda = user::lambda[i];
        clients[i].generate();
    }
}