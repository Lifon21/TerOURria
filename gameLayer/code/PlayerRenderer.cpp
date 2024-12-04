#include "../header_file/PlayerRenderer.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "../header_file/sprites.hpp"

using namespace std;

Player::Player() : entities(500, 400) {
    width   = 32;
    height  = 64;
    playerSprite.load("resources/playersprite.png", 32, 64);
    flipped_Left = false;
    equiped = 1;
}

void Player::displayPlayer(sf::RenderWindow &window, sf::View &view, int x = 500, int y = 400) {
    window.setView(view);
    position_x = x;
    position_y = y;
    playerSprite.setPosition(x, y);
    window.draw(playerSprite.getSprite());
}

void Player::setPosition(float x, float y) { playerSprite.setPosition(x, y); }

void Player::moveView(const sf::Event &event, sf::View &view, float deltaTime, world& World) {
    static bool  jumping      = false;                     // Is the view currently jumping?
    static float velocity     = 0.f;                       // Vertical velocity during the jump
    static float groundY      = view.getCenter().y + 100;  // temp ground variable
    const float  gravity      = 9.81f;                     // Gravity to bring the view down
    const float  jumpStrength = 200.f;                     // Initial upward velocity for the jump
    const float  moveSpeed    = 200.f;  // Speed for horizontal and vertical movement

    bool LeftCollision = checkLeftCollision(World);
    bool RightCollision = checkRightCollision(World);
    bool DownCollision = checkDownCollision(World);
    bool UpCollision = checkUpCollision(World);


    sf::Vector2f movement(0.f, 0.f);
    static float jumpCooldown = 0.f;   // Time until next jump is allowed
    const float jumpCooldownTime = 2.f;

    //Move Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (!(flipped_Left)){
            flipped_Left = true;
            playerSprite.setTextureRect(playerSprite.getTextureCoords(0, 0, flipped_Left));
        }
        if ((view.getCenter().x - view.getSize().x / 2 > 0) && !(LeftCollision)) {
            movement.x -= moveSpeed * deltaTime;  // Move left
        }
    }
    //Move Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if ((flipped_Left)){
            flipped_Left = false;
            playerSprite.setTextureRect(playerSprite.getTextureCoords(0, 0, flipped_Left));
        }
        if ((view.getCenter().x + view.getSize().x / 2 < World.getWidth() * 32.f) &&
            !(RightCollision)) {           // World width in pixels
            movement.x += moveSpeed * deltaTime;  // Move right
        }
    }
    //Fall Faster
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if ((view.getCenter().y + view.getSize().y / 2 < World.getHeight() * 32.f) &&
            !(DownCollision)) {            // World height in pixels
            movement.y += moveSpeed * deltaTime;  // Move down
        }
    }
    // Jumping mechanism
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) &&
        !jumping && !(UpCollision)) {
        // Initiate the jump only if the view is on the ground
        jumping  = true;
        velocity = jumpStrength;  // Set the initial jump velocity
        jumpCooldown = jumpCooldownTime;
    }

    // Handle jump physics (gravity applies whether or not a key is pressed)
    if (jumping) {
        view.move(0, -velocity * deltaTime);  // Move the view upward/downward
        velocity -= gravity;                  // Apply gravity (reduce velocity)

        if (DownCollision) {
            jumping  = false;  // End the jump
            velocity = 0.f;    
        }
    }

    if (!DownCollision) {
        view.move(0, -velocity * deltaTime);  // Move the view upward/downward
        velocity -= gravity;                  

        if (DownCollision) {
            jumping  = false;
            velocity = 0.f;    
        }
    }

    if (jumpCooldown > 0.f) {
        jumpCooldown -= deltaTime;
    }

    view.move(movement);
    position_x = view.getCenter().x;
    position_y = view.getCenter().y;
}

bool Player::checkDownCollision(world& World) {
    int TopLeftPosX = position_x / World.getBlockSize();
    int TopLeftPosY = position_y / World.getBlockSize();
    int Width       = width / World.getBlockSize();
    int Height      = height / World.getBlockSize();

    // Check if there is something below the player's bottom boundary
    for (int i = 0; i <= Width; i++) {
        if (World.getBlock(TopLeftPosX + i, TopLeftPosY + Height) != '0') {
            return true;  // Collision detected
        }
    }
    return false;  // No collision
}

bool Player::checkUpCollision(world& World) {
    int TopLeftPosX = position_x / World.getBlockSize();
    int TopLeftPosY = position_y / World.getBlockSize();
    int Width       = width / World.getBlockSize();
    int Height      = height / World.getBlockSize();

    // Check if there is something above the player's top boundary
    for (int i = 0; i <= Width; i++) {
        if (World.getBlock(TopLeftPosX + i, TopLeftPosY - 1) != '0') {
            return true;  // Collision detected
        }
    }
    return false;  // No collision
}

bool Player::checkLeftCollision(world& World) {
    int TopLeftPosX = position_x / World.getBlockSize();
    int TopLeftPosY = position_y / World.getBlockSize();
    int Width       = width / World.getBlockSize();
    int Height      = height / World.getBlockSize();

    if (World.getBlock(TopLeftPosX, TopLeftPosY) != '0') {
        return true;  // Collision detected
    }

    if (World.getBlock(TopLeftPosX, TopLeftPosY + Height / 2) != '0' &&
        World.getBlock(TopLeftPosX + Width, TopLeftPosY + Height) != '0') {
        return true;  // Collision detected
    }
    return false;  // No collision
}

bool Player::checkRightCollision(world& World) {
    int TopLeftPosX = position_x / World.getBlockSize();
    int TopLeftPosY = position_y / World.getBlockSize();
    int Width       = width / World.getBlockSize();
    int Height      = height / World.getBlockSize();

    if (World.getBlock(TopLeftPosX + Width, TopLeftPosY) != '0') {
        return true;  // Collision detected
    }

    if (World.getBlock(TopLeftPosX + Width, TopLeftPosY + Height / 2) != '0' &&
        World.getBlock(TopLeftPosX + Width, TopLeftPosY + Height) != '0') {
        return true;  // Collision detected
    }
    return false;  // No collision
}

std::vector<std::vector<char>> Player::breakBlock(sf::Event &event, sf::View &view,
                                                  std::vector<std::vector<char>> grid,
                                                  sf::RenderWindow              &window) {
    if (equiped == 1){
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            // Get mouse position in world coordinates
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);

            // Calculate the grid coordinates of the block
            int blockX = static_cast<int>(worldPos.x) / 32;  // Assuming each block is 32x32
            int blockY = static_cast<int>(worldPos.y) / 32;

            // Ensure the grid coordinates are within bounds
            if (blockX >= 0 && blockX < grid[0].size() && blockY >= 0 && blockY < grid.size()) {
                if (grid[blockY][blockX] == 'a' || grid[blockY][blockX] == 'b'){
                    this->insertinventory(1);
                }
                else if(grid[blockY][blockX] == 'c'){
                    this->insertinventory(2);
                }
                else if(grid[blockY][blockX] == 'h'){
                    this->insertinventory(3);
                }
                else if(grid[blockY][blockX] == 'l'){
                    this->insertinventory(4);
                }
                else if(grid[blockY][blockX] == 'E'){
                    this->insertinventory(5);
                }
                grid[blockY][blockX] = '0';
            }
        }
    }
    return grid;  // Return the updated grid
}

std::vector<std::vector<char>> Player::placeBlock(sf::Event &event, sf::View &view,
                                                  std::vector<std::vector<char>> grid,
                                                  sf::RenderWindow &window) {
    if (equiped > 2) {  // Ensure equiped is within bounds
        int blocknum = inventory[equiped - 1];
        
        std::map<int, char> blockMapping = {
            {1, 'a'}, {2, 'c'}, {3, 'h'}, {4, 'l'}, {5, 'E'}
        };
        
        // Get the character corresponding to the block number
        char block = blockMapping[blocknum];

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Right) {
            
            // Get mouse position in pixel coordinates
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

            // Convert pixel position to world coordinates
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);

            // Calculate the grid coordinates of the block
            int blockX = static_cast<int>(worldPos.x) / 32;  // Assuming each block is 32x32
            int blockY = static_cast<int>(worldPos.y) / 32;
            
            // Debug: Print the calculated grid coordinates

            // Ensure the grid coordinates are within bounds
            if (blockX >= 0 && blockX < grid[0].size() && blockY >= 0 && blockY < grid.size()) {

                // Check if the block is empty ('0') before placing the new block
                if (grid[blockY][blockX] == '0') {
                    grid[blockY][blockX] = block;  // Place the block
                }
            }
        }
    }

    return grid;  // Return the updated grid

}


void Player::Attack(sf::RenderWindow &window, enemy& Enemy, sf::Event &event) { 
    static bool canAttack = true; 
    
    heart.load("resources/hearts.png", 32, 32);
    hearts.setTexture(heart.getTexture());
    hearts.setTextureRect(heart.getTextureCoords(1,0));
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (canAttack && equiped == 2) {
            if (Enemy.getPosX() + 50 >= position_x && Enemy.getPosX() - 50 <= position_x + width) {
                Enemy.dealdamage(25.0f);
                hearts.setPosition(Enemy.getPosX(), Enemy.getPosY()-50);
                window.draw(hearts);
                canAttack = false;
                attackCooldownTimer.restart();

            }
        }
    }

    if (!canAttack && attackCooldownTimer.getElapsedTime().asSeconds() > 1.f) { 
        canAttack = true;
    }
}

void Player::Attacked(sf::RenderWindow &window, enemy &dog){
    int playerX = this->getPosX();
    int playerY = this->getPosY();
    int playerWidth = 32;  
    int playerHeight = 64; 
    static bool attacked = false;
    int enemyX = dog.getPosX();
    int enemyY = dog.getPosY();
    int enemyWidth = dog.getWidth();
    int enemyHeight = dog.getHeight();
    heart.load("resources/hearts.png", 32, 32);
    hearts.setTexture(heart.getTexture());
    hearts.setTextureRect(heart.getTextureCoords(2,0));

    if  (playerX < enemyX + enemyWidth && playerX + playerWidth > enemyX && playerY < enemyY + enemyHeight && playerY + playerHeight > enemyY && attacked == false){
        this->dealdamage(dog.getAttac());
        attacked = true;
        attackCooldownTimer.restart();
        hearts.setPosition(this->getPosX(), this->getPosY()-50);
        window.draw(hearts);

            }
    if (attacked && attackCooldownTimer.getElapsedTime().asSeconds() > 1.f) { 
        attacked = false;
    }
}


void Player::displayinventory(sf::RenderWindow &window, sf::View &view, sf::Event &event) {
    sprites Blocks, axes, swords;
    Blocks.load("resources/textures.png", 32, 32);
    axes.load("resources/items/item_1.png", 32, 32);
    swords.load("resources/items/item_6.png", 32, 32);

    // bool showinventory = true;
    
    sf::Texture axeTexture, swordtexture;
    sf::Sprite  axe, sword, emptyblock,emptyblockblue, tile1, tile2, tile3, tile4, tile5;
    for (int i = 1; i <= 7; ++i) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf::Keyboard::Num0 + i))) {
            equiped = i;
            break;
        }
    }
    if (equiped>2){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
            cout<<equiped<<endl;
            this->deleteinventory(inventory[equiped - 1]);
        }
    }
    // axe.setScale(32,32);
    // sword.setScale(32,32);

    // axeTexture.loadFromFile("resources/items/item_1.png");  // 1
    // axe.setTexture(axeTexture);
    axe.setTexture(axes.getTexture());
    

    // swordt.loadFromFile("resources/items/item_6.png");  // 2
    // sword.setTexture(swordtexture);

    sword.setTexture(swords.getTexture());
    static bool left = false;
    sword.setTextureRect(swords.getTextureCoords(0, 0));
    axe.setTextureRect(axes.getTextureCoords(0, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        left = false;
    }

    emptyblock.setTexture(Blocks.getTexture());                // Stone texture
    emptyblock.setTextureRect(Blocks.getTextureCoords(0, 3));  // empty block

    emptyblockblue.setTexture(Blocks.getTexture());                // Stone texture
    emptyblockblue.setTextureRect(Blocks.getTextureCoords(0, 1));

    tile1.setTexture(Blocks.getTexture());                // Stone texture
    tile1.setTextureRect(Blocks.getTextureCoords(1, 4));  // tile 1

    tile2.setTexture(Blocks.getTexture());                // Stone texture
    tile2.setTextureRect(Blocks.getTextureCoords(3, 4));  // tile 2

    tile3.setTexture(Blocks.getTexture());                 // Stone texture
    tile3.setTextureRect(Blocks.getTextureCoords(13, 4));  // tile 3

    tile4.setTexture(Blocks.getTexture());                 // Stone texture
    tile4.setTextureRect(Blocks.getTextureCoords(14, 4));  // tile 4

    tile5.setTexture(Blocks.getTexture());                 // Stone texture
    tile5.setTextureRect(Blocks.getTextureCoords(15, 4));  // tile 5

    // heart_sprite.setPosition(view.getCenter().x - Gamelenght / 2 + 32 * 4,
    //                      view.getCenter().y - Gameheight / 1.1);

    // check inventory

    float x = view.getCenter().x - Gamelenght / 2 - 64;
    float y = view.getCenter().y - Gameheight / 1.1;

    // if (showinventory){
    //     showinventory = false;

    for (int num : inventory) {
    // Determine the texture and sprite to draw based on the inventory item
    if (num == 7) {  // Draw axe
        axe.setPosition(x, y);
        window.draw(axe);
        emptyblock.setPosition(x, y);
        window.draw(emptyblock);
    } else if (num == 6) {  // Draw sword
        sword.setPosition(x, y);
        window.draw(sword);
        emptyblock.setPosition(x, y);
        window.draw(emptyblock);
    } else if (num == 1) {  // Draw tile1
        tile1.setPosition(x, y);
        window.draw(tile1);
        emptyblock.setPosition(x, y);
        window.draw(emptyblock);
    } else if (num == 2) {  // Draw tile2
        tile2.setPosition(x, y);
        window.draw(tile2);
        emptyblock.setPosition(x, y);
        window.draw(emptyblock);
    } else if (num == 3) {  // Draw tile3
        tile3.setPosition(x, y);
        window.draw(tile3);
        emptyblock.setPosition(x, y);
        window.draw(emptyblock);
    } else if (num == 4) {  // Draw tile4
        tile4.setPosition(x, y);
        window.draw(tile4);
        emptyblock.setPosition(x, y);
        window.draw(emptyblock);
    } else if (num == 5) {  // Draw tile5
        tile5.setPosition(x, y);
        window.draw(tile5);
        emptyblock.setPosition(x, y);
        window.draw(emptyblock);
    }

    x += 32;  // Move to the next slot horizontally
}
    
     if (equiped <= (x-(view.getCenter().x - Gamelenght / 2)+64)/32){
        emptyblockblue.setPosition(((view.getCenter().x - Gamelenght / 2)+(equiped*32)-96), y);
        window.draw(emptyblockblue);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||left==true) {
        sword.setTextureRect(swords.getTextureCoords(0, 0, true));
        axe.setTextureRect(axes.getTextureCoords(0, 0, true));
        left = true;
    }
    if (equiped==1){
        axe.setPosition(view.getCenter().x, view.getCenter().y+20);
        
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            if (left){
                axe.move(2.f, 10.f);
                window.draw(axe);
            }
            else{
                axe.move(-2.f, 10.f);
                window.draw(axe);
            }
            
        }
        else{
            window.draw(axe);
        }
    }
    if (equiped==2){
        sword.setPosition(view.getCenter().x, view.getCenter().y+20);
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            if (left){
                sword.move(-15.f, 3.f);
                window.draw(sword);
            }
            else{
                sword.move(15.f, 3.f);
                window.draw(sword);
            }
         }
        else{   
            window.draw(sword);
        }
    }
    x -= 35;
}
    

