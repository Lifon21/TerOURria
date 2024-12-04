#include "../header_file/sprites.hpp"
#include <iostream>

void sprites::load(const char *f)
{
    if (!texture.loadFromFile(f))
    {
        std::cerr << "Error loading texture: " << f << std::endl;
    }

    // Explicitly cast to int to avoid narrowing conversion warnings
    size = {static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y)};
    sprite.setTexture(texture);
}

void sprites::load(const char *f, int x, int y, int start_x, int start_y)
{
    if (!texture.loadFromFile(f))
    {
        std::cerr << "Error loading texture: " << f << std::endl;
    }

    sf::IntRect textureRect(start_x, start_y, x, y);

    // Explicitly cast to int to avoid narrowing conversion warnings
    size = {static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y)};
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    blockSize = {x, y};
}

sf::Sprite sprites::getSprite() const
{
    return sprite; // Return the sprite object
}

sf::IntRect sprites::getTextureCoords(int x, int y, bool flipX)
{
    int tx = x * blockSize.x;
    int ty = y * blockSize.y;
    if (flipX)
    {
        return sf::IntRect(tx + blockSize.x, ty, -blockSize.x, blockSize.y); // Flip horizontally
    }
    return sf::IntRect(tx, ty, blockSize.x, blockSize.y);
}

// Getter functions
sf::Texture &sprites::getTexture()
{
    return texture;
}

sf::Vector2i sprites::getSize()
{
    return size;
}

sf::Vector2i sprites::getBlockSize()
{
    return blockSize;
}

// Setter functions
void sprites::setTexture(sf::Texture &T)
{
    texture = T;
}

void sprites::setSize(sf::Vector2i &S)
{
    size = S;
}

void sprites::setBlockSize(sf::Vector2i &B)
{
    blockSize = B;
}

void sprites::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void sprites::setTextureRect(sf::IntRect Rect){
    sprite.setTextureRect(Rect);
}

