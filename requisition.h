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
    // Global information
    static unsigned alive; // Number of requisitions alive in the program.
    static unsigned count; // Total number of created requisitions

    // Requisition data
    unsigned size, response_size; // bytes
    unsigned processing_time; // ms
    double network_efficiency; // ratio (uniformly distributed in [0.6, 0.8])
    int server_process; // in what process will this requisition be processed?
    Client * source;

    // Local statistics
    unsigned total_queue_time;
    unsigned last_queue_timestamp;

    // Global statistics
    static unsigned minimum_queue_time;
    static unsigned maximum_queue_time;
    static long unsigned total_queue_time;

    /* Generate a new requisition according to the type; see system_overview.md.
     * The source pointer is not set; type is indexed by zero. */
    static Requisition generate_requisition( unsigned type );
};

#endif // REQUISITION_H
