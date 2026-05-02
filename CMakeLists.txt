cmake_minimum_required(VERSION 3.6)
project(nclock)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CURSES_NEED_NCURSES YES)
find_package(Curses REQUIRED)

if (NOT Curses_FOUND)
    message(FATAL_ERROR "NCurses not found")
endif()

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include ${CURSES_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${CURSES_CFLAGS})

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)