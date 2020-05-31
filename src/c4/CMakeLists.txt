file(GLOB c4_SRC "*.h" "*.cc")
add_executable(c4 ${c4_SRC})
target_link_libraries(c4 ${SDL_ALL_LIBS})
target_include_directories(c4 PRIVATE ${SDL_ALL_INCLUDE_DIRS})
