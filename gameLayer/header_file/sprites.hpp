#pragma once
#include <SFML/Graphics.hpp>
//MAde by Mustafa
class sprites {
    protected:
        sf::Sprite sprite;
        sf::Texture texture;  // SFML Texture
        sf::Vector2i size;    // Size of the sprite sheet
        sf::Vector2i blockSize; // Size of each block (tile)
    public:
        void load(const char *f);  // Load texture
        void load(const char *f, int x, int y, int start_x = 0, int start_y = 0);  // Load texture and specify block size

        sf::IntRect getTextureCoords(int x, int y, bool flipX = false);  // Get texture coordinates for tiles
        void setTextureRect(sf::IntRect Rect);

        // Getter and Setter functions
        sf::Texture& getTexture();
        sf::Sprite getSprite() const;
        sf::Vector2i getSize();
        sf::Vector2i getBlockSize();
        void setTexture(sf::Texture& T);
        void setSize(sf::Vector2i& S);
        void setBlockSize(sf::Vector2i& B);
        virtual void setPosition(float x, float y);
        void move(float x, float y){sprite.setPosition(sprite.getPosition().x + static_cast<int>(x), sprite.getPosition().y + static_cast<int>(y));}
        void move (sf::Vector2f movement){sprite.setPosition(sprite.getPosition().x + static_cast<int>(movement.x), sprite.getPosition().y +static_cast<int>(movement.y));}
        sf::Vector2f getPosition(){return sprite.getPosition();}

};
