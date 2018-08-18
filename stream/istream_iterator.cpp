//
// Created by wein on 18/08/18.
//

#include <regex>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char** argv) {
    istream_iterator<string> iter, end;
    ifstream file;
    if (argc == 2) {
        file.open(argv[1]);
        iter = istream_iterator<string>(file);
    } else {
        iter = istream_iterator<string>(cin);
    }
    while (iter != end) {
        cout << ":" << *(iter++);
    }
    return 0;
}
