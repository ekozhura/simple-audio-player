#include "AudioDevice.h"

AudioDevice::AudioDevice(int samplerate, int channels, int frames,
	void (*func)(float*, int, int, void*),
	void* cookie) {
	CoInitialize(NULL);

	event = CreateEvent(0, 0, 0, 0);
	IMMDeviceEnumerator* enumerator = NULL;
	CoCreateInstance(
		__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL,
		__uuidof(IMMDeviceEnumerator), (void **) &enumerator
	);

	REFERENCE_TIME defaultPeriod, minPeriod;
	client->GetDevicePeriod(&defaultPeriod, &minPeriod);
	WAVEFORMATEX* format = NULL;
	client->GetMixFormat(&format);
	format->nSamplesPerSec = samplerate;
	format->nChannels = channels;
	client->Initialize(
		AUDCLNT_SHAREMODE_SHARED,
		AUDCLNT_STREAMFLAGS_EVENTCALLBACK,
		defaultPeriod, 0, format, NULL
	);
	CoTaskMemFree(format);
	client->SetEventHandle(event);
	client->GetService(__uuidof(IAudioRenderClient), (void**)&render);
	client->Start();
	stop = false;
	audio_tread = std::thread(
		[this, func, cookie, channels, frames]() {
			while (!stop) {
				WaitForSingleObject(event, INFINITE);
				BYTE* output_buffer;
				render->GetBuffer(frames, &output_buffer);
				if (output_buffer) {
					func((float*)output_buffer, channels, frames, cookie);
					render->ReleaseBuffer(frames, 0);
				}
			}
		}
	);

	SetThreadPriority(audio_tread.native_handle(), THREAD_PRIORITY_ABOVE_NORMAL);
}

AudioDevice::~AudioDevice() {
	stop = true;
	audio_tread.join();
	render->Release();
	client->Stop();
	client->Release();
	device->Release();
	CloseHandle(event);
}