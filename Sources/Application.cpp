#include "Application.h"
#include "AudioManager.h"
#include "config.h"

bool Application::Init(std::string title, int xpos, int ypos, int width,int height, int flags)
{
	std::string tempTitle;
	tempTitle=  title + " " + GIT_DESCRIBE_VERSION;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{

		// init the window
		pWindow = SDL_CreateWindow(tempTitle.c_str(), xpos, ypos, width, height, flags);
		if (pWindow != 0) // window init success
			{
			pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
			}
		else
			{
				return false;
			}
		}

	AudioManager::Get().Init();

	bRunning = true;
	return true;
}


void Application::Shutdown()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
}




bool Application::IsRunning()
{
	return bRunning;
}

void Application::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
		{
		switch (event.type)
			{
			case SDL_QUIT:
				bRunning = false;
				break;
			default:
				break;
			}
		}
}

void Application::Update()
{

}

void Application::Render()
{
	SDL_RenderClear(pRenderer); 

	SDL_RenderPresent(pRenderer); 
}
