#pragma once
constexpr float PI = 3.14159265359f;
/// <summary>
///　ラジアン変換
/// </summary>
/// <param name="Frequency">度数法表記</param>
/// <returns></returns>
constexpr float ConversionRad(float Frequency)
{
    return Frequency * PI /180;
}
/// <summary>
/// 度数法変換
/// </summary>
/// <param name="Rad">ラジアン表記
/// </param>
/// <returns></returns>
constexpr float ConversionFrequency(float Rad)
{
    return Rad * 180/PI;
}
constexpr bool InRange(int Strat, int Last,int Check)
{
    return Check >= Strat && Last >= Check;
}

constexpr bool InRange(float Strat, float  Last, float Check)
{
    return Check >= Strat && Last >= Check;
}