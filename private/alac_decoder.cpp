#include "alac_decoder.hpp"
#include "CAFFileALAC.h"

#include <malloc.h>

AlacDecoder::AlacDecoder() {}

void AlacDecoder::openFile(const char *filePath)
{
   file = fopen(filePath, "rb");
    if (!file) {
        printf("Failed to open ALAC file: %s\n", filePath);
        return;
    }

    cookieSize = GetMagicCookieSizeFromCAFFkuki(file);
    magicCookie = malloc(cookieSize);
    GetMagicCookieFromCAFFkuki(file, (uint8_t*)magicCookie, &cookieSize);
    decoder.Init(magicCookie, cookieSize);
}

short AlacDecoder::getChannelsAmount()
{
    return decoder.mConfig.numChannels;
}

uint32_t AlacDecoder::getSampleRate()
{
    return decoder.mConfig.sampleRate;
}

short AlacDecoder::getBitDepth()
{
    return decoder.mConfig.bitDepth;
}

void *AlacDecoder::readWholeFileAndConvertToPcm(PCPcmType type, size_t *pSizeOutput)
{

}

size_t AlacDecoder::streamToBuffer(PCPcmType pcmType, void *bufferOutput, size_t bufferSize)
{

}

void AlacDecoder::seek(size_t pcmFrameIndex)
{

}

void AlacDecoder::close()
{
    if(magicCookie){
        free(magicCookie);
    }
    if(file){
        fclose(file);
    }
}
