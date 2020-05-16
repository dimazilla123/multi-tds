#include "graphics_component.h"

GraphicsComponent::GraphicsComponent()
{
}

std::string GraphicsComponent::getTextureName() const
{
    return tex_name;
}

std::string GraphicsComponent::getFileName() const
{
    return filename;
}

void GraphicsComponent::setFileName(const std::string &s)
{
    filename = s;
}

void GraphicsComponent::setTextureName(const std::string &s)
{
    tex_name = s;
}

sf::Sprite& GraphicsComponent::getSprite()
{
    return sprite;
}