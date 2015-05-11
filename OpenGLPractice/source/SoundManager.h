#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <fmod\fmod.hpp>
#include <map>
#include <string>

struct SoundPiece
{
	FMOD::Sound* sound;
	FMOD::Channel* currentChannel;
	FMOD::Channel* prevChannel;
	FMOD::ChannelGroup* groupChannel;

	SoundPiece()
	{
		sound = nullptr;
		currentChannel = nullptr;
		prevChannel = nullptr;
		groupChannel = nullptr;
	}
};

class SoundManager
{
public:
	static SoundManager& Instance();

	void Play(std::string a_TrackName);

	void Update();

	void ErrorCheck(FMOD_RESULT a_Result, const char* error_message);

	~SoundManager();
private:
	SoundManager(const SoundManager&) = delete;
	void operator=(const SoundManager&) = delete;

	SoundManager();

	FMOD::System* system;
	FMOD::ChannelGroup* MainChannel;
	FMOD::Channel* firstSoundChannel;
	FMOD::Sound* firstSound;

	std::map<std::string, SoundPiece> sounds;
};

#endif