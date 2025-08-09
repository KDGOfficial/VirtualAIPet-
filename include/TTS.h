#pragma once
#include <string>

class TTS {
public:
    TTS();
    ~TTS();
    void speak(const std::string &text);
};