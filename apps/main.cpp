#include <cstdlib>
#include <string>
#include <iostream>
#include "Cluster.h"
using namespace std;

int main()
{
    string filename = "trial1.csv";

    Cluster cottonBed(100);             
    
    cottonBed.setExternalForce({0.0, 0.0, 0.0}); 

    cottonBed.run(filename);    

    string command = "../utils/plot.py " + filename;
    int return_code = system(command.c_str());
    
    if (return_code != 0){
        cout << "Python Code failed with exit code : " << return_code;
    }

    return 0;
}