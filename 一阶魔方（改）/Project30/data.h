#include <graphics.h>
#ifndef DATA
#define DATA


// ��ά����
typedef struct {
    double x, y;
} Vec2;

// ��ά����
typedef struct {
    double x, y, z;
} Vec3;
// ����������
typedef enum {
    Up, Down, Left, Right, Front, Back
} Plane;

// ���������ɫ
//COLORREF SurfaceColor[6] = {
//    RGB(255, 0, 0),    // Up
//    RGB(255, 255, 0),  // Down
//    RGB(0, 0, 255),    // Left
//    RGB(0, 255, 0),    // Right
//    RGB(165, 42, 42),  // Front
//    RGB(255, 0, 255)   // Back
//};

// ��������ڵ�ṹ��
typedef struct CubeStateNode {
    Vec3 Vertex[8];
    Vec3 AuxiliaryVector[2];
    COLORREF SurfaceNightColor[6];
    struct CubeStateNode* next;
} CubeStateNode; 

#endif // !DATA