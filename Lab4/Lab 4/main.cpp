//
//  main.cpp
//  Lab 4
//
//  Created by Harkaranjeet Singh  on 10/12/17.
//  Copyright © 2017 Harkaranjeet Singh. All rights reserved.

//
//  Practice for associative Arrays - unordered_map and vector c++
// Given a data file of biological sequences in which each protein
// sequence consists of a label
// and a string of amino acids, find duplicated sequences and rebuild the
// data file with multiple
// labels for those duplicated sequences.
// This program read the sequences and keys from data file.
// Analysis it separated the keys and sequences
// it finds the sequences with same keys
// output the sequences in with same keys
// In this program Unordered map is used with vector to store keys and sequences
//


#include <iostream>
#include <vector>   // for vector
#include <fstream> //for data file
#include <unordered_map>
#include <iterator>
#include <string> // string

using namespace std;

int main(int argc, const char **argv) {
    
    string key;
    string sequence;
    ifstream fin;
    ofstream fout;
    unordered_map<string, vector<string> > mylist;
    
    string xxx = argv[1];
    fin.open (xxx.c_str());   // input file
    string output = "output";   // Name for output file
    fout.open(output.c_str());   // output file
    fin >> key;
    while (!fin.eof())
    {
        fin>> sequence;
        unordered_map<string, vector<string> >::iterator got = mylist.find(sequence);
        if (got != mylist.end())
        {
            mylist[sequence].push_back(key); // key push to vector with sequence
        }
        else
        {
            mylist[sequence];
            mylist[sequence].push_back(key);
        }
        
        fin >> key;  //get key from input file
    } //end while
    
    fin.close();  //file close
    
    
    
    unordered_map<string, vector<string> >::const_iterator it;  // unorederd map
    
    // For display and storing to file
    
    for( it = mylist.begin(); it != mylist.end(); it++)
    {
        int x = it->second.size();
        for (int i = 0; i< x; i++ ) {
            cout << it->second[i];  // for showing output
            fout << it->second[i];  // for loading in file
            
            if (i+1 < x){
                cout << ", ";
                fout << ", ";
            }
        }
        cout << "\n" << it->first << "\n"; // for showing ouput
        fout << "\n" << it->first << "\n"; // for loading in file
        
    }

    return 0;
}
