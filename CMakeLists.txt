cmake_minimum_required(VERSION 3.19)
project(ArcadeGames LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

qt_add_executable(ArcadeGames
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    mainwindow.h
    sudoku.cpp
    sudokuwindow.cpp
    minesweeper.h
    minesweeper.cpp
    minesweeperwindow.h
    minesweeperwindow.cpp
    TICTACTOE.cpp
    TICTACTOE.h
    TicTacToeWindow.cpp
    TicTacToeWindow.h
    sudoku.h
    sudokuwindow.h
    cellbutton.h
    cellbutton.cpp
    snakegame.h
    snakegame.cpp
    windowsnake.h
    WINDOWSNAKE.cpp
)

target_link_libraries(ArcadeGames
    PRIVATE
        Qt::Core
        Qt::Multimedia
        Qt::Widgets
)

target_include_directories(ArcadeGames PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ArcadeGames/Header\ Files
)

include(GNUInstallDirs)

install(TARGETS ArcadeGames
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
# Copiar carpeta 'sounds' al directorio de salida (build/bin)
add_custom_command(TARGET ArcadeGames POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/sounds
            $<TARGET_FILE_DIR:ArcadeGames>/sounds)
            
qt_generate_deploy_app_script(
    TARGET ArcadeGames
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
