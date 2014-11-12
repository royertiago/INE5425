/* server.cpp
 * implementation of server.h
 */

 #include "server.h"

 void Server::process( Requisition req ) {
 	requisitions.push(req);
 	req.last_queue_timestamp = Clock::current_time();
 }

 virtual unsigned int next_event() {
 	return requisitions.front().processing_time;
 }