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

// ���������ɫ
COLORREF SurfaceColor[6] = {
    RGB(255, 0, 0),    // Up
    RGB(255, 255, 0),  // Down
    RGB(0, 0, 255),    // Left
    RGB(0, 255, 0),    // Right
    RGB(165, 42, 42),  // Front
    RGB(255, 0, 255)   // Back
};

int main() {
    // ʹ�� EasyX �ĳ�ʼ������
    initgraph(WIDTH, HEIGHT);
    
    BeginBatchDraw();

    FlushBatchDraw();

    //getchar();

    //��������
    Vec3 AuxiliaryVector[2] = { {1, 0, 0}, {0, 1, 0} };

    //ħ������
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
    double focalLength = 1.0; // ����

    // ��ʼ������ͷ�ڵ㣬�洢��ʼ״̬
    CubeStateNode* stateList = NULL;
    insertNode(&stateList, Vertex, AuxiliaryVector, SurfaceNightColor);

    //��һ�λ���ħ��
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
                // ���������������¼�
                isDragging = true;
                lastMousePos.x = msg.x;
                lastMousePos.y = msg.y;
                break;
            case WM_LBUTTONUP:
                // ����������̧���¼�
                isDragging = false;
                // ��¼��ת���״̬������
                insertNode(&stateList, Vertex, AuxiliaryVector, SurfaceNightColor);
                break;
            case WM_MOUSEMOVE:
                if (isDragging) {
                    // ��������ƶ��ľ���
                    double deltaX = (double)(msg.x - lastMousePos.x);
                    double deltaY = (double)(msg.y - lastMousePos.y);
                    lastMousePos.x = msg.x;
                    lastMousePos.y = msg.y;

                    double zhuan_x, zhuan_y, zhuan_z, yi_x, yi_y, yi_z;
                    calculateTransformationParams(deltaX, deltaY, &zhuan_x, &zhuan_y, &zhuan_z, &yi_x, &yi_y, &yi_z);

                    // ��ħ�������������ת��
                    w_to_c(Vertex, 8, zhuan_x, zhuan_y, zhuan_z, yi_x, yi_y, yi_z);

                    // ���»���ħ��
                    drawCube(Vertex, AuxiliaryVector, pericenter, SurfaceNightColor, scale, focalLength);
                    FlushBatchDraw();
                }
                break;
            case WM_MOUSEWHEEL:
                printf("mousewheel\n");
                // �����������¼���������ͼ
                scale += msg.wheel / 120.0;
                if (scale < 1.0) scale = 1.0;
                if (scale > 20.0) scale = 20.0;

                // ��������
                focalLength += msg.wheel / 120.0 * 10.0; // ���Ը���ʵ���������ϵ��
                if (focalLength < 50.0) focalLength = 50.0;
                if (focalLength > 200.0) focalLength = 200.0;

                // ���»���ħ��
                drawCube(Vertex, AuxiliaryVector, pericenter, SurfaceNightColor, scale, focalLength);
                FlushBatchDraw();
                break;
            case WM_KEYDOWN:
                printf("keydown\n");
                if (msg.vkcode == VK_ESCAPE) {
                    isExiting = true;
                }
                else if (msg.vkcode == VK_BACK) {
                    // ���� Backspace �����г�������
                    printf("����");
                    undo(&stateList, Vertex, AuxiliaryVector, SurfaceNightColor);
                    drawCube(Vertex, AuxiliaryVector, pericenter, SurfaceNightColor, scale, focalLength);
                    FlushBatchDraw();
                }
                else if (msg.vkcode == 'Z') {
                    // ���� Z ���� Z ����ת
                    // ��������� Z ����ת���߼�
                }
                break;
            }
        }
    }

    // �ͷ������ڴ�
    freeList(stateList);

    EndBatchDraw();
    closegraph();
    return 0;
}