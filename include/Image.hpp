//
// Created by John on 7/24/2024.
//
#include "GraphViz.hpp"

#ifndef LIBGRAPHVIZ_IMAGE_HPP
#define LIBGRAPHVIZ_IMAGE_HPP


class Image {
public:
    Image(GraphViz* graphviz = nullptr);
    ~Image();
    std::string getOutput(Graph* graph) const;
    Image& setFormat(const std::string& type);

private:
    GraphViz* graphviz;
    bool ownGraphviz;
};

#endif //LIBGRAPHVIZ_IMAGE_HPP
