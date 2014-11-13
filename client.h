/* client.h
 * Class that generates the requisitions.
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <random>
#include "event_generator.h"

class Client : public EventGenerator {
    double lambda;
    int * type_distribution;
    int index;

    unsigned next_event; // microseconds
public:
    Client( double, int *, int );
    virtual ~Client() override;
    virtual unsigned int next_event() override;
    virtual std::string next_event_description() override;
    virtual bool advance( unsigned microseconds ) override;
};

/* Static array with all four clients. */
Client clients[4];

#endif // CLIENT_H
