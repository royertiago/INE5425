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

    SECTION( "different weights" ) {
        m.insert( 200, 3 );
        CHECK( m.min() == 100 );
        CHECK( m.max() == 200 );
        CHECK( m.average() == Approx(175) );

        m.insert( 40, 2 );
        CHECK( m.min() == 40 );
        CHECK( m.max() == 200 );
        CHECK( m.average() == Approx(130) );

        SECTION( "default values" ) {
            m.insert( 60 );
            CHECK( m.min() == 40 );
            CHECK( m.max() == 200 );
            CHECK( m.average() == Approx(120) );
        }
        SECTION( "specifying 1 as parameter" ) {
            m.insert( 60, 1 );
            CHECK( m.min() == 40 );
            CHECK( m.max() == 200 );
            CHECK( m.average() == Approx(120) );
        }
    }
}
