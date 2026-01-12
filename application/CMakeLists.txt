set(NAME application)

if (WIN32 AND BUILD_GUI)
    add_executable(${NAME} WIN32)
else()
    add_executable(${NAME})
endif()

target_compile_features(${NAME} PUBLIC c_std_11)
target_compile_definitions(${NAME} PUBLIC _CRT_SECURE_NO_WARNINGS)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${NAME} PUBLIC -Wall)
endif()

target_sources(${NAME} PRIVATE
    "src/main.c"
    "src/settings.h"
    "src/common.h"
    "src/common.c"
    "src/game/asset_manager.c"
    "src/game/asset_manager.h"
    "src/game/input.c"
    "src/game/input.h"
    "src/game/level/level_canvas.c"
    "src/game/level/level_canvas.h"
    "src/game/level/level_scene.c"
    "src/game/level/level_scene.h"
    "src/game/level/track.c"
    "src/game/level/track.h"
    "src/game/title/title_canvas.c"
    "src/game/title/title_canvas.h"
    "src/game/title/title_scene.c"
    "src/game/title/title_scene.h"
    "src/utils/math.h"
    "src/utils/math.c"
    "src/utils/text.h"
    "src/utils/text.c"
    "src/utils/timer.h"
    "src/utils/timer.c"
)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(${NAME} PUBLIC ${MATH_LIBRARY})
endif()

#-------------------------------------------------------------------------------
# Third party libraries

if(MSVC)
    message(STATUS "MSCV DETECTED")
    set(THIRD_PARTY_SDL2_DIR       "${CMAKE_SOURCE_DIR}/third_party/SDL2-2.32.10")
    set(THIRD_PARTY_SDL2_IMAGE_DIR "${CMAKE_SOURCE_DIR}/third_party/SDL2_image-2.8.8")
    set(THIRD_PARTY_SDL2_TTF_DIR   "${CMAKE_SOURCE_DIR}/third_party/SDL2_ttf-2.24.0")
    set(THIRD_PARTY_SDL2_MIX_DIR   "${CMAKE_SOURCE_DIR}/third_party/SDL2_mixer-2.8.1")

    list(APPEND CMAKE_PREFIX_PATH
        "${THIRD_PARTY_SDL2_DIR}/cmake"
        "${THIRD_PARTY_SDL2_IMAGE_DIR}/cmake"
        "${THIRD_PARTY_SDL2_TTF_DIR}/cmake"
        "${THIRD_PARTY_SDL2_MIX_DIR}/cmake"
    )
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

if(TARGET SDL2::SDL2main)
    target_link_libraries(${NAME} PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(${NAME} PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)

#-------------------------------------------------------------------------------
# Other include directories

target_include_directories(
    ${NAME} PUBLIC
    "src"
)

#-------------------------------------------------------------------------------
# Copy DLL and files

if(WIN32)
    # Use the imported target file locations so this works with vcpkg, installer, etc.
    add_custom_command(TARGET ${NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:${NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2_image::SDL2_image> $<TARGET_FILE_DIR:${NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2_ttf::SDL2_ttf> $<TARGET_FILE_DIR:${NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2_mixer::SDL2_mixer> $<TARGET_FILE_DIR:${NAME}>
    )
endif()
