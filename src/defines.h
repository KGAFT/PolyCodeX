#ifndef DEFINES_H
#define DEFINES_H

#include <stddef.h>

typedef enum PCFileType {
    MP3_AUDIO,
    FLAC_AUDIO,
    WAV_AUDIO,
    ALAC_AUDIO,
    WAVPACK_AUDIO,
    APE_AUDIO,
    UNKNOWN
} PCFileType;


typedef struct PCFile {
    void *handle;
    size_t handleSize;
    PCFileType fileType;
} PCFile;

typedef enum PCPcmType{
    FLOAT_32,
    INT_32,
    INT_16
} PCPcmType;

#endif // DEFINES_H
