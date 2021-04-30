#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "avlbst.h"
#include "Hashtable.h"
#include <ctime>

using namespace std;


int main(int argc, char * argv[]){
    if (argc < 6) {
        cout << "please specify all the required inputs";
        return 0;
    }
    ifstream infile(argv[1]);
    ofstream ofile(argv[2]);

    // x=0, linear probing. x=1, quadratic probing. x=2, double-hashing. x=3, AVL Tree
    int x = atoi(argv[3]);  
    // d=0, normal HashTable. d=1, a debug-mode HashTable. This value is ignored by your program if x=3.
    int d = atoi(argv[4]);;
    // r will be an integer that says how often to repeat the whole program.
    int r = atoi(argv[5]);;

    stringstream ss;
    AVLTree<string, int> tree;
    Hashtable ht(d, x);
    vector<string> str_vec;
    while (ss << infile){
        string temp;
        ss >> temp;
        temp.erase(remove_if(temp.begin(), temp.end(), [](char c){return !isalpha(c);}), temp.end());
        for_each(temp.begin(), temp.end(), [](char & c) {c = tolower(c);});
        str_vec.push_back(temp);
    }
    for (const auto& it: str_vec){
        if (x == 3){
            if (tree.find(it) != tree.end()){
                tree.find(it)->second = tree.find(it)->second + 1;
            }
            else {tree.insert(make_pair(it, 1));}
        }
        else{
            ht.add(it);
        }
    }
            

    
    clock_t start;
    double duration;

    /* Preprocessing here that you don't want to time */

    start = clock();

    /* Your algorithm here */

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << duration/r << endl;
}
