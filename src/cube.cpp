#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////Hint:
  V.resize(8,3);
  F.resize(6,4);
  UV.resize(14,2);
  UF.resize(6,4);
  NV.resize(6,3);
  NF.resize(6,4);

  V.row(0) = Eigen::Vector3d(0, 0, 0);
  V.row(1) = Eigen::Vector3d(1, 0, 0);
  V.row(2) = Eigen::Vector3d(1, 1, 0);
  V.row(3) = Eigen::Vector3d(0, 1, 0);
  V.row(4) = Eigen::Vector3d(0, 0, 1);
  V.row(5) = Eigen::Vector3d(1, 0, 1);
  V.row(6) = Eigen::Vector3d(1, 1, 1);
  V.row(7) = Eigen::Vector3d(0, 1, 1);

  UV.row(0) = Eigen::Vector2d(0, 1);
  UV.row(1) = Eigen::Vector2d(0, 2);
  UV.row(2) = Eigen::Vector2d(1, 0);
  UV.row(3) = Eigen::Vector2d(1, 1);
  UV.row(4) = Eigen::Vector2d(1, 2);
  UV.row(5) = Eigen::Vector2d(1, 3);
  UV.row(6) = Eigen::Vector2d(2, 0);
  UV.row(7) = Eigen::Vector2d(2, 1);
  UV.row(8) = Eigen::Vector2d(2, 2);
  UV.row(9) = Eigen::Vector2d(2, 3);
  UV.row(10) = Eigen::Vector2d(3, 1);
  UV.row(11) = Eigen::Vector2d(3, 2);
  UV.row(12) = Eigen::Vector2d(4, 1);
  UV.row(13) = Eigen::Vector2d(4, 2);
  UV /= 4.0;

  NV.row(0) = Eigen::Vector3d(1, 0, 0);
  NV.row(1) = Eigen::Vector3d(-1, 0, 0);
  NV.row(2) = Eigen::Vector3d(0, 1, 0);
  NV.row(3) = Eigen::Vector3d(0, -1, 0);
  NV.row(4) = Eigen::Vector3d(0, 0, 1);
  NV.row(5) = Eigen::Vector3d(0, 0, -1);

  F.row(0) = Eigen::Vector4i(1, 2, 6, 5);
  F.row(1) = Eigen::Vector4i(1, 5, 8, 4);
  F.row(2) = Eigen::Vector4i(2, 3, 7, 6);
  F.row(3) = Eigen::Vector4i(5, 6, 7, 8);
  F.row(4) = Eigen::Vector4i(4, 3, 2, 1);
  F.row(5) = Eigen::Vector4i(8, 7, 3, 4);

  UF.row(0) = Eigen::Vector4i(5, 9, 8, 4);
  UF.row(1) = Eigen::Vector4i(5, 4, 1, 2); 
  UF.row(2) = Eigen::Vector4i(9, 12, 11, 8); 
  UF.row(3) = Eigen::Vector4i(4, 8, 7, 3); 
  UF.row(4) = Eigen::Vector4i(6, 10, 9, 5); 
  UF.row(5) = Eigen::Vector4i(13, 11, 12, 14); 

  NF.row(0) = Eigen::Vector4i(4, 4, 4, 4);
  NF.row(1) = Eigen::Vector4i(2, 2, 2, 2);
  NF.row(2) = Eigen::Vector4i(1, 1, 1, 1); 
  NF.row(3) = Eigen::Vector4i(5, 5, 5, 5); 
  NF.row(4) = Eigen::Vector4i(6, 6, 6, 6); 
  NF.row(5) = Eigen::Vector4i(3, 3, 3, 3);
}
