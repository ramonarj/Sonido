#include "AudioSource.h"
#include "System.h"

AudioSource::AudioSource(std::string filename) :
	volume_(0.7f),
	pitch_(1.0f),
	pan_(1.0f),
	position_({ 0.0, 0.0, 0.0 }),
	velocity_({0.0, 0.0, 0.0})
{
	result_ = FMOD_SYSTEM->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound_);
	ERRCHECK(result_);

	result_ = FMOD_SYSTEM->playSound(sound_, 0, true, &channel_);
	ERRCHECK(result_);
}

AudioSource::~AudioSource()
{

}

void AudioSource::play()
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

void AudioSource::pause()
{
	bool paused = true;
	result_ = channel_->getPaused(&paused);
	ERRCHECK(result_);

	result_ = channel_->setPaused(!paused);
	ERRCHECK(result_);
}

void AudioSource::stop()
{
	result_ = channel_->stop();
	ERRCHECK(result_);
}

void AudioSource::setVolume(float volume)
{
	volume_ = volume;
	result_ = channel_->setVolume(volume);
	ERRCHECK(result_);
}

void AudioSource::setPitch(float pitch)
{
	pitch_ = pitch;
	result_ = channel_->setPitch(pitch);
	ERRCHECK(result_);
}

void AudioSource::setPan(float pan)
{
	pan_ = pan;
	result_ = channel_->setPan(pan);
	ERRCHECK(result_);
}

void AudioSource::setCone(FMOD_VECTOR direction, float innerAngle, float outerAngle, float outsideVolume)
{
	this->direction_ = direction;
	this->innerConeAngle_ = innerAngle;
	this->outerConeAngle_ = outerAngle;

	channel_->get3DConeOrientation(&direction);
	channel_->set3DConeSettings(innerAngle, outerAngle, outsideVolume); //Ya está el cono
}

void AudioSource::reset()
{
	setPan(pan_);
	setPitch(pitch_);
	setVolume(volume_);
}
