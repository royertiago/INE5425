System Overview
===============

It is simulated a client-server system.
There are four clients, that send requisitions to the server through a network.
There are four types of requisitions and two processes in the server.
Each process answer two types of requisitions.
Each requisition type has different size, processing time and response size.
After processing, the response is sent back through the network.
The network latency is proportional to both the size of the request/response
being sent and its efficiency, plus 1ms of additional processing time;
the efficiency is between 60% and 80%, uniformly distributed.
The network is assumed to be full-duplex; that is, sending requisitions from
user to server does not affect sending responses from server to user.

Requisitions
-----------

| Type |  Name  |  Requisition size (bytes)  |        Response size (bytes)       | Process time (ms) |
|-----:|:-------|:--------------------------:|:----------------------------------:|:-----------------:|
| 1    | Add    |           1024             |      Discrete uniform 256, 512     |         10        |
| 2    | Delete |           1024             |      Discrete uniform 512, 1024    |          8        |
| 3    | Find   |           256              | Discrete triangular 256, 512, 1024 |         15        |
| 4    | Search | Discrete Uniform 256, 512  |        Discrete weighted *         |         30        |

The fourth requisition response size is an weighted discrete distibuted random
number. It is tabulated below.

| Size (bytes) | Probability |
|:------------:|:-----------:|
|       64     |    20%      |
|      512     |    30%      |
|     1024     |    30%      |
|     2048     |    20%      |

The first process in the server is able to process only the first two
requisition types, and the second can process only the last two.

Clients
-------

We can specify the arrival rate and distribution by type of requisitions 
by the different clients as such:

| Client |  Requisition ETA (messages/msec)  |          Requisition distribution          |
|:------:|:---------------------------------:|:------------------------------------------:|
| 1      | Exponential 1/λ1                  | Discrete 0.2, 1, 0.35, 2, 0.75, 3, 1.00, 4 |
| 2      | Exponential 1/λ2                  | Discrete 0.4, 1, 1.00, 2                   |
| 3      | Exponential 1/λ3                  | Discrete 0.6, 3, 1.00, 4                   |
| 4      | Exponential 1/λ4                  | Discrete 0.6, 3, 1.00, 4                   |

Where, by default, λ1, λ2, λ3 and λ4 are set to 30, 60, 120 and 120 respectively. 
These values can be redefined in the 'user\_config.txt' file. More information can
be found on 'user\_config.md'.

User-definable parameters
-------------------------

-   The mean-time between each requisition of the four clients, individually.
-   The requisition processing time for each requisition type, individually.

Recorded Statistics
-------------------

-   Minimum, maximum and average size of queues.
    The average size is as average between all the sizes, weighted by
    the time spent in each state.
-   Average resource occupation.
-   Minimum, maximum and average time that an entity spends in queues.
    The processing time _is not_ counted as "queue time".
-   Minimum, maximum and average response time
    The processing time _is_ counted as "response time".
-   Count of total entities at current time in the simulation.
