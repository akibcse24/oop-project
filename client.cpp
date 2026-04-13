#include "client.h"
#include <fstream>
using namespace std;
void updateBalance(User* u, double amt, bool add) {
    ifstream in("clients_db.txt"); string line, res=""; bool skip=false;
    while(getline(in,line)) {
        if(!skip) { skip=true; res+=line+"\n"; continue; }
        size_t p1=line.find('\t'), p2=line.find('\t',p1+1);
        if(p1!=string::npos && line.substr(p1+1,p2-p1-1)==u->id)
            res+=line.substr(0,line.rfind('\t'))+"\t"+to_string(add?stod(line.substr(line.rfind('\t')+1))+amt:stod(line.substr(line.rfind('\t')+1))-amt)+"\n";
        else res+=line+"\n";
    }
    in.close(); ofstream("clients_db.txt") << "N\tI\tP\tB\n" << res;
}
void Client::viewAccount() { ifstream f("clients_db.txt"); string line; bool skip=false;
    while(getline(f,line)) if(!(skip=true)) {} else {
        size_t p1=line.find('\t'), p2=line.find('\t',p1+1);
        if(line.substr(p1+1,p2-p1-1)==id) { cout<<line<<"\n"; break; }
    }
    f.close();
}
void Client::withdraw(double a) { updateBalance(this, a, false); }
void Client::deposit(double a) { updateBalance(this, a, true); }
void Client::transfer(string to, double a) {
    ifstream f("clients_db.txt"); string line; double my=0, t=0; bool skip=false;
    while(getline(f,line)) if(skip) {
        size_t p1=line.find('\t'), p2=line.find('\t',p1+1);
        if(line.substr(p1+1,p2-p1-1)==id) my=stod(line.substr(line.rfind('\t')+1));
        if(line.find(to+"\t")==0) t=stod(line.substr(line.rfind('\t')+1));
    } else skip=true;
    f.close(); if(my<a) return;
    f.open("clients_db.txt"); string res=""; skip=false;
    while(getline(f,line)) {
        if(!skip) { skip=true; res+=line+"\n"; continue; }
        size_t p1=line.find('\t'), p2=line.find('\t',p1+1);
        if(line.find(to+"\t")==0) res+=line.substr(0,line.rfind('\t')+1)+to_string(t+a)+"\n";
        else if(line.substr(p1+1,p2-p1-1)==id) res+=line.substr(0,line.rfind('\t')+1)+to_string(my-a)+"\n";
        else res+=line+"\n";
    }
    f.close(); ofstream("clients_db.txt") << "N\tI\tP\tB\n" << res;
}
void Client::menu() {
    ifstream f("banner.txt");
    for (string s; getline(f, s); ) cout << s << '\n';
    f.close();
    for(int op;cout<<"\n1.View \n2.Withdraw \n3.Deposit \n4.Transfer \n5.Exit\n> ",cin>>op,op!=5;)
        if(op==1) viewAccount(); else if(op==2) { double x; cin>>x, withdraw(x), cout<<"OK\n"; }
        else if(op==3) { double x; cin>>x, deposit(x), cout<<"OK\n"; }
        else if(op==4) { string t; double x; cin>>t>>x, transfer(t,x), cout<<"OK\n"; }
}