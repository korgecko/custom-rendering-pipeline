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

inline void MultiplyMatrix(float out[4][4], const float A[4][4], const float B[4][4])
{
    // for (int row = 0; row < 4; row++) // 출력 행
    // {
    //     for (int col = 0; col < 4; col++) // 출력 열
    //     {
    //         	out[row][col] =
    //                 A[row][0] * B[0][col] +
    //                 A[row][1] * B[1][col] +
    //                 A[row][2] * B[2][col] +
    //                 A[row][3] * B[3][col];
    //     }
    // }

    // Row 0
    out[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0] + A[0][3]*B[3][0];
    out[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1] + A[0][2]*B[2][1] + A[0][3]*B[3][1];
    out[0][2] = A[0][0]*B[0][2] + A[0][1]*B[1][2] + A[0][2]*B[2][2] + A[0][3]*B[3][2];
    out[0][3] = A[0][0]*B[0][3] + A[0][1]*B[1][3] + A[0][2]*B[2][3] + A[0][3]*B[3][3];

    // Row 1
    out[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0] + A[1][2]*B[2][0] + A[1][3]*B[3][0];
    out[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1] + A[1][2]*B[2][1] + A[1][3]*B[3][1];
    out[1][2] = A[1][0]*B[0][2] + A[1][1]*B[1][2] + A[1][2]*B[2][2] + A[1][3]*B[3][2];
    out[1][3] = A[1][0]*B[0][3] + A[1][1]*B[1][3] + A[1][2]*B[2][3] + A[1][3]*B[3][3];

    // Row 2
    out[2][0] = A[2][0]*B[0][0] + A[2][1]*B[1][0] + A[2][2]*B[2][0] + A[2][3]*B[3][0];
    out[2][1] = A[2][0]*B[0][1] + A[2][1]*B[1][1] + A[2][2]*B[2][1] + A[2][3]*B[3][1];
    out[2][2] = A[2][0]*B[0][2] + A[2][1]*B[1][2] + A[2][2]*B[2][2] + A[2][3]*B[3][2];
    out[2][3] = A[2][0]*B[0][3] + A[2][1]*B[1][3] + A[2][2]*B[2][3] + A[2][3]*B[3][3];

    // Row 3
    out[3][0] = A[3][0]*B[0][0] + A[3][1]*B[1][0] + A[3][2]*B[2][0] + A[3][3]*B[3][0];
    out[3][1] = A[3][0]*B[0][1] + A[3][1]*B[1][1] + A[3][2]*B[2][1] + A[3][3]*B[3][1];
    out[3][2] = A[3][0]*B[0][2] + A[3][1]*B[1][2] + A[3][2]*B[2][2] + A[3][3]*B[3][2];
    out[3][3] = A[3][0]*B[0][3] + A[3][1]*B[1][3] + A[3][2]*B[2][3] + A[3][3]*B[3][3];
}

inline float DegreesToRadians(float degrees)
{
    return degrees * (3.14159265f / 180.0f);
}

// 행벡터 기준 스케일행렬
inline void ScaleMatrix(float M[4][4], float ScaleX, float ScaleY, float ScaleZ)
{
    M[0][0] = ScaleX;       M[0][1] = 0.0f;         M[0][2] = 0.0f;          M[0][3] = 0.0f;
    M[1][0] = 0.0f;         M[1][1] = ScaleY;       M[1][2] = 0.0f;          M[1][3] = 0.0f;
    M[2][0] = 0.0f;         M[2][1] = 0.0f;         M[2][2] = ScaleZ;        M[2][3] = 0.0f;
    M[3][0] = 0.0f;         M[3][1] = 0.0f;         M[3][2] = 0.0f;          M[3][3] = 1.0f;
}

// 회전행렬 행벡터 기준. 반시계 방향으로 회전
inline void MakeXYPlaneRotationMatrix(float M[4][4], float radians)
{
    float cosTheta = cosf(radians);
    float sinTheta = sinf(radians);

    M[0][0] =  cosTheta;   M[0][1] =  sinTheta;   M[0][2] = 0.0f;   M[0][3] = 0.0f;
    M[1][0] = -sinTheta;   M[1][1] =  cosTheta;   M[1][2] = 0.0f;   M[1][3] = 0.0f;
    M[2][0] = 0.0f;        M[2][1] = 0.0f;        M[2][2] = 1.0f;   M[2][3] = 0.0f;
    M[3][0] = 0.0f;        M[3][1] = 0.0f;        M[3][2] = 0.0f;   M[3][3] = 1.0f;
}

inline void MakeYZPlaneRotationMatrix(float M[4][4], float radians)
{
    float cosTheta = cosf(radians);
    float sinTheta = sinf(radians);

    M[0][0] = 1.0f;    M[0][1] = 0.0f;        M[0][2] = 0.0f;       M[0][3] = 0.0f;
    M[1][0] = 0.0f;    M[1][1] =  cosTheta;   M[1][2] = sinTheta;   M[1][3] = 0.0f;
    M[2][0] = 0.0f;    M[2][1] = -sinTheta;   M[2][2] = cosTheta;   M[2][3] = 0.0f;
    M[3][0] = 0.0f;    M[3][1] = 0.0f;        M[3][2] = 0.0f;       M[3][3] = 1.0f;
}

inline void MakeZXPlaneRotationMatrix(float M[4][4], float radians)
{
    float cosTheta = cosf(radians);
    float sinTheta = sinf(radians);

    M[0][0] = cosTheta;     M[0][1] = 0.0f;   M[0][2] = -sinTheta;   M[0][3] = 0.0f;
    M[1][0] = 0.0f;         M[1][1] = 1.0f;   M[1][2] = 0.0f;        M[1][3] = 0.0f;
    M[2][0] = sinTheta;     M[2][1] = 0.0f;   M[2][2] = cosTheta;    M[2][3] = 0.0f;
    M[3][0] = 0.0f;         M[3][1] = 0.0f;   M[3][2] = 0.0f;        M[3][3] = 1.0f;
}

// 행벡터 기준 이동행렬
inline void TranslationMatrix(float M[4][4], float TranslateX, float TranslateY, float TranslateZ)
{
    M[0][0] = 1.0f;         M[0][1] = 0.0f;         M[0][2] = 0.0f;          M[0][3] = 0.0f;
    M[1][0] = 0.0f;         M[1][1] = 1.0f;         M[1][2] = 0.0f;          M[1][3] = 0.0f;
    M[2][0] = 0.0f;         M[2][1] = 0.0f;         M[2][2] = 1.0f;          M[2][3] = 0.0f;
    M[3][0] = TranslateX;   M[3][1] = TranslateY;   M[3][2] = TranslateZ;    M[3][3] = 1.0f;
}

// Scale 행렬 변환 적용하기. 
// 이후에 Rotation 에서 Translation 까지. 
inline void AppendTransform(float matrix[4][4], const float transform[4][4])
{
    float temp[4][4];
    Multiplymatrix(temp, matrix, transform);
    std::memcpy(matrix, temp, sizeof(temp));
}

inline void AppendScale(float targetMatrix[4][4], float scaleX, float scaleY, float scaleZ)
{
    float scaleMatrix[4][4];

    ScaleMatrix(scaleMatrix, scaleX, scaleY, scaleZ);
    AppendTransform(targetMatrix, scaleMatrix);
}

// Z축 회전 (XY 평면 상 회전)
inline void AppendRotateAroundZAxis(float matrix[4][4], float radians)
{
    float temp[4][4];
    MakeXYPlaneRotationMatrix(temp, radians);
    AppendTransform(matrix, temp);
}

// X축 회전 (YZ 평면 상 회전)
inline void AppendRotateAroundXAxis(float matrix[4][4], float radians)
{
    float temp[4][4];
    MakeYZPlaneRotationMatrix(temp, radians);
    AppendTransform(matrix, temp);
}

// Y축 회전 (ZX 평면 상 회전)
inline void AppendRotateAroundYAxis(float matrix[4][4], float radians)
{
    float temp[4][4];
    MakeZXPlaneRotationMatrix(temp, radians);
    AppendTransform(matrix, temp);
}

inline void AppendTranslation(float matrix[4][4], float TranslateX, float TranslateY, float TranslateZ)
{
    float temp[4][4];
    TranslationMatrix(temp, TranslateX, TranslateY, TranslateZ);
    AppendTransform(matrix, temp);
}