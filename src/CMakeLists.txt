
cmake_minimum_required(VERSION 3.16)
project(App LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB APP_SOURCE src/*.cpp)
file(GLOB APP_HEADERS include/*.h)

add_library(app ${APP_SOURCE} ${APP_HEADERS})
add_library(pw::app ALIAS app)

target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(app PUBLIC sfml-graphics)
target_compile_features(app PUBLIC cxx_std_17)

target_compile_options(app PRIVATE /W4 /WX)

if(WIN32)
    add_custom_command(
        TARGET app
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:app>
        VERBATIM)
endif()
