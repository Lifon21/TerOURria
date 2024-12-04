#include "gameLayer\header_file\game.hpp"
#include <SFML/Audio.hpp>

using namespace std;

void game::play(){
    MainMenu main_menu(window, "Main Menu", 1920, 1080, "resources/splash_3.png", "resources/logo.png", "resources/instruction_screen.png");
    sf::Clock clock;
    sf::Event event;
    sf::View view;
    view.setSize(window.getSize().x, window.getSize().y);
    pS.insertinventory(7);
    pS.insertinventory(6);
    pS.setlife(100); 

    float deltaTime2 = 0.f;

    // Create a music object
    sf::Music music;

    // Load the MP3 file
    if (!music.openFromFile("resources\\Music-Hallow_(Otherworldly).ogg")) {
    std::cerr << "Error: Could not load OGG file." << std::endl;
    }

    // Play the music in a loop
    music.setLoop(true);
    music.play();
    bool musicPlaying = true;
  
    
    while (window.isOpen()) {
        // Event object for processing input
        
        float deltaTime =  clock.restart().asSeconds();


        // Poll for events
        while (window.pollEvent(event)) {
            // if event type is close: handles x button pressed and escape  button pressed
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                std::cout << "Closing the game..." << std::endl;
                // end = true;
                window.close();

            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                if (musicPlaying) {
                    music.pause();  // Pause the music
                } else {
                    music.play();   // Resume the music
                }
                musicPlaying = !musicPlaying;  // Toggle the music state
            }
        }


        // Clear the window once at the beginning of each frame
        window.clear(sf::Color::Black);

        // Render content based on the current state
        if (state == 0 || state == 1 || state == 2) {
            int menu_result = main_menu.run(window, event);
            // Update state based on menu result
            if (menu_result == 3) {
                state = 3;  // Start the game
                view.setCenter(1350, 3596);
                
                // cout << view.getCenter().x << view.getCenter().y << endl;
            } else {
                state = menu_result;  // Stay in menu state
            }
        } else if (state == 3) {  // Game state
            w.display_map(window, view, event, (view.getCenter().x/32), (view.getCenter().y/32));  // Render the game world

            if (event.type == sf::Event::MouseButtonPressed){
                w.setWorldGrid(pS.breakBlock(event, view, w.getWorldGrid(), window)); 
                w.setWorldGrid(pS.placeBlock(event, view, w.getWorldGrid(), window));  
                if (Zombie.getlife()>0){
                    pS.Attack(window, Zombie, event);
                    
                }
                if (Slime.getlife()>0){
                    pS.Attack(window, Slime, event);
                   
                }
            }
            
            pS.moveView(event, view, deltaTime, w);

            pS.displayPlayer(window, view, view.getCenter().x, view.getCenter().y);
            heart.showHearts(window, view, pS);
            pS.displayinventory(window, view, event);
            if (Slime.getlife()>0){
                Slime.move(w,view,deltaTime,pS);
                Slime.draw(window, view);
                pS.Attacked(window, Zombie);
            }
            if (Zombie.getlife()>0){
                Zombie.move(w,view,deltaTime,pS);
                Zombie.draw(window, view);
                pS.Attacked(window, Slime);
            }

            deltaTime2 += deltaTime;
            if (pS.getlife()<=0){
                for(int i = 0; i<5; i++){
                    pS.deleteinventory(i);
                }
                pS.setlife(100); 
                Zombie.setlife(40);
                Slime.setlife(30);
                Zombie.setPosition(1250, 3500);
                Slime.setPosition(1450, 3500);
                view.setCenter(1350, 3500);
                state = 0;
                main_menu.setState(0);
                MainMenu main_menu(window, "Main Menu", 1920, 1080, "resources/splash_3.png", "resources/logo.png", "resources/instruction_screen.png");
                // main_menu.run(window, event);
            }

        }

        window.display();
    }
}

game::game() : 
    window(sf::VideoMode(1920, 1080), "Terraria-like World"),
    w(841, 320),
    Zombie(1350, 3500),
    Slime(1400, 3500), pS()
{
    state =0;
}