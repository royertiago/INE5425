/* requisition.h
 * Class that travels around the system.
 *
 * All random data about a requisition is generated on creation,
 * and then only statistics are updated.
 */
#ifndef REQUISITION_H
#define REQUISITION_H

struct Requisition {
    static unsigned count; // Number of requisitions alive in the program.

    // requisition data
    unsigned size, response_size; // bytes
    unsigned processing_time; // ms
    double network_efficiency; // ratio (uniformly distributed in [0.6, 0.8])

    // statistics
    unsigned creation_timestamp;

    /* Randomly generate the next requisition.
     * The function generate_i generates a requisition according to the
     * type distribition per client; see system_overview.md. */
    static Requisition generate1();
    static Requisition generate2();
    static Requisition generate3();
    static Requisition generate4();
};

#endif // REQUISITION_H
