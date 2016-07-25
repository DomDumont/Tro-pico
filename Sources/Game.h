#ifndef __GAME_H__
#define __GAME_H__
#include <SDL.h>


class Game
{

public:
	void Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Shutdown();
	bool IsRunning();
	void HandleEvents();
	void Update();
	void Render();

private:
	bool bRunning;
	SDL_Window * pWindow;
	SDL_Renderer* pRenderer;
};




#endif
 
