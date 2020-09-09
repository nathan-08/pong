#pragma once

#include <SDL.h>

class Bar
{
  private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    SDL_Rect mCollider;

  public:
    static const int BAR_WIDTH = 1;
    static const int BAR_HEIGHT = 4;
    static const int VEL = 1;

    Bar();

    void handleEvent( SDL_Event &e );

    void move();

    void render( SDL_Renderer *r );
    
    const SDL_Rect& getCollider() { return mCollider; };
};
