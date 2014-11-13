/* measurer.cpp
 * Implementation of measurer.h.
 */
#include <algorithm>
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