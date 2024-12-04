#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include "gameLayer/header_file/Hearts.hpp"
#include "gameLayer/header_file/MainMenu.hpp"
#include "gameLayer/header_file/PlayerRenderer.hpp"
#include "gameLayer/header_file/enemies.hpp"
#include "gameLayer/header_file/entitites.hpp"
#include "gameLayer/header_file/sprites.hpp"
#include "gameLayer/header_file/world.hpp"

using namespace std;
//Made by Nofil(converting the main file to a class)
class game
{
private:
    int state; 
    sf::RenderWindow window;
    world w;
    Player pS;
    humanlikeenemy Zombie;
    slimeentity Slime;
    Hearts heart;
    
public:
    game();
    void play();
};
