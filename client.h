#ifndef CLIENT_H
#define CLIENT_H
#include "user.h"
#include <iostream>
using namespace std;

class Client : public User {
public:
    Client(string n="", string i="", string p="") : User(n,i,p) {}
    void display() override { cout<<"CLIENT: "<<name<<" ("<<id<<")\n"; }
    void menu() override;
    void viewAccount();
    void withdraw(double amt);
    void deposit(double amt);
    void transfer(string to, double amt);
};
#endif