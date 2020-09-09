#include "ball.h"
#include "globals.h"

Ball::Ball()
{
  mPosX = 0;
  mPosY = 0;
  mVelX = BALL_VEL;
  mVelY = BALL_VEL;
  mCollider.w = BALL_WIDTH;
  mCollider.h = BALL_HEIGHT;
}

bool Ball::checkCollision( const SDL_Rect &a, const SDL_Rect &b )
{
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;

  if( bottomA <= topB ) return false;
  if( topA >= bottomB ) return false;
  if( rightA <= leftB ) return false;
  if( leftA >= rightB ) return false;
  return true;
}

void Ball::handleEvent( SDL_Event &e )
{
  if( e.type == SDL_KEYDOWN && e.key.repeat != 0 )
  {
    switch( e.key.keysym.sym )
    {
      case SDLK_UP: break;
      case SDLK_DOWN: break;
      case SDLK_LEFT: break;
      case SDLK_RIGHT: break;
    }
  }
}

bool Ball::move( const SDL_Rect &bar )
{
  bool collided = false;

  mPosX += mVelX;
  mCollider.x = mPosX;
  if( ( mPosX < 0 ) || ( mPosX + BALL_WIDTH > L_WIDTH ) || checkCollision( mCollider, bar ) )
  {
    mVelX = -mVelX;
    collided = true;
  }

  mPosY += mVelY;
  mCollider.y = mPosY;
  if( ( mPosY < 0 ) || ( mPosY + BALL_HEIGHT > L_HEIGHT ) || checkCollision( mCollider, bar ))
  {
    mVelY = -mVelY;
    collided = true;
  }
  return collided;
}

void Ball::render( SDL_Renderer *r )
{
  SDL_Rect rect{ mPosX, mPosY, BALL_WIDTH, BALL_HEIGHT };
  SDL_SetRenderDrawColor( r, 0xff, 0xff, 0xff, 0xff );
  SDL_RenderFillRect( r, &rect );
}

