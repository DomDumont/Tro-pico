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
/*
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
*/
SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(bitmap, 512, 512, 8, 512, 0, 0,0,0);

if (surface == NULL)
{
	SDL_Log(SDL_GetError());
}
this->texture = SDL_CreateTextureFromSurface(g_app->pRenderer, surface);


//delete[] bitmap2;
delete[] bitmap;

SDL_FreeSurface(surface);



}


SDL_Texture * Font::RenderText(const std::string& _text, Color _color)
	{
	float extX;
	float extY;

	

	this->GetTextExtent(_text, extX, extY);

	SDL_Texture * tempTexture = SDL_CreateTexture(g_app->pRenderer, SDL_PIXELFORMAT_INDEX8, SDL_TEXTUREACCESS_TARGET, (int)extX, (int)extY);
	//SDL_SetTextureColorMod(tempTexture, _color.r, _color.g, _color.b);
	//SDL_SetTextureBlendMode(tempTexture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(g_app->pRenderer, tempTexture);

	float x = 0;
	float y = -2;
	int textLen = (int)_text.size();
	for (int i = 0; i < textLen; i++)
		{
		unsigned char ch = _text[i];

		if (ch == '\n')
			{
			x = 0;
			y += this->GetFontHeight();
			continue;
			}

		if (ch < 32 || ch > 128)
			ch = '?';

		stbtt_aligned_quad q;
		stbtt_GetBakedQuad(this->cdata,
						   512,
						   512,
						   ch - 32,  // position of character in font
						   &x,     // current position
						   &y,
						   &q,     // resulted quad
						   1);     // '1' for tex coords for opengl ('0' for d3d)

		float w = q.x1 - q.x0;
		float h = q.y1 - q.y0;



		SDL_Rect rect;
		rect.x = (int)q.x0;
		rect.y = (int)(this->GetFontHeight() + q.y0);
		rect.w = (int)w;
		rect.h = (int)h;

		SDL_Rect tex;
		tex.x = (int)(q.s0 * 512);
		tex.y = (int)(q.t0 * 512);
		tex.w = (int)((q.s1 - q.s0) * 512);
		tex.h = (int)((q.t1 - q.t0) * 512);

		SDL_RenderCopy(g_app->pRenderer, this->texture, &tex, &rect);
		}

	SDL_RenderCopy(g_app->pRenderer, tempTexture, NULL, NULL); // On fait le rendu de la texture
	SDL_SetRenderTarget(g_app->pRenderer, NULL); // On repasse en target normale

	return tempTexture;

	}

float Font::GetFontHeight()
	{
	return fontHeight;
	}


void Font::GetTextExtent(const std::string& _text, float & _x, float &_y)
	{
	float maxX = 0;
	float maxY = 0;

	_x = 0;
	_y = this->fontHeight;

	float xStart = 0;
	int textLen = (int)_text.size();
	for (int i = 0; i < textLen; i++)
		{
		unsigned char ch = _text[i];

		if (ch == '\n')
			{
			_x = xStart;
			_y += this->fontHeight;
			continue;
			}

		if (ch < 32 || ch > 128)
			ch = '?';

		stbtt_aligned_quad q;
		stbtt_GetBakedQuad(this->cdata,
						   512,
						   512,
						   ch - 32,  // position of character in font
						   &_x,     // current position
						   &_y,
						   &q,     // resulted quad
						   1);     // '1' for tex coords for opengl ('0' for d3d)
		if (_x > maxX)
			maxX = _x;
		if (_y > maxY)
			maxY = _y;

		}

	_x = maxX;
	_y = maxY;
	}