#include "signin.h"
#include "client.h"
#include "banker.h"
#include "admin.h"
#include <fstream>
#include <iostream>
using namespace std;

bool init() {
    ifstream f1("clients_db.txt"), f2("banker_db.txt");
    if(!f1.good()) { ofstream of("clients_db.txt"); of<<"N\tI\tP\tB\n"; of.close(); }
    if(!f2.good()) { ofstream of("banker_db.txt"); of<<"N\tI\tP\tS\n"; of.close(); }
    return true;
}

bool verify(User* u, string db) {
    ifstream f(db);
    string line;
    bool skip=false;
    while(getline(f,line))
        if(skip) {
            size_t p1=line.find('\t'), p2=line.find('\t',p1+1);
            if(p1!=string::npos && p2!=string::npos) {
                string id_in_file=line.substr(p1+1,p2-p1-1);
                if(id_in_file==u->id) {
                    string pwd_in_file=line.substr(p2+1,line.find('\t',p2+1)-p2-1);
                    return u->decrypt(pwd_in_file)==u->pwd;
                }
            }
        } else skip=true;
    return false;
}

User* login() {
    init();
    for(int i=0;i<3;i++) {
        string u, p;
        cout<<"User: "; cin>>u; cout<<"Pass: "; cin>>p;
        if(u=="admin" && p=="admin123") { cout<<"OK\n"; return new Admin("admin","admin",p); }
        User* user = u.substr(0,2)=="ac" ? (User*)new Client("",u,p) : (User*)new Banker("",u,p);
        if(verify(user, u.substr(0,2)=="ac" ? "clients_db.txt" : "banker_db.txt")) { cout<<"OK\n"; return user; }
        delete user;
    }
    return nullptr;
}