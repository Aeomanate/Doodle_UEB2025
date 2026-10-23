cmake_minimum_required(VERSION 3.30)
project(Aeomanate_Doodle_UEB2025 LANGUAGES CXX)

if(POLICY CMP0207)
    cmake_policy(SET CMP0207 NEW)
endif()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Deps

include(FetchContent)

# Keep reflect-cpp static for both framework variants.
set(REFLECTCPP_BUILD_SHARED OFF)
set(REFLECTCPP_INSTALL OFF)

FetchContent_Declare(ReflectCPP
        GIT_REPOSITORY https://github.com/getml/reflect-cpp.git
        GIT_TAG main
        SYSTEM
)

FetchContent_Declare(AeoGameFramework
        GIT_REPOSITORY https://github.com/Aeomanate/AeoGameFramework.git
        GIT_TAG master
        SYSTEM
)

FetchContent_MakeAvailable(ReflectCPP AeoGameFramework)

# Only the game and its runtime files belong in this installation.
set_property(DIRECTORY "${reflectcpp_SOURCE_DIR}" PROPERTY EXCLUDE_FROM_ALL TRUE)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Framework header

# Replace the old header while preserving existing Framework.h includes.
configure_file(
        "${aeogameframework_SOURCE_DIR}/include/AeoGameFramework.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/3rd-party/Framework.h"
        COPYONLY
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Target definition

set(SRC_GAME
        src/stdafx.cpp
        src/game.cpp
        src/Application/Details/Logger.cpp
        src/Application/Sprite/FrameAnimation.cpp
        src/UI/Elements/Font.cpp
        src/UI/Elements/Text.cpp
        src/Simulation/GameLevels/Base/LevelBase.cpp
        src/Simulation/GameLevels/Base/LevelsManager.cpp
        src/Simulation/ECS/Features/Info/EDebugText.cpp
        src/Simulation/ECS/Features/Info/SDebugInfo.cpp
        src/Simulation/GameLevels/Level1.cpp
        src/Simulation/ECS/Features/Input/SInputCleaner.cpp
        src/Simulation/Simulation.cpp
        src/Simulation/ECS/Features/Input/SInputInjector.cpp
        src/Simulation/ECS/Features/Input/EInputContainer.cpp
        src/Simulation/ECS/Features/Levels/ELevelState.cpp
        src/Simulation/ECS/Features/Levels/SLevelStateObserver.cpp
        src/Simulation/ECS/Features/Visual/SEntityPainter.cpp
        src/Simulation/ECS/Features/Visual/SSpriteAnimator.cpp
        src/Application/Details/WindowsRelated.cpp
        src/Simulation/ECS/Features/Movable/EntityMover.cpp
        src/Simulation/ECS/Features/LifetimeControl/SSpawner.cpp
        src/Simulation/ECS/Features/LifetimeControl/ESpawnHolder.cpp
        src/Simulation/Features/Score/SScoreTracker.cpp
        src/Simulation/Features/Timer/ETimer.cpp
        src/Application/Application.cpp
        src/Simulation/Features/Timer/STimer.cpp
        src/Application/AppPartGetter.cpp
        src/Simulation/Features/Player/EPlayer.cpp
        src/Simulation/Features/Player/SInputMove.cpp
        src/Simulation/Features/Abilities/Shooting/SHandlerHit.cpp
        src/Simulation/Features/Abilities/Shooting/SInputShoot.cpp
        src/Application/LowLevelApplication.cpp
        src/Application/Config/ConfigSimulation.cpp
        src/Application/Config/ConfigResources.cpp
        src/Application/Config/ConfigGeneral.cpp
        src/Simulation/Features/Background/EBackground.cpp
        src/GameLayers/MenuLayer.cpp
        src/UI/Elements/Button.cpp
        src/UI/Menus/BaseMenu.cpp
        src/UI/Menus/EndGameMenu.cpp
        src/UI/Menus/GameplayMenu.cpp
        src/UI/Menus/MainMenu.cpp
        src/UI/Menus/PauseMenu.cpp
        src/Application/Sprite/CustomSprite.cpp
        src/Simulation/ECS/Features/Movable/SCollisionDetector.cpp
        src/ParamsParser.cpp
        src/Simulation/Features/Platforms/SPlatformsManager.cpp
        src/Simulation/Features/Platforms/EPlatform.cpp
        src/Simulation/Features/Abilities/Shooting/EProjectile.cpp
        src/Simulation/Features/Enemies/EEnemy.cpp
        src/Simulation/Features/Enemies/SEnemyManager.cpp
        src/Simulation/Features/Abilities/Moving/EJetpack.cpp
        src/Simulation/Features/Abilities/Moving/SJetpackController.cpp
        src/Simulation/Features/Abilities/Moving/SJetpackSpawner.cpp
        src/Simulation/Features/Abilities/EShield.cpp
        src/Simulation/Features/Abilities/SShieldController.cpp
        src/Simulation/Features/Abilities/SShieldSpawner.cpp
        src/Simulation/Features/Abilities/Moving/SWallTransfer.cpp
        src/Simulation/Features/Player/SGameOverTracker.cpp
        src/Simulation/Features/Abilities/Moving/SSpeedBoosterHAlfScreen.cpp
        src/Simulation/Features/Platforms/EFragilePlatform.cpp
        src/Simulation/ECS/Features/LifetimeControl/SDespawner.cpp
        src/Simulation/Features/Abilities/Moving/SJump.cpp
        src/Simulation/ECS/Features/Visual/SViewport.cpp
        src/Simulation/Features/Abilities/Moving/SFall.cpp
        src/Simulation/Features/Background/SBackground.cpp
        src/Simulation/Features/Platforms/CTagPlatform.h
        src/Simulation/ECS/Features/Movable/ECollisions.cpp
        src/Simulation/ECS/Features/Movable/ECollisions.h
        src/Simulation/ECS/Features/Movable/CCollisions.h
        src/Simulation/ECS/Features/Movable/CCanCollide.h
        src/Simulation/Features/Enemies/CTagEnemy.h
        src/Simulation/Features/Platforms/CPlatformsStorage.h
        src/Simulation/Features/Platforms/EPlatformsStorage.cpp
        src/Simulation/Features/Platforms/EPlatformsStorage.h
        src/Simulation/Features/Enemies/CTagNoEnemySpawner.h
        src/Simulation/Features/Abilities/Moving/CSpeedBooster.h
)

add_executable(${PROJECT_NAME} ${SRC_GAME})

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Target options

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_26)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS ON)

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.hpp)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Change this line to Aeo::GameFramework::Static for the static variant.
set(FRAMEWORK_TARGET Aeo::GameFramework::Shared)

target_link_libraries(${PROJECT_NAME} PRIVATE
        reflectcpp::reflectcpp
        ${FRAMEWORK_TARGET}
)

get_target_property(FRAMEWORK_TYPE ${FRAMEWORK_TARGET} TYPE)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _WINDOWS)
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            "$<$<CONFIG:Debug>:/Od>"
            "$<$<NOT:$<CONFIG:Debug>>:/O2>"
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -Wpedantic
            -Wno-unused-parameter
            -Wno-unused-but-set-variable
            -Wno-missing-field-initializers
            "$<$<CONFIG:Debug>:-O0>"
            "$<$<NOT:$<CONFIG:Debug>>:-O2>"
    )

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${PROJECT_NAME} PRIVATE -fconcepts-diagnostics-depth=10)
    endif()
endif()

if(MINGW AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
        AND FRAMEWORK_TYPE STREQUAL "STATIC_LIBRARY")
    target_link_options(${PROJECT_NAME} PRIVATE -static)
endif()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Build output

set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/installed/bin")

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Resources

# Run on every game build so resource-only edits are copied too.
add_custom_target(${PROJECT_NAME}_resources
        COMMAND "${CMAKE_COMMAND}" -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
        "${CMAKE_CURRENT_SOURCE_DIR}/installed/res"
        VERBATIM
)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_resources)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Runtime DLLs

if(WIN32 AND FRAMEWORK_TYPE STREQUAL "SHARED_LIBRARY")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            COMMAND_EXPAND_LISTS
            VERBATIM
    )
endif()

if(MINGW)
    get_filename_component(COMPILER_RUNTIME_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    file(GLOB MINGW_RUNTIME_DLLS
            "${COMPILER_RUNTIME_DIR}/libgcc_s_*.dll"
            "${COMPILER_RUNTIME_DIR}/libstdc++-*.dll"
            "${COMPILER_RUNTIME_DIR}/libwinpthread-*.dll"
    )
    if(MINGW_RUNTIME_DLLS)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                ${MINGW_RUNTIME_DLLS}
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
                VERBATIM
        )
        install(FILES ${MINGW_RUNTIME_DLLS} DESTINATION bin)
    endif()
endif()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Target install

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/installed"
        CACHE PATH "Game installation directory" FORCE
)

set(INSTALL_TARGETS ${PROJECT_NAME})
if(FRAMEWORK_TYPE STREQUAL "SHARED_LIBRARY")
    get_target_property(FRAMEWORK_LIBRARY ${FRAMEWORK_TARGET} ALIASED_TARGET)
    set_property(TARGET ${FRAMEWORK_LIBRARY} PROPERTY EXCLUDE_FROM_ALL FALSE)
    list(APPEND INSTALL_TARGETS ${FRAMEWORK_LIBRARY})
endif()

if(WIN32)
    install(TARGETS ${INSTALL_TARGETS}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION bin
    )
else()
    if(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                INSTALL_RPATH "@loader_path/../lib"
        )
    elseif(UNIX)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                INSTALL_RPATH "$ORIGIN/../lib"
        )
    endif()

    install(TARGETS ${INSTALL_TARGETS}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
    )
endif()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/res/"
        DESTINATION res
)
