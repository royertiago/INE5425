/* requisition.h
 * Class that travels around the system.
 *
 * All random data about a requisition is generated on creation,
 * and then only statistics are updated.
 *
 * Note the requisition type is unnecessary.
 */
#ifndef REQUISITION_H
#define REQUISITION_H

class Client;

struct Requisition {
    static unsigned alive; // Number of requisitions alive in the program.
    static unsigned count; // Total number of created requisitions

    // requisition data
    unsigned size, response_size; // bytes
    unsigned processing_time; // ms
    double network_efficiency; // ratio (uniformly distributed in [0.6, 0.8])
    int server_process; // in what process will this requisition be processed?
    Client * source;

    // statistics
    unsigned total_queue_time;
    unsigned last_queue_timestamp;

    static unsigned minimum_queue_time;
    static unsigned maximum_queue_time;
    static long unsigned total_queue_time;
};

#endif // REQUISITION_H
