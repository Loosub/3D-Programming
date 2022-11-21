#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>
#include "MuSoenMath.h"

#pragma comment(lib, "OpenGL32")

using namespace std;

chrono::system_clock::time_point startRenderTimePoint;
chrono::duration<double> renderDuration;

GLFWwindow* window;
bool isFirstFrame = true;

struct Vertex
{
    vec3 pos;
    float r, g, b, a;
};

struct Transform
{
    mat3 translate;
    mat3 scale;
    mat3 rotation;
};

Vertex star[5];             // static mesh
Vertex transformedStar[5];  //화면에 그릴 오망성
Vertex circle[360];             // static mesh 
Vertex transformedCircle[360];  // 화면에 그려질 원

Transform transform;  //world 행렬이 될 transform

//전역변수
float ta = 0;
float ra = 0;
float sa = 1;
float ssa = 0.01;

void Init();
void Update();
void Release();

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void);

void Init()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(720, 720, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);

    startRenderTimePoint = chrono::system_clock::now();

    // object생성부
    // Star(오망성) 생성
    int i = 0;
    for (float theta = 0; theta < 360; theta += 72)
    {
        star[i].pos.v[0] = -sin(theta * PI / 180) * 0.5f;
        star[i].pos.v[1] = cos(theta * PI / 180) * 0.5f;
        star[i].pos.v[2] = 1.0f;

        star[i].r = 0.3f;
        star[i].g = 0.0f;
        star[i].b = theta / 360.0f;
        star[i].a = 0.7f;

        transformedStar[i] = star[i];

        i++;
    }

    // 원 생성
    for (int theta = 0; theta < 360; theta++)
    {
        circle[theta].pos.v[0] = -sin(theta * PI / 180) * 0.5;
        circle[theta].pos.v[1] = cos(theta * PI / 180) * 0.5;
        circle[theta].pos.v[2] = 1.0f;

        circle[theta].r = 0.3f;
        circle[theta].g = 0.0f;
        circle[theta].b = theta / 360.0f;
        circle[theta].a = 0.7f;

        transformedCircle[theta] = circle[theta];
    }

    transform.translate = mat3(new float[3][3]{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
        });
    transform.rotation = mat3(new float[3][3]{
        cos(0.0f), -sin(0.0f), 0,
        sin(0.0f), cos(0.0f), 0,
        0, 0, 1
        });
    transform.scale = mat3(new float[3][3]{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
        });
}

void Release()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Update()
{
    while (!glfwWindowShouldClose(window))
    {
        //Update로직
        //<문제>//////////////////////////////////////////////////////////////////////////////////

        //1. translate 를 프레임당 오른쪽으로 0.001씩 누적시켜서 물체를 이동해보세요.
        //2. Rotation 을 프레임당 1도씩 누적시켜서 물체를 회전시켜보세요.
        //3. Scale은 초당 0.01씩 최대 1.3배까지 늘어났다가 0.7배까지 줄어들도록 만드시오 (반복)
        //   (1.3배 이상이 되면 줄어들고 0.7배 이하가 되면 다시 늘어나게 만드시오)

        ta += 0.001f;

        transform.translate = mat3(new float[3][3]{
            1, 0, 0,
            0, 1, 0,
            ta, 0, 1
            });

        ra += 1.0f;

        transform.rotation = mat3(new float[3][3]{
            (float)cos(ra * PI / 180), -(float)sin(ra * PI / 180), 0,
            (float)sin(ra * PI / 180), (float)cos(ra * PI / 180), 0,
            0, 0, 1
            });

        sa = sa + ssa;

        if (sa >= 1.3)
        {
            ssa = -0.01f;
        }
        else if (sa <= 0.7)
        {
            ssa = +0.01f;
        }

        transform.scale = mat3(new float[3][3]{
            sa, 0, 0,
            0, sa, 0,
            0, 0, 1
            });

        ////////////////////////////////////////////////////////////////////////////////////////////

        for (int i = 0; i < 360; i++)
        {
            transformedCircle[i].pos = circle[i].pos * transform.rotation * transform.scale * transform.translate;
        }

        for (int i = 0; i < 5; i++)
        {
            transformedStar[i].pos = star[i].pos * transform.rotation * transform.scale * transform.translate;
        }

        //색 초기화
        glClearColor(.0f, 0.0f, 0.0f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        //선두께
        glLineWidth(7.0f);
        //오망성 그리기
        glBegin(GL_LINE_STRIP);

        int a = 0;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.v[0], transformedStar[a].pos.v[1], 0.0f);
        a = 3;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.v[0], transformedStar[a].pos.v[1], 0.0f);
        a = 1;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.v[0], transformedStar[a].pos.v[1], 0.0f);
        a = 4;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.v[0], transformedStar[a].pos.v[1], 0.0f);
        a = 2;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.v[0], transformedStar[a].pos.v[1], 0.0f);

        a = 0;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.v[0], transformedStar[a].pos.v[1], 0.0f);
        glEnd();

        //원그리기
        glBegin(GL_LINE_STRIP);
        for (int theta = 0; theta < 360; theta++)
        {
            glColor4f(transformedCircle[theta].r, transformedCircle[theta].g, transformedCircle[theta].b, transformedCircle[theta].a);
            glVertex3f(transformedCircle[theta].pos.v[0], transformedCircle[theta].pos.v[1], 0.0f);
        }
        glEnd();

        //화면 스왑
        glfwSwapBuffers(window);
        glfwPollEvents();

        //렌더시간 측정
        renderDuration = chrono::system_clock::now() - startRenderTimePoint;
        startRenderTimePoint = chrono::system_clock::now();

        float fps = 1.0 / renderDuration.count();
        if (isFirstFrame == true)
        {
            isFirstFrame = false;
            continue;
        }
        if (renderDuration.count() < (1.0f / 60.0f))
            this_thread::sleep_for(chrono::milliseconds((int)(((1.0f / 60.0f) - renderDuration.count()) * 1000)));
        string fps_s = "FPS : " + to_string(fps);
        cout << fps_s << endl;
    }
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
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


	/*mid3********************************************************/

	Init();
	Update();
	Release();

	exit(EXIT_SUCCESS);
}