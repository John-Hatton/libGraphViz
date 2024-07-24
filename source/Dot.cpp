//
// Created by John on 7/23/2024.
//

#include "Dot.hpp"
#include "GraphViz.hpp"
#include "EdgeDirected.hpp"
#include "EdgeUndirected.hpp"
#include "Vertex.hpp"
#include <sstream>
#include <regex>

Dot::Dot(GraphViz* graphviz)
        : graphviz(graphviz) {}

std::string Dot::getOutput(Graph* graph) const {
    return createScript(graph);
}

std::string Dot::createScript(Graph* graph) const {
    bool hasDirectedEdges = false;
    for (const auto& edge : graph->getEdges()) {
        if (dynamic_cast<EdgeDirected*>(edge) != nullptr) {
            hasDirectedEdges = true;
            break;
        }
    }

    std::string name = graph->getAttribute("graphviz.name");
    if (!name.empty()) {
        name = escape(name) + " ";
    }

    std::stringstream ss;
    ss << (hasDirectedEdges ? "di" : "") << "graph " << name << "{" << GraphViz::EOL;

    std::string script = ss.str();

    for (const std::string& key : {"graph", "node", "edge"}) {
        auto layout = getAttributesPrefixed(graph, "graphviz." + key + ".");
        if (!layout.empty()) {
            script += graphviz->formatIndent + key + " " + escapeAttributes(layout) + GraphViz::EOL;
        }
    }

    int tid = 0;
    std::map<std::string, int> vids;
    std::map<int, std::vector<Vertex*>> groups;

    for (const auto& vertex : graph->getVertices()) {
        int group = std::stoi(vertex->getAttribute("group", "0"));
        groups[group].push_back(vertex);

        std::string id = vertex->getAttribute("id");
        if (id.empty()) {
            id = std::to_string(++tid);
        }

        vids[std::to_string(reinterpret_cast<uintptr_t>(vertex))] = std::stoi(id);
    }

    if (groups.size() > 1) {
        int gid = 0;
        for (const auto& group : groups) {
            script += graphviz->formatIndent + "subgraph cluster_" + std::to_string(gid++) + " {" + GraphViz::EOL;
            script += graphviz->formatIndent + graphviz->formatIndent + "label = " + escape(std::to_string(group.first)) + GraphViz::EOL;
            for (const auto& vertex : group.second) {
                int vid = vids[std::to_string(reinterpret_cast<uintptr_t>(vertex))];
                auto layout = getLayoutVertex(vertex, vid);

                script += graphviz->formatIndent + graphviz->formatIndent + escape(std::to_string(vid));
                if (!layout.empty()) {
                    script += " " + escapeAttributes(layout);
                }
                script += GraphViz::EOL;
            }
            script += graphviz->formatIndent + "}" + GraphViz::EOL;
        }
    } else {
        for (const auto& vertex : graph->getVertices()) {
            int vid = vids[std::to_string(reinterpret_cast<uintptr_t>(vertex))];
            auto layout = getLayoutVertex(vertex, vid);

            if (!layout.empty() || vertex->getEdges().empty()) {
                script += graphviz->formatIndent + escape(std::to_string(vid));
                if (!layout.empty()) {
                    script += " " + escapeAttributes(layout);
                }
                script += GraphViz::EOL;
            }
        }
    }

    std::string edgeop = hasDirectedEdges ? " -> " : " -- ";

    for (const auto& edge : graph->getEdges()) {
        auto vertices = edge->getVertices();
        script += graphviz->formatIndent + escape(std::to_string(vids[std::to_string(reinterpret_cast<uintptr_t>(vertices[0]))])) + edgeop + escape(std::to_string(vids[std::to_string(reinterpret_cast<uintptr_t>(vertices[1]))]));

        auto layout = getLayoutEdge(edge);

        if (hasDirectedEdges && dynamic_cast<EdgeDirected*>(edge) == nullptr) {
            layout["dir"] = "none";
        }
        if (!layout.empty()) {
            script += " " + escapeAttributes(layout);
        }

        script += GraphViz::EOL;
    }
    script += "}" + GraphViz::EOL;

    return script;
}

std::string Dot::escape(const std::string& id) const {
    if (std::regex_match(id, std::regex("^(?:-?(?:\\.\\d+|\\d+(?:\\.\\d+)?))$"))) {
        return id;
    }

    std::string escaped = id;
    std::string::size_type pos = 0;
    while ((pos = escaped.find('&', pos)) != std::string::npos) { escaped.replace(pos, 1, "&amp;"); pos += 5; }
    pos = 0;
    while ((pos = escaped.find('<', pos)) != std::string::npos) { escaped.replace(pos, 1, "&lt;"); pos += 4; }
    pos = 0;
    while ((pos = escaped.find('>', pos)) != std::string::npos) { escaped.replace(pos, 1, "&gt;"); pos += 4; }
    pos = 0;
    while ((pos = escaped.find('"', pos)) != std::string::npos) { escaped.replace(pos, 1, "&quot;"); pos += 6; }
    pos = 0;
    while ((pos = escaped.find('\'', pos)) != std::string::npos) { escaped.replace(pos, 1, "&apos;"); pos += 6; }
    pos = 0;
    while ((pos = escaped.find('\\', pos)) != std::string::npos) { escaped.replace(pos, 1, "\\\\"); pos += 2; }
    pos = 0;
    while ((pos = escaped.find('\n', pos)) != std::string::npos) { escaped.replace(pos, 1, "\\l"); pos += 2; }

    return "\"" + escaped + "\"";
}

std::string Dot::escapeAttributes(const std::map<std::string, std::string>& attrs) const {
    std::string script = "[";
    bool first = true;
    for (const auto& attr : attrs) {
        if (!first) {
            script += " ";
        } else {
            first = false;
        }

        std::string name = attr.first;
        std::string value = attr.second;

        if (name.length() > 5 && name.substr(name.length() - 5) == "_html") {
            name = name.substr(0, name.length() - 5);
            value = "<" + value + ">";
        } else if (name.length() > 7 && name.substr(name.length() - 7) == "_record") {
            name = name.substr(0, name.length() - 7);
            value = "\"" + std::regex_replace(value, std::regex("\""), "\\\"") + "\"";
        } else {
            value = escape(value);
        }

        script += name + "=" + value;
    }
    script += "]";

    return script;
}

std::map<std::string, std::string> Dot::getAttributesPrefixed(Entity* entity, const std::string& prefix) const {
    std::map<std::string, std::string> attributes;
    for (const auto& attr : entity->getAttributes()) {
        if (attr.first.find(prefix) == 0) {
            attributes[attr.first.substr(prefix.length())] = attr.second;
        }
    }
    return attributes;
}

std::map<std::string, std::string> Dot::getLayoutVertex(Vertex* vertex, int vid) const {
    auto layout = getAttributesPrefixed(vertex, "graphviz.");

    std::string balance = vertex->getAttribute(graphviz->attributeBalance);
    if (!balance.empty()) {
        if (std::stoi(balance) > 0) {
            balance = "+" + balance;
        }
        if (layout.find("label") == layout.end()) {
            layout["label"] = std::to_string(vid);
        }
        layout["label"] += " (" + balance + ")";
    }

    return layout;
}

std::map<std::string, std::string> Dot::getLayoutEdge(Edge* edge) const {
    auto layout = getAttributesPrefixed(edge, "graphviz.");

    std::string label;

    std::string flow = edge->getAttribute(graphviz->attributeFlow);
    std::string capacity = edge->getAttribute(graphviz->attributeCapacity);
    if (!flow.empty()) {
        label = flow + "/" + (capacity.empty() ? "∞" : capacity);
    } else if (!capacity.empty()) {
        label = "0/" + capacity;
    }

    std::string weight = edge->getAttribute(graphviz->attributeWeight);
    if (!weight.empty()) {
        if (!label.empty()) {
            label += "/" + weight;
        } else {
            label = weight;
        }
    }

    if (!label.empty()) {
        if (layout.find("label") != layout.end()) {
            layout["label"] += " " + label;
        } else {
            layout["label"] = label;
        }
    }

    return layout;
}
