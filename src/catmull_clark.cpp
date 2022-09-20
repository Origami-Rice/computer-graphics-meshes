#include "catmull_clark.h"
#include "vertex_triangle_adjacency.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <vector>
#include <unordered_set>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
    if (num_iters == 0) {
        return;
    }
    std::vector<std::pair<int, int>> E;     	
    std::vector<std::pair<int, int>> FE;    	
    std::vector<std::vector<int>> FV;       	
    std::vector<std::unordered_set<int>> VV;      
    vertex_triangle_adjacency(F, V.rows(), FV);
    VV.resize(V.rows());
    std::vector<Eigen::RowVector3d> face_vertices;
    std::vector<Eigen::RowVector3d> edge_vertices;
    for (int i = 0; i < F.rows(); ++i) {
        for (int j = 0; j < F.cols(); ++j) {
            int v0 = F(i, (j + 3) % 4);
            int v1 = F(i, j);
            int v2 = F(i, (j + 1) % 4);
            auto f_edge = std::make_pair(v1, v2);
            auto b_edge = std::make_pair(v2, v1);
            VV[v1].insert(v0);
            VV[v1].insert(v2);
            bool exists = false;
            for (int k = 0; k < E.size(); ++k) {
                if (E[k] == f_edge || E[k] == b_edge) {
                    exists = true;
                    FE[k] = std::make_pair(FE[k].first, i);
                    break;
                }
            }
            if (!exists) {
                E.push_back(f_edge);
                FE.push_back(std::make_pair(i, -1));
            }
        }
    }
    SV.resize(V.rows() + F.rows() + E.size(), 3);
    SF.resize(F.rows() * F.cols(), 4);
    int sv_row = 0;
    int sf_row = 0;
    int fv_offset = 0;
    for (int i = 0; i < F.rows(); ++i) {
        auto average = Eigen::RowVector3d(0.0, 0.0, 0.0);
        for (int j = 0; j < F.cols(); ++j) {
            average += V.row(F(i, j));
        }
        average /= (double)F.cols();
        face_vertices.push_back(average);
        SV.row(sv_row++) = average;
    }
    int ev_offset = sv_row;
    for (int i = 0; i < E.size(); ++i) {
        Eigen::RowVector3d average = Eigen::RowVector3d(0.0, 0.0, 0.0);
        average += V.row(E[i].first) + V.row(E[i].second);
        average += face_vertices[FE[i].first] + face_vertices[FE[i].second];
        average /= 4.0;
        edge_vertices.push_back(average);
        SV.row(sv_row++) = average;
    }
    int v_offset = sv_row;
    for (int i = 0; i < V.rows(); ++i) {
        auto faces = FV[i];
        auto f = Eigen::RowVector3d(0.0, 0.0, 0.0);
        auto r = Eigen::RowVector3d(0.0, 0.0, 0.0);
        auto p = V.row(i);
        int n = faces.size();
        for (int face : faces) {
            f += face_vertices[face];
        } 
        f /= (double)n;

        for (int v : VV[i]) {
            auto midpoint = (V.row(v) + p) / 2.0;
            r += midpoint;
        }
        r /= VV[i].size();
        auto bary = (f + 2.0 * r + ((double)n - 3.0) * p) / (double)n;
        SV.row(sv_row++) = bary;
    }
    for (int i = 0; i < F.rows(); ++i) {
        int v1;
        int v2;
        int v3 = fv_offset + i;;
        int v4;
        for (int j = 0; j < F.cols(); ++j) {
            v1 = v_offset + F(i, j);
            auto f1 = std::make_pair(F(i, j), F(i, (j + 1) % F.cols()));
            auto b1 = std::make_pair(f1.second, f1.first);
            auto f2 = std::make_pair(F(i, j), F(i, (j + 3) % 4));
            auto b2 = std::make_pair(f2.second, f2.first);
            for (int k = 0; k < E.size(); ++k) {
                if (E[k] == f1 || E[k] == b1) {
                    v2 = k;
                }  
                if (E[k] == f2 || E[k] == b2) {
                    v4 = k;
                }   
            }
            v2 += ev_offset;
            v4 += ev_offset;
            SF.row(sf_row++) = Eigen::RowVector4i(v1, v2, v3, v4);
        }
    }
    Eigen::MatrixXd new_SV;
    Eigen::MatrixXi new_SF;
    catmull_clark(SV, SF, num_iters - 1, new_SV, new_SF);
    if (num_iters > 1) {
        SV = new_SV;
        SF = new_SF;
    }
}
