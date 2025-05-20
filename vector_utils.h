#pragma once
#include <cmath>

struct Vector3 {
    float x, y, z;

    // 1) 값을 안 주고 만들면, 모두 0 으로 채우기
    Vector3() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    // 2) 값을 주고 만들면, 그 값으로 초기화
    Vector3(float a, float b, float c) {
        x = a;
        y = b;
        z = c;
    }

    // 길이(크기) 반환
    float length() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    // 길이 제곱 반환 (루트 연산 없이 빠르게 비교할 때 사용)
    float squaredLength() const {
        return x*x + y*y + z*z;
    }

    // ============================================
    // 방식 1: 멤버 함수로 덧셈 구현
    // 사용: Vector3 c = a.add(b);
    Vector3 add(const Vector3& other) const {
        return Vector3(
            x + other.x,
            y + other.y,
            z + other.z
        );
    }

    // 방식 3-1: 멤버 함수로 operator+ 오버로딩
    // 사용: Vector3 c = a + b;
    Vector3 operator+(const Vector3& other) const {
        return Vector3(
            x + other.x,
            y + other.y,
            z + other.z
        );
    }

    // 방식 3-2: 자유 함수(friend)로 operator+ 오버로딩
    // 사용: Vector3 c = a + b;  (위 멤버 버전 대신 이걸 쓰고 싶다면 주석 해제)
    /*
    friend Vector3 operator+(const Vector3& a, const Vector3& b) {
        return Vector3(
            a.x + b.x,
            a.y + b.y,
            a.z + b.z
        );
    }
    */

/* 사용 예시:
    
    Vector3 a(1,2,3), b(4,5,6);

    // 방식1: 멤버 함수
    Vector3 c1 = a.add(b);        

    // 방식2: 자유 함수
    Vector3 c2 = vectorAdd(a, b);

    // 방식3: operator+ (멤버 혹은 friend)
    Vector3 c3 = a + b;           
*/

    bool normalize() {
        float len = length();
        if (len <= 0.0f) return false;
        x /= len; y /= len; z /= len;
        return true;
    }

    Vector3 normalized() const {
        Vector3 v(*this);
        v.normalize();
        return v;
    }
};

Todo
/* 
Vector3 GetSafeNormal() const
{

}

Vector3 InnerProduct() const {}

Vector3 DotProduct() const {}

Vector3 CrossProduct() const {}
 */