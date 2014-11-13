/* network.h
 * Classes that transfers the requisitions back and forth between the
 * client and the servers and mantains statistics about the queues
 * involved in this process.
 */
#ifndef NETWORK_H
#define NETWORK_H

#include "measurer.h"
#include "event_generator.h"
#include "requisition.h"

class ClientToServer : public EventGenerator {
public:
    void send( Requisition );
}

class ServerToClient : public EventGenerator {
public:
    void send( Requisition );
}

ServerToClient server_to_client;
ClientToServer client_to_server;
measurer response_times;

#endif // NETWORK_H
