#include "Global.h"
#include "Application.h"


int main(int argc, char *argv[])
{
	g_app = new Application();
	g_app->Init("Tro-pico",100,100,256,256,0);
	while(g_app->IsRunning())
		{	
		g_app->HandleEvents();
		g_app->Update();
		g_app->Render();
		}
	g_app->Shutdown();
	return 0;
}
