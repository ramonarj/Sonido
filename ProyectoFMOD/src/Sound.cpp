#include "Sound.h"
#include "System.h"

Sound::Sound(std::string filename) :
	volume_(0.7f),
	pitch_(1.0f),
	pan_(1.0f)
{
	result_ = FMOD_SYSTEM->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound_);
	ERRCHECK(result_);

	result_ = FMOD_SYSTEM->playSound(sound_, 0, true, &channel_);
	ERRCHECK(result_);
}

Sound::~Sound()
{

}

void Sound::play()
{
	bool paused = true;
	result_ = channel_->getPaused(&paused);
	ERRCHECK(result_);

	if (!paused)
	{
		stop();
		result_ = FMOD_SYSTEM->playSound(sound_, 0, true, &channel_);
		ERRCHECK(result_);
		reset();
	}

	result_ = channel_->setPaused(false);
	ERRCHECK(result_);

}

void Sound::pause()
{
	bool paused = true;
	result_ = channel_->getPaused(&paused);
	ERRCHECK(result_);

	result_ = channel_->setPaused(!paused);
	ERRCHECK(result_);
}

void Sound::stop()
{
	result_ = channel_->stop();
	ERRCHECK(result_);
}

void Sound::setVolume(float volume)
{
	volume_ = volume;
	result_ = channel_->setVolume(volume);
	ERRCHECK(result_);
}

void Sound::setPitch(float pitch)
{
	pitch_ = pitch;
	result_ = channel_->setPitch(pitch);
	ERRCHECK(result_);
}

void Sound::setPan(float pan)
{
	pan_ = pan;
	result_ = channel_->setPan(pan);
	ERRCHECK(result_);
}

void Sound::reset()
{
	setPan(pan_);
	setPitch(pitch_);
	setVolume(volume_);
}
