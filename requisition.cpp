/* requisition.cpp
 * Implementation of requisition.h
 */

 #include "server.h"

 static Requisition generate_requisition( unsigned type ) {
 	Requisition req = new Requisition;
 	switch( type ) {
            case 0:
            	req.size = 1024;
            	req.response_size = Random::add_response_size();
            	req.processing_time = 10;
            	//Network efficiency?
            	//Server_process?
            	return req;
            case 1: 
            	req.size = 1024;
            	req.response_size = Random::delete_response_size();
            	req.processing_time = 8;
            	//Network efficiency?
            	//Server_process?
            	return req;
            case 2: 
            	req.size = 256;
            	req.response_size = Random::find_response_size();
            	req.processing_time = 15;
            	//Network efficiency?
            	//Server_process?
            	return req;
            case 3:
            	req.size = 1024;
            	req.response_size = Random::search_response_size();
            	req.processing_time = Random::search_processing_time(); //TODO
            default: return NULL; //TODO
 }

