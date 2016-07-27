#include "Global.h"

#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation

#include "SDL.h"

#include "Application.h"
#include "Font.h"
#include "ResourceManager.h"


/*----------------------------------------------------------------------------*/

void Font::Load(const std::string& _file, int _size)
{

unsigned char *bitmap = new unsigned char[512 * 512];

SDL_RWops*  tempFlow = ResourceManager::Get().Load(_file);
if (tempFlow != NULL)
  {
  int flowSize = (int)SDL_RWsize(tempFlow);
  unsigned char *raw = new unsigned char[flowSize];
  SDL_RWread(tempFlow, raw, flowSize, 1);
  
  this->cdata = new stbtt_bakedchar[96];

  this->fontHeight = (float) _size;

  stbtt_BakeFontBitmap((const unsigned char*)raw,
                       0,
                       this->fontHeight,
                       bitmap,
                       512,
                       512,
                       32,
                       96,
                       (stbtt_bakedchar*)(this->cdata));

  delete[] raw;
  SDL_RWclose(tempFlow);
  }

unsigned char* bitmap2 = new unsigned char[512 * 512 * 4];
int ss = 512 * 512;
for (int i = 0; i < ss; i++)
  {
  bitmap2[i * 4 + 0] = 0xff;
  bitmap2[i * 4 + 1] = 0xff;
  bitmap2[i * 4 + 2] = 0xff;
  bitmap2[i * 4 + 3] = bitmap[i];
  }
delete [] bitmap;

SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(bitmap2, 512, 512,
                                                4 * 8, 512 * 4, 0xff, 0xff00, 0xff0000, 0xff000000);
this->texture = SDL_CreateTextureFromSurface(g_app->pRenderer, surface);


delete[] bitmap2;

SDL_FreeSurface(surface);



}