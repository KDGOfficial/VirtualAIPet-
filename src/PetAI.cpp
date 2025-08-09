#include "PetAI.h"
#include <algorithm>

static std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
    return s;
}

PetAI::PetAI() {}

std::string PetAI::respond(const std::string &userInput, const PetState &state) {
    return ruleRespond(toLower(userInput), state);
}

std::string PetAI::ruleRespond(const std::string &u, const PetState &state) {
    if (u.find("привет") != std::string::npos || u.find("hello") != std::string::npos) {
        return "Привет! Я твой питомец 😊";
    }
    if (u.find("как") != std::string::npos && u.find("дела") != std::string::npos) {
        return "Я: hunger=" + std::to_string(state.hunger) + " energy=" + std::to_string(state.energy) + " happy=" + std::to_string(state.happiness);
    }
    if (u.find("корм") != std::string::npos || u.find("feed") != std::string::npos) {
        return "Спасибо! Я люблю еду.";
    }
    if (u.find("спать") != std::string::npos || u.find("sleep") != std::string::npos) {
        return "Хочу поспать... zzz";
    }
    if (u.size() < 4) return "Мяу?";
    return "Интересно... расскажи ещё!";
}