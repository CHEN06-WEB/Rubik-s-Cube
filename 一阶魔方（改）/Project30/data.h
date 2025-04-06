#include <graphics.h>
#ifndef DATA
#define DATA


// 二维向量
typedef struct {
    double x, y;
} Vec2;

// 三维向量
typedef struct {
    double x, y, z;
} Vec3;
// 定义六个面
typedef enum {
    Up, Down, Left, Right, Front, Back
} Plane;

// 六个面的颜色
//COLORREF SurfaceColor[6] = {
//    RGB(255, 0, 0),    // Up
//    RGB(255, 255, 0),  // Down
//    RGB(0, 0, 255),    // Left
//    RGB(0, 255, 0),    // Right
//    RGB(165, 42, 42),  // Front
//    RGB(255, 0, 255)   // Back
//};

// 定义链表节点结构体
typedef struct CubeStateNode {
    Vec3 Vertex[8];
    Vec3 AuxiliaryVector[2];
    COLORREF SurfaceNightColor[6];
    struct CubeStateNode* next;
} CubeStateNode; 

#endif // !DATA