#pragma once
#include <iostream>
#include <portaudio.h>
#include <sndfile.h>
#include "ConfigManager.h"

class PaDevice {

public:
	PaDevice(ConfigManager* m_config_manager);
	~PaDevice();

	class PaDeviceError {
	public:
		const char* err_msg = nullptr;
		PaDeviceError() {};
		PaDeviceError(PaError err) : err_msg(Pa_GetErrorText(err)) {};

	};
	class InitializationError: public PaDevice::PaDeviceError {};
	class OpenStreamError: public PaDevice::PaDeviceError {
	public:
		OpenStreamError(PaError err) : PaDevice::PaDeviceError(err) {};
	};
	class StartStreamError: public PaDevice::PaDeviceError {
	public:
		StartStreamError(PaError err) : PaDevice::PaDeviceError(err) {};
	};

	void initialize();
	void create_stream_params(
		PaStreamParameters* params,
		int channelsNum,
		PaSampleFormat sampleFormat,
		PaTime latency
	);

	void open_stream(
		PaStreamParameters* outparams,
		int sr,
		int buffsize
	);
	void start_stream(SNDFILE* fin);
	void get_devices();

private:
	PaDeviceIndex m_device;
	PaStream* m_stream_handle = NULL;
	ConfigManager* m_config_manager;
};