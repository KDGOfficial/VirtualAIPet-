#include "TTS.h"
#include <iostream>

#ifdef PLATFORM_WINDOWS
  #include <windows.h>
  #include <sapi.h>
#endif

TTS::TTS() {
#ifdef PLATFORM_WINDOWS
    ::CoInitialize(NULL);
#endif
}

TTS::~TTS() {
#ifdef PLATFORM_WINDOWS
    ::CoUninitialize();
#endif
}

void TTS::speak(const std::string &text) {
#ifdef PLATFORM_WINDOWS
    ISpVoice * pVoice = nullptr;
    if (SUCCEEDED(::CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice))) {
        int wlen = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, nullptr, 0);
        std::wstring wtext(wlen, L'\\0');
        MultiByteToWideChar(CP_UTF8,0,text.c_str(),-1,&wtext[0],wlen);
        pVoice->Speak(wtext.c_str(), SPF_IS_XML, NULL);
        pVoice->Release();
    }
#elif defined(PLATFORM_UNIX)
    std::string cmd = "espeak \"" + text + "\" 2>/dev/null &";
    system(cmd.c_str());
#else
    std::cout << "[TTS] " << text << std::endl;
#endif
}