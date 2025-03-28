#include <cstring>
extern "C"{
#include "decodex.h"
}
#include <portaudio.h>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <alac_decoder.hpp>

class PortAudioPlayer {
public:
    PortAudioPlayer(int sampleRate, int channels)
        : sampleRate(sampleRate), channels(channels), flac(nullptr) {
        Pa_Initialize();
        outputParameters.device = Pa_GetDefaultOutputDevice();
        outputParameters.channelCount = channels;
        outputParameters.sampleFormat = paFloat32;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = nullptr;
    }

    ~PortAudioPlayer() {
        stop();
        Pa_Terminate();
    }

    void playFlac(PCFile* flacFile) {
        flac = flacFile;
        Pa_OpenStream(&stream, nullptr, &outputParameters, sampleRate, 512, paClipOff, audioCallback, this);
        Pa_StartStream(stream);

        while (Pa_IsStreamActive(stream) == 1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        Pa_StopStream(stream);
        Pa_CloseStream(stream);
    }

    void stop() {
        if (stream) {
            Pa_StopStream(stream);
            Pa_CloseStream(stream);
            stream = nullptr;
        }
    }

private:
    static int audioCallback(const void* input, void* output, unsigned long frameCount,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags, void* userData) {
        PortAudioPlayer* player = static_cast<PortAudioPlayer*>(userData);
        if (!player->flac) return paComplete;

        float* out = static_cast<float*>(output);
        size_t samplesToRead = frameCount * player->channels;
        uint64_t samplesRead = readFileToPcmBuffer(player->flac, FLOAT_32, out,
                                                        frameCount*sizeof(float)*player->channels)/(sizeof(float)*player->channels);

        if (samplesRead < frameCount) {
            memset(out + samplesRead * player->channels, 0, (frameCount - samplesRead) * player->channels * sizeof(float));
            return paComplete;
        }

        return paContinue;
    }

    PaStream* stream = nullptr;
    PaStreamParameters outputParameters;
    int sampleRate;
    int channels;
    PCFile* flac;
};

void playFlacFile(const char* filename) {
    PCFile* flac = openFile(filename);

    PortAudioPlayer player(getFileSampleRate(flac), 2);
    player.playFlac(flac);
}

int main() {
   // AlacDecoder decoder;
    std::string path = "/mnt/files/sheep.m4a";
    //decoder.openFile(path.c_str());
    //std::cout<<decoder.getChannelsAmount()<<" "<<decoder.getBitDepth()<<" "<<decoder.getSampleRate()<<std::endl;

    playFlacFile("/mnt/files/sheep.m4a");

    return 0;
}


