#ifndef WAV_DECODER_HPP
#define WAV_DECODER_HPP

#include "IDecoder.hpp"
#include "dr_wav.h"

class WavDecoder: public IDecoder
{
public:
    WavDecoder();
private:
    drwav* handle;
    bool initted = false;
public:

    void openFile(const char* filePath) override;
    short getChannelsAmount() override;
    uint32_t getSampleRate() override;
    short getBitDepth() override;
    void* readWholeFileAndConvertToPcm(PCPcmType type, size_t* pSizeOutput) override;
    size_t streamToBuffer(PCPcmType pcmType,void* bufferOutput, size_t bufferSize) override;
    void seek(size_t pcmFrameIndex) override;
    void close() override;
    ~WavDecoder();
};

#endif // WAV_DECODER_HPP
