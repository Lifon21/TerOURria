#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameLayer/header_file/sprites.hpp"
#include "gameLayer/header_file/world.hpp"
#include "gameLayer/header_file/PlayerRenderer.hpp"
#include "gameLayer\header_file\entitites.hpp"

class Player;
//Made by Mustafa
class enemy: public entities{
    protected:
        sprites EnemySprite;
        int height;
        int width;
        unsigned int type;
        float attatc;
        bool flipped_Left;
    public:
        enemy(int x, int y):entities(x, y){};
        void draw(sf::RenderWindow &window, sf::View &view);
        void move(world& World, sf::View &view, float deltaTime, Player& P);
        void setPosition(int x, int y){position_x = x; position_y = y;}
        int getHeight(){return height;}
        float getAttac(){return attatc;}
        int getWidth(){return width;}
        int getPosX(){return position_x;}
        int getPosY(){return position_y;}
        bool checkDownCollision(world World);
        bool checkUpCollision(world World);
        bool checkLeftCollision(world World);
        bool checkRightCollision(world World);

        //virtual void makemove(entities other){};
};
//Made by Mustafa
class slimeentity:public enemy{
    public:
        slimeentity(int x, int y);
};
//Made by Mustafa
class humanlikeenemy:public enemy{
    protected:
        enum animationstates
        {
        idle,
        walking,
        jumping,
        attacking
        };
    public:
        humanlikeenemy(int x, int y);
};