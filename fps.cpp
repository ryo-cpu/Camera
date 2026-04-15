#include "fps.h"




fps::fps()
{
    FrameStart = std::chrono::high_resolution_clock::now();
    LastTime = FrameStart;
}

void fps::Initialization(double targetFrameTime)
{
    TargetFrameTime = targetFrameTime;
}

void fps::Start()
{
   
    FrameStart = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> duration_ms = FrameStart - LastTime;
    LastTime = FrameStart;
    DeltaTime = duration_ms.count() / 1000;
}

void fps::End()
{
    auto frameEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = frameEnd - FrameStart;

    double sleepTime = TargetFrameTime - elapsed.count();
    if (sleepTime > 0)
    {
     std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
    }
}

float fps::GetDeltaTime()
{
    return DeltaTime;
}
