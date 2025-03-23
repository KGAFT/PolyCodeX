
extern "C"{
#define DR_MP3_IMPLEMENTATION
#define DR_FLAC_IMPLEMENTATION
#define DR_WAV_IMPLEMENTATION
#include "decodex.h"
}

#include "wav_decoder.hpp"
#include "mp3_decoder.hpp"
#include "flac_decoder.hpp"
#include <cstdint>

#include <cstdlib>
#include <cstring>


const char *getFileNameExt(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

PCFileType getFileType(const char *path) {
  const char* fileExt = getFileNameExt(path);
  if (!strcmp(fileExt, "mp3")) {
    return MP3_AUDIO;
  } else if (!strcmp(fileExt, "flac")) {
    return FLAC_AUDIO;
  } else if (!strcmp(fileExt, "wav")) {
    return WAV_AUDIO;
  } else if (!strcmp(fileExt, "m4a")) {
    return ALAC_AUDIO;
  } else if (!strcmp(fileExt, "wv")) {
    return WAVPACK_AUDIO;
  } else if (!strcmp(fileExt, "ape")) {
    return APE_AUDIO;
  }
  return UNKNOWN;
}

PCFile *openFile(const char *path) {
    PCFileType fileType = getFileType(path);
    if(fileType==UNKNOWN){
        return 0;
    }
    return openFileDirect(path, fileType);
}

PCFile* openFileDirect(const char* path, PCFileType fileType){
    PCFile* result = (PCFile*)malloc(sizeof(PCFile));
    result->fileType = fileType;
    switch (fileType) {
    case MP3_AUDIO:
        result->handle = new MP3Decoder;
        result->handleSize = sizeof(MP3Decoder);
        ((MP3Decoder*)result->handle)->openFile(path);
        return result;
    case FLAC_AUDIO:
        result->handle = new FlacDecoder;
        result->handleSize = sizeof(FlacDecoder);
        ((FlacDecoder*)result->handle)->openFile(path);
        return result;
    case WAV_AUDIO:
        result->handle = new WavDecoder;
        result->handleSize = sizeof(WavDecoder);
        ((WavDecoder*)result->handle)->openFile(path);
        return result;
    default:
        break;
    }
    free(result);
    return 0;
}

uint32_t getFileSampleRate(PCFile* file){
    return ((IDecoder*)file->handle)->getSampleRate();
}

uint64_t readFileToPcmBuffer(PCFile* file, PCPcmType type, void* destination, size_t destinationSize){
    return ((IDecoder*)file->handle)->streamToBuffer(type, destination, destinationSize);
}

