/* server.h
 * This class does the requisition enqueue and processing and returns
 * them to the client.
 */
#ifndef SERVER_H
#define SERVER_H

#include "event_generator.h"
#include "requisition.h"

class Server { // server process
    std::queue<Requisition> requisitions;
    unsigned int total_queue_time;
    unsigned int maximum_queue_time;
    unsigned int occupied_us;
    unsigned int empty_us;

public:
    virtual ~Server() = default;

    void process( Requisition );

    virtual unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual bool advance( unsigned microseconds ) override;
};

Server processes[2];

#endif // SERVER_H
