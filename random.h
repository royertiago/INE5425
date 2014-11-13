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

    unsigned next_requisition_type( int * distribution );
    unsigned next_requisition_time( double lambda );

    double network_efficiency();
}
#endif // RANCOM_H
