#pragma once
#include <SFML/Graphics.hpp>

#include "../header_file/sprites.hpp"
//Made by Nofil
class world {
    public:
        world() = default;
        world(int width, int height);
        void display_map(sf::RenderWindow &window, sf::View &view, sf::Event &event, int x, int y);
        void generateWorld(int width, int height); // Generate the world (populate the grid with tiles)
        void moveView(const sf::Event &event, sf::View &view); // Handle camera movements
        int getWidth(){return width;}
        int getHeight(){return height;}
        int getBlockSize(){return blockSize;}
        void setWorldGrid(std::vector<std::vector<char>> Grid);
        std::vector<std::vector<char>> getWorldGrid();
        int getBlock(int x, int y){return worldGrid[y][x];}

    protected:
        int width, height, blockSize; // Dimensions of the world grid (in terms of blocks)
        std::vector<std::vector<char>> worldGrid; // 2D grid of block types (indices into sprite sheet)
        // sprites dirtSprite; // Object to manage sprite sheet
        sprites Blocks;
        sf::Sprite backgroundSprite;
        sf::Sprite backgroundSprite2;
        sf::Texture backgroundTexture;
        sf::Texture backgroundTexture2;
};
