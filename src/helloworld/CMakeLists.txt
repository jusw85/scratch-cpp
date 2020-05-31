add_executable(helloworld main.cpp)
target_link_libraries(helloworld ${SDL_LIBRARY})
target_include_directories(helloworld PRIVATE ${SDL_INCLUDE_DIR})
