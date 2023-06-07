#pragma once

//#include "geo.h"
#include "transport_catalogue.h"

#include <iostream>

namespace bus_catalog {
	//void FillTransportCatalogue(std::istream& in, TransportCatalogue& catalogue); //v2
	//std::pair<std::vector<std::string>, bool> FillRoute(std::string& line);

	void FillTransportCatalogue(TransportCatalogue& catalogue); //v3
	Bus FillRoute(std::string& line);
	Stop FillStop(std::string& line);
	void AddStopDistances(std::string& line, TransportCatalogue& catalogue);
}