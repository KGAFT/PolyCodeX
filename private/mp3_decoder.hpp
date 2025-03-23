#ifndef MP3_DECODER_HPP
#define MP3_DECODER_HPP

#include "IDecoder.hpp"
#include "dr_mp3.h"

class MP3Decoder : public IDecoder
{
public:
    MP3Decoder();
private:
    drmp3 handle;
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
    ~MP3Decoder();
};

#endif // MP3DECODER_H
