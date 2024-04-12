cmake_minimum_required(VERSION 3.16)
project(CourseWork LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CourseWork src/main.cpp
        src/main.cpp "src/sources/Field.cpp"  "src/headers/Constants.h" "src/headers/Checker.h" "src/sources/Checker.cpp" "src/sources/Game.cpp"  "src/headers/Game.h" "src/headers/Button.h" "src/sources/Button.cpp" "src/headers/Label.h" "src/sources/Label.cpp" "src/headers/List.h" "src/headers/Bot.h" "src/sources/Bot.cpp" )
target_link_libraries(CourseWork PRIVATE sfml-graphics)
target_compile_features(CourseWork PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CourseWork
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CourseWork>
        VERBATIM)
endif()

install(TARGETS CourseWork)
