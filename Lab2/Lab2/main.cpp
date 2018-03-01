/////////////////////////////////////////////
////
//// Interpreter for simplified infix expression with +,-,*,/,(,),^
//// Input from a data file
//// compile:  $>g++ main.cpp
//// execution: ./a.out "data file name"
////
//// p1-data   2+3*4/2+3+4*2
//// data1: (2*3*2^3)
//// data2: (2^3)^2+2^3^2
//// data3: ( 2^3) ^ 2 + 2 ^3^2
//// data4: (2+3)*4/2-(3*(4-1))+2^3^2+1
//// data5: (2+3) * 4/ 2 - (3 *(4-1) ) +2^3 ^ 2+1
//// IDE XCODE
//// Compiler  Clang
////
////
//// Created by Harkaranjeet Singh on 9/7/17.
//// Copyright © 2017 Harkaranjeet Singh. All rights reserved.
////
/////////////////////////////////////////////


#include <cstdlib> //for atoi()
#include <iostream>
#include <fstream>
#include <cmath>  //for power
using namespace std;

int Exp(), Term(), Exp2(int), Term2(int), Fact(), Fact2(int inp), Num();
ifstream fin;
string prog, s1; //string for reading 1-line input program
int indexx = 0;  //global index for program string


// This Function Reads the String from a data file
// Display the result by calling exp() function which performs calculations
int main(int argc, const char **argv)
{ //cout<<">";
    string path1 = argv[1];
    fin.open(path1.c_str()); // open data file
    getline(fin, s1);  //read 1 line into string
    while (!fin.eof())
    {
        prog += s1; // extend prog string with s1
        getline(fin, s1); // read next line if any
    }
    //cin>>prog;  //reads 1-line input expression (program)
    cout<<" String = "<<prog<<endl;
    cout<<" Result = "<<Exp()<<endl;
}

//Calling the function as grammer indicates
//returns the Exp2 funtion with a parameter of Term
int Exp(){
    return Exp2(Term());
}

//Calling the function as grammer indicates
//returns the Term2 funtion with a parameter of Fact

int Term(){
    return Term2(Fact());
}


// Read the string char by char
// Handle the space by skiping
// Perform the grammer
// Handles T+T and T-T
int Exp2(int inp)
{
    int result = inp;
    if (indexx < prog.length())   //if not the end of program string
    {
        char a = prog.at(indexx++); //get one chr from program string
        while (a == ' ' && indexx < prog.length()) // if space skip and read until a char
        {
            a = prog.at(indexx++);
        }
        if (a == '+')
            result = Exp2(result + Term());  //handles T+T
        else if (a == '-')
            result = Exp2(result - Term());  //handles T-T
    }
    return result;
}

// Read the string char by char
// Handle the space by skiping
// Perform the grammer
// Handles "*" , "/" , "+" , "-" , ")"

int Term2(int inp)
{
    
    int result = inp;
    if (indexx < prog.length())   //if not the end of program string
    {
        char a = prog.at(indexx++); //get one chr from program string
        while (a == ' ' && indexx < prog.length()) // if space skip and read until a char
        {
            a = prog.at(indexx++);
        }
        if (a == '*')
            result = Term2(result * Fact()); //handles consecutive * operators
        else if (a == '/')
            result = Term2(result / Fact()); //handles consecutive / operators
        else if (a == '+' || a == '-'|| ')')     //if " + , -,or )" get back one position
            indexx--;
    }
    return result;
}

//Calling the function as grammer indicates
//returns the Fact2 funtion with a parameter of Num


int Fact()
{
    
    return Fact2(Num());
}

// Read the string char by char
// Handle the space by skiping
// Perform the grammer
// Handles power ^

int Fact2(int inp)
{
    
    int result = inp;
    char a = prog.at(indexx++); //get one chr from program string
    while (a == ' ' && indexx < prog.length()) // if space skip and read until a char
    {
        a = prog.at(indexx++);
    }
    if (a == '^') //handles consecutive / operators
        result = Fact2(pow(result, Fact()));
    else
        indexx--;
    
    return result;
}

// Read the string char by char
// Handle the space by skiping
// Perform the grammer
// Handles "("
// return by converts a char to a numeric number and return

int Num()
{
    
    char a = prog.at(indexx++); //get one chr from program string
    while (a == ' ' && indexx < prog.length()) // if space skip and read until a char
    {
        a = prog.at(indexx++);
    }
    if (a == '(') // handles the "("
        return Exp();
    else
        return atoi(&a); //converts a char to a numeric number and return
}
