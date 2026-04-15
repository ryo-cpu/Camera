#pragma once
#include <chrono>
#include <thread>
static class fps
{
double TargetFrameTime = 0;
std::chrono::high_resolution_clock::time_point FrameStart;
std::chrono::high_resolution_clock::time_point LastTime;
float DeltaTime=0;
public:
  
    /// 必要なものの用意や目標とするFpsを取る
    void Initialization(double targetFrameTime);
    /// 処理時間を取りスリープで合わせる
    void Start();
    void End();
    float GetDeltaTime();
};

