//
// Created by Ash on 2026-01-10.
//

#ifndef MYRAYTRACING_EXAMPLE01_H
#define MYRAYTRACING_EXAMPLE01_H

#include "App.h"
#include "RayTracerBitmap.h"

#include <memory>

class Example01 : public App
{
public:
    Example01();
    ~Example01() override;

    void Init() override;
    void InitResources() override;
    void Shutdown() override;
    int Run() override;
    void Abort() override;

    void RenderRaytracerBitmap() const;

protected:
    std::unique_ptr<RayTracerBitmap> m_rt_bitmap;

};


#endif //MYRAYTRACING_EXAMPLE01_H
