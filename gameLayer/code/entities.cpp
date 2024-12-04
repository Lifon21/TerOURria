#include <iostream>

#include "gameLayer\header_file\entitites.hpp"

using namespace std;

float entities::getlife() { return life; }
float entities::getMaxLife() { return maxlife; }

void entities::dealdamage(float damage) {
    life-=damage;
}


void entities::insertinventory(int num){
    if (count(inventory.begin(), inventory.end(), num) == 0){
        inventory.push_back(num);
    }
}

void entities::deleteinventory(int num){
    auto it = std::find(inventory.begin(), inventory.end(), num);
    if (it != inventory.end()) {
        inventory.erase(it);
    }
}

void entities::setlife(float num){

    this->life = num;


}
