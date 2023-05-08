#include <iostream>
#include <fstream> 
#include <string>
using namespace std;
#include "ReadFile.h"

void ReadFile(string fname, double (&t)[2000], double (&A)[2000])
    {
        fstream DataFile;
        DataFile.open(fname, ios::in);

        if(!DataFile) {
        cout << "ERROR OPENING FILE!!! EXITING.." << endl;}

        string s;
        for (int i = 0; i < 2; i++) {
            getline(DataFile, s);
        }
        double time, amplitude;
        int ind = 0;
        while (DataFile >> time >> amplitude) {
            t[ind] = time;
            A[ind] = amplitude;
            ind++;
        DataFile.close();
        }
    }