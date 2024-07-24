//
// Created by John on 7/22/2024.
//
#include "Edge.hpp"

#ifndef LIBGRAPH_EDGEUNDIRECTED_HPP
#define LIBGRAPH_EDGEUNDIRECTED_HPP

class EdgeUndirected : public Edge {
public:
    EdgeUndirected(Vertex* a, Vertex* b, const std::map<std::string, std::string>& attributes = {});

    std::vector<const Vertex*> getVerticesTarget() const override;
    std::vector<const Vertex*> getVerticesStart() const override;
    std::vector<const Vertex*> getVertices() const override;

    bool isConnection(const Vertex* from, const Vertex* to) const override;
    bool isLoop() const override;
    const Vertex* getVertexToFrom(const Vertex* startVertex) const override;
    const Vertex* getVertexFromTo(const Vertex* endVertex) const override;
    bool hasVertexStart(const Vertex* startVertex) const override;
    bool hasVertexTarget(const Vertex* targetVertex) const override;

private:
    Vertex* a;
    Vertex* b;
};

#endif //LIBGRAPH_EDGEUNDIRECTED_HPP
