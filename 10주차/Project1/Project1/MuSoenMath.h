#include <iostream>
#include <math.h>

#define PI 3.1415926
using namespace std;

class mat3 {
public:
	float m[3][3]; // 3*3 ���
	//float v[3];
	mat3(float mat3[3][3]); // ������

	mat3(); // ������ 

	mat3 operator*(const mat3& ref); // �� ���� �Լ�

	mat3 identity_matrix(); // ������� �ʱ�ȭ �Լ�
	mat3 Transpose(); // ��ġ��� �Լ�

	mat3 multiply_matrix(const mat3& ref); // mat3 ���� ���� �Լ�
	mat3 plus_matrix(const mat3& ref); // mat3 ���� ���� �Լ�
	mat3 minus_matrix(const mat3& ref); // mat3 ���� ���� �Լ�

	mat3 multiply_transpose_matrix(const mat3& ref); // �� ��ġ ���� �Լ�
};

mat3::mat3() {}

mat3::mat3(float mat3[3][3]) { // mat3 ������
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->m[i][j] = mat3[i][j]; // mat3 Ŭ������ m�� Ŭ���� ������ �Է��� ��� ����
		}
	}
}

mat3 mat3::operator*(const mat3& ref) { // mat3 �� ���� �Լ�
	mat3 result(new float[3][3]{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++)
				result.m[i][j] += ref.m[k][j] * m[i][k]; // 3*3 ��� �� ����
		}
	}

	return result;
}

mat3 operator*(const mat3& m1, const mat3& m2) { // mat3 �� ���� �Լ�
	mat3 result(new float[3][3]{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++)
				result.m[i][j] += m1.m[i][k] * m2.m[k][j]; // 3*3 ��� �� ����
		}
	}

	return result;
}

mat3 mat3::identity_matrix() { //������� �ʱ�ȭ �Լ�
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) this->m[i][j] = 1; // i�� j�� ���� ��� 1 �Է�
			else this->m[i][j] = 0; // i�� j�� �ٸ� ��� 1 �Է�
		}
	}

	return *this;
}

mat3 mat3::Transpose() { //��ġ��� �Լ�
	mat3 result(new float[3][3]{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });

	for (int i = 0; i < 3; i++) // ��� ����
		for (int j = 0; j < 3; j++)
			result.m[i][j] = this->m[i][j];

	for (int i = 0; i < 3; i++) // ��ġ
		for (int j = 0; j < 3; j++)
			this->m[j][i] = result.m[i][j];

	return *this;
}

mat3 mat3::multiply_matrix(const mat3& ref) { // mat3 ���� ���� �Լ�
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m[i][j] *= ref.m[i][j]; // 3*3 ��� ���� ����
		}
	}

	return *this;
}

mat3 mat3::plus_matrix(const mat3& ref) { // mat3 ���� ���� �Լ�
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m[i][j] += ref.m[i][j]; // 3*3 ��� ���� ����
		}
	}

	return *this;
}

mat3 mat3::minus_matrix(const mat3& ref) { // mat3 ���� ���� �Լ�
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m[i][j] -= ref.m[i][j]; // 3*3 ��� ���� ����
		}
	}

	return *this;
}

mat3 mat3::multiply_transpose_matrix(const mat3& ref) { // mat3 �� ��ġ ���� �Լ�
	mat3 temporary(new float[3][3]); // ���� �ӽ÷� ������ ���

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m[i][j] *= ref.m[i][j]; // 3*3 ��� ���� ����
		}
	}

	for (int i = 0; i < 3; i++) // ��� ����
		for (int j = 0; j < 3; j++)
			temporary.m[i][j] = m[i][j];

	for (int i = 0; i < 3; i++) // ��ġ
		for (int j = 0; j < 3; j++)
			m[j][i] = temporary.m[i][j];

	return *this;
}

class vec3
{
public:
	float v[3]; // { x, y, z }
	vec3(float vec3[3]); // ������
	vec3();

	vec3 operator*(const mat3& ref); // ���� �� ���� �Լ�
	vec3 operator*(const vec3& ref);

	vec3 multiply_vector(float ref); // ���� ���� ���� �Լ�

};

vec3::vec3() {}

vec3::vec3(float vec3[3]) {
	for (int i = 0; i < 3; i++) {
		this->v[i] = vec3[i]; // vec3 Ŭ������ v�� Ŭ���� ������ �Է��� ��ǥ ����
	}
}

vec3 vec3::operator*(const mat3& ref) {
	vec3 result(new float[3]{ 0, 0, 0 });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.v[i] += (v[j] * ref.m[j][i]); // (x, y, z) * (3*3) ��� ����
		}
	}

	return result;
}

// vec3 * vec3 ������
vec3 vec3::operator*(const vec3& ref) {
	vec3 result(new float[3]{ 0, 0, 0 });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.v[i] += (v[j] * ref.v[j]);
		}
	}

	return result;
}

// mat3 * vec3 ������
vec3 operator*(const mat3& m, const vec3& v)
{
	vec3 result(new float[3]{ 0, 0, 0 });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.v[i] += (m.m[j][i] * v.v[j]);
		}
	}

	//result.v[0] = m.m[0][0] * v.v[0] + m.m[1][0] * v.v[1] + m.m[2][0] * v.v[2];
	//result.v[1] = m.m[0][1] * v.v[0] + m.m[1][1] * v.v[1] + m.m[2][1] * v.v[2];
	//result.v[2] = m.m[0][2] * v.v[0] + m.m[1][2] * v.v[1] + m.m[2][2] * v.v[2];

	return result;
}


vec3 vec3::multiply_vector(float ref) { // (x, y, z) * (float) ����
	for (int i = 0; i < 3; i++)
		v[i] *= ref;

	return *this;
}

class constNum {
public:
	float num;
	constNum(float num); // ������
	constNum multiply_num(float n); // ���� �Լ�
	constNum divide_num(float n); // ������ �Լ�
};

constNum::constNum(float num) {
	this->num = num;
}

constNum constNum::multiply_num(float n) {
	num *= n;

	return *this;
}

constNum constNum::divide_num(float n) {
	num /= n;

	return *this;
}