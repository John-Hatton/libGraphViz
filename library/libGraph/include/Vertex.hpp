//
// Created by John on 7/22/2024.
//
#include "Entity.hpp"
#include <vector>
#include <map>
#include <string>

class Edge;
class Graph;

#ifndef LIBGRAPH_VERTEX_HPP
#define LIBGRAPH_VERTEX_HPP

class Vertex : public Entity {
public:
    Vertex(Graph* graph, const std::map<std::string, std::string>& attributes = {});
    Graph* getGraph() const;
    void addEdge(Edge* edge);
    bool hasEdgeTo(const Vertex* vertex) const;
    bool hasEdgeFrom(const Vertex* vertex) const;
    std::vector<Edge*> getEdges() const;
    std::vector<Edge*> getEdgesOut() const;
    std::vector<Edge*> getEdgesIn() const;
    std::vector<Edge*> getEdgesTo(const Vertex* vertex) const;
    std::vector<Edge*> getEdgesFrom(const Vertex* vertex) const;
    std::vector<const Vertex*> getVerticesEdge() const;
    std::vector<const Vertex*> getVerticesEdgeTo() const;
    std::vector<const Vertex*> getVerticesEdgeFrom() const;

private:
    std::vector<Edge*> edges;
    Graph* graph;

    // Disable cloning
    Vertex(const Vertex&) = delete;
    Vertex& operator=(const Vertex&) = delete;
};

#endif //LIBGRAPH_VERTEX_HPP
