#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../header_file/Hearts.hpp"
#include "../header_file/sprites.hpp"
#include "../header_file/world.hpp"
#include "../header_file/entitites.hpp"
#include "../header_file/PlayerRenderer.hpp"

//Made by Zainab
class Hearts{
    protected:
    sf::Sprite heart_sprite;
    sprites Hearts_Main;
    sf::Texture heart_texture;
    public:
    Hearts();
    void showHearts(sf::RenderWindow &window, sf::View &view, entities Entity);
     
};