#include "input_reader.h"


namespace bus_catalog {

    void FillTransportCatalogue(TransportCatalogue& catalogue) { //v3
        std::vector<std::string> query_bus;
        std::vector<std::string> query_stop;
        std::vector<std::string> query_stop_distances;
        size_t requests_count;

        std::cin >> requests_count;
        for (size_t i = 0; i < requests_count; ++i) {
            std::string keyword, line;
            std::cin >> keyword;
            std::getline(std::cin, line);
            if (keyword == "Stop") {
                query_stop.push_back(line);
            }
            if (keyword == "Bus") {
                query_bus.push_back(line);
            }
        }
        query_stop_distances = query_stop;
        for (auto& stop_ : query_stop) {
            Stop stop = FillStop(stop_);
            catalogue.AddStop(stop);
        }
        for (auto& stop_ : query_stop_distances) {
            AddStopDistances(stop_, catalogue);
        }
        for (auto& bus_ : query_bus) {
            Bus bus = FillRoute(bus_);
            catalogue.AddRoute(bus);
            bus = {};
        }
    }

  
    Bus FillRoute(std::string& line) { //v3
        Bus bus;
        std::vector<std::string> route_stops;
        std::string route_number = line.substr(1, line.find_first_of(':') - 1);
        line.erase(0, line.find_first_of(':') + 2);
        bool circular_route = false;
        std::string stop_name;
        auto pos = line.find('>') != line.npos ? '>' : '-';
        while (line.find(pos) != line.npos) {
            stop_name = line.substr(0, line.find_first_of(pos) - 1);
            route_stops.push_back(stop_name);
            line.erase(0, line.find_first_of(pos) + 2);
        }
        stop_name = line.substr(0, line.npos - 1);
        route_stops.push_back(stop_name);
        if (pos == '>') circular_route = true;

        bus.number = route_number;
        bus.stops = route_stops;
        bus.circular_route = circular_route;

        return bus;
    }

    Stop FillStop(std::string& line) { //v3
        Stop stop;
        std::string stop_name = line.substr(1, line.find_first_of(':') - line.find_first_of(' ') - 1);
        double lat = std::stod(line.substr(line.find_first_of(':') + 2, line.find_first_of(',') - 1));
        double lng;
        line.erase(0, line.find_first_of(',') + 2);
        if (line.find_last_of(',') == line.npos) {
            lng = std::stod(line.substr(0, line.npos - 1));
            line.clear();
        }
        else {
            lng = std::stod(line.substr(0, line.find_first_of(',')));
            line.erase(0, line.find_first_of(',') + 2);
        }
        geo::Coordinates stop_coordinates = { lat, lng };

        stop.name = stop_name;
        stop.coordinates = stop_coordinates;
        stop.buses = {};

        return stop;
    }

    void AddStopDistances(std::string& line, TransportCatalogue& catalogue) { //v3
        if (!line.empty()) {
            std::string stop_from_name = FillStop(line).name;
            Stop* from = catalogue.FindStop(stop_from_name);

            while (!line.empty()) {
                int distanse = 0;
                std::string stop_to_name;
                distanse = std::stoi(line.substr(0, line.find_first_of("m to ")));
                line.erase(0, line.find_first_of("m to ") + 5);
                if (line.find("m to ") == line.npos) {
                    stop_to_name = line.substr(0, line.npos - 1);
                    Stop* to = catalogue.FindStop(stop_to_name);
                    catalogue.SetDistance(from, to, distanse);
                    if (!catalogue.FindStop(to->name)->stop_distances.count(from->name)) {
                        catalogue.SetDistance(to, from, distanse);
                    }
                    line.clear();
                }
                else {
                    stop_to_name = line.substr(0, line.find_first_of(','));
                    Stop* to = catalogue.FindStop(stop_to_name);
                    catalogue.SetDistance(from, to, distanse);
                    if (!catalogue.FindStop(to->name)->stop_distances.count(from->name)) {
                        catalogue.SetDistance(to, from, distanse);
                    }
                    line.erase(0, line.find_first_of(',') + 2);
                }
            }
        }
    }
}

//#include <string>
//#include <vector>
//#include <cmath>

//void FillTransportCatalogue(std::istream& in, TransportCatalogue& catalogue) { //v2
//    std::vector<std::string> query_bus; //v2
//
//    size_t requests_count;
//    in >> requests_count;
//    for (size_t i = 0; i < requests_count; ++i) {
//        std::string keyword, line;
//        in >> keyword;
//        if (keyword == "Stop") {
//             std::getline(in, line);
//
//            std::string stop_name = line.substr(1, line.find_first_of(':') - line.find_first_of(' ') - 1);
//            double lat = std::stod(line.substr(line.find_first_of(':') + 2, 9));
//            double lng = std::stod(line.substr(line.find_first_of(',') + 2, 9));
//            Coordinates stop_coordinates = { lat, lng };
//            catalogue.AddStop(stop_name, stop_coordinates);
//        }
//        /*else if (keyword == "Bus") { //v1
//            std::string route_number = line.substr(1, line.find_first_of(':') - 1);
//            line.erase(0, line.find_first_of(':') + 2);
//            auto [route_stops, circular_route] = FillRoute(line);
//            catalogue.AddRoute(route_number, route_stops, circular_route);
//            route_stops.clear();
//        }*/
//        if (keyword == "Bus") { //v2
//            std::getline(in, line);
//            query_bus.push_back(line);
//        }
//    }
//
//    for (auto& bus_ : query_bus) { //v2
//        std::string route_number = bus_.substr(1, bus_.find_first_of(':') - 1);
//        bus_.erase(0, bus_.find_first_of(':') + 2);
//        auto [route_stops, circular_route] = FillRoute(bus_);
//        catalogue.AddRoute(route_number, route_stops, circular_route);
//        route_stops.clear();
//    }
//}

//std::pair<std::vector<std::string>, bool> FillRoute(std::string& line) { //v2
    //    std::vector<std::string> route_stops;
    //    bool circular_route = false;
    //    std::string stop_name;
    //    auto pos = line.find('>') != line.npos ? '>' : '-'; //r
    //    while (line.find(pos) != line.npos) {
    //        stop_name = line.substr(0, line.find_first_of(pos) - 1);
    //        route_stops.push_back(stop_name);
    //        line.erase(0, line.find_first_of(pos) + 2);
    //    }
    //    stop_name = line.substr(0, line.npos - 1);
    //    route_stops.push_back(stop_name);
    //    if (pos == '>') circular_route = true;
    //
    //    return std::make_pair(route_stops, circular_route);
    //}
