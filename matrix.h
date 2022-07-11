//
// Created by ayara on 16.01.2022.
//

#ifndef PJC_SEM_WORK_MATRIX_H
#define PJC_SEM_WORK_MATRIX_H

#include <vector>

using namespace std;

class matrix {
private:
    double determinant(const vector<vector<double>> mat);
    vector<vector<double>> transpose(vector<vector<double>> mat);
    vector<vector<double>> cofactor(vector<vector<double>> mat);

public:
    vector<vector<double>> calculate(vector<vector<double>> m);
};
#endif //PJC_SEM_WORK_MATRIX_H
