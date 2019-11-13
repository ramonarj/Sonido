#ifndef __AUDIOSOURCE_H__
#define __AUDIOSOURCE_H__

#include <string>

#include "System.h"

#define FMOD_SYSTEM System::getFmodSystem()

class AudioSource
{
private:
	FMOD::Channel* channel_;
	FMOD::Sound* sound_;
	FMOD_RESULT result_;

	//Pa los atributos
	float volume_;
	float pitch_;
	float pan_;

	//Pa los movimientos
	FMOD_VECTOR position_;
	FMOD_VECTOR velocity_;

	//Para el cono
	float innerConeAngle_;
	float outerConeAngle_;
	FMOD_VECTOR direction_;


public:
	AudioSource(std::string filename);
	~AudioSource();

	void play();
	void pause();
	void stop();

	void setVolume(float volume);
	void setPitch(float pitch);
	void setPan(float pan);

	void setPosition(FMOD_VECTOR v) { position_ = v; updateChannel(); }
	void setVelocity(FMOD_VECTOR v) { velocity_ = v; updateChannel(); }


	void setCone(FMOD_VECTOR direction, float innerAngle, float outerAngle, float outsideVolume);

	void setMinMaxDistance(float minDistance, float maxDistance) { channel_->set3DMinMaxDistance(minDistance, maxDistance); }


	/*
	* Draws sprite centered in the given rectangle
	* Can throw a JavaNullPointerException if the rectangle has not been initialised
	* @returns vector containing sound position
	*/
	FMOD_VECTOR getPosition() const { return position_; }
	FMOD_VECTOR getVelocity() const { return velocity_; }

private:
	void reset();

	void updateChannel() { channel_->set3DAttributes(&position_,&velocity_); }

};

#endif // !__AUDIOSOURCE_H__