#pragma once

#include <SDL.h>

enum Side { LEFT, RIGHT };
class Bar
{
  private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    SDL_Rect mCollider;
    const SDL_Keycode up, down, left, right;
    const Side side;

  public:
    static const int BAR_WIDTH = 60;
    static const int BAR_HEIGHT = 300;
    static const int VEL = 12;
    int getVelX() const { return mVelX; }
    int getVelY() const { return mVelY; }

    Bar( Side s, int x, int y, SDL_Keycode upkey, SDL_Keycode downkey, SDL_Keycode leftkey, SDL_Keycode rightkey );

    void handleEvent( SDL_Event &e );

    void move();

    void render( SDL_Renderer *r );
    
    const SDL_Rect& getCollider() const { return mCollider; };
};
