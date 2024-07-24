//
// Created by John on 7/22/2024.
//
#include "Vertex.hpp"
#include "Graph.hpp"
#include "Edge.hpp"
#include "EdgeDirected.hpp"
#include "EdgeUndirected.hpp"
#include <algorithm>

Vertex::Vertex(Graph* graph, const std::map<std::string, std::string>& attributes) : graph(graph) {
    this->attributes = attributes;
    graph->addVertex(this);
}

Graph* Vertex::getGraph() const {
    return graph;
}

void Vertex::addEdge(Edge* edge) {
    edges.push_back(edge);
}

bool Vertex::hasEdgeTo(const Vertex* vertex) const {
    return std::any_of(edges.begin(), edges.end(), [this, vertex](Edge* edge) {
        return edge->isConnection(this, vertex);
    });
}

bool Vertex::hasEdgeFrom(const Vertex* vertex) const {
    return vertex->hasEdgeTo(this);
}

std::vector<Edge*> Vertex::getEdges() const {
    return edges;
}

std::vector<Edge*> Vertex::getEdgesOut() const {
    std::vector<Edge*> result;
    Edge* prev = nullptr;

    for (const auto& edge : edges) {
        bool ret = edge->hasVertexStart(this);

        // Skip duplicate directed loop edges
        if (edge == prev && dynamic_cast<EdgeDirected*>(edge) != nullptr) {
            ret = false;
        }
        if (ret) {
            result.push_back(edge);
        }
        prev = edge;
    }

    return result;
}

std::vector<Edge*> Vertex::getEdgesIn() const {
    std::vector<Edge*> result;
    Edge* prev = nullptr;

    for (const auto& edge : edges) {
        bool ret = edge->hasVertexTarget(this);

        // Skip duplicate directed loop edges
        if (edge == prev && dynamic_cast<EdgeDirected*>(edge) != nullptr) {
            ret = false;
        }
        if (ret) {
            result.push_back(edge);
        }
        prev = edge;
    }

    return result;
}

std::vector<Edge*> Vertex::getEdgesTo(const Vertex* vertex) const {
    std::vector<Edge*> result;

    for (const auto& edge : edges) {
        if (edge->isConnection(this, vertex)) {
            result.push_back(edge);
        }
    }

    return result;
}

std::vector<Edge*> Vertex::getEdgesFrom(const Vertex* vertex) const {
    return vertex->getEdgesTo(this);
}

std::vector<const Vertex*> Vertex::getVerticesEdge() const {
    std::vector<const Vertex*> result;

    for (const auto& edge : edges) {
        if (edge->hasVertexStart(this)) {
            result.push_back(edge->getVertexToFrom(this));
        } else {
            result.push_back(edge->getVertexFromTo(this));
        }
    }

    return result;
}

std::vector<const Vertex*> Vertex::getVerticesEdgeTo() const {
    std::vector<const Vertex*> result;

    for (const auto& edge : getEdgesOut()) {
        result.push_back(edge->getVertexToFrom(this));
    }

    return result;
}

std::vector<const Vertex*> Vertex::getVerticesEdgeFrom() const {
    std::vector<const Vertex*> result;

    for (const auto& edge : getEdgesIn()) {
        result.push_back(edge->getVertexFromTo(this));
    }

    return result;
}
