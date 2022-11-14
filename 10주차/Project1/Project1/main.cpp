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
		{ (float)cos(PI / 6), -(float)sin(PI / 6), 0}, // (PI/6)라디안 = (30)도
		{ (float)sin(PI / 6), (float)cos(PI / 6), 0},
		{ 0, 0, 1 }
		});

	mat3 Scale(new float[3][3]{
		{ 2, 0, 0 },
		{ 0, 2, 0 },
		{ 0, 0, 1 }
		});

	vec3 p(new float[3]{ 0, 0, 0 }); // p(0, 0, 0)

	p = v * Translate * Rotate * Scale; // 좌표 v를 (3,5 이동 | 30도 회전 | 2배 확대)한 후 좌표 p에 저장

	cout << "x: " << p.v[0] << endl;
	cout << "y: " << p.v[1] << endl;
	cout << endl;

	/*mid2 1.단위행렬*********************************************/

	mat3 Identity(new float[3][3]{ // 3*3행렬 Identity 생성
		{ 6, 3, 1 },
		{ 4, 2, 6 },
		{ 1, 5, 2 }
		});

	cout << "단위행렬 초기화 전: " << endl; // 단위행렬 초기화 전 행렬 출력
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Identity.m[i][j];
		} cout << endl;
	} cout << endl;

	Identity.identity_matrix(); // 단위 행렬 초기화 함수 실행

	cout << "단위행렬로 초기화 후: " << endl;  // 단위행렬 초기화 후 행렬 출력
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Identity.m[i][j];
		} cout << endl;
	} cout << endl;

	/*mid2 2.전치행렬*********************************************/

	mat3 Transpose(new float[3][3]{ // 3*3행렬 Transpose 생성
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
		});

	cout << "전치 전 행렬: " << endl; // 전치 전 행렬 출력
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Transpose.m[i][j];
		} cout << endl;
	} cout << endl;

	Transpose.Transpose(); // 전치 함수 실행

	cout << "전치 후 행렬: " << endl; // 전치 후 행렬 출력
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Transpose.m[i][j];
		} cout << endl;
	} cout << endl;

	/*mid2 3.연산함수
	(multiply matrix, 행렬 덧셈/뺄셈)*/

	mat3 Operate(new float[3][3]{ // 3*3행렬 Operate 생성
		{ 0, 0, 0 },
		{ 1, 1, 1 },
		{ 2, 2, 2 }
		});

	cout << "곱셈 계산 전: " << endl;
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

	cout << "2만큼 곱셈한 후: " << endl;
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

	cout << "1만큼 덧셈한 후: " << endl;
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

	cout << "1만큼 뺄셈한 후: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Operate.m[i][j];
		} cout << endl;
	} cout << endl;

	/*(multiply transpos matrix)*/

	mat3 Operate_b(new float[3][3]{ // 3*3행렬 Operate 생성
		{ 1, 2, 3 },
		{ 1, 2, 3 },
		{ 1, 2, 3 }
		});

	cout << "곱 전치 전: " << endl;
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

	cout << "2만큼 곱하고 전치한 후: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Operate_b.m[i][j];
		} cout << endl;
	} cout << endl;

	/*(multiply vector*/
	vec3 V1(new float[3]{ 1, 1, 1 }); // v(1, 1, 1)

	cout << "vector 곱셈 계산 전: " << endl;
	for (int i = 0; i < 3; i++) {
		cout << V1.v[i] << " ";
	} cout << '\n' << endl;

	V1.multiply_vector(2);

	cout << "vector 2만큼 곱한 후: " << endl;
	for (int i = 0; i < 3; i++) {
		cout << V1.v[i] << " ";
	} cout << '\n' << endl;

	/*상수 곱셈, 나눗셈*/
	constNum N1(2.0);
	cout << "상수:" << N1.num << endl;

	N1.multiply_num(1.5);
	cout << "상수 곱하기 계산: 상수 * 1.5 = " << N1.num << endl;

	N1.divide_num(0.5);
	cout << "상수 나누기 계산: (상수 * 1.5) / 0.5 = " << N1.num << endl;

}


