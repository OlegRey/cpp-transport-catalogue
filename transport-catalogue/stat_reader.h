#pragma once 

#include "transport_catalogue.h" 

namespace bus_catalog {
    void ProcessRequests(TransportCatalogue& catalogue, std::istream& input, std::ostream& output);
    void PrintRoute(std::string& line, TransportCatalogue& catalogue, std::ostream& output);
    void PrintStop(std::string& line, TransportCatalogue& catalogue, std::ostream& output);
}