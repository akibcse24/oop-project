#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "signin.h"
using namespace std;

int main() {
    srand(time(0));
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    ifstream f("banner.txt");
    for (string s; getline(f, s); ) cout << s << '\n';
    User* u = login();
    if(!u) return 1;
    u->display();
    u->menu();
    delete u;
    return 0;
}
