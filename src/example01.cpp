//
// Created by Ash on 2026-01-10.
//

#include "example01.h"

#include <memory>
#include <stdexcept>
#include <allegro5/allegro_primitives.h>

Example01::Example01() : App()
{
}

void Example01::Init()
{
    App::Init();
}


void Example01::InitResources()
{
    m_rt_bitmap = std::make_unique<RayTracerBitmap>(800, 600);
}

void Example01::RenderRaytracerBitmap() const
{
    // Blocking operation to initialize the bitmap texture
    if (!m_rt_bitmap->Lock())
        throw std::runtime_error("Failed to lock bitmap!");

    auto width = m_rt_bitmap->GetWidth();
    auto height = m_rt_bitmap->GetHeight();

    // Raytrace loop: write to m_rt_bitmap.Pixels()
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto u = static_cast<float>(x) / static_cast<float>(width);
            auto v = static_cast<float>(y) / static_cast<float>(height);

            m_rt_bitmap->SetPixel(x, y,
                1.0f,
                0.25f + 0.75f * u,
                0.25f + 0.75f * v);
        }
    }

    m_rt_bitmap->Unlock();
}

int Example01::Run()
{
    m_running = true;

    al_start_timer(m_timer);
    al_rest(0.1);
    float circle_radius = 50.0f;

    // Drop any pending events (e.g., spurious close/switch_out)
    while (!al_is_event_queue_empty(m_event_queue))
    {
        ALLEGRO_EVENT ev;
        al_get_next_event(m_event_queue, &ev);
    }

    RenderRaytracerBitmap();

    while (m_running)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(m_event_queue, &event);

        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
            {
                App::BeginFrame(event);

                // initial Draw
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_filled_circle(320, 240, circle_radius, al_map_rgb(255, 255, 255));

                // Dear ImGui here
                ImGui::Begin("Example01");
                ImGui::SliderFloat("Circle Radius", &circle_radius, 10.0f, 300.0f);
                ImGui::Text("Frames: %llu | FPS: %.1f", m_frames, m_io->Framerate);
                bool quit = ImGui::Button("Quit");
                ImGui::End();

                m_rt_bitmap->Render(m_display, 0.0f, 0.0f);

                App::EndFrame();

                if (quit)
                    m_running = false;
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                m_running = false;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    m_running = false;
                }
                break;
            }

            default:
                break;
        }
    }

    return 0;
}

void Example01::Abort()
{

}

void Example01::Shutdown()
{
    App::Shutdown();
}

Example01::~Example01() = default;
