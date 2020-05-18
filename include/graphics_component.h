#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "component.h"

#include <SFML/Graphics.hpp>

class GraphicsComponent : public ECS::Component
{
public:
    GraphicsComponent();
    sf::Sprite& getSprite();
    std::string getTextureName() const;
    std::string getFileName() const;
    void setTextureName(const std::string &s);
    void setFileName(const std::string &s);
    void save(std::ostream &out) const;
    void load(std::istream &in);
private:
    sf::Sprite sprite;
    std::string tex_name;
    std::string filename;
};

#endif