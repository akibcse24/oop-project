#include "banker.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
void Banker::addAccount(string cn) {
    int id=1; ifstream f("clients_db.txt"); string line; bool skip=false;
    while(getline(f,line))
        if(skip) { size_t t=line.find('\t')+1; string u=line.substr(t,line.find('\t',t)-t); if(u.length()>2 && u.substr(0,2)=="ac") id=max(id,stoi(u.substr(2))); } else skip=true;
    f.close(); int p=1000+(rand()%9000), newId=id+1;
    string idStr="ac"+string(5-to_string(newId).length(),'0')+to_string(newId);
    ofstream of("clients_db.txt",ios::app);
    of<<cn<<"\t"<<idStr<<"\t"<<encrypt(to_string(p))<<"\t0\n"; of.close();
    cout<<"\nClient Created:\nName: "<<cn<<"\nID: "<<idStr<<"\nPassword: "<<p<<"\n";
}
void Banker::removeAccount(string uid) {
    ifstream f("clients_db.txt"); string line, res=""; bool skip=false;
    while(getline(f,line)) {
        if(!skip) { skip=true; res+=line+"\n"; continue; }
        if(line.find(uid)==string::npos) res+=line+"\n";
    }
    f.close(); ofstream of("clients_db.txt"); of<<"N\tI\tP\tB\n"<<res; of.close();
}
void Banker::viewAccounts() {
    ifstream f("clients_db.txt"); string line;
    while(getline(f,line)) cout<<line<<"\n";
    f.close();
}
void Banker::blockTransfer(string uid) {
    ifstream f("clients_db.txt"); string line, res=""; bool skip=false;
    while(getline(f,line)) {
        if(!skip) { skip=true; res+=line+"\n"; continue; }
        if(line.find(uid)!=string::npos) res+=line.substr(0,line.rfind('\t'))+"\tBLOCKED\n"; 
        else res+=line+"\n";
    }
    f.close(); ofstream of("clients_db.txt"); of<<"N\tI\tP\tB\n"<<res; of.close();
}

void Banker::menu() {
    for(int op;cout<<"\n1.Add \n2.Remove \n3.View \n4.Block \n5.Exit\n> ",cin>>op,op!=5;) {
        if(op==1) { string n; cout<<"Name: "; cin>>n; addAccount(n); cout<<"OK\n"; }
        else if(op==2) { string i; cout<<"ID: "; cin>>i; removeAccount(i); cout<<"OK\n"; }
        else if(op==3) viewAccounts();
        else if(op==4) { string i; cout<<"ID: "; cin>>i; blockTransfer(i); cout<<"OK\n"; }
    }
}