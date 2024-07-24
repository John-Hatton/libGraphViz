//
// Created by John on 7/22/2024.
//
#include "EdgeDirected.hpp"
#include "Vertex.hpp"
#include "Graph.hpp"
#include <cassert>

EdgeDirected::EdgeDirected(Vertex* from, Vertex* to, const std::map<std::string, std::string>& attributes)
        : Edge(attributes), from(from), to(to) {
    if (from->getGraph() != to->getGraph()) {
        throw std::invalid_argument("Vertices have to be within the same graph");
    }

    from->getGraph()->addEdge(this);
    from->addEdge(this);
    to->addEdge(this);
}

std::vector<const Vertex*> EdgeDirected::getVerticesTarget() const {
    return {to};
}

std::vector<const Vertex*> EdgeDirected::getVerticesStart() const {
    return {from};
}

std::vector<const Vertex*> EdgeDirected::getVertices() const {
    return {from, to};
}

const Vertex* EdgeDirected::getVertexEnd() const {
    return to;
}

const Vertex* EdgeDirected::getVertexStart() const {
    return from;
}

bool EdgeDirected::isConnection(const Vertex* from, const Vertex* to) const {
    return (this->from == from && this->to == to);
}

bool EdgeDirected::isLoop() const {
    return (from == to);
}

const Vertex* EdgeDirected::getVertexToFrom(const Vertex* startVertex) const {
    if (this->from != startVertex) {
        throw std::invalid_argument("Invalid start vertex");
    }
    return to;
}

const Vertex* EdgeDirected::getVertexFromTo(const Vertex* endVertex) const {
    if (this->to != endVertex) {
        throw std::invalid_argument("Invalid end vertex");
    }
    return from;
}

bool EdgeDirected::hasVertexStart(const Vertex* startVertex) const {
    return (from == startVertex);
}

bool EdgeDirected::hasVertexTarget(const Vertex* targetVertex) const {
    return (to == targetVertex);
}
