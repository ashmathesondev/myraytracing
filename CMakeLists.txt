cmake_minimum_required(VERSION 3.16)  # 4.1 invalid; use 3.16+
project(MyRaytracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Allegro CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/App.cpp
        src/example01.cpp
        src/RayTracerBitmap.cpp
        src/RayTracerBitmap.h
        src/StreamingTexture.cpp
        src/StreamingTexture.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
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
