#ifndef IDECODER_HPP
#define IDECODER_HPP

#include <cstddef>
#include <cstdint>
extern "C"{
#include <defines.h>
}

class IDecoder
{
public:
    virtual void openFile(const char* filePath) = 0;
    virtual short getChannelsAmount() = 0;
    virtual uint32_t getSampleRate() = 0;
    virtual short getBitDepth() = 0;
    virtual void* readWholeFileAndConvertToPcm(PCPcmType type, size_t* pSizeOutput) = 0;
    virtual size_t streamToBuffer(PCPcmType pcmType, void* bufferOutput, size_t bufferSize) = 0;
    virtual void seek(size_t pcmFrameIndex) = 0;
    virtual void close() = 0;

};

#endif // IDECODER_HPP
