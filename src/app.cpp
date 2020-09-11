#include <iostream>
#include <cstdint>
#include <vector>
#include <sstream>

#include "app.h"
#include "globals.h"
#include "textManager.h"
#include "ball.h"
#include "bar.h"

App::App(const char *appName)
{
  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
  {
    fprintf(stderr, "SDL could not init: %s\n", "my error" );
    throw std::runtime_error("");
  }

  gWindow = SDL_CreateWindow(
      appName,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN );
  if( !gWindow )
  {
    fprintf(stderr, "Window error: %s\n", SDL_GetError() );
    throw std::runtime_error("");
  }

  gRenderer = SDL_CreateRenderer(
      gWindow,
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
  if( !gRenderer )
  {
    fprintf(stderr, "Renderer error: %s\n", "my error" );
    throw std::runtime_error("");
  }

  SDL_RenderSetLogicalSize( gRenderer, L_WIDTH, L_HEIGHT );

  if( TTF_Init() == -1 )
  {
    fprintf( stderr, "TTF Error: %s\n", TTF_GetError() );
    throw std::runtime_error("");
  }

  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
    fprintf( stderr, "Mix Error: %s\n", Mix_GetError() );
    throw std::runtime_error("");
  }

  gFont = TTF_OpenFont( "fonts/04b_03.ttf", 80 ); // 8
  if( !gFont )
  {
    fprintf( stderr, "Error loading font: %s\n", TTF_GetError() );
    throw std::runtime_error("");
  }
}

App::~App()
{
  std::cout << "app dtor\n";
  for( auto e : soundFx ) {
    if( e.second ) {
      Mix_FreeChunk( e.second );
      e.second = nullptr;
    }
  }
  if( gFont ) {
    TTF_CloseFont( gFont );
    gFont = nullptr;
  }
  if( gRenderer ) {
    SDL_DestroyRenderer( gRenderer );
    gRenderer = nullptr;
  }
  if( gWindow ) {
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
  }
  TTF_Quit();
  SDL_Quit();
  Mix_Quit();
}

void App::mainloop()
{
  bool paused = false;
  uint32_t frame_counter = 0;
  SDL_Event e;
  bool quit = false;
  std::ostringstream oss;
  int p1score_val = 0;
  int p2score_val = 0;
  TextArea p1score_text( gRenderer, L_WIDTH / 2 - 80*2, 20, 0, 0 );
  TextArea p2score_text( gRenderer, L_WIDTH / 2 + 80, 20, 0, 0 );
  GlyphCache gc( gRenderer, gFont );
  std::vector<Bar> bars;
  soundFx["coin"] = Mix_LoadWAV("../assets/audio/coin.wav");
  soundFx["powup"] = Mix_LoadWAV("../assets/audio/powerup.wav");
  if( !soundFx["coin"] || !soundFx["powup"] )
    throw std::runtime_error( "Failed to load sound fx\n" );

  Ball ball;
  bars.push_back( Bar( RIGHT, L_WIDTH - 80 - Bar::BAR_WIDTH, 80, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT ) );
  bars.push_back( Bar( LEFT, 80, 80, SDLK_w, SDLK_s, SDLK_a, SDLK_d ) );

  while( !quit )
  {
    while( SDL_PollEvent( &e ) != 0 )
    {
      if( e.type == SDL_QUIT ) quit = true;
      if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
      {
        switch( e.key.keysym.sym )
        {
          case SDLK_p:
            paused = !paused;
            break;
          case SDLK_o:
            ball.reset();
            break;
        }
      }
      if( e.type == SDL_KEYUP && e.key.repeat == 0 )
      {
        //
      }
      if( !paused )
      for( auto i = bars.begin(); i < bars.end(); i++ )
        i->handleEvent( e );
    }

    if( !paused ) {
    switch( ball.move( bars ) )
    {
      case Collided:
        Mix_PlayChannel( -1, soundFx["coin"], 0 );
        break;
      case GoalLeft:
        Mix_PlayChannel( -1, soundFx["powup"], 0 );
        p2score_val ++;
        break;
      case GoalRight:
        Mix_PlayChannel( -1, soundFx["powup"], 0 );
        p1score_val ++;
        break;
      default:
        break;
    }

    for( auto i = bars.begin(); i < bars.end(); i++ )
      i->move();
    }

    SDL_SetRenderDrawColor( gRenderer, 0x42, 0x87, 0xf5, 0xFF );
    SDL_RenderClear( gRenderer );

    ball.render( gRenderer );
    for( auto i = bars.begin(); i < bars.end(); i++ )
      i->render( gRenderer );

    oss.str("");
    oss << p1score_val;
    p1score_text.renderPrint( gc, oss.str().c_str() );
    oss.str("");
    oss << p2score_val;
    p2score_text.renderPrint( gc, oss.str().c_str() );
    SDL_RenderDrawLine( gRenderer, L_WIDTH / 2, 0, L_WIDTH / 2, L_HEIGHT );

    SDL_RenderPresent( gRenderer );
    frame_counter++;
  }
}
