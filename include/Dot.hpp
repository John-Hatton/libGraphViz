//
// Created by John on 7/23/2024.
//
#include "GraphViz.hpp"
#include <string>

#ifndef LIBGRAPHVIZ_DOT_HPP
#define LIBGRAPHVIZ_DOT_HPP


class Dot {
public:
    Dot(GraphViz* graphviz = nullptr);
    std::string getOutput(Graph* graph) const;

private:
    std::string createScript(Graph* graph) const;
    std::string escape(const std::string& id) const;
    std::string escapeAttributes(const std::map<std::string, std::string>& attrs) const;
    std::map<std::string, std::string> getAttributesPrefixed(Entity* entity, const std::string& prefix) const;
    std::map<std::string, std::string> getLayoutVertex(Vertex* vertex, int vid) const;
    std::map<std::string, std::string> getLayoutEdge(Edge* edge) const;

    GraphViz* graphviz;
};

#endif //LIBGRAPHVIZ_DOT_HPP
