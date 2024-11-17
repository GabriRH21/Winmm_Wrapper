#include <mmdeviceapi.h>

#include <spdlog/spdlog.h>
#include <SDL.h>



struct WaveOutExtraData {
    SDL_AudioDeviceID devID;
    DWORD_PTR dwInstance;
    DWORD_PTR realCallback;

    std::vector<uint8_t> sdlBuffer;
    int sdlBufferUsed;

    int bytesToDate;
    uint32_t bytesPerSec;
};

using CallbackFormat = void CALLBACK(
   HWAVEOUT  hwo,
   UINT      uMsg,
   DWORD_PTR dwInstance,
   DWORD_PTR dwParam1,
   DWORD_PTR dwParam2
);

#define WAVEOUTOPEN
FAKE(MMRESULT, __stdcall, waveOutOpen, _Inout_updates_bytes_(cbwh)  LPHWAVEOUT phwo, _In_ UINT uDeviceID, _Inout_updates_bytes_(cbwh) LPCWAVEFORMATEX pwfx, _In_ DWORD_PTR dwCallback, _In_ DWORD_PTR dwInstance, _In_ DWORD fdwOpen)
{
    //spdlog::debug("Calling waveOutOpen");
    OutputDebugString("Calling waveOutOpen");
    SDL_AudioDeviceID dev;
    SDL_AudioSpec want, have;
    SDL_zero(want);
    SDL_zero(have);

    auto bytesPerSec = 2;
    if (pwfx->wBitsPerSample == 8) {
        want.format = AUDIO_U8;
    } else {
        want.format = AUDIO_S16SYS;
    }

    auto result = new WaveOutExtraData {
        .devID = (uint32_t)-1,
        .dwInstance = dwInstance,
        .realCallback = dwCallback,

        .sdlBuffer = {},
        .sdlBufferUsed = 0,
        .bytesToDate = 0,
        .bytesPerSec = pwfx->nSamplesPerSec * pwfx->nChannels * bytesPerSec
    };

    want.freq = pwfx->nSamplesPerSec;
    want.channels = pwfx->nChannels;

    want.callback = nullptr;//(SDL_AudioCallback)dwCallback;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (dev == 0) {
        fprintf(stderr, "ERROR: Cannot open audio device: %s\n", SDL_GetError());
        return MMSYSERR_ERROR;
    }

    *phwo = (HWAVEOUT)result;
    result->devID = dev;

    auto castedCallback = (CallbackFormat*)dwCallback;
    castedCallback(*phwo, WOM_OPEN, dwInstance, 0, 0);

    WAVEHDR hdr;
    castedCallback(*phwo, WOM_DONE, dwInstance, reinterpret_cast<DWORD_PTR>(&hdr), 0);

    return MMSYSERR_NOERROR;
}

#define WAVEOUTWRITE
FAKE(MMRESULT, __stdcall, waveOutWrite, _In_ HWAVEOUT hwo,_Inout_updates_bytes_(cbwh) LPWAVEHDR pwh, UINT cbwh)
{
    //spdlog::debug("Calling waveOutWrite");
    //OutputDebugString("Calling waveOutWrite");
    auto data = (WaveOutExtraData*)hwo;

    if (data->sdlBuffer.size() < pwh->dwBufferLength) {
        data->sdlBuffer.resize(pwh->dwBufferLength);
    }

    memcpy(data->sdlBuffer.data(), pwh->lpData, pwh->dwBufferLength);
    data->sdlBufferUsed = 0;

    return MMSYSERR_NOERROR;
}


#define WAVEOUTGETPOSITION
FAKE(MMRESULT, __stdcall, waveOutGetPosition, _In_ HWAVEOUT hwo,_Inout_updates_bytes_(cbwh) LPMMTIME pmmt, UINT cbmmt)
{
    //spdlog::debug("Calling waveOutGetPosition");


    //OutputDebugString(" Calling waveOutGetPosition ");

    auto data = (WaveOutExtraData*)hwo;

    if (data->sdlBufferUsed >= data->sdlBuffer.size()) {
        auto castedCallback = (CallbackFormat*)data->realCallback;
        auto hwo = (HWAVEOUT)data;
        WAVEHDR hdr;
        castedCallback(hwo, WOM_DONE, data->dwInstance, reinterpret_cast<DWORD_PTR>(&hdr), 0);
    }

    pmmt->wType = TIME_BYTES;
    pmmt->u.cb = data->bytesToDate;

    auto queued = SDL_GetQueuedAudioSize(data->devID);

    constexpr auto DataToWrite = 256;
    if (queued < data->bytesPerSec / 16) {
#undef min
        auto dataToRead = std::min((int)(data->sdlBuffer.size() - data->sdlBufferUsed), DataToWrite);

        static char tmp[512];
        sprintf(tmp, "sdlBuffer: %p, sdlBufferUser: %d, dataToRead: %d",data->sdlBuffer.data(), data->sdlBufferUsed, dataToRead);
        //OutputDebugString(tmp);

        SDL_QueueAudio(data->devID, data->sdlBuffer.data() + data->sdlBufferUsed, dataToRead);
        // fprintf(stderr, "Q: %d\n", queued);

        data->sdlBufferUsed += dataToRead;
        data->bytesToDate += dataToRead;

        if (dataToRead < DataToWrite) {
            auto castedCallback = (CallbackFormat*)data->realCallback;
            auto hwo = (HWAVEOUT)data;
            WAVEHDR hdr;
            castedCallback(hwo, WOM_DONE, data->dwInstance, reinterpret_cast<DWORD_PTR>(&hdr), 0);

            auto dataToRead = std::min((int)(data->sdlBuffer.size() - data->sdlBufferUsed), DataToWrite);
            SDL_QueueAudio(data->devID, data->sdlBuffer.data() + data->sdlBufferUsed, dataToRead);

            data->sdlBufferUsed += dataToRead;
            data->bytesToDate += dataToRead;
        }
    }

    return MMSYSERR_NOERROR;
}


#define WAVEOUTPAUSE
FAKE(MMRESULT, __stdcall, waveOutPause, _In_ HWAVEOUT hwo)
{
    //spdlog::debug("Calling waveOutPause");
    OutputDebugString("Calling waveOutPause");
    auto data = (WaveOutExtraData*)hwo;

    SDL_PauseAudioDevice(data->devID, 1);

    return MMSYSERR_NOERROR;
}


#define WAVEOUTPREPAREHEADER
FAKE(MMRESULT, __stdcall, waveOutPrepareHeader, _In_ HWAVEOUT hwo,_Inout_updates_bytes_(cbwh) LPWAVEHDR pwh, UINT cbwh)
{
    spdlog::debug("Calling waveOutPrepareHeader");
    //OutputDebugString("Calling waveOutPrepareHeader");
    auto data = (WaveOutExtraData*)hwo;
    return MMSYSERR_NOERROR;
}


#define WAVEOUTRESET
FAKE(MMRESULT, __stdcall, waveOutReset, _In_ HWAVEOUT hwo)
{
    //spdlog::debug("Calling waveOutReset");
    OutputDebugString("Calling waveOutReset");
    auto data = (WaveOutExtraData*)hwo;
    return MMSYSERR_NOERROR;
}


#define WAVEOUTRESTART
FAKE(MMRESULT, __stdcall, waveOutRestart, _In_ HWAVEOUT hwo)
{
    spdlog::debug("Calling waveOutRestart");
    OutputDebugString("Calling waveOutRestart");
    auto data = (WaveOutExtraData*)hwo;

    SDL_PauseAudioDevice(data->devID, 0);

    return MMSYSERR_NOERROR;
}


#define WAVEOUTUNPREPAREHEADER
FAKE(MMRESULT, __stdcall, waveOutUnprepareHeader, _In_ HWAVEOUT hwo, _Inout_updates_bytes_(cbwh) LPWAVEHDR pwh, UINT cbwh)
{
    //spdlog::debug("Calling waveOutUnprepareHeader");
    OutputDebugString("Calling waveOutUnprepareHeader");
    auto data = (WaveOutExtraData*)hwo;
    return MMSYSERR_NOERROR;
}


#define WAVEOUTCLOSE
FAKE(MMRESULT, __stdcall, waveOutClose, _In_ HWAVEOUT hwo) {
    //spdlog::debug("Calling waveOutClose");
    OutputDebugString("Calling waveOutClose");

    auto data = (WaveOutExtraData*)hwo;

    auto castedCallback = (CallbackFormat*)data->realCallback;
    castedCallback(hwo, WOM_CLOSE, data->dwInstance, 0, 0);

    SDL_CloseAudioDevice(data->devID);
    delete data;

    return MMSYSERR_NOERROR;
}

