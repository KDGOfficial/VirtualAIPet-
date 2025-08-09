#include "UI.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TTS.h"
using json = nlohmann::json;

UI::UI() {}

bool UI::init() {
    sf::VideoMode vm(300, 180);
    sf::ContextSettings settings;
    window_.create(vm, "VirtualPet", sf::Style::Default, settings);
    window_.setVerticalSyncEnabled(true);

    if (!spriteTex_.loadFromFile("resources/sprite_idle.png")) {
        sf::Image img;
        img.create(128,128, sf::Color::Green);
        spriteTex_.loadFromImage(img);
    }
    sprite_.setTexture(spriteTex_);
    sprite_.setPosition(10, 10);

    if (!font_.loadFromFile("resources/font.ttf")) {
        // if font missing SFML will still function but text may not display
    }

    statusText_.setFont(font_);
    statusText_.setCharacterSize(14);
    statusText_.setPosition(150, 10);
    statusText_.setFillColor(sf::Color::White);
    return true;
}

void UI::run(Pet &pet, PetAI &ai) {
    TTS tts;
    while (window_.isOpen()) {
        pet.update();
        handleEvents(pet, ai);
        draw(pet);
        sf::sleep(sf::milliseconds(100));
    }
}

void UI::handleEvents(Pet &pet, PetAI &ai) {
    sf::Event ev;
    while (window_.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) window_.close();
        if (ev.type == sf::Event::MouseButtonPressed) {
            auto pos = sf::Mouse::getPosition(window_);
            if (pos.x < 140) {
                pet.play(20);
            } else {
                pet.feed(20);
            }
        }
    }
}

void UI::draw(const Pet &pet) {
    window_.clear(sf::Color(50,50,70));
    window_.draw(sprite_);
    auto s = pet.getState();
    statusText_.setString(
        "Hunger: " + std::to_string(s.hunger) + "\n" +
        "Energy: " + std::to_string(s.energy) + "\n" +
        "Happy: " + std::to_string(s.happiness) + "\n" +
        "Health: " + std::to_string(s.health)
    );
    window_.draw(statusText_);
    window_.display();
}