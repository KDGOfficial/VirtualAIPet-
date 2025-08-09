#pragma once
#include <string>
#include "Pet.h"

class PetAI {
public:
    PetAI();
    std::string respond(const std::string &userInput, const PetState &state);
private:
    std::string ruleRespond(const std::string &userInput, const PetState &state);
};