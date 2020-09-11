#pragma once

#include <SDL.h>
#include <vector>

#include "bar.h"

enum MoveResult { Default, Collided, GoalLeft, GoalRight };
enum CollisionAxis { None = 0, Horiz = 1, Vert = 2, Both = 3 };
class Ball
{
  private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    SDL_Rect mCollider;
    CollisionAxis checkCollision( const Bar &bar );
    bool isActive = false;

  public:
    static const int BALL_VEL = 6;
    static const int BALL_WIDTH = 60;
    static const int BALL_HEIGHT = 60;
    Ball();

    void handleEvent( SDL_Event &e );

    MoveResult move( const std::vector<Bar> &bars );

    void render( SDL_Renderer *r );
    bool getIsActive() const { return isActive; }
    void reset();
};
