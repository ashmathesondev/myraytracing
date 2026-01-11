//
// Created by Ash on 2026-01-10.
//

#ifndef MYRAYTRACING_RAYTRACERBITMAP_H
#define MYRAYTRACING_RAYTRACERBITMAP_H

#include <cstdint>
#include <allegro5/allegro5.h>

class RayTracerBitmap
{
    ALLEGRO_BITMAP *m_bitmap {nullptr};
    int m_width {0};
    int m_height {0};

    ALLEGRO_LOCKED_REGION *m_locked {nullptr};
    ALLEGRO_COLOR *m_pixels {nullptr}; // Raw RGBA floats
    std::uint8_t* m_pixels_8bit {nullptr};

public:
    RayTracerBitmap(int width, int height);
    ~RayTracerBitmap();

    [[nodiscard]] bool Lock();
    void Unlock();
    void Render(ALLEGRO_DISPLAY* display, float x, float y) const;

    [[nodiscard]] int GetPitch() const
    {
        if (!m_locked) return 0;
        return m_locked->pitch;
    }

    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;

    void SetPixel(int x, int y, float r, float g, float b) const;

    [[nodiscard]] ALLEGRO_COLOR* GetPixels() const { return m_pixels; };

};


#endif //MYRAYTRACING_RAYTRACERBITMAP_H
