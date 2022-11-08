#include "MuSoenMath.h"

void main() {
	vec3 v(new float[3]{ 1, 1, 1 }); // v(1, 1, 1)

	mat3 Translate(new float[3][3]{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 3, 5, 1 }
	});

	mat3 Rotate(new float[3][3]{
		{ (float)cos(PI/6), -(float)sin(PI/6), 0}, // (PI/6)���� = (30)��
		{ (float)sin(PI/6), (float)cos(PI/6), 0},
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
}

