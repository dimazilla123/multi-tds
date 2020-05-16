#include "texture_manager.h"

TextureManager::TextureManager()
{
}
TextureManager::~TextureManager()
{
    for (auto [name, pntr] : textures)
        delete pntr;
}

bool TextureManager::loadTexture(const std::string &name, const std::string &filename)
{
    textures[name] = new sf::Texture;
    return textures[name]->loadFromFile(filename);
}

sf::Texture* TextureManager::getTexture(const std::string &name)
{
    if (textures.find(name) == textures.end())
        return nullptr;
    return textures[name];
}