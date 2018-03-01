

//// Simulation for dyanmic memory (heap) allocation/deallocation (garbage collection)
////
//// The program is start with the menu has several options.
//// User select option from menu to perform action.
//// It has data grid is struct with elements key, next and mark.
//// In the memory allocation part, linked-lists are manipulated.
//// For the memory deallocation, we use the
//// lazy garbage collection mechanism that has mark and sweep phases.
//// Assume that the size of the simulated dynamic memory is 10 cells and
//// each cell consists of three fields,
//// i.e. key, next, and mark_bit (initialized with 0).
//// For this practice, we use two linked lists (list1, list2)
//// whose head pointers are named L1 and L2.
//// Initially, the free-list (head pointer name: Free) contains all the cells
//// L1 = -1, L2 = -1, and Free = 1.
////
////
////
//// The initial memory configuration is:
//// ________________________________________________
//// index [1] [2] [3] [4] [5] [6] [7] [8] [9] [10]  |
//// ------------------------------------------------
//// Key   [0] [0] [0] [0] [0] [0] [0] [0] [0] [0]   |
//// ------------------------------------------------
//// next  [2] [3] [4] [5] [6] [7] [8] [9] [10] [-1] |
//// ------------------------------------------------
//// mark  [0] [0] [0] [0] [0] [0] [0] [0] [0] [0]   |
//// ------------------------------------------------
////   L1 = -1 , L2 = -1 , Free = 1 //head pointer for list1, list2 ,and free-list
////
//// Created by Harkaranjeet Singh on 10/28/17.
//// Copyright © 2017 Harkaranjeet Singh. All rights reserved.
////
/////////////////////////////////////////////

#include <iostream>
#include <string>          //for string
using namespace std;

void insert (int &Head, int _Key);          //Insert function
void Delete (int &Head, int _Key);          //Delete function
void garbage_collect(bool Mark = false);    //Garabage collection function
void My_dataGrid();                         //Datagrid function
void Print_memory();                        //Print memory function
void Menu();                                //Menu function


// Struct for datagrid has key, next and mark.

struct datagrid
{
    int key;        //integer for key
    int next;       // integer for next
    bool mark;      // Boolean for mark
};


datagrid mydatagrid[10];                    //Datagrid has 10 field of each key, next and mark

// Intialize the head pointer
int L1, L2, Free;

// Main function calls functions for building data grid and Menu
int main(int argc, const char **argv)
{
    
    My_dataGrid();              // calling the dataGrid function
    Menu();                     // calling Menu function
    return 0;
}

// Building data grid with intialize headers
// Assigin the value to grid
// Setting up the struct
void My_dataGrid()
{
    //initialization
    L1 = -1;
    L2 = -1;
    Free = 1;
    
    mydatagrid[10 - 1].next = -1;
    for (int i = 0; i < 10 - 1; i++)
    {
        mydatagrid[i].key = 0;
        mydatagrid[i].next = i + 2;
        mydatagrid[i].mark = false;
    }
    
}

// This function is for display menu in program
// Menu has option for Print, Insert , Delete , Garbage Collect and Quit
//

void Menu()
{
    int _List;
    int _Key;
    int Selection;
    bool Exit = false;
    
    // While loop runs until user select option for quit
    // Select option for each case
    // Case will perform its function
    while (!Exit)
    {
        cout << "Please choose Selection and press enter\n";
        cout << "0] Print Memory\n1] Insert\n2] Delete\n3] Garbage Collect\n4] Quit" << endl;
        
        cin >> Selection;
        switch (Selection)
        {
            case 0:
                cout << "--------------- Memory ----------------" << endl;
                Print_memory();                     // call Print memory function
                cout <<"-----------------------------------------"<<endl;
                break;
                
            case 1:
                cout << "\nDo you want to insert into list 1 or list 2? Enter 1 or 2\n";
                cin >> _List;
                cout << "\nWhat value do you want to insert?\n";
                cin >> _Key;
                if (_List == 1)
                    insert(L1, _Key);              // call Insert function with paramenter
                else if (_List == 2)
                    insert(L2, _Key);              // call Insert function with paramenter
                else
                    cout << "Error: Invalid Entry" << endl;
                break;
                
            case 2:
                cout << "\nDo you want to delete from list 1 or list 2? Enter 1 or 2\n";
                cin >> _List;
                cout << "\nWhat value do you want to delete?\n";
                cin >> _Key;
                if (_List == 1)
                    Delete(L1, _Key);               // call Delete function with paramenter
                else if (_List == 2)
                    Delete(L2, _Key);               // call Delete function with paramenter
                else
                    cout << "Error: Invalid Entry" << endl;
                break;
                
            case 3:
                cout << "------------- Collecting garbage -------------" << endl;
                garbage_collect();                  // call garabage collection function with paramenter
                cout << "-------------- Garbage Collected -------------" << endl;
                break;
                
            case 4:
                cout << "---------------------Quit---------------------" << endl;
                Exit = true;                       // setting boolean to true for breaking while loop
                break;
            default:
                cout << "Error: Invalid Entry" << endl;
                break;
        };
  
}

}

// This function prints out the data grid
// It display the Key, next and mark
// it also head pointers
void Print_memory()
{

    cout << " \t";
    for (int i = 1; i <= 10; i++)
    {
        cout << "[" <<i<< "] ";
        
    }
    
    cout << "\n\nKey\t";
    for (int i = 0; i < 10; i++)
    {
        cout << "[" << mydatagrid[i].key << "] ";
        
    }
    
    cout << "\nNext\t";
    for (int i = 0; i < 10; i++)
    {
        cout << "[" << mydatagrid[i].next << "] ";
    }
    
    cout << "\nMark\t";
    for (int i = 0; i < 10; i++)
    {
        cout << "[" << mydatagrid[i].mark << "] ";
    }
    cout << "   \n    L1=" << L1<< ",   L2=" << L2<< ",  Free= " << Free<<"\n";
}


// This function insert the value in specific list by user
// garbage collection will be called fromn this function if there is no free spce
// It has error checking

void insert (int &Head, int _Key)
{
    int i, j;
    i = Free - 1;
    

    if (i + 1 == -1)
        garbage_collect();          //calling garabage collect function if no free nodes
    
    i = Free - 1;
    
    
//    if (i + 1 == -1)
//    {
//        cout << "Segmentation Fault" << endl;
//        return;
//    }
//    
//    else
//    {
    
        Free = mydatagrid[i].next;
        
        
        if (Head == -1)
        {
            Head = i+1;
        }
        
        
        mydatagrid[i].key = _Key;
        mydatagrid[i].next = -1;
        
        
        j = Head - 1;
        while (mydatagrid[j].next != -1)
        {
            j = mydatagrid[j].next - 1;
        }
        if (i != j)
            mydatagrid[j].next = i + 1;
  //  }
    
}

// This function Delete the value specific list by user
// Searches the key and delete the key value from specific list
//
void Delete (int &Head, int _Key)
{
    int i, prev_, next_;
    
    i = Head;
    prev_ = -1;

    while (mydatagrid[i - 1].key != _Key && i != -1)
    {
        prev_ = i;
        i = mydatagrid[i - 1].next;
    }
    

    if (i == -1)
        cout << "Error: Invalid Key" << endl;
    
    else
    {

        next_ = mydatagrid[i-1].next;
        
        if (prev_ != -1)
            mydatagrid[prev_ - 1].next = next_;
        else
            Head = next_;
    }
    
}


void garbage_collect(bool Mark)
{
    int i;
    
    i = L1 - 1;
    while (i + 1 != -1)
    {
        mydatagrid[i].mark = true;
        i = mydatagrid[i].next - 1;
    }
    
    i = L2 - 1;
    while (i + 1 != -1)
    {
        mydatagrid[i].mark = true;
        i = mydatagrid[i].next - 1;
    }
    
    i = Free - 1;
    while (i + 1 != -1)
    {
        mydatagrid[i].mark = true;
        i = mydatagrid[i].next - 1;
    }
    
    if (Mark)
        Print_memory();
    
    
    for (i = 0; i < 10; i++)
    {
        
        if (!mydatagrid[i].mark)
        {
            mydatagrid[i].key = 0;
            mydatagrid[i].next = Free;
            Free = i + 1;
        }
        mydatagrid[i].mark = 0;
    }
}


