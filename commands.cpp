//
// Created by ayara on 16.01.2022.
//

#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <sstream>
#include "commands.h"

using namespace std;

void commands::parse(string &command){
    if(command == "--help"){
        help();
        return;
    }

    if(command == "--end"){
        return;
    }

    if(command == "--examples"){
        examples();
        return;
    }

    if(command == "--start"){
        start();
        cout << "Enter size: " << endl;
        state = "size";
        return;
    }

    if(state == "size"){
        if(is_number(command)){
            size = stoi(command);
        }else
            throw runtime_error("Incorrect input!");

        if(size == 0)
            throw runtime_error("Incorrect input!");

        cout << "\nNow fill the matrix"
                "\n          1  2  3 .."
                "\nExample:  4  5  6 .."
                "\n          7  8  9 .."
                "\n         .. .. .. ..\n"<< endl;
        state = "filling";
        return;
    }

    if(state == "filling"){
        if(counter != size - 1){
            stringstream stream(command);
            vector<double> v;
            string current_number;
            while (stream >> current_number) {
                v.push_back(stoi(current_number));
            }

            if(v.size() != size){
                throw runtime_error("Invalid number of numbers");
            }
            mat.push_back(v);
            counter++;
            return;
        }else{
            stringstream stream(command);
            vector<double> v;
            string current_number;
            while (stream >> current_number) {
                v.push_back(stoi(current_number));
            }

            if(v.size() != size){
                throw runtime_error("Invalid number of numbers");
            }
            mat.push_back(v);
        }
        cout << "\nYour matrix:" << endl;
        print(mat);
        state = "calculation";
        cout << "\nPress ENTER to start calculation" << endl;
        return;
    }

    if(state == "calculation"){
        cout << "\nCalculating..." << endl;

        auto start = chrono::high_resolution_clock::now();
        vector<vector<double>> result = m.calculate(mat);
        auto end = chrono::high_resolution_clock::now();

        cout << "\nResult" << endl;
        print(result);
        time((unsigned long)chrono::duration_cast<chrono::microseconds>(end - start).count());
    }

    // ================Tests=================
    if(command == "--test1"){
        size = 2;
        mat = vector<vector<double>>(size);
        mat[0] = vector<double>{1, 0};
        mat[1] = vector<double>{0, 1};

        state = "calculation";
        cout << "\nYour matrix:" << endl;
        cout << "\nYour matrix:" << endl;
        print(mat);
        cout << "\nPress ENTER to start calculation" << endl;
        return;
    }

    if(command == "--test2"){
        size = 3;
        mat = vector<vector<double>>(size);
        mat[0] = vector<double>{3, -4, 5};
        mat[1] = vector<double>{2, -3, 1};
        mat[2] = vector<double>{3, -5, -1};

        state = "calculation";
        cout << "\nYour matrix:" << endl;
        cout << "\nYour matrix:" << endl;
        print(mat);
        cout << "\nPress ENTER to start calculation" << endl;
        return;
    }

    if(command == "--test3"){
        size = 4;
        mat = vector<vector<double>>(size);
        mat[0] = vector<double>{8, 7, 4, 4};
        mat[1] = vector<double>{3, 4, 2, 9};
        mat[2] = vector<double>{0, 4, 4, 2};
        mat[3] = vector<double>{9, 2, 8, 1};

        state = "calculation";
        cout << "\nYour matrix:" << endl;
        cout << "\nYour matrix:" << endl;
        print(mat);
        cout << "\nPress ENTER to start calculation" << endl;
        return;
    }

    if(command == "--test4"){
        size = 9;
        mat = vector<vector<double>>(size);
        mat[0] = vector<double>{5, 4, 2, 6, 0, 7, 6, 6, 3};
        mat[1] = vector<double>{0, 3, 6, 1, 1, 9, 3, 4, 0};
        mat[2] = vector<double>{0, 0, 8, 4, 4, 7, 5, 6, 4};
        mat[3] = vector<double>{0, 0, 0, 8, 0, 6, 3, 8, 8};
        mat[4] = vector<double>{0, 0, 0, 0, 6, 5, 2, 4, 2};
        mat[5] = vector<double>{0, 0, 0, 0, 0, 9, 0, 7, 0};
        mat[6] = vector<double>{0, 0, 0, 0, 0, 0, 2, 7, 9};
        mat[7] = vector<double>{0, 0, 0, 0, 0, 0, 0, 4, 1};
        mat[8] = vector<double>{0, 0, 0, 0, 0, 0, 0, 0, 2};

        state = "calculation";
        cout << "\nYour matrix:" << endl;
        cout << "\nYour matrix:" << endl;
        print(mat);
        cout << "\nPress ENTER to start calculation" << endl;
        return;
    }
}

commands::commands() {
    cout << " Calculator for calculating the inverse matrix\n"
            "      Created by Aiya Rakhimova(rakhiaiy)\n"
            "   Enter --help to find out more information\n" << endl;
}
void commands::help() const{
    cout << "==================================\n"
            "Instructions for using the project\n"
            "==================================\n"
            "[--help] - instruction \n"
            "[--start] - start counting inverse matrix\n"
            "[--examples] - show prepared examples\n"
            "[--end] - stop program\n" << endl;
}

void commands::examples() const {
    cout << "==================================\n"
            "            Examples\n"
            "==================================\n"
            "[--test1] - type to calculate matrix 2x2\n"
            "[--test2] - type to calculate matrix 3x3\n"
            "[--test3] - type to calculate matrix 4x4\n"
            "[--test4] - type to calculate matrix 9x9\n" << endl;
}

void commands::start() const {
    cout << "\nLet's start!\n"
            "1st step: enter size of matrix (N x N)\n"
            "2nd step: fill matrix\n"
            "3rd step: get result :)\n";
}

bool commands::is_number(const string &s) {
    string::const_iterator iterator = s.begin();
    while (iterator != s.end() && isdigit(*iterator)) ++iterator;
    return !s.empty() && iterator == s.end();
}


void commands::print(vector<vector<double>> a) const {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout.precision(2);
            cout << a[i][j] << "\t";

        }
        cout << endl;
    }
    cout << endl;
}

void commands::time(long time) const {
    cout <<"\nTime to complete calculation was " + to_string(time) + " microseconds.\n";
}