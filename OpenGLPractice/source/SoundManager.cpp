#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::Instance()
{
	static SoundManager instance;
	return instance;
}

SoundManager::SoundManager()
{
	ErrorCheck(FMOD::System_Create(&system), "FAILED TO CREATE FMOD SYSTEM");
	ErrorCheck(system->init(100, FMOD_INIT_NORMAL, nullptr), "FAILED TO INIT FMOD SYSTEM");
	ErrorCheck(system->createChannelGroup("Main", &MainChannel), "FAILED TO CREATE MAIN CHANNEL GROUP");

	ErrorCheck(system->createSound("resources/explosion1.ogg", FMOD_DEFAULT, nullptr, &sounds["explosion1"].sound), "FAILED TO CREATE SOUND");
	ErrorCheck(system->createSound("resources/explosion2.ogg", FMOD_DEFAULT, nullptr, &sounds["explosion2"].sound), "FAILED TO CREATE SOUND");
	ErrorCheck(system->createSound("resources/explosion3.ogg", FMOD_DEFAULT, nullptr, &sounds["explosion3"].sound), "FAILED TO CREATE SOUND");

	ErrorCheck(system->createSound("resources/laser_shoot1.ogg", FMOD_DEFAULT, nullptr, &sounds["lasershoot1"].sound), "FAILED TO CREATE SOUND");
	ErrorCheck(system->createSound("resources/laser_shoot2.ogg", FMOD_DEFAULT, nullptr, &sounds["lasershoot2"].sound), "FAILED TO CREATE SOUND");
	ErrorCheck(system->createSound("resources/laser_shoot3.ogg", FMOD_DEFAULT, nullptr, &sounds["lasershoot3"].sound), "FAILED TO CREATE SOUND");

	ErrorCheck(system->createSound("resources/claire de lune flight facilities.ogg", FMOD_DEFAULT, nullptr, &sounds["background1"].sound), "FAILED TO CREATE SOUND");
}

SoundManager::~SoundManager()
{
	ErrorCheck(system->release(), "FAILED TO RELEASE FMOD SYSTEM");
}

void SoundManager::Play(std::string a_TrackName)
{
	ErrorCheck(system->playSound(sounds[a_TrackName].sound, MainChannel, false, &sounds[a_TrackName].currentChannel), "FAILED TO PLAY SOUND");
}

void SoundManager::Update()
{
	ErrorCheck(system->update(), "FAILED TO UPDATE FMOD SYSTEM");
}

void SoundManager::ErrorCheck(FMOD_RESULT a_Result, const char* error_message)
{
	if (a_Result != FMOD_OK)
	{
		printf(error_message);
	}
}
