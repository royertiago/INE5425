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

    /* Generate rancom response sizes for the various possible requisitions
     * specified in system_overview.md. */
    unsigned add_response_size();
    unsigned delete_response_size();
    unsigned find_response_size();
    unsigned search_response_size();


}
#endif // RANCOM_H
