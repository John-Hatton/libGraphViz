//
// Created by John on 7/22/2024.
//
#include "Edge.hpp"
#include "Vertex.hpp"
#include <cassert>

Edge::Edge(const std::map<std::string, std::string>& attributes) : attributes(attributes) {}

Graph* Edge::getGraph() const {
    auto vertices = getVertices();
    if (!vertices.empty()) {
        const Vertex* vertex = vertices.front();
        assert(vertex != nullptr);
        return vertex->getGraph();
    }
    return nullptr;
}