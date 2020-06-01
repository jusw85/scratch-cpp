cmake_minimum_required(VERSION 3.17)
project(scratch)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# message("${CMAKE_CXX_STANDARD}")

# Module list
# https://cmake.org/cmake/help/v3.17/manual/cmake-modules.7.html#find-modules
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

set(SDL_ALL_LIBS ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES})
set(SDL_ALL_INCLUDE_DIRS ${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIRS})

add_subdirectory("src/helloworld")
add_subdirectory("src/tictactoe")
add_subdirectory("src/connect4")
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
