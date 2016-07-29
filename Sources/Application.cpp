#include "Application.h"
#include "AudioManager.h"
#include "config.h"
#include "Font.h"
#include "Shaders.h"


Application *g_app;

bool Application::Init(std::string title, int xpos, int ypos, int width,int height, int flags)
{
	std::string tempTitle;
	tempTitle=  title + " " + GIT_DESCRIBE_VERSION;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
		return false;
		}
		
	//if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &pWindow, &pRenderer) < 0)
	
	pWindow = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
	if (pWindow == NULL)
	
		{
		return false;
		}

	mainContext = SDL_GL_CreateContext(pWindow);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1);

	GLenum glewError = glewInit();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	AudioManager::Get().Init();

	bRunning = true;

	Shaders * pTempShader = new Shaders();
	pTempShader->LoadFromFile("simple");
	
	return true;
}


void Application::Shutdown()
{
	SDL_GL_DeleteContext(mainContext);
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
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT );

	glMatrixMode(GL_MODELVIEW);
	
    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    //glTranslatef( -1.5f, 0.0f, -6.0f );

    glBegin( GL_TRIANGLES );            /* Drawing Using Triangles */
      glVertex3f(  0.0f,  1.0f, 0.0f ); /* Top */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
    glEnd( );                           /* Finished Drawing The Triangle */

    /* Move Right 3 Units */
    //glTranslatef( 3.0f, 0.0f, 0.0f );
	/*
    glBegin( GL_QUADS );   
      glVertex3f( -1.0f,  1.0f, 0.0f ); 
      glVertex3f(  1.0f,  1.0f, 0.0f ); 
      glVertex3f(  1.0f, -1.0f, 0.0f ); 
      glVertex3f( -1.0f, -1.0f, 0.0f ); 
    glEnd( );                           
	*/
    
	SDL_GL_SwapWindow(pWindow);
}
