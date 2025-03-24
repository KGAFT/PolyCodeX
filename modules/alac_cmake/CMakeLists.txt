cmake_minimum_required(VERSION 3.10)

project(alac)

file(GLOB_RECURSE CODEC_SRC alac/codec/*.*)

add_library(alac-shared SHARED ${CODEC_SRC})
add_library(alac-static STATIC ${CODEC_SRC})

target_include_directories(alac-static PUBLIC alac/codec)
target_include_directories(alac-shared PUBLIC alac/codec)
