add_executable(tictactoe)
target_sources(tictactoe PRIVATE
        ai.cpp
        ai.h
        app.cpp
        app.h
        board.cpp
        board.h
        constants.h
        helpers.cpp
        helpers.h
        main.cpp
        )
target_link_libraries(tictactoe PRIVATE ${SDL_ALL_LIBS})
target_include_directories(tictactoe PRIVATE ${SDL_ALL_INCLUDE_DIRS})
