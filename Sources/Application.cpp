#include "Application.h"
#include "AudioManager.h"
#include "config.h"
#include "Font.h"

Application *g_app;

bool Application::Init(std::string title, int xpos, int ypos, int width,int height, int flags)
{
	std::string tempTitle;
	tempTitle=  title + " " + GIT_DESCRIBE_VERSION;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
		return false;
		}
		
	if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &pWindow, &pRenderer) < 0)
	{
		return false;
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
 	/* Set the background black */
    glClearColor( 1.0f, 0.0f, 0.0f, 0.0f );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef( -1.5f, 0.0f, -6.0f );

    glBegin( GL_TRIANGLES );            /* Drawing Using Triangles */
      glVertex3f(  0.0f,  1.0f, 0.0f ); /* Top */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
    glEnd( );                           /* Finished Drawing The Triangle */

    /* Move Right 3 Units */
    glTranslatef( 3.0f, 0.0f, 0.0f );

    glBegin( GL_QUADS );                /* Draw A Quad */
      glVertex3f( -1.0f,  1.0f, 0.0f ); /* Top Left */
      glVertex3f(  1.0f,  1.0f, 0.0f ); /* Top Right */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
    glEnd( );                           /* Done Drawing The Quad */
    
	SDL_RenderPresent(pRenderer);
}
