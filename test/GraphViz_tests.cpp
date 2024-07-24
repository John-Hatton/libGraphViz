//
// Created by John on 7/23/2024.
//
#include "gtest/gtest.h"
#include "Graph.hpp"
#include "Vertex.hpp"
#include "EdgeDirected.hpp"
#include "EdgeUndirected.hpp"
#include "GraphViz.hpp"
#include "Dot.hpp"

class GraphVizTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up the graph for testing
        graph = new Graph();
        vertex1 = new Vertex(graph, {{"id", "1"}, {"label", "vertex1"}, {"group", "1"}});
        vertex2 = new Vertex(graph, {{"id", "2"}, {"label", "vertex2"}, {"group", "1"}});
        vertex3 = new Vertex(graph, {{"id", "3"}, {"label", "vertex3"}, {"group", "2"}});

        edge1 = new EdgeDirected(vertex1, vertex2, {{"flow", "10"}, {"capacity", "20"}});
        edge2 = new EdgeUndirected(vertex2, vertex3, {{"weight", "5"}});

        graph->addVertex(vertex1);
        graph->addVertex(vertex2);
        graph->addVertex(vertex3);
        graph->addEdge(edge1);
        graph->addEdge(edge2);

        graphViz = new GraphViz();
    }

    void TearDown() override {
        delete graph;
        delete graphViz;
    }

    Graph* graph;
    Vertex* vertex1;
    Vertex* vertex2;
    Vertex* vertex3;
    Edge* edge1;
    Edge* edge2;
    GraphViz* graphViz;
};

TEST_F(GraphVizTest, CreateScript) {
    Dot dot(graphViz);
    std::string script = dot.getOutput(graph);
    EXPECT_FALSE(script.empty());
    EXPECT_NE(script.find("digraph"), std::string::npos);
    auto thing = script.find("vertex1");

    EXPECT_NE(script.find(thing), std::string::npos);
    EXPECT_NE(script.find("vertex2"), std::string::npos);
    EXPECT_NE(script.find("vertex3"), std::string::npos);
    EXPECT_NE(script.find("10/20"), std::string::npos);
    EXPECT_NE(script.find("5"), std::string::npos);
}

TEST_F(GraphVizTest, Display) {
    EXPECT_NO_THROW(graphViz->display(graph));
}

TEST_F(GraphVizTest, CreateImageHtml) {
    std::string html = graphViz->createImageHtml(graph);
    EXPECT_NE(html.find("<img"), std::string::npos);
}

TEST_F(GraphVizTest, CreateImageSrc) {
    std::string src = graphViz->createImageSrc(graph);
    EXPECT_NE(src.find("data:image/"), std::string::npos);
}
//
//TEST_F(GraphVizTest, SetFormat) {
//    std::string newFormat = "svg";
//    graphViz->setFormat(newFormat);
//    EXPECT_EQ(graphViz->getFormat(), newFormat);
//}
