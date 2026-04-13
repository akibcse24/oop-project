#ifndef USER_H
#define USER_H
#include <string>
#include <fstream>
using namespace std;

class User {
public:
    string name, id, pwd;
    char key;
    User(string n="", string i="", string p="") : name(n), id(i), pwd(p), key('K') {}
    virtual ~User() {}
    virtual void display() = 0;
    virtual void menu() = 0;
    string encrypt(string s) const { string r=""; for(char c:s) r+=char(c^key); return r; }
    string decrypt(string s) const { return encrypt(s); }
    friend void updateBalance(User* u, double amt, bool add);
    friend bool findUser(User* u, string db);
    friend void updateDB(User* u, const string& file, const string& data);
protected:
    // Helper to extract numeric part from ID strings
    static int extractIdNumber(const string& id, const string& prefix);
    
    // Helper to generate formatted ID with leading zeros
    static string generateFormattedId(int number, const string& prefix, int totalLength);
    
    // Helper to generate random password
    static int generatePassword();
};

#endif
