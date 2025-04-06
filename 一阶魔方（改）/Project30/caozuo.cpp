#include"caozuo.h"
#include<math.h>
#include<stdio.h>

// 转动函数
void rotate_around_center(Vec3* cam, Vec3 w, double f, double x, double y,
    double* zhuan_x, double* zhuan_y, double* zhuan_z,
    double* yi_x, double* yi_y, double* yi_z) {
    // 假设鼠标位移与转动角度的比例系数
    const double angle_scale = 0.01;

    // 计算转动角度
    *zhuan_x = x * angle_scale;
    *zhuan_y = y * angle_scale;
    *zhuan_z = 0;  // 这里假设 z 轴无转动

    // 计算绕中心点转动后的位置
    Vec3 relative = { cam->x - w.x, cam->y - w.y, cam->z - w.z };

    // 绕 x 轴转动
    double cos_x = cos(*zhuan_x);
    double sin_x = sin(*zhuan_x);
    double new_y_x = relative.y * cos_x - relative.z * sin_x;
    double new_z_x = relative.y * sin_x + relative.z * cos_x;
    relative.y = new_y_x;
    relative.z = new_z_x;

    // 绕 y 轴转动
    double cos_y = cos(*zhuan_y);
    double sin_y = sin(*zhuan_y);
    double new_x_y = relative.x * cos_y - relative.z * sin_y;
    double new_z_y = relative.x * sin_y + relative.z * cos_y;
    relative.x = new_x_y;
    relative.z = new_z_y;

    // 计算位移
    *yi_x = relative.x - (cam->x - w.x);
    *yi_y = relative.y - (cam->y - w.y);
    *yi_z = relative.z - (cam->z - w.z);

    // 更新 cam 的位置
    cam->x = w.x + relative.x;
    cam->y = w.y + relative.y;
    cam->z = w.z + relative.z;
}

// 创建新节点
CubeStateNode* createNode(Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]) {
    CubeStateNode* newNode = (CubeStateNode*)malloc(sizeof(CubeStateNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    for (int i = 0; i < 8; i++) {
        newNode->Vertex[i] = Vertex[i];
    }
    for (int i = 0; i < 2; i++) {
        newNode->AuxiliaryVector[i] = AuxiliaryVector[i];
    }
    for (int i = 0; i < 6; i++) {
        newNode->SurfaceNightColor[i] = SurfaceNightColor[i];
    }
    newNode->next = NULL;
    return newNode;
}

// 在链表头部插入节点
void insertNode(CubeStateNode** head, Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]) {
    CubeStateNode* newNode = createNode(Vertex, AuxiliaryVector, SurfaceNightColor);
    newNode->next = *head;
    *head = newNode;
}

// 释放链表内存
void freeList(CubeStateNode* head) {
    CubeStateNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 撤销操作
void undo(CubeStateNode** head, Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    CubeStateNode* temp = *head;
    *head = (*head)->next;
    free(temp);

    // 恢复上一个状态
    for (int i = 0; i < 8; i++) {
        Vertex[i] = (*head)->Vertex[i];
    }
    for (int i = 0; i < 2; i++) {
        AuxiliaryVector[i] = (*head)->AuxiliaryVector[i];
    }
    for (int i = 0; i < 6; i++) {
        SurfaceNightColor[i] = (*head)->SurfaceNightColor[i];
    }
}