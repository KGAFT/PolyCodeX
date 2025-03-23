#include "flac_decoder.hpp"

#include <malloc.h>

FlacDecoder::FlacDecoder() {}

void FlacDecoder::openFile(const char *filePath)
{
    handle = drflac_open_file(filePath, NULL);
    initted = true;
}

short FlacDecoder::getChannelsAmount()
{
    return handle->channels;
}

uint32_t FlacDecoder::getSampleRate()
{
    return handle->sampleRate;
}

short FlacDecoder::getBitDepth()
{
    return handle->bitsPerSample;
}

void *FlacDecoder::readWholeFileAndConvertToPcm(PCPcmType pcmType, size_t *pSizeOutput)
{

    size_t frameCount = handle->totalPCMFrameCount;
    size_t size = frameCount * handle->channels * pcmType==INT_16?sizeof(int16_t):(pcmType==FLOAT_32?sizeof(float):sizeof(int32_t));
    void* pcmData = malloc(size);
    if(!pcmData){
        return nullptr;
    }
    if(pcmType==INT_16){
        drflac_read_pcm_frames_s16(handle, frameCount, (int16_t*) pcmData);
    } else if(pcmType == FLOAT_32){
        drflac_read_pcm_frames_f32(handle, frameCount, (float*)pcmData);
    } else {
        drflac_read_pcm_frames_s32(handle, frameCount, (int32_t*)pcmData);
    }
    *pSizeOutput = size;
    return pcmData;
}

size_t FlacDecoder::streamToBuffer(PCPcmType pcmType, void *bufferOutput, size_t bufferSize)
{

    size_t read = 0;
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

    if(pcmType==INT_16){
        read = drflac_read_pcm_frames_s16(handle, bufferSize/(handle->channels*sizeof(int16_t)), (int16_t*) bufferOutput);
    } else if(pcmType==FLOAT_32) {
        read = drflac_read_pcm_frames_f32(handle, bufferSize/(handle->channels*sizeof(float)), (float*) bufferOutput);
    } else {
        read = drflac_read_pcm_frames_s32(handle, bufferSize/(handle->channels*sizeof(int32_t)), (int32_t*) bufferOutput);
    }
    return read*amplifier;
}

void FlacDecoder::seek(size_t pcmFrameIndex)
{
    drflac_seek_to_pcm_frame(handle, pcmFrameIndex);
}

void FlacDecoder::close()
{
    drflac_close(handle);
}

FlacDecoder::~FlacDecoder()
{
    if(initted){
        close();
    }
}
