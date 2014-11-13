/* measurer.cpp
 * Implementation of measurer.h.
 */
#include <algorithm>
#include "measurer.h"

double measurer::average() const {
    if( _count == 0 ) return 0.0;
    return (double)_sum / _count;
}

void measurer::insert( unsigned long long value ) {
    _min = std::min( _min, value );
    _max = std::max( _max, value );
    _sum += value;
    _count++;
}
