//
// Created by John on 7/22/2024.
//

#include "EdgeUndirected.hpp"
#include "Vertex.hpp"
#include "Graph.hpp"
#include <cassert>

EdgeUndirected::EdgeUndirected(Vertex* a, Vertex* b, const std::map<std::string, std::string>& attributes)
        : Edge(attributes), a(a), b(b) {
    if (a->getGraph() != b->getGraph()) {
        throw std::invalid_argument("Vertices have to be within the same graph");
    }

    a->getGraph()->addEdge(this);
    a->addEdge(this);
    b->addEdge(this);
}

std::vector<const Vertex*> EdgeUndirected::getVerticesTarget() const {
    return {b, a};
}

std::vector<const Vertex*> EdgeUndirected::getVerticesStart() const {
    return {a, b};
}

std::vector<const Vertex*> EdgeUndirected::getVertices() const {
    return {a, b};
}

bool EdgeUndirected::isConnection(const Vertex* from, const Vertex* to) const {
    return ((a == from && b == to) || (b == from && a == to));
}

bool EdgeUndirected::isLoop() const {
    return (a == b);
}

const Vertex* EdgeUndirected::getVertexToFrom(const Vertex* startVertex) const {
    if (a == startVertex) {
        return b;
    } else if (b == startVertex) {
        return a;
    } else {
        throw std::invalid_argument("Invalid start vertex");
    }
}

const Vertex* EdgeUndirected::getVertexFromTo(const Vertex* endVertex) const {
    if (a == endVertex) {
        return b;
    } else if (b == endVertex) {
        return a;
    } else {
        throw std::invalid_argument("Invalid end vertex");
    }
}

bool EdgeUndirected::hasVertexStart(const Vertex* startVertex) const {
    return (a == startVertex || b == startVertex);
}

bool EdgeUndirected::hasVertexTarget(const Vertex* targetVertex) const {
    return hasVertexStart(targetVertex);
}
