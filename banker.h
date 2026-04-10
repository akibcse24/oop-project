#ifndef BANKER_H
#define BANKER_H
#include "user.h"
#include <iostream>
using namespace std;

class Banker : public User {
public:
    Banker(string n="", string i="", string p="") : User(n,i,p) {}
    void display() override { cout<<"BANKER: "<<name<<" ("<<id<<")\n"; }
    void menu() override;
    void addAccount(string cn);
    void removeAccount(string id);
    void viewAccounts();
    void blockTransfer(string id);
};
#endif