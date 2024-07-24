//
// Created by John on 7/22/2024.
//
#include <vector>
#include <functional>
#include <variant>

class Vertex;
class Edge;
class Graph;

#ifndef LIBGRAPH_WALK_HPP
#define LIBGRAPH_WALK_HPP

class Walk {
public:
    Walk(const std::vector<const Vertex*>& vertices, const std::vector<Edge*>& edges);

    static Walk factoryFromEdges(const std::vector<Edge*>& edges, const Vertex* startVertex);
    static Walk factoryFromVertices(const std::vector<const Vertex*>& vertices, const std::function<int(Edge*)>& orderBy = nullptr, bool desc = false);
    static Walk factoryCycleFromVertices(const std::vector<const Vertex*>& vertices, const std::function<int(Edge*)>& orderBy = nullptr, bool desc = false);
    static Walk factoryCycleFromEdges(const std::vector<Edge*>& edges, const Vertex* startVertex);

    Graph* getGraph() const;
    std::vector<Edge*> getEdges() const;
    std::vector<const Vertex*> getVertices() const;
    std::vector<std::variant<const Vertex*, Edge*>> getAlternatingSequence() const;

private:
    static Edge* pickEdge(const std::vector<Edge*>& edges, const std::function<int(Edge*)>& orderBy, bool desc);

    std::vector<const Vertex*> vertices;
    std::vector<Edge*> edges;
};

#endif //LIBGRAPH_WALK_HPP
