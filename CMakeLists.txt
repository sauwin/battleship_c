cmake_minimum_required(VERSION 3.16)

project(lode LANGUAGES C)

add_executable(lode main.c
    board.c
    board.h
    type.h
    ships.h
    ships.c
    ai.c
    ai.h
    save.c
    save.h



)

include(GNUInstallDirs)
install(TARGETS lode
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
