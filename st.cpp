#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include <string>


class SymbolTable 
{ 
    //size of the symbol table
    int size; 
    // Pointer to an vector containing elements 
    vector<string> *table; 
public: 
    
    SymbolTable(int size)
    { 
        this->size = size; 
        table = new vector<string>[size]; 
    }    
  
    // inserts a element into symbol table 
    void insertElement(string element) 
    { 
        
        if(exists(element)==false)
        {
            int index = hashFunction(element); 
            table[index].push_back(element);  
        }       


    } 
    //check if the element is already in the table
    int exists(string element)
    {
        for(int i=0;i<size;i++)
             if(std::find(table[i].begin(), table[i].end(), element) != table[i].end())
             {
                 return true;
            }  
        return false;
    }
  
    // functions that indicates the index in the table
    int hashFunction(string element) { 
      //sum will return the sum of all chars in ascii
        int sum = 0;
        for (int i = 0; i<element.size(); i++)
        {
            sum = sum + int(element[i]);
        }
        
        return (sum%size); 
    } 
  
    // function to print the symbol table *looks nice :D*
    void printSymbolTable()
     { 
         cout<<"  ______________________________"<<endl;
         cout<<" | INDEX | ELEMENTS             |"<<endl;
         cout<<" |______________________________|"<<endl;
        for (int i = 0; i < size; i++) 
        { 
            cout <<" |   "<< i << "   | "; 
            for (auto element : table[i]) 
              cout <<  "'" << element << "'  "; 
              
            cout << endl;
            cout<<" |_______|______________________|"<<endl;
 
        } 
      } 
}; 
   
int main() 
{ 
  SymbolTable st(7); 

  st.insertElement("abc");
  st.insertElement("abc");
  st.insertElement("cba");
  st.insertElement("cab");
  st.insertElement("cipri");
  st.insertElement("cipri");
  st.insertElement("dan");
 
  st.printSymbolTable(); 
  
  return 0; 
} 