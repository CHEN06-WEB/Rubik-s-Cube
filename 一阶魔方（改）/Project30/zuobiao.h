#include"data.h"

// 向量点乘
double vec3_dot(Vec3, Vec3);
// 向量长度
double vec2_length(Vec2);

double vec3_length(Vec3);
Vec2 vec2_scale(Vec2 , double );
Vec3 vec3_scale(Vec3 , double );
Vec3 vec3_projection(Vec3 A, Vec3 B);
void rotation_x(double f, double z, double R[3][3]);

// 焦距f
void c_to_p(Vec3* Vertex, int numVertices, double f);

// 将三维的点的值转换为在对应 xoy 面上的投影的坐标
Vec2 transform3DTo2D(Vec3 vertex, Vec3 AuxiliaryVector[2], double scale, double focalLength);
// 矩阵乘法函数
void matrixMultiply(double A[3][3], double B[3][3], double C[3][3]);

// 绕x轴旋转的矩阵
void rotation_x_axis(double theta, double R[3][3]);

// 绕y轴旋转的矩阵
void rotation_y_axis(double theta, double R[3][3]);

// 绕z轴旋转的矩阵
void rotation_z_axis(double theta, double R[3][3]);

// 根据鼠标位移计算旋转和平移参数
void calculateTransformationParams(double deltaX, double deltaY, double* zhuan_x, double* zhuan_y, double* zhuan_z, double* yi_x, double* yi_y, double* yi_z);

// 坐标转换函数
void w_to_c(Vec3* Vertex, int numVertices, double zhuan_x, double zhuan_y, double zhuan_z, double yi_x, double yi_y, double yi_z);
// 画表面
void drawSurface(Vec3 Surface[4], Vec3 AuxiliaryVector[2], Vec2 pericenter_Sur, COLORREF color, double scale, double focalLength);

// 画正方体
void drawCube(Vec3 Vertex[8], Vec3 AuxiliaryVector[2], Vec2 pericenter, COLORREF ColorArray[6], double scale, double focalLength);
// 根据投影面 x，y 轴正方向向量求出投影面法向量
//Vec3 getVerticalAxis(Vec3 AuxiliaryVector[2]);