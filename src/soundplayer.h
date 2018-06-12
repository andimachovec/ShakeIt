#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <ao/ao.h>
#include <string>
#include <cstdio>


class SoundPlayer
{

	public:
		SoundPlayer(std::string sound_filename);
		~SoundPlayer();
		void Play();
	
	private:
	
		FILE *sound_file;
		ao_device *audio_device;
		ao_sample_format audio_format;
		int default_driver_id;		
		char *buffer;
		int buffer_size;

};

#endif
