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
#define HEIGHT 888
#define PI 3.14159265
#define SIDE ((WIDTH < HEIGHT) ? WIDTH : HEIGHT) / 8
#define GAMEPAD SIDE / 2
#define ZERO 0.1
#define PIECE 180

// 六个面的颜色
COLORREF SurfaceColor[6] = {
    RGB(255, 0, 0),    // Up
    RGB(255, 255, 0),  // Down
    RGB(0, 0, 255),    // Left
    RGB(0, 255, 0),    // Right
    RGB(165, 42, 42),  // Front
    RGB(255, 0, 255)   // Back
};

int main() {
    // 使用 EasyX 的初始化函数
    initgraph(WIDTH, HEIGHT);
    
    BeginBatchDraw();

    FlushBatchDraw();

    //getchar();

    //特征向量
    Vec3 AuxiliaryVector[2] = { {1, 0, 0}, {0, 1, 0} };

    //魔方坐标
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
    double focalLength = 1.0; // 焦距

    // 初始化链表头节点，存储初始状态
    CubeStateNode* stateList = NULL;
    insertNode(&stateList, Vertex, AuxiliaryVector, SurfaceNightColor);

    //第一次绘制魔方
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
                printf("mousewheel\n");
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
                printf("keydown\n");
                if (msg.vkcode == VK_ESCAPE) {
                    isExiting = true;
                }
                else if (msg.vkcode == VK_BACK) {
                    // 按下 Backspace 键进行撤销操作
                    printf("撤！");
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