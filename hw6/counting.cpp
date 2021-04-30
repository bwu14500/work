#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "avlbst.h"
#include <ctime>

using namespace std;

int main(int argc, char * argv[]){
    if (argc < 4) {
        cout << "please specify two input files and one output file";
        return 0;
    }
    ifstream inputFile(argv[1]);
    stringstream ss;
    ofstream ofile(argv[2]);

    int x = atoi(argv[3]);
    int d = atoi(argv[4]);;
    int r = atoi(argv[5]);;


    clock_t start;
    double duration;

    /* Preprocessing here that you don't want to time */

    start = clock();

    /* Your algorithm here */

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << duration/r << endl;
}
