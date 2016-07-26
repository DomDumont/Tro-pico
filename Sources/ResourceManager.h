#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <string>



struct SDL_RWops; //TODO certainly remove this one also

class ResourceManager
	{
	public:
		static ResourceManager& Get();

		~ResourceManager();


		SDL_RWops*  Load(const std::string & _file);

	private:
		ResourceManager();

	};

#endif