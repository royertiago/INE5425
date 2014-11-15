Developers Manual
=================

This document describes the core of the system, implemented in the files

    client.cpp
    clock.cpp
    measured_resource.cpp
    measurer.cpp
    network.cpp
    random.cpp
    requisition.cpp
    server.cpp

The other two files (main.cpp and user_config.cpp) contains input and output
and are best understood by reading those source files.

This file describes the system without discussing the details of implementation,
such as exact signature and semantics of methods; these are best found reading
each file individually. For each file.cpp, the corresponding documentation
are in file.h.


System Core
===========

To implement the core of the system described in system_overview.md,
four main classes were developed: Client and Server, and the network classes
ServerToClient and ClientToServer. These four classes implements an interface
named EventGenerator, that is used by the clock.cpp file to implement the
time-advancing algorithm.

The Client class generates all requisitions in the system and passes them
to the ClientToServer class. This class multiplexes between each of the Server
process, which in turn, answer the requisitions and return them to the class
ServerToClient. The latter class dispose the objects and compte statistics.


Requisition structure
=====================

The class Requisition, defined in requisition.h, centralizes all the
information needed by the application about a requisition. In particular,
whenever a requisition is generated, (almos) every information about
its passage in the system is known, such as size, processing time in
the server, the server response size, and in which server the requisition
is going to be processed. The only data not generated here is the network
efficiency, that is generated when the requisition arrives one of the
network sides.


Time advancing algorithm
========================

The implemented algorithm is reasonably simple (and somewhat inefficient).
The namespace Clock mantains a list of all EventGenerators of the system.
At each advance, the algorithm iterates over the list to discover the earlier
next event in the program, and advances just the time enough to trigger this
event.

Since each class modifies the others, the order in which the classes are
iterated is relevant; the order is: ServerToClient, Server, ClientToServer,
Client. This way, when some EventGenerator is modified, all the EventGenerators
that depend upon this one are already stable.

To avoid the use of floating-point numbers, all the time measurement is
done in microseconds. This unit was chosen because it is the first unit in the
SI (International System of Units) with more granularity than milisecond,
the unit used to describe the application.


Measurer and MeasuredResource
=============================

These two classes are the only two classes in the program that compute the
statistics. They were thought aiming reuse.

The first one (measurer) merely computes min/avg/max data. It can compute
weighted information about the data entered, and is used by the
MeasuredResource.

The MeasuredResource, in turn, encapsulates processing time and queueing
in a single class, also computing statistics about queue size and response
times.

These classes are used by the four EventGenerators to automate statistics
computing. Since they are at the core of the program, they have specialized
unit tests for them, in subfolder `test/`.


Random number generation
========================

To allow for easier control of the random number generation, there is a single
header responsible for random number generation. The functions in this header
mantains a single random number generator (a Mersenne Twister 19937); since
every other aspect in the system is deterministic, this is the only place
where is needed seeding, thus simplifying the task of allowing for the user
to choose the initial seed.
