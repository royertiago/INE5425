/* server.h
 * This class does the requisition enqueue and processing and returns
 * them to the client.
 */
#ifndef SERVER_H
#define SERVER_H

#include "event_generator.h"
#include "measured_resource.h"
#include "requisition.h"

class Server : public EventGenerator { // server process
    MeasuredResource queue;
public:
    virtual ~Server() = default;

    void process( Requisition );

    virtual unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual std::string advance( unsigned microseconds ) override;
};

extern Server processes[2];

#endif // SERVER_H
