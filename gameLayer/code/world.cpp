#include "../header_file/world.hpp"
#include "../header_file/PlayerRenderer.hpp"
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

// Constructor for world
world::world(int width, int height) : width(width), height(height) {
    // Load the tile sprites for both dirt and stone

   

    blockSize = 32;
    Blocks.load("resources/textures.png", blockSize, blockSize); // Load dirt tilesheet   // Load stone tilesheet
    backgroundTexture.loadFromFile("resources/background.png");
    
    backgroundSprite.setTexture(backgroundTexture);
    backgroundTexture2.loadFromFile("resources/cave.png");
    backgroundSprite2.setTexture(backgroundTexture2);
    backgroundSprite.setScale(2.5,3.5);
    backgroundSprite2.setScale(2.5,3.5);
    backgroundSprite.setPosition(0, 2000);
    backgroundSprite2.setPosition(0, 3500);
    
    //Load background image
    

    generateWorld(width, height); // Generate the world grid
}

void world::setWorldGrid(std::vector<std::vector<char>> Grid){
    worldGrid = Grid;
}

// Function to generate the world grid (this is a simple example)
void world::generateWorld(int width, int height) {
    vector<string> files = {"map1.txt", "map2.txt", "map3.txt"};
    srand(time(0));
    string filename = files[rand() % 3];

    // Read file contents efficiently
    ifstream file(filename, ios::in | ios::binary | ios::ate);
    
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    string data(size, '\0');
    if (!file.read(&data[0], size)) {
        cerr << "Error: Failed to read file " << filename << endl;
        return;
    }

    // Remove newlines
    data.erase(remove(data.begin(), data.end(), '\n'), data.end());

    // Validate file size
    cout<<data.size();
    if (data.size() < width * height) {
        cerr << "Error: Insufficient data in file. Padding with default values." << endl;
        data.append(width * height - data.size(), '0');
    } else if (data.size() > width * height) {
        cerr << "Warning: Extra data in file will be ignored." << endl;
        data.resize(width * height);
    }

    // Pre-allocate the world grid
    worldGrid.assign(height, vector<char>(width, '0'));

    // Fill the grid directly
    int index = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            worldGrid[y][x] = data[index++];
            // cout<<data[index];
        }
    }

}

void world::moveView(const sf::Event &event, sf::View &view) {
    static bool jumping = false;       // Is the view currently jumping?
    static float velocity = 0.2f;       // Vertical velocity during the jump
    const float gravity = 0.5f;        // Gravity to bring the view down
    const float jumpStrength = 15.f;   // Initial upward velocity for the jump
    const float moveSpeed = 5.f;       // Speed for horizontal and vertical movement

    // Define the ground level based on the view center position
    static float groundY = view.getCenter().y;  // Adjust ground level based on view position

    // Handle key presses for movement
    if (event.type == sf::Event::KeyPressed) {
        // Horizontal movement
        if (event.key.code == sf::Keyboard::Left) {
            if (view.getCenter().x - view.getSize().x / 2 > 0) {
                view.move(-moveSpeed, 0);  // Move left
            }
        } else if (event.key.code == sf::Keyboard::Right) {
            if (view.getCenter().x + view.getSize().x / 2 <
                width * 32.f) {           // World width in pixels
                view.move(moveSpeed, 0);  // Move right
            }
        }

        // Vertical movement (only while not jumping)
        if (event.key.code == sf::Keyboard::Up && !jumping) {
            if (view.getCenter().y - view.getSize().y / 2 > -50) {
                view.move(0, -moveSpeed);  // Move up
            }
        } else if (event.key.code == sf::Keyboard::Down) {
            if (view.getCenter().y + view.getSize().y / 2 <
                height * 32.f) {          // World height in pixels
                view.move(0, moveSpeed);  // Move down
            }
        }

        // Jumping movement (only initiate jump if not already jumping)
        if (event.key.code == sf::Keyboard::Space && !jumping) {
            jumping  = true;          // Start jumping
            velocity = jumpStrength;  // Set the initial upward velocity
        }
    }

    // Handle jump physics (gravity applies whether or not a key is pressed)
    if (jumping) {
        view.move(0, -velocity);  // Move the view upward/downward
        velocity -= gravity;      // Apply gravity (reduce velocity)

        // Check if the view has returned to ground level
        if (view.getCenter().y >= groundY) {
            view.setCenter(view.getCenter().x, groundY); // Reset to ground level
            jumping = false;          // End the jump
            velocity = 0.5f;           // Reset velocity
        }
    }
}

std::vector<std::vector<char>> world::getWorldGrid(){
    return worldGrid;
}

void world::display_map(sf::RenderWindow &window, sf::View &view, sf::Event &event, int x, int y) {
    window.setView(view);

    window.draw(backgroundSprite2);
    window.draw(backgroundSprite);

    // Determine the visible region of the map based on x, y (this is a 64x64 square)
    int startX = x - 32;  // Center around x, adjusting by half of the visible range (16 tiles)
    int startY = y - 32;  // Same for y

    // Get the world grid dimensions (assumed to be available in the world class)
    int worldWidth = worldGrid[0].size();
    int worldHeight = worldGrid.size();

    // Clamp values to ensure they stay within the bounds of the world grid
    startX = std::max(0, startX);  // Prevent going out of bounds on the left
    startY = std::max(0, startY);  // Prevent going out of bounds on the top

    // Set the dimensions of the visible region (64x64 tiles)
    int endX = std::min(worldWidth - 1, x + 32);  // Ensure the region doesn't exceed worldGrid bounds
    int endY = std::min(worldHeight - 1, y + 32);  // Same for the Y-axis

    // Loop over the 64x64 square based on the adjusted start and end coordinates
    for (int i = startY; i <= endY; ++i) {
        for (int j = startX; j <= endX; ++j) {
            char tileType = worldGrid[i][j];
            sf::Sprite sprite;

            // Use appropriate tileset based on tile type
            if (tileType == 'a') {
                sprite.setTexture(Blocks.getTexture()); // Dirt texture (Tiles_0)
                sprite.setTextureRect(Blocks.getTextureCoords(1, 0)); // Tile 0
            } else if (tileType == 'b') {
                sprite.setTexture(Blocks.getTexture()); // Stone texture (Tiles_1)
                sprite.setTextureRect(Blocks.getTextureCoords(2, 0)); // Tile 1
            } else if (tileType == 'c') {
                sprite.setTexture(Blocks.getTexture()); // Stone texture (Tiles_2)
                sprite.setTextureRect(Blocks.getTextureCoords(3, 0)); // Tile 2
            } else if (tileType == 'h') {
                sprite.setTexture(Blocks.getTexture()); // Tile 3
                sprite.setTextureRect(Blocks.getTextureCoords(15, 0)); // Tile 3
            } else if (tileType == 'l') {
                sprite.setTexture(Blocks.getTexture()); // Tile 4
                sprite.setTextureRect(Blocks.getTextureCoords(14, 0)); // Tile 4
            } else if (tileType == 'E') {
                sprite.setTexture(Blocks.getTexture()); // Tile 5
                sprite.setTextureRect(Blocks.getTextureCoords(13, 0)); // Tile 5
            } else if (tileType != '0' && tileType != 'k') {
                sprite.setTexture(Blocks.getTexture()); // Default Tile (Tile 1)
                sprite.setTextureRect(Blocks.getTextureCoords(1, 0)); // Tile 1
            }

            // Position the sprite based on its grid location and tile size (32x32)
            sprite.setPosition(j * 32.f, i * 32.f);

            // Draw the sprite for the current tile
            window.draw(sprite);
        }
    }
}
