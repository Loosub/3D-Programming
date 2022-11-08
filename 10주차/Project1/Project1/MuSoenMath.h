#include <iostream>
#include <math.h>

#define PI 3.14159
using namespace std;

class mat3 {
public:
	float m[3][3]; // 3*3 행렬
	mat3(float mat3[3][3]); // 생성자
	mat3 operator*(mat3& ref); // 오버로딩 함수
};

mat3::mat3(float mat3[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->m[i][j] = mat3[i][j]; // mat3 클래스의 m에 클래스 생성시 입력한 행렬 저장
		}
	}
}

mat3 mat3::operator*(mat3& ref) {
	mat3 result(new float[3][3]{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++)
				result.m[i][j] += (m[k][j] * ref.m[i][k]); // 3*3 행렬 곱 연산
		}
	}

	return result;
}

class vec3
{
public:
	float v[3]; // { x, y, z }
	vec3(float vec3[3]); // 생성자
	vec3 operator*(const mat3& ref); // 오버로딩 함수
};

vec3::vec3(float vec3[3]) { 
	for (int i = 0; i < 3; i++) {
		this->v[i] = vec3[i]; // vec3 클래스의 v에 클래스 생성시 입력한 좌표 저장
	}
}

vec3 vec3::operator*(const mat3& ref)
{
	vec3 result(new float[3]{ 0, 0, 0 });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.v[i] += (v[j] * ref.m[j][i]); // (x, y, z) * (3*3) 행렬 연산
		}
	}

	return result;
}