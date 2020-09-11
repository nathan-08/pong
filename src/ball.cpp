#include "ball.h"
#include "globals.h"

Ball::Ball()
{
  mPosX = L_WIDTH / 2;
  mPosY = 0;
  mVelX = BALL_VEL;
  mVelY = BALL_VEL;
  mCollider.w = BALL_WIDTH;
  mCollider.h = BALL_HEIGHT;
}

CollisionAxis Ball::checkCollision( const Bar &bar )
{
  const SDL_Rect a = mCollider;
  const SDL_Rect b = bar.getCollider();

  int barVelX = bar.getVelX();
  int barVelY = bar.getVelY();

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

  // determine if within vertical range of object
  if( bottomA - mVelY > topB + Bar::VEL && topA - mVelY < bottomB - Bar::VEL )
  {
    // within vertical range
    // determine horizontal direction

    if( rightA > leftB  // check for horizontal collision
        && leftA < rightB )
    {
      if( mVelX > 0 ) // moving right
      {
        if( barVelX <= 0 )
        {
          mVelX = barVelX ? barVelX : -BALL_VEL;
          mPosX = leftB - BALL_WIDTH + mVelX;
          mCollider.x = mPosX;

          mVelY = barVelY ? barVelY : mVelY;
        }
        else if( barVelX > 0 )
        {
          mVelX = barVelX;
          mPosX = rightB + mVelX;
          mCollider.x = mPosX;

          mVelY = barVelY ? barVelY : mVelY;
        }
      }
      else if( mVelX < 0 ) // moving left
      {
        if( barVelX >= 0 )
        {
          mVelX = barVelX ? barVelX : BALL_VEL;
          mPosX = rightB + mVelX;
          mCollider.x = mPosX;

          mVelY = barVelY ? barVelY : mVelY;
        }
        else if( barVelX < 0 )
        {
          mVelX = barVelX;
          mPosX = leftB - BALL_WIDTH + mVelX;
          mCollider.x = mPosX;

          mVelY = barVelY ? barVelY : mVelY;
        }
      }
      mPosY += mVelY;
      mCollider.y = mPosY;

      return Vert;
    }
  }
  if( rightA > leftB && leftA < rightB )
  {
    // within horizontal range
    // determine vertical direction

    if( bottomA > topB  // check for vertical collision
        && topA < bottomB )
    {
      if( mVelY > 0 ) // moving down
      {
        if( barVelY <= 0 )
        {
          mVelY = barVelY ? barVelY : -BALL_VEL;
          mPosY = topB - BALL_HEIGHT + mVelY;
          mCollider.y = mPosY;

          mVelX = barVelX ? barVelX : mVelX;
        }
        else if( barVelY > 0)
        {
          mVelY = barVelY;
          mPosY = bottomB + mVelY;
          mCollider.y = mPosY;

          mVelX = barVelX ? barVelX : mVelX;
        }
      }
      else if( mVelY < 0 ) // moving up
      {
        if( barVelY >= 0 )
        {
          mVelY = barVelY ? barVelY : BALL_VEL;
          mPosY = bottomB + mVelY;
          mCollider.y = mPosY;

          mVelX = barVelX ? barVelX : mVelX;
        }
        else if( barVelY < 0 )
        {
          mVelY = barVelY;
          mPosY = topB - BALL_HEIGHT + mVelY;
          mCollider.y = mPosY;

          mVelX = barVelX ? barVelX : mVelX;
        }
      }
      mPosX += mVelX;
      mCollider.x = mPosX;

      return Horiz;
    }
  }

  return None;
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

MoveResult Ball::move( const std::vector<Bar> &bars )
{
  if( !isActive ) return Default;
  bool collided = false;

  for( auto bar : bars )
  {
    CollisionAxis a = checkCollision( bar );
    switch( a )
    {
      case Horiz:
      case Vert:
        return Collided;
      default:
        break;
    }
  }

  mPosX += mVelX;
  mCollider.x = mPosX;
  if( mPosX < 0 ) {
    mPosX = 0;
    mCollider.x = mPosX;
    mVelX = -mVelX;
    isActive = false;
    return GoalLeft;
  }
  if( mPosX + BALL_WIDTH > L_WIDTH )
  {
    mPosX = L_WIDTH - BALL_WIDTH;
    mCollider.x = mPosX;
    mVelX = -mVelX;
    isActive = false;
    return GoalRight;
  }

  mPosY += mVelY;
  mCollider.y = mPosY;
  if( mPosY < 0 )
  {
    mPosY = 0;
    mCollider.y = 0;
    mVelY = -mVelY;
    collided = true;
  }
  if( mPosY + BALL_HEIGHT > L_HEIGHT )
  {
    mPosY = L_HEIGHT - BALL_HEIGHT;
    mCollider.y = mPosY;
    mVelY = -mVelY;
    collided = true;
  }

  return collided ? Collided : Default;
}

void Ball::render( SDL_Renderer *r )
{
  if( !isActive ) return;
  SDL_Rect rect{ mPosX, mPosY, BALL_WIDTH, BALL_HEIGHT };
  SDL_SetRenderDrawColor( r, 0xff, 0xff, 0xff, 0xff );
  SDL_RenderFillRect( r, &rect );
}

void Ball::reset()
{
  if( isActive ) return;
  isActive = true;
  mPosX = L_WIDTH / 2;
  mPosY = L_HEIGHT / 2;
  mCollider.x = mPosX;
  mCollider.y = mPosY;
  mVelX = BALL_VEL;
  mVelY = BALL_VEL;
}
