Program configuration
=====================

There are nine values that can be setted by the user:
-   The mean time between the requisitions of the four clients;
-   The requisition processing time for each type; and
-   The RNG seed.

The first four variables are named lambda1, lambda2, lambda3 and lambda4;
the following four are named processing1, processing2, respose3 and processing4,
and the seed is simply `seed`.

The values for the variables can be set in file user\_config.txt. The syntax is

    variable_name variable_value

variable\_name must be one of the nine strings shown above, and variable\_value
can be any floating point value (except for the seed, where the number must
be a positive number smaller than 2^32) . For example, to set lambda3 to 5, write

    lambda3 5

Or

    lambda3     5.0

(the space is ignored.) Any unset variables get its default value.
The current user\_config.txt merely declares the default values for each
variable.

Default values
--------------

|  Variable   |         Value         |
|:------------|----------------------:|
| lambda1     |                    30 |
| lambda2     |                    60 |
| lambda3     |                   120 |
| lambda4     |                   120 |
| processing1 |                    10 |
| processing2 |                     8 |
| processing3 |                    15 |
| processing4 |                    30 |
| seed        | based on current time |
