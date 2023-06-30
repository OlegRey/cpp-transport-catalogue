#include "stat_reader.h" 
#include "input_reader.h" 


int main() {
    bus_catalog::TransportCatalogue catalogue;
    bus_catalog::FillTransportCatalogue(std::cin, catalogue); //заполнить каталог
    bus_catalog::ProcessRequests(catalogue, std::cin, std::cout); //запрос
    
}