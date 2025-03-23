cmake_minimum_required(VERSION 3.10)

project(PolyCodeX)

add_subdirectory(modules/dr_audio)

file(GLOB_RECURSE SRC_FILES src/*.*)
file(GLOB_RECURSE TEST_FILES test/*.*)
file(GLOB_RECURSE PRV_FILES private/*.*)

add_library(PolyCodeX-shared SHARED ${SRC_FILES} ${PRV_FILES})
add_library(PolyCodeX-static STATIC ${SRC_FILES} ${PRV_FILES})


target_include_directories(PolyCodeX-shared PUBLIC src/ modules/dr_audio)
target_include_directories(PolyCodeX-static PUBLIC src/ modules/dr_audio)

target_include_directories(PolyCodeX-shared PRIVATE private/)
target_include_directories(PolyCodeX-static PRIVATE private/)

add_subdirectory(modules/portaudio)

add_executable(tests ${TEST_FILES})
target_link_libraries(tests PUBLIC PolyCodeX-shared portaudio)
