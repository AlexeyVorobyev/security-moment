cmake_minimum_required(VERSION 3.15...3.30)


project(
        Task_11
        VERSION 1.0
        LANGUAGES CXX
)

include_directories (src)


file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")

add_executable(Main ${SOURCES} ${HEADERS})
