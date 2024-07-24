//
// Created by John on 7/22/2024.
//
#include "Entity.hpp"
#include <vector>
#include <map>
#include <string>

class Vertex;
class Edge;
class EdgeDirected;
class EdgeUndirected;

#ifndef LIBGRAPH_GRAPH_HPP
#define LIBGRAPH_GRAPH_HPP


class Graph : public Entity {
public:
    Graph();
    Graph(const std::map<std::string, std::string>& attributes);

    std::vector<Vertex*> getVertices() const;
    std::vector<Edge*> getEdges() const;

    Vertex* createVertex(const std::map<std::string, std::string>& attributes = {});
    EdgeUndirected* createEdgeUndirected(Vertex* a, Vertex* b, const std::map<std::string, std::string>& attributes = {});
    EdgeDirected* createEdgeDirected(Vertex* source, Vertex* target, const std::map<std::string, std::string>& attributes = {});

    Graph* withoutVertex(Vertex* vertex);
    Graph* withoutVertices(const std::vector<Vertex*>& vertices);
    Graph* withoutEdge(Edge* edge);
    Graph* withoutEdges(const std::vector<Edge*>& edges);

    void addVertex(Vertex* vertex);
    void addEdge(Edge* edge);

    Graph(const Graph& other);

private:
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;
};


#endif //LIBGRAPH_GRAPH_HPP
