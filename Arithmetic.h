#pragma once
constexpr float PI = 3.14159265359;
/// <summary>
///　ラジアン変換
/// </summary>
/// <param name="Frequency">度数法表記</param>
/// <returns></returns>
float ConversionRad(float Frequency)
{
    return Frequency * PI /180;
}
/// <summary>
/// 度数法変換
/// </summary>
/// <param name="Rad">ラジアン表記
/// </param>
/// <returns></returns>
float ConversionFrequency(float Rad)
{
    return Rad * 180/PI;
}