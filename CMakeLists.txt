cmake_minimum_required(VERSION 3.10)

project(PolyCodeX)

add_subdirectory(modules/dr_libs)

file(GLOB_RECURSE SRC_FILES src/*.*)
file(GLOB_RECURSE TEST_FILES test/*.*)
file(GLOB_RECURSE PRV_FILES private/*.*)

add_subdirectory(modules/Bento4)


#add_library(PolyCodeX-shared SHARED ${SRC_FILES} ${PRV_FILES})
add_library(PolyCodeX-static STATIC ${SRC_FILES} ${PRV_FILES})


#target_include_directories(PolyCodeX-shared PUBLIC src/)
target_include_directories(PolyCodeX-static PUBLIC src/)

#target_include_directories(PolyCodeX-shared PUBLIC private/ modules/dr_libs)
target_include_directories(PolyCodeX-static PUBLIC private/ modules/dr_libs)

#target_link_libraries(PolyCodeX-shared PUBLIC ap4)
target_link_libraries(PolyCodeX-static PUBLIC ap4)

add_subdirectory(modules/portaudio)
add_executable(tests ${TEST_FILES})


target_link_libraries(tests PUBLIC PolyCodeX-static portaudio)
