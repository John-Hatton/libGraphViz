//
// Created by John on 7/22/2024.
//
#include "Entity.hpp"
#include <vector>
#include <stdexcept>
#include <map>
#include <string>

class Vertex;
class Graph;

#ifndef LIBGRAPH_EDGE_HPP
#define LIBGRAPH_EDGE_HPP

class Edge : public Entity {
public:
    Edge(const std::map<std::string, std::string>& attributes = {});
    virtual ~Edge() = default;

    virtual std::vector<const Vertex*> getVerticesTarget() const = 0;
    virtual std::vector<const Vertex*> getVerticesStart() const = 0;
    virtual bool hasVertexStart(const Vertex* startVertex) const = 0;
    virtual bool hasVertexTarget(const Vertex* targetVertex) const = 0;
    virtual bool isConnection(const Vertex* from, const Vertex* to) const = 0;
    virtual bool isLoop() const = 0;
    virtual const Vertex* getVertexToFrom(const Vertex* startVertex) const = 0;
    virtual const Vertex* getVertexFromTo(const Vertex* endVertex) const = 0;
    virtual std::vector<const Vertex*> getVertices() const = 0;
    Graph* getGraph() const;

protected:
    std::map<std::string, std::string> attributes;

private:
    Edge(const Edge&) = delete;
    Edge& operator=(const Edge&) = delete;
};

#endif //LIBGRAPH_EDGE_HPP
