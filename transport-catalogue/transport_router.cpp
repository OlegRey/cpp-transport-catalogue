#include "transport_router.h"

namespace bus_catalog {
    namespace detail {
        namespace router {

            void TransportRouter::SetRoutingSettings(RoutingSettings routing_settings) { routing_settings_ = std::move(routing_settings); }
            const RoutingSettings& TransportRouter::GetRoutingSettings() const { return routing_settings_; }

            void TransportRouter::BuildRouter(TransportCatalogue& transport_catalogue) {
                SetGraph(transport_catalogue);
                router_ = std::make_unique<Router<double>>(*graph_);
                router_->Build();
            }

            const DirectedWeightedGraph<double>& TransportRouter::GetGraph() const { return *graph_; }
            const Router<double>& TransportRouter::GetRouter() const { return *router_; }
            const std::variant<StopEdge, BusEdge>& TransportRouter::GetEdge(EdgeId id) const { return edge_id_to_edge_.at(id); }

            std::optional<RouterByStop> TransportRouter::GetRouterByStop(Stop* stop) const {
                if (stop_to_router_.count(stop)) {
                    return stop_to_router_.at(stop);
                }
                else {
                    return std::nullopt;
                }
            }

            std::optional<RouteInfo> TransportRouter::GetRouteInfo(VertexId start, graph::VertexId end) const {
                const auto& route_info = router_->BuildRoute(start, end);
                if (route_info) {
                    RouteInfo result;
                    result.total_time = route_info->weight;

                    for (const auto edge : route_info->edges) {
                        result.edges.emplace_back(GetEdge(edge));
                    }

                    return result;

                }
                else {
                    return std::nullopt;
                }
            }

            const std::unordered_map<Stop*, RouterByStop>& TransportRouter::GetStopToVertex() const { return stop_to_router_; }
            const std::unordered_map<EdgeId, std::variant<StopEdge, BusEdge>>& TransportRouter::GetEdgeIdToEdge() const { return edge_id_to_edge_; }

            std::deque<Stop*> TransportRouter::GetStopsPtr(TransportCatalogue& transport_catalogue) {
                std::deque<Stop*> stops_ptr;

                for (auto [_, stop_ptr] : transport_catalogue.GetStopNameToStop()) {
                    stops_ptr.push_back(stop_ptr);
                }

                return stops_ptr;
            }

            std::deque<Bus*> TransportRouter::GetBusPtr(TransportCatalogue& transport_catalogue) {
                std::deque<Bus*> buses_ptr;

                for (auto [_, bus_ptr] : transport_catalogue.GetBusNameToBus()) {
                    buses_ptr.push_back(bus_ptr);
                }

                return buses_ptr;
            }

            void TransportRouter::SetStops(const std::deque<Stop*>& stops) {
                size_t i = 0;

                for (const auto stop : stops) {
                    VertexId first = i++;
                    VertexId second = i++;

                    stop_to_router_[stop] = RouterByStop{ first, second };
                }
            }

            void TransportRouter::AddEdgeToStop() {

                for (const auto [stop, num] : stop_to_router_) {
                    EdgeId id = graph_->AddEdge(Edge<double>{num.bus_wait_begin,
                        num.bus_wait_end,
                        routing_settings_.bus_wait_time});

                    edge_id_to_edge_[id] = StopEdge{ stop->name, routing_settings_.bus_wait_time };
                }
            }

            void TransportRouter::AddEdgeToBus(TransportCatalogue& transport_catalogue) {

                for (auto bus : GetBusPtr(transport_catalogue)) {
                    ParseBusToEdges(bus->stops.begin(),
                        bus->stops.end(),
                        transport_catalogue,
                        bus);

                    if (!bus->is_roundtrip) {
                        ParseBusToEdges(bus->stops.rbegin(),
                            bus->stops.rend(),
                            transport_catalogue,
                            bus);
                    }
                }
            }

            void TransportRouter::SetGraph(TransportCatalogue& transport_catalogue) {
                const auto stops_ptr_size = GetStopsPtr(transport_catalogue).size();

                graph_ = std::make_unique<DirectedWeightedGraph<double>>(2 * stops_ptr_size);

                SetStops(GetStopsPtr(transport_catalogue));
                AddEdgeToStop();
                AddEdgeToBus(transport_catalogue);
            }

            Edge<double> TransportRouter::MakeEdgeToBus(Stop* start, Stop* end, const double distance) const {
                Edge<double> result;

                result.from = stop_to_router_.at(start).bus_wait_end;
                result.to = stop_to_router_.at(end).bus_wait_begin;
                result.weight = distance * 1.0 / (routing_settings_.bus_velocity * KILOMETER / HOUR);

                return result;
            }

        }
    }
}