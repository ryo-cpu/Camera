#pragma once
constexpr float PI = 3.14159265359;
/// <summary>
///�@���W�A���ϊ�
/// </summary>
/// <param name="Frequency">�x���@�\�L</param>
/// <returns></returns>
float ConversionRad(float Frequency)
{
    return Frequency * PI /180;
}
/// <summary>
/// �x���@�ϊ�
/// </summary>
/// <param name="Rad">���W�A���\�L
/// </param>
/// <returns></returns>
float ConversionFrequency(float Rad)
{
    return Rad * 180/PI;
}