#include "mp3_decoder.hpp"

#include <malloc.h>

MP3Decoder::MP3Decoder() {}

void MP3Decoder::openFile(const char *filePath)
{
    drmp3_init_file(&handle, filePath, NULL);
    initted = true;
}

short MP3Decoder::getChannelsAmount()
{
    return handle.channels;
}

uint32_t MP3Decoder::getSampleRate()
{
    return handle.sampleRate;
}

short MP3Decoder::getBitDepth()
{
    return 16;
}

void *MP3Decoder::readWholeFileAndConvertToPcm(PCPcmType pcmType, size_t *pSizeOutput)
{
    if(pcmType!=INT_16 && pcmType!=FLOAT_32)
        return nullptr;
    size_t frameCount = drmp3_get_pcm_frame_count(&handle);
    size_t size = frameCount * handle.channels * pcmType==INT_16?sizeof(int16_t):sizeof(float);
    void* pcmData = malloc(size);
    if(!pcmData){
        return nullptr;
    }
    if(pcmType==INT_16){
        drmp3_read_pcm_frames_s16(&handle, frameCount, (int16_t*) pcmData);
    } else {
        drmp3_read_pcm_frames_f32(&handle, frameCount, (float*)pcmData);
    }
    *pSizeOutput = size;
    return pcmData;
}

size_t MP3Decoder::streamToBuffer(PCPcmType pcmType, void *bufferOutput, size_t bufferSize)
{
    if(pcmType!=INT_16 && pcmType!=FLOAT_32)
        return 0;

    size_t amplifier = handle.channels;
    switch(pcmType){
    case INT_16:
        amplifier*=sizeof(int16_t);
        break;
    case FLOAT_32:
        amplifier*=sizeof(float);
        break;
    case INT_32:
        amplifier*=sizeof(int32_t);
        break;
    }
    size_t read = 0;
    if(pcmType==INT_16){
       read = drmp3_read_pcm_frames_s16(&handle, bufferSize/(handle.channels*sizeof(int16_t)), (int16_t*) bufferOutput);
    } else {
        read = drmp3_read_pcm_frames_f32(&handle, bufferSize/(handle.channels*sizeof(float)), (float*) bufferOutput);
    }
    return read*amplifier;
}

void MP3Decoder::seek(size_t pcmFrameIndex)
{
    drmp3_seek_to_pcm_frame(&handle, pcmFrameIndex);
}

void MP3Decoder::close()
{
    drmp3_uninit(&handle);
}

MP3Decoder::~MP3Decoder()
{
    if(initted){
        close();
    }
}
