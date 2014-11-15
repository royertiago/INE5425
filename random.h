/* random.h
 * Header that summarizes random number generation in the program.
 *
 * The namespace name is capitalized to not conflict with the name
 * of the POSIX random() function.
 */
#ifndef RANDOM_H
#define RANDOM_H

namespace Random {
    /* restart the random number generation, based on user::seed. */
    void reset();

    /* Generate random response sizes for the various possible requisitions
     * specified in system_overview.md. */
    unsigned add_response_size();
    unsigned delete_response_size();
    unsigned find_response_size();
    unsigned search_response_size();
    unsigned search_requisition_size();

    /* Generate a random requisition type, based with the first
     * four values in of the passed pointer. For example, if
     * the first four values are
     *  10  20  50  30
     * then the likehood of the value 0 to be generated is 10%,
     * the likehood of 1 is 20% and so on. */
    unsigned next_requisition_type( int * distribution );

    unsigned next_requisition_time( double lambda );

    double network_efficiency();
}
#endif // RANCOM_H
