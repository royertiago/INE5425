/* measurer.h
 * Classe that automates measuring minimum, maximum and average values.
 *
 * This class computes eighted average; to choose unweighted average,
 * insert all values with same weight (the default is 1).
 *
 * Note that these statistics are only meaningful after the insertion
 * of the first value.
 */
#ifndef MEASURER_H
#define MEASURER_H

#include <iosfwd>

class measurer {
    unsigned long long _min = -1;
    unsigned long long _max = 0;
    unsigned long long _sum = 0;
    unsigned long long _weight_sum = 0;
public:
    // Operations
    void insert( unsigned long long value, unsigned long long weight = 1 );

    // Statistics
    unsigned long long min() const { return _min; }
    unsigned long long max() const { return _max; }
    double average() const;

    friend std::ostream& operator<<( std::ostream&, const measurer& );
};

#endif // MEASURER_H
