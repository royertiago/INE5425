/* network.h
 * Classes that transfers the requisitions back and forth between the
 * client and the servers and mantains statistics about the queues
 * involved in this process.
 */
#ifndef NETWORK_H
#define NETWORK_H

#include "event_generator.h"
#include "measurer.h"
#include "measured_resource.h"
#include "requisition.h"

class ClientToServer : public EventGenerator {
    measured_resource queue;
public:
    void send( Requisition );

    virtual ~ClientToServer() = default;
    virtual unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual bool advance( unsigned microseconds ) override;
}

class ServerToClient : public EventGenerator {
    measured_resource queue;
public:
    void send( Requisition );

    virtual ~ServerToClient() = default;
    virtual unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual bool advance( unsigned microseconds ) override;
}

ServerToClient server_to_client;
ClientToServer client_to_server;
measurer response_times;

#endif // NETWORK_H
