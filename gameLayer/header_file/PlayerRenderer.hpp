#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "../header_file/entitites.hpp"
#include "../header_file/sprites.hpp"
#include "../header_file/world.hpp"
#include "../header_file/enemies.hpp"

class enemy;
//Further defined collaboration in the functions
class Player : public entities {
protected:

    sprites playerSprite;
    sf::Clock attackCooldownTimer;
    sprites heart;
    sf::Sprite hearts;
    int equiped;
    int     height;
    int     width;
    bool flipped_Left;

public:
    //Made by Mustafa
    Player();
    void displayPlayer(sf::RenderWindow &window, sf::View &view, int x, int y);
    void moveView(const sf::Event &event, sf::View &view,
                  float deltaTime, world& World);  // Nofil and Mustafa
    void setPosition(float x, float y);
    int  getHeight() { return height; }
    int  getWidth() { return width; }
    int  getPosX() { return position_x; }
    int  getPosY() { return position_y; }
    bool checkDownCollision(world& World);
    bool checkUpCollision(world& World);
    bool checkLeftCollision(world& World);
    bool checkRightCollision(world& World);
    //Made by Nofil
    std::vector<std::vector<char>> breakBlock(sf::Event &event, sf::View &view, std::vector<std::vector<char>> grid, sf::RenderWindow &window);
    std::vector<std::vector<char>> placeBlock(sf::Event &event, sf::View &view, std::vector<std::vector<char>> grid, sf::RenderWindow &window);
    void Attack(sf::RenderWindow &window, enemy& Enemy, sf::Event &event);
    void Attacked(sf::RenderWindow &window, enemy &dog);
    void updateGrid(std::vector<std::vector<char>> grid);
    //Made by Zainab
    void displayinventory(sf::RenderWindow &window, sf::View &view, sf::Event &event);

};
