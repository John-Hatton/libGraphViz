//
// Created by John on 7/22/2024.
//
#include <string>
#include <map>

#ifndef LIBGRAPH_ENTITY_HPP
#define LIBGRAPH_ENTITY_HPP

class Entity {
public:
    virtual ~Entity() = default;

    std::string getAttribute(const std::string& name, const std::string& defaultValue = "") const;
    void setAttribute(const std::string& name, const std::string& value);
    void removeAttribute(const std::string& name);
    std::map<std::string, std::string> getAttributes() const;
    void setAttributes(const std::map<std::string, std::string>& attributes);

protected:
    std::map<std::string, std::string> attributes;
};

#endif //LIBGRAPH_ENTITY_HPP
