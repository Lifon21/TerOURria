#pragma once
// #include <glad/glad.h>
// #include <glfw/glfw3.h>
// #include "gl2d/gl2d.h"
// #include "stb_image/stb_image.h"

#include <SFML/Graphics.hpp>

#include <iostream>
using namespace std;
//Made by Zainab
class MainMenu{
    protected:
    // sf::RenderWindow main_menu_window;
    sf::Texture background_texture, logo_texture,instruction_screen_texture, player_screen_texture;   
    sf::Sprite background_sprite, logo_sprite,instruction_screen_sprite, player_screen_sprite ;   
    sf::Font font, font_bold;
    sf::Text play_button,player_back_button, player_next_button, instruction_button, instruction_back_button,settings_button,exit_button;
    sf::IntRect play_button_area,player_back_button_area, player_next_button_area , instructions_button_area, instruction_back_button_area,settings_button_area,exit_button_area;
    int current_state=0; // to maintain screens 0 : main menu , 1 : instruction screen, 2 : choose _player , 3: choose world


    public:

    MainMenu(sf::RenderWindow& window, const std::string& title, int width, int height, const std::string& background_path, const std::string& logo_path,const std::string& instruction_screen_path);
    void player_screen(sf::RenderWindow &window, const std::string& player_screen_path);
    void instruction_screen(sf::RenderWindow &window, const std::string& instruction_screen_path);
    int run(sf::RenderWindow &window, const sf::Event &event);
    void setState(int num){current_state = num;}

};