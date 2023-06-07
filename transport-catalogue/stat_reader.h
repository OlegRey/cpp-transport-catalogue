#pragma once

#include "transport_catalogue.h"

//#include <iostream>

//void ProcessRequests(std::ostream& out, TransportCatalogue& catalogue); v2

namespace bus_catalog {

	void ProcessRequests(TransportCatalogue& catalogue); //v3
	void PrintRoute(std::string& line, TransportCatalogue& catalogue);
	void PrintStop(std::string& line, TransportCatalogue& catalogue);
}