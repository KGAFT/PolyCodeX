#include "alac_decoder.hpp"
#include "pcm_utils.hpp"
#include <malloc.h>

AlacDecoder::AlacDecoder() {}

void AlacDecoder::openFile(const char *filePath)
{
    AP4_Result result = AP4_FileByteStream::Create(filePath, AP4_FileByteStream::STREAM_MODE_READ, fileStream);
    if (AP4_FAILED(result) || !fileStream) {
        printf("Failed to open MP4 file.\n");
        return;
    }

    mp4File = new AP4_File(*fileStream, *(AP4_AtomFactory*)(&AP4_DefaultAtomFactory::Instance_), true);
    if (!mp4File) {
        printf("Failed to parse MP4 file.\n");
        return;
    }

    movie = mp4File->GetMovie();
    if (!movie) {
        printf("No valid movie found in MP4 file.\n");
        return;
    }

    track = movie->GetTrack(AP4_Track::TYPE_AUDIO);
    if (!track) {
        printf("No ALAC audio track found!\n");
        return;
    }
    // Retrieve the first sample description
    sampleDescription = track->GetSampleDescription(0);
    if (!sampleDescription) {
        printf("Failed to retrieve sample description!\n");
        return;
    }


    audioDesc =
            dynamic_cast<AP4_AudioSampleDescription*>(sampleDescription);

    if (!audioDesc) {
        printf("Failed to cast sample description to audio!\n");
        return;
    }


    sampleTable = track->GetSampleTable();
    if (!sampleTable) {
        printf("No valid sample table found!\n");
        return;
    }
}

short AlacDecoder::getChannelsAmount()
{
    return audioDesc->GetChannelCount();
}

uint32_t AlacDecoder::getSampleRate()
{
    return audioDesc->GetSampleRate();
}

short AlacDecoder::getBitDepth()
{
    return audioDesc->GetSampleSize();
}

void *AlacDecoder::readWholeFileAndConvertToPcm(PCPcmType type, size_t *pSizeOutput)
{
    return nullptr;
}

size_t AlacDecoder::streamToBuffer(PCPcmType pcmType, void *bufferOutput, size_t bufferSize)
{
    return 0 ;

}

void AlacDecoder::seek(size_t pcmFrameIndex)
{

}

void AlacDecoder::close()
{

}
