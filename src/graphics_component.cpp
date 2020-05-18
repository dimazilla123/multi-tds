#include "graphics_component.h"
#include "binutils.h"

GraphicsComponent::GraphicsComponent()
{
}

void GraphicsComponent::save(std::ostream &out) const
{
    binutils::write(out, *this);
}

void GraphicsComponent::load(std::istream &in)
{
    binutils::read(in, *this);
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