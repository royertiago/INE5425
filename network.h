/* network.h
 * Class that transfers the requisitions back and forth between the
 * client and the servers and mantains statistics about the queues
 * involved in this process.
 */
#ifndef NETWORK_H
#define NETWORK_H

#include "event_generator.h"
#include "requisition.h"

class Network : public EventGenerator {
public:
    void send_to_server( Requisition );
    void send_to_client( Requisition );
};

Network network;

#endif // NETWORK_H
