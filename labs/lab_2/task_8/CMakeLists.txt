cmake_minimum_required(VERSION 3.15...3.30)


project(
        Task_7
        VERSION 1.0
        LANGUAGES CXX
)

include_directories (src)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")

add_executable(main ${SOURCES} ${HEADERS})

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281
)

FetchContent_MakeAvailable(fmt)

target_link_libraries(main PUBLIC fmt::fmt)

