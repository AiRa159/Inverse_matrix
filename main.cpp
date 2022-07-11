#include <iostream>
#include "commands.h"

using namespace std;

int main(int argc, char *argv[]) {
    commands c = commands();

    string answer;
    while(getline(cin, answer)){
        if(cin.eof() || answer == "--end")
            break;
        if(cin.good()){
            try{
                c.parse(answer);
            }catch (runtime_error &error){
                cout << error.what() << endl;
                break;
            }
        }
    }
}
