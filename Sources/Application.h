#ifndef __GAME_H__
#define __GAME_H__
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>



class Application
{

public:
	bool Init(std::string title, int xpos, int ypos, int width, int height, int flags);
	void Shutdown();
	bool IsRunning();
	void HandleEvents();
	void Update();
	void Render();

public:
	bool bRunning;
	SDL_Window * pWindow;
	SDL_Renderer* pRenderer;
	SDL_GLContext mainContext;


};




#endif
 
