#include "Game.h"
#include "AudioManager.h"


bool Game::Init(const char* title, int xpos, int ypos, int width,int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{

		// init the window
		pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (pWindow != 0) // window init success
			{
			pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
			}
		else
			{
				return false;
			}
		}

	pAudioManager = new AudioManager();
	pAudioManager->Init();

	bRunning = true;
	return true;
}


void Game::Shutdown()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
}




bool Game::IsRunning()
{
	return bRunning;
}

void Game::HandleEvents()
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

void Game::Update()
{

}

void Game::Render()
{
	SDL_RenderClear(pRenderer); 

	SDL_RenderPresent(pRenderer); 
}
