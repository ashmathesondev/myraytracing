//
// Created by Ash on 2026-01-10.
//

#include "RayTracerBitmap.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

RayTracerBitmap::RayTracerBitmap(int width, int height) :
    m_width(width),
    m_height(height)
{
    // limit the size of the bitmap to 1024x1024
    if (m_width > 1024 || m_height > 1024)
        throw std::runtime_error("Bitmap size too large!");

    al_set_new_bitmap_flags(0 /*ALLEGRO_MEMORY_BITMAP | ALLEGRO_MIN_LINEAR*/);
    m_bitmap = al_create_bitmap(m_width, m_height);

    if (m_bitmap == nullptr)
        throw std::runtime_error("Failed to create bitmap!");
}

RayTracerBitmap::~RayTracerBitmap()
{
    if (m_bitmap != nullptr) al_destroy_bitmap(m_bitmap);
    m_bitmap = nullptr;
}

bool RayTracerBitmap::Lock()
{
    if (m_locked) return false; // already locked

    auto fmt = al_get_bitmap_format(m_bitmap);

    m_locked = al_lock_bitmap(m_bitmap, fmt, ALLEGRO_LOCK_WRITEONLY);

    if (m_locked == nullptr)
        throw std::runtime_error("Failed to lock bitmap!");

    m_pixels = static_cast<ALLEGRO_COLOR*>(m_locked->data);
    m_pixels_8bit = static_cast<std::uint8_t*>(m_locked->data);

    std::cout << "Locked bitmap with pitch: " << m_locked->pitch << std::endl;

    return true;
}

void RayTracerBitmap::Unlock()
{
    if (m_locked)
    {
        al_unlock_bitmap(m_bitmap);
        m_locked = nullptr;
        m_pixels = nullptr;
        m_pixels_8bit = nullptr;
    }
}

void RayTracerBitmap::Render(ALLEGRO_DISPLAY* display, float x, float y) const
{
    al_set_target_backbuffer(display);
    al_draw_bitmap(m_bitmap, x, y, 0);
}

void RayTracerBitmap::SetPixel(int x, int y, float r, float g, float b) const
{
    if (!m_locked)
        throw std::runtime_error("Bitmap is not locked!");

    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        throw std::runtime_error("Pixel out of bounds!");

    int bytes_per_pixel = 4; // ABGR_8888
    int index_bytes = y * m_locked->pitch + x * bytes_per_pixel;
    std::uint8_t* p = m_pixels_8bit + index_bytes;

    p[0] = static_cast<std::uint8_t>(b * 255.0f); // B
    p[1] = static_cast<std::uint8_t>(g * 255.0f); // G
    p[2] = static_cast<std::uint8_t>(r * 255.0f); // R
    p[3] = 1.0f;                                  // A

}

int RayTracerBitmap::GetWidth() const {return m_width;};

int RayTracerBitmap::GetHeight() const {return m_height;};
