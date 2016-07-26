#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

class AudioManager
{
    public:
    	static AudioManager& Get();
        bool Init();

    private:
    	AudioManager();
};

#endif