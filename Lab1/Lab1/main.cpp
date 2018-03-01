/////////////////////////////////////////////
//// Interpreter for simplified infix expression with +,-,*,/.
//// Keyboard input, single digit numbers only and no spaces are allowed.
//// compile:  $>g++ prog1.cpp
//// run with: >2+3*4/2+3+4*2
//// text editor Visual studio code
//// terminal  clang
/////////////////////////////////////////////

#include <cstdlib> //for atoi()
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int Exp(), Term(), Exp2(int), Term2(int), Fact();
ifstream fin;
string prog, s1; //string for reading 1-line input program
int indexx = 0; //global index for program string

// main program reads a file line by line in string
// call the other function

int main(int argc, const char **argv)
{ cout<<">";
    string path1 = argv[1];
    fin.open(path1.c_str()); // open data file
    getline(fin, s1);  //read 1 line into string
    while (!fin.eof())
    {
        prog += s1; // extend prog string with s1
        getline(fin, s1); // read next line if any
    }
    //cin>>prog;  //reads 1-line input expression (program)
    cout<<" string = "<<prog<<endl;
    cout<<"result= "<<Exp()<<endl;
}

int Exp()
{ return Exp2(Term());
}

int Term()
{ return Term2(Fact());
}


//

int Exp2(int inp)
{
    int result = inp;
    if (indexx < prog.length())   //if not the end of program string
    {
        char a = prog.at(indexx++); //get one chr from program string
        while (a == ' ' && indexx < prog.length()) // if space skip and read until a char{
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


int Term2(int inp)
{
    
    int result = inp;
    if (indexx < prog.length())   //if not the end of program string
    {
        char a = prog.at(indexx++); //get one chr from program string
        while (a == ' ' && indexx < prog.length()) // if space skip and read until a char{
        {
            a = prog.at(indexx++);
        }
        if (a == '*')
            result = Term2(result * Fact()); //handles consecutive * operators
        else if (a == '/')
            result = Term2(result / Fact()); //handles consecutive / operators
        else if (a == '+' || a == '-')     //if + or -, get back one position
            indexx--;
    }
    return result;
}

int Fact()
{
    char a = prog.at(indexx++); //get one chr from program string
    while (a == ' ' && indexx < prog.length()) // if space skip and read until a char{
    {
        a = prog.at(indexx++);	
    }
    return atoi(&a); //converts a char to a numeric number and return
}
