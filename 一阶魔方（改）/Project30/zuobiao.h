#include"data.h"

// �������
double vec3_dot(Vec3, Vec3);
// ��������
double vec2_length(Vec2);

double vec3_length(Vec3);
Vec2 vec2_scale(Vec2 , double );
Vec3 vec3_scale(Vec3 , double );
Vec3 vec3_projection(Vec3 A, Vec3 B);
void rotation_x(double f, double z, double R[3][3]);

// ����f
void c_to_p(Vec3* Vertex, int numVertices, double f);

// ����ά�ĵ��ֵת��Ϊ�ڶ�Ӧ xoy ���ϵ�ͶӰ������
Vec2 transform3DTo2D(Vec3 vertex, Vec3 AuxiliaryVector[2], double scale, double focalLength);
// ����˷�����
void matrixMultiply(double A[3][3], double B[3][3], double C[3][3]);

// ��x����ת�ľ���
void rotation_x_axis(double theta, double R[3][3]);

// ��y����ת�ľ���
void rotation_y_axis(double theta, double R[3][3]);

// ��z����ת�ľ���
void rotation_z_axis(double theta, double R[3][3]);

// �������λ�Ƽ�����ת��ƽ�Ʋ���
void calculateTransformationParams(double deltaX, double deltaY, double* zhuan_x, double* zhuan_y, double* zhuan_z, double* yi_x, double* yi_y, double* yi_z);

// ����ת������
void w_to_c(Vec3* Vertex, int numVertices, double zhuan_x, double zhuan_y, double zhuan_z, double yi_x, double yi_y, double yi_z);
// ������
void drawSurface(Vec3 Surface[4], Vec3 AuxiliaryVector[2], Vec2 pericenter_Sur, COLORREF color, double scale, double focalLength);

// ��������
void drawCube(Vec3 Vertex[8], Vec3 AuxiliaryVector[2], Vec2 pericenter, COLORREF ColorArray[6], double scale, double focalLength);
// ����ͶӰ�� x��y ���������������ͶӰ�淨����
//Vec3 getVerticalAxis(Vec3 AuxiliaryVector[2]);