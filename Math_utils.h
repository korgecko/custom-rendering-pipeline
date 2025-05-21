#pragma once    
#include <cmath>
#include <concepts>
#include <numbers>
#include <random>
#include <type_traits>

#include "PlatformType.h"

#define PI                   (3.1415926535897932f)
#define SMALL_NUMBER         (1.e-8f)
#define KINDA_SMALL_NUMBER   (1.e-4f)
#define INV_PI				 (0.31830988618f)
#define HALF_PI				 (1.57079632679f)
#define TWO_PI				 (6.28318530717f)
#define PI_SQUARED			 (9.86960440108f)

#define PI_DOUBLE            (3.141592653589793238462643383279502884197169399)
    
struct FMath {
    // nodiscard 로 함수의 반환값은 반드시 사용되어야 한다. 사용하지 않으면 경고하거나 오류를 발생시켜라
    [[nodiscard]] static FORCEINLINE float InvSqrt(float A) {
         return 1.0f / sqrtf(A); 
        }
    [[nodiscard]] static FORCEINLINE double InvSqrt(double A) {
         return 1.0 / sqrt(A); 
        }
};