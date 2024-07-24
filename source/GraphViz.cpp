//
// Created by John on 7/22/2024.
//

#include "GraphViz.hpp"
#include "Dot.hpp"
#include "Image.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <regex>
#include <vector>
//
//const double GraphViz::DELAY_OPEN = 2.0;
//const std::string GraphViz::EOL = "\n";
//
//GraphViz::GraphViz()
//        : format("png"),
//          executable("dot"),
//          formatIndent("  "),
//          attributeFlow("flow"),
//          attributeCapacity("capacity"),
//          attributeWeight("weight"),
//          attributeGroup("group"),
//          attributeBalance("balance") {
//#if defined(_WIN32) || defined(_WIN64)
//    executable = "dot.exe";
//#endif
//    dot = new Dot(this);
//    image = new Image(this);
//    ownDot = true;
//    ownImage = true;
//}
//
//GraphViz::~GraphViz() {
//    if (ownDot) {
//        delete dot;
//    }
//    if (ownImage) {
//        delete image;
//    }
//}
//
//void GraphViz::setExecutable(const std::string& executable) {
//    this->executable = executable;
//}
//
//std::string GraphViz::getExecutable() const {
//    return executable;
//}
//
//void GraphViz::setFormat(const std::string& format) {
//    this->format = format;
//    image->setFormat(format);
//}
//
//std::string GraphViz::getFormat() const {
//    return format;
//}
//
//void GraphViz::display(Graph* graph) {
//    std::string tmp = createImageFile(graph);
//
//    static double next = 0;
//    if (next > static_cast<double>(time(nullptr))) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(DELAY_OPEN * 1000)));
//    }
//
//#if defined(_WIN32) || defined(_WIN64)
//    std::string command = "start \"\" " + tmp + " >NUL";
//#elif defined(__APPLE__)
//    std::string command = "open " + tmp + " > /dev/null 2>&1 &";
//#else
//    std::string command = "xdg-open " + tmp + " > /dev/null 2>&1 &";
//#endif
//
//    system(command.c_str());
//
//    next = static_cast<double>(time(nullptr)) + DELAY_OPEN;
//}
//
//std::string GraphViz::createImageData(Graph* graph) {
//    return image->getOutput(graph);
//}
//
//std::string GraphViz::createImageSrc(Graph* graph) {
//    std::string format = this->format;
//    if (format == "svg" || format == "svgz") {
//        format = "svg+xml;charset=UTF-8";
//    }
//    return "data:image/" + format + ";base64," + base64_encode(createImageData(graph));
//}
//
//std::string GraphViz::createImageHtml(Graph* graph) {
//    if (format == "svg" || format == "svgz") {
//        return "<object type=\"image/svg+xml\" data=\"" + createImageSrc(graph) + "\"></object>";
//    }
//    return "<img src=\"" + createImageSrc(graph) + "\" />";
//}
//
//std::string GraphViz::createImageFile(Graph* graph) {
//    std::string script = createScript(graph);
//
//    std::string tmp = std::tmpnam(nullptr);
//    std::ofstream ofs(tmp);
//    ofs << script;
//    ofs.close();
//
//    std::string command = executable + " -T " + format + " " + tmp + " -o " + tmp + "." + format;
//    int ret = system(command.c_str());
//    if (ret != 0) {
//        throw std::runtime_error("Unable to invoke \"" + executable + "\" to create image file (code " + std::to_string(ret) + ")");
//    }
//
//    std::remove(tmp.c_str());
//    return tmp + "." + format;
//}
//
//std::string GraphViz::createScript(Graph* graph) {
//    return dot->getOutput(graph);
//}
//
//std::string GraphViz::escape(const std::string& id) const {
//    if (std::regex_match(id, std::regex("^(?:-?(?:\\.\\d+|\\d+(?:\\.\\d+)?))$"))) {
//        return id;
//    }
//
//    std::string escaped = id;
//    std::string::size_type pos = 0;
//    while ((pos = escaped.find('&', pos)) != std::string::npos) { escaped.replace(pos, 1, "&amp;"); pos += 5; }
//    pos = 0;
//    while ((pos = escaped.find('<', pos)) != std::string::npos) { escaped.replace(pos, 1, "&lt;"); pos += 4; }
//    pos = 0;
//    while ((pos = escaped.find('>', pos)) != std::string::npos) { escaped.replace(pos, 1, "&gt;"); pos += 4; }
//    pos = 0;
//    while ((pos = escaped.find('"', pos)) != std::string::npos) { escaped.replace(pos, 1, "&quot;"); pos += 6; }
//    pos = 0;
//    while ((pos = escaped.find('\'', pos)) != std::string::npos) { escaped.replace(pos, 1, "&apos;"); pos += 6; }
//    pos = 0;
//    while ((pos = escaped.find('\\', pos)) != std::string::npos) { escaped.replace(pos, 1, "\\\\"); pos += 2; }
//    pos = 0;
//    while ((pos = escaped.find('\n', pos)) != std::string::npos) { escaped.replace(pos, 1, "\\l"); pos += 2; }
//
//    return "\"" + escaped + "\"";
//}
//
//std::string GraphViz::escapeAttributes(const std::map<std::string, std::string>& attrs) const {
//    std::string script = "[";
//    bool first = true;
//    for (const auto& attr : attrs) {
//        if (!first) {
//            script += " ";
//        } else {
//            first = false;
//        }
//
//        std::string name = attr.first;
//        std::string value = attr.second;
//
//        if (name.length() > 5 && name.substr(name.length() - 5) == "_html") {
//            name = name.substr(0, name.length() - 5);
//            value = "<" + value + ">";
//        } else if (name.length() > 7 && name.substr(name.length() - 7) == "_record") {
//            name = name.substr(0, name.length() - 7);
//            value = "\"" + std::regex_replace(value, std::regex("\""), "\\\"") + "\"";
//        } else {
//            value = escape(value);
//        }
//
//        script += name + "=" + value;
//    }
//    script += "]";
//
//    return script;
//}
//
//std::map<std::string, std::string> GraphViz::getAttributesPrefixed(Entity* entity, const std::string& prefix) const {
//    std::map<std::string, std::string> attributes;
//    for (const auto& attr : entity->getAttributes()) {
//        if (attr.first.find(prefix) == 0) {
//            attributes[attr.first.substr(prefix.length())] = attr.second;
//        }
//    }
//    return attributes;
//}
//
//std::map<std::string, std::string> GraphViz::getLayoutVertex(Vertex* vertex, int vid) const {
//    auto layout = getAttributesPrefixed(vertex, "graphviz.");
//
//    std::string balance = vertex->getAttribute(attributeBalance);
//    if (!balance.empty()) {
//        if (std::stoi(balance) > 0) {
//            balance = "+" + balance;
//        }
//        if (layout.find("label") == layout.end()) {
//            layout["label"] = std::to_string(vid);
//        }
//        layout["label"] += " (" + balance + ")";
//    }
//
//    return layout;
//}
//
//std::map<std::string, std::string> GraphViz::getLayoutEdge(Edge* edge) const {
//    auto layout = getAttributesPrefixed(edge, "graphviz.");
//
//    std::string label;
//
//    std::string flow = edge->getAttribute(attributeFlow);
//    std::string capacity = edge->getAttribute(attributeCapacity);
//    if (!flow.empty()) {
//        label = flow + "/" + (capacity.empty() ? "∞" : capacity);
//    } else if (!capacity.empty()) {
//        label = "0/" + capacity;
//    }
//
//    std::string weight = edge->getAttribute(attributeWeight);
//    if (!weight.empty()) {
//        if (!label.empty()) {
//            label += "/" + weight;
//        } else {
//            label = weight;
//        }
//    }
//
//    if (!label.empty()) {
//        if (layout.find("label") != layout.end()) {
//            layout["label"] += " " + label;
//        } else {
//            layout["label"] = label;
//        }
//    }
//
//    return layout;
//}
//
//static const std::string base64_chars =
//        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//        "abcdefghijklmnopqrstuvwxyz"
//        "0123456789+/";
//
//
//std::string GraphViz::base64_encode(const std::string &in) {
//    std::string out;
//    int val = 0, valb = -6;
//    for (unsigned char c : in) {
//        val = (val << 8) + c;
//        valb += 8;
//        while (valb >= 0) {
//            out.push_back(base64_chars[(val >> valb) & 0x3F]);
//            valb -= 6;
//        }
//    }
//    if (valb > -6) out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
//    while (out.size() % 4) out.push_back('=');
//    return out;
//}
//
//

#include "GraphViz.hpp"
#include "Dot.hpp"
#include "Image.hpp"

const std::string GraphViz::EOL = "\n"; // Define the EOL constant

GraphViz::GraphViz()
        : format("png"),
          formatIndent("  "),
          attributeFlow("flow"),
          attributeCapacity("capacity"),
          attributeWeight("weight"),
          attributeGroup("group"),
          attributeBalance("balance"),
          dot(new Dot(this)),
          image(new Image(this)) {}

GraphViz::~GraphViz() {
    delete dot;
    delete image;
}

void GraphViz::setFormat(const std::string& format) {
    this->format = format;
    image->setFormat(format);
}

std::string GraphViz::createScript(Graph* graph) const {
    return dot->getOutput(graph);
}

std::string GraphViz::createImageData(Graph* graph) const {
    return image->getOutput(graph);
}

std::string GraphViz::createImageSrc(Graph* graph) const {
    std::string format = this->format;
    if (format == "svg" || format == "svgz") {
        format = "svg+xml;charset=UTF-8"; // Assuming UTF-8
    }
    return "data:image/" + format + ";base64," + base64_encode(createImageData(graph));
}

std::string GraphViz::createImageHtml(Graph* graph) const {
    if (format == "svg" || format == "svgz") {
        return "<object type=\"image/svg+xml\" data=\"" + createImageSrc(graph) + "\"></object>";
    }
    return "<img src=\"" + createImageSrc(graph) + "\" />";
}

void GraphViz::display(Graph* graph) const {
    std::string tmp = createImageData(graph);

    static double next = 0;
    if (next > static_cast<double>(time(nullptr))) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(DELAY_OPEN * 1000)));
    }

#if defined(_WIN32) || defined(_WIN64)
    std::string command = "start \"\" " + tmp + " >NUL";
#elif defined(__APPLE__)
    std::string command = "open " + tmp + " > /dev/null 2>&1 &";
#else
    std::string command = "xdg-open " + tmp + " > /dev/null 2>&1 &";
#endif

    system(command.c_str());

    next = static_cast<double>(time(nullptr)) + DELAY_OPEN;
}

static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

std::string GraphViz::base64_encode(const std::string &in) const {
    std::string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

