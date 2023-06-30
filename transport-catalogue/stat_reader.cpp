#include "stat_reader.h" 

#include <iomanip> 

namespace bus_catalog {
    void ProcessRequests(TransportCatalogue& catalogue, std::istream& input, std::ostream& output) {
        size_t requests_count;
        input >> requests_count;
        for (size_t i = 0; i < requests_count; ++i) {
            std::string keyword, line;
            input >> keyword;
            std::getline(input, line);
            if (keyword == "Bus") {
                PrintRoute(line, catalogue, output);
            }
            if (keyword == "Stop") {
                PrintStop(line, catalogue, output);
            }
        }
    }
    void PrintRoute(std::string& line, TransportCatalogue& catalogue, std::ostream& output) {
        std::string route_number = line.substr(1, line.npos);
        if (catalogue.FindRoute(route_number)) {
            output << "Bus " << route_number << ": " << catalogue.RouteInformation(route_number).stops_count << " stops on route, "
                << catalogue.RouteInformation(route_number).unique_stops_count << " unique stops, " << std::setprecision(6)
                << catalogue.RouteInformation(route_number).route_length << " route length, "
                << catalogue.RouteInformation(route_number).curvature << " curvature\n";
        }
        else {
            output << "Bus " << route_number << ": not found\n";
        }
    }
    void PrintStop(std::string& line, TransportCatalogue& catalogue, std::ostream& output) {
        std::string stop_name = line.substr(1, line.npos);
        if (catalogue.FindStop(stop_name)) {
            output << "Stop " << stop_name << ": ";
            std::set<std::string> buses = catalogue.GetBusesOnStop(stop_name);
            if (!buses.empty()) {
                output << "buses ";
                for (const auto& bus : buses) {
                    output << bus << " ";
                }
                output << "\n";
            }
            else {
                output << "no buses\n";
            }
        }
        else {
            output << "Stop " << stop_name << ": not found\n";
        }
    }
}