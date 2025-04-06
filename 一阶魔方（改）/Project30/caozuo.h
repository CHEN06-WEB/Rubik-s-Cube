#include"data.h"
// 转动函数
void rotate_around_center(Vec3* cam, Vec3 w, double f, double x, double y,
    double* zhuan_x, double* zhuan_y, double* zhuan_z,
    double* yi_x, double* yi_y, double* yi_z);

// 撤销操作
void undo(CubeStateNode** head, Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]);
// 创建新节点
CubeStateNode* createNode(Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]);

// 在链表头部插入节点
void insertNode(CubeStateNode** head, Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]);

// 释放链表内存
void freeList(CubeStateNode* head);