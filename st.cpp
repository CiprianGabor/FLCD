#include <iostream>
#include <vector>
#include <algorithm>

#include <string>
#include <fstream>
#include <utility>
using namespace std;

class SymbolTable
{
  //size of the symbol table
  int size;

  // Pointer to an vector containing elements

public:
  vector<string> *table;

  SymbolTable(int size)
  {
    this->size = size;
    table = new vector<string>[size];
  }

  // inserts a element into symbol table
  void insertElement(string element)
  {

    if (exists(element) == false)
    {
      int index = hashFunction(element);
      table[index].push_back(element);
    }
  }
  //check if the element is already in the table
  int exists(string element)
  {
    for (int i = 0; i < size; i++)
      if (std::find(table[i].begin(), table[i].end(), element) != table[i].end())
      {
        return true;
      }
    return false;
  }

  // functions that indicates the index in the table
  int hashFunction(string element)
  {
    //sum will return the sum of all chars in ascii
    int sum = 0;
    for (int i = 0; i < element.size(); i++)
    {
      sum = sum + int(element[i]);
    }

    return (sum % size);
  }

  // function to print the symbol table *looks nice :D*
  void printSymbolTable()
  {
    cout << "  ______________________________" << endl;
    cout << " | INDEX | ELEMENTS             |" << endl;
    cout << " |______________________________|" << endl;
    for (int i = 0; i < size; i++)
    {
      cout << " |   " << i << "   | ";
      for (auto element : table[i])
        cout << "'" << element << "'  ";

      cout << endl;
      cout << " |_______|______________________|" << endl;
    }
  }
};
vector<pair<string, int>> my_pifs;

void addToPIF(string word, int index)//add variable
{
  pair<string, int> my_pair;
  my_pair.first = word;
  my_pair.second = index;
  my_pifs.push_back(my_pair);
}
void addToPIF0(char word)//add a const or del
{
  pair<string, int> my_pair;
  string my_word;
  my_word += word;
  my_pair.first = my_word;
  my_pair.second = 0;
  my_pifs.push_back(my_pair);
}
void checkDelimeters(string word, int line)//check the number of ()/[]/""
{
  int n = count(word.begin(), word.end(), '(') + count(word.begin(), word.end(), ')') + count(word.begin(), word.end(), '"');
  string error = "The program cant compute on the line " + to_string(line);
  if (n % 2 != 0) //daca n este impar inseamna ca lipseste o paranteza
    throw error;
}

void readFull(SymbolTable st, string filename,vector<string> allTokens)
{

  int line=0;
  fstream file;
  string word;
  file.open(filename);
  while (file >> word)
  {
    line++;
    string possibleDot="";
    if(word[word.size()-1]=='.'||word[word.size()-1]==',' ||word[word.size()-1]==',') //check for possible ./;/,
    {
      addToPIF0(word[word.size()-1]);
      word.pop_back();
    }
    string possibleToken = "";
    possibleToken += word[0];
    if (std::find(allTokens.begin(), allTokens.end(), possibleToken) != allTokens.end()) //this will check inside delimeters
    {
      checkDelimeters(word, line); //check if misses something
      addToPIF0(word[0]);
      string miniword = "";
      for (int i = 1; i < word.size(); i++)
      {
        possibleToken = "";
        possibleToken += word[i];
        if (std::find(allTokens.begin(), allTokens.end(), possibleToken) != allTokens.end()) //possible < > =
        {
          if (miniword.size() == 0)
            addToPIF0(word[i]); 
          else
          {
            st.insertElement(miniword); //add variable in st and pif
            addToPIF(miniword, st.hashFunction(miniword));
            addToPIF0(word[i]);
            miniword = "";
          }
        }
        else
          miniword += word[i]; //possible variable
      }
    }
    else
    {

      if (std::find(allTokens.begin(), allTokens.end(), word) != allTokens.end())
        addToPIF(word, 0); //check for specific words like read/show
      else
      {
        st.insertElement(word); //insert variables
        addToPIF(word, st.hashFunction(word));
      }
    }
  }

  for (int i = 0; i < my_pifs.size(); i++)
    cout << my_pifs[i].first << "  " << my_pifs[i].second << endl;

  st.printSymbolTable();
}

int main()
{
  SymbolTable st(7);
  
  vector<string> allTokens; //read tokens
  fstream tokenfile;
  string tokens;
  tokenfile.open("tokens.txt");
  while (tokenfile >> tokens)
  {
    allTokens.push_back(tokens);
  }
  tokenfile.close();


  try
  {
    readFull(st, "a.txt",allTokens);
    //readFull(st, "b.txt",allTokens);
    //readFull(st, "c.txt",allTokens);
    //readFull(st, "error.txt",allTokens); //this will throw an error
  }
  catch (string msg)
  {
    cout << msg;
  }

  return 0;
}