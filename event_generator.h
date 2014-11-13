/* event_generator.h
 * Interface to classes that can generate events in time.
 */
#ifndef EVENT_GENERATOR_H
#define EVENT_GENERATOR_H

#include <string>

struct EventGenerator {
    /* Remaining time to the next event, in microsseconds. */
    virtual unsigned int next_event();

    /* Textual description of the next event. 
     * This event is the one that will be generated by the advance() method. */
    virtual std::string next_event_description();

    /* Advance this event generator. If an event was generated, return true;
     * otherwise, return false. */
    virtual bool advance( unsigned microseconds );

    virtual ~EventGenerator();
};

#endif // EVENT_GENERATOR_H