/* measured_resource.test.cpp
 * Unit test for MeasuredResource.
 */
#include "measured_resource.h"
#include <catch.hpp>

TEST_CASE( "MeasuredResource basic funcionality", "[MeasuredResource]" ) {
    MeasuredResource r;
    Requisition req1;
    req1.creation_timestamp = 1;
    Requisition req2;
    req2.creation_timestamp = 2;
    Requisition req3;
    req3.creation_timestamp = 3;
    Requisition req4;
    req4.creation_timestamp = 4;
    std::pair< bool, Requisition > pair;

    CHECK( r.next_event() == -1llu );
    CHECK( r.current_queue() == 0 );

    SECTION( "sample run" ) {
        pair = r.advance( 10 );
        CHECK( pair.first == false );

        r.insert( req1, 5 );
        CHECK( r.current_queue() == 0 );
        CHECK( r.next_event() == 5 );
        // 10 min

        pair = r.advance( 2 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == 3 );
        CHECK( r.max_entities() == 0 );
        CHECK( r.max_delay() == 0 );

        r.insert( req2, 8 );
        CHECK( r.next_event() == 3 );
        CHECK( r.max_entities() == 0 );
        CHECK( r.current_queue() == 1 );
        CHECK( r.max_delay() == 0 );
        CHECK( r.occupancy_rate() == Approx(2.0/12.0) );
        CHECK( r.average_entities() == Approx(0.0/12.0) );
        // 12 min

        pair = r.advance( 2 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == 1 );
        CHECK( r.current_queue() == 1 );
        CHECK( r.occupancy_rate() == Approx(4.0/14.0) );
        CHECK( r.average_entities() == Approx(2.0/14.0) );
        // 14 min

        pair = r.advance( 1 );
        CHECK( pair.first == true );
        CHECK( pair.second.creation_timestamp == 1 );
        CHECK( r.max_entities() == 1 );
        CHECK( r.average_entities() == Approx(3.0/15.0) );
        CHECK( r.current_queue() == 0 );
        CHECK( r.occupancy_rate() == Approx(1.0/3.0) );
        CHECK( r.min_delay() == 0 );
        CHECK( r.next_event() == 8 );
        // 15 min

        pair = r.advance( 5 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == 3 );
        CHECK( r.average_entities() == Approx(3.0/20.0) );
        CHECK( r.current_queue() == 0 );
        CHECK( r.occupancy_rate() == Approx(10.0/20.0) );

        r.insert( req1, 2 );
        CHECK( r.current_queue() == 1 );
        r.insert( req3, 3 );
        CHECK( r.current_queue() == 2 );
        r.insert( req4, 2 );
        CHECK( r.current_queue() == 3 );
        CHECK( r.next_event() == 3 );
        CHECK( r.max_entities() == 1 );
        // 20 min

        pair = r.advance( 3 );
        CHECK( pair.first == true );
        CHECK( pair.second.creation_timestamp == 2 );
        CHECK( r.max_entities() == 3 );
        CHECK( r.average_entities() == Approx(12.0/23.0) );
        CHECK( r.current_queue() == 2 );
        CHECK( r.occupancy_rate() == Approx(13.0/23.0) );
        CHECK( r.max_delay() == 3 );
        CHECK( r.average_delay() == Approx(1.5) );
        CHECK( r.next_event() == 2 );
        // 23 min

        pair = r.advance( 2 );
        CHECK( pair.first == true );
        CHECK( pair.second.creation_timestamp == 1 );
        CHECK( r.max_delay() == 3 );
        CHECK( r.average_delay() == Approx(6.0/3.0) );
        CHECK( r.average_entities() == Approx(16.0/25.0) );
        CHECK( r.current_queue() == 1 );
        CHECK( r.occupancy_rate() == Approx(15.0/25.0) );
        CHECK( r.next_event() == 3 );
        // 25 min

        pair = r.advance( 3 );
        CHECK( pair.first == true );
        CHECK( pair.second.creation_timestamp == 3 );
        CHECK( r.max_delay() == 5 );
        CHECK( r.average_delay() == Approx(11.0/4.0) );
        CHECK( r.average_entities() == Approx(19.0/28.0) );
        CHECK( r.current_queue() == 0 );
        CHECK( r.next_event() == 2 );
        CHECK( r.occupancy_rate() == Approx(18.0/28.0) );
        // 28 min

        pair = r.advance( 2 );
        CHECK( pair.first == true );
        CHECK( pair.second.creation_timestamp == 4 );
        CHECK( r.max_delay() == 8 );
        CHECK( r.average_delay() == Approx(19.0/5.0) );
        CHECK( r.average_entities() == Approx(19.0/30.0) );
        CHECK( r.current_queue() == 0 );
        CHECK( r.occupancy_rate() == Approx(2.0/3.0) );
        CHECK( r.next_event() == -1llu );
        // 30 min

        pair = r.advance( 10 );
        CHECK( pair.first == false );
        CHECK( r.max_delay() == 8 );
        CHECK( r.average_delay() == Approx(19.0/5.0) );
        CHECK( r.max_entities() == 3 );
        CHECK( r.average_entities() == Approx(19.0/40.0) );
        CHECK( r.current_queue() == 0 );
        CHECK( r.occupancy_rate() == Approx(20.0/40.0) );
        CHECK( r.next_event() == -1llu );
    }

    SECTION( "multiple advances" ) {
        pair = r.advance( 10 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == -1llu );
        pair = r.advance( 10 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == -1llu );
        pair = r.advance( 10 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == -1llu );
        pair = r.advance( 10 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == -1llu );

        r.insert( req1, 100 );

        pair = r.advance( 10 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == 90 );
        pair = r.advance( 10 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == 80 );
        pair = r.advance( 10 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == 70 );
        pair = r.advance( 10 );
        CHECK( pair.first == false );
        CHECK( r.next_event() == 60 );
    }
}
