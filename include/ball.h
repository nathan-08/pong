#pragma once

#include <SDL.h>

class Ball
{
  private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    SDL_Rect mCollider;

  public:
    static bool checkCollision( const SDL_Rect &a, const SDL_Rect &b );
    static const int BALL_VEL = 1;
    static const int BALL_WIDTH = 1;
    static const int BALL_HEIGHT = 1;
    Ball();

    void handleEvent( SDL_Event &e );

    bool move( const SDL_Rect &bar );

    void render( SDL_Renderer *r );
};
