#include "ResourceManager.h"
#include <SDL.h>

/*----------------------------------------------------------------------------*/

ResourceManager& ResourceManager::Get()
	{
	static ResourceManager foo;
	return foo;
	}

/*----------------------------------------------------------------------------*/

ResourceManager::ResourceManager()
	{

	}

/*----------------------------------------------------------------------------*/

ResourceManager::~ResourceManager()
	{

	}

/*----------------------------------------------------------------------------*/

SDL_RWops*  ResourceManager::Load(const std::string & _file)
	{
#if defined TARGET_WIN32 || defined TARGET_LINUX || defined TARGET_OSX 
	std::string tempFile = "";

	tempFile = ".//" + _file;
	SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "tempfile = %s", tempFile.c_str());
	return SDL_RWFromFile(tempFile.c_str(), "rb");
#else

	return NULL;
#endif

	}