#pragma once

#include "geo.h"

#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <optional>
#include <unordered_set>
#include <set>

namespace bus_catalog {

    struct Bus {
        std::string number;
        std::vector<std::string> stops; //v3
        //std::optional<std::vector<std::string>> stops; //v2
        bool circular_route = true;
    };

    struct Stop {
        std::string name;
        geo::Coordinates coordinates;
        std::set<std::string> buses; //v2
        std::unordered_map<std::string, int> stop_distances; //v3
    };

    struct RouteInfo {
        size_t stops_count;
        size_t unique_stops_count;
        double route_length;
        double curvature; //v3
    };

    class TransportCatalogue {
    public:
        //void AddRoute(const std::string& route_number, const std::vector<std::string>& route_stops, bool circular_route); //v2
        void AddRoute(Bus& bus); //v3
        //void AddStop(const std::string& stop_name, Coordinates& coordinates); //v3
        void AddStop(Stop& stop); //v2
        const Bus* FindRoute(const std::string& route_number) const;
        Stop* FindStop(const std::string& stop_name) const;
        const RouteInfo RouteInformation(const std::string& route_number) const;
        size_t UniqueStopsCount(const std::string& route_number) const;
        const std::set<std::string> GetBusesOnStop(const std::string& stop_name) const;//v2
        void SetDistance(Stop* from, Stop* to, int distance); //v3
        int GetDistance(const Stop* from, const Stop* to) const; //v3

    private:
        std::deque<Bus> all_buses_;
        std::deque<Stop> all_stops_;
        std::unordered_map<std::string_view, const Bus*> busname_to_bus_;
        std::unordered_map<std::string_view, Stop*> stopname_to_stop_;

    };
}
