System Overview
===============

It is simulated a client-server system.
There are four clients, that send requisitions to the server through a network.
There are four types of requisitions and two processes in the server.
Each process answer two types of requisitions.
Each requisition type has different size, processing time and response size.
After processing, the response is sent back through the network.
The network latency is proportional to both the size of the request/response
being sent and its efficiency,
plus 1ms of additional processing time;
the efficiency is between 60% and 80%, uniformly distributed.

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
-   Minimum, maximum and average response time
-   Count of total entities at current time in the simulation.
