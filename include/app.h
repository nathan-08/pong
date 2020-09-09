#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <map>

class App
{
  private:
    SDL_Window *gWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;
    TTF_Font *gFont = nullptr;
    std::map<std::string, Mix_Chunk*> soundFx;
  public:
    App(const char *appName);
    ~App();
    void mainloop();
};
