#include"data.h"
// ת������
void rotate_around_center(Vec3* cam, Vec3 w, double f, double x, double y,
    double* zhuan_x, double* zhuan_y, double* zhuan_z,
    double* yi_x, double* yi_y, double* yi_z);

// ��������
void undo(CubeStateNode** head, Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]);
// �����½ڵ�
CubeStateNode* createNode(Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]);

// ������ͷ������ڵ�
void insertNode(CubeStateNode** head, Vec3 Vertex[8], Vec3 AuxiliaryVector[2], COLORREF SurfaceNightColor[6]);

// �ͷ������ڴ�
void freeList(CubeStateNode* head);