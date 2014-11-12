/* client.h
 * Class that generates the requisitions.
 */
#ifndef CLIENT_H
#define CLIENT_H

#include "event_generator.h"
#include "requisition.h"

class Client : public EventGenerator {
    double lambda;
    int * type_distribution;
    int index;

    unsigned next_event_time_us; // microseconds
    Requisition next_requisition;

    // Generate the next requisition and requisition times.
    void generate();
public:
    Client( double, int *, int );
    virtual ~Client() = default;
    virtual unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual std::string advance( unsigned microseconds ) override;

    /* Assign the user-defined lambdas to the client array defined
     * below. */
    static void reset();
};

/* Static array with all four clients. */
Client clients[4];

#endif // CLIENT_H
