cmake_minimum_required(VERSION 3.28)

project(DziaGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(DZIA_BUILD_TESTS "Build Dzia-Game tests" ON)

include(FetchContent)

set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(DZIA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Project1)

add_executable(DziaGame
    ${DZIA_SOURCE_DIR}/main.cpp
    ${DZIA_SOURCE_DIR}/ControlPanel.cpp
    ${DZIA_SOURCE_DIR}/Enemy.cpp
    ${DZIA_SOURCE_DIR}/FrogMan.cpp
    ${DZIA_SOURCE_DIR}/GameMenu.cpp
    ${DZIA_SOURCE_DIR}/GameSaver.cpp
    ${DZIA_SOURCE_DIR}/MainCharacter.cpp
    ${DZIA_SOURCE_DIR}/MapGrass.cpp)

target_link_libraries(DziaGame PRIVATE sfml-graphics sfml-window sfml-audio sfml-system)

if(MSVC)
    target_compile_options(DziaGame PRIVATE /utf-8)
endif()

add_custom_command(TARGET DziaGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${DZIA_SOURCE_DIR}/images $<TARGET_FILE_DIR:DziaGame>/images
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${DZIA_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:DziaGame>/fonts
    VERBATIM)

if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(DZIA_OPENAL_DLL ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll)
    else()
        set(DZIA_OPENAL_DLL ${SFML_SOURCE_DIR}/extlibs/bin/x86/openal32.dll)
    endif()
    add_custom_command(TARGET DziaGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${DZIA_OPENAL_DLL} $<TARGET_FILE_DIR:DziaGame>
        VERBATIM)
    install(FILES ${DZIA_OPENAL_DLL} DESTINATION .)
endif()

install(TARGETS DziaGame RUNTIME DESTINATION .)
install(DIRECTORY ${DZIA_SOURCE_DIR}/images ${DZIA_SOURCE_DIR}/fonts DESTINATION .)

if(DZIA_BUILD_TESTS)
    enable_testing()
    add_executable(GameSaverTest tests/GameSaverTest.cpp ${DZIA_SOURCE_DIR}/GameSaver.cpp)
    target_include_directories(GameSaverTest PRIVATE ${DZIA_SOURCE_DIR})
    if(MSVC)
        target_compile_options(GameSaverTest PRIVATE /utf-8)
    endif()
    set(DZIA_TEST_WORKDIR ${CMAKE_BINARY_DIR}/test-workdir)
    file(MAKE_DIRECTORY ${DZIA_TEST_WORKDIR})
    add_test(NAME GameSaverTest COMMAND GameSaverTest WORKING_DIRECTORY ${DZIA_TEST_WORKDIR})
endif()
