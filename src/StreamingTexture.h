//
// Created by Ash on 2026-01-10.
//

#ifndef MYRAYTRACING_STREAMINGTEXTURE_H
#define MYRAYTRACING_STREAMINGTEXTURE_H


#include <vector>
#include <allegro5/allegro5.h>

class StreamingTexture
{
public:
    StreamingTexture();
    ~StreamingTexture();

    bool Create(int width, int height);
    void Destroy();

    [[nodiscard]] int Width()  const { return m_width;  }
    [[nodiscard]] int Height() const { return m_height; }

    // CPU buffer access (32-bit ABGR or RGBA depending on format)
    std::uint32_t* Data()       { return m_pixels.data(); }
    [[nodiscard]] const std::uint32_t* Data() const { return m_pixels.data(); }

    // Upload CPU buffer -> GPU texture
    bool Upload() const;

    // Draw to current target
    void Draw(float x, float y, int flags = 0) const;

    // Get underlying bitmap if needed (for ImGui::Image)
    [[nodiscard]] ALLEGRO_BITMAP* GetBitmap() const { return m_bitmap; }

private:
    ALLEGRO_BITMAP* m_bitmap = nullptr;
    std::vector<std::uint32_t> m_pixels;
    int m_width  = 0;
    int m_height = 0;
};



#endif //MYRAYTRACING_STREAMINGTEXTURE_H
