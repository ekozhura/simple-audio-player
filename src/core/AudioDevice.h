#pragma once
#include <windows.h>
#include <mmdeviceapi.h>
#include <Audioclient.h>
#include <AudioSessionTypes.h>
#include <atomic>
#include <cstdlib>
#include <thread>

class AudioDevice
{
public:
	AudioDevice(int samplerate, int channels, int frames, 
		void (*func)(float*, int, int, void*),
		void* cookie);
	~AudioDevice();

private:
	HANDLE event;
	IMMDevice* device;
	IAudioClient* client;
	IAudioRenderClient* render;
	std::atomic<bool> stop;
	std::thread audio_tread;
};

