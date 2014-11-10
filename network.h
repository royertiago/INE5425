/* network.h
 * Class that transfers the requisitions back and forth between the
 * client and the servers and mantains statistics about the queues
 * involved in this process.
 */
#ifndef NETWORK_H
#define NETWORK_H

#include <queue>
#include "event_generator.h"
#include "requisition.h"

class Network : public EventGenerator {
    std::queue<Requisition> to_server;
    std::queue<Requisition> to_client;
public:
    void send_to_server( Requisition );
    void send_to_client( Requisition );

    virtual ~Network() = default;
    virtual unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual bool advance( unsigned microseconds ) override;
};

Network network;

#endif // NETWORK_H
