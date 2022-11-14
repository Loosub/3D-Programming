#include "MuSoenMath.h"

int main() {
	/*mid1********************************************************/
	vec3 v(new float[3]{ 1, 1, 1 }); // v(1, 1, 1)

	mat3 Translate(new float[3][3]{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 3, 5, 1 }
		});

	mat3 Rotate(new float[3][3]{
		{ (float)cos(PI / 6), -(float)sin(PI / 6), 0}, // (PI/6)���� = (30)��
		{ (float)sin(PI / 6), (float)cos(PI / 6), 0},
		{ 0, 0, 1 }
		});

	mat3 Scale(new float[3][3]{
		{ 2, 0, 0 },
		{ 0, 2, 0 },
		{ 0, 0, 1 }
		});

	vec3 p(new float[3]{ 0, 0, 0 }); // p(0, 0, 0)

	p = v * Translate * Rotate * Scale; // ��ǥ v�� (3,5 �̵� | 30�� ȸ�� | 2�� Ȯ��)�� �� ��ǥ p�� ����

	cout << "x: " << p.v[0] << endl;
	cout << "y: " << p.v[1] << endl;
	cout << endl;

	/*mid2 1.�������*********************************************/

	mat3 Identity(new float[3][3]{ // 3*3��� Identity ����
		{ 6, 3, 1 },
		{ 4, 2, 6 },
		{ 1, 5, 2 }
		});

	cout << "������� �ʱ�ȭ ��: " << endl; // ������� �ʱ�ȭ �� ��� ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Identity.m[i][j];
		} cout << endl;
	} cout << endl;

	Identity.identity_matrix(); // ���� ��� �ʱ�ȭ �Լ� ����

	cout << "������ķ� �ʱ�ȭ ��: " << endl;  // ������� �ʱ�ȭ �� ��� ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Identity.m[i][j];
		} cout << endl;
	} cout << endl;

	/*mid2 2.��ġ���*********************************************/

	mat3 Transpose(new float[3][3]{ // 3*3��� Transpose ����
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
		});

	cout << "��ġ �� ���: " << endl; // ��ġ �� ��� ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Transpose.m[i][j];
		} cout << endl;
	} cout << endl;

	Transpose.Transpose(); // ��ġ �Լ� ����

	cout << "��ġ �� ���: " << endl; // ��ġ �� ��� ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Transpose.m[i][j];
		} cout << endl;
	} cout << endl;

	/*mid2 3.�����Լ�
	(multiply matrix, ��� ����/����)*/

	mat3 Operate(new float[3][3]{ // 3*3��� Operate ����
		{ 0, 0, 0 },
		{ 1, 1, 1 },
		{ 2, 2, 2 }
		});

	cout << "���� ��� ��: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Operate.m[i][j];
		} cout << endl;
	} cout << endl;

	Operate.multiply_matrix(new float[3][3]{
		{ 2, 2, 2 },
		{ 2, 2, 2 },
		{ 2, 2, 2 }
		});

	cout << "2��ŭ ������ ��: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Operate.m[i][j];
		} cout << endl;
	} cout << endl;

	Operate.plus_matrix(new float[3][3]{
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 1, 1, 1 }
		});

	cout << "1��ŭ ������ ��: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Operate.m[i][j];
		} cout << endl;
	} cout << endl;

	Operate.minus_matrix(new float[3][3]{
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 1, 1, 1 }
		});

	cout << "1��ŭ ������ ��: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Operate.m[i][j];
		} cout << endl;
	} cout << endl;

	/*(multiply transpos matrix)*/

	mat3 Operate_b(new float[3][3]{ // 3*3��� Operate ����
		{ 1, 2, 3 },
		{ 1, 2, 3 },
		{ 1, 2, 3 }
		});

	cout << "�� ��ġ ��: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Operate_b.m[i][j];
		} cout << endl;
	} cout << endl;

	Operate_b.multiply_transpose_matrix(new float[3][3]{
		{ 2, 2, 2 },
		{ 2, 2, 2 },
		{ 2, 2, 2 }
		});

	cout << "2��ŭ ���ϰ� ��ġ�� ��: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Operate_b.m[i][j];
		} cout << endl;
	} cout << endl;

	/*(multiply vector*/
	vec3 V1(new float[3]{ 1, 1, 1 }); // v(1, 1, 1)

	cout << "vector ���� ��� ��: " << endl;
	for (int i = 0; i < 3; i++) {
		cout << V1.v[i] << " ";
	} cout << '\n' << endl;

	V1.multiply_vector(2);

	cout << "vector 2��ŭ ���� ��: " << endl;
	for (int i = 0; i < 3; i++) {
		cout << V1.v[i] << " ";
	} cout << '\n' << endl;

	/*��� ����, ������*/
	constNum N1(2.0);
	cout << "���:" << N1.num << endl;

	N1.multiply_num(1.5);
	cout << "��� ���ϱ� ���: ��� * 1.5 = " << N1.num << endl;

	N1.divide_num(0.5);
	cout << "��� ������ ���: (��� * 1.5) / 0.5 = " << N1.num << endl;

}


