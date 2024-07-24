//
// Created by John on 7/22/2024.
//
#include "Edge.hpp"

#ifndef LIBGRAPH_EDGEDIRECTED_HPP
#define LIBGRAPH_EDGEDIRECTED_HPP

class EdgeDirected : public Edge {
public:
    EdgeDirected(Vertex* from, Vertex* to, const std::map<std::string, std::string>& attributes = {});

    std::vector<const Vertex*> getVerticesTarget() const override;
    std::vector<const Vertex*> getVerticesStart() const override;
    std::vector<const Vertex*> getVertices() const override;

    const Vertex* getVertexEnd() const;
    const Vertex* getVertexStart() const;

    bool isConnection(const Vertex* from, const Vertex* to) const override;
    bool isLoop() const override;
    const Vertex* getVertexToFrom(const Vertex* startVertex) const override;
    const Vertex* getVertexFromTo(const Vertex* endVertex) const override;
    bool hasVertexStart(const Vertex* startVertex) const override;
    bool hasVertexTarget(const Vertex* targetVertex) const override;

private:
    Vertex* from;
    Vertex* to;
};

#endif //LIBGRAPH_EDGEDIRECTED_HPP
