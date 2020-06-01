add_executable(connect4)
target_sources(connect4 PRIVATE
        ai.cpp
        ai.h
        app.cpp
        app.h
        # board.cpp
        # board.h
        board2.cpp
        board2.h
        constants.h
        helpers.cpp
        helpers.h
        transtable.h
        main.cpp
        )
target_link_libraries(connect4 PRIVATE ${SDL_ALL_LIBS})
target_include_directories(connect4 PRIVATE ${SDL_ALL_INCLUDE_DIRS})
