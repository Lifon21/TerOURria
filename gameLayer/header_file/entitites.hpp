#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../header_file/declarations.hpp"
#include "../header_file/sprites.hpp"
using std::cout;
//Made by Mustafa and zainab, commented on funtions
class entities : public sprites {
protected:

    float            invurnerabilitytime = 0;
    float            life;
    float            maxlife;
    char             armour               = 0;
    int              position_x;  // start position of sprite
    int              position_y;  // end position of sprite
    std::vector<int> inventory;
    sf::Vector2i     lastpos;  ///
    bool             down_pressed = 0;

public:

    entities() {
        position_x        = 0;
        position_y        = 0;
        life              = 100;
        maxlife           = 100;
    };
    entities(int x, int y){
        // inventory         = std::vector<int>(INVENTORY_SIZE, 0);
        position_x        = x;
        position_y        = y;
        life              = 100;
        maxlife           = 100;
    }
    //Made by Mustafa
    float        getcenterx();
    float        getcentery();
    void setPosition(int x, int y){position_x = x; position_y = y;}
    virtual void move(){};
    virtual bool checkDownCollision(){return true;};
    virtual bool checkUpCollision(){return true;};
    virtual bool checkLeftCollision(){return true;};
    virtual bool checkRightCollision(){return true;};
    virtual void draw(sf::RenderWindow& window, float deltatime, int add = 0) {}
    int getPosX(){return position_x;}
    int getPosY(){return position_y;}

    //Made by zainab
    void         dealdamage(float damage);
    float        getlife();
    float        getMaxLife();
    void         setlife(float num);
    void         insertinventory(int num);
    void         deleteinventory(int num);
    
};