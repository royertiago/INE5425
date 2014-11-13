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

| Type |  Name  | Requisition size (bytes) |        Response size (bytes)       | Process time (ms) |
|-----:|:-------|:------------------------:|:----------------------------------:|:-----------------:|
| 1    | Add    |           1024           |      Discrete uniform 256, 512     |         10        |
| 2    | Delete |           1024           |      Discrete uniform 512, 1024    |          8        |
| 3    | Find   |           256            | Discrete triangular 256, 512, 1024 |         15        |
| 4    | Search |           1024           |        Discrete weighted *         |         30        |

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
