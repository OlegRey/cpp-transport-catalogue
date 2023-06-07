#include "stat_reader.h"
#include "input_reader.h"

int main() {
    bus_catalog::TransportCatalogue catalogue;
    //FillTransportCatalogue(std::cin, catalogue); //v2
    //ProcessRequests(std::cout, catalogue); //v2

    bus_catalog::FillTransportCatalogue( catalogue); //v3
    bus_catalog::ProcessRequests( catalogue);//v3
}