#include "PaDevice.h"
#define BUFFRAMES 256

PaDevice::PaDevice(ConfigManager *config_manager): m_config_manager(config_manager) {
	try {
		initialize();
	}
	catch (PaDevice::InitializationError) {
		std::cout << "InitializationError" << std::endl;
	}
	catch (PaDevice::OpenStreamError e) {
		std::cout << "OpenStreamError: " << e.err_msg << std::endl;
		Pa_CloseStream(m_stream_handle);
	}
	catch (PaDevice::StartStreamError e) {
		std::cout << "StartStreamError" << e.err_msg << std::endl;
		Pa_StopStream(m_stream_handle);
	}
}

PaDevice::~PaDevice() {
	Pa_Terminate();
}

void PaDevice::initialize() {
	PaStreamParameters outparams;
	int sr = 44100, buffsize, channels = 2;
	float* buf, out = 0.f;

	PaError err = Pa_Initialize();
	if (err != paNoError) {
		throw InitializationError();
	}

	get_devices();

	m_device = 10;
	buffsize = BUFFRAMES * channels;

	std::cout << Pa_GetDeviceInfo(10)->name << std::endl;
	std::cout << Pa_GetHostApiInfo(Pa_GetDeviceInfo(10)->hostApi)->name << std::endl;

	buf = (float*)malloc(sizeof(float) * buffsize);
	memset(buf, 0, sizeof(float) * buffsize);
	
	create_stream_params(&outparams, channels, paFloat32, (BUFFRAMES/(double) sr));

	open_stream(&outparams, sr, buffsize);

	free(buf);
}

void PaDevice::get_devices() {
	const PaDeviceInfo* di;
	const PaHostApiInfo* host;
	DeviceInfo d;
	for (int i = 0; i < Pa_GetDeviceCount(); ++i) {
		di = Pa_GetDeviceInfo(i);
		host = Pa_GetHostApiInfo(di->hostApi);
		d.idx = i;
		d.name = (std::string) di->name + ": " + (std::string) host->name;
		m_config_manager->add_device(&d);
	}
}

void PaDevice::open_stream(PaStreamParameters* outparams, int sr, int buffsize) {
	PaError err = Pa_OpenStream(
		&m_stream_handle, NULL, outparams,
		sr, buffsize, paNoFlag,
		NULL, NULL
	);

	if (err != paNoError) {
		throw OpenStreamError(err);
	}
}

void PaDevice::start_stream(SNDFILE *fin) {
	PaError err = Pa_StartStream(m_stream_handle);

	if (err != paNoError) {
		throw StartStreamError(err);
	}

}

void PaDevice::create_stream_params(
	PaStreamParameters* params,
	int channelsNum,
	PaSampleFormat sampleFormat,
	PaTime latency
) {
	params->device = m_device;
	params->channelCount = channelsNum;
	params->sampleFormat = paInt32;
	params->suggestedLatency = latency;
	params->hostApiSpecificStreamInfo = NULL;
}