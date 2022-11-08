#include <iostream>
#include <math.h>

#define PI 3.14159
using namespace std;

class mat3 {
public:
	float m[3][3]; // 3*3 ���
	mat3(float mat3[3][3]); // ������
	mat3 operator*(mat3& ref); // �����ε� �Լ�
};

mat3::mat3(float mat3[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->m[i][j] = mat3[i][j]; // mat3 Ŭ������ m�� Ŭ���� ������ �Է��� ��� ����
		}
	}
}

mat3 mat3::operator*(mat3& ref) {
	mat3 result(new float[3][3]{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++)
				result.m[i][j] += (m[k][j] * ref.m[i][k]); // 3*3 ��� �� ����
		}
	}

	return result;
}

class vec3
{
public:
	float v[3]; // { x, y, z }
	vec3(float vec3[3]); // ������
	vec3 operator*(const mat3& ref); // �����ε� �Լ�
};

vec3::vec3(float vec3[3]) { 
	for (int i = 0; i < 3; i++) {
		this->v[i] = vec3[i]; // vec3 Ŭ������ v�� Ŭ���� ������ �Է��� ��ǥ ����
	}
}

vec3 vec3::operator*(const mat3& ref)
{
	vec3 result(new float[3]{ 0, 0, 0 });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.v[i] += (v[j] * ref.m[j][i]); // (x, y, z) * (3*3) ��� ����
		}
	}

	return result;
}