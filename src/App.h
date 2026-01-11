//
// Created by Ash on 2026-01-10.
// Basic application framework
//

#ifndef MYRAYTRACING_APP_H
#define MYRAYTRACING_APP_H

#include <allegro5/allegro5.h>
#include <imgui.h>
#include <imgui_impl_allegro5.h>

class App
{
public:
    App();
    virtual ~App();

    virtual void Init();
    virtual void InitResources();
    virtual int Run() = 0;
    virtual int BeginFrame(ALLEGRO_EVENT event);
    virtual int EndFrame();
    virtual void Abort();
    virtual void Shutdown();
protected:
    void InternalShutdown();

protected:
    bool m_running {false};

    ALLEGRO_DISPLAY* m_display {nullptr};
    ALLEGRO_EVENT_QUEUE* m_event_queue {nullptr};
    ALLEGRO_TIMER* m_timer {nullptr};
    uint64_t m_frames {0};

    ImGuiIO* m_io;
};


#endif //MYRAYTRACING_APP_H
