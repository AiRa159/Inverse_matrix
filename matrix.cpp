//
// Created by ayara on 16.01.2022.
//

#include <valarray>
#include <stdexcept>
#include "matrix.h"

vector<vector<double>> matrix::calculate(vector<vector<double>> m) {
    if(determinant(m) == 0)
        throw runtime_error("Determinant is 0");

    double det = 1.0/determinant(m);
    vector<vector<double>> result(m.size(), vector<double>(m.size()));

    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < m.size(); j++){
            result[i][j] = m[i][j];
        }
    }

    result = transpose(cofactor(result));

    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < m.size(); j++){
            result[i][j] *= det;
        }
    }

    return result;
}

double matrix::determinant(const vector<vector<double>> mat) {

    if(mat.size() == 0) {
        return 1;
    }

    if(mat.size() == 1) {
        return mat[0][0];
    }

    //Formula for 2x2-matrix
    if(mat.size() == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }

    double result = 0;
    int sign = 1;
    for(int i = 0; i < mat.size(); i++) {

        //Submatrix
        std::vector<std::vector<double>> subVect(mat.size() - 1, std::vector<double> (mat.size() - 1));
        for(int m = 1; m < mat.size(); m++) {
            int z = 0;
            for(int n = 0; n < mat.size(); n++) {
                if(n != i) {
                    subVect[m-1][z] = mat[m][n];
                    z++;
                }
            }
        }

        //recursive call
        result = result + sign * mat[0][i] * determinant(subVect);
        sign = -sign;
    }

    return result;
}

vector<vector<double>> matrix::transpose(vector<vector<double>> mat) {
    //Transpose-matrix: height = width(matrix), width = height(matrix)
    std::vector<std::vector<double>> result(mat[0].size(), std::vector<double> (mat.size()));

    //Filling solution-matrix
    for(int i = 0; i < mat.size(); i++) {
        for(int j = 0; j < mat[0].size(); j++) {
            result[j][i] = mat[i][j];
        }
    }
    return result;
}

vector<vector<double>> matrix::cofactor(vector<vector<double>> mat) {
    std::vector<std::vector<double>> result(mat.size(), std::vector<double> (mat.size()));
    std::vector<std::vector<double>> subVect(mat.size() - 1, std::vector<double> (mat.size() - 1));

    for(int i = 0; i < mat.size(); i++) {
        for(int j = 0; j < mat[0].size(); j++) {

            int p = 0;
            for(int x = 0; x < mat.size(); x++) {
                if(x == i) {
                    continue;
                }
                int q = 0;

                for(int y = 0; y < mat.size(); y++) {
                    if(y == j) {
                        continue;
                    }

                    subVect[p][q] = mat[x][y];
                    q++;
                }
                p++;
            }

            if(determinant(subVect) == 0){
                result[i][j] = 0;
            }else
                result[i][j] = pow(-1, i + j) * determinant(subVect);
        }
    }
    return result;
}