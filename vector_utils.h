#pragma once
#include <cmath>

// 3d 벡터 구조체
struct Vector3
{
    float x;
    float y;
    float z;

    // 생성자
    Vector3() : x(0.f), y(0.f), z(0.f) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    // 길이(크기) 반환
    float Length() const 
    {
        return std::sqrt(x*x + y*y + z*z);
    }

    // 길이 제곱 반환 (루트 연산 없이 빠르게 비교 할 때 사용)
    float SquaredLength() const
    {
        return x*x + y*y + z*z;
    }

    bool Normalize()
    {
        
    }

    Vector3 GetSafeNormal() const
    {

    }

    Vector3 InnerProduct() const {}

    Vector3 DotProduct() const {}

    Vector3 CrossProduct() const {}

}
