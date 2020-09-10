#pragma once

#include <SDL.h>

class Bar
{
  private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    SDL_Rect mCollider;

  public:
    static const int BAR_WIDTH = 300;
    static const int BAR_HEIGHT = 60;
    static const int VEL = 12;
    int getVelX() const { return mVelX; }
    int getVelY() const { return mVelY; }

    Bar( int x, int y );

    void handleEvent( SDL_Event &e );

    void move();

    void render( SDL_Renderer *r );
    
    const SDL_Rect& getCollider() const { return mCollider; };
};
