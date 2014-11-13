/* measurer.h
 * Classe that automates measuring minimum, maximum and average values.
 *
 * Note that these statistics are only meaningful after the insertion
 * of the first value.
 */
#ifndef MEASURER_H
#define MEASURER_H

class measurer {
    unsigned long long _min = -1;
    unsigned long long _max = 0;
    unsigned long long _sum = 0;
    unsigned long long _count = 0;
public:
    // Operations
    void insert( unsigned long long value );

    // Statistics
    unsigned long long min() const { return _min; }
    unsigned long long max() const { return _max; }
    double average() const;
};

#endif // MEASURER_H
