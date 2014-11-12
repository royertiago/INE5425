/* server.h
 * This class does the requisition enqueue and processing and returns
 * them to the client.
 */
#ifndef SERVER_H
#define SERVER_H

#include "event_generator.h"
#include "requisition.h"

class Server { // server process
    std::queue<Requisition> queue;

    /* weighted_queue_time is the sum of all the queueing times
     * weighted by the number of requisitions being processed.
     *
     * Or can be tought as the sum of all queueing times. */
    unsigned int wheighted_queue_time = 0;

    unsigned int maximum_queue_time = 0;
    unsigned int occupied_time_us = 0;
    unsigned int empty_time_us = 0;

public:
    virtual ~Server() = default;

    void process( Requisition );

    virtual unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual std::string advance( unsigned microseconds ) override;
};

Server processes[2];

#endif // SERVER_H
