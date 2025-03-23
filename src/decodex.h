#ifndef DECODEX_H
#define DECODEX_H

#include <stddef.h>
#include <stdint.h>
#include <defines.h>

PCFile* openFile(const char* path);
PCFile* openFileDirect(const char* path, PCFileType fileType);
uint32_t getFileSampleRate(PCFile* file);
uint64_t readFileToPcmBuffer(PCFile* file, PCPcmType type, void* destination, size_t destinationSize);

#endif
