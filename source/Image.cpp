//
// Created by John on 7/24/2024.
//

#include "Image.hpp"

Image::Image(GraphViz* graphviz) : graphviz(graphviz), ownGraphviz(false) {
    if (graphviz == nullptr) {
        this->graphviz = new GraphViz();
        this->graphviz->setFormat("png");
        ownGraphviz = true;
    }
}

Image::~Image() {
    if (ownGraphviz) {
        delete graphviz;
    }
}

std::string Image::getOutput(Graph* graph) const {
    return graphviz->createImageData(graph);
}

Image& Image::setFormat(const std::string& type) {
    graphviz->setFormat(type);
    return *this;
}