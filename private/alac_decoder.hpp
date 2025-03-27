#ifndef ALAC_DECODER_HPP
#define ALAC_DECODER_HPP

#include "IDecoder.hpp"
#include <cstdio>
#include "Ap4.h"

class AlacDecoder : public IDecoder
{
public:
    AlacDecoder();
private:
    AP4_File* mp4File;
    AP4_Movie* movie;
    AP4_Track* track;
    AP4_SampleDescription* sampleDescription;
    AP4_AudioSampleDescription* audioDesc;
    AP4_SampleTable* sampleTable;
    AP4_ByteStream* fileStream;
    AP4_Sample sample;
    AP4_UI32 sampleIndex = 0;
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
