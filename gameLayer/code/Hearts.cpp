#include "../header_file/Hearts.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "../header_file/PlayerRenderer.hpp"
#include "../header_file/declarations.hpp"
#include "../header_file/entitites.hpp"
#include "../header_file/sprites.hpp"
#include "../header_file/world.hpp"

Hearts::Hearts() {
    
    Hearts_Main.load("resources/hearts.png", 32, 32);
    heart_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));  //  32x32 heart sprite
}

void Hearts::showHearts(sf::RenderWindow &window, sf::View &view, entities Entity) {
    heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
    heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(0, 0));
    int count = 0;

    if (Entity.getlife() / Entity.getMaxLife() >= 1) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(0, 0));
        // count = 5;
    } else if (Entity.getlife() / Entity.getMaxLife() >= 0.9) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(1, 0, true));
        // heart_sprite.flip();
        // count = 5;

    } else {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(2, 0));
        // count = 5;
    }

    heart_sprite.setPosition(view.getCenter().x + Gamelenght / 2.3 + 32 * 4,
                             view.getCenter().y - Gameheight / 1.1);
    // heart_sprite.setPosition(view.getSize32*5, 32);
    window.draw(heart_sprite);

    if (Entity.getlife() / Entity.getMaxLife() > 0.7) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(0, 0));
        // count = 4;
    } else if (Entity.getlife() / Entity.getMaxLife() >= 0.6) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(1, 0, true));
        // heart_sprite.flip();
        // count = 4;

    } else {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(2, 0));
        // count = 4;
    }

    heart_sprite.setPosition(view.getCenter().x + Gamelenght / 2.3 + 32 * 3,
                             view.getCenter().y - Gameheight / 1.1);
    // heart_sprite.setPosition(32*4, 32);
    window.draw(heart_sprite);

    if (Entity.getlife() / Entity.getMaxLife() > 0.5) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(0, 0));
        // count = 3;
    } else if (Entity.getlife() / Entity.getMaxLife() >= 0.4) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(1, 0, true));
        // heart_sprite.flip();
        // count = 3;

    } else {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(2, 0));
        // count = 3;
    }

    heart_sprite.setPosition(view.getCenter().x + Gamelenght / 2.3 + 32 * 2,
                             view.getCenter().y - Gameheight / 1.1);

    window.draw(heart_sprite);

    if (Entity.getlife() / Entity.getMaxLife() > 0.3) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(0, 0));
        // count = 2;
    } else if (Entity.getlife() / Entity.getMaxLife() >= 0.2) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(1, 0, true));
        // heart_sprite.flip();
        // count = 2;

    } else {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(2, 0));
        // count = 2;
    }

    heart_sprite.setPosition(view.getCenter().x + Gamelenght / 2.3 + 32 * 1,
                             view.getCenter().y - Gameheight / 1.1);
    // heart_sprite.setPosition(32*2, 32);
    window.draw(heart_sprite);

    if (Entity.getlife() / Entity.getMaxLife() > 0.1) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(0, 0));
        // count = 1;
    } else if (Entity.getlife() / Entity.getMaxLife() > 0) {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(1, 0, true));
        // heart_sprite.flip();
        // count = 1;

    } else {
        heart_sprite.setTexture(Hearts_Main.getTexture());  // heart set texture to full heart
        heart_sprite.setTextureRect(Hearts_Main.getTextureCoords(2, 0));
    }

    heart_sprite.setPosition(view.getCenter().x + Gamelenght / 2.3,
                             view.getCenter().y - Gameheight / 1.1);
    // heart_sprite.setPosition(32*1, 32);
    window.draw(heart_sprite);
}
