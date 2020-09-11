#include <iostream> 

#include "bar.h"
#include "globals.h"

Bar::Bar( Side s, int x, int y, SDL_Keycode upkey, SDL_Keycode downkey, SDL_Keycode leftkey, SDL_Keycode rightkey )
  : up( upkey ), down( downkey ), left( leftkey ), right( rightkey ), side( s )
{
  mPosX = x;
  mPosY = y;
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
    if( e.key.keysym.sym == up ) mVelY -= VEL;
    if( e.key.keysym.sym == down ) mVelY += VEL;
    if( e.key.keysym.sym == left ) mVelX -= VEL;
    if( e.key.keysym.sym == right ) mVelX += VEL;
  }
  else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
  {
    if( e.key.keysym.sym == up ) mVelY += VEL;
    if( e.key.keysym.sym == down ) mVelY -= VEL;
    if( e.key.keysym.sym == left ) mVelX += VEL;
    if( e.key.keysym.sym == right ) mVelX -= VEL;
  }
}

void Bar::move()
{
  mPosY += mVelY;
  if( mPosY < 0 || ( mPosY + BAR_HEIGHT > L_HEIGHT ) )
  {
    mPosY -= mVelY;
  }
  mCollider.y = mPosY;

  if( side == LEFT )
  {
    mPosX += mVelX;
    if( mPosX < 0 || ( mPosX + BAR_WIDTH > L_WIDTH / 2 ) )
    {
      mPosX -= mVelX;
    }
    mCollider.x = mPosX;
  }
  else if( side == RIGHT )
  {
    mPosX += mVelX;
    if( mPosX < L_WIDTH / 2 || ( mPosX + BAR_WIDTH > L_WIDTH ) )
    {
      mPosX -= mVelX;
    }
    mCollider.x = mPosX;
  }
}

void Bar::render( SDL_Renderer *r )
{
  SDL_SetRenderDrawColor( r, 0xff, 0xff, 0xff, 0xff );
  SDL_Rect rect{ mPosX, mPosY, BAR_WIDTH, BAR_HEIGHT };
  SDL_RenderFillRect( r, &rect );
}
