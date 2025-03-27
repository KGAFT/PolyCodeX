#ifndef PCM_UTILS_HPP
#define PCM_UTILS_HPP

#include <cstring>
#include <defines.h>
#include <cstdint>
#include <cstddef>

class PCMUtils
{
public:
    static void convertSamplesToBitDepth(uint8_t* rawPCM, void* buffer, int sampleCount, int bit_depth, PCPcmType format) {
        if (bit_depth == 16) {
            int16_t* inBuffer = (int16_t*)rawPCM;
            if (format == INT_16) {
                memcpy(buffer, rawPCM, sampleCount * sizeof(int16_t));
            } else if (format == INT_32) {
                int32_t* outBuffer = (int32_t*)buffer;
                for (int i = 0; i < sampleCount; ++i) {
                    outBuffer[i] = inBuffer[i] << 16;  // Convert to 32-bit
                }
            } else if (format == FLOAT_32) {
                float* outBuffer = (float*)buffer;
                for (int i = 0; i < sampleCount; ++i) {
                    outBuffer[i] = inBuffer[i] / 32768.0f;  // Convert to float [-1,1]
                }
            }
        } else if (bit_depth == 24) {
            if (format == INT_16) {
                int16_t* outBuffer = (int16_t*)buffer;
                for (int i = 0; i < sampleCount; ++i) {
                    int32_t sampleValue = (rawPCM[i * 3] << 16) | (rawPCM[i * 3 + 1] << 8) | rawPCM[i * 3 + 2];
                    sampleValue = (sampleValue << 8) >> 8;  // Sign extend
                    outBuffer[i] = sampleValue >> 8;  // Convert to 16-bit
                }
            } else if (format == INT_32) {
                int32_t* outBuffer = (int32_t*)buffer;
                for (int i = 0; i < sampleCount; ++i) {
                    int32_t sampleValue = (rawPCM[i * 3] << 16) | (rawPCM[i * 3 + 1] << 8) | rawPCM[i * 3 + 2];
                    sampleValue = (sampleValue << 8) >> 8;  // Sign extend
                    outBuffer[i] = sampleValue << 8;  // Convert to 32-bit
                }
            } else if (format == FLOAT_32) {
                float* outBuffer = (float*)buffer;
                for (int i = 0; i < sampleCount; ++i) {
                    int32_t sampleValue = (rawPCM[i * 3] << 16) | (rawPCM[i * 3 + 1] << 8) | rawPCM[i * 3 + 2];
                    sampleValue = (sampleValue << 8) >> 8;  // Sign extend
                    outBuffer[i] = sampleValue / 8388608.0f;  // Convert to float [-1,1]
                }
            }
        } else if (bit_depth == 32) {
            int32_t* inBuffer = (int32_t*)rawPCM;
            if (format == INT_32) {
                memcpy(buffer, rawPCM, sampleCount * sizeof(int32_t));
            } else if (format == INT_16) {
                int16_t* outBuffer = (int16_t*)buffer;
                for (int i = 0; i < sampleCount; ++i) {
                    outBuffer[i] = inBuffer[i] >> 16;  // Convert to 16-bit
                }
            } else if (format == FLOAT_32) {
                float* outBuffer = (float*)buffer;
                for (int i = 0; i < sampleCount; ++i) {
                    outBuffer[i] = inBuffer[i] / 2147483648.0f;  // Convert to float [-1,1]
                }
            }
        }
    }
};

#endif // PCM_UTILS_HPP
