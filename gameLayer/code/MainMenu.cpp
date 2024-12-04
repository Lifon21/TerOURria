#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../header_file/MainMenu.hpp"
using namespace std;

// to maintain screens 0 : main menu , 1 : instruction screen, 2 : choose _player , 3 : settings

MainMenu::MainMenu(sf::RenderWindow &window, const std::string &title, int width, int height, const std::string &background_path, const std::string &logo_path, const std::string &instruction_screen_path)
{
    // load font
    font.loadFromFile("resources/Comic Sans MS.ttf");
    font_bold.loadFromFile("resources/Comic Sans MS Bold.ttf");

    // Create the window with the specified size and title
    window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);

    // load backgroung using splash2 (matches 1000x600)

    background_texture.loadFromFile(background_path);
    background_sprite.setTexture(background_texture);

    sf::Vector2u textureSize = background_texture.getSize();

    // Calculate the scale factors for width and height
    float scaleX = 1920.f / textureSize.x;
    float scaleY = 1080.f / textureSize.y;

    // Apply the scale to the sprite
    background_sprite.setScale(scaleX, scaleY);

    // load logo

    logo_texture.loadFromFile(logo_path);
    logo_sprite.setTexture(logo_texture);

    // set position of logo

    float logo_x = (window.getSize().x - logo_texture.getSize().x) / 2.f;
    float logo_y = window.getSize().y * 0.15f;

    logo_sprite.setPosition(logo_x, logo_y);

    // set buttons

    // INSTRUCTION

    // instruction button
    instruction_button.setFont(font_bold);
    instruction_button.setString("Instructions");
    instruction_button.setCharacterSize(30);
    instruction_button.setFillColor(sf::Color::White);

    // set position of instruction button
    float instruction_button_x = (window.getSize().x - instruction_button.getLocalBounds().width) / 2.f;
    float instruction_button_y = window.getSize().y * 0.7f;
    instruction_button.setPosition(instruction_button_x, instruction_button_y);

    // clickable area for instructions button
    instructions_button_area.left = instruction_button.getGlobalBounds().left;
    instructions_button_area.top = instruction_button.getGlobalBounds().top;
    instructions_button_area.width = instruction_button.getGlobalBounds().width;
    instructions_button_area.height = instruction_button.getGlobalBounds().height;

    // instruction screen back  button
    instruction_back_button.setFont(font_bold);
    instruction_back_button.setString("Back");
    instruction_back_button.setCharacterSize(30);
    instruction_back_button.setFillColor(sf::Color::White);

    // set position of instruction back button
    float instruction_back_button_x = (window.getSize().x - instruction_back_button.getLocalBounds().width) / 2.f;
    float instruction_back_button_y = window.getSize().y * 0.9f;
    instruction_back_button.setPosition(instruction_back_button_x, instruction_back_button_y);

    // clickable area for instrution back button
    instruction_back_button_area.left = instruction_back_button.getGlobalBounds().left;
    instruction_back_button_area.top = instruction_back_button.getGlobalBounds().top;
    instruction_back_button_area.width = instruction_back_button.getGlobalBounds().width;
    instruction_back_button_area.height = instruction_back_button.getGlobalBounds().height;

    // PLAYER

    // play button
    play_button.setFont(font_bold);
    play_button.setString("Play");
    play_button.setCharacterSize(30);
    play_button.setFillColor(sf::Color::White);

    // set position of play button
    float play_button_x = (window.getSize().x - play_button.getLocalBounds().width) / 2.f;
    float play_button_y = window.getSize().y * 0.4f;
    play_button.setPosition(play_button_x, play_button_y);

    // clickable area for play button
    play_button_area.left = play_button.getGlobalBounds().left;
    play_button_area.top = play_button.getGlobalBounds().top;
    play_button_area.width = play_button.getGlobalBounds().width;
    play_button_area.height = play_button.getGlobalBounds().height;

    // player screen back  button
    player_back_button.setFont(font_bold);
    player_back_button.setString("Back");
    player_back_button.setCharacterSize(30);
    player_back_button.setFillColor(sf::Color::White);

    // set position of player back button
    float player_back_button_x = 220.f;
    float player_back_button_y = window.getSize().y * 0.9f;
    player_back_button.setPosition(player_back_button_x, player_back_button_y);

    // clickable area for player back button
    player_back_button_area.left = player_back_button.getGlobalBounds().left;
    player_back_button_area.top = player_back_button.getGlobalBounds().top;
    player_back_button_area.width = player_back_button.getGlobalBounds().width;
    player_back_button_area.height = player_back_button.getGlobalBounds().height;

    // player screen next  button
    player_next_button.setFont(font_bold);
    player_next_button.setString("Next");
    player_next_button.setCharacterSize(30);
    player_next_button.setFillColor(sf::Color::White);

    // set position of player next button
    float player_next_button_x = window.getSize().x - player_next_button.getLocalBounds().width - 220.f;
    float player_next_button_y = window.getSize().y * 0.9f;
    player_next_button.setPosition(player_next_button_x, player_next_button_y);

    // clickable area for player next button
    player_next_button_area.left = player_next_button.getGlobalBounds().left;
    player_next_button_area.top = player_next_button.getGlobalBounds().top;
    player_next_button_area.width = player_next_button.getGlobalBounds().width;
    player_next_button_area.height = player_next_button.getGlobalBounds().height;

    // EXIT

    // exit button
    exit_button.setFont(font_bold);
    exit_button.setString("Exit");
    exit_button.setCharacterSize(30);
    exit_button.setFillColor(sf::Color::White);

    // set position of exit button
    float exit_button_x = (window.getSize().x - exit_button.getLocalBounds().width) / 2.f;
    float exit_button_y = window.getSize().y * 0.55f;
    exit_button.setPosition(exit_button_x, exit_button_y);

    // clickable area for exit button
    exit_button_area.left = exit_button.getGlobalBounds().left;
    exit_button_area.top = exit_button.getGlobalBounds().top;
    exit_button_area.width = exit_button.getGlobalBounds().width;
    exit_button_area.height = exit_button.getGlobalBounds().height;

    // SETTINGS

    // settings button
    settings_button.setFont(font_bold);
    settings_button.setString("Settings");
    settings_button.setCharacterSize(30);
    settings_button.setFillColor(sf::Color::White);

    // set position of settings button
    float settings_button_x = (window.getSize().x - settings_button.getLocalBounds().width) / 2.f;
    float settings_button_y = window.getSize().y * 0.5f;
    settings_button.setPosition(settings_button_x, settings_button_y);

    // clickable area for settings button
    settings_button_area.left = settings_button.getGlobalBounds().left;
    settings_button_area.top = settings_button.getGlobalBounds().top;
    settings_button_area.width = settings_button.getGlobalBounds().width;
    settings_button_area.height = settings_button.getGlobalBounds().height;

    // set current screen as 0: main menu
    current_state = 0;
}

void MainMenu::player_screen(sf::RenderWindow &window, const std::string &player_screen_path)
{
    player_screen_texture.loadFromFile(player_screen_path);
    player_screen_sprite.setTexture(player_screen_texture);

    sf::Vector2u textureSize = player_screen_texture.getSize();

    // Calculate the scale factors for width and height
    float scaleX = 1920.f / textureSize.x;
    float scaleY = 1080.f / textureSize.y;

    // Apply the scale to the sprite
    player_screen_sprite.setScale(scaleX, scaleY);

    window.clear();
    window.draw(player_screen_sprite);
    window.draw(player_back_button);
    window.draw(player_next_button);
}

void MainMenu::instruction_screen(sf::RenderWindow &window, const std::string &instruction_screen_path)
{
    instruction_screen_texture.loadFromFile(instruction_screen_path);
    instruction_screen_sprite.setTexture(instruction_screen_texture);

    sf::Vector2u textureSize = instruction_screen_texture.getSize();

    // Calculate the scale factors for width and height
    float scaleX = 1920.f / textureSize.x;
    float scaleY = 1080.f / textureSize.y;

    // Apply the scale to the sprite
    instruction_screen_sprite.setScale(scaleX, scaleY);

    window.clear();
    window.draw(instruction_screen_sprite);
    window.draw(instruction_back_button);
    // window.display();
}

int MainMenu::run(sf::RenderWindow &window, const sf::Event &event)
{
    if (current_state == 0)
    { // main_menu
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Get mouse position relative to the window
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                // Check if the mouse position is inside the instruction button area
                if (instructions_button_area.contains(mousePosition))
                { // if instruction button pressed open instruction screen
                    cout << "instruction button clicked" << endl;
                    current_state = 1;
                }
                else if (play_button_area.contains(mousePosition))
                {
                    cout << "play button clicked" << endl;
                    // current_state = 2;
                    current_state = 3;
                }
                else if (exit_button_area.contains(mousePosition))
                {
                    cout << "exit button clicked" << endl;
                    std::cout << "Closed the window";
                    window.close();
                }
                // else if (settings_button_area.contains(mousePosition))
                // {
                //     cout << "settings button clicked" << endl;
                // }
            }
        }
    }
    else if (current_state == 1)
    { // instruction screen
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Get mouse position relative to the window
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                // Check if the mouse position is inside the instruction button area
                if (instruction_back_button_area.contains(mousePosition))
                {
                    cout << "back button clicked" << endl;
                    current_state = 0;
                    // instruction_screen("resources/instruction_screen.png");
                }
            }
        }
    }
    else if (current_state == 2)
    { // select player screen
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Get mouse position relative to the window
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                // Check if the mouse position is inside the instruction button area
                if (player_back_button_area.contains(mousePosition))
                {
                    cout << "back button clicked" << endl;
                    current_state = 0;
                }
                else if (player_next_button_area.contains(mousePosition))
                {
                    cout << "Next button clicked" << endl;
                    current_state = 3;
                    // connect to game
                }
            }
        }
    }

    // draw background image
    if (current_state == 0)
    {
        // window.clear();
        window.draw(background_sprite);
        // window.draw(logo_sprite);
        window.draw(instruction_button);
        window.draw(play_button);
        window.draw(exit_button);
        // window.draw(settings_button);
        // window.display();
    }
    else if (current_state == 1)
    {

        instruction_screen(window, "resources/instruction_screen.png");
    }
    else if (current_state == 2)
    {

        player_screen(window, "resources/select_player.png");
    }
    // window.display();

    return current_state;
}

// int main(){
//     int state = 0;
//     sf::RenderWindow window("Main Menu",1000, 600, "resources/splash_3.png", "resources/logo.png","resources/instruction_screen.png" );
//     MainMenu main_menu("Main Menu",1000, 600, "resources/splash_3.png", "resources/logo.png","resources/instruction_screen.png" );
//     while (window.isOpen()) {
//             // Event processing
//                 sf::Event event;
//                 while (window.pollEvent(event)) {
//                     // Close the window when close button or escape key is pressed
//                     if (event.type == sf::Event::Closed ||(event.type == sf::Event::KeyPressed&& event.key.code == sf::Keyboard::Escape)) {
//                         std::cout << "Closed the window";
//                         window.close();
//                     }
//                 if (state = 3){
//                     while (window.pollEvent(event)) {
//                         w.moveView(event, view);
//                     }
//                     window.clear(sf::Color::Black);
//                     w.display_map(window, view);
//                     window.display();
//                 }
//                 else{
//                     state = main_menu.run(window);
//                 }
//                }

//     }
//     return 0;
// }
