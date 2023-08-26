/*
 * В этом файле вы можете разместить классы/структуры, которые являются частью предметной области (domain)
 * вашего приложения и не зависят от транспортного справочника. Например Автобусные маршруты и Остановки.
 *
 * Их можно было бы разместить и в transport_catalogue.h, однако вынесение их в отдельный
 * заголовочный файл может оказаться полезным, когда дело дойдёт до визуализации карты маршрутов:
 * визуализатор карты (map_renderer) можно будет сделать независящим от транспортного справочника.
 *
 * Если структура вашего приложения не позволяет так сделать, просто оставьте этот файл пустым.
 *
 */

#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <variant>

#include "geo.h"
#include "graph.h"

namespace domain {

    struct StatRequest {
        int id;
        std::string type;
        std::string name;
        std::string from;
        std::string to;
    };

    struct Bus;

    struct Stop {
        std::string name;
        double lat;
        double lng;
        std::vector<Bus*> buses;
    };

    struct Bus {
        std::string name;
        std::vector<Stop*> stops;
        bool is_roundtrip;
        size_t route_length;
    };

    struct Distance {
        const Stop* start;
        const Stop* end;
        int distance;
    };

    struct BusQueryResult {
        std::string_view name;
        bool not_found;
        int stops_on_route;
        int unique_stops;
        int route_length;
        double curvature;
    };

    struct StopQueryResult {
        std::string_view name;
        bool not_found;
        std::vector<std::string> buses_name;
    };

    struct StopEdge {
        std::string_view name;
        double time = 0;
    };

    struct BusEdge {
        std::string_view bus_name;
        size_t span_count = 0;
        double time = 0;
    };

    struct RoutingSettings {
        double bus_wait_time = 0;
        double bus_velocity = 0;
    };

    struct RouterByStop {
        graph::VertexId bus_wait_begin;
        graph::VertexId bus_wait_end;
    };

    struct RouteInfo {
        double total_time = 0.;
        std::vector<std::variant<StopEdge, BusEdge>> edges;
    };

}