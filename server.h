/* server.h
 * This class does the requisition enqueue and processing and returns
 * them to the client.
 */
#ifndef SERVER_H
#define SERVER_H

#include "event_generator.h"
#include "measured_resource.h"
#include "requisition.h"

struct Server : public EventGenerator { // server process
    MeasuredResource queue;
    virtual ~Server() = default;

    void process( Requisition );

    virtual long long unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual std::string advance( long long unsigned microseconds ) override;
};

extern Server processes[2];

#endif // SERVER_H
