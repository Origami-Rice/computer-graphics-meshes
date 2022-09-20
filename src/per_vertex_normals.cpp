#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  for (int i = 0; i < V.rows(); ++i) {
      Eigen::RowVector3d n(0, 0, 0);
      for (int j = 0; j < F.rows(); ++j) {
          if ((i == F.row(j).x()) || (i == F.row(j).y()) || (i == F.row(j).z())) {
              Eigen::RowVector3d v1 = V.row(F(j, 0));
              Eigen::RowVector3d v2 = V.row(F(j, 1));
              Eigen::RowVector3d v3 = V.row(F(j, 2));
              n += triangle_area_normal(v1, v2, v3).normalized();
          }
      }
      N.row(i) = n.normalized();
  }
}
