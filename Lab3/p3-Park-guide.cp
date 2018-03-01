#include <cstdlib> //for atoi()
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
ifstream fin;
string prog, s1, s2;
int indexx = 0; //global index for program string
int sym_index = 0; //global for symbol table index

struct node
{ char id; //single letter var name
  string type;
  double value;
};
struct node sym_table[100]; //symbol table with 100 entries

void declarations();
void declaration(string);
void statements();
void statement(string);
void assign_state(string);
void print_state();
int get_sym_index(char);/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////int main(int argc, const char **argv){ string path1 = argv[1];
  fin.open(path1.c_str()); //open data file

  fin>>s1;
  if(s1 == "program")
  { declarations();

    /****display symbol_table entries****/
    cout<<"++symbol table++"<<endl;
    for(int i=0; i<sym_index; i++)
      cout<<sym_table[i].id<<"   "<<sym_table[i].type<<"   "<<sym_table[i].value<<endl;
    /************************************/
      
    statements();
  }
  else
    cout<<"usage: program {<declarations>} begin {<statements>} end"<<endl;

  fin.close();
  return 0;
}


void declarations() //recursively calls declaration()
{
  string word;
  fin>>word;

  if( word == "begin")
    return;
  else if(word=="int" || word=="double") 
    declaration(word); //for one line of declaration until ';' 
  else
  { cout<<"syntax error: usage: <type> <id> {,<id>} ;"<<endl;
    return; //or exit(1) to terminate the interpreter
  }

  declarations(); //recursion for next declaration
}    


void declaration(string word) //para is type (int or double)
{
  string s1;
  fin>>s1; //assume a, or a; cases
  while(s1.at(1) == ',')
  {
    sym_table[sym_index].id = s1.at(0); //id is char type
    sym_table[sym_index].type = word;
    sym_index++;
    fin>>s1;
  }
  if (s1.at(1) == ';')
  { sym_table[sym_index].id = s1.at(0); //id is char type
    sym_table[sym_index].type = word;
    sym_index++;
  }
  else
  { cout<<"syntax error: missing ;"<<endl;
    //may use exit(1) to terminate the interpreter
  }
}


void statements()
{ 
  string word;
  fin>>word;
  if(word == "end")
    return;
  else
    statement(word); //for single statement

  statements(); //recursion for next single statement
}

void statement(string word)
{
  if(word == "print")
    print_state();
  else if (word.length()==1 && isalpha(word.at(0)))
    assign_state(word);
  else
  { cout<<"syntax error: invalid statement"<<endl;
    //may use exit(1); to terminate interpreter
  }
}


void assign_state(string word)
{ cout<<"=== in assign_state()"<<endl;
  getline(fin, s2); //reads entire line 

}


void print_state()
{ cout<<"=== in print_state()"<<endl;
  getline(fin, s2); //reads entire line

}
