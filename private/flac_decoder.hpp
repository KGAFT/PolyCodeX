#ifndef FLAC_DECODER_HPP
#define FLAC_DECODER_HPP

#include "IDecoder.hpp"
#include <dr_flac.h>

class FlacDecoder: public IDecoder
{
public:
    FlacDecoder();
private:
    drflac* handle;
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
    ~FlacDecoder();
};

#endif // FLAC_DECODER_HPP
