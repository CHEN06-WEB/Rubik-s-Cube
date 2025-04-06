#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "zuobiao.h"
#include "caozuo.h"
#include "xuanran.h"


#define WIDTH 1000
#define HEIGHT 600
#define PI 3.14159265
#define SIDE ((WIDTH < HEIGHT) ? WIDTH : HEIGHT) / 8
#define GAMEPAD SIDE / 2
#define ZERO 0.1
#define PIECE 180

//// 定义六个面
//typedef enum {
//    Up, Down, Left, Right, Front, Back
//} Plane;
//
// 六个面的颜色
COLORREF SurfaceColor[6] = {
    RGB(255, 0, 0),    // Up
    RGB(255, 255, 0),  // Down
    RGB(0, 0, 255),    // Left
    RGB(0, 255, 0),    // Right
    RGB(165, 42, 42),  // Front
    RGB(255, 0, 255)   // Back
};

//// 二维向量
//typedef struct {
//    double x, y;
//} Vec2;
//
//// 三维向量
//typedef struct {
//    double x, y, z;
//} Vec3;



//// 向量缩放
//Vec2 vec2_scale(Vec2 a, double num) {
//    Vec2 result;
//    result.x = a.x * num;
//    result.y = a.y * num;
//    return result;
//}
//
//Vec3 vec3_scale(Vec3 a, double num) {
//    Vec3 result;
//    result.x = a.x * num;
//    result.y = a.y * num;
//    result.z = a.z * num;
//    return result;
//}

//// 向量点乘
//double vec3_dot(Vec3 a, Vec3 b) {
//    return a.x * b.x + a.y * b.y + a.z * b.z;
//}
//
//// 向量长度
//double vec2_length(Vec2 vec) {
//    return sqrt(vec.x * vec.x + vec.y * vec.y);
//}
//
//double vec3_length(Vec3 vec) {
//    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
//}

//// 向量投影
//Vec3 vec3_projection(Vec3 A, Vec3 B) {
//    double num = vec3_dot(A, B) / (vec3_length(B) * vec3_length(B));
//    Vec3 result = vec3_scale(B, num);
//    return result;
//}

//// 根据投影面 x，y 轴正方向向量求出投影面法向量
//Vec3 getVerticalAxis(Vec3 AuxiliaryVector[2]) {
//    double x0 = AuxiliaryVector[0].x;
//    double y0 = AuxiliaryVector[0].y;
//    double z0 = AuxiliaryVector[0].z;
//    double x1 = AuxiliaryVector[1].x;
//    double y1 = AuxiliaryVector[1].y;
//    double z1 = AuxiliaryVector[1].z;
//    Vec3 result = {
//        y0 * z1 - y1 * z0,
//        x1 * z0 - x0 * z1,
//        x0 * y1 - x1 * y0
//    };
//    return result;
//}

//// 透视变换矩阵
//void rotation_x(double f, double z, double R[3][3]) {
//    R[0][0] = f / z; R[0][1] = 0; R[0][2] = 0;
//    R[1][0] = 0; R[1][1] = f / z; R[1][2] = 0;
//    R[2][0] = 0; R[2][1] = 0; R[2][2] = 1 / z;
//}
//
//// 焦距f
//void c_to_p(Vec3* Vertex, int numVertices, double f) {
//    double R[3][3];
//
//    for (int i = 0; i < numVertices; i++) {
//        double point[3] = { Vertex[i].x, Vertex[i].y, Vertex[i].z };
//        double r[3] = { 0 };
//        rotation_x(f, Vertex[i].z, R);
//
//        for (int j = 0; j < 3; j++) {
//            for (int k = 0; k < 3; k++) {
//                r[j] += R[j][k] * point[k];
//            }
//        }
//
//        Vertex[i].x = r[0];
//        Vertex[i].y = r[1];
//        Vertex[i].z = r[2];
//    }
//}
//
//// 将三维的点的值转换为在对应 xoy 面上的投影的坐标
//Vec2 transform3DTo2D(Vec3 vertex, Vec3 AuxiliaryVector[2], double scale, double focalLength) {
//    Vec3 tempVertex = vertex;
//    c_to_p(&tempVertex, 1, focalLength);
//
//    Vec3 tempX = vec3_projection(tempVertex, AuxiliaryVector[0]);
//    Vec3 tempY = vec3_projection(tempVertex, AuxiliaryVector[1]);
//    Vec2 result;
//    result.x = vec3_length(tempX);
//    result.y = vec3_length(tempY);
//    if (vec3_dot(tempX, AuxiliaryVector[0]) < 0) result.x *= -1;
//    if (vec3_dot(tempY, AuxiliaryVector[1]) < 0) result.y *= -1;
//
//    // 调整坐标比例，避免图形过小或超出窗口
//    result.x *= scale;
//    result.y *= scale;
//
//    // 坐标范围检查
//    result.x += WIDTH / 2.0;
//    result.y += HEIGHT / 2.0;
//    if (result.x < 0) result.x = 0;
//    if (result.x >= WIDTH) result.x = WIDTH - 1;
//    if (result.y < 0) result.y = 0;
//    if (result.y >= HEIGHT) result.y = HEIGHT - 1;
//
//    return result;
//}

//// 画表面
//void drawSurface(Vec3 Surface[4], Vec3 AuxiliaryVector[2], Vec2 pericenter_Sur, COLORREF color, double scale, double focalLength) {
//    setlinestyle(PS_SOLID, 2);
//    Vec2 points[4];
//    for (int i = 0; i < 4; i++) {
//        points[i] = transform3DTo2D(Surface[i], AuxiliaryVector, scale, focalLength);
//    }
//
//    // 绘制面的边框
//    setlinecolor(WHITE);
//    for (int i = 0; i < 4; i++) {
//        line(points[i].x, points[i].y, points[(i + 1) % 4].x, points[(i + 1) % 4].y);
//    }
//
//    // 计算面的中心点
//    Vec2 center = { 0, 0 };
//    for (int i = 0; i < 4; i++) {
//        center.x += points[i].x;
//        center.y += points[i].y;
//    }
//    center.x /= 4;
//    center.y /= 4;
//
//    // 填充颜色
//    setfillcolor(color);
//    floodfill(center.x, center.y, WHITE);
//}
//
//// 画正方体
//void drawCube(Vec3 Vertex[8], Vec3 AuxiliaryVector[2], Vec2 pericenter, COLORREF ColorArray[6], double scale, double focalLength) {
//    setbkcolor(RGB(0, 0, 0));  // 设置背景颜色为黑色
//    cleardevice();     // 清屏
//
//    Vec3 Surface[6][4] = {
//        {Vertex[1], Vertex[2], Vertex[6], Vertex[5]}, // Right
//        {Vertex[0], Vertex[3], Vertex[7], Vertex[4]}, // Left
//        {Vertex[3], Vertex[2], Vertex[6], Vertex[7]}, // Back
//        {Vertex[0], Vertex[1], Vertex[5], Vertex[4]}, // Front
//        {Vertex[4], Vertex[5], Vertex[6], Vertex[7]}, // Up
//        {Vertex[0], Vertex[1], Vertex[2], Vertex[3]}  // Down
//    };
//    Vec3 Vector_Z = getVerticalAxis(AuxiliaryVector);
//    Vector_Z = vec3_scale(Vector_Z , (1.0 / vec3_length(Vector_Z)));
//    //Vector_Z = vec3_scale(Vector_Z, (1.0));
//    if (Vector_Z.z > ZERO) drawSurface(Surface[4], AuxiliaryVector, pericenter, ColorArray[Up], scale, focalLength);
//    if (Vector_Z.z < -ZERO) drawSurface(Surface[5], AuxiliaryVector, pericenter, ColorArray[Down], scale, focalLength);
//    if (Vector_Z.y > ZERO) drawSurface(Surface[2], AuxiliaryVector, pericenter, ColorArray[Back], scale, focalLength);
//    if (Vector_Z.y < -ZERO) drawSurface(Surface[3], AuxiliaryVector, pericenter, ColorArray[Front], scale, focalLength);
//    if (Vector_Z.x > ZERO) drawSurface(Surface[0], AuxiliaryVector, pericenter, ColorArray[Right], scale, focalLength);
//    if (Vector_Z.x < -ZERO) drawSurface(Surface[1], AuxiliaryVector, pericenter, ColorArray[Left], scale, focalLength);
//}

//// 矩阵乘法函数
//void matrixMultiply(double A[3][3], double B[3][3], double C[3][3]) {
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            C[i][j] = 0;
//            for (int k = 0; k < 3; k++) {
//                C[i][j] += A[i][k] * B[k][j];
//            }
//        }
//    }
//}
//
//// 绕x轴旋转的矩阵
//void rotation_x_axis(double theta, double R[3][3]) {
//    R[0][0] = 1; R[0][1] = 0; R[0][2] = 0;
//    R[1][0] = 0; R[1][1] = cos(theta); R[1][2] = sin(theta);
//    R[2][0] = 0; R[2][1] = -sin(theta); R[2][2] = cos(theta);
//}
//
//// 绕y轴旋转的矩阵
//void rotation_y_axis(double theta, double R[3][3]) {
//    R[0][0] = cos(theta); R[0][1] = 0; R[0][2] = -sin(theta);
//    R[1][0] = 0; R[1][1] = 1; R[1][2] = 0;
//    R[2][0] = sin(theta); R[2][1] = 0; R[2][2] = cos(theta);
//}
//
//// 绕z轴旋转的矩阵
//void rotation_z_axis(double theta, double R[3][3]) {
//    R[0][0] = cos(theta); R[0][1] = sin(theta); R[0][2] = 0;
//    R[1][0] = -sin(theta); R[1][1] = cos(theta); R[1][2] = 0;
//    R[2][0] = 0; R[2][1] = 0; R[2][2] = 1;
//}
//
//// 根据鼠标位移计算旋转和平移参数
//void calculateTransformationParams(double deltaX, double deltaY, double* zhuan_x, double* zhuan_y, double* zhuan_z, double* yi_x, double* yi_y, double* yi_z) {
//    // 根据鼠标位移计算旋转角度
//    *zhuan_x = deltaY * 0.01;
//    *zhuan_y = deltaX * 0.01;
//    *zhuan_z = 0;
//    *yi_x = 0;
//    *yi_y = 0;
//    *yi_z = 0;
//}
//
//// 坐标转换函数
//void w_to_c(Vec3* Vertex, int numVertices, double zhuan_x, double zhuan_y, double zhuan_z, double yi_x, double yi_y, double yi_z) {
//    double Rx[3][3], Ry[3][3], Rz[3][3];
//    double R1[3][3], R[3][3];
//
//    rotation_x_axis(zhuan_x, Rx);
//    rotation_y_axis(zhuan_y, Ry);
//    rotation_z_axis(zhuan_z, Rz);
//
//    matrixMultiply(Rz, Ry, R1);
//    matrixMultiply(R1, Rx, R);
//
//    for (int i = 0; i < numVertices; i++) {
//        double point[3] = { Vertex[i].x, Vertex[i].y, Vertex[i].z };
//        double r[3] = { 0 };
//
//        for (int j = 0; j < 3; j++) {
//            for (int k = 0; k < 3; k++) {
//                r[j] += R[j][k] * point[k];
//            }
//        }
//
//        Vertex[i].x = yi_x + r[0];
//        Vertex[i].y = yi_y + r[1];
//        Vertex[i].z = yi_z + r[2];
//    }
//}



//// 转动函数
//void rotate_around_center(Vec3* cam, Vec3 w, double f, double x, double y,
//    double* zhuan_x, double* zhuan_y, double* zhuan_z,
//    double* yi_x, double* yi_y, double* yi_z) {
//    // 假设鼠标位移与转动角度的比例系数
//    const double angle_scale = 0.01;
//
//    // 计算转动角度
//    *zhuan_x = x * angle_scale;
//    *zhuan_y = y * angle_scale;
//    *zhuan_z = 0;  // 这里假设 z 轴无转动
//
//    // 计算绕中心点转动后的位置
//    Vec3 relative = { cam->x - w.x, cam->y - w.y, cam->z - w.z };
//
//    // 绕 x 轴转动
//    double cos_x = cos(*zhuan_x);
//    double sin_x = sin(*zhuan_x);
//    double new_y_x = relative.y * cos_x - relative.z * sin_x;
//    double new_z_x = relative.y * sin_x + relative.z * cos_x;
//    relative.y = new_y_x;
//    relative.z = new_z_x;
//
//    // 绕 y 轴转动
//    double cos_y = cos(*zhuan_y);
//    double sin_y = sin(*zhuan_y);
//    double new_x_y = relative.x * cos_y - relative.z * sin_y;
//    double new_z_y = relative.x * sin_y + relative.z * cos_y;
//    relative.x = new_x_y;
//    relative.z = new_z_y;
//
//    // 计算位移
//    *yi_x = relative.x - (cam->x - w.x);
//    *yi_y = relative.y - (cam->y - w.y);
//    *yi_z = relative.z - (cam->z - w.z);
//
//    // 更新 cam 的位置
//    cam->x = w.x + relative.x;
//    cam->y = w.y + relative.y;
//    cam->z = w.z + relative.z;
//}

//// 定义链表节点结构体
//typedef struct CubeStateNode {
//    Vec3 Vertex[8];
//    Vec3 AuxiliaryVector[2];
//    COLORREF SurfaceNightColor[6];
//    struct CubeStateNode* next;
//} CubeStateNode;

//// 创建新节点
//CubeStateNode* createNode(Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]) {
//    CubeStateNode* newNode = (CubeStateNode*)malloc(sizeof(CubeStateNode));
//    if (newNode == NULL) {
//        printf("内存分配失败\n");
//        exit(1);
//    }
//    for (int i = 0; i < 8; i++) {
//        newNode->Vertex[i] = Vertex[i];
//    }
//    for (int i = 0; i < 2; i++) {
//        newNode->AuxiliaryVector[i] = AuxiliaryVector[i];
//    }
//    for (int i = 0; i < 6; i++) {
//        newNode->SurfaceNightColor[i] = SurfaceNightColor[i];
//    }
//    newNode->next = NULL;
//    return newNode;
//}
//
//// 在链表头部插入节点
//void insertNode(CubeStateNode** head, Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]) {
//    CubeStateNode* newNode = createNode(Vertex, AuxiliaryVector, SurfaceNightColor);
//    newNode->next = *head;
//    *head = newNode;
//}
//
//// 释放链表内存
//void freeList(CubeStateNode* head) {
//    CubeStateNode* temp;
//    while (head != NULL) {
//        temp = head;
//        head = head->next;
//        free(temp);
//    }
//}

//// 撤销操作
//void undo(CubeStateNode** head, Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]) {
//    if (*head == NULL || (*head)->next == NULL) {
//        return;
//    }
//    CubeStateNode* temp = *head;
//    *head = (*head)->next;
//    free(temp);
//
//    // 恢复上一个状态
//    for (int i = 0; i < 8; i++) {
//        Vertex[i] = (*head)->Vertex[i];
//    }
//    for (int i = 0; i < 2; i++) {
//        AuxiliaryVector[i] = (*head)->AuxiliaryVector[i];
//    }
//    for (int i = 0; i < 6; i++) {
//        SurfaceNightColor[i] = (*head)->SurfaceNightColor[i];
//    }
//}

int main() {
    // 使用 EasyX 的初始化函数
    initgraph(WIDTH, HEIGHT);
    setbkcolor(RGB(0, 0, 0));  // 设置背景颜色为黑色
    cleardevice();  // 用当前背景色清空屏幕
    BeginBatchDraw();

    Vec3 AuxiliaryVector[2] = { {1, 0, 0}, {0, 1, 0} };
    Vec3 Vertex[8] = {
        {-GAMEPAD, -GAMEPAD, -GAMEPAD},
        {GAMEPAD, -GAMEPAD, -GAMEPAD},
        {GAMEPAD, GAMEPAD, -GAMEPAD},
        {-GAMEPAD, GAMEPAD, -GAMEPAD},
        {-GAMEPAD, -GAMEPAD, GAMEPAD},
        {GAMEPAD, -GAMEPAD, GAMEPAD},
        {GAMEPAD, GAMEPAD, GAMEPAD},
        {-GAMEPAD, GAMEPAD, GAMEPAD}
    };

    COLORREF SurfaceNightColor[6];
    for (int i = 0; i < 6; i++) {
        SurfaceNightColor[i] = SurfaceColor[i];
    }

    Vec2 pericenter = { WIDTH / 2.0, HEIGHT / 2.0 };
    double scale = 10.0;
    double focalLength = 100.0; // 焦距

    // 初始化链表头节点，存储初始状态
    CubeStateNode* stateList = NULL;
    insertNode(&stateList, Vertex, AuxiliaryVector, SurfaceNightColor);

    drawCube(Vertex, AuxiliaryVector, pericenter, SurfaceNightColor, scale, focalLength);

    FlushBatchDraw();

    ExMessage msg;
    bool isExiting = false;
    bool isDragging = false;
    POINT lastMousePos;

    while (!isExiting) {
        if (peekmessage(&msg, EM_MOUSE | EM_KEY, true)) {
            switch (msg.message) {
            case WM_LBUTTONDOWN:
                // 处理鼠标左键按下事件
                isDragging = true;
                lastMousePos.x = msg.x;
                lastMousePos.y = msg.y;
                break;
            case WM_LBUTTONUP:
                // 处理鼠标左键抬起事件
                isDragging = false;
                // 记录旋转后的状态到链表
                insertNode(&stateList, Vertex, AuxiliaryVector, SurfaceNightColor);
                break;
            case WM_MOUSEMOVE:
                if (isDragging) {
                    // 计算鼠标移动的距离
                    double deltaX = (double)(msg.x - lastMousePos.x);
                    double deltaY = (double)(msg.y - lastMousePos.y);
                    lastMousePos.x = msg.x;
                    lastMousePos.y = msg.y;

                    double zhuan_x, zhuan_y, zhuan_z, yi_x, yi_y, yi_z;
                    calculateTransformationParams(deltaX, deltaY, &zhuan_x, &zhuan_y, &zhuan_z, &yi_x, &yi_y, &yi_z);

                    // 对魔方顶点进行坐标转换
                    w_to_c(Vertex, 8, zhuan_x, zhuan_y, zhuan_z, yi_x, yi_y, yi_z);

                    // 重新绘制魔方
                    drawCube(Vertex, AuxiliaryVector, pericenter, SurfaceNightColor, scale, focalLength);
                    FlushBatchDraw();
                }
                break;
            case WM_MOUSEWHEEL:
                // 处理鼠标滚轮事件以缩放视图
                scale += msg.wheel / 120.0;
                if (scale < 1.0) scale = 1.0;
                if (scale > 20.0) scale = 20.0;

                // 调整焦距
                focalLength += msg.wheel / 120.0 * 10.0; // 可以根据实际情况调整系数
                if (focalLength < 50.0) focalLength = 50.0;
                if (focalLength > 200.0) focalLength = 200.0;

                // 重新绘制魔方
                drawCube(Vertex, AuxiliaryVector, pericenter, SurfaceNightColor, scale, focalLength);
                FlushBatchDraw();
                break;
            case WM_KEYDOWN:
                if (msg.vkcode == VK_ESCAPE) {
                    isExiting = true;
                }
                else if (msg.vkcode == VK_BACK) {
                    // 按下 Backspace 键进行撤销操作
                    undo(&stateList, Vertex, AuxiliaryVector, SurfaceNightColor);
                    drawCube(Vertex, AuxiliaryVector, pericenter, SurfaceNightColor, scale, focalLength);
                    FlushBatchDraw();
                }
                else if (msg.vkcode == 'Z') {
                    // 按下 Z 键绕 Z 轴旋转
                    // 可以添加绕 Z 轴旋转的逻辑
                }
                break;
            }
        }
    }

    // 释放链表内存
    freeList(stateList);

    EndBatchDraw();
    closegraph();
    return 0;
}
//// 向量加法
//Vec2 vec2_add(Vec2 a, Vec2 b) {
//    Vec2 result;
//    result.x = a.x + b.x;
//    result.y = a.y + b.y;
//    return result;
//}
//
//// 向量减法
//Vec2 vec2_sub(Vec2 a, Vec2 b) {
//    Vec2 result;
//    result.x = a.x - b.x;
//    result.y = a.y - b.y;
//    return result;
//}
//
//// 向量数乘
//Vec2 vec2_mul(Vec2 a, double num) {
//    Vec2 result;
//    result.x = a.x * num;
//    result.y = a.y * num;
//    return result;
//}
//
//// 向量数除
//Vec2 vec2_div(Vec2 a, double num) {
//    Vec2 result;
//    result.x = a.x / num;
//    result.y = a.y / num;
//    return result;
//}
//
//// 向量点乘
//double vec2_dot(Vec2 a, Vec2 b) {
//    return a.x * b.x + a.y * b.y;
//}
//
//// 向量加法
////Vec3 vec3_add(Vec3 a, Vec3 b) {
////    Vec3 result;
////    result.x = a.x + b.x;
////    result.y = a.y + b.y;
////    result.z = a.z + b.z;
////    return result;
////}
//
//// 向量减法
//Vec3 vec3_sub(Vec3 a, Vec3 b) {
//    Vec3 result;
//    result.x = a.x - b.x;
//    result.y = a.y - b.y;
//    result.z = a.z - b.z;
//    return result;
//}
//
//// 向量数乘
//Vec3 vec3_mul(Vec3 a, double num) {
//    Vec3 result;
//    result.x = a.x * num;
//    result.y = a.y * num;
//    result.z = a.z * num;
//    return result;
//}
//
//// 向量数除
//Vec3 vec3_div(Vec3 a, double num) {
//    Vec3 result;
//    result.x = a.x / num;
//    result.y = a.y / num;
//    result.z = a.z / num;
//    return result;
//}