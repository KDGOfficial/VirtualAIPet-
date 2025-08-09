#pragma once
#include <string>
#include <chrono>
#include <nlohmann/json.hpp>

struct PetState {
    int hunger = 50;     // 0..100 (0 — starving)
    int energy = 80;     // 0..100
    int happiness = 70;  // 0..100
    int health = 100;    // 0..100
    std::chrono::system_clock::time_point lastUpdated;
};

class Pet {
public:
    Pet();
    void update(); // called on each tick
    void feed(int amount = 20);
    void sleep(int amount = 30);
    void play(int amount = 15);
    void heal(int amount = 20);
    PetState getState() const;
    void loadFromJson(const nlohmann::json &j);
    nlohmann::json saveToJson() const;
private:
    PetState state_;
    std::chrono::system_clock::time_point now() const;
};