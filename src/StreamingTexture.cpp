//
// Created by Ash on 2026-01-10.
//

#include "StreamingTexture.h"

#include <cstdio>

StreamingTexture::StreamingTexture() = default;

StreamingTexture::~StreamingTexture()
{
    Destroy();
}

bool StreamingTexture::Create(int width, int height)
{
    Destroy();

    m_width  = width;
    m_height = height;
    m_pixels.resize(static_cast<size_t>(width) * height);

    // Create GPU/display bitmap (no MEMORY flag)
    al_set_new_bitmap_flags(0);
    m_bitmap = al_create_bitmap(width, height);
    if (!m_bitmap)
    {
        std::fprintf(stderr, "StreamingTexture: failed to create bitmap %dx%d\n", width, height);
        m_width = m_height = 0;
        m_pixels.clear();
        return false;
    }

    return true;
}

void StreamingTexture::Destroy()
{
    if (m_bitmap)
    {
        al_destroy_bitmap(m_bitmap);
        m_bitmap = nullptr;
    }
    m_pixels.clear();
    m_width = m_height = 0;
}

bool StreamingTexture::Upload() const
{
    if (!m_bitmap || m_pixels.empty())
        return false;

    // Lock GPU bitmap in a known 4-byte format (ABGR_8888)
    ALLEGRO_LOCKED_REGION* lock =
        al_lock_bitmap(m_bitmap, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
    if (!lock)
    {
        std::fprintf(stderr, "StreamingTexture: al_lock_bitmap failed\n");
        return false;
    }

    const int pitch_bytes   = lock->pitch;
    auto* dst = static_cast<std::uint8_t*>(lock->data);
    const auto* src = reinterpret_cast<const std::uint8_t*>(m_pixels.data());

    // Copy row by row (handles pitch != width * bytes_per_px)
    for (int y = 0; y < m_height; ++y)
    {
        constexpr int bytes_per_px  = 4;
        const std::uint8_t* src_row = src + static_cast<size_t>(y) * m_width * bytes_per_px;
        std::uint8_t*       dst_row = dst + static_cast<size_t>(y) * pitch_bytes;
        std::memcpy(dst_row, src_row, static_cast<size_t>(m_width) * bytes_per_px);
    }

    al_unlock_bitmap(m_bitmap);
    return true;
}

void StreamingTexture::Draw(float x, float y, int flags) const
{
    if (!m_bitmap)
        return;

    al_draw_bitmap(m_bitmap, x, y, flags);
}
