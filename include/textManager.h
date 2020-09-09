#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>

class GlyphCache
{
  private:
    SDL_Renderer *renderer;
    TTF_Font *font;
  public:
    std::map<char, SDL_Rect> glyph_map;

    SDL_Texture *glyphset = nullptr;

    GlyphCache( SDL_Renderer *r, TTF_Font *f );

    ~GlyphCache();
};

class TextArea
{
  private:
    SDL_Renderer *renderer;
    int _x, _y, _w, _h;
  public:
    int getW();
    int getH();
    TextArea( SDL_Renderer *r, int x, int y, int w, int h );

    void renderPrint( const GlyphCache &gc, const char *text );
};
