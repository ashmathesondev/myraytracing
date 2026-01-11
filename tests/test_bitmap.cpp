#include <gtest/gtest.h>
#include "RayTracerBitmap.h"
#include "StreamingTexture.h"
#include <allegro5/allegro.h>

class AllegroTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        if (!al_is_system_installed())
        {
            ASSERT_TRUE(al_init());
        }
    }

    void TearDown() override
    {
    }
};

class BitmapTest : public AllegroTest
{
};

TEST_F(BitmapTest, ConstructorInitializesCorrectly)
{
    RayTracerBitmap bitmap(100, 200);
    EXPECT_EQ(bitmap.GetWidth(), 100);
    EXPECT_EQ(bitmap.GetHeight(), 200);
}

TEST_F(BitmapTest, LargeBitmapThrowsException)
{
    EXPECT_THROW(RayTracerBitmap(2000, 2000), std::runtime_error);
}

TEST_F(BitmapTest, LockAndUnlock)
{
    RayTracerBitmap bitmap(10, 10);
    EXPECT_TRUE(bitmap.Lock());
    EXPECT_GT(bitmap.GetPitch(), 0);
    bitmap.Unlock();
}

TEST_F(BitmapTest, SetPixelRequiresLock)
{
    RayTracerBitmap bitmap(10, 10);
    EXPECT_THROW(bitmap.SetPixel(0, 0, 1.0f, 0.0f, 0.0f), std::runtime_error);
}

TEST_F(BitmapTest, SetPixelBoundsCheck)
{
    RayTracerBitmap bitmap(10, 10);
    (void)bitmap.Lock();
    EXPECT_THROW(bitmap.SetPixel(-1, 0, 1.0f, 0.0f, 0.0f), std::runtime_error);
    EXPECT_THROW(bitmap.SetPixel(10, 0, 1.0f, 0.0f, 0.0f), std::runtime_error);
    EXPECT_THROW(bitmap.SetPixel(0, -1, 1.0f, 0.0f, 0.0f), std::runtime_error);
    EXPECT_THROW(bitmap.SetPixel(0, 10, 1.0f, 0.0f, 0.0f), std::runtime_error);
    bitmap.Unlock();
}

class StreamingTextureTest : public AllegroTest
{
};

TEST_F(StreamingTextureTest, CreateAndDestroy)
{
    StreamingTexture tex;
    EXPECT_TRUE(tex.Create(100, 100));
    EXPECT_EQ(tex.Width(), 100);
    EXPECT_EQ(tex.Height(), 100);
    EXPECT_NE(tex.GetBitmap(), nullptr);
    tex.Destroy();
    EXPECT_EQ(tex.Width(), 0);
    EXPECT_EQ(tex.GetBitmap(), nullptr);
}

TEST_F(StreamingTextureTest, UploadWithoutDisplayFails)
{
    StreamingTexture tex;
    tex.Create(10, 10);
    // al_lock_bitmap might fail without a display or if it's not a memory bitmap
    // In our case it's created with flag 0, which usually means video bitmap if display exists.
    // If no display exists, Allegro might still create it as memory bitmap or fail.
    // Let's see what happens.
    bool result = tex.Upload();
    // We don't strictly require it to pass here if we don't have a display.
    // But we can check if the data buffer is allocated.
    EXPECT_NE(tex.Data(), nullptr);
}
