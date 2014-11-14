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

struct ClientToServer : public EventGenerator {
    MeasuredResource queue;
    void send( Requisition );

    virtual ~ClientToServer() = default;
    virtual long long unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual std::string advance( long long unsigned microseconds ) override;
};

struct ServerToClient : public EventGenerator {
    MeasuredResource queue;
    void send( Requisition );

    virtual ~ServerToClient() = default;
    virtual long long unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual std::string advance( long long unsigned microseconds ) override;
};

extern ServerToClient server_to_client;
extern ClientToServer client_to_server;
extern measurer response_times;

#endif // NETWORK_H
