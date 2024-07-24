//
// Created by John on 7/22/2024.
//

#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "EdgeDirected.hpp"
#include "EdgeUndirected.hpp"
#include <algorithm>
#include <stdexcept>
#include <map>

Graph::Graph() {}

Graph::Graph(const std::map<std::string, std::string>& attributes) {
    this->attributes = attributes;
}

std::vector<Vertex*> Graph::getVertices() const {
    return vertices;
}

std::vector<Edge*> Graph::getEdges() const {
    return edges;
}

Vertex* Graph::createVertex(const std::map<std::string, std::string>& attributes) {
    Vertex* vertex = new Vertex(this, attributes);
    return vertex;
}

EdgeUndirected* Graph::createEdgeUndirected(Vertex* a, Vertex* b, const std::map<std::string, std::string>& attributes) {
    if (a->getGraph() != this) {
        throw std::invalid_argument("Vertices have to be within this graph");
    }
    EdgeUndirected* edge = new EdgeUndirected(a, b, attributes);
    addEdge(edge);
    return edge;
}

EdgeDirected* Graph::createEdgeDirected(Vertex* source, Vertex* target, const std::map<std::string, std::string>& attributes) {
    if (source->getGraph() != this) {
        throw std::invalid_argument("Vertices have to be within this graph");
    }
    EdgeDirected* edge = new EdgeDirected(source, target, attributes);
    return edge;
}

Graph* Graph::withoutVertex(Vertex* vertex) {
    return withoutVertices({vertex});
}

Graph* Graph::withoutVertices(const std::vector<Vertex*>& verticesToRemove) {
    std::vector<Vertex*> originalVertices = vertices;
    std::vector<Edge*> originalEdges = edges;

    for (Vertex* vertex : verticesToRemove) {
        auto it = std::find(vertices.begin(), vertices.end(), vertex);
        if (it != vertices.end()) {
            vertices.erase(it);
            for (Edge* edge : vertex->getEdges()) {
                auto edgeIt = std::find(edges.begin(), edges.end(), edge);
                if (edgeIt != edges.end()) {
                    edges.erase(edgeIt);
                }
            }
        }
    }

    if (vertices.size() == originalVertices.size()) {
        return this;
    }

    Graph* clone = new Graph(*this);
    vertices = originalVertices;
    edges = originalEdges;
    return clone;
}

Graph* Graph::withoutEdge(Edge* edge) {
    return withoutEdges({edge});
}

Graph* Graph::withoutEdges(const std::vector<Edge*>& edgesToRemove) {
    std::vector<Edge*> originalEdges = edges;

    for (Edge* edge : edgesToRemove) {
        auto it = std::find(edges.begin(), edges.end(), edge);
        if (it != edges.end()) {
            edges.erase(it);
        }
    }

    if (edges.size() == originalEdges.size()) {
        return this;
    }

    Graph* clone = new Graph(*this);
    edges = originalEdges;
    return clone;
}

void Graph::addVertex(Vertex* vertex) {
    vertices.push_back(vertex);
}

void Graph::addEdge(Edge* edge) {
    edges.push_back(edge);
}

Graph::Graph(const Graph& other) {
    attributes = other.attributes;
    std::map<const Vertex*, Vertex*> vertexMap;

    for (Vertex* originalVertex : other.vertices) {
        Vertex* newVertex = new Vertex(this, originalVertex->getAttributes());
        vertices.push_back(newVertex);
        vertexMap[originalVertex] = newVertex;
    }

    for (Edge* originalEdge : other.edges) {
        auto vertexList = originalEdge->getVertices();
        const Vertex* v1_const = vertexList[0];
        const Vertex* v2_const = vertexList[1];
        Vertex* v1 = vertexMap[v1_const];
        Vertex* v2 = vertexMap[v2_const];
        if (dynamic_cast<EdgeUndirected*>(originalEdge)) {
            createEdgeUndirected(v1, v2, originalEdge->getAttributes());
        } else {
            createEdgeDirected(v1, v2, originalEdge->getAttributes());
        }
    }
}
