/* measurer.test.cpp
 * Unit test of the measurer.
 */
#include "measurer.h"
#include <catch.hpp>

TEST_CASE( "measurer basic funcionality", "[measurer][statistics]" ) {
    measurer m;
    m.insert( 100 );
    CHECK( m.min() == 100 );
    CHECK( m.max() == 100 );
    CHECK( m.average() == Approx(100) );

    SECTION( "same value repeated" ) {
        m.insert( 100 );
        CHECK( m.min() == 100 );
        CHECK( m.max() == 100 );
        CHECK( m.average() == Approx(100) );

        m.insert( 100 );
        CHECK( m.min() == 100 );
        CHECK( m.max() == 100 );
        CHECK( m.average() == Approx(100) );
    }

    SECTION( "different values" ) {
        m.insert( 50 );
        CHECK( m.min() == 50 );
        CHECK( m.max() == 100 );
        CHECK( m.average() == Approx(75) );

        m.insert( 75 );
        CHECK( m.min() == 50 );
        CHECK( m.max() == 100 );
        CHECK( m.average() == Approx(75) );

        m.insert( 300 );
        CHECK( m.min() == 50 );
        CHECK( m.max() == 300 );
        CHECK( m.average() == Approx(131.25) );

        m.insert( 0 );
        CHECK( m.min() == 0 );
        CHECK( m.max() == 300 );
        CHECK( m.average() == Approx(105) );
    }
}
