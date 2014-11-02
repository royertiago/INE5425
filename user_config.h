/* user_config.h
 * Header that centralizes all possible variables configurable by the user.
 * See system_overview.md. */
#ifndef USER_CONFIG_H
#define USER_CONGIG_H

namespace user {
    /* lamda[i] is the average rate in which the client i sends
     * another requisition.
     *
     * Default values:
     * 30, 60, 120, 120 */
    extern double lambda[4];

    /* response_time[i] is the time that takes to a server process
     * to answer an requisition of type i+1.
     *
     * Default values:
     * 10, 8, 15, 30 */
    extern double response_time[4];

    /* Extracts the configurations from the specified file.
     * Writes to std::cerr three error messages: "absent or inaccessible file",
     * "unknown variable", or "wrong number format".
     *
     * The format shall conform the one described in user_config.md. */
    void read_configuration( const char * filename );
}

#endif // USER_CONFIG_H
