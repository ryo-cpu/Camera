#pragma once
#include <chrono>
#include <thread>
static class fps
{
double TargetFrameTime;
std::chrono::high_resolution_clock::time_point FrameStart;
public:
    /// 必要なものの用意や目標とするFpsを取る
    void Initialization(double targetFrameTime);
    /// 処理時間を取りスリープで合わせる
    void Start();
    void End();
};

