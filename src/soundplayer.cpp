#include "soundplayer.h"

#include <exception>
#include <system_error>
#include <iostream>
#include <cstring>



//-----------------------------------------------------------------------------
SoundPlayer::SoundPlayer(std::string sound_filename)
//-----------------------------------------------------------------------------
{

	//initialize ao library
	ao_initialize();

	//get default driver id
	default_driver_id = ao_default_driver_id();
	

    //set format options
	memset(&audio_format, 0, sizeof(audio_format));
	audio_format.bits = 16;
	audio_format.channels = 1;
	audio_format.rate = 44100;
	audio_format.byte_format = AO_FMT_LITTLE;


	//open audio file
	sound_file = fopen(sound_filename.c_str(), "rb");

	if (sound_file == NULL)
	{
		throw std::system_error(std::error_code(1, std::system_category()), "could not open audio file");
	}


}



//-----------------------------------------------------------------------------
SoundPlayer::~SoundPlayer()
//-----------------------------------------------------------------------------
{

	
	fclose(sound_file);
	ao_shutdown();

}



//-----------------------------------------------------------------------------
void SoundPlayer::Play()
//-----------------------------------------------------------------------------
{

	//open the driver
	audio_device = ao_open_live(default_driver_id, &audio_format, NULL);

	if (audio_device == NULL)
	{
		throw std::system_error(std::error_code(2, std::system_category()), "could not open audio device");

	}

	
	//prepare buffer
	buffer_size = audio_format.bits/8 * audio_format.channels * audio_format.rate;
	buffer = new char[buffer_size];

	while (feof(sound_file) == 0)
	{

		size_t number_of_elements = fread(buffer,buffer_size,1,sound_file);
		if (number_of_elements > 0)
		{
			ao_play(audio_device, buffer, buffer_size);	
		}

	}
	
	ao_close(audio_device);
	delete buffer;
	
	rewind(sound_file);

}


