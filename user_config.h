/* user_config.h
 * Header that centralizes all possible variables configurable by the user.
 * See system_overview.md.
 *
 * All the lambdas and processing_times are defined in user_config.cpp;
 * user::seed is defined in random.cpp. */
#ifndef USER_CONFIG_H
#define USER_CONGIG_H

namespace user {
    /* lamda[i] is the average rate in which the client i sends
     * another requisition.
     *
     * Default values:
     * 30, 60, 120, 120 */
    extern double lambda[4];

    /* processing_time[i] is the time that takes to a server process
     * to answer an requisition of type i+1.
     *
     * Default values:
     * 10, 8, 15, 30 */
    extern double processing_time[4];

    /* Seed used in random number generation.
     * Default: implementation-defined. */
    extern unsigned int seed;

    /* Extracts the configurations from the specified file.
     * Writes to std::cerr three error messages: "absent or inaccessible file",
     * "unknown variable", or "wrong number format".
     *
     * The format shall conform the one described in user_config.md. */
    void read_configuration( const char * filename );
}

#endif // USER_CONFIG_H
