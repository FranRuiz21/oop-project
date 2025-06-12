cmake_minimum_required(VERSION 3.19)
project(ArcadeGames LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(ArcadeGames
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    sudoku.cpp
    sudokuwindow.cpp
    minesweeper.h
    minesweeper.cpp
    minesweeperwindow.h
    minesweeperwindow.cpp


    minesweeperwindow.ui
)

target_link_libraries(ArcadeGames
    PRIVATE
        Qt::Core
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

qt_generate_deploy_app_script(
    TARGET ArcadeGames
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
