#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"
#include <iostream>
using namespace std;

class Admin : public User {
public:
    Admin(string n="", string i="", string p="") : User(n,i,p), key('K') {}
    void display() override { cout<<"ADMIN: "<<name<<"\n"; }
    void menu() override;
    void addBanker(string n);
    void removeBanker(string i);
    void viewBankers();
    void setKey(char k) { key=k; cout<<"Key set to '"<<k<<"'\n"; }
private:
    char key;
};
#endif