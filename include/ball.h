#pragma once

#include <SDL.h>
#include <vector>

#include "bar.h"

enum CollisionAxis { None = 0, Horiz = 1, Vert = 2, Both = 3 };
class Ball
{
  private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    SDL_Rect mCollider;
    CollisionAxis checkCollision( const Bar &bar );

  public:
    static const int BALL_VEL = 6;
    static const int BALL_WIDTH = 60;
    static const int BALL_HEIGHT = 60;
    Ball();

    void handleEvent( SDL_Event &e );

    bool move( const SDL_Rect &bar );
    bool move( const std::vector<Bar> &bars );

    void render( SDL_Renderer *r );
};
