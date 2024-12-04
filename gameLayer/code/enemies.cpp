#include <SFML/Graphics.hpp>
#include<iostream>
#include "gameLayer\header_file\entitites.hpp"
#include "gameLayer\header_file\enemies.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

void enemy::draw(sf::RenderWindow &window, sf::View &view){
   
    window.setView(view);
    EnemySprite.setPosition(position_x, position_y );
    window.draw(EnemySprite.getSprite());
    
}

void enemy::move(world& World, sf::View &view, float deltaTime, Player& P) {
    static bool jumping = false;       // Is the enemy currently jumping?
    static float velocity = 0.f;       // Vertical velocity during the jump
    const float gravity = 9.81f;       // Gravity to bring the enemy down
    const float jumpStrength = 250.f;  // Initial upward velocity for the jump
    const float moveSpeed = 50.f;     // Speed for horizontal and vertical movement
    const float maxSpeedX = 100.f;    // Max horizontal speed
    const float acceleration = 50.f;   // Horizontal acceleration
    const float deceleration = 100.f;  // Horizontal deceleration when no input

    sf::Vector2f movement(0.f, 0.f);  // Movement vector
    static float jumpCooldown = 0.f;   // Time until next jump is allowed
    const float jumpCooldownTime = 4.f;

    // Smooth movement decision - horizontal
    static float speedX = 0.f;
    
    // Randomized horizontal direction
    int DirectionX = P.getPosX() > position_x? 1:-1;
    if (DirectionX != 0) {
        if (DirectionX == -1 && !checkLeftCollision(World)) {
            if (!(flipped_Left)){
                flipped_Left = true;
                EnemySprite.setTextureRect(EnemySprite.getTextureCoords(0, 0, flipped_Left));
            }
            speedX -= acceleration * deltaTime;  // Accelerate left
        }
        else if (DirectionX == 1 && !checkRightCollision(World)) {
            if ((flipped_Left)){
                flipped_Left = false;
                EnemySprite.setTextureRect(EnemySprite.getTextureCoords(0, 0, flipped_Left));
            }
            speedX += acceleration * deltaTime;  // Accelerate right
        }
        else if ((checkLeftCollision(World) && DirectionX == -1) || (checkRightCollision(World) && DirectionX == 1)){
            speedX = 0;
        }
    }
    
    // Apply max speed clamp
    if (speedX > maxSpeedX) speedX = maxSpeedX;
    if (speedX < -maxSpeedX) speedX = -maxSpeedX;

    // Deceleration if not moving (i.e., when DirectionX is 0)
    if (DirectionX == 0) {
        if (speedX > 0) speedX -= deceleration * deltaTime;
        else if (speedX < 0) speedX += deceleration * deltaTime;
    }

    // Random vertical movement with smooth transition
    int randomDirectionY = rand() % 3 - 1;  // Random values -1, 0, or 1

    if (randomDirectionY == 1) {  // Move down if possible
        if (view.getCenter().y + view.getSize().y / 2 < World.getHeight() * 32.f && !checkDownCollision(World)) {
            movement.y += moveSpeed * deltaTime;
        }
    }

    // Jumping logic with gravity
    if (randomDirectionY == -1 && !jumping && !checkUpCollision(World) && (view.getCenter().x + view.getSize().x / 2 < World.getWidth() * 32.f)) {
        // Initiate the jump only if the enemy is on the ground
        jumping = true;
        velocity = jumpStrength;  // Set the initial jump velocity
        jumpCooldown = jumpCooldownTime;
    }

    if (jumping) {
        movement.y += -velocity * deltaTime;  // Apply vertical movement
        velocity -= gravity;              

        // Check if the enemy has returned to ground level
        if (checkDownCollision(World)) {
            jumping = false;  // End the jump
            velocity = 0.f;    // Reset velocity
        }
    }

    if (jumpCooldown > 0.f) {
        jumpCooldown -= deltaTime;
    }

    // Apply the final movement to the sprite
    movement.x = speedX * deltaTime;  // Apply horizontal speed with deltaTime
    movement.y = static_cast<int>(movement.y);

    // Apply movement
    EnemySprite.move(movement);
    
    // Update the position after movement
    position_x += static_cast<int>(movement.x);  // Update position
    position_y += static_cast<int>(movement.y);
}



bool enemy::checkDownCollision(world World) {
    int TopLeftPosX = position_x / World.getBlockSize();
    int TopLeftPosY = position_y / World.getBlockSize();
    int Width = width / World.getBlockSize();
    int Height = height / World.getBlockSize();

    // Check if there is something below the enemy's bottom boundary
    for (int i = 0; i <= Width; i++) {
        char block = World.getBlock(TopLeftPosX + i, TopLeftPosY + Height);
        if (block != '0') {
            return true;  // Collision detected
        }
    }
    return false;
}


bool enemy::checkUpCollision(world World) {
    int TopLeftPosX = position_x / World.getBlockSize();
    int TopLeftPosY = position_y / World.getBlockSize();
    int Width = width / World.getBlockSize();
    int Height = height / World.getBlockSize();

    // Check if there is something above the enemy's top boundary
    for (int i = 0; i <= Width; i++) {
        char block = World.getBlock(TopLeftPosX + i, TopLeftPosY - 1);
        
        if (block != '0') {
            return true;  // Collision detected
        }
    }
    return false;  // No collision
}


bool enemy::checkLeftCollision(world World){
    int TopLeftPosX = position_x / World.getBlockSize();
    int TopLeftPosY = position_y / World.getBlockSize();
    int Width = width / World.getBlockSize();
    int Height = height / World.getBlockSize();


    if (World.getBlock(TopLeftPosX, TopLeftPosY) != '0') {
        return true;  // Collision detected
    }

    if (World.getBlock(TopLeftPosX, TopLeftPosY + Height/2) != '0' && World.getBlock(TopLeftPosX + Width, TopLeftPosY + Height) != '0') {
        return true;  // Collision detected
    }
    return false;  // No collision
}

bool enemy::checkRightCollision(world World){
    int TopLeftPosX = position_x / World.getBlockSize();
    int TopLeftPosY = position_y / World.getBlockSize();
    int Width = width / World.getBlockSize();
    int Height = height / World.getBlockSize();

    if (World.getBlock(TopLeftPosX + Width, TopLeftPosY) != '0') {
        return true;  // Collision detected
    }

    if (World.getBlock(TopLeftPosX + Width, TopLeftPosY + Height/2) != '0' && World.getBlock(TopLeftPosX + Width, TopLeftPosY + Height) != '0') {
        return true;  // Collision detected
    }
    return false;  // No collision
}

humanlikeenemy::humanlikeenemy(int x, int y):enemy(x,y){
    this->EnemySprite.load("resources//zombie.png",32,64);
    this->width = 32;
    this->height = 64;
    this->maxlife=40;
    this->life= this->maxlife;
    this->attatc=8;
    this->flipped_Left = false;
}

slimeentity::slimeentity(int x, int y):enemy(x,y){
    this->EnemySprite.load("resources//slime.png",32,32);
    this->width = 32;
    this->height = 32;
    this->maxlife=30;
    this->life=this->maxlife;
    this->attatc=7;
    this->flipped_Left = false;
}
