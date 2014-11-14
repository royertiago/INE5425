/* measurer.cpp
 * Implementation of measurer.h.
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "measurer.h"

double measurer::average() const {
    if( _weight_sum == 0 ) return 0.0;
    return (double)_sum / _weight_sum;
}

void measurer::insert( unsigned long long value, unsigned long long weight ) {
    _min = std::min( _min, value );
    _max = std::max( _max, value );
    _sum += value * weight;
    _weight_sum += weight;
}

std::ostream & operator<<( std::ostream& os, const measurer& m ) {
    return os << m._min/1000 << "/"
        << std::setprecision(2) << m.average()/1000
        << "/" << m._max/1000;
}
