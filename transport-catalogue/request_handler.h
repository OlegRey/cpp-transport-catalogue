#pragma once

#include "transport_catalogue.h"
#include "map_renderer.h"
#include "json_builder.h"
#include "transport_router.h"

using namespace bus_catalog;
using namespace map_renderer;
using namespace bus_catalog::detail::json;
using namespace bus_catalog::detail::json::builder;
using namespace bus_catalog::detail::router;

namespace request_handler {

    class RequestHandler {
    public:

        RequestHandler() = default;

        std::optional<RouteInfo> GetRouteInfo(std::string_view start,
            std::string_view end,
            TransportCatalogue& catalogue,
            TransportRouter& routing) const;

        std::vector<geo::Coordinates> GetStopsCoordinates(TransportCatalogue& catalogue_) const;
        std::vector<std::string_view> GetSortBusesNames(TransportCatalogue& catalogue_) const;

        BusQueryResult BusQuery(TransportCatalogue& catalogue, std::string_view str);
        StopQueryResult StopQuery(TransportCatalogue& catalogue, std::string_view stop_name);

        Node ExecuteMakeNodeStop(int id_request, const StopQueryResult& query_result);
        Node ExecuteMakeNodeBus(int id_request, const BusQueryResult& query_result);
        Node ExecuteMakeNodeMap(int id_request, TransportCatalogue& catalogue, RenderSettings render_settings);
        Node ExecuteMakeNodeRoute(StatRequest& request, TransportCatalogue& catalogue, TransportRouter& routing);

        void ExecuteQueries(TransportCatalogue& catalogue,
            std::vector<StatRequest>& stat_requests,
            RenderSettings& render_settings,
            RoutingSettings& route_settings);

        void ExecuteRenderMap(MapRenderer& map_catalogue, TransportCatalogue& catalogue_) const;

        const Document& GetDocument();

    private:
        Document doc_out;
    };

}