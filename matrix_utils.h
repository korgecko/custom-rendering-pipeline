#pragma once
#include <cmath>

// 4x4 행렬을 0으로 초기화
inline void ZeroMatrix(float M[4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            M[row][col] = 0.0f;
        }
    }
}

// 4x4 단위행렬을 초기화
inline void IdentityMatrix(float M[4][4])
{
    ZeroMatrix(M);

    for (int diagonal = 0; diagonal < 4; diagonal++)
    {
        M[diagonal][diagonal] = 1.0f;
    }
}

// 4x4 전치행렬 
inline void TransposeMatrix(float M[4][4])
{
    float temp[4][4]; // 임시로 전치 결과 저장

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            temp[row][col] = M[col][row]; // 행과 열 바꿔서 복사
        }
    }

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            M[row][col] = temp[row][col];
        }
    }
}

inline float DegreesToRadians(float degrees)
{
    return degrees * (3.14159265f / 180.0f);
}

// 회전행렬 행벡터 기준. 
inline void MakeXYPlaneRotationMatrix(float M[4][4], float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);

    M[0][0] =  cos;   M[0][1] =  sin;   M[0][2] = 0.0f;   M[0][3] = 0.0f;
    M[1][0] = -sin;   M[1][1] =  cos;   M[1][2] = 0.0f;   M[1][3] = 0.0f;
    M[2][0] = 0.0f;   M[2][1] = 0.0f;   M[2][2] = 1.0f;   M[2][3] = 0.0f;
    M[3][0] = 0.0f;   M[3][1] = 0.0f;   M[3][2] = 0.0f;   M[3][3] = 1.0f;
}

inline void MakeYZPlaneRotationMatrix(float M[4][4], float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);

    M[0][0] = 1.0f;    M[0][1] = 0.0f;   M[0][2] = 0.0f;   M[0][3] = 0.0f;
    M[1][0] = 0.0f;    M[1][1] =  cos;   M[1][2] = sin;   M[1][3] = 0.0f;
    M[2][0] = 0.0f;    M[2][1] = -sin;   M[2][2] = cos;   M[2][3] = 0.0f;
    M[3][0] = 0.0f;    M[3][1] = 0.0f;   M[3][2] = 0.0f;   M[3][3] = 1.0f;
}

inline void MakeZXPlaneRotationMatrix(float M[4][4], float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);

    M[0][0] = cos;     M[0][1] = 0.0f;   M[0][2] = -sin;   M[0][3] = 0.0f;
    M[1][0] = 0.0f;    M[1][1] = 1.0f;   M[1][2] = 0.0f;   M[1][3] = 0.0f;
    M[2][0] = sin;     M[2][1] = 0.0f;   M[2][2] = cos;    M[2][3] = 0.0f;
    M[3][0] = 0.0f;    M[3][1] = 0.0f;   M[3][2] = 0.0f;   M[3][3] = 1.0f;
}