//
// Created by ayara on 16.01.2022.
//

#ifndef PJC_SEM_WORK_COMMANDS_H
#define PJC_SEM_WORK_COMMANDS_H

#include "matrix.h"

using namespace std;

class commands {
private:
    matrix m;
    int size;
    vector<vector<double>> mat;
    string state;

    int counter = 0;
public:
    commands();
    void parse(string &command);
    void help() const;
    void examples() const;
    void start() const;
    bool is_number(const string& s);
    void print(vector<vector<double>> a) const;
    void time(long time) const;
};
#endif //PJC_SEM_WORK_COMMANDS_H