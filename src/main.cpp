#include "Pet.h"
#include "PetAI.h"
#include "UI.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    Pet pet;
    std::ifstream in("save.json");
    if (in.is_open()) {
        try {
            json j; in >> j;
            pet.loadFromJson(j);
            std::cout << "Loaded state\n";
        } catch (...) {
            std::cout << "Failed to load save.json\n";
        }
    }

    PetAI ai;
    UI ui;
    if (!ui.init()) {
        std::cerr << "UI init failed\n";
        return 1;
    }
    ui.run(pet, ai);

    json out = pet.saveToJson();
    std::ofstream o("save.json");
    o << out.dump(4);
    std::cout << "Saved state\n";
    return 0;
}