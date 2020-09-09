#include "bar.h"
#include "globals.h"

Bar::Bar()
{
  mPosX = 5;
  mPosY = 5;
  mVelX = mVelY = 0;
  mCollider.w = BAR_WIDTH;
  mCollider.h = BAR_HEIGHT;
  mCollider.x = mPosX;
  mCollider.y = mPosY;
}

void Bar::handleEvent( SDL_Event &e )
{
  if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
  {
    switch( e.key.keysym.sym )
    {
      case SDLK_UP: mVelY -= VEL; break;
      case SDLK_DOWN: mVelY += VEL; break;
      case SDLK_LEFT: break;
      case SDLK_RIGHT: break;
    }
  }
  else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
  {
    switch( e.key.keysym.sym )
    {
      case SDLK_UP: mVelY += VEL; break;
      case SDLK_DOWN: mVelY -= VEL; break;
      case SDLK_LEFT: break;
      case SDLK_RIGHT: break;
    }
  }
}

void Bar::move()
{
  mPosY += mVelY;
  mCollider.y = mPosY;
  if( mPosY < 0 || ( mPosY + BAR_HEIGHT > L_HEIGHT ) )
  {
    mPosY -= mVelY;
  }
}

void Bar::render( SDL_Renderer *r )
{
  SDL_SetRenderDrawColor( r, 0xff, 0xff, 0xff, 0xff );
  SDL_Rect rect{ mPosX, mPosY, BAR_WIDTH, BAR_HEIGHT };
  SDL_RenderFillRect( r, &rect );
}
