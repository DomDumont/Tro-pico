#include "AudioManager.h"

/*----------------------------------------------------------------------------*/

AudioManager& AudioManager::Get()
{
	static AudioManager foo;
	return foo;
}

/*----------------------------------------------------------------------------*/

AudioManager::AudioManager()
{
	
}


/*----------------------------------------------------------------------------*/

bool AudioManager::Init()
{
	return false;
}