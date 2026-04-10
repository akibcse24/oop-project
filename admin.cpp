#include "admin.h"
#include <fstream>
#include <iostream>
using namespace std;

void Admin::addBanker(string n) {
    int id=1; ifstream f("banker_db.txt"); string line; bool skip=false;
    while(getline(f,line))
        if(skip) { size_t t=line.find('\t')+1; string u=line.substr(t,line.find('\t',t)-t); if(u.length()>1) id=max(id,stoi(u.substr(1))); } else skip=true;
    f.close(); int p=1000+(id%9000);
    ofstream of("banker_db.txt",ios::app);
    of<<n<<"\tb"<<id+1<<"\t"<<encrypt(to_string(p))<<"\t50000\n"; of.close();
}

void Admin::removeBanker(string bid) {
    ifstream f("banker_db.txt"); string line, res=""; bool skip=false;
    while(getline(f,line)) {
        if(!skip) { skip=true; res+=line+"\n"; continue; }
        if(line.find(bid)==string::npos) res+=line+"\n";
    }
    f.close(); ofstream of("banker_db.txt"); of<<"N\tI\tP\tS\n"<<res; of.close();
}

void Admin::viewBankers() {
    ifstream f("banker_db.txt");
    string line;
    while(getline(f,line)) cout<<line<<"\n";
    f.close();
}

void Admin::menu() {

    for(int op;cout<<"\n1.Hax \n2.Add \n3.Remove\n4.View \n5.Exit\n> ",cin>>op,op!=5;) {
        if(op==1) { char k; cout<<"Key: "; cin>>k; setKey(k); }
        else if(op==2) { string n; cout<<"Name: "; cin>>n; addBanker(n); cout<<"OK\n"; }
        else if(op==3) { string i; cout<<"ID: "; cin>>i; removeBanker(i); cout<<"OK\n"; }
        else if(op==4) viewBankers();
    }
}
