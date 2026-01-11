//
// Created by Ash on 2026-01-10.
//

#include "App.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <allegro5/allegro_primitives.h>
#include <imgui_impl_allegro5.h>

App::App() :
    m_running(true), m_event_queue(nullptr), m_timer(nullptr), m_frames(0), m_io(nullptr)
{
    if (!al_init())
    {
        throw std::runtime_error("Failed to initialize Allegro!");
    }

    if (!al_install_keyboard())
    {
        throw std::runtime_error("Failed to install keyboard!");
    }
    al_init_primitives_addon();

}

App::~App()
{
    if (m_running) InternalShutdown();
}

void App::Init()
{
    al_set_new_display_option(ALLEGRO_VSYNC, 0, ALLEGRO_SUGGEST);
    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
    m_display = al_create_display(1024, 768);
    if (!m_display)
        throw std::runtime_error("Failed to create display!");

    m_timer = al_create_timer(1.0 / 60.0);
    if (!m_timer)
        throw std::runtime_error("Failed to create timer!");

    if (!al_install_mouse())
        throw std::runtime_error("Failed to install mouse!");

    m_event_queue = al_create_event_queue();
    if (!m_event_queue)
        throw std::runtime_error("Failed to create event queue!");

    al_register_event_source(m_event_queue, al_get_display_event_source(m_display));
    al_register_event_source(m_event_queue, al_get_keyboard_event_source());
    al_register_event_source(m_event_queue, al_get_mouse_event_source());
    al_register_event_source(m_event_queue, al_get_timer_event_source(m_timer));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_io = &ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplAllegro5_Init(m_display);
}

void App::InitResources()
{}

int App::BeginFrame(ALLEGRO_EVENT event)
{
    // Feed Allegro events to ImGui
    ImGui_ImplAllegro5_ProcessEvent(&event);

    // STRICT SEQUENCE: Backend first, then ImGui
    ImGui_ImplAllegro5_NewFrame();
    // Poll mouse events
    ALLEGRO_MOUSE_STATE mouseState;
    al_get_mouse_state(&mouseState);
    m_io->MousePos = ImVec2(static_cast<float>(mouseState.x), static_cast<float>(mouseState.y));
    m_io->MouseDown[0] = al_mouse_button_down(&mouseState, 1);
    m_io->MouseDown[2] = al_mouse_button_down(&mouseState, 2);
    ImGui::NewFrame();
    return 0;
}

int App::EndFrame()
{
    ImGui::Render();  // Generate draw lists
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());

    al_flip_display();
    m_frames++;

    return 0;
}

void App::InternalShutdown()
{
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_timer(m_timer);
    al_destroy_event_queue(m_event_queue);
    al_destroy_display(m_display);
    al_uninstall_keyboard();

    m_running = false;

    std::cout << "Frame count: " << m_frames << std::endl;

}

void App::Shutdown()
{
    InternalShutdown();
}

void App::Abort()
{}
