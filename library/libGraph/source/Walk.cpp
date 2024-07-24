//
// Created by John on 7/22/2024.
//
#include "Walk.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <stdexcept>
#include <limits>
#include <cassert>

Walk::Walk(const std::vector<const Vertex*>& vertices, const std::vector<Edge*>& edges)
        : vertices(vertices), edges(edges) {}

Walk Walk::factoryFromEdges(const std::vector<Edge*>& edges, const Vertex* startVertex) {
    std::vector<const Vertex*> vertices = {startVertex};
    const Vertex* vertexCurrent = startVertex;

    for (Edge* edge : edges) {
        vertexCurrent = edge->getVertexToFrom(vertexCurrent);
        vertices.push_back(vertexCurrent);
    }

    return Walk(vertices, edges);
}

Walk Walk::factoryFromVertices(const std::vector<const Vertex*>& vertices, const std::function<int(Edge*)>& orderBy, bool desc) {
    if (vertices.empty()) {
        throw std::underflow_error("No vertices given");
    }

    std::vector<Edge*> edges;
    const Vertex* last = nullptr;

    for (const Vertex* vertex : vertices) {
        if (last != nullptr) {
            auto connectingEdges = last->getEdgesTo(vertex);
            if (connectingEdges.empty()) {
                throw std::invalid_argument("No connecting edge between consecutive vertices");
            }
            edges.push_back(pickEdge(connectingEdges, orderBy, desc));
        }
        last = vertex;
    }

    return Walk(vertices, edges);
}

Walk Walk::factoryCycleFromVertices(const std::vector<const Vertex*>& vertices, const std::function<int(Edge*)>& orderBy, bool desc) {
    if (vertices.empty()) {
        throw std::underflow_error("No vertices given");
    }

    Walk cycle = factoryFromVertices(vertices, orderBy, desc);

    if (cycle.getEdges().empty()) {
        throw std::invalid_argument("Cycle with no edges cannot exist");
    }

    if (vertices.front() != vertices.back()) {
        throw std::invalid_argument("Cycle has to start and end at the same vertex");
    }

    return cycle;
}

Walk Walk::factoryCycleFromEdges(const std::vector<Edge*>& edges, const Vertex* startVertex) {
    Walk cycle = factoryFromEdges(edges, startVertex);

    std::vector<const Vertex*> vertices = cycle.getVertices();
    if (vertices.back() != startVertex) {
        throw std::invalid_argument("The given array of edges does not represent a cycle");
    }

    return cycle;
}

Edge* Walk::pickEdge(const std::vector<Edge*>& edges, const std::function<int(Edge*)>& orderBy, bool desc) {
    if (edges.empty()) {
        throw std::underflow_error("No edges between two vertices found");
    }

    if (!orderBy) {
        return edges.front();
    }

    Edge* ret = nullptr;
    int best = desc ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (Edge* edge : edges) {
        int now = orderBy(edge);

        if (!ret || (desc && now > best) || (!desc && now < best)) {
            ret = edge;
            best = now;
        }
    }

    return ret;
}

Graph* Walk::getGraph() const {
    if (vertices.empty()) {
        return nullptr;
    }
    return vertices.front()->getGraph();
}

std::vector<Edge*> Walk::getEdges() const {
    return edges;
}

std::vector<const Vertex*> Walk::getVertices() const {
    return vertices;
}

std::vector<std::variant<const Vertex*, Edge*>> Walk::getAlternatingSequence() const {
    std::vector<std::variant<const Vertex*, Edge*>> sequence;
    for (size_t i = 0; i < edges.size(); ++i) {
        sequence.push_back(vertices[i]);
        sequence.push_back(edges[i]);
    }
    sequence.push_back(vertices.back());
    return sequence;
}
