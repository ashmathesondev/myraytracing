cmake_minimum_required(VERSION 3.16)  # 4.1 invalid; use 3.16+
project(MyRaytracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Allegro CONFIG REQUIRED)

# --- Library target for logic ---
add_library(MyRaytracingLib STATIC
        src/RayTracerBitmap.cpp
        src/RayTracerBitmap.h
        src/StreamingTexture.cpp
        src/StreamingTexture.h
)
target_link_libraries(MyRaytracingLib PRIVATE
        Allegro::allegro
        Allegro::allegro_ttf
        Allegro::allegro_font
        Allegro::allegro_main
        Allegro::allegro_primitives
)
target_include_directories(MyRaytracingLib PUBLIC src)

# --- Main Executable ---
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/App.cpp
        src/example01.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        MyRaytracingLib
        Allegro::allegro
        Allegro::allegro_ttf
        Allegro::allegro_font
        Allegro::allegro_main
        Allegro::allegro_primitives
)

# Dear Imgui as a submodule
target_sources(${PROJECT_NAME}
        PRIVATE
        extern/imgui/imgui.cpp
        extern/imgui/imgui_draw.cpp
        extern/imgui/imgui_widgets.cpp
        extern/imgui/imgui_tables.cpp
        # Backend
        extern/imgui/backends/imgui_impl_allegro5.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        extern/imgui
        extern/imgui/backends
)

# --- Unit Testing ---
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(unit_tests
        tests/test_bitmap.cpp
)
target_link_libraries(unit_tests
        PRIVATE
        MyRaytracingLib
        GTest::gtest_main
        Allegro::allegro
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
