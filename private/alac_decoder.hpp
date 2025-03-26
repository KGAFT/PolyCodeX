#ifndef ALAC_DECODER_HPP
#define ALAC_DECODER_HPP

#include "IDecoder.hpp"
#include <ALACDecoder.h>
#include <cstdio>


class AlacDecoder : public IDecoder
{
public:
    AlacDecoder();
private:
    FILE* file = nullptr;
    ALACDecoder decoder;
    void* magicCookie = nullptr;
    uint32_t cookieSize = 0;
public:
    void openFile(const char* filePath) override;
    short getChannelsAmount() override;
    uint32_t getSampleRate() override;
    short getBitDepth() override;
    void* readWholeFileAndConvertToPcm(PCPcmType type, size_t* pSizeOutput) override;
    size_t streamToBuffer(PCPcmType pcmType,void* bufferOutput, size_t bufferSize) override;
    void seek(size_t pcmFrameIndex) override;
    void close() override;
};

#endif // ALAC_DECODER_H
