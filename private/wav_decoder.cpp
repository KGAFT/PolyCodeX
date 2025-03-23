#include "wav_decoder.hpp"

#include <malloc.h>

WavDecoder::WavDecoder() {}

void WavDecoder::openFile(const char *filePath)
{
    handle = (drwav*) malloc(sizeof(drwav));
    drwav_init_file(handle, filePath, NULL);
    initted = true;
}

short WavDecoder::getChannelsAmount()
{
    return handle->channels;
}

uint32_t WavDecoder::getSampleRate()
{
    return handle->sampleRate;
}

short WavDecoder::getBitDepth()
{
    return handle->bitsPerSample;
}

void *WavDecoder::readWholeFileAndConvertToPcm(PCPcmType pcmType, size_t *pSizeOutput)
{

    size_t frameCount = handle->totalPCMFrameCount;
    size_t size = frameCount * handle->channels * pcmType==INT_16?sizeof(int16_t):(pcmType==FLOAT_32?sizeof(float):sizeof(int32_t));
    void* pcmData = malloc(size);
    if(!pcmData){
        return nullptr;
    }
    if(pcmType==INT_16){
        drwav_read_pcm_frames_s16(handle, frameCount, (int16_t*) pcmData);
    } else if(pcmType == FLOAT_32){
        drwav_read_pcm_frames_f32(handle, frameCount, (float*)pcmData);
    } else {
        drwav_read_pcm_frames_s32(handle, frameCount, (int32_t*)pcmData);
    }
    *pSizeOutput = size;
    return pcmData;
}

size_t WavDecoder::streamToBuffer(PCPcmType pcmType, void *bufferOutput, size_t bufferSize)
{

    size_t amplifier = handle->channels;
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
        read = drwav_read_pcm_frames_s16(handle, bufferSize/(handle->channels*sizeof(int16_t)), (int16_t*) bufferOutput);
    } else if(pcmType==FLOAT_32) {
        read = drwav_read_pcm_frames_f32(handle, bufferSize/(handle->channels*sizeof(float)), (float*) bufferOutput);
    } else {
        read = drwav_read_pcm_frames_s32(handle, bufferSize/(handle->channels*sizeof(int32_t)), (int32_t*) bufferOutput);
    }
    return read*amplifier;
}

void WavDecoder::seek(size_t pcmFrameIndex)
{
    drwav_seek_to_pcm_frame(handle, pcmFrameIndex);
}

void WavDecoder::close()
{
    drwav_uninit(handle);
    free(handle);
}

WavDecoder::~WavDecoder()
{
    if(initted){
        close();
    }
}
