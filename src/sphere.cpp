#include "sphere.h"
#include <iostream>
#include <math.h>
#include <corecrt_math_defines.h>
void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
    int vertices = num_faces_u * (num_faces_v - 1) + 2;
    int faces = num_faces_u * num_faces_v;
    V.resize(vertices, 3);
    F.resize(faces, 4);
    UV.resize(vertices + num_faces_v - 1, 2);
    UF.resize(faces, 4);
    NV.resize(vertices, 3);
    NF.resize(faces, 4);

    double r = 1.0;
    double u_step = 1.0 / num_faces_u;
    double v_step = 1.0 / num_faces_v;
    double lat_step = M_PI * v_step;
    double long_step = 2.0 * M_PI * u_step;
    int cur_u = 0;
    int cur_uv = 0;
    V.row(cur_u++) = Eigen::Vector3d(0, 0, -r);
    UV.row(cur_uv++) = Eigen::Vector2d(0.5, 0);
    for (int i = 1; i < num_faces_v; ++i) {
        double latitude = i * lat_step;
        double v = i * v_step;
        for (int j = 0; j < num_faces_u; ++j) {
            double longitude = j * long_step;
            double x = r * sin(latitude) * cos(longitude);
            double y = r * sin(latitude) * sin(longitude);
            double z = -r * cos(latitude); 
            double u = j * u_step;

            V.row(cur_u++) = Eigen::Vector3d(x, y, z);
            UV.row(cur_uv++) = Eigen::Vector2d(u, v);
        }
        UV.row(cur_uv++) = Eigen::Vector2d(1.0, v);
    }
    V.row(cur_u) = Eigen::Vector3d(0, 0, r);
    UV.row(cur_uv) = Eigen::Vector2d(0.5, 1.0);
    int f_row = 0;
    for (int i = 0; i < num_faces_v; ++i) {
        for (int j = 0; j < num_faces_u; ++j) {
            int prev = (i - 1) * num_faces_u + j + 1;
            int cur = i * num_faces_u + j + 1;
            int v1 = 0;
            int v2 = 0;
            int v3 = 0;
            int v4 = 0;
            bool top = (i == num_faces_v - 1);
            bool bot = (i == 0); 
            bool right = (j == num_faces_u - 1);
            if (top) {
                v2 = cur_u;
                v3 = cur_u;
            }
            else {
                v2 = cur + 1;
                v3 = cur + 2;
                if (right) {
                    v3 -= j;
                }
            }
            if (bot) {
                v1 = 1;
                v4 = 1;
            }
            else {
                v1 = prev + 1;
                v4 = prev + 2;
                if (right) {
                    v4 -= j;
                } 
            } 
            F.row(f_row) = Eigen::Vector4i(v1, v2, v3, v4);
            prev = (i - 1) * (num_faces_u + 1) + j + 1;
            cur = i * (num_faces_u + 1) + j + 1;
            int uv1 = 0;
            int uv2 = 0;
            int uv3 = 0; 
            int uv4 = 0;
            if (top) {
                uv2 = cur_uv;
                uv3 = cur_uv;
            }
            else {
                uv2 = cur + 1;
                uv3 = cur + 2;
            }
            if (bot) {
                uv1 = 1;
                uv4 = 1;
            }
            else {
                uv1 = prev + 1;
                uv4 = prev + 2;
            }
            UF.row(f_row++) = Eigen::Vector4i(uv1, uv2, uv3, uv4);
        }
    }
    NV = V.normalized();
    NF = F;
}
