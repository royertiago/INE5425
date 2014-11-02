Program configuration
=====================

There are eight values that can be setted by the user:
-   The mean time between the requisitions of the four clients; and
-   The requisition processing time for each type.

The first four variables are named lambda1, lambda2, lambda3 and lambda4;
the last four are named response1, response2, respose3 and response4.

The values for the variables can be set in file user_config.txt. The syntax is

    variable_name variable_value

variable_name must be one of the eight strings shown above, and variable_value
can be any floating point value. For example, to set lambda3 to 5, write

    lambda3 5

Or

    lambda3     5.0

(the space is ignored.) Any unset variables get its default value.
The current user_config.txt merely declares the default values for each
variable.

Default values
--------------

|  Variable | Value |
|:----------|------:|
| lambda1   |    30 |
| lambda2   |    60 |
| lambda3   |   120 |
| lambda4   |   120 |
| response1 |    10 |
| response2 |     8 |
| response3 |    15 |
| response4 |    30 |
