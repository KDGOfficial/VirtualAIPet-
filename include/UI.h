#pragma once
#include <SFML/Graphics.hpp>
#include "Pet.h"
#include "PetAI.h"

class UI {
public:
    UI();
    bool init();
    void run(Pet &pet, PetAI &ai);
private:
    sf::RenderWindow window_;
    sf::Texture spriteTex_;
    sf::Sprite sprite_;
    sf::Font font_;
    sf::Text statusText_;
    void handleEvents(Pet &pet, PetAI &ai);
    void draw(const Pet &pet);
};