#ifndef __FONT_H__
#define __FONT_H__

#include <string>
#include "stb_truetype.h"
#include "Color.h"

struct SDL_Texture; //TODO remove this one


class Font
{

public:
	void Load(const std::string& _file, int _size);
	SDL_Texture * Font::RenderText(const std::string& _text, Color _color);
	void GetTextExtent(const std::string& _text, float & _x, float &_y);
	float GetFontHeight();
public:
	SDL_Texture*      texture;      //!< font texture
	stbtt_bakedchar*  cdata;    //!< font data: ASCII 32..126 is 95 glyphs
	float             fontHeight;

};

#endif