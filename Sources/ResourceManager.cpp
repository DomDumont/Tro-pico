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


/*----------------------------------------------------------------------------*/

std::string ResourceManager::LoadTextFile(const std::string& _file)
	{
	std::string contents;


	SDL_RWops *rw;

	rw = this->Load(_file);

	if (rw != NULL)
		{
		/* Seek to 0 bytes from the end of the file */
		Sint64 length = SDL_RWseek(rw, 0, SEEK_END);
		SDL_RWseek(rw, 0, SEEK_SET);// ON retourne au début
		if (length <= 0)
			{
			SDL_Log("Could not seek inside %s\n", _file.c_str());
			return "";
			}
		else
			{
			SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "script is %llu bytes long\n", length);
			contents.resize((unsigned int)length);
			if (SDL_RWread(rw, &contents[0], contents.size(), 1) != 1)
				{
				SDL_Log("Error reading file %s\n", _file.c_str());
				return "";
				}
			SDL_RWclose(rw);
			return contents;
			}
		}
	else
		{
		return "";
		}
	}


/*----------------------------------------------------------------------------*/

unsigned char * ResourceManager::LoadBinaryFile(const std::string& _file)
	{
	unsigned char * pContent;


	SDL_RWops *rw;

	rw = this->Load(_file);

	if (rw != NULL)
		{
		/* Seek to 0 bytes from the end of the file */
		Sint64 length = SDL_RWseek(rw, 0, SEEK_END);
		SDL_RWseek(rw, 0, SEEK_SET);// ON retourne au début
		if (length <= 0)
			{
			SDL_Log("Could not seek inside %s\n", _file.c_str());
			return NULL;
			}
		else
			{
			SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "script is %llu bytes long\n", length);
			
			pContent = (unsigned char*) malloc(length);
			if (SDL_RWread(rw, pContent, length, 1) != 1)
				{
				SDL_Log("Error reading file %s\n", _file.c_str());
				return NULL;
				}
			SDL_RWclose(rw);
			return pContent;
			}
		}
	else
		{
		return NULL;
		}
	}
