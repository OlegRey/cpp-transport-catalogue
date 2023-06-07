#include "stat_reader.h"

#include <iomanip>

namespace bus_catalog {

    void ProcessRequests(TransportCatalogue& catalogue) { //v3
        size_t requests_count;
        std::cin >> requests_count;
        for (size_t i = 0; i < requests_count; ++i) {
            std::string keyword, line;
            std::cin >> keyword;
            std::getline(std::cin, line);
            if (keyword == "Bus") {
                PrintRoute(line, catalogue);
            }
            if (keyword == "Stop") {
                PrintStop(line, catalogue);
            }
        }
    }

    void PrintRoute(std::string& line, TransportCatalogue& catalogue) { //v3
        std::string route_number = line.substr(1, line.npos);
        if (catalogue.FindRoute(route_number)) {
            std::cout << "Bus " << route_number << ": " << catalogue.RouteInformation(route_number).stops_count << " stops on route, "
                << catalogue.RouteInformation(route_number).unique_stops_count << " unique stops, " << std::setprecision(6)
                << catalogue.RouteInformation(route_number).route_length << " route length, "
                << catalogue.RouteInformation(route_number).curvature << " curvature\n";
        }
        else {
            std::cout << "Bus " << route_number << ": not found\n";
        }
    }

    void PrintStop(std::string& line, TransportCatalogue& catalogue) { //v3
        std::string stop_name = line.substr(1, line.npos);
        if (catalogue.FindStop(stop_name)) {
            std::cout << "Stop " << stop_name << ": ";
            std::set<std::string> buses = catalogue.GetBusesOnStop(stop_name);
            if (!buses.empty()) {
                std::cout << "buses ";
                for (const auto& bus : buses) {
                    std::cout << bus << " ";
                }
                std::cout << "\n";
            }
            else {
                std::cout << "no buses\n";
            }
        }
        else {
            std::cout << "Stop " << stop_name << ": not found\n";
        }
    }
}

//void ProcessRequests(std::ostream& out, TransportCatalogue& catalogue) { //v2
//    size_t requests_count;
//    std::cin >> requests_count;
//    for (size_t i = 0; i < requests_count; ++i) {
//     
//        //std::string line; //v1
//        std::string keyword, line;//v2
//        //std::cin >> line; //v1
//        std::cin >> keyword;//v2
//        //if (line.empty()) break; //v1
//        std::getline(std::cin, line);
//        if (keyword == "Bus") { //v2
//            std::string route_number = line.substr(1, line.npos);
//            if (catalogue.FindRoute(route_number)) {
//                out << "Bus " << route_number << ": " << catalogue.RouteInformation(route_number).stops_count << " stops on route, "
//                    << catalogue.RouteInformation(route_number).unique_stops_count << " unique stops, " << std::setprecision(6)
//                    << catalogue.RouteInformation(route_number).route_length << " route length\n";
//            }
//            else {
//                out << "Bus " << route_number << ": not found\n";
//            }
//        }
//        if (keyword == "Stop") { //v2
//            std::string stop_name = line.substr(1, line.npos);
//            if (catalogue.FindStop(stop_name)) {
//                out << "Stop " << stop_name << ": ";
//                std::set<std::string> buses = catalogue.GetBusesOnStop(stop_name);
//                if (!buses.empty()) {
//                    out << "buses ";
//                    for (const auto& bus : buses) {
//                        out << bus << " ";
//                    }
//                    out << "\n";
//                }
//                else {
//                    out << "no buses\n";
//                }
//            }
//            else {
//                out << "Stop " << stop_name << ": not found\n";
//            }
//        }
//    }
//}


