#include "Pet.h"
#include <algorithm>

using json = nlohmann::json;

Pet::Pet() {
    state_.lastUpdated = now();
}

std::chrono::system_clock::time_point Pet::now() const {
    return std::chrono::system_clock::now();
}

void Pet::update() {
    auto cur = now();
    auto dur = std::chrono::duration_cast<std::chrono::seconds>(cur - state_.lastUpdated).count();
    if (dur <= 0) return;
    int minutes = static_cast<int>(dur / 60);
    if (minutes <= 0) return;
    state_.lastUpdated = cur;
    state_.hunger = std::min(100, state_.hunger + minutes * 1); // gets hungrier
    state_.energy = std::max(0, state_.energy - minutes * 1);
    if (state_.hunger > 90) {
        state_.health = std::max(0, state_.health - (state_.hunger - 90));
    }
}

void Pet::feed(int amount) {
    state_.hunger = std::max(0, state_.hunger - amount);
    state_.happiness = std::min(100, state_.happiness + 5);
}

void Pet::sleep(int amount) {
    state_.energy = std::min(100, state_.energy + amount);
    state_.happiness = std::min(100, state_.happiness + 5);
}

void Pet::play(int amount) {
    state_.happiness = std::min(100, state_.happiness + amount);
    state_.energy = std::max(0, state_.energy - 10);
}

void Pet::heal(int amount) {
    state_.health = std::min(100, state_.health + amount);
    state_.happiness = std::min(100, state_.happiness + 5);
}

PetState Pet::getState() const {
    return state_;
}

void Pet::loadFromJson(const json &j) {
    if (j.contains("hunger")) state_.hunger = j["hunger"].get<int>();
    if (j.contains("energy")) state_.energy = j["energy"].get<int>();
    if (j.contains("happiness")) state_.happiness = j["happiness"].get<int>();
    if (j.contains("health")) state_.health = j["health"].get<int>();
    if (j.contains("lastUpdated")) {
        auto t = j["lastUpdated"].get<long long>();
        state_.lastUpdated = std::chrono::system_clock::time_point(std::chrono::milliseconds(t));
    }
}

json Pet::saveToJson() const {
    json j;
    j["hunger"] = state_.hunger;
    j["energy"] = state_.energy;
    j["happiness"] = state_.happiness;
    j["health"] = state_.health;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(state_.lastUpdated.time_since_epoch()).count();
    j["lastUpdated"] = ms;
    return j;
}