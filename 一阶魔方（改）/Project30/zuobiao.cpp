#include"zuobiao.h"
#include <math.h>
#include"data.h"

#define WIDTH 1000
#define HEIGHT 600
#define PI 3.14159265
#define SIDE ((WIDTH < HEIGHT) ? WIDTH : HEIGHT) / 8
#define GAMEPAD SIDE / 2
#define ZERO 0.1
#define PIECE 180

// 向量点乘
double vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 向量长度
double vec2_length(Vec2 vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

double vec3_length(Vec3 vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
// 向量缩放
Vec2 vec2_scale(Vec2 a, double num) {
    Vec2 result;
    result.x = a.x * num;
    result.y = a.y * num;
    return result;
}

Vec3 vec3_scale(Vec3 a, double num) {
    Vec3 result;
    result.x = a.x * num;
    result.y = a.y * num;
    result.z = a.z;
    return result;
}
// 向量投影
Vec3 vec3_projection(Vec3 A, Vec3 B) {
    double num = vec3_dot(A, B) / (vec3_length(B) * vec3_length(B));
    Vec3 result = vec3_scale(B, num);
    return result;
}
// 透视变换矩阵
void rotation_x(double f, double z, double R[3][3]) {
    R[0][0] = f / z; R[0][1] = 0; R[0][2] = 0;
    R[1][0] = 0; R[1][1] = f / z; R[1][2] = 0;
    R[2][0] = 0; R[2][1] = 0; R[2][2] = 1 / z;
}

// 焦距f
void c_to_p(Vec3* Vertex, int numVertices, double f) {
    double R[3][3];

    for (int i = 0; i < numVertices; i++) {
        double point[3] = { Vertex[i].x, Vertex[i].y, Vertex[i].z };
        double r[3] = { 0 };
        rotation_x(f, Vertex[i].z, R);

        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                r[j] += R[j][k] * point[k];
            }
        }

        Vertex[i].x = r[0];
        Vertex[i].y = r[1];
        Vertex[i].z = r[2];
    }
}

// 将三维的点的值转换为在对应 xoy 面上的投影的坐标
Vec2 transform3DTo2D(Vec3 vertex, Vec3 AuxiliaryVector[2], double scale, double focalLength) {
    Vec3 tempVertex = vertex;
    c_to_p(&tempVertex, 1, focalLength);

    Vec3 tempX = vec3_projection(tempVertex, AuxiliaryVector[0]);
    Vec3 tempY = vec3_projection(tempVertex, AuxiliaryVector[1]);
    Vec2 result;
    result.x = vec3_length(tempX);
    result.y = vec3_length(tempY);
    if (vec3_dot(tempX, AuxiliaryVector[0]) < 0) result.x *= -1;
    if (vec3_dot(tempY, AuxiliaryVector[1]) < 0) result.y *= -1;

    // 调整坐标比例，避免图形过小或超出窗口
    result.x *= scale;
    result.y *= scale;

    // 坐标范围检查
    result.x += WIDTH / 2.0;
    result.y += HEIGHT / 2.0;
    if (result.x < 0) result.x = 0;
    if (result.x >= WIDTH) result.x = WIDTH - 1;
    if (result.y < 0) result.y = 0;
    if (result.y >= HEIGHT) result.y = HEIGHT - 1;

    return result;
}
// 矩阵乘法函数
void matrixMultiply(double A[3][3], double B[3][3], double C[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// 绕x轴旋转的矩阵
void rotation_x_axis(double theta, double R[3][3]) {
    R[0][0] = 1; R[0][1] = 0; R[0][2] = 0;
    R[1][0] = 0; R[1][1] = cos(theta); R[1][2] = sin(theta);
    R[2][0] = 0; R[2][1] = -sin(theta); R[2][2] = cos(theta);
}

// 绕y轴旋转的矩阵
void rotation_y_axis(double theta, double R[3][3]) {
    R[0][0] = cos(theta); R[0][1] = 0; R[0][2] = -sin(theta);
    R[1][0] = 0; R[1][1] = 1; R[1][2] = 0;
    R[2][0] = sin(theta); R[2][1] = 0; R[2][2] = cos(theta);
}

// 绕z轴旋转的矩阵
void rotation_z_axis(double theta, double R[3][3]) {
    R[0][0] = cos(theta); R[0][1] = sin(theta); R[0][2] = 0;
    R[1][0] = -sin(theta); R[1][1] = cos(theta); R[1][2] = 0;
    R[2][0] = 0; R[2][1] = 0; R[2][2] = 1;
}

// 根据鼠标位移计算旋转和平移参数
void calculateTransformationParams(double deltaX, double deltaY, double* zhuan_x, double* zhuan_y, double* zhuan_z, double* yi_x, double* yi_y, double* yi_z) {
    // 根据鼠标位移计算旋转角度
    *zhuan_x = deltaY * 0.01;
    *zhuan_y = deltaX * 0.01;
    *zhuan_z = 0;
    *yi_x = 0;
    *yi_y = 0;
    *yi_z = 0;
}

// 坐标转换函数
void w_to_c(Vec3* Vertex, int numVertices, double zhuan_x, double zhuan_y, double zhuan_z, double yi_x, double yi_y, double yi_z) {
    double Rx[3][3], Ry[3][3], Rz[3][3];
    double R1[3][3], R[3][3];

    rotation_x_axis(zhuan_x, Rx);
    rotation_y_axis(zhuan_y, Ry);
    rotation_z_axis(zhuan_z, Rz);

    matrixMultiply(Rz, Ry, R1);
    matrixMultiply(R1, Rx, R);

    for (int i = 0; i < numVertices; i++) {
        double point[3] = { Vertex[i].x, Vertex[i].y, Vertex[i].z };
        double r[3] = { 0 };

        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                r[j] += R[j][k] * point[k];
            }
        }

        Vertex[i].x = yi_x + r[0];
        Vertex[i].y = yi_y + r[1];
        Vertex[i].z = yi_z + r[2];
    }
}
// 根据投影面 x，y 轴正方向向量求出投影面法向量
Vec3 getVerticalAxis(Vec3 AuxiliaryVector[2]) {
    double x0 = AuxiliaryVector[0].x;
    double y0 = AuxiliaryVector[0].y;
    double z0 = AuxiliaryVector[0].z;
    double x1 = AuxiliaryVector[1].x;
    double y1 = AuxiliaryVector[1].y;
    double z1 = AuxiliaryVector[1].z;
    Vec3 result = {
        y0 * z1 - y1 * z0,
        x1 * z0 - x0 * z1,
        x0 * y1 - x1 * y0
    };
    return result;
}

// 画表面
void drawSurface(Vec3 Surface[4], Vec3 AuxiliaryVector[2], Vec2 pericenter_Sur, COLORREF color, double scale, double focalLength) {
    setlinestyle(PS_SOLID, 2);
    Vec2 points[4];
    for (int i = 0; i < 4; i++) {
        points[i] = transform3DTo2D(Surface[i], AuxiliaryVector, scale, focalLength);
    }

    // 绘制面的边框
    setlinecolor(WHITE);
    for (int i = 0; i < 4; i++) {
        line(points[i].x, points[i].y, points[(i + 1) % 4].x, points[(i + 1) % 4].y);
    }

    // 计算面的中心点
    Vec2 center = { 0, 0 };
    for (int i = 0; i < 4; i++) {
        center.x += points[i].x;
        center.y += points[i].y;
    }
    center.x /= 4;
    center.y /= 4;

    // 填充颜色
    setfillcolor(color);
    floodfill(center.x, center.y, WHITE);
}

// 画正方体
void drawCube(Vec3 Vertex[8], Vec3 AuxiliaryVector[2], Vec2 pericenter, COLORREF ColorArray[6], double scale, double focalLength) {
    setbkcolor(RGB(0, 0, 0));  // 设置背景颜色为黑色
    cleardevice();     // 清屏

    Vec3 Surface[6][4] = {
        {Vertex[1], Vertex[2], Vertex[6], Vertex[5]}, // Right
        {Vertex[0], Vertex[3], Vertex[7], Vertex[4]}, // Left
        {Vertex[3], Vertex[2], Vertex[6], Vertex[7]}, // Back
        {Vertex[0], Vertex[1], Vertex[5], Vertex[4]}, // Front
        {Vertex[4], Vertex[5], Vertex[6], Vertex[7]}, // Up
        {Vertex[0], Vertex[1], Vertex[2], Vertex[3]}  // Down
    };
    Vec3 Vector_Z = getVerticalAxis(AuxiliaryVector);
    Vector_Z = vec3_scale(Vector_Z, (1.0 / vec3_length(Vector_Z)));
    //Vector_Z = vec3_scale(Vector_Z, (1.0));
    if (Vector_Z.z > ZERO) drawSurface(Surface[4], AuxiliaryVector, pericenter, ColorArray[Up], scale, focalLength);
    if (Vector_Z.z < -ZERO) drawSurface(Surface[5], AuxiliaryVector, pericenter, ColorArray[Down], scale, focalLength);
    if (Vector_Z.y > ZERO) drawSurface(Surface[2], AuxiliaryVector, pericenter, ColorArray[Back], scale, focalLength);
    if (Vector_Z.y < -ZERO) drawSurface(Surface[3], AuxiliaryVector, pericenter, ColorArray[Front], scale, focalLength);
    if (Vector_Z.x > ZERO) drawSurface(Surface[0], AuxiliaryVector, pericenter, ColorArray[Right], scale, focalLength);
    if (Vector_Z.x < -ZERO) drawSurface(Surface[1], AuxiliaryVector, pericenter, ColorArray[Left], scale, focalLength);
}