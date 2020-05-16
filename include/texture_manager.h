#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    bool loadTexture(const std::string &name, const std::string &filename);
    sf::Texture* getTexture(const std::string &name);

private:
    sf::Texture error;
    std::unordered_map<std::string, sf::Texture*> textures;
};

#endif