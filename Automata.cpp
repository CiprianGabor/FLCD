#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

 class Transition
 {
     public:
         string initialState;
         string literal;
         string nextState;
         Transition(string i,string l,string n){
         this->initialState=i;
         this->literal=l;
         this->nextState=n;
        }
         string getInitialState()
         {
             return this->initialState;
         }
         string getLiteral()
         {
             return this->literal;
         }
         string getNextState()
         {
             return this->nextState;
         }
         void print(){
                cout<<this->initialState<<" -- "<<this->literal<<" ==> "<<this->nextState<<endl;
         }

     
 };
class Automata
{
    public:
    vector<string> states;
    vector<string> alphabet;
    string initialState;
    vector<string> finalStates;
    vector<Transition> transitions;
    bool DFA=false;
    Automata(string filename)
    {
        readData(filename);
        checkTran();
    }
    void checkTran(){
        for(Transition tr1 : this->transitions)
        {
            int i=0;
            for(Transition tr2:this->transitions)
            {
                if(tr1.initialState==tr2.initialState&&tr1.literal==tr2.literal)
                    i++;
            }
            if(i>=2)
                return;
        }
        this->DFA=true;
    }
    void checkSequence(string sequence){
        string sq="";
        sq+=sequence[0];
        string nextState;
        for(Transition tr:this->transitions)
            {
                if(tr.initialState==this->initialState&&sq==tr.literal)
                {
                    nextState=tr.nextState;
                    break;
                }
            }
        
        for(int i=1;i<sequence.size();i++)
        {   
            sq="";
            sq+=sequence[i];
            for (Transition tr:this->transitions)
                if(tr.initialState==nextState&&sq==tr.literal)
                {
                    nextState=tr.nextState;
                    break;
                }
            
        }
        for(string s :this->finalStates)
        {
            if(s==nextState)
                {
                    cout<<"Accepted!";
                    return;
                }
        }
        cout<<"Not Accepted";

    }
    void readData(string filename){
        ifstream myFA(filename);
        //read states
        string statesString;
        getline(myFA,statesString);
        stringstream str(statesString);
        
        while(str.good()){
            string state;
            getline(str,state,',');
            this->states.push_back(state);
        }//read states done

        //read alphabet
        string alphabetString;
        getline(myFA,alphabetString);
        stringstream str2(alphabetString);
        
        while(str2.good()){
            string state;
            getline(str2,state,',');
            this->alphabet.push_back(state);
        }//read alphabet done
        
        getline(myFA,this->initialState);//get initial state

        //read finalStates
        string finalStatesString;
        getline(myFA,finalStatesString);
        stringstream str3(finalStatesString);
        
        while(str3.good()){
            string state;
            getline(str3,state,',');
            this->finalStates.push_back(state);
        }//read finalStates done
        
        string transitionString;
        //read each transition
        while(getline(myFA,transitionString))
        {
            stringstream str4(transitionString);
            string initialStateTranstion;
            getline(str4,initialStateTranstion,',');
            string literalTranstion;
            getline(str4,literalTranstion,',');
            string nextStateTranstion;
            getline(str4,nextStateTranstion,',');
            Transition tr=Transition(initialStateTranstion,literalTranstion,nextStateTranstion);
            this->transitions.push_back(tr);
        }


    }

    void printInitialState(){
        cout<<"Initial State= "<<this->initialState<<endl;
    }
    void printTransitions()
    {
        cout<<"Transtions: "<<endl;
        for(Transition tr : this->transitions)
                tr.print();
        cout<<endl;
    }
     
    void printStates()
    {
        cout<<"States= ";
        for(string s : this->states)
                cout<<s<<"  ";
        cout<<endl;
    }
    void printFinalStates()
    {
        cout<<"Final States= ";
        for(string s : this->finalStates)
                cout<<s<<"  ";
        cout<<endl;
    }
    void printAlphabet()
    {
        cout<<"Alphabet= ";
        for(string s : this->alphabet)
                cout<<s<<"  ";
        cout<<endl;
    }
};

void printMenu()
{
    cout<<endl<<endl;
    cout<<"1---Print set of states"<<endl;
    cout<<"2---Print alphabet"<<endl;
    cout<<"3---Print all transition"<<endl;
    cout<<"4---Print set of final states"<<endl;
    cout<<"5---Insert a sequence"<<endl;
    cout<<"0---Exit"<<endl;
    cout<<"Choose a number:  ";
}
void run()
{
    Automata at=Automata("FA.in");
    int a;
    while(true)
    {
        printMenu();
        
        cin>>a;
        cout<<endl;
        if(a==1)
        {
            at.printStates();
        }
        else if(a==2)
        {
            at.printAlphabet();
        }
        else if(a==3)
        {
            at.printTransitions();
        }
        else if(a==4)
        {
            at.printFinalStates();
        }
        else if(a==5){
            if(at.DFA==false)
                cout<<"Not a DFA!!!";
            else
            {
                string sequence;
                cin>>sequence;
                at.checkSequence(sequence);
            }
            
        }
        else
        {
            break;
        }
        
    }

}

int main(){
    run();
    return 0;
}