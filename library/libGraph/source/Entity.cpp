//
// Created by John on 7/22/2024.
//

#include <Entity.hpp>

std::string Entity::getAttribute(const std::string& name, const std::string& defaultValue) const {
    auto it = attributes.find(name);
    if (it != attributes.end()) {
        return it->second;
    }
    return defaultValue;
}

void Entity::setAttribute(const std::string& name, const std::string& value) {
    attributes[name] = value;
}

void Entity::removeAttribute(const std::string& name) {
    attributes.erase(name);
}

std::map<std::string, std::string> Entity::getAttributes() const {
    return attributes;
}

void Entity::setAttributes(const std::map<std::string, std::string>& newAttributes) {
    attributes.insert(newAttributes.begin(), newAttributes.end());
}
