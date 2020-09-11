#include <string>

#include "textManager.h"

static std::string getCharlist()
{
  std::string charlist;
  for( int i = 0; i < 255; i++ )
  {
    if( isgraph( i ) ) charlist += i;
  }
  charlist += ' ';
  return charlist;
}

GlyphCache::GlyphCache( SDL_Renderer *r, TTF_Font *f )
  : renderer(r), font(f)
{
  std::string charlist = getCharlist();
  int xoffset = 0;
  for( const char &ch : charlist )
  {
    int minx, maxx, miny, maxy, advance;
    TTF_GlyphMetrics( font, ch, &minx, &maxx, &miny, &maxy, &advance );
    int fheight = TTF_FontHeight( font );
    glyph_map[ ch ] = SDL_Rect { xoffset, 0, advance, fheight }; // 8
    xoffset += advance;
  }
  // generate glyphset texture
  SDL_Surface *s = TTF_RenderText_Solid(
      font,
      charlist.c_str(),
      SDL_Color{ 0xff, 0xff, 0xff, 0xff } );

  glyphset = SDL_CreateTextureFromSurface( renderer, s );
  SDL_FreeSurface( s );
}

GlyphCache::~GlyphCache()
{
  if( glyphset )
  {
    SDL_DestroyTexture( glyphset );
    glyphset = nullptr;
  }
}

TextArea::TextArea( SDL_Renderer *r, int x, int y, int w, int h )
    : renderer(r), _x(x), _y(y), _w(w), _h(h)
{}

int TextArea::getW() { return _w; }
int TextArea::getH() { return _h; }

void TextArea::renderPrint( const GlyphCache &gc, const char *text )
{
  int xoffset = _x;
  int yoffset = _y;

  for( int i = 0; text[i] != '\0'; i++ )
  {
    if( text[i] == '\n' )
    {
      yoffset += 8;
      xoffset = _x;
      continue;
    }

    SDL_Rect rect = gc.glyph_map.at( text[i] );
    SDL_Rect destrect = { xoffset, yoffset, rect.w, rect.h };
    SDL_RenderCopy( renderer, gc.glyphset, &rect, &destrect );
    xoffset += rect.w;
  }

}
