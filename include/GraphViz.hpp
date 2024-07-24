//
// Created by John on 7/22/2024.
//

#include "Graph.hpp"
#include <string>
#include <map>

#ifndef LIBGRAPHVIZ_GRAPHVIZ_HPP
#define LIBGRAPHVIZ_GRAPHVIZ_HPP

class Dot;
class Image;

//class GraphViz {
//public:
//    GraphViz();
//    void setFormat(const std::string& format);
//    std::string getFormat() const;
//    void display(Graph* graph);
//    std::string createImageData(Graph* graph);
//    std::string createImageSrc(Graph* graph);
//    std::string createImageHtml(Graph* graph);
//    std::string createScript(Graph* graph);
//    std::string escape(const std::string& id) const;
//    std::string escapeAttributes(const std::map<std::string, std::string>& attrs) const;
//    std::map<std::string, std::string> getAttributesPrefixed(Entity* entity, const std::string& prefix) const;
//    std::map<std::string, std::string> getLayoutVertex(Vertex* vertex, int vid) const;
//    std::map<std::string, std::string> getLayoutEdge(Edge* edge) const;
//
//private:
//    std::string format;
//    std::string formatIndent;
//    std::string attributeFlow;
//    std::string attributeCapacity;
//    std::string attributeWeight;
//    std::string attributeGroup;
//    std::string attributeBalance;
//
//    static const std::string EOL;
//    static const double DELAY_OPEN;
//
//    static std::string base64_encode(const std::string &in);
//};


class GraphViz {
public:
    GraphViz();
    ~GraphViz();

    void setFormat(const std::string& format);
    std::string createScript(Graph* graph) const;
    std::string createImageData(Graph* graph) const;
    std::string createImageSrc(Graph* graph) const;
    std::string createImageHtml(Graph* graph) const;
    void display(Graph* graph) const;

    static const std::string EOL;
    static constexpr double DELAY_OPEN = 2.0;  // Added DELAY_OPEN constant

    std::string formatIndent;
    std::string attributeBalance;
    std::string attributeFlow;
    std::string attributeCapacity;
    std::string attributeWeight;
private:
    std::string format;
    std::string attributeGroup;

    Dot* dot;
    Image* image;

    std::string base64_encode(const std::string &in) const;
};

#endif //LIBGRAPHVIZ_GRAPHVIZ_HPP
