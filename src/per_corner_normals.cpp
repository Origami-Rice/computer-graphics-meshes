#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include <math.h>
#include <corecrt_math_defines.h>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  
  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);
  for (int i = 0; i < F.rows(); ++i) {
      Eigen::RowVector3d cur_n = triangle_area_normal(V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2))).normalized();
      for (int j = 0; j < 3; ++j) {
          Eigen::RowVector3d n(0, 0, 0);
          std::vector<int> indexes = VF[F(i, j)];
          for (int index : indexes) {
              Eigen::RowVector3d temp(0, 0, 0);
              Eigen::RowVector3d v1 = V.row(F(index, 0));
              Eigen::RowVector3d v2 = V.row(F(index, 1));
              Eigen::RowVector3d v3 = V.row(F(index, 2));
              temp = triangle_area_normal(v1, v2, v3).normalized();
              if ((cur_n.dot(temp) > cos((M_PI * corner_threshold) / 180))) {
                  n += temp;
              }
          }
          N.row(i * 3 + j) = n.normalized();
      }
  }
}
