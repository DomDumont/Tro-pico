#include "Application.h"

Application *g_game;
int main(int argc, char *argv[])
{
	g_game = new Application();
	g_game->Init("Tro-pico",100,100,128,128,0);
	while(g_game->IsRunning())
		{	
		g_game->HandleEvents();
		g_game->Update();
		g_game->Render();
		}
	g_game->Shutdown();
	return 0;
}